#include "Handler_SimulationInitThread.h"

#include <jni.h>
#include <jni_md.h>
#include <iostream>
using namespace std;


JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Handler_1SimulationInitThread_StartSimulationThreads(JNIEnv *env, jobject ths)
{
	cout<<"In C"<<endl;
}
