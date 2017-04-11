
#include <cities.h>
#include <tools.h>
#include <sstream>
#include <iostream>
#include <vector>

City::City( char* theName )
{
	name = strip( toW( theName ? theName : "" ) );
}

bool City::isValid() const
{
	return !name.empty();
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
