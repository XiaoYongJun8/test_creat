

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

/**********************�Ĵ�����ַ������ģʽ***************************************/
#define       NO_OPERATION               0x00     //noly  read
#define       RESETREG                   0x01
#define       RESETCON                   0x02
#define       SELECTDAC                  0x03
#define       CONDAC                     0x04
#define       DACDATA                    0x05
#define       SELECTBCBO                 0x06     
#define       CONBCBO                    0x07       //buck-boost������
#define       DACCAILBRA                 0x08      //ͨ��У׼
#define       DACGAINCAILBRA             0x09      //ͨ������У׼
#define       DACOFFSETCAILBRA           0x0A      //ͨ��ƫ��У׼
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


��ע��1)��ѡ��buck--boostΪ����������͵�ѹ����Ŵ����ṩ��ѹ
      ��ַ0x07,CCLP[1:0] = 00,ȫ����ģʽ��VPOS_IN��������С��ѹ4V
			
			CCLP[1:0] = 01, ����дĬ�ϲ�������VPOS_IN��VNEG_IN�²�������С��ѹ����ͨ��PCLMP[3:0]/NCLMP[3:0] ��д��
      CCLP[1:0]	= 10; �Զ�ѧϰģʽ���Զ���֪��ǰ����ĸ��ء���VPOS_IN��������С��ѹ���ù̶�ֵ		
			���ø�ģʽ��CCLP��д0��0��Ȼ��DAC DATA��ֵ����8000H�����дCCLP����10
       
      ͨ��ɹ��󣬱�����дһ��CCLP��
			
			��1д�� 0x0E�е�HSCLMP��ʾѡ�����Ĭ���������ѹ32V��ͨ��ѡ����Ӧ��ͨ�������û��߽��ô˹���
			
			DAC8771ʹ��ת����������PVDD��AVDD��һ��VPOS_IN��VNEG_INͨ���豸�Ĵ�����ʹ�á�
			DAC8771���Բ�ʹ��BUCK--BOOSTת��������¹�����PVDD��AVDD��VPOS_IN,���ӵ�һ����12-33V����


     2) alarm ���ܣ�(���ű�����)
		 (1):IOUT���ش��ڿ�·
		 (2):�¶ȴ���150
		 (3):SPI���ǹ���������
		 (4):SPIУ�����
		 (5):���ڵ�ѹ���ģʽ�����ã��ﵽ��·��������
		 (6):�ﵽ��������ѹ��0x0E�е�HSCLMP��
		 
		 ��0x0B�е�PGΪ��1(ֻ��)��ʾVPOS_IN>4,VNEG_IN<-3.
		 
		 
		 3):ѡ�����ʿ��ƹ��ܣ�ͨ��0x0E��SREN�����������ͽ��ã�Ĭ���ǽ���,����ܵ���������͸������Ƶ�����
		 ʹ�øù��ܵ�ʱ��,���������2��ֵ�����л�,ͨ��SR_STEP[2;0],SRCLK_RATE[3:0],

     4)д������̲��裺ѡ��buck-boost�Ĵ���(�Ƿ�����buck-boost)0x06
		                   ����buck-boost��·(ģʽ���ã�VPOS_IN�ϵĵ�ѹ����)0x07
		                   ѡ��DAC�Ĵ���(����ͨ��) 0x03
											 ����DAC�Ĵ���(�Ƿ���ѡת���ʿ��ƹ���)0x04
											 ����DAC���ݼĴ�����(��ʾ��ѹ����)0x05
											 
											 
		 5):	��У׼ģʽ(���������)��VOUT = VREFIN*GAIN*CODE/2��16�η�(0��5V����0��10V)	
          ��У׼ģʽ��CODE_OUT = CODE*(USER_GAIN+2��15�η�)/2��16�η�+USER_ZERO
          
         
		 7):�����Ե�ѹ������ò��裺����ͨ��0x03�ĵ�5λCHA�� 
		                            ����������ã�0x04�ĵ�12λ��OTEN���������ߵ�ѹ�����
																����У׼������0x08�ĵ���λCLEN��
		                            ��0x0B�ĵ���λUTGL��������ֵ,��0x02�е�UBT���ø�ֵ���Ƿ��оƬͨ�ųɹ�
																



**/















