/*
 * BDSignal.cpp
 *
 *  Created on: 2015. 11. 16.
 *      Author: Sungkyu Hong
 */

#include "BDSignal.h"

BDSignal::BDSignal() {
	initMembers();
}


/**
 * Constructor of BDPort class
 *
 * 	if you want to use this class as a reserved port(SC_*_RV),
 * 	pass the bit range of the reserved port to dataType as a string.
 * 	ex) BDPort("portName", SC_IN_RV, "16");
 */
BDSignal::BDSignal(const char* name, enum SIGNAL_TYPE type, const char* dataType) {
	initMembers();

	setName(name);
	setType(type);
	setDataType(dataType);
}

BDSignal::~BDSignal() {
	if(pm_name != NULL)
		free(pm_name);

	if(pm_dataType != NULL)
		free(pm_dataType);
}

void BDSignal::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("BDSignal");

	m_type = SC_SIGNAL;

	pm_dataType = (char*) malloc(ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	setDataType("int");
}




char* BDSignal::getDataType() {
	return pm_dataType;
}

void BDSignal::setDataType(const char* dataType) {
	memset(pm_dataType, 0x0, ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	strcpy(pm_dataType, dataType);
}

enum SIGNAL_TYPE BDSignal::getType() {
	return m_type;
}

void BDSignal::setType(enum SIGNAL_TYPE type) {
	m_type = type;
}

char* BDSignal::getName() {
	return pm_name;
}

void BDSignal::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, name);
}


char* BDSignal::getTypeText(char* buffer)
{
	if( buffer != NULL)
	{
		switch( m_type ) {
		case SC_SIGNAL:
			strcpy(buffer, "sc_signal");
			break;

		case SC_SIGNAL_RV:
			strcpy(buffer, "sc_signal_rv");
			break;
		}
	}

	return buffer;
}
