# 2015.10.01 harold.Ko
# Cortex-M0DS Software Profiling Test.
#! /bin/csh -f

./remove.csh

g++ -g -I$SYSTEMC_INCLUDE -L$SYSTEMC_LIBDIR -I$SCV_INCLUDE -L$SCV_LIBDIR -c -o sc_main.o sc_main.cpp
g++ -g -I$SYSTEMC_INCLUDE -L$SYSTEMC_LIBDIR -I$SCV_INCLUDE -L$SCV_LIBDIR sc_main.o -o VCM0DS -lsystemc -lscv

echo //////////////////////////////////////////////////////////////
echo // Software profiling test configuration complete.            
echo // If you want to run the test, move the 'obj_dir' directory,
echo // And execute the 'VCM0DS' file.                            
echo //////////////////////////////////////////////////////////////
