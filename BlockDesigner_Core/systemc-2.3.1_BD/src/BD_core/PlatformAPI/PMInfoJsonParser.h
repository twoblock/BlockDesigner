//-----------------------------------------------------------------------------
// Design								: Platform Manager Information Parser
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: PMInfoJsonParser.h
// Date	       					: 2016/1/19
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Extract the information of Platform Manager from Json file
// ----------------------------------------------------------------------------

#ifndef __PM_INFO_JSON_PARSER__
#define __PM_INFO_JSON_PARSER__

#include "json/json.h"
#include <iostream>
#include <fstream>
#include "../manager/ModuleConnectionManager.h"
#include "../SimulationAPI/ChannelManager.h"

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	enum PMInfoReturnStatus
	{
		PMInfoReturnStatusOk,
		PMInfoReturnStatusDisable,
		PMInfoReturnStatusError
	};

	/*
	 * class		    : 
	 * design	      : 
	 */
	class PMInfoJsonParser
	{
		public:
			Json::Reader InfoReader;
			Json::Value InfoRoot;
			Json::Value InfoChannel;

			PMInfoReturnStatus ParsingPlatformManagerInformation(const char *FilePath);
			PMInfoReturnStatus ParsingOwnConnectionInformation(unsigned int Index, BindingInfo* BindingObject);
			PMInfoReturnStatus ParsingChannelInformation(unsigned int Index, ChannelInfo* ChannelObject);
			PMInfoReturnStatus ParsingConnectionInformation(unsigned int PIndex, unsigned int CIndex, BindingInfo* BindingObject);

		private:
	}; 
}

#endif	// __PM_INFO_JSON_PARSER__ 
