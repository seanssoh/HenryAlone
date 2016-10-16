// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FTransform;
#ifdef OSSINTERACTION_OSSInteractiveAgentComponent_generated_h
#error "OSSInteractiveAgentComponent.generated.h already included, missing '#pragma once' in OSSInteractiveAgentComponent.h"
#endif
#define OSSINTERACTION_OSSInteractiveAgentComponent_generated_h

#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_RPC_WRAPPERS
#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS
#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_EVENT_PARMS \
	struct OSSInteractiveAgentComponent_eventDoLookAt_Parms \
	{ \
		float Pitch; \
		float Yaw; \
	}; \
	struct OSSInteractiveAgentComponent_eventInitNeckReferenceTransform_Parms \
	{ \
		FTransform ReturnValue; \
	}; \
	struct OSSInteractiveAgentComponent_eventIsEyeTrackingEnabled_Parms \
	{ \
		bool ReturnValue; \
 \
		/** Constructor, initializes return property only **/ \
		OSSInteractiveAgentComponent_eventIsEyeTrackingEnabled_Parms() \
			: ReturnValue(false) \
		{ \
		} \
	}; \
	struct OSSInteractiveAgentComponent_eventIsNeckTrackingEnabled_Parms \
	{ \
		bool ReturnValue; \
 \
		/** Constructor, initializes return property only **/ \
		OSSInteractiveAgentComponent_eventIsNeckTrackingEnabled_Parms() \
			: ReturnValue(false) \
		{ \
		} \
	};


extern OSSINTERACTION_API  FName OSSINTERACTION_DoLookAt;
extern OSSINTERACTION_API  FName OSSINTERACTION_InitNeckReferenceTransform;
extern OSSINTERACTION_API  FName OSSINTERACTION_IsEyeTrackingEnabled;
extern OSSINTERACTION_API  FName OSSINTERACTION_IsNeckTrackingEnabled;
#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_CALLBACK_WRAPPERS
#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUOSSInteractiveAgentComponent(); \
	friend OSSINTERACTION_API class UClass* Z_Construct_UClass_UOSSInteractiveAgentComponent(); \
	public: \
	DECLARE_CLASS(UOSSInteractiveAgentComponent, UActorComponent, COMPILED_IN_FLAGS(CLASS_Abstract), 0, TEXT("/Script/OSSInteraction"), NO_API) \
	DECLARE_SERIALIZER(UOSSInteractiveAgentComponent) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_INCLASS \
	private: \
	static void StaticRegisterNativesUOSSInteractiveAgentComponent(); \
	friend OSSINTERACTION_API class UClass* Z_Construct_UClass_UOSSInteractiveAgentComponent(); \
	public: \
	DECLARE_CLASS(UOSSInteractiveAgentComponent, UActorComponent, COMPILED_IN_FLAGS(CLASS_Abstract), 0, TEXT("/Script/OSSInteraction"), NO_API) \
	DECLARE_SERIALIZER(UOSSInteractiveAgentComponent) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UOSSInteractiveAgentComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UOSSInteractiveAgentComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOSSInteractiveAgentComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOSSInteractiveAgentComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UOSSInteractiveAgentComponent(UOSSInteractiveAgentComponent&&); \
	NO_API UOSSInteractiveAgentComponent(const UOSSInteractiveAgentComponent&); \
public:


#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UOSSInteractiveAgentComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UOSSInteractiveAgentComponent(UOSSInteractiveAgentComponent&&); \
	NO_API UOSSInteractiveAgentComponent(const UOSSInteractiveAgentComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOSSInteractiveAgentComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOSSInteractiveAgentComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UOSSInteractiveAgentComponent)


#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_24_PROLOG \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_EVENT_PARMS


#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_RPC_WRAPPERS \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_CALLBACK_WRAPPERS \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_INCLASS \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_CALLBACK_WRAPPERS \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_INCLASS_NO_PURE_DECLS \
	HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h_27_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class OSSInteractiveAgentComponent."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HenryAlone_Plugins_OSSInteraction_Source_OSSInteraction_Public_OSSInteractiveAgentComponent_h


#define FOREACH_ENUM_EINTERACTIVETRACKINGSTATE(op) \
	op(EITS_Inactive) \
	op(EITS_EaseIn) \
	op(EITS_Active) \
	op(EITS_EaseOut) 
#define FOREACH_ENUM_EEYEDARTSTATE(op) \
	op(EDS_LookingAtTarget) \
	op(EDS_LookingAway) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
