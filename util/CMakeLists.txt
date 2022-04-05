set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/util.fpp"
)

if (BUILD_TESTING)
  list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/config.fpp")
endif()

register_fprime_module()
