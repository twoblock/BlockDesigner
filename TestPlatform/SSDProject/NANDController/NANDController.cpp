#include "NANDController.h"
#include <stdio.h>
#include <stdarg.h>

void NANDController::communicate()
{
	/**************************************************************************************
	 * Read Signals
	 **************************************************************************************/
	for(int i=0; i<NUM_BANKS; i++) {
		RBn[i] = flash_RBn_SSlave[i];
	}



	/* When all banks are idle, set MON_CHABANKIDLE. */
	bool allIdle = true;

	for(int i=0; ( i<NUM_BANKS ) && allIdle; i++) {
		allIdle = getRegister(BSP_FSM(i)) == BS_IDLE;
	}

	if(allIdle && getRegister(WR_STAT) == WR_STAT_IDLE) {
		setRegister(MON_CHABANKIDLE, 0);
	}




	/**************************************************************************************
	 * If Issue flag is on, Execute command
	 **************************************************************************************/
	if(getRegister(FCP_ISSUE) == ISSUE_ENABLE)
	{
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Command ISSUED\n");

		if(getRegister(WR_STAT) == WR_STAT_BUSY) {
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Waiting Room is Busy, ignore this command\n");
		}
		else
		{
			getCommandInfo();


			//The Banks FSM is already running.
			if(getRegister(BSP_FSM(curFCPCommand.bank)) != BS_IDLE)
			{
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "%d Bank is busy, put this command into WR\n", curFCPCommand.bank);

				//Active Wating Room.
				setRegister(WR_BANK, curFCPCommand.bank);
				setRegister(WR_STAT, WR_STAT_BUSY);
			}
			else {
				issueCommandToBank(curFCPCommand.bank);
				bIssued[curFCPCommand.bank] = true;
			}

			//set some banks are non-idle.
			setRegister(MON_CHABANKIDLE, 1);
		}

		//Clear ISSUE register
		setRegister(FCP_ISSUE, ISSUE_DISABLE);
	}



	/**************************************************************************************
	 * The bank that has next command in WR will be IDLE state, Issue the command.
	 **************************************************************************************/
	int wrBank = getRegister(WR_BANK);

	if(		getRegister(WR_STAT) == WR_STAT_BUSY		&&
			NextStateOfBanks[wrBank] == BS_IDLE)
	{
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "%d Bank become IDLE, issue CMD to %d Bank from WR\n", wrBank, wrBank);

		issueCommandToBank(wrBank);
		bIssued[wrBank] = true;

		setRegister(WR_STAT, WR_STAT_IDLE);
	}




	/**************************************************************************************
	 * Banks FSM
	 **************************************************************************************/
	for(int i=0; i<NUM_BANKS; i++)
	{
		if(bIssued[i]) {
			runCommand(i);
			bIssued[i] = false;
		}


		combinationalLogicBankFSM(i);
	}




	/**************************************************************************************
	 * Send Drive
	 **************************************************************************************/
	// Send(drive) all the signals set in previous update()
	//ahb_m0_mpms->sendDrive();
	// Send(drive) all the signals set in previous update()
	//ahb_m1_mpms->sendDrive();
	// Send(drive) all the signals set in previous update()
	//ahb_s0_spss->sendDrive();
}




void NANDController::update()
{
	/**************************************************************************************
	 * Banks FSM
	 **************************************************************************************/
	for(int i=0; i<NUM_BANKS; i++)
		outputLogicBankFSM(i);





	ahb_s0_spss->clear();
	ahb_s0_spss->setSig(HREADYOUT, true);


	/**************************************************************************************
	 * Data Phase
	 **************************************************************************************/
	if(_isDataCycleActive)
	{
		//offset
		uint32_t _offset = _addr - p_addr_base;
		uint32_t wData = (uint32_t)ahb_s0_spss->getWData(0);

		if(--_currentReadWait) {
			////////////////////Write////////////////////
			if (_isWrite)
			{
				setRegister(_offset, wData); //write to register
			}
			////////////////////Read////////////////////
			else
			{
				ahb_s0_spss->setRData(getRegister(_offset));
			}


			ahb_s0_spss->setSig(HREADYOUT, true);
			_currentReadWait = READ_WAIT_CYCLE;
			_isDataCycleActive = false;
		}
		else
		{
			ahb_s0_spss->setSig(HREADYOUT, false);
			return;
		}
	}




	/**************************************************************************************
	 * Address Phase
	 **************************************************************************************/
	if ((ahb_s0_spss->getSig(HTRANS) != AHB2_TRANS_IDLE) &&
			(ahb_s0_spss->getSig(HTRANS) != AHB2_TRANS_BUSY) &&
			(ahb_s0_spss->getSig(HSEL)) &&
			(ahb_s0_spss->getSig(HREADY)))
	{
		//get Trasnsection info
		_addr = ahb_s0_spss->getSig(HADDR);
		_isWrite = ahb_s0_spss->getSig(HWRITE);

		uint32_t _offset = _addr - p_addr_base;


		////////////////////Write////////////////////
		if(_isWrite) {
			//do nothing.
		}
		////////////////////Read////////////////////
		else {
			if(_currentReadWait <= 0) {
				ahb_s0_spss->setRData(getRegister(_offset));
			}
		}



		_isDataCycleActive = true;
		if(_currentReadWait <= 0) {
			ahb_s0_spss->setSig(HREADYOUT, true);
		}
		else {
			ahb_s0_spss->setSig(HREADYOUT, false);
		}


	}
	else {
		//if current phase is not address phase then next phase won't be data phase
		_isDataCycleActive = false;
	}





	/**************************************************************************************
	 * Send Drive
	 **************************************************************************************/
	for(int i=0; i<NUM_BANKS; i++) {
		flash_dout_SMaster[i] = tmp_flash_dout[i];
		flash_sout_SMaster[i] = tmp_flash_sout[i];
	}


	bm_read_inc_SMaster  = bm_read_inc;
	bm_write_inc_SMaster = bm_write_inc;
	bm_read_inc = 0;
	bm_write_inc = 0;

}



void NANDController::getCommandInfo()
{
	////////////////////////////////////////////////////////////////////
	// Get command infomation
	////////////////////////////////////////////////////////////////////
	curFCPCommand.cmd		= getRegister(FCP_CMD);
	curFCPCommand.bank		= getRegister(FCP_BANK);
	curFCPCommand.option	= getRegister(FCP_OPTION);
	curFCPCommand.dma_addr	= getRegister(FCP_DMA_ADDR);
	curFCPCommand.dma_cnt	= getRegister(FCP_DMA_CNT);
	curFCPCommand.col		= getRegister(FCP_COL);

	curFCPCommand.row[curFCPCommand.bank][0] = getRegister(FCP_ROW_L(curFCPCommand.bank));
	curFCPCommand.row[curFCPCommand.bank][1] = getRegister(FCP_ROW_H(curFCPCommand.bank));
	if(curFCPCommand.row[curFCPCommand.bank][0] != curFCPCommand.row[curFCPCommand.bank][1]) {
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Different row, ROW_L:%d, ROW_H:%d", curFCPCommand.row[curFCPCommand.bank][0], curFCPCommand.row[curFCPCommand.bank][1]);
	}

	curFCPCommand.dst_col		= getRegister(FCP_DST_COL);
	curFCPCommand.dst_row[0]	= getRegister(FCP_DST_ROW_L);
	curFCPCommand.dst_row[1]	= getRegister(FCP_DST_ROW_H);

	curFCPCommand.cmd_id		= 0; //don't know
	curFCPCommand.issue 		= ISSUE_ENABLE;



	////////////////////////////////////////////////////////////////////
	// Print log
	////////////////////////////////////////////////////////////////////
	/*message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, ">> FCP Command Receive------------------\n");
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "cmd:\t0x%x\n", curFCPCommand.cmd);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "bank:\t0x%x\n", curFCPCommand.bank);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "option:\t0x%x\n", curFCPCommand.option);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "dma_addr:\t0x%x\n", curFCPCommand.dma_addr);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "dma_cnt:\t0x%x\n", curFCPCommand.dma_cnt);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "col:\t0x%x\n", curFCPCommand.col);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "row_l:\t0x%x\n", curFCPCommand.row[curFCPCommand.bank][0]);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "row_h:\t0x%x\n", curFCPCommand.row[curFCPCommand.bank][1]);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "dst_col:\t0x%x\n", curFCPCommand.dst_col);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "dst_row_l:\t0x%x\n", curFCPCommand.dst_row[0]);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "dst_row_h:\t0x%x\n", curFCPCommand.dst_row[1]);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "cmd_id:\t0x%x\n", curFCPCommand.cmd_id);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "issue:\t0x%x\n", curFCPCommand.issue);
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "---------------------------------------\n"); */
}



inline void NANDController::issueCommandToBank(int bank)
{
	setRegister(BSP_CMD(bank), curFCPCommand.cmd);
	setRegister(BSP_OPTION(bank), curFCPCommand.option);
	setRegister(BSP_DMA_ADDR(bank), curFCPCommand.dma_addr);
	setRegister(BSP_DMA_CNT(bank), curFCPCommand.dma_cnt);
	setRegister(BSP_COL(bank), curFCPCommand.col);
	setRegister(BSP_ROW_L(bank), curFCPCommand.row[curFCPCommand.bank][0]);
	setRegister(BSP_ROW_H(bank), curFCPCommand.row[curFCPCommand.bank][1]);
	setRegister(BSP_DST_COL(bank), curFCPCommand.dst_col);
	setRegister(BSP_DST_ROW_L(bank), curFCPCommand.dst_row[0]);
	setRegister(BSP_DST_ROW_H(bank), curFCPCommand.dst_row[1]);
	setRegister(BSP_CMD_ID(bank), curFCPCommand.cmd_id);
}





void NANDController::runCommand(int bank)
{
	switch(getRegister(BSP_CMD(bank)))
	{
		// write operations
		case FC_COL_ROW_IN_PROG: //column address - row address - [DRAM or SRAM -> flash] - program command - wait - check result
			if(getRegister(BSP_DMA_ADDR(bank)) != 0) {
				dma_done[bank] = false;
				NextStateOfBanks[bank] = BS_WRITE_DMA;
			}
			else {
				NextStateOfBanks[bank] = BS_WRITE_CMD_1;
			}

			break;


			// read operations
		case FC_COL_ROW_READ_OUT: //column address - row address - read command - wait - [flash -> DRAM or SRAM]
			NextStateOfBanks[bank] = BS_READ_CMD_1;
			break;



			// copyback operations
		case FC_COPYBACK: //see descriptions below
			NextStateOfBanks[bank] = BS_CB_CMD_1;
			break;



			// erase
		case FC_ERASE: //row address - erase command - wait - check result
			NextStateOfBanks[bank] = BS_ERASE_CMD_1;
			break;



			// unused
		case FC_COL_ROW_IN: //column address - row address - [DRAM or SRAM -> flash]
		case FC_IN:			//[DRAM or SRAM -> flash]
		case FC_IN_PROG:	//[DRAM or SRAM -> flash] - program command - wait - check result
		case FC_PROG:		//program command - wait - check result
		case FC_COL_ROW_READ:	//column address - row address - read command - wait
		case FC_OUT:			//[flash -> DRAM or SRAM]
		case FC_COL_OUT:		//column address change - [flash -> DRAM or SRAM]
		case FC_MODIFY_COPYBACK:
		case FC_WAIT: //wait (used after FC_GENERIC when the command involves flash busy signal)
		case FC_GENERIC:		//generic command (FCP_COL = command code)
		case FC_GENERIC_ADDR:	//generic address (FCP_ROW_L and FCP_ROW_H = address, FCP_DMA_CNT = cycle count)
		case FC_READ_ID:		//read_ID command - [flash -> SRAM] (FCP_OPTION = 0, FCP_DMA_ADDR = SRAM address, FCP_DMA_CNT = 16, FCP_COL = 0)
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Unused Command 0x%X\n", curFCPCommand.cmd);
			break;


		default:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Invalid Command 0x%X\n", curFCPCommand.cmd);
			break;
	}
}



void NANDController::combinationalLogicBankFSM(int bank)
{
	/*****************************************************************************
	 * Get pointers that indicating specific bank.
	 *****************************************************************************/
	uint8_t *pStateFSMBanks = ((uint8_t*)m_regs)+BSP_FSM(bank);
	uint8_t *nextState = &(NextStateOfBanks[bank]);
	uint32_t *index = &(curIdx[bank]);




	/*****************************************************************************
	 * Move to Next state
	 *****************************************************************************/
	*pStateFSMBanks = *nextState;



	/*****************************************************************************
	 * Define Next state
	 *****************************************************************************/
	switch(*pStateFSMBanks)
	{
		case BS_IDLE:
			break;


			//////////////////////////////Read Status//////////////////////////////
		case BS_RS_CMD:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_RS_CMD\n", bank);
			*nextState = (uint8_t)BS_RS_DATA;
			break;

		case BS_RS_DATA:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_RS_DATA\n", bank);
			*nextState = (uint8_t)BS_IDLE; //finish
			break;


			//////////////////////////////Read//////////////////////////////
		case BS_READ_CMD_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_CMD_1\n", bank);
			*nextState = (uint8_t)BS_READ_COL_1;
			break;

		case BS_READ_COL_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_COL_1\n", bank);
			*nextState = (uint8_t)BS_READ_COL_2;
			break;

		case BS_READ_COL_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_COL_2\n", bank);
			*nextState = (uint8_t)BS_READ_ROW_1;
			break;

		case BS_READ_ROW_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_ROW_1\n", bank);
			*nextState = (uint8_t)BS_READ_ROW_2;
			break;

		case BS_READ_ROW_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_ROW_2\n", bank);
			*nextState = (uint8_t)BS_READ_CMD_2;
			break;

		case BS_READ_CMD_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_CMD_2\n", bank);
			*nextState = (uint8_t)BS_READ_WAIT;
			flash_inputSignal_active[bank] = false;

			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_READ_WAIT\n", bank);
			break;

		case BS_READ_WAIT:
			if(flash_inputSignal_active[bank])
			{
				if(RBn[bank] == READY) {
					*nextState = *pStateFSMBanks = (uint8_t)BS_READ_DATA;
					*index = 0;
					flash_inputSignal_active[bank] = false;
				}
			}
			else {
				flash_inputSignal_active[bank] = true;
			}
			break;

		case BS_READ_DATA: //1024 iteration: using curReadIdx
			if(*index == 0) {
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_READ_DATA\n", bank);
			}


			if(*index >= BYTE_PER_PAGE-4) {
				if(getRegister(BSP_DMA_ADDR(bank)) != 0) {
					dma_done[bank] = false;
					*nextState = (uint8_t)BS_READ_DMA; //dma
				}
				else {
					*nextState = (uint8_t)BS_IDLE; //finish
				}
			}
			break;

		case BS_READ_DMA:
			if(dma_done[bank]) //Write read data into external memory.
			{
				dma_running_bank = DMA_IDLE;

				if(getRegister(BSP_OPTION(bank)) & FO_B_SATA_R)
				{
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_READ_INC_BM\n", bank);
					*pStateFSMBanks = (uint8_t)BS_READ_INC_BM;
					*nextState = (uint8_t)BS_IDLE; //Move to state for BufferManasger
				}
				else {
					*nextState = *pStateFSMBanks = (uint8_t)BS_IDLE; //finish
				}
			}
			break;

		case BS_READ_INC_BM:
			*nextState = (uint8_t)BS_IDLE;
			break;



			//////////////////////////////Write//////////////////////////////
		case BS_WRITE_DMA:
			if(dma_done[bank]) { //Read data that will be wrote into nand flash from external memory.
				dma_running_bank = DMA_IDLE;

				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_WRITE_CMD_1\n", bank);
				*pStateFSMBanks = (uint8_t)BS_WRITE_CMD_1;
				*nextState = (uint8_t)BS_WRITE_COL_1;
			}
			break;

		case BS_WRITE_CMD_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_CMD_1\n", bank);
			*nextState = (uint8_t)BS_WRITE_COL_1;
			break;

		case BS_WRITE_COL_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_COL_1\n", bank);
			*nextState = (uint8_t)BS_WRITE_COL_2;
			break;

		case BS_WRITE_COL_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_COL_2\n", bank);
			*nextState = (uint8_t)BS_WRITE_ROW_1;
			break;

		case BS_WRITE_ROW_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_ROW_1\n", bank);
			*nextState = (uint8_t)BS_WRITE_ROW_2;
			break;

		case BS_WRITE_ROW_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_ROW_2\n", bank);
			*nextState = (uint8_t)BS_WRITE_DATA;
			*index = 0;
			break;

		case BS_WRITE_DATA: //1024 iteration: using curWriteIdx
			if(*index == 0) {
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_DATA, writeIdx: %d\n", bank, *index);
			}

			if(*index >= BYTE_PER_PAGE-2) {
				*nextState = (uint8_t)BS_WRITE_CMD_2;
			}
			break;

		case BS_WRITE_CMD_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_WRITE_CMD_2\n", bank);
			*nextState = (uint8_t)BS_WRITE_WAIT;
			flash_inputSignal_active[bank] = false;

			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_WRITE_WAIT\n", bank);
			break;

		case BS_WRITE_WAIT:
			if(flash_inputSignal_active[bank])
			{
				if(RBn[bank] == READY)
				{
					if(getRegister(BSP_OPTION(bank)) & FO_B_SATA_W) {
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_WRITE_INC_BM\n", bank);
						*pStateFSMBanks = (uint8_t)BS_WRITE_INC_BM; //Move to the state for Buffer manager
						*nextState = (uint8_t)BS_RS_CMD;
					}
					else {
						//*pStateFSMBanks = (uint8_t)BS_RS_CMD; //finish
						//*nextState = (uint8_t)BS_RS_DATA;
						*nextState = (uint8_t)BS_RS_CMD;
					}

					flash_inputSignal_active[bank] = false;
				}
			}
			else {
				flash_inputSignal_active[bank] = true;
			}
			break;

		case BS_WRITE_INC_BM:
			*nextState = (uint8_t)BS_RS_CMD;
			break;


			//////////////////////////////Copy-Back//////////////////////////////
		case BS_CB_CMD_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_CMD_1\n", bank);
			*nextState = (uint8_t)BS_CB_COL_1;
			break;

		case BS_CB_COL_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_COL_1\n", bank);
			*nextState = (uint8_t)BS_CB_COL_2;
			break;

		case BS_CB_COL_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_COL_2\n", bank);
			*nextState = (uint8_t)BS_CB_ROW_1;
			break;

		case BS_CB_ROW_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_ROW_1\n", bank);
			*nextState = (uint8_t)BS_CB_ROW_2;
			break;

		case BS_CB_ROW_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_ROW_2\n", bank);
			*nextState = (uint8_t)BS_CB_CMD_2;
			break;

		case BS_CB_CMD_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_CMD_2\n", bank);
			*nextState = (uint8_t)BS_CB_WAIT_1;
			flash_inputSignal_active[bank] = false;

			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_CB_WAIT_1\n", bank);
			break;

		case BS_CB_WAIT_1:
			if(flash_inputSignal_active[bank])
			{
				if(RBn[bank] == READY)
				{
					*pStateFSMBanks = (uint8_t)BS_CB_CMD_3;
					*nextState = (uint8_t)BS_CB_COL_3;

					flash_inputSignal_active[bank] = false;
				}
			}
			else {
				flash_inputSignal_active[bank] = true;
			}
			break;

		case BS_CB_CMD_3:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_CMD_3\n", bank);
			*nextState = (uint8_t)BS_CB_COL_3;
			break;

		case BS_CB_COL_3:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_COL_3\n", bank);
			*nextState = (uint8_t)BS_CB_COL_4;
			break;

		case BS_CB_COL_4:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_COL_4\n", bank);
			*nextState = (uint8_t)BS_CB_ROW_3;
			break;

		case BS_CB_ROW_3:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_ROW_3\n", bank);
			*nextState = (uint8_t)BS_CB_ROW_4;
			break;

		case BS_CB_ROW_4:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_ROW_4\n", bank);
			*nextState = (uint8_t)BS_CB_CMD_4;
			break;

		case BS_CB_CMD_4:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_CB_CMD_4\n", bank);
			*nextState = (uint8_t)BS_CB_WAIT_2;
			flash_inputSignal_active[bank] = false;

			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_CB_WAIT_2\n", bank);
			break;

		case BS_CB_WAIT_2:
			if(flash_inputSignal_active[bank])
			{
				if(RBn[bank] == READY)
				{
					//*pStateFSMBanks = (uint8_t)BS_RS_CMD; //finish
					//*nextState = (uint8_t)BS_RS_DATA;
					*nextState = (uint8_t)BS_RS_CMD;

					flash_inputSignal_active[bank] = false;
				}
			}
			else {
				flash_inputSignal_active[bank] = true;
			}
			break;


			//////////////////////////////Erase//////////////////////////////
		case BS_ERASE_CMD_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_ERASE_CMD_1\n", bank);
			*nextState = (uint8_t)BS_ERASE_ROW_1;
			break;

		case BS_ERASE_ROW_1:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_ERASE_ROW_1\n", bank);
			*nextState = (uint8_t)BS_ERASE_ROW_2;
			break;

		case BS_ERASE_ROW_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_ERASE_ROW_2\n", bank);
			*nextState = (uint8_t)BS_ERASE_CMD_2;
			break;

		case BS_ERASE_CMD_2:
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] State: BS_ERASE_CMD_2\n", bank);
			*nextState = (uint8_t)BS_ERASE_WAIT;
			flash_inputSignal_active[bank] = false;

			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Move to BS_ERASE_WAIT\n", bank);
			break;

		case BS_ERASE_WAIT:

			if(flash_inputSignal_active[bank])
			{
				if(RBn[bank] == READY)
				{
					//*pStateFSMBanks = (uint8_t)BS_RS_CMD; //finish
					//*nextState = (uint8_t)BS_RS_DATA;
					*nextState = (uint8_t)BS_RS_CMD;

					flash_inputSignal_active[bank] = false;
				}
			}
			else {
				flash_inputSignal_active[bank] = true;
			}
			break;


			//////////////////////////////Error//////////////////////////////
		default:
			*nextState = (uint8_t)BS_IDLE;
	}
}



void NANDController::outputLogicBankFSM(int bank)
{
	uint32_t r_data = 0;
	uint32_t *index = &(curIdx[bank]);
	signal_t signals;
	uint8_t w_data_l;
	uint8_t w_data_h;

	//Default outputs
	tmp_flash_sout[bank] = 34; //CEn = disable
	tmp_flash_dout[bank] = 0;

	switch(getRegister(BSP_FSM(bank)))
	{
		case BS_IDLE:
			//do nothing.
			break;


			//////////////////////////////Read Status//////////////////////////////
		case BS_RS_CMD:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_READ_STATE;
			break;

		case BS_RS_DATA:
			r_data = flash_din_SSlave[bank];
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Read data: 0x%x\n", r_data);
			break;


			//////////////////////////////Read//////////////////////////////
		case BS_READ_CMD_1:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_READ_1;
			break;

		case BS_READ_COL_1: //two column addresses are zero.
		case BS_READ_COL_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = 0; //fix
			break;

		case BS_READ_ROW_1:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_L(bank));
			break;

		case BS_READ_ROW_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_H(bank));
			break;

		case BS_READ_CMD_2:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_READ_2;
			break;

		case BS_READ_WAIT:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = DISABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			break;

		case BS_READ_DATA: //1024 iteration: using curReadIdx
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = DISABLEn;
			signals.ALE = DISABLE;
			signals.REn = ENABLEn;
			signals.WPn = DISABLEn; //fix

			if(flash_inputSignal_active[bank]) {
				//read data
				r_data = flash_din_SSlave[bank]; //16bit i/o
				buffers[bank][(*index)] = (uint8_t)(r_data & 0x00FF);
				buffers[bank][(*index)+1] = (uint8_t)((r_data & 0xFF00) >> 8);

				//if(p_enableDbgMsg)
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Read data: 0x%X, index: %d\n", bank, r_data, *index);

				(*index) += 2;
			}
			else {
				flash_inputSignal_active[bank] = true;
			}

			tmp_flash_sout[bank] = encodingSignals(signals);
			//;//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Drive to bank#%d] sout(%d)", bank, encoded_signal);
			break;

		case BS_READ_DMA:
			if(runDMA(bank, 1)) {
				dma_done[bank] = true;
			}
			break;

		case BS_READ_INC_BM:
			bm_read_inc = 1;
			break;


			//////////////////////////////Write//////////////////////////////
		case BS_WRITE_DMA:
			if(runDMA(bank, 0)) {
				dma_done[bank] = true;
			}
			break;

		case BS_WRITE_CMD_1:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_WRITE_1;
			break;

		case BS_WRITE_COL_1:
		case BS_WRITE_COL_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_COL(bank)); //fix
			break;

		case BS_WRITE_ROW_1:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_L(bank));
			break;

		case BS_WRITE_ROW_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_H(bank));
			break;

		case BS_WRITE_DATA: //1024 iteration: using curWriteIdx
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			w_data_l = buffers[bank][(*index)]; //need implement
			w_data_h = (buffers[bank][(*index)+1]);

			//if(p_enableDbgMsg)
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] Write data: 0x%X, index: %d\n", bank, ((w_data_h << 8)|w_data_l), *index);

			(*index)+=2;
			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = ((w_data_h << 8)|w_data_l);
			break;

		case BS_WRITE_CMD_2:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_WRITE_2;
			break;

		case BS_WRITE_WAIT:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = DISABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			break;

		case BS_WRITE_INC_BM:
			bm_write_inc = 1;
			break;


			//////////////////////////////Copy-Back//////////////////////////////
		case BS_CB_CMD_1:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_CP_1;
			break;

		case BS_CB_COL_1:
		case BS_CB_COL_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_COL(bank));
			break;

		case BS_CB_ROW_1:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_L(bank));
			break;

		case BS_CB_ROW_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_H(bank));
			break;

		case BS_CB_CMD_2:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_CP_2;
			break;

		case BS_CB_WAIT_1:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = DISABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			break;

		case BS_CB_CMD_3:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_CP_3;
			break;

		case BS_CB_COL_3:
		case BS_CB_COL_4:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_DST_COL(bank));
			break;

		case BS_CB_ROW_3:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_DST_ROW_L(bank));
			break;

		case BS_CB_ROW_4:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_DST_ROW_H(bank));
			break;

		case BS_CB_CMD_4:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_CP_4;
			break;

		case BS_CB_WAIT_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = DISABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			break;


			//////////////////////////////Erase//////////////////////////////
		case BS_ERASE_CMD_1:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_ERASE_1;
			break;

		case BS_ERASE_ROW_1:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_L(bank));
			break;

		case BS_ERASE_ROW_2:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = ENABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = getRegister(BSP_ROW_H(bank));
			break;

		case BS_ERASE_CMD_2:
			signals.CLE = ENABLE;
			signals.CEn = ENABLEn;
			signals.WEn = ENABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			tmp_flash_dout[bank] = FCMD_ERASE_2;
			break;

		case BS_ERASE_WAIT:
			signals.CLE = DISABLE;
			signals.CEn = ENABLEn;
			signals.WEn = DISABLEn;
			signals.ALE = DISABLE;
			signals.REn = DISABLEn;
			signals.WPn = DISABLEn; //fix

			tmp_flash_sout[bank] = encodingSignals(signals);
			break;


			//////////////////////////////Error//////////////////////////////
		default:
			;
	}
}




void NANDController::printRegisters() {
	//for(int i=0; i<NUM_REGISTER; i++) {
	//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,"offset: %d, \tvalue: %d\n", i, m_regs[i]);
	//}
}


void NANDController::log(const char *format, ...) {
	if(p_enableDbgMsg) {
		va_list args;
		va_start(args, format);

		//;//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, format, args);

		va_end(args);
	}
}


int NANDController::encodingSignals(signal_t signals) {
	int result = 0;

	result |= signals.ALE << 0;
	result |= signals.CEn << 1;
	result |= signals.CLE << 2;
	result |= signals.REn << 3;
	result |= signals.WEn << 4;
	result |= 1 << 5; //signals.WPn

	return result;
}

void NANDController::decodingSignals(int value, signal_t *signals) {
	signals->ALE = value & 1;
	signals->CEn = value & 2;
	signals->CLE = value & 4;
	signals->REn = value & 8;
	signals->WEn = value & 16;
	signals->WPn = value & 32;
}

void NANDController::initMyVariables()
{
	//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[initMyVariables]\n");


	//init all registers
	memset(m_regs, 0x0, sizeof(uint32_t)*NUM_REGISTER);
	setRegister(FCP_ISSUE, ISSUE_DISABLE);
	setRegister(WR_STAT, WR_STAT_IDLE);


	for(int i=0; i<NUM_BANKS; i++)
	{
		//init all State register of Banks
		setRegister(BSP_FSM(i), BS_IDLE);
		NextStateOfBanks[i] = (uint8_t)BS_IDLE;

		//init internal buffers
		memset(&buffers[i], 0x0, BYTE_PER_PAGE);

		//for flash master interface
		tmp_flash_dout[i] = 0x0;
		tmp_flash_sout[i] = 0x0;

		//for flash slave interface
		RBn[i] = 0x0;
		tmp_flash_RBn[i] = 0x0;
		tmp_flash_din[i] = 0x0;
		flash_inputSignal_active[i] = false;
		curIdx[i] = 0;

		bIssued[i] = false;

		//DMA
		initDMA(i);
		dma_done[i] = false;
	}


	memset(&curFCPCommand, 0x0, sizeof(fcp_t));


	//for ahb_s0_interface
	_isDataCycleActive = false;
	_isWrite = false;
	_currentReadWait = READ_WAIT_CYCLE;
	_addr = 0;
}


#define SET_BYTE(dst,n,src) ((dst) |= ((src) << ((n)*8)))
#define CLR_BYTE(p,n) ((p) &= (~((0xFF) << ((n)*8))))

void NANDController::setRegister(uint32_t offset, uint32_t val)
{
	//invalid offset
	if(offset > ((NUM_REGISTER-1)*sizeof(uint32_t))) {
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Invalid Register offset 0x%X\n", offset);
		return;
	}

	//Offset for BSP_INTR or BSP_FSM registers, 1byte unit
	if(BSP_INTR_BASE <= offset && offset < BSP_CHASTAT)
	{
		uint32_t tmp = m_regs[offset/4];

		CLR_BYTE(tmp, (offset%4));
		SET_BYTE(tmp, (offset%4), val&0xFF);


		m_regs[offset/4] = tmp;
	}
	//All other registers, 4byte unit
	else {
		m_regs[offset/4] = val;
	}
}

uint32_t NANDController::getRegister(uint32_t _offset)
{
	uint32_t result = 0;

	//Offset for BSP_INTR or BSP_FSM registers, 1byte unit
	if(BSP_INTR_BASE <= _offset && _offset < BSP_CHASTAT)
	{
		uint32_t tmp = m_regs[_offset/4];
		tmp = tmp >> ((_offset%4)*8);
		tmp &= 0x000000FF;

		result = tmp;
	}
	//All other registers, 4byte unit
	else {
		result = m_regs[_offset/4];
	}

	return result;
}



inline void NANDController::initDMA(int bank)
{
	dma_running_bank = DMA_IDLE;
	dma_addr = 0;
	dma_cnt = 0;
	dma_offset = 0;
	dma_write = 0;
	dma_active_data_phase = false;
	dma_wait_data_phase = false;
	dma_bus_granted = false;
	curIdx[bank] = 0;
	//memset(buffers[bank], 0xFF, BYTE_PER_PAGE);
}




bool NANDController::runDMA(int bank, int bWrite)
{
	//if DMA is in idle state, set variables up to run for this bank.
	if(dma_running_bank == DMA_IDLE) {
		initDMA(bank);

		dma_offset = getRegister(BSP_COL(bank)) * 512; //sector size == 512
		dma_running_bank = bank;
		dma_addr = getRegister(BSP_DMA_ADDR(bank));
		dma_cnt = getRegister(BSP_DMA_CNT(bank));
		curIdx[bank] = 0;
		dma_write = bWrite;


		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] [Start DMA] addr: 0x%X, cnt: %d, offset: %d, write: %d, \n", bank, dma_addr, dma_cnt, dma_offset, dma_write);
	}



	//if current DMA isn't for this bank, exit.
	if(dma_running_bank != bank) {
		return false;
	}



	bool busGranted = ahb_m1_mpms->getSig(HGRANT);
	bool HReady = ahb_m1_mpms->getSig(HREADY);

	ahb_m1_mpms->clear();
	ahb_m1_mpms->setSig(HBUSREQ, true); //default


	//////////////////////Bus granted//////////////////////
	if(busGranted)
	{
		//////////////////////Data phase//////////////////////
		if(dma_active_data_phase)
		{
			//////////////////////From buffer, To destination of DMA//////////////////////
			if(dma_write) {
				/* Get 32bit data from buffer, and build data up on tmp. */
				uint32_t tmp = *((uint32_t*)&buffers[bank][curIdx[bank]+dma_offset]);
				ahb_m1_mpms->setWData(tmp, 0);
				//if(p_enableDbgMsg) {
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] [DMA] write data: 0x%08X, index: %d, buffer[index]: 0x%X%X%X%X\n",
				//bank, tmp, curIdx[bank]+dma_offset, buffers[bank][curIdx[bank]+dma_offset], buffers[bank][curIdx[bank]+dma_offset+1], buffers[bank][curIdx[bank]+dma_offset+2], buffers[bank][curIdx[bank]+dma_offset+3]);
				//}



				//Slave is Ready
				if(HReady) {
					curIdx[bank] += 4;
				}
				//Slave is Busy
				else {
					; //Doesn't increase index because to drive same signals with current cycle.
				}
			}
			//////////////////////From source of DMA, To buffer//////////////////////
			else {
				//////////////////////Wait 1cycle//////////////////////
				if(HReady) {	//Slave is Ready
					if(dma_wait_data_phase)
					{
						uint32_t r_data = ahb_m1_mpms->getRData(0);
						//if(p_enableDbgMsg) {
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] [DMA] read data: 0x%08X, index: %d",
						//bank, r_data, curIdx[bank]+dma_offset);
						//}

						*((uint32_t*)&buffers[bank][curIdx[bank]+dma_offset]) = r_data;

						//if(p_enableDbgMsg) {
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, ", buffer[index]: 0x%X%X%X%X\n", buffers[bank][curIdx[bank]+dma_offset], buffers[bank][curIdx[bank]+dma_offset+1], buffers[bank][curIdx[bank]+dma_offset+2], buffers[bank][curIdx[bank]+dma_offset+3]);
						//}

						curIdx[bank] += 4;

					}
					else {
						dma_wait_data_phase = true;
					}
				}
				else {	//Slave is Busy
					; //Do nothing because current data is invalid since the slave is not ready.
				}
			}
		}
		else {
			;
		}



		//////////////////////finish//////////////////////
		if(curIdx[bank] >= dma_cnt) {
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Bank#%d] [End DMA] addr: 0x%X, cnt: %d, write: %d\n", bank, dma_addr, dma_cnt, dma_write);
			ahb_m1_mpms->setSig(HBUSREQ, false);

			return true;
		}


		//////////////////////Address phase//////////////////////
		if(!dma_wait_data_phase) {
			ahb_m1_mpms->setAddr(dma_addr+curIdx[bank]+dma_offset, AHB2_TRANS_NONSEQ, dma_write, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			dma_active_data_phase = true;
		}
		else {
			ahb_m1_mpms->setAddr(dma_addr+curIdx[bank]+dma_offset+4, AHB2_TRANS_SEQ, dma_write, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}


	return false;
}

BDDI* NANDController::GetBDDI()
{
	return bddi;
}

char* NANDController::GetModuleName()
{
	return (char*)"NANDController";
}

void NANDController::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	ahb_m0_mpms = new BD_AHBPort_MM((char*)"MM_M0");
	ahb_m1_mpms = new BD_AHBPort_MM((char*)"MM_M0");
	ahb_s0_spss = new BD_AHBPort_SS((char*)"SS_S0");

	// for BDDI
	bddi = new NANDController_BDDI(this);

	////////////////////////////My code////////////////////////////
	initMyVariables();
	////////////////////////////End of My code////////////////////////////


}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new NANDController(ModuleInstanceName);
}

