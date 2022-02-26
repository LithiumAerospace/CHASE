#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

#include <iostream>

namespace CHASE {
	namespace CLICKS {
		Server::Server() :
				log(logger(std::cout, "CLICKS Server")){
			for (int i = 0; i < max_clients; i++)
		  {
		    clients[i] = {0, 0, false};
		  }

		  if((master_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == 0)
		  {
		    perror("socket failed");
		    exit(EXIT_FAILURE);
		  }

		  address.sun_family = AF_UNIX;
		  strcpy(address.sun_path, SOCK_PATH);
		  unlink(address.sun_path);

		  if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
		  {
		    perror("bind failed");
		    exit(EXIT_FAILURE);
		  }

		  log(LOG_INFO) << "Listening at " << SOCK_PATH << '\n';

		  if (listen(master_socket, 8) < 0)
		  {
		    perror("listen");
		    exit(EXIT_FAILURE);
		  }
		}

		void Server::run() {
		  while(true)
		  {
		    FD_ZERO(&readfds);

		    FD_SET(master_socket, &readfds);
		    max_sd = master_socket;

		    for (int i = 0; i < max_clients; i++)
		    {
		      sd = clients[i].fd;
		      if(sd > 0)
		          FD_SET(sd, &readfds);

		      if(sd > max_sd)
		          max_sd = sd;
		    }

		    activity = select(max_sd + 1, &readfds , NULL , NULL , NULL);

		    if ((activity < 0) && (errno!=EINTR))
		    {
		      printf("select error");
		    }

		    if (FD_ISSET(master_socket, &readfds))
		    {
					newConn();
		    }

		    for (int i = 0; i < max_clients; i++) {
		      sd = clients[i].fd;

		      if (FD_ISSET( sd , &readfds)) {
						char* headbuf;

						valread = read(sd , headbuf, 35);
		        if (valread == 0 || (valread == -1 && (errno == 104 || errno == 14))) { // Reset by peer
		          disconnect();
		        } else if (valread == -1) {
							perror("read");
						} else {
		          onMessage(headbuf);
		        }
		      }
		    }
		  }
		}

		void Server::newConn() {
		  int addrlen = sizeof(address);

			if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
				perror("accept");
				exit(EXIT_FAILURE);
			}

			//inform user of socket number - used in send and receive commands
			log(LOG_INFO) << "New connection, socket fd is " << new_socket << '\n';

			//add new socket to array of sockets
			for (int i = 0; i < max_clients; i++) {
				//if position is empty
				if (clients[i].fd == 0) {
					clients[i].fd = new_socket;
					log(LOG_INFO) << "Adding to list of sockets as " << i << '\n';
					break;
				}
			}
		}

		void Server::onMessage(char* headbuf) {
			Message msg;

			memcpy(&msg.src,     headbuf,       16);
      memcpy(&msg.dst,     headbuf + 16,  16);
      memcpy(&msg.type,    headbuf + 32,   1);
      memcpy(&msg.datalen, headbuf + 33,   2);

			msg.data = malloc(msg.datalen);

			int valread = read(sd , msg.data, msg.datalen);
			if (valread == 0 || (valread == -1 && errno == 104)) { // Reset by peer
				disconnect();
				return;
			} else if (valread == -1) {
				perror("read");
				return;
			}

			switch (msg.type) {
				case INIT:
					for (int i = 0; i < max_clients; i++) {
						if(clients[i].fd == sd) {
							memcpy(clients[i].name, msg.data, 16);
							clients[i].ready = true;
							log(LOG_INFO) << "Client " << clients[i].name << "fd " << clients[i].fd << ", state " << clients[i].ready << '\n';
							break;
						}
					}
					break;
				default:
					send(sd , buffer , 40, 0 ); // FIX
					break;
			}
		}

		void Server::disconnect() {
			log(LOG_INFO) << "Host disconnected, socket fd is " << sd << '\n';

			close(sd);
			for (int i = 0; i < max_clients; i++) {
				if(clients[i].fd == sd) {
					clients[i] = {0, 0, false};
					break;
				}
			}
		}
	}
}
