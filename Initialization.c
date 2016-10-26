#include "BF533 Flags.h"
asm(".section sdram0_bank1");

//--------------------------------------------------------------------------//
// Function:	Init_Flags													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function configures PF8 as input for edge sensitive	//
//				interrupt generation.										//
//				The switch connected to PF8 (SW7) can be used to change the	//
//				direction of the moving light.								//
//--------------------------------------------------------------------------//
void Init_Flags(void)
{
	*pFIO_INEN		= 0x0100; //PF8 input enable
	*pFIO_DIR		= 0x0000; //set to input
	*pFIO_EDGE		= 0x0100; //set interrupt sensivity to edge
	*pFIO_MASKA_D	= 0x0100; //enable interrupt on this pin
}

//--------------------------------------------------------------------------//
// Function:	Init_Timers													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function initialises Timer0 for PWM mode.				//
//				It is used as reference for the 'shift-clock'.				//
//--------------------------------------------------------------------------//
void Init_Timers(void)
{
	*pTIMER0_CONFIG		= 0x0019;
	*pTIMER0_PERIOD		= 0x00800000;
	*pTIMER0_WIDTH		= 0x00400000;
	*pTIMER_ENABLE		= 0x0001;
}

//--------------------------------------------------------------------------//
// Function:	Init_EBIU													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function initialises and enables the asynchronous		//
//				memory banks for the External Bus Interface Unit (EBIU), so	//
//				that access to Flash A is possible.							//
//--------------------------------------------------------------------------//
void Init_EBIU(void)
{
	*pEBIU_AMBCTL0	= 0x7bb07bb0; //7 cycles write access time, 10 cycles read access time, 2 cycles hold time, 2 cycles setup time, 4 cycles for bank transition, Transaction completes if ARDY sampled low, Ignore ARDY for accesses to this memory bank
	*pEBIU_AMBCTL1	= 0x7bb07bb0; 
	*pEBIU_AMGCTL	= 0x000f; //all banks enabled, enable clkout for async memory region access
}

//--------------------------------------------------------------------------//
// Function:	Init_Flash													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function sets the pin direction of Port B in Flash A	//
//				to output.													//
//				The LEDs on the ADSP-BF533 EZ-KIT are connected to Port B.	//
//--------------------------------------------------------------------------//
void Init_Flash(void)
{
	*pFlashA_PortB_Dir = 0x3f; // 0b00111111 (7-6 pins not used, 5-0 pins - leds
}

//--------------------------------------------------------------------------//
// Function:	Init_Interrupts												//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This function initialises the interrupts for Timer0 and		//
//				FlagA (PF8).												//
//--------------------------------------------------------------------------//
void Init_Interrupts(void)
{
	// assign core IDs to interrupts
	*pSIC_IAR0 = 0xffffffff;
	*pSIC_IAR1 = 0xffffffff;
	*pSIC_IAR2 = 0xffff5ff4;					// Timer0 -> ID4; FlagA -> ID5

	// assign ISRs to interrupt vectors
	register_handler(ik_ivg11, Timer0_ISR);		// Timer0 ISR -> IVG 11
	register_handler(ik_ivg12, FlagA_ISR);		// FlagA ISR -> IVG 12

	// enable Timer0 and FlagA interrupt
	*pSIC_IMASK = 0x00090000; //PF interrupt A, timer 0 interrupt enable
}

