#include "swt_dnd_about_Twoblock.h"

#include <jni.h>
#include <jni_md.h>
#include <string.h>
using namespace std;

/* Header for class swt_dnd_about_Twoblock */

struct User {
	long iSerial;
	char caName[32];
	int iAge;
};

JNIEXPORT jint JNICALL _Java_swt_1dnd_about_1Twoblock_add(JNIEnv * _env,
		jclass _clazz, jobject _object) {
	jclass clazz;
	clazz = _env - &gt;
	GetObjectClass(_object);

	jfieldID fid;
	jstring jstr;

	User user;
	fid = _env - &gt;
	GetFieldID(clazz, "serial", "J");
	user.iSerial = _env - &gt;
	GetLongField(_object, fid);
	// L이 아니라 J임에 주의하자

	fid = _env - &gt;
	GetFieldID(clazz, "name", "Ljava/lang/String;");
	jstr = (jstring) _env - &gt;
	GetObjectField(_object, fid);
	const char * pcName = _env - &gt;
	GetStringUTFChars(jstr, NULL);
	strcpy(user.caName, pcName);
	_env - &gt;
	ReleaseStringUTFChars(jstr, pcName);
	// ReleaseStringUTFChars 반드시 해준다.

	fid = _env - &gt;
	GetFieldID(clazz, "age", "I");
	user.iAge = _env - &gt;
	GetIntField(_object, fid);

	return 1;
}
