
#include <global.h>

double Global::getValue( Entity e ) const
{
	switch( e )
	{
	case NB_D:
		return 30;  // days per month

	case NB_WD:
		return 20;  // working days per month

	case NB_WH:
		return 8;   // working hours per day

	case AV_FARE:
		return 8 * 60.4;

	case AV_FUEL:
		return 39.5;

	case H_AIR_COM:
		return 340000;

	case H_AIR_PIL:
		return 290000;

	case H_AIR_STE:
		return 80000;

	default:
		return 0;
	}
}
