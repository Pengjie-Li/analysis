# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
# Author: Penjie Li, 08/12/2016

ARCH          = linux
CXX           =
ObjSuf        = o
SrcSuf        = cpp
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# Linux with egcs, gcc 2.9x, gcc 3.x (>= RedHat 5.2)
CXX           = g++
CXXFLAGS      = -Wall -fPIC
LD            = g++
LDFLAGS       = -o
SOFLAGS       = -shared

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)
CFLAGS = -Wall -O2 -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser

#------------------------------------------------------------------------------

TESTSSO		=classtest.o
TESTSSH		=classtest.h
HEADERS		=classtest.h global.h
SOURCES		= classtest.cpp
#RESULTSO        = Results.o
#RESULTSS        = Results.cpp ResultsDict.cpp
#RESULTSSO       = Results.o ResultsDict.o
#RESULTSH        = Results.h ResultsDict.h
#
#OBJS            = usrini.o usrout.o mgdraw.o

#------------------------------------------------------------------------------

all:		test libtest.so

MyDict.cxx:	$(HEADERS) test_LinkDef.h
		@echo "Generating dictionary $@..."
		@$(ROOTSYS)/bin/rootcint -f $@ -c $(CXXFLAGS) -p $^
		@echo "$@ done"
libtest.so:     MyDict.cxx $(HEADERS) $(SOURCES)
		$(LD) $(SOFLAGS) $(LDFLAGS) $@ `root-config --ldflags` $(CXXFLAGS) -I $(ROOTSYS)/include $^
		@echo "$@ done"
test:		MyDict.cxx main.cpp $(HEADERS) $(SOURCES)
		$(LD) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(LDFLAGS) $@ $^
		@echo "$@ done"


clean:
		@rm -f *.so *.o *Dict* test

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<
