
#include "OSSInteractionPrivatePCH.h"


DEFINE_LOG_CATEGORY(LogOSSInteraction);

#define LOCTEXT_NAMESPACE "OSSInteractionModule"


/**
 * Implements the module.
 */
class OSSInteractionModule
	: public IModuleInterface
{
public:

	/**
	 * Default constructor.
	 */
	OSSInteractionModule() { }

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


IMPLEMENT_MODULE(OSSInteractionModule, OSSInteraction);


#undef LOCTEXT_NAMESPACE
