#include "led.h"


#define     RED_LED_FZ      WANING_FZ 
#define     RED_LED_OFF     WANING_OFF

#define     BLUE_LED_FZ     SYS_FZ  
#define     BLUE_LED_OFF    SYS_OFF
#define     BLUE_LED_ON    SYS_ON

#define TASK_CYCLE_TIME     5
#define MS500_TIME_COUNT   (500/TASK_CYCLE_TIME)
#define MS50_TIME_COUNT    (50/TASK_CYCLE_TIME)
#define S5_TIME_COUNT      (5000/TASK_CYCLE_TIME)
#define S2_TIME_COUNT      (2000/TASK_CYCLE_TIME)


static void LED_DetectWork(void);
static void LED_LowerFlow(void);
static void LED_DoingWork(void);
static void LED_EndWork(void);

const LedHdlCfg_Struct c_stLedHdlCfgArray[LED_ID_MAX_NUM] = 
{
    {LED_BYTE_IDX0,LED_BIT_0,LED_LowerFlow},
    {LED_BYTE_IDX0,LED_BIT_1,LED_DetectWork},
    {LED_BYTE_IDX0,LED_BIT_2,LED_DoingWork},
    {LED_BYTE_IDX0,LED_BIT_3,LED_EndWork},
};
//0 1
static uint8_t s_ucLedData[LED_BYTE_MAX_NUM] = {0};
static uint16_t usCountLowerFlow500ms = 0;

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
PC4---LED1：SYS
PC5---LED2：waning
PB0---LED3:star
*******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //设置传输速率
	
	
	GPIO_Init(GPIOC ,&GPIO_InitStructure); 	   /* 初始化GPIO */
	//GPIO_Init(GPIOB ,&GPIO_InitStructure);
	
	
	
	SYS_OFF;
	WANING_OFF;
	START_OFF;
	
}
void DAC_RESAT_PIN(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB ,&GPIO_InitStructure);
	
	 GPIO_ResetBits(GPIOB ,GPIO_Pin_5);
}


/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : KEY初始化函数
* 输    入         : 无
* 输    出         : 无
PC0---KEY1
PC1---KEY2
PC2---KEY3
PC3---KEY4

*******************************************************************************/

void  KEY_Init(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //开启时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//下拉输入  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_Init(GPIOC,&GPIO_InitStructure);		  /* 初始化GPIO */
	
}


	/*******************************************************************************
* 函 数 名         : KEY_Init
* 函数功能		   : KEY初始化函数
* 输    入         : 无
* 输    出         : 无
PD2---KEY1


*******************************************************************************/

void  Beep_Init(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //开启时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//下拉输入  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_Init(GPIOD,&GPIO_InitStructure);		  /* 初始化GPIO */
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //开启时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//下拉输入  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //设置传输速率
	GPIO_Init(GPIOA,&GPIO_InitStructure);		  /* 初始化GPIO */
	
	   GPIO_ResetBits(GPIOA ,GPIO_Pin_15);
		GPIO_ResetBits(GPIOD ,GPIO_Pin_2);
} 


void LED_5msMainFunction(void)
{

	uint8_t lv_ByteIdx,lv_BitOffset;
	LedId_Enum lv_enErrHdlId;
	for(lv_enErrHdlId = 0u; lv_enErrHdlId < LED_ID_MAX_NUM; lv_enErrHdlId++)
	{
		lv_ByteIdx = c_stLedHdlCfgArray[lv_enErrHdlId].ucFaultByteIdx;
		lv_BitOffset = c_stLedHdlCfgArray[lv_enErrHdlId].ucFaultBitOffset;
 
		if(1 == LIB_GET_UINT8_BIT(s_ucLedData[lv_ByteIdx], lv_BitOffset))
		{

             c_stLedHdlCfgArray[lv_enErrHdlId].ledHandleFun();
             break;

		}
		else
		{

        }
	}
    if(lv_enErrHdlId == LED_ID_MAX_NUM)
    {
        usCountLowerFlow500ms = 0;
        RED_LED_OFF;
        BLUE_LED_OFF;  

    }

} 


/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
 void LED_GetLedDataBuff(uint8_t *buff)
{
    memcpy(buff,s_ucLedData,LED_BYTE_MAX_NUM);
}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void LED_LowerFlow(void)
{
     static uint16_t  usCount500ms = 0;
   if(usCount500ms++>=MS500_TIME_COUNT)
   {
        RED_LED_FZ;
        usCountLowerFlow500ms = 0;
   }
}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void LED_DoingWork(void)
{
    static uint16_t  usCount500ms = 0;
    static uint16_t  usCount5S = 0;
    if(usCount500ms++>=MS500_TIME_COUNT)
    {   
         usCount500ms = 0;
         BLUE_LED_FZ;   
    }
    if(usCount5S++>=S5_TIME_COUNT)
    {
        usCount5S = 0;
        LED_SetLedStatus(LED_ID_DOING_WORK,0);
    }      
}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void LED_EndWork(void)
{
    static uint16_t  usCount50ms = 0;
    static uint16_t  usCount2S = 0;
    if(usCount50ms++>=MS50_TIME_COUNT)
    {   
         usCount50ms = 0;
         BLUE_LED_FZ;   
    }
    if(usCount2S++>=S2_TIME_COUNT)
    {
        usCount2S = 0;
        LED_SetLedStatus(LED_ID_END_WORK,0);
    } 
}

/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void LED_DetectWork(void)
{
    static uint16_t usCount2S = 0;
    BLUE_LED_ON;  
    if(usCount2S++>S2_TIME_COUNT)
    {
        usCount2S = 0;
        LED_SetLedStatus(LED_ID_DETECT_WORK,0); 
    }
}



/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
void LED_SetLedStatus(LedId_Enum lv_enLedId,uint8_t status)
{
    uint8_t lv_ByteIdx,lv_BitOffset;
    LedId_Enum lv_enErrHdlId;
    for(lv_enErrHdlId = 0u; lv_enErrHdlId < LED_ID_MAX_NUM; lv_enErrHdlId++)
    {
        if(lv_enLedId == lv_enErrHdlId)
        {
            lv_ByteIdx = c_stLedHdlCfgArray[lv_enErrHdlId].ucFaultByteIdx;
            lv_BitOffset = c_stLedHdlCfgArray[lv_enErrHdlId].ucFaultBitOffset;
            if(status == 1)
            {
                LIB_SET_UINT8_BIT(s_ucLedData[lv_ByteIdx], lv_BitOffset);  
            }
            else
            {
                LIB_RESET_UINT8_BIT(s_ucLedData[lv_ByteIdx], lv_BitOffset);  
            }
        }
    }
}




#define     BEEP_FZ()       
#define     BEEP_OFF()   
#define     BEEP_ON()  
 

#define TASK_CYCLE_TIME     5
#define MS500_TIME_COUNT   (500/TASK_CYCLE_TIME)
#define MS50_TIME_COUNT    (50/TASK_CYCLE_TIME)
#define S5_TIME_COUNT      (5000/TASK_CYCLE_TIME)
#define S2_TIME_COUNT      (2000/TASK_CYCLE_TIME)
#define S1_TIME_COUNT      (1000/TASK_CYCLE_TIME)
#define MS200_TIME_COUNT      (200/TASK_CYCLE_TIME)
#define MS200_COUNT           4




static void Beep_DetectWork(void);
static void Beep_LowerFlow(void);
static void Beep_DoingWork(void);
static void Beep_EndWork(void);

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
const beepHdlCfg_Struct c_stbeepHdlCfgArray[BEEP_ID_MAX_NUM] = 
{

   {beep_BYTE_IDX0,beep_BIT_0,Beep_LowerFlow},
   {beep_BYTE_IDX0,beep_BIT_1,Beep_LowerFlow},
   {beep_BYTE_IDX0,beep_BIT_2,Beep_DoingWork},
   {beep_BYTE_IDX0,beep_BIT_3,Beep_EndWork},
   
};



static uint8_t s_ucbeepData[BEEP_ID_MAX_NUM] = {0};

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/

/*******************************************************************************
|    Function Source Code
|******************************************************************************/

/*code*/
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
void Beep_5msMainFunction(void)
{

	uint8_t lv_ByteIdx,lv_BitOffset;
	beepId_Enum lv_enErrHdlId;
	for(lv_enErrHdlId = 0u; lv_enErrHdlId < BEEP_ID_MAX_NUM; lv_enErrHdlId++)
	{
		lv_ByteIdx = c_stbeepHdlCfgArray[lv_enErrHdlId].ucFaultByteIdx;
		lv_BitOffset = c_stbeepHdlCfgArray[lv_enErrHdlId].ucFaultBitOffset;

		if(1 == LIB_GET_UINT8_BIT(s_ucbeepData[lv_ByteIdx], lv_BitOffset))
		{
             c_stbeepHdlCfgArray[lv_enErrHdlId].beepHandleFun();
             break;

		}
		else
		{

        }
	}
    if(lv_enErrHdlId == BEEP_ID_MAX_NUM)
    {
        BEEP_OFF();   
    }
} 
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
void Beep_SetbeepStatus(beepId_Enum lv_enbeepId,uint8_t status)
{
    uint8_t lv_ByteIdx,lv_BitOffset;
    beepId_Enum lv_enErrHdlId;
    for(lv_enErrHdlId = 0u; lv_enErrHdlId < BEEP_ID_MAX_NUM; lv_enErrHdlId++)
    {
        if(lv_enbeepId == lv_enErrHdlId)
        {
            lv_ByteIdx = c_stbeepHdlCfgArray[lv_enErrHdlId].ucFaultByteIdx;
            lv_BitOffset = c_stbeepHdlCfgArray[lv_enErrHdlId].ucFaultBitOffset;
            if(status == 1)
            {
                LIB_SET_UINT8_BIT(s_ucbeepData[lv_ByteIdx], lv_BitOffset);  
            }
            else
            {
                LIB_RESET_UINT8_BIT(s_ucbeepData[lv_ByteIdx], lv_BitOffset);  
            }
        }
    }
}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
void Beep_GetBeepDataBuff(uint8_t *buff)
{
    memcpy(buff,s_ucbeepData,BEEP_ID_MAX_NUM);
}


/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void Beep_DetectWork(void)
{
   static uint8_t usCount200ms = 0;
   static uint8_t usCount = 0;
   if(usCount200ms++>=MS200_TIME_COUNT)
   {
     BEEP_FZ();
     if(usCount++>=MS200_COUNT)
     {
        usCount = 0;
        Beep_SetbeepStatus(BEEP_ID_DETECT_WORK,0);
     }
     usCount200ms = 0;
   }
}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void Beep_LowerFlow(void)
{

   static uint8_t usCount200ms = 0;
   if(usCount200ms++>=MS200_TIME_COUNT)
   {
     BEEP_FZ();
     usCount200ms = 0;
   }

}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void Beep_DoingWork(void)
{

   static uint16_t usCount1s = 0;
   static uint16_t usCount5S = 0;
   if(usCount1s++>=S1_TIME_COUNT)
   {
     BEEP_FZ();
     usCount1s = 0;
   }
    if(usCount5S++>=S5_TIME_COUNT)
    {
        usCount5S = 0;
        Beep_SetbeepStatus(BEEP_ID_DOING_WORK,0);
    }     

}
/*******************************************************************************
Name			: 
Syntax			: 
Sync/Async		: 
Reentrancy		:
Parameters(in)	: 
Parameters(out) : 
Return value	: 
Description		: 
Call By			: -
|******************************************************************************/
static void Beep_EndWork(void)
{

    static uint16_t  usCount200ms = 0;
    static uint16_t  usCount2S = 0;
    if(usCount200ms++>=MS200_TIME_COUNT)
    {   
         usCount200ms = 0;
         BEEP_FZ(); 
    }
    if(usCount2S++>=S2_TIME_COUNT)
    {
        usCount2S = 0;
        Beep_SetbeepStatus(BEEP_ID_END_WORK,0);
    } 


}






