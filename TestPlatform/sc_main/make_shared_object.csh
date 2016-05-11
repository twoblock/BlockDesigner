# 2016.1.09 Bryan Choi
# make shared object file ( libBD_sim.so ) 
#! /bin/csh -f

./remove.csh

g++ -fPIC -g -I$SYSTEMC_INCLUDE -L$SYSTEMC_LIBDIR -I$SCV_INCLUDE -L$SCV_LIBDIR -c -o sc_main.o sc_main.cpp
g++ -fPIC -g -I$SYSTEMC_INCLUDE -L$SYSTEMC_LIBDIR -I$SCV_INCLUDE -L$SCV_LIBDIR sc_main.o -o VCM0DS -lsystemc -lscv
g++ -shared -o libBD_sim.so sc_main.o $HOME/workspace/Install/systemc231/lib-linux64/libsystemc-2.3.1.so $HOME/workspace/Install/scv200/lib-linux64/libscv-2.0.0.so

echo //////////////////////////////////////////////////////////////
echo // If you want to get libBD_core.so, move the 'obj_dir' directory,
echo // And find 'libBD_sim.so' file.                            
echo //////////////////////////////////////////////////////////////
