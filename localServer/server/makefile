CXX = g++
CXXFLAGS = -Wall
SRCS = socket.cpp serverSocket.cpp mainServer.cpp
OBJS = ${SRCS:.cpp=.o}

all: windows

windows: $(OBJS) socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o mainServer.exe

linux: $(OBJS) socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o mainServer.exe
	chmod +x mainServer.exe

socket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

serverSocket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

mainServer: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe *.out