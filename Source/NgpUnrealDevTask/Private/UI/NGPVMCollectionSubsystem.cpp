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
