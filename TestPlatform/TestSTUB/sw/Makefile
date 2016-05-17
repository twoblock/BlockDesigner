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

CORTEXM0DS_BIN=CM0DS.bin
CORTEXM0DS_AXF=CM0DS.axf
CORTEXM0DS_ELF=CM0DS.elf

SRCS = $(wildcard *.c)
OBJECTS = $(SRCS:.c=.o)

CFLAGS = --cpu 6-M -c -g  -DCORTEXM0DS

all: clean $(CORTEXM0DS_BIN)

$(CORTEXM0DS_BIN): $(CORTEXM0DS_ELF)
	$(FE) --bin -o $@ $^
	$(FE) -c -o _reverse_asm.txt $^
	#$(FE) -d -o _data_section.txt $^
	#$(FE) -s -o _symbol.txt $^
	$(FE) --disassemble -o _disassemble.txt $^
	#$(FE) --i32 -o _IntelHex32.txt $^
	#$(FE) --m32 -o _Motorola32.txt $^
	$(FE) --vhx -o CM0DS.hex $^
	$(FE) --vhx -o CM0DS.txt $^


$(CORTEXM0DS_ELF):$(OBJECTS)
	$(LD) --cpu=6-M --scatter=scatter.scat -o $@ $^

clean:
	$(call RM,$(OBJECTS))
	$(call RM,$(CORTEXM0DS_AXF))
	$(call RM,$(CORTEXM0DS_BIN))
	$(call RM,$(CORTEXM0DS_ELF))
	$(call RM, *.hex)
	$(call RM, *.txt)

clean_all:
	$(call RM, *.txt)
	$(call RM, log_*)
	$(call RM, *~)
	$(call RM, *.bak)
	$(call RM, *.o)
	$(call RM, *.axf)
	$(call RM, *.bin)
	$(call RM, *.hex)
	$(call RM, *.elf)
