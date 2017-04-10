
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

