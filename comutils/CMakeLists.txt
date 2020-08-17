cmake_policy(SET CMP0074 NEW)
find_package(Boost REQUIRED) 
if (Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIR} )
	link_directories( ${Boost_LIBRARY_DIRS} )
	if (WIN32)
		# Target Windows 7 for compatiblity
		add_definitions(-D_WIN32_WINNT=0x0601)
	else()
		find_package(Threads REQUIRED)
		link_libraries( ${CMAKE_THREAD_LIBS_INIT} )
	endif()
endif()

file (GLOB devconsole_SRC
	"devconsole/*.hpp"
	"devconsole/*.cpp"
	"devconsole/exceptions/*.hpp"
	"devconsole/exceptions/*.cpp"
)

file (GLOB network_SRC
	"network/*.hpp"
	"network/*.cpp"
)
add_library (comutils ${devconsole_SRC} ${network_SRC})
target_include_directories (comutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
