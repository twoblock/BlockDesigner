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
#include "ModuleListManager.h"

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
		LoadSoftware(Command.Argu1, Command.Argu2);
	}

	void SoftwareLoadingManager::LoadSoftware(char *CPUName, char *SoftwarePath)
	{
		FILE* Command;
		char a_Command[1024];

		int CPUIndex = 0;
		CPUIndex = FindCPU(CPUName);

		if(CPUIndex != -1){

			// get hex file from elf file
			// elf file : SoftwarePath
			// hex file : BDsoftware.txt
			sprintf( a_Command, "arm-linux-gnueabi-objcopy -O verilog %s BDsoftware.txt", SoftwarePath);
			Command = popen( a_Command , "r");
			fclose(Command);

			// This CPU load BDsoftware.txt values
			ProcessLoading(CPUIndex);

			// After software loading, remove BDsoftware.txt
			popen("rm BDsoftware.txt", "w");
		}
		else{
			printf("%s cpu Fail to load software\n", CPUName);
		}
	}

	/*
	 * function    	: 
	 * design	      : 
	 * param	      : 
	 * caller		    : 
	 */
	void SoftwareLoadingManager::ProcessLoading(int CPUIndex)
	{
		BDDI *p_BDDI = NULL; 
		ReturnType_Of_Parsing ReturnType;   
		UINT32 dw_Value = 0;
		UINT32 dw_Address = 0;
		UINT32 dw_StartAddress = 1;
		UINT32 dw_EndAddress = 0;
		UINT32 dw_AddressSize = 0;
		UINT32 dw_RestOfMem = 0;

		FILE* fHex;
		fHex = fopen("BDsoftware.txt", "rt");

		if(fHex == NULL)	{
			printf("Hex file open error\n");
		}
		// binary loading
		else	{
			while(1){		
				ReturnType = ParsingHexFile(fHex, &dw_Value);	

				if(ReturnType == Binary){
					p_BDDI->BDDISetMemoryAddressValue(dw_Address, dw_Value);
					dw_Address += 4;
				}
				else if(ReturnType == Address){
					dw_Address = dw_Value;

					if(dw_StartAddress <= dw_Address && dw_Address < dw_EndAddress)
						continue;
					else{
						p_BDDI = FindTargetMemoryBDDI(CPUIndex, dw_Address);
			
						dw_StartAddress = p_BDDI->BDDIGetMemoryBaseAddress();
						dw_AddressSize = p_BDDI->BDDIGetMemoryAddressSize();
						dw_EndAddress = dw_StartAddress + dw_AddressSize;
					}
				}
				else if(ReturnType == End_Of_File)
					break;
			}
		}

		// memory initializing
		//for(dw_RestOfMem = dw_Address; dw_RestOfMem<(262144*4); dw_RestOfMem+=4)	{
			//p_BDDI->BDDISetMemoryAddressValue(dw_RestOfMem, 0);
		//}

		fclose(fHex);
	}

	/*
	 * function    	: 
	 * design	      : 
	 * param	      : 
	 * caller		    : 
	 */
	BDDI* SoftwareLoadingManager::FindTargetMemoryBDDI(int CPUIndex, UINT32 Address)
	{
		sc_module *p_ConnectedSCmodule = NULL;

		// declare variables to check address range of memory
		BDDI *p_BDDITemp = NULL;
		BDDI *p_BDDITargetMemory = NULL;
		UINT32 dw_StartAddress = 0;
		UINT32 dw_EndAddress = 0;
		UINT32 dw_Size = 0;

		// ready to iterate sc_modules connected to cpu 
		vector<string>::iterator FirstModule = CPUs[CPUIndex]->ConnectedModules.begin();
		vector<string>::iterator LastModule = CPUs[CPUIndex]->ConnectedModules.end();
		vector<string>::iterator IndexOfModule = FirstModule;

		/********************************************
		 * Iterate sc_modules connected to cpu
		 ********************************************/
		for(IndexOfModule = FirstModule; IndexOfModule != LastModule; ++IndexOfModule){   

			p_ConnectedSCmodule = p_ModuleListManager->FindModule((*IndexOfModule).c_str());

			// exception handling of NULL pointer access 
			if(p_ConnectedSCmodule != NULL){

				/******* bus ******/
				if(strcmp(p_ConnectedSCmodule->GetBDDI()->BDDIGetModuleType(), "bus") == 0){		

					//p_BDDITemp = SearchTargetMemoryInBus(p_BusMemoryMap);			
					p_BDDITemp = SearchTargetMemoryInBus(p_ConnectedSCmodule);			
			
					// if Find target memory, return!	
					if(p_BDDITemp != NULL){
						p_BDDITargetMemory = p_BDDITemp;
						return p_BDDITargetMemory;
					}					
				}
				/******* memory ******/
				else if(strcmp(p_ConnectedSCmodule->GetBDDI()->BDDIGetModuleType(), "mem") == 0){		
					p_BDDITemp = p_ConnectedSCmodule->GetBDDI();
			
					// Ger memory address range
					dw_StartAddress =	p_BDDITemp->BDDIGetMemoryBaseAddress();
					dw_Size =	p_BDDITemp->BDDIGetMemoryAddressSize();
					dw_EndAddress =	dw_StartAddress + dw_Size;

					// if range is right, return memory!	
					if(dw_StartAddress <= Address && Address < dw_EndAddress){
						p_BDDITargetMemory = p_ConnectedSCmodule->GetBDDI();
						return p_BDDITargetMemory;
					}
					else
						p_BDDITemp = NULL;
				}
			}
		}
		return NULL;
	}

	BDDI* SoftwareLoadingManager::SearchTargetMemoryInBus(sc_module *SCmodule)
	{
		// declare variables that relate to memory map 
		BDMMI *p_BDMMI = NULL;
		vector<SlaveMemoryMap> *p_BusMemoryMap;
		sc_module *p_ConnectedSCmodule = NULL;

		// declare variables to check address range of memory
		BDDI *p_BDDITemp = NULL;
		BDDI *p_BDDITargetMemory = NULL;
		UINT32 dw_StartAddress = 0;
		UINT32 dw_EndAddress = 0;
		UINT32 dw_Size = 0;

	  p_BDMMI = SCmodule->GetBDMMI();	
		p_BusMemoryMap = p_BDMMI->GetMemoryMap();

		// ready to iterate sc_modules connected to bus
		vector<SlaveMemoryMap>::iterator FirstSlave= p_BusMemoryMap->begin();
		vector<SlaveMemoryMap>::iterator LastSlave= p_BusMemoryMap->end();
		vector<SlaveMemoryMap>::iterator IndexOfSlave= FirstSlave;

		/********************************************
		 * Iterate sc_modules connected to bus
		 ********************************************/ 
		for(IndexOfSlave = FirstSlave; IndexOfSlave!= LastSlave; ++IndexOfSlave){   

			p_ConnectedSCmodule = p_ModuleListManager->FindModule((*IndexOfSlave).SlaveModule);

			// exception handling of NULL pointer access 
			if(p_ConnectedSCmodule != NULL){

				/******* bus ******/
				if(strcmp(p_ConnectedSCmodule->GetBDDI()->BDDIGetModuleType(), "bus") == 0){		

					// Find target memory in Bus memory map
					p_BDDITemp = SearchTargetMemoryInBus(p_ConnectedSCmodule);			
		
					// if Find target memory, return!	
					if(p_BDDITemp != NULL){
						p_BDDITargetMemory = p_BDDITemp;
						return p_BDDITargetMemory;
					}					
				}
				/******* memory ******/
				else if(strcmp(p_ConnectedSCmodule->GetBDDI()->BDDIGetModuleType(), "mem") == 0){		
					p_BDDITemp = p_ConnectedSCmodule->GetBDDI();

					// Ger memory address range
					dw_StartAddress =	p_BDDITemp->BDDIGetMemoryBaseAddress();
					dw_Size =	p_BDDITemp->BDDIGetMemoryAddressSize();
					dw_EndAddress =	dw_StartAddress + dw_Size;

					// if range is right, return memory!	
					if(dw_StartAddress <= Address && Address < dw_EndAddress){
						p_BDDITargetMemory = p_BDDITemp;
						return p_BDDITargetMemory;
					}
					else
						p_BDDITemp = NULL;
				}
			}
		}
	
		return NULL;
	}

	ReturnType_Of_Parsing SoftwareLoadingManager::ParsingHexFile(FILE *HexFile, UINT32 *Value)
	{
		char a_Byte1[2] = {0,};
		char a_Byte2[2] = {0,};
		char a_Byte3[2] = {0,}; 
		char a_Byte4[2] = {0,};
		char a_Token[10] = {0,};
		char a_HexFourBytes[10] = {0,};
			
		UINT32 dw_HexValue = 0;

		while(1){
			if(fscanf(HexFile, "%s", a_Token) == EOF){
				*Value = 0;
				return End_Of_File;
			}
			else{
				if(a_Token[0] != '@'){
					strcpy(a_Byte4, a_Token);
					fscanf(HexFile, "%s", a_Byte3);
					fscanf(HexFile, "%s", a_Byte2);
					fscanf(HexFile, "%s", a_Byte1);

					strncpy(a_HexFourBytes, a_Byte1, 2);
					strncpy(a_HexFourBytes+2, a_Byte2, 2);
					strncpy(a_HexFourBytes+4, a_Byte3, 2);
					strncpy(a_HexFourBytes+6, a_Byte4, 2);
					a_HexFourBytes[8] = 0;

					dw_HexValue = strtoul(a_HexFourBytes, NULL, 16);
					*Value = dw_HexValue;

					return Binary;			
				}
				else{
					strncpy(a_HexFourBytes, (a_Token+1), 8);
					a_HexFourBytes[8] = 0;

					dw_HexValue = strtoul(a_HexFourBytes, NULL, 16);
					*Value = dw_HexValue;

					return Address;

				}
			}
		}
	}

	/*
	 * function    	: 
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
	 * function    	: 
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
		p_ModuleListManager = ModuleListManager::GetInstance();
	}

	/*
	 * function 	: ~SoftwareLoadingManager
	 * design	    : Destructor
	 */
	SoftwareLoadingManager::~SoftwareLoadingManager()
	{
	}
}
