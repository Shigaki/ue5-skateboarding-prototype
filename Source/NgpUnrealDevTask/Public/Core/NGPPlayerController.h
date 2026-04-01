// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NGPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NGPUNREALDEVTASK_API ANGPPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		ANGPPlayerController();

		virtual void BeginPlay() override;
};
