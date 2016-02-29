#################### Way 0 PUT ###################   
##                                              ##
##			 Command 0 SoftwareLoad                 ##
##			 Command 1 ExecutionControl             ##
##			 Command 2 PutDebugInterface            ##
##			 Command 3 PutMemoryMap                 ##
##			 Command 4 WireTraceControl             ##
##			 Command 5 RegisterCallBack             ##
##			 Command 6 LoadModule                   ##
##			 Command 7 BDPMDInit                    ##
##                                              ##
#################### Way 1 GET ###################   
##                                              ##
## 			 Command 0 ModuleInfo                   ##
## 			 Command 1 GetDebugInterface            ##
## 			 Command 2 GetMemoryMap                 ##
##                                              ##
################# sleep command ##################   
##                                              ##
##       sleep time                             ##
##                                              ##
##################################################

0 6 /home/harold/workspace/BlockDesigner/TestPlatform/console/libconsole.so BD_CONSOLE
0 6 /home/harold/workspace/BlockDesigner/TestPlatform/AHB_Lite/libAHB_Lite.so BD_AHB_LITE
0 6 /home/harold/workspace/BlockDesigner/TestPlatform/ahbl2mem/libahbl2mem.so BD_ROM
0 6 /home/harold/workspace/BlockDesigner/TestPlatform/ahbl2mem_1/libahbl2mem_1.so BD_SRAM
0 6 /home/harold/workspace/BlockDesigner/TestPlatform/tb/libtb.so BD_TB
0 6 /home/harold/workspace/BlockDesigner/TestPlatform/VCORTEXM0DS/libVCORTEXM0DS.so BD_CORTEXM0DS
0 7 BDPMD.json

0 4 0 BD_CORTEXM0DS$HCLK
0 4 0 BD_CORTEXM0DS$HRESETn
0 4 0 BD_CORTEXM0DS$MM_M0 AHB
0 4 0 BD_ROM$SS_S0 AHB
0 4 0 BD_SRAM$SS_S0 AHB

PUT ExecutionControl STEP 2000

GET GetDebugInterface BD_CORTEXM0DS reg read 16
GET GetDebugInterface BD_CORTEXM0DS reg read 15
GET GetDebugInterface BD_CORTEXM0DS reg read 14
GET GetDebugInterface BD_CORTEXM0DS reg read 13
GET GetDebugInterface BD_CORTEXM0DS reg read 12
GET GetDebugInterface BD_CORTEXM0DS reg read 11
GET GetDebugInterface BD_CORTEXM0DS reg read 10
GET GetDebugInterface BD_CORTEXM0DS reg read 9
GET GetDebugInterface BD_CORTEXM0DS reg read 8
GET GetDebugInterface BD_CORTEXM0DS reg read 7
GET GetDebugInterface BD_CORTEXM0DS reg read 6
GET GetDebugInterface BD_CORTEXM0DS reg read 5
GET GetDebugInterface BD_CORTEXM0DS reg read 4
GET GetDebugInterface BD_CORTEXM0DS reg read 3
GET GetDebugInterface BD_CORTEXM0DS reg read 2
GET GetDebugInterface BD_CORTEXM0DS reg read 1
GET GetDebugInterface BD_CORTEXM0DS reg read 0

PUT ExecutionControl STEP 10 

GET GetDebugInterface BD_CORTEXM0DS reg read 16
GET GetDebugInterface BD_CORTEXM0DS reg read 15
GET GetDebugInterface BD_CORTEXM0DS reg read 14
GET GetDebugInterface BD_CORTEXM0DS reg read 13
GET GetDebugInterface BD_CORTEXM0DS reg read 12
GET GetDebugInterface BD_CORTEXM0DS reg read 11
GET GetDebugInterface BD_CORTEXM0DS reg read 10
GET GetDebugInterface BD_CORTEXM0DS reg read 9
GET GetDebugInterface BD_CORTEXM0DS reg read 8
GET GetDebugInterface BD_CORTEXM0DS reg read 7
GET GetDebugInterface BD_CORTEXM0DS reg read 6
GET GetDebugInterface BD_CORTEXM0DS reg read 5
GET GetDebugInterface BD_CORTEXM0DS reg read 4
GET GetDebugInterface BD_CORTEXM0DS reg read 3
GET GetDebugInterface BD_CORTEXM0DS reg read 2
GET GetDebugInterface BD_CORTEXM0DS reg read 1
GET GetDebugInterface BD_CORTEXM0DS reg read 0

PUT ExecutionControl STEP 10 

GET GetDebugInterface BD_CORTEXM0DS reg read 16
GET GetDebugInterface BD_CORTEXM0DS reg read 15
GET GetDebugInterface BD_CORTEXM0DS reg read 14
GET GetDebugInterface BD_CORTEXM0DS reg read 13
GET GetDebugInterface BD_CORTEXM0DS reg read 12
GET GetDebugInterface BD_CORTEXM0DS reg read 11
GET GetDebugInterface BD_CORTEXM0DS reg read 10
GET GetDebugInterface BD_CORTEXM0DS reg read 9
GET GetDebugInterface BD_CORTEXM0DS reg read 8
GET GetDebugInterface BD_CORTEXM0DS reg read 7
GET GetDebugInterface BD_CORTEXM0DS reg read 6
GET GetDebugInterface BD_CORTEXM0DS reg read 5
GET GetDebugInterface BD_CORTEXM0DS reg read 4
GET GetDebugInterface BD_CORTEXM0DS reg read 3
GET GetDebugInterface BD_CORTEXM0DS reg read 2
GET GetDebugInterface BD_CORTEXM0DS reg read 1
GET GetDebugInterface BD_CORTEXM0DS reg read 0

PUT ExecutionControl STEP 10 

GET GetDebugInterface BD_CORTEXM0DS reg read 16
GET GetDebugInterface BD_CORTEXM0DS reg read 15
GET GetDebugInterface BD_CORTEXM0DS reg read 14
GET GetDebugInterface BD_CORTEXM0DS reg read 13
GET GetDebugInterface BD_CORTEXM0DS reg read 12
GET GetDebugInterface BD_CORTEXM0DS reg read 11
GET GetDebugInterface BD_CORTEXM0DS reg read 10
GET GetDebugInterface BD_CORTEXM0DS reg read 9
GET GetDebugInterface BD_CORTEXM0DS reg read 8
GET GetDebugInterface BD_CORTEXM0DS reg read 7
GET GetDebugInterface BD_CORTEXM0DS reg read 6
GET GetDebugInterface BD_CORTEXM0DS reg read 5
GET GetDebugInterface BD_CORTEXM0DS reg read 4
GET GetDebugInterface BD_CORTEXM0DS reg read 3
GET GetDebugInterface BD_CORTEXM0DS reg read 2
GET GetDebugInterface BD_CORTEXM0DS reg read 1
GET GetDebugInterface BD_CORTEXM0DS reg read 0

PUT ExecutionControl STEP 10 

GET GetDebugInterface BD_CORTEXM0DS reg read 16
GET GetDebugInterface BD_CORTEXM0DS reg read 15
GET GetDebugInterface BD_CORTEXM0DS reg read 14
GET GetDebugInterface BD_CORTEXM0DS reg read 13
GET GetDebugInterface BD_CORTEXM0DS reg read 12
GET GetDebugInterface BD_CORTEXM0DS reg read 11
GET GetDebugInterface BD_CORTEXM0DS reg read 10
GET GetDebugInterface BD_CORTEXM0DS reg read 9
GET GetDebugInterface BD_CORTEXM0DS reg read 8
GET GetDebugInterface BD_CORTEXM0DS reg read 7
GET GetDebugInterface BD_CORTEXM0DS reg read 6
GET GetDebugInterface BD_CORTEXM0DS reg read 5
GET GetDebugInterface BD_CORTEXM0DS reg read 4
GET GetDebugInterface BD_CORTEXM0DS reg read 3
GET GetDebugInterface BD_CORTEXM0DS reg read 2
GET GetDebugInterface BD_CORTEXM0DS reg read 1
GET GetDebugInterface BD_CORTEXM0DS reg read 0

PUT ExecutionControl STEP 10 

GET GetDebugInterface BD_CORTEXM0DS reg read 16
GET GetDebugInterface BD_CORTEXM0DS reg read 15
GET GetDebugInterface BD_CORTEXM0DS reg read 14
GET GetDebugInterface BD_CORTEXM0DS reg read 13
GET GetDebugInterface BD_CORTEXM0DS reg read 12
GET GetDebugInterface BD_CORTEXM0DS reg read 11
GET GetDebugInterface BD_CORTEXM0DS reg read 10
GET GetDebugInterface BD_CORTEXM0DS reg read 9
GET GetDebugInterface BD_CORTEXM0DS reg read 8
GET GetDebugInterface BD_CORTEXM0DS reg read 7
GET GetDebugInterface BD_CORTEXM0DS reg read 6
GET GetDebugInterface BD_CORTEXM0DS reg read 5
GET GetDebugInterface BD_CORTEXM0DS reg read 4
GET GetDebugInterface BD_CORTEXM0DS reg read 3
GET GetDebugInterface BD_CORTEXM0DS reg read 2
GET GetDebugInterface BD_CORTEXM0DS reg read 1
GET GetDebugInterface BD_CORTEXM0DS reg read 0

PUT ExecutionControl STEP 4000

######################### Block Designer command set ########################
##                                                                         ##
## ################# Way 0 Put #################                           ##
##                                                                         ##
##  Command 0 Software Load                                                ##
##                                                                         ##
##     arg1 core name                                                      ##
##     arg2 software path                                                  ##
##                                                                         ##
##  Command 1 execution control                                            ##
##                                                                         ##
##     arg1 control                                                        ##
##     	  	 0 run                                                         ##
##           1 stop                                                        ##
##   	       2 step                                                        ##
##                                                                         ##
##     arg2 value                                                          ##
##                                                                         ##
##  Command 2 module Control( BDDI )                                       ##
##                                                                         ##
##    arg1 Id of module                                                    ##
##                                                                         ##
##    arg2 which API                                                       ##
##   	  0. parameter                                                       ##
##    	1. register                                                        ##
##  	  2. memory                                                          ##
##      3. assembly code                                                   ##
##                                                                         ##
##    arg3 which function                                                  ##
##             0. write                                                    ##
##             1. breakpoint                                               ##
##                                                                         ##
##    arg4  Index of register, address of memory, line of assembly code.   ##
##    arg5  value                                                          ##
##                                                                         ##
##  Command 3 Memory Map                                                   ##
##    arg1 Id of module                                                    ##
##    arg2 which Port                                                      ##
##    arg3 start address                                                   ##
##    arg4 Size                                                            ##
##                                                                         ##
##  Command 4 Wire Trace Control                                           ##
##                                                                         ##
##    arg1 disable or enable                                               ##
##     	0. enable                                                          ##
##     	1. disable                                                         ##
##    arg2 which wire                                                      ##
##		arg3 wire type																											 ##
##                                                                         ##
##  Command 5 Register Call back                                           ##
##                                                                         ##
##   arg1 which call back function                                         ##
##   	0. Status change                                                     ##
##   	1. Cycle Listener                                                    ##
##   	2. Module create                                                     ##
##                                                                         ##
##   arg2 function pointer                                                 ##
##                                                                         ##
##  Command 6 Load module                                                  ##
##                                                                         ##
##   arg1 so file path                                                     ##
##   arg2 module name                                                      ##
##                                                                         ##
##  Command 7 BDPMD Initialization                                         ##
##                                                                         ##
##	 arg1 json file path                                                   ##
##                                                                         ##
## ################# Way 1 Get #################                           ##
##                                                                         ##
##  Command 0 Module Info                                                  ##
##                                                                         ##
##   return module list json string                                        ##
##                                                                         ##
##  Command 1 module Control( BDDI )                                       ##
##                                                                         ##
##   arg1 Id of module                                                     ##
##   arg2 which API                                                        ##
##      0. parameter                                                       ##
##      1. register                                                        ##
##    	2. memory                                                          ##
##      3. assembly code                                                   ##
##                                                                         ##
##   arg3  which function                                                  ##
##      0. read                                                            ##
##                                                                         ##
##   arg4  Index of register, address of memory, line of assembly code.    ##
##                                                                         ##
##  Command 2 Memory Map                                                   ##
##                                                                         ##
##    arg1 Id of module                                                    ##
##    arg2 which Port                                                      ##
##    arg3 start address                                                   ##
##    arg4 Size                                                            ##
##                                                                         ##
#############################################################################                                                                         
