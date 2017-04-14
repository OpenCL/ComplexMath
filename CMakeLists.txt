cmake_minimum_required(VERSION 3.1)

# Change project name
project(ComplexMath)

# find OpenCL
find_package(OpenCL REQUIRED)
include_directories(SYSTEM ${OpenCL_INCLUDE_DIRS})

# find Boost
find_package(Boost 1.54 REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# find Boost.Compute
if(${Boost_VERSION} LESS 106100)
    find_path(BOOST_COMPUTE_INCLUDE boost/compute.hpp)
    include_directories(SYSTEM ${BOOST_COMPUTE_INCLUDE})
endif()

# If no build type specified, configure for Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

# C++11
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Disable "no-unused-result" warning
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-unused-result")
endif()

# Configure Boost.Compute
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BoostComputeConfig.cmake)
# Enable automatic kernel compilation error messages for tests
add_definitions(-DBOOST_COMPUTE_DEBUG_KERNEL_COMPILATION)

# Add project path
add_definitions(-DOPENCL_COMPLEX_MATH_DIR="${PROJECT_SOURCE_DIR}")

enable_testing()
add_subdirectory(test)
