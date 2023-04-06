#include "CH374DRV.H"
#include "CH374HFM.H"
#include "string.h"
#include "iwdg.h"



/*
  *   CS       PB12   
  *   INT      PC6  
  *   SCLK     PB13 
  *   MISO     PB14                 
  *   MOSI     PB15                 
*/  


void SPI2_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;  
	  SPI_InitTypeDef  SPI_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	           //INT
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13;  /* mosi miso clk */
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
                                     
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;                      /* CS */
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    CH374_SPI_SCS_H;            //CS����

	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;/**< ����ȫ˫�� */
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;                /**< ���� */                                
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;                /**< 8λ */  
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;                  /**< ����Ϊ�ߵ�ƽ */
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;                 /**< �����ز��񣨿���Ϊ�ߵ�ƽʱ����1������Ϊ�½��أ� */      
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;                   /**< NSS�ź����������� */ 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;        /**< 72M / 4 = 18M */               
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;               /**< ���ݴ����MSBλ��ʼ */
	SPI_InitStructure.SPI_CRCPolynomial     = 7;                              /**< CRC7 */  
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE); 	
	
}
//SPI�շ�һ���ֽ�
UINT8 SPI3_TransByte(UINT8 TxData)
{		 			 
	while( RESET==SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)); 		//�ȴ��������� 
	SPI_I2S_SendData(SPI2, TxData); 	 	  		    //����һ��byte  
 	while( RESET==SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) );		//�ȴ�������һ��byte  
 	return( SPI_I2S_ReceiveData(SPI2) );          		    //�����յ�������				    
}

void Spi374Start( UINT8 addr, UINT8 cmd )  /* SPI��ʼ */
{
	CH374_SPI_SCS_L;    /* SPIƬѡ��Ч */
	SPI3_TransByte( addr );
	SPI3_TransByte( cmd );
}
void Spi374Stop( void )  /* SPI���� */
{
	CH374_SPI_SCS_H;	 /* SPIƬѡ��Ч */
}
//�ṩ������õĺ���
UINT8 CH374_READ_REGISTER( UINT8 mAddr )  /* �ⲿ����ı�CH374�������õ��ӳ���,��ָ���Ĵ�����ȡ���� */
{
	UINT8	d;
	Spi374Start( mAddr, CMD_SPI_374READ );
	d = SPI3_TransByte( 0xFF );
	Spi374Stop( );
	return( d );
}

void CH374_WRITE_REGISTER( UINT8 mAddr, UINT8 mData )           /* �ⲿ����ı�CH374�������õ��ӳ���,��ָ���Ĵ���д������ */
{
	Spi374Start( mAddr, CMD_SPI_374WRITE );
	SPI3_TransByte( mData );
	Spi374Stop( );
}

void CH374_READ_BLOCK( UINT8 mAddr, UINT8 mLen, PUINT8 mBuf )   /* �ⲿ����ı�CH374�������õ��ӳ���,��ָ����ʼ��ַ�������ݿ� */
{
	Spi374Start( mAddr, CMD_SPI_374READ );
	while ( mLen -- ) *mBuf++ = SPI3_TransByte( 0xFF );
	Spi374Stop( );
}

void CH374_WRITE_BLOCK( UINT8 mAddr, UINT8 mLen, PUINT8 mBuf )  /* �ⲿ����ı�CH374�������õ��ӳ���,��ָ����ʼ��ַд�����ݿ� */
{
	Spi374Start( mAddr, CMD_SPI_374WRITE );
	while ( mLen -- ) SPI3_TransByte( *mBuf++ );
	Spi374Stop( );
}

PUINT8	CH374_READ_BLOCK64( UINT8 mAddr, PUINT8 mBuf )         /* �ⲿ����ı�CH374�������õ��ӳ���,��˫����������64�ֽڵ����ݿ�,���ص�ǰ��ַ */
{
	UINT8	i;
	Spi374Start( mAddr, CMD_SPI_374READ );
	for ( i = CH374_BLOCK_SIZE; i != 0; i -- ) *mBuf++ = SPI3_TransByte( 0xFF );
	Spi374Stop( );
	return( mBuf );
}

PUINT8	CH374_WRITE_BLOCK64( UINT8 mAddr, PUINT8 mBuf )       /* �ⲿ����ı�CH374�������õ��ӳ���,��˫������д��64�ֽڵ����ݿ�,���ص�ǰ��ַ */
{
	UINT8	i;
	Spi374Start( mAddr, CMD_SPI_374WRITE );
	for ( i = CH374_BLOCK_SIZE; i != 0; i -- ) SPI3_TransByte( *mBuf++ );
	Spi374Stop( );
	return( mBuf );
}

void CH374_WRITE_BLOCK_C( UINT8 mLen, PUINT8C mBuf )          /* �ⲿ����ı�CH374�������õ��ӳ���,��RAM_HOST_TRANд�볣�������ݿ� */
{
	Spi374Start( RAM_HOST_TRAN, CMD_SPI_374WRITE );
	do {
		SPI3_TransByte( *mBuf );
		mBuf ++;
	} while ( -- mLen );
	Spi374Stop( );
}
//CH374�ӿڳ�ʼ��
void CH374_Init( void )
{
	SPI2_Init();
	
//	delay_ms(50);                                         /* ��ʱһ�� */
	//��д�Ĵ�������
	CH374_WRITE_REGISTER( REG_USB_ADDR,  0x5A ) ;
	if( CH374_READ_REGISTER( REG_USB_ADDR )!=0x5A )
	{
		printf("Comm Erro\n") ;
	}else
    {
       printf("Comm OK\n") ;
    }
   
}
/* ������״̬,�����������ʾ������벢ͣ�� */

/* ������״̬,�����������ʾ������벢ͣ�� */
void	mStopIfError( u8 iError )
{
	if ( iError == ERR_SUCCESS )return;                        /* �����ɹ� �����ź���*/
	printf( "Error: %02X\n", (UINT16)iError );                  /* ��ʾ���� */
}




void TaskUsbControl(void* pvdata)
 {
	 
	 
   
	 
	 pvdata = pvdata;
   uint8_t i =0;
    
	 while(1){
		 
     OSTimeDly(40);
		 
		 printf( "------------------Wait Udisk------------------------------\r\n" );
		 while ( CH374DiskStatus < DISK_CONNECT ) {            /* ��ѯCH375�жϲ������ж�״̬,�ȴ�U�̲��� */
			   OSTimeDly(10);
			   // TaskDogStrutVar.UdiskIn = 0;
  	     if ( CH374DiskConnect( ) == ERR_SUCCESS )    /* ���豸�����򷵻سɹ�,CH375DiskConnectͬʱ�����ȫ�ֱ���CH375DiskStatus */
           {
		           SYS_ON;
						   WDC_INIT();
						   break;
					 }	
		  }
		 
		 printf("-----------------------Disk Init---------------------------\r\n");
	  for ( i = 0; i < 5; i++ ) {                          /* �е�U�����Ƿ���δ׼����,�������Ա����� */
		
		  printf( "----------------------------Ready ---------------------------\r\n" );
			if ( CH374DiskReady( ) == ERR_SUCCESS ) break;    /* ��ѯ�����Ƿ�׼���� */
		}	
			
			
			
		printf( "-------------DiskSize---------------------------\r\n" );
		i = CH374DiskSize( );  
		mStopIfError( i );
		printf( "TotalSize = %u MB \r\n", (unsigned int)( mCmdParam.DiskSize.mDiskSizeSec * (CH374vSectorSize/512) / 2048 ) );  // ��ʾΪ��MBΪ���   	

    printf( "-------------------CreateFILeName-----------------\r\n" );                                 //���ڴ���ʱ��ᳬ�� /1.c

		mCmdParam.Create.mPathName[0] = '/';
		mCmdParam.Create.mPathName[1] = 'D';
		mCmdParam.Create.mPathName[2] = 'A';
		mCmdParam.Create.mPathName[3] = 'T';
		mCmdParam.Create.mPathName[4] = 'A';
		mCmdParam.Create.mPathName[5] = '.';
		mCmdParam.Create.mPathName[6] = 'C';
		mCmdParam.Create.mPathName[7] = 'S';
		mCmdParam.Create.mPathName[8] = 'V';
       mCmdParam.Create.mPathName[9] = 0;
		
	  i = CH374FileCreate( );                               /* �½��ļ�����,����ļ��Ѿ���������ɾ�������½� */
    mStopIfError( i );	
	  printf("Write some data to file %s\r\n",mCmdParam.Create.mPathName);


//        memcpy(&mCmdParam.ByteWrite.mByteBuffer[0],(const char*)"hello",5);
//				printf("mCmdParam.ByteWrite.mByteBuffer=%s\r\n",mCmdParam.ByteWrite.mByteBuffer);
//        mCmdParam.ByteWrite.mByteCount = 5; 
//        i = CH374ByteWrite( );                                /* ���ֽ�Ϊ��λ���ļ�д������,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO */
//	      mStopIfError( i );




     TaskDogStrutVar.MemoryStart = 1;
     WriteFile();
		 TaskDogStrutVar.MemoryStart = 0;
			 
		    SYS_OFF;
		printf("----------------CloseFile--------------\r\n");

	   mCmdParam.Close.mUpdateLen = 1;                       /* ��Ҫ�Զ������ļ�����,����Զ�����,��ô�ó�������CH374vSectorSize�ı��� */
	   i = CH374FileClose( );
		 mStopIfError( i );
 
		 
	 printf( "---------------------Take out\r\n----------------------------" );
		while ( 1 ) { 
          OSTimeDly(15);  
			     IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);//ʹ�ܿ��Ź�
			  // TaskDogStrutVar.UdiskOut = 0;                        /* û��ҪƵ����ѯ */
		if ( CH374DiskConnect( ) != ERR_SUCCESS )   /* ��ѯ��ʽ: �������Ƿ����Ӳ����´���״̬,���سɹ�˵������ */
	    {
			   SYS_OFF;
				  break;
			}

		} 
		 
  }
  
 }
	


































/****************************************************************************
�������ܣ��ھ��ַ����в��붺���γ����ַ���
����������uint8_t*pDest�����ж��ŵ����ַ���
          uint8_t*pSrc��û�ж��ŵľ��ַ���
          uint8_t arrLen[]���ھ��ַ����в���Ķ��ŵ�λ��
	        uint8_t count��λ������ĸ���
	
��������ֵ����
**************************************************************************/	
	
	
void BeCommaStr(uint8_t*pDest,uint8_t*pSrc,uint8_t arrLen[],uint8_t count)
	 {
	   uint16_t i = 0;
		  uint16_t j = 0;
		  uint16_t k = 0;
		 uint16_t len = 0;
		  uint16_t len1 = 0;

for(k=0;k<count;k++)                //   4  12   4  12  
  {	 
	for(i=len,j=len1;j<=arrLen[k]-1+len1;j++)
	  {
		 pDest[i++] = pSrc[j];
		}
	   pDest[i] = ',';
		 len1 = j;              //4 ,16,20        
		 len=i+1; 
				 
	}	
				
 }
	 
 
 
/*******************************************************************

�������ܣ���U���ļ�д���ַ���
����������uint8_t* pSrc����д����ַ���
          uint8_t size�� ÿ��д��U���ֽڵĳ���
          uint8_t len����д���ַ����ĳ���
��������ֵ����

********************************************************************/


void formationStr(uint8_t* pSrc,uint8_t size,uint8_t len)
  {
	  uint8_t j = 0;
		uint8_t i = 0;
		uint8_t count = 0;
	 for(j=0;j<len/size;j++)
		 {
			  OSTimeDly(10);
		    memcpy(mCmdParam.ByteWrite.mByteBuffer,(const char*)&pSrc[count],size);
        mCmdParam.ByteWrite.mByteCount = size; 
        i = CH374ByteWrite( );                                /* ���ֽ�Ϊ��λ���ļ�д������,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO */
	      mStopIfError( i );
		    count += size;	 
		 
		 }
		memcpy(mCmdParam.ByteWrite.mByteBuffer,(const char*)&pSrc[count],len%16);
    mCmdParam.ByteWrite.mByteCount =len%16; 
     i = CH374ByteWrite( );                                /* ���ֽ�Ϊ��λ���ļ�д������,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO */
	   mStopIfError( i );
	
	   memcpy(mCmdParam.ByteWrite.mByteBuffer,(const char*)"\r\n",2);
     mCmdParam.ByteWrite.mByteCount = 2; 
     i = CH374ByteWrite( );                                /* ���ֽ�Ϊ��λ���ļ�д������,���ζ�д�ĳ��Ȳ��ܳ���MAX_BYTE_IO */
	   mStopIfError( i );
	}
 
 
	
	uint8_t   nijumode[20]  ={0x54,0x6F,0x72,0x71,0x75,0x65,0x2F,0xC5,0xA4,0xBE,0xD8};
	uint8_t   luosmode[20] = {0x42,0x6F,0x6C,0x74,0x2F,0xC2,0xDD,0xCB,0xA8};
	uint8_t   gearmode[20] = {0x47,0x65,0x61,0x72,0x2F,0xB5,0xB2,0xCE,0xBB};
	uint8_t   anglemode[20] = {0x41,0x6E,0x67,0x6C,0x65,0x2F,0xBD,0xC7,0xB6,0xC8};
	uint8_t   sensormode[20] = {0x53,0x65,0x6E,0x73,0x6F,0x72,0x2F,0xB4,0xAB,0xB8,0xD0,0xC6,0xF7};
	uint8_t   zidongmode[20] = {0xD7,0xD4,0xB6,0xAF,0x2F,0x41,0x55,0x54,0x4F};
	uint8_t   shoudongmode[20] = {0xCA,0xD6,0xB6,0xAF,0x2F,0x48,0x41,0x4E,0x44};
	uint8_t   cuo[5] = {0xA1,0xC1};
	uint8_t   dui[5] = {0xA1,0xCC};
	

	
uint8_t  arrChina[170] = {0xD0,0xF2,0xBA,0xC5,0x2C,
	            0xB9,0xA4,0xBE,0xDF,0xD0,0xCD,0xBA,0xC5,0x2C,
              0xB9,0xA4,0xBE,0xDF,0xB3,0xF6,0xB3,0xA7,0xB1,0xE0,0xBA,0xC5,0x2C,
              0xC8,0xD5,0xC6,0xDA,0x2C,
	            0xD3,0xC3,0xBB,0xA7,0xC9,0xE8,0xB1,0xB8,0xC3,0xFB,0xB3,0xC6,0x2C,
              0xD3,0xC3,0xBB,0xA7,0xC9,0xE8,0xB1,0xB8,0xB1,0xE0,0xBA,0xC5,0x2C,
	            0xB2,0xD9,0xD7,0xF7,0xC8,0xCB,0xD4,0xB1,0x2C,
              0xB6,0xD4,0xD3,0xA6,0xD1,0xB9,0xC1,0xA6,0x2C,
	            0xC4,0xBF,0xB1,0xEA,0xC5,0xA4,0xBE,0xD8,0x2C,
              0xCA,0xB5,0xBC,0xCA,0xC5,0xA4,0xBE,0xD8,0x2C,
	            0xC2,0xDD,0xCB,0xA8,0xB9,0xE6,0xB8,0xF1,0x2C,
              0xC2,0xDD,0xCB,0xA8,0xC7,0xBF,0xB6,0xC8,0xB5,0xC8,0xBC,0xB6,0x2C,
              0xC4,0xBF,0xB1,0xEA,0xBD,0xC7,0xB6,0xC8,0x2C,
              0xCA,0xB5,0xBC,0xCA,0xBD,0xC7,0xB6,0xC8,0x2C,
              0xB5,0xB2,0xCE,0xBB,0x2C,
              0xD1,0xA1,0xB6,0xA8,0xC4,0xA3,0xCA,0xBD,0x2C,
              0xB9,0xA4,0xD7,0xF7,0xB7,0xBD,0xCA,0xBD,0x2C,
              0xC5,0xA1,0xBD,0xF4,0xBD,0xE1,0xB9,0xFB,0x2C,};	
	
	
	
char arrEnglish[250] ="Number,Producttype,SerialNumber,Date,UserEquipmentItem,UserEquipmentNumber,Operator,WorkPressure,TargetTorque,ActualTorque,BoltSize,BoltStrength,TargetAngle,ActualAngle,Gear,SelectMode,WorkingMode,FasteningResult,";

void WriteFile(void)
 {
	
	 
  uint8_t buf[250] = {0};
	uint32_t ordinal = 0;    
	SysMemoryPara Data = {0};
	
	 uint32_t i = 0;
//	 uint32_t j = 0;
	 uint32_t addr = 0;

	
	 uint8_t len = 0;
		
	  ordinal = MX25L6406_ReadU32(secop(2046));
	   
  	printf("ordinal=%d\r\n",ordinal);
  
	
	
   formationStr(arrChina,16,strlen((char*)arrChina));
 //  printf("strlen((char*)arrChina)=%d\r\n",strlen((char*)arrChina));
	
	
	
	  formationStr((uint8_t*)arrEnglish,16,strlen((char*)arrEnglish));
	//  printf("strlen((char*)arrEnglish)=%d\r\n",strlen((char*)arrEnglish));

  
   for(i=0;i< ordinal;i++)
		{		
		  OSTimeDly(10);
		  
			TaskDogStrutVar.Memory = 0;
		  memset(buf,0,sizeof(buf));
     			
		  memset(&Data,0,sizeof(SysMemoryPara));
			      
		  addr = i*sizeof(SysMemoryPara);
			     
      MX25L6406_Read((u8*)&Data,addr,sizeof(SysMemoryPara));  //��ȡ
			    
			Data.ordinal = i;          //���
		  StructToStr((char*)buf,Data);
			      
		  len = strlen((char*)buf);
			      
      formationStr(buf,16,len);
          
   }
  	TaskDogStrutVar.Memory = 0;
    	 
 }
 
	

	
	
void StructToStr(char buf[],SysMemoryPara SysMemoryParaVar) 
  {
	  char str[30]  = {0};
		float press = 0.0;
		char i = 0;
		char len = 0;
		char count = 0;

		memset(str,0,sizeof(str));
	//	printf("SysMemoryParaVar.ordinal=%d\r\n",SysMemoryParaVar.ordinal);
	  sprintf(str,"%d",SysMemoryParaVar.ordinal);              //���
		
		len = strlen(str);
	  for(i=0;i<len;i++)
		 {
			 
			 buf[count++] = str[i];
		 }
		 buf[count] = ',';
		 count = count +1;
		
		 
		 
		 len = strlen((char*)SysMemoryParaVar.ProductType);                   //��Ʒ�ͺ�
		 if(len>10)
		 {
			 len = 10;
		 }
		// printf("SysMemoryParaVar.ProductType=%s\r\n",SysMemoryParaVar.ProductType);
		 strncpy(&buf[count],(char*)SysMemoryParaVar.ProductType,len);
		
		 buf[count+len] = ',';
		 count = count+len+1;
		 
	
		 
		 
		// printf("SysMemoryParaVar.TolFacNum=%s\r\n",SysMemoryParaVar.TolFacNum);
		 len = strlen((char*)SysMemoryParaVar.TolFacNum);              //�������     
		 strncpy(&buf[count],(char*)SysMemoryParaVar.TolFacNum,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;
		 
		// printf("SysMemoryParaVar.year=%d\r\n",SysMemoryParaVar.year);
		 memset(str,0,sizeof(str));                             //��
		 sprintf(str,"%d",SysMemoryParaVar.year);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				if(str[0] == '0')break;
			  buf[count++] = str[i];
		  }
		  buf[count] = '.';
		  count = count+1;
		 
		// printf("SysMemoryParaVar.month=%d\r\n",SysMemoryParaVar.month);
		 memset(str,0,sizeof(str));                             //��
		 sprintf(str,"%d",SysMemoryParaVar.month);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				if(str[0] == '0')break;
			  buf[count++] = str[i];
		  }
		  buf[count] = '.';
		  count = count+1;
		 
	//	 printf("SysMemoryParaVar.day=%d\r\n",SysMemoryParaVar.day);
		 memset(str,0,sizeof(str));                             //��
		 sprintf(str,"%d",SysMemoryParaVar.day);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				if(str[0] == '0')break;
			  buf[count++] = str[i];
		  }
		  buf[count] = '-';
		  count = count+1;
			
		
	//	 printf("SysMemoryParaVar.hour=%d\r\n",SysMemoryParaVar.hour);
		 memset(str,0,sizeof(str));                             //ʱ
		 sprintf(str,"%d",SysMemoryParaVar.hour);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				
			  buf[count++] = str[i];
		  }
		  buf[count] = ':';
		  count = count+1;
			
			
	//	 printf("SysMemoryParaVar.min=%d\r\n",SysMemoryParaVar.min);	
		 memset(str,0,sizeof(str));                              //��
		 sprintf(str,"%d",SysMemoryParaVar.min);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
			
			  buf[count++] = str[i];
		  }
		  buf[count] = ':';
		  count = count+1;
			
	//	printf("SysMemoryParaVar.sec=%d\r\n",SysMemoryParaVar.sec);	
		 memset(str,0,sizeof(str));                             //��
		 sprintf(str,"%d",SysMemoryParaVar.sec);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
			  buf[count++] = str[i];
		  }
		  buf[count] = ',';
		  count = count+1;
			
	//	printf("SysMemoryParaVar.devname=%s\r\n",SysMemoryParaVar.devname);	
		 len = strlen((char*)SysMemoryParaVar.devname);              //�豸����   
		 strncpy(&buf[count],(char*)SysMemoryParaVar.devname,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;
			
			
	//	printf("SysMemoryParaVar.devnum=%s\r\n",SysMemoryParaVar.devnum);
		 len = strlen((char*)SysMemoryParaVar.devnum);              //�豸���  
		 strncpy(&buf[count],(char*)SysMemoryParaVar.devnum,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;
			
	//	 printf("SysMemoryParaVar.operate=%s\r\n",SysMemoryParaVar.operate);
		 len = strlen((char*)SysMemoryParaVar.operate);              //������Ա
		 strncpy(&buf[count],(char*)SysMemoryParaVar.operate,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;	
		 
		// printf("SysMemoryParaVar.PressUint=%d\r\n",SysMemoryParaVar.PressUint);
		 ;
		 switch(SysMemoryParaVar.PressUint)           //flahs��ѹ����ʱ���Ӧѹ����chneg100
		  {
			
			 case 0:  
				        press = SysMemoryParaVar.WorkPress/100.0;        //bar
			  //        printf("SysMemoryParaVar.WorkPress=%d\r\n",SysMemoryParaVar.WorkPress);
			//	        printf("press=%0.2f\r\n",press);
				        memset(str,0,sizeof(str));                             
		            sprintf(str,"%.2f",press);
				        len = strlen(str);
                for(i=0;i<len;i++)
		            {
			              buf[count++] = str[i];
		            }
								strncpy(&buf[count],"bar",3);
								count = count+3;
		            buf[count] = ',';
		  
								count = count+1;
                break; 
        			        
			 case 1:  press = SysMemoryParaVar.WorkPress/1000.0;      //Mpa
				        memset(str,0,sizeof(str));                             
		            sprintf(str,"%0.2f",press);
								len = strlen(str);
                for(i=0;i<len;i++)
		            {
			              buf[count++] = str[i];
		            }
								memcpy(&buf[count],"Mpa",3);
								count = count+3;
		            buf[count] = ',';
		            count = count+1;
								
                break; 







			
			 case 2:  press = SysMemoryParaVar.WorkPress/100.0*14;    //Psi
				        memset(str,0,sizeof(str));                             
		            sprintf(str,"%0.2f",press);
								len = strlen(str);
                for(i=0;i<len;i++)
		            {
			              buf[count++] = str[i];
		            }
								strncpy(&buf[count],"Psi",3);
								count = count+3;
		            buf[count] = ',';
		            count = count+1;
                break;         

			}
		 
		 printf("SysMemoryParaVar.TorqueUint=%d\r\n",SysMemoryParaVar.TorqueUint); 
			printf("SysMemoryParaVar.tarque=%d\r\n",SysMemoryParaVar.tarque);
		switch(SysMemoryParaVar.TorqueUint)
		 {
		 
			case 0 : memset(str,0,sizeof(str));                             //Ŀ��Ť��
		           sprintf(str,"%d",SysMemoryParaVar.tarque);
		           len = strlen(str);
	             for(i=0;i<len;i++)
		            {
			          buf[count++] = str[i];
		            }
								strncpy(&buf[count],"N.m",3);
								count = count+3;
							  buf[count] = ',';
		            count = count+1;
								break;
		
		case 1 :   memset(str,0,sizeof(str));                             //Ŀ��Ť��
		           sprintf(str,"%d",ROUND_TO_UINT32(SysMemoryParaVar.tarque/1.3549));
		           len = strlen(str);
	             for(i=0;i<len;i++)
		            {
			          buf[count++] = str[i];
		            }
								strncpy(&buf[count],"ft.lbs",6);
								count = count+6;
							  buf[count] = ',';
		            count = count+1;
		           	break;
		 
		 }			
		 	
			
		printf("SysMemoryParaVar.actque=%d\r\n",SysMemoryParaVar.actque);
		switch(SysMemoryParaVar.TorqueUint)
		 {
		 
			case 0 : memset(str,0,sizeof(str));                             //ʵ��Ť��
		           sprintf(str,"%d",SysMemoryParaVar.actque);
		           len = strlen(str);
	             for(i=0;i<len;i++)
		            {
			          buf[count++] = str[i];
		            }
								strncpy(&buf[count],"N.m",3);
								count = count+3;
							  buf[count] = ',';
		 
								count = count+1;
								break;
		
		case 1 :   memset(str,0,sizeof(str));                            
		           sprintf(str,"%d",ROUND_TO_UINT32(SysMemoryParaVar.actque/1.3549));
		           len = strlen(str);
	             for(i=0;i<len;i++)
		            {
			          buf[count++] = str[i];
		            }
								strncpy(&buf[count],"ft.lbs",6);
								count = count+6;
							  buf[count] = ',';
		            count = count+1;
		           	break;
		
		 }
			
		
			

		 buf[count] = 0x20;
		  count = count+1;
		 len = strlen((char*)SysMemoryParaVar.BoltDia);              //��˨ֱ��
		 strncpy(&buf[count],(char*)SysMemoryParaVar.BoltDia,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;	
			
		 
		 printf("SysMemoryParaVar.BoltGarde=%s\r\n",SysMemoryParaVar.BoltGarde);
		 len = strlen((char*)SysMemoryParaVar.BoltGarde);              //��˨�ȼ�
		 strncpy(&buf[count],(char*)SysMemoryParaVar.BoltGarde,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;	

      printf("SysMemoryParaVar.tarangle=%d\r\n",SysMemoryParaVar.tarangle);
     memset(str,0,sizeof(str));                             //Ŀ��Ƕ�
		 sprintf(str,"%d",SysMemoryParaVar.tarangle);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				if(str[0] =='0') break;
			  buf[count++] = str[i];
		  }
		  buf[count] = ',';
		  count = count+1; 			
			
			printf("SysMemoryParaVar.actangle=%d\r\n",SysMemoryParaVar.actangle);
		 memset(str,0,sizeof(str));                             //ʵ�ʽǶ�
		 sprintf(str,"%d",SysMemoryParaVar.actangle);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				if(str[0] =='0') break;
			  buf[count++] = str[i];
		  }
		  buf[count] = ',';
		  count = count+1;
		 
			
			printf("SysMemoryParaVar.gear=%d\r\n",SysMemoryParaVar.gear);
     memset(str,0,sizeof(str));                             //��λ
		 sprintf(str,"%d",SysMemoryParaVar.gear);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				if(str[0] == '0')break;
			  buf[count++] = str[i];
		  }
		  buf[count] = ',';
		  count = count+1; 			
			
		

			printf("SysMemoryParaVar.mode=%d\r\n",SysMemoryParaVar.mode);
		switch(SysMemoryParaVar.mode)                              //ѡ��ģʽ
	  	{
			
			case 1:   	 len = strlen((char*)nijumode);              //��˨ģʽ
		               strncpy(&buf[count],(char*)nijumode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
		  case 2:   	 len = strlen((char*)luosmode);              //��˨�ȼ�
		               strncpy(&buf[count],(char*)luosmode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
				
					
			case 3:   	 len = strlen((char*)gearmode);              //��˨�ȼ�
		               strncpy(&buf[count],(char*)gearmode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
		 case 4:   	  len = strlen((char*)anglemode);              //��˨�ȼ�
		               strncpy(&buf[count],(char*)anglemode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
     case 5:   	   len = strlen((char*)sensormode);              //��˨�ȼ�
		               strncpy(&buf[count],(char*)sensormode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;									 
				

			}			
			                                                     
	printf("SysMemoryParaVar.workpattern=%d\r\n",SysMemoryParaVar.workpattern);
			switch(SysMemoryParaVar.workpattern)                    //������ʽ
			 {
				case  0:   len = strlen((char*)zidongmode);              
		               strncpy(&buf[count],(char*)zidongmode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
			  case  1:   len = strlen((char*)shoudongmode);              
		               strncpy(&buf[count],(char*)shoudongmode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;	 
		
			 }

			printf("SysMemoryParaVar.tigresult=%d\r\n",SysMemoryParaVar.tigresult);
			 
			 
			 
			 switch(SysMemoryParaVar.tigresult)                        //š�����
			  {
				 case 0:   len = strlen((char*)cuo);                     //
		               strncpy(&buf[count],(char*)cuo,len) ;
		               buf[count+len] = ',';
		               count = count+len+1; ; break;
				
				
				
				 case 1:   len = strlen((char*)dui);                        //
		               strncpy(&buf[count],(char*)dui,len) ;
		               buf[count+len] = ',';
		               count = count+len+1; ; break; 
				}
				
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	





























             
	
	






