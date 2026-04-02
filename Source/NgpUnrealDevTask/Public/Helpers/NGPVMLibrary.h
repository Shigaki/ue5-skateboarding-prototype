// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NGPVMLibrary.generated.h"

class UNGPTraversalViewModel;
/**
 * 
 */
UCLASS()
class NGPUNREALDEVTASK_API UNGPVMLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintPure, Category="NGP|ViewModels", meta=(WorldContext="WorldContextObject"))
		static UNGPTraversalViewModel* GetTraversalViewModel(const UObject* WorldContextObject);
};
