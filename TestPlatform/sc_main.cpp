#include "Vmem_interface.h"	
#include "VCORTEXM0DS.h"
#include "tb.h"
#include <stdio.h>
#include <unistd.h>

int sc_main(int argc, char **argv) {
	sc_set_time_resolution(1, SC_NS);

	Verilated::commandArgs(argc, argv);


	sc_clock 			HCLK ("HCLK",10, SC_NS);
	sc_signal<bool> 		HRESETn;
	sc_signal<uint32_t>		HBURST;
	sc_signal<bool>			HMASTLOCK;
	sc_signal<uint32_t>		HPROT;
	sc_signal<uint32_t>		HSIZE;
	sc_signal<uint32_t>		HTRANS;
	sc_signal<bool>			HWRITE;
	sc_signal<bool>			HREADY;
	sc_signal<bool>			HRESP;
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
	sc_signal<uint32_t>		HADDR;
	sc_signal<uint32_t>		HWDATA;
	sc_signal<uint32_t>		HRDATA;
	sc_signal<bool>			invalid_addr;
	sc_signal<bool>			tty_enable;
	sc_signal<bool>			tty_end;
	sc_signal<uint32_t>		hwdata_out;
	sc_signal<uint32_t>		haddr_last;
	sc_signal<uint32_t>		EXTRACT_PC;


	tb* TB;
	TB = new tb("TB");
	TB->HCLK			(HCLK);
	TB->HRESETn			(HRESETn);
	TB->HREADY   			(HREADY);
	TB->HRESP			(HRESP);
	TB->NMI				(NMI);
	TB->IRQ00			(IRQ00);
	TB->IRQ01			(IRQ01);
	TB->IRQ02			(IRQ02);
	TB->IRQ03			(IRQ03);
	TB->IRQ04			(IRQ04);
	TB->IRQ05			(IRQ05);
	TB->IRQ06			(IRQ06);
	TB->IRQ07			(IRQ07);
	TB->IRQ08			(IRQ08);
	TB->IRQ09			(IRQ09);
	TB->IRQ10			(IRQ10);
	TB->IRQ11			(IRQ11);
	TB->IRQ12			(IRQ12);
	TB->IRQ13			(IRQ13);
	TB->IRQ14			(IRQ14);
	TB->IRQ15			(IRQ15);
	TB->RXEV			(RXEV);
	TB->tty_enable			(tty_enable);
	TB->tty_end			(tty_end);
	TB->LOCKUP			(LOCKUP);
	TB->TXEV			(TXEV);
	TB->invalid_addr		(invalid_addr);
	TB->hwdata_out			(hwdata_out);
	TB->haddr_last			(haddr_last);
	TB->EXTRACT_PC			(EXTRACT_PC);


	Vmem_interface* V_mem_interface;
	V_mem_interface = new Vmem_interface("V_mem_interface");
	V_mem_interface->HCLK		(HCLK);
	V_mem_interface->HRESETn	(HRESETn);
	V_mem_interface->HBURST		(HBURST);
	V_mem_interface->HMASTLOCK	(HMASTLOCK);
	V_mem_interface->HPROT		(HPROT);
	V_mem_interface->HSIZE		(HSIZE);
	V_mem_interface->HTRANS		(HTRANS);
	V_mem_interface->HWRITE		(HWRITE);
	V_mem_interface->HREADY		(HREADY);
	V_mem_interface->invalid_addr	(invalid_addr);
	V_mem_interface->tty_enable	(tty_enable);
	V_mem_interface->tty_end	(tty_end);
	V_mem_interface->hwdata_out	(hwdata_out);
	V_mem_interface->HADDR		(HADDR);
	V_mem_interface->HWDATA		(HWDATA);
	V_mem_interface->HRDATA		(HRDATA);
	V_mem_interface->HADDR_LAST	(haddr_last);


	VCORTEXM0DS* V_CORTEXM0DS;
	V_CORTEXM0DS = new VCORTEXM0DS("V_CORTEXM0DS");
	V_CORTEXM0DS->HCLK		(HCLK);
	V_CORTEXM0DS->HRESETn		(HRESETn);
	V_CORTEXM0DS->HBURST		(HBURST);
	V_CORTEXM0DS->HMASTLOCK		(HMASTLOCK);
	V_CORTEXM0DS->HPROT		(HPROT);
	V_CORTEXM0DS->HSIZE		(HSIZE);
	V_CORTEXM0DS->HTRANS		(HTRANS);
	V_CORTEXM0DS->HWRITE		(HWRITE);
	V_CORTEXM0DS->HREADY		(HREADY);
	V_CORTEXM0DS->HRESP		(HRESP);
	V_CORTEXM0DS->NMI		(NMI);
	V_CORTEXM0DS->IRQ00		(IRQ00);
	V_CORTEXM0DS->IRQ01		(IRQ01);
	V_CORTEXM0DS->IRQ02		(IRQ02);
	V_CORTEXM0DS->IRQ03		(IRQ03);
	V_CORTEXM0DS->IRQ04		(IRQ04);
	V_CORTEXM0DS->IRQ05		(IRQ05);
	V_CORTEXM0DS->IRQ06		(IRQ06);
	V_CORTEXM0DS->IRQ07		(IRQ07);
	V_CORTEXM0DS->IRQ08		(IRQ08);
	V_CORTEXM0DS->IRQ09		(IRQ09);
	V_CORTEXM0DS->IRQ10		(IRQ10);
	V_CORTEXM0DS->IRQ11		(IRQ11);
	V_CORTEXM0DS->IRQ12		(IRQ12);
	V_CORTEXM0DS->IRQ13		(IRQ13);
	V_CORTEXM0DS->IRQ14		(IRQ14);
	V_CORTEXM0DS->IRQ15		(IRQ15);
	V_CORTEXM0DS->TXEV		(TXEV);
	V_CORTEXM0DS->RXEV		(RXEV);
	V_CORTEXM0DS->LOCKUP		(LOCKUP);
	V_CORTEXM0DS->SYSRESETREQ	(SYSRESETREQ);
	V_CORTEXM0DS->SLEEPING		(SLEEPING);
	V_CORTEXM0DS->HADDR		(HADDR);
	V_CORTEXM0DS->HWDATA		(HWDATA);
	V_CORTEXM0DS->HRDATA		(HRDATA);
	V_CORTEXM0DS->EXTRACT_PC	(EXTRACT_PC);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave");
	sc_trace(tf, HADDR, "HADDR");  sc_trace(tf, HWDATA, "HWDATA");
	sc_trace(tf, HRDATA,  "HRDATA"); sc_trace(tf, EXTRACT_PC, "PC");

	//sc_start(1000, SC_NS);
	BDapi::BD_start();
	TB->SP->Summary_Display();

	sc_close_vcd_trace_file(tf);

	delete TB;
	delete V_mem_interface;
	delete V_CORTEXM0DS;
}
