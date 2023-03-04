/******************************************************/
/* Author    : Asmaa Ahmed                            */
/* Date      : 18 jan 2021                            */
/* Version   : V01                                    */
/******************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stdlib.h"

#include "GPIO_interface.h"
#include "STK_interface.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void HLCD_voidInit(void){
	/* Configure the control pins(E,RS,RW) as output push pull with 2MHZ speed A8 -> A10*/
	MGPIO_VoidSetPinDirection  (ENABLE_PIN     ,OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VoidSetPinDirection  (REGISTER_SELECT,OUTPUT_SPEED_2MHZ_PP);
	#if (DATA_BITS_MODE == FOUR_BITS)
		#ifdef UPPER_PORT_PINS
			/* Configure the highest 4 pins as output push pull with 2MHZ speed  A4 ->A7*/
			MGPIO_VoidSetPinDirection  (DATA_PIN4 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN5 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN6 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN7 ,OUTPUT_SPEED_2MHZ_PP);
		#else
			/* Configure the lowest 4 pins as output push pull with 2MHZ speed A0 ->A3 */
			MGPIO_VoidSetPinDirection  (DATA_PIN0 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN1 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN2 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN3 ,OUTPUT_SPEED_2MHZ_PP);
	    #endif
	    HLCD_voidSendCommand(FOUR_BITS_DATA_MODE);        /* initialize LCD in 4-bit mode */
		HLCD_voidSendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == EIGHT_BITS)
		/* Configure the data pins as output push pull with 2MHZ speed */ 
			MGPIO_VoidSetPinDirection  (DATA_PIN0 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN1 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN2 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN3 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN4 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN5 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN6 ,OUTPUT_SPEED_2MHZ_PP);
			MGPIO_VoidSetPinDirection  (DATA_PIN7 ,OUTPUT_SPEED_2MHZ_PP);
			HLCD_voidSendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif
	HLCD_voidSendCommand(CURSOR_OFF); 	    /* cursor off */
	HLCD_voidSendCommand(CLEAR_COMMAND);	/* clear LCD at the beginning */
}

void HLCD_voidSendCommand(u8 command){
	MGPIO_VoidSetPinValue(REGISTER_SELECT , LOW);   /* Instruction Mode RS=0 */ 
	STK_voidSetBusyWait(50); 						/* delay for processing Tas = 50ns */
	MGPIO_VoidSetPinValue(ENABLE_PIN , HIGH); 		/* Enable LCD E=1  */
	STK_voidSetBusyWait(190); 						/* delay for processing Tpw - Tdws = 190ns */
	#if (DATA_BITS_MODE == FOUR_BITS)
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			GPIOA_ODR = (GPIOA_ODR & 0x0F) | (command & 0xF0); 
		#else
			GPIOA_ODR = (GPIOA_ODR & 0xF0) | ((command & 0xF0) >> 4);
		#endif
		STK_voidSetBusyWait(100);					 /* delay for processing Tdsw = 100ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , LOW);  	 /* disable LCD E=0 */
		STK_voidSetBusyWait(13); 					 /* delay for processing Th = 13ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , HIGH);	 /* Enable LCD E=1 */
		STK_voidSetBusyWait(190);					 /* delay for processing Tpw - Tdws = 190ns */
		/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			GPIOA_ODR = (GPIOA_ODR & 0x0F) | ((command & 0x0F) << 4);
		#else
			GPIOA_ODR = (GPIOA_ODR & 0xF0) | (command & 0x0F);
		#endif
		STK_voidSetBusyWait(100); 					 /* delay for processing Tdsw = 100ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , LOW);     /* disable LCD E=0 */
		STK_voidSetBusyWait(13);					 /* delay for processing Th = 13ns */
	#elif (DATA_BITS_MODE == EIGHT_BITS)
		GPIOA_ODR = command;						 /* out the required command to the data bus D0 --> D7 */
		STK_voidSetBusyWait(100);					 /* delay for processing Tdsw = 100ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , LOW);     /* disable LCD E=0 */
		STK_voidSetBusyWait(13);					 /* delay for processing Th = 13ns */
	#endif
}

void HLCD_voidDisplayCharacter(u8 data){
	MGPIO_VoidSetPinValue(REGISTER_SELECT , HIGH);           /* Instruction Mode RS=1 */ 
    STK_voidSetBusyWait(50);                                 /* delay for processing Tas = 50ns */
	MGPIO_VoidSetPinValue(ENABLE_PIN , HIGH);                /* Enable LCD E=1 */
    STK_voidSetBusyWait(190);                                /* delay for processing Tpw - Tdws = 190ns */
	#if (DATA_BITS_MODE == FOUR_BITS)
		/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			GPIOA_ODR = (GPIOA_ODR & 0x0F) | (data & 0xF0);
		#else
			GPIOA_ODR = (GPIOA_ODR & 0xF0) | ((data & 0xF0) >> 4);
		#endif
		STK_voidSetBusyWait(100);                                    /* delay for processing Tdsw = 100ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , LOW);          		     /* disable LCD E=0 */
		STK_voidSetBusyWait(13);                                     /* delay for processing Th = 13ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , HIGH);        			 /* Enable LCD E=1 A8 */
		STK_voidSetBusyWait(190);                                    /* delay for processing Tpw - Tdws = 190ns */
		/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			GPIOA_ODR = (GPIOA_ODR & 0x0F) | ((data & 0x0F) << 4);
		#else
			GPIOA_ODR = (GPIOA_ODR & 0xF0) | (data & 0x0F);
		#endif
		STK_voidSetBusyWait(100);                                    /* delay for processing Tdsw = 100ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , LOW);        		     /* disable LCD E=0 */
		STK_voidSetBusyWait(13);                                     /* delay for processing Th = 13ns */
	#elif (DATA_BITS_MODE == EIGHT_BITS)
		GPIOA_ODR = data;                                 			 /* out the required command to the data bus D0 --> D7 */
		STK_voidSetBusyWait(100);                                    /* delay for processing Tdsw = 100ns */
		MGPIO_VoidSetPinValue(ENABLE_PIN , LOW);           			 /* disable LCD E=0 */
		STK_voidSetBusyWait(13);                                     /* delay for processing Th = 13ns */
	#endif
}

void HLCD_voidDisplayString(const char *Str)
{
	u8 i = 0;
	while(Str[i] != '\0')
	{
		HLCD_voidDisplayCharacter(Str[i]);
		i++;
	}
	
}

void HLCD_voidGoToRowColumn(u8 row,u8 col)
{
	u8 Address=0;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
/*		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
*/
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000|Address */
	HLCD_voidSendCommand(Address | SET_CURSOR_LOCATION_FIRST_LINE); 
}



void HLCD_voidDisplayStringRowColumn(u8 row,u8 col,const char *Str)
{
	HLCD_voidGoToRowColumn(row,col); /* go to to the required LCD position */
	HLCD_voidDisplayString(Str);	 /* display the string */
}

void HLCD_voidIntgerToString(int data)

{
   char buff[16];                     /* String to hold the ascii result */
   /* converts int data type to string data type*/
   itoa(data,buff,10);                /* 10 for decimal */ 
   HLCD_voidDisplayString(buff);
}

void HLCD_voidClearScreen(void)
{
	HLCD_voidSendCommand(CLEAR_COMMAND); //clear display 
}
