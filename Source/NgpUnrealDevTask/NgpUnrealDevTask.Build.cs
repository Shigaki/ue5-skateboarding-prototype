// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NgpUnrealDevTask : ModuleRules
{
	public NgpUnrealDevTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"DeveloperSettings",
			"ModelViewViewModel"
		});
	}
}
