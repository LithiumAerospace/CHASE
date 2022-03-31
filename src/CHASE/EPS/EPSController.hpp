// ======================================================================
// \title  EPSController.hpp
// \author nate
// \brief  hpp file for EPSController component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef EPSController_HPP
#define EPSController_HPP

#include "CHASE/EPS/EPSControllerComponentAc.hpp"

#include <CHASE/EPS/FppConstantsAc.hpp>

namespace CHASE {

  class EPSController :
    public EPSControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object EPSController
      //!
      EPSController(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object EPSController
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object EPSController
      //!
      ~EPSController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for current
      //!
      void current_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 value
      );

      //! Handler implementation for run
      //!
      void run_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!<
      Cycle start timer value
      */
      );

      //! Handler implementation for switchSet
      //!
      void switchSet_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 switchId,
          const Fw::Enabled &enabled
      );

      //! Handler implementation for voltage
      //!
      void voltage_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 value
      );

      EPSSwitchStateArray switchState;

      EPSVoltageStatusArray voltageStatus;
      EPSVoltageArray       voltage;

      EPSCurrentStatusArray currentStatus;
      EPSCurrentArray       current;

    };

} // end namespace CHASE

#endif
