
#include "pclink.h"
#include  "MX25L.h"
#include "screendriver.h"

TorquePattern  TorquePatternVar[50] = {0};
//MemoryFlag     MemoryFlagVar = {0};



/****************************************************************
函数功能：从上位机接收到数据修改时间
函数参数：uint16_t year,
          uint8_t month,
					uint8_t day,
					uint8_t hour,
					uint8_t minute,
					uint8_t sec
函数返回值：无
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
 RTC_Set(calendar.w_year ,calendar.w_month,calendar.w_date , calendar.hour,calendar.min,calendar.sec);  //设置时间	
 }





/*******************************************************************

函数功能：从上位机得到产品的名称和系数给结构体数组赋值
函数参数：TorquePattern Product[]：指向结构体数组的变量
          uint8_t kind 结构体数组的大小
          uint8_t* pBuffer：上位机发来的数据

********************************************************************/


void getProduct(TorquePattern Product[],uint16_t kind,uint8_t* pBuffer)
{

    uint16_t i = 0;
    

	 for(i = 0;i<kind;i++)
	 {
		 
		  memset(&Product[i],0,sizeof(TorquePattern));        //清空缓冲区    
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
	    //从该扇区读出上一次存到的数加上新的产品名称
	     MX25L6406_Erase_Sector(2003);                    //擦除保存上一次存扳手的扇区
	     MX25L6406_Erase_Sector(2002);                    //擦除保存上一次存扳手的扇区 
	 
	     MX25L6406_WriteU16(secop(2002),0);               //记录产品个数的扇区清0
	 
	     for(i=2004;i<=2018;i++){
				  MX25L6406_Erase_Sector(i); 
			 }
			 
	    
	
}




 
/*******************************************************************
 函数功能：查询上位机发来的螺栓帧的扳手名称有没有存在flash中
 函数参数：pDest：存在flash里面的扳手名称
           pSrc：上位机发来的扳手名称
 函数返回值：1：扳手名称存在
             0：扳手名称不存在
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
 函数功能：从flash中读出扳手系数和名称给结构体赋值
 函数参数：TorquePattern* rdata：结构体的地址
           uint32_t addr：保存扳手名称和系数的地址
           uint8_t kind：存在flash里面扳手的个数   
 
 函数返回值；flash已经保存的扳手名称和系数
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
函数功能：对比flash里面的的扳手，如果不存在就存下
函数产数：TorquePattern* Src；上位机发来的扳手名称和数据
          uint32_t addr：存下的首地址
          uint8_t kind：发来的扳手个数 
         
函数返回值：无

************************************************************************/

void CompareSaveTorquePattern(TorquePattern* Src,uint32_t addr,uint16_t kind)
 {
	      uint16_t count = 0;
	      uint32_t newCount = 0;
	     
	      uint32_t i = 0;
//	      uint32_t j = 0;
	   
	   
//				TorquePattern rdata[40] = {0};  //与上位机发来的扳手参数做比较的缓冲区内容
				 newCount = addr;
      //  count =  MX25L6406_ReadU16(addr);    //      读出保存产品个数
				printf("Last product kind=%d\r\n",count);
	     if(count==0){                                          //   还没有保存过扳手全部保存到flsh中                                      				
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
						   MX25L6406_Erase_Sector(i);//擦除保存螺栓的扇区
						 }
       		MX25L6406_WriteU16(newCount,kind);				 //保存产品的个数	 
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
 函数功能：接收上位机发来的扳手名称,对比flash里面
           存在的扳手名称
 函数参数  record[i+1] = i+1; //i=proname;
           record[1] = 1;record[2] = 2;
           表示螺栓产品的名称对应的位置
           uint8_t record[]:记录螺栓产品名称出现的位置
           uint32_t addr:记录表存在的起始地址
           存在扇区?SAVEBOLTPOS中
 函数返回值：螺栓产品名称出现的位置
             如果不存在该产品就返回0;
 
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
						 if(strncmp(pBuff,rdata[i].ProductType,10) ==0 )   //如果存在返回对应的坐标
						  {
               printf("i=%d\r\n",i);
								return (i+1);
							}
		        }
		  return 0 ;
 }
 
/****************************************************************
 
函数功能：保存螺栓的结构体属性公英制下的直径和等级
          
函数参数：uint8_t* pBuff : 上位机发来的指令      
          BoltPattern*Src：保存结果数组的首地址
                           保存螺栓的直径等级个数
          BoltGardeDiaArr*Data：保存螺栓的直径和等级名称    
          uint8_t Pos：螺栓产品名称 对应的位置
          uint32_t addr：保存螺栓结构体属性的首地址
 
函数返回值：无
******************************************************************/
uint8_t RecordBoltPos[40]  = {0};                 //记录产品的位置

BoltGardeDiaArr BoltGardeDiaArrVar = {0};         //保存螺栓直径等级名称的结构体
//TorqueValStruct TorqueValStructVar = {0};         //保存螺栓直径等级对应的扭矩制


void  GetBoltStruct(uint8_t* pBuff,TorquePattern Product[],BoltGardeDiaArr*Data,uint8_t Pos)
 {
	            
              uint8_t i = 0;
	            uint8_t j = 0;
	            uint16_t len = 0;
	            const int column = sizeof(Data->BoltDiaArr_I[i]);   //列数
	            printf("column=%d\r\n",column);
	            uint32_t Arr32[10] = {0};
							
							uint16_t   PosMeticDia   =   pBuff[18];                     //公制直径个数
				      printf("PosMeticDia=%d\r\n",PosMeticDia);
							uint16_t   PosMeticGar   =   pBuff[19+pBuff[18]*10];        //公制等级个数
							printf("PosMeticGar=%d\r\n",PosMeticGar);
							uint16_t   PosMericData  =   20 + PosMeticDia*10 + PosMeticGar*10+(PosMeticDia*PosMeticGar)*4;  //数据区起始位置
						  printf(" PosMericData=%d\r\n",PosMericData);
							uint16_t   PosImpDia   =  pBuff[PosMericData+1];          //英制直径个数
							printf("PosImpDia=%d\r\n",PosImpDia);
							uint16_t   PosImpGar   =  pBuff[PosMericData+2+pBuff[PosMericData+1]*10];  //英制等级个数
							printf("PosImpGar=%d\r\n",PosImpGar);
							memset(Data,0,sizeof(BoltGardeDiaArr));                      //清空缓冲区
							if(pBuff[PosMericData]==1){
	
	            Product[Pos-1].diameter_Imp = PosImpDia ;                      
              Product[Pos-1].garde_Imp = PosImpGar;
								
							}
							
							if(pBuff[17] == 0){
							
							 Product[Pos-1].diameter_Metric =    PosMeticDia;
	             Product[Pos-1].garde_Metric    =    PosMeticGar ;
							}
							
							
						for(i=0;i< Product[Pos-1].diameter_Metric;i++)         //得到公制产品的直径
	            {		
								strncpy((char*)Data->BoltDiaArr_M[i],(char*)&pBuff[19+i*10],10);//i的值需要更改, 保存  
                printf("getData->BoltDiaArr_M[%d]=%s\r\n",i,Data->BoltDiaArr_M[i]);							
				      }	
							
							
						for(i=0;i< Product[Pos-1].garde_Metric;i++)          //得到公制产品的等级
	            {		
								strncpy((char*)Data->BoltGardeArr_M[i],(char*)&pBuff[20+pBuff[18]*10+i*10],10);//i的值需要更改, 保存 
               	printf("getData->BoltGardeArr_M[%d]=%s\r\n",i,Data->BoltGardeArr_M[i]);							
				      }	
							
							
							   
            for(i=0;i<Product[Pos-1].garde_Metric;i++)            //得到公制的螺栓直径等级对应的扭矩值
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
							 
							 
							 
							
			
							
            for(i=0;i< Product[Pos-1].diameter_Imp;i++)         //得到英制产品的直径            
	            {		
								strncpy((char*)Data->BoltDiaArr_I[i],(char*)&pBuff[PosMericData+2+i*10],10);//i的值需要更改, 保存  
                printf("getData->BoltDiaArr_I[%d]=%s\r\n",i,Data->BoltDiaArr_I[i]);								
				      }
							
							
						for(i=0;i< Product[Pos-1].garde_Imp;i++)         //得到英制产品的等级
	            {		
								strncpy((char*)Data->BoltGardeArr_I[i],(char*)&pBuff[PosMericData+3+pBuff[PosMericData+1]*10+i*10],10);//i的值需要更改, 保存  
                 printf("getData->BoltGardeArr_I[%d]=%s\r\n",i,Data->BoltGardeArr_I[i]);								
				      }	
							
							
							
					
						 len = 0;
            for(i=0;i<Product[Pos-1].garde_Imp;i++)              //得到英制的螺栓直径等级对应的扭矩值
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
 函数功能：保存螺栓的直径和等级名称
 函数参数：BoltGardeDiaArr*Data：螺栓的结构体指针
           uint32_t addr：产品的地址
           uint8_t Pos：产品的位置
 
 函数返回值：无
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
		
		 int row = sizeof(Data->BoltDiaArr_I[i][j]) /sizeof(Data->BoltDiaArr_I[i]);  //行数
		 printf("row=%d\r\n",row);
		 int column = sizeof(Data->BoltDiaArr_I[i]);                        //列数
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
	   addr7 = addr-secop(1)+sizeof(TorquePattern)*(Pos-1);                  //保存产品对应的公制英制个数
		 printf("addr7=%d\r\n",addr7/4096);
		 MX25L6406_Write(pbuffer,addr7,sizeof(TorquePattern ));                //保存公英制的螺栓直径和等级个数  
		
		 for(i=0;i<20;i++)
		  {
			//	printf("");
			  MX25L6406_Write(Data->BoltDiaArr_I[i],addr1+(Pos-1)* 200,10);   //保存英制产品的直径
			  addr1 +=10;	
			}
			
			
	    for(i=0;i<20;i++)
		  {
	       printf("2\r\n");
			 MX25L6406_Write(Data->BoltGardeArr_I[i],addr2+(Pos-1)* 240 ,12);//保存英制产品的等级
				  addr2 += 12;	
			}
			
			for(i=0;i<20;i++)
		  {
				 printf("3\r\n");
			 MX25L6406_Write(Data->BoltDiaArr_M[i],addr3+(Pos-1)*200,10);//保存公制产品的直径
			  addr3 += 10;		
			}
			
			for(i=0;i<20;i++)
		  {
				  printf("4\r\n");
			 MX25L6406_Write(Data->BoltGardeArr_M[i],addr4+(Pos-1)*240,12);//保存公制产品的等级
			 addr4 += 12;	
			}
			
		  for(i=0;i<20;i++)                                                        //保存英制的螺栓直径等级对应的扭矩值
		  {
			   printf("5\r\n");
			   MX25L6406_WriteU32ARR(Data->Val_I[i],addr5+(Pos-1)*800,10);	
         				
         addr5 += 10*4;
			}
		  for(i=0;i<20;i++)                                                        //保存英制的螺栓直径等级对应的扭矩值
		  {
			  printf("6\r\n");
			   MX25L6406_WriteU32ARR(Data->Val_M[i],addr6+(Pos-1)*800,10);	
         				
         addr6 += 10*4;
			}
			
	}
 
 /***************************************************************************************
	函数功能：从flash里面读出产品的直径和等级给结构体赋值
	函数参数：BoltGardeDiaArr*Data：结构体指针
	          uint32_t addr：首地址
	          uint8_t Pos：产品对应的位置
  函数返回值：BoltGardeDiaArr*Data：保存螺栓直径等级的名称
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
			
			  MX25L6406_Read(Data->BoltDiaArr_I[i],addr1+(Pos-1)*200,10);   //读出保存英制产品的直径
			  addr1+= 10;			
			}
			
	    for(i=0;i<rdata[Pos-1].garde_Imp;i++)
		  {
			 
			 MX25L6406_Read(Data->BoltGardeArr_I[i],addr2+(Pos-1)*240,12);//读出保存英制产品的等级
			 addr2+=12;			
			}
			
			for(i=0;i<rdata[Pos-1].diameter_Metric;i++)
		  {
			
			 MX25L6406_Read(Data->BoltDiaArr_M[i],addr3+(Pos-1)*200,10);//读出保存公制产品的直径
			 addr3 += 10;	
			}
			
			for(i=0;i<rdata[Pos-1].garde_Metric;i++)
		  {
			
			 MX25L6406_Read(Data->BoltGardeArr_M[i],addr4+(Pos-1)*240,12);//读出保存公制产品的等级	
			 addr4 += 12;	
			}
			
			
			for(i=0;i<rdata[Pos-1].garde_Imp;i++)                                                        //读出保存英制的螺栓直径等级对应的扭矩值
		  {
			 
					 MX25L6406_ReadU32ARR(Data->Val_I[i],addr5+(Pos-1)*800,10);	
					 addr5 += 40;
			}
			
		  for(i=0;i<rdata[Pos-1].garde_Metric;i++)                                                        //读出保存英制的螺栓直径等级对应的扭矩值
		  {
			 
					   MX25L6406_ReadU32ARR(Data->Val_M[i],addr6+(Pos-1)*800,10);	
					   addr6 += 40;
			
			}
			
		for(i=0;i<rdata[Pos-1].garde_Imp;i++)                                                        //读出保存英制的螺栓直径等级对应的扭矩值
		  {
			 
				 for(j=0;j<rdata[Pos-1].diameter_Imp;j++){
				
				 }
			}
			
				
	for(i=0;i<rdata[Pos-1].garde_Metric;i++)                                                        //读出保存英制的螺栓直径等级对应的扭矩值
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
函数功能：读出扳手的位置表



***********************************************/
 
void FlashGetRecord(u8* record,uint32_t addr,uint8_t Pos)
{
              
	MX25L6406_Read((u8*)&record[Pos],addr+Pos*8,1); //第一个产品对应的位置

}
 
/********************************************************
函数功能：设置出厂编号

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
函数功能：设置设备名称

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
函数功能：设置设备编号

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
函数功能：设置操作人员名称

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
函数功能：设置操作密码

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
	函数功能：设置使用次数
	
******************************************************/
 
	
 void setUsingTimes(uint8_t*pSrc,upComputerStruct*pDest)
  {
		
	  memset(&pDest->UsingTime,0,sizeof(pDest->UsingTime));

		pDest->UsingTime = PTR2U32(pSrc);
		printf("pDest->UsingTime=%d\r\n",pDest->UsingTime);
	  printf("sizeof(pDest->UsingTime)=%d\r\n",sizeof(pDest->UsingTime));
	}
 
/*****************************************************
	函数功能：存入上位机发送来的数据
	函数参数：
	
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

		    TorquePattern rdata[40] = {0};  //与上位机发来的扳手参数做比较的缓冲区内容
        count =  WreadNumFormFlash(secop(2) ,0,10);    //      读出保存产品个数
        FlashGetTorquePattern(rdata,secop(1),count);        //读出存在flash里面的扳手名称和系数
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
从上位机得到：最大角度值保存到flash中
函数参数?uuint16_t angle：最大角度值
          uint8_t* buf：上位机得到的字符串
函数返回值无


************************************************************/

uint16_t MaxAngle = 0;


void getAngle(uint16_t* angle,uint8_t buf[])
{
*angle = PTR2U16(buf+7);
printf("angle=%d\r\n",*angle);
}
	 
	 
/*************************************************************************
函数功能:上位机下发挡位指令

************************************************************************/

uint8_t GearKind = 0;






GearPattern GearPatternVar[70] = {0};

void getGear(GearPattern gear[],uint8_t gearkind,uint8_t buf[])
{
   uint8_t i = 0;
	 for(i = 0;i<gearkind;i++)
	 {
		 
		     memset(&gear[i],0,sizeof(GearPattern ));        //清空缓冲区  
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
  函数参数：uint8_t* pBuff
 
 
 **************************************************************************/
 
 void  GetSensor(uint8_t* pBuff,TorquePattern Product[],uint32_t kind)
  {
		
		int count = 0;
		int i = 0;
		int j  = 0;
	
	  count = MX25L6406_ReadU16(secop(2002));    //      读出保存产品个数
	  for(i=0;i<count;i++)                           //遍历产品个数
		 {
		   for(j=0;j<kind;j++)                         //遍历传感器模式下的产品
			  {
				 	 if(strcmp((char*)&pBuff[j*14+9],(char*)Product[i].ProductType)==0)   //如果存在返回对应的坐标
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
 
 
 
 
 
 
 
 
 
 
	
	
	
	
	
	
	
	
	
	

