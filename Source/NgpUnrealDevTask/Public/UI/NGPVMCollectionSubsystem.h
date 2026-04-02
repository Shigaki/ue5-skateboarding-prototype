// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NGPVMCollectionSubsystem.generated.h"

class UNGPTraversalViewModel;
/**
 * 
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
