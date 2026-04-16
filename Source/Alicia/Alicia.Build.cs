// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Alicia : ModuleRules
{
	public Alicia(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "NiagaraCore", "UMG", "AIModule" });

        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities" ,"GameplayTags","GameplayTasks", "Inv_haowenguo" });
    }
}
