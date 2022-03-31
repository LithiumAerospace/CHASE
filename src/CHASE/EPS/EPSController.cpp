// ======================================================================
// \title  EPSController.cpp
// \author nate
// \brief  cpp file for EPSController component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <CHASE/EPS/EPSController.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <CHASE/EPS/F32x2ArrayAc.hpp>

#define PRMVALID(valid) (valid == Fw::ParamValid::VALID || valid == Fw::ParamValid::DEFAULT)

namespace CHASE {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  EPSController ::
    EPSController(
        const char *const compName
    ) : EPSControllerComponentBase(compName)
  {

  }

  void EPSController ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    EPSControllerComponentBase::init(queueDepth, instance);
  }

  EPSController ::
    ~EPSController()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void EPSController ::
    run_handler(
        const NATIVE_INT_TYPE portNum,
        Svc::TimerVal &cycleStart
    )
  {
    for (NATIVE_INT_TYPE i = 0; i < NumVoltage; i++) {
      this->voltageRequest_out(i);
    }

    for (NATIVE_INT_TYPE i = 0; i < NumCurrent; i++) {
      this->currentRequest_out(i);
    }
  }

  void EPSController ::
    switchSet_handler(
        const NATIVE_INT_TYPE portNum,
        U8 switchId,
        const Fw::Enabled &enabled
    )
  {
    this->switchState[switchId] = enabled;

    this->switchMsg_out(switchId, enabled);
    this->tlmWrite_switchState(this->switchState);
  }

  void EPSController ::
    current_handler(
        const NATIVE_INT_TYPE portNum,
        F32 value
    )
  {
    this->current[portNum] = value;

    Fw::ParamValid valid;
    F32 high = this->paramGet_currentConf(valid)[portNum];
    if (value > high && PRMVALID(valid)) {
      this->currentStatus[portNum] = EPSStatus::UNDERVOLT;
      this->tlmWrite_currentStatus(this->currentStatus);
    }

    this->tlmWrite_current(this->current);
  }

  void EPSController ::
    voltage_handler(
        const NATIVE_INT_TYPE portNum,
        F32 value
    )
  {
    this->voltage[portNum] = value;

    Fw::ParamValid valid;
    F32x2 param = this->paramGet_voltageConf(valid)[portNum];
    if (value < param[0] && PRMVALID(valid)) {
      this->voltageStatus[portNum] = EPSStatus::UNDERVOLT;
      this->tlmWrite_voltageStatus(this->voltageStatus);
    }else if (value > param[1] && PRMVALID(valid)) {
      this->voltageStatus[portNum] = EPSStatus::OVERVOLT;
      this->tlmWrite_voltageStatus(this->voltageStatus);
    }

    this->tlmWrite_voltage(this->voltage);
  }

} // end namespace CHASE
