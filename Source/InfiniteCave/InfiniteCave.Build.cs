// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InfiniteCave : ModuleRules
{
	public InfiniteCave(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
