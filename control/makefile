CXX = g++
CXXFLAGS = -Wall
SRCS = myString.cpp readInput.cpp model.cpp student.cpp sortedList.cpp menu.cpp calendar.cpp clock.cpp clockCalendar.cpp timer.cpp main.cpp
OBJS = ${SRCS:.cpp=.o}

all: linux

linux: $(OBJS) node.h
	$(CXX) $(CXXFLAGS) $(OBJS) -o main.exe
	chmod +x main.exe

leon: $(SRCS) node.h
	sparc-gaisler-elf-g++ $(CXXFLAGS) -std=c++11 $(SRCS) -o main

myString: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

readInput: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

model: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

student: $@.cpp $@.h model.o
	$(CXX) $(CXXFLAGS) $@.cpp -c

sortedList: $@.cpp $@.h node.h model.o
	$(CXX) $(CXXFLAGS) $@.cpp -c

menu: $@.cpp $@.h sortedList.o student.o readInput.o
	$(CXX) $(CXXFLAGS) $@.cpp -c

calendar: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

clock: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

clockCalendar: $@.cpp $@.h model.o
	$(CXX) $(CXXFLAGS) $@.cpp -c

timer: $@.cpp $@.h
	$(CXX) $(CXXFLAGS) $@.cpp -c

main: $@.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $@.cpp -c

clean:
	rm -rf *.o *.exe main