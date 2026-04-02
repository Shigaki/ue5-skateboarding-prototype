// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NGPTraversalScoreComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreEarned, int32, Points, int32, Multiplier);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NGPUNREALDEVTASK_API UNGPTraversalScoreComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		UNGPTraversalScoreComponent();

	protected:
		virtual void BeginPlay() override;
		
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		UPROPERTY(BlueprintAssignable, Category = "Traversal|Score")
		FOnScoreEarned OnScoreEarned;

		UPROPERTY(BlueprintAssignable, Category = "Traversal|Score")
		FOnComboChanged OnComboReset;

		UFUNCTION(BlueprintPure, Category = "Traversal|Score")
		int32 GetCurrentMultiplier() const { return CurrentMultiplier; }

	private:
		UFUNCTION()
		void OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
		
		void TickSweep();
		void ScoreObstacle(AActor* Obstacle);
		bool IsOnCooldown(AActor* Obstacle) const;

		// Obstacles detected while airborne this jump (confirmed above)
		TSet<TObjectPtr<AActor>> PendingObstacles;

		// Timestamp of last score per obstacle
		TMap<TObjectPtr<AActor>, float> ObstacleCooldowns;

		int32 CurrentMultiplier = 1;
		float ComboTimeRemaining = 0.0f;
		float SweepAccumulator = 0.0f;
		bool bIsAirborne = false;
};
