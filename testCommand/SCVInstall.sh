#!bin/sh

rm -vrf $HOME/workspace/BlockDesigner/scv-2.0.0/objdir
rm -vrf $HOME/workspace/Install/scv200 

cd $HOME/workspace/BlockDesigner/scv-2.0.0

mkdir objdir
cd objdir
../configure --prefix=$HOME/workspace/Install/scv200 --with-systemc=$HOME/workspace/Install/systemc231
make 
make install

cd $HOME/workspace/BlockDesigner/TestPlatform/sc_main/

source scv.csh

cd $HOME/workspace/BlockDesigner/testCommand/
