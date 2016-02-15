
PACKAGE    = AHB_Lite
BUILDFLAGS = -g3 -fPIC  -Wall -W -pedantic -Wno-long-long -Wwrite-strings -Wpointer-arith 
CXX        = g++ 
CXXFLAGS = -fPIC -I$(SYSTEMC_INCLUDE)
LDFLAGS  = -Wl,--export-dynamic
COMMON_LIBS = -L$(SYSTEMC_LIBDIR) -lsystemc

PACKAGE_SOURCES =   AHB_Lite.cpp \
										AHBDCD.cpp \
										AHBMUX.cpp \
										AHB_Lite_BDDI.cpp \
										AHB_Lite_BDMMI.cpp 

SO = lib$(PACKAGE).so

$(SO) : $(PACKAGE_SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ -shared $^ $(COMMON_LIBS) $(LDFLAGS) 

clean: 
	rm -f $(SO)
	rm -f *.o
