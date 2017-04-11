
#include <etable.h>
#include <tools.h>
#include <sstream>
#include <iostream>

bool ETable::load( const std::string& theFileName )
{
	std::wstring aContents;
	bool isOK = loadUTF16( theFileName, aContents );
	if( !isOK )
		return false;

	std::wstringstream aStream( aContents );
	std::wstring aLine;
	bool isFirst = true;
	while( std::getline( aStream, aLine, wchar_t('\n') ) )
	{
		readLine( aLine, isFirst );
		isFirst = false;
	}
	return true;
}

bool ETable::readLine( const std::wstring& theLine, bool isFirst )
{
	std::vector<std::wstring> items = split( theLine, ';' );
	if( isFirst )
	{
		myFields.clear();
		for( int i=0, n=items.size(); i<n; i++ )
			myFields.push_back( toS( items[i] ) );
		return true;
	}
	
	MapOfValues m;
	for( int i=0, n=items.size(); i<n; i++ )
		m[myFields[i]] = items[i];

	return add( m );
}
