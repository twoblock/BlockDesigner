
#pragma once

#include "misc.h"

#ifdef CORTEXM0DS

//#define CLOCKS_FREQUENCY 1000000  //1MHz
//#define CLOCK_PERIOD 0.000001 //1us clock frequency is assumed to 1MHz
//#define CLOCK_PERIOD_SHIFT 20//1MHz = 10^6 = 2^20

// Disable the inclusion of semihosting support
#pragma import(__use_no_semihosting)
// Define the location of the output console in the DesignStart testbench.
volatile unsigned char *console   = (volatile unsigned char *) 0x25000000U;
//volatile unsigned int  *exit_req  = (volatile unsigned int  *) 0x40000004U;

//Timer0 registers
//typedef struct{
	//volatile unsigned int load;       //Timer 0 load value register
	//volatile unsigned int current;    //Timer 0 current value register
	//volatile unsigned int cnt_en;     //Timer 0 count enable register
	//volatile unsigned int interrupt;  //Timer 0 interrupt register
	//volatile unsigned int int_clear;  //Timer 0 interrupt clear register
//}TIMER0_TYPE;
//#define TIMER0_BASE  0x40004000U
//#define TIMER0       ((TIMER0_TYPE *) TIMER0_BASE)

//static volatile unsigned int timer0_overflows=0;

//Timer0 related functions
//extern __irq void IRQ00_Handler(void);
//static void timer0_reset_cycle_count(void);
//static void timer0_start_cycle_count(void);
//static unsigned int timer0_get_cycle_count(void);
//extern void timer0_clock_init(void);
//extern clock_t clock(void);
//extern time_t time(time_t * t);

struct __FILE{int handle;};
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE *f);   
int ferror(FILE *f);
int fgetc(FILE *f);           
int __backspace(FILE *stream);
void _ttywrch(int ch);
void _sys_exit(void);

#endif //CORTEXM0DS

