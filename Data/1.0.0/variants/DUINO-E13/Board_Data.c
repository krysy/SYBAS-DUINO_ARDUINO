/************************************************************************/
/*  																	*/
/*	Board_Data.c --	Default Board Customization Data Declarations		*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with a generic board using a	*/
/* PIC32 part in a 64-pin package.										*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/28/2011(GeneA): Created by splitting data out of Board_Defs.h	*/
/*  03/11/2012(BrianS): Modified for Fubarino board                     */
/*	02/12/2013(GeneA): removed dependency on Microchip plib library		*/
/*  20/05/2013(): Modified for Olimex Pinguino32 board					*/
/*  03/12/2013(SPP): Modified for Olimex PIC32-T795H					*/
/*																		*/
/************************************************************************/
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA  02111-1307  USA
/************************************************************************/

#if !defined(BOARD_DATA_C)
#define BOARD_DATA_C

#include <inttypes.h>

/* ------------------------------------------------------------ */
/*					Data Tables									*/
/* ------------------------------------------------------------ */
/* The following declarations define data used in pin mapping.	*/
/* ------------------------------------------------------------ */

#if defined(OPT_BOARD_DATA)

/* ------------------------------------------------------------ */
/* This table is used to map from port number to the address of
** the TRIS register for the port. This is used for setting the
** pin direction.
*/
const uint32_t	port_to_tris_PGM[] = {
	NOT_A_PORT,				//index value 0 is not used

#if defined(_PORTA)
	(uint32_t)&TRISA,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTB)
	(uint32_t)&TRISB,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTC)
	(uint32_t)&TRISC,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTD)
	(uint32_t)&TRISD,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTE)
	(uint32_t)&TRISE,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTF)
	(uint32_t)&TRISF,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTG)
	(uint32_t)&TRISG,
#else
	NOT_A_PORT,
#endif

	NOT_A_PORT,
};

/* ------------------------------------------------------------ */
/* This table is used to map the digital pin number to the port
** containing that pin. The default mapping is to assign pin numbers
** for every possible port bit in order from PORTA to PORTG.
*/
const uint8_t	digital_pin_to_port_PGM[] = {

	NOT_A_PORT, 	// inexisting 0
	
	_IOPORT_PF,     //RF2, DIO0
	_IOPORT_PF,		//RF8, DIO1
	
	_IOPORT_PE,		//RE0, DIO2
	_IOPORT_PE,		//RE1, DIO3
	_IOPORT_PE,		//RE2, DIO4
	_IOPORT_PE,		//RE3, DIO5	
	_IOPORT_PE,		//RE4, DIO7
	_IOPORT_PE,		//RE5, DIO9
	_IOPORT_PE,		//RE6, DIO11
	_IOPORT_PE,		//RE7, DIO13

	_IOPORT_PD,		//RD1, DIO6
	_IOPORT_PD,		//RD2, DIO8
	_IOPORT_PD,		//RD3, DIO10
	_IOPORT_PD,		//RD4, DIO12
	
	_IOPORT_PB,		//RB9, AN0
	_IOPORT_PB,		//RB8, AN1
	_IOPORT_PB,		//RB7, AN2
	_IOPORT_PB,		//RB6, AN3
	_IOPORT_PB,		//RB5, AN4
	_IOPORT_PB,		//RB4, AN5
	_IOPORT_PB,		//RB3, AN6
	_IOPORT_PB,		//RB2, AN7
	
	_IOPORT_PA,		//RA10, DIO14
	_IOPORT_PA,		//RA15, DIO15
	_IOPORT_PA,		//RA14, DIO16
	_IOPORT_PB,		//RB14, DIO17
	_IOPORT_PF,		//RF5, DIO18
	_IOPORT_PF,		//RF4, DIO19
	_IOPORT_PA,		//RA7, DIO20
	_IOPORT_PA,		//RA6, DIO21
	_IOPORT_PB,		//RB0, DIO22
	_IOPORT_PD,		//RD15, DIO23
	
	_IOPORT_PD,		//RD14, DIO24
	_IOPORT_PA,		//RA2, DIO25
	_IOPORT_PA,		//RA3, DIO26
	_IOPORT_PG,		//RG12, DIO27
	_IOPORT_PG,		//RG13, DIO28
	_IOPORT_PC,		//RC14, DIO29
	_IOPORT_PC,		//RC4, DIO30
	
	_IOPORT_PD,		//RD0, DIO31
	_IOPORT_PD,		//RD10, DIO32
	_IOPORT_PD,		//RD12, DIO33
	_IOPORT_PA,		//RA4, DIO34
	_IOPORT_PC,		//RC3, DIO35
	_IOPORT_PC,		//RC2, DIO36
	_IOPORT_PC,		//RC1, DIO37
	
	_IOPORT_PE,		//RE9, DIO38
	_IOPORT_PD,		//RD12, DIO39
	_IOPORT_PB,		//RB1, DIO40
	_IOPORT_PF,		//RF12, DIO41
	_IOPORT_PF,		//RF13, DIO42
	
	
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {
	_BV( 0 ), 	// inexisting 0
	
	_BV( 2 ),	//RF2, DIO0
	_BV( 8 ),	//RF8, DIO1
	
	_BV( 0 ),	//RE0, DIO2
	_BV( 1 ),	//RE1, DIO3
	_BV( 2 ),	//RE2, DIO4
	_BV( 3 ),	//RE3, DIO5
	_BV( 4 ),	//RE4, DIO7
	_BV( 5 ),	//RE5, DIO9
	_BV( 6 ),	//RE6, DIO11
	_BV( 7 ),	//RE7, DIO13
	
	_BV( 1 ),	//RD1, DIO6
	_BV( 2 ),	//RD2, DIO8
	_BV( 3 ),	//RD3, DIO10
	_BV( 4 ),	//RD4, DIO12
	
	_BV( 9 ),	//RB9, AN0
	_BV( 8 ),	//RB8, AN1
	_BV( 7 ), 	//RB7, AN2
	_BV( 6 ),	//RB6, AN3
	_BV( 5 ),	//RB5, AN4
	_BV( 4 ),	//RB4, AN5
	_BV( 3 ),	//RB3, AN6
	_BV( 2 ),	//RB2, AN7
	
	_BV(10),	//RA10, DIO14
	_BV(15),		//RA15, DIO15
	_BV(14),		//RA14, DIO16
	_BV(14),		//RB14, DIO17
	_BV(5),		//RF5, DIO18
	_BV(4),		//RF4, DIO19
	_BV(7),		//RA7, DIO20
	_BV(6),		//RA6, DIO21
	_BV(0),		//RB0, DIO22
	_BV(15),		//RD15, DIO23
	
	_BV(14),		//RD14, DIO24
	_BV(2),		//RA2, DIO25
	_BV(3),		//RA3, DIO26
	_BV(12),		//RG12, DIO27
	_BV(13),		//RG13, DIO28
	_BV(14),		//RC14, DIO29
	_BV(4),		//RC4, DIO30
	
	_BV(0),		//RD0, DIO31
	_BV(10),		//RD10, DIO32
	_BV(12),		//RD12, DIO33
	_BV(4),		//RA4, DIO34
	_BV(3),		//RC3, DIO35
	_BV(2),		//RC2, DIO36
	_BV(1),		//RC1, DIO37
	
	_BV(9),		//RE9, DIO38
	_BV(12),		//RD12, DIO39
	_BV(1),		//RB1, DIO40
	_BV(12),		//RF12, DIO41
	_BV(13),		//RF13, DIO42
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t	digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER, 	// inexisting 0
	
	NOT_ON_TIMER, 	// RF2, DIO0
	NOT_ON_TIMER, 	// RF8, DIO1
	
	NOT_ON_TIMER, 	// RE0, DIO2 
	NOT_ON_TIMER,  // RE1, DIO3
	NOT_ON_TIMER,  // RE2, DIO4
	NOT_ON_TIMER,  // RE3, DIO5
	NOT_ON_TIMER,	//RE4, DIO7	
	NOT_ON_TIMER,	//RE5, DIO9
	NOT_ON_TIMER,	//RE6, DIO11
	NOT_ON_TIMER,	//RE7, DIO13
	
	_TIMER_OC2,		//RD1, DIO6/PWM1
	_TIMER_OC3,		//RD2, DIO8/PWM2
	_TIMER_OC4,		//RD3, DIO10/PWM3
	_TIMER_OC5,		//RD4, DIO12/PWM4
	
	NOT_ON_TIMER,	//RB9, AN0
	NOT_ON_TIMER,	//RB8, AN1
	NOT_ON_TIMER,	//RB7, AN2
	NOT_ON_TIMER,	//RB6, AN3
	NOT_ON_TIMER,	//RB5, AN4
	NOT_ON_TIMER,	//RB4, AN5
	NOT_ON_TIMER,	//RB3, AN6
	NOT_ON_TIMER,	//RB2, AN7
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
//#if defined(_NOT_USED_)
const uint8_t digital_pin_to_analog_PGM[] = {
	NOT_ANALOG_PIN, 	// inexisting 0
	
	NOT_ANALOG_PIN, 	//RF2, DIO0
	NOT_ANALOG_PIN,		//RF8, DIO1
	
	NOT_ANALOG_PIN, 	//RE0, DIO2 
	NOT_ANALOG_PIN, 	//RE1, DIO3
	NOT_ANALOG_PIN, 	//RE2, DIO4
	NOT_ANALOG_PIN,		//RE3, DIO5
	NOT_ANALOG_PIN,		//RE4, DIO7	
	NOT_ANALOG_PIN,		//RE5, DIO9
	NOT_ANALOG_PIN,		//RE6, DIO11
	NOT_ANALOG_PIN,		//RE7, DIO13
	
	NOT_ANALOG_PIN,		//RD1, DIO6/PWM1
	NOT_ANALOG_PIN,		//RD2, DIO8/PWM2
	NOT_ANALOG_PIN,		//RD3, DIO10/PWM3
	NOT_ANALOG_PIN,		//RD4, DIO12/PWM4
	
	_BOARD_AN9,		//RB9, AN0
	_BOARD_AN8,		//RB8, AN1
	_BOARD_AN7,		//RB7, AN2
	_BOARD_AN6,		//RB6, AN3
	_BOARD_AN5,		//RB5, AN4
	_BOARD_AN4,		//RB4, AN5
	_BOARD_AN3,		//RB3, AN6
	_BOARD_AN2,		//RB2, AN7
	
};
//#endif

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
** In the default case, where there is a one-to-one mapping, this
** table isn't needed as the analogInPinToChannel() macro is defined
** to provide the mapping.
*/
//#if defined(_NOT_USED_)
const uint8_t analog_pin_to_channel_PGM[] = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
};
//#endif

/* ------------------------------------------------------------ */
/*		Include Files for Board Customization Functions			*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Board Customization Functions					*/
/* ------------------------------------------------------------ */
/*																*/
/* The following can be used to customize the behavior of some	*/
/* of the core API functions. These provide hooks that can be	*/
/* used to extend or replace the default behavior of the core	*/
/* functions. To use one of these functions, add the desired	*/
/* code to the function skeleton below and then set the value	*/
/* of the appropriate compile switch above to 1. This will		*/
/* cause the hook function to be compiled into the build and	*/
/* to cause the code to call the hook function to be compiled	*/
/* into the appropriate core function.							*/
/*																*/
/* ------------------------------------------------------------ */
/***	_board_init
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function is called from the core init() function.
**		This can be used to perform any board specific init
**		that needs to be done when the processor comes out of
**		reset and before the user sketch is run.
*/
#if	(OPT_BOARD_INIT != 0)

void _board_init(void) {

	/*	Turn off Secondary oscillator so pins can be used as GPIO
	*/
	OSCCONCLR	=	_OSCCON_SOSCEN_MASK;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_pinMode
**
**	Parameters:
**		pin		- digital pin number to configure
**		mode	- mode to which the pin should be configured
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the pinMode
**		function. It can perform any special processing needed
**		when setting the pin mode. If this function returns zero,
**		control will pass through the normal pinMode code. If
**		it returns a non-zero value the normal pinMode code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_pinMode(uint8_t pin, uint8_t mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_getPinMode
**
**	Parameters:
**		pin		- digital pin number
**		mode	- pointer to variable to receive mode value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the getPinMode
**		function. It can perform any special processing needed
**		when getting the pin mode. If this function returns zero,
**		control will pass through the normal getPinMode code. If
**		it returns a non-zero value the normal getPinMode code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_getPinMode(uint8_t pin, uint8_t * mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_digitalWrite
**
**	Parameters:
**		pin		- digital pin number
**		val		- value to write to the pin
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the digitalWrite
**		function. It can perform any special processing needed
**		in writing to the pin. If this function returns zero,
**		control will pass through the normal digitalWrite code. If
**		it returns a non-zero value the normal digitalWrite code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_digitalWrite(uint8_t pin, uint8_t val) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_digitalRead
**
**	Parameters:
**		pin		- digital pin number
**		val		- pointer to variable to receive pin value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the digitalRead
**		function. It can perform any special processing needed
**		in reading from the pin. If this function returns zero,
**		control will pass through the normal digitalRead code. If
**		it returns a non-zero value the normal digitalRead code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_digitalRead(uint8_t pin, uint8_t * val) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogRead
**
**	Parameters:
**		pin		- analog channel number
**		val		- pointer to variable to receive analog value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogRead
**		function. It can perform any special processing needed
**		in reading from the pin. If this function returns zero,
**		control will pass through the normal analogRead code. If
**		it returns a non-zero value the normal analogRead code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_READ != 0)

int	_board_analogRead(uint8_t pin, int * val) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogReference
**
**	Parameters:
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogReference
**		function. It can perform any special processing needed
**		to set the reference voltage. If this function returns zero,
**		control will pass through the normal analogReference code. If
**		it returns a non-zero value the normal analogReference code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_READ != 0)

int	_board_analogReference(uint8_t mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogWrite
**
**	Parameters:
**		pin		- pin number
**		val		- analog value to write
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogWrite
**		function. It can perform any special processing needed
**		in writing to the pin. If this function returns zero,
**		control will pass through the normal analogWrite code. If
**		it returns a non-zero value the normal analogWrite code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_WRITE != 0)

int	_board_analogWrite(uint8_t pin, int val) {

	return 0;

}

#endif

#endif // OPT_BOARD_DATA

/* ------------------------------------------------------------ */

#endif	// BOARD_DATA_C

/************************************************************************/
