
#pragma once

#include <decl.h>
#include <string>
#include <vector>
#include <map>

class TRANSPORT_API ETable
{
public:
	bool load( const std::string& );

protected:
	bool readLine( const std::wstring&, bool );

	typedef std::map<std::string, std::wstring> MapOfValues;
	virtual bool add( const MapOfValues& ) = 0;

private:
	std::vector<std::string> myFields;
};
