// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class OSSUtilities : ModuleRules
	{
		public OSSUtilities(TargetInfo Target)
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
					"OSSUtilities/Public"
				}
			);
             
			PrivateIncludePaths.AddRange(
				new string[] {
					"OSSUtilities/Private"
				}
			);
		}
	}
}
