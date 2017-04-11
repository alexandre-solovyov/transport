
#pragma once

#include <decl.h>

struct City;

class TRANSPORT_API IWay
{
public:
	virtual City city( int theIndex ) const = 0;
	virtual double distance() const = 0;
};
