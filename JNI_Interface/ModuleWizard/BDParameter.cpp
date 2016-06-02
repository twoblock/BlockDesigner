/*
 * BDParameter.cpp
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#include "BDParameter.h"

BDParameter::BDParameter() {
	initMembers();
}

BDParameter::BDParameter(const char* name, const char* type, int dataSize, const char* defVal) {
	initMembers();

	setName(name);
	setType(type);
	setDataSize(dataSize);
	setDefaultValue(defVal);
}

BDParameter::~BDParameter() {
	if(pm_name != NULL)
		free(pm_name);

	if(pm_type != NULL)
		free(pm_type);

	if(pm_defaultValue != NULL)
		free(pm_defaultValue);
}

void BDParameter::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("BDParameter");

	pm_type = (char*) malloc(ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	setType("int");

	pm_defaultValue = (char*) malloc(ARR_SIZE(char, MAX_VALUE_SIZE) + 1);
	setDefaultValue("0");
}



char* BDParameter::getName() const {
	return pm_name;
}

void BDParameter::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, "p_");
	strcat(pm_name, name);
}

char* BDParameter::getDataType() const {

	if(strcmp(pm_type, "UINT")==0 && pm_dataSize==8)
		return "unsigned char";

	if(strcmp(pm_type, "UINT")==0 && pm_dataSize==16)
		return "unsigned short";

	if(strcmp(pm_type, "UINT")==0 && pm_dataSize==32)
		return "unsigned int";

	if(strcmp(pm_type, "UINT")==0 && pm_dataSize==64)
		return "unsigned long long";

	if(strcmp(pm_type, "BOOL")==0)
		return "bool";

	if(strcmp(pm_type, "FLOAT")==0 && pm_dataSize==32)
		return "float";

	if(strcmp(pm_type, "FLOAT")==0 && pm_dataSize==64)
		return "double";

	if(strcmp(pm_type, "INT")==0 && pm_dataSize==8)
		return "char";

	if(strcmp(pm_type, "INT")==0 && pm_dataSize==16)
		return "short";

	if(strcmp(pm_type, "INT")==0 && pm_dataSize==32)
		return "int";

	if(strcmp(pm_type, "INT")==0 && pm_dataSize==64)
		return "long long";

	return "unknown";
}

void BDParameter::setType(const char* type) {
	memset(pm_type, 0x0, ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	strcpy(pm_type, type);
}

void BDParameter::setDefaultValue(const char* defVal) {
	memset(pm_defaultValue, 0x0, ARR_SIZE(char, MAX_VALUE_SIZE) + 1);
	strcpy(pm_defaultValue, defVal);
}

char* BDParameter::getType() const {
	return pm_type;
}

char* BDParameter::getDefaultValue() const {
	return pm_defaultValue;
}

int BDParameter::getDataSize() const {
	return pm_dataSize;
}

void BDParameter::setDataSize(int dataSize) {
	pm_dataSize = dataSize;
}
