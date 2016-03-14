# 2015.09.09 harold.Ko
# This file includes SystemC.2.3.1 path.
# Need to run this file for Verilator configuration.

#! /bin/csh -f

SYSTEMC_INCLUDE=$HOME/workspace/Install/systemc231/include
export SYSTEMC_INCLUDE

SYSTEMC_LIBDIR=$HOME/workspace/Install/systemc231/lib-linux64
export SYSTEMC_LIBDIR

LD_LIBRARY_PATH=$SYSTEMC_LIBDIR:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

# Might be needed if SystemC 2.3.0
export SYSTEMC_CXX_FLAGS=-pthread

echo SystemC.2.3.1 Configuration Complete.
