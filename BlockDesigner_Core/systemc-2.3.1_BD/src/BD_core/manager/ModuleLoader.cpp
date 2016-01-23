//-----------------------------------------------------------------------------
// Design								: Block Designer Module Loader 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleLoader.cpp
// Date	       					: 2016/1/20
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Load sc_module from so file. 
//                allocate sc_module by using CreateInstance funtion.
//								and return sc_module pointer. 
// ----------------------------------------------------------------------------

#include "ModuleLoader.h"

namespace BDapi
{		
	/*
	 * function 	: GetScModule
	 * design	    : get sc_module from so file 
	 * param	    : const char * ( so file path )
	 * param	    : const char * ( sc_module instace name)
	 * return    	: sc_module*   ( sc_module pointer in systemc )
	 */
	sc_module* ModuleLoader::GetSCmodule(const char *Path, const char *ModuleName)
	{
		void *p_Handle = NULL;
		Function p_CreateInstance = NULL;

		p_Handle = LoadSoFile(Path);
		if(!p_Handle) 
			printf("fail to load so file, %s\n", dlerror());
		else{
			p_CreateInstance = FindSymbol(p_Handle);
			if ( dlerror() != NULL )
				printf("fail to load function symbol, %s\n", dlerror());
			else
				p_SCmodule =	p_CreateInstance(ModuleName);
		}

		return p_SCmodule;
	}
	
	/*
	 * function 	: LoadSoFile 
	 * design	    : 
	 */
	void* ModuleLoader::LoadSoFile(const char *Path)
	{
		return dlopen(Path, RTLD_NOW);
	}

	/*
	 * function 	: FindSymbol 
	 * design	    : find CreateInstance function symbol
	 */
	Function ModuleLoader::FindSymbol(void *Handle)
	{
		return (Function)dlsym(Handle,"CreateInstance");
	}
}
