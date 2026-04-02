// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NGPPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

/**
 * 
 */
UCLASS()
class NGPUNREALDEVTASK_API ANGPPlayerState : public APlayerState
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintAssignable, Category = "Score")
		FOnScoreChanged OnScoreChanged;

		/**
		 * Adds a traversal score to the player.
		 * 
		 * @param Points The points to add.
		 */
		UFUNCTION(BlueprintCallable, Category = "Score")
		void AddScore(int32 Points);

		/**
		 * Returns the total score of the player.
		 */
		UFUNCTION(BlueprintPure, Category = "Score")
		int32 GetTotalScore() const
		{
			return TotalScore;
		}

	private:
		/** The total score of the player. */
		UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 TotalScore = 0;
};
