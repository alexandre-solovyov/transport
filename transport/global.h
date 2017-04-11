
#pragma once

#include <decl.h>

enum Entity
{
	AV_FUEL,
};

class TRANSPORT_API Global
{
public:
	double getPrice( Entity ) const;
};
