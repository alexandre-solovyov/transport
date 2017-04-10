
#include <tools.h>

std::string toS( const std::wstring& theStr )
{
	return std::string( theStr.begin(), theStr.end() );
}

std::wstring toW( const std::string& theStr )
{
	return std::wstring( theStr.begin(), theStr.end() );
}

std::wstring strip( const std::wstring& theStr )
{
	if( theStr.empty() )
		return theStr;

	int n = theStr.size();
	int i=0, j=n-1;
	while( i<n && theStr[i]==' ' ) i++;
	while( j>=i && theStr[j]==' ' ) j--;

	return std::wstring( theStr.begin()+i, theStr.begin()+j+1 );
}
