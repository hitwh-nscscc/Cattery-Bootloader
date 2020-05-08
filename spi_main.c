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

#define GMEMADDR_PHY                        0x07000000
#define GMEMADDR_V                          0x87000000

#define XTFT_BASE_ADDR                      0xBFD14000
#define XTFT_AR_OFFSET		                0 /**< Address Reg (Video memory) Offset */
#define XTFT_CR_OFFSET		                4 /**< Control Register Offset */
#define XTFT_IESR_OFFSET	                8 /**< Interrupt Enable and Status Reg Offset */


#define XTFT_CHAR_WIDTH			            8    /**< Character width */
#define XTFT_CHAR_HEIGHT		            12   /**< Character height */
#define XTFT_DISPLAY_WIDTH		            640  /**< Width of the screen */
#define XTFT_DISPLAY_HEIGHT		            480  /**< Height of the screen */
#define XTFT_DISPLAY_BUFFER_WIDTH	        1024 /**< Buffer width of a line */

#define XTFT_DCR_REG_SHIFT		            2    /**< Reg Shift for DCR Access */

#define XTFT_CR_TDE_MASK	                0x01 /**< TFT Display Enable Bit Mask */
#define XTFT_CR_DPS_MASK	                0x02 /**< TFT Display Scan Control Bit Mask */

#define XTFT_IESR_VADDRLATCH_STATUS_MASK    0x01 
#define XTFT_IESR_IE_MASK		            0x08

/**
 * The default color is white for foreground and black for background.
 * These values can range from 0 to 0xFFFFFFFF as each color is ranging
 * from 0 to 3F. The default value for column and row is 0.
 */
#define XTFT_DEF_FGCOLOR 0x00FFFFFF	/**< Foreground Color - White */
#define XTFT_DEF_BGCOLOR 0x0		/**< Background Color - Black */
#define XTFT_DEF_COLVAL  0x0		/**< Default Column Value */
#define XTFT_DEF_ROWVAL	 0x0		/**< Default Row Value */

uint32 XTft_GetVsyncStatus()
{
	return
    (
        (
            ReadReg(XTFT_BASE_ADDR, XTFT_IESR_OFFSET) &
		    XTFT_IESR_VADDRLATCH_STATUS_MASK
        )? 
        1 : 0
    );
}

void XTft_SetPixel(uint32 ColVal, uint32 RowVal, uint32 PixelVal)
{
	Out32
    (
        GMEMADDR_V + 
		(4 * ((RowVal) * XTFT_DISPLAY_BUFFER_WIDTH + ColVal)),
		PixelVal
    );
}

void XTft_FillScreen(uint32 ColStartVal, uint32 RowStartVal, uint32 ColEndVal, uint32 RowEndVal, uint32 PixelVal)
{
	uint32 ColIndex;
	uint32 RowIndex;

    printf("Entered XTft_FillScreen 0x%08X\n", XTft_FillScreen);

	for (ColIndex = ColStartVal; ColIndex <= ColEndVal; ColIndex++) 
    {
        printf("SETTING COL %d\r", ColIndex);
		for (RowIndex = RowStartVal; RowIndex <= RowEndVal;
			RowIndex++) 
        {
			XTft_SetPixel(ColIndex, RowIndex, PixelVal);
		}
	}
    printf("\n");

}

void XTft_ClearScreen()
{
    printf("Entered XTft_ClearScreen 0x%08X\n", XTft_ClearScreen);
	XTft_FillScreen(XTFT_DEF_COLVAL, XTFT_DEF_ROWVAL,
			(XTFT_DISPLAY_WIDTH - 1), (XTFT_DISPLAY_HEIGHT - 1),
			0xA020F0);
}

void XTft_DisableDisplay()
{
	uint32 CtrlReg;

	CtrlReg = ReadReg(XTFT_BASE_ADDR, XTFT_CR_OFFSET);

	/*
	 * Clear the Display Enable bit.
	 */
	CtrlReg &= (~XTFT_CR_TDE_MASK);

	/*
	 * Write to the Control Register.
	 */
	WriteReg(XTFT_BASE_ADDR, XTFT_CR_OFFSET, CtrlReg);

}

void XTft_EnableDisplay()
{
	uint32 CtrlReg;

	CtrlReg = ReadReg(XTFT_BASE_ADDR, XTFT_CR_OFFSET);

	/*
	 * Set the Display Enable bit.
	 */
	CtrlReg |= XTFT_CR_TDE_MASK;

	/*
	 * Write to the Control Register.
	 */
	WriteReg(XTFT_BASE_ADDR, XTFT_CR_OFFSET, CtrlReg);

}

void toLoop()
{
    voluint32 addr =  0x80000000;

    asm volatile
    (   
        "jr %0\t\n  \
        nop \t\n"   \
        ::"r"(addr)
    );

    return;
}

void main()
{
    // printf("Wait for Vsnyc......\n");
    // while (XTft_GetVsyncStatus() != XTFT_IESR_VADDRLATCH_STATUS_MASK);

    // WriteReg(XTFT_BASE_ADDR, XTFT_AR_OFFSET, GMEMADDR_PHY);
    // // WriteReg(XTFT_BASE_ADDR, XTFT_AR_OFFSET, RAM_LOADADDR - 0x80000000);

    // printf("VGA FB Buffer is now set to 0x%08X\n", In32(0xBFD14000));

	// int x,y;
	// unsigned char *p = (unsigned char *)gImage_pic;
	// int blue, green, red;
	// int color;
	
	// for(y = 0; y < 480; ++y) // Rollover images
	// {
    //             for (x = 0; x < 640; x++)
    //             {
               	 
    //                     blue  = *p++;
    //                     green = *p++;
    //                     red   = *p++;
 
    //                     color = red << 16 | green << 8 | blue << 0;

	// 					// color = *p++;

    //                     XTft_SetPixel(x, y, color);
	// 			}
	// }
	// printf("END PRINT.\n");
    // // XTft_DisableDisplay();
    // XTft_ClearScreen();
    // // XTft_EnableDisplay();
    // printf("Screen Clear.\n");

	toLoop();

    return;
}