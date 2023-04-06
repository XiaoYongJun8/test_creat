#ifndef  _SCREENSHOW_H_
#define  _SCREENSHOW_H_


//#include "includes.h"
#include "stm32f10x.h"


/******* ************菜单一变量标号***********************/
#define     YearValVarFlag             1        
#define     MonthValVarFlag            2
#define     DayValVarFlag             3
#define     HourValVarFlag             4
#define     MinuteValVarFlag           5
#define     SecondValVarFlag           6
#define     UsageTimesValVarFlag       7    //不需要通过按键来调节，
#define     LanguageValVarFlag         8   //调整中英文 ，1对应英文，(调用英文显示函数) ，2对于中文(调用中文显示函数)    
#define     ChartStandardValVarFlag    9  






/******* ************菜单二变量标号****************************/
#define     TorqueStandValVarFlge        10            //产品标准  50个左右   重复
#define     TorqueTypeValVarFlag         11         // 产品类型    2个   重复
#define     MaxTorqueValVarFlag          12        //最大扭矩值    不需要通过按键来控制，根据产品的型号，自动来对应一个1个最大值
#define     MaxTorqueUintVarFlag      31         //最大扭矩单位   //2中单位N.M  ft.lbs

#define     TargetTorqueValVarFlag        13       //目标扭矩值   //通过按键来设置   重复
#define     TargetTorqueUnitVarFlag   14       //目标扭矩单位      //通过按键来设置
#define     TorquePressUnitVarFlag         15 //扭矩单位              //重复    //Bar,Mpa,Psi,Kg.m四种模式，提供换算表



/******* ************菜单三变量标号***********************/

#define    BoltDiameterValVarFlag             16  //螺栓直径
#define    BoltGardeValVarFlag                17   //螺旋等级
#define    BoltTargetTorqueValVarFlag    18   //螺栓目标扭矩值
#define    BoltTargetTorqueUintVarFlag    19    //螺栓目标扭矩单位 
#define    BoltTypeVareFlag               20   //下调扭矩


/********************菜单四变量标号*************************/

#define     AngleStandvalVarFlag       21    //产品标准
#define     AngleTypeValVarFlag         22    //产品类型
#define     AnglePresetTorValVarFlag        23   //
#define     AnglePresetTorUintFlag     41   //
#define     TarGetAngleValVarFlag     24  //目标角度
#define     AngleUintVarFlag       25  //角度单位

/**********************菜单五变量标号**************************/
#define     GearStandValVarFlag             26   //产品标准
#define     GearTypeValVarFlag            27   //产品类型
#define     MaxGearValVarFlag             28    //最大次轮
#define     TargetGearValVarFlag          29    //目标次轮
#define     GearUintVarFlag            30    //装置单位
#define    GearPressUintFlag              32
#define    GearTargetTorValFlag          45
#define     GearTargetTorUintValFlag    46

/**********************   菜单六变量标号                   **********************/

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

	
	uint32_t  MaxtorVal_TorMode;        //最大扭矩值

	uint32_t  TartorVal_TorMode;        //目标扭矩值


	
	uint8_t garde;
	uint8_t diameter;
	uint8_t garde_M;
	uint8_t diameter_M;
	uint8_t BoltGardeArr[12];
	uint8_t BoltDiameterArr[10];
	uint8_t BoltGardeArr_M[12];
	uint8_t BoltDiameterArr_M[10];
	
	
	

	uint32_t TartorVal_BoltMode ;
	
	
	uint32_t  presetTor_AngMode;   //角度预设扭矩值

  uint16_t  Angle;                  //角度值
	
	
  uint8_t   gear;                       //挡位
	uint32_t  gearpress;                  //挡位对应的压力
	uint32_t  geartor;                    //挡位对应的扭矩值





 uint32_t presettor_sensor;             //预设扭矩值

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



