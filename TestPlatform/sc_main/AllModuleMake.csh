# 2015.10.01 harold.Ko
# Cortex-M0DS Software Profiling Test.
#! /bin/csh -f

cd ../AHB_Lite
make clean
make
cd ..
 
cd ahbl2mem 
make clean
make
cd ..

cd console 
make clean
make
cd ..

cd tb 
make clean
make
cd ..

cd VCORTEXM0DS 
make clean
make
cd ../sc_main

