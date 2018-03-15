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