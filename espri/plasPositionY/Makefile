#TARGET =event_by_event_bdc
TARGET =findPlasVsPosition
#TARGET =bdc

CODESOURCE =  $(TARTSYS)

ROOTCFLAGS  = $(shell $(CFG_ROOT_BIN)root-config --cflags)
ROOTLIBS    = $(shell $(CFG_ROOT_BIN)root-config --libs) -lGX11 -lXMLParser
CFLAGS = -I$(CODESOURCE)/include -L$(CODESOURCE)/lib -lanacore		\
-I$(CODESOURCE)/include -L$(CODESOURCE)/lib -lanaroot -lananadeko	\
-lanabrips -lanadali -lanasamurai -lanacore -lanaespri -lanawinds	\
-lanasilicons -funroll-loops -fgcse-lm -fgcse-sm -fschedule-insns	\
-Wall -ggdb #-O2 # 

GXX = g++ 

all: $(TARGET) 

$(TARGET) : $(TARGET).C
#	./extract_ttree_def.sh
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ $^

clean:
	rm -f $(TARGET)
