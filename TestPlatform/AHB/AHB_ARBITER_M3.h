#ifndef __AHB_ARBITER_M3_H__
#define __AHB_ARBITER_M3_H__

#include "systemc.h"

SC_MODULE(AHB_ARBITER_M3)	{

	////////// [port] //////////
	sc_in<bool>									HCLK;
	sc_in<bool>									HRESETn;
	sc_in<bool>									HREADY;
	sc_in<bool>									HBUSREQ_0;
	sc_in<bool>									HBUSREQ_1;
	sc_in<bool>									HBUSREQ_2;
	sc_out<bool>								HGRANT_0;
	sc_out<bool>								HGRANT_1;
	sc_out<bool>								HGRANT_2;
	sc_out<unsigned int>				HMASTER;

	///// [local variable] /////
	sc_signal<unsigned int>			hbusreq;
	sc_signal<unsigned int>			hgrant;

	///// [process function] /////
	void do_assign_hbusreq()
	{
		if(HBUSREQ_0)		hbusreq = hbusreq | 0x4;
		else						hbusreq = hbusreq & 0x3;

		if(HBUSREQ_1)		hbusreq = hbusreq | 0x2;
		else						hbusreq = hbusreq & 0x5;

		if(HBUSREQ_2)		hbusreq = hbusreq | 0x1;
		else						hbusreq = hbusreq & 0x6;
	}

	void do_assign_hgrant()
	{
		if(hgrant & 0x4)	HGRANT_0 = 1;
		else							HGRANT_0 = 0;

		if(hgrant & 0x2)	HGRANT_1 = 1;
		else							HGRANT_1 = 0;

		if(hgrant & 0x1)	HGRANT_2 = 1;
		else							HGRANT_2 = 0;
	}

	void do_divide_grant()
	{
		while(1)	{
			if(!HRESETn)	hgrant = 0x0;
			else	{
				if(HREADY)	{
					if(hbusreq == 0x0)	hgrant = 0x0;
					else if(hbusreq & 0x4)	{
						if(hgrant == 0x0)	hgrant = 0x4;
						else if(hgrant == 0x4)	hgrant = 0x4;
						else if(hgrant == 0x2)	{
							if(hbusreq & 0x2)	hgrant = 0x0;
							else							hgrant = 0x4;
						}
						else if(hgrant == 0x1)	{
							if(hbusreq & 0x1)	hgrant = 0x0;
							else							hgrant = 0x4;
						}
						else	hgrant = 0x0;
					}
					else if(hbusreq & 0x2)	{
						if(hgrant == 0x0)	hgrant = 0x2;
						else if(hgrant == 0x2)	hgrant = 0x2;
						else if(hgrant == 0x4)	{
							if(hbusreq & 0x4)	hgrant = 0x0;
							else							hgrant = 0x2;
						}
						else if(hgrant == 0x1)	{
							if(hbusreq == 0x2)	hgrant = 0x2;
							else								hgrant = 0x0;
						}
						else	hgrant = 0x0;
					}
					else if(hbusreq & 0x1)	{
						if(hgrant == 0x0)	hgrant = 0x1;
						else if(hgrant == 0x1)	hgrant = 0x1;
						else if(hgrant == 0x4)	{
							if(hbusreq == 0x1)	hgrant = 0x1;
							else								hgrant = 0x0;
						}
						else if(hgrant == 0x2)	{
							if(hbusreq == 0x1)	hgrant = 0x1;
							else								hgrant = 0x0;
						}
						else	hgrant = 0x0;
					}
					else	hgrant = 0x0;
				}	// if(HREADY) end.
			}	// else.
			
			wait();
		}	// while.
	}	// function.

	void do_assign_hmaster()
	{
		while(1)	{
			if(!HRESETn)	HMASTER = 0xF;
			else	{
				if(HREADY)	{
					switch(hgrant)	{
						case	0x4:	HMASTER = 0x0;	break;
						case	0x2:	HMASTER = 0x1;	break;
						case	0x1:	HMASTER = 0x2;	break;
						default:		HMASTER = 0xF;	break;
					}
				}
			}

			wait();
		}
	}

	SC_CTOR(AHB_ARBITER_M3)	{

		///// [enroll sensitivity] /////
		SC_METHOD(do_assign_hbusreq);
		sensitive << HBUSREQ_0;
		sensitive << HBUSREQ_1;
		sensitive << HBUSREQ_2;

		SC_METHOD(do_assign_hgrant);
		sensitive << hgrant;

		SC_THREAD(do_divide_grant);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();

		SC_THREAD(do_assign_hmaster);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();
	}

};

#endif	// __AHB_ARBITER_M3_H__
