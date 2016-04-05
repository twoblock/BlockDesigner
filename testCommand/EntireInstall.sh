#!bin/sh

rm -vrf $HOME/workspace/BlockDesigner/BlockDesigner_Core/systemc-2.3.1_BD/objdir
rm -vrf $HOME/workspace/Install/systemc231 

cd $HOME/workspace/BlockDesigner/BlockDesigner_Core/systemc-2.3.1_BD/
autoconf
automake

mkdir objdir
cd objdir
../configure --enable-debug  --disable-optimize  --prefix=$HOME/workspace/Install/systemc231 
make 
make install

cd $HOME/workspace/BlockDesigner/TestPlatform/sc_main/

source systemc.csh
source $HOME/workspace/BlockDesigner/TestPlatform/sc_main/AllModuleMake.csh
source $HOME/workspace/BlockDesigner/TestPlatform/sc_main/compile.csh
source $HOME/workspace/BlockDesigner/TestPlatform/sc_main/make_shared_object.csh

cd $HOME/workspace/BlockDesigner/testCommand/
