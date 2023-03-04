/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 11/10/2020                                    */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"

void CAN1_voidInit(void){
	CLR_BIT(CAN1 -> MCR , 1); // Exit sleep mode
	SET_BIT(CAN1 -> MCR , 0); // To enter init mode
	#if TTC_MODE == TTC_DISABLE
		CLR_BIT(CAN1 -> MCR , 7);
    #elif TTC_MODE == TTC_ENABLE
		SET_BIT(CAN1 -> MCR , 7);
	#endif
	#if ABOM_MODE == ABOM_DISABLE
		CLR_BIT(CAN1 -> MCR , 6);
    #elif ABOM_MODE == ABOM_ENABLE
		SET_BIT(CAN1 -> MCR , 6);
	#endif
	#if AWUM_MODE == AWUM_DISABLE
		CLR_BIT(CAN1 -> MCR , 5);
    #elif AWUM_MODE == AWUM_ENABLE
		SET_BIT(CAN1 -> MCR , 5);
	#endif
	#if NART_MODE == NART_DISABLE
		CLR_BIT(CAN1 -> MCR , 4);
    #elif NART_MODE == NART_ENABLE
		SET_BIT(CAN1 -> MCR , 4);
	#endif
	#if RFLM_MODE == RFLM_DISABLE
		CLR_BIT(CAN1 -> MCR , 3);
    #elif RFLM_MODE == RFLM_ENABLE
		SET_BIT(CAN1 -> MCR , 3);
	#endif
	#if TXFP_MODE == TXFP_DISABLE
		CLR_BIT(CAN1 -> MCR , 2);
    #elif TXFP_MODE == TXFP_ENABLE
		SET_BIT(CAN1 -> MCR , 2);
	#endif	
	
	CAN1 -> BTR = 0x00060004; /* BaudRate = 1 Mbps , BRP[9:0] = 4 , TS1[3:0] = 6 , TS2 [2:0] = 0 , SJW [1:0] = 0
								 Tq   = (BRP[9:0]+1)*Tpclk = 0.111 us
								 Tbs1 = Tq*(TS1[3:0]+1)    = 0.777 us
								 Tbs2 = Tq*(TS2[2:0]+1)    = 0.111 us
								 NBT  = 1*Tq+Tbs1+Tbs2     = 0.999 us
								 BR   = 1/NBT 			   = 1     Mbps 		*/
	
	CLR_BIT(CAN1 -> MCR , 0); // Out init mode & enter normal mode
	
}
void CAN1_voidTransmit(u32 Copy_u32ID , u32 Copy_u32LowData , u32 Copy_u32HighData){
	if ((GET_BIT(CAN1 -> TSR , 26)) == 1){ 	// Choose mailbox 0
		SET_BIT(CAN1 -> TI0R , 0);			// To request the transmission
		CLR_BIT(CAN1 -> TI0R , 2); 			// Standard ID
		CLR_BIT(CAN1 -> TI0R , 1);      	// Data Frame
		CAN1 -> TDT0R = 0x00000001; 		// DLC = 1 Bytes
		CAN1 -> TI0R  = (Copy_u32ID << 21); // Put ID in STID[10:0]
		CAN1 -> TDL0R = Copy_u32LowData;
		CAN1 -> TDH0R = Copy_u32HighData;
	}
	else if ((GET_BIT(CAN1 -> TSR , 27)) == 1){ // Choose mailbox 1
		SET_BIT(CAN1 -> TI1R , 0);
		CLR_BIT(CAN1 -> TI1R , 2); 			
		CLR_BIT(CAN1 -> TI1R , 1);      	
		CAN1 -> TDT1R = 0x00000001; 		
		CAN1 -> TI1R  = (Copy_u32ID << 21); 
		CAN1 -> TDL1R = Copy_u32LowData;
		CAN1 -> TDH1R = Copy_u32HighData;
	}
	else if ((GET_BIT(CAN1 -> TSR , 28)) == 1){ // Choose mailbox 2
		SET_BIT(CAN1 -> TI2R , 0);
		CLR_BIT(CAN1 -> TI2R , 2); 			
		CLR_BIT(CAN1 -> TI2R , 1);      	
		CAN1 -> TDT2R = 0x00000001; 		
		CAN1 -> TI2R  = (Copy_u32ID << 21); 
		CAN1 -> TDL2R = Copy_u32LowData;
		CAN1 -> TDH2R = Copy_u32HighData;
	}
}
u32 CAN1_voidReceive (void){
	u32 Local_u32Msg = 0;
	if ((GET_BIT(CAN1 -> RF0R , 3)) != 1){    // Choose FIFO 0
		SET_BIT(CAN1 -> FMR , 0); 		      // Init mode of the filters
		CAN1 -> FM1R  = 0x0FFFFFFF;			  // ID List Mode
		CAN1 -> FS1R  = 0x0FFFFFFF;			  // Single 32_Bit Filter
		CAN1 -> FFA1R = 0x00000000;			  // Filters assigned to FIFO 0
		CAN1 -> FA1R  = 0x00000001;			  // Only first filter is active
		CAN1 -> FXR[0] = ((CAN1 -> RI0R)<<21);// Put ID in Filter 0
		CAN1 -> FXR[1] = ((CAN1 -> RI0R)<<21);// Put ID in Filter 0
		Local_u32Msg = CAN1 -> RDL0R;		  // Store recieved data
	} 
	else{									  // Choose FIFO 1
		SET_BIT(CAN1 -> FMR , 0); 		    
		CAN1 -> FM1R  = 0x0FFFFFFF;			
		CAN1 -> FS1R  = 0x0FFFFFFF;			
        CAN1 -> FFA1R = 0x0FFFFFFF;			  // Filters assigned to FIFO 1
        CAN1 -> FA1R  = 0x00000001;			
        CAN1 -> FXR[0] = ((CAN1 -> RI1R)<<21);
        CAN1 -> FXR[1] = ((CAN1 -> RI1R)<<21);
		Local_u32Msg = CAN1 -> RDL1R;
	}
	return (Local_u32Msg);
}
u32 CAN1_voidCheckID(u32 Copy_u32ID){
	if ((GET_BIT(CAN1 -> RF0R , 3)) != 1){ 
		if (((CAN1 -> RI0R)<<21) == Copy_u32ID){
			return ((CAN1 -> RI0R)<<21);
		}
		else {
			return ((CAN1 -> RI0R)<<21);
		}
	}
	else{
		if (((CAN1 -> RI1R)<<21) == Copy_u32ID){
			return ((CAN1 -> RI1R)<<21);
		}
		else {
			return ((CAN1 -> RI1R)<<21);
		}
	}
}