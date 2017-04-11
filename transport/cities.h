
#pragma once

#include <decl.h>
#include <string>
#include <map>

class TRANSPORT_API City
{
public:
	City( const std::wstring& = std::wstring() );
	City( const char* );

	bool isValid() const;
	std::wstring name() const;
	double latitude() const;
	double longitude() const;

	static City load( const std::wstring& );

protected:
	void setName( const std::wstring& );

private:
	std::wstring myName;
	double myLatitude;
	double myLongitude;
};

class TRANSPORT_API Cities
{
public:
	static Cities* get();

	bool load( const std::string& );
	bool add( const City& );
	City find( const std::wstring& ) const;

	size_t size() const;

private:
	static Cities* CITIES;

	typedef std::map<std::wstring, City> MapOfCities;
	MapOfCities myCities;
};
