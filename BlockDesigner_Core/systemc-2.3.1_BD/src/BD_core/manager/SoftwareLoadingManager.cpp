//-----------------------------------------------------------------------------
// Design								: Software Loading Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareLoadingManager.h
// Date	       					: 2016/3/2
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: help tool load software 
// ----------------------------------------------------------------------------

#include "SoftwareLoadingManager.h"

namespace BDapi
{	
	// declare static variable for linker 
	SoftwareLoadingManager* SoftwareLoadingManager::_SoftwareLoadingManager= NULL;
	// initialize mutex 
	pthread_mutex_t SoftwareLoadingManager::SoftwareLoadingManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : 
	 * param	      : 
	 * caller		    : 
	 */
	void SoftwareLoadingManager::PutOperationControl(GUI_COMMAND Command)
	{
	}

	/*
	 * function    	: PutOperationControl
	 * design	      : 
	 * param	      : 
	 * caller		    : 
	 */
	void SoftwareLoadingManager::AddConnectionInfo(string CPUName, string ConnectedModuleName)
	{

		CPUInfo *pst_CPUInfo;
		vector<string> *p_ConnectedModules;

		int CPUIndex = 0;

		// Find CPU Name in CPUs vector	
		CPUIndex = FindCPU(CPUName);

		// Find
		if(CPUIndex != -1){

			pst_CPUInfo =	CPUs[CPUIndex];

			p_ConnectedModules = &(pst_CPUInfo->ConnectedModules);
			p_ConnectedModules->push_back(ConnectedModuleName);      
		}
		// Not find
		else{
			pst_CPUInfo = new CPUInfo();
			pst_CPUInfo->CPUName = CPUName;

			p_ConnectedModules = &(pst_CPUInfo->ConnectedModules);
			p_ConnectedModules->push_back(ConnectedModuleName);      

			CPUs.push_back(pst_CPUInfo);
		}
	}

	/*
	 * function    	: PutOperationControl
	 * design	      : 
	 * param	      : 
	 * caller		    : 
	 */
	int SoftwareLoadingManager::FindCPU(string CPUName)
	{
		int dw_Position = -1;		

		// ready to iteratei CPUs 
		vector<CPUInfo*>::iterator FirstCPU = CPUs.begin(); 
		vector<CPUInfo*>::iterator LastCPU = CPUs.end();
		vector<CPUInfo*>::iterator IndexOfCPU = FirstCPU;  

		/********************************************
		 * Iterate CPUs in system 
		 ********************************************/
		for(IndexOfCPU = FirstCPU; IndexOfCPU != LastCPU; ++IndexOfCPU){   
			// compare cpu name
			if((*IndexOfCPU)->CPUName == CPUName){
				// find index of CPUs vector
				dw_Position	= distance(FirstCPU, IndexOfCPU);
			}
		}
		return dw_Position;
	}
	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	SoftwareLoadingManager* SoftwareLoadingManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&SoftwareLoadingManagerInstanceMutex); 

		if( _SoftwareLoadingManager == NULL ){
			_SoftwareLoadingManager = new SoftwareLoadingManager();
		}
		// unlock
		pthread_mutex_unlock(&SoftwareLoadingManagerInstanceMutex);

		return _SoftwareLoadingManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete SoftwareLoadingManager instance 
	 */
	void SoftwareLoadingManager::DeleteInstance()
	{	
		delete _SoftwareLoadingManager;
		_SoftwareLoadingManager = NULL;
	}

	/*
	 * function 	: SoftwareLoadingManager 
	 * design	    : Constructor 
	 */
	SoftwareLoadingManager::SoftwareLoadingManager()
	{
	}

	/*
	 * function 	: ~SoftwareLoadingManager
	 * design	    : Destructor
	 */
	SoftwareLoadingManager::~SoftwareLoadingManager()
	{
	}
}
