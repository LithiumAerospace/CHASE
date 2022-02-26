#ifndef CLICKS_SERVER
#define CLICKS_SERVER

#include "CLICKS.h"

#include <sys/un.h>
#include <sys/socket.h>

#include "../util/Log.h"

namespace CHASE {
	namespace CLICKS {
		class Server {
			public:
				Server();

				void run();

			private:
				struct client {
					int fd;
					char name[16];
					bool ready = false;
				};

				client clients[8];

				int master_socket, new_socket, max_clients = 8, activity, valread, sd, max_sd;
			  struct sockaddr_un address;

			  char buffer[1025];

				fd_set readfds;

				logger log;

				void newConn();
				void onMessage(char* headbuf);
				void disconnect();
		};
	};
};

#endif
