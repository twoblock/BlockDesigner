//-------------------------------------------------------------
// Design	: AHB Lite Memory
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: ahbl2mem.h
// Date		: 2016. 1. 5
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: 1MB Behavioral Memory
//-------------------------------------------------------------

#ifndef __AHBL2MEM_H__
#define __AHBL2MEM_H__

#define MEM_ADDR_1MB_WIDTH	262144	// 1MB = 262144 words

#define MEM_1MB_NSEQ_RD_DELAY	0
#define MEM_1MB_SEQ_RD_DELAY	0
#define MEM_1MB_NSEQ_WR_DELAY	0
#define MEM_1MB_SEQ_WR_DELAY	0

#define READY_1MB		0
#define NONSEQ_WAIT_1MB		1
#define SEQ_WAIT_1MB		2
#define DONE_1MB		3

#define ENDIAN_BIG		0	// 0 : little endian, 1 : big endian
#define DEBUG_MEM		0

#include "BlockDesigner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ahbl2mem_BDDI.h"

SC_MODULE(AHBL2MEM)	{
	/********** [port] **********/
	// Global Signal
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;
	
	//AHB-Lite Slave Interface Signal
	BD_AHBPort_SS *AHB_SS;

	/********** [local variable] **********/
	// Registers to Store Address Phase Signals
	sc_signal<bool>		REG_ADDR_PHASE_HSEL;
	sc_signal<bool>		REG_ADDR_PHASE_HWRITE;
	sc_signal<UINT32>	REG_ADDR_PHASE_HTRANS;
	sc_signal<UINT32>	REG_ADDR_PHASE_HADDR;
	sc_signal<UINT32>	REG_ADDR_PHASE_HSIZE;
	sc_signal<bool>		REG_HREADYOUT;
	sc_signal<UINT32>	REG_MEM_DELAY;
	sc_signal<UINT32>	REG_MEM_NSEQ_WR_CNT;
	sc_signal<UINT32>	REG_MEM_NSEQ_RD_CNT;
	sc_signal<UINT32>	REG_MEM_SEQ_WR_CNT;
	sc_signal<UINT32>	REG_MEM_SEQ_RD_CNT;
	sc_signal<UINT32>	CUR_STATE;

	sc_signal<bool>		NEXT_ADDR_PHASE_HSEL;
	sc_signal<bool>		NEXT_ADDR_PHASE_HWRITE;
	sc_signal<UINT32>	NEXT_ADDR_PHASE_HTRANS;
	sc_signal<UINT32>	NEXT_ADDR_PHASE_HADDR;
	sc_signal<UINT32>	NEXT_ADDR_PHASE_HSIZE;
	sc_signal<bool>		NEXT_HREADYOUT;
	sc_signal<UINT32>	NEXT_MEM_DELAY;
	sc_signal<UINT32>	NEXT_MEM_NSEQ_WR_CNT;
	sc_signal<UINT32>	NEXT_MEM_NSEQ_RD_CNT;
	sc_signal<UINT32>	NEXT_MEM_SEQ_WR_CNT;
	sc_signal<UINT32>	NEXT_MEM_SEQ_RD_CNT;
	sc_signal<UINT32>	NEXT_STATE;

	sc_signal<UINT32>	dw_WE;

	FILE			*fHex;
	FILE			*fLog;

	// Memory Array
	UINT32			memory[MEM_ADDR_1MB_WIDTH];

	// Address Parameter
	UINT32					base_addr;
	UINT32					addr_size;

	BDDI*						bddi;

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	/********** [member function] **********/
	UINT32 ByteEnable(UINT32 addr, UINT32 size)	{
		UINT32 dw_AddrTmp;
		UINT32 dw_SizeTmp;
		UINT32 dw_EnableState;

		dw_AddrTmp = addr & 0x3;		// address offset.
		dw_SizeTmp = (size & 0x7) << 2;		// transfer size.
		dw_EnableState = dw_SizeTmp | dw_AddrTmp;

		switch(dw_EnableState)	{
#if	ENDIAN_BIG
			case 0x8 :	return 0xF;	// word.	// case 5b'010_00 -> 4b'1111
			case 0x4 :	return 0xC;	// halfword.	// case 5b'001_00 -> 4b'1100
			case 0x6 :	return 0x3;	// halfword.	// case 5b'001_10 -> 4b'0011
			case 0x0 :	return 0x8;	// byte.	// case 5b'000_00 -> 4b'1000
			case 0x1 :	return 0x4;	// byte.	// case 5b'000_01 -> 4b'0100
			case 0x2 :	return 0x2;	// byte.	// case 5b'000_10 -> 4b'0010
			case 0x3 :	return 0x1;	// byte.	// case 5b'000_11 -> 4b'0001
#else	// little-endian (default)
			case 0x8 :	return 0xF;	// word.	// case 5b'010_00 -> 4b'1111
			case 0x4 :	return 0x3;	// halfword.	// case 5b'001_00 -> 4b'0011
			case 0x6 :	return 0xC;	// halfword.	// case 5b'001_10 -> 4b'1100
			case 0x0 :	return 0x1;	// byte.	// case 5b'000_00 -> 4b'0001
			case 0x1 :	return 0x2;	// byte.	// case 5b'000_01 -> 4b'0010
			case 0x2 :	return 0x4;	// byte.	// case 5b'000_10 -> 4b'0100
			case 0x3 :	return 0x8;	// byte.	// case 5b'000_11 -> 4b'1000
#endif
			default :	return 0x0;
		}
	}

	void WriteToMemory(UINT32 addr, UINT32 data, UINT32 we)		{
		UINT32 dw_A;
		UINT32 dw_D;
		UINT32 dw_C;

		dw_A = (addr >> 2) & 0x3FFFFFFF;
		dw_D = data;
		dw_C = memory[dw_A];
				
		if((we & 0x1))	dw_C = (dw_C & 0xFFFFFF00) | (dw_D & 0x000000FF);
		if((we & 0x2))	dw_C = (dw_C & 0xFFFF00FF) | (dw_D & 0x0000FF00);
		if((we & 0x4))	dw_C = (dw_C & 0xFF00FFFF) | (dw_D & 0x00FF0000);
		if((we & 0x8))	dw_C = (dw_C & 0x00FFFFFF) | (dw_D & 0xFF000000);

		//this->bddi->BDDIGenerateMemoryViewJsonFile(addr + base_addr, dw_C);

		memory[dw_A] = dw_C;
	}
	
	UINT32 ReadFromMemory(UINT32 addr)	{
		UINT32 dw_Address;

		dw_Address = (addr >> 2) & 0x3FFFFFFF;

		return memory[dw_Address];
	}

	/********** [process function] **********/
	void do_assign_hreadyout()	{
		AHB_SS->HREADYOUT = REG_HREADYOUT;
	}

	void do_pos_hclk_neg_hresetn()	{
		while(1)	{
			if(!HRESETn)	{
				REG_ADDR_PHASE_HSEL = 0;
				REG_ADDR_PHASE_HWRITE = 0;
				REG_ADDR_PHASE_HTRANS = 0x0;
				REG_ADDR_PHASE_HADDR = 0x0;
				REG_ADDR_PHASE_HSIZE = 0x0;
				REG_MEM_NSEQ_WR_CNT = 0;
				REG_MEM_NSEQ_RD_CNT = 0;
				REG_MEM_SEQ_WR_CNT = 0;
				REG_MEM_SEQ_RD_CNT = 0;
				
				REG_HREADYOUT = 1;
				REG_MEM_DELAY = 0x0;
				CUR_STATE = READY_1MB;

				AHB_SS->HRESP = 0;
			}
			else	{
				REG_ADDR_PHASE_HSEL = NEXT_ADDR_PHASE_HSEL;
				REG_ADDR_PHASE_HWRITE = NEXT_ADDR_PHASE_HWRITE;
				REG_ADDR_PHASE_HTRANS = NEXT_ADDR_PHASE_HTRANS;
				REG_ADDR_PHASE_HADDR = NEXT_ADDR_PHASE_HADDR;
				REG_ADDR_PHASE_HSIZE = NEXT_ADDR_PHASE_HSIZE;
				REG_MEM_NSEQ_WR_CNT = NEXT_MEM_NSEQ_WR_CNT;
				REG_MEM_NSEQ_RD_CNT = NEXT_MEM_NSEQ_RD_CNT;
				REG_MEM_SEQ_WR_CNT = NEXT_MEM_SEQ_WR_CNT;
				REG_MEM_SEQ_RD_CNT = NEXT_MEM_SEQ_RD_CNT;				
				REG_HREADYOUT = NEXT_HREADYOUT;
				REG_MEM_DELAY = NEXT_MEM_DELAY;
				CUR_STATE = NEXT_STATE;

				AHB_SS->HRESP = 0;
			}
			wait();
		}
	}

	void do_assign_fsm()	{
		switch(CUR_STATE)	{
			case READY_1MB : 
				if(AHB_SS->HREADY && AHB_SS->HSEL && (AHB_SS->HTRANS == 0x2))		{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = NONSEQ_WAIT_1MB;
						
					if(AHB_SS->HWRITE)	NEXT_MEM_DELAY = MEM_1MB_NSEQ_WR_DELAY;
					else		NEXT_MEM_DELAY = MEM_1MB_NSEQ_RD_DELAY;
				}
				else if(AHB_SS->HREADY && AHB_SS->HSEL && (AHB_SS->HTRANS == 0x3))	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = SEQ_WAIT_1MB;
					
					if(AHB_SS->HWRITE)	NEXT_MEM_DELAY = MEM_1MB_SEQ_WR_DELAY;
					else		NEXT_MEM_DELAY = MEM_1MB_SEQ_RD_DELAY;
				}
				else	{
					NEXT_HREADYOUT = 1;
					NEXT_STATE = READY_1MB;
					NEXT_MEM_DELAY = 0;
				}
				break;
			case NONSEQ_WAIT_1MB :
				if(REG_MEM_DELAY != 0)	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = NONSEQ_WAIT_1MB;
					NEXT_MEM_DELAY = REG_MEM_DELAY - 1;
				}
				else	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = DONE_1MB;
					NEXT_MEM_DELAY = 0;
				}
				break;
			case SEQ_WAIT_1MB :
				if(REG_MEM_DELAY != 0)	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = SEQ_WAIT_1MB;
					NEXT_MEM_DELAY = REG_MEM_DELAY - 1;
				}
				else	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = DONE_1MB;
					NEXT_MEM_DELAY = 0;
				}
				break;
			case DONE_1MB :
				NEXT_HREADYOUT = 1;
				NEXT_STATE = READY_1MB;
				NEXT_MEM_DELAY = 0;
				break;
			default :
				NEXT_HREADYOUT = 1;
				NEXT_STATE = READY_1MB;
				NEXT_MEM_DELAY = 0;
				break;
		}	// switch
	}	// process

	void do_assign_address_phase()	{
		if((CUR_STATE == READY_1MB) && AHB_SS->HREADY && AHB_SS->HSEL)	{
			NEXT_ADDR_PHASE_HSEL = AHB_SS->HSEL;
			NEXT_ADDR_PHASE_HWRITE = AHB_SS->HWRITE;
			NEXT_ADDR_PHASE_HTRANS = AHB_SS->HTRANS;
			NEXT_ADDR_PHASE_HADDR = AHB_SS->HADDR - base_addr;
			NEXT_ADDR_PHASE_HSIZE = AHB_SS->HSIZE;
#if	DEBUG_MEM
printf("[addr_phase_receive] haddr : %08x, next addr : %08x, cur addr : %08x\n", (UINT32)AHB_SS->HADDR, (UINT32)NEXT_ADDR_PHASE_HADDR, (UINT32)REG_ADDR_PHASE_HADDR);
#endif	// DEBUG_MEM

			if(AHB_SS->HWRITE && (AHB_SS->HTRANS == 0x2))	NEXT_MEM_NSEQ_WR_CNT = REG_MEM_NSEQ_WR_CNT + 1;
			else				NEXT_MEM_NSEQ_WR_CNT = REG_MEM_NSEQ_WR_CNT;
			if(!AHB_SS->HWRITE && (AHB_SS->HTRANS == 0x2))	NEXT_MEM_NSEQ_RD_CNT = REG_MEM_NSEQ_RD_CNT + 1;
			else				NEXT_MEM_NSEQ_RD_CNT = REG_MEM_NSEQ_RD_CNT;
			if(AHB_SS->HWRITE && (AHB_SS->HTRANS == 0x3))	NEXT_MEM_SEQ_WR_CNT = REG_MEM_SEQ_WR_CNT + 1;
			else				NEXT_MEM_SEQ_WR_CNT = REG_MEM_SEQ_WR_CNT;
			if(!AHB_SS->HWRITE && (AHB_SS->HTRANS == 0x3))	NEXT_MEM_SEQ_RD_CNT = REG_MEM_SEQ_RD_CNT + 1;
			else				NEXT_MEM_SEQ_RD_CNT = REG_MEM_SEQ_RD_CNT;
		}
		else	{
			NEXT_ADDR_PHASE_HSEL = REG_ADDR_PHASE_HSEL;
			NEXT_ADDR_PHASE_HWRITE = REG_ADDR_PHASE_HWRITE;
			NEXT_ADDR_PHASE_HTRANS = REG_ADDR_PHASE_HTRANS;
			NEXT_ADDR_PHASE_HADDR = REG_ADDR_PHASE_HADDR;
			NEXT_ADDR_PHASE_HSIZE = REG_ADDR_PHASE_HSIZE;
#if	DEBUG_MEM
printf("[addr_phase_keep] next addr : %08x, cur addr : %08x\n", (UINT32)NEXT_ADDR_PHASE_HADDR, (UINT32)REG_ADDR_PHASE_HADDR);
#endif	// DEBUG_MEM
		}
	}

	void do_byte_enable()	{
		dw_WE = ByteEnable((UINT32)REG_ADDR_PHASE_HADDR, (UINT32)REG_ADDR_PHASE_HSIZE);
	}
	
	void do_write_to_memory_pos_hclk()	{
		while(1)	{
			if(REG_ADDR_PHASE_HSEL && 
				REG_ADDR_PHASE_HWRITE && 
				(REG_ADDR_PHASE_HTRANS & 0x2) && 
				(CUR_STATE == DONE_1MB))	{
				WriteToMemory((UINT32)REG_ADDR_PHASE_HADDR, (UINT32)AHB_SS->HWDATA, (UINT32)dw_WE);
			}

			wait();
		}
	}

	void do_assign_read_data()	{
		AHB_SS->HRDATA = ReadFromMemory((UINT32)REG_ADDR_PHASE_HADDR);
#if	DEBUG_MEM
printf("[read_rom] addr : %08x, transfer : %08x, hrdata : %08x\n", (UINT32)REG_ADDR_PHASE_HADDR, ReadFromMemory((UINT32)REG_ADDR_PHASE_HADDR), (UINT32)AHB_SS->HRDATA);
#endif	// DEBUG_MEM
	}

	SC_CTOR(AHBL2MEM)	{

		BDInit();

		/***** [initial condition] *****/
		//BinaryLoadingAndInitialize("CM0DS.txt");
		//BinaryLoadingAndInitialize("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.txt");
		
		/***** [process enrollment] *****/
		SC_METHOD(do_assign_hreadyout);
		sensitive << REG_HREADYOUT;

		SC_THREAD(do_pos_hclk_neg_hresetn);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();	
	
		SC_METHOD(do_assign_fsm);
		sensitive << CUR_STATE;
		sensitive << AHB_SS->HREADY;
		sensitive << AHB_SS->HSEL;
		sensitive << AHB_SS->HTRANS;
		sensitive << AHB_SS->HWRITE;

		SC_METHOD(do_assign_address_phase);
		sensitive << CUR_STATE;
		sensitive << AHB_SS->HREADY;
		sensitive << AHB_SS->HSEL;
		sensitive << AHB_SS->HWRITE;
		sensitive << AHB_SS->HTRANS;
		sensitive << AHB_SS->HADDR;
		sensitive << AHB_SS->HSIZE;
		//sensitive << REG_ADDR_PHASE_HSIZE;
		//sensitive << REG_ADDR_PHASE_HSEL;
		//sensitive << REG_ADDR_PHASE_HWRITE;
		//sensitive << REG_ADDR_PHASE_HTRANS;
		//sensitive << REG_ADDR_PHASE_HADDR;
	
		SC_METHOD(do_byte_enable);
		sensitive << REG_ADDR_PHASE_HADDR;
		sensitive << REG_ADDR_PHASE_HSIZE;

		SC_THREAD(do_write_to_memory_pos_hclk);
		sensitive << HCLK.pos();

		SC_METHOD(do_assign_read_data);
		sensitive << REG_ADDR_PHASE_HADDR;
	}
};

#endif	// __AHBL2MEM_H__
