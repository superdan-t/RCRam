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
set ( NANOGUI_BUILD_SHARED	OFF CACHE BOOL " " FORCE )
add_subdirectory ( ext/nanogui )
set_property ( TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies" )
add_definitions ( ${NANOGUI_EXTRA_DEFS} )
include_directories ( ${NANOGUI_EXTRA_INCS} "ext/nanogui/include" )
link_libraries ( nanogui ${NANOGUI_EXTRA_LIBS} )

find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
find_library(AVUTIL_LIBRARY avutil)

find_path(AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h)
find_library(AVDEVICE_LIBRARY avdevice)

file (GLOB remotecontrol_SRC
	"remotecontrol/*.hpp"
	"remotecontrol/*.cpp"
)

file (GLOB gui_SRC
	"gui/*.hpp"
	"gui/*.cpp"
)

add_executable ( ControlStation "ControlStation.cpp" ${remotecontrol_SRC} ${gui_SRC} )

#add_subdirectory( glfw-3.3.2 )
#add_subdirectory( wxWidgets-3.1.3 )
#find_package(OpenGL REQUIRED)
#include_directories( wxWidgets-3.1.3/include ) # ${OPENGL_INCLUDE_DIRS} glfw-3.3.2/include
#target_include_directories( ${Boost_INCLUDE_DIRS} )
target_include_directories(ControlStation PRIVATE ${AVCODEC_INCLUDE_DIR} ${AVFORMAT_INCLUDE_DIR} ${AVUTIL_INCLUDE_DIR} ${AVDEVICE_INCLUDE_DIR})
target_link_libraries( ControlStation PRIVATE ${AVCODEC_LIBRARY} ${AVFORMAT_LIBRARY} ${AVUTIL_LIBRARY} ${AVDEVICE_LIBRARY})
target_link_libraries( ControlStation LINK_PUBLIC comutils ) # glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} net core base
