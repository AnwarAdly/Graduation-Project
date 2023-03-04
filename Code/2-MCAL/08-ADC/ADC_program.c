/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/11/2020                                    */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

void ADC1_voidInit(void){
	#if ADC1_STATUS == ADC_ENABLE
		ADC1 -> SR =0;
		SET_BIT(ADC1 -> CR2 , 0);
		
		#if AWD_MODE == AWD_DISABLE
			CLR_BIT(ADC1 -> CR1 , 23);
		#elif AWD_MODE == AWD_ENABLE	
			SET_BIT(ADC1 -> CR1 , 23);
		#endif
		#if DISC_MODE == DISC_DISABLE
			CLR_BIT(ADC1 -> CR1 , 11);
		#elif DISC_MODE == DISC_ENABLE	
			SET_BIT(ADC1 -> CR1 , 11);
		#endif	
		#if SCAN_MODE == SCAN_DISABLE
			CLR_BIT(ADC1 -> CR1 , 8);
		#elif SCAN_MODE == SCAN_ENABLE	
			SET_BIT(ADC1 -> CR1 , 8);
		#endif
		#if ADC_INT == INT_DISABLE
			CLR_BIT(ADC1 -> CR1 , 5); //  EOSIE
			CLR_BIT(ADC1 -> CR1 , 6); //  AWDIE
			CLR_BIT(ADC1 -> CR1 , 7); // JEOCIE
		#elif ADC_INT == EOC_INT_ENABLE
			SET_BIT(ADC1 -> CR1 , 5);			
		#elif ADC_INT == AWD_INT_ENABLE
			SET_BIT(ADC1 -> CR1 , 6);
		#elif ADC_INT == JEOC_INT_ENABLE
			SET_BIT(ADC1 -> CR1 , 7);
		#endif
		
		#if CONT_MODE == CONT_DISABLE
			CLR_BIT(ADC1 -> CR2 , 1);
		#elif CONT_MODE == CONT_ENABLE	
			SET_BIT(ADC1 -> CR2 , 1);
		#endif		
		#if DMA_MODE == DMA_DISABLE
			CLR_BIT(ADC1 -> CR2 , 8);
		#elif DMA_MODE == DMA_ENABLE	
			SET_BIT(ADC1 -> CR2 , 8);
		#endif
		#if TEMP_SENSOR == TSVREFE_DISABLE
			CLR_BIT(ADC1 -> CR2 , 23);
		#elif TEMP_SENSOR == TSVREFE_ENABLE	
			SET_BIT(ADC1 -> CR2 , 23);
		#endif	
		#if DATA_ALIGN == RIGHT_ALIGN
			CLR_BIT(ADC1 -> CR2 , 11);
		#elif DATA_ALIGN == LEFT_ALIGN	
			SET_BIT(ADC1 -> CR2 , 11);
		#endif
		
		#if ST_SELECTION == ST_1_5_CYCLES
			ADC1 -> SMPR[0] = 0x00000000;
			ADC1 -> SMPR[1] = 0x00000000;
		#elif ST_SELECTION == ST_7_5_CYCLES
			ADC1 -> SMPR[0] = 0x00249249;
			ADC1 -> SMPR[1] = 0x09249249;
		#elif ST_SELECTION == ST_13_5_CYCLES
			ADC1 -> SMPR[0] = 0x00492492;
			ADC1 -> SMPR[1] = 0x12492492;
		#elif ST_SELECTION == ST_28_5_CYCLES
			ADC1 -> SMPR[0] = 0x006DB6DB;
			ADC1 -> SMPR[1] = 0x1B6DB6DB;
		#elif ST_SELECTION == ST_41_5_CYCLES
			ADC1 -> SMPR[0] = 0x00924924;
			ADC1 -> SMPR[1] = 0x24924924;
		#elif ST_SELECTION == ST_55_5_CYCLES
			ADC1 -> SMPR[0] = 0x00B6DB6D;
			ADC1 -> SMPR[1] = 0x2DB6DB6D;
		#elif ST_SELECTION == ST_71_5_CYCLES
			ADC1 -> SMPR[0] = 0x00DB6DB6;
			ADC1 -> SMPR[1] = 0x36DB6DB6;
		#elif ST_SELECTION == ST_239_5_CYCLES
			ADC1 -> SMPR[0] = 0x00FFFFFF;
			ADC1 -> SMPR[1] = 0x3FFFFFFF;
		#endif
		
		#if SEQ_LENGTH == ONE_CONVERSION
			ADC1 -> SQR[0] = (ONE_CONVERSION>>20);
		#elif SEQ_LENGTH == TWO_CONVERSION
			ADC1 -> SQR[0] = (TWO_CONVERSION>>20);
		#elif SEQ_LENGTH == THREE_CONVERSION
			ADC1 -> SQR[0] = (THREE_CONVERSION>>20);
		#elif SEQ_LENGTH == FOUR_CONVERSION
			ADC1 -> SQR[0] = (FOUR_CONVERSION>>20);
		#elif SEQ_LENGTH == FIVE_CONVERSION
			ADC1 -> SQR[0] = (FIVE_CONVERSION>>20);
		#elif SEQ_LENGTH == SIX_CONVERSION
			ADC1 -> SQR[0] = (SIX_CONVERSION>>20);
		#elif SEQ_LENGTH == SEVEN_CONVERSION
			ADC1 -> SQR[0] = (SEVEN_CONVERSION>>20);
		#elif SEQ_LENGTH == EIGHT_CONVERSION
			ADC1 -> SQR[0] = (EIGHT_CONVERSION>>20);
		#elif SEQ_LENGTH == NINE_CONVERSION
			ADC1 -> SQR[0] = (NINE_CONVERSION>>20);
		#elif SEQ_LENGTH == TEN_CONVERSION
			ADC1 -> SQR[0] = (TEN_CONVERSION>>20);
		#elif SEQ_LENGTH == ELEVEN_CONVERSION
			ADC1 -> SQR[0] = (ELEVEN_CONVERSION>>20);
		#elif SEQ_LENGTH == TWELVE_CONVERSION
			ADC1 -> SQR[0] = (TWELVE_CONVERSION>>20);
		#elif SEQ_LENGTH == THIRTEEN_CONVERSION
			ADC1 -> SQR[0] = (THIRTEEN_CONVERSION>>20);
		#elif SEQ_LENGTH == FOURTENN_CONVERSION
			ADC1 -> SQR[0] = (FOURTENN_CONVERSION>>20);
		#elif SEQ_LENGTH == FIFTEEN_CONVERSION
			ADC1 -> SQR[0] = (FIFTEEN_CONVERSION>>20);
		#elif SEQ_LENGTH == SIXTEEN_CONVERSION
			ADC1 -> SQR[0] = (SIXTEEN_CONVERSION>>20);			
		#endif		
		
	#elif ADC1_STATUS == ADC_DISABLE
		CLR_BIT(ADC1 -> CR2 , 0);
	#endif
}
void ADC1_voidStartConv(void){
	SET_BIT (ADC1 -> CR2 , 17);  
	SET_BIT (ADC1 -> CR2 , 18);   
	SET_BIT (ADC1 -> CR2 , 19);   
	SET_BIT (ADC1 -> CR2 , 22); // SW START 
	while (GET_BIT(ADC1 -> SR , 1) == 0); // Wait till conversion completed
	CLR_BIT (ADC1 -> SR , 1); // Clear End Of Conv flag

}
u16 ADC1_u16GetData(void){
	u16 Local_u16Data=0;
	Local_u16Data = ADC1 -> DR;
	return Local_u16Data;
}
void ADC1_voidSetThresholds(u16 Copy_u16LowThreshold, u16 Copy_u16HighThreshold){
	ADC1 -> HTR = Copy_u16HighThreshold;
	ADC1 -> LTR = Copy_u16LowThreshold;
}
void ADC1_SetAWDCallBack(void (*CallBack) (void)){
	ADC1_voidAWDCallBack = CallBack;
}
void ADC1_SetEOCCallBack(void (*CallBack) (void)){
	ADC1_voidEOCCallBack = CallBack;
}

void ADC1_2_IRQHandler(void)
{
	if ((GET_BIT((ADC1 -> SR), 0)) == 1){
		CLR_BIT((ADC1 -> SR), 0);
		ADC1_voidAWDCallBack();
	}
	else if((GET_BIT((ADC1 -> SR), 1)) == 1){
		CLR_BIT((ADC1 -> SR), 1);
		ADC1_voidEOCCallBack();
	}
}