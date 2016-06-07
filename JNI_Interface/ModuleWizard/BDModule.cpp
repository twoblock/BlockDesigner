/*
 * BDModule.cpp
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#include "BDModule.h"

BDModule::BDModule() {
	initMembers();
}

BDModule::BDModule(const char* name, const char* type) {
	initMembers();
	setName(name);
	setType(type);
}

BDModule::~BDModule()
{
	if( pm_name != NULL )
		free(pm_name);

	if( pm_type != NULL )
		free(pm_type);

	if( pm_proc != NULL )
		delete pm_proc;


	//just call destructor of BDPortGroup
	//because elements of the BDPortGroup are handled by the BDPortGroup.
	if( pm_ports != NULL )
		delete pm_ports;



	/* following are need handling to release memory to elements of list */
	if( pm_sensitives != NULL ) {
		while( !pm_sensitives->empty() ) {
			BDSensitive *s = pm_sensitives->front();
			pm_sensitives->pop_front();
			delete s;
		}
		delete pm_sensitives;
	}


	if( pm_signals != NULL ) {
		while( !pm_signals->empty() ) {
			BDSignal *sig = pm_signals->front();
			pm_signals->pop_front();

			delete sig;
		}
		delete pm_signals;
	}


	if( pm_registers != NULL ) {
		while( !pm_registers->empty() ) {
			BDRegister *r = pm_registers->front();
			pm_registers->pop_front();
			delete r;
		}
		delete pm_registers;
	}


	if( pm_params != NULL ) {
		while( !pm_params->empty() ) {
			BDParameter *p = pm_params->front();
			pm_params->pop_front();
			delete p;
		}
		delete pm_params;
	}

}

void BDModule::initMembers() {
	pm_name = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	pm_type = (char*) malloc(ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	setName("BDModule");

	pm_proc = NULL;
	pm_ports = NULL;
	pm_signals = NULL;
	pm_sensitives = NULL;
	pm_registers = NULL;
	pm_params = NULL;
}



/**
 * method
 */
void BDModule::setName(const char* name) {
	memset(pm_name, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_name, name);
}

void BDModule::setType(const char* type) {
	memset(pm_type, 0x0, ARR_SIZE(char, MAX_NAME_SIZE) + 1);
	strcpy(pm_type, type);
}

void BDModule::setProc(const char* procName, const char* procType) {
	if(pm_proc != NULL) {
		delete pm_proc;
	}

	pm_proc = new BDProcess(procName, procType);
}

const char* BDModule::getName() {
	return pm_name;
}

const char* BDModule::getType() const {
	return pm_type;
}

BDProcess* BDModule::getProcess() {
	if(pm_proc == NULL) {
		pm_proc = new BDProcess();
	}

	return pm_proc;
}

BDPortGroup*& BDModule::getPorts() {
	return pm_ports;
}






int BDModule::addPort(const char* portName, const char* portType, const char* dataType) {
	if(pm_ports == NULL) {
		pm_ports = new BDPortGroup();
	}

	return pm_ports->addPort(portName, portType, dataType);
}


std::list<BDRegister*>*& BDModule::getRegisters() {
	return pm_registers;
}

std::list<BDSensitive*>*& BDModule::getSensitives() {
	return pm_sensitives;
}

std::list<BDParameter*>*& BDModule::getParams() {
	return pm_params;
}

int BDModule::addRegister(const char* regName, const char* dataType, int dataSize, const char* defVal)
{
	if(pm_registers == NULL) {
		pm_registers = new std::list<BDRegister*>();
	}

	BDRegister *reg = new BDRegister(regName, dataType, dataSize, defVal);
	pm_registers->push_back(reg);

	return pm_registers->size();
}

std::list<BDSignal*>*& BDModule::getSignals() {
	return pm_signals;
}



int BDModule::addSignal(const char* sigName, enum SIGNAL_TYPE sigType, const char* dataType)
{
	if( pm_signals == NULL ) {
		pm_signals = new std::list<BDSignal*>();
	}

	BDSignal *sig = new BDSignal(sigName, sigType, dataType);
	pm_signals->push_back(sig);

	return pm_signals->size();
}



int BDModule::addParameter(const char* paramName, const char* dataType, int dataSize, const char* defVal)
{
	if(pm_params == NULL) {
		pm_params = new std::list<BDParameter*>();
	}

	BDParameter *param = new BDParameter(paramName, dataType, dataSize, defVal);
	pm_params->push_back(param);

	return pm_params->size();
}

int BDModule::addSensitivity(const char* portName, const char* senseType)
{
	if(pm_sensitives == NULL) {
		pm_sensitives = new std::list<BDSensitive*>();
	}

	if(strcmp(senseType, "None") != 0) {
		BDSensitive *sens = new BDSensitive(portName, senseType);
		pm_sensitives->push_back(sens);
	}

	return pm_sensitives->size();
}
