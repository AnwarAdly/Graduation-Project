/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/11/2020                                    */
/**********************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

// Enabling ADC
#define ADC_DISABLE    			0 
#define ADC_ENABLE     			1   

// Enabling AWD Mode
#define AWD_DISABLE    			0 
#define AWD_ENABLE     			1   

// Enabling DISC Mode
#define DISC_DISABLE    		0 
#define DISC_ENABLE     		1   

// Enabling CONT Mode
#define CONT_DISABLE    		0 // Single    Conversion Mode 
#define CONT_ENABLE     		1 // Continous Conversion Mode  

// ADC Interrupts
#define INT_DISABLE             0
#define JEOC_INT_ENABLE         1 // Injected channels interrupt
#define AWD_INT_ENABLE          3 // Analog Watch Dog  interrupt
#define EOC_INT_ENABLE          5 // End Of Conversion interrupt

// ADC DMA
#define DMA_DISABLE    			0 
#define DMA_ENABLE     			1  

// Scan Mode
#define SCAN_DISABLE    		0 
#define SCAN_ENABLE     		1  

// Temp Sensor and Ref. voltage
#define TSVREFE_DISABLE    		0 
#define TSVREFE_ENABLE     		1  

// Data Alignment
#define RIGHT_ALIGN				0
#define LEFT_ALIGN				1

// Sample Time Selection
#define ST_1_5_CYCLES			0b000 // 1.5 Cycles
#define ST_7_5_CYCLES			0b001 // 7.5 Cycles
#define ST_13_5_CYCLES			0b010
#define ST_28_5_CYCLES			0b011
#define ST_41_5_CYCLES			0b100
#define ST_55_5_CYCLES			0b101
#define ST_71_5_CYCLES			0b110
#define ST_239_5_CYCLES			0b111

// Channels 
#define ADC_CHANNEL0			0
#define ADC_CHANNEL1			1
#define ADC_CHANNEL2			2
#define ADC_CHANNEL3			3
#define ADC_CHANNEL4			4
#define ADC_CHANNEL5			5
#define ADC_CHANNEL6			6
#define ADC_CHANNEL7			7
#define ADC_CHANNEL8			8
#define ADC_CHANNEL9			9
#define ADC_CHANNEL10			10
#define ADC_CHANNEL11			11
#define ADC_CHANNEL12			12
#define ADC_CHANNEL13			13
#define ADC_CHANNEL14			14
#define ADC_CHANNEL15			15
#define ADC_CHANNEL16			16
#define ADC_CHANNEL17			17

// Sequence Length
#define  ONE_CONVERSION			0b0000
#define  TWO_CONVERSION         0b0001
#define  THREE_CONVERSION       0b0010
#define  FOUR_CONVERSION        0b0011
#define  FIVE_CONVERSION        0b0100
#define  SIX_CONVERSION         0b0101
#define  SEVEN_CONVERSION       0b0110
#define  EIGHT_CONVERSION       0b0111
#define  NINE_CONVERSION	    0b1000
#define  TEN_CONVERSION			0b1001
#define  ELEVEN_CONVERSION      0b1010
#define  TWELVE_CONVERSION      0b1011
#define  THIRTEEN_CONVERSION    0b1100
#define  FOURTENN_CONVERSION    0b1101
#define  FIFTEEN_CONVERSION     0b1110
#define  SIXTEEN_CONVERSION     0b1111

// Functions Prototypes
void ADC1_voidInit(void);
void ADC1_voidStartConv(void);
u16  ADC1_u16GetData(void);
void ADC1_voidSetThresholds(u16 Copy_u16LowThreshold, u16 Copy_u16HighThreshold);
void ADC1_SetAWDCallBack(void (*CallBack) (void));
void ADC1_SetEOCCallBack(void (*CallBack) (void));

#endif