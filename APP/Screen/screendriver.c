#include "screendriver.h"

#include "dac8771.h"



KeyMode KeyModeVar = {0,0,1};
uint8_t PressMem = 0;

/**************************************************************

*  \brief      ���õ�ǰ����
*  \param  screen_id ����ID

***************************************************************/



void SetScreen(uint16_t screen_id)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x00);
    TX_16(screen_id);
    END_CMD();
}


/****************************************************************

*  \brief     �����ı�ֵ
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  str �ı�ֵ
******************************************************************/


void SetTextValue(uint16_t screen_id,uint16_t control_id,uint8_t *str)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x10);
    TX_16(screen_id);
    TX_16(control_id);
    SendStrings(str);
    END_CMD();
}

#define   FIRMWARE_VER   1000

#if FIRMWARE_VER>=908
/*! 
*  \brief     �����ı�Ϊ����ֵ��Ҫ��FIRMWARE_VER>=908
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  value �ı���ֵ
*  \param  sign 0-�޷��ţ�1-�з���
*  \param  fill_zero ����λ��������ʱ��ಹ��
*/
void SetTextInt32(uint16_t screen_id,uint16_t control_id,uint32_t value,uint8_t sign,uint8_t fill_zero)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x07);
    TX_16(screen_id);
    TX_16(control_id);
    TX_8(sign?0X01:0X00);
    TX_8((fill_zero&0x0f)|0x80);
    TX_32(value);
    END_CMD();
}
/*! 
*  \brief     �����ı������ȸ���ֵ��Ҫ��FIRMWARE_VER>=908   
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  value �ı���ֵ
*  \param  precision С��λ��
*  \param  show_zeros Ϊ1ʱ����ʾĩβ0
*/
void SetTextFloat(uint16_t screen_id,uint16_t control_id,float value,uint8_t precision,uint8_t show_zeros)
{
	uint8_t i = 0;

	BEGIN_CMD();
	TX_8(0xB1);
	TX_8(0x07);
	TX_16(screen_id);
	TX_16(control_id);
	TX_8(0x02);
	TX_8((precision&0x0f)|(show_zeros?0x80:0x00));
	
	for (i=0;i<4;++i)
	{
	 //��Ҫ���ִ�С��
#if(0)
		TX_8(((uint8_t *)&value)[i]);
#else
		TX_8(((uint8_t *)&value)[3-i]);
#endif
	}
	END_CMD();
}
#endif



/*! 
*  \brief     ���ÿؼ�ǰ��ɫ
* \details  ֧�ֿؼ���������
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  color ǰ��ɫ
*/
void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x19);
    TX_16(screen_id);
    TX_16(control_id);
    TX_16(color);
    END_CMD();
}



#if FIRMWARE_VER>=921
/*! 
*  \brief     ����������
*  \param  ui_lang �û���������0~9
*  \param  sys_lang ϵͳ��������-0���ģ�1Ӣ��
*/
void SetLanguage(uint8_t ui_lang,uint8_t sys_lang)
{
    uint8_t lang = ui_lang;
    if(sys_lang)    lang |= 0x80;

    BEGIN_CMD();
    TX_8(0xC1);
    TX_8(lang);
    TX_8(0xC1+lang);//У�飬��ֹ�����޸�����
    END_CMD();
}
#endif




/*! 
*  \brief      ����ѡ��ؼ�
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  item ��ǰѡ��
*/
void SetflashTime(uint16_t screen_id,uint16_t control_id,uint16_t delaynms)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0x15);
    TX_16(screen_id);
    TX_16(control_id);
    TX_16(delaynms);
    END_CMD();
}


#if FIRMWARE_VER>=921
/*! 
*  \brief     ��ʼ����ؼ���ֵ��FLASH
*  \param  version ���ݰ汾�ţ�������ָ������16λΪ���汾�ţ���16λΪ�ΰ汾��
*  \param  address �������û��洢���Ĵ�ŵ�ַ��ע���ֹ��ַ�ص�����ͻ
*/
void FlashBeginSaveControl(uint32_t version,uint32_t address)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0xAA);
    TX_32(version);
    TX_32(address);
}

/*! 
*  \brief     ����ĳ���ؼ�����ֵ��FLASH
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*/
void FlashSaveControl(uint16_t screen_id,uint16_t control_id)
{
    TX_16(screen_id);
    TX_16(control_id);
}
/*! 
*  \brief     ����ĳ���ؼ�����ֵ��FLASH
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*/
void FlashEndSaveControl()
{
    END_CMD();
}
/*! 
*  \brief     ��FLASH�лָ��ؼ�����
*  \param  version ���ݰ汾�ţ����汾�ű�����洢ʱһ�£���������ʧ��
*  \param  address �������û��洢���Ĵ�ŵ�ַ
*/
void FlashRestoreControl(uint32_t version,uint32_t address)
{
    BEGIN_CMD();
    TX_8(0xB1);
    TX_8(0xAB);
    TX_32(version);
    TX_32(address);
    END_CMD();
}

#endif


/*! 
*  \brief   ����������
*  \time  time ����ʱ��(���뵥λ)
*/
void SetBuzzer(uint8_t time)
{
    BEGIN_CMD();
    TX_8(0x61);
    TX_8(time);
    END_CMD();
}





//static uint8_t      PictureInit = 1;



void MemuOne(void)
{


static	uint8_t i = 1;

	uint8_t   zhowen[10] = {0xD6,0xD0,0xCE,0xC4};
//	uint8_t   yinwen[10] = {0xD3,0xA2,0xCE,0xC4};
	
	uint8_t   gongzhi[10] = {0xB9,0xAB,0xD6,0xC6,0x00};
	
	uint8_t   yinzhi[10] = {0xD3,0xA2,0xD6,0xC6};
	
	 OSTimeDly(25);
	
		SetScreen(0);
	

  ModifyVarStructVar.WorkMode  = 0;

	   if(ModifyVarStructVar.Language == 0)
		  {
			  SetTextValue(0,1,(uint8_t*)"English");
				 if(ModifyVarStructVar.ChartType == 0)
				  {
					 SetTextValue(0,2,(uint8_t*)"Imperial");
					}
					 if(ModifyVarStructVar.ChartType == 1)
					  {
						 SetTextValue(0,2,(uint8_t*)"Metric");
						}
						SetLanguage(0,0);
			}
			
			if(ModifyVarStructVar.Language == 1)
		  {
				
			  SetTextValue(0,1,zhowen);
				 if(ModifyVarStructVar.ChartType == 0)
				  {
					 SetTextValue(0,2, yinzhi);
					}
					 if(ModifyVarStructVar.ChartType == 1)
					  {
							
							 SetTextValue(0,2,gongzhi);
					 
						}
						SetLanguage(1,1);
			}
			

	 SetTextInt32(0,9,upComputerStructVar.UsingTime,0,0);        
	
	

	  for(i=1;i<9;i++)
	   {
	      SetControlForeColor(0,i, COLORFIRST);
     }
	 
   
	 
	 KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;

		 

 
	
}



void MemuOneOptionOne(void)
{
	
int i = 0;
	

//ѡ���һҳ���ѡ��1 ()

      SetScreen(0);
	  SetflashTime(0,1,0);
	 	
	
 for(i=1;i<9;i++)
	{
		if(i==1)SetControlForeColor(0,i, COLORLAST);
	    else SetControlForeColor(0,i, COLORFIRST);

  }

	 KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	
	
	
	 if(KeyModeVar.Mode==1)
	  {
		KeyModeVar.Mode = 0;
		// Memory = ScreenMem;
	 }
	
	
}


void MemuOneOptionTwo(void)
{
	
int i = 0;
	

//ѡ���һҳ���ѡ���
  SetScreen(0);
	

	  
 SetflashTime(0,2,0);

	 
for(i=1;i<9;i++)
	{
		if(i==2)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);

  }
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 //Memory = ScreenMem;
		}
}





void MemuOneOptionThree(void)
{
int i = 0;
//ѡ���һҳ���ѡ����

	SetScreen(0);
		
	
	  
SetflashTime(0,3,0);

	
	
for(i=1;i<9;i++)
	{
		if(i==3)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);

  }
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;
}




void MemuOneOptionFour(void)
{
	
	
	
        int i = 0;
//ѡ���һҳ���ѡ��4
	

	  
			 SetflashTime(0,4,0);

	 
SetScreen(0);

for(i=1;i<9;i++)
	{
		if(i==4)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);

  }
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;

}



void MemuOneOptionFive(void)
{
	
	
       int i = 0;
//ѡ���һҳ���ѡ��5
	


      	SetScreen(0);
		
	  
			 SetflashTime(0,5,0);

	
	
for(i=1;i<9;i++)
	{
		if(i==5)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);

  }
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;

}

void MemuOneOptionSix(void)
{
int i = 0;
//ѡ���һҳ���ѡ��6

           SetScreen(0);
		
	 
	  
			 SetflashTime(0,6,0);

	 
for(i=1;i<9;i++)
	{
		if(i==6)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);

  }
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;

}


void MemuOneOptionSeven(void)
{
int i = 0;
//ѡ���һҳ���ѡ��7

       SetScreen(0);

	  
			 SetflashTime(0,7,0);

	 
for(i=1;i<9;i++)
	{
		if(i==7)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);

  }
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;

}


void MemuOneOptionEight(void)
{
int i = 0;
//ѡ���һҳ���ѡ��8

       SetScreen(0);
			 SetflashTime(0,8,0);

for(i=1;i<9;i++)
	{
		if(i==8)SetControlForeColor(0,i, COLORLAST);
	  else SetControlForeColor(0,i, COLORFIRST);
  }
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;

}





void EnterMemuOneOptionOne(void)
{ 
	
	

	
	SetScreen(0);
	
	  
 SetflashTime(0,1,DELAYNMS);
			 
	
	 

 

if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = LanguageValVarFlag ;                           //�л���Ӣ��


}

void EnterMemuOneOptionTwo(void)
{
	

  //�����һҳ���ѡ��2

	  SetScreen(0);
    

	 SetflashTime(0,2,DELAYNMS);
			 


if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = ChartStandardValVarFlag;   //�л���ĸ�Ĺ��ƺ�Ӣ��                        
                   

}



void EnterMemuOneOptionThree(void)
{
		

	  SetScreen(0);
   
	

			 SetflashTime(0,3,DELAYNMS);


 
	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = YearValVarFlag;                              //�޸����
 
}



void EnterMemuOneOptionFour(void)
{

	
	  SetScreen(0);
   	

	  
			 SetflashTime(0,4,DELAYNMS);
	


 

 if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = MonthValVarFlag  ;                  //�޸��·�
 
}



void EnterMemuOneOptionFive(void)
{	
	

	
	  SetScreen(0);
   

	 SetflashTime(0,5,DELAYNMS);



if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = DayValVarFlag ;                      //�޸���  
 
}


void EnterMemuOneOptionSix(void)
{
	
	

	  SetScreen(0);
    	

			 SetflashTime(0,6,DELAYNMS);


  
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = HourValVarFlag;                      //�޸�Сʱ
	
}



void EnterMemuOneOptionSeven(void)
{


	  SetScreen(0);
  	

			 SetflashTime(0,7,DELAYNMS);


	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
{
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
}

	
 KeyModeVar.ModifyVarFlag = MinuteValVarFlag ;                      //�޸ķ��� 
 
}


void EnterMemuOneOptionEight(void)
{
	
	
   SetScreen(0);
  

			 SetflashTime(0,8,DELAYNMS);

 
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = SecondValVarFlag;                      //�޸�����  
}












void MemuTwo(void)
{
	
 uint8_t i = 1;
	
	
	
ModifyVarStructVar.WorkMode = 1;
OSTimeDly(25);
		 SetScreen(1);

	
		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
			 SetTextInt32(1,3,ModifyVarStructVar.TartorVal_TorMode,0,0); 
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
		 
		  	
		 
		  
	
	 if(ModifyVarStructVar.fabricName == 0)
			  {	
					ModifyVarStructVar.fabricName = 1;
				}	
	    	
		   SetTextValue(1,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����	
		   ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor* MAXMPA;	
		
		 
	 
	  if(ModifyVarStructVar.TorqueUint == 0)
		 {
		   	  SetTextValue(1,2,(uint8_t*)"N.m");
			    SetTextInt32(1,6, ModifyVarStructVar.MaxtorVal_TorMode,0,0);
		 }
		 else{
		      SetTextValue(1,2,(uint8_t*)"ft.lbs");
			    SetTextInt32(1,6, ROUND_TO_UINT32(ModifyVarStructVar.MaxtorVal_TorMode/1.3549),0,0);
		 }

   if(ResetPress.DacOutData_T==0){
		 
     ResetPress.SetPress_Torque = 60000.0;
		 ResetPress.DacOutData_T =  getOutData(ResetPress.SetPress_Torque); 
		 PressMem = 1;
		 Memory = ScreenMem;

	   }		 
		 
		
	
	   for(i=1;i<6;i++)
	   {
			
	   SetControlForeColor(1,i, COLORFIRST);
     }
	 

	 KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;
	   


}


void MemuTwoOptionOne(void)                //ѡ���ƽ�ͺŵ�
{
	int i = 0;



   SetScreen(1);
	
	  
	SetflashTime(1,1,0);

	 
for(i=1;i<6;i++)
	{
		if(i==1)SetControlForeColor(1,i, COLORLAST);
	   else SetControlForeColor(1,i, COLORFIRST);

  }
	 KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	
	
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
	


}


void MemuTwoOptionTwo(void)
{
   int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
    SetScreen(1);
	
	  
		SetflashTime(1,2,0);

	 
for(i=1;i<6;i++)
	{
		if(i==2)SetControlForeColor(1,i, COLORLAST);
	  else SetControlForeColor(1,i, COLORFIRST);

  }
	
}



void MemuTwoOptionThree(void)                 //Ŀ��Ť��ֵ
{

	int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	if(KeyModeVar.Mode==1)
	  {
			 niujupress = 1;
		   KeyModeVar.Mode = 0;
			 PressMem = 1;
			 Memory = ScreenMem;
			
		}
	
     SetScreen(1);
	   SetflashTime(1,3,0);

for(i=1;i<6;i++)
	{
		if(i==3)SetControlForeColor(1,i, COLORLAST);
	  else SetControlForeColor(1,i, COLORFIRST);

  }


	
}


void MemuTwoOptionFour(void)
{

  int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}

       SetScreen(1);
	
	  
			 SetflashTime(1,4,0);

	 
for(i=1;i<6;i++)
	{
		if(i==4)SetControlForeColor(1,i, COLORLAST);
	  else SetControlForeColor(1,i, COLORFIRST);

  }

}


void MemuTwoOptionFive(void)
{

  int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}

//ѡ���һҳ���ѡ���
        SetScreen(1);
	
	  
			 SetflashTime(1,5,0);

	
for(i=1;i<6;i++)
	{
		if(i==5)SetControlForeColor(1,i, COLORLAST);
	  else SetControlForeColor(1,i, COLORFIRST);

  }

}






void EnterMemuTwoOptionOne(void)
{
    
    SetScreen(1);

	 SetflashTime(1,1,DELAYNMS);
			
	 
 
	
	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = TorqueTypeValVarFlag ;                    //�޸�Ť��ģʽ�µİ����ͺ�
                                 
}


void EnterMemuTwoOptionTwo(void)                     
{

   SetScreen(1);
	 
   

	 SetflashTime(1,2,DELAYNMS);
		


	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = MaxTorqueUintVarFlag ;                            //�޸�Ť��ģʽ�����Ť��ֵ��λ
}


void EnterMemuTwoOptionThree(void)
{
	
	


   SetScreen(1);
 	
	
			 SetflashTime(1,3,DELAYNMS);
			

	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }
 

	
 KeyModeVar.ModifyVarFlag = TargetTorqueValVarFlag ;                           //�޸�Ť��ģʽ��Ŀ��Ť��ֵ
 
	
}


void EnterMemuTwoOptionFour(void)
{	
	

	 
   SetScreen(1);
   

	 SetflashTime(1,4,DELAYNMS);
			

 

if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = TargetTorqueUnitVarFlag;                                 //�޸�Ť��ģʽ��Ŀ��Ť��ֵ��λ
	
	
}


void EnterMemuTwoOptionFive(void)
{
	
	
	
   SetScreen(1);
 	

			 SetflashTime(1,5,DELAYNMS);
			 
	
 

if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =TorquePressUnitVarFlag	 ;                                        //�޸�Ť��ģʽ��ѹ����λ

}









void MemuThree(void)
{
  static  int i = 1;
	


	 ModifyVarStructVar.WorkMode  = 2;
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;
	
    OSTimeDly(25);
			  SetScreen(2);
 
 
		if(ModifyVarStructVar.fabricName == 0) ModifyVarStructVar.fabricName = 1;
		 SetTextValue(2,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ���� 		
	 
	
	if(TorquePatternVar[ModifyVarStructVar.fabricName-1].diameter_Imp==0||TorquePatternVar[ModifyVarStructVar.fabricName-1].garde_Imp==0)
	 {
	   SetTextValue(2,2,(uint8_t*)" ");
	   SetTextValue(2,3,(uint8_t*)" ");
		 SetTextInt32(2,5,0,0,0);
	 } 
	 else if(ModifyVarStructVar.ChartType == 0){
	 
		 
		 SetTextValue(2,2,(uint8_t*)ModifyVarStructVar.BoltDiameterArr);
	   SetTextValue(2,3,(uint8_t*)ModifyVarStructVar.BoltGardeArr);
		 
		}
	 
	  if(ModifyVarStructVar.TorqueUint==0)
		 {
			 
			SetTextInt32(2,5,	 ModifyVarStructVar.TartorVal_BoltMode,0,0);
		  SetTextValue(2,4,(uint8_t*)"N.m");
		 }else{
		 	SetTextInt32(2,5,	 ROUND_TO_UINT32(ModifyVarStructVar.TartorVal_BoltMode/1.3549),0,0);
		  SetTextValue(2,4,(uint8_t*)"ft.lbs");
		 }
	 		 
	 
	 if(TorquePatternVar[ModifyVarStructVar.fabricName-1].diameter_Metric==0||TorquePatternVar[ModifyVarStructVar.fabricName-1].garde_Metric==0)
	  {
		 SetTextValue(2,2,(uint8_t*)" ");
	   SetTextValue(2,3,(uint8_t*)" ");
		 SetTextInt32(2,5,0,0,0);
		}
		
		else if(ModifyVarStructVar.ChartType == 1){
	
		 SetTextValue(2,2,(uint8_t*)ModifyVarStructVar.BoltDiameterArr_M);
	   SetTextValue(2,3,(uint8_t*)ModifyVarStructVar.BoltGardeArr_M);
	 
		}
		
		if(ResetPress.SetPress_Bolt==0){
			
		   ResetPress.SetPress_Bolt = 20000;
		   ResetPress.DacOutData_G =  getOutData(ResetPress.SetPress_Bolt);
			 PressMem = 1;	
			 Memory = ScreenMem;
			
		  }
		
			
	
	   for(i=1;i<5;i++)
	   {
	      SetControlForeColor(2,i, COLORFIRST);
     
	   }
	 


}


void MemuThreeOptionOne(void)
{

  int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
	
	
    SetScreen(2);

	  
		SetflashTime(2,1,0);

	 
for(i=1;i<5;i++)
	{
		if(i==1)SetControlForeColor(2,i, COLORLAST);
	  else SetControlForeColor(2,i, COLORFIRST);

  }


}


void MemuThreeOptionTwo(void)
{


  int i = 0;
	 
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
			 niujupress = 1;
		   KeyModeVar.Mode = 0;
			 PressMem = 1;
			 Memory = ScreenMem;
		}
	
	
 SetScreen(2);
	
			 SetflashTime(2,2,0);

	 
for(i=1;i<5;i++)
	{
		if(i==2)SetControlForeColor(2,i, COLORLAST);
	  else SetControlForeColor(2,i, COLORFIRST);

  }
	
	


	

}


void MemuThreeOptionThree(void)
{

  int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
			 niujupress = 1; 
		   KeyModeVar.Mode = 0;
			 PressMem = 1;
			 Memory = ScreenMem;
		}
	
     SetScreen(2);
		SetflashTime(2,3,0);
	 
for(i=1;i<5;i++)
	{
		if(i==3)SetControlForeColor(2,i, COLORLAST);
	  else SetControlForeColor(2,i, COLORFIRST);
  }
	

	
}


void MemuThreeOptionFour(void)
{


  int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(2);
	
	  
			 SetflashTime(2,4,0);

	 
for(i=1;i<5;i++)
	{
		if(i==4)SetControlForeColor(2,i, COLORLAST);
	  else SetControlForeColor(2,i, COLORFIRST);

  }
	
	

	
	
}






void EnterMemuThreeOptionOne(void)
{
	
	

	
	 SetScreen(2);
  

	SetflashTime(2,1,DELAYNMS);
	
	
	

	
	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =  BoltTypeVareFlag;                      //�޸���˨ģʽ�µ��ͺ�
	
	
	
	

}


void EnterMemuThreeOptionTwo(void)
{


	
	 SetScreen(2);
  	

			 SetflashTime(2,2,DELAYNMS);

	 
	
 
	
	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }
 
  
	
 KeyModeVar.ModifyVarFlag =   BoltDiameterValVarFlag  ;                  //  �޸���˨ģʽ�µĲ�Ʒֱ�� 


 
}


void EnterMemuThreeOptionThree(void)
{

	
	SetScreen(2);
  	

			 SetflashTime(2,3,DELAYNMS);
			 




 if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 
 KeyModeVar.ModifyVarFlag = BoltGardeValVarFlag ;                  //�޸���˨ģʽ�µĵȼ�
 
   
}


void EnterMemuThreeOptionFour(void)
{
	

   SetScreen(2);
   
	
	SetflashTime(2,4,DELAYNMS);

	 

	
	
  
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =  BoltTargetTorqueUintVarFlag ;                  //�޸���˨ģʽ�µ�Ŀ��Ť�ص�λ
	
}



void MemuFour(void)
{
   int j = 0;
	static uint8_t  i = 1;

	 ModifyVarStructVar.WorkMode  = 4;
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;
	
	 SetScreen(3);
OSTimeDly(25);
	 

	  SetTextInt32(3,4,ModifyVarStructVar.Angle,0,0);              
		
	 	switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(3,5,(uint8_t*)"Bar");break;
				case 1: SetTextValue(3,5,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(3,5,(uint8_t*)"Psi");break;
			 }
	   
	   
	
	

	if(ModifyVarStructVar.fabricName==0) ModifyVarStructVar.fabricName =1;
	 ModifyVarStructVar.MaxtorVal_TorMode = TorquePatternVar[ModifyVarStructVar.fabricName-1].Factor* MAXMPA;
		SetTextValue(3,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ���� 		 
		
	
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

	
//     if( ResetPress.SetPress_Angle==0){
//       Memory = ScreenMem;
//       PressMem = 1;
//		 }			 
     ResetPress.SetPress_Angle= 60000.0;
		 ResetPress.DacOutData_A =  getOutData(ResetPress.SetPress_Angle); 

	   	
	
	
	for(j = 0;j<7;j++)
	 {
	   for(i=1;i<6;i++)
	   {
			 if( j == 3)
	   SetControlForeColor(j,i, COLORFIRST);
     }
	 }
	 


	

	
	
}


void MemuFourOptionOne(void)
{

	int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(3);

	  
			 SetflashTime(3,1,0);

	 
 for(i=1;i<6;i++)
	{
		if(i==1)SetControlForeColor(3,i, COLORLAST);
	  else SetControlForeColor(3,i, COLORFIRST);
  }
	


}

void MemuFourOptionTwo(void)
{

	int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(3);

	  
	SetflashTime(3,2,0);

	 
for(i=1;i<6;i++)
	{
		if(i==2)SetControlForeColor(3,i, COLORLAST);
	  else SetControlForeColor(3,i, COLORFIRST);

  }
}


void MemuFourOptionThree(void)
{

	int i = 0;
	
	
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(3);
	
	  
			 SetflashTime(3,3,0);

	 
for(i=1;i<6;i++)
	{
		if(i==3)SetControlForeColor(3,i, COLORLAST);
	  else SetControlForeColor(3,i, COLORFIRST);

  }
}

void MemuFourOptionFour(void)
{

	int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(3);
	

			 SetflashTime(3,4,0);

	 
for(i=1;i<6;i++)
	{
		if(i==4)SetControlForeColor(3,i, COLORLAST);
	  else SetControlForeColor(3,i, COLORFIRST);

  }
}


void MemuFourOptionFive(void)
{

	int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
  SetScreen(3);
	
	  
			 SetflashTime(3,5,0);

	 
for(i=1;i<6;i++)
	{
		if(i==5)SetControlForeColor(3,i, COLORLAST);
	  else SetControlForeColor(3,i, COLORFIRST);

  }

}




void EnterMemuFourOptionOne(void)
{
	
	
	
	 SetScreen(3);
   
	
	SetflashTime(3,1,DELAYNMS);
			 
	 
	


	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

 
 KeyModeVar.ModifyVarFlag =  AngleTypeValVarFlag   ;                //�޸ĽǶ�ģʽ�µĲ�Ʒ�ͺ�
	
	
	
}

void EnterMemuFourOptionTwo(void)
{
	  	

	 SetScreen(3);
 
	
		SetflashTime(3,2,DELAYNMS);
			 
	

	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	

	

}


void EnterMemuFourOptionThree(void)
{
	

	 SetScreen(3);
   
	
			 SetflashTime(3,3,DELAYNMS);
			 
	 

	
if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = AnglePresetTorUintFlag  ;                   //�޸ĽǶ�ģʽ�µ�Ԥ��Ť�ص�λ

}

void EnterMemuFourOptionFour(void)
{
   
	
	 SetScreen(3);
  	

SetflashTime(3,4,DELAYNMS);
			


	
	
	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	


	
 KeyModeVar.ModifyVarFlag =   TarGetAngleValVarFlag  ;                  //�޸ĽǶ�ģʽ�µ�Ŀ��Ƕ�ֵ

}



void EnterMemuFourOptionFive(void)
{


	 SetScreen(3);
   
	
			 SetflashTime(3,5,DELAYNMS);

	

	
	
	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = AngleUintVarFlag  ;                     //�޸ĽǶ�ģʽ�µ�ѹ����λ
	
	
}



void MemuFive(void)
{



	int i = 1;
	
    ModifyVarStructVar.WorkMode  = 3;
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;
	
	SetScreen(4);
OSTimeDly(25);
	
	   

 

	
	 	switch(ModifyVarStructVar.pressUint)
			 {
				case 0: SetTextValue(4,4,(uint8_t*)"Bar");break;
				case 1: SetTextValue(4,4,(uint8_t*)"Mpa");break; 
			  case 2: SetTextValue(4,4,(uint8_t*)"Psi");break;
			 }
	   

	
	   if(ModifyVarStructVar.gear==0)ModifyVarStructVar.gear = 1;
		 SetTextInt32(4,2,  GearPatternVar[ModifyVarStructVar.gear-1].gear,0,0);
			 
		 if(ModifyVarStructVar.fabricName ==0)ModifyVarStructVar.fabricName = 1;
		 SetTextValue(4,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ���� 
			ModifyVarStructVar.gearpress = GearPatternVar[ModifyVarStructVar.gear-1].gearPress;
			ModifyVarStructVar.geartor =  ROUND_TO_UINT32(TorquePatternVar[ ModifyVarStructVar.fabricName-1].Factor* ModifyVarStructVar.gearpress/10000) ; //Ŀ��Ť��ֵ	 
			 
		 if(ModifyVarStructVar.TorqueUint == 0)
		  {
				 SetTextValue(4,3,(uint8_t*)"N.m");
			   SetTextInt32(4,5,  ModifyVarStructVar.geartor,0,0);
			}
			else
			 {
				 SetTextValue(4,3,(uint8_t*)"ft.lbs");
			   SetTextInt32(4,5, ROUND_TO_UINT32(ModifyVarStructVar.geartor/1.3549),0,0);
			 }
			 
		 if(ResetPress.SetPress_Gear==0){
			
		  ResetPress.SetPress_Gear = ModifyVarStructVar.gearpress*10;
		  ResetPress.DacOutData_G =  getOutData(ResetPress.SetPress_Gear);
			PressMem = 1;	
			Memory = ScreenMem;	
				
		  }
	  

	   for(i=1;i<5;i++)
	   {
			
	   SetControlForeColor(4,i, COLORFIRST);
     }
	

		 
}


void MemuFiveOptionOne(void)
{

	int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(4);
	
	  
	 SetflashTime(4,1,0);

	 
for(i=1;i<5;i++)
	{
		if(i==1)SetControlForeColor(4,i, COLORLAST);
	  else SetControlForeColor(4,i, COLORFIRST);

  }


}

void MemuFiveOptionTwo(void)             //�޸ĵ�λѡ��
{

	int i = 0;
	
  KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
			niujupress = 1;
		   KeyModeVar.Mode = 0;
			 PressMem = 1;
			 Memory = ScreenMem;
		}
 SetScreen(4);
	
	  
			 SetflashTime(4,2,0);

	 
for(i=1;i<5;i++)
	{
		if(i==2)SetControlForeColor(4,i, COLORLAST);
	  else SetControlForeColor(4,i, COLORFIRST);

  }



}


void MemuFiveOptionThree(void)
{

	int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
   SetScreen(4);
	
	  
		SetflashTime(4,3,0);

	 
for(i=1;i<5;i++)
	{
		if(i==3)SetControlForeColor(4,i, COLORLAST);
	  else SetControlForeColor(4,i, COLORFIRST);

  }

}

void MemuFiveOptionFour(void)
{

	int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
 SetScreen(4);
	
	  
			 SetflashTime(4,4,0);

	 
for(i=1;i<5;i++)
	{
		if(i==4)SetControlForeColor(4,i, COLORLAST);
	  else SetControlForeColor(4,i, COLORFIRST);

  }

}




void EnterMemuFiveOptionOne(void)
{
		

		SetScreen(4);
  
	
			 SetflashTime(4,1,DELAYNMS);
	
  

if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = GearTypeValVarFlag   ;                //�޸ĵ�λģʽ�µĲ�Ʒ�ͺ�
	
	
	
}

void EnterMemuFiveOptionTwo(void)
{
	

		SetScreen(4);
  	

			 SetflashTime(4,2,DELAYNMS);

	
 
	
		if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

 KeyModeVar.ModifyVarFlag = TargetGearValVarFlag  ;                   //�޸ĵ�λģʽ�µ�Ŀ�굲λ
	
	
	
	
}


void EnterMemuFiveOptionThree(void)
{
	

	
		SetScreen(4);
 	

			 SetflashTime(4,3,DELAYNMS);

 	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag = GearTargetTorUintValFlag  ;                    //�޸ĵ�λģʽ�µ�Ť�ص�λ
	
	
	
}

void EnterMemuFiveOptionFour(void)
{
 
	
		SetScreen(4);
  

			 SetflashTime(4,4,DELAYNMS);
	

	
		if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =  GearUintVarFlag  ;                  //�޸ĵ�λģʽ�µ�ѹ����λ
	
	
	
	
}








void MemuSix(void)
{


  static uint8_t  i = 1;

	 ModifyVarStructVar.WorkMode  = 5;
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 KeyModeVar.Mode = 0;
	
	     
	OSTimeDly(25);

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
	
	    
	

	    if(ModifyVarStructVar.fabricName==0) ModifyVarStructVar.fabricName  = 1;
		  SetTextValue(5,1,(uint8_t*)TorquePatternVar[ModifyVarStructVar.fabricName-1].ProductType);   //��ʾ��Ʒ����
	  	ModifyVarStructVar.tartor_sensor = TorquePatternVar[ModifyVarStructVar.fabricName-1].SensorTor;
		 
		
		  if(ResetPress.SetPress_Sensor==0){
			
			
		  ResetPress.SetPress_Sensor = setSensorPresetTorValVarFlag(ModifyVarStructVar.TorqueUint, &ModifyVarStructVar.tartor_sensor);
		  ResetPress.DacOutData_S =  getOutData(ResetPress.SetPress_Sensor);
			PressMem = 1;	
			Memory = ScreenMem;	
				
		  }
	
	
	 
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
	

	  for(i=1;i<7;i++)
	   {
	    SetControlForeColor(5,i, COLORFIRST); 
		 }


}




void MemuSixOptionOne(void)
{
  int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
	 SetScreen(5);

	 
			 SetflashTime(5,1,0);


for(i=1;i<7;i++)
	{
		if(i==1)SetControlForeColor(5,i, COLORLAST);
	  else SetControlForeColor(5,i, COLORFIRST);

  }

}

void MemuSixOptionTwo(void)
{
	
int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
					niujupress = 1;
		   KeyModeVar.Mode = 0;
			 PressMem =1;
			 Memory = ScreenMem;
		}
		 SetScreen(5);

			 SetflashTime(5,2,0);

	 
for(i=1;i<7;i++)
	{
		if(i==2)SetControlForeColor(5,i, COLORLAST);
	  else SetControlForeColor(5,i, COLORFIRST);

  }
	

}


void MemuSixOptionThree(void)
{
int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
		 SetScreen(5);
	
	  
		SetflashTime(5,3,0);

	 
for(i=1;i<7;i++)
	{
		if(i==3)SetControlForeColor(5,i, COLORLAST);
	  else SetControlForeColor(5,i, COLORFIRST);

  }

}

void MemuSixOptionFour(void)
{

 int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
		 SetScreen(5);
	
	  
		SetflashTime(5,4,0);

	 
for(i=1;i<7;i++)
	{
		if(i==4)SetControlForeColor(5,i, COLORLAST);
	  else SetControlForeColor(5,i, COLORFIRST);

  }
	


}


void MemuSixOptionFive(void)
{

  int i = 0;
	
   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
	SetScreen(5);
	
	  
			 SetflashTime(5,5,0);

	 
for(i=1;i<7;i++)
	{
		if(i==5)SetControlForeColor(5,i, COLORLAST);
	  else SetControlForeColor(5,i, COLORFIRST);

  }
}

void MemuSixOptionSix(void)
{

  int i = 0;

   KeyModeVar.ModifyVarFlag = 0;
	 KeyModeVar.ModeMutex = 1;
	 if(KeyModeVar.Mode==1)
	  {
		   KeyModeVar.Mode = 0;
			 Memory = ScreenMem;
		}
	SetScreen(5);

	  
			 SetflashTime(5,6,0);

	 
for(i=1;i<7;i++)
	{
		if(i==6)SetControlForeColor(5,i, COLORLAST);
	  else SetControlForeColor(5,i, COLORFIRST);

  }
}




void EnterMemuSixOptionOne(void)
{


		SetScreen(5);
  

	  SetflashTime(5,1,DELAYNMS);
			 

	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =  SensorTypeValVarFlag    ;                    //�޸Ĵ�����ģʽ�µĲ�Ʒ����
  	
}

void EnterMemuSixOptionTwo(void)
{


		SetScreen(5);
  	
	
	  
			 SetflashTime(5,2,DELAYNMS);
			 
	

	 
			if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }


 KeyModeVar.ModifyVarFlag =  SensorPresetTorValVarFlag    ;                    // �޸Ĵ�����ģʽ�µ�Ԥ��Ť��

}


void EnterMemuSixOptionThree(void)
{


	
		SetScreen(5);
   	

			 SetflashTime(5,3,DELAYNMS);


	 

			if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =  SensorPresetTorValVarUintFlag  ;                          // �޸Ĵ�����ģʽ�µ�Ԥ��Ť�ص�λ
	
	
	
}

void EnterMemuSixOptionFour(void)
{
	

	
	SetScreen(5);
  	

			 SetflashTime(5,4,DELAYNMS);


	 
	
	
			if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =  SensorTargetToreValVarFlag     ;                   //�޸Ĵ�����ģʽ�µ�Ŀ��Ť��ֵ
	
	
}


void EnterMemuSixOptionFive(void)
{
	


		SetScreen(5);
   	

			 SetflashTime(5,5,DELAYNMS);


	 
	
			if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
 { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
 }

	
 KeyModeVar.ModifyVarFlag =   SensorTargetToreValVarUintFlag ;                              //�޸Ĵ�����ģʽ�µ�Ŀ��Ť��ֵ��λ
	
	

}

void EnterMemuSixOptionSix(void)
{
   

		SetScreen(5);
    	

			 SetflashTime(5,6,DELAYNMS);

	 
	
	if(KeyModeVar.Mode != KeyModeVar.ModeMutex)
   { 
    KeyModeVar.Mode  = 1;
	  KeyModeVar.ModeMutex = 1;
  }

	
 KeyModeVar.ModifyVarFlag =  SensorPressUintFlag    ;                          //�޸Ĵ�����ģʽ�µ�ѹ����λ
	
	
	
}
















