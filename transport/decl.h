
#pragma once

#ifdef WIN32
  #ifdef TRANSPORT_EXPORTS
    #define TRANSPORT_API __declspec(dllexport)
  #else
    #define TRANSPORT_API __declspec(dllimport)
  #endif
#else
  #define TRANSPORT_API
  #define __stdcall
  #define override
#endif


const int    BOM_SIZE = 1;
const double PI       = 3.14159265;
const double R_TERRE  = 6371.0;
