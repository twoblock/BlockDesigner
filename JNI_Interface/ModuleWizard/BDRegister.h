/*
 * BDRegister.h
 *
 *  Created on: 2015. 11. 16.
 *      Author: Sungkyu Hong
 */



#include "BDConfig.h"


#ifndef SRC_COMP_BDREGISTER_H_
#define SRC_COMP_BDREGISTER_H_


class BDRegister {
public:
	BDRegister();
	BDRegister(const char* name, const char* type, const char* defVal);
	virtual ~BDRegister();


private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(const char* type);
	void setDefaultValue(const char* defVal);
	char* getName() const;
	char* getType() const;
	char* getDefaultValue();


private:
	char *pm_name;
	char *pm_type;
	char *pm_defaultValue;
};


#endif /* SRC_COMP_BDREGISTER_H_ */
