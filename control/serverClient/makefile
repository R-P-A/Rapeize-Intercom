CXX = g++
CXXFLAGS = -Wall
SRCS = socket.cpp clientSocket.cpp testClient.cpp
OBJS = ${SRCS:.cpp=.o}

all: windows

windows: $(OBJS) socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o testClient.exe

linux: $(OBJS) socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o testClient.exe
	chmod +x testClient.exe

socket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

clientSocket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

testClient: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe *.out