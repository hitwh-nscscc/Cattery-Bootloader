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

#include "mysleep.h"

void mysleep(uint32 sec)
{
    int wait = 0;
    _GLOBAL_TIMER_ON = 1;
    set_cp0compare(sec);
    // while (_GLOBAL_TIMER_ON);
    for(wait = 0; wait < 0x80000 * sec; wait++);

    return;
}

void set_cp0compare(uint32 sec)
{
    uint32 compare = sec * CPU_FREQ / 2;
    asm volatile
    (
        "mtc0 $zero, $9\n\t"    \
        "mtc0 %0, $11\n\t"      \
        "mtc0 $zero, $9\n\t"
        : "=r" (compare)
    );
};