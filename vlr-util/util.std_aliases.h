#pragma once

#include <string>

#include "UtilMacros.Namespace.h"
#include "config.h"

VLR_NAMESPACE_BEGIN( vlr )

// TODO? Replace this with non-preprocessor impl
#ifndef UNICODE
using tstring = std::string;
#else
using tstring = std::wstring;
#endif

using string = std::string;
using wstring = std::wstring;

VLR_NAMESPACE_END //( vlr )
