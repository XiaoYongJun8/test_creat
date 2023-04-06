
#include "ADS8688.h"
#include "led.h"



/**********************************************************************************************************
*	函 数 名: ADS8688_Init
*	功能说明: ADS8688初始化
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void ADS8688_Init(uint8_t ch_en)	   //ADS8688初始化
{
	ADS8688_IO_Init();
	SOFT_RESET(); //复位
//	delay_ms(25);
  Set_Auto_Scan_Sequence(ch_en);//使能通道
  Set_Auto_Scan_Sequence(ch_en);//使能通道
	ADS8688_WriteReg(CH_PD,~ch_en);//通道退出低功耗状态 通道上电
	//delay_ms(50);
	printf("ADS8688_ReadReg(AUTO_SEQ_EN) =%d\r\n",ADS8688_ReadReg(AUTO_SEQ_EN));
  
  //add-2022-8-16 初始化不过就会死机，灯亮
	while(ADS8688_ReadReg(AUTO_SEQ_EN)!=ch_en)//是否使能成功
	{
		SYS_ON;
		Set_Auto_Scan_Sequence(ch_en);//使能通道
		ADS8688_WriteReg(CH_PD,~ch_en);//通道退出低功耗状态 通道上电
	//	delay_ms(50);
	}		
	 SYS_OFF;
}






/**********************************************************************************************************
*	函 数 名: ADS8688_IO_Init
*	功能说明: ADS8688 IO口初始化
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void ADS8688_IO_Init(void)	   //ADS8688 IO口初始化
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* SPI的 CS  */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关JATG调试接口
	/* SPI的 MISO  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* SPI的 MOSI  */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* SPI的 SCK  */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADS8688_CS_H;
  //RST_H;	
	ADS8688_SCLK_H;
	
	
	//delay_ms(5);
}


/**********************************************************************************************************
*	函 数 名: ADS8688_SPI_Read8Bit
*	功能说明: 从SPI总线读8个bit数据。 不带CS控制。
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
uint8_t ADS8688_SPI_Read8Bit(void)
{
	uint8_t i=0;
  uint8_t read=0;
  for(i=0;i<8;i++)
  {
    read<<=1;
    ADS8688_SCLK_H;
//delay_us(100);
    if(ADS8688_MISO) read++;
    ADS8688_SCLK_L;
	//	delay_us(100);
  }
  return read;
}
/**********************************************************************************************************
*	函 数 名: ADS8688_SPI_Write8Bit
*	功能说明: 向SPI总线写8个bit数据。 不带CS控制。
*	形    参: data : 数据
*	返 回 值: 无
**********************************************************************************************************/
void ADS8688_SPI_Write8Bit(uint8_t data)
{
	uint8_t i=0;
  ADS8688_CS_L;
  for(i=0;i<8;i++)
  {
    if(data&0x80)	ADS8688_MOSI_H;
    else	ADS8688_MOSI_L;
		data<<=1;
    ADS8688_SCLK_H;
	//	delay_us(100);
    ADS8688_SCLK_L;
		//delay_us(100);
  }
	
}
/**********************************************************************************************************
*	函 数 名: ADS8688_WriteCmd
*	功能说明: 写命令寄存器
*	形    参:  cmd : 命令
*	返 回 值: 无
**********************************************************************************************************/
void ADS8688_WriteCmd(uint16_t cmd)//写ADS8688命令寄存器
{
  ADS8688_CS_L;
  ADS8688_SPI_Write8Bit(cmd>>8 & 0XFF);
  ADS8688_SPI_Write8Bit(cmd & 0XFF);
	ADS8688_SPI_Write8Bit(0X00);
	ADS8688_SPI_Write8Bit(0X00);
  ADS8688_CS_H;
}

/*
*********************************************************************************************************
*	函 数 名: SOFT_RESET
*	功能说明: 软件复位
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void SOFT_RESET(void)//软件复位
{
  ADS8688_WriteCmd(RST);
}

/**********************************************************************************************************
*	函 数 名: AUTO_RST_Mode
*	功能说明: 自动模式
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
void AUTO_RST_Mode(void)//自动扫描模式
{
  ADS8688_WriteCmd(AUTO_RST);
}
/**********************************************************************************************************
*	函 数 名: MAN_CH_Mode
*	功能说明: 手动模式通道选择
*	形    参:  ch : 要选择的通道
*	返 回 值: 无
**********************************************************************************************************/
void MAN_CH_Mode(uint16_t ch)//手动模式
{
  ADS8688_WriteCmd(ch);	
}

/**********************************************************************************************************
*	函 数 名: ADS8688_ReadReg
*	功能说明: 读指定的寄存器
*	形    参:  addr : 寄存器地址
*	返 回 值: data : 读到的寄存器值。
**********************************************************************************************************/
uint8_t ADS8688_ReadReg(uint8_t addr)
{
  uint8_t data = 0;
  ADS8688_CS_L;
  ADS8688_SPI_Write8Bit(addr<<1);
  data = ADS8688_SPI_Read8Bit();
  data = ADS8688_SPI_Read8Bit();
  ADS8688_CS_H;
  return data;
}
/**********************************************************************************************************
*	函 数 名: ADS8688_WriteReg
*	功能说明: 写指定的寄存器
*	形    参:  addr : 寄存器地址
*			  		data : 寄存器值
*	返 回 值: 无
**********************************************************************************************************/
void ADS8688_WriteReg(uint8_t addr,uint8_t data)
{
  ADS8688_CS_L;
  ADS8688_SPI_Write8Bit(addr<<1| 0X01);
  ADS8688_SPI_Write8Bit(data);
  ADS8688_CS_H;
}
/**********************************************************************************************************
*	函 数 名: Set_Auto_Scan_Sequence
*	功能说明: 设置自动扫描序列通道
*	形    参:  seq：需要设置自动扫描序列使能寄存器的值
*	返 回 值: 无
**********************************************************************************************************/
void Set_Auto_Scan_Sequence(uint8_t seq)	
{
	ADS8688_WriteReg(AUTO_SEQ_EN, seq);
}
/**********************************************************************************************************
*	函 数 名: Set_CH_Range
*	功能说明: 设置指定通道测量范围
*	形    参:  ch : 通道
*			  		range : 测量范围
*	返 回 值: 无
**********************************************************************************************************/
void Set_CH_Range(uint8_t ch,uint8_t range)
{
  ADS8688_WriteReg(ch,range);
}

/**********************************************************************************************************
*	函 数 名: Get_AUTO_RST_Mode_Data
*	功能说明: 读取自动扫描模式AD值
*	形    参:data : 数据指针
*			  	chnum : 通道个数
*	返 回 值: 无
**********************************************************************************************************/
void Get_AUTO_RST_Mode_Data(uint16_t *data, uint8_t chnum)
{
  uint8_t i=0,datal=0,datah=0;
  for (i=0; i<chnum; i++)
  {
    ADS8688_CS_L;
    ADS8688_SPI_Write8Bit(0X00);
    ADS8688_SPI_Write8Bit(0X00);
    datah = ADS8688_SPI_Read8Bit();
    datal = ADS8688_SPI_Read8Bit();
	//	delay_ms(1);
    ADS8688_CS_H;
    *(data+i) = datah<<8 | datal;
  }
	
//	for (i=0;i<8;i++)
//	{
////*(outputdata+i)=inibuf[i];				
//		*(outputdata+i)=(inibuf[i]+inibuf[i+8]+inibuf[i+16]+inibuf[i+24]+inibuf[i+32])/5;		
//	//	if(i==5)
//		//	printf("5:%.6f\r\n",		((*(outputdata+i)-32768)/32768.0*10.24));//输出读取值		
//		if(i==5)
//		printf("%02x\r\n",*(outputdata+i));//输出读取值		
//	
//		//			printf("2:%.6f\r\n",		((*(outputdata+i)-32768)/32768.0*10.24));//输出读取值		
//	
//		//	if(i==7)
//		//	printf("3:%.6f\r\n",		((*(outputdata+i)-32768)/32768.0*10.24));//输出读取值		
//	}
	
	
	
}


/**********************************************************************************************************
*	函 数 名: Get_MAN_CH_Mode_Data
*	功能说明: 读取手动模式AD值
*	形    参: 无
*	返 回 值: 无
**********************************************************************************************************/
uint16_t Get_MAN_CH_Mode_Data(void)
{
  u8 datah=0,datal=0;
  ADS8688_CS_L;
  ADS8688_SPI_Write8Bit(0X00);
  ADS8688_SPI_Write8Bit(0X00);
  datah = ADS8688_SPI_Read8Bit();
  datal = ADS8688_SPI_Read8Bit();
  ADS8688_CS_H;
  return (datah<<8 | datal);
}





/*******************************************************************************
|    Macro Definition
|******************************************************************************/

//???????????
#define  ADC_PRESS_CH    0
#define  ADC_FLOW_CH     1
#define  ADC_ANGLE_CH    2
#define  ADC_INIT_CH_NUM      8
#define  ADC_CH_NUM     8
#define  ADC_SINGLE_CH_COLLECT_COUNT   100
#define  ADC_ALL_CH_COLLECT_COUNT      10

//0 2 4
//0 3 6
//1 4 7
//2 5 8

/*******************************************************************************
|    Enum Definition
|******************************************************************************/


/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/
static uint16_t s_AdcRecvBuff[ADC_ALL_CH_COLLECT_COUNT] = {0};
static uint16_t s_AdcSingleRecvBuff[ADC_CH_NUM][ADC_SINGLE_CH_COLLECT_COUNT] = {0};
static float s_Press = 0.0;
static float s_Angle = 0;
static float s_Flow = 0;

const uint8_t  s_AdcChRecvCount_Table[8] = 
{
      10,
      10,
      10,
      10,
      10,
      10,
      10,
      10,
};

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
static uint16_t averageValue_Fillter(const uint16_t *pData, uint16_t len);
static float mAValueToAngleVal(float value);
static float mAValueToFlowVal(float value);
static float mAValueToPressVal(float value);
static float averageValueTomA(uint8_t ch,uint16_t value);
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
void ADS8688_5msMainFunction(void)
{



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
void ADS8688_CollectTask(void)
{
    uint8_t chcnt = 0;
    uint16_t count = 0;
    uint16_t averageValue[ADC_CH_NUM] = {0};
    uint16_t mAValue[ADC_CH_NUM] = {0.0};
    Get_AUTO_RST_Mode_Data(s_AdcRecvBuff, ADC_ALL_CH_COLLECT_COUNT);
    for(chcnt = ADC_PRESS_CH;chcnt < ADC_ALL_CH_COLLECT_COUNT;chcnt + ADC_INIT_CH_NUM)
    {
         s_AdcSingleRecvBuff[ADC_PRESS_CH][count++] = s_AdcRecvBuff[chcnt];
         if(count == s_AdcChRecvCount_Table[ADC_PRESS_CH])
         {
            break;
         }  
    }
    count = 0;
    for(chcnt = ADC_FLOW_CH;chcnt < ADC_ALL_CH_COLLECT_COUNT;chcnt + ADC_INIT_CH_NUM)
    {
         s_AdcSingleRecvBuff[ADC_FLOW_CH][count++] = s_AdcRecvBuff[chcnt];
         if(count == s_AdcChRecvCount_Table[ADC_FLOW_CH])
         {
            break;
         }  
    }
    count = 0;
    for(chcnt = ADC_ANGLE_CH;chcnt < ADC_ALL_CH_COLLECT_COUNT;chcnt + ADC_INIT_CH_NUM)
    {
         s_AdcSingleRecvBuff[ADC_ANGLE_CH][count++] = s_AdcRecvBuff[chcnt];
         if(count == s_AdcChRecvCount_Table[ADC_ANGLE_CH])
         {
            break;
         }  
    }

    averageValue[ADC_PRESS_CH] = averageValue_Fillter( s_AdcSingleRecvBuff[ADC_PRESS_CH], s_AdcChRecvCount_Table[ADC_PRESS_CH]);
    averageValue[ADC_FLOW_CH] = averageValue_Fillter( s_AdcSingleRecvBuff[ADC_FLOW_CH], s_AdcChRecvCount_Table[ADC_FLOW_CH]);
    averageValue[ADC_ANGLE_CH] = averageValue_Fillter( s_AdcSingleRecvBuff[ADC_ANGLE_CH], s_AdcChRecvCount_Table[ADC_ANGLE_CH]);

    mAValue[ADC_PRESS_CH]  = averageValueTomA(ADC_PRESS_CH, averageValue[ADC_PRESS_CH]);
    mAValue[ADC_FLOW_CH]   = averageValueTomA(ADC_FLOW_CH, averageValue[ADC_FLOW_CH]);
    mAValue[ADC_ANGLE_CH]  = averageValueTomA(ADC_ANGLE_CH, averageValue[ADC_ANGLE_CH]);

    s_Press = mAValueToPressVal(mAValue[ADC_ANGLE_CH]);
    s_Angle = mAValueToAngleVal(mAValue[ADC_PRESS_CH]);
    s_Flow = mAValueToFlowVal(mAValue[ADC_FLOW_CH]);

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
static uint16_t averageValue_Fillter(const uint16_t *pData, uint16_t len)
{
	uint16_t min = 0, max = 0, verg = 0, invaild_count = 0,vaild_count = 0;
	uint32_t sum = 0;
	uint16_t tmp;
	if(len == 0)
	{
		return 0;
	}
	else
	{
		min = pData[0];
		max = pData[0];
		for(uint16_t i = 0; i < len; i++)
	    {
			tmp = pData[i];
	        if(pData[i] != 0)
	        {
	        	if(min == 0)
	        	{
	        		min = pData[i];
	        	}
	            if(min > pData[i])
	            {
	                min = pData[i];
	            }
	            if(max < pData[i])
	            {
	                max = pData[i];
	            }
	        }
			else
	        {
	            invaild_count++;
	        }
			sum += pData[i];
	    }
		vaild_count = len - invaild_count;
		if(vaild_count > 2)
		{
			sum -= min;
			sum -= max;
			verg = sum / (vaild_count - 2);
		}
		else if(vaild_count == 2)
		{
			verg = sum / 2;
		}
		else if((vaild_count = 0) || (vaild_count = 1))
		{
			verg = 0;
		}
		else{
			verg = 0;
		}
	}
	return verg;
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
static float averageValueTomA(uint8_t ch,uint16_t value)
{
   
    float MaretVal = 0.0;
    if(ch == ADC_PRESS_CH)
    {
        MaretVal = value/65535.0*10.24/500.0*1000;	
    }
    else if(ch == ADC_FLOW_CH)
    {
        
    }
    else if(ch == ADC_ANGLE_CH)
    {

    }
    else
    {

    }

    return MaretVal;

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
static float mAValueToPressVal(float value)
{
    return ((0.625*value)-2.5); 
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
static float mAValueToFlowVal(float value)
{
    return ((4.6875*value)-18.75); 
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
static float mAValueToAngleVal(float value)
{
    return 0.0;
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
float getPress(float value)
{
    return s_Press; 
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
 float getFlow(float value)
{
    return s_Flow; 
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
float getAngle1(float value)
{
    return s_Angle;
}







