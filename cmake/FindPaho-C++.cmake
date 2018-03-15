find_path(Paho-C++_INCLUDE_DIR "mqtt/async_client.h"
	DOC "Specify Paho C++ include directory")

find_library(Paho-C++_LIBRARY
	NAMES paho-mqttpp3
	PATHS
	DOC "Specify location of paho-mqttpp3")


include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
	Paho-C++
	DEFAULT_MSG
	Paho-C++_LIBRARY Paho-C++_INCLUDE_DIR)

if (PAHO_FOUND)
	set(PAHO_CPP_LIBRARIES ${PAHO_CPP_LIBRARY})
    set(PAHO_CPP_DEFINITIONS)
endif()

# Tell cmake GUIs to ignore the "local" variables.
mark_as_advanced(Paho-C++_LIBRARY Paho-C++_INCLUDE_DIR)