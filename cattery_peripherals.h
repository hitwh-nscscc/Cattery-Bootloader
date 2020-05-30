// =============================================================================
//  ArHShRn :: Ragdoll SoC :: Cattery BIOS
//   _____                 _       _ _  _____        _____
//  |  __ \               | |     | | |/ ____|      / ____|
//  | |__) |__ _  __ _  __| | ___ | | | (___   ___ | |
//  |  _  // _` |/ _` |/ _` |/ _ \| | |\___ \ / _ \| |
//  | | \ \ (_| | (_| | (_| | (_) | | |____) | (_) | |____
//  |_|  \_\__,_|\__, |\__,_|\___/|_|_|_____/ \___/ \_____|
//                __/ |
//               |___/
//                          /\_____/\
//                         /  o   o  \
//                        ( ==  ^  == )
//                         )         (
//                        (           )
//                       ( (  )   (  ) )
//                      (__(__)___(__)__)
//
//  Code And Concept By ArHShRn
//  https://github.com/ArHShRn
// =============================================================================

#ifndef __CATTERY_PERIPHERALS_H_
#define __CATTERY_PERIPHERALS_H_

#include "def.h"

/* Basic Bit Operations */
#define SETBIT(x,y)                 x |= (1 << y)
#define CLRBIT(x,y)                 x &= ~(1 << y)
#define REVBIT(x,y)                 x ^= (1 << y)
#define GETBIT(x,y)                 ((x) >> (y) & 1)

/* Base Addresses and Register Offsets */
#define HLED_BASE_ADDR	            GPIOBASE                     // GPIO1_Data
#define HSWITCH_BASE_ADDR           GPIOBASE + 0x0008            // GPIO2_Data

#define UART_REGBASE_ADDR           UARTBASE + 0x1000
#define UART_DAT_ADDR               UART_REGBASE_ADDR + 0x0
#define UART_FCR_ADDR               UART_REGBASE_ADDR + 0x8
#define UART_LCR_ADDR               UART_REGBASE_ADDR + 0xC
#define UART_LSR_ADDR               UART_REGBASE_ADDR + 0x14
#define UART_DLL_ADDR               UART_REGBASE_ADDR + 0x0
#define UART_DLM_ADDR               UART_REGBASE_ADDR + 0x4
#define UART_MCR_ADDR               UART_REGBASE_ADDR + 0x10
#define UART_IER_ADDR               UART_REGBASE_ADDR + 0x4

/* Basic Reg Read/Write */
#define OutputLED(x)                (*(volatile unsigned int*)HLED_BASE_ADDR = ~x)

#define                             WriteReg(BaseAddress, RegOffset, Data) \
                                    Out32((BaseAddress) + (RegOffset), (unsigned int)(Data))

#define                             ReadReg(BaseAddress, RegOffset) \
                                    In32((BaseAddress) + (RegOffset))

void                                Out32(unsigned int Addr, unsigned int Value);
unsigned int                        In32(unsigned int Addr);

void                                UART16550_Init();
uint8                               UART16550_ReadChar();
void                                UART16550_PutChar(uint8 data);
uint32                              UART16550_ReadWord();

void                                Toggle_CKSEG0(int cacheable);

#endif