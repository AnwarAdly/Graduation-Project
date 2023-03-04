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

void light(void);
void temp(void);
void fuel (void);

void main (void) {
	// RCC Commands
	MRCC_VoidInit();															 			 //Enable RCC
	MRCC_VoidEnablePeripheralClock(APB2_BUS,GPIOA_RCC); //Enable GPIOA
	MRCC_VoidEnablePeripheralClock(APB2_BUS,GPIOB_RCC); //Enable GPIOB
	MRCC_VoidEnablePeripheralClock(APB2_BUS,ADC1_RCC  ); //Enable ADC1
	MRCC_VoidEnablePeripheralClock(APB1_BUS,CAN_RCC    ); //Enable CAN

	// GPIO Commands
	MGPIO_VoidSetPinDirection(GPIOA,PIN0,INPUT_ANLOG); 					  	    // LDR Pin
	MGPIO_VoidSetPinDirection(GPIOA,PIN1,INPUT_ANLOG); 					        // LM35 (Temp)  Pin
	MGPIO_VoidSetPinDirection(GPIOA,PIN2,INPUT_ANLOG); 						    // Fuel  Pin
	MGPIO_VoidSetPinDirection(GPIOA,PIN11,INPUT_FLOATING);  				    // CAN RX
	MGPIO_VoidSetPinDirection(GPIOA,PIN12,OUTPUT_SPEED_2MHZ_AFOD); // CAN TX

	// Peripherals Initializations
	STK_voidInit();
	ADC1_voidInit();
	CAN1_voidInit();

	while (1){
		light();
		temp();
		fuel();
	}
}

void light(void){
	u8 l=MGPIO_u8GetPinValue(GPIOA,PIN0);
	u16 data=0;
	u32 MsgID=1;
	if(l==LOW){
		STK_voidSetBusyWait(100);
	}
	if(l==HIGH){   // DARK
		ADC1_voidStartConv();
		data=ADC1_u16GetData();
		CAN1_voidTransmit(MsgID,data,0);
		STK_voidSetBusyWait(100);
	}
}

void temp (void){
	u8 t=MGPIO_u8GetPinValue(GPIOA,PIN1);
	u16 data=0;
	u32 MsgID=2;
	if((t>10)&&(t<60)){
		STK_voidSetBusyWait(100);
	}
	if((t>60)&&(t<100)){
		ADC1_voidStartConv();
		data=ADC1_u16GetData();
		CAN1_voidTransmit(MsgID,data,0);
		STK_voidSetBusyWait(100);
	}
}

void fuel (void){
	u16 f=MGPIO_u8GetPinValue(GPIOA,PIN2);
	u16 data=0;
	u32 MsgID=3;
	if((f>400)&&(f<550)){
		ADC1_voidStartConv();
		data=ADC1_u16GetData();
		CAN1_voidTransmit(MsgID,data,0);
		STK_voidSetBusyWait(1000);
	}
	if((f>50)&&(f<400)){
		ADC1_voidStartConv();
		data=ADC1_u16GetData();
		CAN1_voidTransmit(MsgID,data,0);
		STK_voidSetBusyWait(1000);
	}
	if((f>0)&&(f<50)){
		ADC1_voidStartConv();
		data=ADC1_u16GetData();
		CAN1_voidTransmit(MsgID,data,0);
		STK_voidSetBusyWait(1000);
	}
}


