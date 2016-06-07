#ifndef __SATADevice_H__
#define __SATADevice_H__



#include <map>
#include <queue>
#include <iostream>
#include	<stdio.h>
#include <stdlib.h>
#include <list>
#define BS_BASE 0x70000000
using namespace std;
//-------------------------------------------------ADD JH
#define SATA_CTRL_1					0x0000
#define SATA_INT_ENABLE				0x0008
#define SATA_INT_STAT				0x000C
#define SATA_CTRL_2					0x0010
#define SATA_FIS_D2H_0				0x0014
#define SATA_FIS_D2H_1				0x0018
#define SATA_FIS_D2H_2				0x001C
#define SATA_FIS_D2H_3				0x0020
#define SATA_FIS_D2H_4				0x0024
#define SATA_FIS_D2H_5				0x0028
#define SATA_FIS_D2H_6				0x002C
#define SATA_FIS_D2H_7				0x0030
#define SATA_FIS_D2H_LEN			0x0034
#define SATA_FIS_H2D_0				0x0038
#define SATA_FIS_H2D_1				0x003C
#define SATA_FIS_H2D_2				0x0040
#define SATA_FIS_H2D_3				0x0044
#define SATA_FIS_H2D_4				0x0048
#define SATA_FIS_H2D_5				0x004C
#define SATA_FIS_H2D_6				0x0050
#define SATA_FIS_H2D_7				0x0054
#define SATA_XFER_BYTES				0x005C
#define SATA_XFER_BYTES_REMAIN		0x0060
#define SATA_XFER_SECTORS_REMAIN	0x0064
#define SATA_SACTIVE				0x0070
#define SATA_NCQ_BMP_1				0x0074
#define SATA_NCQ_BMP_2				0x0078
#define SATA_STATUS					0x00A0// 0=idle, 1/2=read, 3/4=write
#define SATA_SECT_OFFSET			0x00A4
#define SATA_BUF_PAGE_SIZE			0x00B4// size of each buffer
#define SATA_RESET_FIFO_1			0x00D4// reset command layer FIFO
#define SATA_MANUAL_MODE_ADDR		0x00D8
#define SATA_CTRL_3					0x00DC// Buffer Manager Mode or Manual Mode
#define SATA_FIFO_1_STATUS			0x00E4// command layer FIFO status						//=============Used in Command layer Status
#define SATA_FIFO_2_STATUS			0x00E8// transport layer FIFO status
#define SATA_FIFO_S_STATUS			0x00EC// slave FIFO status
#define SATA_PHY_STATUS				0x0100
#define SATA_ERROR					0x0104
#define SATA_PHY_CTRL				0x0108
#define SATA_CFG_1					0x0140
#define SATA_CFG_2					0x0148
#define SATA_CFG_3					0x014C
#define SATA_CFG_4					0x0150
#define SATA_CFG_5					0x015C
#define SATA_CFG_6					0x0160
#define SATA_CFG_7					0x0164
#define SATA_WBUF_BASE				0x0170// should be DRAM
#define SATA_RBUF_BASE				0x0174// should be DRAM
#define SATA_WBUF_SIZE				0x0178// number of write buffers
#define SATA_RBUF_SIZE				0x017C// number of read buffers
#define SATA_WBUF_MARGIN			0x0180
#define SATA_RESET_WBUF_PTR			0x0184
#define SATA_RESET_RBUF_PTR			0x0188
#define SATA_NCQ_BASE				0x0190// should be SRAM
#define SATA_WBUF_PTR				0x0194
#define SATA_RBUF_PTR				0x0198
#define SATA_WBUF_FREE				0x019C// number of free write buffers
#define SATA_RBUF_PENDING			0x01A0// number of pending read buffers
#define SATA_CFG_8					0x01A8
#define SATA_MAX_LBA				0x01B0
#define SATA_CFG_9					0x01C8
#define SATA_INSERT_EQ_W			0x01D0
#define SATA_LBA					0x01D4
#define SATA_SECT_CNT				0x01D8
#define SATA_INSERT_EQ_R			0x01DC
#define SATA_NCQ_ORDER				0x0220
#define SATA_NCQ_CTRL				0x0224
#define SATA_CFG_10					0x022C// bm sector read enable
#define SATA_EQ_CFG_1				0x0230
#define SATA_EQ_CTRL				0x0234
#define SATA_EQ_PTR					0x0238
#define SATA_EQ_STATUS				0x023C
#define SATA_EQ_DATA_0				0x0240
#define SATA_EQ_DATA_1				0x0244
#define SATA_EQ_DATA_2				0x0248
#define SATA_EQ_CFG_2				0x026C

#define SATA_TempReg0				0x0270
#define	 SATA_TempReg1				0x0274

#define DMA_WRITE true
#define DMA_READ  false
//============================================================
#define RBUF_ADDRESS				0x60000000
#define WBUF_ADDRESS				0x605E2000

#define SEND_NON_DATA_FIS	(1 << 0)
#define SEND_DATA_FIS		(1 << 1)
#define GET_DATA_FIS		(1 << 2)
#define SEND_GOOD_RESP		(1 << 3)
#define SEND_SACTIVE		(1 << 4)
#define COMPLETE			(1 << 5)		// register FIS D2H is sent automatically upon successful protocol completion
#define PIO_READ			(1 << 8)
#define CLR_STAT_PIO_SETUP	(1 << 9)
#define S_DMA_READ			(1 << 10)
#define FPDMA_READ			(1 << 11)
#define PIO_WRITE			(1 << 12)
#define S_DMA_WRITE			(1 << 14)
#define FPDMA_WRITE			(1 << 15)
#define SEND_R_OK			(1 << 24)
#define SEND_R_ERR			(1 << 25)

#define	CMD_RECV		0x00000001		// non-NCQ command received
#define	REG_FIS_RECV	0x00000002		// register FIS H2D without C flag or unknown type of FIS received
#define	OPERATION_OK	0x00000008		// SATA operation completed successfully
#define	OPERATION_ERR	0x00400040		// SATA operation terminated due to an error
#define	PHY_ONLINE		0x00000080		// Successful OOB
#define	PHY_OFFLINE		0x00000100		// Connection lost
#define	NCQ_CMD_RECV	0x00000200		// NCQ command received
#define	NCQ_CMD_ERR		0x00000400		// wrong NCQ command received
#define NCQ_INVALID_LBA	0x00200000		// NCQ command with an invalid LBA received (included by NCQ_CMD_ERR)

#define SYNC_PRIMITIVE				0xB5B5957C
#define R_OK_PRIMITIVE				0x3535B57C
#define SOF_PRIMITIVE				0x3636757C
#define EOF_PRIMITIVE				0xD5D5B57C

#define Switch_Nope		    0
#define Switch_Read		    1
#define Switch_Write	    2
#define Switch_Read_EQ_Active   3
#define Switch_Write_EQ_Active  4
#define Switch_Nope_EQ_Active   5 



typedef enum {
	STATUS_IDLE = 0,
	STATUS_POPEQ = 1,

	STATUS_HostTX = 2,
	STATUS_InterruptWait = 3,
	STATUS_EQ_R = 4,
	STATUS_EQ_W = 5,
	STATUS_DMA_R = 6,
	STATUS_DMA_W = 7,
	STATUS_HostRX = 8
} STATE;

typedef struct {
	unsigned int lba;
	unsigned int sector_count;
	unsigned int cmd_type;
	unsigned int C_DMA_DONE;
} CMD_Q;

typedef enum {
	STATUS_DMA_IDLE = 1, STATUS_DMA_TRANSFER = 2, STATUS_DMA_DONE = 3
} DMA_STATUS;

typedef enum {
	STATUS_CM_IDLE = 0,
	STATUS_CM_FISCHECK = 1,
	STATUS_CM_CommandCHECK = 2,
	STATUS_CM_DMAIN = 3,

	STATUS_CM_SendData = 4,
	STATUS_CM_DMAOUT = 5,
	STATUS_CM_SendDMAAC = 6,
	STATUS_CM_ReceiveData = 7,
	STATUS_CM_SendStatus = 8,
	//-----------------------------------ADD Later
	STATUS_CM_RegFIS = 9,
	STATUS_CM_1 = 10,
	STATUS_CM_2 = 11
} COMMAND_STATE;

#include "BlockDesigner.h"
#include <stdio.h>
#include <string.h>

// for BDDI
#include "SATADevice_BDDI.h"

SC_MODULE(SATADevice){

	/********** [port] **********/
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// Place instance declarations for the Ports here:
	BD_AHBPort_MM *AHBv2_Dram_M_mpms;
	BD_AHBPort_SS *AHBv2_Process_S_spss;

	BDDI*						bddi;

	sc_in<unsigned int> BM_read_limit_SSlave;
	sc_in<unsigned int> BM_write_limit_SSlave;
	sc_in<unsigned int> Rx_SSlave;

	sc_out<unsigned int> Tx_SMaster;
	sc_out<unsigned int> BM_R_size_SMaster;
	sc_out<unsigned int> BM_W_size_SMaster;
	sc_out<unsigned int> dout_Switch_SMaster;
	sc_out<bool> FIQ_int_SMaster;

	/////// for test of BDDI ///////
	UINT8						hw_reg;
	UINT16					w_reg;
	UINT32					dw_reg;
	UINT64					lw_reg;
	bool						b_reg;
	UINT32					h_reg;	// hex
	float						f_reg;
	double					df_reg;
	char						a_reg[128];

	char						hw_par;
	short						w_par;
	int							dw_par;
	long long				lw_par;
	bool						b_par;
	UINT32					dw_paru;	// hex
	float						f_par;
	double					df_par;
	char						a_par[128];


	// parameters
	bool p_enableDbgMsg;
	uint64_t p_baseaddr;
	unsigned int p_Interrupt_ID;
	unsigned int p_Rx_ID;
	uint64_t p_size;
	unsigned int p_Tx_ID;
	int p_Data_Bit_Width;

	uint32_t r_SATA_CTRL_1;
	uint32_t r_SATA_INT_ENABLE;
	uint32_t r_SATA_INT_STAT;
	uint32_t r_SATA_CTRL_2;
	uint32_t r_SATA_FIS_D2H_0;
	uint32_t r_SATA_FIS_D2H_1;
	uint32_t r_SATA_FIS_D2H_2;
	uint32_t r_SATA_FIS_D2H_3;
	uint32_t r_SATA_FIS_D2H_4;
	uint32_t r_SATA_FIS_D2H_5;
	uint32_t r_SATA_FIS_D2H_6;
	uint32_t r_SATA_FIS_D2H_7;
	uint32_t r_SATA_FIS_D2H_LEN;
	uint32_t r_SATA_FIS_H2D_0;
	uint32_t r_SATA_FIS_H2D_1;
	uint32_t r_SATA_FIS_H2D_2;
	uint32_t r_SATA_FIS_H2D_3;
	uint32_t r_SATA_FIS_H2D_4;
	uint32_t r_SATA_FIS_H2D_5;
	uint32_t r_SATA_FIS_H2D_6;
	uint32_t r_SATA_FIS_H2D_7;
	uint32_t r_SATA_XFER_BYTES;
	uint32_t r_SATA_XFER_BYTES_REMAIN;
	uint32_t r_SATA_XFER_SECTORS_REMAIN;
	uint32_t r_SATA_SACTIVE;
	uint32_t r_SATA_NCQ_BMP_1;
	uint32_t r_SATA_NCQ_BMP_2;
	uint32_t r_SATA_STATUS;
	uint32_t r_SATA_SECT_OFFSET;
	uint32_t r_SATA_BUF_PAGE_SIZE;
	uint32_t r_SATA_RESET_FIFO_1;
	uint32_t r_SATA_MANUAL_MODE_ADDR;
	uint32_t r_SATA_CTRL_3;
	uint32_t r_SATA_FIFO_1_STATUS;
	uint32_t r_SATA_FIFO_2_STATUS;
	uint32_t r_SATA_FIFO_S_STATUS;
	uint32_t r_SATA_PHY_STATUS;
	uint32_t r_SATA_ERROR;
	uint32_t r_SATA_PHY_CTRL;
	uint32_t r_SATA_CFG_1;
	uint32_t r_SATA_CFG_2;
	uint32_t r_SATA_CFG_3;
	uint32_t r_SATA_CFG_4;
	uint32_t r_SATA_CFG_5;
	uint32_t r_SATA_CFG_6;
	uint32_t r_SATA_CFG_7;
	uint32_t r_SATA_WBUF_BASE;
	uint32_t r_SATA_RBUF_BASE;
	uint32_t r_SATA_WBUF_SIZE;
	uint32_t r_SATA_RBUF_SIZE;
	uint32_t r_SATA_WBUF_MARGIN;
	uint32_t r_SATA_RESET_WBUF_PTR;
	uint32_t r_SATA_RESET_RBUF_PTR;
	uint32_t r_SATA_NCQ_BASE;
	uint32_t r_SATA_WBUF_PTR;
	uint32_t r_SATA_RBUF_PTR;
	uint32_t r_SATA_WBUF_FREE;
	uint32_t r_SATA_RBUF_PENDING;
	uint32_t r_SATA_CFG_8;
	uint32_t r_SATA_MAX_LBA;
	uint32_t r_SATA_CFG_9;
	uint32_t r_SATA_INSERT_EQ_W;
	uint32_t r_SATA_LBA;
	uint32_t r_SATA_SECT_CNT;
	uint32_t r_SATA_INSERT_EQ_R;
	uint32_t r_SATA_NCQ_ORDER;
	uint32_t r_SATA_NCQ_CTRL;
	uint32_t r_SATA_CFG_10;
	uint32_t r_SATA_EQ_CFG_1;
	uint32_t r_SATA_EQ_CTRL;
	uint32_t r_SATA_EQ_PTR;
	uint32_t r_SATA_EQ_STATUS;
	uint32_t r_SATA_EQ_DATA_0;
	uint32_t r_SATA_EQ_DATA_1;
	uint32_t r_SATA_EQ_DATA_2;
	uint32_t r_SATA_EQ_CFG_2;
	uint32_t r_SATA_TempReg0;
	uint32_t r_SATA_TempReg1;

	int32_t _waitCycles;
	int32_t _currentWait;
	uint32_t _addr;
	bool _isWrite;
	bool _isDataCycleActive;

	uint32_t r_SATA_CTRL_1_tmp;
	uint32_t r_SATA_INT_ENABLE_tmp;
	uint32_t r_SATA_INT_STAT_tmp;
	uint32_t r_SATA_CTRL_2_tmp;
	uint32_t r_SATA_FIS_D2H_0_tmp;
	uint32_t r_SATA_FIS_D2H_1_tmp;
	uint32_t r_SATA_FIS_D2H_2_tmp;
	uint32_t r_SATA_FIS_D2H_3_tmp;
	uint32_t r_SATA_FIS_D2H_4_tmp;
	uint32_t r_SATA_FIS_D2H_5_tmp;
	uint32_t r_SATA_FIS_D2H_6_tmp;
	uint32_t r_SATA_FIS_D2H_7_tmp;
	uint32_t r_SATA_FIS_D2H_LEN_tmp;
	uint32_t r_SATA_FIS_H2D_0_tmp;
	uint32_t r_SATA_FIS_H2D_1_tmp;
	uint32_t r_SATA_FIS_H2D_2_tmp;
	uint32_t r_SATA_FIS_H2D_3_tmp;
	uint32_t r_SATA_FIS_H2D_4_tmp;
	uint32_t r_SATA_FIS_H2D_5_tmp;
	uint32_t r_SATA_FIS_H2D_6_tmp;
	uint32_t r_SATA_FIS_H2D_7_tmp;
	uint32_t r_SATA_XFER_BYTES_tmp;
	uint32_t r_SATA_XFER_BYTES_REMAIN_tmp;
	uint32_t r_SATA_XFER_SECTORS_REMAIN_tmp;
	uint32_t r_SATA_SACTIVE_tmp;
	uint32_t r_SATA_NCQ_BMP_1_tmp;
	uint32_t r_SATA_NCQ_BMP_2_tmp;
	uint32_t r_SATA_STATUS_tmp;
	uint32_t r_SATA_SECT_OFFSET_tmp;
	uint32_t r_SATA_BUF_PAGE_SIZE_tmp;
	uint32_t r_SATA_RESET_FIFO_1_tmp;
	uint32_t r_SATA_MANUAL_MODE_ADDR_tmp;
	uint32_t r_SATA_CTRL_3_tmp;
	uint32_t r_SATA_FIFO_1_STATUS_tmp;
	uint32_t r_SATA_FIFO_2_STATUS_tmp;
	uint32_t r_SATA_FIFO_S_STATUS_tmp;
	uint32_t r_SATA_PHY_STATUS_tmp;
	uint32_t r_SATA_ERROR_tmp;
	uint32_t r_SATA_PHY_CTRL_tmp;
	uint32_t r_SATA_CFG_1_tmp;
	uint32_t r_SATA_CFG_2_tmp;
	uint32_t r_SATA_CFG_3_tmp;
	uint32_t r_SATA_CFG_4_tmp;
	uint32_t r_SATA_CFG_5_tmp;
	uint32_t r_SATA_CFG_6_tmp;
	uint32_t r_SATA_CFG_7_tmp;
	uint32_t r_SATA_WBUF_BASE_tmp;
	uint32_t r_SATA_RBUF_BASE_tmp;
	uint32_t r_SATA_WBUF_SIZE_tmp;
	uint32_t r_SATA_RBUF_SIZE_tmp;
	uint32_t r_SATA_WBUF_MARGIN_tmp;
	uint32_t r_SATA_RESET_WBUF_PTR_tmp;
	uint32_t r_SATA_RESET_RBUF_PTR_tmp;
	uint32_t r_SATA_NCQ_BASE_tmp;
	uint32_t r_SATA_WBUF_PTR_tmp;
	uint32_t r_SATA_RBUF_PTR_tmp;
	uint32_t r_SATA_WBUF_FREE_tmp;
	uint32_t r_SATA_RBUF_PENDING_tmp;
	uint32_t r_SATA_CFG_8_tmp;
	uint32_t r_SATA_MAX_LBA_tmp;
	uint32_t r_SATA_CFG_9_tmp;
	uint32_t r_SATA_INSERT_EQ_W_tmp;
	uint32_t r_SATA_LBA_tmp;
	uint32_t r_SATA_SECT_CNT_tmp;
	uint32_t r_SATA_INSERT_EQ_R_tmp;
	uint32_t r_SATA_NCQ_ORDER_tmp;
	uint32_t r_SATA_NCQ_CTRL_tmp;
	uint32_t r_SATA_CFG_10_tmp;
	uint32_t r_SATA_EQ_CFG_1_tmp;
	uint32_t r_SATA_EQ_CTRL_tmp;
	uint32_t r_SATA_EQ_PTR_tmp;
	uint32_t r_SATA_EQ_STATUS_tmp;
	uint32_t r_SATA_EQ_DATA_0_tmp;
	uint32_t r_SATA_EQ_DATA_1_tmp;
	uint32_t r_SATA_EQ_DATA_2_tmp;
	uint32_t r_SATA_EQ_CFG_2_tmp;
	uint32_t r_SATA_TempReg0_tmp;
	uint32_t r_SATA_TempReg1_tmp;
	//--------------------------------------------------------ADD JH
	queue<CMD_Q> EQ;
	CMD_Q CMD_Temp;
	CMD_Q CMD_Temp2;

	queue<uint32_t> Sata_Read_Q;
	queue<uint32_t> Sata_Write_Q;

	int32_t _TraceWait;
	//uint32_t sata_read_ptr;
	//uint32_t sata_write_ptr;
	uint32_t BM_R_temp;
	uint32_t BM_W_temp;

	uint32_t BM_R_limit;
	uint32_t BM_W_limit;

	//DMA Section
	bool Master_isTxActive;
	bool Master_busReqMade;
	bool Master_isAddressPhase;
	bool _data_wait, _data_sent;

	uint32_t Master_Addr;
	uint32_t Master_Data;
	uint32_t Size_tmp;

	uint8_t DMA_STATUS;

	bool m_flag;

	uint32_t Data_tmp_W;
	uint32_t Data_tmp_R;

	uint32_t DST_Addr;
	int S_DMA_DONE_CHECK;
	int S_BUFFER_PTR;

	//===============================NEWDMA member
	int dma_running_bank;
	int dma_addr;
	uint32_t dma_cnt;
	int dma_write;
	bool dma_active_data_phase;
	bool dma_wait_data_phase;
	bool dma_bus_granted;

	uint32_t dma_CurIdx;

	//================================================================SATA&DEVICE Seperated
	int Sata_Startbit;
	uint32_t ReceiceData;

	//=========================Physical Layer Part===========================================//
	int phy_40bitCount;
	int phy_Startbit;
	unsigned int phy_ReceTemp;
	list<unsigned int> phy_R_Elasticity;
	list<unsigned int> phy_S_Elasticity;

	unsigned int phy_SendTemp;
	int phy_SendDone;
	int phy_SendCount;

	//=========================
	uint32_t FISTemp[5];
	//=====================Link Layer Part ==================================================//
	uint32_t SYNC_PRIM[5];
	int HOST_LinkSignal;
	int ReceviceLoopCnt;
	//uint32_t FISTemp1;
	//uint32_t FISTemp2;
	//uint32_t FISTemp3;
	//uint32_t FISTemp4;

	//===========================================================IN DEVICE TEMP
	int C_DMADONECHECK;
	int C_DMACOMPLETE;
	int CHECK_START;

	//=============================SATAHOST & DEVICE ADDTION=========================================
	int Write_FIS_RECEIVE;
	int Read_RIS_RECEIVE;

	int D2H_Write_COMMAND_DONE;
	int D2H_Read_COMMAND_DONE;

	int RESETCHCOUNT;
	int DATATransferCheck;

	int POPEQDMAWRITE;

	int WAITCYCLE;
	int Sata_R_out;
	int Sata_W_out;
	// place your private functions and data members here:
	// ...
	// This shows an example state variable for the save/restore mechanism.
	// int		exampleStateVariable;

	// place your private functions and data members here:
	// ...
	// This shows an example state variable for the save/restore mechanism.
	// int		exampleStateVariable;

	//NOW

	uint32_t DMAREADlba;
	uint32_t DMAREADsector_count;
	uint32_t DMAREADcmd_type;
	uint32_t DMAREAD_DONE;

	int PageDMACount;
	int PageDMASectCount;

	int PageDMACount_W;
	int PageDMASectCount_W;

	int DMARWCount;




	// place your private functions and data members here:
	// ...
	// This shows an example state variable for the save/restore mechanism.
	// int		exampleStateVariable;



	// overloaded methods for clocked components
	void communicate();
	void update();

	//---------------------------------------------------------------
	int32_t ReadTrace();
	bool DMA_Transaction(bool StartBit, bool DMA_CMD, uint32_t DST_Addr,
			uint32_t m_Size);
	//===========NEW DMA
	void initDMA();
	bool runDMA(int bWrite, uint32_t DST_Addr, uint32_t m_Size);

	//======================================================================================SATADEVICE & HOST Separated

	//=========================================================LinkLayer & Transport Layer function
	//Receive part and Send part
	unsigned int Rece_PhyLayer();
	unsigned int Rece_LinkLayer(unsigned int input);
	unsigned int Rece_TransportLayer(unsigned int input);
	unsigned int Send_PhyLayer(unsigned int input);
	unsigned int Send_LinkLayer(unsigned int input);
	unsigned int Send_TransportLayer(unsigned int input);

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	~SATADevice();

	SC_CTOR(SATADevice)	{
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
