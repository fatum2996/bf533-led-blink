#ifndef  __BF533_FLAGS_DEFINED
	#define __BF533_FLAGS_DEFINED

//--------------------------------------------------------------------------//
// Header files																//
//--------------------------------------------------------------------------//
#include <sys\exception.h>
#include <cdefBF533.h>

//--------------------------------------------------------------------------//
// Symbolic constants														//
//--------------------------------------------------------------------------//
// addresses for Port B in Flash A
#define pFlashA_PortB_Dir	(volatile unsigned char *)0x20270007
#define pFlashA_PortB_Data	(volatile unsigned char *)0x20270005

//--------------------------------------------------------------------------//
// Global variables															//
//--------------------------------------------------------------------------//
extern short sLight_Move_Direction;

//--------------------------------------------------------------------------//
// Prototypes																//
//--------------------------------------------------------------------------//
// in file Initialization.c
void Init_Flags(void);
void Init_Timers(void);
void Init_EBIU(void);
void Init_Flash(void);
void Init_Interrupts(void);
// in file ISRs.c
EX_INTERRUPT_HANDLER(Timer0_ISR);
EX_INTERRUPT_HANDLER(FlagA_ISR);

#endif //__BF533_FLAGS_DEFINED

