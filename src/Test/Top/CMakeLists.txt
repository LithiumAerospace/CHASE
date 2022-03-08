set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/Instances.fpp"
	"${CMAKE_CURRENT_LIST_DIR}/Topology.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/TopTopologyDefs.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"
)

set(MOD_DEPS
  Drv/Udp
  Drv/TcpClient

  Svc/LinuxTime
)

register_fprime_executable()
