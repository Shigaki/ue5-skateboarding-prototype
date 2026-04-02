// Fill out your copyright notice in the Description page of Project Settings.


#include "NgpUnrealDevTask/Public/Systems/TraversalScoring/NGPTraversalScoreComponent.h"

#include "Core/NGPPlayerState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Helpers/NGPCvarManager.h"
#include "Systems/TraversalScoring/NGPObstacleInterface.h"
#include "Systems/TraversalScoring/NGPTraversalDeveloperSettings.h"

#define NGP_OBSTACLE_CHANNEL ECC_GameTraceChannel1

class UNGPTraversalDeveloperSettings;

UNGPTraversalScoreComponent::UNGPTraversalScoreComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UNGPTraversalScoreComponent::BeginPlay()
{
    Super::BeginPlay();

    if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
    {
        Owner->MovementModeChangedDelegate.AddDynamic(this, &UNGPTraversalScoreComponent::OnMovementModeChanged);
    }
}

void UNGPTraversalScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (ComboTimeRemaining > 0.0f)
    {
        ComboTimeRemaining -= DeltaTime;
        if (ComboTimeRemaining <= 0.0f)
        {
            CurrentMultiplier = 1;
            OnComboReset.Broadcast();
        }
    }

    if (!bIsAirborne)
    {
        return;
    }
    
    const UNGPTraversalDeveloperSettings* Settings = GetDefault<UNGPTraversalDeveloperSettings>();
    SweepAccumulator += DeltaTime;
    if (SweepAccumulator >= Settings->SweepInterval)
    {
        SweepAccumulator = 0.f;
        TickSweep();
    }
}

void UNGPTraversalScoreComponent::OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode,
    uint8 PreviousCustomMode)
{
    const bool bAirborne = Character->GetCharacterMovement()->IsFalling();

    if (bAirborne && !bIsAirborne)
    {
        // Just became airborne — start fresh
        bIsAirborne = true;
        PendingObstacles.Empty();
        SweepAccumulator = 0.f;
    }
    else if (!bAirborne && bIsAirborne)
    {
        // Just landed — score everything we flew over
        bIsAirborne = false;

        for (AActor* Obstacle : PendingObstacles)
        {
            if (IsValid(Obstacle) && !IsOnCooldown(Obstacle))
            {
                ScoreObstacle(Obstacle);
            }
        }

        PendingObstacles.Empty();
    }
}

void UNGPTraversalScoreComponent::TickSweep()
{
    const ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner)
    {
        return;
    }
    
    const UNGPTraversalDeveloperSettings* Settings = GetDefault<UNGPTraversalDeveloperSettings>();

    const FVector Start = Owner->GetActorLocation();
    const FVector End = Start - FVector(0.f, 0.f, Settings->SweepLength);

    TArray<FHitResult> Hits;
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(Settings->SweepRadius);
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity,ECC_Visibility, Sphere, Params);


    if (CVarTraversalDebug.GetValueOnGameThread())
    {
        DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, Settings->SweepInterval);
    }

    for (const FHitResult& Hit : Hits)
    {
        AActor* HitActor = Hit.GetActor();
        if (!IsValid(HitActor))
        {
            continue;
        }
        if (!HitActor->GetClass()->ImplementsInterface(UNGPObstacleInterface::StaticClass()))
        {
            continue;
        }
        
        PendingObstacles.Add(HitActor);
    }
}

void UNGPTraversalScoreComponent::ScoreObstacle(AActor* Obstacle)
{
    const int32 BasePoints = INGPObstacleInterface::Execute_GetPoints(Obstacle);
    const int32 FinalPoints = BasePoints * CurrentMultiplier;

    const ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner)
    {
        return;
    }
    
    if (ANGPPlayerState* PS = Owner->GetPlayerState<ANGPPlayerState>())
    {
        PS->AddScore(FinalPoints);
    }

    const UNGPTraversalDeveloperSettings* Settings = GetDefault<UNGPTraversalDeveloperSettings>();

    ObstacleCooldowns.Add(Obstacle, GetWorld()->GetTimeSeconds());

    OnScoreEarned.Broadcast(FinalPoints, CurrentMultiplier);

    CurrentMultiplier = FMath::Clamp(CurrentMultiplier + 1, 1, Settings->MaxComboMultiplier);
    ComboTimeRemaining = Settings->ComboWindowSeconds;
}

bool UNGPTraversalScoreComponent::IsOnCooldown(AActor* Obstacle) const
{
    const float* LastScored = ObstacleCooldowns.Find(Obstacle);
    if (!LastScored)
    {
        return false;
    }
    
    const UNGPTraversalDeveloperSettings* Settings = GetDefault<UNGPTraversalDeveloperSettings>();

    return (GetWorld()->GetTimeSeconds() - *LastScored) < Settings->ObstacleCooldown;
}