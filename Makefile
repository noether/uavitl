LIBS_PATH = -I/usr/include/eigen3
COMM_PATH = ./comm/
XPLANE_PATH = ./XPlane/
ENVIRONMENT_PATH = ./environment/
MATH_PATH = ./math/
QUAD_PATH = ./quadrotor/

CXX = g++-5
CXXFLAGS=-std=c++11 -Wall -Wextra -O2 -ggdb3 $(LIBS_PATH)

OBJECTS_UAVITL = $(COMM_PATH)udp_client_server.o \
				 $(XPLANE_PATH)XPdata.o \
				 $(XPLANE_PATH)XPgps.o \
				 $(XPLANE_PATH)XPattitude.o \
				 $(XPLANE_PATH)XPpqr.o \
				 $(XPLANE_PATH)XPspeeds.o \
				 $(XPLANE_PATH)XPloads.o \
				 $(XPLANE_PATH)XPxyz.o \
				 $(XPLANE_PATH)XPthrottelc.o \
				 $(XPLANE_PATH)XPthrottela.o \
				 $(XPLANE_PATH)XPgearbrakes.o \
				 $(XPLANE_PATH)XPyoke.o \
				 $(XPLANE_PATH)XPaerangles.o \
				 $(XPLANE_PATH)XPatmosphere.o \
				 $(ENVIRONMENT_PATH)gravity.o \
				 $(MATH_PATH)math_util.o \
				 sim.o \
				 flyingmachine.o \
				 gnc.o \
				 sensors.o \
				 $(QUAD_PATH)quad_gnc.o \
				 $(QUAD_PATH)quad_sensors.o \
				 uavitl.o

all: uavitl

uavitl: $(OBJECTS_UAVITL)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_PATH)

clean:
	$(RM) *~ *.o *.swp uavitl \
		$(COMM_PATH)*~  $(COMM_PATH)*.o $(COMM_PATH)*.swp  \
		$(XPLANE_PATH)*~  $(XPLANE_PATH)*.o $(XPLANE_PATH)*.swp \
		$(ENVIRONMENT_PATH)*~  $(ENVIRONMENT_PATH)*.o $(ENVIRONMENT_PATH)*.swp \
		$(QUAD_PATH)*~  $(QUAD_PATH)*.o $(QUAD_PATH)*.swp \

.PHONY: clean
