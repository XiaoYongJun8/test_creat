#include "screenshow.h"
#include "screendriver.h"
#include "dac8771.h"
uint8_t  func_index = 0 ;


void (*current_operation_index)();





KEY_Table table[75] = {

{0,17,0,8,1,(*MemuOne)}, //������1

{1,17, 9,8,2,(*MemuOneOptionOne)},       //ѡ��������1ѡ��1
{2,17,10,1,3,(*MemuOneOptionTwo)},       //ѡ��������1ѡ��2
{3,17,11,2,4,(*MemuOneOptionThree)},     //ѡ��������1ѡ��3
{4,17,12,3,5,(*MemuOneOptionFour)},      // ѡ��������1ѡ��4
{5,17,13,4,6,(*MemuOneOptionFive)},      //ѡ��������1ѡ��5
{6,17,14,5,7,(*MemuOneOptionSix)},       //ѡ��������1ѡ��6
{7,17,15,6,8,(*MemuOneOptionSeven)},     //ѡ��������1ѡ��7
{8,17,16,7,1,(*MemuOneOptionEight)},     // ѡ��������1ѡ��8

{9,  9,1,9, 9, (*EnterMemuOneOptionOne)},     //����������1ѡ��1
{10,10,2,10,10,(*EnterMemuOneOptionTwo)},    //����������1ѡ��2
{11,11,3,11,11,(*EnterMemuOneOptionThree)},  //����������1ѡ��3
{12,12,4,12,12,(*EnterMemuOneOptionFour)},   //����������1ѡ��4
{13,13,5,13,13,(*EnterMemuOneOptionFive)},   //����������1ѡ��5
{14,14,6,14,14,(*EnterMemuOneOptionSix)},    //����������1ѡ��6
{15,15,7,15,15,(*EnterMemuOneOptionSeven)},  //����������1ѡ��7
{16,16,8,16,16,(*EnterMemuOneOptionEight)},  //����������1ѡ��8




{17,28,17,22,18,(*MemuTwo)}, //������2                                 //Ť��ģʽ


{18,28,23,22,19,(*MemuTwoOptionOne)},       //ѡ��������1ѡ��1        
{19,28,24,18,20,(*MemuTwoOptionTwo)},       //ѡ��������1ѡ��2
{20,28,25,19,21,(*MemuTwoOptionThree)},     //ѡ��������1ѡ��3         //�޸�Ť��ֵ
{21,28,26,20,22,(*MemuTwoOptionFour)},      // ѡ��������1ѡ��4
{22,28,27,21,18,(*MemuTwoOptionFive)},      //ѡ��������1ѡ��5


{23,23,18,23,23, (*EnterMemuTwoOptionOne)},    //����������1ѡ��1       
{24,24,19,24,24,(*EnterMemuTwoOptionTwo)},    //����������1ѡ��2
{25,25,20,25,25,(*EnterMemuTwoOptionThree)},  //����������1ѡ��3       
{26,26,21,26,26,(*EnterMemuTwoOptionFour)},   //����������1ѡ��4
{27,27,22,27,27,(*EnterMemuTwoOptionFive)},   //����������1ѡ��5







{28,37,28,32,29,(*MemuThree)}, //������3                              //��˨ģʽ    


{29,37,33,32,30,(*MemuThreeOptionOne)},       //ѡ��������1ѡ��1     
{30,37,34,29,31,(*MemuThreeOptionTwo)},       //ѡ��������1ѡ��2      //��˨ֱ��
{31,37,35,30,32,(*MemuThreeOptionThree)},     //ѡ��������1ѡ��3      //��˨�ȼ�  
{32,37,36,31,29,(*MemuThreeOptionFour)},      // ѡ��������1ѡ��4


{33,33,29,33,33, (*EnterMemuThreeOptionOne)},    //����������1ѡ��1
{34,34,30,34,34,(*EnterMemuThreeOptionTwo)},    //����������1ѡ��2   
{35,35,31,35,35,(*EnterMemuThreeOptionThree)},  //����������1ѡ��3   
{36,36,32,36,36,(*EnterMemuThreeOptionFour)},   //����������1ѡ��4









{37,46,37,41,38,(*MemuFive)}, //������4                                      //��λģʽ


{38,46,42,41,39,(*MemuFiveOptionOne)},       //ѡ��������1ѡ��1
{39,46,43,38,40,(*MemuFiveOptionTwo)},       //ѡ��������1ѡ��2             //�޸ĵ�λ
{40,46,44,39,41,(*MemuFiveOptionThree)},     //ѡ��������1ѡ��3
{41,46,45,40,38,(*MemuFiveOptionFour)},      // ѡ��������1ѡ��4


{42,42,38,42,42, (*EnterMemuFiveOptionOne)},    //����������1ѡ��1        
{43,43,39,43,43,(*EnterMemuFiveOptionTwo)},    //����������1ѡ��2
{44,44,40,44,44,(*EnterMemuFiveOptionThree)},  //����������1ѡ��3
{45,45,41,45,45,(*EnterMemuFiveOptionFour)},   //����������1ѡ��4



{46,57,46,51,47,(*MemuFour)}, //������4                                      //�Ƕ�ģʽ


{47,57,52,51,48,(*MemuFourOptionOne)},       //ѡ��������1ѡ��1
{48,57,53,47,49,(*MemuFourOptionTwo)},       //ѡ��������1ѡ��2
{49,57,54,48,50,(*MemuFourOptionThree)},     //ѡ��������1ѡ��3
{50,57,55,49,51,(*MemuFourOptionFour)},      // ѡ��������1ѡ��4
{51,57,56,50,47,(*MemuFourOptionFive)},      // ѡ��������1ѡ��4

{52,52,47,52,52, (*EnterMemuFourOptionOne)},    //����������1ѡ��1        
{53,53,48,53,53,(*EnterMemuFourOptionTwo)},    //����������1ѡ��2
{54,54,49,54,54,(*EnterMemuFourOptionThree)},  //����������1ѡ��3
{55,55,50,55,55,(*EnterMemuFourOptionFour)},   //����������1ѡ��4
{56,56,51,56,56,(*EnterMemuFourOptionFive)},     // ѡ��������1ѡ��4








{57,0,57,63,58,(*MemuSix)}, //������6                                      //������ģʽ


{58,0,64,63,59,(*MemuSixOptionOne)},       //ѡ��������1ѡ��1
{59,0,65,58,60,(*MemuSixOptionTwo)},       //ѡ��������1ѡ��2           //Ԥ��Ť��
{60,0,66,59,61,(*MemuSixOptionThree)},     //ѡ��������1ѡ��3      
{61,0,67,60,62,(*MemuSixOptionFour)},      // ѡ��������1ѡ��4
{62,0,68,61,63,(*MemuSixOptionFive)},      //ѡ��������1ѡ��3
{63,0,69,62,58,(*MemuSixOptionSix)},       // ѡ��������1ѡ��4

{64,64,58,64,64, (*EnterMemuSixOptionOne)},    //����������1ѡ��1
{65,65,59,65,65,(*EnterMemuSixOptionTwo)},     //����������1ѡ��2     //7
{66,66,60,66,66,(*EnterMemuSixOptionThree)},   //����������1ѡ��3
{67,67,61,67,67,(*EnterMemuSixOptionFour)},    //����������1ѡ��4
{68,68,62,68,68,(*EnterMemuSixOptionFive)},    //����������1ѡ��3
{69,69,63,69,69,(*EnterMemuSixOptionSix)},     //����������1ѡ��4


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
		 
		  OSTimeDly(5);		//����һ������Ϊ5ms,�ȴ�2������Ϊ10ms,ȷ����10MS����
		 
		  if(j==0){
				TIM_Cmd(TIM4,DISABLE); //ʹ�ܶ�ʱ��	
				OSTaskSuspend(6);
				if(!(--ucCount1S))
				 {
					 j = 1;
					 ucCount1S = 40;
				   OSTaskResume(6);
				 TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��	
				 }	
				 
			}
		 
	 

		if(KeyMemu){          
				  memutimes--; 
				  if(memutimes==0 )
				   {
						  func_index=table[func_index].memu;    //ȷ��ѡ������˵���ѡ��
	            memutimes= MEMUTIME; 
           					 
				   } 
			}
			
		else{
		  memutimes = MEMUTIME;
		 }
			  
				 
				
	   if(KeyEnter)       //�����KEY4
	      {
					
			   entertimes--;
					
	       if(entertimes==0){
					    entertimes = ENTERTIMES;
					 		func_index=table[func_index].enter;    //ȷ��ѡ������˵���ѡ��	 
				 }
			
					
        }
				else{
					 entertimes = ENTERTIMES;
				}
				
				
				
		
	
       if(KeyUp)                         //�Ϸ���KEY1
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
				
		
       if(KeyDown)       //�·���KEY2
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
	     current_operation_index=table[func_index].current_operation;//ָ���������
			if((func_index==0||func_index==17||func_index==28||func_index==37||func_index==46||func_index==57)&&(picinit==1)){
				Memory = ScreenMem;
				
				for(i=0;i<8;i++){
					
				current_operation_index();//ִ�е�ǰ��������
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
uint32_t  maxdata = 0;  //Ť��ģʽ���Ť��ֵ
uint32_t  datafts = 0;  //��λft.lbs��Ť��ֵ

void ModiVarAdd(uint8_t Flag)
{
	
uint8_t arr[5] = {0};
	
switch(Flag)
	
  {
	 
	   /************************************�˵�һ **************************************************************/
	 
  	case  LanguageValVarFlag:      Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
                                	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0��Ӣ��
	                
  	case 	ChartStandardValVarFlag :	 ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                                 else ModifyVarStructVar.ChartType = 1;
		
                                     		 if(ModifyVarStructVar.fabricName != readBoltFlag){
																	       ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
			                                   readBoltFlag =  ModifyVarStructVar.fabricName; 
																       }
                                   	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0��Ӣ��
							
	  case  YearValVarFlag :  if(FastDecTimes>=ADDTIMES)calendar.w_year+=111 ;else calendar.w_year++;setYearValVarFlag(&calendar.w_year);break; 																							    
																									
	  case	MonthValVarFlag : calendar.w_month++;setMonthValVarFlag(&calendar.w_month);break;																							           
	
    case  DayValVarFlag :   calendar.w_date++; setDayValVarFlag(&calendar.w_date); break;
  	case  HourValVarFlag :  calendar.hour++; setHourValVarFlag(&calendar.hour); break;
	  case  MinuteValVarFlag :calendar.min++; setMinuteValVarFlag(&calendar.min); break;
    case  SecondValVarFlag :calendar.sec++;  setSecondValVarFlag(&calendar.sec);break;
	

	/************************************�˵���Ť��ģʽ **************************************************************/

                                 
   case 	 TorqueTypeValVarFlag: ModifyVarStructVar.fabricName+=1;
                  
	                              if(ModifyVarStructVar.fabricName > productKind)
																 { 
																	 ModifyVarStructVar.fabricName = 1;
																 }
																 
														 SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
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


	/************************************�˵�����˨ģʽ **************************************************************/	
	
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
																
																	
	                                ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
																
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
																		
																
                                  ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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




	/************************************�˵��ĽǶ�ģʽ **************************************************************/		


 	case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName++;
																 if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                              		SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
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
	 
	
 /************************************�˵��嵲λģʽ **************************************************************/			 
	 
	case  GearTypeValVarFlag     :   ModifyVarStructVar.fabricName++;
																   if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                   SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
															     if(ModifyVarStructVar.fabricName != readBoltFlag){
																   ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																   readBoltFlag = ModifyVarStructVar.fabricName;
															    }break;
                                
	case  TargetGearValVarFlag   :  ModifyVarStructVar.gear++;if(ModifyVarStructVar.gear > gearKind)ModifyVarStructVar.gear = 1; 
																  SetTextInt32(4,2,  GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
	                                ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
																	ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ŀ��Ť��ֵ
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
	
  
/***************************************** ������ģʽ  ***********************************************************/

  case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 
		
		                          SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
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



  case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //��λ�������Ŀ��Ť��
	                                       
  
                                       }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//�������ɼ���Ť�ش���Ŀ��Ť��ͣ��
	
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
/************************************�˵�һ **************************************************************/

case  LanguageValVarFlag:     Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
	                           setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0��Ӣ��
						 
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


/************************************�˵���Ť��ģʽ **************************************************************/


case 	 TorqueTypeValVarFlag: 	 
														 ModifyVarStructVar.fabricName--;
														 if((signed char)ModifyVarStructVar.fabricName < 1 ){
															 
															 ModifyVarStructVar.fabricName = productKind;
														 }
														 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
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


/************************************�˵�����˨ģʽ **************************************************************/	

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
															ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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
														 
															ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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
    




/************************************�˵��ĽǶ�ģʽ **************************************************************/		


case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName--;if(ModifyVarStructVar.fabricName <1) ModifyVarStructVar.fabricName = productKind;
														   											  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
		
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


/************************************�˵��嵲λģʽ **************************************************************/			 

case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
															if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															}  break;

case  TargetGearValVarFlag   :  ModifyVarStructVar.gear--;if(ModifyVarStructVar.gear < 1)ModifyVarStructVar.gear = gearKind; 
												
															SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress; //Ŀ��ѹ��ֵ
															ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ŀ��Ť��ֵ
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


/***************************************** ������ģʽ  ***********************************************************/

case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
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



case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //��λ�������Ŀ��Ť��
																			 

																		 }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//�������ɼ���Ť�ش���Ŀ��Ť��ͣ��

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
	                                     	}break;   //��ʾ���Ť�ص�λ  

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
	 
	  /************************************�˵�һ **************************************************************/
	 
  	case  LanguageValVarFlag:      Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
	                                 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0��Ӣ��
	               
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
	

	/************************************�˵���Ť��ģʽ **************************************************************/

                                 
   case 	 TorqueTypeValVarFlag: ModifyVarStructVar.fabricName+=1;
                  
	                              if(ModifyVarStructVar.fabricName > productKind)
																 { 
																	 ModifyVarStructVar.fabricName = 1;
																 }
																 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
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


	/************************************�˵�����˨ģʽ **************************************************************/	
	
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
																	 
	                                ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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
																	 
																	 
                                  ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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




	/************************************�˵��ĽǶ�ģʽ **************************************************************/		


 	case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName++;
																 if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 											  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
		
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
	 
	
 /************************************�˵��嵲λģʽ **************************************************************/			 
	 
	case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName++;
																  if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
															    if(ModifyVarStructVar.fabricName != readBoltFlag){
																  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																   readBoltFlag = ModifyVarStructVar.fabricName ;
															    }break;
                                
	case  TargetGearValVarFlag   :  ModifyVarStructVar.gear++;if(ModifyVarStructVar.gear > gearKind)ModifyVarStructVar.gear = 1; 
																	SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
	                                ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
																	ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ŀ��Ť��ֵ
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
	
  
/***************************************** ������ģʽ  ***********************************************************/

  case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
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



  case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //��λ�������Ŀ��Ť��
	                                     
  
                                       }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//�������ɼ���Ť�ش���Ŀ��Ť��ͣ��
	
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
/************************************�˵�һ ********* *****************************************************/

case  LanguageValVarFlag:       Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                            else  ModifyVarStructVar.Language = 1; 
	                              setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0��Ӣ��
						 
case 	ChartStandardValVarFlag :	ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                             else ModifyVarStructVar.ChartType = 1;
                                if(ModifyVarStructVar.fabricName != readBoltFlag){
																	  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																	  readBoltFlag =  ModifyVarStructVar.fabricName; 
																 }
																 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0��Ӣ�  //0��Ӣ��
					
case  YearValVarFlag :    calendar.w_year-=111;  setYearValVarFlag(&calendar.w_year);break; 																							    
																							
case	MonthValVarFlag : calendar.w_month--;setMonthValVarFlag(&calendar.w_month);break;																							           

case  DayValVarFlag :   calendar.w_date--; setDayValVarFlag(&calendar.w_date); break;
case  HourValVarFlag :  calendar.hour--; setHourValVarFlag(&calendar.hour); break;
case  MinuteValVarFlag :calendar.min--; setMinuteValVarFlag(&calendar.min); break;
case  SecondValVarFlag :calendar.sec--;  setSecondValVarFlag(&calendar.sec);break;


/************************************�˵���Ť��ģʽ **************************************************************/


case 	 TorqueTypeValVarFlag: 	 
														 ModifyVarStructVar.fabricName--;
														 if((signed char)ModifyVarStructVar.fabricName < 1 ){
															 
															 ModifyVarStructVar.fabricName = productKind;
														 }
														 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
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


/************************************�˵�����˨ģʽ **************************************************************/	

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
															
															ResetPress.SetPress_Bolt  = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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
															 ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //�õ�Ŀ��ѹ��ֵ
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




/************************************�˵��ĽǶ�ģʽ **************************************************************/		


case  AngleTypeValVarFlag   : ModifyVarStructVar.fabricName--;if(ModifyVarStructVar.fabricName <1) ModifyVarStructVar.fabricName = productKind;
																		
														  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
		
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


/************************************�˵��嵲λģʽ **************************************************************/			 

case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   
															  if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															 }  break;

case  TargetGearValVarFlag   :  ModifyVarStructVar.gear--;if(ModifyVarStructVar.gear < 1)ModifyVarStructVar.gear = gearKind; 
												
															 SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress; //Ŀ��ѹ��ֵ
															 ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ŀ��Ť��ֵ
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


/***************************************** ������ģʽ  ***********************************************************/

case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
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



case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //��λ�������Ŀ��Ť��
																			

																		}SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//�������ɼ���Ť�ش���Ŀ��Ť��ͣ��

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
	                                     	}break;   //��ʾ���Ť�ص�λ  

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
		 
		 
		   SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
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
		 	
		
		 SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ���� 		
		 
	}
	
	
	
	
	
	
	
void AdjustGearMode(void)
	{
	
	

       	SetScreen(4);
		
		SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
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
	   
	   
	
	

	 
	SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
		 
		 
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
		
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
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
					case 1:switch(pressuint){                                                           //Ť��
						
						     case 0: SetTextValue(1,5,(uint8_t*)"Bar");SetTextFloat(1,7,press,2,0); break;
						     case 1: SetTextValue(1,5,(uint8_t*)"Mpa");SetTextFloat(1,7,press/10,2,0); break; 				
				         case 2: SetTextValue(1,5,(uint8_t*)"Psi");SetTextFloat(1,7,press*14,2,0); break;          
			 
						     
					       }break;
					case 4:switch(ModifyVarStructVar.pressUint){                                       //�Ƕ�
						
						     case 0: SetTextValue(3,5,(uint8_t*)"Bar");SetTextFloat(3,6,press,2,0); break;
						     case 1: SetTextValue(3,5,(uint8_t*)"Mpa");SetTextFloat(3,6,press/10,2,0); break; 				
				         case 2: SetTextValue(3,5,(uint8_t*)"Psi");SetTextFloat(3,6,press*14,2,0); break;          
			 
						     
					     }break;	
						
				 case 3:switch(ModifyVarStructVar.pressUint){                                        //��λ
						
						     case 0: SetTextValue(4,4,(uint8_t*)"Bar");SetTextFloat(4,6,press,2,0); break;
						     case 1: SetTextValue(4,4,(uint8_t*)"Mpa");SetTextFloat(4,6,press/10,2,0); break; 				
				         case 2: SetTextValue(4,4,(uint8_t*)"Psi");SetTextFloat(4,6,press*14,2,0); break;          
			 
						     
					     }break;		
	      case 5:switch(ModifyVarStructVar.pressUint){                                        //������
						
						     case 0: SetTextValue(5,6,(uint8_t*)"Bar");SetTextFloat(5,7,press,2,0); break;
						     case 1: SetTextValue(5,6,(uint8_t*)"Mpa");SetTextFloat(5,7,press/10,2,0); break; 				
				         case 2: SetTextValue(5,6,(uint8_t*)"Psi");SetTextFloat(5,7,press*14,2,0); break;          
			     
					     }break;	
			}	
	
	
	
	}










