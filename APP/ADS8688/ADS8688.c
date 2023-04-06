
#include "ADS8688.h"
#include "led.h"



/**********************************************************************************************************
*	�� �� ��: ADS8688_Init
*	����˵��: ADS8688��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void ADS8688_Init(uint8_t ch_en)	   //ADS8688��ʼ��
{
	ADS8688_IO_Init();
	SOFT_RESET(); //��λ
//	delay_ms(25);
  Set_Auto_Scan_Sequence(ch_en);//ʹ��ͨ��
  Set_Auto_Scan_Sequence(ch_en);//ʹ��ͨ��
	ADS8688_WriteReg(CH_PD,~ch_en);//ͨ���˳��͹���״̬ ͨ���ϵ�
	//delay_ms(50);
	printf("ADS8688_ReadReg(AUTO_SEQ_EN) =%d\r\n",ADS8688_ReadReg(AUTO_SEQ_EN));
  
  //add-2022-8-16 ��ʼ�������ͻ�����������
	while(ADS8688_ReadReg(AUTO_SEQ_EN)!=ch_en)//�Ƿ�ʹ�ܳɹ�
	{
		SYS_ON;
		Set_Auto_Scan_Sequence(ch_en);//ʹ��ͨ��
		ADS8688_WriteReg(CH_PD,~ch_en);//ͨ���˳��͹���״̬ ͨ���ϵ�
	//	delay_ms(50);
	}		
	 SYS_OFF;
}






/**********************************************************************************************************
*	�� �� ��: ADS8688_IO_Init
*	����˵��: ADS8688 IO�ڳ�ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void ADS8688_IO_Init(void)	   //ADS8688 IO�ڳ�ʼ��
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* SPI�� CS  */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//��JATG���Խӿ�
	/* SPI�� MISO  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* SPI�� MOSI  */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* SPI�� SCK  */
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
*	�� �� ��: ADS8688_SPI_Read8Bit
*	����˵��: ��SPI���߶�8��bit���ݡ� ����CS���ơ�
*	��    ��: ��
*	�� �� ֵ: ��
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
*	�� �� ��: ADS8688_SPI_Write8Bit
*	����˵��: ��SPI����д8��bit���ݡ� ����CS���ơ�
*	��    ��: data : ����
*	�� �� ֵ: ��
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
*	�� �� ��: ADS8688_WriteCmd
*	����˵��: д����Ĵ���
*	��    ��:  cmd : ����
*	�� �� ֵ: ��
**********************************************************************************************************/
void ADS8688_WriteCmd(uint16_t cmd)//дADS8688����Ĵ���
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
*	�� �� ��: SOFT_RESET
*	����˵��: �����λ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SOFT_RESET(void)//�����λ
{
  ADS8688_WriteCmd(RST);
}

/**********************************************************************************************************
*	�� �� ��: AUTO_RST_Mode
*	����˵��: �Զ�ģʽ
*	��    ��: ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void AUTO_RST_Mode(void)//�Զ�ɨ��ģʽ
{
  ADS8688_WriteCmd(AUTO_RST);
}
/**********************************************************************************************************
*	�� �� ��: MAN_CH_Mode
*	����˵��: �ֶ�ģʽͨ��ѡ��
*	��    ��:  ch : Ҫѡ���ͨ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void MAN_CH_Mode(uint16_t ch)//�ֶ�ģʽ
{
  ADS8688_WriteCmd(ch);	
}

/**********************************************************************************************************
*	�� �� ��: ADS8688_ReadReg
*	����˵��: ��ָ���ļĴ���
*	��    ��:  addr : �Ĵ�����ַ
*	�� �� ֵ: data : �����ļĴ���ֵ��
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
*	�� �� ��: ADS8688_WriteReg
*	����˵��: дָ���ļĴ���
*	��    ��:  addr : �Ĵ�����ַ
*			  		data : �Ĵ���ֵ
*	�� �� ֵ: ��
**********************************************************************************************************/
void ADS8688_WriteReg(uint8_t addr,uint8_t data)
{
  ADS8688_CS_L;
  ADS8688_SPI_Write8Bit(addr<<1| 0X01);
  ADS8688_SPI_Write8Bit(data);
  ADS8688_CS_H;
}
/**********************************************************************************************************
*	�� �� ��: Set_Auto_Scan_Sequence
*	����˵��: �����Զ�ɨ������ͨ��
*	��    ��:  seq����Ҫ�����Զ�ɨ������ʹ�ܼĴ�����ֵ
*	�� �� ֵ: ��
**********************************************************************************************************/
void Set_Auto_Scan_Sequence(uint8_t seq)	
{
	ADS8688_WriteReg(AUTO_SEQ_EN, seq);
}
/**********************************************************************************************************
*	�� �� ��: Set_CH_Range
*	����˵��: ����ָ��ͨ��������Χ
*	��    ��:  ch : ͨ��
*			  		range : ������Χ
*	�� �� ֵ: ��
**********************************************************************************************************/
void Set_CH_Range(uint8_t ch,uint8_t range)
{
  ADS8688_WriteReg(ch,range);
}

/**********************************************************************************************************
*	�� �� ��: Get_AUTO_RST_Mode_Data
*	����˵��: ��ȡ�Զ�ɨ��ģʽADֵ
*	��    ��:data : ����ָ��
*			  	chnum : ͨ������
*	�� �� ֵ: ��
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
//		//	printf("5:%.6f\r\n",		((*(outputdata+i)-32768)/32768.0*10.24));//�����ȡֵ		
//		if(i==5)
//		printf("%02x\r\n",*(outputdata+i));//�����ȡֵ		
//	
//		//			printf("2:%.6f\r\n",		((*(outputdata+i)-32768)/32768.0*10.24));//�����ȡֵ		
//	
//		//	if(i==7)
//		//	printf("3:%.6f\r\n",		((*(outputdata+i)-32768)/32768.0*10.24));//�����ȡֵ		
//	}
	
	
	
}


/**********************************************************************************************************
*	�� �� ��: Get_MAN_CH_Mode_Data
*	����˵��: ��ȡ�ֶ�ģʽADֵ
*	��    ��: ��
*	�� �� ֵ: ��
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







