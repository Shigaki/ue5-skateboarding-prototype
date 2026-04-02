// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NGPTraversalScoreComponent.generated.h"

class UNGPTraversalViewModel;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreEarned, int32, Points, int32, Multiplier);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboChanged);

/**
 * The traversal score component is responsible for tracking and awarding traversal points.
 * Recomended to be used with a character class.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NGPUNREALDEVTASK_API UNGPTraversalScoreComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		UNGPTraversalScoreComponent();

		UPROPERTY(BlueprintReadOnly, Category = "Traversal|Score")
		TObjectPtr<UNGPTraversalViewModel> TraversalViewModel;

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
		/**
		 * Called when the movement mode of the character changes.
		 * 
		 * @param Character The character that the component is attached to.
		 * @param PrevMovementMode The previous movement mode.
		 * @param PreviousCustomMode The previous custom movement mode.
		 */
		UFUNCTION()
		void OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

		/**
		 * Called every SweepInterval (see NGPTraversalDeveloperSettings) tick to process traversal scoring.
		 */
		void TickSweep();
		
		/**
		 * Adds a traversal score to the player based on the obstacle doubled by his current multiplier.
		 * 
		 * @param Obstacle The obstacle to score.
		 */
		void ScoreObstacle(AActor* Obstacle);

		/**
		 * Checks if the obstacle has been scored recently.
		 * Prevents double scoring the same obstacle.
		 * 
		 * @param Obstacle The obstacle to check.
		 * @return True if the obstacle is on cooldown, false otherwise.
		 */
		bool IsOnCooldown(AActor* Obstacle) const;

		/**
		 * The set of obstacles detected while the character was airborne this jump.
		 *
		 * This set is used to track obstacles over the course of the jump,
		 * before they are scored. New obstacles are added to this set when they
		 * are detected with the TickSweep function, and scored when the character
		 * lands with the ScoreObstacle function.
		 */
		TSet<TObjectPtr<AActor>> PendingObstacles;

		/**
		 * Maps obstacles to their last scored timestamp.
		 * Used to prevent double scoring the same obstacle within the cooldown period.
		 *
		 * @see NGPTraversalDeveloperSettings::ObstacleCooldown
		 */
		TMap<TObjectPtr<AActor>, float> ObstacleCooldowns;

		int32 CurrentMultiplier = 1;
		float ComboTimeRemaining = 0.0f;
		float SweepAccumulator = 0.0f;
		bool bIsAirborne = false;
};
