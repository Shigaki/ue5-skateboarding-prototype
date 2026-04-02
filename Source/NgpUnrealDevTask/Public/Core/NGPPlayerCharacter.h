// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NGPPlayerCharacter.generated.h"

class UNGPTraversalScoreComponent;
class UCameraComponent;
class USpringArmComponent;
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

		virtual void Tick(float DeltaTime) override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		TObjectPtr<USpringArmComponent> SpringArm;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		TObjectPtr<UCameraComponent> Camera;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		TObjectPtr<UNGPTraversalScoreComponent> TraversalScoreComponent;

		/** Acceleration */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float Acceleration = 800.f;

		/** Max speed */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float MaxSpeed = 12000.f;

		/** Carve ratio */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float CarveRatio = 0.65f;

		/** Coasting drag */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float CoastDrag = 0.6f;

		/** Manual brake */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float BrakeDrag = 4.5f;

		/** Low speed turns */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float TurnSpeedAtRest = 140.f;

		/** High speed turns */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float TurnSpeedAtMax = 55.f;

		/** Initial burst of movement */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Movement")
		float PushImpulse = 420.f;

		bool bIsBraking = false;

	public:

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Inputs
	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputMappingContext> PlayerDefaultMappingContext;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> MoveAction;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> TurnAction;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> LookAction;

		UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
		TObjectPtr<UInputAction> JumpAction;
	
	public:
		void HandleMove(const FInputActionValue& Value);
		void HandleTurn(const FInputActionValue& Value);
		void HandleLook(const FInputActionValue& Value);
		
		void OnJumpPressed();
		void OnJumpReleased();

#pragma endregion Inputs
};
