# 2016.1.09 Bryan Choi
# make shared object file ( libBD_sim.so ) 
#! /bin/csh -f

./remove.csh

g++ -fPIC -g -I$SYSTEMC_INCLUDE -L$SYSTEMC_LIBDIR -c -o sc_main.o sc_main.cpp
g++ -fPIC -g -I$SYSTEMC_INCLUDE -L$SYSTEMC_LIBDIR sc_main.o -o VCM0DS -lsystemc
g++ -shared -o libBD_sim.so sc_main.o /usr/local/systemc231/lib-linux64/libsystemc-2.3.1.so

echo //////////////////////////////////////////////////////////////
echo // If you want to get libBD_core.so, move the 'obj_dir' directory,
echo // And find 'libBD_sim.so' file.                            
echo //////////////////////////////////////////////////////////////
