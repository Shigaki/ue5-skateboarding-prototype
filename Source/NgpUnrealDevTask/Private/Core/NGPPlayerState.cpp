// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NGPPlayerState.h"

#include "Core/NGPPlayerCharacter.h"
#include "Core/NGPPlayerController.h"
#include "Helpers/NGPVMLibrary.h"
#include "UI/NGPTraversalViewModel.h"

void ANGPPlayerState::AddScore(const int32 Points)
{
	TotalScore += Points;
	OnScoreChanged.Broadcast(TotalScore);

	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}
	
	if (UNGPTraversalViewModel* TraversalVM = UNGPVMLibrary::GetTraversalViewModel(World);
		IsValid(TraversalVM))
	{
		TraversalVM->SetLastEarnedPoints(Points);
		TraversalVM->SetTotalScore(TotalScore);
	}
}
