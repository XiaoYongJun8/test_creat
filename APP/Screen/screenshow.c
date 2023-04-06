#include "screenshow.h"
#include "screendriver.h"
#include "dac8771.h"
uint8_t  func_index = 0 ;


void (*current_operation_index)();





KEY_Table table[75] = {

{0,17,0,8,1,(*MemuOne)}, //Ö÷½çÃæ1

{1,17, 9,8,2,(*MemuOneOptionOne)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî1
{2,17,10,1,3,(*MemuOneOptionTwo)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî2
{3,17,11,2,4,(*MemuOneOptionThree)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3
{4,17,12,3,5,(*MemuOneOptionFour)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4
{5,17,13,4,6,(*MemuOneOptionFive)},      //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî5
{6,17,14,5,7,(*MemuOneOptionSix)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî6
{7,17,15,6,8,(*MemuOneOptionSeven)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî7
{8,17,16,7,1,(*MemuOneOptionEight)},     // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî8

{9,  9,1,9, 9, (*EnterMemuOneOptionOne)},     //½øÈëÖ÷½çÃæ1Ñ¡Ïî1
{10,10,2,10,10,(*EnterMemuOneOptionTwo)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî2
{11,11,3,11,11,(*EnterMemuOneOptionThree)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî3
{12,12,4,12,12,(*EnterMemuOneOptionFour)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî4
{13,13,5,13,13,(*EnterMemuOneOptionFive)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî5
{14,14,6,14,14,(*EnterMemuOneOptionSix)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî6
{15,15,7,15,15,(*EnterMemuOneOptionSeven)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî7
{16,16,8,16,16,(*EnterMemuOneOptionEight)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî8




{17,28,17,22,18,(*MemuTwo)}, //Ö÷½çÃæ2                                 //Å¤¾ØÄ£Ê½


{18,28,23,22,19,(*MemuTwoOptionOne)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî1        
{19,28,24,18,20,(*MemuTwoOptionTwo)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî2
{20,28,25,19,21,(*MemuTwoOptionThree)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3         //ÐÞ¸ÄÅ¤¾ØÖµ
{21,28,26,20,22,(*MemuTwoOptionFour)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4
{22,28,27,21,18,(*MemuTwoOptionFive)},      //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî5


{23,23,18,23,23, (*EnterMemuTwoOptionOne)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî1       
{24,24,19,24,24,(*EnterMemuTwoOptionTwo)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî2
{25,25,20,25,25,(*EnterMemuTwoOptionThree)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî3       
{26,26,21,26,26,(*EnterMemuTwoOptionFour)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî4
{27,27,22,27,27,(*EnterMemuTwoOptionFive)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî5







{28,37,28,32,29,(*MemuThree)}, //Ö÷½çÃæ3                              //ÂÝË¨Ä£Ê½    


{29,37,33,32,30,(*MemuThreeOptionOne)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî1     
{30,37,34,29,31,(*MemuThreeOptionTwo)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî2      //ÂÝË¨Ö±¾¶
{31,37,35,30,32,(*MemuThreeOptionThree)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3      //ÂÝË¨µÈ¼¶  
{32,37,36,31,29,(*MemuThreeOptionFour)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4


{33,33,29,33,33, (*EnterMemuThreeOptionOne)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî1
{34,34,30,34,34,(*EnterMemuThreeOptionTwo)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî2   
{35,35,31,35,35,(*EnterMemuThreeOptionThree)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî3   
{36,36,32,36,36,(*EnterMemuThreeOptionFour)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî4









{37,46,37,41,38,(*MemuFive)}, //Ö÷½çÃæ4                                      //µ²Î»Ä£Ê½


{38,46,42,41,39,(*MemuFiveOptionOne)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî1
{39,46,43,38,40,(*MemuFiveOptionTwo)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî2             //ÐÞ¸Äµ²Î»
{40,46,44,39,41,(*MemuFiveOptionThree)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3
{41,46,45,40,38,(*MemuFiveOptionFour)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4


{42,42,38,42,42, (*EnterMemuFiveOptionOne)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî1        
{43,43,39,43,43,(*EnterMemuFiveOptionTwo)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî2
{44,44,40,44,44,(*EnterMemuFiveOptionThree)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî3
{45,45,41,45,45,(*EnterMemuFiveOptionFour)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî4



{46,57,46,51,47,(*MemuFour)}, //Ö÷½çÃæ4                                      //½Ç¶ÈÄ£Ê½


{47,57,52,51,48,(*MemuFourOptionOne)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî1
{48,57,53,47,49,(*MemuFourOptionTwo)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî2
{49,57,54,48,50,(*MemuFourOptionThree)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3
{50,57,55,49,51,(*MemuFourOptionFour)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4
{51,57,56,50,47,(*MemuFourOptionFive)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4

{52,52,47,52,52, (*EnterMemuFourOptionOne)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî1        
{53,53,48,53,53,(*EnterMemuFourOptionTwo)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî2
{54,54,49,54,54,(*EnterMemuFourOptionThree)},  //½øÈëÖ÷½çÃæ1Ñ¡Ïî3
{55,55,50,55,55,(*EnterMemuFourOptionFour)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî4
{56,56,51,56,56,(*EnterMemuFourOptionFive)},     // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4








{57,0,57,63,58,(*MemuSix)}, //Ö÷½çÃæ6                                      //´«¸ÐÆ÷Ä£Ê½


{58,0,64,63,59,(*MemuSixOptionOne)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî1
{59,0,65,58,60,(*MemuSixOptionTwo)},       //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî2           //Ô¤ÉèÅ¤¾Ø
{60,0,66,59,61,(*MemuSixOptionThree)},     //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3      
{61,0,67,60,62,(*MemuSixOptionFour)},      // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4
{62,0,68,61,63,(*MemuSixOptionFive)},      //Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî3
{63,0,69,62,58,(*MemuSixOptionSix)},       // Ñ¡ÔñÖ÷½çÃæ1Ñ¡Ïî4

{64,64,58,64,64, (*EnterMemuSixOptionOne)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî1
{65,65,59,65,65,(*EnterMemuSixOptionTwo)},     //½øÈëÖ÷½çÃæ1Ñ¡Ïî2     //7
{66,66,60,66,66,(*EnterMemuSixOptionThree)},   //½øÈëÖ÷½çÃæ1Ñ¡Ïî3
{67,67,61,67,67,(*EnterMemuSixOptionFour)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî4
{68,68,62,68,68,(*EnterMemuSixOptionFive)},    //½øÈëÖ÷½çÃæ1Ñ¡Ïî3
{69,69,63,69,69,(*EnterMemuSixOptionSix)},     //½øÈëÖ÷½çÃæ1Ñ¡Ïî4


};









  uint16_t FastAddTimes = 0;
  uint16_t FastDecTimes = 0;
  
  static  uint8_t  uptimes = UPTIMES ;  
  static  uint8_t entertimes = ENTERTIMES; 
	static  uint8_t  dowmtimes = DOWNTIMES ;            
  static	 uint8_t startflag = 100;  
void TaskKeyControl(void* pvData)
{
	
   static uint8_t picinit = 1;
   static uint8_t RESUME = 1;
	 static  uint8_t memutimes = MEMUTIME;
	 static uint8_t i = 0; 
	 static uint8_t j = 0;
   static uint16_t ucCount1S = 40;	
   pvData = pvData;

	
   while(1){
		 
		  OSTimeDly(5);		//ÉèÖÃÒ»¸ö½ÚÅÄÎª5ms,µÈ´ý2¸ö½ÚÅÄÎª10ms,È·¶¨ÁË10MS¼ÆÊý
		 
		  if(j==0){
				TIM_Cmd(TIM4,DISABLE); //Ê¹ÄÜ¶¨Ê±Æ÷	
				OSTaskSuspend(6);
				if(!(--ucCount1S))
				 {
					 j = 1;
					 ucCount1S = 40;
				   OSTaskResume(6);
				 TIM_Cmd(TIM4,ENABLE); //Ê¹ÄÜ¶¨Ê±Æ÷	
				 }	
				 
			}
		 
	 

		if(KeyMemu){          
				  memutimes--; 
				  if(memutimes==0 )
				   {
						  func_index=table[func_index].memu;    //È·ÈÏÑ¡ÔñÕâ»ú²Ëµ¥µÄÑ¡ÐÍ
	            memutimes= MEMUTIME; 
           					 
				   } 
			}
			
		else{
		  memutimes = MEMUTIME;
		 }
			  
				 
				
	   if(KeyEnter)       //½øÈë¼üKEY4
	      {
					
			   entertimes--;
					
	       if(entertimes==0){
					    entertimes = ENTERTIMES;
					 		func_index=table[func_index].enter;    //È·ÈÏÑ¡ÔñÕâ»ú²Ëµ¥µÄÑ¡ÐÍ	 
				 }
			
					
        }
				else{
					 entertimes = ENTERTIMES;
				}
				
				
				
		
	
       if(KeyUp)                         //ÉÏ·­½¨KEY1
	      {
					
				 FastAddTimes++;
				 uptimes--;
					
				switch(KeyModeVar.Mode)
				   {
					case 0:  if(uptimes ==0){
			                uptimes = UPTIMES;
						         func_index=table[func_index].up;
					         }break;
					                    						   
				  case 1:   
						        if(uptimes==0){
											  uptimes = UPTIMES;
											  ModiVarAdd(KeyModeVar.ModifyVarFlag);
										} break;             	
				   }
         }else{
					 
					  uptimes = UPTIMES;
				    FastAddTimes = 0;
					 
				 }
				
		
       if(KeyDown)       //ÏÂ·­½¨KEY2
	      {
				 FastDecTimes++;
			  
				 dowmtimes--;
			
					switch(KeyModeVar.Mode)
					{ 
						case 0:  if(dowmtimes==0){
							       func_index=table[func_index].down;	
                     dowmtimes = DOWNTIMES;
						         } break; 
						           
					  case 1: if(dowmtimes==0){
							        ModiVarDec(KeyModeVar.ModifyVarFlag);
							        dowmtimes = DOWNTIMES;
					            } break;
	      
          }
				}
				
				else{
				    dowmtimes = DOWNTIMES;
				    FastDecTimes = 0;	 
				 }
				

		if(func_index != startflag){
	    // OSTaskSuspend(6);
			 RESUME =1;
	     startflag = func_index ;
	     current_operation_index=table[func_index].current_operation;//Ö¸ÏòÕâ¸öº¯Êý
			if((func_index==0||func_index==17||func_index==28||func_index==37||func_index==46||func_index==57)&&(picinit==1)){
				Memory = ScreenMem;
				
				for(i=0;i<8;i++){
					
				current_operation_index();//Ö´ÐÐµ±Ç°²Ù×÷º¯Êý
				}
			}else
	        	current_operation_index();
    }
	
//			if(RESUME==1){
//		   OSTaskResume(6);
//				RESUME = 0;
//				
//			}
			
		
		
  }
		 
}



















uint8_t readBoltFlag = 100;
ModifyVarStruct ModifyVarStructVar = {0};


float  SetPress  = 0;


ResetPressStruct ResetPress;



uint32_t DacOutData = 0;

double   AdcGetPress = 0.0;
uint32_t  TorqueUint_C = 0;
uint32_t  Language_C = 0;
uint32_t  ChartType_C = 0;
uint32_t  maxdata = 0;  //Å¤¾ØÄ£Ê½×î´óÅ¤¾ØÖµ
uint32_t  datafts = 0;  //µ¥Î»ft.lbsµÄÅ¤¾ØÖµ

void ModiVarAdd(uint8_t Flag)
{
	
uint8_t arr[5] = {0};
	
switch(Flag)
	
  {
	 
	   /************************************²Ëµ¥Ò» **************************************************************/
	 
  	case  LanguageValVarFlag:      Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
                                	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0ÊÇÓ¢ÎÄ
	                
  	case 	ChartStandardValVarFlag :	 ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                                 else ModifyVarStructVar.ChartType = 1;
		
                                     		 if(ModifyVarStructVar.fabricName != readBoltFlag){
																	       ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
			                                   readBoltFlag =  ModifyVarStructVar.fabricName; 
																       }
                                   	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0ÊÇÓ¢ÖÆ
							
	  case  YearValVarFlag :  if(FastDecTimes>=ADDTIMES)calendar.w_year+=111 ;else calendar.w_year++;setYearValVarFlag(&calendar.w_year);break; 																							    
																									
	  case	MonthValVarFlag : calendar.w_month++;setMonthValVarFlag(&calendar.w_month);break;																							           
	
    case  DayValVarFlag :   calendar.w_date++; setDayValVarFlag(&calendar.w_date); break;
  	case  HourValVarFlag :  calendar.hour++; setHourValVarFlag(&calendar.hour); break;
	  case  MinuteValVarFlag :calendar.min++; setMinuteValVarFlag(&calendar.min); break;
    case  SecondValVarFlag :calendar.sec++;  setSecondValVarFlag(&calendar.sec);break;
	

	/************************************²Ëµ¥¶þÅ¤¾ØÄ£Ê½ **************************************************************/

                                 
   case 	 TorqueTypeValVarFlag: ModifyVarStructVar.fabricName+=1;
                  
	                              if(ModifyVarStructVar.fabricName > productKind)
																 { 
																	 ModifyVarStructVar.fabricName = 1;
																 }
																 
														 SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		                         ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;	
													  if(ModifyVarStructVar.TorqueUint == 0)
		                          {
		   	           
			                          SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                          }
		                        else{
		                     
			                      SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }	

	                               if(ModifyVarStructVar.fabricName != readBoltFlag){
	                               ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																 readBoltFlag =  ModifyVarStructVar.fabricName; 	  
																 }break;
                                  
                                

   case 	 MaxTorqueUintVarFlag:  TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                }else  ModifyVarStructVar.TorqueUint = 1;

													       if(ModifyVarStructVar.TorqueUint == 0)
		                               {
		   	                            SetTextValue(1,2,(uint8_t*)"N.m");
			                              SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
																		SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                              SetTextValue(1,4,(uint8_t*)"N.m");  
		                               }
																	 
		                         else{
		                            SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
															  SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                        SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                          }break;  
	                                                        
	
	     
   case   TargetTorqueValVarFlag:  maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
																	
                               		 if(ModifyVarStructVar.TorqueUint == 0){
		                               ModifyVarStructVar.TartorVal_TorMode += 1;
																   if(FastAddTimes>=ADDTIMES)ModifyVarStructVar.TartorVal_TorMode += (ROUND_TO_UINT32(maxdata*ADDRATE));
	                                 }	
																	 
																	 
																	 if(ModifyVarStructVar.TorqueUint == 1){
		                              
																	 datafts = ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549);	
                                   datafts += 1;																	 
																   if(FastAddTimes>=ADDTIMES)datafts +=(ROUND_TO_UINT32(maxdata*ADDRATE/1.3549));
																	 ModifyVarStructVar.TartorVal_TorMode = (ROUND_TO_UINT32(datafts*1.3549));
																		 
	                                 }	
	                               
																	 
																	 
                                  ResetPress.SetPress_Torque = setTargetTorqueValVarFlag(ModifyVarStructVar.TorqueUint,&ModifyVarStructVar.TartorVal_TorMode) ; 
															    if(ModifyVarStructVar.TorqueUint == 0)
		                              {
																	//	SetTextValue(1,2,(uint8_t*)"N.m");
			                              SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			                              SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                            //  SetTextValue(1,4,(uint8_t*)"N.m");  
			                            }				
			                           else{
				                         // SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                            SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
				                         // SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                          SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
			                           }
																                    
                                 ResetPress.DacOutData_T =  getOutData(ResetPress.SetPress_Torque);break;
																	

   case   TargetTorqueUnitVarFlag: TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;

													        if(ModifyVarStructVar.TorqueUint == 0)
		                              {
																		SetTextValue(1,2,(uint8_t*)"N.m");
			                              SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			                              SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                              SetTextValue(1,4,(uint8_t*)"N.m");  
			                            }				
			                           else{
				                          SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                            SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
				                          SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                          SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
			                          } break; 
              


   case 	TorquePressUnitVarFlag	:ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0;
																  
																  switch(ModifyVarStructVar.pressUint)
			                              {
				                              case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				                              case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			                                case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			                              } break;


	/************************************²Ëµ¥ÈýÂÝË¨Ä£Ê½ **************************************************************/	
	
	case   BoltTypeVareFlag   :    ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                              
																 if(ModifyVarStructVar.fabricName != readBoltFlag){
																  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
															    readBoltFlag = ModifyVarStructVar.fabricName ;
																	 
															   }
																SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);  
  															if(ModifyVarStructVar.ChartType == 0){
	
		                                  SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
	                                    SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
		                               }
		                             if(ModifyVarStructVar.ChartType == 1){
	
		                               SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
	                                 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
		                             }	break;
                                
															
														
  case 	  BoltDiameterValVarFlag : if(ModifyVarStructVar.ChartType == 0){
																		    ModifyVarStructVar.diameter++;
																	      ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar);
                          
                              
															    	 }
																	if(ModifyVarStructVar.ChartType == 1){
												
																		ModifyVarStructVar.diameter_M++;
																	  ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);  
																  	}
																	
																 	if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
																 if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
																
																	
	                                ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
																
																  ResetPress.DacOutData_B =  getOutData(ResetPress.SetPress_Bolt);break;
	                                
																	
	case	   BoltGardeValVarFlag: 
                              		if(ModifyVarStructVar.ChartType == 0){
																		    ModifyVarStructVar.garde++;
																	      ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar); 
                     
																	     																	
																	 }
																	if(ModifyVarStructVar.ChartType == 1){
												
																		ModifyVarStructVar.garde_M++;
																		
																	  ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);       
																							
																	}
																		if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
																if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
																		
																
                                  ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
																	ResetPress.DacOutData_B  =  getOutData(ResetPress.SetPress_Bolt);
																  break;


  case     BoltTargetTorqueUintVarFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                       }else  ModifyVarStructVar.TorqueUint = 1;
                              	if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }break;     




	/************************************²Ëµ¥ËÄ½Ç¶ÈÄ£Ê½ **************************************************************/		


 	case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName++;
																 if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                              		SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
	                                ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;
		 
																if(ModifyVarStructVar.TorqueUint==0)
																	{
																		SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
																		SetTextValue(3,3,(uint8_t*)"N.m");
																	}
																 else
																	{
																		SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
																		SetTextValue(3,3,(uint8_t*)"ft.lbs");
																	}		
                                
															   ResetPress.SetPress_Angle = 60000;ResetPress.DacOutData_A =  getOutData(ResetPress.SetPress_Angle); 
																	
																 if(ModifyVarStructVar.fabricName != readBoltFlag){
																 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																 readBoltFlag = ModifyVarStructVar.fabricName ;
															   }break;
                         

 case  AnglePresetTorUintFlag  : TorqueUint_C++;if(TorqueUint_C%2==0)ModifyVarStructVar.TorqueUint = 0; 
																 else ModifyVarStructVar.TorqueUint = 1;
																											 
			
	                           if(ModifyVarStructVar.TorqueUint==0)
	                             {
		                              SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			                            SetTextValue(3,3,(uint8_t*)"N.m");
		                           }
	                           else
	                            {
		                            SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
			                          SetTextValue(3,3,(uint8_t*)"ft.lbs");
		                          }break; 
	                            
		 
	

																 

 case 	TarGetAngleValVarFlag :  data++; SetTextInt32(3,4,data,0,0);break; //if(data > ModifyVarStructVar.Angle)DAC8771_WRITE_CMD(0x05,0);  break;
 

 case  AngleUintVarFlag :        ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0 ;
																   switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;
	 
	
 /************************************²Ëµ¥Îåµ²Î»Ä£Ê½ **************************************************************/			 
	 
	case  GearTypeValVarFlag     :   ModifyVarStructVar.fabricName++;
																   if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                   SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
															     if(ModifyVarStructVar.fabricName != readBoltFlag){
																   ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																   readBoltFlag = ModifyVarStructVar.fabricName;
															    }break;
                                
	case  TargetGearValVarFlag   :  ModifyVarStructVar.gear++;if(ModifyVarStructVar.gear > gearKind)ModifyVarStructVar.gear = 1; 
																  SetTextInt32(4,2,  GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
	                                ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
																	ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ä¿±êÅ¤¾ØÖµ
																 if(ModifyVarStructVar.TorqueUint == 0)
		                              {
				                            SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				                            SetTextValue(4,3,(uint8_t*)"N.m");
			                            }
		                    	 else
			                      {
				                    SetTextValue(4,3,(uint8_t*)"ft.lbs");
			                      SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			                      }
                            ResetPress.SetPress_Gear = ModifyVarStructVar.gearpress*10;ResetPress.DacOutData_G = getOutData(ResetPress.SetPress_Gear );
														break;
															
																	
  case 	GearTargetTorUintValFlag :  TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }break; 
	                                  
		 
	case  GearUintVarFlag :        ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0 ; 
															    switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;
	
  
/***************************************** ´«¸ÐÆ÷Ä£Ê½  ***********************************************************/

  case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 
		
		                          SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
	  	                        ModifyVarStructVar.tartor_sensor = TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor;
		
																	if(ModifyVarStructVar.TorqueUint==0)
																	 {
																		 SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
																		 SetTextValue(5,5,(uint8_t*)"N.m");
																	 }
																	 
																	if(ModifyVarStructVar.TorqueUint==1)
																	 {
																		 SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
																		 SetTextValue(5,5,(uint8_t*)"ft.lbs");
																	 }
																																	if(ModifyVarStructVar.fabricName != readBoltFlag){
																  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																  readBoltFlag = ModifyVarStructVar.fabricName ;
															    } break;
                                  

 	case    SensorPresetTorValVarFlag :     maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
	
                                       		if(ModifyVarStructVar.TorqueUint==0){
		                                      ModifyVarStructVar.presettor_sensor+=1;
		                                      if(FastAddTimes>=ADDTIMES)ModifyVarStructVar.presettor_sensor += (ROUND_TO_UINT32(maxdata*ADDRATE));  
	                                        }
																				
																					
																					if(ModifyVarStructVar.TorqueUint==1){
																						 datafts = ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549);	
                                             datafts += 1;																	 
																             if(FastAddTimes>=ADDTIMES) datafts +=(ROUND_TO_UINT32(maxdata*ADDRATE/1.3549));
																	           ModifyVarStructVar.presettor_sensor = (ROUND_TO_UINT32(datafts*1.3549));
		                                     
	                                        }
	                                     
                                       ResetPress.SetPress_Sensor = setSensorPresetTorValVarFlag(ModifyVarStructVar.TorqueUint, &ModifyVarStructVar.presettor_sensor);
																			
																			    if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																					 SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                      // SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                      // SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                     //  SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                   //  SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	}
																		 
                                      ResetPress.DacOutData_S = getOutData(ResetPress.SetPress_Sensor);break;
                               	
	
	
	
	                                     
	
  case    SensorPresetTorValVarUintFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                        }else  ModifyVarStructVar.TorqueUint = 1;   
	                                      if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	} break;



  case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //ÉÏÎ»»úµ¼ÈëµÄÄ¿±êÅ¤¾Ø
	                                       
  
                                       }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//´«¸ÐÆ÷²É¼¯µÄÅ¤¾Ø´óÓÚÄ¿±êÅ¤¾ØÍ£»ú
	
	case 	  SensorTargetToreValVarUintFlag:	TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                     }else  ModifyVarStructVar.TorqueUint = 1; 
		                                    if(ModifyVarStructVar.TorqueUint==0)
	                                        {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	 }  
 
 case      SensorPressUintFlag  :  ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0 ; 
																	    switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;
																			
 }
 
 

}




void ModiVarDec(uint8_t Flag)
{
	uint32_t data = 0;

	
	uint8_t arr[5] = {0};
	uint8_t arr1[5] = {0};
  switch(Flag)

{
/************************************²Ëµ¥Ò» **************************************************************/

case  LanguageValVarFlag:     Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
	                           setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0ÊÇÓ¢ÎÄ
						 
case 	ChartStandardValVarFlag :	ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                             else ModifyVarStructVar.ChartType = 1;
	                               setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr1);
	                               if(ModifyVarStructVar.fabricName != readBoltFlag){
																	ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																	 readBoltFlag =  ModifyVarStructVar.fabricName; 
																 }
																 
																break; 
					
case  YearValVarFlag : if(FastDecTimes>=DECTIMES)calendar.w_year-=111;else calendar.w_year-- ; setYearValVarFlag(&calendar.w_year);break; 																							    
																							
case	MonthValVarFlag : calendar.w_month--;setMonthValVarFlag(&calendar.w_month);break;																							           

case  DayValVarFlag :   calendar.w_date--; setDayValVarFlag(&calendar.w_date); break;
case  HourValVarFlag :  calendar.hour--; setHourValVarFlag(&calendar.hour); break;
case  MinuteValVarFlag :calendar.min--; setMinuteValVarFlag(&calendar.min); break;
case  SecondValVarFlag :calendar.sec--;  setSecondValVarFlag(&calendar.sec);break;


/************************************²Ëµ¥¶þÅ¤¾ØÄ£Ê½ **************************************************************/


case 	 TorqueTypeValVarFlag: 	 
														 ModifyVarStructVar.fabricName--;
														 if((signed char)ModifyVarStructVar.fabricName < 1 ){
															 
															 ModifyVarStructVar.fabricName = productKind;
														 }
														 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		                        ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;	
													 if(ModifyVarStructVar.TorqueUint == 0)
		                          {
		   	           
			                        SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                          }
		                       else{
		                     
			                       SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                        }	 
														 
														 
														 if(ModifyVarStructVar.fabricName != readBoltFlag){
														 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
														 readBoltFlag  =   ModifyVarStructVar.fabricName; 

														 }break;
															 
														


case 	 MaxTorqueUintVarFlag:  TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                }else  ModifyVarStructVar.TorqueUint = 1;;
														        if(ModifyVarStructVar.TorqueUint == 0)
		                         {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                          SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                     SetTextValue(1,2,(uint8_t*)"N.m");
			                       SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															   SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                            SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }	break;     

	 
case   TargetTorqueValVarFlag:    maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
																	
                               		 if(ModifyVarStructVar.TorqueUint == 0){
		                               ModifyVarStructVar.TartorVal_TorMode -= 1;
																   if(FastDecTimes>=DECTIMES)ModifyVarStructVar.TartorVal_TorMode -= (ROUND_TO_UINT32(maxdata*DECRATE));
	                                 }	
																	 
																	 
																	 if(ModifyVarStructVar.TorqueUint == 1){
		                              
																	 datafts = ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549);	
                                   datafts -= 1;																	 
																   if(FastDecTimes>=DECTIMES)datafts -=(ROUND_TO_UINT32(maxdata*DECRATE/1.3549));
																	 ModifyVarStructVar.TartorVal_TorMode = (ROUND_TO_UINT32(datafts*1.3549));
																		 
	                                 }

															 ResetPress.SetPress_Torque = setTargetTorqueValVarFlag(ModifyVarStructVar.TorqueUint,&ModifyVarStructVar.TartorVal_TorMode) ; 
			        if(ModifyVarStructVar.TorqueUint == 0)
		                         {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                         // SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                    // SetTextValue(1,2,(uint8_t*)"N.m");
			                       SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															  // SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                          //  SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }
													
															ResetPress.DacOutData_T = getOutData(ResetPress.SetPress_Torque);break;
															

case   TargetTorqueUnitVarFlag: TorqueUint_C++;if(TorqueUint_C%2==0){
		                               ModifyVarStructVar.TorqueUint = 0;        
	                                }else  ModifyVarStructVar.TorqueUint = 1;
				                     if(ModifyVarStructVar.TorqueUint == 0)
		                         {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                        SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                     SetTextValue(1,2,(uint8_t*)"N.m");
			                       SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															   SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                            SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }break; 


case 	TorquePressUnitVarFlag	 :ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint<0)ModifyVarStructVar.pressUint = 2 ;
															
															  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 } break;


/************************************²Ëµ¥ÈýÂÝË¨Ä£Ê½ **************************************************************/	

case   BoltTypeVareFlag   :   ModifyVarStructVar.fabricName--;
														 if(ModifyVarStructVar.fabricName < 1 ) ModifyVarStructVar.fabricName =  productKind;
														 
														 if(ModifyVarStructVar.fabricName != readBoltFlag){
														 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
															readBoltFlag = ModifyVarStructVar.fabricName;
														 }		
														 SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);  
  													if(ModifyVarStructVar.ChartType == 0){
	
		                                  SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
	                                    SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
		                             }
		                             if(ModifyVarStructVar.ChartType == 1){
	
		                               SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
	                                 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
		                             }	break;
													 
														 
case 	  BoltDiameterValVarFlag : 
															if(ModifyVarStructVar.ChartType == 0){
																		ModifyVarStructVar.diameter--;
																		ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar);  
																
																 }
															if(ModifyVarStructVar.ChartType == 1){
										
																ModifyVarStructVar.diameter_M--;
																ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);       
																}
																	if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
																															 	if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
															ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
															ResetPress.DacOutData_B =  getOutData(ResetPress.SetPress_Bolt);break;
															
														 
															
case	   BoltGardeValVarFlag:   
															if(ModifyVarStructVar.ChartType == 0){
																		ModifyVarStructVar.garde--;
																		ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar);  
																		
																													
																 }
															if(ModifyVarStructVar.ChartType == 1){
										
																ModifyVarStructVar.garde_M--;
																ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);  
																																
															}
																	if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
																	if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
														 
															ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
															ResetPress.DacOutData_B  =  getOutData(ResetPress.SetPress_Bolt);break;


case     BoltTargetTorqueUintVarFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;
                                    		if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }break; 
    




/************************************²Ëµ¥ËÄ½Ç¶ÈÄ£Ê½ **************************************************************/		


case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName--;if(ModifyVarStructVar.fabricName <1) ModifyVarStructVar.fabricName = productKind;
														   											  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		
	                             ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;
		 
	
	
																		if(ModifyVarStructVar.TorqueUint==0)
																			{
																				SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
																				SetTextValue(3,3,(uint8_t*)"N.m");
																			}
																		 else
																			{
																				SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
																				SetTextValue(3,3,(uint8_t*)"ft.lbs");
																			}		
														  ResetPress.SetPress_Angle = 60000;ResetPress.DacOutData_A =  getOutData(ResetPress.SetPress_Angle); 
														 if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															}
															break;

case  AnglePresetTorUintFlag  : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1; 										
		
	                             
		 
	
																		
																		if(ModifyVarStructVar.TorqueUint==0)
																			{
																				SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
																				SetTextValue(3,3,(uint8_t*)"N.m");
																			}
																		 else
																			{
																				SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
																				SetTextValue(3,3,(uint8_t*)"ft.lbs");
																			}		 break; 
														 

case 	TarGetAngleValVarFlag :  data++; SetTextInt32(3,4,data,0,0);break; //if(data > ModifyVarStructVar.Angle)DAC8771_WRITE_CMD(0x05,0);  break;


case  AngleUintVarFlag :     ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint < 0)ModifyVarStructVar.pressUint = 2;
														 
													  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;


/************************************²Ëµ¥Îåµ²Î»Ä£Ê½ **************************************************************/			 

case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
															if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															}  break;

case  TargetGearValVarFlag   :  ModifyVarStructVar.gear--;if(ModifyVarStructVar.gear < 1)ModifyVarStructVar.gear = gearKind; 
												
															SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress; //Ä¿±êÑ¹Á¦Öµ
															ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ä¿±êÅ¤¾ØÖµ
																	 if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }
															ResetPress.SetPress_Gear = ModifyVarStructVar.gearpress*10;ResetPress.DacOutData_G =  getOutData(ResetPress.SetPress_Gear); break;
															
case 	GearTargetTorUintValFlag :  TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;
     if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }break; 
 
case  GearUintVarFlag :         ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint<0)ModifyVarStructVar.pressUint = 2 ;
															  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;


/***************************************** ´«¸ÐÆ÷Ä£Ê½  ***********************************************************/

case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
	  	ModifyVarStructVar.tartor_sensor = TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor;
		 
	
	 
	if(ModifyVarStructVar.TorqueUint==0)
	 {
	   SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		 SetTextValue(5,5,(uint8_t*)"N.m");
	 }
	 
	if(ModifyVarStructVar.TorqueUint==1)
	 {
	   SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		 SetTextValue(5,5,(uint8_t*)"ft.lbs");
	 }
															if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName;
															}break; 
																		
case    SensorPresetTorValVarFlag :   maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
	
                                       		if(ModifyVarStructVar.TorqueUint==0){
		                                      ModifyVarStructVar.presettor_sensor-=1;
		                                      if(FastDecTimes>=DECTIMES)ModifyVarStructVar.presettor_sensor -= (ROUND_TO_UINT32(maxdata*DECRATE));  
	                                        }
																					
																					if(ModifyVarStructVar.TorqueUint==1){
																						 datafts = ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549);	
                                             datafts -= 1;																	 
																             if(FastDecTimes>=DECTIMES) datafts -=(ROUND_TO_UINT32(maxdata*DECRATE/1.3549));
																	           ModifyVarStructVar.presettor_sensor = (ROUND_TO_UINT32(datafts*1.3549));
		                                     
	                                        }
																	ResetPress.SetPress_Sensor = setSensorPresetTorValVarFlag(ModifyVarStructVar.TorqueUint, &ModifyVarStructVar.presettor_sensor);
																	  	    if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                    //   SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                   //    SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                    //   SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                  //   SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	} 	
		
																	  ResetPress.DacOutData_S =  getOutData(ResetPress.SetPress_Sensor);break;

case    SensorPresetTorValVarUintFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;  
		                                if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	}break;



case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //ÉÏÎ»»úµ¼ÈëµÄÄ¿±êÅ¤¾Ø
																			 

																		 }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//´«¸ÐÆ÷²É¼¯µÄÅ¤¾Ø´óÓÚÄ¿±êÅ¤¾ØÍ£»ú

case 	  SensorTargetToreValVarUintFlag:	TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;	
	                                      if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	}break;   //ÏÔÊ¾×î´óÅ¤¾Øµ¥Î»  

case      SensorPressUintFlag  :     ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint < 0)ModifyVarStructVar.pressUint = 2 ; 
																	  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }  break;
																	
}

}




void ModiVarAddWide(uint8_t Flag)
{
uint32_t data = 0;


	uint8_t arr[5] = {0};
	
switch(Flag)
	
 {
	 
	  /************************************²Ëµ¥Ò» **************************************************************/
	 
  	case  LanguageValVarFlag:      Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
	                                 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0ÊÇÓ¢ÎÄ
	               
  	case 	ChartStandardValVarFlag :	 	ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                                   else ModifyVarStructVar.ChartType = 1; 
                                    	 if(ModifyVarStructVar.fabricName != readBoltFlag){
																	    ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																	    readBoltFlag =  ModifyVarStructVar.fabricName; 
																       }
                                   	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; 
							
	  case  YearValVarFlag :  calendar.w_year+=111;setYearValVarFlag(&calendar.w_year);break; 																							    
																									
	  case	MonthValVarFlag : calendar.w_month++;setMonthValVarFlag(&calendar.w_month);break;																							           
	
    case  DayValVarFlag :   calendar.w_date++; setDayValVarFlag(&calendar.w_date); break;
  	case  HourValVarFlag :  calendar.hour++; setHourValVarFlag(&calendar.hour); break;
	  case  MinuteValVarFlag :calendar.min++; setMinuteValVarFlag(&calendar.min); break;
    case  SecondValVarFlag :calendar.sec++;  setSecondValVarFlag(&calendar.sec);break;
	

	/************************************²Ëµ¥¶þÅ¤¾ØÄ£Ê½ **************************************************************/

                                 
   case 	 TorqueTypeValVarFlag: ModifyVarStructVar.fabricName+=1;
                  
	                              if(ModifyVarStructVar.fabricName > productKind)
																 { 
																	 ModifyVarStructVar.fabricName = 1;
																 }
																 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		                        ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;	
													 if(ModifyVarStructVar.TorqueUint == 0)
		                          {
		   	           
			                        SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                          }
		                       else{
		                     
			                      SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }	

	                               if(ModifyVarStructVar.fabricName != readBoltFlag){
	                               ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																 readBoltFlag =  ModifyVarStructVar.fabricName; 	  
																 };break;
                                  
                                

   case 	 MaxTorqueUintVarFlag:  TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                }else  ModifyVarStructVar.TorqueUint = 1; 
                       	  if(ModifyVarStructVar.TorqueUint == 0)
		                          {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                         SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                      SetTextValue(1,2,(uint8_t*)"N.m");
			                        SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															  SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                        SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                            SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }break;  
	                                                        
	
	     
   case   TargetTorqueValVarFlag:  maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
																	
                               		 if(ModifyVarStructVar.TorqueUint == 0){
		                               
																   ModifyVarStructVar.TartorVal_TorMode += (ROUND_TO_UINT32(maxdata*ADDRATE));
	                                 }	
																	 
																	 
																	 if(ModifyVarStructVar.TorqueUint == 1){
		                              
																	 datafts = ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549);	
                                  																 
																   datafts +=(ROUND_TO_UINT32(maxdata*ADDRATE/1.3549));
																	 ModifyVarStructVar.TartorVal_TorMode = (ROUND_TO_UINT32(datafts*1.3549));
																		 
	                                 }
															    ResetPress.SetPress_Torque = setTargetTorqueValVarFlag(ModifyVarStructVar.TorqueUint,&ModifyVarStructVar.TartorVal_TorMode) ; 
													if(ModifyVarStructVar.TorqueUint == 0)
		                         {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                       // SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                     // SetTextValue(1,2,(uint8_t*)"N.m");
			                       SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															 //  SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                          //  SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }
	                                                       
                                  ResetPress.DacOutData_T =  getOutData(ResetPress.SetPress_Torque);break;
																	

   case   TargetTorqueUnitVarFlag: TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                }else  ModifyVarStructVar.TorqueUint = 1;	
              	              if(ModifyVarStructVar.TorqueUint == 0)
		                           {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                        SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                     SetTextValue(1,2,(uint8_t*)"N.m");
			                       SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															   SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                            SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }break; 
              


   case 	TorquePressUnitVarFlag	:ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0;
																    switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;


	/************************************²Ëµ¥ÈýÂÝË¨Ä£Ê½ **************************************************************/	
	
	case   BoltTypeVareFlag   :    ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                               
															 
																 if(ModifyVarStructVar.fabricName != readBoltFlag){
																 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
															   readBoltFlag = ModifyVarStructVar.fabricName  ;
															   } 
                                	SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);  
  															if(ModifyVarStructVar.ChartType == 0){
	
		                                  SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
	                                    SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
		                               }
		                             if(ModifyVarStructVar.ChartType == 1){
	
		                               SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
	                                 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
		                             }	break;
															
														
  case 	  BoltDiameterValVarFlag : if(ModifyVarStructVar.ChartType == 0){
																		    ModifyVarStructVar.diameter++;
																	      ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar);  
                                    
															    	 }
																	if(ModifyVarStructVar.ChartType == 1){
												
																		ModifyVarStructVar.diameter_M++;
																	  ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);       
																  	}
																 			if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
																	 if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
																	 
	                                ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
																  ResetPress.DacOutData_B =  getOutData(ResetPress.SetPress_Bolt);break;
	                                
																	
	case	   BoltGardeValVarFlag: 
                              		if(ModifyVarStructVar.ChartType == 0){
																		    ModifyVarStructVar.garde++;
																	      ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar); 
                                       
																	     																	
																	 }
																	if(ModifyVarStructVar.ChartType == 1){
												
																		ModifyVarStructVar.garde_M++;
																	  ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);       
																
																	}
																			if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
																		if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
																	 
																	 
                                  ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
																	ResetPress.DacOutData_B =  getOutData(ResetPress.SetPress_Bolt);break;


  case     BoltTargetTorqueUintVarFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;	
	                               	if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 } break;     




	/************************************²Ëµ¥ËÄ½Ç¶ÈÄ£Ê½ **************************************************************/		


 	case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName++;
																 if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 											  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		
	                             ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;
		 
	
	
	if(ModifyVarStructVar.TorqueUint==0)
	  {
		  SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			SetTextValue(3,3,(uint8_t*)"N.m");
		}
	 else
	  {
		  SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
			SetTextValue(3,3,(uint8_t*)"ft.lbs");
		}		
                                
																 ResetPress.SetPress_Angle = 60000;ResetPress.DacOutData_A =  getOutData(ResetPress.SetPress_Angle);
																	
																 if(ModifyVarStructVar.fabricName != readBoltFlag){
																 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																  readBoltFlag = ModifyVarStructVar.fabricName ;
															   }break;
                         

 case  AnglePresetTorUintFlag  : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1; 											 
		
	                            
		 
	
	
	if(ModifyVarStructVar.TorqueUint==0)
	  {
		  SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			SetTextValue(3,3,(uint8_t*)"N.m");
		}
	 else
	  {
		  SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
			SetTextValue(3,3,(uint8_t*)"ft.lbs");
		}		 break; 
																 

 case 	TarGetAngleValVarFlag :  data++; SetTextInt32(3,4,data,0,0);break; //if(data > ModifyVarStructVar.Angle)DAC8771_WRITE_CMD(0x05,0);  break;
 

 case  AngleUintVarFlag :       ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0 ; 
															  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;
	 
	
 /************************************²Ëµ¥Îåµ²Î»Ä£Ê½ **************************************************************/			 
	 
	case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName++;
																  if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
															    if(ModifyVarStructVar.fabricName != readBoltFlag){
																  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																   readBoltFlag = ModifyVarStructVar.fabricName ;
															    }break;
                                
	case  TargetGearValVarFlag   :  ModifyVarStructVar.gear++;if(ModifyVarStructVar.gear > gearKind)ModifyVarStructVar.gear = 1; 
																	SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
	                                ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
																	ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ä¿±êÅ¤¾ØÖµ
																			 if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }
                                  ResetPress.SetPress_Gear = ModifyVarStructVar.gearpress*10;ResetPress.DacOutData_G =  getOutData(ResetPress.SetPress_Gear);break;
//																	
  case 	GearTargetTorUintValFlag :   TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }break;  
	                                  
		 
	case  GearUintVarFlag :        ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0 ; 
															     switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;
	
  
/***************************************** ´«¸ÐÆ÷Ä£Ê½  ***********************************************************/

  case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
	  	ModifyVarStructVar.tartor_sensor = TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor;
		 
	
	 
	if(ModifyVarStructVar.TorqueUint==0)
	 {
	   SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		 SetTextValue(5,5,(uint8_t*)"N.m");
	 }
	 
	if(ModifyVarStructVar.TorqueUint==1)
	 {
	   SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		 SetTextValue(5,5,(uint8_t*)"ft.lbs");
	 }
																	if(ModifyVarStructVar.fabricName != readBoltFlag){
																  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																  readBoltFlag = ModifyVarStructVar.fabricName ;
															    };break;
                                  

 	case    SensorPresetTorValVarFlag :   maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
	
                                       		if(ModifyVarStructVar.TorqueUint==0){
		                                     
		                                      ModifyVarStructVar.presettor_sensor += (ROUND_TO_UINT32(maxdata*ADDRATE));  
	                                        }
																					
																					if(ModifyVarStructVar.TorqueUint==1){
																						 datafts = ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549);	
                                             																 
																             datafts +=(ROUND_TO_UINT32(maxdata*ADDRATE/1.3549));
																	           ModifyVarStructVar.presettor_sensor = (ROUND_TO_UINT32(datafts*1.3549));
		                                     
	                                        }
                                      ResetPress.SetPress_Sensor = setSensorPresetTorValVarFlag(ModifyVarStructVar.TorqueUint, &ModifyVarStructVar.presettor_sensor);
																			  	    if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                    //   SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                    //   SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                     //  SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                   //  SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	}
				
                                      ResetPress.DacOutData_S =  getOutData(ResetPress.SetPress_Sensor);break;
	
  case    SensorPresetTorValVarUintFlag :TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;    
	                                    if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                     //  SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                     //  SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                     //  SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                   //  SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                      	}break;



  case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //ÉÏÎ»»úµ¼ÈëµÄÄ¿±êÅ¤¾Ø
	                                     
  
                                       }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//´«¸ÐÆ÷²É¼¯µÄÅ¤¾Ø´óÓÚÄ¿±êÅ¤¾ØÍ£»ú
	
	case 	  SensorTargetToreValVarUintFlag:	TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                       }else  ModifyVarStructVar.TorqueUint = 1; 
	 	                                if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	 } break;  
 
 case      SensorPressUintFlag  :     ModifyVarStructVar.pressUint++;if(ModifyVarStructVar.pressUint>2)ModifyVarStructVar.pressUint =0 ; 
																		  switch(ModifyVarStructVar.pressUint)
			                                  {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 } break;
																			
 }
 
 

}



void ModiVarDecWide(uint8_t Flag)
{
	uint32_t data = 0;


	
	uint8_t arr[5] = {0};
	
switch(Flag)

{
/************************************²Ëµ¥Ò» ********* *****************************************************/

case  LanguageValVarFlag:       Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                            else  ModifyVarStructVar.Language = 1; 
	                              setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0ÊÇÓ¢ÎÄ
						 
case 	ChartStandardValVarFlag :	ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                             else ModifyVarStructVar.ChartType = 1;
                                if(ModifyVarStructVar.fabricName != readBoltFlag){
																	  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																	  readBoltFlag =  ModifyVarStructVar.fabricName; 
																 }
																 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0ÊÇÓ¢Î  //0ÊÇÓ¢ÖÆ
					
case  YearValVarFlag :    calendar.w_year-=111;  setYearValVarFlag(&calendar.w_year);break; 																							    
																							
case	MonthValVarFlag : calendar.w_month--;setMonthValVarFlag(&calendar.w_month);break;																							           

case  DayValVarFlag :   calendar.w_date--; setDayValVarFlag(&calendar.w_date); break;
case  HourValVarFlag :  calendar.hour--; setHourValVarFlag(&calendar.hour); break;
case  MinuteValVarFlag :calendar.min--; setMinuteValVarFlag(&calendar.min); break;
case  SecondValVarFlag :calendar.sec--;  setSecondValVarFlag(&calendar.sec);break;


/************************************²Ëµ¥¶þÅ¤¾ØÄ£Ê½ **************************************************************/


case 	 TorqueTypeValVarFlag: 	 
														 ModifyVarStructVar.fabricName--;
														 if((signed char)ModifyVarStructVar.fabricName < 1 ){
															 
															 ModifyVarStructVar.fabricName = productKind;
														 }
														 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		                        ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;	
													 if(ModifyVarStructVar.TorqueUint == 0)
		                          {
		   	           
			                        SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                          }
		                       else{
		                     
			                      SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                        }	
														 
														 if(ModifyVarStructVar.fabricName != readBoltFlag){
														 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
														 readBoltFlag  =   ModifyVarStructVar.fabricName; 

														 } break;
															 
														


case 	 MaxTorqueUintVarFlag:   TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                }else  ModifyVarStructVar.TorqueUint = 1;
                                  if(ModifyVarStructVar.TorqueUint == 0)
		                         {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                        SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                     SetTextValue(1,2,(uint8_t*)"N.m");
			                       SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															   SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                            SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                          SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                         }break; 	    

	 
case   TargetTorqueValVarFlag:   maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
																	
                               		 if(ModifyVarStructVar.TorqueUint == 0){
		                              
																   ModifyVarStructVar.TartorVal_TorMode -= (ROUND_TO_UINT32(maxdata*ADDRATE));
																	 	
	                                 }	
																	 
																	 
																	 if(ModifyVarStructVar.TorqueUint == 1){
		                              
																	 datafts = ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549);	
                                 																 
																   datafts -=(ROUND_TO_UINT32(maxdata*ADDRATE/1.3549));
																	 ModifyVarStructVar.TartorVal_TorMode = (ROUND_TO_UINT32(datafts*1.3549));
																		 
																		 
														 
	                                 }

															 ResetPress.SetPress_Torque = setTargetTorqueValVarFlag(ModifyVarStructVar.TorqueUint,&ModifyVarStructVar.TartorVal_TorMode) ; 
															if(ModifyVarStructVar.TorqueUint == 0)
		                         {
															 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                        // SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                      // SetTextValue(1,2,(uint8_t*)"N.m");
			                         SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                         }
		                        else{
															
															 //  SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                          SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                          //  SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                           SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                          }
															 
														ResetPress.DacOutData_T =  getOutData(ResetPress.SetPress_Torque);break;
															

case   TargetTorqueUnitVarFlag: TorqueUint_C++;if(TorqueUint_C%2==0){
		                                   ModifyVarStructVar.TorqueUint = 0;        
	                              }else  ModifyVarStructVar.TorqueUint = 1;
                                if(ModifyVarStructVar.TorqueUint == 0)
		                            {
															   SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			                           SetTextValue(1,4,(uint8_t*)"N.m");  
		   	                         SetTextValue(1,2,(uint8_t*)"N.m");
			                           SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		                            }
		                          else{
															
															   SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				                         SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
		                             SetTextValue(1,2,(uint8_t*)"ft.lbs");
			                           SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		                          }break; 


case 	TorquePressUnitVarFlag	 :ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint<0)ModifyVarStructVar.pressUint = 2 ;
															  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 } break;


/************************************²Ëµ¥ÈýÂÝË¨Ä£Ê½ **************************************************************/	

case   BoltTypeVareFlag   :  ModifyVarStructVar.fabricName--;
														 if(ModifyVarStructVar.fabricName < 1 ) ModifyVarStructVar.fabricName =  productKind;
														
														 if(ModifyVarStructVar.fabricName != readBoltFlag){
														 ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
															readBoltFlag = ModifyVarStructVar.fabricName;
														 }
															SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);  
  														if(ModifyVarStructVar.ChartType == 0){
	
		                                  SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
	                                    SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
		                             }
		                             if(ModifyVarStructVar.ChartType == 1){
	
		                               SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
	                                 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
		                             }	break; 
													 
														 
case 	  BoltDiameterValVarFlag : 
															if(ModifyVarStructVar.ChartType == 0){
																		ModifyVarStructVar.diameter--;
																		ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar);  
																
																 }
															if(ModifyVarStructVar.ChartType == 1){
										
																ModifyVarStructVar.diameter_M--;
																ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);       
																}
															
																
																	if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
																	if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
															
															ResetPress.SetPress_Bolt  = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
															ResetPress.DacOutData_B   =  getOutData(ResetPress.SetPress_Bolt );break;
															
														 
															
case	   BoltGardeValVarFlag:   
															if(ModifyVarStructVar.ChartType == 0){
																		ModifyVarStructVar.garde--;
																		ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde,&ModifyVarStructVar.diameter,TorquePatternVar,&BoltGardeDiaArrVar);  
																		
																													
																 }
															if(ModifyVarStructVar.ChartType == 1){
										
																ModifyVarStructVar.garde_M--;
																ModifyVarStructVar.TartorVal_BoltMode = setBoltGradeValVarFlag(&ModifyVarStructVar.garde_M,&ModifyVarStructVar.diameter_M,TorquePatternVar,&BoltGardeDiaArrVar);  
																																
															}
															
																		if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
														     	if(ModifyVarStructVar.ChartType == 0){
	
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
																	}
																	if(ModifyVarStructVar.ChartType == 1){
																
																	 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
																	 SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
																	}
															 ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //µÃµ½Ä¿±êÑ¹Á¦Öµ
															ResetPress.DacOutData_B =  getOutData(ResetPress.SetPress_Bolt);break;


case     BoltTargetTorqueUintVarFlag :TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1;
                                  if(ModifyVarStructVar.TorqueUint == 0)
																	{
																		SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
																		SetTextValue(2,4,(uint8_t*)"N.m"); 
																	}
																	 if(ModifyVarStructVar.TorqueUint == 1)
																		{
																		SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
																		SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
																	 }
                                    break;     




/************************************²Ëµ¥ËÄ½Ç¶ÈÄ£Ê½ **************************************************************/		


case  AngleTypeValVarFlag   : ModifyVarStructVar.fabricName--;if(ModifyVarStructVar.fabricName <1) ModifyVarStructVar.fabricName = productKind;
																		
														  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		
	                             ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;
		 
	
	
	if(ModifyVarStructVar.TorqueUint==0)
	  {
		  SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			SetTextValue(3,3,(uint8_t*)"N.m");
		}
	 else
	  {
		  SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
			SetTextValue(3,3,(uint8_t*)"ft.lbs");
		}		
														  ResetPress.SetPress_Angle = 60000;ResetPress.DacOutData_A =  getOutData(ResetPress.SetPress_Angle);
																		
														 if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															}
														break;

case  AnglePresetTorUintFlag  : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1; 											

		 
	
	
	if(ModifyVarStructVar.TorqueUint==0)
	  {
		  SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			SetTextValue(3,3,(uint8_t*)"N.m");
		}
	 else
	  {
		  SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
			SetTextValue(3,3,(uint8_t*)"ft.lbs");
		}		break; 
														 

case 	TarGetAngleValVarFlag :  data++; SetTextInt32(3,4,data,0,0);break; //if(data > ModifyVarStructVar.Angle)DAC8771_WRITE_CMD(0x05,0);  break;


case  AngleUintVarFlag :        ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint < 0)ModifyVarStructVar.pressUint = 2;
														
														     switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }break;


/************************************²Ëµ¥Îåµ²Î»Ä£Ê½ **************************************************************/			 

case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   
															  if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															 }  break;

case  TargetGearValVarFlag   :  ModifyVarStructVar.gear--;if(ModifyVarStructVar.gear < 1)ModifyVarStructVar.gear = gearKind; 
												
															 SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress; //Ä¿±êÑ¹Á¦Öµ
															 ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ä¿±êÅ¤¾ØÖµ
														    if(ModifyVarStructVar.TorqueUint == 0)
		                              {
				                           SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				                           SetTextValue(4,3,(uint8_t*)"N.m");
			                            }
			                       else
			                         {
				                        SetTextValue(4,3,(uint8_t*)"ft.lbs");
			                          SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			                         }
														 ResetPress.SetPress_Gear = ModifyVarStructVar.gearpress*10; ResetPress.DacOutData_G =  getOutData(ResetPress.SetPress_Gear); break;
															
case 	GearTargetTorUintValFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                    ModifyVarStructVar.TorqueUint = 0;        
	                                  }else  ModifyVarStructVar.TorqueUint = 1; if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }break; 
 
case  GearUintVarFlag :          ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint<0)ModifyVarStructVar.pressUint = 2 ; 
															  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 } break;


/***************************************** ´«¸ÐÆ÷Ä£Ê½  ***********************************************************/

case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
	  	                          ModifyVarStructVar.tartor_sensor = TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor;
																if(ModifyVarStructVar.TorqueUint==0)
																 {
																	 SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
																	 SetTextValue(5,5,(uint8_t*)"N.m");
																 }
																 
																if(ModifyVarStructVar.TorqueUint==1)
																 {
																	 SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
																	 SetTextValue(5,5,(uint8_t*)"ft.lbs");
																 }
																 
															 if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName;
															 }break; 
																		
case    SensorPresetTorValVarFlag :   maxdata = (TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA);
	
                                       		if(ModifyVarStructVar.TorqueUint==0){
		                                      ModifyVarStructVar.presettor_sensor -= (ROUND_TO_UINT32(maxdata*DECRATE));  
	                                        }
																					
																					if(ModifyVarStructVar.TorqueUint==1){
																						 datafts = ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549);	
                                             																 
																             datafts -=(ROUND_TO_UINT32(maxdata*ADDRATE/1.3549));
																	           ModifyVarStructVar.presettor_sensor = (ROUND_TO_UINT32(datafts*1.3549));
		                                     
	                                        }
																	ResetPress.SetPress_Sensor = setSensorPresetTorValVarFlag(ModifyVarStructVar.TorqueUint, &ModifyVarStructVar.presettor_sensor);
																	 	    if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																					 SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                      // SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                      // SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                      // SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                    // SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	}	
		
																	ResetPress.DacOutData_S =  getOutData(ResetPress.SetPress_Sensor);break;

case    SensorPresetTorValVarUintFlag : TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                     }else  ModifyVarStructVar.TorqueUint = 1;   
	  	                                 if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                    else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                      }break;



case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //ÉÏÎ»»úµ¼ÈëµÄÄ¿±êÅ¤¾Ø
																			

																		}SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//´«¸ÐÆ÷²É¼¯µÄÅ¤¾Ø´óÓÚÄ¿±êÅ¤¾ØÍ£»ú

case 	  SensorTargetToreValVarUintFlag:	TorqueUint_C++;if(TorqueUint_C%2==0){
		                                      ModifyVarStructVar.TorqueUint = 0;        
	                                     }else  ModifyVarStructVar.TorqueUint = 1;	
	 	                                 if(ModifyVarStructVar.TorqueUint==0)
	                                         {
																						SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		                                       SetTextValue(5,5,(uint8_t*)"N.m"); 
		                                       SetTextValue(5,3,(uint8_t*)"N.m");  
	                                         SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		                                       }
		                                     else{
			                                     SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		                                       SetTextValue(5,5,(uint8_t*)"ft.lbs");
			                                     SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	                                         SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
	                                     	}break;   //ÏÔÊ¾×î´óÅ¤¾Øµ¥Î»  

case      SensorPressUintFlag  :       ModifyVarStructVar.pressUint--;if((signed char)ModifyVarStructVar.pressUint < 0)ModifyVarStructVar.pressUint = 2 ; 
																		   switch(ModifyVarStructVar.pressUint)
			                                  {
				                                case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				                                case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			                                  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			                                  }break;
																	
}

}










void AdjustTorqueMode(void)
 {
 
     SetScreen(1);
	
		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
			 SetTextInt32(1,3, ModifyVarStructVar.TartorVal_TorMode,0,0); 
			 SetTextValue(1,4,(uint8_t*)"N.m");  
			}				
			else{
				
				 SetTextValue(1,4,(uint8_t*)"ft.lbs"); 
				 SetTextInt32(1,3, ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_TorMode/1.3549),0,0); 
			}
			 
		  switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(1,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(1,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(1,5,(uint8_t*)"Psi");break;
			 }
		 
		 
		   SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		   ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;	
		
		
	 
	  if(ModifyVarStructVar.TorqueUint == 0)
		 {
		   	  SetTextValue(1,2,(uint8_t*)"N.m");
			    SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		 }
		 else{
		      SetTextValue(1,2,(uint8_t*)"ft.lbs");
			    SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		 }	
		 

 }
 
 
 
 
 
 
 void AdjustBoltMode(void)
  {
	


	 SetScreen(2);
	
	if(ModifyVarStructVar.ChartType == 0){
	
		 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr);
	   SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr);
		}
		if(ModifyVarStructVar.ChartType == 1){
	
		 SetTextValue(2,2,(uint8_t*)	 ModifyVarStructVar.BoltDiameterArr_M);
	   SetTextValue(2,3,(uint8_t*)	 ModifyVarStructVar.BoltGardeArr_M);
		}
		
		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
			  SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
				SetTextValue(2,4,(uint8_t*)"N.m"); 
			}
			 if(ModifyVarStructVar.TorqueUint == 1)
		    {
			  SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
				SetTextValue(2,4,(uint8_t*)"ft.lbs"); 
			 }
		 	
		
		 SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ 		
		 
	}
	
	
	
	
	
	
	
void AdjustGearMode(void)
	{
	
	

       	SetScreen(4);
		
		SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
		switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(4,4,(uint8_t*)"Bar");break;
				case 1: SetTextValue(4,4,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(4,4,(uint8_t*)"Psi");break;
			 }
	   

	
		 SetTextInt32(4,2,  GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
			 
		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
				
				 SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
				 SetTextValue(4,3,(uint8_t*)"N.m");
			  
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }
	  
	  
		 
	  

	
	}




void AdjustAngleMode(void)
 {
 
 

 SetScreen(3);
  SetTextInt32(3,4,ModifyVarStructVar.Angle,0,0);              //
		
	 	switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(3,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(3,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(3,5,(uint8_t*)"Psi");break;
			 }
	   
	   
	
	

	 
	SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ	
		 
		 
	 ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor*MAXMPA ;
		 
	
	
	if(ModifyVarStructVar.TorqueUint==0)
	  {
		  SetTextInt32(3,2,ModifyVarStructVar.MaxtorVal_TorMode,0,0);
			SetTextValue(3,3,(uint8_t*)"N.m");
		}
	 else
	  {
		  SetTextInt32(3,2,ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
			SetTextValue(3,3,(uint8_t*)"ft.lbs");
		}		

	 
  
	

 }


void AdjustSensorMode(void)
 {

	 
		  SetScreen(5);
		 
 	switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(5,6,(uint8_t*)"Bar");break;
				case 1: SetTextValue(5,6,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(5,6,(uint8_t*)"Psi");break;
			 }
	
   if(ModifyVarStructVar.TorqueUint==0)
	  {
		 SetTextValue(5,3,(uint8_t*)"N.m");  
	   SetTextInt32(5,2,ModifyVarStructVar.presettor_sensor,0,0);   
		}
		else{
			
			 SetTextValue(5,3,(uint8_t*)"ft.lbs");  
	     SetTextInt32(5,2,ROUND_TO_UINT32(ModifyVarStructVar.presettor_sensor/1.3549),0,0);  	
		}
	
	    

	    if(ModifyVarStructVar.fabricName==0)ModifyVarStructVar.fabricName = 1;
		
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //ÏÔÊ¾²úÆ·Ãû³Æ
	  	ModifyVarStructVar.tartor_sensor = TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor;
		 
	
	 
	if(ModifyVarStructVar.TorqueUint==0)
	 {
	   SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0);
		 SetTextValue(5,5,(uint8_t*)"N.m");
	 }
	 
	if(ModifyVarStructVar.TorqueUint==1)
	 {
	   SetTextInt32(5,4,ROUND_TO_UINT32(ModifyVarStructVar.tartor_sensor/1.3549),0,0);
		 SetTextValue(5,5,(uint8_t*)"ft.lbs");
	 }
	
 
 }


 
 
 
 void  AdcGetShow(uint8_t memu,uint8_t pressuint,float press)
  {
	
	
	switch(memu)
			 {
					case 1:switch(pressuint){                                                           //Å¤¾Ø
						
						     case 0: SetTextValue(1,5,(uint8_t*)"Bar");SetTextFloat(1,7,press,2,0); break;
						     case 1: SetTextValue(1,5,(uint8_t*)"Mpa");SetTextFloat(1,7,press/10,2,0); break; 				
				         case 2: SetTextValue(1,5,(uint8_t*)"Psi");SetTextFloat(1,7,press*14,2,0); break;          
			 
						     
					       }break;
					case 4:switch(ModifyVarStructVar.pressUint){                                       //½Ç¶È
						
						     case 0: SetTextValue(3,5,(uint8_t*)"Bar");SetTextFloat(3,6,press,2,0); break;
						     case 1: SetTextValue(3,5,(uint8_t*)"Mpa");SetTextFloat(3,6,press/10,2,0); break; 				
				         case 2: SetTextValue(3,5,(uint8_t*)"Psi");SetTextFloat(3,6,press*14,2,0); break;          
			 
						     
					     }break;	
						
				 case 3:switch(ModifyVarStructVar.pressUint){                                        //µµÎ»
						
						     case 0: SetTextValue(4,4,(uint8_t*)"Bar");SetTextFloat(4,6,press,2,0); break;
						     case 1: SetTextValue(4,4,(uint8_t*)"Mpa");SetTextFloat(4,6,press/10,2,0); break; 				
				         case 2: SetTextValue(4,4,(uint8_t*)"Psi");SetTextFloat(4,6,press*14,2,0); break;          
			 
						     
					     }break;		
	      case 5:switch(ModifyVarStructVar.pressUint){                                        //´«¸ÐÆ÷
						
						     case 0: SetTextValue(5,6,(uint8_t*)"Bar");SetTextFloat(5,7,press,2,0); break;
						     case 1: SetTextValue(5,6,(uint8_t*)"Mpa");SetTextFloat(5,7,press/10,2,0); break; 				
				         case 2: SetTextValue(5,6,(uint8_t*)"Psi");SetTextFloat(5,7,press*14,2,0); break;          
			     
					     }break;	
			}	
	
	
	
	}










