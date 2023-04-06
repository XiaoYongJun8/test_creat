#ifndef  __CH375DRIV_H__
#define  __CH375DRIV_H__

#include "includes.h"


#include "stm32f10x.h"
#include "stdio.h"

void  CH374_Init( void );
void	mStopIfError( u8 iError );
void BeCommaStr(uint8_t*pDest,uint8_t*pSrc,uint8_t arrLen[],uint8_t count);
void formationStr(uint8_t* pSrc,uint8_t size,uint8_t len);
void StructToStr(char buf[],SysMemoryPara SysMemoryParaVar);
void WriteFile(void);
void TaskUsbControl(void* pvdata);

#define CH374_INT_WIRE    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define CH374_SPI_SCS_H   GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CH374_SPI_SCS_L   GPIO_ResetBits(GPIOB,GPIO_Pin_12)


#endif

