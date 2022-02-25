#ifndef BUS_CLIENT
#define BUS_CLIENT

#include <vector>

#include "CLICKS.h"

namespace CHASE {
  namespace CLICKS {
    class Client {
      public:
        Client(char name[16]);
        ~Client();

        std::vector<Message*> gather();
        void                  sendMsg(Message*);

      private:
        unsigned int s;

        char m_name[16];
    };
  };
};

#endif // BUS_CLIENT
