

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

 /*********************GPIO口设置*********************************************/
	EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9  ;//管脚设置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;;	 //设置下拉输入模式或者浮空模式
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* 初始化GPIO */


	
	/* EXTI line(PC789) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7); 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8); 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9); 
	EXTI_InitStructure.EXTI_Line = EXTI_Line8 | EXTI_Line7 | EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
	
	
}



/**********************************************************************
函数功能：旋钮控制控件变量参数的增减
函数参数：无，旋钮有4种状态，逆时针，顺时针，按下逆时针，按下顺时针
              分别对应微调变量控件(减小)，
                  对应微调变量控件(增加)
                  对应大幅度变量控件(减小)
                  对应大幅度变量控件(增加)，  
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
		            if(KEYB==0)func_index=table[func_index].down;  //顺时针
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
	   current_operation_index=table[func_index].current_operation;//指向这个函数
    (*current_operation_index)();//执行当前操作函数
		startflag = func_index ;
	//}
  		 
 }
   
if(EXTI_GetITStatus(EXTI_Line7)==1&&(KEYC==0)) //按下去
	{ 
	
		switch(KeyModeVar.Mode)
		{						 
			case 1:	  if(KEYB)ModiVarDecWide(KeyModeVar.ModifyVarFlag);
			          if(KEYB==0)ModiVarAddWide(KeyModeVar.ModifyVarFlag); break;					
										                                      					 			
		}
	
  if(func_index != startflag)
  { 
	  current_operation_index=table[func_index].current_operation;//指向这个函数
    (*current_operation_index)();//执行当前操作函数
		startflag = func_index ;
	}
  	 
 }	
	
	EXTI_ClearITPendingBit(EXTI_Line9);
  EXTI_ClearITPendingBit(EXTI_Line7);
	EXTI_ClearITPendingBit(EXTI_Line8);
	
}

















