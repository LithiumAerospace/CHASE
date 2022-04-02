// ======================================================================
// \title  EPSController/test/ut/Tester.hpp
// \author nate
// \brief  hpp file for EPSController test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "CHASE/EPS/EPSController.hpp"

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
      void from_currentRequest_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler for from_switchMsg
      //!
      void from_switchMsg_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const Fw::Enabled &enabled
      );

      //! Handler for from_voltageRequest
      //!
      void from_voltageRequest_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
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
