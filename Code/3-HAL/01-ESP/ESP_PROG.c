/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/20/2020                                    */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_INTERFACE.h"
#include "STK_INTERFACE.h"
#include "ESP_INTERFACE.h"


u8 volatile Iterator = 0  ;
u8 volatile DataCome[200] ;

void MUSART_CallBack ( void ){

	/* Receive ESP Response */
	DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
	/* ------------------ */
	Iterator++;
	MUSART1_voidClearFlags();

}

void ESP_voidInit ( void ){

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
	MUSART1_voidSetCallBack( MUSART_CallBack );

	/* Sending AT Command To Check ESP Is Working Or Not  */
	MUSART1_voidSendString( (u8 *)"AT\r\n" );

	STK_voidSetBusyWait( 3000 );

	/* Clear ESP Buffer */
	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *)"AT+CWMODE=1\r\n" );
	STK_voidSetBusyWait( 3000 );

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *)"AT+CIPMODE=0\r\n" );
	STK_voidSetBusyWait( 3000 );

}

void ESP_voidConnectToWiFi ( u8 * SSID , u8 * Password ){

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *) "AT+CWJAP=\"" );
	MUSART1_voidSendString( (u8 *) SSID );
	MUSART1_voidSendString( (u8 *) "\",\"" );
	MUSART1_voidSendString( (u8 *) Password);
	MUSART1_voidSendString( (u8 *) "\"\r\n");
	STK_voidSetBusyWait( 8000 );

}


void ESP_voidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port ){

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	MUSART1_voidSendString( (u8 *) Copy_u8Domain );
	MUSART1_voidSendString( (u8 *) "\"," );
	MUSART1_voidSendString( (u8 *) Copy_u8Port );
	MUSART1_voidSendString( (u8 *) "\r\n" );
	STK_voidSetBusyWait( 2000 );

}

void ESP_voidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ){

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *) "AT+CIPSEND=" );
	MUSART1_voidSendString( (u8 *) Copy_u8Length );
	MUSART1_voidSendString( (u8 *) "\r\n" );
	STK_voidSetBusyWait( 4000 );

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *) "GET /update?api_key=" );
	MUSART1_voidSendString( (u8 *) Copy_u8Key );
	MUSART1_voidSendString( (u8 *) "&field1=" );
	MUSART1_voidSendString( (u8 *) Copy_u8Data );
	MUSART1_voidSendString( (u8 *) "\r\n" );
	STK_voidSetBusyWait( 20000 );

}

u8   ESP_u8ReceiveHttpReq( u8 * Copy_u8ChannelID , u8 * Copy_u8Length ){

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *) "AT+CIPSEND=" );
	MUSART1_voidSendString( (u8 *) Copy_u8Length );
	MUSART1_voidSendString( (u8 *) "\r\n" );
	STK_voidSetBusyWait( 4000 );

	ESP_voidClearBuffer();

	MUSART1_voidSendString( (u8 *) "GET http://" );
	MUSART1_voidSendString( (u8 *) Copy_u8ChannelID );
	MUSART1_voidSendString( (u8 *) "/value.txt\r\n" );
	STK_voidSetBusyWait( 20000 );

	ESP_voidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/
	return  DataCome[82] ;

}

void ESP_voidClearBuffer ( void ){

	u8 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 150 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}
