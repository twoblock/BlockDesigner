/*
 * MemoryArray.h
 *
 *  Created on: Mar 12, 2015
 *      Author: ryan
 */

#ifndef MEMORYARRAY_H_
#define MEMORYARRAY_H_

#include<string.h>

class MemoryArray {
	public:
		MemoryArray();
		virtual ~MemoryArray();

		void init(int bytesPerPage, int sectorsPerPage, int pagesPerBlock);
		char* write(int addr, char *buffer, int bufferSize);
		char* read(int addr, char *buffer, int bufferSize);
		void erase(int addr);


	private:
		char* allocateRow(int addr);
		void releaseAllRows();
		bool isLPNPage(int addr);


		char **m_array;
		int m_pagesPerBlock;
		int m_sectorsPerPage;
		int m_bytesPerPage;
};

#endif /* MEMORYARRAY_H_ */
