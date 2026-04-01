// Fill out your copyright notice in the Description page of Project Settings.


#include "NgpUnrealDevTask/Public/Core/NGPPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ANGPPlayerCharacter::ANGPPlayerCharacter()
{
}

void ANGPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANGPPlayerCharacter::HandleLook);
	EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ANGPPlayerCharacter::OnJumpPressed);
	EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANGPPlayerCharacter::OnJumpReleased);
}

void ANGPPlayerCharacter::HandleMove(const FInputActionValue& Value)
{
	const FVector2D InputDirection = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), InputDirection.X);
	AddMovementInput(GetActorRightVector(), InputDirection.Y);
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

