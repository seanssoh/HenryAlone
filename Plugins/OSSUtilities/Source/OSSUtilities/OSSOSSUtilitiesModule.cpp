
#include "OSSUtilitiesPrivatePCH.h"


DEFINE_LOG_CATEGORY(LogOSSUtilities);

#define LOCTEXT_NAMESPACE "OSSUtilitiesModule"


/**
 * Implements the OSSWmfMedia module.
 */
class OSSUtilitiesModule
	: public IModuleInterface
{
public:

	/**
	 * Default constructor.
	 */
	OSSUtilitiesModule() { }

public:

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


IMPLEMENT_MODULE(OSSUtilitiesModule, OSSUtilities);


#undef LOCTEXT_NAMESPACE
