#include "rs485.h"
#include "SysTick.h"
#include "crc16.h"
#include "led.h"
#include "uart.h"
#include "pclink.h"
#include "includes.h"



/*******************************************************************************
* 函 数 名         : RS485_Init
* 函数功能		   : USART2初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/  

u8 USART2_RX_BUF[640] = {0};                   //接收缓冲，最大64字节
u16 USART2_RX_CNT=0;                       //接收字节计数器
u8 flagFrame=0;                         //帧接收完成标志，即接收到一帧新数据
uint32_t   Kind = 0 ;
unsigned char regGroup[5];  //Modbus寄存器组，地址为0x00~0x04
SysMemoryPara SysMemoryParaVar = {0};
void RS485_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA\G时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	//TX-485	//串口输出PA2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);		/* 初始化串口输入IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;	//RX-485	   //串口输入PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	    //模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	USART_Cmd(USART2, ENABLE);  //使能串口 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启接受中断


	
	
}

	

//1ms定时

void TIM2_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=1000;   //自动装载值 
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //开启定时器中断
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	

	
	TIM_Cmd(TIM2,ENABLE); //使能定时器	
}



//10ms定时
void TIM4_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=20000;   //自动装载值 
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //开启定时器中断
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	TIM_Cmd(TIM4,DISABLE); //使能定时器	
}








//计算发送的数据长度，并且将数据放到*buf数组中                     
u16 UartRead(u8 *buf, u16 len)  
{
	 u16 i;
	if(len>USART2_RX_CNT)  //指定读取长度大于实际接收到的数据长度时
	{
		len=USART2_RX_CNT; //读取长度设置为实际接收到的数据长度
	}
	for(i=0;i<len;i++)  //拷贝接收到的数据到接收指针中
	{
		*buf=USART2_RX_BUF[i];  //将数据复制到buf中
		buf++;
	}
	USART2_RX_CNT=0;              //接收计数器清零
	return len;                   //返回实际读取长度
}


u8 rs485_UartWrite(u8 *buf ,u16 len) 										//发送
{
	u16 i=0; 

    for(i=0;i<=len;i++)
    {
	USART_SendData(USART2,buf[i]);	                                      //通过USARTx外设发送单个数据
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);             //检查指定的USART标志位设置与否，发送数据空位标
  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);             //检查指定的USART标志位设置与否，发送数据空位标			
    }
		
 return 0 ;

}



 








				
void UartRxMonitor(u8 ms) //串口接收监控
{
	static u16 USART2_RX_BKP=0;  //定义USART2_RC_BKP暂时存储诗句长度与实际长度比较
	static u8 idletmr=0;        //定义监控时间
	if(USART2_RX_CNT>0)//接收计数器大于零时，监控总线空闲时间
	{
		if(USART2_RX_BKP!=USART2_RX_CNT) //接收计数器改变，即刚接收到数据时，清零空闲计时
		{
			USART2_RX_BKP=USART2_RX_CNT;  //赋值操作，将实际长度给USART2_RX_BKP
			idletmr=0;                    //将监控时间清零
		}
		else                              ////接收计数器未改变，即总线空闲时，累计空闲时间
		{
			//如果在一帧数据完成之前有超过3.5个字节时间的停顿，接收设备将刷新当前的消息并假定下一个字节是一个新的数据帧的开始
			if(idletmr<5)                  //空闲时间小于1ms时，持续累加
			{
				idletmr += ms;
				if(idletmr>=5)             //空闲时间达到1ms时，即判定为1帧接收完毕
				{
					flagFrame=1;//设置命令到达标志，帧接收完毕标志
				}
			}
		}
	}
	else
	{
		USART2_RX_BKP=0;
	}
}
							
						
							
			
		
/*******************************************************************************
* 函 数 名         : USART2_IRQHandler
* 函数功能		   : USART2中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART2_IRQHandler(void)
{
	u8 res;	                                    //定义数据缓存变量
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 	
		res =USART_ReceiveData(USART2);//;读取接收到的数据USART2->DR
		
		if(USART2_RX_CNT < sizeof(USART2_RX_BUF))    //一次只能接收64个字节，人为设定，可以更大，但浪费时间
		{
			USART2_RX_BUF[USART2_RX_CNT]=res;  //记录接收到的值
			USART2_RX_CNT++;        //使收数据增加1 
		}
	}
}

			 
/*******************************************************************************
* 函 数 名         : TIM2_IRQHandler
* 函数功能		   : TIM2中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void TIM2_IRQHandler(void)
{

	UartRxMonitor(1); //串口接收监控
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//更新中断
}




	


 


 upComputerStruct upComputerStructVar = {0};
 uint8_t Memory = 0;
  uint8_t ReadMemory = 0;
 u8 gearkind = 0;
 uint8_t   productPos = 0;
//串口驱动函数，检测数据帧的接收，调度功能函数，需在主循环中调用
void UartDriver()
{
 
	unsigned int crc = 0;
	unsigned char crch = 0,crcl = 0;
    u16 len = 0;

	u8 buf[640] = {0};
	 
	if(flagFrame)            //帧接收完成标志，即接收到一帧新数据
	{
	
		flagFrame=0;           //帧接收完成标志清零
	
		len = UartRead(buf,sizeof(buf));   //将接收到的命令读到缓冲区中
  
	
		
	if((buf[0]==0x5A)&&(buf[1]==0xA5))                   //判断地址是不是帧头
		{
	    
			crc=GetCRC16(buf,len-2);       //计算CRC校验值，出去CRC校验值
			crch=crc>>8;    				//crc高位
			crcl=crc&0xFF;					//crc低位
			
			
		if((buf[len-2]==crch)&&(buf[len-1]==crcl))  //判断CRC校验是否正确
			{
				
			  rs485_UartWrite(buf,len);  //发送响应帧	
		   
			 switch (buf[4])               //按功能码执行操作
				{
						
		  	 case 1:   setTime(PTR2U16(buf+7),buf[9],buf[10],buf[11],buf[12],buf[13]);break;      //设置时间;
			   case 3:   setAppearanceNumber(&buf[7],&upComputerStructVar,PTR2U16(&buf[5])); Memory  = appearanceNumberMem;  break;  //设置出厂编号
     		 case 5:   setUserEquipName(&buf[7],&upComputerStructVar,PTR2U16(&buf[5]));   Memory = UserEquipNameMem; break;	     //设置设备名称

			   case 7:   setUserEquipNumber(&buf[7],&upComputerStructVar,PTR2U16(&buf[5])); Memory =  appearanceNumberMem;  break;      //	设置设备编号

			   case 9:  ToolsUnlock(&buf[8],&upComputerStructVar,PTR2U16(&buf[5])-1);   break;    //设置锁定状态

         case 10:    setPassWord(&buf[7],&upComputerStructVar,PTR2U16(&buf[5])) ; Memory = PassWordMem;   break;     //设置使用密码
         case 11:    setUsingTimes(&buf[7],&upComputerStructVar);SetTextInt32(0,9,upComputerStructVar.UsingTime,0,0); Memory = UsingTimesMem; break;      //设置使用次数
					
                    //将产品个数清零 
				 case 17:  	 MX25L6406_WriteU16(secop(2002),0);productKind = PTR2U16(buf+7);getProduct(TorquePatternVar,productKind,buf);Memory =   productMem;  break;
				             
                  
         case 18:  printf("productKind=%d\r\n",productKind); productPos =  CompareBoltName(TorquePatternVar,&buf[7],productKind);printf("productPos=%d\r\n",productPos); if(productPos==0)break; GetBoltStruct(buf,TorquePatternVar,&BoltGardeDiaArrVar,productPos);Memory = BoltStructMem;break;
				 case 19:   getAngle(&ModifyVarStructVar.Angle,buf); SetTextInt32(3,4,ModifyVarStructVar.Angle,0,0);Memory =   AngleMemMem;  break;
					          //挡位个数清零 
				 case 20:   MX25L6406_WriteU16(secop(2022),0); gearKind = buf[7];  getGear(GearPatternVar,gearKind,buf); Memory =  GearMem;  break;
				 case 21:   Kind = PTR2U16(buf+7);  GetSensor(buf,TorquePatternVar,Kind); Memory =  SensorMem;  break;
					
				 case 15:	  setUserName(&buf[7],&upComputerStructVar,PTR2U16(&buf[5]) );  Memory =  UserNameMem;break;           
					
 
				}	
     

		  }
			
			
	}
 }
}




void TaskPcDebug(void* pData)
{
	


   pData = pData;
   static uint32_t i = 0;
    static uint32_t j = 0;
   
  while(1)
	 {
		 OSTimeDly(6);
		
		   UartDriver();
		 
		  if(ADCGetPress[0]<0.0)
			{
			  ADCGetPress[0] = 0.0;
			}				
//		  if(AdcSignalFlag==3)
//			 {
//				  i++;
//				  if(i%2==0){
//					ADCGetPress[0] =  (SetPress+100) /10000;
//					}
//			    
//				 if(i%2==1){
//						ADCGetPress[0] =  (SetPress-100) /10000;
//					}
//			 }		
			j++;
			 if(j>20)
			 {
				 j = 0 ;
//				 if(ADCGetPress[0]*10000>30000)
//				 {
//	       AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]+0.15); 
//				 }
//				 else if(ADCGetPress[0]*10000>35000)//672
//				 {
//					 AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]+0.2); 
//				 }
//				 else if(ADCGetPress[0]*10000>40000)//768
//				 {
//					  AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]+0.3);
//				 }
//				 else if(ADCGetPress[0]*10000>45000)//864
//				 {
//					 AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]+0.4);
//				 }	
//				 else if(ADCGetPress[0]*10000>50000)//960
//				 {
//					  AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]+0.5);
//				 }
//				 else if(ADCGetPress[0]*10000>55000)//1056
//				 {
//					  AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]+0.7);
//				 }
//				 else
//				 {
//					   StructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]); 
//				 }
				  AdcGetShow(ModifyVarStructVar.WorkMode,ModifyVarStructVar.pressUint,ADCGetPress[0]); 
				 	 
			 }
	 }

}



float Maopao(float* pressarr,uint8_t len)
{
	
	 uint8_t i = 0;
	 uint8_t j = 0;
	 float press1 = 0;

		for(j=0;j<len;j++)
		{                                       		
			for(i=0;i<len-j;i++)
			{		
				if( pressarr[i] >  pressarr[i+1])
				{
					 press1 =  pressarr[i];
					 pressarr[i] =  pressarr[i+1];
					 pressarr[i+1] = press1;	
				}	
			}
		}
		 press1 = 0.0;  //5
		 for(i=1;i<=len-2;i++)//0 1 2 3  4
		 {
			 press1+=pressarr[i];
		 }
		 
		 press1= press1/(float)(len - 2);	
		 return press1;	 
}






 // press = (4.6875*getMA1)-18.75; 流量计,75/h
void TIM4_IRQHandler(void)
{
  uint16_t buff[128] = {0};

	uint8_t i = 0;
	uint8_t j = 0;//气体压力个数
	uint8_t k = 0;//流量计流速个数
	uint8_t l = 0;//角度个数
	float GetMa[10] = {0.0} ;//气体压力对应的MA
	float GetMa1[10] = {0.0} ; //流量计对应的MA
	float GetMa2[10] = {0.0} ; //角度传感器对应的MA

  //ADC_ShowPres(0,&ADCGetPress[0],8);
	//Get_AUTO_RST_Mode_Data(buff,40);//采集40次、0.5ms

	#if 0
	for(i=3 ;i<40;i = i+4)
	{
		GetMa[j++] = buff[i]/65536.0*10.24/500.0*1000;	
	}
	
  GetMa[0] = Maopao(GetMa,j);
	
	ADCGetPress[0] = (0.625*GetMa[0])-2.5;      //Bar 
#endif 

ADS8688_CollectTask();

    
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//更新中断
}






















			


