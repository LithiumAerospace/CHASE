module CHASE {
  enum SubsystemStatus : U8 {
    NOMINAL,
    WARN,
    ERROR
  }

  port SubsystemStatusPort ( status: SubsystemStatus )
}
