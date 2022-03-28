cmake_minimum_required(VERSION 3.13)
project(Test VERSION 1.0.0 LANGUAGES C CXX)

include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

set(FPRIME_CURRENT_BUILD_ROOT "${FPRIME_PROJECT_ROOT}")
message(STATUS "F prime BUILD_ROOT currently set to: ${FPRIME_CURRENT_BUILD_ROOT}")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Svc/")

#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")
