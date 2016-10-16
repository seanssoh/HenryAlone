// Copyright 2015 Oculus Story Studio, Inc. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "OSSInteractiveAgentComponent.generated.h"

UENUM()
enum EEyeDartState
{
	EDS_LookingAtTarget,
	EDS_LookingAway
};

UENUM()
enum EInteractiveTrackingState
{
	EITS_Inactive,
	EITS_EaseIn,
	EITS_Active,
	EITS_EaseOut
};

UCLASS(Abstract, Blueprintable, ClassGroup = OSS, meta = (BlueprintSpawnableComponent))
class UOSSInteractiveAgentComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	/**
	 * INTERFACE
	 **/

	/** Overridable check to see if eye tracking should be active */
	UFUNCTION(BlueprintImplementableEvent, Category = Interface)
	bool IsEyeTrackingEnabled();

	/** Overridable check to see if eye tracking should be active */
	UFUNCTION(BlueprintImplementableEvent, Category = Interface)
	bool IsNeckTrackingEnabled();

	/** Overridable check to see if eye tracking should be active */
	UFUNCTION(BlueprintImplementableEvent, Category = Interface)
	void DoLookAt(float Pitch, float Yaw);

	/** Overridable check to see if eye tracking should be active */
	UFUNCTION(BlueprintImplementableEvent, Category = Interface)
	FTransform InitNeckReferenceTransform();


	/**
	 * GENERAL
	 **/

	UPROPERTY(Transient, BlueprintReadOnly, Category = General)
	USkeletalMeshComponent *SkelMeshComponent;

	/** Is this componend enabled */
	UPROPERTY(EditAnywhere, Category = General)
	bool IsEnabled;

	/** Socket that we use for reference for aiming */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = General)
	FName AimSocket;


	/**
	 * EYE TRACKING
	 **/

	/** Socket that we use for reference for eye aiming. It must not be affected by moving the EyeAimBone (LEFT) */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	FName EyeReferenceSocketLeft;
	/** Socket that we use for reference for eye aiming. It must not be affected by moving the EyeAimBone (RIGHT) */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	FName EyeReferenceSocketRight;

	/** actual bone that this component will adjust to aim the eyes (LEFT) */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	FName EyeAimBoneLeft;
	/** actual bone that this component will adjust to aim the eyes (RIGHT) */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	FName EyeAimBoneRight;

	/** Seconds to ease in eye tracking */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	float EyeEaseTime;

	/** Amount of extra separation (in degrees) for the eyes */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	float EyeSeparationModifier;

	/** Constraints (in degrees) of eye pitch (relative to reference sockets */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	FVector2D EyePitchConstraints;
	/** Constraints (in degrees) of eye yaw (relative to reference sockets */
	UPROPERTY(EditAnywhere, Category = EyeTracking)
	FVector2D EyeYawConstraints;

	EInteractiveTrackingState EyeState;
	float EyeEaseTimerCurrent; /** [0..1] how much the eyes are currently "eased in" */


	/**
	 * EYE DARTS
	 **/

	/** bounds of random time (in seconds) between procedural eye darts */
	UPROPERTY(EditAnywhere, Category = EyeDarts)
	FVector2D EyeDartFrequencyRange;

	/** random range in degrees for eye darts */
	UPROPERTY(EditAnywhere, Category = EyeDarts)
	FVector2D EyeDartMovementRange;

	FRotator EyeDartOffsets;
	float EyeDartTimer;
	EEyeDartState EyeDartState;


	/**
	 * NECK TRACKING
	 **/

	/** Seconds to ease in neck tracking */
	UPROPERTY(EditAnywhere, Category = NeckTracking)
	float NeckEaseTime;

	EInteractiveTrackingState NeckState;
	float NeckEaseTimerCurrent;
	FTransform NeckReferenceTransform;


	/**
	 * PLAYER LAG
	 **/

	/** Where does the Blueprint currently think the player is */
	UPROPERTY(BlueprintReadOnly, Category = PlayerLag)
	FVector PlayerLagPosition;

	/** Maximum rotation we can apply to update the PlayerLagPosition per frame */
	UPROPERTY(EditAnywhere, Category = PlayerLag)
	float PlayerLagMaxDegPerSec;

	/** Threshols (in degrees) that is considered close enough to the PlayerLagPosition being in the same place as the actual position */
	UPROPERTY(EditAnywhere, Category = PlayerLag)
	float PlayerLagCloseEnoughDeg;

	/** PlayerLagPosition won't get updated if the actual Player position is less than PlayerAngleLagBounds.X degrees away. The PlayerAngleLagBounds.Y determines basically that we should move as fast as possible (PlayerLagMaxDegPerSec) */
	UPROPERTY(EditAnywhere, Category = PlayerLag)
	FVector2D PlayerLagAngleBounds;

	/** lag movement ease-in curve */
	UPROPERTY(EditAnywhere, Category = PlayerLag)
	UCurveFloat *LagCurveEaseIn;

	/** lag movement ease-out curve */
	UPROPERTY(EditAnywhere, Category = PlayerLag)
	UCurveFloat *LagCurveEaseOut;

	bool PlayerLagIsMoving;
	float PlayerLagEaseInTimer;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void Activate(bool bReset = false) override;

private:
	void OnEnterNeck();

	void TickEyeDart(float DeltaTime);
	void TickEyes(float DeltaTime);
	void TickNeck(float DeltaTime);
	void TickPlayerLag(float DeltaTime);
	
	void TickEaseTimer(float DeltaTime, EInteractiveTrackingState CurState, float TimerMax, float &TimerValue);
	void TickEaseState(float DeltaTime, bool StateActive, float TimerValue, float TimerMax, EInteractiveTrackingState &CurState);

	FVector GetPlayerPosition() const;
	float GetEaseMultiplier(float EaseTimerCurrent, float EaseTimerMax) const;
	float CalculateEyeSeparation() const;
};
