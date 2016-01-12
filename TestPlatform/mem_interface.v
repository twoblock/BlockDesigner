//------------------------------------------------------------------------------
// Memory converter for testbench - bkang
//------------------------------------------------------------------------------

`timescale 1ns / 100ps

//------------------------------------------------------------------------------
// Define parameters for clock period and power-on reset delay
//------------------------------------------------------------------------------

`define ram_log2   		18             // Power of two of RAM words
`define addr_tty   		32'h40000000
`define MEM_ADDR_1MB_WIDTH     	20

module mem_interface (
  // CLOCK AND RESETS ------------------
  	input wire        	HCLK,              // Clock
  	input wire        	HRESETn,           // Asynchronous reset

  // AHB-LITE MASTER PORT --------------
  	input wire [31:0] 	HADDR,             // AHB transaction address
  	input wire [ 2:0] 	HBURST,            // AHB burst: tied to single
  	input wire        	HMASTLOCK,         // AHB locked transfer (always zero)
  	input wire [ 3:0] 	HPROT,             // AHB protection: priv; data or inst
  	input wire [ 2:0] 	HSIZE,             // AHB size: byte, half-word or word
  	input wire [ 1:0] 	HTRANS,            // AHB transfer: non-sequential only
  	input wire [31:0] 	HWDATA,            // AHB write-data
  	input wire        	HWRITE,            // AHB write control
  	output wire [31:0] 	HRDATA,            // AHB read-data
  	input wire        	HREADY,            // AHB stall signal

  // Required for tb
  	output wire [31:0] 	HADDR_LAST,
	output wire		invalid_addr,
	output wire		tty_enable,
	output wire		tty_end,
	output wire [ 7:0]	hwdata_out

);

//------------------------------------------------------------------------------
// Simulation model of an AHB memory
//------------------------------------------------------------------------------
reg [31:0] ram [0:(2**(`ram_log2))-1];     // Storage for AHB memory model
reg [7:0] memory [0:(2**(`MEM_ADDR_1MB_WIDTH)-1)];

reg [ 1:0] htrans_last;
reg [31:0] haddr_last;
reg 	   hwrite_last;
reg [ 2:0] hsize_last;

// Initiazlie memory and software loading
integer i;
integer j=0;
initial begin
  $display(" * Instruction memory initialization");
  for(i=0; i<2**20; i=i+1) memory[i] = 8'h00;
  $display(" * Loading software to memory");
  //$readmemh("CM0DS.hex", memory);
  $readmemh("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.hex", memory);
  for (i = 0; i < (2**(`ram_log2)-4); i = i + 4) begin
//    ram[j] = {memory[i],memory[i+1],memory[i+2],memory[i+3]};
    ram[j] = {memory[i+3],memory[i+2],memory[i+1],memory[i]};
    j = j + 1;
  end
  $display("ram0 = %h", ram[0]);
  $display("ram1 = %h", ram[1]);
  $display("ram2 = %h", ram[2]);
  $display("ram3 = %h", ram[3]);
  $display("ram4 = %h", ram[4]);
  $display("ram5 = %h", ram[5]);
  $display("ram6 = %h", ram[6]);
  $display("ram7 = %h", ram[7]);
  $display(" ......... Done!");
end

always @(posedge HCLK)
  	if (HREADY) begin
    		htrans_last <= HTRANS;
    		hwrite_last <= HWRITE;
    		haddr_last  <= HADDR;
    		hsize_last  <= HSIZE;
  	end

assign HADDR_LAST = haddr_last;

// Select RAM only if between address zero and top of RAM
wire hsel_ram = ~|haddr_last[31:(`ram_log2)];

assign HRDATA[31:0] = hsel_ram ? ram[haddr_last[(`ram_log2)+1:2]] : 32'd0;

wire hsel_tty = (haddr_last == `addr_tty);
assign tty_enable = hwrite_last & hsel_tty & htrans_last[1];
assign invalid_addr = htrans_last[1] & ~(hsel_ram | hsel_tty);
assign tty_end = (HWDATA[7:0] != 8'hD) ? 1 : 0;
assign hwdata_out = HWDATA[7:0];

reg [31:0] ram_tmp;

always @(posedge HCLK)
  if(HREADY & hwrite_last & hsel_ram & htrans_last[1]) begin

    // Extract RAM entry into temporary buffer
    ram_tmp = ram[haddr_last[(`ram_log2)+1:2]];

    // Insert appropriate bytes from AHB-Lite transaction
    case({hsize_last[1:0], haddr_last[1:0]})
      // Byte writes are valid to any address
      4'b00_00 : ram_tmp[ 7: 0] = HWDATA[ 7: 0];
      4'b00_01 : ram_tmp[15: 8] = HWDATA[15: 8];
      4'b00_10 : ram_tmp[23:16] = HWDATA[23:16];
      4'b00_11 : ram_tmp[31:24] = HWDATA[31:24];
      // Halfword writes are only valid to even addresses
      4'b01_00 : ram_tmp[15: 0] = HWDATA[15: 0];
      4'b01_10 : ram_tmp[31:16] = HWDATA[31:16];
      // Word writes are only valid to word aligned addresses
      4'b10_00 : ram_tmp[31: 0] = HWDATA[31: 0];
//      default  : begin
//        $display("%t: Illegal AHB transaction, stopping simulation\n", $time);
//        $finish(2);
//      end
    endcase

    // Commit write to RAM model
    ram[haddr_last[(`ram_log2)+1:2]] <= ram_tmp;
  end

endmodule // memory interface module
