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

noinst_LTLIBRARIES = libBD_core.la

SUBDIRS = \
	manager \
  SimulationAPI 

H_FILES = \
	BD_core.h

CXX_FILES =

localincludedir = $(includedir)/BD_core
nobase_localinclude_HEADERS = $(H_FILES)

libBD_core_la_SOURCES = $(NO_H_FILES) $(CXX_FILES)
# dummy C++ source to cause C++ linking
nodist_EXTRA_libBD_core_la_SOURCES = BD_core_nonexistent.cpp

libBD_core_la_LIBADD = \
       manager/libmanager.la \
       SimulationAPI/libBDSim.la 

## Taf!
