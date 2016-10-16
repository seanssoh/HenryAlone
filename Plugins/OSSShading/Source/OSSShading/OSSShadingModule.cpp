// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "OSSShadingPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogOSSShading);

#define LOCTEXT_NAMESPACE "OSSPlayerModule"

/**
 * Implements the FOSSPlayer module.
 */
class OSSShadingModule
	: public IModuleInterface
{
public:

	/**
	 * Default constructor.
	 */
	OSSShadingModule( ) { }

	// IModuleInterface interface
	virtual void StartupModule( ) override
	{
	}

	virtual void ShutdownModule( ) override
	{
	}

protected:

private:

};


IMPLEMENT_MODULE(OSSShadingModule, OSSShading);


#undef LOCTEXT_NAMESPACE
