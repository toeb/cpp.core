cmake_minimum_required(VERSION 2.8.7)

include("$ENV{CUTIL_PATH}/cmake/cutil_init.cmake")
cutil_init("" "${cutil_command_line_args} --target ${CMAKE_CURRENT_LIST_DIR}")
cpp_auto_configure()

