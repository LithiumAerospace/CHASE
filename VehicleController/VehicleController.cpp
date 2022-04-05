// ======================================================================
// \title  VehicleController.cpp
// \author codeflight
// \brief  cpp file for VehicleController component implementation class
// ======================================================================


#include <VehicleController/VehicleController.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace CHASE {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  VehicleController ::
    VehicleController(
        const char *const compName
    ) : VehicleControllerComponentBase(compName)
  {

  }

  void VehicleController ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    VehicleControllerComponentBase::init(queueDepth, instance);
  }

  VehicleController ::
    ~VehicleController()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  CHASE::FlightState VehicleController ::
    getState_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    return this->state;
  }

  void VehicleController ::
    run_handler(
        const NATIVE_INT_TYPE portNum,
        Svc::TimerVal &cycleStart
    )
  {
    // TODO
  }

  void VehicleController ::
    setState_handler(
        const NATIVE_INT_TYPE portNum,
        const CHASE::FlightState &state
    )
  {
    this->state = state;

    this->tlmWrite_state(this->state);
    this->log_ACTIVITY_HI_StateChanged(this->state);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void VehicleController ::
    SET_STATE_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        CHASE::FlightState state
    )
  {
    this->setState_handler(0, state);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace CHASE
