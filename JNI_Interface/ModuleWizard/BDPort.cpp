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
BDPort::BDPort(const char* name, const char* type, const char* dataType) {
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

void BDPort::setType(const char* strType)
{
	if(strcmp(strType, STR_SC_IN) == 0)
		m_type = SC_IN;

	if(strcmp(strType, STR_SC_OUT) == 0)
		m_type = SC_OUT;

	if(strcmp(strType, STR_SC_INOUT) == 0)
		m_type = SC_INOUT;

	if(strcmp(strType, STR_SC_IN_RV) == 0)
		m_type = SC_IN_RV;

	if(strcmp(strType, STR_SC_OUT_RV) == 0)
		m_type = SC_OUT_RV;

	if(strcmp(strType, STR_SC_INOUT_RV) == 0)
		m_type = SC_INOUT_RV;

	if(strcmp(strType, STR_AHB_MM) == 0)
		m_type = AHB_MM;

	if(strcmp(strType, STR_AHB_MS) == 0)
		m_type = AHB_MS;

	if(strcmp(strType, STR_AHB_SM) == 0)
		m_type = AHB_SM;

	if(strcmp(strType, STR_AHB_SS) == 0)
		m_type = AHB_SS;

	if(strcmp(strType, STR_AHB_LITE_MM) == 0)
		m_type = AHB_LITE_MM;

	if(strcmp(strType, STR_AHB_LITE_MS) == 0)
		m_type = AHB_LITE_MS;

	if(strcmp(strType, STR_AHB_LITE_SM) == 0)
		m_type = AHB_LITE_SM;

	if(strcmp(strType, STR_AHB_LITE_SS) == 0)
		m_type = AHB_LITE_SS;
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
			strcpy(buffer, STR_SC_IN);
			break;

		case SC_OUT:
			strcpy(buffer, STR_SC_OUT);
			break;

		case SC_INOUT:
			strcpy(buffer, STR_SC_INOUT);
			break;

		case SC_IN_RV:
			strcpy(buffer, STR_SC_IN_RV);
			break;

		case SC_OUT_RV:
			strcpy(buffer, STR_SC_OUT_RV);
			break;

		case SC_INOUT_RV:
			strcpy(buffer, STR_SC_INOUT_RV);
			break;

		case AHB_MM:
			strcpy(buffer, STR_AHB_MM);
			break;

		case AHB_MS:
			strcpy(buffer, STR_AHB_MS);
			break;

		case AHB_SM:
			strcpy(buffer, STR_AHB_SM);
			break;

		case AHB_SS:
			strcpy(buffer, STR_AHB_SS);
			break;

		case AHB_LITE_MM:
			strcpy(buffer, STR_AHB_LITE_MM);
			break;

		case AHB_LITE_MS:
			strcpy(buffer, STR_AHB_LITE_MS);
			break;

		case AHB_LITE_SM:
			strcpy(buffer, STR_AHB_LITE_SM);
			break;

		case AHB_LITE_SS:
			strcpy(buffer, STR_AHB_LITE_SS);
			break;
		}
	}

	return buffer;
}

