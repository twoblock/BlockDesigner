/*
 * BDPort.cpp
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */

#include "BDPort.h"

BDPort::BDPort() {
	initMembers();
}


/**
 * Constructor of BDPort class
 *
 * 	if you want to use this class as a reserved port(SC_*_RV),
 * 	pass the bit range of the reserved port to dataType as a string.
 * 	ex) BDPort("portName", SC_IN_RV, "16");
 */
BDPort::BDPort(const char* name, enum PORT_TYPE type, const char* dataType) {
	initMembers();

	setName(name);
	setType(type);
	setDataType(dataType);
}

BDPort::~BDPort() {
	if(pm_name != NULL)
		free(pm_name);

	if(pm_dataType != NULL)
		free(pm_dataType);
}

void BDPort::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("BDPort");

	m_type = SC_IN;

	pm_dataType = (char*) malloc(ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	setDataType("int");

}


char* BDPort::getDataType() {
	return pm_dataType;
}

/**
 * 	 if you want to use this class as a reserved port(SC_*_RV),
 * 	pass the bit range of the reserved port to dataType as a string.
 * 	ex) BDPort("portName", SC_IN_RV, "16");
 */
void BDPort::setDataType(const char* dataType) {
	memset(pm_dataType, 0x0, ARR_SIZE(char, MAX_DATATYPE_NAME_SIZE) + 1);
	strcpy(pm_dataType, dataType);
}

enum PORT_TYPE BDPort::getType() {
	return m_type;
}

void BDPort::setType(enum PORT_TYPE type) {
	m_type = type;
}

char* BDPort::getName() {
	return pm_name;
}

void BDPort::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, name);
}

char* BDPort::getTypeText(char* buffer)
{
	if( buffer != NULL)
	{
		switch( m_type ) {
		case SC_IN:
			strcpy(buffer, "sc_in");
			break;

		case SC_OUT:
			strcpy(buffer, "sc_out");
			break;

		case SC_INOUT:
			strcpy(buffer, "sc_inout");
			break;

		case SC_IN_RV:
			strcpy(buffer, "sc_in_rv");
			break;

		case SC_OUT_RV:
			strcpy(buffer, "sc_out_rv");
			break;

		case SC_INOUT_RV:
			strcpy(buffer, "sc_inout_rv");
			break;
		}
	}

	return buffer;
}

