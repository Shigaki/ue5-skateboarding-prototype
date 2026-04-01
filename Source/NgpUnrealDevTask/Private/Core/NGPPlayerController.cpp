// Fill out your copyright notice in the Description page of Project Settings.


#include "NgpUnrealDevTask/Public/Core/NGPPlayerController.h"

ANGPPlayerController::ANGPPlayerController()
{
}

void ANGPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->ViewPitchMin = -60.f;
	PlayerCameraManager->ViewPitchMax = 60.f;
}
