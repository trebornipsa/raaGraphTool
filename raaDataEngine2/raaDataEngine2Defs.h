#pragma once
#ifndef RAADATAENGINE2DEFS
#define RAADATAENGINE2DEFS

#ifdef _WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4565 )
#pragma warning( disable : 4150 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )

#ifdef _STATIC_RAADATAENGINE2
#define RAADATAENGINE2_DLL_DEF
#else
#ifdef RAADATAENGINE2_EXPORTS
#define RAADATAENGINE2_DLL_DEF __declspec(dllexport)
#else
#define RAADATAENGINE2_DLL_DEF __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"raaDataEngine2D")
#else
#pragma comment(lib,"raaDataEngine2R")
#endif
#endif 
#endif
#else
#define RAADATAENGINE2_DLL_DEF
#endif

#endif