# This is a makefile template

include files.mk

#root := /home/penguin/Desktop/MolSim/src

#include $(root)/build/cxx/rules.make
#include $(root)/build/xsd/tree-rules.make

# Compiler
# --------
CC=g++
#CC=icpc

# Build.
#
#hello.cpp hello.h: hello.xsd

# xy

# Compiler flags
# -------------------------------------------------------------------------
CFLAGS=-g -O3 -ggdb

# Linker flags
# ------------
LDFLAGS= -lxerces-c -lcppunit -lapr-1 -laprutil-1 -llog4cxx -lxerces-c -Wl,--version-script memcpy_wrap.map 
INCLUDES= -I./src -I./libxsd

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) memcpy_wrap.o $(LDFLAGS) -o $@ 

clean:
	rm $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

