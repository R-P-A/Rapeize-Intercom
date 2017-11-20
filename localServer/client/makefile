CXX = g++
CXXFLAGS = -Wall
SRCS = socket.cpp clientSocket.cpp mainClient.cpp
OBJS = ${SRCS:.cpp=.o}

all: windows

windows: $(OBJS) socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o mainClient.exe

linux: $(OBJS) socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o mainClient.exe
	chmod +x mainClient.exe

socket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

clientSocket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

mainClient: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe *.out