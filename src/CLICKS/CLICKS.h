#ifndef CLICKS_H
#define CLICKS_H

#include <ostream>

#include <stdint.h>

// Coordinative Logistics Infrastructure and Communicative Kernel for Spacecraft

#define SOCK_PATH "/home/nate/clicks.sock"

namespace CHASE {
	namespace CLICKS {
		enum MsgType: uint8_t {
			VEHICLE = 0,
			INTERNAL = 1,
			SYNC_RQST = 2,
			SYNC_RTRN = 3,
			INIT = 8
		};

		struct Message {
			char src[16];
			char dst[16];
			MsgType type;

			uint16_t datalen;
			void* data = NULL;
		};

		inline std::ostream& operator<<(std::ostream& os, const Message& msg) {
			os << "{Message: " << msg.src << "->" << msg.dst << ", " << msg.type << "}";

			return os;
		};
	};
};

#endif // CLICKS_H
