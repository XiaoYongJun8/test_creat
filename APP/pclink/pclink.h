#ifndef     _PCLINK_H_
#define     _PCLINK_H_


#include "stm32f10x.h"
#include "rs485.h"
#include "screenshow.h"


typedef  struct
{
	
	
	uint8_t  ProductType[10];     //��Ʒ����
	uint32_t Factor;              //��Ʒϵ��
  uint8_t     garde_Imp;            
  uint8_t     diameter_Imp;
  uint8_t     garde_Metric;            
  uint8_t     diameter_Metric;	
	uint32_t    SensorTor; 
	}TorquePattern;


typedef struct{
	
	
	uint8_t     gear;
	uint32_t     gearPress;
	
	
	
}GearPattern;






typedef struct
{

 uint8_t BoltGardeArr_I[20][12];
 uint8_t BoltDiaArr_I[20][10];
	
 uint8_t BoltGardeArr_M[20][12];
 uint8_t BoltDiaArr_M[20][10];

 uint32_t   Val_I[20][10];
 uint32_t   Val_M[20][10];	

}BoltGardeDiaArr;




typedef struct{
	
	
	uint8_t  ProductType[10];     //��Ʒ����
	uint32_t Tarque;              //��Ʒϵ��
	
}SensorStruct;




typedef   enum
{

    productMem = 1,          //�����Ʒ��־λ
	  BoltStructMem = 2,           //������˨���Ա�־λ
    appearanceNumberMem =3,     //�����豸���Ʊ�ű�־
	  UserEquipNameMem = 4,        //�����豸����
	  UserEquipNumberMem = 5,      //�豸���
	  UserNameMem = 6,             //������Ա����
	  UsingTimesMem = 7,           //ʹ�ô���
	  PassWordMem =8 ,             //�豸����
	  AngleMemMem =9,             
	  GearMem = 10,
	  SensorMem = 11,
	  ToolLockMem = 12,
	  ScreenMem = 13,
	  readBoltMem = 14,
	  SysParaMem = 15, 
	//  PressMem = 16,
	 
	 
}MemoryFlag;

typedef struct
{


uint32_t   Val_I[20][10];
uint32_t   Val_M[20][10];

}TorqueValStruct;


void setTime(uint16_t year,uint8_t month,uint8_t day,uint8_t hour,uint8_t minute,uint8_t sec);





extern TorquePattern  TorquePatternVar[50];

extern uint8_t RecordBoltPos[40] ;                 //��¼��Ʒ��λ��

extern BoltGardeDiaArr BoltGardeDiaArrVar ;         //������˨ֱ���ȼ��Ľṹ��




void getProduct(TorquePattern Product[],uint16_t kind,uint8_t* pBuffer);
void FlashWriteTorquePattern(TorquePattern* wdata,uint32_t addr,uint8_t kind);
void CompareSaveTorquePattern(TorquePattern* Src,uint32_t addr,uint16_t kind);
void FlashGetTorquePattern(TorquePattern* rdata,uint32_t addr,uint16_t kind);


void  GetBoltStruct(uint8_t* pBuff,TorquePattern Product[],BoltGardeDiaArr*Data,uint8_t Pos);
void  SaveBoltGardeMeterArr(TorquePattern Product[],BoltGardeDiaArr*Data,uint32_t addr,uint8_t Pos);
void  ReadBoltGardeMeterArr(TorquePattern Product[],BoltGardeDiaArr*Data,uint32_t addr,uint8_t Pos);
uint8_t  CompareBoltName(TorquePattern* rdata,uint8_t* pBuff,uint16_t count);





#define PTR2U16(PTR) ((((uint8_t *)(PTR))[0]<<8)|((uint8_t *)(PTR))[1])  //�ӻ�����ȡ16λ����
#define PTR2U32(PTR) ((((uint8_t *)(PTR))[0]<<24)|(((uint8_t *)(PTR))[1]<<16)|(((uint8_t *)(PTR))[2]<<8)|((uint8_t *)(PTR))[3])  //�ӻ�����ȡ32λ����







void FlashGetRecord(u8* record,uint32_t addr,uint8_t Pos);










void ToolsUnlock(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len);
void setPassWord(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len);
void setUsingTimes(uint8_t*pSrc,upComputerStruct*pDest);
void setUserName(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len);
void setUserEquipNumber(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len);
void setUserEquipName(uint8_t*pSrc, upComputerStruct*pDest,uint16_t len);
void setAppearanceNumber(uint8_t*pSrc,upComputerStruct*pDest,uint16_t len);
void FlashReadupComputerStruct(upComputerStruct* rdata,uint32_t addr);
void FlashWriteupComputerStruct(upComputerStruct* wdata,uint32_t addr);
void getAngle(uint16_t* angle,uint8_t buf[]);
extern uint16_t MaxAngle;

extern uint8_t GearKind;
extern GearPattern GearPatternVar[70];
void getGear(GearPattern gear[],uint8_t gearkind,uint8_t buf[]);
void FlashWriteGear(GearPattern wdata[],uint8_t gearkind,uint32_t addr);
void FlashReadGear(GearPattern rdata[],uint8_t gearkind,uint32_t addr);


void  GetSensor(uint8_t* pBuff,TorquePattern Product[],uint32_t kind);



void FlashWriteScreenVar(ModifyVarStruct* wdata,uint32_t addr);
void FlashReadScreenVar(ModifyVarStruct* rdata,uint32_t addr);






#endif




