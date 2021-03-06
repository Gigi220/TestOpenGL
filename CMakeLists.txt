cmake_minimum_required(VERSION 3.7)

project(TestOpenGL)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
	add_compile_options(/MP)				#Use multiple processors when building
	add_compile_options(/W4 /wd4201 /WX)	#Warning level 4, all warnings are errors
else()
	add_compile_options(-W -Wall -Werror) #All Warnings, all warnings are errors
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set( CMAKE_CXX_STANDARD_LIBRARIES "$(CMAKE_CXX_STANDARD_LIBRARIES) %(AdditionalDependencies) " )

# link directories with libs and including files
link_directories( ${CMAKE_SOURCE_DIR}/ExternalLibraries/libs )
link_directories( ${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_1_75_0/stage/lib )
include_directories( ${CMAKE_SOURCE_DIR}/ExternalLibraries/boost_1_75_0 )
include_directories( ${CMAKE_SOURCE_DIR}/ExternalLibraries/include )
	
# OpenGL and other stuff
find_package(OpenGL REQUIRED)

# RTTR
find_package(RTTR CONFIG REQUIRED Core)

# source files
file(
	GLOB_RECURSE _source_list 
	LIST_DIRECTORIES false
	"${CMAKE_SOURCE_DIR}/src/*.c*"
	"${CMAKE_SOURCE_DIR}/src/*.h*"
)

foreach(_source IN ITEMS ${_source_list})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${CMAKE_SOURCE_DIR}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()
#-----------------------------------------

# resources files
file(
	GLOB_RECURSE _resources_list 
	LIST_DIRECTORIES false
	"${CMAKE_SOURCE_DIR}/base/*.xml"
)

foreach(_resource IN ITEMS ${_resources_list})
	get_filename_component(_resource_path "${_resource}" PATH)
	file(RELATIVE_PATH _resource_path_rel "${CMAKE_SOURCE_DIR}" "${_resource_path}")
	string(REPLACE "/" "\\" _resource_group_path "${_resource_path_rel}")
	source_group("${_resource_group_path}" FILES "${_resource}")
endforeach()
#-----------------------------------------

add_executable( ${PROJECT_NAME} ${_source_list} ${_resources_list})

target_link_libraries(${PROJECT_NAME} PUBLIC RTTR::Core_Lib	# rttr as static library
								OpenGL::GL
								glfw3 ${GLFW_LIBRARIES}
                                glew32s ${GLEW_LIBRARIES}
                                soil2-debug
                                )  