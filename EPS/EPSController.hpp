// ======================================================================
// \title  EPSController.hpp
// \author codeflight
// \brief  hpp file for EPSController component implementation class
// ======================================================================

#ifndef EPSController_HPP
#define EPSController_HPP

#include <EPS/EPSControllerComponentAc.hpp>
#include <EPS/EPSItemArrayArrayAc.hpp>
#include <EPS/EPSItemConfigArrayArrayAc.hpp>
#include <util/FppConstantsAc.hpp>

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
          const NATIVE_INT_TYPE instance = 0, /*!< The instance number*/
          EPSItemConfigArray config = EPSItemConfigArray()
      );

      //! Destroy object EPSController
      //!
      ~EPSController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for data
      //!
      void data_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 itemId,
          const EPSValueType& type,
          F32 value
      );

      //! Handler implementation for run
      //!
      void run_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!< Cycle start timer value*/
      );

      //! Handler implementation for switchSet
      //!
      void switchSet_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 switchId,
          const Fw::Enabled &enabled
      );

      EPSItemArray items;
      EPSItemConfigArray config;

    };

} // end namespace CHASE

#endif
