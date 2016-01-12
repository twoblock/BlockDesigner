#include "systemc.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <set>
#include <fstream>
#include <string>
#include <ctime>
#include <fstream>		
#include "Software_Profiler.h"

using namespace std;

SC_MODULE(tb){
	sc_in<bool>		HCLK;
	sc_out<bool>		HRESETn;
	sc_out<bool>		HREADY;
	sc_out<bool>		HRESP;
	sc_out<bool>		NMI;
	sc_out<bool>		IRQ00;
	sc_out<bool>		IRQ01;
	sc_out<bool>		IRQ02;
	sc_out<bool>		IRQ03;
	sc_out<bool>		IRQ04;
	sc_out<bool>		IRQ05;
	sc_out<bool>		IRQ06;
	sc_out<bool>		IRQ07;
	sc_out<bool>		IRQ08;
	sc_out<bool>		IRQ09;
	sc_out<bool>		IRQ10;
	sc_out<bool>		IRQ11;
	sc_out<bool>		IRQ12;
	sc_out<bool>		IRQ13;
	sc_out<bool>		IRQ14;
	sc_out<bool>		IRQ15;
	sc_out<bool>		RXEV;
	sc_in<bool>		tty_enable;
	sc_in<bool>		tty_end;
	sc_in<bool>		LOCKUP;
	sc_in<bool>		TXEV;
	sc_in<bool>		invalid_addr;
	sc_in<uint32_t>		hwdata_out;
	sc_in<uint32_t>		haddr_last;
	sc_in<uint32_t>		EXTRACT_PC;

	Software_Profiler *SP;

	void print_console() {
		unsigned char ch;

		ch = (unsigned char)hwdata_out;

		if (HRESETn && HREADY && tty_enable) {
			if (tty_end)
				cout<<ch;
			else {
				cout<<sc_time_stamp()<<": Simulation stop requested by CPU"<<endl;
				sc_stop();
				wait();
			}
		}
	}

	void print_lockup() {
		if (HRESETn && LOCKUP) {
			cout<<sc_time_stamp()<<": CPU LOCKUP asserted, stopping simulation"<<endl;
			sc_stop();
			wait();
		}
	}

	void print_sev_txev() {
		if (HRESETn && TXEV) {
			cout<<sc_time_stamp()<<": CPU executed SEV instruction and asserted TXEV"<<endl;
			sc_stop();
			wait();
		}
	}

	void print_invalid_addr() {
		if (HRESETn && HREADY && invalid_addr) {
			cout<<sc_time_stamp()<<": Warning, address "<<haddr_last<<" select neither RAM or console"<<endl;
			sc_stop();
			wait();
		}
	}

	void do_test() {
		ofstream pc_trace_out("pc_trace_file.txt", ios::out|ios::app);	// Software profiling test by Ko.

		HRESETn.write(0);
		wait(10);
		cout<<"Reset is deasserted at : "<<sc_time_stamp()<<endl;
		HRESETn.write(1);
		HREADY.write(1);
		HRESP.write(0);
		NMI.write(0);
		IRQ00.write(0);
		IRQ01.write(0);
		IRQ02.write(0);
		IRQ03.write(0);
		IRQ04.write(0);
		IRQ05.write(0);
		IRQ06.write(0);
		IRQ07.write(0);
		IRQ08.write(0);
		IRQ09.write(0);
		IRQ10.write(0);
		IRQ11.write(0);
		IRQ12.write(0);
		IRQ13.write(0);
		IRQ14.write(0);
		IRQ15.write(0);
		RXEV.write(0);
		wait();
		while(true){
			print_console();
			print_lockup();
			print_sev_txev();
			print_invalid_addr();

			EXTRACT_PC.read();				// Software profiling test by Ko.
			pc_trace_out << EXTRACT_PC << endl;		// Software profiling test by Ko.
			SP->PC_Analyzer(EXTRACT_PC);
			wait();
		}
	}
	SC_CTOR(tb) {
		SP = new Software_Profiler( (char *)("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/helloworld.elf") );
		SC_CTHREAD(do_test, HCLK.pos());
		HRESETn.initialize(0);
	}
};
