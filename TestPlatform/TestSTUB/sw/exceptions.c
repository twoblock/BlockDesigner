//************************************************************************
//exceptions.c
//************************************************************************

#include "stack.h"
//************************************************************************
// Function definitions
//************************************************************************

// The following functions are declared with weak attributes.
// If another handler with the same name is presented it will be overriden.
__irq void NMI_Handler(void)           {while(1);}
__irq void HardFault_Handler(void)     {while(1);}
__irq void SVC_Handler(void)           {while(1);}
__irq void PendSV_Handler(void)        {while(1);}
#ifndef CORTEXM0DS
  //24-bit system timer (SysTick) is not implemented in Cortex-M0 DesignStart processor
  __irq void SysTick_Handler(void)     {while(1);}
#endif //CORTEXM0DS
//extern __irq void IRQ00_Handler(void);
__irq void IRQ00_Handler(void)		{while(1);}
//__irq void IRQ00_Handler(void)         {while(1);}
__irq void IRQ01_Handler(void)         {while(1);}
__irq void IRQ02_Handler(void)		   {while(1);}
__irq void IRQ03_Handler(void)		   {while(1);}
__irq void IRQ04_Handler(void)		   {while(1);}
__irq void IRQ05_Handler(void)		   {while(1);}
__irq void IRQ06_Handler(void)		   {while(1);}
__irq void IRQ07_Handler(void)		   {while(1);}
__irq void IRQ08_Handler(void)		   {while(1);}
__irq void IRQ09_Handler(void)		   {while(1);}
__irq void IRQ10_Handler(void)		   {while(1);}
__irq void IRQ11_Handler(void)		   {while(1);}
__irq void IRQ12_Handler(void)		   {while(1);}
__irq void IRQ13_Handler(void)		   {while(1);}
__irq void IRQ14_Handler(void)		   {while(1);}
__irq void IRQ15_Handler(void)		   {while(1);}
#ifndef CORTEXM0DS
  //Cortex-M0 DesignStart processor support 16 interrupt inputs only
  __irq void IRQ16_Handler(void)       {while(1);} 
  __irq void IRQ17_Handler(void)	   {while(1);} 
  __irq void IRQ18_Handler(void)	   {while(1);} 
  __irq void IRQ19_Handler(void)	   {while(1);} 
  __irq void IRQ20_Handler(void)	   {while(1);} 
  __irq void IRQ21_Handler(void)	   {while(1);} 
  __irq void IRQ22_Handler(void)	   {while(1);} 
  __irq void IRQ23_Handler(void)	   {while(1);} 
  __irq void IRQ24_Handler(void)	   {while(1);} 
  __irq void IRQ25_Handler(void)	   {while(1);} 
  __irq void IRQ26_Handler(void)	   {while(1);} 
  __irq void IRQ27_Handler(void)	   {while(1);} 
  __irq void IRQ28_Handler(void)	   {while(1);} 
  __irq void IRQ29_Handler(void)	   {while(1);} 
  __irq void IRQ30_Handler(void)	   {while(1);} 
  __irq void IRQ31_Handler(void)	   {while(1);} 
#endif //CORTEXM0DS


//************************************************************************
// Linker-generated Stack Base addresses, two region and one region
//************************************************************************
extern unsigned int Image$$ARM_LIB_STACK$$ZI$$Limit;
extern unsigned int Image$$ARM_LIB_STACKHEAP$$ZI$$Limit;
typedef void (* const ExecFuncPtr) (void) __irq;
extern int __main(void);


//************************************************************************
// Vector table
//************************************************************************

#pragma arm section rodata="exception_area"

ExecFuncPtr exception_table[] = {  
  (ExecFuncPtr) &Image$$ARM_LIB_STACK$$ZI$$Limit,
    /* Initial Main Stack Pointer */
  (ExecFuncPtr) &__main,
    /* Initial PC, set to entry point. Branch to __main */
  NMI_Handler, /* Non-maskable Interrupt handler */
  HardFault_Handler, /* Hard fault handler */
  0, 0, 0, 0, 0, 0, 0, /* Reserved */
  SVC_Handler, /* SVC handler */
  0, 0, /* Reserved */
  PendSV_Handler, /* PendSV handler */
  #ifdef CORTEXM0DS
    0, /* SysTick Handler - Not implemented in Cortex-0 DesignStart processor */
  #else
	SysTick_Handler, /* SysTick Handler */
  #endif //CORTEXM0DS    
  0, 
  /* Device specific configurable interrupts start here */
  IRQ00_Handler,
  IRQ01_Handler,
  IRQ02_Handler,
  IRQ03_Handler,
  IRQ04_Handler,
  IRQ05_Handler,
  IRQ06_Handler,
  IRQ07_Handler,
  IRQ08_Handler,
  IRQ09_Handler,
  IRQ10_Handler,
  IRQ11_Handler,
  IRQ12_Handler,
  IRQ13_Handler,
  IRQ14_Handler,
  IRQ15_Handler
  #ifndef CORTEXM0DS
    ,
    IRQ16_Handler,
    IRQ17_Handler,
    IRQ18_Handler,
    IRQ19_Handler,
    IRQ20_Handler,
    IRQ21_Handler,
    IRQ22_Handler,
    IRQ23_Handler,
    IRQ24_Handler,
    IRQ25_Handler,
    IRQ26_Handler,
    IRQ27_Handler,
    IRQ28_Handler,
    IRQ29_Handler,
    IRQ30_Handler,
    IRQ31_Handler
  #endif //CORTEXM0DS
};
#pragma arm section

