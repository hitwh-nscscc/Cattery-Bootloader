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

// #include "def.h"
// #include "regdef.h"
// #include "cp0regdef.h"
// #include "cattery_peripherals.h"
// #include "printf.h"
#include "irq.h"

// #define DEBUG

uint8 _GLOBAL_TIMER_ON = 0;

void printStack()
{
    uint32 status = get_cp0Status(), cause = get_cp0Cause(), EPC = get_cp0EPC();
    uint32 ExcCode = 0;
    uint32 gp, sp, fp, ra;

    asm volatile("move %0, $gp\n\t" : "=r" (gp));
    asm volatile("move %0, $sp\n\t" : "=r" (sp));
    asm volatile("move %0, $fp\n\t" : "=r" (fp));
    asm volatile("move %0, $ra\n\t" : "=r" (ra));
    ExcCode = (cause & 0x7C) >> 2;

    printf("\n## WARNING :: UNHANDLED EXCEPTION!\n");
    printf("#  CP0 EPC      = 0x%08x\n",    EPC);
    printf("#  INSTRUCTION  = 0x%08x\n\n",  In32(EPC));
    
    printf("#  GP           = 0x%08x\n",    gp);
    printf("#  SP           = 0x%08x\n",    sp);
    printf("#  FP           = 0x%08x\n",    fp);
    printf("#  RA           = 0x%08x\n\n",  ra);

    printf("#  CP0 STATUS   = 0x%08x\n",    status);
    printf("#  CP0 CAUSE    = 0x%08x\n",    cause);
    printf("#  ExcCode      = %d\n",        ExcCode);

    printf("#  Exception Details: ");
    switch(ExcCode)
    {
        case 0:     printf("Int\n"); break;
        case 1:     printf("TLB Mod Exception\n"); break;
        case 2:     printf("TLB Load Exception\n"); break;
        case 3:     printf("TLB Sava Exception\n"); break;
        case 4:     printf("Address Error While Load/InsFetch\n"); break;
        case 5:     printf("Address Error While Save\n"); break;
        case 6:     printf("InsFetch Bus Error\n"); break;
        case 7:     printf("DataFetch Bus Error\n"); break;
        case 8:     printf("SysCall\n"); break;
        case 9:     printf("Break Point\n"); break;
        case 10:    printf("Reserved Instruction\n"); break;
        case 11:    printf("Coprocessor Unuseable\n"); break;
        case 12:    printf("Integer Overflow\n"); break;
        case 13:    printf("Trap\n"); break;
        case 23:    printf("WATCH\n"); break;
        case 24:    printf("Mechine Check: Critical Error in CPU Control\n"); break;
        default:    printf("### RESERVED EXCCODE ###\n"); break;
    }


    return;
}

void irq_request()
{
    // Unhandled return
    printStack();
    for(;;);
}

void tlb_error()
{
    printStack();
    for(;;);
}

uint32 get_cp0Status()
{
    uint32 cp0status;
    asm volatile
    (
        "mfc0 %0, $12\n\t"
        : "=r" (cp0status)
    );
    return cp0status;
}

uint32 get_cp0Cause()
{
    uint32 cp0cause;
    asm volatile
    (
        "mfc0 %0, $13\n\t"
        : "=r" (cp0cause)
    );
    return cp0cause;
}

uint32 get_cp0EPC()
{
    uint32 cp0EPC;
    asm volatile
    (
        "mfc0 %0, $14\n\t"
        : "=r" (cp0EPC)
    );
    return cp0EPC;
}