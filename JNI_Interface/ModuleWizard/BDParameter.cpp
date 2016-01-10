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

BDParameter::BDParameter(const char* name, const char* type, const char* defVal) {
	initMembers();

	setName(name);
	setType(type);
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

char* BDParameter::getType() const {
	return pm_type;
}

void BDParameter::setType(const char* type) {
	memset(pm_type, 0x0, ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	strcpy(pm_type, type);
}

void BDParameter::setDefaultValue(const char* defVal) {
	memset(pm_defaultValue, 0x0, ARR_SIZE(char, MAX_VALUE_SIZE) + 1);
	strcpy(pm_defaultValue, defVal);
}

char* BDParameter::getDefaultValue() const {
	return pm_defaultValue;
}
