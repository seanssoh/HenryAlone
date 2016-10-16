// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class OSSInteraction : ModuleRules
	{
        public OSSInteraction(TargetInfo Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[] {                    
                     "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
				}
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
				}
            );


			PublicIncludePaths.AddRange(
				new string[] {
					"OSSInteraction/Public"
				}
			);
             
			PrivateIncludePaths.AddRange(
				new string[] {
					"OSSInteraction/Private"
				}
			);
		}
	}
}
