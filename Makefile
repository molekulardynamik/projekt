# This is a makefile template

include files.mk


# Compiler
# --------
CC=g++
#CC=icpc


# Compiler flags
# -------------------------------------------------------------------------
#CFLAGS=-O3 -ip -ipo -fast
CFLAGS=-g -O3 -ggdb

# Linker flags
# ------------
LDFLAGS= -lxerces-c -lcppunit -llog4cxx -lxerces-c -lgomp
INCLUDES= -I./src -I./libxsd -fopenmp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

clean:
	rm $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

