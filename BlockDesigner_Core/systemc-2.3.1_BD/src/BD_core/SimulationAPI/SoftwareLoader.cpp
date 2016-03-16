//-----------------------------------------------------------------------------
// Design								: Software Loader
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareLoader.h
// Date	       					: 2016/3/2
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: help tool load software 
// ----------------------------------------------------------------------------

#include "SoftwareLoader.h"
#include "../manager/SoftwareManager.h"
#include "../manager/ModuleListManager.h"

namespace BDapi
{	
	/*
	 * function    	: LoadSoftware 
	 * design	      : load software for this cpu 
	 * param	      : CPUIndex 
	 *              : SoftwarePath 
	 */
	void SoftwareLoader::LoadSoftware(int CPUIndex, char *SoftwarePath)
	{
		FILE* Command;
		char a_Command[1024];

		// get hex file from elf file
		// elf file : SoftwarePath
		// hex file : BDsoftware.txt
		sprintf( a_Command, "arm-linux-gnueabi-objcopy -O verilog %s BDsoftware.txt", SoftwarePath);
		Command = popen( a_Command , "r");
		if(Command == NULL){
			perror("fail to execute popen function");
			return;
		}
		else{
			fclose(Command);
			// This CPU load BDsoftware.txt values
			ProcessLoading(CPUIndex);
			// After software loading, remove BDsoftware.txt
			popen("rm BDsoftware.txt", "w");
		}
	}

	/*
	 * function    	: 
	 * design	      : 
	 * param	      : 
	 * caller		    : 
	 */
	void SoftwareLoader::ProcessLoading(int CPUIndex)
	{
		sc_module *p_SCmodule = NULL; 
		ReturnType_Of_Parsing ReturnType;   

		UINT32 dw_Value = 0;
		UINT32 dw_Address = 0;
		UINT32 dw_StartAddress = 1;
		UINT32 dw_EndAddress = 0;
		UINT32 dw_AddressSize = 0;
		bool b_Check = false;

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
					PushBinaryToJson(p_SCmodule->name(), dw_Address, dw_Value);
					p_SCmodule->GetBDDI()->BDDISetMemoryAddressValue(dw_Address, dw_Value);
					dw_Address += 4;
				}
				else if(ReturnType == Address){

					if(b_Check == false)
						b_Check = true;
					else
						continue;

					dw_Address = dw_Value;

					if(dw_StartAddress <= dw_Address && dw_Address < dw_EndAddress)
						continue;
					else{
						p_SCmodule = FindTargetMemoryBDDI(CPUIndex, dw_Address);

						if(p_SCmodule == NULL){
							printf("can't find memory (Software Loader)\n");
							continue;
						}
						dw_StartAddress = p_SCmodule->GetBDDI()->BDDIGetMemoryBaseAddress();
						dw_AddressSize = p_SCmodule->GetBDDI()->BDDIGetMemoryAddressSize();
						dw_EndAddress = dw_StartAddress + dw_AddressSize;
					}
				}
				else if(ReturnType == End_Of_File)
					break;
			}
		}

		fclose(fHex);
	}

	/*
	 * function    	: FindTargetMemoryBDDI 
	 * design	      : find taget memory BDDI 
	 * param	      : CPUIndex - index of CPU in member variable CPUs(vector<CPUInfo*>)
	 *                           in SoftwareManager 
	 *              : Address - find memory based on this address
	 * rerturn      : sc_module* 
	 */
	sc_module* SoftwareLoader::FindTargetMemoryBDDI(int CPUIndex, UINT32 dw_Address)
	{
		sc_module *p_ConnectedSCmodule = NULL;

		// declare variables to check address range of memory
		sc_module *p_SCmoduleTemp = NULL;
		BDDI *p_BDDITemp = NULL;
		UINT32 dw_StartAddress = 0;
		UINT32 dw_EndAddress = 0;
		UINT32 dw_Size = 0;

		SoftwareManager *p_SoftwareManager = SoftwareManager::GetInstance();

		vector<CPUInfo*> *p_CPUs = p_SoftwareManager->GetCPUInfo();

		CPUInfo *p_CPUInfo = p_CPUs->at(CPUIndex);	

		// ready to iterate sc_modules connected to cpu 
		vector<string>::iterator FirstModule = p_CPUInfo->ConnectedModules.begin();
		vector<string>::iterator LastModule = p_CPUInfo->ConnectedModules.end();
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
					p_SCmoduleTemp = SearchTargetMemoryInBus(p_ConnectedSCmodule, dw_Address);			

					// if Find target memory, return!	
					if(p_SCmoduleTemp != NULL)
						return p_SCmoduleTemp;
				}
				/******* memory ******/
				else if(strcmp(p_ConnectedSCmodule->GetBDDI()->BDDIGetModuleType(), "mem") == 0){		
					p_BDDITemp = p_ConnectedSCmodule->GetBDDI();

					// Ger memory address range
					dw_StartAddress =	p_BDDITemp->BDDIGetMemoryBaseAddress();
					dw_Size =	p_BDDITemp->BDDIGetMemoryAddressSize();
					dw_EndAddress =	dw_StartAddress + dw_Size;

					// if range is right, return memory!	
					if(dw_StartAddress <= dw_Address && dw_Address < dw_EndAddress){
						return p_ConnectedSCmodule;
					}
					else
						p_BDDITemp = NULL;
				}
			}
		}
		return NULL;
	}

	/*
	 * function    	: SearchTargetMemoryInBus
	 * design	      : find taget memory in this bus( SCmodule ) 
	 * param	      : SCmodule - bus module 
	 * rerturn      : sc_module* 
	 */
	sc_module* SoftwareLoader::SearchTargetMemoryInBus(sc_module *SCmodule, UINT32 dw_Address)
	{
		// declare variables that relate to memory map 
		BDMMI *p_BDMMI = NULL;
		vector<SlaveMemoryMap> *p_BusMemoryMap;
		sc_module *p_ConnectedSCmodule = NULL;

		// declare variables to check address range of memory
		sc_module *p_SCmoduleTemp = NULL;
		BDDI *p_BDDITemp = NULL;
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
					p_SCmoduleTemp = SearchTargetMemoryInBus(p_ConnectedSCmodule, dw_Address);			
					// if Find target memory, return!	
					if(p_SCmoduleTemp != NULL)
						return p_SCmoduleTemp;
				}					
				/******* memory ******/
				else if(strcmp(p_ConnectedSCmodule->GetBDDI()->BDDIGetModuleType(), "mem") == 0){		
					p_BDDITemp = p_ConnectedSCmodule->GetBDDI();

					// Ger memory address range
					dw_StartAddress =	p_BDDITemp->BDDIGetMemoryBaseAddress();
					dw_Size =	p_BDDITemp->BDDIGetMemoryAddressSize();
					dw_EndAddress =	dw_StartAddress + dw_Size;

					// if range is right, return memory!	
					if(dw_StartAddress <= dw_Address && dw_Address < dw_EndAddress){
						return p_ConnectedSCmodule;
					}
					else
						p_BDDITemp = NULL;
				}
			}
		}
		return NULL;
	}

	/*
	 * function    	: ParsingHexFile 
	 * design	      : parse 4 byte from software hex file
	 * param	      : HexFile - file pointer
	 *              : Value - store 4 btye to this space(call by reference)  
	 * rerturn      : ReturnType_Of_Parsing - to check what kind of retuen value is	
	 *								 
	 *							  three kind
	 *                1. End of file
	 *							  2. Address
	 *                3. Binary( code or data )
	 */
	ReturnType_Of_Parsing SoftwareLoader::ParsingHexFile(FILE *HexFile, UINT32 *Value)
	{
		char a_Byte1[2] = {0,};
		char a_Byte2[2] = {0,};
		char a_Byte3[2] = {0,}; 
		char a_Byte4[2] = {0,};
		char a_Token[10] = {0,};
		char a_HexFourBytes[10] = {0,};

		UINT32 dw_HexValue = 0;

		while(1){
			// check end of file
			if(fscanf(HexFile, "%s", a_Token) == EOF){
				*Value = 0;
				return End_Of_File;
			}
			else{
				// if first character is not @, this means next data is binary(code or data) 
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

					// convert string to unsigned int
					dw_HexValue = strtoul(a_HexFourBytes, NULL, 16);
					// assign value
					*Value = dw_HexValue;

					return Binary;			
				}
				// if first character is @, this means next data is address 
				else{
					strncpy(a_HexFourBytes, (a_Token+1), 8);
					a_HexFourBytes[8] = 0;

					// convert string to unsigned int
					dw_HexValue = strtoul(a_HexFourBytes, NULL, 16);
					// assign value
					*Value = dw_HexValue;

					return Address;

				}
			}
		}
	}

	void SoftwareLoader::PushBinaryToJson(const char *ModuleInstanceName, unsigned int Address, unsigned int Value)
	{
		char a_Buffer[128] = {0,};

		unsigned int dw_Index= 0;
		unsigned int dw_MemoryNum = 0;
		dw_MemoryNum = MemoryViewList.size();

		for(dw_Index = 0; dw_Index < dw_MemoryNum; dw_Index++){
			if(strcmp(MemoryViewList[dw_Index]["instance_name"].asCString(), ModuleInstanceName) == 0)
				break;
		}

		memset(a_Buffer, 0, sizeof(a_Buffer));
		sprintf(a_Buffer, "0x%08x", Address);
		BinaryValue["address"] = a_Buffer;

		memset(a_Buffer, 0, sizeof(a_Buffer));
		sprintf(a_Buffer, "0x%08x", Value);
		BinaryValue["value"] = a_Buffer;

		if(dw_Index == dw_MemoryNum){
			MemoryView["instance_name"] = ModuleInstanceName;
			BinaryValueList.append(BinaryValue);
			MemoryView["binary_value"] = BinaryValueList;
			MemoryViewList.append(MemoryView);

			MemoryView.clear();
			BinaryValueList.clear();
			BinaryValue.clear();
		}
		else{
			MemoryViewList[dw_Index]["binary_value"].append(BinaryValue);
			BinaryValue.clear();
		}
	}

	/*
	 * function 	: GetMemoryView 
	 * design	    : get json string to show binary(software) on memory
	 */
	string SoftwareLoader::GetMemoryViewList()
	{
		Root_MemoryViewList["MemoryView"] = MemoryViewList;

		Json::StyledWriter writer;
		string StringBinary = writer.write(Root_MemoryViewList);
		cout<< endl << StringBinary << endl; 

		return StringBinary;
	}

	/*
	 * function 	: SoftwareLoader 
	 * design	    : Constructor 
	 */
	SoftwareLoader::SoftwareLoader()
	{
		p_ModuleListManager = ModuleListManager::GetInstance();
		Root_MemoryViewList.clear();
		MemoryViewList.clear();
		MemoryView.clear();
		BinaryValueList.clear();
		BinaryValue.clear();
	}

	/*
	 * function 	: ~SoftwareLoader
	 * design	    : Destructor
	 */
	SoftwareLoader::~SoftwareLoader()
	{
	}
}
