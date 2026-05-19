// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Archero : ModuleRules
{
	public Archero(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Archero",
			"Archero/Variant_Platforming",
			"Archero/Variant_Platforming/Animation",
			"Archero/Variant_Combat",
			"Archero/Variant_Combat/AI",
			"Archero/Variant_Combat/Animation",
			"Archero/Variant_Combat/Gameplay",
			"Archero/Variant_Combat/Interfaces",
			"Archero/Variant_Combat/UI",
			"Archero/Variant_SideScrolling",
			"Archero/Variant_SideScrolling/AI",
			"Archero/Variant_SideScrolling/Gameplay",
			"Archero/Variant_SideScrolling/Interfaces",
			"Archero/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
