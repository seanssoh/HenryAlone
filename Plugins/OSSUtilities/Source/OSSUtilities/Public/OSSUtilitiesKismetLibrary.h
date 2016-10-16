
#pragma once

#include "OSSUtilitiesKismetLibrary.generated.h"

UCLASS()
class UOSSUtilitiesKismetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	 * @return: the number of intersection points [0,1,2]
	 **/
	UFUNCTION(BlueprintPure, Category = "OSS|Utilities")
	static int32 RaySphereIntersection(const FVector &RayOrigin, const FVector &RayDirection, const FVector &SphereOrigin, float SphereRadius, FVector &IntersectionA, FVector &IntersectionB);

	/**
	* Grabs the current orientation and position for the HMD and converts them to WorldSpace.
	*
	* @param DeviceRotation	(out) The device's current rotation
	* @param DevicePosition	(out) The device's current position, in its own tracking space
	*/
	UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void GetWorldOrientationAndPosition(UObject* WorldContextObject, FRotator& DeviceRotation, FVector& DevicePosition);
};
