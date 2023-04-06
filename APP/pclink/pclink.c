
#include "pclink.h"
#include  "MX25L.h"
#include "screendriver.h"

TorquePattern  TorquePatternVar[50] = {0};
//MemoryFlag     MemoryFlagVar = {0};



/****************************************************************
�������ܣ�����λ�����յ������޸�ʱ��
����������uint16_t year,
          uint8_t month,
					uint8_t day,
					uint8_t hour,
					uint8_t minute,
					uint8_t sec
��������ֵ����
****************************************************************/

void setTime(uint16_t year,uint8_t month,uint8_t day,uint8_t hour,uint8_t minute,uint8_t sec)
 {
  
   calendar.w_year = year;
   calendar.w_month = month;
   calendar.w_date = day;
	 calendar.hour = hour;
	 calendar.min = minute;
	 calendar.sec = sec;
	 SetTextInt32(0,3,calendar.w_year,0,0);
   SetTextInt32(0,4,calendar.w_month,0,0);
	 SetTextInt32(0,5,calendar.w_date,0,0);
	 SetTextInt32(0,6,calendar.hour,0,0);
	 SetTextInt32(0,7,calendar.min,0,0);
	 SetTextInt32(0,8,calendar.sec,0,0);
 RTC_Set(calendar.w_year ,calendar.w_month,calendar.w_date , calendar.hour,calendar.min,calendar.sec);  //����ʱ��	
 }





/*******************************************************************

�������ܣ�����λ���õ���Ʒ�����ƺ�ϵ�����ṹ�����鸳ֵ
����������TorquePattern Product[]��ָ��ṹ������ı���
          uint8_t kind �ṹ������Ĵ�С
          uint8_t* pBuffer����λ������������

********************************************************************/


void getProduct(TorquePattern Product[],uint16_t kind,uint8_t* pBuffer)
{

    uint16_t i = 0;
    

	 for(i = 0;i<kind;i++)
	 {
		 
		  memset(&Product[i],0,sizeof(TorquePattern));        //��ջ�����    
	    strncpy((char*)Product[i].ProductType,(const char*)&pBuffer[9+i*15],10);
      Product[i].Factor = (PTR2U32(&pBuffer[19+i*15])/10000 ); 
	
		 	printf(" Product[%d].Factor=%d\r\n", i,Product[i].Factor);
			printf("Product[%d].ProductType=%s\r\n",i,Product[i].ProductType);
		 	printf("Product[%d].diameter_Imp=%d\r\n",i,Product[i].diameter_Imp);
		  printf("Product[%d].diameter_Metric=%d\r\n",i,Product[i].diameter_Metric);
		  printf("Product[%d].garde_Imp=%d\r\n",i,Product[i].garde_Imp);
		  printf("Product[%d].garde_Metric=%d\r\n",i,Product[i].garde_Metric);
			printf("Product[%d].SensorTor=%d\r\n",i,Product[i].SensorTor);
		  
	 }
	    //�Ӹ�����������һ�δ浽���������µĲ�Ʒ����
	     MX25L6406_Erase_Sector(2003);                    //����������һ�δ���ֵ�����
	     MX25L6406_Erase_Sector(2002);                    //����������һ�δ���ֵ����� 
	 
	     MX25L6406_WriteU16(secop(2002),0);               //��¼��Ʒ������������0
	 
	     for(i=2004;i<=2018;i++){
				  MX25L6406_Erase_Sector(i); 
			 }
			 
	    
	
}




 
/*******************************************************************
 �������ܣ���ѯ��λ����������˨֡�İ���������û�д���flash��
 ����������pDest������flash����İ�������
           pSrc����λ�������İ�������
 ��������ֵ��1���������ƴ���
             0���������Ʋ�����
*******************************************************************/

 void FlashWriteTorquePattern(TorquePattern* wdata,uint32_t addr,uint8_t kind)
  {
	
	  uint8_t i = 0;
//	  uint8_t temp = 0;
		
		for(i=0;i<kind;i++)
		 {
			 
		   u8*pbuffer = (u8*)(&wdata[i]);
	     MX25L6406_Write(pbuffer,addr,sizeof(TorquePattern));
		   printf(" wdata[%d].Factor=%d\r\n", i,wdata[i].Factor);
			 printf("wdata[%d].ProductType=%s\r\n",i,wdata[i].ProductType);
			 addr+=sizeof(TorquePattern);
		
		 }
	}
 
/***************************************************************
 �������ܣ���flash�ж�������ϵ�������Ƹ��ṹ�帳ֵ
 ����������TorquePattern* rdata���ṹ��ĵ�ַ
           uint32_t addr������������ƺ�ϵ���ĵ�ַ
           uint8_t kind������flash������ֵĸ���   
 
 ��������ֵ��flash�Ѿ�����İ������ƺ�ϵ��
****************************************************************/

void FlashGetTorquePattern(TorquePattern* rdata,uint32_t addr,uint16_t kind)
 {
     

			 int i = 0;


    for(i=0;i<kind;i++)
			{
			  MX25L6406_Read((u8*)&rdata[i],addr+secop(1),sizeof(TorquePattern));
	      printf("rdata[%d].ProductType=%s\r\n",i,rdata[i].ProductType);
		    printf("rdata[%d].Factor=%d\r\n",i,rdata[i].Factor);
				printf("rdata[%d].diameter_Imp=%d\r\n",i,rdata[i].diameter_Imp);
		    printf("rdata[%d].diameter_Metric=%d\r\n",i,rdata[i].diameter_Metric);
				printf("rdata[%d].garde_Imp=%d\r\n",i,rdata[i].garde_Imp);
		    printf("rdata[%d].garde_Metric=%d\r\n",i,rdata[i].garde_Metric);
				printf("rdata[%d].SensorTor=%d\r\n",i,rdata[i].SensorTor);   
				addr +=sizeof(TorquePattern);
			
		 }
 
}
	

/*************************************************************************
�������ܣ��Ա�flash����ĵİ��֣���������ھʹ���
����������TorquePattern* Src����λ�������İ������ƺ�����
          uint32_t addr�����µ��׵�ַ
          uint8_t kind�������İ��ָ��� 
         
��������ֵ����

************************************************************************/

void CompareSaveTorquePattern(TorquePattern* Src,uint32_t addr,uint16_t kind)
 {
	      uint16_t count = 0;
	      uint32_t newCount = 0;
	     
	      uint32_t i = 0;
//	      uint32_t j = 0;
	   
	   
//				TorquePattern rdata[40] = {0};  //����λ�������İ��ֲ������ȽϵĻ���������
				 newCount = addr;
      //  count =  MX25L6406_ReadU16(addr);    //      ���������Ʒ����
				printf("Last product kind=%d\r\n",count);
	     if(count==0){                                          //   ��û�б��������ȫ�����浽flsh��                                      				
         	for(i=0;i<kind;i++)
		         {
		           u8*pbuffer = (u8*)(&Src[i]);
			         printf("wdata[%d].ProductType=%s\r\n",i,Src[i].ProductType);
		           printf("wdata[%d].Factor=%d\r\n",i,Src[i].Factor);
							 printf("wdata[%d].diameter_Imp=%d\r\n",i,Src[i].diameter_Imp);
		           printf("wdata[%d].diameter_Metric=%d\r\n",i,Src[i].diameter_Metric);
							 printf("wdata[%d].garde_Imp=%d\r\n",i,Src[i].garde_Imp);
		           printf("wdata[%d].garde_Metric=%d\r\n",i,Src[i].garde_Metric);
							 printf("wdata[%d].SensorTor=%d\r\n",i,Src[i].SensorTor);
				       MX25L6406_Write(pbuffer,addr+secop(1),sizeof(TorquePattern));
	             addr+=sizeof(TorquePattern);
		         }  
         	for(i=2004;i<=2016;i++) 	
						 {
						   MX25L6406_Erase_Sector(i);//����������˨������
						 }
       		MX25L6406_WriteU16(newCount,kind);				 //�����Ʒ�ĸ���	 
			 }
			 else{                                           
				 
  	      for(i=0;i<kind;i++)
		         {
		           u8*pbuffer = (u8*)(&Src[i]);
			         printf("wdata[%d].ProductType=%s\r\n",i,Src[i].ProductType);
		           printf("wdata[%d].Factor=%d\r\n",i,Src[i].Factor);
							 printf("wdata[%d].diameter_Imp=%d\r\n",i,Src[i].diameter_Imp);
		           printf("wdata[%d].diameter_Metric=%d\r\n",i,Src[i].diameter_Metric);
							 printf("wdata[%d].garde_Imp=%d\r\n",i,Src[i].garde_Imp);
		           printf("wdata[%d].garde_Metric=%d\r\n",i,Src[i].garde_Metric);
							 printf("wdata[%d].SensorTor=%d\r\n",i,Src[i].SensorTor);
				       MX25L6406_Write(pbuffer,addr+secop(1),sizeof(TorquePattern));
	             addr+=sizeof(TorquePattern);
		         } 
					 
			  }
			 	 			  
 }
 
/***********************************************************************
 �������ܣ�������λ�������İ�������,�Ա�flash����
           ���ڵİ�������
 ��������  record[i+1] = i+1; //i=proname;
           record[1] = 1;record[2] = 2;
           ��ʾ��˨��Ʒ�����ƶ�Ӧ��λ��
           uint8_t record[]:��¼��˨��Ʒ���Ƴ��ֵ�λ��
           uint32_t addr:��¼����ڵ���ʼ��ַ
           ��������?SAVEBOLTPOS��
 ��������ֵ����˨��Ʒ���Ƴ��ֵ�λ��
             ��������ڸò�Ʒ�ͷ���0;
 
************************************************************************/

 
uint8_t  CompareBoltName(TorquePattern* rdata,uint8_t* pBuff,uint16_t count)
 {
   
	 uint8_t i = 0;
   uint8_t j = 0;     
       
     
				for(i=0;i<count;i++)
		        {
			     	 printf("rdata[%d].ProductType=%s\r\n",i,rdata[i].ProductType);
							for(j=0;j<10;j++)
							{
								 printf("pBuff[%d]=%c\r\n",j,pBuff[j]);
								printf("rdata[1].ProductType[%d]=%c\r\n",j,rdata[1].ProductType[j]);
							}
							
		         printf("rdata[%d].Factor=%d\r\n",i,rdata[i].Factor);
						 if(strncmp(pBuff,rdata[i].ProductType,10) ==0 )   //������ڷ��ض�Ӧ������
						  {
               printf("i=%d\r\n",i);
								return (i+1);
							}
		        }
		  return 0 ;
 }
 
/****************************************************************
 
�������ܣ�������˨�Ľṹ�����Թ�Ӣ���µ�ֱ���͵ȼ�
          
����������uint8_t* pBuff : ��λ��������ָ��      
          BoltPattern*Src��������������׵�ַ
                           ������˨��ֱ���ȼ�����
          BoltGardeDiaArr*Data��������˨��ֱ���͵ȼ�����    
          uint8_t Pos����˨��Ʒ���� ��Ӧ��λ��
          uint32_t addr��������˨�ṹ�����Ե��׵�ַ
 
��������ֵ����
******************************************************************/
uint8_t RecordBoltPos[40]  = {0};                 //��¼��Ʒ��λ��

BoltGardeDiaArr BoltGardeDiaArrVar = {0};         //������˨ֱ���ȼ����ƵĽṹ��
//TorqueValStruct TorqueValStructVar = {0};         //������˨ֱ���ȼ���Ӧ��Ť����


void  GetBoltStruct(uint8_t* pBuff,TorquePattern Product[],BoltGardeDiaArr*Data,uint8_t Pos)
 {
	            
              uint8_t i = 0;
	            uint8_t j = 0;
	            uint16_t len = 0;
	            const int column = sizeof(Data->BoltDiaArr_I[i]);   //����
	            printf("column=%d\r\n",column);
	            uint32_t Arr32[10] = {0};
							
							uint16_t   PosMeticDia   =   pBuff[18];                     //����ֱ������
				      printf("PosMeticDia=%d\r\n",PosMeticDia);
							uint16_t   PosMeticGar   =   pBuff[19+pBuff[18]*10];        //���Ƶȼ�����
							printf("PosMeticGar=%d\r\n",PosMeticGar);
							uint16_t   PosMericData  =   20 + PosMeticDia*10 + PosMeticGar*10+(PosMeticDia*PosMeticGar)*4;  //��������ʼλ��
						  printf(" PosMericData=%d\r\n",PosMericData);
							uint16_t   PosImpDia   =  pBuff[PosMericData+1];          //Ӣ��ֱ������
							printf("PosImpDia=%d\r\n",PosImpDia);
							uint16_t   PosImpGar   =  pBuff[PosMericData+2+pBuff[PosMericData+1]*10];  //Ӣ�Ƶȼ�����
							printf("PosImpGar=%d\r\n",PosImpGar);
							memset(Data,0,sizeof(BoltGardeDiaArr));                      //��ջ�����
							if(pBuff[PosMericData]==1){
	
	            Product[Pos-1].diameter_Imp = PosImpDia ;                      
              Product[Pos-1].garde_Imp = PosImpGar;
								
							}
							
							if(pBuff[17] == 0){
							
							 Product[Pos-1].diameter_Metric =    PosMeticDia;
	             Product[Pos-1].garde_Metric    =    PosMeticGar ;
							}
							
							
						for(i=0;i< Product[Pos-1].diameter_Metric;i++)         //�õ����Ʋ�Ʒ��ֱ��
	            {		
								strncpy((char*)Data->BoltDiaArr_M[i],(char*)&pBuff[19+i*10],10);//i��ֵ��Ҫ����, ����  
                printf("getData->BoltDiaArr_M[%d]=%s\r\n",i,Data->BoltDiaArr_M[i]);							
				      }	
							
							
						for(i=0;i< Product[Pos-1].garde_Metric;i++)          //�õ����Ʋ�Ʒ�ĵȼ�
	            {		
								strncpy((char*)Data->BoltGardeArr_M[i],(char*)&pBuff[20+pBuff[18]*10+i*10],10);//i��ֵ��Ҫ����, ���� 
               	printf("getData->BoltGardeArr_M[%d]=%s\r\n",i,Data->BoltGardeArr_M[i]);							
				      }	
							
							
							   
            for(i=0;i<Product[Pos-1].garde_Metric;i++)            //�õ����Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
               {
								    memset(Arr32,0,sizeof(Arr32));
							    for(j=0;j<Product[Pos-1].diameter_Metric;j++) 
								   {
										  Arr32[j]  =  PTR2U32(&pBuff[20 + PosMeticDia*10 + PosMeticGar*10+len+(j*4)]);   
									 }
									  len += (j*4);
									  memcpy(Data->Val_M[i], Arr32,sizeof(Arr32));
							 }
							 
							
							for(i=0;i<Product[Pos-1].garde_Metric;i++)
							  {
								   for(j=0;j<Product[Pos-1].diameter_Metric;j++)
									  {
										   printf("Data->Val_M[%d][%d]=%d\r\n",i,j,Data->Val_M[i][j]);
										}

								}
							 
							 
							 
							
			
							
            for(i=0;i< Product[Pos-1].diameter_Imp;i++)         //�õ�Ӣ�Ʋ�Ʒ��ֱ��            
	            {		
								strncpy((char*)Data->BoltDiaArr_I[i],(char*)&pBuff[PosMericData+2+i*10],10);//i��ֵ��Ҫ����, ����  
                printf("getData->BoltDiaArr_I[%d]=%s\r\n",i,Data->BoltDiaArr_I[i]);								
				      }
							
							
						for(i=0;i< Product[Pos-1].garde_Imp;i++)         //�õ�Ӣ�Ʋ�Ʒ�ĵȼ�
	            {		
								strncpy((char*)Data->BoltGardeArr_I[i],(char*)&pBuff[PosMericData+3+pBuff[PosMericData+1]*10+i*10],10);//i��ֵ��Ҫ����, ����  
                 printf("getData->BoltGardeArr_I[%d]=%s\r\n",i,Data->BoltGardeArr_I[i]);								
				      }	
							
							
							
					
						 len = 0;
            for(i=0;i<Product[Pos-1].garde_Imp;i++)              //�õ�Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
               {
								   memset(Arr32,0,sizeof(Arr32));
							    for(j=0;j<Product[Pos-1].diameter_Imp;j++)         
								   {
										
										   Arr32[j]  =  PTR2U32(&pBuff[PosMericData+3 + PosImpDia*10 + PosImpGar*10+len+(j*4)]);
										
										  
									 }
									 
									  len += (j*4);
									  memcpy(Data->Val_I[i], Arr32,sizeof(Arr32));
									
							 }
							 
							 
          
							 
							 for(i=0;i<Product[Pos-1].garde_Imp;i++)
							  {
								   for(j=0;j<Product[Pos-1].diameter_Imp;j++)
									  {
										   printf("getData->Val_I[%d][%d]=%d\r\n",i,j,Data->Val_I[i][j]);
										}
								
								}

					
								
 }
 
 
 /**********************************************************************
 �������ܣ�������˨��ֱ���͵ȼ�����
 ����������BoltGardeDiaArr*Data����˨�Ľṹ��ָ��
           uint32_t addr����Ʒ�ĵ�ַ
           uint8_t Pos����Ʒ��λ��
 
 ��������ֵ����
*********************************************************************/
 void SaveBoltGardeMeterArr(TorquePattern Product[],BoltGardeDiaArr*Data,uint32_t addr,uint8_t Pos)
  {
	
	   int i = 0;
	   int j = 0;
		
		
//		 uint16_t BoltDiaArr_I_Space = sizeof(Data->BoltDiaArr_I);
// 		 uint16_t  BoltGardeArr_I_Space = sizeof(Data->BoltGardeArr_I); 
//		 uint16_t BoltDiaArr_M_Space = sizeof(Data->BoltDiaArr_M);
//		 uint16_t BoltGardeArr_M_Space = sizeof(Data->BoltGardeArr_M);
//		 uint16_t Val_I_Space = sizeof(Data->Val_I);
//		 uint16_t Val_M_Space = sizeof(Data->Val_M);
		 printf("BoltDiaArr_I_Space=%d\r\n",sizeof(Data->BoltDiaArr_I));
		 printf("BoltGardeArr_I_Space=%d\r\n",sizeof(Data->BoltGardeArr_I));
		 printf("BoltDiaArr_M_Space=%d\r\n",sizeof(Data->BoltDiaArr_M));
		 printf("BoltGardeArr_M_Space=%d\r\n",sizeof(Data->BoltGardeArr_M));
		 printf("Val_I_Space=%d\r\n",sizeof(Data->Val_I));
		 printf("Val_M_Space=%d\r\n",sizeof(Data->Val_M));
		
		 int row = sizeof(Data->BoltDiaArr_I[i][j]) /sizeof(Data->BoltDiaArr_I[i]);  //����
		 printf("row=%d\r\n",row);
		 int column = sizeof(Data->BoltDiaArr_I[i]);                        //����
		 printf("column=%d\r\n",column);  
		 
		 uint32_t addr1 = addr;                 
		  printf("addr1=%d\r\n",addr1/4096);
     uint32_t addr2 = addr+secop(2);
		 printf("addr2=%d\r\n",addr2/4096);
     uint32_t addr3 = addr+secop(4);
		 printf("addr3=%d\r\n",addr3/4096);
		 uint32_t addr4 = addr+secop(6);
		 printf("addr4=%d\r\n",addr4/4096);
     uint32_t addr5 = addr+secop(8);
		 printf("addr5=%d\r\n",addr5/4096);
     uint32_t addr6 = addr+secop(10);
		 printf("addr6=%d\r\n",addr6/4096);
		 
		 uint32_t addr7 = 0;
		 u8*pbuffer = (u8*)(&Product[Pos-1]);
	   addr7 = addr-secop(1)+sizeof(TorquePattern)*(Pos-1);                  //�����Ʒ��Ӧ�Ĺ���Ӣ�Ƹ���
		 printf("addr7=%d\r\n",addr7/4096);
		 MX25L6406_Write(pbuffer,addr7,sizeof(TorquePattern ));                //���湫Ӣ�Ƶ���˨ֱ���͵ȼ�����  
		
		 for(i=0;i<20;i++)
		  {
			//	printf("");
			  MX25L6406_Write(Data->BoltDiaArr_I[i],addr1+(Pos-1)* 200,10);   //����Ӣ�Ʋ�Ʒ��ֱ��
			  addr1 +=10;	
			}
			
			
	    for(i=0;i<20;i++)
		  {
	       printf("2\r\n");
			 MX25L6406_Write(Data->BoltGardeArr_I[i],addr2+(Pos-1)* 240 ,12);//����Ӣ�Ʋ�Ʒ�ĵȼ�
				  addr2 += 12;	
			}
			
			for(i=0;i<20;i++)
		  {
				 printf("3\r\n");
			 MX25L6406_Write(Data->BoltDiaArr_M[i],addr3+(Pos-1)*200,10);//���湫�Ʋ�Ʒ��ֱ��
			  addr3 += 10;		
			}
			
			for(i=0;i<20;i++)
		  {
				  printf("4\r\n");
			 MX25L6406_Write(Data->BoltGardeArr_M[i],addr4+(Pos-1)*240,12);//���湫�Ʋ�Ʒ�ĵȼ�
			 addr4 += 12;	
			}
			
		  for(i=0;i<20;i++)                                                        //����Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
		  {
			   printf("5\r\n");
			   MX25L6406_WriteU32ARR(Data->Val_I[i],addr5+(Pos-1)*800,10);	
         				
         addr5 += 10*4;
			}
		  for(i=0;i<20;i++)                                                        //����Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
		  {
			  printf("6\r\n");
			   MX25L6406_WriteU32ARR(Data->Val_M[i],addr6+(Pos-1)*800,10);	
         				
         addr6 += 10*4;
			}
			
	}
 
 /***************************************************************************************
	�������ܣ���flash���������Ʒ��ֱ���͵ȼ����ṹ�帳ֵ
	����������BoltGardeDiaArr*Data���ṹ��ָ��
	          uint32_t addr���׵�ַ
	          uint8_t Pos����Ʒ��Ӧ��λ��
  ��������ֵ��BoltGardeDiaArr*Data��������˨ֱ���ȼ�������
 ****************************************************************************************/

 void ReadBoltGardeMeterArr(TorquePattern*rdata,BoltGardeDiaArr*Data,uint32_t addr,uint8_t Pos)
 {
 
 	   int i = 0;
	   int j = 0;
	  static uint16_t read = 0;

	   uint32_t addr1 = addr;
     uint32_t addr2 = addr+secop(2);
     uint32_t addr3 = addr+secop(4);
		 
		 uint32_t addr4 = addr+secop(6);
     uint32_t addr5 = addr+secop(8);
     uint32_t addr6 = addr+secop(10);
	     
		 memset(Data,0,sizeof(BoltGardeDiaArr));
 if(ModifyVarStructVar.ChartType == 0){
		if(rdata[Pos-1].diameter_Imp == 0 || rdata[Pos-1].garde_Imp == 0)
		  {
			
				memset(ModifyVarStructVar.BoltDiameterArr,0,sizeof(ModifyVarStructVar.BoltDiameterArr));
				memset(ModifyVarStructVar.BoltGardeArr,0,sizeof(ModifyVarStructVar.BoltGardeArr));
			  ModifyVarStructVar.TartorVal_BoltMode = 0;
			
				return;
		
			}
		}		
 
	 if(ModifyVarStructVar.ChartType == 1){	
			if(rdata[Pos-1].garde_Metric == 0 || rdata[Pos-1].diameter_Metric == 0)
		  {
		
				memset(ModifyVarStructVar.BoltDiameterArr_M,0,sizeof(ModifyVarStructVar.BoltDiameterArr_M));
				memset(ModifyVarStructVar.BoltGardeArr_M,0,sizeof(ModifyVarStructVar.BoltGardeArr_M));;
				ModifyVarStructVar.TartorVal_BoltMode = 0;
			
		     return;
			}
		}	
			
		 for(i=0;i<rdata[Pos-1].diameter_Imp;i++)
		  {
			
			  MX25L6406_Read(Data->BoltDiaArr_I[i],addr1+(Pos-1)*200,10);   //��������Ӣ�Ʋ�Ʒ��ֱ��
			  addr1+= 10;			
			}
			
	    for(i=0;i<rdata[Pos-1].garde_Imp;i++)
		  {
			 
			 MX25L6406_Read(Data->BoltGardeArr_I[i],addr2+(Pos-1)*240,12);//��������Ӣ�Ʋ�Ʒ�ĵȼ�
			 addr2+=12;			
			}
			
			for(i=0;i<rdata[Pos-1].diameter_Metric;i++)
		  {
			
			 MX25L6406_Read(Data->BoltDiaArr_M[i],addr3+(Pos-1)*200,10);//�������湫�Ʋ�Ʒ��ֱ��
			 addr3 += 10;	
			}
			
			for(i=0;i<rdata[Pos-1].garde_Metric;i++)
		  {
			
			 MX25L6406_Read(Data->BoltGardeArr_M[i],addr4+(Pos-1)*240,12);//�������湫�Ʋ�Ʒ�ĵȼ�	
			 addr4 += 12;	
			}
			
			
			for(i=0;i<rdata[Pos-1].garde_Imp;i++)                                                        //��������Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
		  {
			 
					 MX25L6406_ReadU32ARR(Data->Val_I[i],addr5+(Pos-1)*800,10);	
					 addr5 += 40;
			}
			
		  for(i=0;i<rdata[Pos-1].garde_Metric;i++)                                                        //��������Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
		  {
			 
					   MX25L6406_ReadU32ARR(Data->Val_M[i],addr6+(Pos-1)*800,10);	
					   addr6 += 40;
			
			}
			
		for(i=0;i<rdata[Pos-1].garde_Imp;i++)                                                        //��������Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
		  {
			 
				 for(j=0;j<rdata[Pos-1].diameter_Imp;j++){
				
				 }
			}
			
				
	for(i=0;i<rdata[Pos-1].garde_Metric;i++)                                                        //��������Ӣ�Ƶ���˨ֱ���ȼ���Ӧ��Ť��ֵ
		  {
			 
			   for(j=0;j<rdata[Pos-1].diameter_Metric;j++){
					 
				 } 
				 
			}
			 
			
		  if(ModifyVarStructVar.ChartType == 0){

        if(read !=0 ){
				strncpy((char*)ModifyVarStructVar.BoltDiameterArr,(char*)Data->BoltDiaArr_I[0],strlen((char*)Data->BoltDiaArr_I[0]));
				strncpy((char*)ModifyVarStructVar.BoltGardeArr,(char*)Data->BoltGardeArr_I[0],strlen((char*)Data->BoltGardeArr_I[0]));
	      ModifyVarStructVar.TartorVal_BoltMode = Data->Val_I[0][0];
				
				}
         read++;
			}			

    if(ModifyVarStructVar.ChartType == 1){ 
  
		   if(read!=0){
		   strncpy((char*)ModifyVarStructVar.BoltDiameterArr_M,(char*)Data->BoltDiaArr_M[0],strlen((char*)Data->BoltDiaArr_M[0]));
		   strncpy((char*)ModifyVarStructVar.BoltGardeArr_M,(char*)Data->BoltGardeArr_M[0],strlen((char*)Data->BoltGardeArr_M[0]));
	  	 ModifyVarStructVar.TartorVal_BoltMode = Data->Val_M[0][0];

			 }

			 read++;
			
			}			

	
			
 }
 

 

 

 

/*************************************************
�������ܣ��������ֵ�λ�ñ�



***********************************************/
 
void FlashGetRecord(u8* record,uint32_t addr,uint8_t Pos)
{
              
	MX25L6406_Read((u8*)&record[Pos],addr+Pos*8,1); //��һ����Ʒ��Ӧ��λ��

}
 
/********************************************************
�������ܣ����ó������

*******************************************************/

void setAppearanceNumber(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len)
 {
	  uint16_t i = 0;
    memset(pDest,0,sizeof(pDest->appearanceNumberArr));
	  for(i=0;i<len;i++)
	  {
		    pDest->appearanceNumberArr[i] = pSrc[i];
		}
	  
   
	  printf("pDest->appearanceNumberArr=%s\r\n",pDest->appearanceNumberArr);
	  printf("sizeof(pDest->appearanceNumberArr)=%d\r\n",sizeof(pDest->appearanceNumberArr));

 }
 
/********************************************************
�������ܣ������豸����

*******************************************************/
 
 
 void setUserEquipName(uint8_t*pSrc, upComputerStruct*pDest,uint16_t len)
  {
		uint16_t i = 0;
	  memset(pDest->UserEquipNameArr,0,sizeof( pDest->UserEquipNameArr));
    for(i=0;i<len;i++)
	  {
		    pDest->UserEquipNameArr[i] = pSrc[i];
		}
	  
   
	  printf(" pDest->UserEquipNameArr=%s\r\n", pDest->UserEquipNameArr);
	  printf("sizeof( pDest->UserEquipNameArr)=%d\r\n",sizeof( pDest->UserEquipNameArr));
		
		
	}
 
 
 
  
/********************************************************
�������ܣ������豸���

*******************************************************/
 void setUserEquipNumber(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len)
  {
		uint16_t i = 0;
	  memset(pDest->UserEquipNumberArr,0,sizeof(pDest->UserEquipNumberArr));
    for(i=0;i<len;i++)
	  {
		    pDest->UserEquipNumberArr[i] = pSrc[i];
		}
	  
   
	  printf(" pDest->UserEquipNumberArr=%s\r\n", pDest->UserEquipNumberArr);
	  printf("sizeof(pDest->UserEquipNumberArr)=%d\r\n",sizeof(pDest->UserEquipNumberArr));
		
	}
 
 
/********************************************************
�������ܣ����ò�����Ա����

*******************************************************/
 void setUserName(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len)
  {
		uint16_t i = 0;
	  memset(pDest->UserNameArr,0,sizeof(pDest->UserNameArr));
    for(i=0;i<len;i++)
	  {
		   pDest->UserNameArr[i] = pSrc[i];
			 printf("pDest->UserNameArr[%d]=%d\r\n",i, pDest->UserNameArr[i]);
		}
	  
   
	  printf("pDest->UserNameArr=%s\r\n", pDest->UserNameArr);
	  printf("sizeof(pDest->UserNameArr)=%d\r\n",sizeof(pDest->UserNameArr));
	}
	
 /*****************************************************	
	
	
	
	
	
	
	******************************************/
 
void ToolsUnlock(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len)
 {
	 
   if(strncmp((char*)pSrc,(char*)pDest->passWordArr,len) == 0)
	  {
		   SetBuzzer(10);
			 printf("OK\r\n");
		}
  

 }

 
 
 
 
 
/********************************************************
�������ܣ����ò�������

*******************************************************/
 
 void setPassWord(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len)
  {
		uint16_t i = 0;
	 	memset(pDest->passWordArr,0,sizeof(pDest->passWordArr));
    for(i=0;i<len;i++)
	  {
		  pDest->passWordArr[i] = pSrc[i];
		}
	  
   
	  printf("pDest->passWordArr=%s\r\n", pDest->passWordArr);
	  printf("sizeof(pDest->passWordArr)=%d\r\n",sizeof(pDest->passWordArr));
	}
/******************************************************
	�������ܣ�����ʹ�ô���
	
******************************************************/
 
	
 void setUsingTimes(uint8_t*pSrc,upComputerStruct*pDest)
  {
		
	  memset(&pDest->UsingTime,0,sizeof(pDest->UsingTime));

		pDest->UsingTime = PTR2U32(pSrc);
		printf("pDest->UsingTime=%d\r\n",pDest->UsingTime);
	  printf("sizeof(pDest->UsingTime)=%d\r\n",sizeof(pDest->UsingTime));
	}
 
/*****************************************************
	�������ܣ�������λ��������������
	����������
	
*******************************************************/
 
  
 void FlashWriteupComputerStruct(upComputerStruct* wdata,uint32_t addr)
  {
	
	  
	 
	
		   u8*pbuffer = (u8*)(wdata);
	     MX25L6406_Write(pbuffer,addr,sizeof(upComputerStruct));
			  printf("wdata->appearanceNumberArr=%s\r\n",wdata->appearanceNumberArr);
			  printf("wdata->passWordArr=%s\r\n", wdata->passWordArr);
			  printf("wdata->UserEquipNameArr=%s\r\n", wdata->UserEquipNameArr);
			  printf("wdata->UserEquipNumberArr=%s\r\n",  wdata->UserEquipNumberArr);
		    printf("wdata->UserNameArr=%s\r\n", wdata->UserNameArr);
			  printf("wdata->UsingTime=%d\r\n",  wdata->UsingTime);
	
	}



	  
 void FlashReadupComputerStruct(upComputerStruct* rdata,uint32_t addr)
  {
	
	 
			  MX25L6406_Read((u8*)rdata,addr,sizeof(upComputerStruct));
			  printf("rdata->appearanceNumberArr=%s\r\n",rdata->appearanceNumberArr);
			  printf("rdata->passWordArr=%s\r\n", rdata->passWordArr);
			  printf("rdata->UserEquipNameArr=%s\r\n", rdata->UserEquipNameArr);
			  printf("rdata->UserEquipNumberArr=%s\r\n",  rdata->UserEquipNumberArr);
		     printf(" rdata->UserNameArr=%s\r\n", rdata->UserNameArr);
			  printf("  rdata->UsingTime=%d\r\n",  rdata->UsingTime);
			
	}
	
	
	
	//SensorStruct SensorStructVar[40] = {0};
/*******************************************************************************
	
	
	
 *********************************************************************************/
void FlashWriteSensorStruct()
 {
 
 
 
 
 
 
 }
	
	
	
	
	void getSensorStructBuf(uint8_t* pBuffer,SensorStruct* rbuff,uint8_t kind)
	 {
	 
	       int i = 0;
		     int j = 0;
		     int count = 0;

		    TorquePattern rdata[40] = {0};  //����λ�������İ��ֲ������ȽϵĻ���������
        count =  WreadNumFormFlash(secop(2) ,0,10);    //      ���������Ʒ����
        FlashGetTorquePattern(rdata,secop(1),count);        //��������flash����İ������ƺ�ϵ��
			  printf("Last product kind=%d\r\n",count);
				for(i=0;i<count;i++)
		        {
			     	 printf("flashdata[%d].ProductType=%s\r\n",i,rdata[i].ProductType);
		         printf("flashdata[%d].Factor=%d\r\n",i,rdata[i].Factor);
							for(j=0;j<kind;j++)
							 {
							     if(strncmp((char*)&pBuffer[j],(char*)rdata[i].ProductType,10)==0)
									  {
										
										
										}
							 
							 }

		        }
	 }
		 
		 
		 
		 

//    uint8_t i = 0;


//	 for(i = 0;i<kind;i++)
//	 {
//		 
//	    strncpy((char*)Product[i].ProductType,(const char*)&pBuffer[12+i*14],10);
//      Product[i].Factor = (PTR2U32(&pBuffer[22+i*14])/10000 ); 
//	
//		 	printf(" Product[%d].Factor=%d\r\n", i,Product[i].Factor);
//			printf("Product[%d].ProductType=%s\r\n",i,Product[i].ProductType);
//		  
//	 }
	     
/***********************************************************
����λ���õ������Ƕ�ֵ���浽flash��
��������?uuint16_t angle�����Ƕ�ֵ
          uint8_t* buf����λ���õ����ַ���
��������ֵ��


************************************************************/

uint16_t MaxAngle = 0;


void getAngle(uint16_t* angle,uint8_t buf[])
{
*angle = PTR2U16(buf+7);
printf("angle=%d\r\n",*angle);
}
	 
	 
/*************************************************************************
��������:��λ���·���λָ��

************************************************************************/

uint8_t GearKind = 0;






GearPattern GearPatternVar[70] = {0};

void getGear(GearPattern gear[],uint8_t gearkind,uint8_t buf[])
{
   uint8_t i = 0;
	 for(i = 0;i<gearkind;i++)
	 {
		 
		     memset(&gear[i],0,sizeof(GearPattern ));        //��ջ�����  
		     gear[i].gear = buf[i*5+8];   
		     printf(" gear[%d].gear=%d\r\n ",i, gear[i].gear);		 
         gear[i].gearPress = PTR2U32(&buf[i*5+9]);
		     printf(" gear[%d].gearPress=%d\r\n ",i, gear[i].gearPress);	
	 }
	 

}	

/********************************************************************************


********************************************************************************/
	

void FlashWriteGear(GearPattern wdata[],uint8_t gearkind,uint32_t addr)
 {
 
	 
	   uint8_t i = 0;
	 
	   uint32_t newaddr = 0;
	   newaddr = addr;
		
		for(i=0;i<gearkind;i++)
		 {
			 
		   u8*pbuffer = (u8*)(&wdata[i]);
			 wdata[i].gearPress = wdata[i].gearPress/10;
	     MX25L6406_Write(pbuffer,addr,sizeof(GearPattern ));
		   printf("wdata[%d].gear=%d\r\n", i,wdata[i].gear);
			 printf("wdata[%d].gearPress=%d\r\n",i,wdata[i].gearPress);
			 addr+=sizeof(GearPattern );
		 }
		 
  MX25L6406_Write((u8*)&gearkind, newaddr+secop(1),1);
 }	
	
	
	
void FlashReadGear(GearPattern rdata[],uint8_t gearkind,uint32_t addr)
 {
 
			 int i = 0;
	   
	    
     for(i=0;i<gearkind;i++)
			{
			  MX25L6406_Read((u8*)&rdata[i],addr,sizeof(GearPattern));
	      printf("rdata[%d].gear=%d\r\n", i,rdata[i].gear);
			  printf("rdata[%d].gearPress=%d\r\n",i,rdata[i].gearPress);
				addr +=sizeof(GearPattern);
			
		 }
 
 
 }
 
 
 /**************************************************************************
  ����������uint8_t* pBuff
 
 
 **************************************************************************/
 
 void  GetSensor(uint8_t* pBuff,TorquePattern Product[],uint32_t kind)
  {
		
		int count = 0;
		int i = 0;
		int j  = 0;
	
	  count = MX25L6406_ReadU16(secop(2002));    //      ���������Ʒ����
	  for(i=0;i<count;i++)                           //������Ʒ����
		 {
		   for(j=0;j<kind;j++)                         //����������ģʽ�µĲ�Ʒ
			  {
				 	 if(strcmp((char*)&pBuff[j*14+9],(char*)Product[i].ProductType)==0)   //������ڷ��ض�Ӧ������
						  {
                   Product[i].SensorTor = PTR2U32(&pBuff[j*14+19]); 
								   printf("Product[%d].SensorTor=%d\r\n",i,Product[i].SensorTor);
								   break;
							}
				}
			 
		 }
	
	
	
	}
 
 
 
 
 
 
 
 


 void FlashReadScreenVar(ModifyVarStruct* rdata,uint32_t addr)
 {

   MX25L6406_Read((u8*)rdata,addr,sizeof(ModifyVarStruct));
	 
	  printf("rdata->Language=%d\r\n",rdata->Language);
	  if(rdata->Language !=0 && rdata->Language != 1)
		 {
		   rdata->Language = 0;
		 }
	 

	 
	 printf("rdata->ChartType=%d\r\n",rdata->ChartType);
		 
		if(rdata->ChartType !=0 && rdata->ChartType != 1)
		 {
		   rdata->ChartType = 0;
		 }
		 
	
	 printf("rdata->pressUint=%d\r\n",rdata->pressUint);
		 
		if(rdata->pressUint !=0 && rdata->pressUint != 1 && rdata->pressUint !=2)
		 {
		  rdata->pressUint = 0;
		 }
		 

	   
//	  if(rdata->WorkMode !=0 && rdata->WorkMode != 1 && rdata->WorkMode !=2 && rdata->WorkMode!=3 && rdata->WorkMode !=4 && rdata->WorkMode !=5)
//		 {
//		  rdata->WorkMode = 0;
//		 }
		 
		 printf("rdata->WorkMode=%d\r\n",rdata->WorkMode);	
	
		 printf("wdata->TorqueUint=%d\r\n",rdata->TorqueUint);
		 
		if(rdata->TorqueUint !=0 && rdata->TorqueUint != 1)
		 {
		   rdata->TorqueUint = 0;
		 }
		 
	
		 printf("wdata->fabricName=%d\r\n",rdata->fabricName);
	


		
		 printf("wdata->MaxtorVal_TorMode=%d\r\n",rdata->MaxtorVal_TorMode);
	
	
		
	
		
		
		 printf("rdata->TartorVal_TorMode=%d\r\n",rdata->TartorVal_TorMode);


		
 
		
		 printf("wdata->garde=%d\r\n",rdata->garde);
		 printf("wdata->diameter=%d\r\n",rdata->diameter);
		 printf("wdata->garde_M=%d\r\n",rdata->garde_M);
		 printf("wdata->diameter_M=%d\r\n",rdata->diameter_M);
		 
		 printf("wdata->BoltDiameterArr=%s\r\n",rdata->BoltDiameterArr);
		 printf("wdata->BoltGardeArr=%s\r\n",rdata->BoltGardeArr);
		 printf("wdata->BoltDiameterArr_M=%s\r\n",rdata->BoltDiameterArr_M);
		 printf("wdata->BoltGardeArr_M=%s\r\n",rdata->BoltGardeArr_M);
		 printf(" wdata->TartorVal_BoltMode=%d\r\n",rdata->TartorVal_BoltMode);
	
		

	 
	 
	 
	   printf("wdata->Angle=%d\r\n",rdata->Angle);
	   printf("wdata->presetTor_AngMode=%d\r\n",rdata->presetTor_AngMode);
	
	 

	 
	 
	 
	    printf("wdata->gear=%d\r\n",rdata->gear);
	  	printf("wdata->geartor=%d\r\n",rdata->geartor);

	 
	 
		 
		 
		 
		 
		  printf("wdata->presettor_sensor=%d\r\n",rdata->presettor_sensor);


		 
	
		  printf("wdata->tartor_sensor=%d\r\n",rdata->tartor_sensor);

			
	
		 
		 
		 
 }



 void FlashWriteScreenVar(ModifyVarStruct* wdata,uint32_t addr)
  {
		
		
	
		
	    u8* pBuffer = (u8*)(wdata);
		 MX25L6406_Write(pBuffer,addr,sizeof(ModifyVarStruct));
		

	
	
	}
 
 
 
 
 
 
 
 
 
 
	
	
	
	
	
	
	
	
	
	

