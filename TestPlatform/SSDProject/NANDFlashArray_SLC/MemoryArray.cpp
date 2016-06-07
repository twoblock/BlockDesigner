/*
 * MemoryArray.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: ryan
 */

#include "MemoryArray.h"
#include <memory>

MemoryArray::MemoryArray() : m_array(NULL), m_pagesPerBlock(0), m_sectorsPerPage(0), m_bytesPerPage(0)
{
	;
}

MemoryArray::~MemoryArray()
{
	releaseAllRows();
}



void MemoryArray::init(int pagesPerBlock, int sectorsPerPage, int bytesPerPage)
{
	if(m_array != NULL) {
		releaseAllRows();
	}

	m_pagesPerBlock = pagesPerBlock;
	m_sectorsPerPage = sectorsPerPage;
	m_bytesPerPage = bytesPerPage;

	m_array = new char*[m_pagesPerBlock];
	for(int i=0; i<m_pagesPerBlock; i++) {
		m_array[i] = NULL;
	}
}


char* MemoryArray::allocateRow(int addr)
{
	if(m_array == NULL) {
		return NULL;
	}

	if(addr >= m_pagesPerBlock) {
		return NULL;
	}

	if(m_array[addr] == NULL)
	{
		//if the row is last page of this block as lpn list block, it needs all bytes for block.
		//else it needs some bytes to cover sectors in a page.
		int size = 0;
		if(isLPNPage(addr)) {
			size = m_bytesPerPage;
		}
		else {
			size = m_sectorsPerPage * sizeof(int);
		}


		m_array[addr] = new char[size];
		memset(m_array[addr], 0xFF, size);
	}

	return m_array[addr];
}

void MemoryArray::releaseAllRows()
{
	if(m_array != NULL) {
		for(int i=0; i<m_pagesPerBlock; i++)
		{
			if(m_array[i] != NULL)
				delete[] m_array[i];
		}

		delete[] m_array;
	}
}



char* MemoryArray::write(int addr, char *buffer, int bufferSize)
{
	if(m_array == NULL) {
		return NULL;
	}

	if(addr >= m_pagesPerBlock) {
		return NULL;
	}

	if(m_array[addr] == NULL) {
		allocateRow(addr);
	}



	if(isLPNPage(addr)) {
		memcpy(m_array[addr], buffer, m_bytesPerPage < bufferSize ? m_bytesPerPage : bufferSize);
	}
	else
	{
		for(int i=0; i<m_sectorsPerPage; i++)
		{
			int offset = i * (m_bytesPerPage/m_sectorsPerPage);
			*(m_array[addr]+i) = buffer[offset];
		}
	}

	return m_array[addr];
}



char* MemoryArray::read(int addr, char *buffer, int bufferSize)
{
	if(m_array == NULL) {
		return NULL;
	}

	if(addr >= m_pagesPerBlock) {
		return NULL;
	}

	if(m_array[addr] == NULL) {
		allocateRow(addr);
	}



	if(isLPNPage(addr)) {
		memcpy(buffer, m_array[addr], m_bytesPerPage < bufferSize ? m_bytesPerPage : bufferSize);
	}
	else
	{
		for(int i=0; i<m_sectorsPerPage; i++)
		{
			int offset = i * (m_bytesPerPage/m_sectorsPerPage);
			memset(buffer+offset, *(m_array[addr]+i), m_bytesPerPage/m_sectorsPerPage);
		}
	}


	return m_array[addr];
}

void MemoryArray::erase(int addr)
{
	if(addr >= m_pagesPerBlock) {
		return;
	}

	if(m_array[addr] != NULL)
	{
		int size = 0;
		if(isLPNPage(addr)) {
			size = m_bytesPerPage;
		}
		else {
			size = m_sectorsPerPage * sizeof(int);
		}

		memset(m_array[addr], 0x0, size);
	}
}


bool MemoryArray::isLPNPage(int addr)
{
	return addr == m_pagesPerBlock-1;
}
