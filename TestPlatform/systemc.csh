# 2015.09.09 harold.Ko
# This file includes SystemC.2.3.1 path.
# Need to run this file for Verilator configuration.

#! /bin/csh -f

SYSTEMC_INCLUDE=/home/bryan/workspace/Install/systemc_2.3.1_BD/include


export SYSTEMC_INCLUDE

SYSTEMC_LIBDIR=/home/bryan/workspace/Install/systemc_2.3.1_BD/lib-linux
export SYSTEMC_LIBDIR

LD_LIBRARY_PATH=$SYSTEMC_LIBDIR:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

# Might be needed if SystemC 2.3.0
export SYSTEMC_CXX_FLAGS=-pthread

echo SystemC_2.3.1_BD Configuration Complete.
