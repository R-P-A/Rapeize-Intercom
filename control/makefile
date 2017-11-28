CXX = g++
CXXFLAGS = -Wall -pthread
SRCS = centralControl.cpp dateTime.cpp model.cpp myio.cpp sortedList.cpp user.cpp socket.cpp serverSocket.cpp control.cpp
OBJS = ${SRCS:.cpp=.o}

all: windows

windows: $(OBJS) $(OBJS) node.h socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o main.exe

linux: $(OBJS) $(OBJS) node.h socketException.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o main.exe
	chmod +x main.exe

centralControl: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

dateTime: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

model: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

myio: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

sortedList: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

user: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

socket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

serverSocket: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

control: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe *.out