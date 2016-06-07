#ifndef __SATAHOST_H__
#define __SATAHOST_H__

#include <iostream>
#include	<stdio.h>
#include <stdlib.h>
#include <list>
#include <queue>

#define BS_BASE 0x80000000
using namespace std;
//-------------------------------------------------ADD JH
#define HOST_Reg0					0x0000
#define HOST_Reg1					0x0004
#define HOST_Reg2					0x0008
#define HOST_Reg3					0x000C
#define HOST_Reg4					0x0010
#define HOST_Reg5					0x0014
#define HOST_Reg6					0x0018
#define HOST_Reg7					0x001C
#define HOST_Reg8					0x0020
#define HOST_Reg9					0x0024

// -------------------------------------------------DEFINE PRIMTIVE
#define SYNC_PRIMITIVE				0xB5B5957C
#define R_OK_PRIMITIVE				0x3535B57C
#define SOF_PRIMITIVE				0x3636757C
#define EOF_PRIMITIVE				0xD5D5B57C



// Place global class declarations here:
typedef enum {
	STATUS_HOST_IDLE = 0,
	STATUS_HOST_CommandCheck = 1,			//
	STATUS_HOST_TransIDLE = 2,		//Common
	STATUS_HOST_FISCHECK = 3,		//Common
	STATUS_HOST_SendStatus = 4,		//Common
	STATUS_HOST_DMAEND = 5,		//Common
	STATUS_HOST_DMAIN = 6,
	STATUS_HOST_DMAOUT = 7,
	STATUS_RegisterFIS = 8,
	STATUS_HOST_RegFIS = 9
} H_COMMAND_STATE;

#include "BlockDesigner.h"
#include <stdio.h>
#include <string.h>

// for BDDI
#include "SATAHOST_BDDI.h"

SC_MODULE(SATAHOST){

	/********** [port] **********/
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	BD_AHBPort_SS *AHBv2_Process_S_spss;

	BDDI*						bddi;

	sc_in<unsigned int> Rx_SSlave;
	sc_out<unsigned int> Tx_SMaster;

	// parameters
	bool p_enableDbgMsg;
	uint64_t p_HOST_baseaddr;
	uint64_t p_HOST_size;
	unsigned int p_Rx_ID;
	unsigned int p_Tx_ID;
	int p_Data_Bit_Width;

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

	uint32_t r_HOST_Reg0;
	uint32_t r_HOST_Reg1;
	uint32_t r_HOST_Reg2;
	uint32_t r_HOST_Reg3;
	uint32_t r_HOST_Reg4;
	uint32_t r_HOST_Reg5;
	uint32_t r_HOST_Reg6;
	uint32_t r_HOST_Reg7;
	uint32_t r_HOST_Reg8;			//FSM
	uint32_t r_HOST_Reg9;

	//=================================ADD
	uint32_t r_HOST_Reg0_tmp;
	uint32_t r_HOST_Reg1_tmp;
	uint32_t r_HOST_Reg2_tmp;
	uint32_t r_HOST_Reg3_tmp;
	uint32_t r_HOST_Reg4_tmp;
	uint32_t r_HOST_Reg5_tmp;
	uint32_t r_HOST_Reg6_tmp;
	uint32_t r_HOST_Reg7_tmp;			//
	uint32_t r_HOST_Reg8_tmp;		//FSM
	uint32_t r_HOST_Reg9_tmp;

	//Register IO
	int32_t _waitCycles;
	int32_t _currentWait;
	uint32_t _addr;
	bool _isWrite;
	bool _isDataCycleActive;

	int32_t _TraceWait;

	//================================SATA HOST Seperated
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

	//=====================================================SATA HOST PART
	//FSM HOST IDLE -> FIS Type CHECKED State (LINK Layer Report Frame Receipt)
	int HOST_LinkSignal;
	int RW_CommandFlag;	//Read=0, Write=1
	int FIRSTTIME;

	//
	int CHECK_START;

	//====================
	int RESETCHCOUNT;

	int DATATransferCheck;

	// place your private functions and data members here:
	// ...
	// This shows an example state variable for the save/restore mechanism.
	// int		exampleStateVariable;



	// overloaded methods for clocked components
	void communicate();
	void update();

	//===================================================================ADD
	int32_t ReadTrace();

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

	~SATAHOST();

	SC_CTOR(SATAHOST)	{
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
