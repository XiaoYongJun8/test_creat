#ifndef _UART_H_
#define _UART_H_

#include "stm32f10x.h"
#include "stdio.h"


#define USART1_DR_Base  0x40013804
#define USART2_DR_Base  0x40004404
#define USART3_DR_Base  0x40004804


#ifndef UART1_BAUT_RATE_115200        
#define UART1_BAUT_RATE_115200         115200
#endif


#ifndef UART1_RX_BUFF_LENGTH
#define UART1_RX_BUFF_LENGTH         128
#endif
#define      UART_1RECV_BUFF_LENGTH              255      //串口1接收缓冲区的大小


















uint8_t UART1_Init(uint32_t bps);
uint8_t UART2_Init(uint32_t bps);
uint8_t UART3_Init(uint32_t bps);

uint8_t UART1Write(uint8_t *Data, uint16_t NByte);
void SendStrings(uint8_t *str);




void uart_init(void);

void  SendChar(uint8_t t);
void USART2_SendString(uint8_t* pStr,uint8_t size);
void  SendNU8(uint8_t *pData,uint16_t DataLen);
void SendNU16(uint16_t*pData,uint16_t DataLen);
void  SendNU32(uint32_t*pData,uint16_t DataLen);


#define ROUND_TO_UINT16(x)   ((uint16_t)(x)+0.5)>(x)? ((uint16_t)(x)):((uint16_t)(x)+1)   //四舍五入
#define ROUND_TO_UINT32(x)   ((uint32_t)(x)+0.5)>(x)? ((uint32_t)(x)):((uint32_t)(x)+1)   //四舍五入




/***************** 串口1接收错误的标志 ******************/
#define UART_NO_ERROR                  0
#define UART_TIMEOUT                   1
#define UART_MSG_TOO_BIG               2
#define UART_BUSY                      3



#define   SEND_DATA(P)   SendChar(P)
#define   TX_8(P)        SEND_DATA((P)&0xFF)   
#define   TX_8N(P,N)     SendNU8((P),N)
#define   TX_16(P)       TX_8((P)>>8);TX_8(P)
#define   TX_16N(P,N)    SendNU16((P),N) 
#define   TX_32(P)       TX_16((P)>>16);TX_16(P)
#define   TX_32N(P,N)     SendNU32((P),N)



#define BEGIN_CMD() TX_8(0XEE)            //帧头
#define END_CMD() TX_32(0XFFFCFFFF)       //帧尾










#endif


