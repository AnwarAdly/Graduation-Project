/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 11/10/2020                                    */
/**********************************************************/

#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

/*  Register Definitions    */
typedef struct{
	volatile u32 MCR;
	volatile u32 MSR;
	volatile u32 TSR;
	volatile u32 RF0R;
	volatile u32 RF1R;
	volatile u32 IER;
	volatile u32 ESR;
	volatile u32 BTR;
	volatile u32 RESERVED1[64];
	volatile u32 TI0R;
	volatile u32 TDT0R;
	volatile u32 TDL0R;
	volatile u32 TDH0R;
	volatile u32 TI1R;
	volatile u32 TDT1R;
	volatile u32 TDL1R;
	volatile u32 TDH1R;
	volatile u32 TI2R;
	volatile u32 TDT2R;
	volatile u32 TDL2R;
	volatile u32 TDH2R;
	volatile u32 RI0R;
	volatile u32 RDT0R;
	volatile u32 RDL0R;
	volatile u32 RDH0R;
	volatile u32 RI1R;
	volatile u32 RDT1R;
	volatile u32 RDL1R;
	volatile u32 RDH1R;
	volatile u32 RESERVED2[12];
	volatile u32 FMR;
	volatile u32 FM1R;
	volatile u32 RESERVED3;
	volatile u32 FS1R;
	volatile u32 RESERVED4;
	volatile u32 FFA1R;
	volatile u32 RESERVED5;
	volatile u32 FA1R;
	volatile u32 RESERVED6[8];
	volatile u32 FXR[56];
}CAN_Type;
#define CAN1 ( ( volatile CAN_Type* ) 0x40006400 )
#define CAN2 ( ( volatile CAN_Type* ) 0x40006800 )

#endif 
