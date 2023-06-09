#include "screenshow.h"
#include "screendriver.h"
#include "dac8771.h"
uint8_t  func_index = 0 ;


void (*current_operation_index)();





KEY_Table table[75] = {

{0,17,0,8,1,(*MemuOne)}, //主界面1

{1,17, 9,8,2,(*MemuOneOptionOne)},       //选择主界面1选项1
{2,17,10,1,3,(*MemuOneOptionTwo)},       //选择主界面1选项2
{3,17,11,2,4,(*MemuOneOptionThree)},     //选择主界面1选项3
{4,17,12,3,5,(*MemuOneOptionFour)},      // 选择主界面1选项4
{5,17,13,4,6,(*MemuOneOptionFive)},      //选择主界面1选项5
{6,17,14,5,7,(*MemuOneOptionSix)},       //选择主界面1选项6
{7,17,15,6,8,(*MemuOneOptionSeven)},     //选择主界面1选项7
{8,17,16,7,1,(*MemuOneOptionEight)},     // 选择主界面1选项8

{9,  9,1,9, 9, (*EnterMemuOneOptionOne)},     //进入主界面1选项1
{10,10,2,10,10,(*EnterMemuOneOptionTwo)},    //进入主界面1选项2
{11,11,3,11,11,(*EnterMemuOneOptionThree)},  //进入主界面1选项3
{12,12,4,12,12,(*EnterMemuOneOptionFour)},   //进入主界面1选项4
{13,13,5,13,13,(*EnterMemuOneOptionFive)},   //进入主界面1选项5
{14,14,6,14,14,(*EnterMemuOneOptionSix)},    //进入主界面1选项6
{15,15,7,15,15,(*EnterMemuOneOptionSeven)},  //进入主界面1选项7
{16,16,8,16,16,(*EnterMemuOneOptionEight)},  //进入主界面1选项8




{17,28,17,22,18,(*MemuTwo)}, //主界面2                                 //扭矩模式


{18,28,23,22,19,(*MemuTwoOptionOne)},       //选择主界面1选项1        
{19,28,24,18,20,(*MemuTwoOptionTwo)},       //选择主界面1选项2
{20,28,25,19,21,(*MemuTwoOptionThree)},     //选择主界面1选项3         //修改扭矩值
{21,28,26,20,22,(*MemuTwoOptionFour)},      // 选择主界面1选项4
{22,28,27,21,18,(*MemuTwoOptionFive)},      //选择主界面1选项5


{23,23,18,23,23, (*EnterMemuTwoOptionOne)},    //进入主界面1选项1       
{24,24,19,24,24,(*EnterMemuTwoOptionTwo)},    //进入主界面1选项2
{25,25,20,25,25,(*EnterMemuTwoOptionThree)},  //进入主界面1选项3       
{26,26,21,26,26,(*EnterMemuTwoOptionFour)},   //进入主界面1选项4
{27,27,22,27,27,(*EnterMemuTwoOptionFive)},   //进入主界面1选项5







{28,37,28,32,29,(*MemuThree)}, //主界面3                              //螺栓模式    


{29,37,33,32,30,(*MemuThreeOptionOne)},       //选择主界面1选项1     
{30,37,34,29,31,(*MemuThreeOptionTwo)},       //选择主界面1选项2      //螺栓直径
{31,37,35,30,32,(*MemuThreeOptionThree)},     //选择主界面1选项3      //螺栓等级  
{32,37,36,31,29,(*MemuThreeOptionFour)},      // 选择主界面1选项4


{33,33,29,33,33, (*EnterMemuThreeOptionOne)},    //进入主界面1选项1
{34,34,30,34,34,(*EnterMemuThreeOptionTwo)},    //进入主界面1选项2   
{35,35,31,35,35,(*EnterMemuThreeOptionThree)},  //进入主界面1选项3   
{36,36,32,36,36,(*EnterMemuThreeOptionFour)},   //进入主界面1选项4









{37,46,37,41,38,(*MemuFive)}, //主界面4                                      //挡位模式


{38,46,42,41,39,(*MemuFiveOptionOne)},       //选择主界面1选项1
{39,46,43,38,40,(*MemuFiveOptionTwo)},       //选择主界面1选项2             //修改挡位
{40,46,44,39,41,(*MemuFiveOptionThree)},     //选择主界面1选项3
{41,46,45,40,38,(*MemuFiveOptionFour)},      // 选择主界面1选项4


{42,42,38,42,42, (*EnterMemuFiveOptionOne)},    //进入主界面1选项1        
{43,43,39,43,43,(*EnterMemuFiveOptionTwo)},    //进入主界面1选项2
{44,44,40,44,44,(*EnterMemuFiveOptionThree)},  //进入主界面1选项3
{45,45,41,45,45,(*EnterMemuFiveOptionFour)},   //进入主界面1选项4



{46,57,46,51,47,(*MemuFour)}, //主界面4                                      //角度模式


{47,57,52,51,48,(*MemuFourOptionOne)},       //选择主界面1选项1
{48,57,53,47,49,(*MemuFourOptionTwo)},       //选择主界面1选项2
{49,57,54,48,50,(*MemuFourOptionThree)},     //选择主界面1选项3
{50,57,55,49,51,(*MemuFourOptionFour)},      // 选择主界面1选项4
{51,57,56,50,47,(*MemuFourOptionFive)},      // 选择主界面1选项4

{52,52,47,52,52, (*EnterMemuFourOptionOne)},    //进入主界面1选项1        
{53,53,48,53,53,(*EnterMemuFourOptionTwo)},    //进入主界面1选项2
{54,54,49,54,54,(*EnterMemuFourOptionThree)},  //进入主界面1选项3
{55,55,50,55,55,(*EnterMemuFourOptionFour)},   //进入主界面1选项4
{56,56,51,56,56,(*EnterMemuFourOptionFive)},     // 选择主界面1选项4








{57,0,57,63,58,(*MemuSix)}, //主界面6                                      //传感器模式


{58,0,64,63,59,(*MemuSixOptionOne)},       //选择主界面1选项1
{59,0,65,58,60,(*MemuSixOptionTwo)},       //选择主界面1选项2           //预设扭矩
{60,0,66,59,61,(*MemuSixOptionThree)},     //选择主界面1选项3      
{61,0,67,60,62,(*MemuSixOptionFour)},      // 选择主界面1选项4
{62,0,68,61,63,(*MemuSixOptionFive)},      //选择主界面1选项3
{63,0,69,62,58,(*MemuSixOptionSix)},       // 选择主界面1选项4

{64,64,58,64,64, (*EnterMemuSixOptionOne)},    //进入主界面1选项1
{65,65,59,65,65,(*EnterMemuSixOptionTwo)},     //进入主界面1选项2     //7
{66,66,60,66,66,(*EnterMemuSixOptionThree)},   //进入主界面1选项3
{67,67,61,67,67,(*EnterMemuSixOptionFour)},    //进入主界面1选项4
{68,68,62,68,68,(*EnterMemuSixOptionFive)},    //进入主界面1选项3
{69,69,63,69,69,(*EnterMemuSixOptionSix)},     //进入主界面1选项4


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
		 
		  OSTimeDly(5);		//设置一个节拍为5ms,等待2个节拍为10ms,确定了10MS计数
		 
		  if(j==0){
				TIM_Cmd(TIM4,DISABLE); //使能定时器	
				OSTaskSuspend(6);
				if(!(--ucCount1S))
				 {
					 j = 1;
					 ucCount1S = 40;
				   OSTaskResume(6);
				 TIM_Cmd(TIM4,ENABLE); //使能定时器	
				 }	
				 
			}
		 
	 

		if(KeyMemu){          
				  memutimes--; 
				  if(memutimes==0 )
				   {
						  func_index=table[func_index].memu;    //确认选择这机菜单的选型
	            memutimes= MEMUTIME; 
           					 
				   } 
			}
			
		else{
		  memutimes = MEMUTIME;
		 }
			  
				 
				
	   if(KeyEnter)       //进入键KEY4
	      {
					
			   entertimes--;
					
	       if(entertimes==0){
					    entertimes = ENTERTIMES;
					 		func_index=table[func_index].enter;    //确认选择这机菜单的选型	 
				 }
			
					
        }
				else{
					 entertimes = ENTERTIMES;
				}
				
				
				
		
	
       if(KeyUp)                         //上翻建KEY1
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
				
		
       if(KeyDown)       //下翻建KEY2
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
	     current_operation_index=table[func_index].current_operation;//指向这个函数
			if((func_index==0||func_index==17||func_index==28||func_index==37||func_index==46||func_index==57)&&(picinit==1)){
				Memory = ScreenMem;
				
				for(i=0;i<8;i++){
					
				current_operation_index();//执行当前操作函数
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
uint32_t  maxdata = 0;  //扭矩模式最大扭矩值
uint32_t  datafts = 0;  //单位ft.lbs的扭矩值

void ModiVarAdd(uint8_t Flag)
{
	
uint8_t arr[5] = {0};
	
switch(Flag)
	
  {
	 
	   /************************************菜单一 **************************************************************/
	 
  	case  LanguageValVarFlag:      Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
                                	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0是英文
	                
  	case 	ChartStandardValVarFlag :	 ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                                 else ModifyVarStructVar.ChartType = 1;
		
                                     		 if(ModifyVarStructVar.fabricName != readBoltFlag){
																	       ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
			                                   readBoltFlag =  ModifyVarStructVar.fabricName; 
																       }
                                   	 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0是英制
							
	  case  YearValVarFlag :  if(FastDecTimes>=ADDTIMES)calendar.w_year+=111 ;else calendar.w_year++;setYearValVarFlag(&calendar.w_year);break; 																							    
																									
	  case	MonthValVarFlag : calendar.w_month++;setMonthValVarFlag(&calendar.w_month);break;																							           
	
    case  DayValVarFlag :   calendar.w_date++; setDayValVarFlag(&calendar.w_date); break;
  	case  HourValVarFlag :  calendar.hour++; setHourValVarFlag(&calendar.hour); break;
	  case  MinuteValVarFlag :calendar.min++; setMinuteValVarFlag(&calendar.min); break;
    case  SecondValVarFlag :calendar.sec++;  setSecondValVarFlag(&calendar.sec);break;
	

	/************************************菜单二扭矩模式 **************************************************************/

                                 
   case 	 TorqueTypeValVarFlag: ModifyVarStructVar.fabricName+=1;
                  
	                              if(ModifyVarStructVar.fabricName > productKind)
																 { 
																	 ModifyVarStructVar.fabricName = 1;
																 }
																 
														 SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
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


	/************************************菜单三螺栓模式 **************************************************************/	
	
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
																
																	
	                                ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
																
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
																		
																
                                  ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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




	/************************************菜单四角度模式 **************************************************************/		


 	case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName++;
																 if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                              		SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
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
	 
	
 /************************************菜单五挡位模式 **************************************************************/			 
	 
	case  GearTypeValVarFlag     :   ModifyVarStructVar.fabricName++;
																   if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                   SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
															     if(ModifyVarStructVar.fabricName != readBoltFlag){
																   ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																   readBoltFlag = ModifyVarStructVar.fabricName;
															    }break;
                                
	case  TargetGearValVarFlag   :  ModifyVarStructVar.gear++;if(ModifyVarStructVar.gear > gearKind)ModifyVarStructVar.gear = 1; 
																  SetTextInt32(4,2,  GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
	                                ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
																	ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //目标扭矩值
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
	
  
/***************************************** 传感器模式  ***********************************************************/

  case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 
		
		                          SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
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



  case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //上位机导入的目标扭矩
	                                       
  
                                       }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//传感器采集的扭矩大于目标扭矩停机
	
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
/************************************菜单一 **************************************************************/

case  LanguageValVarFlag:     Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
	                           setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0是英文
						 
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


/************************************菜单二扭矩模式 **************************************************************/


case 	 TorqueTypeValVarFlag: 	 
														 ModifyVarStructVar.fabricName--;
														 if((signed char)ModifyVarStructVar.fabricName < 1 ){
															 
															 ModifyVarStructVar.fabricName = productKind;
														 }
														 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
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


/************************************菜单三螺栓模式 **************************************************************/	

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
															ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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
														 
															ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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
    




/************************************菜单四角度模式 **************************************************************/		


case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName--;if(ModifyVarStructVar.fabricName <1) ModifyVarStructVar.fabricName = productKind;
														   											  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
		
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


/************************************菜单五挡位模式 **************************************************************/			 

case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
															if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															}  break;

case  TargetGearValVarFlag   :  ModifyVarStructVar.gear--;if(ModifyVarStructVar.gear < 1)ModifyVarStructVar.gear = gearKind; 
												
															SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress; //目标压力值
															ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //目标扭矩值
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


/***************************************** 传感器模式  ***********************************************************/

case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
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



case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //上位机导入的目标扭矩
																			 

																		 }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//传感器采集的扭矩大于目标扭矩停机

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
	                                     	}break;   //显示最大扭矩单位  

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
	 
	  /************************************菜单一 **************************************************************/
	 
  	case  LanguageValVarFlag:      Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                               else  ModifyVarStructVar.Language = 1;
	                                 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0是英文
	               
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
	

	/************************************菜单二扭矩模式 **************************************************************/

                                 
   case 	 TorqueTypeValVarFlag: ModifyVarStructVar.fabricName+=1;
                  
	                              if(ModifyVarStructVar.fabricName > productKind)
																 { 
																	 ModifyVarStructVar.fabricName = 1;
																 }
																 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
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


	/************************************菜单三螺栓模式 **************************************************************/	
	
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
																	 
	                                ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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
																	 
																	 
                                  ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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




	/************************************菜单四角度模式 **************************************************************/		


 	case  AngleTypeValVarFlag   :  ModifyVarStructVar.fabricName++;
																 if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 											  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
		
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
	 
	
 /************************************菜单五挡位模式 **************************************************************/			 
	 
	case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName++;
																  if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
															    if(ModifyVarStructVar.fabricName != readBoltFlag){
																  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																   readBoltFlag = ModifyVarStructVar.fabricName ;
															    }break;
                                
	case  TargetGearValVarFlag   :  ModifyVarStructVar.gear++;if(ModifyVarStructVar.gear > gearKind)ModifyVarStructVar.gear = 1; 
																	SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
	                                ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
																	ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //目标扭矩值
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
	
  
/***************************************** 传感器模式  ***********************************************************/

  case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName++;if(ModifyVarStructVar.fabricName > productKind) ModifyVarStructVar.fabricName = 1;
                                SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
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



  case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //上位机导入的目标扭矩
	                                     
  
                                       }SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//传感器采集的扭矩大于目标扭矩停机
	
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
/************************************菜单一 ********* *****************************************************/

case  LanguageValVarFlag:       Language_C++;if(Language_C%2==0) ModifyVarStructVar.Language = 0;
		                            else  ModifyVarStructVar.Language = 1; 
	                              setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0是英文
						 
case 	ChartStandardValVarFlag :	ChartType_C++;if(ChartType_C%2==0)ModifyVarStructVar.ChartType = 0;
		                             else ModifyVarStructVar.ChartType = 1;
                                if(ModifyVarStructVar.fabricName != readBoltFlag){
																	  ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																	  readBoltFlag =  ModifyVarStructVar.fabricName; 
																 }
																 setLangChartFlag(ModifyVarStructVar.Language,ModifyVarStructVar.ChartType,arr,arr);break; //0是英�  //0是英制
					
case  YearValVarFlag :    calendar.w_year-=111;  setYearValVarFlag(&calendar.w_year);break; 																							    
																							
case	MonthValVarFlag : calendar.w_month--;setMonthValVarFlag(&calendar.w_month);break;																							           

case  DayValVarFlag :   calendar.w_date--; setDayValVarFlag(&calendar.w_date); break;
case  HourValVarFlag :  calendar.hour--; setHourValVarFlag(&calendar.hour); break;
case  MinuteValVarFlag :calendar.min--; setMinuteValVarFlag(&calendar.min); break;
case  SecondValVarFlag :calendar.sec--;  setSecondValVarFlag(&calendar.sec);break;


/************************************菜单二扭矩模式 **************************************************************/


case 	 TorqueTypeValVarFlag: 	 
														 ModifyVarStructVar.fabricName--;
														 if((signed char)ModifyVarStructVar.fabricName < 1 ){
															 
															 ModifyVarStructVar.fabricName = productKind;
														 }
														 
														SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
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


/************************************菜单三螺栓模式 **************************************************************/	

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
															
															ResetPress.SetPress_Bolt  = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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
															 ResetPress.SetPress_Bolt = getPressValue(TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor,ModifyVarStructVar.TartorVal_BoltMode);  //得到目标压力值
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




/************************************菜单四角度模式 **************************************************************/		


case  AngleTypeValVarFlag   : ModifyVarStructVar.fabricName--;if(ModifyVarStructVar.fabricName <1) ModifyVarStructVar.fabricName = productKind;
																		
														  SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
		
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


/************************************菜单五挡位模式 **************************************************************/			 

case  GearTypeValVarFlag     :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   
															  if(ModifyVarStructVar.fabricName != readBoltFlag){
																ReadBoltGardeMeterArr(TorquePatternVar,&BoltGardeDiaArrVar,secop(2004),ModifyVarStructVar.fabricName);
																readBoltFlag = ModifyVarStructVar.fabricName; 
															 }  break;

case  TargetGearValVarFlag   :  ModifyVarStructVar.gear--;if(ModifyVarStructVar.gear < 1)ModifyVarStructVar.gear = gearKind; 
												
															 SetTextInt32(4,2, GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress; //目标压力值
															 ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //目标扭矩值
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


/***************************************** 传感器模式  ***********************************************************/

case   	SensorTypeValVarFlag :  ModifyVarStructVar.fabricName--;if((signed char)ModifyVarStructVar.fabricName < 1) ModifyVarStructVar.fabricName = productKind;
															  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
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



case     SensorTargetToreValVarFlag  :if(ModifyVarStructVar.tartor_sensor>= TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor ){          //上位机导入的目标扭矩
																			

																		}SetTextInt32(5,4,ModifyVarStructVar.tartor_sensor,0,0); break;//传感器采集的扭矩大于目标扭矩停机

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
	                                     	}break;   //显示最大扭矩单位  

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
		 
		 
		   SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
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
		 	
		
		 SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称 		
		 
	}
	
	
	
	
	
	
	
void AdjustGearMode(void)
	{
	
	

       	SetScreen(4);
		
		SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
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
	   
	   
	
	

	 
	SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称	
		 
		 
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
		
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //显示产品名称
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
					case 1:switch(pressuint){                                                           //扭矩
						
						     case 0: SetTextValue(1,5,(uint8_t*)"Bar");SetTextFloat(1,7,press,2,0); break;
						     case 1: SetTextValue(1,5,(uint8_t*)"Mpa");SetTextFloat(1,7,press/10,2,0); break; 				
				         case 2: SetTextValue(1,5,(uint8_t*)"Psi");SetTextFloat(1,7,press*14,2,0); break;          
			 
						     
					       }break;
					case 4:switch(ModifyVarStructVar.pressUint){                                       //角度
						
						     case 0: SetTextValue(3,5,(uint8_t*)"Bar");SetTextFloat(3,6,press,2,0); break;
						     case 1: SetTextValue(3,5,(uint8_t*)"Mpa");SetTextFloat(3,6,press/10,2,0); break; 				
				         case 2: SetTextValue(3,5,(uint8_t*)"Psi");SetTextFloat(3,6,press*14,2,0); break;          
			 
						     
					     }break;	
						
				 case 3:switch(ModifyVarStructVar.pressUint){                                        //档位
						
						     case 0: SetTextValue(4,4,(uint8_t*)"Bar");SetTextFloat(4,6,press,2,0); break;
						     case 1: SetTextValue(4,4,(uint8_t*)"Mpa");SetTextFloat(4,6,press/10,2,0); break; 				
				         case 2: SetTextValue(4,4,(uint8_t*)"Psi");SetTextFloat(4,6,press*14,2,0); break;          
			 
						     
					     }break;		
	      case 5:switch(ModifyVarStructVar.pressUint){                                        //传感器
						
						     case 0: SetTextValue(5,6,(uint8_t*)"Bar");SetTextFloat(5,7,press,2,0); break;
						     case 1: SetTextValue(5,6,(uint8_t*)"Mpa");SetTextFloat(5,7,press/10,2,0); break; 				
				         case 2: SetTextValue(5,6,(uint8_t*)"Psi");SetTextFloat(5,7,press*14,2,0); break;          
			     
					     }break;	
			}	
	
	
	
	}










