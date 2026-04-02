// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NGPTraversalDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName="NGP Traversal Settings"))
class NGPUNREALDEVTASK_API UNGPTraversalDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	public:
		/** The default points for an obstacle */
		UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle")
		int32 DefaultObstaclePoints = 100.f;

		/** The default cooldown per obstacle */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
		float ObstacleCooldown = 3.0f;

		/** The time in seconds that a combo is active */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traversal")
		float ComboWindowSeconds = 2.0f;

		/** The max multiplier a combo can reach */
		UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Traversal")
		int32 MaxComboMultiplier = 8;

		/** The size of the sweep in the X and Y direction. The sweep is a box that is used to check for obstacles. */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traversal|Trace")
		float SweepRadius = 40.0f;

		/** The length of the sweep in the Z direction. The sweep is a box that is used to check for obstacles. */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traversal|Trace")
		float SweepLength = 120.0f;

		/** How often the sweep runs while airborne (seconds) */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traversal|Trace")
		float SweepInterval = 0.1f;
		
};
