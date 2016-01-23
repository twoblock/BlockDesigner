//-----------------------------------------------------------------------------
// Design								: Block Designer Module Loader 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleLoader.h
// Date	       					: 2016/1/20
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Load sc_module from so file. 
//                allocate sc_module by using CreateInstance funtion.
//								and return sc_module pointer. 
// ----------------------------------------------------------------------------

#ifndef LOADMANGER_H 
#define LOADMANGER_H 

#include <dlfcn.h>
#include "../../sysc/kernel/sc_module.h"

typedef sc_core::sc_module sc_module;

typedef sc_module* (*Function)(const char*);

/*
 * namespacei 	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : ModuleLoader 
	 * design	      : load so file and return sc_module 
	 */
	class ModuleLoader
	{
		public:
			sc_module* GetSCmodule(const char *Path, const char *ModuleName);

		private:
			void* LoadSoFile(const char *Path);
			Function FindSymbol(void *Handle);
			
			sc_module *p_SCmodule;	
	};
} // namespace BDapi 

#endif 


