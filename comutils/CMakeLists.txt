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
