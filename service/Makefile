CXX=g++
AR=ar
CXXFLAGS=-Wall -g -O2
CXX_OPTS=-c -I../libs/

SOURCES=sensors_mpu9250.cpp AHRS.cpp StringOp.cpp bt_recv.cpp
OBJECTS=$(SOURCES:.cpp=.o)

LIB=libsensorservice.a

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXX_OPTS) $< -o $@ 
	

$(LIB): $(OBJECTS) 
	$(AR) rcs $(LIB) $(OBJECTS) 

all: $(LIB)

clean:
	rm -rf *.o
	rm -rf $(LIB)
