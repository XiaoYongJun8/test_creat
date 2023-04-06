#ifndef _SysTick_H
#define _SysTick_H

#include "system.h"
#include "includes.h"
#include "rs485.h"








extern  void Sys_huiFu(uint8_t mode);
extern uint8_t OneMinuteFlag ;
extern uint16_t Seed ;
extern uint8_t AdcSignalFlag;
extern uint8_t BeginSaveFlag ;
extern double AdcGetPress ;
extern uint8_t uCcount1SMemory;
extern uint8_t MoterStart ;
extern uint32_t Ratio ;
extern uint8_t ERROR_HAND ;


void SysTick_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void RCC_Configuration(void);
void   TaskTime(void* pData);



#define    MaxSize     4


typedef struct{
	
	
	uint8_t   tail;
	uint8_t   head;
	SysMemoryPara  SysMemoryParaArr[3];
	
	
	
}QUEUE;

extern uint8_t     niujupress ;
extern QUEUE  queue;
void queue_push(SysMemoryPara data);
uint8_t queue_size(void);
void queue_reset(void);








#endif
