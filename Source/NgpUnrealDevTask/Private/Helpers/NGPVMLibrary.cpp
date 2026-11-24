#include "Helpers/NGPVMLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "UI/NGPVMCollectionSubsystem.h"

UNGPTraversalViewModel* UNGPVMLibrary::GetTraversalViewModel(const UObject* WorldContextObject)
{
	const UGameInstance* GI = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (!IsValid(GI))
	{
		return nullptr;
	}
	
	UNGPVMCollectionSubsystem* VMCollection = GI->GetSubsystem<UNGPVMCollectionSubsystem>();
	return IsValid(VMCollection) ? VMCollection->GetOrCreateTraversalViewModel() : nullptr;
}
