#ifndef _iwdg_H
#define _iwdg_H

#include "system.h"
void IWDG_Init(u8 pre,u16 rlr);
void IWDG_FeedDog(void);  //Î¹¹·
void WDC_INIT(void);
void TaskDog(void *pData);

typedef struct{
	
	
	uint8_t      KeyControl;
	uint8_t      Time;
	uint8_t      PcDebug;
	uint8_t      Memory;
	uint8_t      MemoryStart;
	uint8_t      UdiskIn; 
	uint8_t      UdiskOut;
	
	
}TaskDogStrut;



extern TaskDogStrut TaskDogStrutVar ;







#endif







