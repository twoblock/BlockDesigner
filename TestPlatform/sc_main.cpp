//-------------------------------------------------------------
// Design	: sc_main
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: sc_main.cpp
// Date		: 2016. 1. 5
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: sc_main for Test System v.1.0.1
//-------------------------------------------------------------

#include "VCORTEXM0DS.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "AHB_Lite.h"
#include "ahbl2mem.h"
#include "ahbl2mem_1.h"
#include "console.h"
#include "tb.h"

using namespace BDapi;

int sc_main(int argc, char **argv) {
	sc_set_time_resolution(1, SC_NS);

	Verilated::commandArgs(argc, argv);
/*
	sc_clock 			HCLK ("HCLK", 10, SC_NS);
	sc_signal<bool> 		HRESETn;

	sc_signal<UINT32>		HBURST_P;
 	sc_signal<bool>			HLOCK_P;
 	sc_signal<UINT32>		HPROT_P;
	sc_signal<UINT32>		HSIZE_P;
	sc_signal<UINT32>		HTRANS_P;
	sc_signal<bool>			HWRITE_P;
	sc_signal<bool>			HREADY_P;
	sc_signal<bool>			HRESP_P;
	sc_signal<UINT32>		HADDR_P;
	sc_signal<UINT32>		HWDATA_P;
	sc_signal<UINT32>		HRDATA_P;
	sc_signal<UINT32>		HBURST_S;
	sc_signal<bool>			HLOCK_S;
	sc_signal<UINT32>		HPROT_S;
	sc_signal<UINT32>		HSIZE_S;
	sc_signal<UINT32>		HTRANS_S;
	sc_signal<bool>			HWRITE_S;
	sc_signal<bool>			HREADY_S;
	sc_signal<UINT32>		HADDR_S;
	sc_signal<bool>			HSEL_S0;
	sc_signal<bool>			HREADYOUT_S0;
	sc_signal<bool>			HRESP_S0;
	sc_signal<bool>			HSEL_S1;
	sc_signal<bool>			HREADYOUT_S1;
	sc_signal<bool>			HRESP_S1;
	sc_signal<bool>			HSEL_S2;
	sc_signal<bool>			HREADYOUT_S2;
	sc_signal<bool>			HRESP_S2;
	sc_signal<bool>			HSEL_S3;
	sc_signal<bool>			HREADYOUT_S3;
	sc_signal<bool>			HRESP_S3;
	sc_signal<bool>			HSEL_S4;
	sc_signal<bool>			HREADYOUT_S4;
	sc_signal<bool>			HRESP_S4;
	sc_signal<bool>			HSEL_S5;
	sc_signal<bool>			HREADYOUT_S5;
	sc_signal<bool>			HRESP_S5;
	sc_signal<bool>			HSEL_S6;
	sc_signal<bool>			HREADYOUT_S6;
	sc_signal<bool>			HRESP_S6;
	sc_signal<bool>			HSEL_S7;
	sc_signal<bool>			HREADYOUT_S7;
	sc_signal<bool>			HRESP_S7;
	sc_signal<bool>			HSEL_S8;
	sc_signal<bool>			HREADYOUT_S8;
	sc_signal<bool>			HRESP_S8;
	sc_signal<bool>			HSEL_S9;
	sc_signal<bool>			HREADYOUT_S9;
	sc_signal<bool>			HRESP_S9;
	sc_signal<bool>			HSEL_NOMAP;
	sc_signal<UINT32>		HWDATA_S;
	sc_signal<UINT32>		HRDATA_S0;
	sc_signal<UINT32>		HRDATA_S1;
	sc_signal<UINT32>		HRDATA_S2;
	sc_signal<UINT32>		HRDATA_S3;
	sc_signal<UINT32>		HRDATA_S4;
	sc_signal<UINT32>		HRDATA_S5;
	sc_signal<UINT32>		HRDATA_S6;
	sc_signal<UINT32>		HRDATA_S7;
	sc_signal<UINT32>		HRDATA_S8;
	sc_signal<UINT32>		HRDATA_S9;

	
	sc_signal<bool>			NMI;
 	sc_signal<bool>			IRQ00;
 	sc_signal<bool>			IRQ01;
 	sc_signal<bool>			IRQ02;
 	sc_signal<bool>			IRQ03;
 	sc_signal<bool>			IRQ04;
 	sc_signal<bool>			IRQ05;
 	sc_signal<bool>			IRQ06;
	sc_signal<bool>			IRQ07;
	sc_signal<bool>			IRQ08;
	sc_signal<bool>			IRQ09;	  
	sc_signal<bool>			IRQ10;
 	sc_signal<bool>			IRQ11;
 	sc_signal<bool>			IRQ12;
 	sc_signal<bool>			IRQ13;
 	sc_signal<bool>			IRQ14;
 	sc_signal<bool>			IRQ15;
 	sc_signal<bool>			TXEV;
 	sc_signal<bool>			RXEV;
 	sc_signal<bool>			LOCKUP;
 	sc_signal<bool>			SYSRESETREQ;
 	sc_signal<bool>			SLEEPING;
	sc_signal<UINT32>		EXTRACT_PC;
	sc_signal<UINT32>		EXTRACT_R3;
	sc_signal<UINT32>		EXTRACT_R4;
	sc_signal<UINT32>		EXTRACT_R10;


	VCORTEXM0DS* BD_CORTEXM0DS;
	BD_CORTEXM0DS = new VCORTEXM0DS("BD_CORTEXM0DS");
	BD_CORTEXM0DS->HCLK							(HCLK);
	BD_CORTEXM0DS->HRESETn					(HRESETn);
	BD_CORTEXM0DS->HADDR						(HADDR_P);
	BD_CORTEXM0DS->HBURST						(HBURST_P);
	BD_CORTEXM0DS->HMASTLOCK				(HLOCK_P);
	BD_CORTEXM0DS->HPROT						(HPROT_P);
	BD_CORTEXM0DS->HSIZE						(HSIZE_P);
	BD_CORTEXM0DS->HTRANS						(HTRANS_P);
	BD_CORTEXM0DS->HWDATA						(HWDATA_P);
	BD_CORTEXM0DS->HWRITE						(HWRITE_P);
	BD_CORTEXM0DS->HRDATA						(HRDATA_P);
	BD_CORTEXM0DS->HREADY						(HREADY_P);
	BD_CORTEXM0DS->HRESP						(HRESP_P);
	BD_CORTEXM0DS->NMI							(NMI);        
	BD_CORTEXM0DS->IRQ00						(IRQ00);      
	BD_CORTEXM0DS->IRQ01						(IRQ01);
	BD_CORTEXM0DS->IRQ02						(IRQ02);
	BD_CORTEXM0DS->IRQ03						(IRQ03);
	BD_CORTEXM0DS->IRQ04						(IRQ04);
	BD_CORTEXM0DS->IRQ05						(IRQ05);
	BD_CORTEXM0DS->IRQ06						(IRQ06);
	BD_CORTEXM0DS->IRQ07						(IRQ07);
	BD_CORTEXM0DS->IRQ08						(IRQ08);
	BD_CORTEXM0DS->IRQ09						(IRQ09);
	BD_CORTEXM0DS->IRQ10						(IRQ10);
	BD_CORTEXM0DS->IRQ11						(IRQ11);
	BD_CORTEXM0DS->IRQ12						(IRQ12);
	BD_CORTEXM0DS->IRQ13						(IRQ13);
	BD_CORTEXM0DS->IRQ14						(IRQ14);
	BD_CORTEXM0DS->IRQ15						(IRQ15);     
	BD_CORTEXM0DS->TXEV							(TXEV);       
	BD_CORTEXM0DS->RXEV							(RXEV);      
	BD_CORTEXM0DS->LOCKUP						(LOCKUP);     
	BD_CORTEXM0DS->SYSRESETREQ			(SYSRESETREQ);
	BD_CORTEXM0DS->SLEEPING					(SLEEPING);   
	BD_CORTEXM0DS->EXTRACT_PC				(EXTRACT_PC);
	BD_CORTEXM0DS->EXTRACT_R3				(EXTRACT_R3);
	BD_CORTEXM0DS->EXTRACT_R4				(EXTRACT_R4);
	BD_CORTEXM0DS->EXTRACT_R10			(EXTRACT_R10);


	AHB_Lite* BD_AHB_LITE;
 	BD_AHB_LITE = new AHB_Lite("BD_AHB_LITE");
	BD_AHB_LITE->HCLK               (HCLK);
	BD_AHB_LITE->HRESETn            (HRESETn); 
	BD_AHB_LITE->HADDR_M            (HADDR_P);
	BD_AHB_LITE->HBURST_M           (HBURST_P);
	BD_AHB_LITE->HLOCK_M            (HLOCK_P);;;
	BD_AHB_LITE->HPROT_M            (HPROT_P);;
	BD_AHB_LITE->HSIZE_M            (HSIZE_P);
	BD_AHB_LITE->HTRANS_M           (HTRANS_P);
	BD_AHB_LITE->HWDATA_M           (HWDATA_P);
	BD_AHB_LITE->HWRITE_M           (HWRITE_P);
	BD_AHB_LITE->HRDATA_M           (HRDATA_P); 
	BD_AHB_LITE->HREADY_M           (HREADY_P);
	BD_AHB_LITE->HRESP_M            (HRESP_P); 
	BD_AHB_LITE->HADDR_S            (HADDR_S);
	BD_AHB_LITE->HBURST_S           (HBURST_S);
	BD_AHB_LITE->HLOCK_S            (HLOCK_S);
	BD_AHB_LITE->HPROT_S            (HPROT_S);
	BD_AHB_LITE->HSIZE_S            (HSIZE_S);
	BD_AHB_LITE->HTRANS_S           (HTRANS_S);
	BD_AHB_LITE->HWDATA_S           (HWDATA_S);
	BD_AHB_LITE->HWRITE_S           (HWRITE_S);
	BD_AHB_LITE->HREADY_S           (HREADY_S);
	BD_AHB_LITE->HSEL_S0            (HSEL_S0);
	BD_AHB_LITE->HREADYOUT_S0       (HREADYOUT_S0);
	BD_AHB_LITE->HRESP_S0           (HRESP_S0);
	BD_AHB_LITE->HRDATA_S0          (HRDATA_S0);
	BD_AHB_LITE->HSEL_S1            (HSEL_S1);
	BD_AHB_LITE->HREADYOUT_S1       (HREADYOUT_S1);
	BD_AHB_LITE->HRESP_S1           (HRESP_S1);
	BD_AHB_LITE->HRDATA_S1          (HRDATA_S1);
	BD_AHB_LITE->HSEL_S2            (HSEL_S2);
	BD_AHB_LITE->HREADYOUT_S2       (HREADYOUT_S2);
	BD_AHB_LITE->HRESP_S2           (HRESP_S2);
	BD_AHB_LITE->HRDATA_S2          (HRDATA_S2);
	BD_AHB_LITE->HSEL_S3            (HSEL_S3);
	BD_AHB_LITE->HREADYOUT_S3       (HREADYOUT_S3);
	BD_AHB_LITE->HRESP_S3           (HRESP_S3);
	BD_AHB_LITE->HRDATA_S3          (HRDATA_S3);
	BD_AHB_LITE->HSEL_S4            (HSEL_S4);
	BD_AHB_LITE->HREADYOUT_S4       (HREADYOUT_S4);
	BD_AHB_LITE->HRESP_S4           (HRESP_S4);
	BD_AHB_LITE->HRDATA_S4          (HRDATA_S4);
	BD_AHB_LITE->HSEL_S5            (HSEL_S5);
	BD_AHB_LITE->HREADYOUT_S5       (HREADYOUT_S5);
	BD_AHB_LITE->HRESP_S5           (HRESP_S5);
	BD_AHB_LITE->HRDATA_S5          (HRDATA_S5);
	BD_AHB_LITE->HSEL_S6            (HSEL_S6);
	BD_AHB_LITE->HREADYOUT_S6       (HREADYOUT_S6);
	BD_AHB_LITE->HRESP_S6           (HRESP_S6);
	BD_AHB_LITE->HRDATA_S6          (HRDATA_S6);
	BD_AHB_LITE->HSEL_S7            (HSEL_S7);
	BD_AHB_LITE->HREADYOUT_S7       (HREADYOUT_S7);
	BD_AHB_LITE->HRESP_S7           (HRESP_S7);
	BD_AHB_LITE->HRDATA_S7          (HRDATA_S7);
	BD_AHB_LITE->HSEL_S8            (HSEL_S8);
	BD_AHB_LITE->HREADYOUT_S8       (HREADYOUT_S8);
	BD_AHB_LITE->HRESP_S8           (HRESP_S8);
	BD_AHB_LITE->HRDATA_S8          (HRDATA_S8);
	BD_AHB_LITE->HSEL_S9            (HSEL_S9);
	BD_AHB_LITE->HREADYOUT_S9       (HREADYOUT_S9);
	BD_AHB_LITE->HRESP_S9           (HRESP_S9);
	BD_AHB_LITE->HRDATA_S9          (HRDATA_S9);
	BD_AHB_LITE->HSEL_NOMAP         (IRQ14);

   	
	AHBL2MEM* BD_ROM;
	BD_ROM = new AHBL2MEM("BD_ROM");
	BD_ROM->HCLK										(HCLK);
	BD_ROM->HRESETn									(HRESETn);
	BD_ROM->HSEL										(HSEL_S0);
	BD_ROM->HADDR										(HADDR_S);
	BD_ROM->HTRANS									(HTRANS_S);
	BD_ROM->HWRITE									(HWRITE_S);
	BD_ROM->HSIZE										(HSIZE_S);
	BD_ROM->HBURST									(HBURST_S);
	BD_ROM->HWDATA									(HWDATA_S);
	BD_ROM->HRDATA									(HRDATA_S0);
	BD_ROM->HRESP										(HRESP_S0);
	BD_ROM->HREADY									(HREADY_S);
	BD_ROM->HREADYOUT								(HREADYOUT_S0);
	BD_ROM->HPROT										(HPROT_S);
	

	AHBL2MEM_1* BD_SRAM;
	BD_SRAM = new AHBL2MEM_1("BD_SRAM");
	BD_SRAM->HCLK										(HCLK);
	BD_SRAM->HRESETn								(HRESETn);
	BD_SRAM->HSEL										(HSEL_S1);
	BD_SRAM->HADDR									(HADDR_S);
	BD_SRAM->HTRANS									(HTRANS_S);
	BD_SRAM->HWRITE									(HWRITE_S);
	BD_SRAM->HSIZE									(HSIZE_S);
	BD_SRAM->HBURST									(HBURST_S);
	BD_SRAM->HWDATA									(HWDATA_S);
	BD_SRAM->HRDATA									(HRDATA_S1);
	BD_SRAM->HRESP									(HRESP_S1);
	BD_SRAM->HREADY									(HREADY_S);
	BD_SRAM->HREADYOUT							(HREADYOUT_S1);
	BD_SRAM->HPROT									(HPROT_S);

	
	CONSOLE* BD_CONSOLE;
	BD_CONSOLE = new CONSOLE("BD_CONSOLE");
	BD_CONSOLE->HCLK								(HCLK);
	BD_CONSOLE->HRESETn							(HRESETn);
	BD_CONSOLE->HSEL								(HSEL_S2);
	BD_CONSOLE->HADDR								(HADDR_S);
	BD_CONSOLE->HREADY							(HREADY_S);
	BD_CONSOLE->HBURST							(HBURST_S);
	BD_CONSOLE->HPROT								(HPROT_S);
	BD_CONSOLE->HTRANS							(HTRANS_S);
	BD_CONSOLE->HWRITE							(HWRITE_S);
	BD_CONSOLE->HSIZE								(HSIZE_S);
	BD_CONSOLE->HWDATA							(HWDATA_S);
	BD_CONSOLE->HREADYOUT						(HREADYOUT_S2);
	BD_CONSOLE->HRDATA							(HRDATA_S2);
	BD_CONSOLE->HRESP								(HRESP_S2);

	
	TB* BD_TB;
	BD_TB = new TB("BD_TB");
	BD_TB->HCLK											(HCLK);
	BD_TB->HRESETn									(HRESETn);
	BD_TB->EXTRACT_PC								(EXTRACT_PC);


	sc_trace_file *wtf = sc_create_vcd_trace_file("wave");
	sc_trace(wtf, HCLK, "HCLK");
	sc_trace(wtf, HADDR_S, "HADDR");			sc_trace(wtf, HWDATA_S, "HWDATA");
	sc_trace(wtf, HTRANS_S, "HTRANS");		sc_trace(wtf, HSIZE_S, "HSIZE");
	sc_trace(wtf, HBURST_S, "HBURST");		sc_trace(wtf, HPROT_S, "HPROT");
	sc_trace(wtf, HREADY_S, "HREADY");		sc_trace(wtf, HWRITE_S, "HWRITE");
	sc_trace(wtf, HSEL_S0, "HSEL0");			sc_trace(wtf, HSEL_S1, "HSEL1");
	sc_trace(wtf, HRESP_S0, "HRESP0");		sc_trace(wtf, HRESP_S1, "HRESP1");
	sc_trace(wtf, HREADYOUT_S0, "HREADY0");		sc_trace(wtf, HREADYOUT_S1, "HREADY1");
	sc_trace(wtf, HRDATA_S0,  "HRDATA0");		sc_trace(wtf, HRDATA_S1, "HRDATA1");
	sc_trace(wtf, HADDR_P, "M_HADDR");		sc_trace(wtf, HTRANS_P, "M_HTRANS");
	sc_trace(wtf, HWRITE_P, "M_HWRITE");		sc_trace(wtf, HSIZE_P, "M_HSIZE");
	sc_trace(wtf, HBURST_P, "M_HBURST");		sc_trace(wtf, HPROT_P, "M_HPROT");
	sc_trace(wtf, HWDATA_P, "M_HWDATA");		sc_trace(wtf, HRDATA_P, "M_HRDATA");
	sc_trace(wtf, HRESP_P, "M_HRESP");		sc_trace(wtf, HREADY_P, "M_HREADY");
	sc_trace(wtf, EXTRACT_PC, "PC");
	sc_trace(wtf, EXTRACT_R3, "EXTRACT_R3");		sc_trace(wtf, EXTRACT_R4, "EXTRACT_R4");
	sc_trace(wtf, EXTRACT_R10, "EXTRACT_R10");

	BDStart();
	BD_TB->SP->Summary_Display();

	delete BD_CORTEXM0DS;
	delete BD_AHB_LITE;
	delete BD_ROM;
	delete BD_SRAM;
	delete BD_CONSOLE;
	delete BD_TB;
*/ while(1);
	exit(0);
}
