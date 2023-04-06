

#ifndef  _DAC8771_H_
#define  _DAC8771_H_



#include "stm32f10x.h"

void TaskDacOutData(void* pvData);
void  DAC8771_Init(void);
void DAC8771_WRITE_CMD(unsigned char commond,unsigned int date);
unsigned char SPI_ReadByte(unsigned char commond);
void DAC8771_OUT_VOLTARE(uint16_t data);
void DAC8771_init(void);
void test1(void);
void autoxieya(uint32_t cjipress,uint32_t* outputdata);

 uint16_t DAC8771_Read_CMD(uint8_t addr,uint16_t data);
 
uint8_t DacOutPut(float press,uint16_t Data,uint16_t times);
 
 
 

#define   SYNC1          GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define   SYNC0          GPIO_ResetBits(GPIOB,GPIO_Pin_6)



#define SCLK0 GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SCLK1 GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define DIN0  GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define DIN1  GPIO_SetBits(GPIOB,GPIO_Pin_8)


#define MISO  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)

extern  float voltage;
extern uint16_t data;
extern uint16_t user_gain;

/**********************寄存器地址单极性模式***************************************/
#define       NO_OPERATION               0x00     //noly  read
#define       RESETREG                   0x01
#define       RESETCON                   0x02
#define       SELECTDAC                  0x03
#define       CONDAC                     0x04
#define       DACDATA                    0x05
#define       SELECTBCBO                 0x06     
#define       CONBCBO                    0x07       //buck-boost控制器
#define       DACCAILBRA                 0x08      //通道校准
#define       DACGAINCAILBRA             0x09      //通道增益校准
#define       DACOFFSETCAILBRA           0x0A      //通道偏移校准
#define       STATUSREG                  0x0B
#define       STATUSMASKREG              0x0C
#define       ALARMACTOIN                0x0D
#define       ALARMCODEREG               0x0E    
#define       WATDOGTIMEREAST            0x10      // only write
#define       DEVICEID                   0x11      //only read

#define      DEFAULT_MODE        DAC8771_WRITE_CMD(CONBCBO,0<<10)
#define      FIXCLA_MODE         DAC8771_WRITE_CMD(CONBCBO,1<<10)
#define      ATULEN_MODE         DAC8771_WRITE_CMD(CONBCBO,2<<10)

  


#endif



/**


备注：1)在选用buck--boost为电流输出级和电压输出放大器提供电压
      地址0x07,CCLP[1:0] = 00,全跟踪模式，VPOS_IN产生的最小电压4V
			
			CCLP[1:0] = 01, 来重写默认操作，在VPOS_IN和VNEG_IN下产生的最小电压可以通过PCLMP[3:0]/NCLMP[3:0] 来写入
      CCLP[1:0]	= 10; 自动学习模式来自动感知当前输出的负载。在VPOS_IN产生的最小电压设置固定值		
			设置该模式：CCLP先写0：0，然后DAC DATA的值大于8000H，最后写CCLP等于10
       
      通电成功后，必须再写一次CCLP。
			
			将1写入 0x0E中的HSCLMP表示选择产生默认最大正电压32V，通过选择相应的通道来启用或者禁用此功能
			
			DAC8771使用转换器工作：PVDD和AVDD在一起，VPOS_IN和VNEG_IN通过设备寄存器来使用。
			DAC8771可以不使用BUCK--BOOST转换器情况下工作，PVDD，AVDD，VPOS_IN,链接到一起，用12-33V供电


     2) alarm 功能：(引脚被拉低)
		 (1):IOUT负载处于开路
		 (2):温度大于150
		 (3):SPI看们狗超过周期
		 (4):SPI校验错误
		 (5):当在电压输出模式下启用，达到短路电流限制
		 (6):达到最大输出电压，0x0E中的HSCLMP。
		 
		 当0x0B中的PG为是1(只读)表示VPOS_IN>4,VNEG_IN<-3.
		 
		 
		 3):选择速率控制功能：通过0x0E的SREN来设置启动和禁用，默认是禁用,输出受到输出驱动和负载限制的速率
		 使用该功能的时候,输出不会在2个值来回切换,通过SR_STEP[2;0],SRCLK_RATE[3:0],

     4)写操作编程步骤：选择buck-boost寄存器(是否启用buck-boost)0x06
		                   配置buck-boost电路(模式配置，VPOS_IN上的电压配置)0x07
		                   选择DAC寄存器(开启通道) 0x03
											 配置DAC寄存器(是否开启选转速率控制功能)0x04
											 配置DAC数据寄存器：(表示电压调整)0x05
											 
											 
		 5):	无校准模式(单极性输出)。VOUT = VREFIN*GAIN*CODE/2的16次方(0到5V或者0到10V)	
          有校准模式：CODE_OUT = CODE*(USER_GAIN+2的15次方)/2的16次方+USER_ZERO
          
         
		 7):单极性电压输出配置步骤：开启通道0x03的第5位CHA； 
		                            输出启用设置：0x04的第12位，OTEN：电流或者电压输出。
																启用校准，设置0x08的第零位CLEN，
		                            将0x0B的第六位UTGL读出来的值,在0x02中的UBT设置该值看是否和芯片通信成功
																



**/















