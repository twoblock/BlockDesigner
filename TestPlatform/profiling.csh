# 2015.10.01 harold.Ko
# Cortex-M0DS Software Profiling Test.

#! /bin/csh -f

verilator --sc CORTEXM0DS.v cortexm0ds_logic.v
verilator --sc mem_interface.v
cd obj_dir

make CXXFLAGS+=' -g' -j -f VCORTEXM0DS.mk VCORTEXM0DS__ALL.a
make CXXFLAGS+=' -g' -j -f Vmem_interface.mk Vmem_interface__ALL.a
#make CXXFLAGS+=' -g' -j -f VCORTEXM0DS.mk Vmem_interface.mk  ../sc_main.o verilated.o ../Software_Profiler.o

#g++  -fdiagnostics-color -g -L$SYSTEMC_LIBDIR ../sc_main.o VCORTEXM0DS__ALL*.o Vmem_interface__ALL*.o verilated.o ../Software_Profiler.o -o VCM0DS -lsystemc
#cp ../CM0DS.hex ./
#cp ../wave.gtkw ./

#filename="wave.vcd"
#if [ -e $filename ] ; then 
#rm -rf $filename
#mkfifo $filename
#else
#mkfifo $filename
#fi

#cd obj_dir
#./VCM0DS

echo //////////////////////////////////////////////////////////////
echo // Software profiling test configuration complete.            
echo // If you want to run the test, move the 'obj_dir' directory,
echo // And execute the 'VCM0DS' file.                            
echo //////////////////////////////////////////////////////////////
