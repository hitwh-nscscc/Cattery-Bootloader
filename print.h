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
 * Copyright (C) 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#ifndef _print_h_
#define _print_h_

#include <stdarg.h>

/* this is the maximum width for a variable */
#define LP_MAX_BUF	255

/* -*-
 * output function takes an void pointer which is passed in as the
 * second argument in lp_Print().  This black-box argument gives output
 * function a way to track state.
 *
 * The second argument in output function is a pointer to char buffer.
 * The third argument specifies the number of chars to outputed.
 *
 * output function cannot assume the buffer is null-terminated after
 * l number of chars.
 */
void lp_Print
(
	void (*output)(void *, char *, int), 
	void * arg,
	char *fmt, 
	va_list ap
);

#endif
