#include "iwdg.h"

#include "includes.h"
/*******************************************************************************
* 函 数 名         : IWDG_Init
* 函数功能		   : IWDG初始化
* 输    入         : pre:预分频系数(0-6)
					 rlr:重装载值(12位范围0xfff)
					 独立看门狗复位时间计算公式：t=(4*2^pre*rlr)/40
* 输    出         : 无
*******************************************************************************/
void IWDG_Init(u8 pre,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //取消寄存器写保护
	IWDG_SetPrescaler(pre);//设置预分频系数 0-6
	IWDG_SetReload(rlr);//设置重装载值
	IWDG_ReloadCounter();  //重装载初值
	IWDG_Enable(); //打开独立看门狗
	
}


void WDC_INIT(void)
{
    
	
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//使能看门狗
    IWDG_SetPrescaler(IWDG_Prescaler_64);//设置看门狗分频系数
	  IWDG_SetReload(1250);
    IWDG_ReloadCounter();				//喂狗
    IWDG_Enable();
   
}



/*******************************************************************************
* 函 数 名         : IWDG_FeedDog
* 函数功能		   : 喂狗
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void IWDG_FeedDog(void)  //喂狗
{
	IWDG_ReloadCounter();  //重装载初值
}



TaskDogStrut TaskDogStrutVar = {0};


void TaskDog(void *pData)
  {
	  
		

		static uint8_t NeedToResT = 0;
		static uint8_t ucCount1000ms = 10;
//		static uint8_t ucCount10s = 100;
		pData = pData;
		while(1){
			
			 OSTimeDly(20);               //100
			
			if(!(--ucCount1000ms))
			 { 
				 ucCount1000ms = 10;
				 if(NeedToResT==0){
					//  printf("程序归位\r\n");
				IWDG_FeedDog(); 
				 }else {
					 
					 printf("程序复位\r\n");
				 }
				 
			 }
			
			
			
			
			
		   if(TaskDogStrutVar.MemoryStart == 1){
				  TaskDogStrutVar.Memory++;
			 if(TaskDogStrutVar.Memory>100)
			  {
					printf("读数据超时\r\n");
				  NeedToResT = 1;
				  TaskDogStrutVar.Memory = 0;	
				}
			}
			 
//				TaskDogStrutVar.UdiskIn++;
//				if(TaskDogStrutVar.UdiskIn>20)
//				 {
//					 printf("插入U盘超时\r\n");
//				  NeedToResT = 1;
//				 }
//			 
//				TaskDogStrutVar.UdiskOut++;
//				if(TaskDogStrutVar.UdiskOut>25)
//				 {
//					 printf("拔掉U盘超时\r\n");
//				  NeedToResT = 1;
//				 } 
				 
			 
		   TaskDogStrutVar.PcDebug++;
			 TaskDogStrutVar.Time++;
			
			
			
			
	
		}
	
	}



















