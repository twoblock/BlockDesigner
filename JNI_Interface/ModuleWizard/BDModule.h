/*
 * BDModule.h
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */


#include "BDConfig.h"
#include "BDProcess.h"
#include "BDPortGroup.h"
#include "BDSignal.h"
#include "BDRegister.h"
#include "BDParameter.h"


#ifndef BDMODULE_H_
#define BDMODULE_H_

class BDModule {

public:
	BDModule();
	BDModule(const char* name, const char* type);
	virtual ~BDModule();


private:
	void initMembers();


public:
	void setName(const char *name);
	void setType(const char* type);
	void setProc(const char *procName, const char* procType);

	const char* getName();
	const char* getType() const;
	BDProcess* getProcess();
	std::list<BDSensitive*>*& getSensitives();
	BDPortGroup*& getPorts();
	std::list<BDSignal*>*& getSignals();
	std::list<BDRegister*>*& getRegisters();
	std::list<BDParameter*>*& getParams();

	int addPort(const char* portName, const char* portType, const char* dataType);
	int addSignal(const char* sigName, enum SIGNAL_TYPE sigType, const char* dataType);
	int addRegister(const char* regName, const char* dataType, int dataSize, const char* defVal);
	int addParameter(const char* paramName, const char* dataType, int dataSize, const char* defVal);
	int addSensitivity(const char* portName, const char* senseType);





private:
	char *pm_name;
	char *pm_type;
	BDProcess *pm_proc;
	std::list<BDSensitive*> *pm_sensitives;
	BDPortGroup *pm_ports;
	std::list<BDSignal*> *pm_signals;
	std::list<BDRegister*> *pm_registers;
	std::list<BDParameter*> *pm_params;


};



#endif /* BDMODULE_H_ */
