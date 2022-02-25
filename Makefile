SRCS = \
	src/Loop.cpp \
	src/CLICKS/Client.cpp \
	src/CLICKS/Server.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -g

%.o: %.cpp
	g++ ${CFLAGS} -c $< -o $@

test: ${OBJS}
	g++ ${CFLAGS} -c tests/test.cpp -o tests/test.o
	g++ ${CFLAGS} ${OBJS} tests/test.o -o tests/test

CLICKS: ${OBJS}
	g++ ${CFLAGS} -c src/CLICKS/main.cpp -o src/CLICKS/main.o
	g++ ${CFLAGS} ${OBJS} src/CLICKS/main.o -o src/CLICKS/CLICKS

clean:
	@rm -v ${OBJS}
