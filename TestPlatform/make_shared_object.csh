# 2016.1.09 Bryan Choi
# make shared object file ( libBD_core.so ) 

#! /bin/csh -f

verilator --sc CORTEXM0DS.v cortexm0ds_logic.v
verilator --sc mem_interface.v
cd obj_dir

# make all object file here, -fPIC option make speed up for loading so.file
make CXXFLAGS+='-fPIC ' -j -f VCORTEXM0DS.mk VCORTEXM0DS__ALL.a
make CXXFLAGS+='-fPIC'  -j -f Vmem_interface.mk Vmem_interface__ALL.a
make CXXFLAGS+='-fPIC'  -j -f VCORTEXM0DS.mk Vmem_interface.mk  ../sc_main.o verilated.o ../Software_Profiler.o

g++ -shared -o libBD_sim.so ../sc_main.o  VCORTEXM0DS__ALL*.o Vmem_interface__ALL*.o verilated.o ../Software_Profiler.o /usr/local/systemc231/lib-linux64/libsystemc-2.3.1.so 

cp libBD_sim.so /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/
chmod 777 /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_sim.so

echo //////////////////////////////////////////////////////////////
echo // If you want to get libBD_core.so, move the 'obj_dir' directory,
echo // And find 'libBD_core.so' file.                            
echo //////////////////////////////////////////////////////////////
