add_executable ( ControlStation )

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

set ( NANOGUI_BUILD_EXAMPLE	OFF CACHE BOOL " " FORCE )
set ( NANOGUI_BUILD_PYTHON	OFF CACHE BOOL " " FORCE )
set ( NANOGUI_INSTALL		OFF CACHE BOOL " " FORCE )
add_subdirectory ( ext/nanogui )
set_property ( TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies" )
add_definitions ( ${NANOGUI_EXTRA_DEFS} )
include_directories ( ${NANOGUI_EXTRA_INCS} "ext/nanogui/include" )
target_link_libraries ( ControlStation LINK_PRIVATE nanogui ${NANOGUI_EXTRA_LIBS} )

file (GLOB remotecontrol_SRC
	"remotecontrol/*.hpp"
	"remotecontrol/*.cpp"
)

file (GLOB gui_SRC
	"gui/*.hpp"
	"gui/*.cpp"
)

target_sources ( ControlStation PRIVATE "ControlStation.cpp" ${remotecontrol_SRC} ${gui_SRC} )

#add_subdirectory( glfw-3.3.2 )
#add_subdirectory( wxWidgets-3.1.3 )
#find_package(OpenGL REQUIRED)
#include_directories( wxWidgets-3.1.3/include ) # ${OPENGL_INCLUDE_DIRS} glfw-3.3.2/include
#target_include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries( ControlStation LINK_PUBLIC comutils ) # glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} net core base
