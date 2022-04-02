set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/EPSController.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/EPSController.cpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/EPSController.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Test.cpp"
)

register_fprime_ut()
