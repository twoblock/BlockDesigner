//-----------------------------------------------------------------------------
// Design								: Software Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareManager.h
// Date	       					: 2016/3/2
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manager each software for each cpu
//
//                todo list
//                1. load software
//                2. profile software flow data
//                3. display assembly code 
// ----------------------------------------------------------------------------

#include "SoftwareManager.h"
#include "ModuleListManager.h"
#include "CallBackManager.h"

namespace BDapi
{	
	// declare static variable for linker 
	SoftwareManager* SoftwareManager::_SoftwareManager= NULL;
	// initialize mutex 
	pthread_mutex_t SoftwareManager::SoftwareManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : for Argu1 cpu, do things below 
   *                1. load software
   *                2. profile software flow data
   *                3. display assembly code 
   * 
	 * param	      : Command.Argu1 - CPU name
	 *              : Command.Argu1 - Software path 
	 */
	void SoftwareManager::PutOperationControl(GUI_COMMAND Command)
	{
		CallBackManager *p_CallBackManager = NULL;
		p_CallBackManager = CallBackManager::GetInstance();

		int CPUIndex = 0;
		CPUIndex = FindCPU(Command.Argu1);	

		if(CPUIndex != -1){
		
			LoadSoftware(CPUIndex, Command.Argu2);
			// assembly code displayer
			SetSoftwareDisplayer(CPUIndex, Command.Argu2);
			SetSoftwareProfiler(CPUIndex, Command.Argu2);

			p_CallBackManager->SendBackAllWhenStart();
		}
		else{
			printf("can not find %s cpu \n", Command.Argu1);
		}
	}

	/*
	 * function    	: LoadSoftware 
	 * design	      : load software for this cpu 
	 * param	      : CPUIndex - index of CPU in member variable CPUs(vector<CPUInfo*>)
	 *              : SoftwarePath 
	 */
	void SoftwareManager::LoadSoftware(int CPUIndex, char *SoftwarePath)
	{
		p_SoftwareLoader = new SoftwareLoader();
		p_SoftwareLoader->LoadSoftware(CPUIndex, SoftwarePath);
		delete p_SoftwareLoader;
	}

	/*
	 * function    	: SetSoftwareDisplayer 
	 * design	      : set this displayer for this cpu 
	 *                this is used for displaying  assembly code
	 * param	      : CPUIndex - index of CPU in member variable CPUs(vector<CPUInfo*>)
	 *              : SoftwarePath 
	 */
	void SoftwareManager::SetSoftwareDisplayer(int CPUIndex, char *SoftwarePath)
	{

		// make SoftwareDisplayer
		SoftwareDisplayer *p_SoftwareDisplayer = NULL;
		p_SoftwareDisplayer = new SoftwareDisplayer();
		p_SoftwareDisplayer->StoreAssemblyCode(SoftwarePath);

		// set this displayer to the cpu that have CPUIndex 
		CPUInfo *pst_CPUInfo;
		pst_CPUInfo =	CPUs.at(CPUIndex);
		pst_CPUInfo->p_SoftwareDisplayer = p_SoftwareDisplayer;
	}

	/*
	 * function    	: DisplayAssemblyCode
	 * design	      : display assembly code 
	 */
	void SoftwareManager::DisplayAssemblyCode()
	{
		unsigned int dw_PC;

    ModuleListManager *p_ModuleListManager = NULL;
		p_ModuleListManager = ModuleListManager::GetInstance();
		dw_PC = p_ModuleListManager->FindModule(CPUs[0]->CPUName.c_str())->GetBDDI()->BDDIGetPCValue();
		printf("\n\nAssembly Code\n\n");
		CPUs[0]->p_SoftwareDisplayer->DisplayAssemblyCode(dw_PC);
		printf("\n\n");
	}

	/*
	 * function    	: SetSoftwareProfiler 
	 * design	      : set this profiler for this cpu 
	 *                this is used for profiling software 
	 * param	      : CPUIndex - index of CPU in member variable CPUs(vector<CPUInfo*>)
	 *              : SoftwarePath 
	 */
	void SoftwareManager::SetSoftwareProfiler(int CPUIndex, char *SoftwarePath)
	{
		// make SoftwareProfiler
		SoftwareProfiler *p_SoftwareProfiler = NULL;
		p_SoftwareProfiler = new SoftwareProfiler(SoftwarePath);

		// set this profiler to the cpu that have CPUIndex 
		CPUInfo *pst_CPUInfo;
		pst_CPUInfo =	CPUs.at(CPUIndex);
		pst_CPUInfo->p_SoftwareProfiler = p_SoftwareProfiler;
	}

	/*
	 * function    	: PCAnalyzer 
	 * design	      : analyze current pc in this cpu
	 */
	void SoftwareManager::PCAnalyzer()
	{
		unsigned int dw_PC;

    ModuleListManager *p_ModuleListManager = NULL;
		p_ModuleListManager = ModuleListManager::GetInstance();
		dw_PC = p_ModuleListManager->FindModule(CPUs[0]->CPUName.c_str())->GetBDDI()->BDDIGetPCValue();
		CPUs[0]->p_SoftwareProfiler->PC_Analyzer(dw_PC);
	}

	string SoftwareManager::GetPC()
	{
		string PC;
		unsigned int dw_PC;
		char a_PC[128] = {0,};

    ModuleListManager *p_ModuleListManager = NULL;
		p_ModuleListManager = ModuleListManager::GetInstance();
		dw_PC = p_ModuleListManager->FindModule(CPUs[0]->CPUName.c_str())->GetBDDI()->BDDIGetPCValue();
		
	  sprintf(a_PC, "%x", dw_PC); 	
		PC = a_PC;

		return PC;
	}


	/*
	 * function    	: DisplayProfilingData
	 * design	      : display profiling data in this cpu
	 */
	void SoftwareManager::DisplayProfilingData()
	{
		CPUs[0]->p_SoftwareProfiler->Summary_Display();
	}

	SoftwareProfiler* SoftwareManager::GetSoftwareProfiler()
	{
		return CPUs[0]->p_SoftwareProfiler;
	}

	SoftwareDisplayer* SoftwareManager::GetSoftwareDisplayer()
	{
		return CPUs[0]->p_SoftwareDisplayer;
	}
	/*
	 * function    	: AddConnectionInfo
	 * design	      : add connected module to this cpu
	 * param	      : CPUName - this cpu is connected with this module
	 *              : ConnectedModuleName - this module is connected with this cpu
	 */
	void SoftwareManager::AddConnectionInfo(string CPUName, string ConnectedModuleName)
	{

		CPUInfo *pst_CPUInfo;
		vector<string> *p_ConnectedModules;

		int CPUIndex = 0;

		// Find CPU Name in CPUs vector	
		CPUIndex = FindCPU(CPUName);

		// Find
		if(CPUIndex != -1){

			pst_CPUInfo =	CPUs.at(CPUIndex);

			p_ConnectedModules = &(pst_CPUInfo->ConnectedModules);
			p_ConnectedModules->push_back(ConnectedModuleName);      
		}
		// can not find
		else{
			pst_CPUInfo = new CPUInfo();
			pst_CPUInfo->CPUName = CPUName;

			p_ConnectedModules = &(pst_CPUInfo->ConnectedModules);
			p_ConnectedModules->push_back(ConnectedModuleName);      

			CPUs.push_back(pst_CPUInfo);
		}
	}

	/*
	 * function    	: FindCPU
	 * design	      : find cpu in member variable CPUs(vector<CPUInfo*>)
	 * param	      : CPUName 
	 */
	int SoftwareManager::FindCPU(string CPUName)
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
	 * function    	: GetCPUInfo 
	 * design	      : get member variable CPUs(vector<CPUInfo*>)
	 * return       : vector<CPUInfo*>*
	 */
	vector<CPUInfo*>* SoftwareManager::GetCPUInfo()
	{
		return &CPUs;
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	SoftwareManager* SoftwareManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&SoftwareManagerInstanceMutex); 

		if( _SoftwareManager == NULL ){
			_SoftwareManager = new SoftwareManager();
		}
		// unlock
		pthread_mutex_unlock(&SoftwareManagerInstanceMutex);

		return _SoftwareManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete SoftwareManager instance 
	 */
	void SoftwareManager::DeleteInstance()
	{	
		delete _SoftwareManager;
		_SoftwareManager = NULL;
	}

	/*
	 * function 	: SoftwareManager 
	 * design	    : Constructor 
	 */
	SoftwareManager::SoftwareManager()
	{
	}

	/*
	 * function 	: ~SoftwareManager
	 * design	    : Destructor
	 */
	SoftwareManager::~SoftwareManager()
	{
	}
}
