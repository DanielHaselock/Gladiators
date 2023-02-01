// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gladiators : ModuleRules
{
	public Gladiators(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"GameplayTasks",
			"HeadMountedDisplay",
			"AIModule",
			"NavigationSystem"});
	}
}
