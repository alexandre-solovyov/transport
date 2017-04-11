
#include <vehicle.h>
#include <math.h>
#include <global.h>
#include <iway.h>

double kmh2ms( double v )
{
	return v * 1000 / 3600;
}

double ms2kmh( double v )
{
	return v / 1000 * 3600;
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



Info VehicleInfo::info( MODE theMode, double theDistance ) const
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

Info VehicleInfo::complete( double theDistanceKM ) const
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

double VehicleInfo::mass() const
{
	//TODO: include weight of pass and fuel
	return MA;
}

double VehicleInfo::cost( double theDistanceKM,
										  double theTimeH,
											double theCapacity ) const
{
	Info i = complete( theDistanceKM );
	Global g;

	double aComplPrice = i.fuel * g.getValue( AV_FUEL );
	for( int i=0, n=EQ.size(); i<n; i++ )
	{
		double s = g.getValue( EQ[i] );
		s = s / g.getValue( NB_WD ) / g.getValue( NB_WH );
		s = s * theTimeH;
		aComplPrice += s;
	}

	aComplPrice += g.getValue( AV_FARE ) * mass() / 1000.0;

	double nb = NP * theCapacity;
	double p = aComplPrice / nb;
	return p;
}

Info VehicleInfo::complete( const IWay& theWay ) const
{
	return complete( theWay.distance() );
}

double VehicleInfo::cost( const IWay& theWay, double theCapacity ) const
{
	Info i = complete( theWay );
	return cost( i.distance/1000, i.time/3600, theCapacity );
}



Vehicle::Vehicle( const VehicleInfo& theInfo )
	: myInfo( theInfo )
{
	setWay( 0 );
}

IWay* Vehicle::way() const
{
	return myWay;
}

void Vehicle::setWay( IWay* theWay )
{
	myWay = theWay;
	myDistance = myWay ? myWay->distance()*1000 : 0;
	myLDistance = 0;
	myPosition = 0;
	myVelocity = 0;
	myMode = VehicleInfo::STOP;
}

double Vehicle::position() const
{
	return myPosition;
}

double Vehicle::velocity() const
{
	return myVelocity;
}

void Vehicle::print()
{
	printf( "[%.0f km %.0f km/h]\n", myPosition/1000, ms2kmh( myVelocity ) );
}

void Vehicle::go()
{
	myMode = VehicleInfo::ACCEL;
	Info i = myInfo.info( VehicleInfo::LAND, myDistance );
	myLDistance = myDistance - i.distance;
}

void Vehicle::next( double dt )
{
	if( myMode==VehicleInfo::STOP )
		return;

	double a = myInfo.A[myMode];
	myPosition += ( myVelocity * dt + a * dt * dt / 2 );
	myVelocity += a * dt;
	if( myVelocity<0 )
		myVelocity = 0;

	double cv_ms = kmh2ms( myInfo.CV );
	if( myMode==VehicleInfo::ACCEL && myVelocity>=cv_ms )
	{
		myVelocity = cv_ms;
		myMode = VehicleInfo::CRUISE;
	}
	if( myMode==VehicleInfo::CRUISE && myPosition>=myLDistance )
	{
		myMode = VehicleInfo::LAND;
	}
	if( myMode==VehicleInfo::LAND && myVelocity<=0 )
	{
		myMode = VehicleInfo::STOP;
	}
}
