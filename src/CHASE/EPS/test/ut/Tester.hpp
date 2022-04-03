// ======================================================================
// \title  EPSController/test/ut/Tester.hpp
// \author codeflight
// \brief  hpp file for EPSController test harness implementation class
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "CHASE/EPS/EPSController.hpp"

#include <CHASE/EPS/EPSItemConfigArrayArrayAc.hpp>

namespace CHASE {

  class Tester :
    public EPSControllerGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester();

      //! Destroy object Tester
      //!
      ~Tester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      //!
      void switchTest();

      void undervoltTest();
      void overvoltTest();
      void overcurrentTest();

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_currentRequest
      //!
      void from_request_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler for from_switchMsg
      //!
      void from_switchMsg_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 itemId,
          const Fw::Enabled &enabled
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      EPSController component;

  };

} // end namespace CHASE

#endif
