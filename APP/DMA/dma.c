#include "dma.h"
#include "uart.h"


void DMA_Configuration(void)
{
 //DMA的通道14映射到USART1的TX引脚上
	
  DMA_InitTypeDef DMA_InitStructure;
	
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//禁止存储器到存储器
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //存储器到外设
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //存储器的地址增量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设基地址不变
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)0;   //
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;//串口缓冲区地址

  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //数据传输宽度
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;          
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;   //低优先级
	DMA_InitStructure.DMA_BufferSize = 0;  //
	
	DMA_DeInit(DMA1_Channel4);
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	DMA_ClearFlag(DMA1_FLAG_TC4);//清除发送完成标志
	
	
	
	//DMA1的通道15映射到USART1的RX引脚上
	
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //外设到存储器
//		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;     //存储器地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  //外设地址
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_BufferSize = UART1_RX_BUFF_LENGTH;            //表示一次性帮128个字节


    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    
	  DMA_DeInit(DMA1_Channel5);
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel5, ENABLE);
		
		
		
		//DMA1的通道17映射到USART2的Tx引脚上
		
		 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//禁止存储器到存储器
	   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //存储器到外设
	   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //存储器的地址增量
     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设基地址不变
		 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)0;       
	   DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_DR_Base;
	
	
		 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //数据传输宽度
	   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
		 DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //正常模式
	   DMA_InitStructure.DMA_Priority = DMA_Priority_Low;   //低优先级

	   DMA_InitStructure.DMA_BufferSize = 0;  //
		
    DMA_DeInit(DMA1_Channel7);
	  DMA_Init(DMA1_Channel7, &DMA_InitStructure);
	 
		DMA_ClearFlag(DMA1_FLAG_TC4);   //清除发送标志
    DMA_ClearFlag(DMA1_FLAG_TC7);
    DMA_ClearFlag(DMA1_FLAG_TC2);
		
	
	
	 
		
		//DMA1的通道16映射到USART2的Rx引脚上
		
		
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //外设到存储器
	//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer2;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//	DMA_InitStructure.DMA_BufferSize = UART2_RX_BUFF_LENGTH;
		
		
   	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
		
		
	
	  DMA_DeInit(DMA1_Channel6);
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel6, ENABLE);

   
		
		
		
		
		
		
		
		
		
	

}















