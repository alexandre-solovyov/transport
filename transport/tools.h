
#pragma once

#include <decl.h>
#include <string>

TRANSPORT_API std::string  toS( const std::wstring& );
TRANSPORT_API std::wstring toW( const std::string& );
TRANSPORT_API std::wstring strip( const std::wstring& );
