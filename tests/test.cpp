#include "../src/Loop.h"

#include <iostream>
#include <vector>

class TestLoop : public CHASE::Loop {
  public:
    TestLoop() : Loop() {
      CHASE::LoopConf conf = {"test", 10, 10};

      this->init(conf);
    }

    ~TestLoop() {

    }

    void update(float dt, std::vector<CHASE::CLICKS::Message*> msgs) {
      for (CHASE::CLICKS::Message* msg : msgs) {
        std::cout << *msg << std::endl;
      }
      std::cout << '\r' << dt << std::flush;
    }

    CHASE::CLICKS::Message* syncRqst() {
      CHASE::CLICKS::Message* msg = new CHASE::CLICKS::Message;
      msg->type = CHASE::CLICKS::MsgType::SYNC_RQST;

      return msg;
    }

    void syncRtrn(CHASE::CLICKS::Message* msg) {
      std::cout << *msg << std::endl;
    }
};

int main(int argv, char* argc[]) {
  TestLoop* loop = new TestLoop();
  loop->run();

  delete loop;
  return 0;
}
