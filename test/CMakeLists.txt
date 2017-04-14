include_directories(../include)

set(BOOST_COMPONENTS unit_test_framework)

if(${BOOST_COMPUTE_USE_CPP11})
  # allow tests to use C++11 features
  add_definitions(-DBOOST_COMPUTE_USE_CPP11)
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

# enable automatic kernel compilation error messages for tests
add_definitions(-DBOOST_COMPUTE_DEBUG_KERNEL_COMPILATION)
 
function(add_opencl_test TEST_NAME TEST_SOURCE)
  get_filename_component(TEST_TARGET ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_TARGET} ${TEST_SOURCE})
  target_link_libraries(${TEST_TARGET}
    ${OpenCL_LIBRARIES}
    ${Boost_LIBRARIES}
  )

  add_test(${TEST_NAME} ${TEST_TARGET})
endfunction()

add_opencl_test("basics" test_basics.cpp)
