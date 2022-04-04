module CHASE {
  enum EPSItemStatus : U8 {
    NOMINAL,
    UNDERVOLTWARN,
    UNDERVOLTERROR,
    OVERVOLTWARN,
    OVERVOLTERROR,
    OVERCURRENTWARN,
    OVERCURRENTERROR
  }

  enum EPSValueType : U8 {
    VOLTAGE,
    CURRENT
  }

  struct EPSItemConfig {
    $severity:    U8,
    hasVoltage:  bool,
    hasCurrent:  bool,
    hasSwitch:   bool,
    disableable: bool, @< Disable on overcurrent error
    undervolterror:   F32,
    undervoltwarn:    F32,
    overvoltwarn:     F32,
    overvolterror:    F32,
    overcurrentwarn:  F32,
    overcurrenterror: F32
  } default {
    overvoltwarn     = 999,
    overvolterror    = 999,
    overcurrentwarn  = 999,
    overcurrenterror = 999
  }

  struct EPSItem {
    switchState: Fw.Enabled,
    voltage: F32,
    current: F32,
    status: EPSItemStatus
  }

  constant NumEPSItems = 8

  array EPSItemArray       = [NumEPSItems] EPSItem
  array EPSItemConfigArray = [NumEPSItems] EPSItemConfig

  port Request
  port SwitchSet ( itemId: U8, enabled: Fw.Enabled )
  port EPSDataPort ( itemId: U8, $type: EPSValueType, value: F32 )

  active component EPSController {

    # -------------------------------------------------------------------------
    # Ports
    # -------------------------------------------------------------------------

    async input port run: Svc.Cycle

    async input port switchSet: SwitchSet
    output port switchMsg: [NumEPSItems] SwitchSet

    output port request: [NumEPSItems] Request
    async input port data: EPSDataPort

    # -------------------------------------------------------------------------
    # Telemetry
    # -------------------------------------------------------------------------

    @ Telemetry port
    telemetry port tlmOut

    @ Time get port
    time get port timeGetOut

    telemetry itemStatus: EPSItemArray

  }
}
