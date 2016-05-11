# 2016.05.10 harold.Ko
# This file includes SCV.2.0.0 path.

#! /bin/csh -f

SCV_INCLUDE=$HOME/workspace/Install/scv200/include
export SCV_INCLUDE

SCV_LIBDIR=$HOME/workspace/Install/scv200/lib-linux64
export SCV_LIBDIR

LD_LIBRARY_PATH=$SCV_LIBDIR:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

echo SCV.2.0.0 Configuration Complete.
