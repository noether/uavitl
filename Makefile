LIBS_PATH = -I/usr/include/eigen3

CXX = g++
CXXFLAGS=-std=c++11 -Wall -Wextra -O2 -ggdb3 $(LIBS_PATH)

OBJECTS_UAVITL = sim.o \
				 flyingmachine.o \
				 guidance.o \
				 navigation.o \
				 control.o \
				 gnc.o \
				 uavitl.o

all: uavitl

uavitl: $(OBJECTS_UAVITL)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_PATH)

clean:
	$(RM) *~ *.o *.swp uavitl

.PHONY: clean
