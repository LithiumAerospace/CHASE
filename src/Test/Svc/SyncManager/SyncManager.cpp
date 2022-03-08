// ======================================================================
// \title  SyncManager.cpp
// \author codeflight
// \brief  cpp file for SyncManager component implementation class
//
// ======================================================================


#include <Svc/SyncManager/SyncManager.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SyncManager ::
    SyncManager(
        const char *const compName
    ) : SyncManagerComponentBase(compName)
  {

  }

  void SyncManager ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    SyncManagerComponentBase::init(queueDepth, instance);
  }

  SyncManager ::
    ~SyncManager()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SyncManager ::
    externalIn_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    // TODO
  }

  void SyncManager ::
    pingIn_handler(
        const NATIVE_INT_TYPE portNum,
        U32 key
    )
  {
    this->pingOut_out(0,key);
  }

  void SyncManager ::
    run_handler(
        const NATIVE_INT_TYPE portNum,
        Svc::TimerVal &cycleStart
    )
  {
    // TODO
  }

  void SyncManager ::
    syncIn_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    // TODO
  }

} // end namespace Svc
