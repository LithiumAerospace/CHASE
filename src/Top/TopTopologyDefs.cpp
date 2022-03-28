#include "Top/TopTopologyDefs.hpp"

namespace Test {

  namespace Allocation {

    Fw::MallocAllocator mallocator;

  }

  Svc::LinuxTimer linuxTimer(FW_OPTIONAL_NAME("linuxTimer"));

}
