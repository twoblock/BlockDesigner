/*
 * BDPortGroup.cpp
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */

#include "BDPortGroup.h"

BDPortGroup::BDPortGroup() {
	initMembers();
}

BDPortGroup::BDPortGroup(const char* name) {
	initMembers();

	setName(name);
}

BDPortGroup::~BDPortGroup() {
	if(pm_name != NULL)
		free(pm_name);

	while( !empty() ) {
		BDPort *p = front();
		pop_front();
		delete p;
	}
}

void BDPortGroup::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("BDPortGroup");
}



/**
 * method
 */
char* BDPortGroup::getName() {
	return pm_name;
}

void BDPortGroup::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, name);
}



/**
 * 	 if you want to use this class as a reserved port(SC_*_RV),
 * 	pass the bit range of the reserved port to dataType as a string.
 * 	ex) addPort("portName", SC_IN_RV, "16");
 */
int BDPortGroup::addPort(const char* portName, const char* portType, const char* dataType)
{
	BDPort *port = new BDPort(portName, portType, dataType);
	push_back(port);
	return size();
}
