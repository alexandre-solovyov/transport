
#pragma once

#include <decl.h>
#include <string>
#include <vector>

TRANSPORT_API std::string  toS( const std::wstring& );
TRANSPORT_API std::wstring toW( const std::string&, bool fromUtf16=false );
TRANSPORT_API std::wstring strip( const std::wstring& );
TRANSPORT_API bool loadUTF16( const std::string&, std::wstring& );
TRANSPORT_API std::vector<std::wstring> split( const std::wstring&, char );
TRANSPORT_API int toInt( const std::wstring& );
TRANSPORT_API double toDouble( const std::wstring& );
