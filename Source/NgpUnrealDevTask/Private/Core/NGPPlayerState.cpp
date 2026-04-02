// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NGPPlayerState.h"

void ANGPPlayerState::AddScore(int32 Points)
{
	TotalScore += Points;
	OnScoreChanged.Broadcast(TotalScore);
	UE_LOG(LogTemp, Log, TEXT("Score: %d"), TotalScore);
}
