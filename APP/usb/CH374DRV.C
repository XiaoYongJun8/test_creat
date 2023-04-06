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
    
    CH374_SPI_SCS_H;            //CSÀ­¸ß

	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;/**< Á½ÏßÈ«Ë«¹¤ */
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;                /**< Ö÷»ú */                                
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;                /**< 8Î» */  
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;                  /**< ¿ÕÏÐÎª¸ßµçÆ½ */
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;                 /**< ÉÏÉýÑØ²¶»ñ£¨¿ÕÏÐÎª¸ßµçÆ½Ê±£¬µÚ1¸ö±ßÑØÎªÏÂ½µÑØ£© */      
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;                   /**< NSSÐÅºÅÓÉÈí¼þ¹ÜÀí */ 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;        /**< 72M / 4 = 18M */               
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;               /**< Êý¾Ý´«Êä´ÓMSBÎ»¿ªÊ¼ */
	SPI_InitStructure.SPI_CRCPolynomial     = 7;                              /**< CRC7 */  
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE); 	
	
}
//SPIÊÕ·¢Ò»¸ö×Ö½Ú
UINT8 SPI3_TransByte(UINT8 TxData)
{		 			 
	while( RESET==SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)); 		//µÈ´ý·¢ËÍÇø¿Õ 
	SPI_I2S_SendData(SPI2, TxData); 	 	  		    //·¢ËÍÒ»¸öbyte  
 	while( RESET==SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) );		//µÈ´ý½ÓÊÕÍêÒ»¸öbyte  
 	return( SPI_I2S_ReceiveData(SPI2) );          		    //·µ»ØÊÕµ½µÄÊý¾Ý				    
}

void Spi374Start( UINT8 addr, UINT8 cmd )  /* SPI¿ªÊ¼ */
{
	CH374_SPI_SCS_L;    /* SPIÆ¬Ñ¡ÓÐÐ§ */
	SPI3_TransByte( addr );
	SPI3_TransByte( cmd );
}
void Spi374Stop( void )  /* SPI½áÊø */
{
	CH374_SPI_SCS_H;	 /* SPIÆ¬Ñ¡ÎÞÐ§ */
}
//Ìá¹©¸ø¿âµ÷ÓÃµÄº¯Êý
UINT8 CH374_READ_REGISTER( UINT8 mAddr )  /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,´ÓÖ¸¶¨¼Ä´æÆ÷¶ÁÈ¡Êý¾Ý */
{
	UINT8	d;
	Spi374Start( mAddr, CMD_SPI_374READ );
	d = SPI3_TransByte( 0xFF );
	Spi374Stop( );
	return( d );
}

void CH374_WRITE_REGISTER( UINT8 mAddr, UINT8 mData )           /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,ÏòÖ¸¶¨¼Ä´æÆ÷Ð´ÈëÊý¾Ý */
{
	Spi374Start( mAddr, CMD_SPI_374WRITE );
	SPI3_TransByte( mData );
	Spi374Stop( );
}

void CH374_READ_BLOCK( UINT8 mAddr, UINT8 mLen, PUINT8 mBuf )   /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,´ÓÖ¸¶¨ÆðÊ¼µØÖ·¶Á³öÊý¾Ý¿é */
{
	Spi374Start( mAddr, CMD_SPI_374READ );
	while ( mLen -- ) *mBuf++ = SPI3_TransByte( 0xFF );
	Spi374Stop( );
}

void CH374_WRITE_BLOCK( UINT8 mAddr, UINT8 mLen, PUINT8 mBuf )  /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,ÏòÖ¸¶¨ÆðÊ¼µØÖ·Ð´ÈëÊý¾Ý¿é */
{
	Spi374Start( mAddr, CMD_SPI_374WRITE );
	while ( mLen -- ) SPI3_TransByte( *mBuf++ );
	Spi374Stop( );
}

PUINT8	CH374_READ_BLOCK64( UINT8 mAddr, PUINT8 mBuf )         /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,´ÓË«»º³åÇø¶Á³ö64×Ö½ÚµÄÊý¾Ý¿é,·µ»Øµ±Ç°µØÖ· */
{
	UINT8	i;
	Spi374Start( mAddr, CMD_SPI_374READ );
	for ( i = CH374_BLOCK_SIZE; i != 0; i -- ) *mBuf++ = SPI3_TransByte( 0xFF );
	Spi374Stop( );
	return( mBuf );
}

PUINT8	CH374_WRITE_BLOCK64( UINT8 mAddr, PUINT8 mBuf )       /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,ÏòË«»º³åÇøÐ´Èë64×Ö½ÚµÄÊý¾Ý¿é,·µ»Øµ±Ç°µØÖ· */
{
	UINT8	i;
	Spi374Start( mAddr, CMD_SPI_374WRITE );
	for ( i = CH374_BLOCK_SIZE; i != 0; i -- ) SPI3_TransByte( *mBuf++ );
	Spi374Stop( );
	return( mBuf );
}

void CH374_WRITE_BLOCK_C( UINT8 mLen, PUINT8C mBuf )          /* Íâ²¿¶¨ÒåµÄ±»CH374³ÌÐò¿âµ÷ÓÃµÄ×Ó³ÌÐò,ÏòRAM_HOST_TRANÐ´Èë³£Á¿ÐÍÊý¾Ý¿é */
{
	Spi374Start( RAM_HOST_TRAN, CMD_SPI_374WRITE );
	do {
		SPI3_TransByte( *mBuf );
		mBuf ++;
	} while ( -- mLen );
	Spi374Stop( );
}
//CH374½Ó¿Ú³õÊ¼»¯
void CH374_Init( void )
{
	SPI2_Init();
	
//	delay_ms(50);                                         /* ÑÓÊ±Ò»ÏÂ */
	//¶ÁÐ´¼Ä´æÆ÷²âÊÔ
	CH374_WRITE_REGISTER( REG_USB_ADDR,  0x5A ) ;
	if( CH374_READ_REGISTER( REG_USB_ADDR )!=0x5A )
	{
		printf("Comm Erro\n") ;
	}else
    {
       printf("Comm OK\n") ;
    }
   
}
/* ¼ì²é²Ù×÷×´Ì¬,Èç¹û´íÎóÔòÏÔÊ¾´íÎó´úÂë²¢Í£»ú */

/* ¼ì²é²Ù×÷×´Ì¬,Èç¹û´íÎóÔòÏÔÊ¾´íÎó´úÂë²¢Í£»ú */
void	mStopIfError( u8 iError )
{
	if ( iError == ERR_SUCCESS )return;                        /* ²Ù×÷³É¹¦ ·¢ËÍÐÅºÅÁ¿*/
	printf( "Error: %02X\n", (UINT16)iError );                  /* ÏÔÊ¾´íÎó */
}




void TaskUsbControl(void* pvdata)
 {
	 
	 
   
	 
	 pvdata = pvdata;
   uint8_t i =0;
    
	 while(1){
		 
     OSTimeDly(40);
		 
		 printf( "------------------Wait Udisk------------------------------\r\n" );
		 while ( CH374DiskStatus < DISK_CONNECT ) {            /* ²éÑ¯CH375ÖÐ¶Ï²¢¸üÐÂÖÐ¶Ï×´Ì¬,µÈ´ýUÅÌ²åÈë */
			   OSTimeDly(10);
			   // TaskDogStrutVar.UdiskIn = 0;
  	     if ( CH374DiskConnect( ) == ERR_SUCCESS )    /* ÓÐÉè±¸Á¬½ÓÔò·µ»Ø³É¹¦,CH375DiskConnectÍ¬Ê±»á¸üÐÂÈ«¾Ö±äÁ¿CH375DiskStatus */
           {
		           SYS_ON;
						   WDC_INIT();
						   break;
					 }	
		  }
		 
		 printf("-----------------------Disk Init---------------------------\r\n");
	  for ( i = 0; i < 5; i++ ) {                          /* ÓÐµÄUÅÌ×ÜÊÇ·µ»ØÎ´×¼±¸ºÃ,²»¹ý¿ÉÒÔ±»ºöÂÔ */
		
		  printf( "----------------------------Ready ---------------------------\r\n" );
			if ( CH374DiskReady( ) == ERR_SUCCESS ) break;    /* ²éÑ¯´ÅÅÌÊÇ·ñ×¼±¸ºÃ */
		}	
			
			
			
		printf( "-------------DiskSize---------------------------\r\n" );
		i = CH374DiskSize( );  
		mStopIfError( i );
		printf( "TotalSize = %u MB \r\n", (unsigned int)( mCmdParam.DiskSize.mDiskSizeSec * (CH374vSectorSize/512) / 2048 ) );  // ÏÔÊ¾ÎªÒÔMBÎªµ¥Î   	

    printf( "-------------------CreateFILeName-----------------\r\n" );                                 //´®¿Ú´´½¨Ê±¼ä»á³¬³¤ /1.c

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
		
	  i = CH374FileCreate( );                               /* ÐÂ½¨ÎÄ¼þ²¢´ò¿ª,Èç¹ûÎÄ¼þÒÑ¾­´æÔÚÔòÏÈÉ¾³ýºóÔÙÐÂ½¨ */
    mStopIfError( i );	
	  printf("Write some data to file %s\r\n",mCmdParam.Create.mPathName);


//        memcpy(&mCmdParam.ByteWrite.mByteBuffer[0],(const char*)"hello",5);
//				printf("mCmdParam.ByteWrite.mByteBuffer=%s\r\n",mCmdParam.ByteWrite.mByteBuffer);
//        mCmdParam.ByteWrite.mByteCount = 5; 
//        i = CH374ByteWrite( );                                /* ÒÔ×Ö½ÚÎªµ¥Î»ÏòÎÄ¼þÐ´ÈëÊý¾Ý,µ¥´Î¶ÁÐ´µÄ³¤¶È²»ÄÜ³¬¹ýMAX_BYTE_IO */
//	      mStopIfError( i );




     TaskDogStrutVar.MemoryStart = 1;
     WriteFile();
		 TaskDogStrutVar.MemoryStart = 0;
			 
		    SYS_OFF;
		printf("----------------CloseFile--------------\r\n");

	   mCmdParam.Close.mUpdateLen = 1;                       /* ²»Òª×Ô¶¯¼ÆËãÎÄ¼þ³¤¶È,Èç¹û×Ô¶¯¼ÆËã,ÄÇÃ´¸Ã³¤¶È×ÜÊÇCH374vSectorSizeµÄ±¶Êý */
	   i = CH374FileClose( );
		 mStopIfError( i );
 
		 
	 printf( "---------------------Take out\r\n----------------------------" );
		while ( 1 ) { 
          OSTimeDly(15);  
			     IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);//Ê¹ÄÜ¿´ÃÅ¹·
			  // TaskDogStrutVar.UdiskOut = 0;                        /* Ã»±ØÒªÆµ·±²éÑ¯ */
		if ( CH374DiskConnect( ) != ERR_SUCCESS )   /* ²éÑ¯·½Ê½: ¼ì²é´ÅÅÌÊÇ·ñÁ¬½Ó²¢¸üÐÂ´ÅÅÌ×´Ì¬,·µ»Ø³É¹¦ËµÃ÷Á¬½Ó */
	    {
			   SYS_OFF;
				  break;
			}

		} 
		 
  }
  
 }
	


































/****************************************************************************
º¯Êý¹¦ÄÜ£ºÔÚ¾É×Ö·û´®ÖÐ²åÈë¶ººÅÐÎ³ÉÐÂ×Ö·û´®
º¯Êý²ÎÊý£ºuint8_t*pDest£º´øÓÐ¶ººÅµÄÐÂ×Ö·û´®
          uint8_t*pSrc£ºÃ»ÓÐ¶ººÅµÄ¾É×Ö·û´®
          uint8_t arrLen[]£ºÔÚ¾É×Ö·û´®ÖÐ²åÈëµÄ¶ººÅµÄÎ»ÖÃ
	        uint8_t count£ºÎ»ÖÃÊý×éµÄ¸öÊý
	
º¯Êý·µ»ØÖµ£ºÎÞ
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

º¯Êý¹¦ÄÜ£ºÏòUÅÌÎÄ¼þÐ´Èë×Ö·û´®
º¯Êý²ÎÊý£ºuint8_t* pSrc£º´ýÐ´ÈëµÄ×Ö·û´®
          uint8_t size£º Ã¿´ÎÐ´ÈëUÅÌ×Ö½ÚµÄ³¤¶È
          uint8_t len£º´ýÐ´Èë×Ö·û´®µÄ³¤¶È
º¯Êý·µ»ØÖµ£ºÎÞ

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
        i = CH374ByteWrite( );                                /* ÒÔ×Ö½ÚÎªµ¥Î»ÏòÎÄ¼þÐ´ÈëÊý¾Ý,µ¥´Î¶ÁÐ´µÄ³¤¶È²»ÄÜ³¬¹ýMAX_BYTE_IO */
	      mStopIfError( i );
		    count += size;	 
		 
		 }
		memcpy(mCmdParam.ByteWrite.mByteBuffer,(const char*)&pSrc[count],len%16);
    mCmdParam.ByteWrite.mByteCount =len%16; 
     i = CH374ByteWrite( );                                /* ÒÔ×Ö½ÚÎªµ¥Î»ÏòÎÄ¼þÐ´ÈëÊý¾Ý,µ¥´Î¶ÁÐ´µÄ³¤¶È²»ÄÜ³¬¹ýMAX_BYTE_IO */
	   mStopIfError( i );
	
	   memcpy(mCmdParam.ByteWrite.mByteBuffer,(const char*)"\r\n",2);
     mCmdParam.ByteWrite.mByteCount = 2; 
     i = CH374ByteWrite( );                                /* ÒÔ×Ö½ÚÎªµ¥Î»ÏòÎÄ¼þÐ´ÈëÊý¾Ý,µ¥´Î¶ÁÐ´µÄ³¤¶È²»ÄÜ³¬¹ýMAX_BYTE_IO */
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
			     
      MX25L6406_Read((u8*)&Data,addr,sizeof(SysMemoryPara));  //¶ÁÈ¡
			    
			Data.ordinal = i;          //ÐòºÅ
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
	  sprintf(str,"%d",SysMemoryParaVar.ordinal);              //ÐòºÅ
		
		len = strlen(str);
	  for(i=0;i<len;i++)
		 {
			 
			 buf[count++] = str[i];
		 }
		 buf[count] = ',';
		 count = count +1;
		
		 
		 
		 len = strlen((char*)SysMemoryParaVar.ProductType);                   //²úÆ·ÐÍºÅ
		 if(len>10)
		 {
			 len = 10;
		 }
		// printf("SysMemoryParaVar.ProductType=%s\r\n",SysMemoryParaVar.ProductType);
		 strncpy(&buf[count],(char*)SysMemoryParaVar.ProductType,len);
		
		 buf[count+len] = ',';
		 count = count+len+1;
		 
	
		 
		 
		// printf("SysMemoryParaVar.TolFacNum=%s\r\n",SysMemoryParaVar.TolFacNum);
		 len = strlen((char*)SysMemoryParaVar.TolFacNum);              //³ö³§±àºÅ     
		 strncpy(&buf[count],(char*)SysMemoryParaVar.TolFacNum,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;
		 
		// printf("SysMemoryParaVar.year=%d\r\n",SysMemoryParaVar.year);
		 memset(str,0,sizeof(str));                             //Äê
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
		 memset(str,0,sizeof(str));                             //ÔÂ
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
		 memset(str,0,sizeof(str));                             //ÈÕ
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
		 memset(str,0,sizeof(str));                             //Ê±
		 sprintf(str,"%d",SysMemoryParaVar.hour);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
				
			  buf[count++] = str[i];
		  }
		  buf[count] = ':';
		  count = count+1;
			
			
	//	 printf("SysMemoryParaVar.min=%d\r\n",SysMemoryParaVar.min);	
		 memset(str,0,sizeof(str));                              //·Ö
		 sprintf(str,"%d",SysMemoryParaVar.min);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
			
			  buf[count++] = str[i];
		  }
		  buf[count] = ':';
		  count = count+1;
			
	//	printf("SysMemoryParaVar.sec=%d\r\n",SysMemoryParaVar.sec);	
		 memset(str,0,sizeof(str));                             //Ãë
		 sprintf(str,"%d",SysMemoryParaVar.sec);
		 len = strlen(str);
	   for(i=0;i<len;i++)
		  {
			  buf[count++] = str[i];
		  }
		  buf[count] = ',';
		  count = count+1;
			
	//	printf("SysMemoryParaVar.devname=%s\r\n",SysMemoryParaVar.devname);	
		 len = strlen((char*)SysMemoryParaVar.devname);              //Éè±¸Ãû³Æ   
		 strncpy(&buf[count],(char*)SysMemoryParaVar.devname,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;
			
			
	//	printf("SysMemoryParaVar.devnum=%s\r\n",SysMemoryParaVar.devnum);
		 len = strlen((char*)SysMemoryParaVar.devnum);              //Éè±¸±àºÅ  
		 strncpy(&buf[count],(char*)SysMemoryParaVar.devnum,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;
			
	//	 printf("SysMemoryParaVar.operate=%s\r\n",SysMemoryParaVar.operate);
		 len = strlen((char*)SysMemoryParaVar.operate);              //²Ù×÷ÈËÔ±
		 strncpy(&buf[count],(char*)SysMemoryParaVar.operate,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;	
		 
		// printf("SysMemoryParaVar.PressUint=%d\r\n",SysMemoryParaVar.PressUint);
		 ;
		 switch(SysMemoryParaVar.PressUint)           //flahs´æÑ¹Á¦µÄÊ±ºò¶ÔÓ¦Ñ¹Á¦¶¼chneg100
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
		 
			case 0 : memset(str,0,sizeof(str));                             //Ä¿±êÅ¤¾Ø
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
		
		case 1 :   memset(str,0,sizeof(str));                             //Ä¿±êÅ¤¾Ø
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
		 
			case 0 : memset(str,0,sizeof(str));                             //Êµ¼ÊÅ¤¾Ø
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
		 len = strlen((char*)SysMemoryParaVar.BoltDia);              //ÂÝË¨Ö±¾¶
		 strncpy(&buf[count],(char*)SysMemoryParaVar.BoltDia,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;	
			
		 
		 printf("SysMemoryParaVar.BoltGarde=%s\r\n",SysMemoryParaVar.BoltGarde);
		 len = strlen((char*)SysMemoryParaVar.BoltGarde);              //ÂÝË¨µÈ¼¶
		 strncpy(&buf[count],(char*)SysMemoryParaVar.BoltGarde,len) ;
		 buf[count+len] = ',';
		 count = count+len+1;	

      printf("SysMemoryParaVar.tarangle=%d\r\n",SysMemoryParaVar.tarangle);
     memset(str,0,sizeof(str));                             //Ä¿±ê½Ç¶È
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
		 memset(str,0,sizeof(str));                             //Êµ¼Ê½Ç¶È
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
     memset(str,0,sizeof(str));                             //µ²Î»
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
		switch(SysMemoryParaVar.mode)                              //Ñ¡¶¨Ä£Ê½
	  	{
			
			case 1:   	 len = strlen((char*)nijumode);              //ÂÝË¨Ä£Ê½
		               strncpy(&buf[count],(char*)nijumode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
		  case 2:   	 len = strlen((char*)luosmode);              //ÂÝË¨µÈ¼¶
		               strncpy(&buf[count],(char*)luosmode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
				
					
			case 3:   	 len = strlen((char*)gearmode);              //ÂÝË¨µÈ¼¶
		               strncpy(&buf[count],(char*)gearmode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
		 case 4:   	  len = strlen((char*)anglemode);              //ÂÝË¨µÈ¼¶
		               strncpy(&buf[count],(char*)anglemode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;
     case 5:   	   len = strlen((char*)sensormode);              //ÂÝË¨µÈ¼¶
		               strncpy(&buf[count],(char*)sensormode,len) ;
		               buf[count+len] = ',';
		               count = count+len+1;	 
			             break;									 
				

			}			
			                                                     
	printf("SysMemoryParaVar.workpattern=%d\r\n",SysMemoryParaVar.workpattern);
			switch(SysMemoryParaVar.workpattern)                    //¹¤×÷·½Ê½
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
			 
			 
			 
			 switch(SysMemoryParaVar.tigresult)                        //Å¡½ô½á¹û
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	





























             
	
	







