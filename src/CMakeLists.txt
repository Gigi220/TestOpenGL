cmake_minimum_required(VERSION 3.7)

set (TARGET_NAME "EngineTest" )

project("${TARGET_NAME}")

if(MSVC)
	add_compile_options(/MP)				#Use multiple processors when building
	add_compile_options(/W4 /wd4201 /WX)	#Warning level 4, all warnings are errors
else()
	add_compile_options(-W -Wall -Werror) #All Warnings, all warnings are errors
endif()

#get_filename_component(ENGINE_DIR "${MAKER_MODULE_DIR}/../.." ABSOLUTE)

# source for the test executable
set  (OpenGL_TEST_SOURCES
		"main.cpp")

add_executable( ${TARGET_NAME}
	${OpenGL_TEST_SOURCES} 
	)

find_package(RTTR CONFIG REQUIRED Core)
target_link_libraries(${TARGET_NAME} PUBLIC RTTR::Core_Lib)     # rttr as static library