LIBS_PATH = -I/usr/include/eigen3 -I/usr/include/boost
COMM_PATH = ./comm/
XPLANE_PATH = ./XPlane/
ENVIRONMENT_PATH = ./environment/
QUAD_PATH = ./quadrotor/
FORMATION_PATH = ./formation/

LDFLAGS = -lm -lboost_filesystem -lboost_system

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
				 sim.o \
				 flyingmachine.o \
				 gnc.o \
				 sensors.o \
				 $(QUAD_PATH)quad_gnc.o \
				 $(QUAD_PATH)quad_sensors.o \
				 $(FORMATION_PATH)distance_formation.o \
				 $(FORMATION_PATH)position_formation.o \
				 $(FORMATION_PATH)bearing_formation.o \

OBJECTS_UAVITL_1QUAD = $(OBJECTS_UAVITL) uavitl_1quad.o
OBJECTS_UAVITL_FORM = $(OBJECTS_UAVITL) uavitl_form.o

all: uavitl_1quad uavitl_form

uavitl_1quad: $(OBJECTS_UAVITL_1QUAD)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_PATH) $(LDFLAGS)

uavitl_form: $(OBJECTS_UAVITL_FORM)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS_PATH) $(LDFLAGS)

clean:
	$(RM) *~ *.o *.swp uavitl_form uavitl_1quad \
		$(COMM_PATH)*~  $(COMM_PATH)*.o $(COMM_PATH)*.swp  \
		$(XPLANE_PATH)*~  $(XPLANE_PATH)*.o $(XPLANE_PATH)*.swp \
		$(ENVIRONMENT_PATH)*~  $(ENVIRONMENT_PATH)*.o $(ENVIRONMENT_PATH)*.swp \
		$(QUAD_PATH)*~  $(QUAD_PATH)*.o $(QUAD_PATH)*.swp \
		$(FORMATION_PATH)*~  $(FORMATION_PATH)*.o $(FORMATION_PATH)*.swp \

.PHONY: clean
