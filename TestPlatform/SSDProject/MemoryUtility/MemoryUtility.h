#ifndef __MemoryUtility_H__
#define __MemoryUtility_H__

// ************************************ //
// ***** Memory Utility FSM State ***** //
// ************************************ //
#define S_ILDE          		0x1
#define S_SRAM_MEMSET 		    0x2
#define S_DRAM_MEMSET 		 	0x3

#define S_MEMCOPY_Read  	    0x4
#define S_MEMCOPY_Write         0x5

#define S_SRAM_Search_Equal     0x6
#define S_DRAM_Search_Equal     0x7

#define S_SRAM_Search_MIN       0x8
#define S_DRAM_Search_MIN       0x9

#define S_SRAM_Search_MAX       0xa
#define S_DRAM_Search_MAX       0xb

// ************************************ //
// ***** Memory Utility Command  ****** //
// ************************************ //
#define MU_CMD_SET_REPT_SRAM		0x000
#define MU_CMD_SET_INCR_32_SRAM		0x010
#define MU_CMD_SET_INCR_16_SRAM		0x020
#define MU_CMD_SET_INCR_8_SRAM		0x030

#define MU_CMD_SET_REPT_DRAM		0x040
#define MU_CMD_SET_INCR_32_DRAM		0x050
#define MU_CMD_SET_INCR_16_DRAM		0x060
#define MU_CMD_SET_INCR_8_DRAM		0x070

#define MU_CMD_COPY					0x001

#define MU_CMD_FIND_SRAM			0x002
#define MU_CMD_FIND_DRAM			0x042

#define MU_CMD_SEARCH_MAX_SRAM		0x103
#define MU_CMD_SEARCH_MIN_SRAM		0x083
#define MU_CMD_SEARCH_EQU_SRAM		0x003

#define MU_CMD_SEARCH_MAX_DRAM		0x143
#define MU_CMD_SEARCH_MIN_DRAM		0x0C3
#define MU_CMD_SEARCH_EQU_DRAM		0x043

// ************************************ //
// ***** Memory Utility Register ****** //
// ************************************ //
#define MU_SRC_ADDR 0x010
#define MU_DST_ADDR 0x014
#define MU_VALUE    0x018
#define MU_SIZE     0x01c
#define MU_RESULT   0x020
#define MU_CMD      0x024
#define MU_UNITSTEP 0x030

// ************************************ //
// ***** Memory Utility Flag     ****** //
// ************************************ //
#define Write true
#define Read  false

#define MIN 0x1
#define MAX 0x2
#define EQUAL 0x3

#define Unit8    ( (0<<8) | 1 )
#define Unit16   ( (1<<8) | 2 )
#define Unit32	 ( (2<<8) | 4 )

#include "BlockDesigner.h"
#include <stdio.h>
#include <string.h>

// for BDDI
#include "MemoryUtility_BDDI.h"

SC_MODULE(MemoryUtility){

	/********** [port] **********/
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

  // SRAM
	BD_AHBPort_MM *SRAM_M_AHBv2_mpms;
  // DRAM
	BD_AHBPort_MM *DRAM_M_AHBv2_mpms;
	BD_AHBPort_SS *S_AHBv2_spss;

	BDDI*						bddi;

	// parameters
	uint32_t p_Base_Addr;
	uint32_t p_Addr_Size;
	bool p_enableDbgMsg;
	int p_Data_Bit_Width;

	// ************************************ //
	// ***** Memory Utility Register ****** //
	// ************************************ //

	uint32_t r_MU_SRC_ADDR;
	uint32_t r_MU_DST_ADDR;
	uint32_t r_MU_VALUE;
	uint32_t r_MU_SIZE;
	uint32_t r_MU_RESULT;
	uint32_t r_MU_CMD;
	uint32_t r_MU_UNITSTEP;

	uint32_t r_MU_SRC_ADDR_temp;
	uint32_t r_MU_DST_ADDR_temp;
	uint32_t r_MU_VALUE_temp;
	uint32_t r_MU_SIZE_temp;
	uint32_t r_MU_RESULT_temp;
	uint32_t r_MU_CMD_temp;
	uint32_t r_MU_UNITSTEP_temp;


	// ************************************ //
	// ******* AHB Bus Slave Side ********* //
	// ************************************ //

	int32_t c_Slave_waitCycles;  
	int32_t c_Slave_currentWait;
	uint32_t c_Slave_addr;
	bool c_Slave_isWrite;
	bool c_Slave_isDataCycleActive;


	// ************************************ //
	// ******* AHB Bus Master Side ******** //
	// ************************************ //

	int32_t  c_DRAM_wait_DataPhase;
	uint32_t c_DRAM_DataPhase;
	bool     c_DRAM_write;
	bool     c_DRAM_Granted;

	int32_t  c_SRAM_wait_DataPhase;
	uint32_t c_SRAM_DataPhase;
	bool     c_SRAM_write;
	bool     c_SRAM_Granted;

	uint32_t c_STATE ; 
	uint32_t c_STATE_temp ; 

	bool c_WriteBusrtComplete;
	bool c_ReadBusrtComplete;
	uint32_t c_Index;
	uint32_t c_Excute_Bytes;
	uint32_t c_Remain_Bytes;

	uint32_t c_Copy_Data[16];
	uint32_t c_Index_of_MinMaxEqual; 
	uint32_t c_Result_Index; 
	uint32_t c_Addr_of_MinMaxEqual; 
	uint32_t c_UnitStep;
	int32_t  c_Min;
	int32_t  c_Max;
	int32_t  c_Equal;

	bool Debug_Flag_Read;
	bool Debug_Flag_Write;

	void update();

	// ************************************ //
	// ***** Memory Utility Function ****** //
	// ************************************ //
	// SRAM Memset
	bool S_Memset_OneBurst(); 
	void S_MemsetBusrt_And_Select_NextState();

	// DRAM Memset
	bool D_Memset_OneBurst();
	void D_MemsetBusrt_And_Select_NextState();

	// SRAM Memcopy
	bool SRAM_Memcopy( uint32_t Addr );
	void S_MemCopy_Busrt_And_Select_NextState( uint32_t Addr );

	// DRAM Memcopy
	bool DRAM_Memcopy( uint32_t Addr );
	void D_MemCopy_Busrt_And_Select_NextState( uint32_t Addr );

	// SRAM MemSearch
	bool SRAM_MemSearch(uint32_t Min_Max_Equal);
	void S_MemSearch_Burst_And_Select_NextState(uint32_t Min_Max_Equal);  

	// DRAM MemSearch
	bool DRAM_MemSearch(uint32_t Min_Max_Equal);
	void D_MemSearch_Burst_And_Select_NextState(uint32_t Min_Max_Equal);  

	//////////////////////////////////////////

	// assist function
	void Select_NextState();
	void Compare_And_Select( int32_t Data, uint32_t Min_Max_Equal );

	void Calculate_Bytes();
	void Inc_64Bytes_Src();
	void Inc_64Bytes_Dst();

	// Initialize
	void SRAM_Init(bool IsWrite);
	void DRAM_Init(bool IsWrite);
	void Master_Init();
	void SRAM_DRAM_Master_Init();

	void Regitser_Initialize();

	// ************************************ //
	// *** Memory Utility Register I/O **** //
	// ************************************ //

	void RegisterIO();
	void WriteRegieter(uint32_t offset, uint32_t value);
	void ReadRegister(uint32_t offset);

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	~MemoryUtility();

	SC_CTOR(MemoryUtility)	{
		BDInit();

		SC_METHOD(update);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();
	}
};

#endif
