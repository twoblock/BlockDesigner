
#ifndef __BufferManager_H__
#define __BufferManager_H__

#define BM_WRITE_LIMIT    0x00
#define BM_READ_LIMIT      0x04
#define BM_STACK_RESET   0x08
#define BM_STACK_WRSET  0x28
#define BM_STACK_RDSET   0x2C

#include "BlockDesigner.h"
#include <stdio.h>
#include <string.h>

// for BDDI
#include "BufferManager_BDDI.h"

SC_MODULE(BufferManager){

	/********** [port] **********/
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// Place instance declarations for the Ports here:
	BD_AHBPort_SS *AHBv2_spss;

	BDDI*						bddi;

	sc_in<unsigned int> bm_read_inc_SSlave;
	sc_in<unsigned int> bm_write_inc_SSlave;
	sc_in<unsigned int> BM_R_size_SSlave;
	sc_in<unsigned int> BM_W_size_SSlave;

	sc_out<unsigned int> BM_read_limit_SMaster;
	sc_out<unsigned int> BM_write_limit_SMaster;

	// parameters
	bool p_enableDbgMsg;
	uint64_t p_BM_addr_size;
	uint64_t p_BM_Base_addr;
	int p_Data_Bit_Width;

	/////// for test of BDDI ///////
	UINT8						hw_reg;
	UINT16					w_reg;
	UINT32					dw_reg;
	UINT64					lw_reg;
	bool						b_reg;
	UINT32					h_reg;	// hex
	float						f_reg;
	double					df_reg;
	char						a_reg[128];

	char						hw_par;
	short						w_par;
	int							dw_par;
	long long				lw_par;
	bool						b_par;
	UINT32					dw_paru;	// hex
	float						f_par;
	double					df_par;
	char						a_par[128];

	uint32_t r_BM_WRITE_LIMIT;
	uint32_t r_BM_READ_LIMIT;
	uint32_t r_BM_STACK_RESET;
	uint32_t r_BM_STACK_WRSET;
	uint32_t r_BM_STACK_RDSET;

	uint32_t _addr;
	bool _isWrite;
	bool _isDataCycleActive;
	int32_t _waitCycles; /* ssd */
	int32_t _currentWait;

	uint32_t r_BM_WRITE_LIMIT_temp; 
	uint32_t r_BM_READ_LIMIT_temp;	
	uint32_t r_BM_STACK_RESET_temp; 
	uint32_t r_BM_STACK_WRSET_temp;
	uint32_t r_BM_STACK_RDSET_temp;

	uint32_t  BM_W_size;
	uint32_t  BM_R_size;
	uint32_t  Flash_Read_Inc;
	uint32_t  Flash_Write_Inc;

	uint32_t PreFlash_Read_Inc;
	uint32_t PreFlash_Write_Inc;

	// overloaded methods for clocked components
	void communicate();
	void update();

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	~BufferManager();

	SC_CTOR(BufferManager)	{
		BDInit();

		SC_METHOD(communicate);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();

		SC_METHOD(update);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();
	}
};

#endif
