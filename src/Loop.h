#ifndef CHASE_BASE
#define CHASE_BASE

#include <vector>

#include "CLICKS/CLICKS.h"
#include "CLICKS/Client.h"

#include "util/Log.h"

namespace CHASE {
  struct LoopConf {
    char name[16];
    int  freq;
    int  syncFreq;
  };

  class Loop {
    public:
      Loop();

      void init(LoopConf conf);

      void run();

    protected:
      virtual void update(float dt, std::vector<CLICKS::Message*> msgs) {};

      virtual CLICKS::Message* syncRqst() {return 0;};
      virtual void             syncRtrn(CLICKS::Message* update) {};

      CLICKS::Client* m_busConn;

    private:
      LoopConf m_conf;

      bool m_ready;
      bool m_running;

      logger log;
  };
};

#endif // CHASE_BASE
