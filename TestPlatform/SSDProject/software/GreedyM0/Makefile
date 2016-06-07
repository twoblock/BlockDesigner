
CC=wine /root/ARM/RVCT/Programs/4.0/400/win_32-pentium/armcc
AS=wine /root/ARM/RVCT/Programs/4.0/400/win_32-pentium/armasm
LD=wine /root/ARM/RVCT/Programs/4.0/400/win_32-pentium/armlink
AR=wine /root/ARM/RVCT/Programs/4.0/400/win_32-pentium/armar
FE=wine /root/ARM/RVCT/Programs/4.0/400/win_32-pentium/fromelf
#CC=armcc
#AS=armasm
#LD=armlink
#AR=armar
#FE=fromelf
RM=rm -f $(1)

CORTEXM0DS_BIN=CM4-firmware.bin
CORTEXM0DS_AXF=CM4-firmware.axf

SRCS = $(wildcard *.c)
OBJECTS = $(SRCS:.c=.o)

CFLAGS = --cpu 6-M -c -g  -DCORTEXM0DS -DUsePrintf --c99 -I/root/ARM/RVCT/Data/4.0/400/include/windows

all: clean $(CORTEXM0DS_BIN)

$(CORTEXM0DS_BIN): $(CORTEXM0DS_AXF)
	$(FE) --bin -o $@ $^
	$(FE) -c -o _reverse_asm.txt $^
	$(FE) -d -o _data_section.txt $^
	$(FE) -s -o _symbol.txt $^
	$(FE) --disassemble -o _disassemble.txt $^
	$(FE) --i32 -o _IntelHex32.txt $^
	$(FE) --m32 -o _Motorola32.txt $^
	$(FE) --vhx -o _VerilogHex.txt $^


$(CORTEXM0DS_AXF):$(OBJECTS)
	$(LD) --cpu 6-M --scatter=scatter.scat -o $@ $^ --libpath=/root/ARM/RVCT/Data/4.0/400/lib

clean:
	$(call RM, *.txt)
	$(call RM, log_*)
	$(call RM, *~)
	$(call RM, *.bak)
	$(call RM, *.o)
	$(call RM, *.axf)
	$(call RM, *.bin)

clean_all:
	$(call RM, *.txt)
	$(call RM, log_*)
	$(call RM, *~)
	$(call RM, *.bak)
	$(call RM, *.o)
	$(call RM, *.axf)
	$(call RM, *.bin)

