#ifndef __ADC_H
#define __ADC_H	


#include "stm32f10x.h"

/*
16·ADC����DMA����
����Adc_Init()������ʼ���豸��ADCѭ������ 
���ݱ�DMA���˵�ADC_Value[ADC_CH_NUM]������
�˲����������ADC_AfterFilter[ADC_CH_NUM]��
*/


#define   ADC_CH_NUM   6    //ADCͨ����Ŀ 16��ͨ��



extern u16 ADC_Value[ADC_CH_NUM];				 //ADC����ԭʼ����
extern u16 ADC_AfterFilter[ADC_CH_NUM];  //ADC���������˲��������
extern float ADCGetPress[10];

void Adc_Init(void);										//ADC�豸��ʼ��
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








