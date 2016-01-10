/*
 * BDParameter.h
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#include "BDConfig.h"


#ifndef BDPARAMETER_H_
#define BDPARAMETER_H_


class BDParameter {

public:
	BDParameter();
	BDParameter(const char* name, const char* type, const char* defVal);
	virtual ~BDParameter();


private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(const char* type);
	void setDefaultValue(const char* defVal);
	char* getName() const;
	char* getType() const;
	char* getDefaultValue() const;


private:
	char *pm_name;
	char *pm_type;
	char *pm_defaultValue;

};

#endif /* BDPARAMETER_H_ */
