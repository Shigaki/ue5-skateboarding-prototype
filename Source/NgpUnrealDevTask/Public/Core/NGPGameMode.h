#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NGPGameMode.generated.h"

/**
 * Gameplay game mode base class. Defaults (pawn, controller, HUD) are assigned in its Blueprint subclass.
 */
UCLASS()
class NGPUNREALDEVTASK_API ANGPGameMode : public AGameModeBase
{
	GENERATED_BODY()
};
