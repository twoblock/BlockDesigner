/*
 * BDProcess.cpp
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */

#include "BDProcess.h"

BDProcess::BDProcess() {
	initMembers();
}

BDProcess::BDProcess(const char* name, enum PROC_TYPE type) {
	initMembers();

	setName(name);
	setType(type);
}

BDProcess::~BDProcess() {
	if(pm_name != NULL)
		free(pm_name);
}

void BDProcess::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("do_bdproc");

	m_type = METHOD;
}





enum PROC_TYPE BDProcess::getType() {
	return m_type;
}

void BDProcess::setType(enum PROC_TYPE type) {
	m_type = type;
}

char* BDProcess::getName() {
	return pm_name;
}

void BDProcess::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, name);
}
