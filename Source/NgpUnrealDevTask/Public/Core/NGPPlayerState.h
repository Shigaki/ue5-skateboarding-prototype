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

		UFUNCTION(BlueprintCallable, Category = "Score")
		void AddScore(int32 Points);

		UFUNCTION(BlueprintPure, Category = "Score")
		int32 GetTotalScore() const
		{
			return TotalScore;
		}

	private:
		UPROPERTY(VisibleAnywhere, Category = "Score")
		int32 TotalScore = 0;
};
