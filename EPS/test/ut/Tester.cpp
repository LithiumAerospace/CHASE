// ======================================================================
// \title  EPSController.hpp
// \author codeflight
// \brief  cpp file for EPSController test harness implementation class
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
    this->clearHistory();

    this->invoke_to_data(0, 0, EPSValueType::VOLTAGE, 8.5);
    this->component.doDispatch();
    this->invoke_to_data(0, 0, EPSValueType::VOLTAGE, 7.5);
    this->component.doDispatch();

    ASSERT_TLM_SIZE(2);

    ASSERT_EQ(this->tlmHistory_itemStatus->at(0).arg[0].getstatus(), EPSItemStatus::UNDERVOLTWARN);
    ASSERT_EQ(this->tlmHistory_itemStatus->at(1).arg[0].getstatus(), EPSItemStatus::UNDERVOLTERROR);
  }

  void Tester ::
    overvoltTest()
  {
    this->clearHistory();

    this->invoke_to_data(0, 0, EPSValueType::VOLTAGE, 11.5);
    this->component.doDispatch();
    this->invoke_to_data(0, 0, EPSValueType::VOLTAGE, 12.5);
    this->component.doDispatch();

    ASSERT_TLM_SIZE(2);

    ASSERT_EQ(this->tlmHistory_itemStatus->at(0).arg[0].getstatus(), EPSItemStatus::OVERVOLTWARN);
    ASSERT_EQ(this->tlmHistory_itemStatus->at(1).arg[0].getstatus(), EPSItemStatus::OVERVOLTERROR);
  }

  void Tester ::
    overcurrentTest()
  {
    this->clearHistory();

    this->invoke_to_data(0, 0, EPSValueType::CURRENT, 11.5);
    this->component.doDispatch();
    this->invoke_to_data(0, 0, EPSValueType::CURRENT, 12.5);
    this->component.doDispatch();

    ASSERT_TLM_SIZE(2);

    ASSERT_EQ(this->tlmHistory_itemStatus->at(0).arg[0].getstatus(), EPSItemStatus::OVERCURRENTWARN);
    ASSERT_EQ(this->tlmHistory_itemStatus->at(1).arg[0].getstatus(), EPSItemStatus::OVERCURRENTERROR);
  }

  void Tester ::
    switchTest()
  {
    this->invoke_to_switchSet(0, 0, Fw::Enabled::ENABLED);
    this->component.doDispatch();

    ASSERT_from_switchMsg(0, 0, Fw::Enabled(Fw::Enabled::ENABLED));
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------
  void Tester ::
    from_request_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    this->pushFromPortEntry_request();
  }

  void Tester ::
    from_switchMsg_handler(
        const NATIVE_INT_TYPE portNum,
        U8 itemId,
        const Fw::Enabled &enabled
    )
  {
    this->pushFromPortEntry_switchMsg(itemId, enabled);
  }

  void Tester ::
    from_status_handler(
        const NATIVE_INT_TYPE portNum,
        const SubsystemStatus& status
    )
  {
    this->pushFromPortEntry_status(status);
  }

  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts()
  {
    // data
    this->connect_to_data(
        0,
        this->component.get_data_InputPort(0)
    );

    // run
    this->connect_to_run(
        0,
        this->component.get_run_InputPort(0)
    );

    // switchSet
    this->connect_to_switchSet(
        0,
        this->component.get_switchSet_InputPort(0)
    );

    // request
    for (NATIVE_INT_TYPE i = 0; i < 8; ++i) {
      this->component.set_request_OutputPort(
          i,
          this->get_from_request(i)
      );
    }

    // switchMsg
    for (NATIVE_INT_TYPE i = 0; i < 8; ++i) {
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




  }

  void Tester ::
    initComponents()
  {
    this->init();

    CHASE::EPSItemConfigArray config;

    CHASE::EPSItemConfig item;
    item.setundervolterror(8);
    item.setundervoltwarn(9);
    item.setovervoltwarn(11);
    item.setovervolterror(12);
    item.setovercurrentwarn(11);
    item.setovercurrenterror(12);

    config[0] = item;

    this->component.init(
        QUEUE_DEPTH, INSTANCE, config
    );
  }

} // end namespace CHASE
