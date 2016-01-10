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

BDRegister::BDRegister(const char* name, const char* type, const char* defVal) {
	initMembers();

	setName(name);
	setType(type);
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

char* BDRegister::getType() const {
	return pm_type;
}

void BDRegister::setType(const char* type) {
	memset(pm_type, 0x0, ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	strcpy(pm_type, type);
}

char* BDRegister::getDefaultValue() {
	return pm_defaultValue;
}
