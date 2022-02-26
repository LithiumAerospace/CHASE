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

namespace CHASE {
  namespace CLICKS {
    Client::Client(char name[16]) {
    //  m_name = name;
      std::cout << "Client, Name: " << m_name << std::endl;

      struct sockaddr_un remote;

      if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
      }

      printf("Trying to connect...\n");

      remote.sun_family = AF_UNIX;
      strcpy(remote.sun_path, SOCK_PATH);
      if (connect(s, (struct sockaddr *)&remote, strlen(remote.sun_path) + sizeof(remote.sun_family)) == -1) {
        perror("connect");
        exit(1);
      }

      printf("Connected.\n");

      Message msg;
      msg.type = MsgType::INIT;
      msg.data = m_name;
      strcpy(msg.dst, "000000000000000");
      msg.datalen = strlen(name) + 1;

      sendMsg(&msg);
    }

    Client::~Client() {
      close(s);
    }

    std::vector<Message*> Client::gather() {
      std::vector<Message*> v;

      return v;
    }

    void Client::sendMsg(Message *msg) {
      std::cout << "Sending... " << *msg << std::endl;
      void* buf = malloc(35 + msg->datalen);

      memcpy(buf, m_name, 16);
      memcpy(buf + 16, &msg->dst,     16);
      memcpy(buf + 32, &msg->type,    1);
      memcpy(buf + 33, &msg->datalen, 2);
      memcpy(buf + 35, msg->data, msg->datalen);

      if(send(s, buf, 35+msg->datalen, 0) == -1) {
        free(buf);
        perror("send");
        exit(1);
      }

      free(buf);
    }
  }
}
