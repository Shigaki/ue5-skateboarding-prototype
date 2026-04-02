// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NGPTraversalViewModel.h"

int32 UNGPTraversalViewModel::GetTotalScore() const
{
	return TotalScore;
}

int32 UNGPTraversalViewModel::GetLastEarnedPoints() const
{
	return LastEarnedPoints;
}

int32 UNGPTraversalViewModel::GetComboMultiplier() const
{
	return ComboMultiplier;
}

float UNGPTraversalViewModel::GetComboTimeRemaining() const
{
	return ComboTimeRemaining;
}

bool UNGPTraversalViewModel::GetIsComboActive() const
{
	return ComboTimeRemaining > 0.f;
}

float UNGPTraversalViewModel::GetComboPercent() const
{
	return ComboTimeMax > 0.f ? ComboTimeRemaining / ComboTimeMax : 0.f;
}

void UNGPTraversalViewModel::SetTotalScore(int32 NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(TotalScore, NewValue);
}

void UNGPTraversalViewModel::SetLastEarnedPoints(int32 NewValue)
{
	LastEarnedPoints = NewValue;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(LastEarnedPoints);
}

void UNGPTraversalViewModel::SetComboMultiplier(int32 NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(ComboMultiplier, NewValue);
}

void UNGPTraversalViewModel::SetComboTimeRemaining(float NewValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(ComboTimeRemaining, NewValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetComboPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetIsComboActive);
	}
}

void UNGPTraversalViewModel::SetComboTimeMax(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(ComboTimeMax, NewValue);
}
