#ifndef  _SCREENCORE_H_
#define  _SCREENCORE_H_


//#include "includes.h"


#include "stm32f10x.h"
#include "pclink.h"
#include "screenshow.h"
#include "time.h"

void RecordDataFuc(SysMemoryPara* pSysMemoryParaVar);
uint32_t RandomFun(uint32_t data,uint16_t seed);
uint32_t  setBoltDiameterValVarFlag (uint8_t chart,uint8_t name,uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data);
char* ModifyTorqueUnit(uint8_t Unit,char pUnit[],uint32_t*DestNum,uint32_t SourNum);
char* ModifyPressUnit(uint8_t pressUnit,char*pPressUnit,float*DestNum,float SourNum);
float getPressValue(uint32_t factor,uint32_t torquevalue);
uint32_t getOutData(float press);
void setLangChartFlag(uint8_t lang,uint8_t chart,uint8_t*pLang,uint8_t*pChart);
void setYearValVarFlag(uint16_t* year);
void setMonthValVarFlag(uint8_t* month);
void setDayValVarFlag(uint8_t* date);
void setHourValVarFlag(uint8_t* hour);
void setMinuteValVarFlag(uint8_t* min);
void setSecondValVarFlag(uint8_t* sec);
void ShowProductType(char*pName,uint8_t Memu);
void ShowMaxTorque(uint8_t Memu,uint32_t maxtor);
float setTargetTorqueValVarFlag(uint8_t TorqueUint,uint32_t *targetTorVal);
void showPress(uint8_t memu,uint8_t pressuint,float num);
//uint32_t  setBoltGradeValVarFlag (uint8_t chart,uint8_t name,uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data) ;
//uint32_t  setBoltGradeValVarFlag (uint8_t chart,uint8_t name,uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data) ;
uint32_t  setSensorPresetTorValVarFlag(uint8_t Unit,uint32_t* presetvalue);



uint32_t  setBoltDiameterValVarFlag1 (uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data); 
uint32_t  setBoltGradeValVarFlag (uint8_t*GardeNum,uint8_t*DiamNum,TorquePattern Product[],BoltGardeDiaArr*Data) ;

#endif





