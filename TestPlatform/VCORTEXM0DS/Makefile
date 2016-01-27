PACKAGE    = VCORTEXM0DS
BUILDFLAGS = -g3 -fPIC  -Wall -W -pedantic -Wno-long-long -Wwrite-strings -Wpointer-arith 
CXX        = g++ 
CXXFLAGS = -fPIC -I$(SYSTEMC_INCLUDE) -I/usr/local/share/verilator/include/ -I/usr/local/share/verilator/include/vltstd
LDFLAGS  = -Wl,--export-dynamic
COMMON_LIBS = -L$(SYSTEMC_LIBDIR) -lsystemc

PACKAGE_SOURCES =   VCORTEXM0DS.cpp \
										VCORTEXM0DS_BDDI.cpp \
										VCORTEXM0DS__Syms.cpp

SO = lib$(PACKAGE).so

$(SO) : $(PACKAGE_SOURCES:.cpp=.o)
	make CXXFLAGS+=' -g ' -j -f VCORTEXM0DS.mk verilated.o 
	$(CXX) $(CXXFLAGS) -o $@ -shared $^ verilated.o $(COMMON_LIBS) $(LDFLAGS) 

clean: 
	rm -f $(SO)
	rm -f *.o
	rm -f verilated.d
