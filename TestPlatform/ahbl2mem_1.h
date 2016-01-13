//-------------------------------------------------------------
// Design	: AHB Lite Memory
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: ahbl2mem_1.h
// Date		: 2016. 1. 5
//-------------------------------------------------------------
// Copyright (C) 2015 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: 1MB Behavioral Memory
//-------------------------------------------------------------

#ifndef __AHBL2MEM_1_H__
#define __AHBL2MEM_1_H__

#define MEM_ADDR_1MB_WIDTH	262144	// 1MB = 262144 words

#define MEM_1MB_NSEQ_RD_DELAY	0
#define MEM_1MB_SEQ_RD_DELAY	0
#define MEM_1MB_NSEQ_WR_DELAY	0
#define MEM_1MB_SEQ_WR_DELAY	0

#define READY			0
#define NONSEQ_WAIT		1
#define SEQ_WAIT		2
#define DONE			3

#define ENDIAN_BIG		0	// 0 : little endian, 1 : big endian

#define BASE_ADDR		0x20000000

#include "systemc.h"
#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SC_MODULE(AHBL2MEM_1)	{
	/********** [port] **********/
	// Global Signal
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;
	
	//AHB-Lite Slave Interface Signal
	sc_in<bool>		HSEL;
	sc_in<bool>		HREADY;
	sc_in<UINT32>		HADDR;
	sc_in<UINT32>		HBURST;
	sc_in<UINT32>		HPROT;
	sc_in<UINT32>		HTRANS;
	sc_in<bool>		HWRITE;
	sc_in<UINT32>		HSIZE;
	sc_in<UINT32>		HWDATA;
	sc_out<bool>		HREADYOUT;
	sc_out<UINT32>		HRDATA;
	sc_out<bool>		HRESP;		// Always Okay (zero)

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

		memory[dw_A] = dw_C;
	}
	
	UINT32 ReadFromMemory(UINT32 addr)	{
		UINT32 dw_Address;

		dw_Address = (addr >> 2) & 0x3FFFFFFF;

		return memory[dw_Address];
	}

	void BinaryLoadingAndInitialize(const char *pHex)		{
		fHex = fopen(pHex, "rt");
		fLog = fopen("mem_log.txt", "wt");
		
		char aTemp1[5];
		char aTemp2[5];
		char aTemp3[5];
		char aTemp4[5];
		char aHexValue[20];
		
		UINT32 dwMemAddr = 0;
		UINT32 dwHexValue;
		UINT32 dwRestOfMem;

		if(fHex == NULL)	{
			printf("Hex file open error\n");
		}
		// binary loading
		else	{
			for(dwMemAddr=0; dwMemAddr<MEM_ADDR_1MB_WIDTH; dwMemAddr++)	{
				if(fscanf(fHex, "%s", aTemp4) != EOF)
				{
				}
				else break;

				fscanf(fHex, "%s", aTemp3);
				fscanf(fHex, "%s", aTemp2);
				fscanf(fHex, "%s", aTemp1);
				
				strcpy(aHexValue, aTemp1);
				strcat(aHexValue, aTemp2);
				strcat(aHexValue, aTemp3);
				strcat(aHexValue, aTemp4);
	
				dwHexValue = strtoul(aHexValue, NULL, 16);
				memory[dwMemAddr] = dwHexValue;
					
				fprintf(fLog, "%d : %08x\n", dwMemAddr, memory[dwMemAddr]);
			}
		}
		
		// memory initializing
		for(dwRestOfMem=dwMemAddr; dwRestOfMem<MEM_ADDR_1MB_WIDTH; dwRestOfMem++)	{
			memory[dwRestOfMem] = 0;
			fprintf(fLog, "%d : %08x\n", dwRestOfMem, memory[dwRestOfMem]);
		}
		
		if(fHex != NULL)	fclose(fHex);
		fclose(fLog);
	}

	/********** [process function] **********/
	void do_assign_hreadyout()	{
		HREADYOUT = REG_HREADYOUT;
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
				CUR_STATE = READY;

				HRESP = 0;
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

				HRESP = 0;
			}
			wait();
		}
	}

	void do_assign_fsm()	{
		switch(CUR_STATE)	{
			case READY : 
				if(HREADY && HSEL && (HTRANS == 0x2))		{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = NONSEQ_WAIT;
						
					if(HWRITE)	NEXT_MEM_DELAY = MEM_1MB_NSEQ_WR_DELAY;
					else		NEXT_MEM_DELAY = MEM_1MB_NSEQ_RD_DELAY;
				}
				else if(HREADY && HSEL && (HTRANS == 0x3))	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = SEQ_WAIT;
					
					if(HWRITE)	NEXT_MEM_DELAY = MEM_1MB_SEQ_WR_DELAY;
					else		NEXT_MEM_DELAY = MEM_1MB_SEQ_RD_DELAY;
				}
				else	{
					NEXT_HREADYOUT = 1;
					NEXT_STATE = READY;
					NEXT_MEM_DELAY = 0;
				}
				break;
			case NONSEQ_WAIT :
				if(REG_MEM_DELAY != 0)	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = NONSEQ_WAIT;
					NEXT_MEM_DELAY = REG_MEM_DELAY - 1;
				}
				else	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = DONE;
					NEXT_MEM_DELAY = 0;
				}
				break;
			case SEQ_WAIT :
				if(REG_MEM_DELAY != 0)	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = SEQ_WAIT;
					NEXT_MEM_DELAY = REG_MEM_DELAY - 1;
				}
				else	{
					NEXT_HREADYOUT = 0;
					NEXT_STATE = DONE;
					NEXT_MEM_DELAY = 0;
				}
				break;
			case DONE :
				NEXT_HREADYOUT = 1;
				NEXT_STATE = READY;
				NEXT_MEM_DELAY = 0;
				break;
			default :
				NEXT_HREADYOUT = 1;
				NEXT_STATE = READY;
				NEXT_MEM_DELAY = 0;
				break;
		}	// switch
	}	// process

	void do_assign_address_phase()	{
		if((CUR_STATE == READY) && HREADY && HSEL)	{
			NEXT_ADDR_PHASE_HSEL = HSEL;
			NEXT_ADDR_PHASE_HWRITE = HWRITE;
			NEXT_ADDR_PHASE_HTRANS = HTRANS;
			NEXT_ADDR_PHASE_HADDR = HADDR - BASE_ADDR;
			NEXT_ADDR_PHASE_HSIZE = HSIZE;

			if(HWRITE && (HTRANS == 0x2))	NEXT_MEM_NSEQ_WR_CNT = REG_MEM_NSEQ_WR_CNT + 1;
			else				NEXT_MEM_NSEQ_WR_CNT = REG_MEM_NSEQ_WR_CNT;
			if(!HWRITE && (HTRANS == 0x2))	NEXT_MEM_NSEQ_RD_CNT = REG_MEM_NSEQ_RD_CNT + 1;
			else				NEXT_MEM_NSEQ_RD_CNT = REG_MEM_NSEQ_RD_CNT;
			if(HWRITE && (HTRANS == 0x3))	NEXT_MEM_SEQ_WR_CNT = REG_MEM_SEQ_WR_CNT + 1;
			else				NEXT_MEM_SEQ_WR_CNT = REG_MEM_SEQ_WR_CNT;
			if(!HWRITE && (HTRANS == 0x3))	NEXT_MEM_SEQ_RD_CNT = REG_MEM_SEQ_RD_CNT + 1;
			else				NEXT_MEM_SEQ_RD_CNT = REG_MEM_SEQ_RD_CNT;
		}
		else	{
			NEXT_ADDR_PHASE_HSEL = REG_ADDR_PHASE_HSEL;
			NEXT_ADDR_PHASE_HWRITE = REG_ADDR_PHASE_HWRITE;
			NEXT_ADDR_PHASE_HTRANS = REG_ADDR_PHASE_HTRANS;
			NEXT_ADDR_PHASE_HADDR = REG_ADDR_PHASE_HADDR;
			NEXT_ADDR_PHASE_HSIZE = REG_ADDR_PHASE_HSIZE;
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
				(CUR_STATE == DONE))	{
				WriteToMemory((UINT32)REG_ADDR_PHASE_HADDR, (UINT32)HWDATA, (UINT32)dw_WE);
			}

			wait();
		}
	}

	void do_assign_read_data()	{
		HRDATA = ReadFromMemory((UINT32)REG_ADDR_PHASE_HADDR);
	}

	SC_CTOR(AHBL2MEM_1)	{
		/***** [initial condition] *****/
		//BinaryLoadingAndInitialize("CM0DS.txt");
		
		/***** [process enrollment] *****/
		SC_METHOD(do_assign_hreadyout);
		sensitive << REG_HREADYOUT;

		SC_THREAD(do_pos_hclk_neg_hresetn);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();	
	
		SC_METHOD(do_assign_fsm);
		sensitive << CUR_STATE;
		sensitive << HREADY;
		sensitive << HSEL;
		sensitive << HTRANS;
		sensitive << HWRITE;

		SC_METHOD(do_assign_address_phase);
		sensitive << CUR_STATE;
		sensitive << HREADY;
		sensitive << HSEL;
		sensitive << HWRITE;
		sensitive << HTRANS;
		sensitive << HADDR;
		sensitive << HSIZE;
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

#endif	// __AHBL2MEM_1_H__
