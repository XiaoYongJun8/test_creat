
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
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�0
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);

    
   //  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	 //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�1
	//   NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
  //   NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTCȫ���ж�
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�1λ,�����ȼ�3λ
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//��ռ���ȼ�0λ,�����ȼ�4λ
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ�ܸ�ͨ���ж�
	  NVIC_Init(&NVIC_InitStructure);		//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		
		
	  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//��ʱ���ж�ͨ��
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	  NVIC_Init(&NVIC_InitStructure);	
		
		

		
			//Usart2 NVIC ����
	 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�2
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		


 // TIM4
	
	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//��ʱ���ж�ͨ��
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
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
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//ʹ��TIM8ʱ��

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   //ʹ��SPI1ʱ��
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//ʹ��SPI2ʱ��

}



uint16_t productKind = 0;
uint8_t gearKind = 0 ;
 uint32_t Ordinal = 0;
void InitTarget(void)
{
   uint16_t i = 0;
   uint8_t Range[10] = {0};
  
  uint32_t addr = secop(2003);    //Ť��
	 uint32_t addr1 = secop(2021);   //��λ
   CPU_IntDis();    //���ж�

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
  Set_CH_Range(CHIR_0,VREF_0_125);//����ͨ�����뷶Χ��0~5.12V   ��1.25*ref  ref=4.096V 
  Set_CH_Range(CHIR_1,VREF_0_125);
  Set_CH_Range(CHIR_2,VREF_0_125);
  Set_CH_Range(CHIR_3,VREF_0_125);
  Set_CH_Range(CHIR_4,VREF_0_25);
  Set_CH_Range(CHIR_5,VREF_0_25);
  Set_CH_Range(CHIR_6,VREF_0_25);
  Set_CH_Range(CHIR_7,VREF_0_25);
	 
  AUTO_RST_Mode();//�����Զ�ɨ��ģʽ
	 

	 
	
     MX25L6406_Init();
	 RTC_Init();
	  
	 CH374_Init();
	 i = CH374LibInit();                                      /* ��ʼ��CH375������CH375оƬ,�����ɹ�����0 */
	 mStopIfError(i);
	 

	
	 SysTick_Config(SystemCoreClock/200);//���õδ�ʱ��Ϊ5ms,
	
//add-2022-8-25 ��һ���ճ��������Ļ�ϳ������룬���������ε����ݴ򿪣�������¼���ٴ����μ��ɡ�

	 //��ʼ���1bar��ѹ����������
   //DacOutData =  getOutData(10000.0);
	// DAC8771_WRITE_CMD(0x05,65530);
	 
	 
//	 
//	    memset(&ResetPress,0,sizeof(ResetPress));
//	    MX25L6406_Write((u8*)&ResetPress,secop(2047),sizeof(ResetPress));  //������ģʽ��Ӧ��ѹ�������ֵ����	
//	 
//	 
//	
 //     MX25L6406_WriteU32(secop(2000),TorqueUint_C);    //��Ť�ص�λ����


//      MX25L6406_WriteU32(secop(2046),Ordinal);    //����¼��������
// 
// 
// 

//	 MX25L6406_WriteU16(secop(2002),0);         //����Ʒ��������  

//   MX25L6406_WriteU16(secop(2022),0);        //��λ��������
//	 
//	 for(i=0;i<50;i++)                          //�洢Ť����Ϣ��������
//	  {
//		memset(&TorquePatternVar[i],0,sizeof( TorquePattern ));
//    MX25L6406_Write((u8*)&TorquePatternVar[i],addr,sizeof(TorquePattern));
//    addr+=sizeof(TorquePattern);
//		  
//		
//		}
//	
//	 
//	 for(i=0;i<70;i++){                        //�洢��λ����������
//		 	 
//		memset(&GearPatternVar[i],0,sizeof( GearPattern ));
//    MX25L6406_Write((u8*)&GearPatternVar[i],addr1,sizeof(GearPattern));
//    addr1+=sizeof(GearPattern);

//		}
//	 
//	 memset(&ModifyVarStructVar,0,sizeof(ModifyVarStructVar));//����ϵͳ��Ҫ����Ĳ�������
//	 FlashWriteScreenVar(&ModifyVarStructVar,secop(2040));	 

  // memset(&upComputerStructVar,0,sizeof(upComputerStructVar));                          //������λ����������Ϣ�õ�ַ����
  // MX25L6406_Write((u8*)&upComputerStructVar,secop(2001),sizeof(upComputerStructVar));
//	
//   MX25L6406_WriteU16(secop(2020),0);  //����Ƕȵõ�ַ���㿴0
//	
// 	 memset(&BoltGardeDiaArrVar,0,sizeof(BoltGardeDiaArr));        //��˨����



/****************************************************************/

		TorqueUint_C = MX25L6406_ReadU32(secop(2000));
		printf("TorqueUint_C = %d\r\n",TorqueUint_C);
		
    Ordinal = MX25L6406_ReadU32(secop(2046));
		printf("ordinal=%d\r\n",Ordinal);
	 
    productKind = MX25L6406_ReadU16(secop(2002));
    FlashGetTorquePattern(TorquePatternVar,secop(2002), productKind);//Ť��ģʽ�ȴ�����ģʽ

	
	  MX25L6406_Read((u8*)&gearKind,secop(2022),1);
		printf("gearKind=%d\r\n",gearKind);
	  FlashReadGear(GearPatternVar,gearKind,secop(2021));                    //��λģʽ
   
			
	  FlashReadScreenVar(&ModifyVarStructVar,secop(2040));                //�ָ���һ�ν����ֵ
  

			
	  
	
	
	  FlashReadupComputerStruct(&upComputerStructVar ,secop(2001));    //������λ���޸Ĳ�Ʒ�ĸ��ֳ�����Ϣ
	 
	  if(ModifyVarStructVar.fabricName==0)ModifyVarStructVar.fabricName=1;
			
    ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);  //������˨
	  
	//add-2022-8-16  ADC�ɼ���ֵ������Ա�	
        ModifyVarStructVar.Angle = MX25L6406_ReadU16(secop(2020));                //�Ƕ�ģʽ
		printf("  ModifyVarStructVar.Angle=%d\r\n",  ModifyVarStructVar.Angle);
		
    //֪��ADS8688�ɼ�ADCֵ�ù���ԭ�����������
	//֪���ͻ��ṩ�Ĵ�������ADC�ɼ���ֵ�û����ϵƥ��Ϊ�Ƕ�ֵ
	//��ADC�ɼ��ĽǶ�ֵ��   ModifyVarStructVar.Angle �ԱȽ��пͻ�������
	
		

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








