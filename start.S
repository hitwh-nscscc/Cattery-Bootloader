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
#include "regdef.h"
#include "cp0regdef.h"
#include "asm.h"

    .set noreorder

LEAF(_start)
    .org 0x000
    # Clear all the regs
    add     $0,     zero, zero
    add     $1,     zero, zero
    add     $2,     zero, zero
    add     $3,     zero, zero
    add     $4,     zero, zero
    add     $5,     zero, zero
    add     $6,     zero, zero
    add     $7,     zero, zero
    add     $8,     zero, zero
    add     $9,     zero, zero
    add     $10,    zero, zero
    add     $11,    zero, zero
    add     $12,    zero, zero
    add     $13,    zero, zero
    add     $14,    zero, zero
    add     $15,    zero, zero
    add     $16,    zero, zero
    add     $17,    zero, zero
    add     $18,    zero, zero
    add     $19,    zero, zero
    add     $20,    zero, zero
    add     $21,    zero, zero
    add     $22,    zero, zero
    add     $23,    zero, zero
    add     $24,    zero, zero
    add     $25,    zero, zero
    add     $26,    zero, zero
    add     $27,    zero, zero
    add     $28,    zero, zero
    add     $29,    zero, zero
    add     $30,    zero, zero
    add     $31,    zero, zero
    

    # Jump to START
    b       START

    #------------------------------------------------------------------------------------
    # BOOTROM Unhandled Exceptions
    .org 0x200
    /* TLB refill, 32 bit task */
    TLBL:
    jal		tlb_error	        # branch to TLBL
    nop
    
    .org 0x380
    /* General exception */
    GENERAL_EXC:
    jal		irq_request			# jump to INTR service program, EXL is set to 1 when entered here
    nop
    nop
    nop
    
    eret
    nop

    #------------------------------------------

    #------------------------------------------------------------------------------------
    # BOOT STAGE 1
    .org 0x500
    START:
    # Init CP0 Status
    mfc0    t0, CP0_STATUS

    or      t0, ST1_BEV                 # Set BEV to 1 to use kseg1 to boot

    and     t0, 0xFFFF00FF              # Close all interrupts      
    # and     t0, ~ST1_ERL                # Set ERL to 0 to respond intrs
    # ori     t0, ST1_IE                  # Enable interrupts
    # ori     t0, CP0_ENABLE_IM2          # Open IM2(hardware interrupt 0) to receive UART exception
    # ori     t0, CP0_ENABLE_IM7          # Open IM7 to receive count interrupt

    mtc0    t0, CP0_STATUS 

        # Disable kernel mode cache
    mfc0	t0, CP0_CONFIG
    and	t0, ~0x7
    mtc0	t0, CP0_CONFIG

        # setup stack
    /* set up stack */
    li  t1, 0x80000000 + RAMSIZE - STACK_SIZE
    li  t0, -16   
    and sp, t1, t0              # force 16 byte alignment
    #------------------------------------------
    
    #------------------------------------------------------------------------------------
    # START TO BOOT
    # Initialize URAT Lite
    jal UART16550_Init
    nop

    # # Enable INTC
    # jal INIT_INTC
    # nop

    # Jump to main function, start of the c/c++ code
    jal	main
    nop
    #------------------------------------------

    jal end_call
    nop
END(_start)

