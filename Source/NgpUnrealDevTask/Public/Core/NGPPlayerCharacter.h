// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NGPPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class NGPUNREALDEVTASK_API ANGPPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	public:
		ANGPPlayerCharacter();

	protected:
		virtual void BeginPlay() override;

	public:

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Inputs
	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputMappingContext> PlayerDefaultMappingContext;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> MoveAction;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> LookAction;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> JumpAction;
	
	public:
		void HandleMove(const FInputActionValue& Value);
		void HandleLook(const FInputActionValue& Value);
		
		void OnJumpPressed();
		void OnJumpReleased();

#pragma endregion Inputs
};
