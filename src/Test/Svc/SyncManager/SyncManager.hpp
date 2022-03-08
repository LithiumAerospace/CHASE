// ======================================================================
// \title  SyncManager.hpp
// \author codeflight
// \brief  hpp file for SyncManager component implementation class
//
// ======================================================================

#ifndef SyncManager_HPP
#define SyncManager_HPP

#include "Svc/SyncManager/SyncManagerComponentAc.hpp"

namespace Svc {

  class SyncManager :
    public SyncManagerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SyncManager
      //!
      SyncManager(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object SyncManager
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object SyncManager
      //!
      ~SyncManager();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for externalIn
      //!
      void externalIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer
      );

      //! Handler implementation for pingIn
      //!
      void pingIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 key /*!<
      Value to return to pinger
      */
      );

      //! Handler implementation for run
      //!
      void run_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::TimerVal &cycleStart /*!<
      Cycle start timer value
      */
      );

      //! Handler implementation for syncIn
      //!
      void syncIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer
      );


    };

} // end namespace Svc

#endif
