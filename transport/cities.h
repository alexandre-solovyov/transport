
#pragma once

#include <decl.h>
#include <string>
#include <vector>

class TRANSPORT_API City
{
public:
	City( const std::wstring& = std::wstring() );
	City( const char* );

	bool isValid() const;
	std::wstring name() const;

	static City load( const std::wstring& );

protected:
	void setName( const std::wstring& );

private:
	std::wstring myName;
};

class TRANSPORT_API Cities
{
public:
	static Cities* get();

	bool load( const std::string& );

private:
	static Cities* CITIES;
	std::vector<City> myCities;
};
