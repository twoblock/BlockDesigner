/*
 * BDConfig.h
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */

#ifndef BDCONFIG_H_
#define BDCONFIG_H_




/**
 * Header file
 */
#include <list>
#include <cstring>
#include <fstream>
#include <cctype>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
using namespace std;



/**
 * Constants
 */
#define MAX_NAME_SIZE 64
#define MAX_DATATYPE_NAME_SIZE 64
#define MAX_PATH_SIZE 256
#define MAX_VALUE_SIZE 8


#define FUNC_NAME_BD_INIT "BDInit"





/**
 * Macro
 */
#define T1 ("\t")
#define T2 ("\t\t")
#define L(str) {printf("%s::%d::%s\n", __FILE__, __LINE__, str);}
#define ARR_SIZE(type, size) ((sizeof(type)) * (size))



namespace blockdesigner {}
using namespace blockdesigner;


#endif /* BDCONFIG_H_ */
