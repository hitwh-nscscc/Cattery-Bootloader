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

#ifndef __CATTERY_IRQ_H_
#define __CATTERY_IRQ_H_
#endif

#include "regdef.h"
#include "cp0regdef.h"
#include "def.h"

#define         GetIRQ(CP0_ST, IRQ_BIT) CP0_ST & IRQ_MASK & IRQ_BIT == IRQ_BIT
#define         TRACE_COUNT         4

uint32          get_cp0Status();
uint32          get_cp0Cause();
uint32          get_cp0EPC();

// extern uint8    _GLOBAL_TIMER_ON;