// ======================================================================
// \title  EPSController.cpp
// \author codeflight
// \brief  cpp file for EPSController component implementation class
// ======================================================================


#include <CHASE/EPS/EPSController.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <CHASE/EPS/EPSItemStatusEnumAc.hpp>

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
        const NATIVE_INT_TYPE instance,
        EPSItemConfigArray config
    )
  {
    EPSControllerComponentBase::init(queueDepth, instance);

    this->config = config;
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
    for (NATIVE_INT_TYPE i = 0; i < NumEPSItems; i++) {
      this->request_out(i);
    }
  }

  void EPSController ::
    switchSet_handler(
        const NATIVE_INT_TYPE portNum,
        U8 itemId,
        const Fw::Enabled &enabled
    )
  {
    this->items[itemId].setswitchState(enabled);

    this->switchMsg_out(0, itemId, enabled);

    this->tlmWrite_itemStatus(this->items);
  }

  void EPSController ::
    data_handler(
        const NATIVE_INT_TYPE portNum,
        U8 itemId,
        const EPSValueType& itemType,
        F32 value
    )
  {
    if (itemType == EPSValueType::VOLTAGE) {
      this->items[itemId].setvoltage(value);

      if (value < this->config[itemId].getundervolterror()) {
        this->items[itemId].setstatus(EPSItemStatus::UNDERVOLTERROR);
      }else if (value < this->config[itemId].getundervoltwarn()) {
        this->items[itemId].setstatus(EPSItemStatus::UNDERVOLTWARN);
      }else if (value > this->config[itemId].getovervolterror()) {
        this->items[itemId].setstatus(EPSItemStatus::OVERVOLTERROR);
      }else if (value > this->config[itemId].getovervoltwarn()) {
        this->items[itemId].setstatus(EPSItemStatus::OVERVOLTWARN);
      }
    }else if (itemType == EPSValueType::CURRENT) {
      this->items[itemId].setcurrent(value);

      if (value > this->config[itemId].getovercurrenterror()) {
        this->items[itemId].setstatus(EPSItemStatus::OVERCURRENTERROR);
      }else if (value > this->config[itemId].getovercurrentwarn()) {
        this->items[itemId].setstatus(EPSItemStatus::OVERCURRENTWARN);
      }
    }

    this->tlmWrite_itemStatus(this->items);
  }

} // end namespace CHASE
