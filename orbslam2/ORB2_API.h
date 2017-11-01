#pragma once

#ifdef _MSC_VER
// We are using a Microsoft compiler:
#ifdef ORB_SHARED_LIBS
#ifdef Orb_Export
#define ORB2_API __declspec(dllexport)
#else
#define ORB2_API __declspec(dllimport)
#endif
#else
#define ORB2_API
#endif

#else
// Not Microsoft compiler so set empty definition:
#define ORB2_API
#endif