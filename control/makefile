CXX = g++
CXXFLAGS = -Wall
SRCS = controlInterface.cpp dateTime.cpp model.cpp myio.cpp sortedList.cpp user.cpp testControlInterface.cpp
OBJS = ${SRCS:.cpp=.o}

all: windows

windows: $(OBJS) node.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o main.exe

linux: $(OBJS) node.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o main.exe
	chmod +x main.exe

controlInterface: $@.cpp $@.h
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

testControlInterface: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe *.out main