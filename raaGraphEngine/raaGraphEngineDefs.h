#ifndef RAAGRAPHENGINEDEFS
#define RAAGRAPHENGINEDEFS

#ifdef WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4565 )
#pragma warning( disable : 4150 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )

#ifdef _STATIC_RAAGRAPHENGINE
#define RAAGRAPHENGINE_DLL_DEF
#else
#ifdef RAAGRAPHENGINE_EXPORTS
#define RAAGRAPHENGINE_DLL_DEF __declspec(dllexport)
#else
#define RAAGRAPHENGINE_DLL_DEF __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"raaGraphEngineD")
#else
#pragma comment(lib,"raaGraphEngineR")
#endif
#endif 
#endif
#else
#define RAAGRAPHENGINE_DLL_DEF
#endif

#endif