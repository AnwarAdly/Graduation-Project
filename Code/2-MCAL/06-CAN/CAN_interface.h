/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 11/10/2020                                    */
/**********************************************************/

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#define TTC_DISABLE			0 // Time Triggered Communication
#define TTC_ENABLE			1

#define ABOM_DISABLE		0 // Bus Off left on SW request 
#define ABOM_ENABLE			1 // Bus off left auto by HW

#define AWUM_DISABLE		0 // Sleep mode left on SW request 
#define AWUM_ENABLE			1 // Sleep mode left auto by HW

#define NART_DISABLE		0 // Auto retransmit 
#define NART_ENABLE			1 // Transmit only once

#define RFLM_DISABLE		0 // Receive FIFO Locked Mode 
#define RFLM_ENABLE			1 

#define TXFP_DISABLE		0 // Priority driven by ID
#define TXFP_ENABLE			1 // Priority driven by Request order

/* Function Prototypes  */
void CAN1_voidInit    (void);
void CAN1_voidTransmit(u32 Copy_u32ID , u32 Copy_u32LowData , u32 Copy_u32HighData);
u32  CAN1_voidReceive (void);
u32  CAN1_voidCheckID(u32 Copy_u32ID);

#endif