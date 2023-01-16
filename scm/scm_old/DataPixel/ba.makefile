
OBJ = ldp
#sourcefile = main.cpp ldp.cpp ldp.h 
sourcefile = main.cpp 

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -O2 -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser

PIXEL= -I/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/class/include/ -L/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/class/lib -lTNewPixel
GXX = g++

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(PIXEL) -o $@ $(filter %.cpp ,$(sourcefile))

clean:
	rm -f *~ *.o $(OBJ)
