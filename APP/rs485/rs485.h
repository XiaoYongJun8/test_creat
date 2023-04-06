#ifndef _rs485_H
#define _rs485_H

#include "system.h"

extern u8 flagFrame;
extern u8 buf[640];
extern uint8_t ToolsUnlockArr[8];
uint32_t SetUsageTime(uint8_t* pBuffer);
void SetUsagePassWord(char*pDest,char*pSrc);
extern uint32_t UsageTimes ;

														 
void RS485_Init(u32 bound);
extern void TIM4_Init();
void TIM2_Init(void);
void UartRxMonitor(u8 ms); //���ڽ��ռ��
void UartDriver(void); //������������void UartRead(u8 *buf, u8 len); //���ڽ�������
u8 rs485_UartWrite(u8 *buf2 ,u16 len2);  //���ڷ�������
u16 UartRead(u8 *buf, u16 len) ;

extern   uint32_t   Kind ;
extern 	uint8_t  MemoryProductFlag ;
extern   uint8_t   productPos ;
extern uint8_t Memory ;
extern uint8_t ReadMemory;


 
typedef struct
 {
 
 
 uint8_t  appearanceNumberArr[10] ;      //���ó������
 uint8_t  UserEquipNameArr[10];          //�����豸����
 uint8_t  UserEquipNumberArr[10] ;       //�����豸���
 uint8_t  UserNameArr[20] ;              //���ò�����Ա����
 uint8_t  passWordArr[10];	              //ʹ������
 uint32_t UsingTime;                     //ʹ�ô���

 }upComputerStruct; 
 
 
 
 
 
typedef struct 
{

	uint32_t  ordinal;              //���                             
	
	uint8_t ProductType[10];        //�����ͺ�
	uint16_t  WorkPress;            //��Ӧѹ��
	
	uint8_t   TolFacNum[8];         //���߳������      //12            4-11    
  uint16_t    year;                 // 	��                            12-13
	uint8_t   BoltGarde[12];       //��˨�ȼ�      //20                 14-23
	
	
	uint8_t    month;                //��                              24
	uint8_t     day;                //��                               25
	uint8_t     hour;                //ʱ                              26
	uint8_t     min;                //��                               27
	
	
	uint8_t     sec;                //��           //7                 28     
	uint8_t    gear;                 //��λ                            29  
	uint16_t   actangle;       //ʵ�ʽǶ�                              30 - 31
	
   uint8_t    mode;          //ѡ��ģʽ                              32    
	 uint8_t    tigresult;       //š�����       //13                33
	 uint8_t   BoltDia[10];        //��˨ֱ��                           34 -43
	
	 
	uint8_t    devname[16];               //�豸����                  44 -59
	uint8_t    devnum[8];              //�豸���                     60- 67
	uint8_t    operate[16];             //������Ա                     68-83
	uint32_t   tarque;              //Ŀ��Ť��;                       84-87
	uint32_t   actque;            //ʵ��Ť��            //48          88-91
	
  uint16_t   tarangle;     //Ŀ��Ƕ�  
	uint8_t    workpattern;        //������ʽ
	uint8_t    PressUint;           //ѹ����λ
	uint8_t    TorqueUint;         //Ť�ص�λ
		
		

		
		
		
		
		
}SysMemoryPara,*pSysMemoryPara;
 
 
 
 extern SysMemoryPara SysMemoryParaVar;
 
 
 
 

 extern  u8 gearkind ;
 extern upComputerStruct upComputerStructVar;


void TaskPcDebug(void* pData);



#endif

