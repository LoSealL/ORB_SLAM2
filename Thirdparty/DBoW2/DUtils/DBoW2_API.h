#pragma once

#ifdef _MSC_VER
// We are using a Microsoft compiler:
#ifdef ORB_SHARED_LIBS
#ifdef DBoW2_Export
#define DBOW2_API __declspec(dllexport)
#else
#define DBOW2_API __declspec(dllimport)
#endif
#else
#define DBOW2_API
#endif

#else
// Not Microsoft compiler so set empty definition:
#define DBOW2_API
#endif