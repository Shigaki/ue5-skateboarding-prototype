// Fill out your copyright notice in the Description page of Project Settings.


#include "NgpUnrealDevTask/Public/Core/NGPPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ANGPPlayerCharacter::ANGPPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	UCharacterMovementComponent* CMC = GetCharacterMovement();
	CMC->BrakingDecelerationWalking = 0.f; 
	CMC->BrakingDecelerationFalling = 0.f;
	CMC->GroundFriction = 0.f;
	CMC->MaxWalkSpeed = 99999.f;
	CMC->AirControl = 0.6f;
	CMC->GravityScale = 1.3f;
	CMC->JumpZVelocity = 520.f;
}

void ANGPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANGPPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Velocity = GetCharacterMovement()->Velocity;
	const float Speed = Velocity.Size2D();

	const float CurrentDrag = bIsBraking ? BrakeDrag : CoastDrag;
	FVector HorizontalVel = FVector(Velocity.X, Velocity.Y, 0.f);
	HorizontalVel = HorizontalVel * FMath::Max(0.f, 1.f - CurrentDrag * DeltaTime);

	const float HorizontalSpeed = HorizontalVel.Size();
	if (HorizontalSpeed > MaxSpeed)
	{
		// Ease back to MaxSpeed rather than hard-clamping — feels less 'wall-y'
		HorizontalVel = HorizontalVel.GetSafeNormal() * FMath::FInterpTo(HorizontalSpeed, MaxSpeed, DeltaTime, 6.f);
	}

	GetCharacterMovement()->Velocity = FVector(HorizontalVel.X, HorizontalVel.Y, Velocity.Z);
}

void ANGPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = Cast<APlayerController>(GetController());
	if (!IsValid(PC))
	{
		UE_LOG(LogInit, Warning, TEXT("%hs: Invalid Player Controller."), __FUNCTION__);
		return;
	}
	
	const ULocalPlayer* LP = PC->GetLocalPlayer();
	if (!IsValid(LP))
	{
		UE_LOG(LogInit, Warning, TEXT("%hs: Invalid Local Player Controller."), __FUNCTION__);
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(PlayerDefaultMappingContext, 0);
	}

	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANGPPlayerCharacter::HandleMove);
	EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ANGPPlayerCharacter::HandleTurn);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANGPPlayerCharacter::HandleLook);
	EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ANGPPlayerCharacter::OnJumpPressed);
	EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANGPPlayerCharacter::OnJumpReleased);
}

void ANGPPlayerCharacter::HandleMove(const FInputActionValue& Value)
{
	const float Input = Value.Get<float>();

	if (Input > 0.f)
	{
		GetCharacterMovement()->Velocity +=	GetActorForwardVector() * Acceleration * Input * GetWorld()->GetDeltaSeconds();
	}

	bIsBraking = Input < 0.f;
}

void ANGPPlayerCharacter::HandleTurn(const FInputActionValue& Value)
{
	const float Input = Value.Get<float>();
	const float Speed = GetCharacterMovement()->Velocity.Size2D();
	const float SpeedRatio = FMath::Clamp(Speed / MaxSpeed, 0.f, 1.f);
	const float AdaptiveTurnSpeed = FMath::Lerp(TurnSpeedAtRest, TurnSpeedAtMax, SpeedRatio);
	const float TurnDelta = Input * AdaptiveTurnSpeed * GetWorld()->DeltaTimeSeconds;

	AddActorWorldRotation(FRotator(0.f, TurnDelta, 0.f));

	if (Speed > 50.f)
	{
		FVector Vel = GetCharacterMovement()->Velocity;
		FVector HorizVel = FVector(Vel.X, Vel.Y, 0.f);

		HorizVel = HorizVel.RotateAngleAxis(TurnDelta * CarveRatio, FVector::UpVector);

		const float TurnSharpness = FMath::Abs(Input);
		const float CarveSpeedLoss = 1.f - (TurnSharpness * SpeedRatio * 0.015f);
		HorizVel *= CarveSpeedLoss;

		GetCharacterMovement()->Velocity = FVector(HorizVel.X, HorizVel.Y, Vel.Z);
	}
}

void ANGPPlayerCharacter::HandleLook(const FInputActionValue& Value)
{
	const FVector2D InputDirection = Value.Get<FVector2D>();
	AddControllerYawInput(InputDirection.X);
	AddControllerPitchInput(InputDirection.Y);
}

void ANGPPlayerCharacter::OnJumpPressed()
{
	Jump();
}

void ANGPPlayerCharacter::OnJumpReleased()
{
	StopJumping();
}

