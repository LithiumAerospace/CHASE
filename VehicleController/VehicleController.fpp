module CHASE {
  port stateReturnPort -> FlightState
  port statePort ( state: FlightState )

  active component VehicleController {
    async input port run: Svc.Cycle

    sync input port getState: stateReturnPort
    sync input port setState: statePort

    @ Command receive port
    command recv port CmdDisp

    @ Command registration port
    command reg port CmdReg

    @ Command response port
    command resp port CmdStatus

    @ Event port
    event port Log

    @ Text event port
    text event port LogText

    @ Time get port
    time get port Time

    @ Telemetry port
    telemetry port Tlm

    sync command SET_STATE( state: FlightState )

    event StateChanged( state: FlightState ) severity activity high format "New state is {}"

    telemetry state: FlightState

  }
}
