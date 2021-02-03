cmake_minimum_required(VERSION 3.7)

set (PROJECT_NAME "TestOpenGL" )

project("${PROJECT_NAME}")

# PROJECT_ROOT

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(src)

#find_package(OpenGL REQUIRED)

#include_directories(${OPENGL_INCLUDE_DIR})

# find_package(Boost COMPONENTS thread-mt REQUIRED)
# if(NOT Boost_FOUND)
# 	message(SEND_ERROR "Failed to find boost::thread-mt.")
# 	return()
# else()
# 	include_directories(${Boost_INCLUDE_DIRS})
# endif()

#target_link_libraries(${PROJECT_NAME} 
#                                ${CMAKE_DL_LIBS}
#                                ${OPENGL_LIBRARY}
#                                ${Boost_LIBRARIES})
                                