# Generated by Boost 1.75.0

# address-model=64

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "64 bit, need 32")
  return()
endif()

# layout=versioned

# toolset=vc142

if(Boost_COMPILER)
  if(NOT Boost_COMPILER STREQUAL "vc142" AND NOT Boost_COMPILER STREQUAL "-vc142")
    _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "vc142, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc142")
    _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "vc142, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=static

if(NOT Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "static runtime, Boost_USE_STATIC_RUNTIME not ON")
  return()
endif()

# runtime-debugging=off

if(Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "release runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=release

if(NOT "${Boost_USE_RELEASE_LIBS}" STREQUAL "" AND NOT Boost_USE_RELEASE_LIBS)
  _BOOST_SKIPPED("libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib" "release, Boost_USE_RELEASE_LIBS=${Boost_USE_RELEASE_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib")
endif()

# Create imported target Boost::stacktrace_noop

if(NOT TARGET Boost::stacktrace_noop)
  add_library(Boost::stacktrace_noop STATIC IMPORTED)

  set_target_properties(Boost::stacktrace_noop PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB"
  )
endif()

# Target file name: libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib

get_target_property(__boost_imploc Boost::stacktrace_noop IMPORTED_LOCATION_RELEASE)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::stacktrace_noop already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::stacktrace_noop APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

set_target_properties(Boost::stacktrace_noop PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE CXX
  IMPORTED_LOCATION_RELEASE "${_BOOST_LIBDIR}/libboost_stacktrace_noop-vc142-mt-s-x64-1_75.lib"
  )

set_target_properties(Boost::stacktrace_noop PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

list(APPEND _BOOST_STACKTRACE_NOOP_DEPS headers)
