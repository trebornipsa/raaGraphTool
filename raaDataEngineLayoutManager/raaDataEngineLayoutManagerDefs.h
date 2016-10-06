#pragma once
#pragma once
#ifndef RAADATAENGINELAYOUTMANAGERDEFS
#define RAADATAENGINELAYOUTMANAGERDEFS

#ifdef _WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4565 )
#pragma warning( disable : 4150 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )

#ifdef _STATIC_RAADATAENGINELAYOUTMANAGER
#define RAADATAENGINELAYOUTMANAGER_DLL_DEF
#else
#ifdef RAADATAENGINELAYOUTMANAGER_EXPORTS
#define RAADATAENGINELAYOUTMANAGER_DLL_DEF __declspec(dllexport)
#else
#define RAADATAENGINELAYOUTMANAGER_DLL_DEF __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"raaDataEngineLayoutManagerD")
#else
#pragma comment(lib,"raaDataEngineLayoutManagerR")
#endif
#endif 
#endif
#else
#define RAADATAENGINELAYOUTMANAGER_DLL_DEF
#endif

#endif