// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class OSSShading : ModuleRules
	{
		public OSSShading(TargetInfo Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[] {
                     "Core", "CoreUObject", "Engine", "InputCore"
				}
			);

			PublicIncludePaths.AddRange(
				new string[] {
					"OSSShading/Public"
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"OSSShading/Private"
				}
			);
		}
	}
}
