# 2015.10.01 harold.Ko
# Cortex-M0DS Software Profiling Test.
#! /bin/csh -f

cd BufferManager 
make clean
make
cd ..

cd MemoryUtility 
make clean
make
cd ..

cd NANDController 
make clean
make
cd ..

cd NANDFlashArray_SLC 
make clean
make
cd ..

cd SATADevice 
make clean
make
cd ..

cd SATAHOST 
make clean
make
cd ..


