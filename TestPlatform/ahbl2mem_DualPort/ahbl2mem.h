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

#define MEM_ADDR_1MB_WIDTH		262144	// 1MB = 262144 words
#define MEM_ADDR_100MB_WIDTH	26214400	// 100MB = 26214400 words

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
	BD_AHBPort_SS *AHB_S0;
	BD_AHBPort_SS *AHB_S1;

	/********** [local variable] **********/
	// Registers to Store Address Phase Signals
	sc_signal<bool>		S0_REG_ADDR_PHASE_HSEL;
	sc_signal<bool>		S0_REG_ADDR_PHASE_HWRITE;
	sc_signal<UINT32>	S0_REG_ADDR_PHASE_HTRANS;
	sc_signal<UINT32>	S0_REG_ADDR_PHASE_HADDR;
	sc_signal<UINT32>	S0_REG_ADDR_PHASE_HSIZE;
	sc_signal<bool>		S0_REG_HREADYOUT;
	sc_signal<UINT32>	S0_REG_MEM_DELAY;
	sc_signal<UINT32>	S0_REG_MEM_NSEQ_WR_CNT;
	sc_signal<UINT32>	S0_REG_MEM_NSEQ_RD_CNT;
	sc_signal<UINT32>	S0_REG_MEM_SEQ_WR_CNT;
	sc_signal<UINT32>	S0_REG_MEM_SEQ_RD_CNT;
	sc_signal<UINT32>	S0_CUR_STATE;

	sc_signal<bool>		S0_NEXT_ADDR_PHASE_HSEL;
	sc_signal<bool>		S0_NEXT_ADDR_PHASE_HWRITE;
	sc_signal<UINT32>	S0_NEXT_ADDR_PHASE_HTRANS;
	sc_signal<UINT32>	S0_NEXT_ADDR_PHASE_HADDR;
	sc_signal<UINT32>	S0_NEXT_ADDR_PHASE_HSIZE;
	sc_signal<bool>		S0_NEXT_HREADYOUT;
	sc_signal<UINT32>	S0_NEXT_MEM_DELAY;
	sc_signal<UINT32>	S0_NEXT_MEM_NSEQ_WR_CNT;
	sc_signal<UINT32>	S0_NEXT_MEM_NSEQ_RD_CNT;
	sc_signal<UINT32>	S0_NEXT_MEM_SEQ_WR_CNT;
	sc_signal<UINT32>	S0_NEXT_MEM_SEQ_RD_CNT;
	sc_signal<UINT32>	S0_NEXT_STATE;

	sc_signal<UINT32>	S0_dw_WE;

	// Registers to Store Address Phase Signals
	sc_signal<bool>		S1_REG_ADDR_PHASE_HSEL;
	sc_signal<bool>		S1_REG_ADDR_PHASE_HWRITE;
	sc_signal<UINT32>	S1_REG_ADDR_PHASE_HTRANS;
	sc_signal<UINT32>	S1_REG_ADDR_PHASE_HADDR;
	sc_signal<UINT32>	S1_REG_ADDR_PHASE_HSIZE;
	sc_signal<bool>		S1_REG_HREADYOUT;
	sc_signal<UINT32>	S1_REG_MEM_DELAY;
	sc_signal<UINT32>	S1_REG_MEM_NSEQ_WR_CNT;
	sc_signal<UINT32>	S1_REG_MEM_NSEQ_RD_CNT;
	sc_signal<UINT32>	S1_REG_MEM_SEQ_WR_CNT;
	sc_signal<UINT32>	S1_REG_MEM_SEQ_RD_CNT;
	sc_signal<UINT32>	S1_CUR_STATE;

	sc_signal<bool>		S1_NEXT_ADDR_PHASE_HSEL;
	sc_signal<bool>		S1_NEXT_ADDR_PHASE_HWRITE;
	sc_signal<UINT32>	S1_NEXT_ADDR_PHASE_HTRANS;
	sc_signal<UINT32>	S1_NEXT_ADDR_PHASE_HADDR;
	sc_signal<UINT32>	S1_NEXT_ADDR_PHASE_HSIZE;
	sc_signal<bool>		S1_NEXT_HREADYOUT;
	sc_signal<UINT32>	S1_NEXT_MEM_DELAY;
	sc_signal<UINT32>	S1_NEXT_MEM_NSEQ_WR_CNT;
	sc_signal<UINT32>	S1_NEXT_MEM_NSEQ_RD_CNT;
	sc_signal<UINT32>	S1_NEXT_MEM_SEQ_WR_CNT;
	sc_signal<UINT32>	S1_NEXT_MEM_SEQ_RD_CNT;
	sc_signal<UINT32>	S1_NEXT_STATE;

	sc_signal<UINT32>	S1_dw_WE;


	FILE			*fHex;
	FILE			*fLog;

	// Memory Array
	//UINT32			memory[MEM_ADDR_1MB_WIDTH];
	unsigned int *memory;

	// Address Parameter
	UINT32					base_addr;
	UINT32					addr_size;

	BDDI*						bddi;

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	virtual ~AHBL2MEM();

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
	void S0_do_assign_hreadyout()	{
		AHB_S0->HREADYOUT = S0_REG_HREADYOUT;
	}

	void S0_do_pos_hclk_neg_hresetn()	{
		while(1)	{
			if(!HRESETn)	{
				S0_REG_ADDR_PHASE_HSEL = 0;
				S0_REG_ADDR_PHASE_HWRITE = 0;
				S0_REG_ADDR_PHASE_HTRANS = 0x0;
				S0_REG_ADDR_PHASE_HADDR = 0x0;
				S0_REG_ADDR_PHASE_HSIZE = 0x0;
				S0_REG_MEM_NSEQ_WR_CNT = 0;
				S0_REG_MEM_NSEQ_RD_CNT = 0;
				S0_REG_MEM_SEQ_WR_CNT = 0;
				S0_REG_MEM_SEQ_RD_CNT = 0;
				
				S0_REG_HREADYOUT = 1;
				S0_REG_MEM_DELAY = 0x0;
				S0_CUR_STATE = READY_1MB;

				AHB_S0->HRESP = 0;
			}
			else	{
				S0_REG_ADDR_PHASE_HSEL = S0_NEXT_ADDR_PHASE_HSEL;
				S0_REG_ADDR_PHASE_HWRITE = S0_NEXT_ADDR_PHASE_HWRITE;
				S0_REG_ADDR_PHASE_HTRANS = S0_NEXT_ADDR_PHASE_HTRANS;
				S0_REG_ADDR_PHASE_HADDR = S0_NEXT_ADDR_PHASE_HADDR;
				S0_REG_ADDR_PHASE_HSIZE = S0_NEXT_ADDR_PHASE_HSIZE;
				S0_REG_MEM_NSEQ_WR_CNT = S0_NEXT_MEM_NSEQ_WR_CNT;
				S0_REG_MEM_NSEQ_RD_CNT = S0_NEXT_MEM_NSEQ_RD_CNT;
				S0_REG_MEM_SEQ_WR_CNT = S0_NEXT_MEM_SEQ_WR_CNT;
				S0_REG_MEM_SEQ_RD_CNT = S0_NEXT_MEM_SEQ_RD_CNT;				
				S0_REG_HREADYOUT = S0_NEXT_HREADYOUT;
				S0_REG_MEM_DELAY = S0_NEXT_MEM_DELAY;
				S0_CUR_STATE = S0_NEXT_STATE;

				AHB_S0->HRESP = 0;
			}
			wait();
		}
	}

	void S0_do_assign_fsm()	{
		switch(S0_CUR_STATE)	{
			case READY_1MB : 
				if(AHB_S0->HREADY && AHB_S0->HSEL && (AHB_S0->HTRANS == 0x2))		{
					S0_NEXT_HREADYOUT = 0;
					S0_NEXT_STATE = NONSEQ_WAIT_1MB;
						
					if(AHB_S0->HWRITE)	S0_NEXT_MEM_DELAY = MEM_1MB_NSEQ_WR_DELAY;
					else		S0_NEXT_MEM_DELAY = MEM_1MB_NSEQ_RD_DELAY;
				}
				else if(AHB_S0->HREADY && AHB_S0->HSEL && (AHB_S0->HTRANS == 0x3))	{
					S0_NEXT_HREADYOUT = 0;
					S0_NEXT_STATE = SEQ_WAIT_1MB;
					
					if(AHB_S0->HWRITE)	S0_NEXT_MEM_DELAY = MEM_1MB_SEQ_WR_DELAY;
					else		S0_NEXT_MEM_DELAY = MEM_1MB_SEQ_RD_DELAY;
				}
				else	{
					S0_NEXT_HREADYOUT = 1;
					S0_NEXT_STATE = READY_1MB;
					S0_NEXT_MEM_DELAY = 0;
				}
				break;
			case NONSEQ_WAIT_1MB :
				if(S0_REG_MEM_DELAY != 0)	{
					S0_NEXT_HREADYOUT = 0;
					S0_NEXT_STATE = NONSEQ_WAIT_1MB;
					S0_NEXT_MEM_DELAY = S0_REG_MEM_DELAY - 1;
				}
				else	{
					S0_NEXT_HREADYOUT = 0;
					S0_NEXT_STATE = DONE_1MB;
					S0_NEXT_MEM_DELAY = 0;
				}
				break;
			case SEQ_WAIT_1MB :
				if(S0_REG_MEM_DELAY != 0)	{
					S0_NEXT_HREADYOUT = 0;
					S0_NEXT_STATE = SEQ_WAIT_1MB;
					S0_NEXT_MEM_DELAY = S0_REG_MEM_DELAY - 1;
				}
				else	{
					S0_NEXT_HREADYOUT = 0;
					S0_NEXT_STATE = DONE_1MB;
					S0_NEXT_MEM_DELAY = 0;
				}
				break;
			case DONE_1MB :
				S0_NEXT_HREADYOUT = 1;
				S0_NEXT_STATE = READY_1MB;
				S0_NEXT_MEM_DELAY = 0;
				break;
			default :
				S0_NEXT_HREADYOUT = 1;
				S0_NEXT_STATE = READY_1MB;
				S0_NEXT_MEM_DELAY = 0;
				break;
		}	// switch
	}	// process

	void S0_do_assign_address_phase()	{
		if((S0_CUR_STATE == READY_1MB) && AHB_S0->HREADY && AHB_S0->HSEL)	{
			S0_NEXT_ADDR_PHASE_HSEL = AHB_S0->HSEL;
			S0_NEXT_ADDR_PHASE_HWRITE = AHB_S0->HWRITE;
			S0_NEXT_ADDR_PHASE_HTRANS = AHB_S0->HTRANS;
			S0_NEXT_ADDR_PHASE_HADDR = AHB_S0->HADDR - base_addr;
			S0_NEXT_ADDR_PHASE_HSIZE = AHB_S0->HSIZE;
#if	DEBUG_MEM
printf("[addr_phase_receive] haddr : %08x, next addr : %08x, cur addr : %08x\n", (UINT32)AHB_S0->HADDR, (UINT32)S0_NEXT_ADDR_PHASE_HADDR, (UINT32)S0_REG_ADDR_PHASE_HADDR);
#endif	// DEBUG_MEM

			if(AHB_S0->HWRITE && (AHB_S0->HTRANS == 0x2))	S0_NEXT_MEM_NSEQ_WR_CNT = S0_REG_MEM_NSEQ_WR_CNT + 1;
			else				S0_NEXT_MEM_NSEQ_WR_CNT = S0_REG_MEM_NSEQ_WR_CNT;
			if(!AHB_S0->HWRITE && (AHB_S0->HTRANS == 0x2))	S0_NEXT_MEM_NSEQ_RD_CNT = S0_REG_MEM_NSEQ_RD_CNT + 1;
			else				S0_NEXT_MEM_NSEQ_RD_CNT = S0_REG_MEM_NSEQ_RD_CNT;
			if(AHB_S0->HWRITE && (AHB_S0->HTRANS == 0x3))	S0_NEXT_MEM_SEQ_WR_CNT = S0_REG_MEM_SEQ_WR_CNT + 1;
			else				S0_NEXT_MEM_SEQ_WR_CNT = S0_REG_MEM_SEQ_WR_CNT;
			if(!AHB_S0->HWRITE && (AHB_S0->HTRANS == 0x3))	S0_NEXT_MEM_SEQ_RD_CNT = S0_REG_MEM_SEQ_RD_CNT + 1;
			else				S0_NEXT_MEM_SEQ_RD_CNT = S0_REG_MEM_SEQ_RD_CNT;
		}
		else	{
			S0_NEXT_ADDR_PHASE_HSEL = S0_REG_ADDR_PHASE_HSEL;
			S0_NEXT_ADDR_PHASE_HWRITE = S0_REG_ADDR_PHASE_HWRITE;
			S0_NEXT_ADDR_PHASE_HTRANS = S0_REG_ADDR_PHASE_HTRANS;
			S0_NEXT_ADDR_PHASE_HADDR = S0_REG_ADDR_PHASE_HADDR;
			S0_NEXT_ADDR_PHASE_HSIZE = S0_REG_ADDR_PHASE_HSIZE;
#if	DEBUG_MEM
printf("[addr_phase_keep] next addr : %08x, cur addr : %08x\n", (UINT32)S0_NEXT_ADDR_PHASE_HADDR, (UINT32)S0_REG_ADDR_PHASE_HADDR);
#endif	// DEBUG_MEM
		}
	}

	void S0_do_byte_enable()	{
		S0_dw_WE = ByteEnable((UINT32)S0_REG_ADDR_PHASE_HADDR, (UINT32)S0_REG_ADDR_PHASE_HSIZE);
	}
	
	void S0_do_write_to_memory_pos_hclk()	{
		while(1)	{
			if(S0_REG_ADDR_PHASE_HSEL && 
				S0_REG_ADDR_PHASE_HWRITE && 
				(S0_REG_ADDR_PHASE_HTRANS & 0x2) && 
				(S0_CUR_STATE == DONE_1MB))	{
				WriteToMemory((UINT32)S0_REG_ADDR_PHASE_HADDR, (UINT32)AHB_S0->HWDATA, (UINT32)S0_dw_WE);
			}

			wait();
		}
	}

	void S0_do_assign_read_data()	{
		AHB_S0->HRDATA = ReadFromMemory((UINT32)S0_REG_ADDR_PHASE_HADDR);
#if	DEBUG_MEM
printf("[read_rom] addr : %08x, transfer : %08x, hrdata : %08x\n", (UINT32)S0_REG_ADDR_PHASE_HADDR, ReadFromMemory((UINT32)S0_REG_ADDR_PHASE_HADDR), (UINT32)AHB_S0->HRDATA);
#endif	// DEBUG_MEM
	}


	/********** [process function] **********/
	void S1_do_assign_hreadyout()	{
		AHB_S1->HREADYOUT = S1_REG_HREADYOUT;
	}

	void S1_do_pos_hclk_neg_hresetn()	{
		while(1)	{
			if(!HRESETn)	{
				S1_REG_ADDR_PHASE_HSEL = 0;
				S1_REG_ADDR_PHASE_HWRITE = 0;
				S1_REG_ADDR_PHASE_HTRANS = 0x0;
				S1_REG_ADDR_PHASE_HADDR = 0x0;
				S1_REG_ADDR_PHASE_HSIZE = 0x0;
				S1_REG_MEM_NSEQ_WR_CNT = 0;
				S1_REG_MEM_NSEQ_RD_CNT = 0;
				S1_REG_MEM_SEQ_WR_CNT = 0;
				S1_REG_MEM_SEQ_RD_CNT = 0;
				
				S1_REG_HREADYOUT = 1;
				S1_REG_MEM_DELAY = 0x0;
				S1_CUR_STATE = READY_1MB;

				AHB_S1->HRESP = 0;
			}
			else	{
				S1_REG_ADDR_PHASE_HSEL = S1_NEXT_ADDR_PHASE_HSEL;
				S1_REG_ADDR_PHASE_HWRITE = S1_NEXT_ADDR_PHASE_HWRITE;
				S1_REG_ADDR_PHASE_HTRANS = S1_NEXT_ADDR_PHASE_HTRANS;
				S1_REG_ADDR_PHASE_HADDR = S1_NEXT_ADDR_PHASE_HADDR;
				S1_REG_ADDR_PHASE_HSIZE = S1_NEXT_ADDR_PHASE_HSIZE;
				S1_REG_MEM_NSEQ_WR_CNT = S1_NEXT_MEM_NSEQ_WR_CNT;
				S1_REG_MEM_NSEQ_RD_CNT = S1_NEXT_MEM_NSEQ_RD_CNT;
				S1_REG_MEM_SEQ_WR_CNT = S1_NEXT_MEM_SEQ_WR_CNT;
				S1_REG_MEM_SEQ_RD_CNT = S1_NEXT_MEM_SEQ_RD_CNT;				
				S1_REG_HREADYOUT = S1_NEXT_HREADYOUT;
				S1_REG_MEM_DELAY = S1_NEXT_MEM_DELAY;
				S1_CUR_STATE = S1_NEXT_STATE;

				AHB_S1->HRESP = 0;
			}
			wait();
		}
	}

	void S1_do_assign_fsm()	{
		switch(S1_CUR_STATE)	{
			case READY_1MB : 
				if(AHB_S1->HREADY && AHB_S1->HSEL && (AHB_S1->HTRANS == 0x2))		{
					S1_NEXT_HREADYOUT = 0;
					S1_NEXT_STATE = NONSEQ_WAIT_1MB;
						
					if(AHB_S1->HWRITE)	S1_NEXT_MEM_DELAY = MEM_1MB_NSEQ_WR_DELAY;
					else		S1_NEXT_MEM_DELAY = MEM_1MB_NSEQ_RD_DELAY;
				}
				else if(AHB_S1->HREADY && AHB_S1->HSEL && (AHB_S1->HTRANS == 0x3))	{
					S1_NEXT_HREADYOUT = 0;
					S1_NEXT_STATE = SEQ_WAIT_1MB;
					
					if(AHB_S1->HWRITE)	S1_NEXT_MEM_DELAY = MEM_1MB_SEQ_WR_DELAY;
					else		S1_NEXT_MEM_DELAY = MEM_1MB_SEQ_RD_DELAY;
				}
				else	{
					S1_NEXT_HREADYOUT = 1;
					S1_NEXT_STATE = READY_1MB;
					S1_NEXT_MEM_DELAY = 0;
				}
				break;
			case NONSEQ_WAIT_1MB :
				if(S1_REG_MEM_DELAY != 0)	{
					S1_NEXT_HREADYOUT = 0;
					S1_NEXT_STATE = NONSEQ_WAIT_1MB;
					S1_NEXT_MEM_DELAY = S1_REG_MEM_DELAY - 1;
				}
				else	{
					S1_NEXT_HREADYOUT = 0;
					S1_NEXT_STATE = DONE_1MB;
					S1_NEXT_MEM_DELAY = 0;
				}
				break;
			case SEQ_WAIT_1MB :
				if(S1_REG_MEM_DELAY != 0)	{
					S1_NEXT_HREADYOUT = 0;
					S1_NEXT_STATE = SEQ_WAIT_1MB;
					S1_NEXT_MEM_DELAY = S1_REG_MEM_DELAY - 1;
				}
				else	{
					S1_NEXT_HREADYOUT = 0;
					S1_NEXT_STATE = DONE_1MB;
					S1_NEXT_MEM_DELAY = 0;
				}
				break;
			case DONE_1MB :
				S1_NEXT_HREADYOUT = 1;
				S1_NEXT_STATE = READY_1MB;
				S1_NEXT_MEM_DELAY = 0;
				break;
			default :
				S1_NEXT_HREADYOUT = 1;
				S1_NEXT_STATE = READY_1MB;
				S1_NEXT_MEM_DELAY = 0;
				break;
		}	// switch
	}	// process

	void S1_do_assign_address_phase()	{
		if((S1_CUR_STATE == READY_1MB) && AHB_S1->HREADY && AHB_S1->HSEL)	{
			S1_NEXT_ADDR_PHASE_HSEL = AHB_S1->HSEL;
			S1_NEXT_ADDR_PHASE_HWRITE = AHB_S1->HWRITE;
			S1_NEXT_ADDR_PHASE_HTRANS = AHB_S1->HTRANS;
			S1_NEXT_ADDR_PHASE_HADDR = AHB_S1->HADDR - base_addr;
			S1_NEXT_ADDR_PHASE_HSIZE = AHB_S1->HSIZE;
#if	DEBUG_MEM
printf("[addr_phase_receive] haddr : %08x, next addr : %08x, cur addr : %08x\n", (UINT32)AHB_S1->HADDR, (UINT32)S1_NEXT_ADDR_PHASE_HADDR, (UINT32)S1_REG_ADDR_PHASE_HADDR);
#endif	// DEBUG_MEM

			if(AHB_S1->HWRITE && (AHB_S1->HTRANS == 0x2))	S1_NEXT_MEM_NSEQ_WR_CNT = S1_REG_MEM_NSEQ_WR_CNT + 1;
			else				S1_NEXT_MEM_NSEQ_WR_CNT = S1_REG_MEM_NSEQ_WR_CNT;
			if(!AHB_S1->HWRITE && (AHB_S1->HTRANS == 0x2))	S1_NEXT_MEM_NSEQ_RD_CNT = S1_REG_MEM_NSEQ_RD_CNT + 1;
			else				S1_NEXT_MEM_NSEQ_RD_CNT = S1_REG_MEM_NSEQ_RD_CNT;
			if(AHB_S1->HWRITE && (AHB_S1->HTRANS == 0x3))	S1_NEXT_MEM_SEQ_WR_CNT = S1_REG_MEM_SEQ_WR_CNT + 1;
			else				S1_NEXT_MEM_SEQ_WR_CNT = S1_REG_MEM_SEQ_WR_CNT;
			if(!AHB_S1->HWRITE && (AHB_S1->HTRANS == 0x3))	S1_NEXT_MEM_SEQ_RD_CNT = S1_REG_MEM_SEQ_RD_CNT + 1;
			else				S1_NEXT_MEM_SEQ_RD_CNT = S1_REG_MEM_SEQ_RD_CNT;
		}
		else	{
			S1_NEXT_ADDR_PHASE_HSEL = S1_REG_ADDR_PHASE_HSEL;
			S1_NEXT_ADDR_PHASE_HWRITE = S1_REG_ADDR_PHASE_HWRITE;
			S1_NEXT_ADDR_PHASE_HTRANS = S1_REG_ADDR_PHASE_HTRANS;
			S1_NEXT_ADDR_PHASE_HADDR = S1_REG_ADDR_PHASE_HADDR;
			S1_NEXT_ADDR_PHASE_HSIZE = S1_REG_ADDR_PHASE_HSIZE;
#if	DEBUG_MEM
printf("[addr_phase_keep] next addr : %08x, cur addr : %08x\n", (UINT32)S1_NEXT_ADDR_PHASE_HADDR, (UINT32)S1_REG_ADDR_PHASE_HADDR);
#endif	// DEBUG_MEM
		}
	}

	void S1_do_byte_enable()	{
		S1_dw_WE = ByteEnable((UINT32)S1_REG_ADDR_PHASE_HADDR, (UINT32)S1_REG_ADDR_PHASE_HSIZE);
	}
	
	void S1_do_write_to_memory_pos_hclk()	{
		while(1)	{
			if(S1_REG_ADDR_PHASE_HSEL && 
				S1_REG_ADDR_PHASE_HWRITE && 
				(S1_REG_ADDR_PHASE_HTRANS & 0x2) && 
				(S1_CUR_STATE == DONE_1MB))	{
				WriteToMemory((UINT32)S1_REG_ADDR_PHASE_HADDR, (UINT32)AHB_S1->HWDATA, (UINT32)S1_dw_WE);
			}

			wait();
		}
	}

	void S1_do_assign_read_data()	{
		AHB_S1->HRDATA = ReadFromMemory((UINT32)S1_REG_ADDR_PHASE_HADDR);
#if	DEBUG_MEM
printf("[read_rom] addr : %08x, transfer : %08x, hrdata : %08x\n", (UINT32)S1_REG_ADDR_PHASE_HADDR, ReadFromMemory((UINT32)S1_REG_ADDR_PHASE_HADDR), (UINT32)AHB_S1->HRDATA);
#endif	// DEBUG_MEM
	}


	SC_CTOR(AHBL2MEM)	{

		BDInit();

		/***** [initial condition] *****/
		//BinaryLoadingAndInitialize("CM0DS.txt");
		//BinaryLoadingAndInitialize("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.txt");
		
		/***** [process enrollment] *****/
		SC_METHOD(S0_do_assign_hreadyout);
		sensitive << S0_REG_HREADYOUT;

		SC_THREAD(S0_do_pos_hclk_neg_hresetn);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();	
	
		SC_METHOD(S0_do_assign_fsm);
		sensitive << S0_CUR_STATE;
		sensitive << AHB_S0->HREADY;
		sensitive << AHB_S0->HSEL;
		sensitive << AHB_S0->HTRANS;
		sensitive << AHB_S0->HWRITE;

		SC_METHOD(S0_do_assign_address_phase);
		sensitive << S0_CUR_STATE;
		sensitive << AHB_S0->HREADY;
		sensitive << AHB_S0->HSEL;
		sensitive << AHB_S0->HWRITE;
		sensitive << AHB_S0->HTRANS;
		sensitive << AHB_S0->HADDR;
		sensitive << AHB_S0->HSIZE;
		//sensitive << S0_REG_ADDR_PHASE_HSIZE;
		//sensitive << S0_REG_ADDR_PHASE_HSEL;
		//sensitive << S0_REG_ADDR_PHASE_HWRITE;
		//sensitive << S0_REG_ADDR_PHASE_HTRANS;
		//sensitive << S0_REG_ADDR_PHASE_HADDR;
	
		SC_METHOD(S0_do_byte_enable);
		sensitive << S0_REG_ADDR_PHASE_HADDR;
		sensitive << S0_REG_ADDR_PHASE_HSIZE;

		SC_THREAD(S0_do_write_to_memory_pos_hclk);
		sensitive << HCLK.pos();

		SC_METHOD(S0_do_assign_read_data);
		sensitive << S0_REG_ADDR_PHASE_HADDR;

		/***** [process enrollment] *****/
		SC_METHOD(S1_do_assign_hreadyout);
		sensitive << S1_REG_HREADYOUT;

		SC_THREAD(S1_do_pos_hclk_neg_hresetn);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();	
	
		SC_METHOD(S1_do_assign_fsm);
		sensitive << S1_CUR_STATE;
		sensitive << AHB_S1->HREADY;
		sensitive << AHB_S1->HSEL;
		sensitive << AHB_S1->HTRANS;
		sensitive << AHB_S1->HWRITE;

		SC_METHOD(S1_do_assign_address_phase);
		sensitive << S1_CUR_STATE;
		sensitive << AHB_S1->HREADY;
		sensitive << AHB_S1->HSEL;
		sensitive << AHB_S1->HWRITE;
		sensitive << AHB_S1->HTRANS;
		sensitive << AHB_S1->HADDR;
		sensitive << AHB_S1->HSIZE;
		//sensitive << S1_REG_ADDR_PHASE_HSIZE;
		//sensitive << S1_REG_ADDR_PHASE_HSEL;
		//sensitive << S1_REG_ADDR_PHASE_HWRITE;
		//sensitive << S1_REG_ADDR_PHASE_HTRANS;
		//sensitive << S1_REG_ADDR_PHASE_HADDR;
	
		SC_METHOD(S1_do_byte_enable);
		sensitive << S1_REG_ADDR_PHASE_HADDR;
		sensitive << S1_REG_ADDR_PHASE_HSIZE;

		SC_THREAD(S1_do_write_to_memory_pos_hclk);
		sensitive << HCLK.pos();

		SC_METHOD(S1_do_assign_read_data);
		sensitive << S1_REG_ADDR_PHASE_HADDR;

	}
};

#endif	// __AHBL2MEM_H__
