#ifndef _system_H
#define _system_H


#include "stm32f10x.h"


void RCC_Configuration(void);
void NVIC_Configuration(void);
void InitTarget(void);

extern uint16_t productKind ;
extern uint8_t gearKind;
extern  uint32_t Ordinal ;



#endif
