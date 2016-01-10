//-----------------------------------------------------------------------------
// Design				: Block Designer Execution Manager 
// Autor				: Bryan.Choi 
// Email				: bryan.choi@twoblocktech.com 
// File		     		: ExecutionManager.h
// Date	       			: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#ifndef EXECUTIONMANAGER_H 
#define EXECUTIONMANAGER_H 

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

namespace BDapi
{
	#define RUN   	0
	#define STOP  	1
	#define STEP  	2
	#define STEP  	3
	#define STEPN 	4
	
/*
	 * class		: ExecutionManager 
	 * description	: Control Execution of simulation 
	 * version	    : v1.0 
	 */
	class ExecutionManager
	{
		public:
		
		ExecutionManager();

		/*
		 * function 	: 함수 명
		 * design	: 함수의 간략한 설명
		 * description	: 함수의 자세한 설명
		 * param	: 함수의 인자에 대한 설명 / void 시 줄 삭제
		 * return	: 함수의 반환 값에 대한 설명 / void 시 줄 삭제
		 * issue		: 함수의 필요성 혹은 함수에서 발견된 문제점 
		 * todo		: 함수의 수정이 필요한 부분 기술
		 * caller		: 이 함수를 호출하는 함수 명 표기
		 * callee		: 이 함수가 호출하는 함수 명 표기
		 * see		: 함수의 이해를 위해 참고할 만한 함수 혹은 라인을 표기
		 */

  			static unsigned int GetExcutionFlag();
  			static SetExcutionFlag(unsigned int ExecutionControlFlag);
  			
			static unsigned int GetStepValue();
  			static SetStepValue(unsigned int StepValue);
	
		private:
			static unsigned int g_ExecutionControlFlag;
			static unsigned int g_StepValue;

	};


} // namespace BDapi 

#endif 


