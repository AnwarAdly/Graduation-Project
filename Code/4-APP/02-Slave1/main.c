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
#include"CAN_interface.h"

void obstacle(void);

void main (void) {
	// RCC Commands
	MRCC_VoidInit();															 			 //Enable RCC
	MRCC_VoidEnablePeripheralClock(APB2_BUS,GPIOA_RCC); //Enable GPIOA
	MRCC_VoidEnablePeripheralClock(APB2_BUS,GPIOB_RCC); //Enable GPIOB
	MRCC_VoidEnablePeripheralClock(APB2_BUS,ADC1_RCC  ); //Enable ADC1
	MRCC_VoidEnablePeripheralClock(APB1_BUS,CAN_RCC    ); //Enable CAN

	// GPIO Commands
	MGPIO_VoidSetPinDirection(GPIOA,PIN0,INPUT_ANLOG); 					 	    // IR Pin
	MGPIO_VoidSetPinDirection(GPIOA,PIN1,OUTPUT_SPEED_2MHZ_OD);       // Motor  Pin
	MGPIO_VoidSetPinDirection(GPIOA,PIN11,INPUT_FLOATING);					    // CAN RX
	MGPIO_VoidSetPinDirection(GPIOA,PIN12,OUTPUT_SPEED_2MHZ_AFOD); // CAN TX

	// Peripherals Initializations
	STK_voidInit();
	ADC1_voidInit();
	CAN1_voidInit();

	while (1){
		obstacle();
	}
}

void obstacle(void){
	u8 o=MGPIO_u8GetPinValue(GPIOA,PIN0);
	u16 data=0;
	u32 MsgID=4;
	if(o==LOW){
		MGPIO_VoidSetPinValue(GPIOA,PIN1,HIGH);
		STK_voidSetBusyWait(100);
	}
	if(o==HIGH){
		MGPIO_VoidSetPinValue(GPIOA,PIN1,LOW);
		ADC1_voidStartConv();
		data=ADC1_u16GetData();
		CAN1_voidTransmit(MsgID,data,0);
		STK_voidSetBusyWait(100);
	}
}

