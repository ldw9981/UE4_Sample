// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPSCPP : ModuleRules
{
	public FPSCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule","NavigationSystem" });
    }
}
