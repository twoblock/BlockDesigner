# 2015.10.01 harold.Ko
# Cortex-M0DS Software Profiling Test.

#! /bin/csh -f
./remove_test.csh

verilator --sc CORTEXM0DS.v cortexm0ds_logic.v

cd obj_dir

#make -j -f VCORTEXM0DS.mk VCORTEXM0DS__ALL.a
#make -j -f VCORTEXM0DS.mk ../sc_main.o verilated.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o ../Software_Profiler.o
make CXXFLAGS+=' -g ' -j -f VCORTEXM0DS.mk VCORTEXM0DS__ALL.a
make CXXFLAGS+=' -g ' -j -f VCORTEXM0DS.mk ../sc_main.o verilated.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o ../Software_Profiler.o ../console_BDDI.o ../console.o ../ahbl2mem.o ../ahbl2mem_BDDI.o ../ahbl2mem_1.o ../ahbl2mem_1_BDDI.o ../tb.o ../tb_BDDI.o ../AHB_Lite_BDDI.o
#make CXXFLAGS+=' -g ' -j -f VCORTEXM0DS.mk ../sc_main.o verilated.o ../Software_Profiler.o 

#g++ -L$SYSTEMC_LIBDIR ../sc_main.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o VCORTEXM0DS__ALL*.o verilated.o ../Software_Profiler.o -o VCM0DS -lsystemc
g++ -g -L$SYSTEMC_LIBDIR ../sc_main.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o VCORTEXM0DS__ALL*.o verilated.o ../Software_Profiler.o ../console_BDDI.o ../console.o ../AHB_Lite_BDDI.o ../ahbl2mem.o ../ahbl2mem_BDDI.o ../ahbl2mem_1.o ../ahbl2mem_1_BDDI.o ../tb.o ../tb_BDDI.o -o VCM0DS -lsystemc
#g++ -g -L$SYSTEMC_LIBDIR ../sc_main.o VCORTEXM0DS__ALL*.o verilated.o ../Software_Profiler.o -o VCM0DS -lsystemc

cp ../CM0DS.elf ./
cp ../wave.gtkw ./
cp ../CM0DS.txt ./

echo //////////////////////////////////////////////////////////////
echo // Software profiling test configuration complete.            
echo // If you want to run the test, move the 'obj_dir' directory,
echo // And execute the 'VCM0DS' file.                            
echo //////////////////////////////////////////////////////////////
