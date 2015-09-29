LIBS_PATH = -I/usr/include/eigen3
COMM_PATH = ./comm/
XPLANE_PATH = ./XPlane/

CXX = g++
CXXFLAGS=-std=c++11 -Wall -Wextra -O2 -ggdb3 $(LIBS_PATH)

OBJECTS_UAVITL = $(COMM_PATH)udp_client_server.o \
				 $(XPLANE_PATH)XPdata.o \
				 $(XPLANE_PATH)XPposition.o \
				 $(XPLANE_PATH)XPattitude.o \
				 sim.o \
				 flyingmachine.o \
				 guidance.o \
				 navigation.o \
				 control.o \
				 gnc.o \
				 sensors.o \
				 uavitl.o

all: uavitl

uavitl: $(OBJECTS_UAVITL)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_PATH)

clean:
	$(RM) *~ *.o *.swp uavitl \
		$(COMM_PATH)*~  $(COMM_PATH)*.o $(COMM_PATH)*.swp  \
		$(XPLANE_PATH)*~  $(XPLANE_PATH)*.o $(XPLANE_PATH)*.swp

.PHONY: clean
