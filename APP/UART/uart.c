
#include  "uart.h"
#include  "dma.h"
#include "rs485.h"





//uint8_t RxBuffer1[UART1_RX_BUFF_LENGTH];

//uint8_t RxBuffer3[UART3_RX_BUFF_LENGTH];


volatile uint16_t RxPos1=0;





/*********************************************
�������ܣ���ʼ������1
PA9��TX
PA10��RX

************************************************/
uint8_t UART1_Init(uint32_t bps)
{

	  GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
  

    /* Configure USART1 Rx as input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //����
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	 /* Configure USART1 Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //ģ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
   
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = bps;//���ڲ�����
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	  USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Cmd(USART1, DISABLE);
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
    return 1;
	
}
/********************************************
TX:PA3
RX:PA2


**************************************/

uint8_t UART2_Init(uint32_t bps)
{
	
	   GPIO_InitTypeDef GPIO_InitStructure;
     USART_InitTypeDef USART_InitStructure;
	 /* Configure USART2 Tx as alternate function push-pull */
    
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //ģ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	  /* Configure USART2 Rx as input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //����
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
	
	  USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = bps;//���ڲ�����
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	  USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Cmd(USART2, DISABLE);
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);
	

    return 1;
} 


/*********************************************
�������ܣ���ʼ������3
PB10��TX
PB11��RX

************************************************/
uint8_t UART3_Init(uint32_t bps)
{

	  GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
  

    /* Configure USART3 Rx as input pull-up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //����
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	 /* Configure USART3 Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = bps;//���ڲ�����
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	  USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Cmd(USART3, DISABLE);
    USART_Init(USART3, &USART_InitStructure);
	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART3, ENABLE);
    return 1;
	
}

/*********************************************************************************************************
** ��������: UART1Write
** ��������: ���ͻ���������
** �䡡     ��: Data    -   �������ݻ�����ָ��
**                         NByte  -   �������ݸ���
** �䡡     ��: UART_NO_ERROR -- 0:  �ɹ�
**           UART_MSG_TOO_BIG -- 2: ���� ����
                    UART_BUSY -- 3: ����æ
**
** ����     ��: shy
** �ա�     ��: 2020��6��7��
********************************************************************************************************/

uint8_t UART1Write(uint8_t *Data, uint16_t NByte)
{
    CPU_IntDis();
    while(DMA1_Channel4->CNDTR) {
		CPU_IntEn();
		OSTimeDly(1);
		CPU_IntDis();
    }
    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA1_Channel4->CNDTR=NByte;			//���÷��ͳ���
    DMA1_Channel4->CMAR=(uint32_t)Data;	//�洢����ַ
    DMA_Cmd(DMA1_Channel4, ENABLE);		//����DMA����
    while(DMA1_Channel4->CNDTR) {
        CPU_IntEn();
        OSTimeDly(1);
        CPU_IntDis();
    }
    CPU_IntEn();
		
    return UART_NO_ERROR;
}






/*************************************************************
void USART1_IRQHandler(void)                	//����4�жϷ������
{
	
	uint8_t r = 0;
	if(USART_GetITStatus(USART1, USART_FLAG_ORE) != RESET)  //�����ж�
	{	
	  USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
	}   
	
	 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	 
    {
         r = USART_ReceiveData(USART1);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
		
}

*******************************************************************/







void uart_init(void)
{

  UART1_Init(115200);    //��ʼ������
 UART3_Init(115200);
	RS485_Init(115200);

 DMA_Configuration();  //����DMA
	
 USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);  //ʹ�ܴ���1��DMAͨ��
 USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	

    
  
   
    

	
    USART_Cmd(USART1, ENABLE);   //ʹ�ܴ���
    USART_Cmd(USART3, ENABLE);
	  USART_Cmd(USART2, ENABLE);
}



/********************************************************
�������ܣ�ͨ������3���͵��ֽ�

***********************************************************/

void  SendChar(uint8_t t)
{
   
	  USART_SendData(USART3,t);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
    while((USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET));//�ȴ����ڷ������
	 
}


/*********************************************************
�������ܣ�����1��ӳ��

*******************************************************/

int fputc(int ch, FILE *f)
{
    uint8_t ch1[1];
    ch1[0]=ch;
    UART1Write(ch1,1);
    return ch;
}





void  SendNU8(uint8_t *pData,uint16_t DataLen)

{
	int i ;
  for( i=0;i<DataLen;i++)
	{
		
	  TX_8(pData[i]);
	
	}
}


void SendNU16(uint16_t*pData,uint16_t DataLen)
{

  int i=0;
	for(i=0;i<DataLen;i++)
	{
		
		TX_16(pData[i]);
		
	}

}

void  SendNU32(uint32_t*pData,uint16_t DataLen)
{
	 int i = 0;
	for(i=0;i<DataLen;i++)
	{
	
	TX_32(pData[i]);
		
	}
	
}










/************************************************
*  \brief  ���ڷ������ַ���
*  \param  �ַ���
************************************************/



void SendStrings(uint8_t *str)
{
    while(*str)
    {
        TX_8(*str);
        str++;
    }
}













 
 

 
 
 /*!
*   \brief  ����1���ֽ�
*   \param  t ���͵��ֽ�
*/
void  USART2_SendChar(uint8_t t)
{
    USART_SendData(USART2,t);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    while((USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET));//�ȴ����ڷ������
}

void USART2_SendString(uint8_t* pStr,uint8_t size)
 {
    int i = 0;
	  for(i=0;i<size;i++)
		 {
		  USART2_SendChar(pStr[i]);
		 }
		 
 }



 
 
 
 
 
 
 
 
 
 




