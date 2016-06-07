#include "misc.h"

#define MIN(X, Y)       ((X) > (Y) ? (Y) : (X))
#define MAX(X, Y)       ((X) > (Y) ? (X) : (Y))

#define SETREG(ADDR, VAL) *(volatile unsigned int*)(ADDR) = (unsigned int)(VAL)
#define GETREG(ADDR)    (*(volatile unsigned int*)(ADDR))

#define MU_BASE_ADDR 0x30000000

#define MU_MAX_BYTES  32768  

// ************************************ //
// ***** Memory Utility Command  ****** //
// ************************************ //
#define MU_CMD_SET_REPT_SRAM		0x000
#define MU_CMD_SET_INCR_32_SRAM		0x010
#define MU_CMD_SET_INCR_16_SRAM		0x020
#define MU_CMD_SET_INCR_8_SRAM		0x030

#define MU_CMD_SET_REPT_DRAM		0x040
#define MU_CMD_SET_INCR_32_DRAM		0x050
#define MU_CMD_SET_INCR_16_DRAM		0x060
#define MU_CMD_SET_INCR_8_DRAM		0x070

#define MU_CMD_COPY					0x001

#define MU_CMD_FIND_SRAM			0x002
#define MU_CMD_FIND_DRAM			0x042

#define MU_CMD_SEARCH_MAX_SRAM		0x103
#define MU_CMD_SEARCH_MIN_SRAM		0x083
#define MU_CMD_SEARCH_EQU_SRAM		0x003

#define MU_CMD_SEARCH_MAX_DRAM		0x143
#define MU_CMD_SEARCH_MIN_DRAM		0x0C3
#define MU_CMD_SEARCH_EQU_DRAM		0x043



// ************************************ //
// ***** Memory Utility Register ****** //
// ************************************ //
#define MU_SRC_ADDR 0x30000010
#define MU_DST_ADDR 0x30000014
#define MU_VALUE    0x30000018
#define MU_SIZE     0x3000001c
#define MU_RESULT   0x30000020
#define MU_CMD      0x30000024
#define MU_UNITSTEP 0x30000030

void _mem_set_sram(unsigned int addr, unsigned int const val, unsigned int num_bytes);

int main()
{

  //SETREG(0x30000010 , GETREG(0x30000024));	
  //SETREG(0x30000014 , GETREG(0x30000024));	
  ////_mem_set_sram(0x20011100, 0xffff, 0x40);
  _mem_set_sram(0x20001000, 0xffff, 0x40);
  //_mem_set_sram(0x20009000, 0xaaaa, 0x3c);
  //_mem_set_sram(0x20001000, 0xffff, 0x3c);
  //_mem_set_sram(0x20002000, 0xffff, 0x3c);

  printf("Welcome to TwoBlock Technologies!\n");  
  printf("Happy Engineering with us!\n");  
  return 0;
}

void _mem_set_sram(unsigned int addr, unsigned int const val, unsigned int num_bytes)
{
  unsigned int size;

  //ASSERT((unsigned int)addr % sizeof(unsigned int) == 0); 
  //ASSERT(num_bytes % sizeof(unsigned int) == 0); 
  //ASSERT((unsigned int) addr + num_bytes <= SRAM_SIZE);

  #if DEBUG_MEM_UTIL
  //ASSERT(busy == 0); 
  //busy = 1;
  #endif

  SETREG(MU_VALUE, val);

  do  
  {
    size = MIN(num_bytes, MU_MAX_BYTES);

    SETREG(MU_DST_ADDR, addr);
    SETREG(MU_SIZE, size );
    SETREG(MU_CMD, MU_CMD_SET_REPT_SRAM);

    addr += size;
    num_bytes -= size;

    while (GETREG(MU_RESULT) == 0xFFFFFFFF);
  }
  while (num_bytes != 0); 

  //#if DEBUG_MEM_UTIL
  //busy = 0;
  //#endif
}

