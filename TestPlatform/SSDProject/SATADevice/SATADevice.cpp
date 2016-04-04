#include "SATADevice.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <queue>

using namespace std;

#define Eq_limit_to_Switcher 1
#define timeunit 10;

uint32_t Temp[2][5];
char inputString[100];
ifstream inFile;
bool flag;
bool Equal_flag;
uint32_t intPulse;
ofstream outFile;
int DMA_TEST_flag;
int DMA_Write;
bool first;				// is changed by TB
int DMA_RW_CHECK;
//FILE *INPUTFILE = fopen("Financial1.trace","r");
ofstream outFile_WriteRQ;
//uint32_t j=0;
ofstream Sata_RFile;
ofstream Sata_WFile;

int yy_sect_offset;
int yy_remain_sects;
int yy_num_sector_to_write ;

int rr_sect_offset;
int rr_remain_sects;
int rr_num_sector_to_write ;

unsigned int SATADevice::Rece_PhyLayer() {
	//Pop phy_Elasticity Data to transport LinkLayer
	//return type : unsigned int
	unsigned int RECETEMP = 0;
	if (phy_R_Elasticity.size() != 0) {
		RECETEMP = phy_R_Elasticity.front();
		phy_R_Elasticity.pop_front();							//CHECKLATER
		//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
		//				"============		This is Rece_PhyLayer : RECETEMP Data 0x%x \n",
		//				RECETEMP);
	}
	return RECETEMP;

}

unsigned int SATADevice::Rece_LinkLayer(unsigned int input) {

	if (input == SYNC_PRIMITIVE) {
		HOST_LinkSignal = 0;
	} else if (input == R_OK_PRIMITIVE) {
		HOST_LinkSignal = 2;
	} else
		HOST_LinkSignal = 1;

	return input;
}
unsigned int SATADevice::Rece_TransportLayer(unsigned int input) {
	return input;
}
unsigned int SATADevice::Send_PhyLayer(unsigned int input) {

	//if (input != 0)							//Push to S_Elastivity Buffer
	//		{
	phy_S_Elasticity.push_back(input);
	//}
	//	return 0;
	return input;
}
unsigned int SATADevice::Send_LinkLayer(unsigned int input) {
	return input;
}
unsigned int SATADevice::Send_TransportLayer(unsigned int input) {
	return input;
}

void SATADevice::communicate() {
	// the following message will be printed only in the debug version of MxExplorer
	//if (p_enableDbgMsg == true) {
	//	message(eslapi::CASI_MSG_INFO, "Executing communicate function");
	//}
	//if (p_enableDbgMsg == true) {
	//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
	//		"This Communicate function\n");
	//}
	// TODO:  Add your communicate code here.

	unsigned int ReceData = 0;
	unsigned int SendData = 0;

	unsigned int S_PhyLTemp = 0;
	unsigned int S_LinkLTemp = 0;
	unsigned int S_TransLTemp = 0;

	unsigned int R_PhyLTemp = 0;
	unsigned int R_LinkLTemp = 0;
	unsigned int R_TransLTemp = 0;
	//int ReceviceLoopCnt = 0;
	uint32_t Reg = 0;

	uint32_t FIS_H2D_0[5];
	//	uint32_t	FIS_TEMP=0;
	int sendbit = 0;

	if (RESETCHCOUNT == 0) {
		//==========================================Physical Layer===========================
		ReceData = Rx_SSlave;

		//=========================================Physical Layer -----------Receive Part=======

		if (phy_Startbit == 1) {
			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "phy_Startbit : %d	phy_40bitCount : %d	ReceiveData : %d \n", phy_Startbit,phy_40bitCount,ReceData);
			for (int i = 0; i < phy_40bitCount; i++)
				ReceData = ReceData << 1;
			phy_ReceTemp = phy_ReceTemp + ReceData;
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, 		"phy_Temp Data 0x%x 'b \n", phy_ReceTemp);
			if (phy_40bitCount == 31) {
				//push phy_Temp value to list Buffer

				phy_R_Elasticity.push_back(phy_ReceTemp);
				phy_40bitCount = 0;
				phy_ReceTemp = 0;

			} else {
				//phy_ReceTemp = phy_ReceTemp << 1;
				phy_40bitCount++;
			}

		}
		if (ReceData == 1)							//-> Going to Reset function
		{
			phy_Startbit = 1;

		}

		//===========================================Physical Layer ------------Send Part==========

		if (CHECK_START == 0) {
			Tx_SMaster = 1;
			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
			//		"---------------------This CHECK START\n");

			CHECK_START = 1;
		} else if ((phy_SendCount == 0) || (phy_SendCount == 32)) {

			if (phy_S_Elasticity.size() != 0) {
				if (phy_SendCount == 32)
					phy_SendCount = 0;
				phy_SendTemp = phy_S_Elasticity.front();
				phy_S_Elasticity.pop_front();
				sendbit = phy_SendTemp & 0x1;
				phy_SendTemp = phy_SendTemp >> 1;
				Tx_SMaster = sendbit;	//Sending Bits

				phy_SendCount++;

			}

		} else {
			sendbit = phy_SendTemp & 0x1;
			phy_SendTemp = phy_SendTemp >> 1;
			Tx_SMaster = sendbit;			//Sending Bits
			phy_SendCount++;
		}

		//==========================================================================Physical Layer

		//==========================================================================Link Layer
		if (phy_S_Elasticity.size() == 0)
			phy_S_Elasticity.push_back(SYNC_PRIMITIVE);

		//==========================================================================Link Layer

		//=============================Command Layer FSM==========================================
		//Register : r_TempReg0 is internal register of Command Layer FSM
		switch (r_SATA_FIFO_1_STATUS) {

			case STATUS_CM_IDLE:			//0

				if ((D2H_Write_COMMAND_DONE == 0)
						&& ((FISTemp[0] & 0x00FF0000) == 0x00350000)) {

					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_IDLE;
				} else if ((D2H_Read_COMMAND_DONE == 0)
						&& ((FISTemp[0] & 0x00FF0000) == 0x00250000)) {
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_IDLE;
				}
				else if(r_SATA_EQ_STATUS == (128<<16))
				{
					//ver4//
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_IDLE;
				}
				else
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_FISCHECK;

				break;
			case STATUS_CM_FISCHECK:		//1
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//	"This STATUS_CM_FISCHECK function\n");
				D2H_Write_COMMAND_DONE = 0;
				D2H_Read_COMMAND_DONE = 0;

				//Register FIS C bit=1, SRST=0 -> Command Check state
				r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_CommandCHECK;
				//								-> Control Check state

				break;
			case STATUS_CM_CommandCHECK:	//2
				if ((phy_R_Elasticity.size() != 0) && (ReceviceLoopCnt != 5)) {
					R_PhyLTemp = Rece_PhyLayer();
					R_LinkLTemp = Rece_LinkLayer(R_PhyLTemp);
					if (HOST_LinkSignal == 1) {
						R_TransLTemp = Rece_TransportLayer(R_LinkLTemp);
						FISTemp[ReceviceLoopCnt] = R_TransLTemp;
						ReceviceLoopCnt++;
					}

				} else if (ReceviceLoopCnt == 5) {
					//===========================================================Receive FIS Information
					//for (int i = 0; i < 5; i++) {
					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//		"FISTemp[%d] : 0x%x	\n", i, FISTemp[i]);
					//}
					if ((FISTemp[0] & 0x00FF0000) == 0x00250000) {
						r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_DMAIN;			//READ
						Read_RIS_RECEIVE = 1;
					}

					//if Command is Write(DMA OUT)
					else if ((FISTemp[0] & 0x00FF0000) == 0x00350000) {
						r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_DMAOUT;		//WRITE
					} else
						r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_CommandCHECK;
					ReceviceLoopCnt = 0;
					DATATransferCheck = FISTemp[3];
				} else
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_CommandCHECK;

				break;

			case STATUS_CM_DMAIN:

				if (D2H_Read_COMMAND_DONE == 1) {
					//			D2H_Read_COMMAND_DONE = 0;
					for (int i = 0; i < DMAREADsector_count; i++) {
						unsigned int Temp22 = Sata_Read_Q.front();
						for (int j = 0; j < 128; j++)
							Sata_Read_Q.pop();
						S_TransLTemp = Send_TransportLayer(Temp22);

						S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
						S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//	"This  STATUS_CM_DMAIN:S_PhyLTemp :0x%x\n",
						//	Temp22);
					}
					S_TransLTemp = Send_TransportLayer(R_OK_PRIMITIVE);
					S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
					S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//	"This STATUS_HOST_TransIDLE :S_PhyLTemp :0x%x\n",
					//	S_PhyLTemp);
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_IDLE;

				} else
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_DMAIN;
				break;
			case STATUS_CM_SendData:
				//4
				//Read Command
				//Transmit Data FIS to Host
				//Send Sata Data to HOST

				r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_DMAIN;

				break;
			case STATUS_CM_DMAOUT:

				if (phy_R_Elasticity.size() != 0) {
					R_PhyLTemp = Rece_PhyLayer();
					R_LinkLTemp = Rece_LinkLayer(R_PhyLTemp);
					if (HOST_LinkSignal == 1) {
						R_TransLTemp = Rece_TransportLayer(R_LinkLTemp);
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//	"STATUS_CM_DMAOUT R_TransLTemp - Put In Sata_Write_Q: 0x%x\n",
						//	R_TransLTemp);
						for (int j = 0; j < 128; j++)
							Sata_Write_Q.push(R_TransLTemp);
						//Write_FIS_RECEIVE = 1;
						DATATransferCheck--;
					}
				}
				if (DATATransferCheck == 0) {

					S_TransLTemp = Send_TransportLayer(R_OK_PRIMITIVE);
					S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
					S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//	"This STATUS_HOST_TransIDLE :S_PhyLTemp :0x%x\n",
					//	S_PhyLTemp);
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_IDLE;
					Write_FIS_RECEIVE = 1;
					Read_RIS_RECEIVE = 0;
				} else
					r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_DMAOUT;
				break;
			case STATUS_CM_SendDMAAC:
				//6

				break;
			case STATUS_CM_ReceiveData:
				//7

				break;
			case STATUS_CM_SendStatus:
				//8
				//Transmit Register FIS to Host
				r_SATA_FIFO_1_STATUS_tmp = STATUS_CM_IDLE;

				break;

			default:
				break;
		}

		//=====================================================================================================
		//========================================================================================ORIGINAL SATA
		//FSM implementation
		switch (r_SATA_STATUS) {
			case STATUS_IDLE:
				if (r_SATA_INT_ENABLE == 0)
				{	
					FIQ_int_SMaster = intPulse;
					//r_SATA_EQ_DATA_2_tmp=8;
					r_SATA_STATUS_tmp = STATUS_IDLE;
				}
				else {
					r_SATA_EQ_DATA_2_tmp=0;
					if ((Write_FIS_RECEIVE == 1) || (Read_RIS_RECEIVE == 1)) {

						if (Write_FIS_RECEIVE == 1)	//REQUSET WRITE COMMAND RECEIVCE
						{
							Write_FIS_RECEIVE = 0;			//=> NEXT CHANGE STATE

						} else if (Read_RIS_RECEIVE == 1) {
							Read_RIS_RECEIVE = 0;			//=> NEXT CHANGE STATE
						}

						//Read & Write Command Section
						r_SATA_FIS_H2D_0_tmp = FISTemp[0];
						r_SATA_FIS_H2D_1_tmp = FISTemp[1];
						r_SATA_FIS_H2D_2_tmp = FISTemp[2];
						r_SATA_FIS_H2D_3_tmp = FISTemp[3];
						r_SATA_FIS_H2D_4_tmp = FISTemp[4];
						intPulse = 1;
						FIQ_int_SMaster = intPulse;
						//intPulse=0;
						//FIQ_int_SMaster->driveSignal(intPulse,&p_Interrupt_ID);

					} else if (r_SATA_INSERT_EQ_R == 1) {
						r_SATA_STATUS_tmp = STATUS_EQ_R;

						if( EQ.size() <= Eq_limit_to_Switcher ){
							r_SATA_TempReg0_tmp = Switch_Read_EQ_Active;	
						}
						else{
							r_SATA_TempReg0_tmp = Switch_Read;
						}
						intPulse = 0;
						FIQ_int_SMaster = intPulse;
					} else if (r_SATA_INSERT_EQ_W == 1) {
						r_SATA_STATUS_tmp = STATUS_EQ_W;

						if( EQ.size() <= Eq_limit_to_Switcher ){
							r_SATA_TempReg0_tmp = Switch_Write_EQ_Active;	
						}
						else{
							r_SATA_TempReg0_tmp = Switch_Write;
						}

						intPulse = 0;
						FIQ_int_SMaster = intPulse;
					} else{

						if( EQ.size() >= Eq_limit_to_Switcher  )
						{
							r_SATA_TempReg0_tmp = Switch_Nope_EQ_Active;
						}
						else
						{
							r_SATA_TempReg0_tmp = Switch_Nope;
						}

						r_SATA_STATUS_tmp = STATUS_IDLE;
					}

					if (r_SATA_EQ_CTRL == 1) {

						if (EQ.front().cmd_type == 1) {
							r_SATA_EQ_DATA_2_tmp = 8;
							//if (POPEQDMAWRITE == 1) {
							if( EQ.front().C_DMA_DONE == 1 ){
								r_SATA_STATUS_tmp = STATUS_POPEQ;
								r_SATA_EQ_DATA_2_tmp = 8;
								//POPEQDMAWRITE=0;
							}
							else
								r_SATA_STATUS_tmp = STATUS_IDLE;

						} else {
							r_SATA_STATUS_tmp = STATUS_POPEQ;
							r_SATA_EQ_DATA_2_tmp = 8;
						}

						}

					}


					break;

					case STATUS_POPEQ:

					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//	"==========================================STATUS_POPEQ\n");
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "				Flag : %d\n",
					//	flag);
					//r_SATA_STATUS_tmp=STATUS_IDLE;
					r_SATA_EQ_CTRL_tmp = 0;
					//pop event queue
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "	EQ Front\n");
					CMD_Temp = EQ.front();
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "	%x %x %x\n",
					//	CMD_Temp.cmd_type, CMD_Temp.lba, CMD_Temp.sector_count);

					DMAREADlba = CMD_Temp.lba;
					DMAREADsector_count = CMD_Temp.sector_count;
					PageDMASectCount = DMAREADsector_count;
					DMAREADcmd_type = CMD_Temp.cmd_type;
					DMAREAD_DONE = 0;

					PageDMACount = ((DMAREADsector_count - 1) >> 2) + 1;
					r_SATA_EQ_DATA_0_tmp = CMD_Temp.sector_count << 16;
					//r_SATA_EQ_DATA_0_tmp=r_SATA_EQ_DATA_0_tmp<<16;
					r_SATA_EQ_DATA_1_tmp = CMD_Temp.lba | CMD_Temp.cmd_type << 31;

					r_SATA_EQ_DATA_2_tmp = 0;		//CHECK

					EQ.pop();
					r_SATA_EQ_STATUS_tmp = r_SATA_EQ_STATUS - (1 << 16);//if Event Queue full -> exception !!
					//}
					//wait(1);
					r_SATA_STATUS_tmp = STATUS_HostTX;

					rr_sect_offset  = DMAREADlba % 4;
					rr_remain_sects = PageDMASectCount;
					rr_num_sector_to_write ;

					if (( rr_sect_offset + rr_remain_sects ) < 4 )
					{
						rr_num_sector_to_write = rr_remain_sects ;
					}
					else
					{
						rr_num_sector_to_write = 4 - rr_sect_offset;
					}


					//
					//EQ.pop();
					break;
					//case STATUS_HOST:
					//  	break;
			case STATUS_HostTX:	//  write Device Host Data to FIS register
					r_SATA_STATUS_tmp = STATUS_IDLE;
					break;

			case STATUS_InterruptWait:
					//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		STATUS_InterruptWait\n");
					if (r_SATA_INSERT_EQ_R == 1) {
						r_SATA_STATUS_tmp = STATUS_EQ_R;
						intPulse = 0;
						FIQ_int_SMaster = intPulse;
					} else if (r_SATA_INSERT_EQ_W == 1) {
						r_SATA_STATUS_tmp = STATUS_EQ_W;
						intPulse = 0;
						FIQ_int_SMaster = intPulse;
					}

					else
						r_SATA_STATUS_tmp = STATUS_InterruptWait;//====================CHECK!

					break;

			case STATUS_EQ_R:
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		STATUS_EQ_R\n");
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//	"		SATA_CTRL_2 : %x\n", r_SATA_CTRL_2);
					//Insert event Queue
					//===========================================CHANGE_
					if (r_SATA_EQ_STATUS != (128<<16)) {
						CMD_Temp.cmd_type = r_SATA_FIS_H2D_4;
						CMD_Temp.lba = r_SATA_FIS_H2D_1 | r_SATA_FIS_H2D_2 << 24;
						CMD_Temp.sector_count = r_SATA_FIS_H2D_3;
						CMD_Temp.C_DMA_DONE = 0;
						EQ.push(CMD_Temp);
						CMD_Temp2 = EQ.front();
						//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "	%x %x %x\n",
						//		CMD_Temp2.cmd_type, CMD_Temp2.lba,
						//		CMD_Temp2.sector_count);
						r_SATA_INSERT_EQ_R_tmp = 0;
						//if(Equal_flag==1) r_SATA_STATUS_tmp=STATUS_HostTX;
						r_SATA_EQ_STATUS_tmp = r_SATA_EQ_STATUS + (1 << 16);//if Event Queue full -> exception !!
					}
					r_SATA_STATUS_tmp = STATUS_IDLE;				//CHANGE
					//r_SATA_EQ_STATUS_tmp=r_SATA_EQ_STATUS+1;	//if Event Queue full -> exception !!
					// EQ Check
					if( EQ.size() >= Eq_limit_to_Switcher  )
					{
						r_SATA_TempReg0_tmp = Switch_Nope_EQ_Active;
					}
					else
					{
						r_SATA_TempReg0_tmp = Switch_Nope;
					}
					//Equal_flag=0;
					break;
			case STATUS_EQ_W:
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		STATUS_EQ_W\n");
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//	"		SATA_CTRL_2 : %x\n", r_SATA_CTRL_2);
					//Insert event Queue
					if (r_SATA_EQ_STATUS != (128<<16)) {
						CMD_Temp.cmd_type = r_SATA_FIS_H2D_4;
						CMD_Temp.lba = r_SATA_FIS_H2D_1 | r_SATA_FIS_H2D_2 << 24;
						CMD_Temp.sector_count = r_SATA_FIS_H2D_3;
						CMD_Temp.C_DMA_DONE = 0;
						PageDMASectCount_W=r_SATA_FIS_H2D_3;
						PageDMACount_W = ((PageDMASectCount_W - 1) >> 2) + 1;
						EQ.push(CMD_Temp);
						CMD_Temp2 = EQ.front();
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "	%x %x %x\n",
						//	CMD_Temp2.cmd_type, CMD_Temp2.lba,
						//	CMD_Temp2.sector_count);

						//Data Insert In Sata_Write_Q
						r_SATA_INSERT_EQ_W_tmp = 0;
						r_SATA_STATUS_tmp = STATUS_IDLE;	//CHANGE
						r_SATA_EQ_STATUS_tmp = r_SATA_EQ_STATUS + (1 << 16);


						yy_sect_offset  = CMD_Temp.lba % 4;
						yy_remain_sects = PageDMASectCount_W;
						yy_num_sector_to_write ;

						if (( yy_sect_offset + yy_remain_sects ) < 4 )
						{
							yy_num_sector_to_write = yy_remain_sects ;
						}
						else
						{
							yy_num_sector_to_write = 4 - yy_sect_offset;
						}


						//if(Equal_flag==1) r_SATA_STATUS_tmp=STATUS_HostTX;
						//Equal_flag=0;
						//			for (uint32_t j = 0; j < CMD_Temp.sector_count; j++)	///NOWADD
						//				Sata_Write_Q.push(CMD_Temp.lba);
					}
					r_SATA_STATUS_tmp = STATUS_IDLE;
					// EQ Check
					if( EQ.size() >= Eq_limit_to_Switcher   )
					{
						r_SATA_TempReg0_tmp = Switch_Nope_EQ_Active;
					}
					else
					{
						r_SATA_TempReg0_tmp = Switch_Nope;
					}
					break;

			case STATUS_DMA_R:
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		STATUS_DMA_R\n");

					r_SATA_STATUS_tmp = STATUS_HostRX;
					break;
			case STATUS_DMA_W:
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		STATUS_DMA_W\n");
					//DMA_Transaction( bool StartBit, bool DMA_CMD  , uint32_t DST_Addr, uint32_t m_Size );

					break;
			case STATUS_HostRX:
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		STATUS_HostRX\n");
					break;
			default:
					break;
		}		//
		//	=======================================================================================ONLYSATATEST
		BM_R_temp = BM_read_limit_SSlave;
		BM_W_temp = BM_write_limit_SSlave;

	} else
		RESETCHCOUNT--;

	dout_Switch_SMaster = r_SATA_TempReg0;

	BM_R_size_SMaster = r_SATA_RBUF_SIZE;
	BM_W_size_SMaster = r_SATA_WBUF_SIZE;
}

void SATADevice::update() {

	// the following message will be printed only in the debug version of MxExplorer
	if (p_enableDbgMsg == true) {
		//message(eslapi::CASI_MSG_INFO, "Executing update function");
	}

	if (first) {				// is changed by TB
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
		//	"This UPDATE function\n");
	}
	// TODO:  Add your update code here.
	// ...

	//ADD JH
	uint64_t offset = 0;
	uint64_t w_data = 0;
	//uint64_t m_currentWait=0;
	AHBv2_Process_S_spss->clear();

	AHBv2_Process_S_spss->setSig(HREADYOUT, true);

	if (first) {				// is changed by TB
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "OUT addr %x\n", _addr);
		first = false;
	}

	if (_isDataCycleActive) {
		if (--_currentWait <= 0) {
			_currentWait = _waitCycles;
			_isDataCycleActive = false;

			offset = _addr - p_baseaddr;
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "addr %x\n", _addr);

			if (_isWrite) {

				w_data = AHBv2_Process_S_spss->getWData(0);

				switch (offset) {
					case SATA_CTRL_1:
						r_SATA_CTRL_1_tmp = w_data;
						break;

					case SATA_INT_ENABLE:
						r_SATA_INT_ENABLE_tmp = w_data;
						break;

					case SATA_INT_STAT:
						r_SATA_INT_STAT_tmp = w_data;
						break;

					case SATA_CTRL_2:
						r_SATA_CTRL_2_tmp = w_data;
						break;

					case SATA_FIS_D2H_0:
						r_SATA_FIS_D2H_0_tmp = w_data;
						break;

					case SATA_FIS_D2H_1:
						r_SATA_FIS_D2H_1_tmp = w_data;
						break;

					case SATA_FIS_D2H_2:
						r_SATA_FIS_D2H_2_tmp = w_data;
						break;

					case SATA_FIS_D2H_3:
						r_SATA_FIS_D2H_3_tmp = w_data;
						break;

					case SATA_FIS_D2H_4:
						r_SATA_FIS_D2H_4_tmp = w_data;
						break;

					case SATA_FIS_D2H_5:
						r_SATA_FIS_D2H_5_tmp = w_data;
						break;

					case SATA_FIS_D2H_6:
						r_SATA_FIS_D2H_6_tmp = w_data;
						break;

					case SATA_FIS_D2H_7:
						r_SATA_FIS_D2H_7_tmp = w_data;
						break;
						//D2H
					case SATA_FIS_D2H_LEN:
						r_SATA_FIS_D2H_LEN_tmp = w_data;
						break;

					case SATA_FIS_H2D_0:
						r_SATA_FIS_H2D_0_tmp = w_data;
						break;

					case SATA_FIS_H2D_1:
						r_SATA_FIS_H2D_1_tmp = w_data;
						break;

					case SATA_FIS_H2D_2:
						r_SATA_FIS_H2D_2_tmp = w_data;
						break;

					case SATA_FIS_H2D_3:
						r_SATA_FIS_H2D_3_tmp = w_data;
						break;

					case SATA_FIS_H2D_4:
						r_SATA_FIS_H2D_4_tmp = w_data;
						break;

					case SATA_FIS_H2D_5:
						r_SATA_FIS_H2D_5_tmp = w_data;
						break;

					case SATA_FIS_H2D_6:
						r_SATA_FIS_H2D_6_tmp = w_data;
						break;

					case SATA_FIS_H2D_7:
						r_SATA_FIS_H2D_7_tmp = w_data;
						break;
						//H2D
					case SATA_XFER_BYTES:
						r_SATA_XFER_BYTES_tmp = w_data;
						break;

					case SATA_XFER_BYTES_REMAIN:
						r_SATA_XFER_BYTES_REMAIN_tmp = w_data;
						break;

					case SATA_SACTIVE:
						r_SATA_SACTIVE_tmp = w_data;
						break;

					case SATA_NCQ_BMP_1:
						r_SATA_NCQ_BMP_1_tmp = w_data;
						break;

					case SATA_NCQ_BMP_2:
						r_SATA_NCQ_BMP_2_tmp = w_data;
						break;

					case SATA_STATUS:
						r_SATA_STATUS_tmp = w_data;
						break;

					case SATA_SECT_OFFSET:
						r_SATA_SECT_OFFSET_tmp = w_data;
						break;

					case SATA_BUF_PAGE_SIZE:
						r_SATA_BUF_PAGE_SIZE_tmp = w_data;
						break;

					case SATA_RESET_FIFO_1:
						r_SATA_RESET_FIFO_1_tmp = w_data;
						break;

					case SATA_MANUAL_MODE_ADDR:
						r_SATA_MANUAL_MODE_ADDR_tmp = w_data;
						break;

					case SATA_CTRL_3:
						r_SATA_CTRL_3_tmp = w_data;
						break;

					case SATA_FIFO_1_STATUS:
						r_SATA_FIFO_1_STATUS_tmp = w_data;
						break;

					case SATA_FIFO_2_STATUS:
						r_SATA_FIFO_2_STATUS_tmp = w_data;
						break;

					case SATA_FIFO_S_STATUS:
						r_SATA_FIFO_S_STATUS_tmp = w_data;
						break;

					case SATA_PHY_STATUS:
						r_SATA_PHY_STATUS_tmp = w_data;
						break;

					case SATA_ERROR:
						r_SATA_ERROR_tmp = w_data;
						break;

					case SATA_PHY_CTRL:
						r_SATA_PHY_CTRL_tmp = w_data;
						break;

					case SATA_CFG_1:
						r_SATA_CFG_1_tmp = w_data;
						break;

					case SATA_CFG_2:
						r_SATA_CFG_2_tmp = w_data;
						break;

					case SATA_CFG_3:
						r_SATA_CFG_3_tmp = w_data;
						break;

					case SATA_CFG_4:
						r_SATA_CFG_4_tmp = w_data;
						break;

					case SATA_CFG_5:
						r_SATA_CFG_5_tmp = w_data;
						break;

					case SATA_CFG_6:
						r_SATA_CFG_6_tmp = w_data;
						break;

					case SATA_CFG_7:
						r_SATA_CFG_7_tmp = w_data;
						break;

					case SATA_WBUF_BASE:
						r_SATA_WBUF_BASE_tmp = w_data;
						break;

					case SATA_RBUF_BASE:
						r_SATA_RBUF_BASE_tmp = w_data;
						break;

					case SATA_WBUF_SIZE:
						r_SATA_WBUF_SIZE_tmp = w_data;
						break;

					case SATA_RBUF_SIZE:
						r_SATA_RBUF_SIZE_tmp = w_data;
						break;

					case SATA_WBUF_MARGIN:
						r_SATA_WBUF_MARGIN_tmp = w_data;
						break;

					case SATA_RESET_WBUF_PTR:
						r_SATA_RESET_WBUF_PTR_tmp = w_data;
						break;

					case SATA_RESET_RBUF_PTR:
						r_SATA_RESET_RBUF_PTR_tmp = w_data;
						break;

					case SATA_NCQ_BASE:
						r_SATA_NCQ_BASE_tmp = w_data;
						break;

					case SATA_WBUF_PTR:
						r_SATA_WBUF_PTR_tmp = w_data;
						break;

					case SATA_RBUF_PTR:
						r_SATA_RBUF_PTR_tmp = w_data;
						break;

					case SATA_WBUF_FREE:
						r_SATA_WBUF_FREE_tmp = w_data;
						break;

					case SATA_RBUF_PENDING:
						r_SATA_RBUF_PENDING_tmp = w_data;
						break;

					case SATA_CFG_8:
						r_SATA_CFG_8_tmp = w_data;
						break;

					case SATA_MAX_LBA:
						r_SATA_MAX_LBA_tmp = w_data;
						break;

					case SATA_CFG_9:
						r_SATA_CFG_9_tmp = w_data;
						break;

					case SATA_INSERT_EQ_W:
						r_SATA_INSERT_EQ_W_tmp = w_data;
						break;

					case SATA_LBA:
						r_SATA_LBA_tmp = w_data;
						break;

					case SATA_SECT_CNT:
						r_SATA_SECT_CNT_tmp = w_data;
						break;

					case SATA_INSERT_EQ_R:
						r_SATA_INSERT_EQ_R_tmp = w_data;
						break;

					case SATA_NCQ_ORDER:
						r_SATA_NCQ_ORDER_tmp = w_data;
						break;

					case SATA_NCQ_CTRL:
						r_SATA_NCQ_CTRL_tmp = w_data;
						break;

					case SATA_CFG_10:
						r_SATA_CFG_10_tmp = w_data;
						break;

					case SATA_EQ_CFG_1:
						r_SATA_EQ_CFG_1_tmp = w_data;
						break;

					case SATA_EQ_CTRL:
						r_SATA_EQ_CTRL_tmp = w_data;
						break;

					case SATA_EQ_PTR:
						r_SATA_EQ_PTR_tmp = w_data;
						break;

					case SATA_EQ_STATUS:
						r_SATA_EQ_STATUS_tmp = w_data;
						break;

					case SATA_EQ_DATA_0:
						r_SATA_EQ_DATA_0_tmp = w_data;
						break;

					case SATA_EQ_DATA_1:
						r_SATA_EQ_DATA_1_tmp = w_data;
						break;

					case SATA_EQ_DATA_2:
						r_SATA_EQ_DATA_2_tmp = w_data;
						break;

					case SATA_EQ_CFG_2:
						r_SATA_EQ_CFG_2_tmp = w_data;
						break;

					case SATA_TempReg0:
						r_SATA_TempReg0_tmp = w_data;
						break;

					case SATA_TempReg1:
						r_SATA_TempReg1_tmp = w_data;
						break;

					default:
						if (p_enableDbgMsg) {
							//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//		"(Error! Access to out of range!(offset : 0x%x))\n",
							//		offset);
						}
						break;

				}

			}	/////////
			else						//READ DATA
			{

				switch (offset) {
					case SATA_CTRL_1:
						AHBv2_Process_S_spss->setRData(r_SATA_CTRL_1);
						break;

					case SATA_INT_ENABLE:
						AHBv2_Process_S_spss->setRData(r_SATA_INT_ENABLE);
						break;

					case SATA_INT_STAT:
						AHBv2_Process_S_spss->setRData(r_SATA_INT_STAT);
						break;

					case SATA_CTRL_2:
						AHBv2_Process_S_spss->setRData(r_SATA_CTRL_2);
						break;

					case SATA_FIS_D2H_0:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_0);
						break;

					case SATA_FIS_D2H_1:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_1);
						break;

					case SATA_FIS_D2H_2:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_2);
						break;

					case SATA_FIS_D2H_3:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_3);
						break;

					case SATA_FIS_D2H_4:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_4);
						break;

					case SATA_FIS_D2H_5:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_5);
						break;

					case SATA_FIS_D2H_6:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_6);
						break;

					case SATA_FIS_D2H_7:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_7);
						break;
						//D2H
					case SATA_FIS_D2H_LEN:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_LEN);
						break;

					case SATA_FIS_H2D_0:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_0);
						break;

					case SATA_FIS_H2D_1:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_1);
						break;

					case SATA_FIS_H2D_2:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_2);
						break;

					case SATA_FIS_H2D_3:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_3);
						break;

					case SATA_FIS_H2D_4:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_4);
						break;

					case SATA_FIS_H2D_5:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_5);
						break;

					case SATA_FIS_H2D_6:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_6);
						break;

					case SATA_FIS_H2D_7:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_7);
						break;
						//H2D
					case SATA_XFER_BYTES:
						AHBv2_Process_S_spss->setRData(r_SATA_XFER_BYTES);
						break;

					case SATA_XFER_BYTES_REMAIN:
						AHBv2_Process_S_spss->setRData(r_SATA_XFER_BYTES_REMAIN);
						break;

					case SATA_SACTIVE:
						AHBv2_Process_S_spss->setRData(r_SATA_SACTIVE);
						break;

					case SATA_NCQ_BMP_1:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_BMP_1);
						break;

					case SATA_NCQ_BMP_2:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_BMP_2);
						break;

					case SATA_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_STATUS);
						break;

					case SATA_SECT_OFFSET:
						AHBv2_Process_S_spss->setRData(r_SATA_SECT_OFFSET);
						break;

					case SATA_BUF_PAGE_SIZE:
						AHBv2_Process_S_spss->setRData(r_SATA_BUF_PAGE_SIZE);
						break;

					case SATA_RESET_FIFO_1:
						AHBv2_Process_S_spss->setRData(r_SATA_RESET_FIFO_1);
						break;

					case SATA_MANUAL_MODE_ADDR:
						AHBv2_Process_S_spss->setRData(r_SATA_MANUAL_MODE_ADDR);
						break;

					case SATA_CTRL_3:
						AHBv2_Process_S_spss->setRData(r_SATA_CTRL_3);
						break;

					case SATA_FIFO_1_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_FIFO_1_STATUS);
						break;

					case SATA_FIFO_2_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_FIFO_2_STATUS);
						break;

					case SATA_FIFO_S_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_FIFO_S_STATUS);
						break;

					case SATA_PHY_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_PHY_STATUS);
						break;

					case SATA_ERROR:
						AHBv2_Process_S_spss->setRData(r_SATA_ERROR);
						break;

					case SATA_PHY_CTRL:
						AHBv2_Process_S_spss->setRData(r_SATA_PHY_CTRL);
						break;

					case SATA_CFG_1:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_1);
						break;

					case SATA_CFG_2:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_2);
						break;

					case SATA_CFG_3:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_3);
						break;

					case SATA_CFG_4:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_4);
						break;

					case SATA_CFG_5:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_5);
						break;

					case SATA_CFG_6:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_6);
						break;

					case SATA_CFG_7:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_7);
						break;

					case SATA_WBUF_BASE:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_BASE);
						break;

					case SATA_RBUF_BASE:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_BASE);
						break;

					case SATA_WBUF_SIZE:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_SIZE);
						break;

					case SATA_RBUF_SIZE:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_SIZE);
						break;

					case SATA_WBUF_MARGIN:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_MARGIN);
						break;

					case SATA_RESET_WBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_RESET_WBUF_PTR);
						break;

					case SATA_RESET_RBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_RESET_RBUF_PTR);
						break;

					case SATA_NCQ_BASE:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_BASE);
						break;

					case SATA_WBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_PTR);
						break;

					case SATA_RBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_PTR);
						break;

					case SATA_WBUF_FREE:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_FREE);
						break;

					case SATA_RBUF_PENDING:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_PENDING);
						break;

					case SATA_CFG_8:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_8);
						break;

					case SATA_MAX_LBA:
						AHBv2_Process_S_spss->setRData(r_SATA_MAX_LBA);
						break;

					case SATA_CFG_9:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_9);
						break;

					case SATA_INSERT_EQ_W:
						AHBv2_Process_S_spss->setRData(r_SATA_INSERT_EQ_W);
						break;

					case SATA_LBA:
						AHBv2_Process_S_spss->setRData(r_SATA_LBA);
						break;

					case SATA_SECT_CNT:
						AHBv2_Process_S_spss->setRData(r_SATA_SECT_CNT);
						break;

					case SATA_INSERT_EQ_R:
						AHBv2_Process_S_spss->setRData(r_SATA_INSERT_EQ_R);
						break;

					case SATA_NCQ_ORDER:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_ORDER);
						break;

					case SATA_NCQ_CTRL:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_CTRL);
						break;

					case SATA_CFG_10:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_10);
						break;

					case SATA_EQ_CFG_1:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_CFG_1);
						break;

					case SATA_EQ_CTRL:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_CTRL);
						break;

					case SATA_EQ_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_PTR);
						break;

					case SATA_EQ_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_STATUS);
						break;

					case SATA_EQ_DATA_0:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_DATA_0);
						break;

					case SATA_EQ_DATA_1:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_DATA_1);
						break;

					case SATA_EQ_DATA_2:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_DATA_2);
						break;

					case SATA_EQ_CFG_2:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_CFG_2);
						break;

					case SATA_TempReg0:
						AHBv2_Process_S_spss->setRData(r_SATA_TempReg0);
						break;

					case SATA_TempReg1:
						AHBv2_Process_S_spss->setRData(r_SATA_TempReg1);
						break;

					default:
						if (p_enableDbgMsg) {
							//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//		"(Error! Access to out of range!(offset : 0x%x))\n",
							//		offset);
						}
						AHBv2_Process_S_spss->setRData(0);
						break;

				}
			}
			AHBv2_Process_S_spss->setSig(HREADYOUT, true);
		}
	}		//-----------------------------------------------DATA phase

	AHBv2_Process_S_spss->setSig(HREADYOUT, false);

	//-----------------------------------------------------------
	if ((AHBv2_Process_S_spss->getSig(HTRANS) != AHB2_TRANS_IDLE)
			&& (AHBv2_Process_S_spss->getSig(HTRANS) != AHB2_TRANS_BUSY)
			&& (AHBv2_Process_S_spss->getSig(HSEL))
			&& (AHBv2_Process_S_spss->getSig(HREADY))) {
		_addr = AHBv2_Process_S_spss->getSig(HADDR);

		if (AHBv2_Process_S_spss->getSig(HWRITE)) {
			_isWrite = true;
		} else {
			_isWrite = false;

			//zero wait

			if (_currentWait <= 0) {
				//read

				offset = _addr - p_baseaddr;
				switch (offset) {
					case SATA_CTRL_1:
						AHBv2_Process_S_spss->setRData(r_SATA_CTRL_1);
						break;

					case SATA_INT_ENABLE:
						AHBv2_Process_S_spss->setRData(r_SATA_INT_ENABLE);
						break;

					case SATA_INT_STAT:
						AHBv2_Process_S_spss->setRData(r_SATA_INT_STAT);
						break;

					case SATA_CTRL_2:
						AHBv2_Process_S_spss->setRData(r_SATA_CTRL_2);
						break;

					case SATA_FIS_D2H_0:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_0);
						break;

					case SATA_FIS_D2H_1:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_1);
						break;

					case SATA_FIS_D2H_2:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_2);
						break;

					case SATA_FIS_D2H_3:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_3);
						break;

					case SATA_FIS_D2H_4:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_4);
						break;

					case SATA_FIS_D2H_5:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_5);
						break;

					case SATA_FIS_D2H_6:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_6);
						break;

					case SATA_FIS_D2H_7:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_7);
						break;
						//D2H
					case SATA_FIS_D2H_LEN:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_D2H_LEN);
						break;

					case SATA_FIS_H2D_0:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_0);
						break;

					case SATA_FIS_H2D_1:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_1);
						break;

					case SATA_FIS_H2D_2:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_2);
						break;

					case SATA_FIS_H2D_3:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_3);
						break;

					case SATA_FIS_H2D_4:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_4);
						break;

					case SATA_FIS_H2D_5:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_5);
						break;

					case SATA_FIS_H2D_6:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_6);
						break;

					case SATA_FIS_H2D_7:
						AHBv2_Process_S_spss->setRData(r_SATA_FIS_H2D_7);
						break;
						//H2D
					case SATA_XFER_BYTES:
						AHBv2_Process_S_spss->setRData(r_SATA_XFER_BYTES);
						break;

					case SATA_XFER_BYTES_REMAIN:
						AHBv2_Process_S_spss->setRData(r_SATA_XFER_BYTES_REMAIN);
						break;

					case SATA_SACTIVE:
						AHBv2_Process_S_spss->setRData(r_SATA_SACTIVE);
						break;

					case SATA_NCQ_BMP_1:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_BMP_1);
						break;

					case SATA_NCQ_BMP_2:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_BMP_2);
						break;

					case SATA_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_STATUS);
						break;

					case SATA_SECT_OFFSET:
						AHBv2_Process_S_spss->setRData(r_SATA_SECT_OFFSET);
						break;

					case SATA_BUF_PAGE_SIZE:
						AHBv2_Process_S_spss->setRData(r_SATA_BUF_PAGE_SIZE);
						break;

					case SATA_RESET_FIFO_1:
						AHBv2_Process_S_spss->setRData(r_SATA_RESET_FIFO_1);
						break;

					case SATA_MANUAL_MODE_ADDR:
						AHBv2_Process_S_spss->setRData(r_SATA_MANUAL_MODE_ADDR);
						break;

					case SATA_CTRL_3:
						AHBv2_Process_S_spss->setRData(r_SATA_CTRL_3);
						break;

					case SATA_FIFO_1_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_FIFO_1_STATUS);
						break;

					case SATA_FIFO_2_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_FIFO_2_STATUS);
						break;

					case SATA_FIFO_S_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_FIFO_S_STATUS);
						break;

					case SATA_PHY_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_PHY_STATUS);
						break;

					case SATA_ERROR:
						AHBv2_Process_S_spss->setRData(r_SATA_ERROR);
						break;

					case SATA_PHY_CTRL:
						AHBv2_Process_S_spss->setRData(r_SATA_PHY_CTRL);
						break;

					case SATA_CFG_1:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_1);
						break;

					case SATA_CFG_2:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_2);
						break;

					case SATA_CFG_3:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_3);
						break;

					case SATA_CFG_4:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_4);
						break;

					case SATA_CFG_5:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_5);
						break;

					case SATA_CFG_6:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_6);
						break;

					case SATA_CFG_7:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_7);
						break;

					case SATA_WBUF_BASE:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_BASE);
						break;

					case SATA_RBUF_BASE:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_BASE);
						break;

					case SATA_WBUF_SIZE:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_SIZE);
						break;

					case SATA_RBUF_SIZE:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_SIZE);
						break;

					case SATA_WBUF_MARGIN:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_MARGIN);
						break;

					case SATA_RESET_WBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_RESET_WBUF_PTR);
						break;

					case SATA_RESET_RBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_RESET_RBUF_PTR);
						break;

					case SATA_NCQ_BASE:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_BASE);
						break;

					case SATA_WBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_PTR);
						break;

					case SATA_RBUF_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_PTR);
						break;

					case SATA_WBUF_FREE:
						AHBv2_Process_S_spss->setRData(r_SATA_WBUF_FREE);
						break;

					case SATA_RBUF_PENDING:
						AHBv2_Process_S_spss->setRData(r_SATA_RBUF_PENDING);
						break;

					case SATA_CFG_8:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_8);
						break;

					case SATA_MAX_LBA:
						AHBv2_Process_S_spss->setRData(r_SATA_MAX_LBA);
						break;

					case SATA_CFG_9:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_9);
						break;

					case SATA_INSERT_EQ_W:
						AHBv2_Process_S_spss->setRData(r_SATA_INSERT_EQ_W);
						break;

					case SATA_LBA:
						AHBv2_Process_S_spss->setRData(r_SATA_LBA);
						break;

					case SATA_SECT_CNT:
						AHBv2_Process_S_spss->setRData(r_SATA_SECT_CNT);
						break;

					case SATA_INSERT_EQ_R:
						AHBv2_Process_S_spss->setRData(r_SATA_INSERT_EQ_R);
						break;

					case SATA_NCQ_ORDER:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_ORDER);
						break;

					case SATA_NCQ_CTRL:
						AHBv2_Process_S_spss->setRData(r_SATA_NCQ_CTRL);
						break;

					case SATA_CFG_10:
						AHBv2_Process_S_spss->setRData(r_SATA_CFG_10);
						break;

					case SATA_EQ_CFG_1:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_CFG_1);
						break;

					case SATA_EQ_CTRL:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_CTRL);
						break;

					case SATA_EQ_PTR:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_PTR);
						break;

					case SATA_EQ_STATUS:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_STATUS);
						break;

					case SATA_EQ_DATA_0:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_DATA_0);
						break;

					case SATA_EQ_DATA_1:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_DATA_1);
						break;

					case SATA_EQ_DATA_2:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_DATA_2);
						break;

					case SATA_EQ_CFG_2:
						AHBv2_Process_S_spss->setRData(r_SATA_EQ_CFG_2);
						break;

					case SATA_TempReg0:
						AHBv2_Process_S_spss->setRData(r_SATA_TempReg0);
						break;

					case SATA_TempReg1:
						AHBv2_Process_S_spss->setRData(r_SATA_TempReg1);
						break;

					default:
						if (p_enableDbgMsg) {
							//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//	"(Error! Access to out of range!(offset : 0x%x))\n",
							//	offset);
						}
						AHBv2_Process_S_spss->setRData(0);
						break;

				}	//Switch END
			}	//IF END

		}
		_isDataCycleActive = true;

		if (_currentWait <= 0) {
			//read

			AHBv2_Process_S_spss->setSig(HREADYOUT, true);
		} else {

			AHBv2_Process_S_spss->setSig(HREADYOUT, false);
		}

	} else {
		_isDataCycleActive = false;
	}

	//=====================================================================================================

	switch (r_SATA_STATUS) {
		case STATUS_IDLE:

			//r_SATA_EQ_DATA_2=8;

			break;

		case STATUS_HostTX:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "%d\n %d\n %d\n",
			//	(r_SATA_CTRL_2 == S_DMA_READ | COMPLETE),
			//	(BM_R_temp != r_SATA_RBUF_PTR), (EQ.empty() == 0));
			break;
		default:
			break;
	}


	if (r_SATA_CTRL_2 != 0) {
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "!!r_SATA_CTRL_2 : %x\n",r_SATA_CTRL_2);
		//if((r_SATA_CTRL_2==S_DMA_READ|COMPLETE) &&(BM_R_temp!=r_SATA_RBUF_PTR)&&(EQ.empty()==0) )				//READ SECTION
		if ((r_SATA_CTRL_2 == 0x420) && (BM_R_temp != r_SATA_RBUF_PTR)
				&& (DMAREADcmd_type == 0))
		{




			DST_Addr = 0x60000000 + r_SATA_RBUF_BASE + r_SATA_RBUF_PTR * r_SATA_BUF_PAGE_SIZE;
			//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
			//					"DST Addr : %x sect : %d \n", DST_Addr,
			//					DMAREADsector_count);

			//TEST			S_DMA_DONE_CHECK = DMA_Transaction(1, DMA_READ, DST_Addr + rr_sect_offset*512, rr_num_sector_to_write *128);

			//TEST
			//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
			//				"		READ DMASTART	dstAddr	0x%x	sector %d\n",DST_Addr + rr_sect_offset*512,rr_num_sector_to_write *128);

			S_DMA_DONE_CHECK= runDMA(0, DST_Addr + rr_sect_offset*512, rr_num_sector_to_write *128);


			//S_DMA_DONE_CHECK = runDMA(0, DST_Addr, EQ.front().sector_count);
			//	S_DMA_DONE_CHECK = DMA_Transaction(1, DMA_READ, DST_Addr,
			//			DMAREADsector_count * 128);
			if (S_DMA_DONE_CHECK == 1) {
				//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//						"READ DST Addr : %x sect : %d \n", DST_Addr,
				//						DMAREADsector_count);
				//D2H_Read_COMMAND_DONE = 1;
				//EQ.pop();


				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//	"[DONE SUB DMA READ]  DST Addr : %x sect : %d PageCnt : %d\n",
				//	DST_Addr, DMAREADsector_count, PageDMASectCount);

				rr_sect_offset   = 0;
				rr_remain_sects -= rr_num_sector_to_write;


				if( ( r_SATA_RBUF_PTR + 1 ) == r_SATA_RBUF_SIZE )
					r_SATA_RBUF_PTR_tmp = 0;
				else
					r_SATA_RBUF_PTR_tmp = r_SATA_RBUF_PTR + 1;

				//+ ((DMAREADsector_count - 1) >> 2) + 1;


				S_DMA_DONE_CHECK = 0;

				if(rr_remain_sects != 0)
				{

					if ((rr_sect_offset + rr_remain_sects) < 4 )
					{
						rr_num_sector_to_write = rr_remain_sects;
					}
					else
					{
						rr_num_sector_to_write = 4 - rr_sect_offset;
					}

				}
				else{
					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//		"[END DMA READ] DST Addr : %x sect : %d PageCnt : %d\n\n",
					//		DST_Addr, DMAREADsector_count, PageDMASectCount);
					D2H_Read_COMMAND_DONE = 1;
					r_SATA_CTRL_2_tmp = 0;
					S_DMA_DONE_CHECK = 0;
				}


				//
				//	Sata_RFile<<"r "<<Sata_R_out<<" "<<DMAREADsector_count<<" "<<<<endl;
				//	Sata_R_out++;
			}


		}
		//else if((r_SATA_CTRL_2==S_DMA_WRITE|COMPLETE) &&(BM_W_temp!=++r_SATA_WBUF_PTR) &&(EQ.empty()==0))
		else if ((r_SATA_CTRL_2 == 0x4020)
				&& (BM_W_temp != (r_SATA_WBUF_PTR + 1)) && (EQ.empty() == 0)
				&& (CMD_Temp.cmd_type == 1)) {

			DST_Addr = 0x60000000 + r_SATA_WBUF_BASE + r_SATA_WBUF_PTR * r_SATA_BUF_PAGE_SIZE;

			//TEST				S_DMA_DONE_CHECK = DMA_Transaction(1, DMA_WRITE, DST_Addr + yy_sect_offset*512, yy_num_sector_to_write *128);

			//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
			//					"		WRTIE DMASTART	dstAddr	0x%x	sector %d\n",DST_Addr + yy_sect_offset*512,yy_num_sector_to_write *128);

			S_DMA_DONE_CHECK=runDMA(1,  DST_Addr + yy_sect_offset*512, yy_num_sector_to_write *128);

			/*	//Write DMA Print Check
					S_DMA_DONE_CHECK = DMA_Transaction(1, DMA_WRITE, DST_Addr,
					CMD_Temp.sector_count * 128);
					*/
			//S_DMA_DONE_CHECK = runDMA(1, DST_Addr, EQ.front().sector_count);//WRITE
			if (S_DMA_DONE_CHECK == 1) {
				//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//						"===UPDATE -> DMA DONE\n	");
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//	"[DONE SUB DMA Write] DST Addr : %x sect : %d PageCnt : %d \n ",
				//	DST_Addr,PageDMASectCount_W, CMD_Temp.sector_count);

				//EQ.pop();

				yy_sect_offset   = 0;
				yy_remain_sects -= yy_num_sector_to_write;


				if((r_SATA_WBUF_PTR +1)==r_SATA_WBUF_SIZE)
					r_SATA_WBUF_PTR_tmp=0;
				else
					r_SATA_WBUF_PTR_tmp=r_SATA_WBUF_PTR+1;

				/*
					 r_SATA_WBUF_PTR_tmp = r_SATA_WBUF_PTR + ((CMD_Temp.sector_count - 1) >> 2) + 1;

					 if( ( r_SATA_WBUF_PTR_tmp ) >= r_SATA_RBUF_SIZE )
					 {
					 r_SATA_WBUF_PTR_tmp = r_SATA_WBUF_PTR_tmp - r_SATA_RBUF_SIZE;
					 }
					 */

				S_DMA_DONE_CHECK=0;

				if(yy_remain_sects != 0)
				{

					if ((yy_sect_offset + yy_remain_sects) < 4 )
					{
						yy_num_sector_to_write = yy_remain_sects;
					}
					else
					{
						yy_num_sector_to_write = 4 - yy_sect_offset;
					}

				}
				else
				{

					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//		"[END DMA Write] DST Addr : %x sect : %d PageCnt : %d \n\n ",
					//		DST_Addr, PageDMASectCount_W,CMD_Temp.sector_count);
					r_SATA_CTRL_2_tmp = 0;
					S_DMA_DONE_CHECK = 0;
					D2H_Write_COMMAND_DONE = 1;
					POPEQDMAWRITE = 1;
					//
					EQ.back().C_DMA_DONE = 1;

				}


			}

			//}
	} else {

	}
}

//----------------------------------------------------------------------------------
//ADD JH
r_SATA_CTRL_1 = r_SATA_CTRL_1_tmp;
r_SATA_INT_ENABLE = r_SATA_INT_ENABLE_tmp;
r_SATA_INT_STAT = r_SATA_INT_STAT_tmp;
r_SATA_CTRL_2 = r_SATA_CTRL_2_tmp;
r_SATA_FIS_D2H_0 = r_SATA_FIS_D2H_0_tmp;
r_SATA_FIS_D2H_1 = r_SATA_FIS_D2H_1_tmp;
r_SATA_FIS_D2H_2 = r_SATA_FIS_D2H_2_tmp;
r_SATA_FIS_D2H_3 = r_SATA_FIS_D2H_3_tmp;
r_SATA_FIS_D2H_4 = r_SATA_FIS_D2H_4_tmp;
r_SATA_FIS_D2H_5 = r_SATA_FIS_D2H_5_tmp;
r_SATA_FIS_D2H_6 = r_SATA_FIS_D2H_6_tmp;
r_SATA_FIS_D2H_7 = r_SATA_FIS_D2H_7_tmp;
r_SATA_FIS_D2H_LEN = r_SATA_FIS_D2H_LEN_tmp;
r_SATA_FIS_H2D_0 = r_SATA_FIS_H2D_0_tmp;
r_SATA_FIS_H2D_1 = r_SATA_FIS_H2D_1_tmp;
r_SATA_FIS_H2D_2 = r_SATA_FIS_H2D_2_tmp;
r_SATA_FIS_H2D_3 = r_SATA_FIS_H2D_3_tmp;
r_SATA_FIS_H2D_4 = r_SATA_FIS_H2D_4_tmp;
r_SATA_FIS_H2D_5 = r_SATA_FIS_H2D_5_tmp;
r_SATA_FIS_H2D_6 = r_SATA_FIS_H2D_6_tmp;
r_SATA_FIS_H2D_7 = r_SATA_FIS_H2D_7_tmp;
r_SATA_XFER_BYTES = r_SATA_XFER_BYTES_tmp;
r_SATA_XFER_BYTES_REMAIN = r_SATA_XFER_BYTES_REMAIN_tmp;
r_SATA_XFER_SECTORS_REMAIN = r_SATA_XFER_SECTORS_REMAIN_tmp;
r_SATA_SACTIVE = r_SATA_SACTIVE_tmp;
r_SATA_NCQ_BMP_1 = r_SATA_NCQ_BMP_1_tmp;
r_SATA_NCQ_BMP_2 = r_SATA_NCQ_BMP_2_tmp;
r_SATA_STATUS = r_SATA_STATUS_tmp;
r_SATA_SECT_OFFSET = r_SATA_SECT_OFFSET_tmp;
r_SATA_BUF_PAGE_SIZE = r_SATA_BUF_PAGE_SIZE_tmp;
r_SATA_RESET_FIFO_1 = r_SATA_RESET_FIFO_1_tmp;
r_SATA_MANUAL_MODE_ADDR = r_SATA_MANUAL_MODE_ADDR_tmp;
r_SATA_CTRL_3 = r_SATA_CTRL_3_tmp;
r_SATA_FIFO_1_STATUS = r_SATA_FIFO_1_STATUS_tmp;
r_SATA_FIFO_2_STATUS = r_SATA_FIFO_2_STATUS_tmp;
r_SATA_FIFO_S_STATUS = r_SATA_FIFO_S_STATUS_tmp;
r_SATA_PHY_STATUS = r_SATA_PHY_STATUS_tmp;
r_SATA_ERROR = r_SATA_ERROR_tmp;
r_SATA_PHY_CTRL = r_SATA_PHY_CTRL_tmp;
r_SATA_CFG_1 = r_SATA_CFG_1_tmp;
r_SATA_CFG_2 = r_SATA_CFG_2_tmp;
r_SATA_CFG_3 = r_SATA_CFG_3_tmp;
r_SATA_CFG_4 = r_SATA_CFG_4_tmp;
r_SATA_CFG_5 = r_SATA_CFG_5_tmp;
r_SATA_CFG_6 = r_SATA_CFG_6_tmp;
r_SATA_CFG_7 = r_SATA_CFG_7_tmp;
r_SATA_WBUF_BASE = r_SATA_WBUF_BASE_tmp;
r_SATA_RBUF_BASE = r_SATA_RBUF_BASE_tmp;
r_SATA_WBUF_SIZE = r_SATA_WBUF_SIZE_tmp;
r_SATA_RBUF_SIZE = r_SATA_RBUF_SIZE_tmp;
r_SATA_WBUF_MARGIN = r_SATA_WBUF_MARGIN_tmp;
r_SATA_RESET_WBUF_PTR = r_SATA_RESET_WBUF_PTR_tmp;
r_SATA_RESET_RBUF_PTR = r_SATA_RESET_RBUF_PTR_tmp;
r_SATA_NCQ_BASE = r_SATA_NCQ_BASE_tmp;
r_SATA_WBUF_PTR = r_SATA_WBUF_PTR_tmp;
r_SATA_RBUF_PTR = r_SATA_RBUF_PTR_tmp;
r_SATA_WBUF_FREE = r_SATA_WBUF_FREE_tmp;
r_SATA_RBUF_PENDING = r_SATA_RBUF_PENDING_tmp;
r_SATA_CFG_8 = r_SATA_CFG_8_tmp;
r_SATA_MAX_LBA = r_SATA_MAX_LBA_tmp;
r_SATA_CFG_9 = r_SATA_CFG_9_tmp;
r_SATA_INSERT_EQ_W = r_SATA_INSERT_EQ_W_tmp;
r_SATA_LBA = r_SATA_LBA_tmp;
r_SATA_SECT_CNT = r_SATA_SECT_CNT_tmp;
r_SATA_INSERT_EQ_R = r_SATA_INSERT_EQ_R_tmp;
r_SATA_NCQ_ORDER = r_SATA_NCQ_ORDER_tmp;
r_SATA_NCQ_CTRL = r_SATA_NCQ_CTRL_tmp;
r_SATA_CFG_10 = r_SATA_CFG_10_tmp;
r_SATA_EQ_CFG_1 = r_SATA_EQ_CFG_1_tmp;
r_SATA_EQ_CTRL = r_SATA_EQ_CTRL_tmp;
r_SATA_EQ_PTR = r_SATA_EQ_PTR_tmp;
r_SATA_EQ_STATUS = r_SATA_EQ_STATUS_tmp;
r_SATA_EQ_DATA_0 = r_SATA_EQ_DATA_0_tmp;
r_SATA_EQ_DATA_1 = r_SATA_EQ_DATA_1_tmp;
r_SATA_EQ_DATA_2 = r_SATA_EQ_DATA_2_tmp;
r_SATA_EQ_CFG_2 = r_SATA_EQ_CFG_2_tmp;
r_SATA_TempReg0 = r_SATA_TempReg0_tmp;
r_SATA_TempReg1 = r_SATA_TempReg1_tmp;

}
void SATADevice::initDMA() {
	dma_running_bank = 0;
	dma_addr = 0;
	dma_cnt = 0;
	dma_write = 0;
	dma_active_data_phase = false;
	dma_wait_data_phase = false;
	dma_bus_granted = false;
	dma_CurIdx = 0;
	//curIdx[bank] = 0;
}
//bool SATADevice::DMA_Transaction( bool StartBit, bool DMA_CMD  , uint32_t DST_Addr, uint32_t m_Size )
bool SATADevice::runDMA(int bWrite, uint32_t DST_Addr, uint32_t m_Size) {
	//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
	//ta			"===============================================DMA_Transaction CALL\n");
	//bWrite==1 -> Write
	//bWrite==0 -> Read
	if (dma_running_bank == 0) {
		initDMA();

		dma_running_bank = 1;
		dma_addr = DST_Addr;					//Adddress
		dma_cnt = m_Size;					//Count
		dma_write = bWrite;

		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
		//		" [Start DMA] addr: 0x%X, cnt: %d, write: %d, \n", dma_addr,
		//		dma_cnt, dma_write);
	}

	bool busGranted = AHBv2_Dram_M_mpms->getSig(HGRANT);
	bool HReady = AHBv2_Dram_M_mpms->getSig(HREADY);

	AHBv2_Dram_M_mpms->clear();
	AHBv2_Dram_M_mpms->setSig(HBUSREQ, true); //default

	//////////////////////Bus granted//////////////////////
	if (busGranted) {
		//////////////////////Data phase//////////////////////
		if (dma_active_data_phase) {
			//////////////////////Write//////////////////////
			if (dma_write) {
				/* Get 32bit data from buffer, and build data up into tmp. */
				//uint32_t tmp = *((uint32_t*)&buffers[bank][curIdx[bank]]);
				//					Master_Data = Sata_Write_Q.front(); // Your Data   ;
				//											Sata_Write_Q.pop();
				//											//Master_Data=0xFFFFFFFF;
				//											AHBv2_Dram_M_mpms->setWData( Master_Data, 0 );
				//
				//											message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		Sata_Write_Q [0X%x]\n",Master_Data);
				//											message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "WRITE\n");
				//											message( eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "WRITE data (0x%08x)", Master_Data);
				//											outFile_WriteRQ<<"LBA"<<Master_Addr<<"	"<<Master_Data<<endl;
				//
				//
				uint32_t tmp = Sata_Write_Q.front();

				AHBv2_Dram_M_mpms->setWData(tmp, 0);
				//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//						"		Sata_Write_Q [0X%x]\n", tmp);
				//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "WRITE\n");
				//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//						"Address : %0x	WRITE data (0x%08x)",
				//						dma_addr + dma_CurIdx, tmp);
				//				outFile_WriteRQ << "LBA" << dma_addr + dma_CurIdx << "	" << tmp						<< endl;

				//Slave is Ready
				if (HReady) {
					//						uint32_t tmp=Sata_Write_Q.front();
					//											Sata_Write_Q.pop();
					//											AHBv2_Dram_M_mpms->setWData(tmp, 0);
					//											message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		Sata_Write_Q [0X%x]\n",tmp);
					//											message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "WRITE\n");
					//											message( eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Address : %0x	WRITE data (0x%08x)", dma_addr+dma_CurIdx,tmp);
					//											outFile_WriteRQ<<"LBA"<<dma_addr+dma_CurIdx<<"	"<<tmp<<endl;
					Sata_Write_Q.pop();
					//					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//							"dma_CurIdx	Rising \n");
					dma_CurIdx += 4;
				}
				//Slave is Busy
				else {
					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//			"NOT HREADY\n");
					; //Doesn't increase index because to drive same signals with current cycle.
				}
			}
			//////////////////////Read//////////////////////
			else {
				//////////////////////Wait 1cycle//////////////////////
				if (HReady) {	//Slave is Ready
					if (dma_wait_data_phase) {
						uint32_t r_data = AHBv2_Dram_M_mpms->getRData(0);
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] [DMA] read data: 0x%X, index: %d", bank, r_data, curIdx[bank]);

						//*((uint32_t*)&buffers[bank][curIdx[bank]]) = r_data;

						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, ", buffer[index]: 0x%X%X%X%X\n", buffers[bank][curIdx[bank]], buffers[bank][curIdx[bank]+1], buffers[bank][curIdx[bank]+2], buffers[bank][curIdx[bank]+3]);

						//Master_Data = AHBv2_Dram_M_mpms->getRData(0);

						//						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//								"Read\n");
						//						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//								"Read Address : %x	read data(0x%08x)",
						//								dma_addr + dma_CurIdx, r_data);
						// ADD your Code //
						// Get Read Data For you //
						//PUSH
						//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,				"Read !!! IN HOST FILE\n");

						//=================================================================INSERT SATA Read Q
						Sata_Read_Q.push(r_data);
						//		outFile << "LBA" << dma_addr + dma_CurIdx - 4 << "	"					<< r_data << endl;

						dma_CurIdx += 4;

					} else {
						dma_wait_data_phase = true;
						dma_CurIdx += 4;
					}
				} else {	//Slave is Busy
					; //Do nothing because current data is invalid since the slave is not ready.
				}
			}
		} else {
			;
		}

		//finish
		if (bWrite) {
			if (dma_CurIdx >= dma_cnt * 4) {
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//		"[WRITE#] [End DMA] addr: 0x%X, cnt: %d, write: %d\n",
				//		dma_addr, dma_cnt, dma_write);
				dma_running_bank=0;
				AHBv2_Dram_M_mpms->setSig(HBUSREQ, false);

				return true;
			}
		} else {
			if (dma_CurIdx > dma_cnt * 4) {
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//		"[READ#] [End DMA] addr: 0x%X, cnt: %d, write: %d\n",
				//		dma_addr, dma_cnt, dma_write);
				dma_running_bank=0;
				AHBv2_Dram_M_mpms->setSig(HBUSREQ, false);

				return true;
			}
		}

		//////////////////////Address phase//////////////////////
		if (dma_CurIdx == 0) {
			AHBv2_Dram_M_mpms->setAddr(dma_addr + dma_CurIdx, AHB2_TRANS_NONSEQ,
					dma_write, AHB2_SIZE_DATA32, AHB2_BURST_INCR, 0, false);
			dma_active_data_phase = true;
		} else {
			AHBv2_Dram_M_mpms->setAddr(dma_addr + dma_CurIdx, AHB2_TRANS_SEQ,
					dma_write, AHB2_SIZE_DATA32, AHB2_BURST_INCR, 0, false);
		}
	}

	return false;

}

BDDI* SATADevice::GetBDDI()
{
	return bddi;
}

char* SATADevice::GetModuleName()
{
	return (char*)"SATADevice";
}

void SATADevice::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHBv2_Dram_M_mpms = new BD_AHBPort_MM((char*)"MM_M0");
	AHBv2_Process_S_spss = new BD_AHBPort_SS((char*)"SS_S0");

	// for BDDI
	bddi = new SATADevice_BDDI(this);

	int i;
	char *ptr;
	flag = 1;
	Equal_flag = 0;
	unsigned int S_PhyLTemp = 0;
	unsigned int S_LinkLTemp = 0;
	unsigned int S_TransLTemp = 0;
	//	SYNC_PRIM[0]=0x7C;
	//	SYNC_PRIM[1]=0x95;
	//	SYNC_PRIM[2]=0xB5;
	//	SYNC_PRIM[3]=0xB5;
	SYNC_PRIM[0] = 0xB5B5957C;
	//inFile.open("/media/1TB_HDD/Financial1.trace");
	//outFile.open("/media/1TB_HDD/Host_Outfile.txt");
	//outFile_WriteRQ.open("/media/1TB_HDD/Host_outFile_WriteRQ.txt");
	//int i1,i2,i3,i4,i5;
	Sata_RFile.open("/media/1TB_HDD/JY/Project_All/Sata_R_Output.txt",ios::trunc);
	Sata_WFile.open("/media/1TB_HDD/JY/Project_All/Sata_W_Output.txt",ios::trunc);
	//============================================SENDING SYNC
	//for (i = 0; i < 4; i++) {
	S_TransLTemp = Send_TransportLayer(SYNC_PRIM[0]);
	S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
	S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
	//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "SYNC : %x\n",
	//		phy_S_Elasticity.front());

	_TraceWait = 0;
	r_SATA_CTRL_1 = 0;
	r_SATA_INT_ENABLE = 0;
	r_SATA_INT_STAT = 0;
	r_SATA_CTRL_2 = 0;
	r_SATA_FIS_D2H_0 = 0;
	r_SATA_FIS_D2H_1 = 0;
	r_SATA_FIS_D2H_2 = 0;
	r_SATA_FIS_D2H_3 = 0;
	r_SATA_FIS_D2H_4 = 0;
	r_SATA_FIS_D2H_5 = 0;
	r_SATA_FIS_D2H_6 = 0;
	r_SATA_FIS_D2H_7 = 0;
	r_SATA_FIS_D2H_LEN = 0;
	r_SATA_FIS_H2D_0 = 0;
	r_SATA_FIS_H2D_1 = 0;
	r_SATA_FIS_H2D_2 = 0;
	r_SATA_FIS_H2D_3 = 0;
	r_SATA_FIS_H2D_4 = 0;
	r_SATA_FIS_H2D_5 = 0;
	r_SATA_FIS_H2D_6 = 0;
	r_SATA_FIS_H2D_7 = 0;
	r_SATA_XFER_BYTES = 0;
	r_SATA_XFER_BYTES_REMAIN = 0;
	r_SATA_XFER_SECTORS_REMAIN = 0;
	r_SATA_SACTIVE = 0;
	r_SATA_NCQ_BMP_1 = 0;
	r_SATA_NCQ_BMP_2 = 0;
	r_SATA_STATUS = 0;
	r_SATA_SECT_OFFSET = 0;
	r_SATA_BUF_PAGE_SIZE = 0;
	r_SATA_RESET_FIFO_1 = 0;
	r_SATA_MANUAL_MODE_ADDR = 0;
	r_SATA_CTRL_3 = 0;
	r_SATA_FIFO_1_STATUS = 0;
	r_SATA_FIFO_2_STATUS = 0;
	r_SATA_FIFO_S_STATUS = 0;
	r_SATA_PHY_STATUS = 0;
	r_SATA_ERROR = 0;
	r_SATA_PHY_CTRL = 0;
	r_SATA_CFG_1 = 0;
	r_SATA_CFG_2 = 0;
	r_SATA_CFG_3 = 0;
	r_SATA_CFG_4 = 0;
	r_SATA_CFG_5 = 0;
	r_SATA_CFG_6 = 0;
	r_SATA_CFG_7 = 0;
	r_SATA_WBUF_BASE = 0;
	r_SATA_RBUF_BASE = 0;
	r_SATA_WBUF_SIZE = 0;
	r_SATA_RBUF_SIZE = 0;
	r_SATA_WBUF_MARGIN = 0;
	r_SATA_RESET_WBUF_PTR = 0;
	r_SATA_RESET_RBUF_PTR = 0;
	r_SATA_NCQ_BASE = 0;
	r_SATA_WBUF_PTR = 0;
	r_SATA_RBUF_PTR = 0;
	r_SATA_WBUF_FREE = 0;
	r_SATA_RBUF_PENDING = 0;
	r_SATA_CFG_8 = 0;
	r_SATA_MAX_LBA = 0;
	r_SATA_CFG_9 = 0;
	r_SATA_INSERT_EQ_W = 0;
	r_SATA_LBA = 0;
	r_SATA_SECT_CNT = 0;
	r_SATA_INSERT_EQ_R = 0;
	r_SATA_NCQ_ORDER = 0;
	r_SATA_NCQ_CTRL = 0;
	r_SATA_CFG_10 = 0;
	r_SATA_EQ_CFG_1 = 0;
	r_SATA_EQ_CTRL = 0;
	r_SATA_EQ_PTR = 0;
	r_SATA_EQ_STATUS = 0;
	r_SATA_EQ_DATA_0 = 0;
	r_SATA_EQ_DATA_1 = 0;
	r_SATA_EQ_DATA_2 = 0;
	r_SATA_EQ_CFG_2 = 0;
	r_SATA_TempReg0 = 0;
	r_SATA_TempReg1 = 0;

	//Previous_Address=0;

	r_SATA_CTRL_1_tmp = 0;
	r_SATA_INT_ENABLE_tmp = 0;
	r_SATA_INT_STAT_tmp = 0;
	r_SATA_CTRL_2_tmp = 0;
	r_SATA_FIS_D2H_0_tmp = 0;
	r_SATA_FIS_D2H_1_tmp = 0;
	r_SATA_FIS_D2H_2_tmp = 0;
	r_SATA_FIS_D2H_3_tmp = 0;
	r_SATA_FIS_D2H_4_tmp = 0;
	r_SATA_FIS_D2H_5_tmp = 0;
	r_SATA_FIS_D2H_6_tmp = 0;
	r_SATA_FIS_D2H_7_tmp = 0;
	r_SATA_FIS_D2H_LEN_tmp = 0;
	r_SATA_FIS_H2D_0_tmp = 0;
	r_SATA_FIS_H2D_1_tmp = 0;
	r_SATA_FIS_H2D_2_tmp = 0;
	r_SATA_FIS_H2D_3_tmp = 0;
	r_SATA_FIS_H2D_4_tmp = 0;
	r_SATA_FIS_H2D_5_tmp = 0;
	r_SATA_FIS_H2D_6_tmp = 0;
	r_SATA_FIS_H2D_7_tmp = 0;
	r_SATA_XFER_BYTES_tmp = 0;
	r_SATA_XFER_BYTES_REMAIN_tmp = 0;
	r_SATA_XFER_SECTORS_REMAIN_tmp = 0;
	r_SATA_SACTIVE_tmp = 0;
	r_SATA_NCQ_BMP_1_tmp = 0;
	r_SATA_NCQ_BMP_2_tmp = 0;
	r_SATA_STATUS_tmp = 0;
	r_SATA_SECT_OFFSET_tmp = 0;
	r_SATA_BUF_PAGE_SIZE_tmp = 0;
	r_SATA_RESET_FIFO_1_tmp = 0;
	r_SATA_MANUAL_MODE_ADDR_tmp = 0;
	r_SATA_CTRL_3_tmp = 0;
	r_SATA_FIFO_1_STATUS_tmp = 0;
	r_SATA_FIFO_2_STATUS_tmp = 0;
	r_SATA_FIFO_S_STATUS_tmp = 0;
	r_SATA_PHY_STATUS_tmp = 0;
	r_SATA_ERROR_tmp = 0;
	r_SATA_PHY_CTRL_tmp = 0;
	r_SATA_CFG_1_tmp = 0;
	r_SATA_CFG_2_tmp = 0;
	r_SATA_CFG_3_tmp = 0;
	r_SATA_CFG_4_tmp = 0;
	r_SATA_CFG_5_tmp = 0;
	r_SATA_CFG_6_tmp = 0;
	r_SATA_CFG_7_tmp = 0;
	r_SATA_WBUF_BASE_tmp = 0;
	r_SATA_RBUF_BASE_tmp = 0;
	r_SATA_WBUF_SIZE_tmp = 0;
	r_SATA_RBUF_SIZE_tmp = 0;
	r_SATA_WBUF_MARGIN_tmp = 0;
	r_SATA_RESET_WBUF_PTR_tmp = 0;
	r_SATA_RESET_RBUF_PTR_tmp = 0;
	r_SATA_NCQ_BASE_tmp = 0;
	r_SATA_WBUF_PTR_tmp = 0;
	r_SATA_RBUF_PTR_tmp = 0;
	r_SATA_WBUF_FREE_tmp = 0;
	r_SATA_RBUF_PENDING_tmp = 0;
	r_SATA_CFG_8_tmp = 0;
	r_SATA_MAX_LBA_tmp = 0;
	r_SATA_CFG_9_tmp = 0;
	r_SATA_INSERT_EQ_W_tmp = 0;
	r_SATA_LBA_tmp = 0;
	r_SATA_SECT_CNT_tmp = 0;
	r_SATA_INSERT_EQ_R_tmp = 0;
	r_SATA_NCQ_ORDER_tmp = 0;
	r_SATA_NCQ_CTRL_tmp = 0;
	r_SATA_CFG_10_tmp = 0;
	r_SATA_EQ_CFG_1_tmp = 0;
	r_SATA_EQ_CTRL_tmp = 0;
	r_SATA_EQ_PTR_tmp = 0;
	r_SATA_EQ_STATUS_tmp = 0;
	r_SATA_EQ_DATA_0_tmp = 0;
	r_SATA_EQ_DATA_1_tmp = 0;
	r_SATA_EQ_DATA_2_tmp = 0;
	r_SATA_EQ_CFG_2_tmp = 0;
	r_SATA_TempReg0_tmp = 0;
	r_SATA_TempReg1_tmp = 0;

	DATATransferCheck = 0;
	_addr = 0;
	_isWrite = false;
	_isDataCycleActive = false;
	_waitCycles = 0;
	_currentWait = _waitCycles;
	intPulse = 0;
	//sata_read_ptr=0;
	//sata_write_ptr=0;
	BM_R_temp = 0;
	BM_W_temp = 0;
	BM_R_limit = 0;
	BM_W_limit = 0;

	Master_isTxActive = false;
	Master_busReqMade = false;
	Master_isAddressPhase = true;

	Master_Addr = 0;
	Master_Data = 0;

	DMA_STATUS = STATUS_DMA_IDLE;

	m_flag = false;
	Size_tmp = 0;
	Data_tmp_W = 0;
	Data_tmp_R = 0;
	DMA_TEST_flag = 0;
	DST_Addr = 0;
	S_DMA_DONE_CHECK = 0;

	//===============================NEW DMA
	dma_running_bank = 0;
	dma_addr = 0;
	dma_cnt = 0;
	dma_write = 0;
	dma_active_data_phase = 0;
	dma_wait_data_phase = 0;
	dma_bus_granted = 0;
	dma_CurIdx = 0;

	S_BUFFER_PTR = true;
	//================================================================SATA &HOST Separted
	Sata_Startbit = 0;
	ReceiceData = 0;
	//===========================Physical Layer Part====================
	phy_40bitCount = 0;
	//phy_Temp = 0;
	phy_Startbit = 0;
	phy_ReceTemp = 0;
	//===========================
	for (int i = 0; i < 5; i++)
		FISTemp[i] = 0;
	HOST_LinkSignal = 0;
	//=====================================================SATA HOST PART

	phy_SendDone = 0;
	phy_SendTemp = 0;
	phy_SendCount = 0;
	CHECK_START = 0;
	ReceviceLoopCnt = 0;

	//========================================================SATAHOST & DEVICE ADDITION
	Write_FIS_RECEIVE = 0;
	Read_RIS_RECEIVE = 0;

	D2H_Write_COMMAND_DONE = 0;
	D2H_Read_COMMAND_DONE = 0;

	PageDMACount = 0;
	RESETCHCOUNT = 140000;
	DMAREADlba = 0;
	DMAREADsector_count = 0;
	DMAREADcmd_type = 0;
	DMAREAD_DONE = 0;
	PageDMASectCount = 0;
	POPEQDMAWRITE = 0;
	Sata_R_out=0;
	Sata_W_out=0;

	PageDMACount_W=0;
	PageDMASectCount_W=0;
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new SATADevice(ModuleInstanceName);
}
