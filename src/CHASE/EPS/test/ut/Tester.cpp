// ======================================================================
// \title  EPSController.hpp
// \author nate
// \brief  cpp file for EPSController test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10
#define QUEUE_DEPTH 10

namespace CHASE {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
#if FW_OBJECT_NAMES == 1
      EPSControllerGTestBase("Tester", MAX_HISTORY_SIZE),
      component("EPSController")
#else
      EPSControllerGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void Tester ::
    undervoltTest()
  {
    F32 value = 10;

    EPSVoltageConf conf;
    conf[0][0] = value + 1;

    this->clearHistory();

    this->paramSet_voltageConf(conf, Fw::ParamValid::VALID);
    this->paramSend_voltageConf(0, 1);

    this->invoke_to_voltage(0, value);
    this->component.doDispatch();

    EPSVoltageStatusArray stat;
    stat[0] = EPSStatus::UNDERVOLT;

    EPSVoltageArray expected;
    expected[0] = value;

    ASSERT_TLM_SIZE(2);
    ASSERT_TLM_voltage(0, expected);
    ASSERT_TLM_voltageStatus(0, stat);
  }

  void Tester ::
    overvoltTest()
  {
    F32 value = 10;

    EPSVoltageConf conf;
    conf[0][1] = value - 1;

    this->clearHistory();

    this->paramSet_voltageConf(conf, Fw::ParamValid::VALID);
    this->paramSend_voltageConf(0, 1);

    this->invoke_to_voltage(0, value);
    this->component.doDispatch();

    EPSVoltageStatusArray stat;
    stat[0] = EPSStatus::OVERVOLT;

    EPSVoltageArray expected;
    expected[0] = value;

    ASSERT_TLM_SIZE(2);
    ASSERT_TLM_voltage(0, expected);
    ASSERT_TLM_voltageStatus(0, stat);
  }

  void Tester ::
    overcurrentTest()
  {
    F32 value = 10;

    EPSCurrentConf conf;
    conf[0] = value - 1;

    this->clearHistory();

    this->paramSet_currentConf(conf, Fw::ParamValid::VALID);
    this->paramSend_currentConf(0, 1);

    this->invoke_to_current(0, value);
    this->component.doDispatch();

    EPSCurrentStatusArray stat;
    stat[0] = EPSStatus::OVERCURRENT;

    EPSCurrentArray expected;
    expected[0] = value;

    ASSERT_TLM_SIZE(2);
    ASSERT_TLM_current(0, expected);
    ASSERT_TLM_currentStatus(0, stat);
  }

  void Tester ::
    switchTest()
  {
    this->invoke_to_switchSet(0, 0, Fw::Enabled::ENABLED);
    this->component.doDispatch();

    ASSERT_from_switchMsg(0, Fw::Enabled(Fw::Enabled::ENABLED));
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_currentRequest_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->pushFromPortEntry_currentRequest();
  }

  void Tester ::
    from_switchMsg_handler(
        const NATIVE_INT_TYPE portNum,
        const Fw::Enabled &enabled
    )
  {
    this->pushFromPortEntry_switchMsg(enabled);
  }

  void Tester ::
    from_voltageRequest_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->pushFromPortEntry_voltageRequest();
  }

  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts()
  {

    // cmdIn
    this->connect_to_cmdIn(
        0,
        this->component.get_cmdIn_InputPort(0)
    );

    // current
    for (NATIVE_INT_TYPE i = 0; i < 2; ++i) {
      this->connect_to_current(
          i,
          this->component.get_current_InputPort(i)
      );
    }

    // run
    this->connect_to_run(
        0,
        this->component.get_run_InputPort(0)
    );

    // switchSet
    for (NATIVE_INT_TYPE i = 0; i < 8; ++i) {
      this->connect_to_switchSet(
          i,
          this->component.get_switchSet_InputPort(i)
      );
    }

    // voltage
    for (NATIVE_INT_TYPE i = 0; i < 2; ++i) {
      this->connect_to_voltage(
          i,
          this->component.get_voltage_InputPort(i)
      );
    }

    // cmdRegOut
    this->component.set_cmdRegOut_OutputPort(
        0,
        this->get_from_cmdRegOut(0)
    );

    // cmdResponseOut
    this->component.set_cmdResponseOut_OutputPort(
        0,
        this->get_from_cmdResponseOut(0)
    );

    // currentRequest
    for (NATIVE_INT_TYPE i = 0; i < 2; ++i) {
      this->component.set_currentRequest_OutputPort(
          i,
          this->get_from_currentRequest(i)
      );
    }

    // prmGetOut
    this->component.set_prmGetOut_OutputPort(
        0,
        this->get_from_prmGetOut(0)
    );

    // prmSetOut
    this->component.set_prmSetOut_OutputPort(
        0,
        this->get_from_prmSetOut(0)
    );

    // switchMsg
    for (NATIVE_INT_TYPE i = 0; i < 2; ++i) {
      this->component.set_switchMsg_OutputPort(
          i,
          this->get_from_switchMsg(i)
      );
    }

    // timeGetOut
    this->component.set_timeGetOut_OutputPort(
        0,
        this->get_from_timeGetOut(0)
    );

    // tlmOut
    this->component.set_tlmOut_OutputPort(
        0,
        this->get_from_tlmOut(0)
    );

    // voltageRequest
    for (NATIVE_INT_TYPE i = 0; i < 2; ++i) {
      this->component.set_voltageRequest_OutputPort(
          i,
          this->get_from_voltageRequest(i)
      );
    }




  }

  void Tester ::
    initComponents()
  {
    this->init();
    this->component.init(
        QUEUE_DEPTH, INSTANCE
    );
  }

} // end namespace CHASE
