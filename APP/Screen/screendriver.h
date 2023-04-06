#ifndef _SCREENDRIVER_H_
#define  _SCREENDRIVER_H_



#include "includes.h"
#include "stm32f10x.h"

#define  COLORFIRST       31              
#define  COLORLAST        65504
#define  DELAYNMS         50


#define   FIRMWARE_VER   1000

typedef struct
{

  uint8_t  ModifyVarFlag ;
  uint8_t  Mode;
	uint8_t  ModeMutex;

}KeyMode;


extern KeyMode KeyModeVar ;
extern uint8_t PressMem;


void SetScreen(uint16_t screen_id);
void SetTextValue(uint16_t screen_id,uint16_t control_id,uint8_t *str);
void SetTextInt32(uint16_t screen_id,uint16_t control_id,uint32_t value,uint8_t sign,uint8_t fill_zero);
void SetTextFloat(uint16_t screen_id,uint16_t control_id,float value,uint8_t precision,uint8_t show_zeros);
void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color);
void SetLanguage(uint8_t ui_lang,uint8_t sys_lang);
void SetflashTime(uint16_t screen_id,uint16_t control_id,uint16_t delaynms);
void SetBuzzer(uint8_t time);








void MemuOne(void);


void MemuOneOptionOne(void);
void MemuOneOptionTwo(void);
void MemuOneOptionThree(void);
void MemuOneOptionFour(void);
void MemuOneOptionFive(void);
void MemuOneOptionSix(void);
void MemuOneOptionSeven(void);
void MemuOneOptionEight(void);

void EnterMemuOneOptionOne(void);//修改变量语言
void EnterMemuOneOptionTwo(void);//修改变量标准
void EnterMemuOneOptionThree(void);
void EnterMemuOneOptionFour(void);
void EnterMemuOneOptionFive(void);
void EnterMemuOneOptionSix(void);
void EnterMemuOneOptionSeven(void);
void EnterMemuOneOptionEight(void);









void MemuTwo(void);

void MemuTwoOptionOne(void);
void MemuTwoOptionTwo(void);
void MemuTwoOptionThree(void);
void MemuTwoOptionFour(void);
void MemuTwoOptionFive(void);

void EnterMemuTwoOptionOne(void);
void EnterMemuTwoOptionTwo(void);
void EnterMemuTwoOptionThree(void);
void EnterMemuTwoOptionFour(void);
void EnterMemuTwoOptionFive(void);






void MemuThree(void);

void MemuThreeOptionOne(void);
void MemuThreeOptionTwo(void);
void MemuThreeOptionThree(void);
void MemuThreeOptionFour(void);


void EnterMemuThreeOptionOne(void);
void EnterMemuThreeOptionTwo(void);
void EnterMemuThreeOptionThree(void);
void EnterMemuThreeOptionFour(void);




void MemuFour(void);

void MemuFourOptionOne(void);
void MemuFourOptionTwo(void);
void MemuFourOptionThree(void);
void MemuFourOptionFour(void);
void MemuFourOptionFive(void);

void EnterMemuFourOptionOne(void);
void EnterMemuFourOptionTwo(void);
void EnterMemuFourOptionThree(void);
void EnterMemuFourOptionFour(void);
void EnterMemuFourOptionFive(void);



void MemuFive(void);

void MemuFiveOptionOne(void);
void MemuFiveOptionTwo(void);
void MemuFiveOptionThree(void);
void MemuFiveOptionFour(void);

void EnterMemuFiveOptionOne(void);
void EnterMemuFiveOptionTwo(void);
void EnterMemuFiveOptionThree(void);
void EnterMemuFiveOptionFour(void);




void MemuSix(void);

void MemuSixOptionOne(void);
void MemuSixOptionTwo(void);
void MemuSixOptionThree(void);
void MemuSixOptionFour(void);
void MemuSixOptionFive(void);
void MemuSixOptionSix(void);

void EnterMemuSixOptionOne(void);
void EnterMemuSixOptionTwo(void);
void EnterMemuSixOptionThree(void);
void EnterMemuSixOptionFour(void);
void EnterMemuSixOptionFive(void);
void EnterMemuSixOptionSix(void);


#endif













