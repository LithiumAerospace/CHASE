module Svc {
  active component SyncManager {

    # ----------------------------------------------------------------------
    # General Ports
    # ----------------------------------------------------------------------

    async input port run: Svc.Cycle

    async input port externalIn: Fw.BufferSend

    async input port syncIn: [32] Fw.BufferSend
    output port syncOut: [32] Fw.BufferGet

    async input port pingIn: Svc.Ping
    output port pingOut: Svc.Ping

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ Event port
    event port eventOut

    @ Text event port
    text event port LogText

    @ Time get port
    time get port timeCaller

    @ Telemetry port
    telemetry port tlmOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------


    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------


    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

  }
}
