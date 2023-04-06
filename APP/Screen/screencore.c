#include "screencore.h"
#include "uart.h"
#include "screendriver.h"
#include "time.h"
#include "SysTick.h"


												 
												 
												 
												 
/*********************************************************
�������ܣ�����Ť�صĵ�λ
����������Unit :0 N.m
               :1 ft.lbs
          pUint:��λ�ַ�ָ��
          SourNum��Ť�ص�ֵ
         
��������ֵ����λ�ַ�ָ�룻
            DestNum��Ť��ֵ�ڲ�ͬ��λ�µĴ�С

********************************************************/												 
												 
												 
												 
char* ModifyTorqueUnit(uint8_t Unit,char pUnit[],uint32_t*DestNum,uint32_t SourNum)
{
	 char*p = pUnit;
	
   if(Unit==0)
	   {
			 
		 // memset(pUnit,0,sizeof(*pUnit));
		//	strncpy(pUnit,(const char*)"N.m",3);  
			*DestNum = SourNum;
		 }
   
    if(Unit==1)
	  {
		  //memset(pUnit,0,sizeof(*pUnit));
		//	strncpy(pUnit,(const char*)"ft.lbs",6);  
		 *DestNum = ROUND_TO_UINT32((SourNum)/1.3549);
		
		}
   return p;

}





/************************************************************
�������ܣ�����ѹ���ĵ�λ
����������pressUnit��ѹ����λ��1��Bar��2��Mpa,3:Psi
          pPressUnit:ѹ����λ�ַ�ָ��
          SourNum��ѹ��ֵ
��������ֵ�� pPressUnit:ѹ����λ�ַ�ָ��
             DestNum����ͬ��λ��ѹ��ֵ�Ĵ�С


***********************************************************/


char* ModifyPressUnit(uint8_t pressUnit,char*pPressUnit,float*DestNum,float SourNum)
{


  char* p = pPressUnit;
	
	switch(pressUnit)
	 {
	   	  case 0:*DestNum = (SourNum*10);break;
																		    
				case 1:*DestNum = (SourNum);break;
																		      
				case 2: *DestNum = (SourNum*140);break;
	 }
	 return p;
	
}


/*********************************************************
�������ܣ�����ѹ��ֵ������10��,����bar�ı�׼
����������factor��Ʒϵ��
         torquevalue:�趨��Ť��ֵ
��������ֵ���趨��Ť��ֵ��Ӣ��ѹ��,bar

********************************************************/

float getPressValue(uint32_t factor,uint32_t torquevalue)
{

   return (torquevalue*100000/factor);
	
}

/**********************************************************

����������press��ѹ��ֵ,bar
�������ܣ�DAC���ѹ����Ӧ��ѹ��
��������ֵ��д��DAC���ݼĴ���������ֵ

V = (12 * data)/65535
press/0.5  = data/273;
data = (273*2)*temp;

**********************************************************/

 uint32_t getOutData(float press)
	{
	  uint32_t data = 0;
		float temp = press/1000.0;
		
		data =(ROUND_TO_UINT32(temp*2*273));
		return data;
	
	}
	
	
	
//	/**********************************************************

//����������press��ѹ��ֵ,bar
//�������ܣ�DAC���ѹ����Ӧ��ѹ��
//��������ֵ��д��DAC���ݼĴ���������ֵ

//  Bar = 0.625*(16*(code/65536)+4)-2.5;
//  //0.05bar      327.68	
//   **********************************************************/

// uint32_t getOutData(float press)
//	{
//	  uint32_t data = 0;
//		float temp = press/1000.0;
//		
//		data =(ROUND_TO_UINT32(temp*2*328));
//		return data;
//	
//	}
	
	
	
	

	
float setTargetTorqueValVarFlag(uint8_t TorqueUint,uint32_t *targetTorVal)  
 {
	 	   
	    
        float press = 0;
	     if(*targetTorVal < (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*0.125))              //���ڲ�ƷŤ��ֵ
						{
									*targetTorVal = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*0.125);
					  }
			 if(*targetTorVal > (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA))    
						{
									*targetTorVal = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
					  }			
	 
	    press = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,*targetTorVal);  //�õ�Ŀ��ѹ��ֵ
									
			return press;
		        					
 } 	
	
	
	
	
	
	
void showPress(uint8_t memu,uint8_t pressuint,float num)
 {
 
	 float data = 0.0;
	char arr[10]  ={0};
   ModifyPressUnit(pressuint, arr,&data, num);
	
				switch(memu)
				 {
					case 1:SetTextFloat(1,7,data,2,0); break;
				  case 2:break;
					case 3:  SetTextFloat(3,6,data,2,0)	; break;
				  case 4:  SetTextFloat(4,6,data,2,0)	;break;  
					case 5:   SetTextFloat(5,7,data,2,0); break;
				 }
		  


		
}
	
	
	



/*************************************************************************
	
	
*************************************************************************/



void setLangChartFlag(uint8_t lang,uint8_t chart,uint8_t*pLang,uint8_t*pChart)
{
	uint8_t   zhowen[5] = {0xD6,0xD0,0xCE,0xC4};
//	uint8_t   yinwen[5] = {0xD3,0xA2,0xCE,0xC4};
	uint8_t   gongzhi[5] = {0xB9,0xAB,0xD6,0xC6,0x00};
	uint8_t   yinzhi[5] = {0xD3,0xA2,0xD6,0xC6};
//	uint8_t i = 0;
	if(lang == 0)
	 {
		  if(chart == 0)
			 {
			  
	      SetTextValue(0,2,(uint8_t*)"Imperial");
			
				 
			 }
			 
			if(chart == 1)
			 {
			
	      SetTextValue(0,2,(uint8_t*)"Metric");
		  
			 }
			 
	SetTextValue(0,1,(uint8_t*)"English");	
	SetLanguage(0,0);
	
	 }
	 
	 if(lang == 1)
	  {
		
			 if(chart == 0)
			 {
	      SetTextValue(0,2,yinzhi);
			 }
			 
			if(chart == 1)
			 {
			
				// for(i=0;i<5;i++)
				//  {
					 SetTextValue(0,2,gongzhi);
				//	}
	     
				 
			 }
	// 	for(i=0;i<5;i++)
		//	 {
			 SetTextValue(0,1,zhowen);
		//	 }
		
    SetLanguage(1,1);
		}
	

}



void setYearValVarFlag(uint16_t* year)
{
 
	if(*year <= 1970)
	 {
	  *year = 1970;
	 }
	
	
	RTC_Set(*year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
  SetTextInt32(0,3,*year,0,4);
	
	     
}









void setMonthValVarFlag(uint8_t* month)
{


if(*month> 12)*month = 1;
if((signed char)*month < 1) *month = 12;

RTC_Set(calendar.w_year,*month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
SetTextInt32(0,4,*month,0,2);

}

void setMonthValVarFlagDec(void)
{

calendar.w_month--;if((signed char)calendar.w_month<1)calendar.w_month = 1;
            #ifdef DEBUG
          //	printf("calendar.w_month=%d\r\n",calendar.w_month);
	          #endif
RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
SetTextInt32(0,4,calendar.w_month,0,2);

}



void setDayValVarFlag(uint8_t* date)
{

    
   if((Is_Leap_Year(calendar.w_year))&&(calendar.w_month==2)){
	
	         if(*date>29)*date = 1;
		       if((signed char)*date<1) *date = 29;
																							   
			        }else if(calendar.w_month==4||calendar.w_month==6||calendar.w_month==9||calendar.w_month==11||calendar.w_month==2){
																							    
					 if(*date>30)*date = 1;
		       if((signed char)*date<1) *date = 30;
																
						 }else{
																								
			     if(*date>31)*date = 1;
		       if((signed char)*date<1) *date = 31;
																								
					}
						 
	 //if((signed char)*date<1) *date = 1;
		 
					
					
	
	RTC_Set(calendar.w_year,calendar.w_month,*date,calendar.hour,calendar.min,calendar.sec);
 	SetTextInt32(0,5,*date,0,2);					 


}	









void setHourValVarFlag(uint8_t* hour)
{


	if((signed char)*hour<1) *hour = 23;
  if(calendar.hour>23) calendar.hour = 0;


	
 RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,*hour,calendar.min,calendar.sec);
 SetTextInt32(0,6,*hour,0,2);


}







void setMinuteValVarFlag(uint8_t* min)
{

if((signed char)*min<1)	*min = 59;
if(*min>59)	*min = 0;
	

	

 RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,*min,calendar.sec);
 SetTextInt32(0,7,*min,0,2);
}









void setSecondValVarFlag(uint8_t* sec)
{

   calendar.sec++;
	if(*sec>59)	*sec = 0;
  if((signed char)*sec < 1) *sec = 59;

  RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,*sec);
	SetTextInt32(0,8,*sec,0,2);

}


void ShowProductType(char*pName,uint8_t Memu)
 {
 
  int i = 0;
	 
 	  for(i=1;i<6;i++)
		{
			if(i == Memu)
			{
			  SetTextValue(i,1,(uint8_t*)pName);   //��ʾ��Ʒ����
                                             
			}
		
		}
 
}
 

/*****************************************

��ʾ���Ť��ֵ
*******************************************/

void  ShowMaxTorque(uint8_t Memu,uint32_t maxtor)
 {

	 
 	if(Memu==1)
		 {
		
		  SetTextInt32(1,6,maxtor,0,0);               //��ʾ���Ť��ֵ
		 }
		 
	if(Memu==3)
	
		 {
		 	 SetTextInt32(3,2,maxtor,0,0);             //��ʾ���Ť��ֵ
      
		 }

 }








/******************************************************************************************
 �������ܣ�����ѡ��Ĳ�Ʒ��Ӧ֪����˨��ֱ���͵ȼ�����
           uint8_t chart:��˨�Ĺ�Ӣ��
           uint8_t name����Ӧ�������±�λ��
           uint8_t*GardeNum����˨�ȼ���
           uint8_t*DiamNum����˨ֱ��
           TorquePattern Product[]����Ʒ�Ļ�����Ϣ
           BoltGardeDiaArr*Data����˨��ֱ���ȼ� 

           
           
 
 
 
*******************************************************************************************/


uint32_t  setBoltDiameterValVarFlag1 (uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data) 
 {
   int i = 0;
	 int j = 0;
	 uint32_t BoltTorqueVal = 0;
	
  if(ModifyVarStructVar.ChartType == 0){    //Ӣ���µ���˨ֱ���͵ȼ�
		
	  if(Product[ModifyVarStructVar.fabricName-1].diameter_Imp == 0 || Product[ModifyVarStructVar.fabricName-1].garde_Imp== 0)
		  {
				
				memset(ModifyVarStructVar.BoltDiameterArr,0,sizeof(ModifyVarStructVar.BoltDiameterArr));
				memset(ModifyVarStructVar.BoltGardeArr,0,sizeof(ModifyVarStructVar.BoltGardeArr));
	  
			  BoltTorqueVal = 0;
				
			  return BoltTorqueVal;
				
			  //SetTextValue(2,2,(uint8_t*)" ");
			//SetTextValue(2,3,(uint8_t*)" ");
			 // return 0;
			}
			
		  if(*DiamNum  > Product[ModifyVarStructVar.fabricName-1].diameter_Imp){  //���ڵĸò�Ʒ��Ӧ����˨ֱ������
				  *DiamNum = 1;  
			   }
				
		  if((signed char)*DiamNum  < 1){        //���ڵĸò�Ʒ��Ӧ����˨ֱ������
			     *DiamNum = Product[ModifyVarStructVar.fabricName-1].diameter_Imp;  
				 }
				 
			if(*GardeNum  >Product[ModifyVarStructVar.fabricName-1].garde_Imp){  //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
				               *GardeNum = 1;  
				}
				
		    if((signed char)*GardeNum  < 1){          //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
			   *GardeNum = Product[ModifyVarStructVar.fabricName-1].garde_Imp;  
				}
				
			for(i=0;i<=*DiamNum;i++){                   //��ʾ��˨ֱ��
			 	
					if( i== *DiamNum-1){
					 	memset(ModifyVarStructVar.BoltDiameterArr,0,10);
						SetTextValue(2,2,(uint8_t*)Data->BoltDiaArr_I[i]);
						strncpy((char*)ModifyVarStructVar.BoltDiameterArr,(char*)Data->BoltDiaArr_I[i],9);
						printf("ModifyVarStructVar.BoltDiameterArr=%s\r\n",ModifyVarStructVar.BoltDiameterArr);
						strncpy((char*)SysMemoryParaVar.BoltDia,(char*)ModifyVarStructVar.BoltDiameterArr,10);
						
						  
						}
				}
				
			for(j=0;j<=*GardeNum;j++){                     //��ʾ��˨�ȼ�
			 	
					 if( j== *GardeNum-1){
					  
							memset(ModifyVarStructVar.BoltGardeArr,0,10);
						  SetTextValue(2,3,(uint8_t*)Data->BoltGardeArr_I[j]); 
							strncpy((char*)ModifyVarStructVar.BoltGardeArr,(char*)Data->BoltGardeArr_I[j],9);
						 strncpy((char*)SysMemoryParaVar.BoltGarde,(char*)ModifyVarStructVar.BoltGardeArr,10);
						 printf("ModifyVarStructVar.BoltGardeArr=%s\r\n",ModifyVarStructVar.BoltGardeArr);
						 							
					 }
			 }
				
				BoltTorqueVal = Data->Val_M[*GardeNum-1][*DiamNum-1]; //�õ�ֱ���͵ȼ���Ӧ��Ť��ֵ
			  printf("Data->Val_I[%d][%d]=%d\r\n",*GardeNum-1,*DiamNum-1,Data->Val_I[*GardeNum-1][*DiamNum-1]);
				return    BoltTorqueVal;
		}
	
		
	if(ModifyVarStructVar.ChartType==1) {            //������ĸֱ���͵ȼ�
			
		if(Product[ModifyVarStructVar.fabricName-1].diameter_Metric == 0 || Product[ModifyVarStructVar.fabricName-1].garde_Metric==0)
		  {
				
				
				 memset(ModifyVarStructVar.BoltDiameterArr_M,0,sizeof(ModifyVarStructVar.BoltDiameterArr_M));
			 	 memset(ModifyVarStructVar.BoltGardeArr_M,0,sizeof(ModifyVarStructVar.BoltGardeArr_M));
				
				 BoltTorqueVal = 0;
			   return BoltTorqueVal;
				// SetTextValue(2,2,(uint8_t*)" ");
				// SetTextValue(2,3,(uint8_t*)" ");
			  // return 0;
			}
			
			
		 	if(*DiamNum  > Product[ModifyVarStructVar.fabricName-1].diameter_Metric){  //���ڵĸò�Ʒ��Ӧ����˨ֱ������
			  
				  *DiamNum = 1;  
				}
				
		   if((signed char)*DiamNum  < 1){             //���ڵĸò�Ʒ��Ӧ����˨ֱ������
			  
				  *DiamNum = Product[ModifyVarStructVar.fabricName-1].diameter_Metric;  
				}
				
				
			 if(*GardeNum  > Product[ModifyVarStructVar.fabricName-1].garde_Metric){  //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
			  
				  *GardeNum = 1;  
				}
				
		   if((signed char)*GardeNum  < 1){         //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
			  
				  *GardeNum = Product[ModifyVarStructVar.fabricName-1].garde_Metric;  
				}
				
			for(i=0;i<=*DiamNum;i++){                   //��ʾ��˨ֱ��
			 	
					 if( i== *DiamNum-1){
					  
							memset(ModifyVarStructVar.BoltDiameterArr_M,0,9);
						  SetTextValue(2,2,(uint8_t*)Data->BoltDiaArr_M[i]);
							strncpy((char*)ModifyVarStructVar.BoltDiameterArr_M,(char*)Data->BoltDiaArr_M[i],9);
						  printf("ModifyVarStructVar.BoltDiameterArr=%s\r\n",ModifyVarStructVar.BoltDiameterArr_M);
						  strncpy((char*)SysMemoryParaVar.BoltDia,(char*)ModifyVarStructVar.BoltDiameterArr_M,10);
						     
						}
				}
				
			for(j=0;j<=*GardeNum;j++){                     //��ʾ��˨�ȼ�
			 	
					 if( j== *GardeNum-1){
					  
							memset(ModifyVarStructVar.BoltGardeArr_M,0,9);
						   SetTextValue(2,3,(uint8_t*)Data->BoltGardeArr_M[j]); 
							strncpy((char*)ModifyVarStructVar.BoltGardeArr_M,(char*)Data->BoltGardeArr_M[j],9);
						 
						 //printf("ModifyVarStructVar.BoltGardeArr=%s\r\n",ModifyVarStructVar.BoltGardeArr);
						   strncpy((char*)SysMemoryParaVar.BoltGarde,(char*)ModifyVarStructVar.BoltGardeArr_M,10);
						 
						}
				}	
//				
			BoltTorqueVal = Data->Val_M[*GardeNum-1][*DiamNum-1]; //�õ�ֱ���͵ȼ���Ӧ��Ť��ֵ
			 printf("Data->Val_I[%d][%d]=%d\r\n",*GardeNum-1,*DiamNum-1,Data->Val_I[*GardeNum-1][*DiamNum-1]);
				return    BoltTorqueVal;
		 
		 }
	 		
 }

 

/******************************************************************************************
 �������ܣ�����ѡ��Ĳ�Ʒ��Ӧ֪����˨��ֱ���͵ȼ�����
           uint8_t chart:��˨�Ĺ�Ӣ��
           uint8_t name����Ӧ�������±�λ��
           uint8_t*GardeNum����˨�ȼ���
           uint8_t*DiamNum����˨ֱ��
           TorquePattern Product[]����Ʒ�Ļ�����Ϣ
           BoltGardeDiaArr*Data����˨��ֱ���ȼ� 

           
           
 
 
 
*******************************************************************************************/
 
uint32_t  setBoltGradeValVarFlag (uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data) 
 {
   int i = 0;
	 int j = 0;
	 uint32_t BoltTorqueVal = 0;
	
  if(ModifyVarStructVar.ChartType == 0){    //Ӣ���µ���˨ֱ���͵ȼ�
		
	  if(Product[ModifyVarStructVar.fabricName-1].diameter_Imp == 0 || Product[ModifyVarStructVar.fabricName-1].garde_Imp==0)
		  {
				
				memset(ModifyVarStructVar.BoltDiameterArr,0,sizeof(ModifyVarStructVar.BoltDiameterArr));
				memset(ModifyVarStructVar.BoltGardeArr,0,sizeof(ModifyVarStructVar.BoltGardeArr));
	  
			  BoltTorqueVal = 0;
				
			  return BoltTorqueVal;
			}
				
	
	if(*DiamNum  > Product[ModifyVarStructVar.fabricName-1].diameter_Imp){  //���ڵĸò�Ʒ��Ӧ����˨ֱ������
				  *DiamNum = 1;  
			   }
				
	if((signed char)*DiamNum  < 1){        //���ڵĸò�Ʒ��Ӧ����˨ֱ������
			     *DiamNum = Product[ModifyVarStructVar.fabricName-1].diameter_Imp;  
				 }
				 
	if(*GardeNum  >Product[ModifyVarStructVar.fabricName-1].garde_Imp){  //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
				               *GardeNum = 1;  
	}
				
	 if((signed char)*GardeNum  < 1){          //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
			   *GardeNum = Product[ModifyVarStructVar.fabricName-1].garde_Imp;  
	}
				
			for(i=0;i<=*DiamNum;i++){                   //��ʾ��˨ֱ��
			 	
					if( i== *DiamNum-1){
					 	memset(ModifyVarStructVar.BoltDiameterArr,0,10);
						strncpy((char*)ModifyVarStructVar.BoltDiameterArr,(char*)Data->BoltDiaArr_I[i],10);
						}
				}
				
			for(j=0;j<=*GardeNum;j++){                     //��ʾ��˨�ȼ�
			 	
					 if( j== *GardeNum-1){
					  
							memset(ModifyVarStructVar.BoltGardeArr,0,12);
							strncpy((char*)ModifyVarStructVar.BoltGardeArr,(char*)Data->BoltGardeArr_I[j],12);
				
					 }
			 }
				
				  BoltTorqueVal = Data->Val_I[*GardeNum-1][*DiamNum-1]; //�õ�ֱ���͵ȼ���Ӧ��Ť��ֵ
				  return    BoltTorqueVal;
		}
		
	if(ModifyVarStructVar.ChartType==1) {           //������ĸֱ���͵ȼ�
			
		if(Product[ModifyVarStructVar.fabricName-1].diameter_Metric == 0 || Product[ModifyVarStructVar.fabricName-1].garde_Metric==0)
		  {
				
				
				memset(ModifyVarStructVar.BoltDiameterArr_M,0,sizeof(ModifyVarStructVar.BoltDiameterArr_M));
				memset(ModifyVarStructVar.BoltGardeArr_M,0,sizeof(ModifyVarStructVar.BoltGardeArr_M));
				
				BoltTorqueVal = 0;
			  return BoltTorqueVal;
			}
		
			
		 	if(*DiamNum  > Product[ModifyVarStructVar.fabricName-1].diameter_Metric){  //���ڵĸò�Ʒ��Ӧ����˨ֱ������
			  
				  *DiamNum = 1;  
				}
				
		   if((signed char)*DiamNum  < 1){             //���ڵĸò�Ʒ��Ӧ����˨ֱ������
			  
				  *DiamNum = Product[ModifyVarStructVar.fabricName-1].diameter_Metric;  
				}
				
				
			 if(*GardeNum  > Product[ModifyVarStructVar.fabricName-1].garde_Metric){  //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
			  
				  *GardeNum = 1;  
				}
				
		   if((signed char)*GardeNum  < 1){         //���ڵĸò�Ʒ��Ӧ����˨�ȼ�����
			  
				  *GardeNum = Product[ModifyVarStructVar.fabricName-1].garde_Metric;  
				}
				
			for(i=0;i<=*DiamNum;i++){                   //��ʾ��˨ֱ��
			 	
					 if( i== *DiamNum-1){
					  
							memset(ModifyVarStructVar.BoltDiameterArr_M,0,10);
					
							strncpy((char*)ModifyVarStructVar.BoltDiameterArr_M,(char*)Data->BoltDiaArr_M[i],10);
					
						   
						}
				}
				
			for(j=0;j<=*GardeNum;j++){                     //��ʾ��˨�ȼ�
			 	
					 if( j== *GardeNum-1){
					  
							memset(ModifyVarStructVar.BoltGardeArr_M,0,12);
							strncpy((char*)ModifyVarStructVar.BoltGardeArr_M,(char*)Data->BoltGardeArr_M[j],12);
						}
				}	
				
				BoltTorqueVal = Data->Val_M[*GardeNum-1][*DiamNum-1];  //�õ�ֱ���͵ȼ���Ӧ��Ť��ֵ
			
				return    BoltTorqueVal;
		 
		 } 
 }

 
 
uint32_t setSensorPresetTorValVarFlag(uint8_t Unit,uint32_t* presetvalue)
 {
 
 
  	
	 
     uint32_t press = 0;
	     if(*presetvalue<(ROUND_TO_UINT32(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*0.1)))
						{
									*presetvalue = (ROUND_TO_UINT32(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*0.1));
					  }
			 if(*presetvalue>(ROUND_TO_UINT32(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA)))
						{
									*presetvalue = (ROUND_TO_UINT32( TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA));
					  }			
	 
	      press = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,*presetvalue);  //�õ�Ԥ��ѹ��ֵ
	 			
		 return press;
  
 }
 
 //0.01*i;(0.0001*i) i = [0,300] 
 //50,100,150,200,250,300
uint32_t RandomFun(uint32_t data,uint16_t seed)
 {
	   uint32_t redata = 0;
		  srand(seed);
	 
		 if(data>0&&data<50){	              //0-10;
		    if(seed%2==0){
				 redata = data+rand()%50;
					 }else
					  redata = data-rand()%10;				
			}
		 
		 if(data>=100&&data<=500){
				 
		    if(seed%2==0){
				 redata = data+rand()%20;
					 }else
					  redata = data-rand()%20;		  //0-20
		 }
	 	
		 
		if(data>500&&data<=1000){
			 	 
		    if(seed%2==0){
				 redata = data+rand()%50;         //0-50
					 }else
					  redata = data-rand()%50;		
		 
	  }	 
		 if(data>1000&&data<=5000){             //0-100
			 
		    if(seed%2==0){
				 redata = data+rand()%100;
					 }else
					  redata = data-rand()%100;
	 }
		 
		if(data>5000){                        //0-200
			 
		    if(seed%2==0){
				 redata = data+rand()%200;
					 }else
					  redata = data-rand()%200;	
	
	}
    return redata;

}
 
 
 
 
 
 
 
 
 /*********************************************************************
 
 �������ܣ���¼ÿһ�β������ֵ�����
 
 *********************************************************************/
 
 
 void RecordDataFuc(SysMemoryPara* pSysMemoryParaVar)
  {
	
		
		uint32_t i = 0;
	memset(pSysMemoryParaVar,0,sizeof(SysMemoryPara));         //����������
		
	pSysMemoryParaVar->mode =  ModifyVarStructVar.WorkMode  ;  //����ģʽ
		
 // printf("pSysMemoryParaVar->mode=%d\r\n",pSysMemoryParaVar->mode);
		
		

	
	switch(pSysMemoryParaVar->mode) 
		{
		   case 1:   pSysMemoryParaVar->tarque = ModifyVarStructVar.TartorVal_TorMode ; 
                // pSysMemoryParaVar->actque = RandomFun( pSysMemoryParaVar->tarque,Seed);	
			             //i  = RandomFun( 300,Seed);
			           //  if(i>300) i = 300;
			           //  pSysMemoryParaVar->WorkPress = RandomFun(SetPress/100,Seed); 
		              pSysMemoryParaVar->actque = pSysMemoryParaVar->tarque*(0.95+0.0001*Seed);
		            	pSysMemoryParaVar->WorkPress  =  (pSysMemoryParaVar->actque*100)/(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10);
			            pSysMemoryParaVar->tigresult = 1;
			             if(ERROR_HAND == 1)
		                {
										 pSysMemoryParaVar->WorkPress = ADCGetPress[5]*100;
			               pSysMemoryParaVar->actque = ADCGetPress[5] *TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
				             pSysMemoryParaVar->tigresult = 0;  //š�����
											
		                }
			
			
			         //  printf(" pSysMemoryParaVar->WorkPress =%d\r\n",  pSysMemoryParaVar->WorkPress);
			           break; 
			         
			      
			
			 case 2: pSysMemoryParaVar->tarque = ModifyVarStructVar.TartorVal_BoltMode;
			
             //  pSysMemoryParaVar->actque = RandomFun( pSysMemoryParaVar->tarque,Seed);
			
			      //   printf("pSysMemoryParaVar->actque=%d\r\n",pSysMemoryParaVar->actque);	
			      //   printf("pSysMemoryParaVar->tarque=%d\r\n",pSysMemoryParaVar->tarque);
			        //  pSysMemoryParaVar->WorkPress = RandomFun( SetPress/100,Seed);
               pSysMemoryParaVar->actque = pSysMemoryParaVar->tarque*(0.95+0.0001*Seed);
		           pSysMemoryParaVar->WorkPress  =  (pSysMemoryParaVar->actque*100)/(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10);
			           pSysMemoryParaVar->tigresult = 1;

									
                    if(ERROR_HAND == 1)
		                {
										 pSysMemoryParaVar->WorkPress = ADCGetPress[5]*100;
			               pSysMemoryParaVar->actque = ADCGetPress[5] *TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
				             pSysMemoryParaVar->tigresult = 0;  //š�����
											
		                }

										
			      //   printf(" pSysMemoryParaVar->WorkPress =%d\r\n",  pSysMemoryParaVar->WorkPress);
			        if(ModifyVarStructVar.ChartType == 0){
			          if(ModifyVarStructVar.diameter == 0)ModifyVarStructVar.diameter =1;
			            if(ModifyVarStructVar.garde==0)ModifyVarStructVar.garde = 1;
										strncpy((char*)pSysMemoryParaVar->BoltDia,(char*)ModifyVarStructVar.BoltDiameterArr,10);
				              strncpy((char*)pSysMemoryParaVar->BoltGarde,(char*)ModifyVarStructVar.BoltGardeArr,12);
	              
		            }		

              if(ModifyVarStructVar.ChartType == 1){	
		            if(ModifyVarStructVar.diameter_M ==0)ModifyVarStructVar.diameter_M = 1;
		              if(ModifyVarStructVar.garde_M==0)ModifyVarStructVar.garde_M =1;
	                  strncpy((char*)pSysMemoryParaVar->BoltDia,(char*)ModifyVarStructVar.BoltDiameterArr_M,10);
				              strncpy((char*)pSysMemoryParaVar->BoltGarde,(char*)ModifyVarStructVar.BoltGardeArr_M,12);
	            	} printf("pSysMemoryParaVar->BoltDia =%s\r\n",  pSysMemoryParaVar->BoltDia);                
			            printf("pSysMemoryParaVar->BoltGarde =%s\r\n",  pSysMemoryParaVar->BoltGarde); 
			            break;
			 case 3: 	if(ModifyVarStructVar.fabricName==0) ModifyVarStructVar.fabricName = 1;  //�����ͺ�
				        if(ModifyVarStructVar.gear == 0) ModifyVarStructVar.gear = 1;
		            pSysMemoryParaVar->gear = GearPatternVar[ModifyVarStructVar.gear-1].gear;
						    if( ModifyVarStructVar.fabricName==0) ModifyVarStructVar.fabricName = 1;
		            ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ŀ��Ť��ֵ	 
	              
			           pSysMemoryParaVar->tarque =ModifyVarStructVar.geartor;
								// pSysMemoryParaVar->actque = RandomFun( pSysMemoryParaVar->tarque,Seed);
               //  pSysMemoryParaVar->WorkPress = RandomFun( SetPress/100,Seed);
								  pSysMemoryParaVar->actque = pSysMemoryParaVar->tarque*(0.95+0.0001*Seed);
		            	pSysMemoryParaVar->WorkPress  =  (pSysMemoryParaVar->actque*100)/TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
			           pSysMemoryParaVar->tigresult = 1;
								  pSysMemoryParaVar->tigresult = 1;
								   if(ERROR_HAND == 1)
		                {
										 pSysMemoryParaVar->WorkPress = ADCGetPress[5]*100;
			               pSysMemoryParaVar->actque = ADCGetPress[5] *TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
				             pSysMemoryParaVar->tigresult = 0;  //š�����
											
		                }
								
								
								
								  break;	
								
								
								
			
		   case 4:	 pSysMemoryParaVar->tarangle =  ModifyVarStructVar.Angle;                  //Ŀ��Ƕ�	
			           pSysMemoryParaVar->actangle = 0;                                          //�������ɼ���ֵʵ�ʽǶ�
								 pSysMemoryParaVar->tarque = ModifyVarStructVar.MaxtorVal_TorMode;
	             //  pSysMemoryParaVar->actque = RandomFun( pSysMemoryParaVar->tarque,Seed); 
                 	pSysMemoryParaVar->actque = pSysMemoryParaVar->tarque*(0.95+0.0001*Seed);
		            	pSysMemoryParaVar->WorkPress  =  (pSysMemoryParaVar->actque*100)/TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
			           pSysMemoryParaVar->tigresult = 1;					
               //  pSysMemoryParaVar->WorkPress = RandomFun(SetPress/100,Seed);
                 pSysMemoryParaVar->tigresult = 1;
                    if(ERROR_HAND == 1)
		                {
										 pSysMemoryParaVar->WorkPress = ADCGetPress[5]*100;
			               pSysMemoryParaVar->actque = ADCGetPress[5] *TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
				             pSysMemoryParaVar->tigresult = 0;  //š�����
											
		                }


										break;
			
       case 5:    

           			 pSysMemoryParaVar->tarque = 	ModifyVarStructVar.presettor_sensor;
								// pSysMemoryParaVar->actque = RandomFun( pSysMemoryParaVar->tarque,Seed);
                // pSysMemoryParaVar->WorkPress = RandomFun(SetPress/100,Seed);
			           pSysMemoryParaVar->actque = pSysMemoryParaVar->tarque*(0.95+0.0001*Seed);
		            	pSysMemoryParaVar->WorkPress  =  (pSysMemoryParaVar->actque*100)/TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
			           pSysMemoryParaVar->tigresult = 1;
										
			             if(ERROR_HAND == 1)
		                {
										 pSysMemoryParaVar->WorkPress = ADCGetPress[5]*100;
			               pSysMemoryParaVar->actque = ADCGetPress[5] *TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor/10;
				             pSysMemoryParaVar->tigresult = 0;  //š�����
											
		                }
			 
										break; 			
		
		}
    
	pSysMemoryParaVar->ordinal = 1; //���
	if(ModifyVarStructVar.fabricName==0) ModifyVarStructVar.fabricName = 1;  //�����ͺ�
	strncpy((char*)pSysMemoryParaVar->ProductType,(char*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType,strlen((char*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType));	
  strncpy((char*)pSysMemoryParaVar->TolFacNum ,(char*)upComputerStructVar.appearanceNumberArr,strlen((char*)upComputerStructVar.appearanceNumberArr));//���߳������	
		
	 // printf(" pSysMemoryParaVar->ProductType =%s\r\n",  pSysMemoryParaVar->ProductType);	
	//	printf(" pSysMemoryParaVar->TolFacNum =%s\r\n",  pSysMemoryParaVar->TolFacNum);
		
		
	pSysMemoryParaVar->hour = calendar.hour;
	//printf(" pSysMemoryParaVar->hour =%d\r\n",  pSysMemoryParaVar->hour);
	pSysMemoryParaVar->day = calendar.w_date;
	//printf(" pSysMemoryParaVar->day =%d\r\n",  pSysMemoryParaVar->day);	
	pSysMemoryParaVar->month = calendar.w_month;
	//printf(" pSysMemoryParaVar->month =%d\r\n",  pSysMemoryParaVar->month);	
	pSysMemoryParaVar->year = calendar.w_year;
//	printf(" pSysMemoryParaVar->year =%d\r\n",  pSysMemoryParaVar->year);	
	pSysMemoryParaVar->min = calendar.min;
	//printf(" pSysMemoryParaVar->min =%d\r\n",  pSysMemoryParaVar->min);	
	pSysMemoryParaVar->sec = calendar.sec;
	//printf(" pSysMemoryParaVar->sec =%d\r\n",  pSysMemoryParaVar->sec);
	
	
	 strncpy((char*)pSysMemoryParaVar->devname, (char*)upComputerStructVar.UserEquipNameArr,strlen((char*)upComputerStructVar.UserEquipNameArr));
	// printf("pSysMemoryParaVar->devname =%s\r\n", pSysMemoryParaVar->devname);
	 strncpy((char*)pSysMemoryParaVar->devnum, (char*)upComputerStructVar.UserEquipNumberArr,strlen((char*)upComputerStructVar.UserEquipNumberArr));
	 // printf("pSysMemoryParaVar->devnum =%s\r\n",pSysMemoryParaVar->devnum);
	 strncpy((char*)pSysMemoryParaVar->operate, (char*)upComputerStructVar.UserNameArr,strlen((char*)upComputerStructVar.UserNameArr));
	// printf("pSysMemoryParaVar->operate =%s\r\n",pSysMemoryParaVar->operate);
	
	   pSysMemoryParaVar->TorqueUint =  ModifyVarStructVar.TorqueUint;
	//	 printf(" pSysMemoryParaVar->TorqueUint =%d\r\n", pSysMemoryParaVar->TorqueUint);
		 pSysMemoryParaVar->PressUint = ModifyVarStructVar.pressUint;
	//printf(" pSysMemoryParaVar->PressUin=%d\r\n", pSysMemoryParaVar->PressUint);
    pSysMemoryParaVar->workpattern = 0;  //������ʽ
//printf(" pSysMemoryParaVar->workpattern =%d\r\n", pSysMemoryParaVar->workpattern);




	
		
		
		
//printf(" pSysMemoryParaVar->tigresult =%d\r\n", pSysMemoryParaVar->tigresult);
	}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

