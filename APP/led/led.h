#ifndef _led_H
#define _led_H

#include "system.h"



#define LIB_SET_UINT32_BIT(Data, Offset)    ((Data) |= (uint32_t)((uint32_t)1u << (Offset)))
#define LIB_SET_UINT16_BIT(Data, Offset)    ((Data) |= (uint16_t)((uint16_t)1u << (Offset)))
#define LIB_SET_UINT8_BIT(Data, Offset)     ((Data) |= (uint8_t)((uint8_t) 1u << (Offset)))

#define LIB_RESET_UINT32_BIT(Data, Offset)  ((Data) &= (uint32_t)(~(uint32_t)((uint32_t)1u << (Offset))))
#define LIB_RESET_UINT16_BIT(Data, Offset)  ((Data) &= (uint16_t)(~(uint16_t)((uint16_t)1u << (Offset))))
#define LIB_RESET_UINT8_BIT(Data, Offset)   ((Data) &= (uint8_t )(~(uint8_t )((uint8_t )1u << (Offset))))

#define LIB_GET_UINT32_BIT(Data, Offset)    (((uint8_t)(((uint32_t) (Data)) >> (Offset))) & (uint8_t)0x01u)
#define LIB_GET_UINT16_BIT(Data, Offset)    (((uint8_t)(((uint16_t) (Data)) >> (Offset))) & (uint8_t)0x01u)
#define LIB_GET_UINT8_BIT(Data, Offset)     (((uint8_t)(((uint8_t ) (Data)) >> (Offset))) & (uint8_t)0x01u)

#define LIB_GET_BYTE_0(Data)                ((uint8_t) (Data))
#define LIB_GET_BYTE_1(Data)                ((uint8_t)((Data)>>(uint8_t)8u))
#define LIB_GET_BYTE_2(Data)                ((uint8_t)((Data)>>(uint8_t)16u))
#define LIB_GET_BYTE_3(Data)                ((uint8_t)((Data)>>(uint8_t)24u))

#define LIB_GET_BYTE_LIT_UINT16(Data)		((uint16_t)Data[0u] + ((uint16_t)Data[1u] << 8u))
#define LIB_GET_BYTE_BIG_UINT16(Data)		((uint16_t)Data[1u] + ((uint16_t)Data[0u] << 8u))




/*  LED时钟端口、引脚定义 */
#define LED_PORT 			GPIOD   
#define LED_PIN 			(GPIO_Pin_14|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15)
#define LED_PORT_RCC		RCC_APB2Periph_GPIOD

/*
#define KEY1	!(GPIOC->IDR & (1<<0))
#define KEY2	!(GPIOC->IDR & (1<<1))
#define KEY3	!(GPIOC->IDR & (1<<2))
#define KEY4	!(GPIOC->IDR & (1<<3))
*/


#define KeyUp !( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0))
#define KeyMemu	!(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
#define KeyDown	!(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
#define KeyEnter	!(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))


void  KEY_Scan(void);
void  KEY_Init(void);



#define      SYS_OFF  	 GPIO_SetBits(GPIOC ,GPIO_Pin_4)
#define      SYS_ON   	 GPIO_ResetBits(GPIOC ,GPIO_Pin_4)
#define      SYS_FZ		   GPIOC->ODR ^= (1<<4)


#define      WANING_OFF  	  GPIO_SetBits(GPIOC ,GPIO_Pin_5)
#define      WANING_ON  	   GPIO_ResetBits(GPIOC ,GPIO_Pin_5)
#define      WANING_FZ		   GPIOC->ODR ^= (1<<5)

#define      START_OFF   	GPIO_SetBits(GPIOB ,GPIO_Pin_0)
#define      START_ON    	GPIO_ResetBits(GPIOB ,GPIO_Pin_0)
#define      START_FZ		   GPIOB->ODR ^= (1<<0)


   

#define      BEEP_ON   	  GPIO_SetBits(GPIOD ,GPIO_Pin_2)
#define      BEEP_OFF    	GPIO_ResetBits(GPIOD ,GPIO_Pin_2)
#define      BEEP_FZ		   GPIOD->ODR ^= (1<<2)
//平板
#define      BEEP1_ON   	  GPIO_SetBits(GPIOA ,GPIO_Pin_15)
#define      BEEP1_OFF    	GPIO_ResetBits(GPIOA ,GPIO_Pin_15)
#define      BEEP1_FZ		   GPIOA->ODR ^= (1<<15)

#define      DAC_REAST      GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define      DAC_SET      GPIO_ResetBits(GPIOB,GPIO_Pin_5)


typedef void(*pLedHdlFun)();
typedef enum
{
/*0*/	LED_ID_LOWER_FLOW = 0,
/*1*/	LED_ID_DETECT_WORK,
/*2*/	LED_ID_DOING_WORK,
/*3*/	LED_ID_END_WORK,
/*4*/	
/*5*/	
/*6*/	
/*7*/	
/*8*/	
/*9*/   LED_ID_MAX_NUM
} LedId_Enum;


typedef enum
{
    LED_BYTE_IDX0 = 0u,
    LED_BYTE_IDX1,
    LED_BYTE_IDX2,
    LED_BYTE_IDX3,
    LED_BYTE_IDX4,
    LED_BYTE_MAX_NUM
} LedHdlByteIdx_Enum;

typedef enum
{
    LED_BIT_0 = 0u,
    LED_BIT_1,
    LED_BIT_2,
    LED_BIT_3,
    LED_BIT_4,
    LED_BIT_5,
    LED_BIT_6,
    LED_BIT_7
} LedBitOffset_Enum;

typedef struct
{

	LedHdlByteIdx_Enum ucFaultByteIdx;
	LedBitOffset_Enum ucFaultBitOffset;
	pLedHdlFun ledHandleFun;

} LedHdlCfg_Struct;







void LED_Init(void);
void  Beep_Init(void);

void DAC_RESAT_PIN(void);


extern void LED_SetLedStatus(LedId_Enum lv_enLedId,uint8_t status);
extern void LED_5msMainFunction(void);
extern void LED_GetLedDataBuff(uint8_t *buff); 





typedef void(*pbeepHdlFun)();
typedef enum
{
/*0*/	BEEP_ID_LOWER_FLOW = 0,
/*1*/	BEEP_ID_DETECT_WORK,
/*2*/	BEEP_ID_DOING_WORK,
/*3*/	BEEP_ID_END_WORK,
/*4*/	
/*5*/	
/*6*/	
/*7*/	
/*8*/	
/*9*/   BEEP_ID_MAX_NUM
} beepId_Enum;


typedef enum
{
    beep_BYTE_IDX0 = 0u,
    beep_BYTE_IDX1,
    beep_BYTE_IDX2,
    beep_BYTE_IDX3,
    beep_BYTE_IDX4,
    beep_BYTE_MAX_NUM
} beepHdlByteIdx_Enum;


typedef enum
{
    beep_BIT_0 = 0u,
    beep_BIT_1,
    beep_BIT_2,
    beep_BIT_3,
    beep_BIT_4,
    beep_BIT_5,
    beep_BIT_6,
    beep_BIT_7
} beepBitOffset_Enum;

typedef struct
{
	beepHdlByteIdx_Enum ucFaultByteIdx;
	beepBitOffset_Enum ucFaultBitOffset;
	pbeepHdlFun beepHandleFun;
} beepHdlCfg_Struct;


extern void Beep_SetbeepStatus(beepId_Enum lv_enbeepId,uint8_t status);
extern void Beep_5msMainFunction(void);
extern void Beep_GetBeepDataBuff(uint8_t *buff); 











#endif
