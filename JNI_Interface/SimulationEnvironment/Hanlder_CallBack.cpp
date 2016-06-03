#include "Hanlder_CallBack.h"
#include "../../BlockDesigner_Core/systemc-2.3.1_BD/src/BD_core/manager/CallBackManager.h"	
#include <stddef.h>
#include <iostream>

using namespace std;
using namespace BDapi;

long pub_long_cycle;
int pub_int_status;
int pub_int_error;

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_CycleListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "CycleCallBack", "(J)V");
	if (mid == NULL) {
		return; /*method not found*/
	}
	pub_long_cycle = 1000;
	env->CallVoidMethod(ths, mid, BDapi::glw_Cycle );
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_StatusListener(JNIEnv *env, jobject ths)
{
	// excepting handling
	// if simulation don't start, nothing was written to named pipe(wave.vcd)
	// so related processed(gtkwave, shmidcat) can't be removed
	if(glw_Cycle == 0){
		// write some value to named pipe(wave.vcd) 
		// to remove gtkwave, shmidcat processes
		popen("echo 1 > wave.vcd", "r");
	}
	popen("rm -rf wave.vcd", "r");
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_OutputListener(JNIEnv *env, jobject ths)
{
	CallBackManager *p_CallBackManager = NULL;
	p_CallBackManager = CallBackManager::GetInstance();	
	p_CallBackManager->SetObject(env->NewGlobalRef(ths));
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_ResultListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "ResultCallBack", "()V");
	if (mid == NULL) {
		return; /*method not found*/
	}
	env->CallVoidMethod(ths, mid);
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_MemoryViewListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "MemoryViewCallBack", "()V");
	if (mid == NULL) {
		return; /*method not found*/
	}
	env->CallVoidMethod(ths, mid);
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_ModuleInfoListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "ModuleInfoCallBack", "()V");
	if (mid == NULL) {
		return; /*method not found*/
	}
	env->CallVoidMethod(ths, mid);
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_ErrorListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "ErrorCallBack", "(I)V");
	if (mid == NULL) {
		return; /*method not found*/
	}
	pub_int_error=1;
	env->CallVoidMethod(ths, mid, pub_int_error);
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {

	CallBackManager *p_CallBackManager = NULL;
	p_CallBackManager = CallBackManager::GetInstance();	
	p_CallBackManager->SetJVM(vm);
	//p_CallBackManager->SetEnv();

	return JNI_VERSION_1_6;
}
