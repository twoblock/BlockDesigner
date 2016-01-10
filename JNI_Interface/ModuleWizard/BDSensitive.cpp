/*
 * BDSensitive.cpp
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */

#include "BDSensitive.h"

BDSensitive::BDSensitive() {
	initMembers();
}

BDSensitive::BDSensitive(const char *portName, enum SENSE_TYPE edgeType) {
	initMembers();

	setPortName(portName);
	setSenseType(edgeType);
}

BDSensitive::~BDSensitive() {
	if(pm_portName != NULL)
		free(pm_portName);
}

void BDSensitive::initMembers() {
	pm_portName = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setPortName("BDPort");

	m_senseType = EVAL;
}



enum SENSE_TYPE BDSensitive::getSenseType() {
	return m_senseType;
}

void BDSensitive::setSenseType(enum SENSE_TYPE senseType) {
	m_senseType = senseType;
}

char* BDSensitive::getPortName() const {
	return pm_portName;
}

void BDSensitive::setPortName(const char* portName) {
	memset(pm_portName, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_portName, portName);
}

char* BDSensitive::getMethodNameForSensitive(char* buffer)
{
	if(buffer != NULL)
	{
		switch(m_senseType) {
		case POS:
			strcpy(buffer, ".pos()");
			break;

		case NEG:
			strcpy(buffer, ".neg()");
			break;

		default:
			; //nop
		}
	}

	return buffer;
}
