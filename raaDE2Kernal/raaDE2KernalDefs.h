#pragma once
#ifndef RAADE2KERNALDEFS
#define RAADE2KERNALDEFS

#ifdef _WIN32
#pragma warning( disable : 4251 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4565 )
#pragma warning( disable : 4150 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )

#ifdef _STATIC_RAADE2KERNAL
#define RAADE2KERNAL_DLL_DEF
#else
#ifdef RAADE2KERNAL_EXPORTS
#define RAADE2KERNAL_DLL_DEF __declspec(dllexport)
#else
#define RAADE2KERNAL_DLL_DEF __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"raaDE2KernalD")
#else
#pragma comment(lib,"raaDE2KernalR")
#endif
#endif 
#endif
#else
#define RAADE2KERNAL_DLL_DEF
#endif

#endif