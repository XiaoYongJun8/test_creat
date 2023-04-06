
#include "includes.h"
#define CH374HF_NO_CODE 
#include "CH374DRV.H"
#include "CH374HFM.H"
#include "exti.h"
#include "screendriver.h"
#include "iwdg.h"

void NVIC_Configuration(void)
{
     NVIC_InitTypeDef NVIC_InitStructure;

      
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

     NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级0
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);

    
   //  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	 //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级1
	//   NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
  //   NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTC全局中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//先占优先级1位,从优先级3位
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//先占优先级0位,从优先级4位
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能该通道中断
	  NVIC_Init(&NVIC_InitStructure);		//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		
		
	  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//定时器中断通道
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	
		
		

		
			//Usart2 NVIC 配置
	 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级2
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	 NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
		


 // TIM4
	
	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//定时器中断通道
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	






	 
}







void RCC_Configuration(void)
{
    /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD| RCC_APB2Periph_AFIO, ENABLE);

    /* Enable USART1 Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  
    /* Enable USART2 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
    /* Enable USART3 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
	    /* Enable USART4 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);  

	/* CAN1  Periph clocks enable 322 */
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); 
		  /* Enable TIM8 Clock */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//使能TIM8时钟

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   //使能SPI1时钟
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//使能SPI2时钟

}



uint16_t productKind = 0;
uint8_t gearKind = 0 ;
 uint32_t Ordinal = 0;
void InitTarget(void)
{
   uint16_t i = 0;
   uint8_t Range[10] = {0};
  
  uint32_t addr = secop(2003);    //扭矩
	 uint32_t addr1 = secop(2021);   //挡位
   CPU_IntDis();    //关中断

     RCC_Configuration();
	 NVIC_Configuration();
     uart_init();
	 TIM2_Init();
	 TIM4_Init();
	 
	 Input_Init();
	 LED_Init();
	 KEY_Init(); 
	
	 DAC_RESAT_PIN();
	
     Beep_Init();
  // Adc_Init();
	 SysTick_Init(72);

	 DAC8771_Init();

	 


  ADS8688_Init(CH2_EN|CH3_EN|CH4_EN|CH5_EN);
  Set_CH_Range(CHIR_0,VREF_0_125);//设置通道输入范围：0~5.12V   ±1.25*ref  ref=4.096V 
  Set_CH_Range(CHIR_1,VREF_0_125);
  Set_CH_Range(CHIR_2,VREF_0_125);
  Set_CH_Range(CHIR_3,VREF_0_125);
  Set_CH_Range(CHIR_4,VREF_0_25);
  Set_CH_Range(CHIR_5,VREF_0_25);
  Set_CH_Range(CHIR_6,VREF_0_25);
  Set_CH_Range(CHIR_7,VREF_0_25);
	 
  AUTO_RST_Mode();//进入自动扫描模式
	 

	 
	
     MX25L6406_Init();
	 RTC_Init();
	  
	 CH374_Init();
	 i = CH374LibInit();                                      /* 初始化CH375程序库和CH375芯片,操作成功返回0 */
	 mStopIfError(i);
	 

	
	 SysTick_Config(SystemCoreClock/200);//设置滴答定时器为5ms,
	
//add-2022-8-25 第一次烧程序或者屏幕上出现乱码，将下面屏蔽的内容打开，重新烧录后再次屏蔽即可。

	 //开始输出1bar的压力开启机器
   //DacOutData =  getOutData(10000.0);
	// DAC8771_WRITE_CMD(0x05,65530);
	 
	 
//	 
//	    memset(&ResetPress,0,sizeof(ResetPress));
//	    MX25L6406_Write((u8*)&ResetPress,secop(2047),sizeof(ResetPress));  //将各个模式对应的压力和输出值清零	
//	 
//	 
//	
 //     MX25L6406_WriteU32(secop(2000),TorqueUint_C);    //将扭矩单位清零


//      MX25L6406_WriteU32(secop(2046),Ordinal);    //将记录条数清零
// 
// 
// 

//	 MX25L6406_WriteU16(secop(2002),0);         //将产品个数清零  

//   MX25L6406_WriteU16(secop(2022),0);        //挡位个数清零
//	 
//	 for(i=0;i<50;i++)                          //存储扭矩信息内容清零
//	  {
//		memset(&TorquePatternVar[i],0,sizeof( TorquePattern ));
//    MX25L6406_Write((u8*)&TorquePatternVar[i],addr,sizeof(TorquePattern));
//    addr+=sizeof(TorquePattern);
//		  
//		
//		}
//	
//	 
//	 for(i=0;i<70;i++){                        //存储挡位的扇区清零
//		 	 
//		memset(&GearPatternVar[i],0,sizeof( GearPattern ));
//    MX25L6406_Write((u8*)&GearPatternVar[i],addr1,sizeof(GearPattern));
//    addr1+=sizeof(GearPattern);

//		}
//	 
//	 memset(&ModifyVarStructVar,0,sizeof(ModifyVarStructVar));//保存系统需要保存的参数清零
//	 FlashWriteScreenVar(&ModifyVarStructVar,secop(2040));	 

  // memset(&upComputerStructVar,0,sizeof(upComputerStructVar));                          //保存上位机发来的信息得地址清零
  // MX25L6406_Write((u8*)&upComputerStructVar,secop(2001),sizeof(upComputerStructVar));
//	
//   MX25L6406_WriteU16(secop(2020),0);  //保存角度得地址清零看0
//	
// 	 memset(&BoltGardeDiaArrVar,0,sizeof(BoltGardeDiaArr));        //螺栓清零



/****************************************************************/

		TorqueUint_C = MX25L6406_ReadU32(secop(2000));
		printf("TorqueUint_C = %d\r\n",TorqueUint_C);
		
    Ordinal = MX25L6406_ReadU32(secop(2046));
		printf("ordinal=%d\r\n",Ordinal);
	 
    productKind = MX25L6406_ReadU16(secop(2002));
    FlashGetTorquePattern(TorquePatternVar,secop(2002), productKind);//扭矩模式喝传感器模式

	
	  MX25L6406_Read((u8*)&gearKind,secop(2022),1);
		printf("gearKind=%d\r\n",gearKind);
	  FlashReadGear(GearPatternVar,gearKind,secop(2021));                    //挡位模式
   
			
	  FlashReadScreenVar(&ModifyVarStructVar,secop(2040));                //恢复上一次界面得值
  

			
	  
	
	
	  FlashReadupComputerStruct(&upComputerStructVar ,secop(2001));    //读出上位机修改产品的各种出厂信息
	 
	  if(ModifyVarStructVar.fabricName==0)ModifyVarStructVar.fabricName=1;
			
    ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);  //读出螺栓
	  
	//add-2022-8-16  ADC采集的值和这个对比	
        ModifyVarStructVar.Angle = MX25L6406_ReadU16(secop(2020));                //角度模式
		printf("  ModifyVarStructVar.Angle=%d\r\n",  ModifyVarStructVar.Angle);
		
    //知道ADS8688采集ADC值得工作原理和驱动程序
	//知道客户提供的传感器与ADC采集的值得换算关系匹配为角度值
	//将ADC采集的角度值和   ModifyVarStructVar.Angle 对比进行客户需求处理。
	
		

	   MX25L6406_Read((u8*)&ResetPress,secop(2047),sizeof(ResetPressStruct));
		 
		 printf("ResetPress.SetPress_Torque=%.2f\r\n",ResetPress.SetPress_Torque);
		 printf("ResetPress.SetPress_Bolt=%.2f\r\n",ResetPress.SetPress_Bolt);
		 printf("ResetPress.SetPress_Gear=%.2f\r\n",ResetPress.SetPress_Gear);
		 printf("ResetPress.SetPress_Angle=%.2f\r\n",ResetPress.SetPress_Angle);
		 printf("ResetPress.SetPress_Sensor=%.2f\r\n",ResetPress.SetPress_Sensor);
		 
		 
		 printf("ResetPress.DacOutData_T=%d\r\n",ResetPress.DacOutData_T);
		 printf("ResetPress.DacOutData_B=%d\r\n",ResetPress.DacOutData_B);
		 printf("ResetPress.DacOutData_G=%d\r\n",ResetPress.DacOutData_G);
		 printf("ResetPress.acOutData_A=%d\r\n",ResetPress.DacOutData_A);
		 printf("ResetPress.DacOutData_S=%d\r\n",ResetPress.DacOutData_S);
		 
		 
		 
		 
		
	switch(ModifyVarStructVar.WorkMode) 
	  {
		 case 0:func_index = 0;break;
		 case 1:func_index = 17;break;     
		 case 2:func_index = 28;break;
		 case 3:func_index = 37;break;
		 case 4:func_index = 46;break;
		 case 5:func_index = 57;break;
			
		}	
		
	 // WDC_INIT();
		
		
		CPU_IntEn();	
		
		
}








