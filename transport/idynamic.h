
#pragma once

#include <decl.h>

class TRANSPORT_API IDynamic
{
public:
	virtual void next( double dt ) = 0;
};
