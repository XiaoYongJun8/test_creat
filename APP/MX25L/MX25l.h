#ifndef  _MX25L_H_
#define  _MX25L_H_

#include "stm32f10x.h"
#include "includes.h"







#define    secop(X)    ((X)*4096)  
#define        SAVEPRODUCTKIND                  secop(99)               //保存产品个数的扇区
#define        SAVEPRODUCTNAME                  secop(100)              //保存产品名称的扇区
#define        SAVEPRODUCTFAC                   secop(97)              //保存产品的系数的扇区
#define        SAVEBOLTPOS                      secop(121)              //记录螺栓位置表的位置
#define	Sector	  0x20
#define	Block	    0xD8
#define	Chip	    0xC7


void SPI1_Init(void);
void MX25L6406_Init(void);
void MX25L6406_Write_EN(void);
void MX25L6406_Read_status(void);
void MX25L6406_Read(u8 *data,u32 addr,u32 NumByteToRead);
void MX25L6406_Write_Page(u8* pBuffer,u32 addr,u16 NumToWrite);
void MX25L6406_Write_Page_Nocheck(u8* pBuffer,u32 WriteAddr,u16 NumToWriteByte);
void MX25L6406_Erase_Sector(u32 addr);
void MX25L6406_Write(u8*pBuffer,u32 WriteAddr,u16 NumToWriteByte);


uint32_t  WreadNumFormFlash(uint32_t addr,uint32_t count,uint8_t readLen);
u32 MX25L6406_ReadU32(u32 addr);
void  MX25L6406_WriteU32(uint32_t addr,uint32_t num);
void  MX25L6406_WriteU32ARR(uint32_t*pData,uint32_t addr,uint32_t DataLen);
void  MX25L6406_ReadU32ARR(uint32_t*pData,uint32_t addr,uint32_t DataLen);

u16 MX25L6406_ReadU16(u32 addr);
void  MX25L6406_WriteU16(uint32_t addr,uint16_t num);


void TaskMemory(void* pData);






void numToStr(char*str,int num,int* count);
void WriteStrToFlash(uint8_t* pStr,int count);
void DoubleToStr(char*str,double num,int* count);


extern uint16_t uCcount60S;





#define   MX25L6406_CS_H        GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define   MX25L6406_CS_L        GPIO_ResetBits(GPIOA,GPIO_Pin_4)


















#endif



