/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/20/2020                                    */
/**********************************************************/

#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

void ESP_voidInit            ( void                                                    ) ;
void ESP_voidConnectToWiFi   ( u8 * SSID , u8 * Password                               ) ;
void ESP_voidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port                   ) ;
void ESP_voidSendHttpReq     ( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ) ;
u8   ESP_u8ReceiveHttpReq    ( u8 * Copy_u8ChannelID , u8 * Copy_u8Length              ) ;
void ESP_voidClearBuffer     ( void                                                    ) ;

#endif 
