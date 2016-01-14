#include "Handler_SimulationInitThread.h"

#include "../jdk_h/jni.h"
#include "../jdk_h/jni_md.h"
#include <iostream>
using namespace std;

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Handler_1SimulationInitThread_StartSimulationThreads(JNIEnv *env, jobject ths)
{
	StartSimulationThreads();
}
