
#include <vehicle.h>
#include <math.h>

double kmh2ms( double v )
{
	return v * 1000 / 3600;
}

Info::Info()
{
	time = 0;
	distance = 0;
	fuel = 0;
}

Info Info::operator+( const Info& i2)
{
	Info r;
	r.time = time + i2.time;
	r.distance = distance + i2.distance;
	r.fuel = fuel + i2.fuel;
	return r;
}



Info Vehicle::info( MODE theMode, double theDistance ) const
{
	double CV_ms = kmh2ms( CV );
	double GT_s = GT/3600;

	Info info;
	double t;

	switch( theMode )
	{
	case ACCEL:
		t = CV_ms/fabs(A[theMode]);         //time of acceleration
		info.time = t;
		info.distance = A[theMode]*t*t/2;   //distance of acceleration
		break;

	case CRUISE:
		info.time = theDistance / CV_ms;   // cruise time
		info.distance = theDistance;       // cruise distance
		break;

	case LAND:
		t = CV_ms/fabs(A[LAND]);                   //time of landing
		info.time = t;
		info.distance = CV_ms*t + A[LAND]*t*t/2;   //distance of landing
		break;

	default:
		return info;
	}

	info.fuel = GT_s * FC[theMode] * info.time;
	return info;
}

Info Vehicle::complete( double theDistanceKM ) const
{
	double DM = theDistanceKM * 1000;

	Info i1 = info( ACCEL, 0 );
	Info i2 = info( LAND, 0 );
	double dc = DM - i1.distance - i2.distance;
	if( dc < 0 )
		return Info();

	Info ic = info( CRUISE, dc );
	return i1 + i2 + ic;
}
