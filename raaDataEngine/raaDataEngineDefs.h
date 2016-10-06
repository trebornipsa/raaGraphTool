#pragma once
#ifndef RAADATAENGINEDEFS
#define RAADATAENGINEDEFS

#ifdef _WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4565 )
#pragma warning( disable : 4150 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )

#ifdef _STATIC_RAADATAENGINE
#define RAADATAENGINE_DLL_DEF
#else
#ifdef RAADATAENGINE_EXPORTS
#define RAADATAENGINE_DLL_DEF __declspec(dllexport)
#else
#define RAADATAENGINE_DLL_DEF __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"raaDataEngineD")
#else
#pragma comment(lib,"raaDataEngineR")
#endif
#endif 
#endif
#else
#define RAADATAENGINE_DLL_DEF
#endif

#endif