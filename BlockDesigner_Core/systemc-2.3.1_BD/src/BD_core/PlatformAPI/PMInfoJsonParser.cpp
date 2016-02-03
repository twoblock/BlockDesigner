//-----------------------------------------------------------------------------
// Design								: Platform Manager Information Parser
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: PMInfoJsonParser.cpp
// Date	       					: 2016/1/19
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Extract the information of Platform Manager from Json file
// ----------------------------------------------------------------------------

#include "PMInfoJsonParser.h"

namespace BDapi
{
	PMInfoReturnStatus PMInfoJsonParser::ParsingPlatformManagerInformation(const char *FilePath)
	{
		bool b_ParsingStatus = false;

		ifstream PMInfo(FilePath, ifstream::binary);
		if(PMInfo == NULL)	{
			printf("Json File Path Error\n");
			return PMInfoReturnStatusError;
		}

		b_ParsingStatus = InfoReader.parse(PMInfo, InfoRoot, false);

		if(!b_ParsingStatus)	{
			cout << InfoReader.getFormatedErrorMessages() << endl;
			return PMInfoReturnStatusError;
		}

		InfoChannel = InfoRoot["BDPMD"]["Channel_Info"];

		return PMInfoReturnStatusOk;
	}

	PMInfoReturnStatus PMInfoJsonParser::ParsingOwnConnectionInformation(unsigned int Index, BindingInfo* BindingObject)
	{
		char *phw_TempBuf = NULL;
		char *phw_TokBuf = NULL;

		if(Index == InfoChannel.size())	return PMInfoReturnStatusError;
		else	{
			phw_TokBuf = (char *)InfoChannel[Index]["name"].asCString();

			BindingObject->ChannelName = InfoChannel[Index]["name"].asCString();
			phw_TempBuf = strtok(phw_TokBuf, "$");
			BindingObject->ModuleName = phw_TempBuf;
			phw_TempBuf = strtok(NULL, "$");
			BindingObject->ModulePortName = phw_TempBuf;

			return PMInfoReturnStatusOk;
		}
	}

	PMInfoReturnStatus PMInfoJsonParser::ParsingChannelInformation(unsigned int Index, ChannelInfo* ChannelObject)
	{
		if(Index == InfoChannel.size())	return PMInfoReturnStatusError;
		else	{
			ChannelObject->ChannelType = InfoChannel[Index]["channel_type"].asCString();
			ChannelObject->ChannelName = InfoChannel[Index]["name"].asCString();
			ChannelObject->DataType = InfoChannel[Index]["data_type"].asCString();

			return PMInfoReturnStatusOk;
		}
	}

	PMInfoReturnStatus PMInfoJsonParser::ParsingConnectionInformation(unsigned int PIndex, unsigned int CIndex, BindingInfo* BindingObject)
	{
		if(CIndex == InfoChannel[PIndex]["connection_info"].size())	return PMInfoReturnStatusError;
		else	{
			BindingObject->ModuleName = InfoChannel[PIndex]["connection_info"][CIndex]["module_name"].asCString();
			BindingObject->ModulePortName = InfoChannel[PIndex]["connection_info"][CIndex]["port_name"].asCString();
			BindingObject->ChannelName = InfoChannel[PIndex]["name"].asCString();
		
			return PMInfoReturnStatusOk;
		}
	}

}
