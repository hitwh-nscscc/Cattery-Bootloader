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

#include "cattery_peripherals.h"

/* Implementation */
void Out32(unsigned int Addr, unsigned int Value)
{
    volatile unsigned int *LocalAddr = (volatile unsigned int *)Addr;
    *LocalAddr = Value;
}

unsigned int In32(unsigned int Addr)
{
    return *(volatile unsigned int *) Addr;
}

void UART16550_Init()
{
    // Enable 8 bytes receive FIFO
    WriteReg(UART_FCR_ADDR, 0, 0x81);
    // enable DLAB latch
    WriteReg(UART_LCR_ADDR, 0, 0x80);
    // set the baudrate to 115200
    WriteReg(UART_DLL_ADDR, 0, 0x1B);  // 50M / (16 x 115200) = 0x1B
    WriteReg(UART_DLM_ADDR, 0, 0x0);
    // 8 data bits, 1 stop bit, parity off; turn off DLAB latch
    WriteReg(UART_LCR_ADDR, 0, ~0x80 & 0x03);
    // disable modem controls
    WriteReg(UART_MCR_ADDR, 0, 0);
    // disable interrupts
    WriteReg(UART_IER_ADDR, 0, 0);
}

uint8 UART16550_ReadChar()
{
    while (!(ReadReg(UART_LSR_ADDR, 0) & 0x01));
    return (uint8)ReadReg(UART_DAT_ADDR, 0);
}

uint8 UART16550_ReadbackChar()
{
    while (!(ReadReg(UART_LSR_ADDR, 0) & 0x01));
    uint8 data = ReadReg(UART_DAT_ADDR, 0);
    UART16550_PutChar(data);
    return data;
}

void UART16550_PutChar(uint8 data)
{
    while (!(ReadReg(UART_LSR_ADDR, 0) & 0x40));
    WriteReg(UART_DAT_ADDR, 0, data);
}

uint32 UART16550_ReadWord()
{
    uint32 word = 0;
    word |= UART16550_ReadChar();
    word |= UART16550_ReadChar() << 8;
    word |= UART16550_ReadChar() << 16;
    word |= UART16550_ReadChar() << 24;
    return word;
}

void Toggle_CKSEG0(int cacheable)
{
    uint32 cp0_config0;
    asm volatile("mfc0 %0, $16, 0;" :"=r"(cp0_config0));
    cp0_config0 &= ~0x7; // remove last 3 bits (K0)
    cp0_config0 |= cacheable == 1 ? 0x3 : 0x2; // set last 3 bits (K0)
    asm volatile("mtc0 %0, $16, 0;" ::"r"(cp0_config0));

    return;
}

