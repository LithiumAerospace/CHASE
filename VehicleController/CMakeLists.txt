set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/VehicleController.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/VehicleController.cpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/VehicleController.fpp"
)

register_fprime_ut()
