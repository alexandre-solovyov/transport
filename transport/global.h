
#pragma once

#include <decl.h>

enum Entity
{
	NB_D,
	NB_WD,
	NB_WH,

	AV_FARE,
	AV_FUEL,

	H_AIR_COM,
	H_AIR_PIL,
	H_AIR_STE,
};

class TRANSPORT_API Global
{
public:
	double getValue( Entity ) const;
};
