// Copyright 2015 Oculus Story Studio, Inc. All Rights Reserved.

#include "OSSInteractionPrivatePCH.h"

#include "IHeadMountedDisplay.h"

namespace nUOSSInteractiveAgentComponent
{
	inline FQuat ComposeRotators(const FRotator &A, const FRotator &B)
	{
		FQuat AQuat = FQuat(A);
		FQuat BQuat = FQuat(B);

		return BQuat*AQuat;
	}
}

UOSSInteractiveAgentComponent::UOSSInteractiveAgentComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_DuringPhysics;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
	//bTickInEditor = true;
	bAutoActivate = true;
	bNeverNeedsRenderUpdate = true;

	/** GENERAL DEFAULTS **/
	SkelMeshComponent = nullptr;
	IsEnabled = false;
	AimSocket = FName(TEXT("NoseEnd"));

	/** EYES DEFAULTS **/
	EyeState = EITS_Inactive;
	EyeEaseTime = 0.1f;
	EyeSeparationModifier = 2.f;
	EyePitchConstraints = FVector2D(-20.f, 20.f);
	EyeYawConstraints = FVector2D(-45.f, 15.f);

	/** EYE DART DEFAULTS **/
	EyeDartFrequencyRange = FVector2D(0.5f, 1.f);
	EyeDartMovementRange = FVector2D(1.f, 2.5f);
	EyeDartState = EDS_LookingAtTarget;
	
	/** NECK DEFAULTS **/
	NeckState = EITS_Inactive;
	NeckEaseTime = 0.75f;

	/** PLAYER LAG DEFAULTS **/
	PlayerLagMaxDegPerSec = 180.f;
	PlayerLagCloseEnoughDeg = 0.4f;
	PlayerLagAngleBounds = FVector2D(5.f, 45.f);
	LagCurveEaseIn = nullptr;
	LagCurveEaseOut = nullptr;
	PlayerLagIsMoving = false;
	PlayerLagEaseInTimer = 0.f;
}

void UOSSInteractiveAgentComponent::Activate(bool bReset)
{
	//get the skeletal mesh component
	TInlineComponentArray<USkeletalMeshComponent*> SkelComponents;
	GetOwner()->GetComponents<USkeletalMeshComponent>(SkelComponents);
	if (SkelComponents.Num() == 0)
	{
		return;
	}
	ensure(SkelComponents.Num() == 1); //don't currently support more than one SkeletalMeshComponent

	SkelMeshComponent = SkelComponents[0];
	check(SkelMeshComponent != nullptr);
}

void UOSSInteractiveAgentComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	TickPlayerLag(DeltaTime);
	TickNeck(DeltaTime);

	TickEyeDart(DeltaTime);
	TickEyes(DeltaTime);
}

void UOSSInteractiveAgentComponent::TickPlayerLag(float DeltaTime)
{
	if (!IsEnabled || NeckState == EITS_Inactive)
	{
		return;
	}

	if (SkelMeshComponent == nullptr)
	{
		UE_LOG(LogEngine, Warning, TEXT("Trying to TickPlayerLag on an Actor with no SkeletalMeshComponent."));
		return;
	}
	if (LagCurveEaseIn == nullptr)
	{
		UE_LOG(LogEngine, Warning, TEXT("Trying to TickPlayerLag with no EaseIn curve."));
		return;
	}
	if (LagCurveEaseOut == nullptr)
	{
		UE_LOG(LogEngine, Warning, TEXT("Trying to TickPlayerLag with no EaseOut curve."));
		return;
	}

	const FTransform NoseEndTransform = SkelMeshComponent->GetSocketTransform(AimSocket, RTS_World);
	const FVector PlayerPosition = GetPlayerPosition();

	//Vector from the AimSocket to the Player's actual current position
	const FVector PlayerCurrentLocal = NoseEndTransform.InverseTransformPosition(PlayerPosition);
	const FVector PlayerCurrentDirection = PlayerCurrentLocal.GetSafeNormal();

	//Vector from the AimSocket to the Player's lag position
	const FVector PlayerLagLocal = NoseEndTransform.InverseTransformPosition(PlayerLagPosition);
	const FVector PlayerLagDirection = PlayerLagLocal.GetSafeNormal();
	
	//DOT between actual and lag position from our aim socket
	const float dotCurLag = FVector::DotProduct(PlayerCurrentDirection, PlayerLagDirection);

	//if we're less than our min bound angle and not currently moving, don't adjust the lag position
	if (!PlayerLagIsMoving && dotCurLag >= FMath::Cos(PI/180.f * PlayerLagAngleBounds.X))
	{
		return;
	}

	//update some state
	PlayerLagIsMoving = true;
	PlayerLagEaseInTimer += DeltaTime;

	//figure out the most we can rotate this frame
	float maxRotateDegrees = 0.f;
	{
		//calculate the interpolation of where we are in our current angle bounds
		float interpAngleBounds = 0.f;
		{
			float dotNoseCur = FVector::DotProduct(FVector(1, 0, 0), PlayerCurrentDirection);
			float degNoseCur = FMath::Clamp((180.f) / PI * FMath::Acos(dotNoseCur), PlayerLagAngleBounds.X, PlayerLagAngleBounds.Y);
			interpAngleBounds = (degNoseCur - PlayerLagAngleBounds.X) / (PlayerLagAngleBounds.Y - PlayerLagAngleBounds.X);
			interpAngleBounds = FMath::Clamp(interpAngleBounds, 0.f, 1.f);
		}

		//get our ease in/out value
		float easeAmount = 0.f;
		{
			float easeInAmount = LagCurveEaseIn->GetFloatValue(PlayerLagEaseInTimer);
			float easeOutAmount = LagCurveEaseOut->GetFloatValue(dotCurLag);
			easeAmount = easeInAmount * easeOutAmount;
		}

		//total interp
		float totalInterp = interpAngleBounds * easeAmount;

		//finally our calculation
		maxRotateDegrees = PlayerLagMaxDegPerSec * DeltaTime * totalInterp;
	}

	//if the amount we need to move is less than the amount we can move, just update the lag position
	//and reset state so that any future movement will trigger a nice movement delay
	if (dotCurLag >= FMath::Cos(PI / 180.f * maxRotateDegrees) || dotCurLag >= FMath::Cos(PI / 180.f * PlayerLagCloseEnoughDeg))
	{
		PlayerLagPosition = PlayerPosition;
		PlayerLagIsMoving = false;
		PlayerLagEaseInTimer = 0.f;
		return;
	}

	//rotate from the lag position towards the current position
	//to calculate the new PlayerLagPosition (in world space)
	FVector RotationAxis = FVector::CrossProduct(PlayerLagDirection, PlayerCurrentDirection);
	FVector NewPlayerLagLocalPosition = PlayerLagLocal.RotateAngleAxis(maxRotateDegrees, RotationAxis.GetSafeNormal());
	PlayerLagPosition = NoseEndTransform.TransformPosition(NewPlayerLagLocalPosition);
}

void UOSSInteractiveAgentComponent::TickEyeDart(float DeltaTime)
{
	if (!IsEnabled || !IsEyeTrackingEnabled())
	{
		EyeDartTimer = 0.f;
		EyeDartOffsets = FRotator::ZeroRotator;
		return;
	}

	EyeDartTimer -= DeltaTime;
	if (EyeDartTimer > 0.f)
		return;

	//timer is up so figure out where the eyes should be now
	switch (EyeDartState)
	{
		case EDS_LookingAtTarget:
			EyeDartState = EDS_LookingAway;
			{
				float Yaw = FMath::FRandRange(EyeDartMovementRange.X, EyeDartMovementRange.Y) * (FMath::RandBool()) ? -1.f : 1.f;
				float Pitch = FMath::FRandRange(EyeDartMovementRange.X, EyeDartMovementRange.Y) * (FMath::RandBool()) ? -1.f : 1.f;
				EyeDartOffsets = FRotator(0.f, Yaw, Pitch);
			}
			break;

		case EDS_LookingAway:
			EyeDartState = EDS_LookingAtTarget;
			EyeDartOffsets = FRotator::ZeroRotator;
			break;
	}

	//reset the timer since we changed state
	EyeDartTimer = FMath::FRandRange(EyeDartFrequencyRange.X, EyeDartFrequencyRange.Y);
}

void UOSSInteractiveAgentComponent::TickEyes(float DeltaTime)
{
	if (!IsEnabled || !IsEyeTrackingEnabled())
	{
		// TODO : 엔진 레벨에서 수정된 코드 마이그레이션 필요 SetRelativeBoneTransform / EUserAtomDeltaType::Additive
		//SkelMeshComponent->SetRelativeBoneTransform(EyeAimBoneLeft, FTransform::Identity, EUserAtomDeltaType::Additive);
		//SkelMeshComponent->SetRelativeBoneTransform(EyeAimBoneRight, FTransform::Identity, EUserAtomDeltaType::Additive);
		return;
	}

	TickEaseTimer(DeltaTime, EyeState, EyeEaseTime, EyeEaseTimerCurrent);
	TickEaseState(DeltaTime, IsEyeTrackingEnabled(), EyeEaseTimerCurrent, EyeEaseTime, EyeState);

	const FVector PlayerWorldPos = GetPlayerPosition();
	const float EyeSeparation = CalculateEyeSeparation();

	//Left eye
	FRotator EyeRotationLeft;
	{
		FRotator EyeAimRotator;
		{
			FRotator PlayerPosRotator;
			{
				FTransform AimReferenceTransform = SkelMeshComponent->GetSocketTransform(EyeReferenceSocketLeft, RTS_World);
				FVector PlayerPosDirection = AimReferenceTransform.InverseTransformPosition(PlayerWorldPos);
				PlayerPosRotator = PlayerPosDirection.Rotation();
			}

			//TODO HACK - In Henry we had to cross-wire the desired Pitch into the Roll transform because of how the bone was aligned
			EyeRotationLeft.Pitch = 0.f;
			{
				float minYaw = FMath::Min(EyeYawConstraints.X, EyeYawConstraints.Y);
				float maxYaw = FMath::Max(EyeYawConstraints.X, EyeYawConstraints.Y);
				EyeRotationLeft.Yaw = FMath::Clamp(PlayerPosRotator.Yaw + (EyeSeparation * -1.f), minYaw, maxYaw);
			}
			EyeRotationLeft.Roll = FMath::Clamp(PlayerPosRotator.Pitch * -1.f, EyePitchConstraints.X, EyePitchConstraints.Y);
		}
	}

	//Right eye
	FRotator EyeRotationRight;
	{
		FRotator PlayerPosRotator;
		{
			FTransform AimReferenceTransform = SkelMeshComponent->GetSocketTransform(EyeReferenceSocketRight, RTS_World);
			FVector PlayerPosDirection = AimReferenceTransform.InverseTransformPosition(PlayerWorldPos);
			PlayerPosRotator = PlayerPosDirection.Rotation();
		}

		//TODO HACK - In Henry we had to cross-wire the desired Pitch into the Roll transform because of how the bone was aligned
		EyeRotationRight.Pitch = 0.f;
		{
			float minYaw = FMath::Min(-EyeYawConstraints.X, -EyeYawConstraints.Y);
			float maxYaw = FMath::Max(-EyeYawConstraints.X, -EyeYawConstraints.Y);
			EyeRotationRight.Yaw = FMath::Clamp(PlayerPosRotator.Yaw + (EyeSeparation * -1.f), minYaw, maxYaw);
		}
		EyeRotationRight.Roll = FMath::Clamp(PlayerPosRotator.Pitch * -1.f, EyePitchConstraints.X, EyePitchConstraints.Y);
	}

	//we want to average the calculated pitches so that the eyes appear to behave normally. It looks really wonky if they end up at different pitches
	float AveragePitch = (EyeRotationLeft.Roll + EyeRotationRight.Roll) / 2.f;
	EyeRotationLeft.Roll = AveragePitch;
	EyeRotationRight.Roll = AveragePitch;

	//add in the eye darts
	FTransform EyeTransformLeft = FTransform::Identity;
	EyeTransformLeft.SetRotation( nUOSSInteractiveAgentComponent::ComposeRotators(EyeRotationLeft, EyeDartOffsets) );
	FTransform EyeTransformRight = FTransform::Identity;
	EyeTransformRight.SetRotation( nUOSSInteractiveAgentComponent::ComposeRotators(EyeRotationRight, EyeDartOffsets) );

	//set up the transforms
	// TODO : 엔진 레벨에서 수정된 코드 마이그레이션 필요 SetRelativeBoneTransform / EUserAtomDeltaType::AdditiveToRefPose
	//SkelMeshComponent->SetRelativeBoneTransform(EyeAimBoneLeft, EyeTransformLeft, EUserAtomDeltaType::AdditiveToRefPose);
	//SkelMeshComponent->SetRelativeBoneTransform(EyeAimBoneRight, EyeTransformRight, EUserAtomDeltaType::AdditiveToRefPose);
}

void UOSSInteractiveAgentComponent::OnEnterNeck()
{
	NeckReferenceTransform = InitNeckReferenceTransform();

	//initialize player lag position
	{
		const FVector PlayerWorldPos = GetPlayerPosition();
		FTransform LocalNeckReference = NeckReferenceTransform * SkelMeshComponent->GetComponentToWorld();

		FVector PlayerToLocal = PlayerWorldPos - LocalNeckReference.GetLocation();
		PlayerLagPosition = LocalNeckReference.GetLocation() + LocalNeckReference.Rotator().Vector() * PlayerToLocal.Size();
	}
}

void UOSSInteractiveAgentComponent::TickNeck(float DeltaTime)
{
	if (SkelMeshComponent == nullptr)
	{
		UE_LOG(LogEngine, Warning, TEXT("Trying to TickNeck on an Actor with no SkeletalMeshComponent."));
		return;
	}

	EInteractiveTrackingState LastState = NeckState;

	TickEaseTimer(DeltaTime, NeckState, NeckEaseTime, NeckEaseTimerCurrent);
	TickEaseState(DeltaTime, IsNeckTrackingEnabled(), NeckEaseTimerCurrent, NeckEaseTime, NeckState);

	if (LastState == EITS_Inactive && NeckState == EITS_EaseIn)
	{
		OnEnterNeck();
	}

	FTransform SocketWorldToLocal = NeckReferenceTransform * SkelMeshComponent->GetComponentTransform();
	FVector PlayerLagPositionLocal = SocketWorldToLocal.InverseTransformPosition(PlayerLagPosition);
	FRotator LookAtRotator = PlayerLagPositionLocal.Rotation();
	
	float EaseMultiplier = GetEaseMultiplier(NeckEaseTimerCurrent, NeckEaseTime);
	DoLookAt(LookAtRotator.Pitch*EaseMultiplier, LookAtRotator.Yaw*EaseMultiplier);
}

void UOSSInteractiveAgentComponent::TickEaseTimer(float DeltaTime, EInteractiveTrackingState CurState, float TimerMax, float &TimerValue)
{
	switch (CurState)
	{
	case EITS_Inactive:
		TimerValue = 0.f;
		break;

	case EITS_EaseIn:
		TimerValue = FMath::Clamp<float>(TimerValue + DeltaTime, 0.f, TimerMax);
		break;

	case EITS_Active:
		TimerValue = TimerMax;
		break;

	case EITS_EaseOut:
		TimerValue = FMath::Clamp<float>(TimerValue - DeltaTime, 0.f, TimerMax);
		break;
	}
}

void UOSSInteractiveAgentComponent::TickEaseState(float DeltaTime, bool StateActive, float TimerValue, float TimerMax, EInteractiveTrackingState &CurState)
{
	switch (CurState)
	{
	case EITS_Inactive:
		if (StateActive)
		{
			CurState = EITS_EaseIn;
		}
		break;

	case EITS_EaseIn:
		if (TimerValue >= TimerMax)
		{
			CurState = EITS_Active;
		}
		break;

	case EITS_Active:
		if (!StateActive)
		{
			CurState = EITS_EaseOut;
		}
		break;

	case EITS_EaseOut:
		if (TimerValue <= 0.f)
		{
			CurState = EITS_Inactive;
		}
		break;
	}
}

FVector UOSSInteractiveAgentComponent::GetPlayerPosition() const
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
	APlayerCameraManager *CameraManager = UGameplayStatics::GetPlayerCameraManager(GetOwner(), 0);
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
	return RootCameraTransform.TransformPosition(DeviceLocalPosition);
}

float UOSSInteractiveAgentComponent::GetEaseMultiplier(float EaseTimerCurrent, float EaseTimerMax) const
{
	return FMath::Clamp(EaseTimerCurrent / EaseTimerMax, 0.f, 1.f);
}

float UOSSInteractiveAgentComponent::CalculateEyeSeparation() const
{
	const FTransform NoseEndTransform = SkelMeshComponent->GetSocketTransform(AimSocket, RTS_World);
	FVector PlayerWorldPos = GetPlayerPosition();
	FVector PlayerPosDirection = NoseEndTransform.InverseTransformPosition(PlayerWorldPos);
	PlayerPosDirection.Normalize();

	float toPlayerDot = FMath::Clamp(FVector::DotProduct(FVector(1, 0, 0), PlayerPosDirection), 0.f, 1.f);

	//more separation the more in front of the character we are (prevent crossed looking eyes for some cartoony geometries)
	return toPlayerDot * EyeSeparationModifier;
}
