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
	unsigned int req_down;
	unsigned int data_stop;

	BDDI*						bddi;

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	/********** [process function] **********/
	void do_pos_hclk_neg_hresetn()	{
		addr_t->keep_only(0x20001000, 0x20001300);
		data_t->keep_only(0x100, 0xfff);

		while(1)	{
			addr_t->next();
			data_t->next();

			if( (req_down--) == 0)
				AHB_MM->HBUSREQ = true;

			if(AHB_MM->HGRANT)
			{
				//***** Data phase *****//
				if(data_phase)
				{
					AHB_MM->setWData(data_t->get_unsigned() , 0);

					if( (data_stop--) == 0)	{
						AHB_MM->HBUSREQ = false;
						req_down = 20;
						data_stop = 10;
					}
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
