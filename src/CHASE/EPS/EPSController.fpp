module CHASE {
  enum EPSStatus : U8 {
    NOMINAL      = 0x00,
    UNDERVOLT    = 0x01,
    OVERVOLT     = 0x02,
    OVERCURRENT  = 0x04
  }

  constant NumSwitches = 2
  constant NumSwitchSetPorts = 8
  constant NumVoltage = 2
  constant NumCurrent = 2

  array F32x2 = [2] F32

  array EPSVoltageStatusArray = [NumVoltage] EPSStatus
  array EPSCurrentStatusArray = [NumCurrent] EPSStatus

  array EPSVoltageArray = [NumVoltage] F32
  array EPSCurrentArray = [NumCurrent] F32

  array EPSVoltageConf    = [NumVoltage] F32x2
  array EPSCurrentConf    = [NumCurrent] F32

  array EPSSwitchStateArray = [NumSwitches] Fw.Enabled

  port Request ()
  port F32Port ( value: F32 )
  port EnabledPort ( enabled: Fw.Enabled )
  port SwitchSet ( switchId: U8, enabled: Fw.Enabled)

  active component EPSController {

    # -------------------------------------------------------------------------
    # Ports
    # -------------------------------------------------------------------------

    async input port run: Svc.Cycle

    async input port switchSet: [NumSwitchSetPorts] SwitchSet
    output port switchMsg: [NumSwitches] EnabledPort

    output port voltageRequest: [NumVoltage] Request
    async input port voltage:  [NumVoltage] F32Port
    match voltageRequest with voltage

    output port currentRequest: [NumCurrent] Request
    async input port current:  [NumCurrent] F32Port
    match currentRequest with current

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    # -------------------------------------------------------------------------
    # Telemetry
    # -------------------------------------------------------------------------

    @ Telemetry port
    telemetry port tlmOut

    @ Time get port
    time get port timeGetOut

    telemetry switchState: EPSSwitchStateArray

    telemetry voltageStatus: EPSVoltageStatusArray
    telemetry voltage:       EPSVoltageArray

    telemetry currentStatus: EPSCurrentStatusArray
    telemetry current:       EPSCurrentArray

    # -------------------------------------------------------------------------
    # Parameters
    # -------------------------------------------------------------------------

    @ Parameter get port
    param get port prmGetOut

    @ Parameter set port
    param set port prmSetOut

    param voltageConf: EPSVoltageConf
    param currentConf: EPSCurrentConf

  }
}
