
#include <stdway.h>

StdWay::StdWay( const City& theCity1, const City& theCity2 )
	: myCity1( theCity1 ), myCity2( theCity2 )
{
}

City StdWay::city( int theIndex ) const
{
	if( theIndex==0 )
		return myCity1;
	else if( theIndex==1 )
		return myCity2;
	else
		return City();
}

double StdWay::distance() const
{
	return myCity1.distance( myCity2 );
}
