
#include "MX25L.h"
#include "SysTick.h"






/***************************************************
PA5:SCK
PA6:MISO
PA7:MOSI
PA4:CS
�������ܣ�SPI1��ʼ��
*****************************************************/
void SPI1_Init(void)
{
	
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	/* SPI��IO������ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
	
}

/**********************************************************
�������ܣ�ͨ��SPI���ͺͽ���һ���ֽ�����
����������Ҫ���͵�����
��������ֵ��SPI������յ�����
**********************************************************/
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{		 			 
 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//�ȴ���������  
	
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ��byte  ����
		
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //�ȴ�������һ��byte  
 
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����	
 		    
}

/*************************************************************
�������ܣ�MX25L6404��ʼ��
������������
��������ֵ����
8M��1024*8K ��Ϊ128��block,2048��������32768ҳ��
ҳ����256B
������4K��
������64K

**************************************************************/

void MX25L6406_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
	/*��������SPI_FLASH_CS(PA4)*/  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;  
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;   /*����ʽ���*/  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init( GPIOA, &GPIO_InitStructure);  

	  /*��ѡflash*/ 
	 MX25L6406_CS_H;            

   SPI1_Init();

}

/***********************************
�������ܣ�оƬдʹ��(0X06)
������������
��������ֵ����

***********************************/


void MX25L6406_Write_EN(void)
{
	
	MX25L6406_CS_L;//CS����
	SPI1_ReadWriteByte(0x06);//����ָ��0x06
	MX25L6406_CS_H;//CS����
	
}


/***********************************
�������ܣ���״̬�Ĵ���0X05
������������
��������ֵ����

***********************************/
void MX25L6406_Read_status(void)
{
	u8 data;
	
	MX25L6406_CS_L;//CS����
	
	SPI1_ReadWriteByte(0x05);//����ָ��0x05
	//�������ղ����BUSYλ��״̬��ֱ����æ��0��
	do
	{
		data = SPI1_ReadWriteByte(0x00);//����һ����Ч���ݣ�Ŀ���ǽ���
	}while(data);
	//CS����
	MX25L6406_CS_H;
}

/**************************************************
�������ܣ���оƬ��ȡ���ݴ浽�ڴ���
����������data���ڴ��ַ��addr��оƬ��ַ��
��������ֵ����

******************************************************/
void MX25L6406_Read(u8 *data,u32 addr,u32 NumByteToRead)
{
	u32 i;

	MX25L6406_CS_L;	//CS����
	SPI1_ReadWriteByte(0x03);	//����ָ��0x03
	
	SPI1_ReadWriteByte(addr>>16);//����24λ��ַ���û���Ҫ�Ӹõ�ַ��ʼ��ȡ���ݵĵ�ַ��,�ȷ��͸�λ
	SPI1_ReadWriteByte(addr>>8);
	SPI1_ReadWriteByte(addr);
	
	for(i=0;i<NumByteToRead;i++)//����n�ν��գ���ȡ������
	{
		*data = SPI1_ReadWriteByte(0x00);
		data++;
	}
	
	MX25L6406_CS_H;//CS����
}


/**************************************************
�������ܣ�д���ݵ�оƬָ����ַ��(ҳд)(32768)
����������data���ڴ��ַ��addr��оƬ��ַ��
��������ֵ����


******************************************************/



void MX25L6406_Write_Page(u8* pBuffer,u32 addr,u16 NumToWrite)
{
  int i = 0;
	MX25L6406_Write_EN();	//дʹ��

	MX25L6406_CS_L;	//CS����

	SPI1_ReadWriteByte(0x02);	//����ָ��0x02(ҳд)
	
	SPI1_ReadWriteByte(addr>>16);//����24λ��ַ���û���Ҫ�Ӹõ�ַ��ʼд�����ݵĵ�ַ��
	SPI1_ReadWriteByte(addr>>8);
	SPI1_ReadWriteByte(addr);
	for( i=0;i<NumToWrite;i++)
	SPI1_ReadWriteByte(pBuffer[i]);//�������ͣ�д�룩һ������
	//CS����
	MX25L6406_CS_H;
	//��ȡBUSYλ�ж������Ƿ����
	MX25L6406_Read_status();
	
}

/******************************************************************************
�������ܣ���ҳд����
����������pBuffer��д�������
          WriteAddr:д��flash�ĵ�ַ
          NumToWriteByte:��д�����ݵĳ���
��������ֵ����
********************************************************************************/


void MX25L6406_Write_Page_Nocheck(u8* pBuffer,u32 WriteAddr,u16 NumToWriteByte)
{

  u16 pageremain;
	pageremain = 256 - WriteAddr%256;//��ҳʣ��Ŀռ�
	if(NumToWriteByte<pageremain) pageremain = NumToWriteByte; //д����ֽڱ�һҳʣ��Ŀռ�С
	while(1)
	{
	
	  MX25L6406_Write_Page(pBuffer,WriteAddr,pageremain);
	  if(NumToWriteByte==pageremain) break;
		else  
		{
		    pBuffer += pageremain;          //���ݵ�ַƫ��pageremain
			  WriteAddr += pageremain;        //flash��ַƫ��pageremain
			 NumToWriteByte -= pageremain;   //��ȥ��д�����ַ�
			 if(NumToWriteByte>256) pageremain=256; //����Ѿ���ȥд�������ݻ��Ǳ�һҳ��
			 else pageremain = NumToWriteByte;
		}
	
	}

}

/*****************************************************************
�������ܣ���������
����������sddr:�������׵�ַ
��������ֵ����

***************************************************************/


void MX25L6406_Erase_Sector(u32 addr)
{

  addr*=4096;  //4K�ֽ�
	
  MX25L6406_Write_EN();//дʹ��
	MX25L6406_CS_L;//CS����
  SPI1_ReadWriteByte(0x20);  //��������
	
  SPI1_ReadWriteByte((u8)((addr)>>16));  //����24bit��ַ    
  SPI1_ReadWriteByte((u8)((addr)>>8));   
  SPI1_ReadWriteByte((u8)addr);  
	MX25L6406_CS_H;//CS����
	MX25L6406_Read_status();	//��ȡBUSYλ�ж������Ƿ����

}


u8 MX25L6406_Buff[4096];
/***************************************************************
�������ܣ�������������д��
����������pBuffer:��д���


***************************************************************/

void MX25L6406_Write(u8*pBuffer,u32 WriteAddr,u16 NumToWriteByte)

{

  u16 i=0;
	u32 secpos = 0;
	u16 secoff = 0;
	u16 secremain = 0;
	u8* MX25L6406_Buf;
	MX25L6406_Buf = MX25L6406_Buff;
	secpos = WriteAddr/4096;
	secoff = WriteAddr%4096;   //���￪ʼд
	secremain = 4096 - secoff;
	
	if(NumToWriteByte<secremain) secremain = NumToWriteByte;
	while(1)
	{
	  MX25L6406_Read(MX25L6406_Buf,secpos*4096,4096);  //������������������
		for(i=0;i<NumToWriteByte;i++)
		{
			if(MX25L6406_Buf[secoff+i]!=0xFF) break;
		}
	  if(i<secremain)   //��Ҫ����
		{
		    
		MX25L6406_Erase_Sector(secpos);//�����������
		for(i=0;i<secremain;i++)
			{
			MX25L6406_Buf[secoff+i] = pBuffer[i];
			}
			MX25L6406_Write_Page_Nocheck(MX25L6406_Buf,secpos*4096,4096);  //д����������
		
		}
		else MX25L6406_Write_Page_Nocheck(pBuffer,WriteAddr,secremain);//ֱ��д���Ѿ�������
	 if(NumToWriteByte==secremain) break;
		else
		{
		   secpos += 1;//������ַ��1
			 secoff = 0; //ƫ�Ƶ�ַΪ0
			
		   pBuffer += secremain; //
			 WriteAddr += secremain;
			 NumToWriteByte -= secremain;
			if(NumToWriteByte>4096) secremain = 4096;//��û��д��
			else secremain = NumToWriteByte;        //ֱ�ӿ���д��
		
		}
		
	}
	
}







/*************************************************************
�������ܣ�����оƬ��������ָ�0x20),�����ָ�0xD8��
����оƬ����ָ�0xC7��


************************************************************/

void MX25L6406_Erase(u32 addr,u8 cmd)
{
	
	MX25L6406_Write_EN();//дʹ��
	
	MX25L6406_CS_L;//CS����
	//����ָ��
	SPI1_ReadWriteByte(cmd);
	if(cmd==Sector || cmd==Block)
	{
		//����24λ��ַ���û���Ҫ�Ӹõ�ַ��ʼд�����ݵĵ�ַ��
		SPI1_ReadWriteByte(addr>>16);
		SPI1_ReadWriteByte(addr>>8);
		SPI1_ReadWriteByte(addr);
	}
	//CS����
	MX25L6406_CS_H;
	//��ȡBUSYλ�ж������Ƿ����
	MX25L6406_Read_status();
	
}



 void MX25L6406_Erase_Chip()
	{
	
	MX25L6406_Write_EN();//дʹ��
	MX25L6406_CS_L;//CS����
  SPI1_ReadWriteByte(0xc7);  //����оƬ
	MX25L6406_CS_H;//CS����
	MX25L6406_Read_status();	//��ȡBUSYλ�ж������Ƿ����
	
	
	}








/**************************************************************
�������ܣ���Ҫ����ı������յ�ַ�����ķ�ʽ�浽flash��
��������: pStr:Ҫ����ı����ַ�����count�ַ�������
          
��������ֵ��


***************************************************************/

void WriteStrToFlash(uint8_t* pStr,int count)
{
	
   char arrLastAddr[10] = {0}; //���潫ÿ��д���׵�ַ���浽flash��
	 uint32_t  LastAddr = 0;     //flash��ַ��ʹ�ϵ绹���Դ�ԭ���ĵ�ַд������
	 int  addrCount = 0;//��ַ���ӵĳ���
	
	
		MX25L6406_Read((u8*)arrLastAddr, secop(2010),10);//��ʼ��ʱ��������һ�δ�оƬ�ĵ�ַ
		LastAddr = atoi(arrLastAddr);             //���ַ���ת��Ϊ����

		MX25L6406_Write(pStr,LastAddr,count); //�����ݴ浽flash�ĵ�ַ��
    LastAddr+=count;                     //�����ַƫ��count���ֽ�
	  numToStr(arrLastAddr,LastAddr,&addrCount);	               //����ַװ��Ϊ�ַ��������浽�ַ�������
		
    MX25L6406_Write((u8*)arrLastAddr,secop(2010),addrCount); 	 //���ڶ���д��ĵ�ַ���浽flash�е�80000,�����ϵ��Ժ���˵һ��λ�ÿ�ʼ���������
    if(LastAddr>=secop(1888)) MX25L6406_Erase_Sector(secop(2010)); 
}





























void numToStr(char*str,int num,int* count)
{
 sprintf(str,"%d",num);
 *count = strlen(str);
}


void DoubleToStr(char*str,double num,int* count)
{
	

 sprintf(str,"%.1f",num);
 *count = strlen(str);

}




u32 MX25L6406_ReadU32(u32 addr)
{
    u8 buf[10] = {0};
    u32 data ;
    MX25L6406_Read(buf,addr,4);
    data =  ((u32)buf[0] << 24) | ((u32)buf[1] << 16) | ((u32)buf[2] << 8) | ((u32)buf[3]); 
    return data;
}


u16 MX25L6406_ReadU16(u32 addr)
{
    u8 buf[10] = {0};
		
    u16 data = 0;
    MX25L6406_Read(buf,addr,2);
		
    data =  (buf[0] << 8) | buf[1] ; 
    return data;
}



 void  MX25L6406_WriteU32(uint32_t addr,uint32_t num)
 {
    
		
    u8 buf[10] = {0};
	  
    buf[0] = (u8)(num >>24);
    buf[1] = (u8)(num >>16);
    buf[2] = (u8)(num >>8);
    buf[3] = (u8)num;
    MX25L6406_Write(buf,addr,4);
		
 }
 
 
 void  MX25L6406_WriteU16(uint32_t addr,uint16_t num)
 {
    
    u8 buf[10] = {0};
	
	 
    buf[0] = (u8)(num >>8);
    buf[1] = (u8)num;
    MX25L6406_Write(buf,addr,2);
		
 }
 
 
 
 /*********************************************************************
 �������ܣ�
 
 *********************************************************************/
 
 void  MX25L6406_WriteU32ARR(uint32_t*pData,uint32_t addr,uint32_t DataLen)
 {
 
   int i = 0;
	 for(i=0;i<DataLen;i++)
	  {
		   MX25L6406_WriteU32(addr,pData[i]);
			 addr+=sizeof(*pData);
		}
 }
 
 
  void  MX25L6406_WriteU16ARR(uint16_t*pData,uint32_t addr,uint32_t DataLen)
 {
 
   int i = 0;
	 for(i=0;i<DataLen;i++)
	  {
		   MX25L6406_WriteU16(addr,pData[i]);
			 addr+=sizeof(*pData);
		}
 }
 
 
 
 /**************************************************************************
 
 
 **************************************************************************/

 
 void  MX25L6406_ReadU32ARR(uint32_t*pData,uint32_t addr,uint32_t DataLen)
 {
 
   int i = 0;
	 for(i=0;i<DataLen;i++)
	  {
		   pData[i] = MX25L6406_ReadU32(addr);
			 addr+=sizeof(*pData);
		}
 }
 
 
 
  void  MX25L6406_ReadU16ARR(uint16_t*pData,uint32_t addr,uint32_t DataLen)
 {
 
   int i = 0;
	 for(i=0;i<DataLen;i++)
	  {
		   pData[i] = MX25L6406_ReadU16(addr);
			 addr+=sizeof(*pData);
		}
 }
 


 /****************************************************************************************
 �������ܣ�������������������תת��Ϊ����,�����¼��ϵ�����,���ظ�����,���浽flash��
 
 
 ******************************************************************************************/
 
 uint32_t  WreadNumFormFlash(uint32_t addr,uint32_t count,uint8_t readLen)
  {
	
	
	
	  uint32_t  num = 0;     //flash��ַ��ʹ�ϵ绹���Դ�ԭ���ĵ�ַд������
	  uint32_t  newNum = 0;
	 
 
		num =  MX25L6406_ReadU32(addr);
		newNum = num +count;                //�õ�Ҫ������µĸ���
		MX25L6406_WriteU32(addr,newNum);
		
    return newNum;                     //�����µĸ���
	
	
	}


uint16_t uCcount60S = 1500; 
void TaskMemory(void* pData)
 {
	 
//	 uint32_t i = 0;
//	 uint8_t size = 0;
	 uint32_t addr = 0;
//	 uint32_t  len = 0;
	 
	 pData = pData;

	 while(1)
	  {
			
		      
		OSTimeDly(8); 
//			  printf("TorqueModeSetPress=%0.2f\r\n",SetPress);
//		     printf("TorqueModeDacOutData=%d\r\n",DacOutData);
//            printf("ADCGetPress[0]=%0.2f\r\n",ADCGetPress[0]); 
			
			
			
    switch(Memory)
		 {
       
			case  productMem:         SYS_ON; CompareSaveTorquePattern(TorquePatternVar,secop(2002),productKind) ;SYS_OFF;  Memory = 0;    break;
		  case  BoltStructMem:      SYS_ON; SaveBoltGardeMeterArr(TorquePatternVar, &BoltGardeDiaArrVar,secop(2004),productPos);SYS_OFF; Memory = 0;     break;
		  case  appearanceNumberMem:SYS_ON; FlashWriteupComputerStruct(&upComputerStructVar ,secop(2001)) ;SYS_OFF;   Memory = 0;    break;
		  case  UserEquipNameMem:   SYS_ON; FlashWriteupComputerStruct(&upComputerStructVar ,secop(2001)) ; SYS_OFF;    Memory = 0;    break;
			case  UserEquipNumberMem: SYS_ON; FlashWriteupComputerStruct(&upComputerStructVar ,secop(2001)) ; SYS_OFF;   Memory = 0;    break;
			case  UserNameMem:        SYS_ON; FlashWriteupComputerStruct(&upComputerStructVar ,secop(2001)) ; SYS_OFF;         Memory = 0;   break;
			case  UsingTimesMem:      FlashWriteupComputerStruct(&upComputerStructVar ,secop(2001)) ;       Memory = 0;   break;
			case  PassWordMem:        SYS_ON; FlashWriteupComputerStruct(&upComputerStructVar ,secop(2001)) ; SYS_OFF;        Memory = 0;    break;
			case  AngleMemMem:        SYS_ON; MX25L6406_WriteU16(secop(2020),ModifyVarStructVar.Angle);SetTextInt32(3,4,ModifyVarStructVar.Angle,0,0);SYS_OFF;  Memory = 0;   break;
      case	GearMem:            SYS_ON; FlashWriteGear(GearPatternVar,gearKind,secop(2021));SYS_OFF;Memory = 0;     break;
			case	SensorMem:          SYS_ON; CompareSaveTorquePattern(TorquePatternVar,secop(2002),productKind) ; SYS_OFF;Memory = 0;    break;
      case	ToolLockMem:        Memory = 0;  break;
			case  ScreenMem:          FlashWriteScreenVar(&ModifyVarStructVar,secop(2040));MX25L6406_WriteU32(secop(2000),TorqueUint_C);
			                          if(PressMem==1){ 
                                   MX25L6406_Write((u8*)&ResetPress,secop(2047),sizeof(ResetPress));  //�������ģʽ��Ӧ��ѹ�������ֵ	
																	 PressMem = 0;
																}	Memory = 0; break;
			case  SysParaMem:         addr=(Ordinal-1)*sizeof(SysMemoryPara) ;
																if(addr >secop(1000))
																{
																	addr = 0;
																}
									
																MX25L6406_Write((u8*)&SysMemoryParaVar,addr,sizeof(SysMemoryPara));Memory = 0;break;
			 


		 }
		
	 }
				
}				



