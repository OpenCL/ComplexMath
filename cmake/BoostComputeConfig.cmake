# Configure Boost.Compute

# Support for C++11
set(BOOST_COMPUTE_USE_CPP11 OFF)
if(NOT (CMAKE_CXX_STANDARD LESS 11))  
  set(BOOST_COMPUTE_USE_CPP11 ON)
  add_definitions(-DBOOST_COMPUTE_USE_CPP11)
endif()

# Support for offline-caching
option(BOOST_COMPUTE_USE_OFFLINE_CACHE "Use offline cache for OpenCL program binaries" ON)
if(${BOOST_COMPUTE_USE_OFFLINE_CACHE})
  add_definitions(-DBOOST_COMPUTE_USE_OFFLINE_CACHE)
endif()

# Thread-safety options
option(BOOST_COMPUTE_THREAD_SAFE "Compile with BOOST_COMPUTE_THREAD_SAFE defined" OFF)
if(${BOOST_COMPUTE_THREAD_SAFE})
  add_definitions(-DBOOST_COMPUTE_THREAD_SAFE)
  if(${BOOST_COMPUTE_USE_CPP11})
    if(MSVC)
      if (MSVC_VERSION GREATER 1800)
        add_definitions(-DBOOST_COMPUTE_HAVE_THREAD_LOCAL)
      endif()
    else()
      add_definitions(-DBOOST_COMPUTE_HAVE_THREAD_LOCAL)
    endif()
  endif()
endif()

if(${OpenCL_HEADER_CL_EXT_FOUND})
  add_definitions(-DBOOST_COMPUTE_HAVE_HDR_CL_EXT)
endif()

# Windows-only
if(WIN32)
  # Optional support for boost dynamic libraries
  option(BOOST_COMPUTE_BOOST_ALL_DYN_LINK "Use boost dynamic link libraries" OFF)
  if(${BOOST_COMPUTE_BOOST_ALL_DYN_LINK})
    add_definitions(-DBOOST_ALL_DYN_LINK)
  else()
    # For default use statis libs
    set(Boost_USE_STATIC_LIBS ON)
  endif()
  link_directories(${Boost_LIBRARY_DIRS})
endif()

# Visual Studio C++
if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-DNOMINMAX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4003") # Not enough actual parameters for a BOOST_PP macro
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244") # Warning C4244: 'initializing': conversion from 'double' to 'int', possible loss of data
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4305") # Warning C4305: 'initializing': truncation from 'double' to 'float'
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4800") # Warning C4800: 'uint32_t' : forcing value to bool 'true' or 'false' (performance warning)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4838") # Warning C4838: conversion from 'double' to 'float' requires a narrowing conversion
endif()

if (${BOOST_COMPUTE_USE_OFFLINE_CACHE})
  set(BOOST_COMPONENTS ${BOOST_COMPONENTS} system filesystem)
  add_definitions(-DBOOST_COMPUTE_USE_OFFLINE_CACHE)
endif()

if(${BOOST_COMPUTE_THREAD_SAFE} AND NOT ${BOOST_COMPUTE_USE_CPP11})
  set(BOOST_COMPONENTS ${BOOST_COMPONENTS} system thread)
endif()

if(MSVC AND BOOST_COMPONENTS)
  set(BOOST_COMPONENTS ${BOOST_COMPONENTS} chrono)
endif()

if(BOOST_COMPONENTS)
  list(REMOVE_DUPLICATES BOOST_COMPONENTS)
endif()
find_package(Boost 1.54 REQUIRED COMPONENTS ${BOOST_COMPONENTS})

if(NOT MSVC)
  add_definitions(-DBOOST_TEST_DYN_LINK)
else()
  if(MSVC AND ${BOOST_COMPUTE_BOOST_ALL_DYN_LINK})
      add_definitions(-DBOOST_TEST_DYN_LINK)
  endif()
endif()

