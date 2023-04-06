#include "iwdg.h"

#include "includes.h"
/*******************************************************************************
* �� �� ��         : IWDG_Init
* ��������		   : IWDG��ʼ��
* ��    ��         : pre:Ԥ��Ƶϵ��(0-6)
					 rlr:��װ��ֵ(12λ��Χ0xfff)
					 �������Ź���λʱ����㹫ʽ��t=(4*2^pre*rlr)/40
* ��    ��         : ��
*******************************************************************************/
void IWDG_Init(u8 pre,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ȡ���Ĵ���д����
	IWDG_SetPrescaler(pre);//����Ԥ��Ƶϵ�� 0-6
	IWDG_SetReload(rlr);//������װ��ֵ
	IWDG_ReloadCounter();  //��װ�س�ֵ
	IWDG_Enable(); //�򿪶������Ź�
	
}


void WDC_INIT(void)
{
    
	
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ʹ�ܿ��Ź�
    IWDG_SetPrescaler(IWDG_Prescaler_64);//���ÿ��Ź���Ƶϵ��
	  IWDG_SetReload(1250);
    IWDG_ReloadCounter();				//ι��
    IWDG_Enable();
   
}



/*******************************************************************************
* �� �� ��         : IWDG_FeedDog
* ��������		   : ι��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void IWDG_FeedDog(void)  //ι��
{
	IWDG_ReloadCounter();  //��װ�س�ֵ
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
					//  printf("�����λ\r\n");
				IWDG_FeedDog(); 
				 }else {
					 
					 printf("����λ\r\n");
				 }
				 
			 }
			
			
			
			
			
		   if(TaskDogStrutVar.MemoryStart == 1){
				  TaskDogStrutVar.Memory++;
			 if(TaskDogStrutVar.Memory>100)
			  {
					printf("�����ݳ�ʱ\r\n");
				  NeedToResT = 1;
				  TaskDogStrutVar.Memory = 0;	
				}
			}
			 
//				TaskDogStrutVar.UdiskIn++;
//				if(TaskDogStrutVar.UdiskIn>20)
//				 {
//					 printf("����U�̳�ʱ\r\n");
//				  NeedToResT = 1;
//				 }
//			 
//				TaskDogStrutVar.UdiskOut++;
//				if(TaskDogStrutVar.UdiskOut>25)
//				 {
//					 printf("�ε�U�̳�ʱ\r\n");
//				  NeedToResT = 1;
//				 } 
				 
			 
		   TaskDogStrutVar.PcDebug++;
			 TaskDogStrutVar.Time++;
			
			
			
			
	
		}
	
	}



















