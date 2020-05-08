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
/*
 * Copyright (C) 1994, 1995, 1996, 1997, 2000, 2001 by Ralf Baechle
 *
 * Copyright (C) 2001, Monta Vista Software
 * Author: jsun@mvista.com or jsun@junsun.net
 */
#ifndef _cp0regdef_h_
#define _cp0regdef_h_

/*
 * Coprocessor 0 register names
 */
#define CP0_INDEX           $0
#define CP0_RANDOM          $1
#define CP0_ENTRYLO0        $2
#define CP0_ENTRYLO1        $3
#define CP0_CONF            $3
#define CP0_GLOBALNUMBER    $3, 1
#define CP0_CONTEXT         $4
#define CP0_PAGEMASK        $5
#define CP0_WIRED           $6
#define CP0_INFO            $7
#define CP0_HWRENA          $7, 0
#define CP0_BADVADDR        $8
#define CP0_BADINSTR        $8, 1
#define CP0_COUNT           $9
#define CP0_ENTRYHI         $10
#define CP0_COMPARE         $11
#define CP0_STATUS          $12
#define CP0_CAUSE           $13
#define CP0_EPC             $14
#define CP0_PRID            $15
#define CP0_EBASE           $15, 1
#define CP0_CMGCRBASE       $15, 3
#define CP0_CONFIG          $16
#define CP0_CONFIG3         $16, 3
#define CP0_CONFIG5         $16, 5
#define CP0_LLADDR          $17
#define CP0_WATCHLO         $18
#define CP0_WATCHHI         $19
#define CP0_XCONTEXT        $20
#define CP0_FRAMEMASK       $21
#define CP0_DIAGNOSTIC      $22
#define CP0_DEBUG           $23
#define CP0_DEPC            $24
#define CP0_PERFORMANCE     $25
#define CP0_ECC             $26
#define CP0_CACHEERR        $27
#define CP0_TAGLO           $28
#define CP0_TAGHI           $29
#define CP0_ERROREPC        $30
#define CP0_DESAVE          $31

#define ST1_IE              0x00000001
#define ST1_ERL             0x00000004
#define ST1_CH              0x00040000
#define ST1_NMI             0x00080000
#define ST1_SR              0x00100000
#define ST1_TS              0x00200000
#define ST1_BEV             0x00400000
#define ST1_RE              0x02000000
#define ST1_FR              0x04000000
#define ST1_CU              0xf0000000
#define ST1_CU0             0x10000000
#define ST1_CU1             0x20000000
#define ST1_CU2             0x40000000
#define ST1_CU3             0x80000000

// STATUS BIT 8-15
#define CP0_ENABLE_IM0      0x00000100
#define CP0_ENABLE_IM1      0x00000200
#define CP0_ENABLE_IM2      0x00000400
#define CP0_ENABLE_IM3      0x00000800
#define CP0_ENABLE_IM4      0x00001000
#define CP0_ENABLE_IM5      0x00002000
#define CP0_ENABLE_IM6      0x00004000
#define CP0_ENABLE_IM7      0x00008000

#define IM7_OFFSET_BIT      15
#define IM6_OFFSET_BIT      14
#define IM5_OFFSET_BIT      13
#define IM4_OFFSET_BIT      12
#define IM3_OFFSET_BIT      11
#define IM2_OFFSET_BIT      10
#define IM1_OFFSET_BIT      9
#define IM0_OFFSET_BIT      8

#define IRQ_MASK            0x0000FF00

#define ereturn             asm volatile("eret\n\t" "nop\n\t");

#endif
