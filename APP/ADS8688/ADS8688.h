
#ifndef _ADS8688_H_
#define  _ADS8688_H_


#include "stm32f10x.h"



//MOSI 9 PC12
//MISO  13  PB3
//CS  10   PB4
//SCK  2  PA1


#define        ADS8688_CS_L        GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define        ADS8688_CS_H        GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define  ADS8688_SCLK_L   GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define  ADS8688_SCLK_H   GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define ADS8688_MOSI_L  GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define ADS8688_MOSI_H  GPIO_SetBits(GPIOC,GPIO_Pin_12)


#define  ADS8688_MISO  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)   

//ͨ����������
#define _10_10V  0X00
#define _0_10V   0X01
#define _1_5V    0X02
#define _0_20mA  0X03
#define _4_20mA  0X04



//Command Register 

#define MAN_Ch_0	0XC000
#define MAN_Ch_1	0XC400
#define MAN_Ch_2	0XC800
#define MAN_Ch_3	0XCC00
#define MAN_Ch_4	0XD000
#define MAN_Ch_5	0XD400
#define MAN_Ch_6	0XD800
#define MAN_Ch_7	0XDC00
#define MAN_AUX		0XE000

//Program Register

#define Channel Power Down 		0X02
#define Feature Select			0X03

#define Channel_0_Input_Range		0X05
#define Channel_1_Input_Range		0X06
#define Channel_2_Input_Range		0X07
#define Channel_3_Input_Range		0X08
#define Channel_4_Input_Range		0X09
#define Channel_5_Input_Range		0X0A
#define Channel_6_Input_Range		0X0B
#define Channel_7_Input_Range		0X0C

#define Ch_0_Hysteresis				0X15
#define Ch_0_High_Threshold_MSB		0X16
#define Ch_0_High_Threshold_LSB		0X17
#define Ch_0_Low_Threshold_MSB		0X18
#define Ch_0_Low_Threshold_LSB		0X19

#define Ch_7_Hysteresis				0X38
#define Ch_7_High_Threshold_MSB		0X39
#define Ch_7_High_Threshold_LSB		0X3A
#define Ch_7_Low_Threshold_MSB		0X3B
#define Ch_7_Low_Threshold_LSB		0X3C

#define Command_Read_Back		0X3F	

#define WRITE 1
#define READ 0

#define CH7_EN  0X80
#define CH6_EN  0X40
#define CH5_EN  0X20
#define CH4_EN  0X10
#define CH3_EN  0X08
#define CH2_EN  0X04
#define CH1_EN  0X02
#define CH0_EN  0X01

#define CH7_PD  0X80
#define CH6_PD  0X40
#define CH5_PD  0X20
#define CH4_PD  0X10
#define CH3_PD  0X08
#define CH2_PD  0X04
#define CH1_PD  0X02
#define CH0_PD  0X01

#define VREF_25_25		0X00    //��2.5*ref  ref=4.096V  ��10.24V
#define VREF_125_125	0X01      //��1.25*ref    ��5.12V
#define VREF_0625_0625	0X02    //��0.625*ref   ��2.56V
#define VREF_0_25		0X05      //0-2.5*ref      0-10.24V
#define VREF_0_125		0X06   //0-1.25*ref     0-5.12V








/*************************************************************************************************************/
//����Ĵ��� 
#define NO_OP			0x0000 /*��ѡ��ģʽ�¼�������  
													���豸�����ڼ佫SDI����������Ϊ�͵�ƽ���൱��������16λд��0�������������ѡ���ģʽ��STDBY��PWR_DN��AUTO_RST��MAN_Ch_n���½����豸������
													������ģʽ�£��豸����ѭ����Ĵ�������ַ01h��3Ch���������õ���ͬ���á�*/
#define STDBY			0x8200 /*����ģʽ   
													����֧�ֵ͹��Ĵ���ģʽ��STDBY�����ڸ�ģʽ�£������ֵ�·�ϵ硣
													�ڲ���׼��ѹԴ�ͻ�����δ�ϵ磬���˳�STDBYģʽʱ��������20 ��s��Ϊ�����ӵ硣�˳�STDBYģʽʱ������Ĵ������ḴλΪĬ��ֵ��*/
#define PWR_DN  	0x8300/*����ģʽ��PWR_DN��
													����֧��Ӳ�����������ģʽ��PWR_DN�����ڸ�ģʽ�£������ڲ���·�������磬�����ڲ���׼��ѹԴ�ͻ�������
													����豸���ڲ��ο�ģʽ�����У�REFSEL = 0�������˳�PWR_DNģʽ���豸�ӵ粢ת����ѡģ������ͨ��������Ҫ15 ms��ʱ�䡣
													�豸��Ӳ����Դģʽ��RST / PD�����룩������˵����
													Ӳ�����������ģʽ֮�����Ҫ�������ڣ����豸��Ӳ�����绽��ʱ������Ĵ���������ΪĬ��ֵ�����ǵ��豸���������ʱ������Ĵ�������ǰ���ûᱣ�����硣*/
#define RST				0x8500/*���ó���Ĵ�����RST��
													����֧��Ӳ���������λ��RST��ģʽ���ڸ�ģʽ�£����г���Ĵ�������λΪ��Ĭ��ֵ��Ҳ����ʹ��Ӳ�����Ž��豸����RSTģʽ*/
#define AUTO_RST	0xA000/*�Զ�ͨ������
													�Զ�ɨ������ģ���ŵ��ϵ������źš��Զ�ɨ���ͨ�����п��ɳ���Ĵ����е��Զ�ɨ��˳����ƼĴ�����01h��02h�����ã�����ĳ���Ĵ���ӳ�䲿�֡�
													�ڴ�ģʽ�£��豸����������ѭ��ͨ����ѡͨ���������ͨ����ʼ��ת������Ĵ�����ѡ�������ͨ����
													������ɺ��豸���ص�����Ĵ����е���ͼ���ͨ�������ظ������С�ͨ�����ó���Ĵ����ķ�Χѡ��Ĵ��������������Զ�ɨ��������ÿ��ͨ���������ѹ��Χ��*/
#define MAN_CH_0	0xC000/**/
#define MAN_CH_1	0xC400/**/
#define MAN_CH_2	0xC800/**/
#define MAN_CH_3	0xCC00/**/
#define MAN_CH_4	0xD000/**/
#define MAN_CH_5	0xD400/**/
#define MAN_CH_6	0xD800/**/
#define MAN_CH_7	0xDC00/*�ֶ�ͨ��nѡ��MAN_Ch_n��
												ͨ�����ֶ�ͨ��nɨ��ģʽ��MAN_Ch_n���н��в��������Զ��豸���б����ת���ض���ģ������ͨ����ͨ��������Ĵ�����д����Ч���ֶ�ͨ��nѡ�����MAN_Ch_n������ɸñ��*/
#define MAN_AUX		0XE000/*AUXͨ��*/

//����Ĵ���
#define AUTO_SEQ_EN	0x01	/*�Զ�ɨ������ʹ�ܼĴ���
													�üĴ���ѡ�񵥸�ͨ������AUTO_RSTģʽ�½������� 
													�üĴ�����Ĭ��ֵΪFFh������ζ����Ĭ������������ͨ�����������Զ�ɨ�������С�*/
#define CH_PD				0x02	/*ͨ������Ĵ���
													�üĴ����رյ�AUTO_RSTģʽ�²������ĵ���ͨ���ĵ�Դ�� �üĴ�����Ĭ��ֵΪ00h������ζ����Ĭ������������ͨ�������ϵ硣*/																
#define F_S					0X03	/*��������ѡ����ƼĴ���
													�üĴ����е�λ���������þջ����������豸ID��������SDO�ϵ����λ��ʽ��*/
							
//��ͨ����Χѡ��Ĵ���	Ĭ��ֵΪ00h		 				
#define CHIR_0		0x05/**/
#define CHIR_1		0x06/**/
#define CHIR_2		0x07/**/
#define CHIR_3		0x08/**/
#define CHIR_4		0x09/**/
#define CHIR_5		0x0A/**/
#define CHIR_6		0x0B/**/
#define CHIR_7		0x0C/**/

#define CMD_READ	0x3F	/*����ض��Ĵ���
												�üĴ��������û���ȡ�豸�Ĳ���ģʽ�� ִ�д�������豸�������ǰһ������֡��ִ�е������֡�
												�й�����Ĵ�����������Ϣ��ǰ8λ�а��������Һ�8λΪ0��*/
												


#define REF 4083
//���뷶Χ
#define ADS8688_IR_N2_5V    0x00  //��2.5*ref  ref=4.096V  ��10.24V
#define ADS8688_IR_N1_25V   0x01  //��1.25*ref    ��5.12V
#define ADS8688_IR_N0_625V  0x02  //��0.625*ref   ��2.56V
#define ADS8688_IR_2_5V   	0x05  //0-2.5*ref      0-10.24V
#define ADS8688_IR_1_25V    0x06  //0-1.25*ref     0-5.12V

#define CONST_N2_5V_LSB_mV  	2.5*2*REF/65535
#define CONST_N1_25V_LSB_mV  	1.25*2*REF/65535
#define CONST_N0_625V_LSB_mV  0.625*2*REF/65535
#define CONST_2_5V_LSB_mV  		2.5*REF/65535
#define CONST_1_25V_LSB_mV 	 	1.25*REF/65535

//ͨ����������
#define _10_10V  0X00
#define _0_10V   0X01
#define _1_5V    0X02
#define _0_20mA  0X03
#define _4_20mA  0X04

#define VREF_25_25		0X00
#define VREF_125_125	0X01
#define VREF_0625_0625	0X02
#define VREF_0_25		0X05
#define VREF_0_125		0X06





void ADS8688_IO_Init(void);	   //ADS8688 IO�ڳ�ʼ��
void ADS8688_Init(uint8_t ch_en);	   //ADS8688��ʼ��

uint8_t ADS8688_SPI_Read8Bit(void);//��8��bit����
void ADS8688_SPI_Write8Bit(uint8_t com);//д8��bit����

void ADS8688_WriteCmd(uint16_t cmd);//дADS8688����Ĵ���

void SOFT_RESET(void);//�����λ
void AUTO_RST_Mode(void);//�Զ�ɨ��ģʽ
void MAN_CH_Mode(uint16_t ch);//�ֶ�ģʽ

uint8_t ADS8688_ReadReg(uint8_t addr);//��ָ���ļĴ���
void ADS8688_WriteReg(uint8_t addr,uint8_t data);//дָ���ļĴ���

void Set_Auto_Scan_Sequence(uint8_t seq);//�����Զ�ɨ������ͨ��
void Set_CH_Range(uint8_t ch,uint8_t range);//����ָ��ͨ��������Χ
	
u16 Get_MAN_CH_Mode_Data(void);//��ȡ�ֶ�ģʽADֵ
void Get_AUTO_RST_Mode_Data(uint16_t* outputdata, uint8_t chnum);//��ȡ�Զ�ɨ��ģʽADֵ









extern  void ADS8688_CollectTask(void);
extern  void ADS8688_5msMainFunction(void);
extern  float getPress(float value);
extern  float getFlow(float value);
extern  float getAngle1(float value);













#endif






