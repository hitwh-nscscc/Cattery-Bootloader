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

#include "printf.h"
#include "cattery_peripherals.h"

#ifdef DEBUG
#define fullprintf printf
#else
#define fullprintf (void)
#endif

void printLogo(uint32 main_addr)
{
    printf("                      /\\_____/\\\n");
    printf("                     /  o   o  \\\n");
    printf("                    ( ==  ^  == )\n");
    printf("                     )         (\n");
    printf("                    (           )\n");
    printf("                   ( (  )   (  ) )\n");
    printf("                  (__(__)___(__)__)\n");
    printf(" \n");
    printf(" Welcome to Cattery Bootloader.\n");
    printf(" \t## STATUS:\n");
    printf(" \t\tBootloader Loading Address : 0x%08X\n", LOADADDR);
    printf(" \t\t           Main Entrance   : 0x%08X\n", main_addr);
    #ifdef DEBUG
    printf(" \t\t           Booting Mode    : Full\n");
    #else
    printf(" \t\t           Booting Mode    : Reduced\n");
    #endif

    return;
}

#ifdef DEBUG
// Print full mode functions.
void printHelp()
{
    fullprintf(" -=          Cattery Bootloader has several launching modes          =-\n\n");
    fullprintf("\t 1 - Memory Test      : Write n'  Dump 1K Data From 0x%08X\n", RAM_LOADADDR);
    fullprintf("\t 2 - Memory Dump      :           Dump 1K Data From 0x%08X\n", RAM_LOADADDR);
    fullprintf("\t 3 - SPI Flash Dump   :           Dump 1K Data From 0x%08X\n", SPIBASE);
    fullprintf("\t 4 - Load SPI to Mem  : Copy SPI Flash data to Memory 0x%08X\n", RAM_LOADADDR);
    fullprintf("\t 5 - BootM            : From Memory\n");
    fullprintf("\t 6 - BootSPI          : From SPI Flash\n");
    fullprintf("\t 7 - Load Serial      : Receive binary from serial and copy it to Mem\n");
    fullprintf("\t 8 - Read  Mem Data   : Read a data from a given address.\n");
    fullprintf("\t 9 - Alter Mem Data   : Set a specified data to a given addr\n");
    fullprintf("\t a - Dump Addr Range  : Dump a given range from a given start address\n");
    fullprintf("\t b - Memory Reset     : Set 1M Data 0x00000000 From 0x%08X\n", RAM_LOADADDR);
    fullprintf("\t 0 - END CALL         : TERMINATE THE BOOTLOADER, INFINITE LOOP.\n");
    fullprintf(" -====================================================================-\n");

    return;
}

// 8 data per row
void DumpAddrRange(uint32 _startAddr, uint32 range)
{
    if(range % 8 != 0) return;
    
    uint32 itr = _startAddr, row = 0, col = 0;
    printf("-= MEMDUMP DATA FROM 0x%08x RANGE 0x%08x=-\n", _startAddr, range);
    printf("  BASE/OFS   |\t0x00000000\t0x00000004\t0x00000008\t0x0000000C\t0x00000010\t0x00000014\t0x00000018\t0x0000001C\n");

    for(row = 0; row < range / 8; ++row)
    {
        printf("0x%08x---|", itr);
        for(col = 0; col < 8; ++col)
        {
            printf("\t0x%08x", In32(itr));
            itr += 4;
        }
        printf("\n");
    }

    return;
}

void testMem(int mode)
{
    uint32 itr = 0;
    // 1. Write 
    for(itr = RAM_LOADADDR; itr < RAM_LOADADDR + (0x00002000 * 4); itr += 4)
    {
        if(mode == 0) Out32(itr, itr);
        else *((voluint32*)itr) = itr;
    }

    // 2. Dump
    DumpAddrRange((uint32)RAM_LOADADDR, 1024);

    return;
}

uint8 atohex(uint8 ascii)
{
    //0-9
    if(ascii < 0x40) return (ascii - '0');
    // A-F
    else if(ascii > 0x40 && ascii < 0x60) return (ascii - 'A' + 10);
    else if(ascii > 0x60) return (ascii - 'a' + 10);
    else return 0;
}

void dumpRange()
{
    uint32 addr = 0, range = 0;

    printf("  > Please input a start addresss(like 0xBFD10000): ");
    UART16550_ReadbackChar();UART16550_ReadbackChar();
	addr |= atohex(UART16550_ReadbackChar()) << 28;
	addr |= atohex(UART16550_ReadbackChar()) << 24;
	addr |= atohex(UART16550_ReadbackChar()) << 20;
	addr |= atohex(UART16550_ReadbackChar()) << 16;
	addr |= atohex(UART16550_ReadbackChar()) << 12;
	addr |= atohex(UART16550_ReadbackChar()) << 8;
	addr |= atohex(UART16550_ReadbackChar()) << 4;
	addr |= atohex(UART16550_ReadbackChar());

    printf("\n  > Start Address = 0x%08X, input a hex range(must be multi of 8, like 0x00100000): ", addr);
    UART16550_ReadbackChar();UART16550_ReadbackChar();
	range |= atohex(UART16550_ReadbackChar()) << 28;
	range |= atohex(UART16550_ReadbackChar()) << 24;
	range |= atohex(UART16550_ReadbackChar()) << 20;
	range |= atohex(UART16550_ReadbackChar()) << 16;
	range |= atohex(UART16550_ReadbackChar()) << 12;
	range |= atohex(UART16550_ReadbackChar()) << 8;
	range |= atohex(UART16550_ReadbackChar()) << 4;
	range |= atohex(UART16550_ReadbackChar());

    printf("\n > SADDR[0x%08X] EADDR[0x%08X] Range = 0x%08X. (0/No, 1/Yes): ", addr, addr + range, range);
    if(UART16550_ReadbackChar() == '0') return;
    printf("\n");

    DumpAddrRange(addr, range);

    return;
}

void alterAddr()
{
    uint32 addr = 0, data = 0;

    printf("  > Please input an addresss to be altered(like 0xBFD10000): ");
    UART16550_ReadbackChar();UART16550_ReadbackChar();
	addr |= atohex(UART16550_ReadbackChar()) << 28;
	addr |= atohex(UART16550_ReadbackChar()) << 24;
	addr |= atohex(UART16550_ReadbackChar()) << 20;
	addr |= atohex(UART16550_ReadbackChar()) << 16;
	addr |= atohex(UART16550_ReadbackChar()) << 12;
	addr |= atohex(UART16550_ReadbackChar()) << 8;
	addr |= atohex(UART16550_ReadbackChar()) << 4;
	addr |= atohex(UART16550_ReadbackChar());

    printf("\n  > Target Address = 0x%08X, input a hex data(must be multi of 8, like 0x00100000): ", addr);
    UART16550_ReadbackChar();UART16550_ReadbackChar();
	data |= atohex(UART16550_ReadbackChar()) << 28;
	data |= atohex(UART16550_ReadbackChar()) << 24;
	data |= atohex(UART16550_ReadbackChar()) << 20;
	data |= atohex(UART16550_ReadbackChar()) << 16;
	data |= atohex(UART16550_ReadbackChar()) << 12;
	data |= atohex(UART16550_ReadbackChar()) << 8;
	data |= atohex(UART16550_ReadbackChar()) << 4;
	data |= atohex(UART16550_ReadbackChar());

    printf("\n > SADDR[0x%08X] DATA[0x%08X]. (0/No, 1/Yes): ", addr, data);
    if(UART16550_ReadbackChar() == '0') return;
    printf("\n");

    Out32(addr, data);

    return;
}

void readAddr()
{
    uint32 addr = 0;

    printf("  > Please input an addresss to be read(like 0xBFD10000): ");
    UART16550_ReadbackChar();UART16550_ReadbackChar();
	addr |= atohex(UART16550_ReadbackChar()) << 28;
	addr |= atohex(UART16550_ReadbackChar()) << 24;
	addr |= atohex(UART16550_ReadbackChar()) << 20;
	addr |= atohex(UART16550_ReadbackChar()) << 16;
	addr |= atohex(UART16550_ReadbackChar()) << 12;
	addr |= atohex(UART16550_ReadbackChar()) << 8;
	addr |= atohex(UART16550_ReadbackChar()) << 4;
	addr |= atohex(UART16550_ReadbackChar());

    printf("\n > ADDR[0x%08X] DATA[0x%08X]\n", addr, In32(addr));

    return;
}
 
int main(int argc, char** argv)                                
{
    uint8   ctl         = 0;
    uint32  itr         = 0, mem_itr    = 0, process    = 0;
    uint32  err_flag    = 0;
    uint32  spi_data    = 0, ram_data   = 0;

    Toggle_CKSEG0(0);

    printLogo(main);

    while(1)
    {
        printHelp();
        printf(" -> Please press a button to select exeMode: ");
        ctl = UART16550_ReadbackChar();
        printf("\n");

        if(ctl == '1')
        {
            printf(" -> Entering memory test...\n");
            testMem(0);
            continue;
        }
        if(ctl == '2')
        {
            printf(" -> Dumping 1K data from memory...\n");
            DumpAddrRange(RAM_LOADADDR, 1024);
            continue;
        }
        if(ctl == '3')
        {
            printf(" -> Dumping 1K data from SPI Flash...\n");
            DumpAddrRange(SPIBASE, 1024);
            continue;
        }
        if(ctl == '4')
        {
            printf(" -> Copying 1M SPI Flash data to memory, please wait...\n");
            for(itr = SPIBASE, mem_itr = RAM_LOADADDR; itr < SPIBASE + 0x00100000; itr += 4, mem_itr += 4)
            {
                Out32(mem_itr, In32(itr));
            }
            printf("\n");
            printf(" -> Load Complete. Need to dump memory for 1K data? (0:NO / 1:YES)\n");
            if(UART16550_ReadbackChar() == '1') DumpAddrRange(RAM_LOADADDR, 1024);
            continue;
        }
        if(ctl == '5')
        {
            uint32 addr = RAM_LOADADDR;
            printf(" -> Booting from memory...\n");

            printf(" -> Enable KSEG0 Cacheability? (0:NO / 1:YES) : ");
            if(UART16550_ReadbackChar() == '1') Toggle_CKSEG0(1);
            printf("\n");

            asm volatile
            (   
                "jr %0\t\n  \
                nop \t\n"   \
                ::"r"(addr)
            );
            
            continue;
        }
        if(ctl == '6')
        {
            uint32 addr = SPIBASE;
            printf(" -> Booting from SPI...\n");
            printf(" -> Dumping 1K data from SPI Flash...\n");
            DumpAddrRange(SPIBASE, 1024);

            printf(" -> Enable KSEG0 Cacheability...\n\n");
            Toggle_CKSEG0(1);

            printf("### Handle control to Das U-Boot. ###\n");
            
            asm volatile
            (   
                "jr %0\t\n  \
                nop \t\n"   \
                ::"r"(addr)
            );
            
            continue;
        }
        if(ctl == '7')
        {
            printf(" -> Prepared to receive data from serial.\n");
            printf(" -> Waiting to receive...\n");
            itr = 0; ram_data = 0;
            while(1)
            {
                ram_data = UART16550_ReadWord();

                if(ram_data == 0x03030303) break;

                printf(".");

                Out32(RAM_LOADADDR + itr, ram_data);

                itr += 4;
            }
            printf(" -> Done.\n");
            continue;
        }
        if(ctl == '8')
        {
            printf(" -> Prepare to read data.\n");
            readAddr();
            continue;
        }
        if(ctl == '9')
        {
            printf(" -> Prepare to alter a given address's data.\n");
            alterAddr();
            continue;
        }
        if(ctl == 'a')
        {
            printf(" -> Prepare to dump given range of an address.\n");
            dumpRange();
            continue;
        }
        if(ctl == 'b')
        {
            printf(" -> Clearing memory...\n");
            for(mem_itr = RAM_LOADADDR; mem_itr < RAM_LOADADDR + 0x00100000; itr += 4, mem_itr += 4)
            {
                Out32(mem_itr, 0);
            }

            continue;
        }
        if(ctl == '0')
        {
            printf(" -> Cattery Bootloader terminating, thanks for your support.\n");
            break;
        }

        printf(" -> INVALID INPUT.\n");
    }
    
    return 0;
}
#else
int main(int argc, char** argv)                                
{
    uint32 addr = SPIBASE;

    Toggle_CKSEG0(0);
    printLogo(main);

    // Start to boot U-Boot(or else) from SPI.
    //  Generally dump SPI Flash for twice to ensure the data is right.
    In32((voluint32)SPIBASE);
    In32((voluint32)SPIBASE);

    printf(" -> Booting from 0x%08X...\n", addr);
    printf(" -> Enable KSEG0 Cacheability...\n\n");
    Toggle_CKSEG0(1);
    printf("#### Handle control to the next stage. ####\n");
    
    asm volatile
    (   
        "jr %0\t\n  \
        nop \t\n"   \
        ::"r"(addr)
    );

    return 0;
}
#endif

void end_call()
{
    printf("#### [CATTERY BOOTLOADER] PROGRAM HAS TERMINATED, LIFE CYCLE ENDED.\n");
    for(;;);
}
