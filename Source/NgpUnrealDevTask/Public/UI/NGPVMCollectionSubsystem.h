#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NGPVMCollectionSubsystem.generated.h"

class UNGPTraversalViewModel;
/**
 * Game instance subsystem that owns the view models and creates them on demand.
 */
UCLASS()
class NGPUNREALDEVTASK_API UNGPVMCollectionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintPure, Category="NGP|ViewModels")
		UNGPTraversalViewModel* GetOrCreateTraversalViewModel();

	private:
		UPROPERTY()
		TObjectPtr<UNGPTraversalViewModel> TraversalViewModel;
};
