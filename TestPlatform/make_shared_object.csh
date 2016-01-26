# 2016.1.09 Bryan Choi
# make shared object file ( libBD_sim.so ) 

#! /bin/csh -f

verilator --sc CORTEXM0DS.v cortexm0ds_logic.v
cd obj_dir

# make all object file here, -fPIC option make speed up for loading so.file
make CXXFLAGS+='-fPIC ' -j -f VCORTEXM0DS.mk VCORTEXM0DS__ALL.a
make CXXFLAGS+='-fPIC'  -j -f VCORTEXM0DS.mk ../sc_main.o verilated.o ../Software_Profiler.o ../AHBDCD.o ../AHBMUX.o ../AHB_Lite.o ../console_BDDI.o

g++ -shared -o libBD_sim.so ../sc_main.o ../AHBMUX.o ../AHBDCD.o ../AHB_Lite.o ../console_BDDI.o VCORTEXM0DS__ALL*.o verilated.o ../Software_Profiler.o /usr/local/systemc231/lib-linux64/libsystemc-2.3.1.so

cp libBD_sim.so /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/
chmod 777 /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_sim.so
chown lucas: /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_sim.so

cp ../wave.gtkw /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/
cp ../CM0DS.txt /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/
cp ../CM0DS.elf /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/

chmod 777 /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/wave.gtkw
chown lucas: /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/wave.gtkw

chmod 777 /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.txt
chown lucas: /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.txt

chmod 777 /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.elf
chown lucas: /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.elf

#cd /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/

#filename="wave.vcd"
#if [ -e $filename ] ; then 
#rm -rf $filename
#mkfifo $filename
#else
#mkfifo $filename
#fi

#chmod 777 /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/wave.vcd
#chown lucas: /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/wave.vcd

echo //////////////////////////////////////////////////////////////
echo // If you want to get libBD_core.so, move the 'obj_dir' directory,
echo // And find 'libBD_sim.so' file.                            
echo //////////////////////////////////////////////////////////////
