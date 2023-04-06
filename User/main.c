
#include "includes.h"
#include "iwdg.h"
#define CH374HF_NO_CODE 

#include "CH374DRV.H"
#include "CH374HFM.H"

void  TaskStart(void* pData);

#define    TASK_START_STK_SIZE      600
#define    TASK_START_PRIO           3
#define    TASK_START_ID             3

#define     TASK_KEY_CONTROL_STK_SIZE   600
#define     TASK_KEY_CONTROL_PRIO       5
#define     TAST_KEY_CONTROL_ID        5

#define     TAST_TIME_STK_SIZE       1200
#define     TASK_TIME_PRIO          6
#define     TASK_TIME_ID             6

#define   TASK_USB_CONTROL_STK_SIZE    1200
#define   TASK_USB_CONTROL_PRIO        11
#define    TASK_USB_CONTROL_ID         11

#define   TASK_DOG_STK_SIZE    400
#define   TASK_DOG_PRIO        13
#define    TASK_DOG_ID         13



#define TASK_PCDEBUG_STK_SIZE            1450  
#define TASK_PCDEBUG_ID                  4  
#define TASK_PCDEBUG_PRIO                4  



#define TASK_MEMORY_STK_SIZE            1500
#define TASK_MEMORY_ID                  7  
#define TASK_MEMORY_PRIO                7  





OS_STK    TaskStartStk[TASK_START_STK_SIZE];                        //开始任务
OS_STK    TaskKeyControlStk[TASK_KEY_CONTROL_STK_SIZE];             //屏幕控制任务
OS_STK    TaskTimeStk[TAST_TIME_STK_SIZE];                          //时间任务
OS_STK    TaskPCDebugStk[TASK_PCDEBUG_STK_SIZE];                    //上位机通信任务
OS_STK    TaskMemoryStk[TASK_MEMORY_STK_SIZE ];                     //flash存储任务
OS_STK    TaskUsbControlStk[TASK_USB_CONTROL_STK_SIZE];             //usb任务
OS_STK    TaskDogStk[TASK_DOG_STK_SIZE];             //看门狗任务

__align(8) static OS_STK    TaskUsbControlStk[TASK_USB_CONTROL_STK_SIZE];

int main(void)
{
	
	OS_STK* pTop =NULL;
	OS_STK* pBot = NULL;
	INT32U size = 0;
	
  InitTarget();
	
	OSInit();       //操作系统初始化
	pTop = &TaskStartStk[TASK_START_STK_SIZE-1];
	pBot = &TaskStartStk[0];
	size = TASK_START_STK_SIZE;
	
	OSTaskCreateExt(TaskStart,     
		              (void*)0,
		               pTop,
		               TASK_START_PRIO,
		               TASK_START_ID,
		               pBot,
		               size,
		              (void*)0,
		              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

	OSStart();//操作系统开始工作
}





void  TaskStart(void* pData)
{

	OS_STK* pTop;
	OS_STK* pBot;
	INT32U size;
  static uint32_t i = 0;


	pData = pData;
	

	
	pTop = &TaskKeyControlStk[TASK_KEY_CONTROL_STK_SIZE-1];
	pBot = &TaskKeyControlStk[0];
	size = TASK_KEY_CONTROL_STK_SIZE;
	
	
	OSTaskCreateExt(TaskKeyControl,      //按键控制任务操作屏幕   5
		              (void*)0,
		               pTop,
		               TASK_KEY_CONTROL_PRIO,
		               TAST_KEY_CONTROL_ID,
		               pBot,
		               size,
		               (void*)0,
		               OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
								 


								 
	pTop = &TaskTimeStk[TAST_TIME_STK_SIZE-1];
	pBot = &TaskTimeStk[0];
	size = TAST_TIME_STK_SIZE;
									 
//	OSTaskCreateExt(TaskTime,      //时间任务       6
//		                  (void*)0,
//		                  pTop,
//		                  TASK_TIME_PRIO ,
//		                  TASK_TIME_ID,
//		                  pBot,
//		                  size,
//		                 (void*)0,
//		                  OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);		
//										 

//		
//	//上位机通信任务
//	pTop = &TaskPCDebugStk[TASK_PCDEBUG_STK_SIZE-1];
//	pBot = &TaskPCDebugStk[0];
//	size = TASK_PCDEBUG_STK_SIZE;
//	
//										 
//	OSTaskCreateExt(TaskPcDebug,
//				(void*)0,
//				pTop,
//				TASK_PCDEBUG_PRIO,     //116
//				TASK_PCDEBUG_ID,
//				pBot,
//				size,
//				(void*)0,
//				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	
//				
//				

//				
//		//usb任务
//  pTop = &TaskUsbControlStk[TASK_USB_CONTROL_STK_SIZE-1];
//	pBot = &TaskUsbControlStk[0];
//	size = TASK_USB_CONTROL_STK_SIZE;
//										 
//	OSTaskCreateExt(TaskUsbControl,
//				(void*)0,
//			  pTop,
//			  TASK_USB_CONTROL_PRIO,     
//			  TASK_USB_CONTROL_ID ,
//				pBot,
//				size,
//				(void*)0,
//				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
////				
////				
//   //flash任务
//  pTop = &TaskMemoryStk[TASK_MEMORY_STK_SIZE-1];
//	pBot = &TaskMemoryStk[0];
//	size = TASK_MEMORY_STK_SIZE;
//										 
//	OSTaskCreateExt(TaskMemory,
//				(void*)0,
//				pTop,
//				TASK_MEMORY_PRIO,     
//				TASK_MEMORY_ID,
//				pBot,
//				size,
//				(void*)0,
//				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		
//		


   //看门狗任务
	pTop = &TaskDogStk[TASK_DOG_STK_SIZE-1];
	pBot = &TaskDogStk[0];
	size = TASK_DOG_STK_SIZE;			
				
										 
	OSTaskCreateExt(TaskDog,
				(void*)0,
				pTop,
				TASK_DOG_PRIO,     
				TASK_DOG_ID ,
				pBot,
				size,
				(void*)0,
				OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);				
				
				
				
				
				
						

	while(1){
	
			   OSTimeDly(OS_TICKS_PER_SEC*20);
		
	
			//	 DAC8771_WRITE_CMD(0x05,30000);
	
		
	 }
	

}
