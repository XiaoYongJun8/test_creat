#ifndef  _SCREENSHOW_H_
#define  _SCREENSHOW_H_


//#include "includes.h"
#include "stm32f10x.h"


/******* ************�˵�һ�������***********************/
#define     YearValVarFlag             1        
#define     MonthValVarFlag            2
#define     DayValVarFlag             3
#define     HourValVarFlag             4
#define     MinuteValVarFlag           5
#define     SecondValVarFlag           6
#define     UsageTimesValVarFlag       7    //����Ҫͨ�����������ڣ�
#define     LanguageValVarFlag         8   //������Ӣ�� ��1��ӦӢ�ģ�(����Ӣ����ʾ����) ��2��������(����������ʾ����)    
#define     ChartStandardValVarFlag    9  






/******* ************�˵����������****************************/
#define     TorqueStandValVarFlge        10            //��Ʒ��׼  50������   �ظ�
#define     TorqueTypeValVarFlag         11         // ��Ʒ����    2��   �ظ�
#define     MaxTorqueValVarFlag          12        //���Ť��ֵ    ����Ҫͨ�����������ƣ����ݲ�Ʒ���ͺţ��Զ�����Ӧһ��1�����ֵ
#define     MaxTorqueUintVarFlag      31         //���Ť�ص�λ   //2�е�λN.M  ft.lbs

#define     TargetTorqueValVarFlag        13       //Ŀ��Ť��ֵ   //ͨ������������   �ظ�
#define     TargetTorqueUnitVarFlag   14       //Ŀ��Ť�ص�λ      //ͨ������������
#define     TorquePressUnitVarFlag         15 //Ť�ص�λ              //�ظ�    //Bar,Mpa,Psi,Kg.m����ģʽ���ṩ�����



/******* ************�˵����������***********************/

#define    BoltDiameterValVarFlag             16  //��˨ֱ��
#define    BoltGardeValVarFlag                17   //�����ȼ�
#define    BoltTargetTorqueValVarFlag    18   //��˨Ŀ��Ť��ֵ
#define    BoltTargetTorqueUintVarFlag    19    //��˨Ŀ��Ť�ص�λ 
#define    BoltTypeVareFlag               20   //�µ�Ť��


/********************�˵��ı������*************************/

#define     AngleStandvalVarFlag       21    //��Ʒ��׼
#define     AngleTypeValVarFlag         22    //��Ʒ����
#define     AnglePresetTorValVarFlag        23   //
#define     AnglePresetTorUintFlag     41   //
#define     TarGetAngleValVarFlag     24  //Ŀ��Ƕ�
#define     AngleUintVarFlag       25  //�Ƕȵ�λ

/**********************�˵���������**************************/
#define     GearStandValVarFlag             26   //��Ʒ��׼
#define     GearTypeValVarFlag            27   //��Ʒ����
#define     MaxGearValVarFlag             28    //������
#define     TargetGearValVarFlag          29    //Ŀ�����
#define     GearUintVarFlag            30    //װ�õ�λ
#define    GearPressUintFlag              32
#define    GearTargetTorValFlag          45
#define     GearTargetTorUintValFlag    46

/**********************   �˵����������                   **********************/

#define    SensorTypeValVarFlag                 33
#define    SensorPresetTorValVarFlag              34   
#define    SensorPresetTorValVarUintFlag           35
#define    SensorTargetToreValVarFlag               36
#define    SensorTargetToreValVarUintFlag               37
#define    SensorPressUintFlag                        38



typedef struct
{

  uint8_t Language;
	uint8_t ChartType;

	uint8_t fabricName;
	uint8_t WorkMode;
	
	uint8_t pressUint;
	
	uint8_t  TorqueUint;

	
	uint32_t  MaxtorVal_TorMode;        //���Ť��ֵ

	uint32_t  TartorVal_TorMode;        //Ŀ��Ť��ֵ


	
	uint8_t garde;
	uint8_t diameter;
	uint8_t garde_M;
	uint8_t diameter_M;
	uint8_t BoltGardeArr[12];
	uint8_t BoltDiameterArr[10];
	uint8_t BoltGardeArr_M[12];
	uint8_t BoltDiameterArr_M[10];
	
	
	

	uint32_t TartorVal_BoltMode ;
	
	
	uint32_t  presetTor_AngMode;   //�Ƕ�Ԥ��Ť��ֵ

  uint16_t  Angle;                  //�Ƕ�ֵ
	
	
  uint8_t   gear;                       //��λ
	uint32_t  gearpress;                  //��λ��Ӧ��ѹ��
	uint32_t  geartor;                    //��λ��Ӧ��Ť��ֵ





 uint32_t presettor_sensor;             //Ԥ��Ť��ֵ

 uint32_t tartor_sensor;




}ModifyVarStruct;

extern ModifyVarStruct ModifyVarStructVar;
extern uint32_t DacOutData;
extern uint32_t DacOutData_M;








typedef struct 
{

uint8_t current;
	
uint8_t memu;
uint8_t enter;
uint8_t up;
uint8_t down;
	

void (*current_operation)();	

} KEY_Table;

extern 	float SetPress ;



extern  uint8_t  func_index ;
extern  uint8_t  func_index ;

extern  void (*current_operation_index)();

extern KEY_Table table[75];


void ModiVarAdd(uint8_t Flag);
void ModiVarDec(uint8_t Flag);
void ModiVarAddWide(uint8_t Flag);
void ModiVarDecWide(uint8_t Flag);

void TaskKeyControl(void* pvData);
void AdjustTorqueMode(void);
void AdjustBoltMode(void);
void AdjustGearMode(void);
void AdjustAngleMode(void);
void AdjustSensorMode(void);
void  AdcGetShow(uint8_t memu,uint8_t pressuint,float press);




#define  MEMUTIME     80
#define  UPTIMES      4
#define  DOWNTIMES    4
#define  ENTERTIMES   5
#define  ADDTIMES     200
#define  DECTIMES     200
#define  ADDRATE      0.01
#define  DECRATE      0.01
#define  MAXMPA       0.625



typedef struct{
	
	
	
float  SetPress_Torque ;  //
float  SetPress_Bolt ;  
float  SetPress_Gear ; 
float  SetPress_Angle ; 
float  SetPress_Sensor ; 

uint16_t DacOutData_T ;
uint16_t DacOutData_B;
uint16_t DacOutData_G ;
uint16_t DacOutData_A ;
uint16_t DacOutData_S;
	
	
	

}ResetPressStruct;



extern ResetPressStruct ResetPress;
extern uint32_t  TorqueUint_C ;






#endif



