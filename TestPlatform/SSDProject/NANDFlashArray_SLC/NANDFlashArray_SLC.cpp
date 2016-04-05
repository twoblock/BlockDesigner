#include "NANDFlashArray_SLC.h"

//////////////////// Delay Information ////////////////////
//defineParameter( "tADL", "5", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tBERS", "640000", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tPROG", "36000", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tBERS", "64", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tPROG", "36", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tR", "2", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tRC", "1", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tRR", "1", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tWB", "5", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "tWC", "1", eslapi::CASI_PARAM_VALUE, 0);

void NANDFlashArray_SLC::excuteCommand()
{
	switch(temp_reg)
	{
		//case READ_COPYBACK_CMD1: duplicated with READ_CMD1
		case READ_CMD1:
		case PROG_CMD1:
		case PROG_COPYBACK_CMD1:
			state = ADDRESS;
			busy_mode = NOT_BUSY;

			b_RWaddr_first_state = true;
			b_Eaddr_first_state = false;
			break;

		case READ_CMD2:
			state = BUSY;
			busy_mode = BUSY_READ;

			b_RWaddr_first_state = false;
			b_Eaddr_first_state = false;


			b_prepared_busy = false;
			p_RBn = LOW;
			break;

		case READ_COPYBACK_CMD2:
			state = BUSY;
			b_RWaddr_first_state = false;
			b_Eaddr_first_state = false;

			busy_mode = BUSY_CB_READ;
			b_prepared_busy = false;
			p_RBn = LOW;
			break;

		case PROG_CMD2:
			//case PROG_COPYBACK_CMD2: duplicated with PROG_CMD2
			state = BUSY;
			p_RBn = LOW;
			b_RWaddr_first_state = false;
			b_Eaddr_first_state = false;

			busy_mode = BUSY_WRITE;
			b_prepared_busy = false;
			break;

		case STATUS_CMD:
			state = STATUS;
			busy_mode = NOT_BUSY;

			///////////////////////
			// Need implementing //
			///////////////////////

			temp_data = SUCCESS;
			break;

		case ERASE_CMD1:
			state = ADDRESS;
			b_RWaddr_first_state = false;
			b_Eaddr_first_state = true;

			busy_mode = NOT_BUSY;
			break;

		case ERASE_CMD2:
			state = BUSY;
			p_RBn = LOW;
			b_RWaddr_first_state = false;
			b_Eaddr_first_state = false;

			busy_mode = BUSY_ERASE;
			b_prepared_busy = false;
			break;

		default:
			break;
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] Command is illegal(temp_reg: %d)\n", temp_signal);
	}
}

void NANDFlashArray_SLC::communicate()
{
	//////////////////// Busy cycle ////////////////////
	if(busy_mode != NOT_BUSY)
	{
		if(--busy_delay == 0) //When delay ended.
		{
			switch(busy_mode)
			{
				case BUSY_CB_READ:
					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Copy-back)\n");
				case BUSY_READ:
					state = COMMAND;
					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Busy state] Read end. page:%d, blk:%d\n", temp_page_n, temp_blk_n);
					break;

				case BUSY_CB_WRITE:
					//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Copy-back)\n");
				case BUSY_WRITE:
					state = COMMAND;
					m_blocks[temp_blk_n].write(temp_page_n, temp_buffers, PAGE_SIZE);
					//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Busy state] Write end. page:%d, blk:%d\n", temp_page_n, temp_blk_n);
					break;

				case BUSY_ERASE:
					state = COMMAND;
					//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Busy state] Erase end.\n");
					break;

				default:
					break;
					//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] Busy mode is illegal. (busy_mode=%d)\n", busy_mode);
			}

			busy_mode = NOT_BUSY;
			p_RBn = HIGH;
		}
	}
	else //////////////////// Get signals from controller and change mode ////////////////////
	{
		temp_signal = S_in_SSlave;

		//Idle
		switch(temp_signal)
		{
			case STAND_BY:
				state = IDLE;
				break;

			case R_CMD:
				temp_reg = r_CmdReg;
				excuteCommand();
				break;

			case R_ADDR:
				//Read/Write address cycle
				if(RWAddr_DelayCycles)
				{
					RWAddr_DelayCycles--;

					if(RWAddr_DelayCycles == 4 || RWAddr_DelayCycles == 3) {
						temp_reg = r_C_AddrReg;
					}



					if(RWAddr_DelayCycles == 2)
					{
						temp_reg = r_P_AddrReg;
						if(temp_reg >= PAGES_PER_BLOCK) {
							//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] input page addr is too large(0x$x)\n", temp_reg);
							return;
						}
						temp_page_n = temp_reg;
					}



					if(RWAddr_DelayCycles == 1)
					{
						temp_reg = r_B_AddrReg;
						if(temp_reg >= BLOCKS_PER_CHIP) {
							//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] input block addr is too large(0x$x)\n", temp_reg);
							return;
						}
						temp_blk_n = temp_reg;
					}
				}



				if(EAddr_DelayCycles)
				{
					EAddr_DelayCycles--;

					if(EAddr_DelayCycles == 1)
					{
						temp_reg = r_B_AddrReg;
						if(temp_reg >= BLOCKS_PER_CHIP) {
							//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] input block addr is too large(0x$x)\n", temp_reg);
							return;
						}

						temp_blk_n = temp_reg;
					}
				}
				break;

			case D_OUT:
			case D_IN:
				state = DATA;
				break;
		}
	}




	switch(state)
	{
		case IDLE :
			RBn_SMaster = p_RBn;
			if(p_RBn != HIGH) {
				//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] RBn is low\n");
				return;
			}
			break;

		case ADDRESS :
			RBn_SMaster = p_RBn;
			if(p_RBn != HIGH) {
				//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] RBn is low\n");
				return;
			}

			if(b_RWaddr_first_state) {
				RWAddr_DelayCycles = p_tWC * 5;
				b_RWaddr_first_state = false;
				for(int i=0; i<BLOCKS_PER_CHIP; i++)
					m_indexes[i] = 0;
			}

			if(b_Eaddr_first_state) {
				EAddr_DelayCycles = p_tWC * 2;
				b_Eaddr_first_state = false;
			}
			break;

		case COMMAND :
			RBn_SMaster = p_RBn;
			if(p_RBn != HIGH) {
				//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] RBn is low\n");
				return;
			}
			break;

		case BUSY :
			RBn_SMaster = p_RBn;
			if(p_RBn != LOW) {
				//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] RBn is high\n");
				return;
			}

			if(!b_prepared_busy)
			{
				b_prepared_busy = true;
				switch(busy_mode)
				{
					case BUSY_CB_READ:
						//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Copy-back)\n");
					case BUSY_READ:
						busy_delay = p_tR + p_tRR;
						m_blocks[temp_blk_n].read(temp_page_n, temp_buffers, PAGE_SIZE);
						//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Busy state] Read start. it takes %d cycles. page:%d, blk:%d\n", busy_delay, temp_page_n,temp_blk_n);
						break;

					case BUSY_CB_WRITE:
						//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Copy-back)\n");
					case BUSY_WRITE:
						busy_delay = p_tWB + p_tPROG;
						//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Busy state] Write start. it takes %d cycles. page:%d, blk:%d\n", busy_delay, temp_page_n, temp_blk_n);
						break;

					case BUSY_ERASE:
						busy_delay = p_tWB + p_tBERS;
						for(erase_page=0; erase_page<PAGES_PER_BLOCK; erase_page++)
							m_blocks[temp_blk_n].erase(temp_page_n);

						//			message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Busy state] Erase start. it takes %d cycles. blk:%d\n", busy_delay, temp_blk_n);
						break;
				}
			}
			break;

		case DATA :
			RBn_SMaster = p_RBn;
			if(p_RBn != HIGH) {
				//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] RBn is low\n");
				return;
			}

			//din
			if(temp_signal == D_IN)
			{
				temp_data = r_DataReg;
				/*	if(p_enableDbgMsg) {
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Din] Block: %d, Page: %d, Index: %d, Data 0x%x\n", temp_blk_n, temp_page_n, m_indexes[temp_blk_n], temp_data);
						}
						*/
				unsigned char temp_byte = 0;
				temp_byte = temp_data & 0x00FF;
				temp_buffers[m_indexes[temp_blk_n]] = temp_byte;
				m_indexes[temp_blk_n]++;

				temp_byte = (temp_data>>8) & 0x00FF;
				temp_buffers[m_indexes[temp_blk_n]] = temp_byte;
				m_indexes[temp_blk_n]++;
			}
			//dout
			else
			{
				temp_data = 0;
				temp_data = (unsigned char)temp_buffers[m_indexes[temp_blk_n]];
				m_indexes[temp_blk_n]++;
				temp_data |= ((unsigned char)temp_buffers[m_indexes[temp_blk_n]]<<8);
				m_indexes[temp_blk_n]++;

				D_out_SMaster = temp_data;
				/*		if(p_enableDbgMsg) {
							message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Dout] Block: %d, Page: %d, Index: %d, Data 0x%x\n", temp_blk_n, temp_page_n, m_indexes[temp_blk_n]-2, temp_data);
							}
							*/
			}

			break;

		case STATUS :
			RBn_SMaster = p_RBn;
			if(p_RBn != HIGH) {
				//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "[Error] RBn is low\n");
				return;
			}

			D_out_SMaster = temp_data;
			break;
	}
}

void NANDFlashArray_SLC::update()
{
	;
}

void NANDFlashArray_SLC::driveSignal()
{
	r_CmdReg = D_in_SSlave;
	r_P_AddrReg = D_in_SSlave; 
	r_B_AddrReg = D_in_SSlave; 
	r_DataReg = D_in_SSlave;   
	r_C_AddrReg = D_in_SSlave; 
}

void NANDFlashArray_SLC::MyInit()
{
	////////// Blocks Init //////////
	for(int i=0; i<BLOCKS_PER_CHIP; i++) {
		m_blocks[i].init(PAGES_PER_BLOCK, SECTORS_PER_PAGE, PAGE_SIZE);
		m_indexes[i] = 0;
	}
	//////////////////////////////////

	///// Pin Variable Init /////
	p_CLE = LOW;
	p_CEn = HIGH;
	p_WEn = HIGH;
	p_WPn = HIGH;
	p_ALE = LOW;
	p_RBn = HIGH;
	p_REn = HIGH;
	/////////////////////////////

	busy_mode = NOT_BUSY;

	///// Global Variable Init /////
	Dout_DelayCycles = 0;
	b_RWaddr_first_state = false;
	b_Eaddr_first_state = false;
	b_prepared_busy = false;
	erase_page = 0;
	state = IDLE;
	RWAddr_DelayCycles = 0;
	EAddr_DelayCycles = 0;
	check_signal = STAND_BY;
	temp_signal = STAND_BY;
	temp_reg = DEBUG_VALUE;
	temp_page_n = DEBUG_VALUE;
	temp_blk_n = DEBUG_VALUE;
	r_C_AddrReg = 0;
	////////////////////////////////
}

BDDI* NANDFlashArray_SLC::GetBDDI()
{
	return bddi;
}

char* NANDFlashArray_SLC::GetModuleName()
{
	return (char*)"NANDFlashArray_SLC";
}

void NANDFlashArray_SLC::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	D_in_SSlave.set_port_name("D_in_SSlave");
	S_in_SSlave.set_port_name("S_in_SSlave");
	D_out_SMaster.set_port_name("D_out_SMaster");
	RBn_SMaster.set_port_name("RBn_SMaster");

	// for BDDI
	bddi = new NANDFlashArray_SLC_BDDI(this);

	r_DataReg = 0;
	r_CmdReg = 0;
	r_P_AddrReg = 0;
	r_B_AddrReg = 0;
	r_StatusReg = 0;

	//my code
	MyInit();
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new NANDFlashArray_SLC(ModuleInstanceName);
}
