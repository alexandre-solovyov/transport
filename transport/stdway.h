
#pragma once

#include <iway.h>
#include <cities.h>

class TRANSPORT_API StdWay : public IWay
{
public:
	StdWay( const City& theCity1, const City& theCity2 );

	virtual City city( int theIndex ) const override;
	virtual double distance() const override;

private:
	City myCity1;
	City myCity2;
};
