#include "Core/NGPPlayerController.h"

void ANGPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(PlayerCameraManager))
	{
		PlayerCameraManager->ViewPitchMin = -20.f;
		PlayerCameraManager->ViewPitchMax = 20.f;
	}
}
