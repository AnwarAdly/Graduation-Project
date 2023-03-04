/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/11/2020                                    */
/**********************************************************/

#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#define ADC1_STATUS			ADC_ENABLE

// Configurations of CR1
#define AWD_MODE			AWD_DISABLE
#define DISC_MODE			DISC_DISABLE
#define SCAN_MODE			SCAN_DISABLE
#define ADC_INT				EOC_INT_ENABLE

// Configurations of CR2
#define CONT_MODE			CONT_ENABLE
#define DMA_MODE			DMA_DISABLE
#define TEMP_SENSOR			TSVREFE_DISABLE
#define DATA_ALIGN			RIGHT_ALIGN

// Configurations of SMPR
#define ST_SELECTION		ST_1_5_CYCLES

// Configurations of SQR
#define SEQ_LENGTH			ONE_CONVERSION
#define SEQ_CHANNEL			ADC_CHANNEL0

#endif