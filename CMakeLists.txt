cmake_minimum_required(VERSION 3.5.1)
project(ORB_SLAM2)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

# Build Options
option(ORBSLAM2_BUILD_SHARED_LIBS "build shared lib (.dll or .so)" ON)
option(ORBSLAM2_BUILD_EXAMPLES "build open dataset examples" OFF)
# Compile Options
option(orbslam2_compile_dbow2_manually "compile dbow2 with source (recommended for windows user)" OFF)
option(orbslam2_compile_g2o_manually "compile g2o with source (recommended for windows user)" OFF)
option(orbslam2_compile_pangolin "" OFF)

if(MSVC)
  # For MSVC, CMake sets certain flags to defaults we want to override.
  # This replacement code is taken from sample in the CMake Wiki at
  # http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace.
  foreach (flag_var
           CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
           CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
           CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
           CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
    # string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    # string(REPLACE "/W3" "/W4" ${flag_var} "${${flag_var}}")
  endforeach()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -wd4251 -wd4996 /bigobj")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4251 -wd4996 /bigobj")
  # Use unicode
  # add_definitions(-DUNICODE)
  # add_definitions(-D_UNICODE)
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -march=native")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native")
endif(MSVC)

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  add_definitions(-DCOMPILEDWITHC11)
  message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  add_definitions(-DCOMPILEDWITHC0X)
  message(STATUS "Using flag -std=c++0x.")
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set build type
if(ORBSLAM2_BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
  set(LIB_TYPE SHARED)
  add_definitions(-DORB_SHARED_LIBS)
  add_definitions(-DOrb_Export)
else()
  set(LIB_TYPE STATIC)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(Eigen3 3.1.0 REQUIRED)
find_package(OpenCV 3.0 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 2.4.3 QUIET)
   if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
   endif()
endif()

# DBoW2
if(orbslam2_compile_dbow2_manually)
  add_subdirectory(Thirdparty/DBoW2)
else()
  add_library(DBoW2 ${LIB_TYPE} IMPORTED)
  include_directories(Thirdparty/DBoW2)
  set_target_properties(DBoW2 PROPERTIES IMPORTED_LOCATION Thirdparty/DBoW2/lib/DBoW2.lib)
endif()
# g2o
set(G2O_LIBS stuff core types_sba types_sim3 types_slam3d solver_eigen solver_dense)
include_directories(Thirdparty/g2o ${PROJECT_BINARY_DIR}/Thirdparty/g2o)
if(orbslam2_compile_g2o_manually)
  add_subdirectory(Thirdparty/g2o)
else()

endif()
# pangolin
if(orbslam2_compile_pangolin)
  add_subdirectory(Thirdparty/pangolin)
  target_include_directories(pangolin PUBLIC Thirdparty/pangolin/include)
endif()

add_subdirectory(orbslam2)
# Build examples
if(ORBSLAM2_BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()
