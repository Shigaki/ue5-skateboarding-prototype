#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NGPVMLibrary.generated.h"

class UNGPTraversalViewModel;
/**
 * Blueprint helpers to reach the project's MVVM view models from widgets and Blueprints.
 */
UCLASS()
class NGPUNREALDEVTASK_API UNGPVMLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintPure, Category="NGP|ViewModels", meta=(WorldContext="WorldContextObject"))
		static UNGPTraversalViewModel* GetTraversalViewModel(const UObject* WorldContextObject);
};
