
#include <cities.h>
#include <tools.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>

City::City( char* theName )
{
	name = strip( toW( theName ? theName : "" ) );
}

bool City::isValid() const
{
	return !name.empty();
}

double City::distance( const City& theCity ) const
{
	double phi_a = toRad( latitude );
	double phi_b = toRad( theCity.latitude );
	double lam_a = toRad( longitude );
	double lam_b = toRad( theCity.longitude );
	
	double cosd = sin(phi_a)*sin(phi_b) + cos(phi_a)*cos(phi_b)*cos(lam_a - lam_b);
	double d = acos( cosd );
	double L = d*R_TERRE;
	return L;
}

bool Cities::add( const MapOfValues& m )
{
	City aCity;
	aCity.country    = m.find("Country")->second;
	aCity.name       = m.find("AccentCity")->second;
	aCity.population = toInt( m.find("Population")->second );
	aCity.latitude   = toDouble( m.find("Latitude")->second );
	aCity.longitude  = toDouble( m.find("Longitude")->second );
	return add( aCity );
}

bool Cities::add( const City& theCity )
{
	if( !theCity.isValid() )
		return false;

	std::wstring aName = theCity.name;
	MapOfCities::const_iterator it = myCities.find( aName );
	if( it!=myCities.end() )
		return false;

	myCities[aName] = theCity;
	return true;
}

void Cities::clear()
{
	myCities.clear();
}

size_t Cities::size() const
{
	return myCities.size();
}

City Cities::find( const std::wstring& theName ) const
{
	MapOfCities::const_iterator it = myCities.find( theName );
	if( it==myCities.end() )
		return City();
	else
		return it->second;
}
