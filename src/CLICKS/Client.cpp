#include "Client.h"

#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <stdint.h>

#include "../util/Log.h"

namespace CHASE {
  namespace CLICKS {
    Client::Client(char name[16]) :
        log(logger(std::cout, "CLICKS Client")){
      strcpy(m_name, name);

      struct sockaddr_un remote;

      if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        log(LOG_ERROR) << "socket error: " << strerror(errno) << '\n';
        exit(1);
      }

      remote.sun_family = AF_UNIX;
      strcpy(remote.sun_path, SOCK_PATH);
      if (connect(s, (struct sockaddr *)&remote, strlen(remote.sun_path) + sizeof(remote.sun_family)) == -1) {
        log(LOG_ERROR) << "connect error: " << strerror(errno) << '\n';
        exit(1);
      }

      log(LOG_INFO) << "Connected\n";

      Message msg;
      msg.type = MsgType::INIT;
      msg.data = m_name;
      strcpy(msg.dst, "000000000000000");
      msg.datalen = strlen(name) + 1;

      sendMsg(&msg);
    }

    Client::~Client() {
      log(LOG_DEBUG) << "Client::~Client()\n";
      close(s);
    }

    std::vector<Message*> Client::gather() {
      std::vector<Message*> v;

      return v;
    }

    void Client::sendMsg(Message *msg) {
      void* buf = malloc(35 + msg->datalen);

      memcpy(buf, m_name, 16);
      memcpy(buf + 16, &msg->dst,     16);
      memcpy(buf + 32, &msg->type,    1);
      memcpy(buf + 33, &msg->datalen, 2);
      memcpy(buf + 35, msg->data, msg->datalen);

      if(send(s, buf, 35+msg->datalen, 0) == -1) {
        free(buf);
        log(LOG_ERROR) << "send error: " << strerror(errno) << '\n';
        exit(1);
      }

      free(buf);
    }
  }
}
