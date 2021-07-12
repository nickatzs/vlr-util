#pragma once

#include "UtilMacros.Namespace.h"
#include "config.h"

VLR_NAMESPACE_BEGIN( vlr )

VLR_NAMESPACE_BEGIN( util )

template< size_t nIndex >
struct choice : public choice<nIndex + 1> {};

// An arbitrary cutoff...
template<>
struct choice<10> {};

VLR_NAMESPACE_END //( util )

VLR_NAMESPACE_END //( vlr )
