# Find the Args C++ include files.
#
# This module defines
# Args-C++_INCLUDE_DIRS - where to find args.hxx
# Args-C++_FOUND - false if header wasn't find

find_path(Args-C++_INCLUDE_DIR "args.hxx"
    DOC "Specify the JsonCpp include directory here")

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
	Args-C++
	DEFAULT_MSG
	Args-C++_INCLUDE_DIR)

# Tell cmake GUIs to ignore the "local" variables.
mark_as_advanced(Paho-C++_INCLUDE_DIR)