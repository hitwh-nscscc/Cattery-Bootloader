# =============================================================================
#  ArHShRn :: Ragdoll SoC :: Cattery BIOS
#   _____                 _       _ _  _____        _____ 
#  |  __ \               | |     | | |/ ____|      / ____|
#  | |__) |__ _  __ _  __| | ___ | | | (___   ___ | |     
#  |  _  // _` |/ _` |/ _` |/ _ \| | |\___ \ / _ \| |     
#  | | \ \ (_| | (_| | (_| | (_) | | |____) | (_) | |____ 
#  |_|  \_\__,_|\__, |\__,_|\___/|_|_|_____/ \___/ \_____|
#                __/ |                                    
#               |___/                                     
#                          /\_____/\
#                         /  o   o  \
#                        ( ==  ^  == )
#                         )         (
#                        (           )
#                       ( (  )   (  ) )
#                      (__(__)___(__)__)                                           

#  Code And Concept By ArHShRn
#  https://github.com/ArHShRn
# =============================================================================
######## CONFIGURATION #########

LEDBASE =		0xB0600000					# Base addr of AXI GPIO to control LEDs
UARTBASE = 		0xB0400000					# Base addr of AXI UART16550. 
											# RegOffset is calculated in cattery_peripherals.h
SPIBASE = 		0xBD000000					# Base addr of SPI Flash read addr, not CRs addr!

LOADADDR = 		0xBFC00000					# Bootloader load address
RAM_LOADADDR =  0x80000000					# Binary file memory load address
								
RAMSIZE = 		0x07000000					# 128M - 16M / 16M GRAM
				
STACK_SIZE =	0x00001000					# 4K, U-Boot recommended

CROSS_COMPILE = mipsel-linux-gnu-

######## END OF CONFIGURATION #########

CC =       $(CROSS_COMPILE)gcc
LD =       $(CROSS_COMPILE)ld
OBJCOPY =  $(CROSS_COMPILE)objcopy
OBJDUMP =  $(CROSS_COMPILE)objdump

TARGET = cattery_bootloader

CFLAGS = -DLEDBASE=${LEDBASE} -DUARTBASE=${UARTBASE} -DSPIBASE=${SPIBASE} -DLOADADDR=${LOADADDR} -DRAM_LOADADDR=${RAM_LOADADDR} -DRAMSIZE=${RAMSIZE} -DSTACK_SIZE=${STACK_SIZE} -O0 -msoft-float -mips32 -mxgot -fno-builtin -fno-PIC -fno-PIE -ffunction-sections -fdata-sections -G 0 -nostdlib -ffreestanding

# Drop some uninteresting sections in the kernel.
# This is only relevant for ELF kernels but doesn't hurt a.out
drop-sections   = .reginfo .mdebug
strip-flags     = $(addprefix --remove-section=,$(drop-sections))


all : clean elf srec bin coe disasm

srec : 		$(TARGET).srec
elf : 		$(TARGET).elf
bin : 		$(TARGET).bin
coe : 		$(TARGET).coe
disasm : 	$(TARGET).s

.S.s:
	$(CPP) $(CFLAGS) $< -o $*.s
.S.o:
	$(CC) $(CFLAGS) -c $< -o $*.o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $*.o
bin2coe.elf: bin2coe.c
	gcc $< -o bin2coe.elf

$(TARGET).elf : 	start.o main.o cattery_peripherals.o print.o printf.o irq.o
	$(LD) -o $(TARGET).elf -N -Tcattery_ld.lds -Ttext $(LOADADDR) $^

$(TARGET).srec : 	$(TARGET).elf
	$(OBJCOPY) -S -O srec $(strip-flags) $(TARGET).elf $(TARGET).srec

$(TARGET).bin : 	$(TARGET).elf
	$(OBJCOPY) -O binary $(strip-flags) $(TARGET).elf $(TARGET).bin

$(TARGET).coe : 	$(TARGET).bin bin2coe.elf
	./bin2coe.elf -f $(TARGET).bin -o $(TARGET).coe

$(TARGET).s : 		$(TARGET).elf
	$(OBJDUMP) -alD $(TARGET).elf > $(TARGET).s

clean:
	rm -f *.o *.elf *.srec *.bin *.s *.coe

nm:
	$(CROSS_COMPILE)nm $(TARGET).elf

