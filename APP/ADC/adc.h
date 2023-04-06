#ifndef __ADC_H
#define __ADC_H	


#include "stm32f10x.h"

/*
16路ADC采样DMA传输
调用Adc_Init()函数初始化设备，ADC循环采样 
数据被DMA搬运到ADC_Value[ADC_CH_NUM]数组中
滤波后的数据在ADC_AfterFilter[ADC_CH_NUM]中
*/


#define   ADC_CH_NUM   6    //ADC通道数目 16个通道



extern u16 ADC_Value[ADC_CH_NUM];				 //ADC采样原始数据
extern u16 ADC_AfterFilter[ADC_CH_NUM];  //ADC采样数据滤波后的数据
extern float ADCGetPress[10];

void Adc_Init(void);										//ADC设备初始化
u16 ADC_Filter(uint8_t ADC_Channel, u8 times);

u32 ADC_GetPress(uint8_t ADC_Channel);
void  ADC_ShowPres(uint8_t ADC_Channel,float*ret,uint8_t len);
 void AdcGatherTask(void* pData);

typedef struct
{
	
 uint8_t   start;
 uint8_t   uCcount100ms; 
 uint8_t   uCcount500ms;
 uint8_t   start100flag;
 uint8_t   start500flag;

}AdcFlag;


extern AdcFlag  AdcFlagVar;
extern  float adcGetPress[5];

extern	uint8_t AdcCompareFlag;
extern  uint8_t     adcGetTimes ;
extern  int  AdcGetData[20];

#endif 








