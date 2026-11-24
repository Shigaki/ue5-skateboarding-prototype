#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NGPPlayerController.generated.h"

/**
 * Player controller for the skater. Clamps camera pitch for the third-person skating camera.
 */
UCLASS()
class NGPUNREALDEVTASK_API ANGPPlayerController : public APlayerController
{
	GENERATED_BODY()

	protected:
		virtual void BeginPlay() override;

};
