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
void UartRxMonitor(u8 ms); //串口接收监控
void UartDriver(void); //串口驱动函数void UartRead(u8 *buf, u8 len); //串口接收数据
u8 rs485_UartWrite(u8 *buf2 ,u16 len2);  //串口发送数据
u16 UartRead(u8 *buf, u16 len) ;

extern   uint32_t   Kind ;
extern 	uint8_t  MemoryProductFlag ;
extern   uint8_t   productPos ;
extern uint8_t Memory ;
extern uint8_t ReadMemory;


 
typedef struct
 {
 
 
 uint8_t  appearanceNumberArr[10] ;      //设置出厂编号
 uint8_t  UserEquipNameArr[10];          //设置设备名称
 uint8_t  UserEquipNumberArr[10] ;       //设置设备编号
 uint8_t  UserNameArr[20] ;              //设置操作人员名称
 uint8_t  passWordArr[10];	              //使用密码
 uint32_t UsingTime;                     //使用次数

 }upComputerStruct; 
 
 
 
 
 
typedef struct 
{

	uint32_t  ordinal;              //序号                             
	
	uint8_t ProductType[10];        //工具型号
	uint16_t  WorkPress;            //对应压力
	
	uint8_t   TolFacNum[8];         //工具出产编号      //12            4-11    
  uint16_t    year;                 // 	年                            12-13
	uint8_t   BoltGarde[12];       //螺栓等级      //20                 14-23
	
	
	uint8_t    month;                //月                              24
	uint8_t     day;                //日                               25
	uint8_t     hour;                //时                              26
	uint8_t     min;                //分                               27
	
	
	uint8_t     sec;                //秒           //7                 28     
	uint8_t    gear;                 //挡位                            29  
	uint16_t   actangle;       //实际角度                              30 - 31
	
   uint8_t    mode;          //选定模式                              32    
	 uint8_t    tigresult;       //拧紧结果       //13                33
	 uint8_t   BoltDia[10];        //螺栓直径                           34 -43
	
	 
	uint8_t    devname[16];               //设备名称                  44 -59
	uint8_t    devnum[8];              //设备编号                     60- 67
	uint8_t    operate[16];             //操作人员                     68-83
	uint32_t   tarque;              //目标扭矩;                       84-87
	uint32_t   actque;            //实际扭矩            //48          88-91
	
  uint16_t   tarangle;     //目标角度  
	uint8_t    workpattern;        //工作方式
	uint8_t    PressUint;           //压力单位
	uint8_t    TorqueUint;         //扭矩单位
		
		

		
		
		
		
		
}SysMemoryPara,*pSysMemoryPara;
 
 
 
 extern SysMemoryPara SysMemoryParaVar;
 
 
 
 

 extern  u8 gearkind ;
 extern upComputerStruct upComputerStructVar;


void TaskPcDebug(void* pData);



#endif

