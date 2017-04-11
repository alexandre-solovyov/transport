
#include <tools.h>
#include <fstream>
#include <vector>
#include <sstream>

std::string toS( const std::wstring& theStr )
{
	return std::string( theStr.begin(), theStr.end() );
}

std::wstring toW( const std::string& theStr, bool fromUtf16 )
{
	if( fromUtf16 )
	{
		wchar_t* p = (wchar_t*)theStr.c_str();
		int n = theStr.size();
		return std::wstring( p, p + n );
	}
	else
		return std::wstring( theStr.begin(), theStr.end() );
}

std::wstring strip( const std::wstring& theStr )
{
	if( theStr.empty() )
		return theStr;

	int n = theStr.size();
	int i=0, j=n-1;
	while( i<n && iswspace(theStr[i]) ) i++;
	while( j>=i && iswspace(theStr[j]) ) j--;

	return std::wstring( theStr.begin()+i, theStr.begin()+j+1 );
}

bool loadUTF16( const std::string& theFileName, std::wstring& theContents )
{
	std::ifstream aFile( theFileName.c_str(), std::ios::binary | std::ios::in );
	if( !aFile.is_open() )
		return false;

  aFile.seekg( 0, std::ios::end );
	size_t aSize = aFile.tellg();

	std::vector<char> aBuffer( aSize );
	aFile.seekg( 0, std::ios::beg );
	aFile.read( &aBuffer[0], aSize );

	wchar_t* aWBuffer = (wchar_t*)(&aBuffer[0]);
	theContents = std::wstring( aWBuffer + BOM_SIZE, aWBuffer + aSize/sizeof(wchar_t) );
	aFile.close();

	return true;
}

std::vector<std::wstring> split( const std::wstring& theData, char theSep )
{
	std::wstringstream aStream( theData );
	std::vector<std::wstring> items;
	std::wstring anItem;
	while( std::getline( aStream, anItem, wchar_t( theSep ) ) )
		if( !anItem.empty() )
			items.push_back( anItem );
	return items;
}

int toInt( const std::wstring& theData )
{
	std::string aData = toS( theData );
	int aValue;
	if( sscanf( aData.c_str(), "%i", &aValue )==1 )
		return aValue;
	else
		return 0;
}

double toDouble( const std::wstring& theData )
{
	std::string aData = toS( theData );
	double aValue;
	if( sscanf( aData.c_str(), "%lf", &aValue )==1 )
		return aValue;
	else
		return 0;
}

double toRad( double theDegrees )
{
	return theDegrees / 180.0 * PI;
}
