
#include <tools.h>
#include <fstream>
#include <vector>

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
	const int BOM_SIZE = 2;
	theContents = std::wstring( aWBuffer + BOM_SIZE, aWBuffer + aSize/sizeof(wchar_t) );
	aFile.close();

	return true;
}
