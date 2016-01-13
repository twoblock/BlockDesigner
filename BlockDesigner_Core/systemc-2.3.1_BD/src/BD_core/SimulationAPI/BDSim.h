//-----------------------------------------------------------------------------
// Design								: Block Designer Simulator 
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDSim.h
// Date	       					: 2015/1/3
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Simulator API
// ----------------------------------------------------------------------------

#ifndef BDSIM_H 
#define BDSIM_H 

#include "systemc.h"	
//#include "/home/bryan/workspace/simulationTest/tb.h"	
//Change Manager
#include "BD_core/manager/ExecutionManager.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

using namespace sc_core;

namespace BDapi
{


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
	int Simulate(unsigned int SimControl);
	
	void Run();
	void Step();
	void Stop();

	extern void BD_start();
	
	extern long cycle;
	extern sc_trace_file *wtf;
	//void ExecuteOneCycle();



} // namespace BDapi 

#endif 

