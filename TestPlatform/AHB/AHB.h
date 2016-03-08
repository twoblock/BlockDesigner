#ifndef __AHB_H___
#define __AHB_H___ 

#include "BlockDesigner.h"
#include "AHB_Lite.h"
#include "AHB_ARBITER_M3.h"
#include "AHB_M2S_M3.h"
#include "AHB_BDDI.h"
#include "AHB_BDMMI.h"

SC_MODULE(AHB)	{

	// Global Clock & Resetn
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// Master Interface
  BD_AHBPort_MS *AHBMaster_M0;
  BD_AHBPort_MS *AHBMaster_M1;
  BD_AHBPort_MS *AHBMaster_M2;

	sc_out<unsigned int>			M_HRDATA;
	sc_out<bool>							M_HREADY;
	sc_out<bool>							M_HRESP;

	// Slave Interface
	BD_AHBPort_SM *AHBSlave_S0;
	BD_AHBPort_SM *AHBSlave_S1;
	BD_AHBPort_SM *AHBSlave_S2;
	BD_AHBPort_SM *AHBSlave_S3;
	BD_AHBPort_SM *AHBSlave_S4;
	BD_AHBPort_SM *AHBSlave_S5;
	BD_AHBPort_SM *AHBSlave_S6;
	BD_AHBPort_SM *AHBSlave_S7;
	BD_AHBPort_SM *AHBSlave_S8;
	BD_AHBPort_SM *AHBSlave_S9;

	sc_signal<bool>						HSEL_NOMAP;

	sc_signal<unsigned int>		M_HMASTER;

	sc_signal<unsigned int>		M_HADDR;
	sc_signal<unsigned int>		M_HTRANS;
	sc_signal<unsigned int>		M_HSIZE;
	sc_signal<unsigned int>		M_HBURST;
	sc_signal<unsigned int>		M_HPROT;
	sc_signal<bool>						M_HWRITE;
	sc_signal<unsigned int>		M_HWDATA;
	sc_signal<bool>						M_HLOCK;

	AHB_Lite* 				U_AHB_Lite;
	AHB_ARBITER_M3*		U_AHB_ARBITER_M3;
	AHB_M2S_M3*				U_AHB_M2S_M3;

	BDDI*						bddi;
	BDMMI*					bdmmi;

	BDDI* GetBDDI();
	BDMMI* GetBDMMI();
	char* GetModuleName();
	void BDInit();

	SC_CTOR(AHB)	{

		BDInit();

		// AHB_ARBITER_M3 Port Connection
		U_AHB_ARBITER_M3 = new AHB_ARBITER_M3("ahb_arbiter_m3");
		U_AHB_ARBITER_M3->HCLK					(HCLK);
		U_AHB_ARBITER_M3->HRESETn				(HRESETn);
		U_AHB_ARBITER_M3->HREADY				(M_HREADY);
		U_AHB_ARBITER_M3->HBUSREQ_0			(AHBMaster_M0->HBUSREQ);
		U_AHB_ARBITER_M3->HBUSREQ_1			(AHBMaster_M1->HBUSREQ);
		U_AHB_ARBITER_M3->HBUSREQ_2			(AHBMaster_M2->HBUSREQ);
		U_AHB_ARBITER_M3->HGRANT_0			(AHBMaster_M0->HGRANT);
		U_AHB_ARBITER_M3->HGRANT_1			(AHBMaster_M0->HGRANT);
		U_AHB_ARBITER_M3->HGRANT_2			(AHBMaster_M0->HGRANT);
		U_AHB_ARBITER_M3->HMASTER				(M_HMASTER);

		// AHB_M2S_M3 Port Connection
		U_AHB_M2S_M3 = new AHB_M2S_M3("ahb_m2s_m3");
		U_AHB_M2S_M3->HRESETn						(HRESETn);
		U_AHB_M2S_M3->HCLK							(HCLK);
		U_AHB_M2S_M3->HREADY						(M_HREADY);
		U_AHB_M2S_M3->HMASTER						(M_HMASTER);
		U_AHB_M2S_M3->HADDR							(M_HADDR);
		U_AHB_M2S_M3->HPROT							(M_HPROT);
		U_AHB_M2S_M3->HTRANS						(M_HTRANS);
		U_AHB_M2S_M3->HWRITE						(M_HWRITE);
		U_AHB_M2S_M3->HSIZE							(M_HSIZE);
		U_AHB_M2S_M3->HBURST						(M_HBURST);
		U_AHB_M2S_M3->HWDATA						(M_HWDATA);
		U_AHB_M2S_M3->HADDR_0						(AHBMaster_M0->HADDR);
		U_AHB_M2S_M3->HPROT_0						(AHBMaster_M0->HPROT);
		U_AHB_M2S_M3->HTRANS_0					(AHBMaster_M0->HTRANS);
		U_AHB_M2S_M3->HWRITE_0					(AHBMaster_M0->HWRITE);
		U_AHB_M2S_M3->HSIZE_0						(AHBMaster_M0->HSIZE);
		U_AHB_M2S_M3->HBURST_0					(AHBMaster_M0->HBURST);
		U_AHB_M2S_M3->HWDATA_0					(AHBMaster_M0->HWDATA);
		U_AHB_M2S_M3->HADDR_1						(AHBMaster_M1->HADDR);
		U_AHB_M2S_M3->HPROT_1						(AHBMaster_M1->HPROT);
		U_AHB_M2S_M3->HTRANS_1					(AHBMaster_M1->HTRANS);
		U_AHB_M2S_M3->HWRITE_1					(AHBMaster_M1->HWRITE);
		U_AHB_M2S_M3->HSIZE_1						(AHBMaster_M1->HSIZE);
		U_AHB_M2S_M3->HBURST_1					(AHBMaster_M1->HBURST);
		U_AHB_M2S_M3->HWDATA_1					(AHBMaster_M1->HWDATA);
		U_AHB_M2S_M3->HADDR_2						(AHBMaster_M2->HADDR);
		U_AHB_M2S_M3->HPROT_2						(AHBMaster_M2->HPROT);
		U_AHB_M2S_M3->HTRANS_2					(AHBMaster_M2->HTRANS);
		U_AHB_M2S_M3->HWRITE_2					(AHBMaster_M2->HWRITE);
		U_AHB_M2S_M3->HSIZE_2						(AHBMaster_M2->HSIZE);
		U_AHB_M2S_M3->HBURST_2					(AHBMaster_M2->HBURST);
		U_AHB_M2S_M3->HWDATA_2					(AHBMaster_M2->HWDATA);

		// AHB_Lite Port Connection
		U_AHB_Lite = new AHB_Lite("ahb_lite");
		U_AHB_Lite->HCLK					(HCLK);
		U_AHB_Lite->HRESETn				(HRESETn);
		U_AHB_Lite->HADDR_M				(M_HADDR);
		U_AHB_Lite->HBURST_M			(M_HBURST);
		U_AHB_Lite->HLOCK_M				(M_HLOCK);
		U_AHB_Lite->HPROT_M				(M_HPROT);
		U_AHB_Lite->HSIZE_M				(M_HSIZE);
		U_AHB_Lite->HTRANS_M			(M_HTRANS);
		U_AHB_Lite->HWDATA_M			(M_HWDATA);
		U_AHB_Lite->HWRITE_M			(M_HWRITE);
		U_AHB_Lite->HRDATA_M			(M_HRDATA);
		U_AHB_Lite->HREADY_M			(M_HREADY);
		U_AHB_Lite->HRESP_M				(M_HRESP);
		U_AHB_Lite->HADDR_S0			(AHBSlave_S0->HADDR);
		U_AHB_Lite->HBURST_S0			(AHBSlave_S0->HBURST);
		U_AHB_Lite->HLOCK_S0			(AHBSlave_S0->HLOCK);
		U_AHB_Lite->HPROT_S0			(AHBSlave_S0->HPROT);
		U_AHB_Lite->HSIZE_S0			(AHBSlave_S0->HSIZE);
		U_AHB_Lite->HTRANS_S0			(AHBSlave_S0->HTRANS);
		U_AHB_Lite->HWDATA_S0			(AHBSlave_S0->HWDATA);
		U_AHB_Lite->HWRITE_S0			(AHBSlave_S0->HWRITE);
		U_AHB_Lite->HREADY_S0			(AHBSlave_S0->HREADY);
		U_AHB_Lite->HSEL_S0				(AHBSlave_S0->HSEL);
		U_AHB_Lite->HREADYOUT_S0	(AHBSlave_S0->HREADYOUT);
		U_AHB_Lite->HRESP_S0			(AHBSlave_S0->HRESP);
		U_AHB_Lite->HRDATA_S0			(AHBSlave_S0->HRDATA);
		U_AHB_Lite->HADDR_S1			(AHBSlave_S1->HADDR);
		U_AHB_Lite->HBURST_S1			(AHBSlave_S1->HBURST);
		U_AHB_Lite->HLOCK_S1			(AHBSlave_S1->HLOCK);
		U_AHB_Lite->HPROT_S1			(AHBSlave_S1->HPROT);
		U_AHB_Lite->HSIZE_S1			(AHBSlave_S1->HSIZE);
		U_AHB_Lite->HTRANS_S1			(AHBSlave_S1->HTRANS);
		U_AHB_Lite->HWDATA_S1			(AHBSlave_S1->HWDATA);
		U_AHB_Lite->HWRITE_S1			(AHBSlave_S1->HWRITE);
		U_AHB_Lite->HREADY_S1			(AHBSlave_S1->HREADY);
		U_AHB_Lite->HSEL_S1				(AHBSlave_S1->HSEL);
		U_AHB_Lite->HREADYOUT_S1	(AHBSlave_S1->HREADYOUT);
		U_AHB_Lite->HRESP_S1			(AHBSlave_S1->HRESP);
		U_AHB_Lite->HRDATA_S1			(AHBSlave_S1->HRDATA);
		U_AHB_Lite->HADDR_S2			(AHBSlave_S2->HADDR);
		U_AHB_Lite->HBURST_S2			(AHBSlave_S2->HBURST);
		U_AHB_Lite->HLOCK_S2			(AHBSlave_S2->HLOCK);
		U_AHB_Lite->HPROT_S2			(AHBSlave_S2->HPROT);
		U_AHB_Lite->HSIZE_S2			(AHBSlave_S2->HSIZE);
		U_AHB_Lite->HTRANS_S2			(AHBSlave_S2->HTRANS);
		U_AHB_Lite->HWDATA_S2			(AHBSlave_S2->HWDATA);
		U_AHB_Lite->HWRITE_S2			(AHBSlave_S2->HWRITE);
		U_AHB_Lite->HREADY_S2			(AHBSlave_S2->HREADY);
		U_AHB_Lite->HSEL_S2				(AHBSlave_S2->HSEL);
		U_AHB_Lite->HREADYOUT_S2	(AHBSlave_S2->HREADYOUT);
		U_AHB_Lite->HRESP_S2			(AHBSlave_S2->HRESP);
		U_AHB_Lite->HRDATA_S2			(AHBSlave_S2->HRDATA);
		U_AHB_Lite->HADDR_S3			(AHBSlave_S3->HADDR);
		U_AHB_Lite->HBURST_S3			(AHBSlave_S3->HBURST);
		U_AHB_Lite->HLOCK_S3			(AHBSlave_S3->HLOCK);
		U_AHB_Lite->HPROT_S3			(AHBSlave_S3->HPROT);
		U_AHB_Lite->HSIZE_S3			(AHBSlave_S3->HSIZE);
		U_AHB_Lite->HTRANS_S3			(AHBSlave_S3->HTRANS);
		U_AHB_Lite->HWDATA_S3			(AHBSlave_S3->HWDATA);
		U_AHB_Lite->HWRITE_S3			(AHBSlave_S3->HWRITE);
		U_AHB_Lite->HREADY_S3			(AHBSlave_S3->HREADY);
		U_AHB_Lite->HSEL_S3				(AHBSlave_S3->HSEL);
		U_AHB_Lite->HREADYOUT_S3	(AHBSlave_S3->HREADYOUT);
		U_AHB_Lite->HRESP_S3			(AHBSlave_S3->HRESP);
		U_AHB_Lite->HRDATA_S3			(AHBSlave_S3->HRDATA);
		U_AHB_Lite->HADDR_S4			(AHBSlave_S4->HADDR);
		U_AHB_Lite->HBURST_S4			(AHBSlave_S4->HBURST);
		U_AHB_Lite->HLOCK_S4			(AHBSlave_S4->HLOCK);
		U_AHB_Lite->HPROT_S4			(AHBSlave_S4->HPROT);
		U_AHB_Lite->HSIZE_S4			(AHBSlave_S4->HSIZE);
		U_AHB_Lite->HTRANS_S4			(AHBSlave_S4->HTRANS);
		U_AHB_Lite->HWDATA_S4			(AHBSlave_S4->HWDATA);
		U_AHB_Lite->HWRITE_S4			(AHBSlave_S4->HWRITE);
		U_AHB_Lite->HREADY_S4			(AHBSlave_S4->HREADY);
		U_AHB_Lite->HSEL_S4				(AHBSlave_S4->HSEL);
		U_AHB_Lite->HREADYOUT_S4	(AHBSlave_S4->HREADYOUT);
		U_AHB_Lite->HRESP_S4			(AHBSlave_S4->HRESP);
		U_AHB_Lite->HRDATA_S4			(AHBSlave_S4->HRDATA);
		U_AHB_Lite->HADDR_S5			(AHBSlave_S5->HADDR);
		U_AHB_Lite->HBURST_S5			(AHBSlave_S5->HBURST);
		U_AHB_Lite->HLOCK_S5			(AHBSlave_S5->HLOCK);
		U_AHB_Lite->HPROT_S5			(AHBSlave_S5->HPROT);
		U_AHB_Lite->HSIZE_S5			(AHBSlave_S5->HSIZE);
		U_AHB_Lite->HTRANS_S5			(AHBSlave_S5->HTRANS);
		U_AHB_Lite->HWDATA_S5			(AHBSlave_S5->HWDATA);
		U_AHB_Lite->HWRITE_S5			(AHBSlave_S5->HWRITE);
		U_AHB_Lite->HREADY_S5			(AHBSlave_S5->HREADY);
		U_AHB_Lite->HSEL_S5				(AHBSlave_S5->HSEL);
		U_AHB_Lite->HREADYOUT_S5	(AHBSlave_S5->HREADYOUT);
		U_AHB_Lite->HRESP_S5			(AHBSlave_S5->HRESP);
		U_AHB_Lite->HRDATA_S5			(AHBSlave_S5->HRDATA);
		U_AHB_Lite->HADDR_S6			(AHBSlave_S6->HADDR);
		U_AHB_Lite->HBURST_S6			(AHBSlave_S6->HBURST);
		U_AHB_Lite->HLOCK_S6			(AHBSlave_S6->HLOCK);
		U_AHB_Lite->HPROT_S6			(AHBSlave_S6->HPROT);
		U_AHB_Lite->HSIZE_S6			(AHBSlave_S6->HSIZE);
		U_AHB_Lite->HTRANS_S6			(AHBSlave_S6->HTRANS);
		U_AHB_Lite->HWDATA_S6			(AHBSlave_S6->HWDATA);
		U_AHB_Lite->HWRITE_S6			(AHBSlave_S6->HWRITE);
		U_AHB_Lite->HREADY_S6			(AHBSlave_S6->HREADY);
		U_AHB_Lite->HSEL_S6				(AHBSlave_S6->HSEL);
		U_AHB_Lite->HREADYOUT_S6	(AHBSlave_S6->HREADYOUT);
		U_AHB_Lite->HRESP_S6			(AHBSlave_S6->HRESP);
		U_AHB_Lite->HRDATA_S6			(AHBSlave_S6->HRDATA);
		U_AHB_Lite->HADDR_S7			(AHBSlave_S7->HADDR);
		U_AHB_Lite->HBURST_S7			(AHBSlave_S7->HBURST);
		U_AHB_Lite->HLOCK_S7			(AHBSlave_S7->HLOCK);
		U_AHB_Lite->HPROT_S7			(AHBSlave_S7->HPROT);
		U_AHB_Lite->HSIZE_S7			(AHBSlave_S7->HSIZE);
		U_AHB_Lite->HTRANS_S7			(AHBSlave_S7->HTRANS);
		U_AHB_Lite->HWDATA_S7			(AHBSlave_S7->HWDATA);
		U_AHB_Lite->HWRITE_S7			(AHBSlave_S7->HWRITE);
		U_AHB_Lite->HREADY_S7			(AHBSlave_S7->HREADY);
		U_AHB_Lite->HSEL_S7				(AHBSlave_S7->HSEL);
		U_AHB_Lite->HREADYOUT_S7	(AHBSlave_S7->HREADYOUT);
		U_AHB_Lite->HRESP_S7			(AHBSlave_S7->HRESP);
		U_AHB_Lite->HRDATA_S7			(AHBSlave_S7->HRDATA);
		U_AHB_Lite->HADDR_S8			(AHBSlave_S8->HADDR);
		U_AHB_Lite->HBURST_S8			(AHBSlave_S8->HBURST);
		U_AHB_Lite->HLOCK_S8			(AHBSlave_S8->HLOCK);
		U_AHB_Lite->HPROT_S8			(AHBSlave_S8->HPROT);
		U_AHB_Lite->HSIZE_S8			(AHBSlave_S8->HSIZE);
		U_AHB_Lite->HTRANS_S8			(AHBSlave_S8->HTRANS);
		U_AHB_Lite->HWDATA_S8			(AHBSlave_S8->HWDATA);
		U_AHB_Lite->HWRITE_S8			(AHBSlave_S8->HWRITE);
		U_AHB_Lite->HREADY_S8			(AHBSlave_S8->HREADY);
		U_AHB_Lite->HSEL_S8				(AHBSlave_S8->HSEL);
		U_AHB_Lite->HREADYOUT_S8	(AHBSlave_S8->HREADYOUT);
		U_AHB_Lite->HRESP_S8			(AHBSlave_S8->HRESP);
		U_AHB_Lite->HRDATA_S8			(AHBSlave_S8->HRDATA);
		U_AHB_Lite->HADDR_S9			(AHBSlave_S9->HADDR);
		U_AHB_Lite->HBURST_S9			(AHBSlave_S9->HBURST);
		U_AHB_Lite->HLOCK_S9			(AHBSlave_S9->HLOCK);
		U_AHB_Lite->HPROT_S9			(AHBSlave_S9->HPROT);
		U_AHB_Lite->HSIZE_S9			(AHBSlave_S9->HSIZE);
		U_AHB_Lite->HTRANS_S9			(AHBSlave_S9->HTRANS);
		U_AHB_Lite->HWDATA_S9			(AHBSlave_S9->HWDATA);
		U_AHB_Lite->HWRITE_S9			(AHBSlave_S9->HWRITE);
		U_AHB_Lite->HREADY_S9			(AHBSlave_S9->HREADY);
		U_AHB_Lite->HSEL_S9				(AHBSlave_S9->HSEL);
		U_AHB_Lite->HREADYOUT_S9	(AHBSlave_S9->HREADYOUT);
		U_AHB_Lite->HRESP_S9			(AHBSlave_S9->HRESP);
		U_AHB_Lite->HRDATA_S9			(AHBSlave_S9->HRDATA);
		U_AHB_Lite->HSEL_NOMAP		(HSEL_NOMAP);
	}

};

#endif	// __AHB_H___ 
