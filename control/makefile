CXX = g++
CXXFLAGS = -Wall
SRCS = centralControl.cpp dateTime.cpp model.cpp myio.cpp sortedList.cpp user.cpp socket.cpp serverSocket.cpp main.cpp
OBJS = ${SRCS:.cpp=.o}

all: windows

windows: $(OBJS) node.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o main.exe

linux: $(OBJS) node.h
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

main: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe *.out