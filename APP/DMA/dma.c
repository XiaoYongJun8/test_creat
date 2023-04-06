#include "dma.h"
#include "uart.h"


void DMA_Configuration(void)
{
 //DMA��ͨ��14ӳ�䵽USART1��TX������
	
  DMA_InitTypeDef DMA_InitStructure;
	
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//��ֹ�洢�����洢��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //�洢��������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�洢���ĵ�ַ����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�������ַ����
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)0;   //
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;//���ڻ�������ַ

  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //���ݴ�����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;          
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //����ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;   //�����ȼ�
	DMA_InitStructure.DMA_BufferSize = 0;  //
	
	DMA_DeInit(DMA1_Channel4);
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	DMA_ClearFlag(DMA1_FLAG_TC4);//���������ɱ�־
	
	
	
	//DMA1��ͨ��15ӳ�䵽USART1��RX������
	
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���赽�洢��
//		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;     //�洢����ַ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);  //�����ַ
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_BufferSize = UART1_RX_BUFF_LENGTH;            //��ʾһ���԰�128���ֽ�


    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //ѭ��ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    
	  DMA_DeInit(DMA1_Channel5);
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel5, ENABLE);
		
		
		
		//DMA1��ͨ��17ӳ�䵽USART2��Tx������
		
		 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//��ֹ�洢�����洢��
	   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //�洢��������
	   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�洢���ĵ�ַ����
     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�������ַ����
		 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)0;       
	   DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_DR_Base;
	
	
		 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //���ݴ�����
	   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
		 DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //����ģʽ
	   DMA_InitStructure.DMA_Priority = DMA_Priority_Low;   //�����ȼ�

	   DMA_InitStructure.DMA_BufferSize = 0;  //
		
    DMA_DeInit(DMA1_Channel7);
	  DMA_Init(DMA1_Channel7, &DMA_InitStructure);
	 
		DMA_ClearFlag(DMA1_FLAG_TC4);   //������ͱ�־
    DMA_ClearFlag(DMA1_FLAG_TC7);
    DMA_ClearFlag(DMA1_FLAG_TC2);
		
	
	
	 
		
		//DMA1��ͨ��16ӳ�䵽USART2��Rx������
		
		
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���赽�洢��
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















