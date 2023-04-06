#include "SysTick.h"
#include "includes.h"


#define CH374HF_NO_CODE 
#include "CH374DRV.H"
#include "CH374HFM.H"
#include "adc.h"


 
static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数

float fun(float press,uint32_t* num);
uint8_t BeginSaveFlag = 0;

//初始化延迟函数
//SYSTICK的时钟固定为AHB时钟的1/8
//SYSCLK:系统时钟频率
void SysTick_Init(u8 SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;					
	fac_ms=(u16)fac_us*1000;				   
}								    


//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  	    
} 


#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
//systick中断服务函数,使用ucos时用到
void SysTick_Handler(void)
{				   
	  OSIntEnter();		//进入中断
    OSTimeTick();       //调用ucos的时钟服务程序               
    OSIntExit();        //触发任务切换软中断
}

#endif



 QUEUE  queue = {0,0,0};


static uint8_t SysMode_Select(uint8_t mode);
void queue_push(SysMemoryPara data)
{
	char pos = (queue.head+1)% MaxSize;
	
  if(pos !=queue.tail)
	 {
		memcpy(&queue.SysMemoryParaArr[queue.head] ,&data,sizeof(data));	 
		queue.head = pos;	
	 } 
	else{
	 	
	memcpy(&queue.SysMemoryParaArr[0],&queue.SysMemoryParaArr[queue.head-2],sizeof(queue.SysMemoryParaArr[queue.head-2]));
	memcpy(&queue.SysMemoryParaArr[queue.head-2],&queue.SysMemoryParaArr[queue.head-1],sizeof(queue.SysMemoryParaArr[queue.head-1]));
	memcpy(&queue.SysMemoryParaArr[queue.head-1] ,&data,sizeof(data));	

		
	  }
      	 	
}

uint8_t queue_size(void)
{
return ((queue.head+MaxSize-queue.tail)% MaxSize);	
}



void queue_reset(void)
 {
   queue.head = queue.tail = 0;
 }
	





uint8_t     niujupress =0;
uint16_t Seed = 0;           
uint8_t AdcSignalFlag  = 0; 
uint8_t OneMinuteFlag = 0;


float temppress = 0 ;

 #if 0
 uint8_t SysMode_Select(uint8_t mode)
 {
	 
	 static uint8_t First[6] = {0};
	 static uint8_t StartCaiji[6] = {0};
	 static uint16_t  Count2S = 400;
	 static uint8_t Ret = 0;
	 switch(mode)
	 {
		 case 1:    if(First[1] == 0)                   //扭矩模式
		            {
									Ret = 0;
									niujupress = 1;
									First[1] = 1;
								}
							 if(niujupress ==1)  //扭矩发生变化
								 {
									 	Ret = 0;
									 StartCaiji[1] = 1;
									 niujupress = 0;
									 DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Torque));
									 SetPress = ResetPress.SetPress_Torque;
								 }
							 if(StartCaiji[1] == 1)
							 {
								 if(!(--Count2S))
								 {
									 Count2S = 400;
									 temppress = ADCGetPress[0]*10000;
									 StartCaiji[1] = 0;
									 Ret = 1;
								 }
							 }break;
						
			 case 2:  if(First[2] == 0)                           //螺栓模式
		            {
											Ret = 0;
									niujupress = 1;
									First[2] = 1;
								}
							 if(niujupress ==1)  //扭矩发生变化
								 {
									 		Ret = 0;
									 StartCaiji[2] = 1;
									 niujupress = 0;
									 DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Bolt));
									 SetPress = ResetPress.SetPress_Bolt;
								 }
							 if(StartCaiji[2] == 1)
							 {
								 if(!(--Count2S))
								 {
									 		Ret = 1;
									 Count2S = 400;
									 temppress = ADCGetPress[0]*10000;
									 StartCaiji[2] = 0;
								 }
							 }break;						
								
				case 3: if(First[3] == 0)                    // 档位模式
		            {
											Ret = 0;
									niujupress = 1;
									First[3] = 1;
								}
							 if(niujupress ==1)  //扭矩发生变化
								 {
									 		Ret = 0;
									 StartCaiji[3] = 1;
									 niujupress = 0;
									 DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Gear));
									 SetPress = ResetPress.SetPress_Gear;
								 }
							 if(StartCaiji[3] == 1)
							 {
								 if(!(--Count2S))
								 {
									 		Ret = 1;
									 Count2S = 400;
									 temppress = ADCGetPress[0]*10000;
									 StartCaiji[3] = 0;
								 }
							 }break;

	 case 4:    if(First[4] == 0)                         //角度模式
		            {
											Ret = 0;
									niujupress = 1;
									First[4] = 1;
								}
							 if(niujupress ==1)  //扭矩发生变化
								 {
									 		Ret = 0;
									 StartCaiji[4] = 1;
									 niujupress = 0;
									 DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Angle));
									 SetPress = ResetPress.SetPress_Angle;
								 }
							 if(StartCaiji[4] == 1)
							 {
								 if(!(--Count2S))
								 {
									 		Ret = 1;
									 Count2S = 400;
									 temppress = ADCGetPress[0]*10000;
									 StartCaiji[4] = 0;
								 }
							 }break;
							 
				 case 5: if(First[5] == 0)                         //传感器模式
		            {
											Ret = 0;
									niujupress = 1;
									First[5] = 1;
								}
							 if(niujupress ==1)  //扭矩发生变化
								 {
									 		Ret = 0;
									 StartCaiji[5] = 1;
									 niujupress = 0;
									 DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Sensor));
									 SetPress = ResetPress.SetPress_Sensor;
								 }
							 if(StartCaiji[5] == 1)
							 {
								 if(!(--Count2S))
								 {
									 		Ret = 1;
									 Count2S = 400;
									 temppress = ADCGetPress[0]*10000;
									 StartCaiji[5] = 0;
								 }
							 }break;				 
													 
	 }
	 return Ret;
	
 }
 
 #endif 
 void Sys_huiFu(uint8_t mode)
 {
	 switch(mode)
	 {
		 
		 case 1: DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Torque));break;
		 case 2: DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Bolt));break;
		 case 3: DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Gear));break;
		 case 4: DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Angle));break;
		 case 5: DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Sensor));break;
	 }
	 
 }
 
 
 	 // 
 
 
 
 
 
 
 
 void Machine_5msMainFunction(void);
 
uint8_t ERROR_HAND = 0;
void   TaskTime(void* pData)
{
	
	static uint16_t ucCount1s = 150;
	static uint8_t  Systimes = 200;
  static uint16_t ucCount2s = 300;     //20
	 static uint16_t ucCount3s = 50;     //20
  static uint16_t ucCount5s = 1000;    //50   35
	static uint16_t ucCount15s = 12000;
	 static uint16_t ucCount200ms = 100;
	
static uint8_t i = 0;
	static uint16_t beepCount200ms = 40;
	
	 static uint16_t Count1S = 40;
	
  static uint8_t jiance = 0;
	static int count = 0;

		 static uint16_t Count2S = 400;

		static uint8_t Ret = 0;
	static uint16_t timeout = 0;
	
	  pData = pData;
	 
	  while(1)
			{
		     OSTimeDly(1);     
        LED_5msMainFunction();
				Beep_5msMainFunction();
        Machine_5msMainFunction();	
			} 

}



		
void Matchine_SetMachine(uint8_t step);			
	
#define   getSysMode 
#define   getSysRun

#define   MS_COUNT_200    (200/5)   
#define   S_COUNT_10     (100000/5)  
#define   MS_COUNT_500   (500/5)


static uint8_t machine_step = 0;
static void Machine_DoPress(void);
//static uint8_t SysMode_Select(uint8_t mode);
static void  Machine_DoAngle();
static float compareFac = 0.90;
/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/


/*******************************************************************************
|    Extern variables and functions declaration
|******************************************************************************/
float ADCGetFlow[10];
float ADCGetAngle[10];
float UserSetFlow[10];
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
void Machine_5msMainFunction(void)
{
      uint8_t ret = 0;
      ret = SysMode_Select(ModifyVarStructVar.WorkMode);
      if(ret ==1)
      {
            if((ModifyVarStructVar.WorkMode == 1) || (ModifyVarStructVar.WorkMode == 2) || (ModifyVarStructVar.WorkMode == 3 ))
            {
                  Machine_DoPress();          
            }
            else if(ModifyVarStructVar.WorkMode == 4)
            {
                    Machine_DoAngle();
            }
            else
            {

            }
            if(machine_step != 0)
            {
                  // ADCGetFlow[0] = getFlow(0.0);
                  if(ADCGetFlow[0]<UserSetFlow[0])
                  {
                        LED_SetLedStatus(LED_ID_LOWER_FLOW,1);
                        Beep_SetbeepStatus(BEEP_ID_LOWER_FLOW,1);
                  }
                  else
                  {
                        LED_SetLedStatus(LED_ID_LOWER_FLOW,0);
                        Beep_SetbeepStatus(BEEP_ID_LOWER_FLOW,0);
                  }   
            }
            else
            {
                     LED_SetLedStatus(LED_ID_LOWER_FLOW,0);
                     Beep_SetbeepStatus(BEEP_ID_LOWER_FLOW,0);
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
static void Machine_DoPress(void)
{
   static uint8_t ucCount200ms  = 0 ;
    static uint8_t ucCount500ms  = 0 ;
   static uint16_t usCount10s = 0;
   static uint8_t  ucTrueCount = 0;
   uint8_t led_buff[6];
   uint8_t beep_buff[6];
   switch(machine_step)
   {
    case 0:      ADCGetPress[0] = getPress(0);
//		     printf(" ADCGetPress[0]=%0.1f\r\n", ADCGetPress[0]*10000);;
//		     printf(" temppress=%0.1f\r\n", temppress);
                 if((ADCGetPress[0]*10000) < (temppress-1000) )
                  { 
                        LED_SetLedStatus(LED_ID_DETECT_WORK,1);
                        Beep_SetbeepStatus(BEEP_ID_DETECT_WORK,1);
                        Matchine_SetMachine(1);

                  } break; 


    case 1:      if(ucCount200ms++ >= MS_COUNT_200)
                  {
                        ucCount200ms = 0;
				ADCGetPress[0] = getPress(0);
                        if(((ADCGetPress[0]*10000)>= temppress*compareFac))
                        {
                            if(ucTrueCount++>2)
                            {
                              ucTrueCount = 0;
                              upComputerStructVar.UsingTime +=1;         
			            Memory =  UsingTimesMem;    
                              Matchine_SetMachine(2);
                            }
                        }
                        else
                        {
                              ucTrueCount = 0;
                        }									
                  }  
                  if(usCount10s++ >= S_COUNT_10)
                  {
                        Matchine_SetMachine(2);
                        usCount10s = 0;
                  }

      case 2:   
                        LED_SetLedStatus(LED_ID_DOING_WORK,1);
                        Beep_SetbeepStatus(BEEP_ID_DOING_WORK,1);
                        Matchine_SetMachine(3);  
                        break;


      case 3:           Beep_GetBeepDataBuff(led_buff);
                        LED_GetLedDataBuff(beep_buff);
                        if((LIB_GET_UINT8_BIT(beep_buff[beep_BYTE_IDX0],beep_BIT_2) == 0) && (LIB_GET_UINT8_BIT(beep_buff[LED_BYTE_IDX0],LED_BIT_2) ==0))
                        {
                              Matchine_SetMachine(4);     
                              Ordinal += 1;    
                              MX25L6406_WriteU32(secop(2046),Ordinal); 
                              RecordDataFuc(&SysMemoryParaVar);                                     
                              Memory =  SysParaMem;                     
                              DAC8771_WRITE_CMD(0x05,1); 
                              Matchine_SetMachine(4);        
                        }break;

      case 4:            Sys_huiFu(ModifyVarStructVar.WorkMode);
                         Matchine_SetMachine(5); 
                         break;
      case 5:            LED_SetLedStatus(LED_ID_END_WORK,1);
                         Beep_SetbeepStatus(BEEP_ID_END_WORK,1);
                         Matchine_SetMachine(6);  
                         break;
      case 6:           Beep_GetBeepDataBuff(led_buff);
                        LED_GetLedDataBuff(beep_buff); 
                       if((LIB_GET_UINT8_BIT(beep_buff[beep_BYTE_IDX0],beep_BIT_3)==0) && (LIB_GET_UINT8_BIT(beep_buff[LED_BYTE_IDX0],LED_BIT_3)==0))
                        {
                             Matchine_SetMachine(0);   
                        }break;
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
static uint8_t SysMode_Select(uint8_t mode)
{

      static uint8_t First[6] = {0};
      static uint8_t StartCaiji[6] = {0};
      static uint16_t  Count2S = 400;
      static uint8_t Ret = 0;
      switch(mode)
      {
      case 1:    if(First[1] == 0)                   //扭矩模式
                  {
                        Ret = 0;
                        niujupress = 1;
                        First[1] = 1;
                  }
                  if(niujupress ==1)  //扭矩发生变化
                  {
                        Ret = 0;
                        StartCaiji[1] = 1;
                        niujupress = 0;
                        DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Torque));
                        SetPress = ResetPress.SetPress_Torque;
                  }
                  if(StartCaiji[1] == 1)
                  {
                        if(!(--Count2S))
                        {
                              Count2S = 400;
                              ADCGetPress[0] = getPress(0.0);
                              temppress = ADCGetPress[0]*10000;
                              StartCaiji[1] = 0;
                              Ret = 1;
                        }
                  }break;

      case 2:  if(First[2] == 0)                           //螺栓模式
                  {
                        Ret = 0;
                        niujupress = 1;
                        First[2] = 1;
                  }
                  if(niujupress ==1)  //扭矩发生变化
                  {
                        Ret = 0;
                        StartCaiji[2] = 1;
                        niujupress = 0;
                        DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Bolt));
                        SetPress = ResetPress.SetPress_Bolt;
                  }
                  if(StartCaiji[2] == 1)
                  {
                        if(!(--Count2S))
                        {
                               Ret = 1;
                              Count2S = 400;
  //                            ADCGetPress[0] = getPress(float value);
                              temppress = ADCGetPress[0]*10000;
                              StartCaiji[2] = 0;
                        }
                  }break;						

      case 3: if(First[3] == 0)                    // 档位模式
                  {
                        Ret = 0;
                        niujupress = 1;
                        First[3] = 1;
                  }
                  if(niujupress ==1)  //扭矩发生变化
                  {
                        Ret = 0;
                        StartCaiji[3] = 1;
                        niujupress = 0;
                        DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Gear));
                        SetPress = ResetPress.SetPress_Gear;
                  }
                  if(StartCaiji[3] == 1)
                  {
                        if(!(--Count2S))
                        {
                        Ret = 1;
                        Count2S = 400;
//                        ADCGetPress[0] = getPress(float value);
                        temppress = ADCGetPress[0]*10000;
                        StartCaiji[3] = 0;
                        }
                  }break;

      case 4:    if(First[4] == 0)                         //角度模式
                  {
                        Ret = 0;
                        niujupress = 1;
                        First[4] = 1;
                  }
                  if(niujupress ==1)  //扭矩发生变化
                  {
                        Ret = 0;
                        StartCaiji[4] = 1;
                        niujupress = 0;
    //                    ADCGetPress[0] = getPress(float value);
                        DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Angle));
                        SetPress = ResetPress.SetPress_Angle;
                  }
                  if(StartCaiji[4] == 1)
                  {
                        if(!(--Count2S))
                        {
                              Ret = 1;
                              Count2S = 400;
                              temppress = ADCGetPress[0]*10000;
                              StartCaiji[4] = 0;
                        }
                  }break;

      case 5: if(First[5] == 0)                         //传感器模式
            {
                  Ret = 0;
                  niujupress = 1;
                  First[5] = 1;
            }
            if(niujupress ==1)  //扭矩发生变化
            {
                  Ret = 0;
                  StartCaiji[5] = 1;
                  niujupress = 0;
                  DAC8771_WRITE_CMD(0x05,getOutData(ResetPress.SetPress_Sensor));
                  SetPress = ResetPress.SetPress_Sensor;
            }
            if(StartCaiji[5] == 1)
            {
                  if(!(--Count2S))
                  {
                        Ret = 1;
                        Count2S = 400;
                        temppress = ADCGetPress[0]*10000;
                        StartCaiji[5] = 0;
                  }
            }break;				 

            }
            return Ret;
}
/*EOF*/

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
void Matchine_SetMachine(uint8_t step)
{
      machine_step = step;
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
static void  Machine_DoAngle()
{
  static uint8_t ucCount200ms  = 0 ;
    static uint8_t ucCount500ms  = 0 ;
   static uint16_t usCount10s = 0;
   static uint8_t  ucTrueCount = 0;
   uint8_t led_buff[6];
   uint8_t beep_buff[6];
   switch(machine_step)
   {
    case 0:    //  ADCGetPress[0] = getPress(float value);
                 if((ADCGetPress[0]*10000) < temppress-1000 ) 
                  { 
                        LED_SetLedStatus(LED_ID_DETECT_WORK,1);
                        Beep_SetbeepStatus(BEEP_ID_DETECT_WORK,1);
                        Matchine_SetMachine(1);
                  } break; 


    case 1:      if(ucCount200ms++ >= MS_COUNT_200)
                  {
                        ucCount200ms = 0;
                    //    ADCGetAngle[0] = getAngle(0.0);
                        if(ADCGetAngle[0] >= ModifyVarStructVar.Angle)
                        {
                              Matchine_SetMachine(2);
                        }
									
                  }  
                  if(usCount10s++ >= S_COUNT_10)
                  {
                        Matchine_SetMachine(2);
                        usCount10s = 0;
                  }

      case 2:   
                        LED_SetLedStatus(LED_ID_DOING_WORK,1);
                        Beep_SetbeepStatus(BEEP_ID_DOING_WORK,1);
                        Matchine_SetMachine(3);  
                        break;
      case 3:          if((LIB_GET_UINT8_BIT(beep_buff[beep_BYTE_IDX0],beep_BIT_2)==0) && (LIB_GET_UINT8_BIT(beep_buff[LED_BYTE_IDX0],LED_BIT_2)==0))
                        {
                              Matchine_SetMachine(4);     
                              Ordinal += 1;    
                              MX25L6406_WriteU32(secop(2046),Ordinal); 
                              RecordDataFuc(&SysMemoryParaVar);                                     
                              Memory =  SysParaMem;                     
                              DAC8771_WRITE_CMD(0x05,1); 
                              Matchine_SetMachine(4);        
                        }

      case 4:            Sys_huiFu(ModifyVarStructVar.WorkMode);
                         Matchine_SetMachine(5); 
                         break;
      case 5:            LED_SetLedStatus(LED_ID_END_WORK,1);
                         Beep_SetbeepStatus(LED_ID_END_WORK,1);
                         Matchine_SetMachine(6);  
                         break;
      case 6:           Beep_GetBeepDataBuff(led_buff);
                        LED_GetLedDataBuff(beep_buff); 
                       if((LIB_GET_UINT8_BIT(beep_buff[beep_BYTE_IDX0],beep_BIT_3)==0) && (LIB_GET_UINT8_BIT(beep_buff[LED_BYTE_IDX0],LED_BIT_3)==0))
                        {
                             Matchine_SetMachine(0);   
                        }break;
   }

}









			
				
				
				












