## ****************************************************************************
##
##  The following code is derived, directly or indirectly, from the SystemC
##  source code Copyright (c) 1996-2014 by all Contributors.
##  All Rights reserved.
##
##  The contents of this file are subject to the restrictions and limitations
##  set forth in the SystemC Open Source License (the "License");
##  You may not use this file except in compliance with such restrictions and
##  limitations. You may obtain instructions on how to receive a copy of the
##  License at http://www.accellera.org/. Software distributed by Contributors
##  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
##  ANY KIND, either express or implied. See the License for the specific
##  language governing rights and limitations under the License.
##
## ****************************************************************************
##
##  src/sysc/kernel/Makefile.am --
##  Process this file with automake to produce a Makefile.in file.
##
##  Original Author: Martin Janssen, Synopsys, Inc., 2001-05-21
##
## ****************************************************************************
##
##  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
##  changes you are making here.
##
##      Name, Affiliation, Date:
##  Description of Modification:
##
## ****************************************************************************

include $(top_srcdir)/config/Make-rules.sysc

noinst_LTLIBRARIES = libgui.la

H_FILES = \
	test.h \
	StartSimulationThreads.h \
	StartPlatformManagerThreads.h \
	../../../../../JNI_Interface/SimulationEnvironment/Handler_Command.h \
	../../../../../JNI_Interface/SimulationEnvironment/Handler_SimulationInitThread.h \
	../../../../../JNI_Interface/SimulationEnvironment/Hanlder_CallBack.h \
	../../../../../JNI_Interface/jdk_h/jni.h  \
	../../../../../JNI_Interface/jdk_h/jni_md.h 
 
CXX_FILES = \
	test.cpp \
	StartSimulationThreads.cpp \
	StartPlatformManagerThreads.cpp \
	../../../../../JNI_Interface/SimulationEnvironment/Handler_Command.cpp \
	../../../../../JNI_Interface/SimulationEnvironment/Handler_SimulationInitThread.cpp \
	../../../../../JNI_Interface/SimulationEnvironment/Hanlder_CallBack.cpp 

localincludedir = $(includedir)/BD_core/gui
nobase_localinclude_HEADERS = $(H_FILES)

libgui_la_SOURCES = $(NO_H_FILES) $(CXX_FILES)

## Taf!
