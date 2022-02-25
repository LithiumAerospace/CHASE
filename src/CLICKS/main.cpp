#include "Server.h"

int main(int argc, char const *argv[]) {
	CHASE::CLICKS::Server server = CHASE::CLICKS::Server();
	server.run();

	return 0;
}
