//-------------------------------------------------------------
// Design	: Memory_Map
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: memory_map.h
// Date		: 2015. 11. 20
// Reference	: AHBDCD.v (by Changwon Choi)
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: Memory Map of Cortex-M0DS based sub-system
//-------------------------------------------------------------

#ifndef __MEMORY_MAP_H__
#define __MEMORY_MAP_H__

#define S0_BASE_ADDR	0x00000000
#define S1_BASE_ADDR	0x20000000
#define S2_BASE_ADDR	0x25000000
#define S3_BASE_ADDR	0x30000000
#define S4_BASE_ADDR	0x40000000
#define S5_BASE_ADDR	0x50000000
#define S6_BASE_ADDR	0x60000000
#define S7_BASE_ADDR	0x70000000
#define S8_BASE_ADDR	0x80000000
#define S9_BASE_ADDR	0x90000000

#define S0_END_ADDR	0x000FFFFF
#define S1_END_ADDR	0x200FFFFF
#define S2_END_ADDR	0x250FFFFF
#define S3_END_ADDR	0x3FFFFFFF
#define S4_END_ADDR	0x4FFFFFFF
#define S5_END_ADDR	0x5FFFFFFF
#define S6_END_ADDR	0x6FFFFFFF
#define S7_END_ADDR	0x7FFFFFFF
#define S8_END_ADDR	0x8FFFFFFF
#define S9_END_ADDR	0x9FFFFFFF

#define S0_ADDR_SIZE	0x00100000
#define S1_ADDR_SIZE	0x00100000
#define S2_ADDR_SIZE	0x00100000
#define S3_ADDR_SIZE	0x10000000
#define S4_ADDR_SIZE	0x10000000
#define S5_ADDR_SIZE	0x10000000
#define S6_ADDR_SIZE	0x10000000
#define S7_ADDR_SIZE	0x10000000
#define S8_ADDR_SIZE	0x10000000
#define S9_ADDR_SIZE	0x10000000

#endif // __MEMORY_MAP_H__
