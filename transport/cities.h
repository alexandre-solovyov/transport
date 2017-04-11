
#pragma once

#include <etable.h>

struct TRANSPORT_API City
{
public:
	City( char* = 0 );
	bool isValid() const;
	double distance( const City& ) const;

public:
	std::wstring country;
	std::wstring name;
	int          population;
	double       latitude;
	double       longitude;
};

class TRANSPORT_API Cities : public ETable
{
public:
	bool   add( const City& theCity );
	City   find( const std::wstring& ) const;
	void   clear();
	size_t size() const;

protected:
	virtual bool add( const MapOfValues& );

private:
	typedef std::map<std::wstring, City> MapOfCities;
	MapOfCities myCities;
};
