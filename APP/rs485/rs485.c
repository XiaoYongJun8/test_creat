#include "rs485.h"
#include "SysTick.h"
#include "crc16.h"
#include "led.h"
#include "uart.h"
#include "pclink.h"
#include "includes.h"



/*******************************************************************************
* �� �� ��         : RS485_Init
* ��������		   : USART2��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/  

u8 USART2_RX_BUF[640] = {0};                   //���ջ��壬���64�ֽ�
u16 USART2_RX_CNT=0;                       //�����ֽڼ�����
u8 flagFrame=0;                         //֡������ɱ�־�������յ�һ֡������
uint32_t   Kind = 0 ;
unsigned char regGroup[5];  //Modbus�Ĵ����飬��ַΪ0x00~0x04
SysMemoryPara SysMemoryParaVar = {0};
void RS485_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOA\Gʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	//TX-485	//�������PA2
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		  //�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);		/* ��ʼ����������IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;	//RX-485	   //��������PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	    //ģ������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ��� 2
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���������ж�


	
	
}

	

//1ms��ʱ

void TIM2_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=1000;   //�Զ�װ��ֵ 
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	

	
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��	
}



//10ms��ʱ
void TIM4_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=20000;   //�Զ�װ��ֵ 
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	TIM_Cmd(TIM4,DISABLE); //ʹ�ܶ�ʱ��	
}








//���㷢�͵����ݳ��ȣ����ҽ����ݷŵ�*buf������                     
u16 UartRead(u8 *buf, u16 len)  
{
	 u16 i;
	if(len>USART2_RX_CNT)  //ָ����ȡ���ȴ���ʵ�ʽ��յ������ݳ���ʱ
	{
		len=USART2_RX_CNT; //��ȡ��������Ϊʵ�ʽ��յ������ݳ���
	}
	for(i=0;i<len;i++)  //�������յ������ݵ�����ָ����
	{
		*buf=USART2_RX_BUF[i];  //�����ݸ��Ƶ�buf��
		buf++;
	}
	USART2_RX_CNT=0;              //���ռ���������
	return len;                   //����ʵ�ʶ�ȡ����
}


u8 rs485_UartWrite(u8 *buf ,u16 len) 										//����
{
	u16 i=0; 

    for(i=0;i<=len;i++)
    {
	USART_SendData(USART2,buf[i]);	                                      //ͨ��USARTx���跢�͵�������
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);             //���ָ����USART��־λ������񣬷������ݿ�λ��
  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);             //���ָ����USART��־λ������񣬷������ݿ�λ��			
    }
		
 return 0 ;

}



 








				
void UartRxMonitor(u8 ms) //���ڽ��ռ��
{
	static u16 USART2_RX_BKP=0;  //����USART2_RC_BKP��ʱ�洢ʫ�䳤����ʵ�ʳ��ȱȽ�
	static u8 idletmr=0;        //������ʱ��
	if(USART2_RX_CNT>0)//���ռ�����������ʱ��������߿���ʱ��
	{
		if(USART2_RX_BKP!=USART2_RX_CNT) //���ռ������ı䣬���ս��յ�����ʱ��������м�ʱ
		{
			USART2_RX_BKP=USART2_RX_CNT;  //��ֵ��������ʵ�ʳ��ȸ�USART2_RX_BKP
			idletmr=0;                    //�����ʱ������
		}
		else                              ////���ռ�����δ�ı䣬�����߿���ʱ���ۼƿ���ʱ��
		{
			//�����һ֡�������֮ǰ�г���3.5���ֽ�ʱ���ͣ�٣������豸��ˢ�µ�ǰ����Ϣ���ٶ���һ���ֽ���һ���µ�����֡�Ŀ�ʼ
			if(idletmr<5)                  //����ʱ��С��1msʱ�������ۼ�
			{
				idletmr += ms;
				if(idletmr>=5)             //����ʱ��ﵽ1msʱ�����ж�Ϊ1֡�������
				{
					flagFrame=1;//����������־��֡������ϱ�־
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
* �� �� ��         : USART2_IRQHandler
* ��������		   : USART2�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/ 
void USART2_IRQHandler(void)
{
	u8 res;	                                    //�������ݻ������
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 	
		res =USART_ReceiveData(USART2);//;��ȡ���յ�������USART2->DR
		
		if(USART2_RX_CNT < sizeof(USART2_RX_BUF))    //һ��ֻ�ܽ���64���ֽڣ���Ϊ�趨�����Ը��󣬵��˷�ʱ��
		{
			USART2_RX_BUF[USART2_RX_CNT]=res;  //��¼���յ���ֵ
			USART2_RX_CNT++;        //ʹ����������1 
		}
	}
}

			 
/*******************************************************************************
* �� �� ��         : TIM2_IRQHandler
* ��������		   : TIM2�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void TIM2_IRQHandler(void)
{

	UartRxMonitor(1); //���ڽ��ռ��
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//�����ж�
}




	


 


 upComputerStruct upComputerStructVar = {0};
 uint8_t Memory = 0;
  uint8_t ReadMemory = 0;
 u8 gearkind = 0;
 uint8_t   productPos = 0;
//���������������������֡�Ľ��գ����ȹ��ܺ�����������ѭ���е���
void UartDriver()
{
 
	unsigned int crc = 0;
	unsigned char crch = 0,crcl = 0;
    u16 len = 0;

	u8 buf[640] = {0};
	 
	if(flagFrame)            //֡������ɱ�־�������յ�һ֡������
	{
	
		flagFrame=0;           //֡������ɱ�־����
	
		len = UartRead(buf,sizeof(buf));   //�����յ������������������
  
	
		
	if((buf[0]==0x5A)&&(buf[1]==0xA5))                   //�жϵ�ַ�ǲ���֡ͷ
		{
	    
			crc=GetCRC16(buf,len-2);       //����CRCУ��ֵ����ȥCRCУ��ֵ
			crch=crc>>8;    				//crc��λ
			crcl=crc&0xFF;					//crc��λ
			
			
		if((buf[len-2]==crch)&&(buf[len-1]==crcl))  //�ж�CRCУ���Ƿ���ȷ
			{
				
			  rs485_UartWrite(buf,len);  //������Ӧ֡	
		   
			 switch (buf[4])               //��������ִ�в���
				{
						
		  	 case 1:   setTime(PTR2U16(buf+7),buf[9],buf[10],buf[11],buf[12],buf[13]);break;      //����ʱ��;
			   case 3:   setAppearanceNumber(&buf[7],&upComputerStructVar,PTR2U16(&buf[5])); Memory  = appearanceNumberMem;  break;  //���ó������
     		 case 5:   setUserEquipName(&buf[7],&upComputerStructVar,PTR2U16(&buf[5]));   Memory = UserEquipNameMem; break;	     //�����豸����

			   case 7:   setUserEquipNumber(&buf[7],&upComputerStructVar,PTR2U16(&buf[5])); Memory =  appearanceNumberMem;  break;      //	�����豸���

			   case 9:  ToolsUnlock(&buf[8],&upComputerStructVar,PTR2U16(&buf[5])-1);   break;    //��������״̬

         case 10:    setPassWord(&buf[7],&upComputerStructVar,PTR2U16(&buf[5])) ; Memory = PassWordMem;   break;     //����ʹ������
         case 11:    setUsingTimes(&buf[7],&upComputerStructVar);SetTextInt32(0,9,upComputerStructVar.UsingTime,0,0); Memory = UsingTimesMem; break;      //����ʹ�ô���
					
                    //����Ʒ�������� 
				 case 17:  	 MX25L6406_WriteU16(secop(2002),0);productKind = PTR2U16(buf+7);getProduct(TorquePatternVar,productKind,buf);Memory =   productMem;  break;
				             
                  
         case 18:  printf("productKind=%d\r\n",productKind); productPos =  CompareBoltName(TorquePatternVar,&buf[7],productKind);printf("productPos=%d\r\n",productPos); if(productPos==0)break; GetBoltStruct(buf,TorquePatternVar,&BoltGardeDiaArrVar,productPos);Memory = BoltStructMem;break;
				 case 19:   getAngle(&ModifyVarStructVar.Angle,buf); SetTextInt32(3,4,ModifyVarStructVar.Angle,0,0);Memory =   AngleMemMem;  break;
					          //��λ�������� 
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






 // press = (4.6875*getMA1)-18.75; ������,75/h
void TIM4_IRQHandler(void)
{
  uint16_t buff[128] = {0};

	uint8_t i = 0;
	uint8_t j = 0;//����ѹ������
	uint8_t k = 0;//���������ٸ���
	uint8_t l = 0;//�Ƕȸ���
	float GetMa[10] = {0.0} ;//����ѹ����Ӧ��MA
	float GetMa1[10] = {0.0} ; //�����ƶ�Ӧ��MA
	float GetMa2[10] = {0.0} ; //�Ƕȴ�������Ӧ��MA

  //ADC_ShowPres(0,&ADCGetPress[0],8);
	//Get_AUTO_RST_Mode_Data(buff,40);//�ɼ�40�Ρ�0.5ms

	#if 0
	for(i=3 ;i<40;i = i+4)
	{
		GetMa[j++] = buff[i]/65536.0*10.24/500.0*1000;	
	}
	
  GetMa[0] = Maopao(GetMa,j);
	
	ADCGetPress[0] = (0.625*GetMa[0])-2.5;      //Bar 
#endif 

ADS8688_CollectTask();

    
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//�����ж�
}






















			


