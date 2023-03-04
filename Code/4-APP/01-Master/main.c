/**********************************************************/
/* Author  : Anwar Ahmad                              					    */
/* Version : 01                                          								 */
/* Date    : 10/05/2021                                 							 */
/**********************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ERROR_STATUS.h"

#include"RCC_INTERFACE.h"
#include"GPIO_INTERFACE.h"
#include"STK_interface.h"
#include"ADC_interface.h"
#include"LCD_interface.h"
#include"CAN_interface.h"
#include"ESP_interface.h"
#include"FPEC_interface.h"
#include"USART_interface.h"

// BOOTLOADER Configurations
/*
void Parser_voidParseRecord(u8* Copy_u8BufData);
volatile u8  RecBuffer[100]   ;
volatile u8  RecCounter    = 0;
volatile u8  TimeOutFlag   = 0;
volatile u16 TimerCounter  = 0;
volatile u8  BLWriteReq    = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void){
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}
*/

#define LIGHT_ID         1
#define TEMP_ID  	      2
#define FUEL_ID  		  3
#define OBSTACLE_ID 4

void LED_ON (void){
	MGPIO_VoidSetPinValue(GPIOA,PIN0,HIGH);
}
void LED_OFF (void){
	MGPIO_VoidSetPinValue(GPIOA,PIN0,LOW);
}

void ALARM_ON (void){
	MGPIO_VoidSetPinValue(GPIOA,PIN1,HIGH);
}
void ALARM_OFF (void){
	MGPIO_VoidSetPinValue(GPIOA,PIN1,LOW);
}

void light(void);
void temp(void);
void fuel (void);
void obstacle(void);

void main (void) {
	// RCC Commands
	MRCC_VoidInit();															 			   //Enable RCC
	MRCC_VoidEnablePeripheralClock(APB2_BUS,GPIOA_RCC);   //Enable GPIOA
	MRCC_VoidEnablePeripheralClock(APB2_BUS,GPIOB_RCC);   //Enable GPIOB
	MRCC_VoidEnablePeripheralClock(APB2_BUS,ADC1_RCC  );   //Enable ADC1
	MRCC_VoidEnablePeripheralClock(APB2_BUS,USART1_RCC); //Enable USART1
	MRCC_VoidEnablePeripheralClock(APB1_BUS,CAN_RCC    );   //Enable CAN
	MRCC_VoidEnablePeripheralClock(AHB_BUS,FPEC_RCC    );   //Enable FPEC

	// GPIO Commands
	MGPIO_VoidSetPinDirection(GPIOA,PIN0,OUTPUT_SPEED_2MHZ_PP); 	      // LDR LED
	MGPIO_VoidSetPinDirection(GPIOA,PIN1,OUTPUT_SPEED_2MHZ_PP);          // ALARM
	MGPIO_VoidSetPinDirection(GPIOA,PIN11,INPUT_FLOATING);					     // CAN RX
	MGPIO_VoidSetPinDirection(GPIOA,PIN12,OUTPUT_SPEED_2MHZ_AFOD);  // CAN TX
	MGPIO_VoidSetPinDirection(GPIOA,PIN8,OUTPUT_SPEED_10MHZ_AFPP);   // ESP RST
	MGPIO_VoidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_10MHZ_AFPP);   // TX with ESP RX
	MGPIO_VoidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);  					// RX with ESP TX

	// Peripherals Initializations
	STK_voidInit();
	HLCD_voidInit();
	ADC1_voidInit();
	CAN1_voidInit();
	MUSART_voidInit();
	ESP_voidInit();

	// LCD Commands
	HLCD_voidSendCommand(SET_CURSOR_LOCATION_FIRST_LINE);
	HLCD_voidDisplayString(" We CAN FOTA ");
	STK_voidSetBusyWait(1000);
	HLCD_voidClearScreen();
	STK_voidSetBusyWait(100);
	HLCD_voidSendCommand(SET_CURSOR_LOCATION_FIRST_LINE);
	HLCD_voidDisplayString("Vehicle Control");
	STK_voidSetBusyWait(1000);
	HLCD_voidSendCommand(SET_CURSOR_LOCATION_SECOND_LINE);
	HLCD_voidDisplayString("System");
	STK_voidSetBusyWait(1000);
	HLCD_voidClearScreen();
	STK_voidSetBusyWait(100);
	HLCD_voidSendCommand(SET_CURSOR_LOCATION_FIRST_LINE);
	HLCD_voidDisplayString("Implementation");
	STK_voidSetBusyWait(1000);
	HLCD_voidSendCommand(SET_CURSOR_LOCATION_SECOND_LINE);
	HLCD_voidDisplayString("Using CAN Bus");
	STK_voidSetBusyWait(1000);
	HLCD_voidClearScreen();
	STK_voidSetBusyWait(100);

	// BOTLOADER TASKS
/*
	u8 Local_u8RecStatus;
	STK_voidSetIntervalSingle(15000000,func);
	ESP_voidConnectToWiFi((u8 *)"The flower" , (u8 *)"nona909090");
	while(TimeOutFlag == 0){
		ESP_voidConnectToSrvTcp((u8 *)"162.253.155.226" , (u8 *)"80");
		Local_u8RecStatus = MUSART1_PtrReadString( &(RecBuffer[RecCounter]) );
		if (Local_u8RecStatus == 1){
			STK_voidStopInterval();
			RecBuffer[RecCounter]=ESP_u8ReceiveHttpReq((u8 *)"yrabiot3.freevar.com" , (u8 *)"50");
			if(RecBuffer[RecCounter] == '\n'){
				if (BLWriteReq == 1){
					FPEC_voidEraseAppArea();
					BLWriteReq = 0;
				}
				Parser_voidParseRecord(RecBuffer);
				MUSART1_voidSendString("ok");
				RecCounter = 0;
			}
			else{
				RecCounter ++ ;
			}
			STK_voidSetIntervalSingle(15000000,func);
		}

	}
*/
	while (1){
		if (CAN1_voidCheckID(LIGHT_ID)==1){
			light();
		}
		else if (CAN1_voidCheckID(TEMP_ID)==2){
			temp();
		}
		else if (CAN1_voidCheckID(FUEL_ID)==3){
			fuel();
		}
		else if (CAN1_voidCheckID(OBSTACLE_ID)==4){
			obstacle();
		}
		else {
			ALARM_OFF();
			STK_voidSetBusyWait(100);
		}
	}
}

void light(void){
	u16 data=0;
	if (CAN1_voidCheckID(LIGHT_ID)==1){
		data=CAN1_voidReceive();
		LED_ON();
		STK_voidSetBusyWait(1000);
		HLCD_voidSendCommand(SET_CURSOR_LOCATION_FIRST_LINE);
		HLCD_voidDisplayString("L=");
		HLCD_voidDisplayCharacter(data);
		STK_voidSetBusyWait(1000);
	}
	else {
		LED_OFF();
		STK_voidSetBusyWait(100);
	}
}
void temp(void){
	u16 data=0;
	if (CAN1_voidCheckID(TEMP_ID)==2){
		data=CAN1_voidReceive();
		ALARM_ON();
		STK_voidSetBusyWait(1000);
		HLCD_voidSendCommand(SET_CURSOR_LOCATION_FIRST_LINE | 0x08);
		HLCD_voidDisplayString("T=");
		HLCD_voidDisplayCharacter(data);
		STK_voidSetBusyWait(1000);
	}
	else {
		ALARM_OFF();
		STK_voidSetBusyWait(1000);
	}
}
void fuel (void){
	u16 data=0;
	if (CAN1_voidCheckID(FUEL_ID)==3){
		data=CAN1_voidReceive();
		if((data>400)&&(data<550)){
			HLCD_voidSendCommand(SET_CURSOR_LOCATION_SECOND_LINE);
			HLCD_voidDisplayString("FULL");
			STK_voidSetBusyWait(1000);
		}
		else if((data>100)&&(data<400)){
			HLCD_voidSendCommand(SET_CURSOR_LOCATION_SECOND_LINE);
			HLCD_voidDisplayString("LOW");
			STK_voidSetBusyWait(1000);
		}
		else if((data>0)&&(data<50)){
			ALARM_ON();
			HLCD_voidSendCommand(SET_CURSOR_LOCATION_SECOND_LINE);
			HLCD_voidDisplayString("EMPTY");
			STK_voidSetBusyWait(1000);
		}
	}
	else {
		ALARM_OFF();
		STK_voidSetBusyWait(1000);
	}
}
void obstacle(void){
	if (CAN1_voidCheckID(OBSTACLE_ID)==4){
		ALARM_ON();
		STK_voidSetBusyWait(1000);
		HLCD_voidSendCommand(SET_CURSOR_LOCATION_SECOND_LINE | 0x08);
		HLCD_voidDisplayString("!OBS!");
		STK_voidSetBusyWait(1000);
	}
	else {
		ALARM_OFF();
		STK_voidSetBusyWait(1000);
	}
}



