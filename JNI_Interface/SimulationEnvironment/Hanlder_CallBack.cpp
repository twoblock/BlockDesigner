#include "Hanlder_CallBack.h"

#include <jni.h>
#include <jni_md.h>
#include <stddef.h>
#include <iostream>
using namespace std;

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
	env->CallVoidMethod(ths, mid, pub_long_cycle);
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_StatusListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "StatusCallBack", "(I)V");
	if (mid == NULL) {
		return; /*method not found*/
	}
	pub_int_status = 1;
	env->CallVoidMethod(ths, mid, pub_int_status);
}

JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Hanlder_1CallBack_OutputListener(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);
	jmethodID mid = env->GetMethodID(cls, "OutputCallBack", "()V");
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
