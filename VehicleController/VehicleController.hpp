// ======================================================================
// \title  VehicleController.hpp
// \author codeflight
// \brief  hpp file for VehicleController component implementation class
// ======================================================================

#ifndef VehicleController_HPP
#define VehicleController_HPP

#include "VehicleController/VehicleControllerComponentAc.hpp"

#include <util/FlightStateEnumAc.hpp>

namespace CHASE {

  class VehicleController :
    public VehicleControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object VehicleController
      //!
      VehicleController(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object VehicleController
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object VehicleController
      //!
      ~VehicleController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for getState
      //!
      CHASE::FlightState getState_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for run
      //!
      void run_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!<
      Cycle start timer value
      */
      );

      //! Handler implementation for setState
      //!
      void setState_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const CHASE::FlightState &state
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SET_STATE command handler
      //!
      void SET_STATE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          CHASE::FlightState state
      );

      FlightState state;

    };

} // end namespace CHASE

#endif
