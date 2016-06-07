#ifndef __AHB_M2S_M3_H__
#define __AHB_M2S_M3_H__

#include "systemc.h"

SC_MODULE(AHB_M2S_M3)	{

	////////// [port] //////////
	sc_in<bool>									HRESETn;
	sc_in<bool>									HCLK;

	sc_in<bool>									HREADY;
	sc_in<unsigned int>					HMASTER;
	sc_out<unsigned int>				HADDR;
	sc_out<unsigned int>				HPROT;
	sc_out<unsigned int>				HTRANS;
	sc_out<bool>								HWRITE;
	sc_out<unsigned int>				HSIZE;
	sc_out<unsigned int>				HBURST;
	sc_out<unsigned int>				HWDATA;

	sc_in<unsigned int>					HADDR_0;
	sc_in<unsigned int>					HPROT_0;
	sc_in<unsigned int>					HTRANS_0;
	sc_in<bool>									HWRITE_0;
	sc_in<unsigned int>					HSIZE_0;
	sc_in<unsigned int>					HBURST_0;
	sc_in<unsigned int>					HWDATA_0;

	sc_in<unsigned int>					HADDR_1;
	sc_in<unsigned int>					HPROT_1;
	sc_in<unsigned int>					HTRANS_1;
	sc_in<bool>									HWRITE_1;
	sc_in<unsigned int>					HSIZE_1;
	sc_in<unsigned int>					HBURST_1;
	sc_in<unsigned int>					HWDATA_1;

	sc_in<unsigned int>					HADDR_2;
	sc_in<unsigned int>					HPROT_2;
	sc_in<unsigned int>					HTRANS_2;
	sc_in<bool>									HWRITE_2;
	sc_in<unsigned int>					HSIZE_2;
	sc_in<unsigned int>					HBURST_2;
	sc_in<unsigned int>					HWDATA_2;

	///// [local variable] /////
	sc_signal<unsigned int>			hmaster_delay;

	///// [process function] /////
	void do_pos_hclk_neg_hresetn()
	{
		while(1)	{
			if(!HRESETn)	{
				hmaster_delay = 0;
			}
			else	{
				if(HREADY)	{
					hmaster_delay = HMASTER;
				}
			}

			wait();
		}
	}

	void do_master_haddr()
	{
			//HADDR = HADDR_0;			
		switch(HMASTER)
		{
			case 0:		HADDR = HADDR_0;			break;
			case 1:		HADDR = HADDR_1;			break;
			case 2:		HADDR = HADDR_2;			break;
			default:	HADDR = 0xFFFFFFFF;		break;
		}
	}

	void do_master_hprot()
	{
			//HPROT = HPROT_0;	
		switch(HMASTER)
		{
			case 0:		HPROT = HPROT_0;			break;
			case 1:		HPROT = HPROT_1;			break;
			case 2:		HPROT = HPROT_2;			break;
			default:	HPROT = 0;						break;
		} 
	}

	void do_master_htrans()
	{
			//HTRANS = HTRANS_0;			
		switch(HMASTER)
		{
			case 0:		HTRANS = HTRANS_0;			break;
			case 1:		HTRANS = HTRANS_1;			break;
			case 2:		HTRANS = HTRANS_2;			break;
			default:	HTRANS = 0;							break;
		} 
	}

	void do_master_hwrite()
	{
			//HWRITE = HWRITE_0;			
		switch(HMASTER)
		{
			case 0:		HWRITE = HWRITE_0;			break;
			case 1:		HWRITE = HWRITE_1;			break;
			case 2:		HWRITE = HWRITE_2;			break;
			default:	HWRITE = 0;							break;
		}
	}

	void do_master_hsize()
	{
			//HSIZE = HSIZE_0;				
		switch(HMASTER)
		{
			case 0:		HSIZE = HSIZE_0;				break;
			case 1:		HSIZE = HSIZE_1;				break;
			case 2:		HSIZE = HSIZE_2;				break;
			default:	HSIZE = 0;							break;
		} 
	}

	void do_master_hburst()
	{
			//HBURST = HBURST_0;			
		switch(HMASTER)
		{
			case 0:		HBURST = HBURST_0;			break;
			case 1:		HBURST = HBURST_1;			break;
			case 2:		HBURST = HBURST_2;			break;
			default:	HBURST = 0;							break;
		} 
	}

	void do_master_hwdata()
	{
			//HWDATA = HWDATA_0;			
		switch(hmaster_delay)
		{
			case 0:		HWDATA = HWDATA_0;			break;
			case 1:		HWDATA = HWDATA_1;			break;
			case 2:		HWDATA = HWDATA_2;			break;
			default:	HWDATA = 0;							break;
		} 
	}

	SC_CTOR(AHB_M2S_M3)	{

		///// [enroll sensitivity] /////
		SC_THREAD(do_pos_hclk_neg_hresetn);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();

		SC_METHOD(do_master_haddr);
		sensitive	<< HMASTER;
		sensitive << HADDR_0;
		sensitive << HADDR_1;
		sensitive << HADDR_2;

		SC_METHOD(do_master_hprot);
		sensitive << HMASTER;
		sensitive << HPROT_0;
		sensitive << HPROT_1;
		sensitive << HPROT_2;

		SC_METHOD(do_master_htrans);
		sensitive << HMASTER;
		sensitive << HTRANS_0;
		sensitive << HTRANS_1;
		sensitive << HTRANS_2;

		SC_METHOD(do_master_hwrite);
		sensitive << HMASTER;
		sensitive << HWRITE_0;
		sensitive << HWRITE_1;
		sensitive << HWRITE_2;

		SC_METHOD(do_master_hsize);
		sensitive << HMASTER;
		sensitive << HSIZE_0;
		sensitive << HSIZE_1;
		sensitive << HSIZE_2;

		SC_METHOD(do_master_hburst);
		sensitive << HMASTER;
		sensitive << HBURST_0;
		sensitive << HBURST_1;
		sensitive << HBURST_2;

		SC_METHOD(do_master_hwdata);
		sensitive << hmaster_delay;
		sensitive << HWDATA_0;
		sensitive << HWDATA_1;
		sensitive << HWDATA_2;
	}

};

#endif	// __AHB_M2S_M3_H__
