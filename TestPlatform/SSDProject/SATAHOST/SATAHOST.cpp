#include "SATAHOST.h"
#include <stdio.h>

#define timeunit 10;
uint32_t Temp[2][5];
char inputString[100];
//ifstream inFile;
bool flag;
bool Equal_flag;
uint32_t intPulse;
ifstream inFile;
ofstream outFile;
ofstream outFile_WriteRQ;
bool Last_flag;

unsigned int SATAHOST::Rece_PhyLayer() {
	//Pop phy_Elasticity Data to transport LinkLayer
	//return type : unsigned int
	unsigned int RECETEMP = 0;
	if (phy_R_Elasticity.size() != 0) {
		RECETEMP = phy_R_Elasticity.front();
		phy_R_Elasticity.pop_front();
//		phy_R_Elasticity.pop();	
//CHECKLATER
	}
//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//			"============================		This is Rece_PhyLayer : RECETEMP Data 0x%x \n",
//			RECETEMP);

	return RECETEMP;
}

unsigned int SATAHOST::Rece_LinkLayer(unsigned int input) {

	if (input == SYNC_PRIMITIVE) {
		HOST_LinkSignal = 0;
	} else if (input == R_OK_PRIMITIVE) {
		HOST_LinkSignal = 2;
	} else
		HOST_LinkSignal = 1;

	return input;
}
unsigned int SATAHOST::Rece_TransportLayer(unsigned int input) {
	return input;
}
unsigned int SATAHOST::Send_PhyLayer(unsigned int input) {
	//int Sendbit=0;

	//if (input != 0)							//Push to S_Elastivity Buffer
	//		{
	phy_S_Elasticity.push_back(input);
//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//			"This is Send_PhyLater input:   0x%x \n", input);
	//}
	return input;
}
unsigned int SATAHOST::Send_LinkLayer(unsigned int input) {
	return input;
}
unsigned int SATAHOST::Send_TransportLayer(unsigned int input) {
	return input;
}

int32_t SATAHOST::ReadTrace() {
	//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "This ReadTrace function\n");

	char *ptr;
	int i = 0;
	//int j=0;
	int RT_wait = 0;

	  //fgets( inputString, sizeof(inputString),  input_file);

//if(!inFile.eof())
//{
	if(inFile.getline(inputString, 100)){				//is changed by TB
	ptr = strtok(inputString, " ");					//is changed by TB
	Temp[flag][0] = atoi(ptr);						//is changed by TB

	for (i = 1; i < 5; i++)								//is changed by TB
			//for(i=0;i<5;i++)
			{
		ptr = strtok(NULL, " ");						//is changed by TB
		Temp[flag][i] = atoi(ptr);					//is changed by TB
		//inFile >> Temp[flag][i];
	}

	//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "%d %d %d %d %d\n",
			//Temp[flag][0], Temp[flag][1], Temp[flag][2], Temp[flag][3],
			//Temp[flag][4]);		//TB

	if (Temp[1][0] == Temp[0][0])
		Equal_flag = 1;
	if (flag == 1) {
		//RT_wait = (Temp[1][0] - Temp[0][0]) * 200000;	//TEST2
		RT_wait = (Temp[1][0] - Temp[0][0]) * 500;	//TEST2
		//RT_wait = (Temp[1][0] - Temp[0][0]) * 1;	//TEST2

		flag = 0;
	} else {
		//RT_wait = (Temp[0][0] - Temp[1][0]) * 200000;	//TEST2
		RT_wait = (Temp[0][0] - Temp[1][0]) * 500;	//TEST2
		//RT_wait = (Temp[1][0] - Temp[0][0]) * 1;	//TEST2

		flag = 1;
	}
	/*
	 if(RT_wait==0)
	 return 0;
	 //while(RT_wait--!=0);
	 */
	return RT_wait;
}
else{
	if (flag == 1) {
		//RT_wait = (Temp[1][0] - Temp[0][0]) * 200000;	//TEST2
		RT_wait = (Temp[1][0] - Temp[0][0]) * 500;	//TEST2
		//RT_wait = (Temp[1][0] - Temp[0][0]) * 1;	//TEST2

		flag = 0;
	} else {
		//RT_wait = (Temp[0][0] - Temp[1][0]) * 200000;	//TEST2
		RT_wait = (Temp[0][0] - Temp[1][0]) * 500;	//TEST2
		//RT_wait = (Temp[1][0] - Temp[0][0]) * 1;	//TEST2

		flag = 1;
	}
	Last_flag=1;
	return -1;
}
}
void SATAHOST::communicate() {
	//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[communicate function] \n");
	unsigned int ReceData = 0;
	unsigned int SendData = 0;

	unsigned int S_PhyLTemp = 0;
	unsigned int S_LinkLTemp = 0;
	unsigned int S_TransLTemp = 0;

	unsigned int R_PhyLTemp = 0;
	unsigned int R_LinkLTemp = 0;
	unsigned int R_TransLTemp = 0;

	uint32_t StoreTemp = 0;
	uint32_t FIS_H2D_0[5];
//	uint32_t	FIS_TEMP=0;
	int sendbit = 0;

	 

//	uint32_t	FIS_H2D_1=0;
//	uint32_t	FIS_H2D_2=0;
//	uint32_t	FIS_H2D_3=0;
//	uint32_t	FIS_H2D_4=0;
//	uint32_t	FIS_H2D_5=0;
//
	int i = 0;

	// the following message will be printed only in the debug version of MxExplorer
	//if (p_enableDbgMsg == true) {
		//message(eslapi::CASI_MSG_INFO, "Executing communicate function");
	//}

	if (RESETCHCOUNT == 0) {

////	if(CHECK_START==0){
//		Tx_SMaster->driveSignal(1, &p_Tx_ID);
//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "---------------------This CHECK START\n");
//
//	//		CHECK_START=1;
//	//	}
		//==========================================Physical Layer===========================
		// This is Receive Physical Layer Part
		//-----------------------------------------------------------------------------------
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Before Receive Data %d \n", ReceData);
		ReceData = Rx_SSlave;
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "		After Receive Data %d \n", ReceData);
		//========================-----------------------
		//Tx_SMaster->driveSignal(1, &p_Tx_ID);

		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "phy_40bitCount %d \n", phy_40bitCount);
		//if(phy_40bitCount!=40)
		//{

		//=========================================Physical Layer -----------Receive Part=======

		if (phy_Startbit == 1) {
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "phy_Startbit : %d	phy_40bitCount : %d	ReceiveData : %d \n",phy_Startbit,phy_40bitCount,ReceData);
			for (int i = 0; i < phy_40bitCount; i++)
				ReceData = ReceData << 1;
			phy_ReceTemp = phy_ReceTemp + ReceData;
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, 		"phy_Temp Data 0x%x  \n", phy_ReceTemp);
			if (phy_40bitCount == 31) {
				//push phy_Temp value to list Buffer

				phy_R_Elasticity.push_back(phy_ReceTemp);
//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//					"Make Temp Data DONE : 0x%x \n", phy_ReceTemp);
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

		//if(phy_SendDone==0)
		//{
		if (CHECK_START == 0) {
			Tx_SMaster = 1;
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//"---------------------This CHECK START\n");

			CHECK_START = 1;
		} else if ((phy_SendCount == 0) || (phy_SendCount == 32)) {
			if (phy_S_Elasticity.size() != 0) {
				if (phy_SendCount == 32)
					phy_SendCount = 0;
				phy_SendTemp = phy_S_Elasticity.front();
				phy_S_Elasticity.pop_front();
//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//					"POP DATA : phy_SendTemp 0x%x \n", phy_SendTemp);
				sendbit = phy_SendTemp & 0x1;
				phy_SendTemp = phy_SendTemp >> 1;
				//		  intPulse=0;
				//		  			FIQ_int_SMaster->driveSignal(intPulse,&p_Interrupt_ID);
				//Tx_SMaster->driveSignal(1, &p_Tx_ID);					//This is Start bit
				Tx_SMaster = sendbit; //Sending Bits
				//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "	Send bit : sendbit %d \n", 	sendbit);
				phy_SendCount++;

			}
//	} else if (phy_SendCount == 8)					//sending 8bit
//			{
//		if (phy_R_Elasticity.size() != 0) {
//			phy_SendTemp = phy_R_Elasticity.front();
//			phy_R_Elasticity.pop_front();
//
//			phy_SendCount = 0;
//		}
// phy_SendDone=0;
		} else {
			sendbit = phy_SendTemp & 0x1;
			phy_SendTemp = phy_SendTemp >> 1;
//		  intPulse=0;
//		  			FIQ_int_SMaster->driveSignal(intPulse,&p_Interrupt_ID);
			Tx_SMaster = sendbit;			//Sending Bits
			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "	Send bit : sendbit %d \n", 	sendbit);
			phy_SendCount++;
		}
		//}

		//==========================================================================Physical Layer

		//==========================================================================Link Layer
		if (phy_S_Elasticity.size() == 0)
			phy_S_Elasticity.push_back(SYNC_PRIMITIVE);

		//==========================================================================Link Layer

		//=============================Command Layer FSM==========================================
		//Register : r_TempReg0 is internal register of Command Layer FSM
		switch (r_HOST_Reg8) {

		case STATUS_HOST_IDLE:
			if(Last_flag==1)
			{
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
								//"\n\n\n\n\n\n\n\n END of Trace File\n\n\n\n\n\n\n\n");
				Last_flag=0;
			}
//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//				"This STATUS_HOST_IDLE function\n");
			if (_TraceWait == 0) {

				r_HOST_Reg8_tmp = STATUS_HOST_CommandCheck;
				_TraceWait = ReadTrace();

				//if(_TraceWait==-1)
				//	r_HOST_Reg8_tmp = STATUS_HOST_IDLE;
			}
			else if(_TraceWait==-1)
			{
				r_HOST_Reg8_tmp = STATUS_HOST_IDLE;
			}
			else {

				r_HOST_Reg8_tmp = STATUS_HOST_IDLE;
				_TraceWait--;
			}
			break;

		case STATUS_HOST_CommandCheck:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//"This STATUS_HOST_CommandCheck function\n");
			if (Temp[flag][4] == 0)	//Read
					{
				r_HOST_Reg0_tmp = 0x00250000;
				RW_CommandFlag = 0;

			} else					//Write
			{
				r_HOST_Reg0_tmp = 0x00350000;
				RW_CommandFlag = 1;
			}
			r_HOST_Reg1_tmp = Temp[flag][2] & 0x00FFFFFF;//----------SeperatedSection 3:
			r_HOST_Reg2_tmp = Temp[flag][2] >> 24;
			r_HOST_Reg3_tmp = Temp[flag][3];
			r_HOST_Reg4_tmp = Temp[flag][4];

			r_HOST_Reg8_tmp = STATUS_HOST_TransIDLE;

//		FIS_H2D_0[0] = r_HOST_Reg0;
//		FIS_H2D_0[1] = r_HOST_Reg1;
//		FIS_H2D_0[2] = r_HOST_Reg2;
//		FIS_H2D_0[3] = r_HOST_Reg3;
//		FIS_H2D_0[4] = r_HOST_Reg4;

			FIS_H2D_0[0] = r_HOST_Reg0_tmp;
			FIS_H2D_0[1] = r_HOST_Reg1_tmp;
			FIS_H2D_0[2] = r_HOST_Reg2_tmp;
			FIS_H2D_0[3] = r_HOST_Reg3_tmp;
			FIS_H2D_0[4] = r_HOST_Reg4_tmp;

			DATATransferCheck=r_HOST_Reg3_tmp;

			for (i = 0; i < 5; i++) {
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//"This FIS_H2D_0[%d] :  %x\n", i, FIS_H2D_0[i]);
//			for(int j=0;j<4;j++)
//			{
//				if(j==0)
//				{
//					StoreTemp=FIS_H2D_0[i]&0xFF000000;
//					StoreTemp=StoreTemp>>24;
//				}
//				else if(j==1)
//				{
//					StoreTemp=FIS_H2D_0[i]&0x00FF0000;
//					StoreTemp=StoreTemp>>16;
//				}
//				else if(j==2)
//				{
//					StoreTemp=FIS_H2D_0[i]&0x0000FF00;
//					StoreTemp=StoreTemp>>8;
//				}
//				else
//				{
//					StoreTemp=FIS_H2D_0[i]&0x000000FF;
//					//StoreTemp=StoreTemp;
//				}
//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//									"		Sending DATA 32bit (FIS : 0x%x) :  %x\n",FIS_H2D_0[i],StoreTemp);
				S_TransLTemp = Send_TransportLayer(FIS_H2D_0[i]);
				S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
				S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);

				//	}
//			S_TransLTemp = Send_TransportLayer(StoreTemp);
//			S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
//			S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
			}

			//if(RW_CommandFlag==0)					//READ Write Send to Drive Register FIS (contained Commmand)
			//{

			//}

			break;

		case STATUS_HOST_TransIDLE:			//0
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, 	"This STATUS_HOST_TransIDLE function\n");

			//In this, Physical Layer Data -> Link Layer (by calling Link Layer func)
			//Link Layer FIS -> Transport Layer 			(by calling Transport Layer func)

//  		  PhyLTemp=Rece_PhyLayer();
//  		  LinkLTemp=Rece_LinkLayer(PhyLTemp);
//  		  TransLTemp=Rece_TransportLayer(LinkLTemp);

// Read Command Sending Part
			if (RW_CommandFlag == 0) {
//			if (HOST_LinkSignal == 1)	//SIGNAL From Link Layer
//				r_HOST_Reg8_tmp = STATUS_HOST_FISCHECK;
//			else
//				r_HOST_Reg8_tmp = STATUS_HOST_TransIDLE;
				r_HOST_Reg8_tmp = STATUS_HOST_DMAIN;

			} else				//Write Command
			{
//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//					"This STATUS_HOST_TransIDLE // Write Command Data function\n");
//			for (i = 0; i < 5; i++) {
//						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//								"This FIS_H2D_0[%d] :  %x\n", i, FIS_H2D_0[i]);
//			}
				int sectorcount = r_HOST_Reg3;
				//Sending Data
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//"This sectorcount %d\n", sectorcount);
				for (int i = 0; i < sectorcount; i++) {
					S_TransLTemp = Send_TransportLayer(r_HOST_Reg1);
					S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
					S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//"This STATUS_HOST_TransIDLE :S_PhyLTemp :0x%x\n",
							//_PhyLTemp);
				}
				r_HOST_Reg8_tmp = STATUS_HOST_DMAOUT;

			}

//
//  		  for(int i=0;i<5;i++)
//  		  {
//  			  FIS_TEMP=FIS_H2D_0[i];
//  			  for(int j=0;j<8;j++)
//  			  {
//  				  	sendbit=FIS_TEMP&0x1;
//  				  	FIS_TEMP=FIS_TEMP>>1;
//					PhyLTemp=Send_PhyLayer();
//					LinkLTemp=Send_LinkLayer(PhyLTemp);
//					TransLTemp=Send_TransportLayer(LinkLTemp);
//			  }
//  		  }

// Write Command Sending Part

			break;
		case STATUS_HOST_FISCHECK:		//1
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
					//"This STATUS_HOST_FISCHECK function\n");
			//FIS Type Checked State

			//if DATA (IN READ Command)					//Read Command first
			r_HOST_Reg8_tmp = STATUS_HOST_DMAIN;

			//if FIS Register == READ Command				//Read Command Second=========================LATER
			r_HOST_Reg8_tmp = STATUS_HOST_RegFIS;

			//if FIS Register == WRITE Command
			//<if FIS Register is DMA Activate FIS>
			r_HOST_Reg8_tmp = STATUS_HOST_DMAOUT;

			break;
		case STATUS_HOST_SendStatus:	//2
			//Receive Register DW1-DW4 -> 4 times
//		for (i = 0; i < 5; i++) {
//			FISTemp[i] = Rece_PhyLayer();
//		}
//
//		//if Command is Read(DMA IN)
//		if ((FISTemp[0] && 0x00FF0000) == 0x00250000) {
//			//	r_HOST_Reg0_tmp=STATUS_CM_DMAIN;					//READ					CHECK
//		}
//
//		//if Command is Write(DMA OUT)
//		else if ((FISTemp[0] && 0x00FF0000) == 0x00350000) {
//			//	r_HOST_Reg0_tmp=STATUS_CM_DMAOUT;				//WRITE						CHECK
//		}
			if (phy_R_Elasticity.size() != 0) {
				//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
				//			"This STATUS_HOST_SendStatus function %d\n",
				//			phy_R_Elasticity.size());
				R_PhyLTemp = Rece_PhyLayer();
				R_LinkLTemp = Rece_LinkLayer(R_PhyLTemp);
				if (HOST_LinkSignal == 2) {
					R_TransLTemp = Rece_TransportLayer(R_LinkLTemp);
					r_HOST_Reg8_tmp = STATUS_HOST_IDLE;			//Get a Command
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//"				== STATUS_HOST_SendStatus function 0x%x\n",
							//R_TransLTemp);
				} else
					r_HOST_Reg8_tmp = STATUS_HOST_SendStatus;

			}

			break;

		case STATUS_HOST_DMAEND:

			r_HOST_Reg8_tmp = STATUS_HOST_TransIDLE;

			break;
		case STATUS_HOST_DMAIN:							//Read Command State
			//5						//-------------------------WRTIE STATUS
			//Write Command
			//Receive count of Write DATA Sector
//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//				"STATUS_HOST_DMAIN FISTemp[3]: 0x%x\n", r_HOST_Reg3);
//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//				"STATUS_HOST_DMAIN phy_R_Elasticity: %d\n",
//				phy_R_Elasticity.size());

			if (phy_R_Elasticity.size() != 0) {
				R_PhyLTemp = Rece_PhyLayer();
				R_LinkLTemp = Rece_LinkLayer(R_PhyLTemp);
				if (HOST_LinkSignal == 1){

				R_TransLTemp = Rece_TransportLayer(R_LinkLTemp);
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//"STATUS_HOST_DMAIN R_TransLTemp : 0x%x\n",
						//R_TransLTemp);
				outFile << R_TransLTemp << endl;
				DATATransferCheck--;
				}

			}
			if(DATATransferCheck==0)
				r_HOST_Reg8_tmp = STATUS_HOST_SendStatus;
			else
				r_HOST_Reg8_tmp = STATUS_HOST_DMAIN;

			//==============================================LAST
//		if (phy_R_Elasticity.size() >= r_HOST_Reg3) {
//			for (int i = 0; i < r_HOST_Reg3; i++) {
//				R_PhyLTemp = Rece_PhyLayer();
//				R_LinkLTemp = Rece_LinkLayer(R_PhyLTemp);
//				R_TransLTemp = Rece_TransportLayer(R_LinkLTemp);
//				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//						"STATUS_HOST_DMAIN R_TransLTemp : 0x%x\n",
//						R_TransLTemp);
//				outFile<<R_TransLTemp<<endl;
//			}
//			r_HOST_Reg8_tmp = STATUS_HOST_SendStatus;
//			//		}
			//		else
			//		r_HOST_Reg8_tmp = STATUS_HOST_DMAIN;
			//=============================================================================LAST

			//Sata_Write_Q.push(R_TransLTemp);
//			S_TransLTemp = Send_TransportLayer(R_OK_PRIMITIVE);
//			S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
//			S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//					"This STATUS_HOST_DMAIN :S_PhyLTemp :0x%x\n",
//					S_PhyLTemp);
//

		//r_HOST_Reg8_tmp = STATUS_HOST_DMAEND;

		break;
		case STATUS_HOST_DMAOUT:
		//WRITE
		//=========================================Wait until  SATA Device DONE Signal
//===========================RIGHT HERE
//CHECK PRIMITIVE// Reiceve R_OK
		//R_OK_PRIMITIVE
		//if()
		//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
		//					"This STATUS_HOST_DMAOUT function %d\n",phy_R_Elasticity.size());
		if (phy_R_Elasticity.size() != 0) {
//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
//					"This STATUS_HOST_DMAOUT function %d\n",
//					phy_R_Elasticity.size());
			R_PhyLTemp = Rece_PhyLayer();
			R_LinkLTemp = Rece_LinkLayer(R_PhyLTemp);
			if (HOST_LinkSignal == 2) {
				R_TransLTemp = Rece_TransportLayer(R_LinkLTemp);
				r_HOST_Reg8_tmp = STATUS_HOST_IDLE;				//Get a Command
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
						//"				==ARIVEThis STATUS_HOST_DMAOUT function 0x%x\n",
						//R_TransLTemp);
			} else
				r_HOST_Reg8_tmp = STATUS_HOST_DMAOUT;

		}

		//r_HOST_Reg8_tmp=STATUS_HOST_DMAOUT;
		//Write Command
		break;
		case STATUS_RegisterFIS:

		break;
		case STATUS_HOST_RegFIS:

		break;
		//case STATUS_HOST_2:	//8
		//Temp FSM

		//=========================================================MUST ADD Code
		//
		//	r_HOST_Reg0_tmp=STATUS_CM_IDLE;

		break;

		default:
		break;
	}

}
else
RESETCHCOUNT--;

// TODO:  Add your communicate code here.
// ...
// Send(drive) all the signals set in previous update()
//AHBv2_Process_S_spss->sendDrive();
}

void SATAHOST::update() {

uint64_t offset = 0;
uint64_t w_data = 0;
// the following message will be printed only in the debug version of MxExplorer
//if (p_enableDbgMsg == true) {
	//message(eslapi::CASI_MSG_INFO, "Executing update function");
//}


if (_isDataCycleActive) {
	if (--_currentWait <= 0) {
		_currentWait = _waitCycles;
		_isDataCycleActive = false;

		offset = _addr - p_HOST_baseaddr;
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "addr %x\n", _addr);

		if (_isWrite) {

			w_data = AHBv2_Process_S_spss->getWData(0);

			switch (offset) {
			case HOST_Reg0:
				r_HOST_Reg0_tmp = w_data;
				break;
			case HOST_Reg1:
				r_HOST_Reg1_tmp = w_data;
				break;
			case HOST_Reg2:
				r_HOST_Reg2_tmp = w_data;
				break;

			case HOST_Reg3:
				r_HOST_Reg3_tmp = w_data;
				break;
			case HOST_Reg4:
				r_HOST_Reg4_tmp = w_data;
				break;

			case HOST_Reg5:
				r_HOST_Reg5_tmp = w_data;
				break;
			case HOST_Reg6:
				r_HOST_Reg6_tmp = w_data;
				break;

			case HOST_Reg7:
				r_HOST_Reg7_tmp = w_data;
				break;
			case HOST_Reg8:
				r_HOST_Reg8_tmp = w_data;
				break;

			case HOST_Reg9:
				r_HOST_Reg9_tmp = w_data;
				break;

			default:
				//if (p_enableDbgMsg) {
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//"(Error! Access to out of range!(offset : 0x%x))\n",
							//offset);
				//}
				break;
			}
		} else						//READ DATA
		{

			switch (offset) {
			case HOST_Reg0:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg0);
				break;

			case HOST_Reg1:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg1);
				break;
			case HOST_Reg2:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg2);
				break;

			case HOST_Reg3:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg3);
				break;
			case HOST_Reg4:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg4);
				break;

			case HOST_Reg5:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg5);
				break;
			case HOST_Reg6:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg6);
				break;

			case HOST_Reg7:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg7);
				break;
			case HOST_Reg8:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg8);
				break;

			case HOST_Reg9:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg9);
				break;

			default:
				//if (p_enableDbgMsg) {
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//"(Error! Access to out of range!(offset : 0x%x))\n",
							//offset);
				//}
				AHBv2_Process_S_spss->setRData(0);
				break;
			}
		}
		AHBv2_Process_S_spss->setSig(HREADYOUT, true);
	}
}				//-----------------------------------------------DATA phase

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

			offset = _addr - p_HOST_baseaddr;
			switch (offset) {
			case HOST_Reg0:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg7);
				break;

			case HOST_Reg1:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg1);
				break;
			case HOST_Reg2:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg2);
				break;
			case HOST_Reg3:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg3);
				break;
			case HOST_Reg4:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg4);
				break;
			case HOST_Reg5:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg5);
				break;
			case HOST_Reg6:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg6);
				break;
			case HOST_Reg7:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg7);
				break;
			case HOST_Reg8:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg8);
				break;
			case HOST_Reg9:
				AHBv2_Process_S_spss->setRData(r_HOST_Reg9);
				break;

			default:
				//if (p_enableDbgMsg) {
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,
							//"(Error! Access to out of range!(offset : 0x%x))\n",
							//offset);
				//}
				AHBv2_Process_S_spss->setRData(0);
				break;

			}						//Switch END
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
r_HOST_Reg0 = r_HOST_Reg0_tmp;
r_HOST_Reg1 = r_HOST_Reg1_tmp;
r_HOST_Reg2 = r_HOST_Reg2_tmp;
r_HOST_Reg3 = r_HOST_Reg3_tmp;
r_HOST_Reg4 = r_HOST_Reg4_tmp;
r_HOST_Reg5 = r_HOST_Reg5_tmp;
r_HOST_Reg6 = r_HOST_Reg6_tmp;
r_HOST_Reg7 = r_HOST_Reg7_tmp;
r_HOST_Reg8 = r_HOST_Reg8_tmp;
r_HOST_Reg9 = r_HOST_Reg9_tmp;
}


BDDI* SATAHOST::GetBDDI()
{
	return bddi;
}

char* SATAHOST::GetModuleName()
{
	return (char*)"SATAHOST";
}

void SATAHOST::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHBv2_Process_S_spss = new BD_AHBPort_SS((char*)"SS_S0");

	// for BDDI
	bddi = new SATAHOST_BDDI(this);


int i,j;

char temp;

char *ptr;
flag = 1;
Equal_flag = 0;
unsigned int S_PhyLTemp = 0;
unsigned int S_LinkLTemp = 0;
unsigned int S_TransLTemp = 0;
//
//	SYNC_PRIM[0] = 0x7C;
//	SYNC_PRIM[1] = 0x95;
//	SYNC_PRIM[2] = 0xB5;
//	SYNC_PRIM[3] = 0xB5;
SYNC_PRIM[0] = 0xB5B5957C;


//sinFile.open("D:\SSD\Financial1.trace");
	inFile.open("/media/1TB_HDD/All_SSD_Project/Trace/Financial.trace");

//outFile.open("D:\SSD\SATAHOST_Readfile.txt");
//outFile_WriteRQ.open("D:\SSD\SATAHOST_Writefile.txt");
//int i1,i2,i3,i4,i5;

//fgets( inputString, sizeof(inputString),  input_file); 
inFile.getline(inputString, 100);			//is changed by TB

ptr = strtok(inputString, " ");					//is changed by TB
Temp[0][0] = atoi(ptr);							//is changed by TB

for (i = 1; i < 5; i++)								//is changed by TB
		//for(i=0;i<5;i++)
		{
	ptr = strtok(NULL, " ");						//is changed by TB
	Temp[0][i] = atoi(ptr);						//is changed by TB
	//inFile >> Temp[0][i];
}


//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "READ %d %d %d %d %d\n",
		//Temp[0][0], Temp[0][1], Temp[0][2], Temp[0][3], Temp[0][4]);	//TB

//============================================SENDING SYNC
//	for (i = 0; i < 4; i++) {
//		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "SYNC[i] : %x\n",SYNC_PRIM[i]);
//		S_TransLTemp = Send_TransportLayer(SYNC_PRIM[i]);
//		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "S_TransLTemp[i] : %x\n",S_TransLTemp);
//		S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
//		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "S_LinkLTemp[i] : %x\n",S_LinkLTemp);
//		S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
//		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "S_PhyLTemp[i] : %x\n",S_PhyLTemp);
//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "SYNC : %x\n",phy_S_Elasticity.front());
//	}
S_TransLTemp = Send_TransportLayer(SYNC_PRIM[0]);
S_LinkLTemp = Send_LinkLayer(S_TransLTemp);
S_PhyLTemp = Send_PhyLayer(S_LinkLTemp);
//Tx_SMaster->driveSignal(1, &p_Tx_ID);
//=========================================================

//Read Trace file in Reset
/*
 if(INPUTFILE)
 {

 fscanf(INPUTFILE,"%d %d %d %d %d",&i1,&i2,&i3,&i4,&i5);
 message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "READ %d %d %d %d %d\n",i1,i2,i3,i4,i5 );		//TB

 //fscanf(INPUTFILE,"%d %d %d %d %d",&Temp[0][0],&Temp[0][1],&Temp[0][2],&Temp[0][3],&Temp[0][4]);
 //message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "READ %d %d %d %d %d\n", Temp[0][0], Temp[0][1], Temp[0][2], Temp[0][3], Temp[0][4]);		//TB
 }
 */
_TraceWait = 0;

r_HOST_Reg0 = 0;
r_HOST_Reg1 = 0;
r_HOST_Reg2 = 0;
r_HOST_Reg3 = 0;
r_HOST_Reg4 = 0;
r_HOST_Reg5 = 0;
r_HOST_Reg6 = 0;
r_HOST_Reg7 = 0;
r_HOST_Reg8 = 0;
r_HOST_Reg9 = 0;

r_HOST_Reg0_tmp = 0;
r_HOST_Reg1_tmp = 0;
r_HOST_Reg2_tmp = 0;
r_HOST_Reg3_tmp = 0;
r_HOST_Reg4_tmp = 0;
r_HOST_Reg5_tmp = 0;
r_HOST_Reg6_tmp = 0;
r_HOST_Reg7_tmp = 0;
r_HOST_Reg8_tmp = 0;
r_HOST_Reg9_tmp = 0;

_waitCycles = 0;
_currentWait = 0;
_addr = 0;
_isWrite = 0;
_isDataCycleActive = 0;

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

//=====================================================SATA HOST PART
HOST_LinkSignal = 0;
RW_CommandFlag = 0;
FIRSTTIME = 0;

phy_SendDone = 0;
phy_SendTemp = 0;
phy_SendCount = 0;
RESETCHCOUNT = 140000;
DATATransferCheck = 0;
CHECK_START = 0;
Last_flag=0;


}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new SATAHOST(ModuleInstanceName);
}
