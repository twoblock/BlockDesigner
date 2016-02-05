//-----------------------------------------------------------------------------
// Design								: PMML(PlatformManager Module List) generator 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: PMMLGenerationManager.h
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: generate PMML.json for Platform Manager
// ----------------------------------------------------------------------------

#ifndef __PMML_GENERATION_MANAGER_H__
#define __PMML_GENERATION_MANAGER_H__

#include "TopManagerBase.h"
#include <pthread.h>
#include <string>
#include <list>

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : PMMLGenerationManager 
	 * design	      : PMML(PlatformManager Module List) json file generator for sc_module list
	 *                the generated information is used at Platform Manager
	 */
	class PMMLGenerationManager: public TopManagerBase
	{
		public:
			void GetOperationControl(GUI_COMMAND Command);

			string GeneratePMMLJsonFile();
			
			static PMMLGenerationManager* GetInstance();
			static void DeleteInstance();

		protected:
			PMMLGenerationManager();
		  virtual ~PMMLGenerationManager();

		private:
			string JsonFileOfPMModuleList;
			
			static PMMLGenerationManager *_PMMLGenerationManager;
			// mutex for singleton pattern 
			static pthread_mutex_t PMMLGenerationManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
