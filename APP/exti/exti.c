

#include "led.h"
#include "screenshow.h"
#include "exti.h"
#include "screendriver.h"
/*********************************
KEYA:TIM8_CH2:PC7
KEYB:TIM8_CH3:PC8
KEYC:TIM8_CH4:PC9

TIM8:72M
*******************************/

void Input_Init(void)
{

 /*********************GPIO������*********************************************/
	EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9  ;//�ܽ�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;;	 //������������ģʽ���߸���ģʽ
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */


	
	/* EXTI line(PC789) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7); 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8); 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9); 
	EXTI_InitStructure.EXTI_Line = EXTI_Line8 | EXTI_Line7 | EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
	
	
}



/**********************************************************************
�������ܣ���ť���ƿؼ���������������
�����������ޣ���ť��4��״̬����ʱ�룬˳ʱ�룬������ʱ�룬����˳ʱ��
              �ֱ��Ӧ΢�������ؼ�(��С)��
                  ��Ӧ΢�������ؼ�(����)
                  ��Ӧ����ȱ����ؼ�(��С)
                  ��Ӧ����ȱ����ؼ�(����)��  
***********************************************************************/
uint32_t dataa = 0;
void  EXTI9_5_IRQHandler()
{
	
	
	  static	 uint8_t startflag = 100; 
											 
if(EXTI_GetITStatus(EXTI_Line7)==1&&KEYC)  //
	{ 
	
		switch(KeyModeVar.Mode)
		{
		  case 0:   if(KEYB) func_index=table[func_index].up; 
		            if(KEYB==0)func_index=table[func_index].down;  //˳ʱ��
		            break;
									 
		  case 1:	  if(KEYB){
			          ModiVarDec(KeyModeVar.ModifyVarFlag);
			          break;	
		            }
			          if(KEYB==0){
									
									ModiVarAdd(KeyModeVar.ModifyVarFlag);				
								}	break;					                                      					 	
		}
		
 // if(func_index != startflag)
 // { 
	   current_operation_index=table[func_index].current_operation;//ָ���������
    (*current_operation_index)();//ִ�е�ǰ��������
		startflag = func_index ;
	//}
  		 
 }
   
if(EXTI_GetITStatus(EXTI_Line7)==1&&(KEYC==0)) //����ȥ
	{ 
	
		switch(KeyModeVar.Mode)
		{						 
			case 1:	  if(KEYB)ModiVarDecWide(KeyModeVar.ModifyVarFlag);
			          if(KEYB==0)ModiVarAddWide(KeyModeVar.ModifyVarFlag); break;					
										                                      					 			
		}
	
  if(func_index != startflag)
  { 
	  current_operation_index=table[func_index].current_operation;//ָ���������
    (*current_operation_index)();//ִ�е�ǰ��������
		startflag = func_index ;
	}
  	 
 }	
	
	EXTI_ClearITPendingBit(EXTI_Line9);
  EXTI_ClearITPendingBit(EXTI_Line7);
	EXTI_ClearITPendingBit(EXTI_Line8);
	
}

















