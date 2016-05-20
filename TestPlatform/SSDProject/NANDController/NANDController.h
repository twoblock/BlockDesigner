#ifndef __NANDController_H__
#define __NANDController_H__

////////////////////////////////////////////////
// Bank configuration
// from Bank.h
////////////////////////////////////////////////
#define A0	0x00
#define B0	0x01
#define C0	0x02
#define D0	0x03
#define A1	0x04
#define B1	0x05
#define C1	0x06
#define D1	0x07
#define A2	0x08
#define B2	0x09
#define C2	0x0A
#define D2	0x0B
#define A3	0x0C
#define B3	0x0D
#define C3	0x0E
#define D3	0x0F
#define A4	0x10
#define B4	0x11
#define C4	0x12
#define D4	0x13
#define A5	0x14
#define B5	0x15
#define C5	0x16
#define D5	0x17
#define A6	0x18
#define B6	0x19
#define C6	0x1A
#define D6	0x1B
#define A7	0x1C
#define B7	0x1D
#define C7	0x1E
#define D7	0x1F
#define __X__ 0xFF

//#define BMAP_2CH_4WY_C												\
//{ 																	\
//	A0, B0,  		A1, B1,						 						\
//	A4, B4, 		A5, B5, 			 		 						\
//}

//#define BRMAP_2CH_4WY_C																					\
//{ 																										\
//	0x00, 0x01, _X_,  _X_,  0x02, 0x03,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_, 	\
//	0x04, 0x05, _X_,  _X_,  0x06, 0x07,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_,  _X_ 		\
//}

//Modified by ryan
#define BMAP_2CH_4WY_C				\
{ 									\
	A0, B0,							\
	A4, B4,	 						\
}

#define BANK_MAP			BMAP_2CH_4WY_C
//#define BANK_RMAP			BRMAP_2CH_4WY_C
#define NUM_BANKS			4

const unsigned int c_bank_map[NUM_BANKS] = BANK_MAP;	//jasmine.h
//unsigned int c_bank_rmap[NUM_BANKS_MAX] = BANK_RMAP;





////////////////////////////////////////////////
// Global constant
////////////////////////////////////////////////
#define NUM_BANKS_MAX		32	//jasmine.h
#define CHN_WIDTH			2	//jasmine.h: 2=16bit IO
#define NUM_REGISTER		509
#define READ_WAIT_CYCLE		0
#define SIZE_OF_BSP			48
#define BYTE_PER_PAGE		2048
#define WR_STAT_BUSY		1
#define WR_STAT_IDLE		0



////////////////////////////////////////////////
// Register offset
// from Flash.h
////////////////////////////////////////////////
#define INTR_BSP			0x000
#define INTR_MASK			0x004
#define FCONF_NANDCFG_1		0x008 //2byte
#define BANK_RESET			0x00C

#define FCONF_CHKCMD		0x00A //2byte
#define FCONF_PAUSE			0x010
#define FCONF_NANDCFG_2		0x014
#define FCONF_REBDELAY		0x018
#define FCONF_TIMECYCLE		0x01C
#define FCONF_CPBDMABASE	0x020
#define FCONF_BUFSIZE		0x024
#define FCONF_COMMAND		0x028
#define WR_STAT				0x02C
#define WR_BANK				0x030
#define FCP_BASE			0x034
#define BSP_BASE			0x160
#define BSP_INTR_BASE		0x760
#define BSP_FSM_BASE		0x780	//The base address of Registers that has FSM state code of specific Bank, use BSP_FSM macro.
#define SCRAMSEED_BASE		0x780	//8 registers, 15 bits each
#define REMAP_BASE			0x7C0

#define FCP_CMD				FCP_BASE + 0x00 // 0x34
#define FCP_BANK			FCP_BASE + 0x04	// 6 bits
#define FCP_OPTION			FCP_BASE + 0x08
#define FCP_DMA_ADDR		FCP_BASE + 0x0C
#define FCP_DMA_CNT			FCP_BASE + 0x10
#define FCP_COL				FCP_BASE + 0x14
#define FCP_ROW0_L			FCP_BASE + 0x18
#define FCP_ROW0_H			FCP_BASE + 0x1C
#define FCP_DST_COL			FCP_ROW0_L + NUM_BANKS_MAX*8 + 0x00 //0x34+0x18+0x100+0x00
#define FCP_DST_ROW_L		FCP_ROW0_L + NUM_BANKS_MAX*8 + 0x04
#define FCP_DST_ROW_H		FCP_ROW0_L + NUM_BANKS_MAX*8 + 0x08
#define FCP_CMD_ID			FCP_ROW0_L + NUM_BANKS_MAX*8 + 0x0C	// 10 bits
#define FCP_ISSUE			FCP_ROW0_L + NUM_BANKS_MAX*8 + 0x10

#define REMAPBANK0			REMAP_BASE + 0x00
#define REMAPBANK1			REMAP_BASE + 0x04
#define REMAPBANK2			REMAP_BASE + 0x08
#define REMAPBANK3			REMAP_BASE + 0x0C
#define REMAPBLOCK0			REMAP_BASE + 0x10
#define REMAPBLOCK1			REMAP_BASE + 0x14
#define REMAPBLOCK2			REMAP_BASE + 0x18
#define REMAPBLOCK3			REMAP_BASE + 0x1C

#define BSP_CHASTAT			0x7A0
#define MON_CHABANKIDLE		0x7A4		// When the value of MON_CHABANKIDLE is zero, Waiting Room is empty and all the banks are idle.
#define MON_TRANCOUNT		0x7A8
#define MON_DATACOUNT		0x7AC
#define MON_DMACOUNT1		0x7B0
#define MON_DMACOUNT2		0x7B4
#define MONITOR_CTRL		0x7B8
#define MONSELECT			0x7BC
#define BANK_FLAG_SEL		0x7E0		// [4:0] BankFlagSel - Bank selection for Secfor flag of ECC/EDC
#define ECC_SEC_FLAG		0x7E4		// [31:0] ECCSecFlag - ECC sector flag
#define EDC_SEC_FLAG		0x7E8		// [31:0] EDCSecFlag - EDC sector flag
#define TAKEDATAMON			0x7EC
#define FTL_READ_PTR		0x7F0



////////////////////////////////////////////////
// helper macros
// from Flash.h
////////////////////////////////////////////////
#define _FCP_ROW_L(RBANK)			(FCP_ROW0_L + (RBANK) * 8)
#define _FCP_ROW_H(RBANK)			(FCP_ROW0_H + (RBANK) * 8)
#define _BSP_INTR(RBANK)			(volatile uint8_t*)(BSP_INTR_BASE + (RBANK))
#define _BSP_CMD(RBANK)				(BSP_BASE + 0x00 + SIZE_OF_BSP * (RBANK))
#define _BSP_OPTION(RBANK)			(BSP_BASE + 0x04 + SIZE_OF_BSP * (RBANK))
#define _BSP_DMA_ADDR(RBANK)		(BSP_BASE + 0x08 + SIZE_OF_BSP * (RBANK))
#define _BSP_DMA_CNT(RBANK)			(BSP_BASE + 0x0C + SIZE_OF_BSP * (RBANK))
#define _BSP_COL(RBANK)				(BSP_BASE + 0x10 + SIZE_OF_BSP * (RBANK))
#define _BSP_ROW_H(RBANK)			(BSP_BASE + 0x14 + SIZE_OF_BSP * (RBANK))
#define _BSP_ROW_L(RBANK)			(BSP_BASE + 0x18 + SIZE_OF_BSP * (RBANK))
#define _BSP_DST_COL(RBANK)			(BSP_BASE + 0x1C + SIZE_OF_BSP * (RBANK))
#define _BSP_DST_ROW_H(RBANK)		(BSP_BASE + 0x20 + SIZE_OF_BSP * (RBANK))
#define _BSP_DST_ROW_L(RBANK)		(BSP_BASE + 0x24 + SIZE_OF_BSP * (RBANK))
#define _BSP_CMD_ID(RBANK)			(BSP_BASE + 0x28 + SIZE_OF_BSP * (RBANK))
#define _BSP_ECCNUM(RBANK)			(BSP_BASE + 0x2C + SIZE_OF_BSP * (RBANK))
#define _BSP_FSM(RBANK)				(BSP_FSM_BASE + (RBANK*4))
#define _CLR_BSP_INTR(RBANK, FLAG)	(unsigned int*)(BSP_INTR_BASE + (RBANK)/4*4) = (FLAG) << (((RBANK)%4)*8)

//#define REAL_BANK(BANK)				((unsigned int)(c_bank_map[BANK])) //It doesn't use bank map
#define REAL_BANK(BANK)				((unsigned int)(BANK))
#define FCP_ROW_L(BANK)				_FCP_ROW_L(REAL_BANK(BANK))
#define FCP_ROW_H(BANK)				_FCP_ROW_H(REAL_BANK(BANK))
#define BSP_INTR(BANK)				_BSP_INTR(REAL_BANK(BANK))
#define BSP_CMD(BANK)				_BSP_CMD(REAL_BANK(BANK))
#define BSP_OPTION(BANK)			_BSP_OPTION(REAL_BANK(BANK))
#define BSP_DMA_ADDR(BANK)			_BSP_DMA_ADDR(REAL_BANK(BANK))
#define BSP_DMA_CNT(BANK)			_BSP_DMA_CNT(REAL_BANK(BANK))
#define BSP_COL(BANK)				_BSP_COL(REAL_BANK(BANK))
#define BSP_ROW_H(BANK)				_BSP_ROW_H(REAL_BANK(BANK))
#define BSP_ROW_L(BANK)				_BSP_ROW_L(REAL_BANK(BANK))
#define BSP_DST_COL(BANK)			_BSP_DST_COL(REAL_BANK(BANK))
#define BSP_DST_ROW_H(BANK)			_BSP_DST_ROW_H(REAL_BANK(BANK))
#define BSP_DST_ROW_L(BANK)			_BSP_DST_ROW_L(REAL_BANK(BANK))
#define BSP_CMD_ID(BANK)			_BSP_CMD_ID(REAL_BANK(BANK))
#define BSP_ECCNUM(BANK)			_BSP_ECCNUM(REAL_BANK(BANK))
#define BSP_FSM(BANK)				_BSP_FSM(REAL_BANK(BANK))
#define CLR_BSP_INTR(BANK, FLAG)	_CLR_BSP_INTR(REAL_BANK(BANK), FLAG)

typedef struct TAG_FCP
{
	unsigned int	cmd;
	unsigned int	bank;
	unsigned int	option;
	unsigned int	dma_addr;
	unsigned int	dma_cnt;
	unsigned int	col;
	unsigned int	row[NUM_BANKS][CHN_WIDTH];
	unsigned int	dst_col;
	unsigned int	dst_row[CHN_WIDTH];
	unsigned int	cmd_id;
	unsigned int	issue;
}fcp_t;

#define ISSUE_ENABLE	0
#define ISSUE_DISABLE	1




////////////////////////////////////////////////
// Flash command codes
// from Flash.h
////////////////////////////////////////////////

// write operations
#define FC_COL_ROW_IN_PROG		0x01	// column address - row address - [DRAM or SRAM -> flash] - program command - wait - check result
#define FC_COL_ROW_IN			0x02	// column address - row address - [DRAM or SRAM -> flash]
#define FC_IN					0x03	//                                [DRAM or SRAM -> flash]
#define FC_IN_PROG				0x04	//                                [DRAM or SRAM -> flash] - program command - wait - check result
#define FC_PROG					0x09	//                                                          program command - wait - check result

// read operations
#define FC_COL_ROW_READ_OUT		0x0a	// column address - row address - read command - wait - [flash -> DRAM or SRAM]
#define FC_COL_ROW_READ			0x0b	// column address - row address - read command - wait
#define FC_OUT					0x0c	// [flash -> DRAM or SRAM]
#define FC_COL_OUT				0x0f	// column address change - [flash -> DRAM or SRAM]

// copyback operations
#define FC_COPYBACK				0x12	// see descriptions below
#define FC_MODIFY_COPYBACK		0x17

// others
#define FC_WAIT					0x00	// wait (used after FC_GENERIC when the command involves flash busy signal)
#define FC_ERASE				0x14	// row address - erase command - wait - check result
#define FC_GENERIC				0x15	// generic command (FCP_COL = command code)
#define FC_GENERIC_ADDR			0x16	// generic address (FCP_ROW_L and FCP_ROW_H = address, FCP_DMA_CNT = cycle count)
#define FC_READ_ID				0x10	// read_ID command - [flash -> SRAM] (FCP_OPTION = 0, FCP_DMA_ADDR = SRAM address, FCP_DMA_CNT = 16, FCP_COL = 0)





////////////////////////////////////////////////
// FCP_OPTION flags
// from Flash.h
////////////////////////////////////////////////
#define FO_P				(0x01 * OPTION_2_PLANE)		// 1 = use 2-plane mode, 0 = use 1-plane mode
#define FO_E				0x06						// 1 = use ECC/EDC hardware, 0 = do not use ECC/EDC hardware (see the notes below)
#define FO_SCRAMBLE			0x08						// enable data scrambler
#define FO_L				0x10						// disable LOW chip
#define FO_H				0x20						// disable HIGH chip
#define FO_B_W_DRDY			0x40
#define FO_B_SATA_W			0x80
#define FO_B_SATA_R			0x100




//////////////////////////////
// bank FSM codes
// from Flash.h
//////////////////////////////
#define BANK_IDLE		0x0
#define BANK_GRANT		0x1
#define BANK_START		0x2
#define BANK_CHAGET		0x3
#define BANK_WAIT		0x4
#define BANK_CMDEND		0x5
#define BANK_ECCWAIT	0x6
#define BANK_TAKE		0x7
#define BANK_END		0xf




//////////////////////////////
// channel FSM codes
// BSP_CHASTAT[4:0]
// from Flash.h
//////////////////////////////
#define CHA_IDLE      		0x00
#define CHA_START    	 	0x01
#define CHA_COMMAND1 		0x02
#define CHA_ADDR   			0x03
#define CHA_WRITE       	0x04
#define CHA_READ        	0x05
#define CHA_COMMAND2    	0x06
#define CHA_WAIT        	0x07
#define CHA_WRITE2      	0x08
#define CHA_BANKSEL     	0x09
#define CHA_COM1STA     	0x0a
#define CHA_COM2STA     	0x0b
#define CHA_ADDRSTA     	0x0c
#define CHA_WRITESTA    	0x0d
#define CHA_READSTA     	0x0e
#define CHA_ADDREND    		0x0f
#define CHA_READNOP     	0x10
#define CHA_WRITENOP    	0x11
#define CHA_COM1NOP     	0x12
#define CHA_ENDNOP      	0x13
#define CHA_BUFREADY    	0x14
#define CHA_END         	0x1f


//////////////////////////////
// my bank FSM codes
// BS(Bank State)
//////////////////////////////
enum BANK_STATE {
	BS_IDLE=0x0,

	BS_RS_CMD, //Read Status
	BS_RS_DATA,

	BS_READ_CMD_1, //Read
	BS_READ_COL_1,
	BS_READ_COL_2,
	BS_READ_ROW_1,
	BS_READ_ROW_2,
	BS_READ_CMD_2,
	BS_READ_WAIT,
	BS_READ_DATA, //1024 iteration, using curReadIdx
	BS_READ_DMA,
	BS_READ_INC_BM,

	BS_WRITE_DMA, //Write
	BS_WRITE_CMD_1,
	BS_WRITE_COL_1,
	BS_WRITE_COL_2,
	BS_WRITE_ROW_1,
	BS_WRITE_ROW_2,
	BS_WRITE_DATA, //1024 iteration, using curWriteIdx
	BS_WRITE_CMD_2,
	BS_WRITE_WAIT,
	BS_WRITE_INC_BM,

	BS_CB_CMD_1, //copy-back
	BS_CB_COL_1,
	BS_CB_COL_2,
	BS_CB_ROW_1,
	BS_CB_ROW_2,
	BS_CB_CMD_2,
	BS_CB_WAIT_1,
	BS_CB_CMD_3,
	BS_CB_COL_3,
	BS_CB_COL_4,
	BS_CB_ROW_3,
	BS_CB_ROW_4,
	BS_CB_CMD_4,
	BS_CB_WAIT_2,

	BS_ERASE_CMD_1,
	BS_ERASE_ROW_1,
	BS_ERASE_ROW_2,
	BS_ERASE_CMD_2,
	BS_ERASE_WAIT
};



//////////////////////////////
// Flash Command Interface
//////////////////////////////
typedef struct signal_t
{
	int ALE;
	int CEn;
	int CLE;
	int REn;
	int WEn;
	int WPn;
} signal_t;

#define ENABLE		1
#define DISABLE		0
#define ENABLEn		0 //use low-enable
#define DISABLEn	1
#define READY		1
#define BUSY		0



#define FCMD_READ_STATE		0x70
#define FCMD_READ_1			0x00
#define FCMD_READ_2			0x30
#define FCMD_WRITE_1		0x80
#define FCMD_WRITE_2		0x10
#define FCMD_CP_1			0x00
#define FCMD_CP_2			0x35
#define FCMD_CP_3			0x85
#define FCMD_CP_4			0x10
#define FCMD_ERASE_1		0x60
#define FCMD_ERASE_2		0xD0



//////////////////////////////
// DMAC
//////////////////////////////
#define DMA_IDLE -1

#include "BlockDesigner.h"
#include <stdio.h>
#include <string.h>

// for BDDI
#include "NANDController_BDDI.h"

SC_MODULE(NANDController){

	/********** [port] **********/
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	BD_AHBPort_MM *ahb_m0_mpms;
	BD_AHBPort_MM *ahb_m1_mpms;
	BD_AHBPort_SS *ahb_s0_spss;

	BDDI*						bddi;

	sc_in<unsigned int> flash_din_SSlave[4];
	sc_in<unsigned int> flash_RBn_SSlave[4];

	sc_out<unsigned int> flash_dout_SMaster[4];
	sc_out<unsigned int> flash_sout_SMaster[4];
	sc_out<unsigned int> bm_read_inc_SMaster;
	sc_out<unsigned int> bm_write_inc_SMaster;

	// parameters
	bool p_enableDbgMsg;
	unsigned int p_addr_base;
	unsigned int p_addr_size;
	int p_Data_Bit_Width;

	///////////////for FSM of banks///////////////
	fcp_t curFCPCommand;
	uint8_t NextStateOfBanks[NUM_BANKS];
	bool bIssued[NUM_BANKS];


	///////////////for flash_master///////////////
	unsigned int tmp_flash_dout[NUM_BANKS];
	unsigned int tmp_flash_sout[NUM_BANKS];


	///////////////for flash_slave///////////////
	unsigned int tmp_flash_din[NUM_BANKS];
	unsigned int tmp_flash_RBn[NUM_BANKS];

	unsigned int RBn[NUM_BANKS];
	bool flash_inputSignal_active[NUM_BANKS];


	///////////////for ahb_s0_port///////////////
	bool _isDataCycleActive;
	bool _isWrite;
	int32_t _currentReadWait;
	unsigned int _addr;


	///////////////Register file///////////////
	unsigned int m_regs[NUM_REGISTER];


	///////////////buffer///////////////
	uint8_t buffers[NUM_BANKS][BYTE_PER_PAGE];
	unsigned int curIdx[NUM_BANKS];


	///////////////DMA///////////////
	int dma_running_bank;
	int dma_addr;
	unsigned int dma_cnt;
	unsigned int dma_offset;
	int dma_write;
	bool dma_active_data_phase;
	bool dma_wait_data_phase;
	bool dma_bus_granted;
	bool dma_done[NUM_BANKS];


	//////////////////////Buffer manager//////////////////////
	int bm_read_inc;
	int bm_write_inc;


	// overloaded methods for clocked components
	void communicate();
	void update();

	/////////////////////////////////My Functions/////////////////////////////////
	void initMyVariables();
	void setRegister(unsigned int offset, unsigned int val);
	unsigned int getRegister(unsigned int offset);

	int encodingSignals(signal_t signals);
	void decodingSignals(int value, signal_t *signals);

	void combinationalLogicBankFSM(int bank);
	void outputLogicBankFSM(int bank);

	void getCommandInfo();
	void runCommand(int bank);
	void issueCommandToBank(int bank);

	void log(const char *format, ...);
	void printRegisters();

	bool runDMA(int bank, int bWrite);
	void initDMA(int bank);

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	SC_CTOR(NANDController)	{
		BDInit();

		SC_METHOD(communicate);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();

		SC_METHOD(update);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();
	}
};

#endif
