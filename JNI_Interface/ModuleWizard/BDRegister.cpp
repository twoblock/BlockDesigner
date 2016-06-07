/*
 * BDRegister.cpp
 *
 *  Created on: 2015. 11. 16.
 *      Author: Sungkyu Hong
 */

#include "BDRegister.h"


BDRegister::BDRegister() {
	initMembers();
}

BDRegister::BDRegister(const char* name, const char* type, int dataSize, const char* defVal) {
	initMembers();

	setName(name);
	setType(type);
	setDataSize(dataSize);
	setDefaultValue(defVal);
}

BDRegister::~BDRegister() {
	if(pm_name != NULL)
		free(pm_name);

	if(pm_type != NULL)
		free(pm_type);

	if(pm_defaultValue != NULL)
		free(pm_defaultValue);
}

void BDRegister::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("BDRegister");

	pm_type = (char*) malloc(ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	setType("int");

	pm_defaultValue = (char*) malloc(ARR_SIZE(char, MAX_VALUE_SIZE) + 1);
	setDefaultValue("0");
}



char* BDRegister::getName() const {
	return pm_name;
}

void BDRegister::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, "r_");
	strcat(pm_name, name);
}

void BDRegister::setDefaultValue(const char* defVal) {
	memset(pm_defaultValue, 0x0, ARR_SIZE(char, MAX_VALUE_SIZE) + 1);
	strcpy(pm_defaultValue, defVal);
}

char* BDRegister::getDataType() const {

	if(strcmp(pm_type, "HEX")==0)
		return "unsigned int";

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

	return "unknown";
}

void BDRegister::setType(const char* type) {
	memset(pm_type, 0x0, ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	strcpy(pm_type, type);
}

char* BDRegister::getType() const {
	return pm_type;
}

char* BDRegister::getDefaultValue() {
	return pm_defaultValue;
}


int BDRegister::getDataSize() const {
	return pm_dataSize;
}

void BDRegister::setDataSize(int DataSize) {
	pm_dataSize = DataSize;
}
