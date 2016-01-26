#
# ***************** Way 0 PUT *****************   
# 
# Command 0 SoftwareLoad       
# Command 1 ExecutionControl    
# Command 2 PutDebugInterface  
# Command 3 PutMemoryMap        
# Command 4 WireTraceControl    
# Command 5 RegisterCallBack    
# Command 6 LoadModule          
#
# ***************** Way 1 GET *****************   
#
# Command 0 ModuleInfo         
# Command 1 GetDebugInterface   
# Command 2 GetMemoryMap       
#
# ***************** sleep command *****************   
#
#  sleep time  
#
#
#
#PUT ExecutionControl STEP 3000
#sleep 0.5
#PUT ExecutionControl STEP 1000
#sleep 0.5
#PUT ExecutionControl STEP 1000
#
#sleep 0.05
#PUT PutDebugInterface BD_CONSOLE reg write 5 0xFFFF
#sleep 0.05
#GET GetDebugInterface BD_CONSOLE reg read 5
#
#sleep 1.5
#PUT ExecutionControl STEP 2000
#sleep 1
#PUT ExecutionControl STEP 4000
#sleep 1.5
#
#
##0 1 STEP 1000
#sleep 2
#0 1 STEP 1000
#sleep 2
#0 1 STEP 1000
#sleep 2
#0 2 BD_CONSOLE reg write 5 0xFFFF
#sleep 2
#1 1 BD_CONSOLE reg read 5
#sleep 2
#0 1 STEP 3000
#sleep 2
#0 1 STEP 3000

#sleep 5

0 6 /home/bryan/workspace/BlockDesigner/TestPlatform/console/libconsole.so BD_CONSOLEee
1 0



################ Block Designer command set #########################
#
# *********************************************
# ***************** Way 0 Put *****************   
# *********************************************
# 
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 0 Software Load
#
#     arg1 core name
#     arg2 software path  
#
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 1 execution control
#
#     arg1 control
#     	  	0 run 
#           1 stop
#   	      2 step  
#
#     arg2 value
# 
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 2 module Control( BDDI ) 
#
#    arg1 Id of module
#
#    arg2 which API 
#   	 0. parameter
#   	 1. register
#  	   2. memory
#    	 3. assembly code 
#
#    arg3 which function
#             0. write
#             1. breakpoint 
#
#    arg4  Index of register, address of memory, line of assembly code.
#    arg5  value
#
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 3 Memory Map 
#    arg1 Id of module
#    arg2 which Port
#    arg3 start address
#    arg4 Size  
# 
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 4 Wire Trace Control
# 
#    arg1 Id of module ( What's wire? )
#    arg2 which wire
#    arg3 disable or enable 
#     	0. enable
#     	1. disable
#
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 5 Register Call back
# 
#   arg1 which call back function
#   	0. Status change
#   	1. Cycle Listener
#   	2. Module create 
# 
#   arg2 function pointer
#
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 6 Load module
#
#   arg1 so file path 
#   arg2 module name
#
#
# *********************************************
# ***************** Way 1 Get *****************   
# *********************************************
# 
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 0 Module Info
#
#   return module list json string 
#  
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 1 module Control( BDDI ) 
#
#   arg1 Id of module
#   arg2 which API 
#      0. parameter
#      1. register
#    	 2. memory
#      3. assembly code 
# 
#   arg3  which function
#      0. read 
# 
#   arg4  Index of register, address of memory, line of assembly code.
# 
#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
# 
#  Command 2 Memory Map 
# 
#    arg1 Id of module
#    arg2 which Port
#    arg3 start address
#    arg4 Size  
# 
# 
# 
# 
# 
# 
# 
# 
# 
