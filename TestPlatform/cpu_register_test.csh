# 2015.10.01 harold.Ko
# Cortex-M0DS Software Profiling Test.

#! /bin/csh -f
./remove_test.csh

mkdir obj_dir
cd obj_dir

cp ../VCORTEXM0DS/VCORTEXM0DS.mk ./
cp ../VCORTEXM0DS/VCORTEXM0DS_classes.mk ./
cp ../VCORTEXM0DS/VCORTEXM0DS__Syms.h ./
cp ../VCORTEXM0DS/VCORTEXM0DS__Syms.cpp ./
cp ../VCORTEXM0DS/VCORTEXM0DS.cpp ./
cp ../VCORTEXM0DS/VCORTEXM0DS.h ./
cp ../VCORTEXM0DS/VCORTEXM0DS_BDDI.cpp ./
cp ../VCORTEXM0DS/VCORTEXM0DS_BDDI.h ./

make CXXFLAGS+=' -g ' -j -f VCORTEXM0DS.mk verilated.o 

make CXXFLAGS+=' -g ' -j -f VCORTEXM0DS.mk ../sc_main.o verilated.o VCORTEXM0DS__Syms.o VCORTEXM0DS.o VCORTEXM0DS_BDDI.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o ../Software_Profiler.o ../console_BDDI.o ../console.o ../ahbl2mem.o ../ahbl2mem_BDDI.o ../ahbl2mem_1.o ../ahbl2mem_1_BDDI.o ../tb.o ../tb_BDDI.o ../AHB_Lite_BDDI.o

g++ -g -L$SYSTEMC_LIBDIR ../sc_main.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o VCORTEXM0DS__Syms.o VCORTEXM0DS.o VCORTEXM0DS_BDDI.o verilated.o ../Software_Profiler.o ../console_BDDI.o ../console.o ../AHB_Lite_BDDI.o ../ahbl2mem.o ../ahbl2mem_BDDI.o ../ahbl2mem_1.o ../ahbl2mem_1_BDDI.o ../tb.o ../tb_BDDI.o -o VCM0DS -lsystemc

cp ../CM0DS.elf ./
cp ../wave.gtkw ./
cp ../CM0DS.txt ./

echo //////////////////////////////////////////////////////////////
echo // Software profiling test configuration complete.            
echo // If you want to run the test, move the 'obj_dir' directory,
echo // And execute the 'VCM0DS' file.                            
echo //////////////////////////////////////////////////////////////
