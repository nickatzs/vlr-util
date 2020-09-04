#include "pch.h"

#include "vlr/zstring_view.h"

static std::function<void( vlr::tzstring_view svzFailureMessage )> g_fOnCheckFailure;

void HandleCheckFailure( vlr::tzstring_view svzFailureMessage )
{
	if (g_fOnCheckFailure)
	{
		g_fOnCheckFailure( svzFailureMessage );
	}
}

#define VLR_CONFIG_HAVEIMPL_HandleCheckFailure

#include "vlr/UtilMacros.Assertions.h"

TEST( Assertions, general )
{

}