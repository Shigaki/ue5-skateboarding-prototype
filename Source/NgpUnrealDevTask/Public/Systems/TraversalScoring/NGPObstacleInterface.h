// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NGPObstacleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UNGPObstacleInterface : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class NGPUNREALDEVTASK_API INGPObstacleInterface
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintNativeEvent, Category = "Traversal")
		int32 GetPoints() const;
};
