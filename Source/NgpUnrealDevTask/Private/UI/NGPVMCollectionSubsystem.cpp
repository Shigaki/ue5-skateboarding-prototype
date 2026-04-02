// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NGPVMCollectionSubsystem.h"

#include "UI/NGPTraversalViewModel.h"

UNGPTraversalViewModel* UNGPVMCollectionSubsystem::GetOrCreateTraversalViewModel()
{
	if (!IsValid(TraversalViewModel))
	{
		TraversalViewModel = NewObject<UNGPTraversalViewModel>(this);
	}
	return TraversalViewModel;
}
