#!bin/sh

rm -vrf $HOME/workspace/Install/systemc231 

cd $HOME/workspace/BlockDesigner/BlockDesigner_Core/systemc-2.3.1_BD/
cd objdir
make
make install

cd $HOME/workspace/BlockDesigner/TestPlatform/sc_main/

source systemc.csh
source scv.csh
#source $HOME/workspace/BlockDesigner/TestPlatform/sc_main/AllModuleMake.csh
source $HOME/workspace/BlockDesigner/TestPlatform/sc_main/compile.csh
source $HOME/workspace/BlockDesigner/TestPlatform/sc_main/make_shared_object.csh

#cd $HOME/workspace/BlockDesigner/TestPlatform/SSDProject/
#source $HOME/workspace/BlockDesigner/TestPlatform/SSDProject/SSDModuleMake.csh

cd $HOME/workspace/BlockDesigner/testCommand/
