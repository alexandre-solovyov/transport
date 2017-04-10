
#include <cities.h>
#include <fstream>
#include <tools.h>

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

City City::load( const std::wstring& )
{
	City aCity;

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
	std::ifstream aFile( theFileName.c_str() );
	if( !aFile.is_open() )
		return false;

	std::string aLine;
	while( std::getline( aFile, aLine ) )
	{
		std::wstring aWLine = (wchar_t*)aLine.c_str();
		City aCity = City::load( aWLine );
		if( aCity.isValid() )
			myCities.push_back( aCity );
	}
	aFile.close();
	return true;
}
