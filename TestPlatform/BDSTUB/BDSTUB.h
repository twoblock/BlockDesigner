//-------------------------------------------------------------
// Design	: AHB Lite Console
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: BDSTUB.h
// Date		: 2016. 1. 6
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: Console for Test System.v.1.0.1
//-------------------------------------------------------------

#ifndef	__BDSTUB_H__
#define	__BDSTUB_H__

#define	ENDIAN_BIG	0

#include "BlockDesigner.h"
#include <stdio.h>
#include <string.h>
#include "scv.h"

// for BDDI
#include "BDSTUB_BDDI.h"

SC_MODULE(BDSTUB)	{
	/********** [port] **********/
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	BD_AHBPort_MM *AHB_MM;

	/********** [local variable] **********/
	scv_smart_ptr<unsigned int> addr_t;
	scv_smart_ptr<unsigned int> data_t;

	bool data_phase;

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

	BDDI*						bddi;

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();
	////////////////////////////////

	/********** [process function] **********/
	void do_pos_hclk_neg_hresetn()	{
		addr_t->keep_only(0x20001000, 0x20004000);
		data_t->keep_only(0x100, 0xfff);

		wait(2000);

		while(1)	{
			addr_t->next();
			data_t->next();
			
			AHB_MM->HBUSREQ = true;

			if(AHB_MM->HGRANT)
			{
				//***** Data phase *****//
				if(data_phase)
				{
					AHB_MM->setWData(data_t->get_unsigned() , 0);
				}
				//***** Address phase *****//
				AHB_MM->setAddr(addr_t->get_unsigned() , AHB2_TRANS_NONSEQ, true, AHB2_SIZE_DATA32, AHB2_BURST_INCR, 0, false);
				data_phase = true; 
			}

			wait();
		}
	}

	SC_CTOR(BDSTUB)	{
		BDInit();

		SC_THREAD(do_pos_hclk_neg_hresetn);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();
	}
};

#endif	// __BDSTUB_H__
