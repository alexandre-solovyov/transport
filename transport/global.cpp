
#include <global.h>

double Global::getPrice( Entity e ) const
{
	switch( e )
	{
	case AV_FUEL:
		return 39.5;

	default:
		return 0;
	}
}
