cmake_minimum_required (VERSION 2.6)

project (mqtt-cpp)

set(MQTTAPP_CMAKE_DIR ${mqtt-cpp_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${MQTTAPP_CMAKE_DIR} ${CMAKE_MODULE_PATH})

include(cmake/macros.cmake)

# Finding packages

find_package(JsonCpp REQUIRED)
if(NOT JsonCpp_FOUND)
	message(SEND_ERROR "Failed to find jsoncpp library")
endif()

find_package(Paho REQUIRED)
if(NOT Paho_FOUND)
	message(SEND_ERROR "Failed to find Paho C library")
endif()

find_package(Paho-C++ REQUIRED)
if(NOT Paho-C++_FOUND)
	message(SEND_ERROR "Failed to find Pago C++ library")
endif()

use_cxx11()

include_directories(${JsonCpp_INCLUDE_DIR})
include_directories(
		src
		src/params
		src/cli
		src/helper
		src/mqtt
		src/mqtt/action_listeners
		src/mqtt/msg_handlers
	)

file(GLOB_RECURSE SOURCES
		src/*.cpp
		app/*.cpp
	)

add_executable(mqtt-cpp ${SOURCES})
target_link_libraries(mqtt-cpp jsoncpp paho-mqtt3as paho-mqttpp3)

# Documentation
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

if(BUILD_DOC)
	# check if Doxygen is installed
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
			# set input and output files
			set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
			set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

			# request to configure the file
			configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
			message("-- Building Doxyfile done")

			# note the option ALL which allows to build the docs together with the application
			add_custom_target( doc_doxygen ALL
				COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
				COMMENT "Generating API documentation with Doxygen"
				VERBATIM )
	else(DOXYGEN_FOUND)
		message(SEND_ERROR "Doxygen need to be installed to generate the doxygen documentation")
	endif(DOXYGEN_FOUND)
endif(BUILD_DOC)