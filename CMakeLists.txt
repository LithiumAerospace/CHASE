cmake_minimum_required(VERSION 3.13)
project(Test VERSION 1.0.0 LANGUAGES C CXX)

include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/util/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/EPS/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SystemController/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/VehicleController/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")
