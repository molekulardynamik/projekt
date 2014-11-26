# file      : examples/build/xsd/tree-rules.make
# copyright : Copyright (c) 2006-2014 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(root)/build/xsd/common.make

override LIBS := -lxerces-c $(LIBS)

# Rules.
#
.PRECIOUS: %.cpp %.h %.ixx

%.cpp %.h %.ixx: %.xsd
	$(XSD) cxx-tree --hxx-suffix .h --cxx-suffix .cpp $(XSDFLAGS) cuboid.xsd

# original: $(XSD) cxx-tree --hxx-suffix .h --cxx-suffix .cpp $(XSDFLAGS) $<
