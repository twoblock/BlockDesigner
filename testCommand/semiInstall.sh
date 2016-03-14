#!bin/sh

rm -vrf $HOME/workspace/Install/systemc231 

cd $HOME/workspace/BlockDesigner/BlockDesigner_Core/systemc-2.3.1_BD/
cd objdir
make
make install

cd $HOME/workspace/BlockDesigner/testCommand/

