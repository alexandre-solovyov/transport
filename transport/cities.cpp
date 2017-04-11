
#include <cities.h>
#include <tools.h>
#include <sstream>
#include <iostream>
#include <vector>

Cities* Cities::CITIES = 0;

City::City( const char* theName )
{
	setName( toW( theName ) );
}

City::City( const std::wstring& theName )
{
	setName( theName );
}

void City::setName( const std::wstring& theName )
{
	myName = strip( theName );
}

bool City::isValid() const
{
	return !name().empty();
}

std::wstring City::name() const
{
	return myName;
}

double coord( const std::wstring& theGrad, const std::wstring& theMin )
{
	//TODO
	return 0.0;
}

bool isStandard( const std::wstring& theName )
{
	//TODO
	return true;
}

City City::load( const std::wstring& theData )
{
	City aCity;

	std::wstringstream aStream( theData );
	std::vector<std::wstring> items;
	std::wstring anItem;
	while( std::getline( aStream, anItem, wchar_t(' ') ) )
		if( !anItem.empty() )
			items.push_back( anItem );

	const int STD_ITEMS = 7;
	while( items.size() > STD_ITEMS )
	{
		items[0] += toW( " " );
		items[0] += items[1];
		items.erase( items.begin()+1 );
	}

	if( items.size()==STD_ITEMS )
	{
		aCity.setName( items[0] );

		double latitude = coord( items[1], items[2] );
		if( !isStandard( items[3] ) )
			latitude = -latitude;

		double longitude = coord( items[4], items[5] );
		if( !isStandard( items[6] ) )
			longitude = -longitude;

		aCity.myLatitude = latitude;
		aCity.myLongitude = longitude;
	}

	return aCity;
}




Cities* Cities::get()
{
	if( !CITIES )
		CITIES = new Cities();
	return CITIES;
}

bool Cities::load( const std::string& theFileName )
{
	std::wstring aContents;
	bool isOK = loadUTF16( theFileName, aContents );
	if( !isOK )
		return false;

	//TODO: treatment of the contents
	std::wstringstream aStream( aContents );
	std::wstring aLine;
	while( std::getline( aStream, aLine, wchar_t('\n') ) )
	{
		aLine = strip(aLine);
		City aCity = City::load( aLine );
		if( aCity.isValid() )
			add( aCity );
  }
	return true;
}

bool Cities::add( const City& theCity )
{
	if( !theCity.isValid() )
		return false;

	std::wstring aName = theCity.name();
	MapOfCities::const_iterator it = myCities.find( aName );
	if( it!=myCities.end() )
		return false;

	myCities[aName] = theCity;
	return true;
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
