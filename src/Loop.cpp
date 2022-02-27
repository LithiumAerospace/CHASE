#include "Loop.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "CLICKS/Client.h"

namespace CHASE {
  Loop::Loop() :
      log(logger(std::cout, "Main Loop")){
    m_ready = false;
    m_running = false;
  }

  void Loop::init(LoopConf conf) {
    m_conf = conf;

    log(LOG_INFO) << "Loop Initialization:" << '\n';
    log(LOG_INFO) << "  Name:      " << this->m_conf.name     << '\n';
    log(LOG_INFO) << "  Iter/Sync: " << this->m_conf.syncFreq << '\n';
    log(LOG_INFO) << "  Frequency: " << this->m_conf.freq     << " hz" << '\n';

    m_busConn  = new CLICKS::Client(m_conf.name);

    m_ready = true;
  }

  void Loop::run() {
    if (m_ready == false) {
      log(LOG_ERROR) << "FATAL ERROR, not initialized" << '\n';
      return;
    }

    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> next;
    std::chrono::time_point<std::chrono::steady_clock> end;
    std::chrono::milliseconds tick (1000/m_conf.freq);
    float dt = 0.0f;

    m_running = true;

    while (m_running) {
      /* ******** TIMING ******** */
      next = start+tick;
      std::this_thread::sleep_until(next);
      end = std::chrono::steady_clock::now();

      dt = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.f;
      start = std::chrono::steady_clock::now();

      /* ******** LOGIC ******** */
      std::vector<CLICKS::Message*> messages = m_busConn->gather();
      std::vector<CLICKS::Message*> out;

      for (CLICKS::Message* msg : messages) {
        switch (msg->type) {
          case CLICKS::MsgType::VEHICLE:
          case CLICKS::MsgType::INTERNAL:
            out.push_back(msg);
            break;

          case CLICKS::MsgType::SYNC_RQST:
            {
              CLICKS::Message* rtrn = this->syncRqst();

              m_busConn->sendMsg(rtrn);
            }
            break;

          case CLICKS::MsgType::SYNC_RTRN:
            this->syncRtrn(msg);
            break;
        }
      }

      this->update(dt, out);
    }
  }
}
