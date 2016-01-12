//------------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited.
//
//            (C) COPYRIGHT 2010 ARM Limited.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited.
//
//      SVN Information
//
//      Checked In          : 2010-08-03 21:05:56 +0100 (Tue, 03 Aug 2010)
//
//      Revision            : 144987
//
//      Release Information : AT510-MN-80001-r0p0-00rel0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Cortex-M0 DesignStart testbench example
//------------------------------------------------------------------------------

`timescale 1ns / 100ps

module cortexm0ds_tb ();

//------------------------------------------------------------------------------
// Define parameters for clock period and power-on reset delay
//------------------------------------------------------------------------------

localparam clk_period = 100;            // Simulation cycles per clock period
localparam por_delay  = 1001;           // Simulation cycles of power-on-reset
localparam ram_log2   = 18;             // Power of two of RAM words
//localparam addr_tty   = 32'h40000000;   // Address of output console

//------------------------------------------------------------------------------
// Define registers for clock, reset and memory
//------------------------------------------------------------------------------

reg sim_clock;                          // System clock
reg power_on_reset_n;                   // Power-on reset signal

//------------------------------------------------------------------------------
// Cortex-M0 DesignStart signal list
//------------------------------------------------------------------------------

// See the AMBA(r)3 AHB-Lite Protocol Specification v1.0 (ARM IHI 0033),
// and the Cortex(tm)-M0 Technical Reference Manual (ARM DDI 0432), for
// further details on the following signals:

wire        HCLK;               // AHB-Lite interface and CPU master clock
wire        HRESETn;            // AHB-Lite active-low reset signal

wire [31:0] HADDR;              // AHB-Lite byte address
wire [ 2:0] HBURST;             // AHB-Lite burst type (not used by testbench)
wire        HMASTLOCK;          // AHB-Lite locked transaction (always zero)
wire [ 3:0] HPROT;              // AHB-Lite protection (not used by testbench)
wire [ 2:0] HSIZE;              // AHB-Lite size (# of bits: 0=8, 1=16, 2=32)
wire [ 1:0] HTRANS;             // AHB-Lite perform transaction
wire [31:0] HWDATA;             // AHB-Lite write-data
wire        HWRITE;             // AHB-Lite transaction is write not read
wire [31:0] HRDATA;             // AHB-Lite read-data
wire        HREADY;             // AHB-Lite bus ready signal
wire        HRESP;              // AHB-Lite bus error (not used by testbench)

// See the ARMv6-M Architecture Reference Manual (ARM DDI 0419), and the
// Cortex(tm)-M0 Technical Reference Manual (ARM DDI 0432), for further
// details on the following signals:

wire        NMI;                // Non-maskable interrupt input (not used by tb)
wire [15:0] IRQ;                // Interrupt inputs (not used by testbench)

wire        TXEV;               // Event output (CPU executed SEV instruction)
wire        RXEV;               // Event input (not used by testbench)

wire        LOCKUP;             // CPU stopped due to multiple software errors
wire        SYSRESETREQ;        // CPU request for system to be reset

wire        SLEEPING;           // CPU is sleeping (not used by testbench)

wire [31:0] haddr_last;
wire	    invalid_addr;
wire	    tty_enable;
wire	    tty_end;
wire [ 7:0] hwdata_out;

// initial
//   begin
//           $dumpfile("scenarioT.vcd");
//           $dumpvars(0, u_cortexm0ds);
//           //$dumpvars(0, clk, wCGEN);
//   end

//------------------------------------------------------------------------------
// Generate system clock, power-on reset and synchronized AHB reset signals
//------------------------------------------------------------------------------

// Generate a clock of the appropriate period
initial
  #0 sim_clock = 1'b0;

always @(sim_clock)
  #(clk_period/2) sim_clock <= ~sim_clock;

// Release the active-low power-on reset signal after the given delay
initial begin
  #0 power_on_reset_n = 1'b0;
  #(por_delay) power_on_reset_n = 1'b1;
end

// Synchronize AHB reset, and factor in reset request from the CPU
reg [1:0] rst_sync;
always @(posedge sim_clock or negedge power_on_reset_n)
  if(!power_on_reset_n)
    rst_sync <= 2'b00;
  else
    rst_sync <= {rst_sync[0],~SYSRESETREQ};

//------------------------------------------------------------------------------
// Connect clock and reset to AHB signals and assign static signals
//------------------------------------------------------------------------------

assign HCLK    = sim_clock;    // Assign AHB clock from simulation clock
assign HRESETn = rst_sync[1];  // Assign AHB clock from synchronizer
assign HREADY  = 1'b1;         // All devices are zero-wait-state
assign HRESP   = 1'b0;         // No device in this system generates errors
assign NMI     = 1'b0;         // Do not generate any non-maskable interrupts
assign IRQ     = {16{1'b0}};   // Do not generate any interrupts
assign RXEV    = 1'b0;         // Do not generate any external events

//------------------------------------------------------------------------------
// Instantiate Cortex-M0 DesignStart processor macro cell
//------------------------------------------------------------------------------

CORTEXM0DS u_cortexm0ds (
  	.HCLK        	(HCLK),
  	.HRESETn     	(HRESETn),
  	.HADDR       	(HADDR[31:0]),
  	.HBURST      	(HBURST[2:0]),
  	.HMASTLOCK   	(HMASTLOCK),
  	.HPROT       	(HPROT[3:0]),
  	.HSIZE       	(HSIZE[2:0]),
  	.HTRANS      	(HTRANS[1:0]),
  	.HWDATA      	(HWDATA[31:0]),
  	.HWRITE      	(HWRITE),
  	.HRDATA      	(HRDATA[31:0]),
  	.HREADY      	(HREADY),
  	.HRESP       	(HRESP),
  	.NMI         	(NMI),
  	.IRQ00       	(IRQ[0]),
  	.IRQ01       	(IRQ[1]),
  	.IRQ02       	(IRQ[2]),
  	.IRQ03       	(IRQ[3]),
  	.IRQ04       	(IRQ[4]),
  	.IRQ05       	(IRQ[5]),
  	.IRQ06       	(IRQ[6]),
  	.IRQ07       	(IRQ[7]),
  	.IRQ08       	(IRQ[8]),
  	.IRQ09       	(IRQ[9]),
  	.IRQ10       	(IRQ[10]),
  	.IRQ11       	(IRQ[11]),
  	.IRQ12       	(IRQ[12]),
  	.IRQ13       	(IRQ[13]),
  	.IRQ14       	(IRQ[14]),
  	.IRQ15       	(IRQ[15]),
  	.TXEV        	(TXEV),
  	.RXEV        	(RXEV),
  	.LOCKUP      	(LOCKUP),
  	.SYSRESETREQ 	(SYSRESETREQ),
  	.SLEEPING    	(SLEEPING)
);

mem_interface u_mem_interface (
 	.HCLK 		(HCLK),              
 	.HRESETn 	(HRESETn),          

 	.HADDR 		(HADDR),           
 	.HBURST 	(HBURST),         
 	.HMASTLOCK 	(HMASTLOCK),     
 	.HPROT 		(HPROT),        
 	.HSIZE 		(HSIZE),       
 	.HTRANS 	(HTRANS),     
 	.HWDATA 	(HWDATA),    
 	.HWRITE 	(HWRITE),   
 	.HRDATA 	(HRDATA),   
  	.HREADY 	(HREADY),   

 	.HADDR_LAST 	(haddr_last),     
	.invalid_addr	(invalid_addr),
	.tty_enable	(tty_enable),
	.tty_end	(tty_end),
	.hwdata_out	(hwdata_out)
);

//------------------------------------------------------------------------------
// Simulation model of an AHB memory
//------------------------------------------------------------------------------

// move to the memory interface

//------------------------------------------------------------------------------
// Simulation model of a simple AHB output console
//------------------------------------------------------------------------------

always @(posedge HCLK)
  if(HRESETn & HREADY & tty_enable) begin
    if(tty_end)
      $write("%c", hwdata_out);
    else begin
      $display("%t: Simulation stop requested by CPU\n", $time);
      $finish(2);
    end
  end

//------------------------------------------------------------------------------
// Simulation commentary
//------------------------------------------------------------------------------

always @(posedge HRESETn)
  $display("%t: Simulation leaving reset", $time);

always @(posedge HCLK)
  if (HRESETn & LOCKUP) begin
    $display("%t: CPU LOCKUP asserted, stopping simulation\n", $time);
    #(clk_period * 32)
    $finish(2);
  end

always @(posedge HCLK)
  if (HRESETn & TXEV) begin
    $display("%t: CPU executed SEV instruction and asserted TXEV\n", $time);
  end

always @(posedge HCLK)
  if (HRESETn & HREADY & invalid_addr)
    $display("%t: Warning, address %x selects neither RAM or console",
      $time, haddr_last);

endmodule // cortexm0ds_tb
