// Fill out your copyright notice in the Description page of Project Settings.


#include "NgpUnrealDevTask/Public/Core/NGPPlayerController.h"

ANGPPlayerController::ANGPPlayerController()
{
}

void ANGPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(PlayerCameraManager))
	{
		PlayerCameraManager->ViewPitchMin = -20.f;
		PlayerCameraManager->ViewPitchMax = 20.f;
	}
}
