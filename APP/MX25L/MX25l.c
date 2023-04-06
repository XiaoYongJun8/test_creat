
#include "MX25L.h"
#include "SysTick.h"






/***************************************************
PA5:SCK
PA6:MISO
PA7:MOSI
PA4:CS
函数功能：SPI1初始化
*****************************************************/
void SPI1_Init(void)
{
	
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	/* SPI的IO口设置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
}

/**********************************************************
函数功能：通过SPI发送和接收一个字节数据
函数参数：要发送的数据
函数返回值：SPI最近接收的数据
**********************************************************/
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{		 			 
 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//等待发送区空  
	
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个byte  数据
		
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据	
 		    
}

/*************************************************************
函数功能：MX25L6404初始化
函数参数：无
函数返回值：无
8M：1024*8K 分为128个block,2048个扇区，32768页。
页区：256B
扇区：4K，
块区：64K

**************************************************************/

void MX25L6406_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
	/*配置输入SPI_FLASH_CS(PA4)*/  
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;  
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;   /*推挽式输出*/  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init( GPIOA, &GPIO_InitStructure);  

	  /*不选flash*/ 
	 MX25L6406_CS_H;            

   SPI1_Init();

}

/***********************************
函数功能：芯片写使能(0X06)
函数参数：无
函数返回值：无

***********************************/


void MX25L6406_Write_EN(void)
{
	
	MX25L6406_CS_L;//CS拉低
	SPI1_ReadWriteByte(0x06);//发送指令0x06
	MX25L6406_CS_H;//CS拉高
	
}


/***********************************
函数功能：读状态寄存器0X05
函数参数：无
函数返回值：无

***********************************/
void MX25L6406_Read_status(void)
{
	u8 data;
	
	MX25L6406_CS_L;//CS拉低
	
	SPI1_ReadWriteByte(0x05);//发送指令0x05
	//反复接收并检测BUSY位的状态，直到不忙（0）
	do
	{
		data = SPI1_ReadWriteByte(0x00);//发送一个无效数据，目的是接收
	}while(data);
	//CS拉高
	MX25L6406_CS_H;
}

/**************************************************
函数功能：从芯片读取数据存到内存中
函数参数：data：内存地址，addr：芯片地址，
函数返回值：无

******************************************************/
void MX25L6406_Read(u8 *data,u32 addr,u32 NumByteToRead)
{
	u32 i;

	MX25L6406_CS_L;	//CS拉低
	SPI1_ReadWriteByte(0x03);	//发送指令0x03
	
	SPI1_ReadWriteByte(addr>>16);//发送24位地址（用户想要从该地址开始读取数据的地址）,先发送高位
	SPI1_ReadWriteByte(addr>>8);
	SPI1_ReadWriteByte(addr);
	
	for(i=0;i<NumByteToRead;i++)//主机n次接收（读取）数据
	{
		*data = SPI1_ReadWriteByte(0x00);
		data++;
	}
	
	MX25L6406_CS_H;//CS拉高
}


/**************************************************
函数功能：写数据到芯片指定地址中(页写)(32768)
函数参数：data：内存地址，addr：芯片地址，
函数返回值：无


******************************************************/



void MX25L6406_Write_Page(u8* pBuffer,u32 addr,u16 NumToWrite)
{
  int i = 0;
	MX25L6406_Write_EN();	//写使能

	MX25L6406_CS_L;	//CS拉低

	SPI1_ReadWriteByte(0x02);	//发送指令0x02(页写)
	
	SPI1_ReadWriteByte(addr>>16);//发送24位地址（用户想要从该地址开始写入数据的地址）
	SPI1_ReadWriteByte(addr>>8);
	SPI1_ReadWriteByte(addr);
	for( i=0;i<NumToWrite;i++)
	SPI1_ReadWriteByte(pBuffer[i]);//主机发送（写入）一个数据
	//CS拉高
	MX25L6406_CS_H;
	//读取BUSY位判定操作是否完毕
	MX25L6406_Read_status();
	
}

/******************************************************************************
函数功能：换页写功能
函数参数：pBuffer待写入的数据
          WriteAddr:写入flash的地址
          NumToWriteByte:待写入数据的长度
函数返回值：无
********************************************************************************/


void MX25L6406_Write_Page_Nocheck(u8* pBuffer,u32 WriteAddr,u16 NumToWriteByte)
{

  u16 pageremain;
	pageremain = 256 - WriteAddr%256;//该页剩余的空间
	if(NumToWriteByte<pageremain) pageremain = NumToWriteByte; //写入的字节比一页剩余的空间小
	while(1)
	{
	
	  MX25L6406_Write_Page(pBuffer,WriteAddr,pageremain);
	  if(NumToWriteByte==pageremain) break;
		else  
		{
		    pBuffer += pageremain;          //数据地址偏移pageremain
			  WriteAddr += pageremain;        //flash地址偏移pageremain
			 NumToWriteByte -= pageremain;   //减去以写进的字符
			 if(NumToWriteByte>256) pageremain=256; //如果已经减去写进的内容还是比一页大
			 else pageremain = NumToWriteByte;
		}
	
	}

}

/*****************************************************************
函数功能：擦除扇区
函数参数：sddr:扇区的首地址
函数返回值：无

***************************************************************/


void MX25L6406_Erase_Sector(u32 addr)
{

  addr*=4096;  //4K字节
	
  MX25L6406_Write_EN();//写使能
	MX25L6406_CS_L;//CS拉低
  SPI1_ReadWriteByte(0x20);  //擦除扇区
	
  SPI1_ReadWriteByte((u8)((addr)>>16));  //发送24bit地址    
  SPI1_ReadWriteByte((u8)((addr)>>8));   
  SPI1_ReadWriteByte((u8)addr);  
	MX25L6406_CS_H;//CS拉高
	MX25L6406_Read_status();	//读取BUSY位判定操作是否完毕

}


u8 MX25L6406_Buff[4096];
/***************************************************************
函数功能：带扇区擦除的写入
函数参数；pBuffer:带写入的


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
	secoff = WriteAddr%4096;   //这里开始写
	secremain = 4096 - secoff;
	
	if(NumToWriteByte<secremain) secremain = NumToWriteByte;
	while(1)
	{
	  MX25L6406_Read(MX25L6406_Buf,secpos*4096,4096);  //读出整个扇区的内容
		for(i=0;i<NumToWriteByte;i++)
		{
			if(MX25L6406_Buf[secoff+i]!=0xFF) break;
		}
	  if(i<secremain)   //需要擦除
		{
		    
		MX25L6406_Erase_Sector(secpos);//擦除这个扇区
		for(i=0;i<secremain;i++)
			{
			MX25L6406_Buf[secoff+i] = pBuffer[i];
			}
			MX25L6406_Write_Page_Nocheck(MX25L6406_Buf,secpos*4096,4096);  //写入整个扇区
		
		}
		else MX25L6406_Write_Page_Nocheck(pBuffer,WriteAddr,secremain);//直接写入已经擦除的
	 if(NumToWriteByte==secremain) break;
		else
		{
		   secpos += 1;//扇区地址加1
			 secoff = 0; //偏移地址为0
			
		   pBuffer += secremain; //
			 WriteAddr += secremain;
			 NumToWriteByte -= secremain;
			if(NumToWriteByte>4096) secremain = 4096;//还没有写完
			else secremain = NumToWriteByte;        //直接可以写完
		
		}
		
	}
	
}







/*************************************************************
函数功能：擦除芯片扇区擦除指令（0x20),块擦除指令（0xD8）
整个芯片擦除指令（0xC7）


************************************************************/

void MX25L6406_Erase(u32 addr,u8 cmd)
{
	
	MX25L6406_Write_EN();//写使能
	
	MX25L6406_CS_L;//CS拉低
	//发送指令
	SPI1_ReadWriteByte(cmd);
	if(cmd==Sector || cmd==Block)
	{
		//发送24位地址（用户想要从该地址开始写入数据的地址）
		SPI1_ReadWriteByte(addr>>16);
		SPI1_ReadWriteByte(addr>>8);
		SPI1_ReadWriteByte(addr);
	}
	//CS拉高
	MX25L6406_CS_H;
	//读取BUSY位判定操作是否完毕
	MX25L6406_Read_status();
	
}



 void MX25L6406_Erase_Chip()
	{
	
	MX25L6406_Write_EN();//写使能
	MX25L6406_CS_L;//CS拉低
  SPI1_ReadWriteByte(0xc7);  //擦除芯片
	MX25L6406_CS_H;//CS拉高
	MX25L6406_Read_status();	//读取BUSY位判定操作是否完毕
	
	
	}








/**************************************************************
函数功能：将要保存的变量按照地址递增的方式存到flash中
函数参数: pStr:要保存的变量字符串，count字符串长度
          
函数返回值：


***************************************************************/

void WriteStrToFlash(uint8_t* pStr,int count)
{
	
   char arrLastAddr[10] = {0}; //保存将每次写的首地址保存到flash中
	 uint32_t  LastAddr = 0;     //flash地址即使断电还可以从原来的地址写入数据
	 int  addrCount = 0;//地址增加的长度
	
	
		MX25L6406_Read((u8*)arrLastAddr, secop(2010),10);//开始的时候读出最后一次存芯片的地址
		LastAddr = atoi(arrLastAddr);             //将字符串转换为数字

		MX25L6406_Write(pStr,LastAddr,count); //将数据存到flash的地址中
    LastAddr+=count;                     //保存地址偏移count个字节
	  numToStr(arrLastAddr,LastAddr,&addrCount);	               //将地址装换为字符串，保存到字符数组中
		
    MX25L6406_Write((u8*)arrLastAddr,secop(2010),addrCount); 	 //将第二次写入的地址保存到flash中的80000,重新上电以后还在说一次位置开始后面存数据
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
 函数功能：
 
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
 函数功能：从扇区读出来的数据转转化为整数,加上新加上的数字,返回该数字,并存到flash中
 
 
 ******************************************************************************************/
 
 uint32_t  WreadNumFormFlash(uint32_t addr,uint32_t count,uint8_t readLen)
  {
	
	
	
	  uint32_t  num = 0;     //flash地址即使断电还可以从原来的地址写入数据
	  uint32_t  newNum = 0;
	 
 
		num =  MX25L6406_ReadU32(addr);
		newNum = num +count;                //得到要保存的新的个数
		MX25L6406_WriteU32(addr,newNum);
		
    return newNum;                     //返回新的个数
	
	
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
                                   MX25L6406_Write((u8*)&ResetPress,secop(2047),sizeof(ResetPress));  //保存各个模式对应的压力和输出值	
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



