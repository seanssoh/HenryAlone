
#include "OSSUtilitiesPrivatePCH.h"

#include "IHeadMountedDisplay.h"

/**
 * UOSSUtilitiesKismetLibrary
 **/

UOSSUtilitiesKismetLibrary::UOSSUtilitiesKismetLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

int32 UOSSUtilitiesKismetLibrary::RaySphereIntersection(const FVector &RayOrigin, const FVector &RayDirection, const FVector &SphereOrigin, float SphereRadius, FVector &IntersectionA, FVector &IntersectionB)
{
	if (RayDirection.IsZero())
	{
		return 0;
	}

	FVector RayDirNormalized = RayDirection;
	RayDirNormalized.Normalize();

	float a = 1.f; //RayDirectionNormalized dot RayDirectionNormalized which is always 1
	float b = 2.f * FVector::DotProduct(RayDirNormalized, RayOrigin - SphereOrigin);
	float c = FVector::DistSquared(RayOrigin, SphereOrigin) - SphereRadius*SphereRadius;

	float discriminant = b*b - 4 * a * c;
	if (discriminant < 0.f)
	{
		return 0;
	}

	float disA = -b + (sqrtf(discriminant) / (2*a));
	IntersectionA = RayOrigin + RayDirNormalized * disA;

	float disB = -b - (sqrtf(discriminant) / (2 * a));
	IntersectionB = RayOrigin + RayDirNormalized * disB;

	const float epsilon = 0.0001f;
	return (fabs(discriminant) < epsilon) ? 1 : 2;
}

void UOSSUtilitiesKismetLibrary::GetWorldOrientationAndPosition(UObject* WorldContextObject, FRotator& DeviceRotation, FVector& DevicePosition)
{
	//get the TrackingCamera-space position and rotation of the hmd
	FRotator DeviceLocalRotation;
	FVector DeviceLocalPosition;
	if (GEngine->HMDDevice.IsValid() && GEngine->HMDDevice->IsHeadTrackingAllowed())
	{
		FQuat OrientationAsQuat;
		FVector Position(0.f);

		GEngine->HMDDevice->GetCurrentOrientationAndPosition(OrientationAsQuat, Position);

		DeviceLocalRotation = OrientationAsQuat.Rotator();
		DeviceLocalPosition = Position;
	}
	else
	{
		DeviceLocalRotation = FRotator::ZeroRotator;
		DeviceLocalPosition = FVector::ZeroVector;
	}

	//get Yaw only inverse-rotator of the HMD (HMD will throw away world pitch and yaw of camera and use it's own
	//so to transform HMD orientation into worldspace we only care about backing out the yaw component
	FRotator HMDYawOnly(0.f, DeviceLocalRotation.Yaw, 0.f);
	{
		//invert the rotator
		FQuat AQuat = FQuat(HMDYawOnly);
		HMDYawOnly = FRotator(AQuat.Inverse());
	}

	//get camera yaw-only rotator
	APlayerCameraManager *CameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, 0);
	FRotator PlayerYawOnly(0.f, CameraManager->GetCameraRotation().Yaw, 0.f);

	//remove the HMD rotation from the camera so we can finally transform the HMD-local offset into worldspace
	FRotator ComposedYawOnly;
	{
		FQuat AQuat = FQuat(HMDYawOnly);
		FQuat BQuat = FQuat(PlayerYawOnly);

		ComposedYawOnly = FRotator(BQuat*AQuat);
	}

	//finally we can compose the base camera LocalToWorld (as it was before HMD rotation was applied)
	FTransform RootCameraTransform(ComposedYawOnly, CameraManager->GetCameraLocation());
	
	//transform HMD-space offset + camera position into final world-space coordinates by transforming by camera local-to-world
	//rotation is just the normal camera rotation
	DevicePosition = RootCameraTransform.TransformPosition(DeviceLocalPosition);
	DeviceRotation = CameraManager->GetCameraRotation();
}
