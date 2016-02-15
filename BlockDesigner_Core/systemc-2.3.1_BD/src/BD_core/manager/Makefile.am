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

LIBS+= -ldl

noinst_LTLIBRARIES = libmanager.la

H_FILES = \
	ExecutionManager.h \
	TopManager.h \
	TopManagerBase.h \
	AllManager.h \
	BDDIManager.h \
	ModuleListManager.h \
  ModuleLoader.h \
  ModuleConnector.h \
	BDPMDInitManager.h \
	PMMLGenerationManager.h \
	SignalTraceManager.h
 
CXX_FILES = \
	ExecutionManager.cpp \
	BDDIManager.cpp \
	ModuleListManager.cpp \
	ModuleLoader.cpp \
  ModuleConnector.cpp \
	BDPMDInitManager.cpp \
	PMMLGenerationManager.cpp \
	SignalTraceManager.cpp

localincludedir = $(includedir)/BD_core/manager
nobase_localinclude_HEADERS = $(H_FILES)

libmanager_la_SOURCES = $(NO_H_FILES) $(CXX_FILES)

## Taf!
