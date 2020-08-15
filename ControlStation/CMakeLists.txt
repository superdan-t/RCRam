# CMakeList.txt : CMake project for ControlStation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
cmake_policy(SET CMP0074 NEW)

project ("ControlStation")

find_package(Boost REQUIRED) 
if (Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIR} )
	link_directories( ${Boost_LIBRARY_DIRS} )
	if (WIN32)
		# Target Windows 7 for compatiblity
		message("Boost target is WIN32")
		add_definitions(-D_WIN32_WINNT=0x0601)
	else()
		message("Boost target is POSIX")
		find_package(Threads REQUIRED)
		link_libraries( ${CMAKE_THREAD_LIBS_INIT} )
	endif()
endif()

# Add source to this project's executable.
file (GLOB devconsole_SRC
	"devconsole/*.hpp"
	"devconsole/*.cpp"
	"devconsole/exceptions/*.hpp"
	"devconsole/exceptions/*.cpp"
)

file (GLOB remotecontrol_SRC
	"remotecontrol/*.hpp"
	"remotecontrol/*.cpp"
)

add_executable (ControlStation "ControlStation.cpp" ${devconsole_SRC} ${remotecontrol_SRC} )
#add_subdirectory( glfw-3.3.2 )
#add_subdirectory( wxWidgets-3.1.3 )
#find_package(OpenGL REQUIRED)
#include_directories( wxWidgets-3.1.3/include ) # ${OPENGL_INCLUDE_DIRS} glfw-3.3.2/include
#target_include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries( ControlStation ) # glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} net core base
