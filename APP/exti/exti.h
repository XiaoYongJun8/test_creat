#ifndef _EXTI_H_
#define _EXTI_H_

#include "stm32f10x.h"


#define KEYA	(GPIOC->IDR & (1<<7))
#define KEYB	(GPIOC->IDR & (1<<8))
#define KEYC	(GPIOC->IDR & (1<<9))



//extern uint8_t flag1 ;

void Input_Init(void);



#endif





