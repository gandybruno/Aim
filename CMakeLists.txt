cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

include_directories(include)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"${ADDITIONAL_LIBRARY_DEPENDENCIES}"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/api_civ.9.lib"
	PARENT_SCOPE
)

 set(LIBRARIES
	"${LIBRARIES}"
	"${CMAKE_CURRENT_SOURCE_DIR}/bin/api_civ.9.dll"
	PARENT_SCOPE
 )