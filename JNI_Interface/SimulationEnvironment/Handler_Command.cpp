#include "Handler_Command.h"

#include <stddef.h>
#include <iostream>

using namespace std;


JNIEXPORT void JNICALL Java_com_twoblock_blockdesigner_command_Handler_1Command_PushCommand(JNIEnv *env, jobject ths)
{
	jclass cls = env->GetObjectClass(ths);

	jfieldID OperID 		= env->GetFieldID(cls,"Operation", "I");
	jfieldID CmdID 		= env->GetFieldID(cls,"Command", "I");
	jfieldID Argu1ID 		= env->GetFieldID(cls,"Argu1", "Ljava/lang/String;");
	jfieldID Argu2ID 		= env->GetFieldID(cls,"Argu2", "Ljava/lang/String;");
	jfieldID Argu3ID 		= env->GetFieldID(cls,"Argu3", "Ljava/lang/String;");
	jfieldID Argu4ID 		= env->GetFieldID(cls,"Argu4", "Ljava/lang/String;");
	jfieldID Argu5ID 		= env->GetFieldID(cls,"Argu5", "Ljava/lang/String;");

	jint OperInt 			= env->GetIntField(ths, OperID);
	jint CmdInt 			= env->GetIntField(ths, CmdID);

	jstring Argu1Str 		= (jstring) env->GetObjectField(ths,Argu1ID);
	jstring Argu2Str 		= (jstring) env->GetObjectField(ths,Argu2ID);
	jstring Argu3Str 		= (jstring) env->GetObjectField(ths,Argu3ID);
	jstring Argu4Str 		= (jstring) env->GetObjectField(ths,Argu4ID);
	jstring Argu5Str 		= (jstring) env->GetObjectField(ths,Argu5ID);

	const char *c_Argu1 = env->GetStringUTFChars(Argu1Str, NULL);
	const char *c_Argu2 = env->GetStringUTFChars(Argu2Str, NULL);
	const char *c_Argu3 = env->GetStringUTFChars(Argu3Str, NULL);
	const char *c_Argu4 = env->GetStringUTFChars(Argu4Str, NULL);
	const char *c_Argu5 = env->GetStringUTFChars(Argu5Str, NULL);
	
//	GUI_COMMAND GUI_commnad;
//
//	GUI_commnad.Operation = OperInt;
//	GUI_commnad.Command   = CmdInt;
//	strcpy( GUI_commnad.Argu1, c_Argu1 );
//	strcpy( GUI_commnad.Argu2, c_Argu2 );
//	strcpy( GUI_commnad.Argu3, c_Argu3 );
//	strcpy( GUI_commnad.Argu4, c_Argu4 );
//	strcpy( GUI_commnad.Argu5, c_Argu5 );
//
//	CommandQueue::PushCommand( GUI_commnad );
	cout<< OperInt <<"/"<< CmdInt <<"/"<< c_Argu1 <<"/"<< c_Argu2 <<"/"<< c_Argu3 <<"/"<< c_Argu4 <<"/"<< c_Argu5 << endl;

	env->ReleaseStringUTFChars(Argu1Str,c_Argu1);
	env->ReleaseStringUTFChars(Argu2Str,c_Argu2);
	env->ReleaseStringUTFChars(Argu3Str,c_Argu3);
	env->ReleaseStringUTFChars(Argu4Str,c_Argu4);
	env->ReleaseStringUTFChars(Argu5Str,c_Argu5);
}
