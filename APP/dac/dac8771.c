
#include "dac8771.h"
#include "uart.h"
#include "MX25L.h"
#include "stm32f10x.h"
#include "screenshow.h"
#include "led.h"

float  voltage = 0;//要显示的电压
uint16_t data = 0;//写入数据寄存器的值
uint16_t user_gain = 0;//调整精度的值
char str[6] = {0};

/*************
CS ：PB6
SCLK：PB7
MOSI：PB8
MISO：PB9


*************/

void  DAC8771_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* SPI的IO口设置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*不选DAC*/ 

	/*不选DAC*/ 
	
	/*不选DAC*/ 
	
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	
	
  DAC8771_init();
	
}


void  DAC8771_WRITE_CMD(unsigned char commond,unsigned int date)
{

  unsigned char i;


  SYNC0;    //选中从设备
	SCLK1;    //起始的时候是高电平
	

	for(i=0; i<8; i++)
	{	
		SCLK1;   // 在高电平到低电平期间采样数据

		if (commond & 0x80)   
		{
		  DIN1;
		}
		else
		{
		  DIN0;
		}
	  commond <<= 1;
		SCLK0;

	} 

	for (i=0; i<16; i++)
	{
		SCLK1;
		if (date & 0x8000)
		{
			DIN1;
		}
		else
		{
			DIN0;
		}
		date <<= 1;
	
		SCLK0;

	} 
	
	SYNC1;  //释放从设备
	SCLK1;  //恢复高电平

}




uint16_t DAC8771_Read_CMD(uint8_t addr,uint16_t data)
{
	    int i = 0;
	    uint8_t nop = 0x00;   //发送步操作指令
	    
	    uint16_t nop1 = 0x0000;
      uint16_t redata = 0; 
     	
	   addr|=(1<<7);           //读数据的时候最高位必须是1
	   nop|=(0<<7);
	   DAC8771_WRITE_CMD(addr,data); //DB23是1,16-22是寄存器地址,后面的值不管  
	   SYNC1;
	   SCLK1;

	   SYNC0;
	
	for(i=0; i<8; i++)
	{	
		SCLK1;   // 在高电平到低电平期间采样数据
		if (nop & 0x80)   
		{
		  DIN1;
		}
		else
		{
		  DIN0;
		}
		
		nop<<= 1;

		SCLK0;

	}
	
	for (i=0; i<16; i++)
	{
		SCLK1;
		if (nop1 & 0x8000)
		{
			DIN1;
		}
		else
		{
			DIN0;
		}
		
		nop1 <<= 1;
		redata<<=1;
		if(MISO==1) redata |= 0x0001;
		SCLK0;
	} 
	SYNC1;  //释放从设备
	SCLK1;  //恢复高电平  
	return redata;

}

/***************************************

 DAC8775_WRITE_CMD(0x06,DAC_DCA);DAC8775_WRITE_CMD(0x03,DAC_CHA)
#define   DAC_DCA          1<<0
#define   DAC_DCB          1<<1
#define   DAC_DCC         1<<2
#define   DAC_DCD         1<<3

#define    DAC_CHA         1<<5          //32
#define    DAC_CHB         1<<6          //64
#define    DAC_CHC         1<<7          //128
#define    DAC_CHD         1<<8          //256

***************************************/

void DAC8771_init(void)
{
	
uint16_t temp1 = 0;
uint16_t temp2 = 0 ;
uint16_t temp3 = 0 ;
uint16_t temp4 = 0;
uint16_t temp5 = 0;	
uint16_t temp6 = 0;
uint16_t temp7 = 0;
uint16_t temp8 = 0;
uint16_t temp9 = 0;
uint16_t temp10 = 0;
uint16_t temp11 = 0;
uint16_t temp12 = 0;	
	
uint16_t ref = 0;
uint16_t buck = 0;
uint16_t opench = 0;
uint16_t pnout = 0;
//uint16_t range = 0;
uint16_t opendac = 0;
uint16_t value = 0;
uint16_t clcsa = 0;
uint16_t clr = 0;
uint16_t clren = 0;
uint16_t poc = 0;
	int i = 0;
ref |=(1<<4);	
//buck |=(1<<0);     //使用BUCKA	
//buck |=(1<<1);   //使用BUCKB
buck |=(1<<2);   //使用BUCKC
//buck |=(1<<3);   //使用BUCKD
//opench |= (1<<5);   //开启通道A	
//opench |= (1<<6);   //开启通道B	
opench |= (1<<7);   //开启通道C	
//opench |= (1<<8);   //开启通道D	

pnout = (3<<0);     //
opendac |= ((1<<12)|(9<<0));  //   (6<<0)	0-24MA.  (12<<0) 4-20MA,(9<<0),0-12V

//value = ROUND_TO_UINT16(65536*(12-4)/16);

clcsa |= (1<<9);
clr |= (1<<2);
clren |= (1<<9);
poc |= (1<<1);	
delay_ms(1000);
delay_ms(1000);
delay_ms(1000);
	  DAC_REAST;
	  //add-2022-8-16 初始化不过就会死机，灯亮
	while(1)
	{
		 SYS_ON;

		//  GPIO_ReSetBits(GPIOB ,GPIO_Pin_3);
DAC8771_WRITE_CMD(0x02,ref);              //使用内部参考  0x02的第4位写1
//temp1 = DAC8771_Read_CMD(0x02,0x0000);

DAC8771_WRITE_CMD(0x06 ,buck);            //使用内部BUCK给VPOS和VNEG供电,0x06的第0位写1
//temp2 = DAC8771_Read_CMD(0x06,0x0000);


DAC8771_WRITE_CMD(0x07,pnout);            //正负臂启用,+-9V,1:0写3启用正负臂,2:5写入2启用负臂-9V,9:6写3启用正臂9V  0010 0001 1111
temp4 = DAC8771_Read_CMD(0x07,0x0000);


DAC8771_WRITE_CMD(0x03 ,opench);          //开通道A ,0x03的第5位写1
//temp3 = DAC8771_Read_CMD(0x03,0x0000);	

//DAC8771_WRITE_CMD(0x04,range);            //电压输出模式 0x04的第3：0写1；
//temp5 = DAC8771_Read_CMD(0x04,0x0000);

//DAC8771_WRITE_CMD(0x02,clren);              //CLREN 
//temp11 = DAC8771_Read_CMD(0x02,0x0000);

//DAC8771_WRITE_CMD(0x02,clr);              //CLR位
//temp10 = DAC8771_Read_CMD(0x02,0x0000);


//DAC8771_WRITE_CMD(0x03 ,clcsa);             //使用
//temp8 = DAC8771_Read_CMD(0x03,0x0000);

//DAC8771_WRITE_CMD(0x02 ,poc);             //POC
//temp12 = DAC8771_Read_CMD(0x02,0x0000);

DAC8771_WRITE_CMD(0x04,opendac);              //开启输出,0x04的第12位写入1	,选择量程和开启输出
//temp6 = DAC8771_Read_CMD(0x04,000000);	

//DAC8771_WRITE_CMD(0x05,value);                  //输出值
//temp7	= DAC8771_Read_CMD(0x05,0);
temp9	 = 0;
 delay_ms(100);
temp9	= DAC8771_Read_CMD(0x0B,0);              //读取电源状态
	 delay_ms(100);
if(temp9& 0x0200 )
{
	printf("cgggpower=%d\r\n",temp9& 0x0200);
	
}
temp12 = 0;
temp12 = (temp9& 0x0200);
if(temp12 != 512)
{
	  delay_ms(100);
		printf("DACREAET\r\n");
	  DAC_REAST;
		delay_ms(100);
	  printf("DACREASTOK\r\n");
  	DAC_SET;
	
}
else
{
	//delay_ms(100);
	break;
}



printf("power=%d\r\n",temp9);
//if(temp9 == 4096)
//{
	//printf("pnout=%d\r\n",temp4); 
   
//	temp9 = 0;
//	break;
//}
//	printf("ref=%d\r\n",temp1);            //16
//	printf("buck=%d\r\n",temp2);            //1  
//	printf("opench=%d\r\n",temp3);          
	          
	//printf("range=%d\r\n",temp5);             
	//printf("opendac=%d\r\n",temp6);            
	//printf("value=%d\r\n",temp7);          
 // printf("clcsa=%d\r\n",temp8);
  //printf("power=%d\r\n",temp9);             //5888
 // printf("clr=%d\r\n",temp10);            
  //printf("clren=%d\r\n",temp11);
	//printf("poc=%d\r\n",temp12);          
//}


}
 SYS_OFF;
 DAC_SET;
}













void test1(void)
{
u8 temp=2;
u16 temp1 = 0;
u16 temp2 = 0 ;
u16 temp3 = 0 ;
u16 temp4 = 0;
	
u32 data = 0;
u32 data1 = 0;
u16 range = 0 ;
u16 start_ma = 0;
u16 value =0 ;	 
	
data |= (1<<5);   //开启通道
data1 |=(0<<0);   //步使用BUCK
range &=~(0xF<<0);//电流输出模式0---24mA
range |= 6<<0;
start_ma &= ~(1<<12); //开启DAC输出
start_ma |= 1<<12;

value = 888;//数据寄存器的值.	
	
DAC8771_WRITE_CMD(SELECTDAC ,data);
temp = DAC8771_Read_CMD(SELECTDAC,0x0000);
	
DAC8771_WRITE_CMD( SELECTBCBO   ,data1);
temp1	= DAC8771_Read_CMD( SELECTBCBO ,0x0000);
	
DAC8771_WRITE_CMD(CONDAC ,range);
temp2	= DAC8771_Read_CMD( CONDAC,range);	
	
DAC8771_WRITE_CMD(CONDAC ,start_ma);
temp3	= DAC8771_Read_CMD( CONDAC,start_ma);

DAC8771_WRITE_CMD(DACDATA,value);
temp4	= DAC8771_Read_CMD(DACDATA,0);

	printf("temp=%d\r\n",temp);
	printf("temp1=%d\r\n",temp1);
	printf("temp2=%d\r\n",temp2);
	printf("temp3=%d\r\n",temp3);
	printf("temp4=%d\r\n",temp4);
	
}


/**********************************************************************
函数功能：自动采集的压力，DAC控制电磁阀泄气来对应采集的压力值
函数参数：采集的压力值,采集的压力会达不到我们与预设计的压力
           会有0.1Bar的误差

都是以bar为换算单位。
**********************************************************************/


void TaskDacOutData(void* pvData)
 {
	 
	 
	  pvData = pvData;
 
    while(1)
		 {
		 
		   OSTimeDly(20);
//		   ADC_ShowPres(0,&ADCGetPress[1],5);
//			 
//			   for(i=1;i<6;i++)
//				 { 
//					 
//					 showPress(i,ModifyVarStructVar.pressUint,ADCGetPress[1]);
//				  }
        WANING_FZ;
		
		 }
 
 }

 
 
 
 
 
 
uint8_t DacOutPut(float press,uint16_t Data,uint16_t times)
 {
     uint8_t ret = 0;
	   int DacOutData = 0;
	    static  uint16_t i = 1;   
	 
	   DacOutData =  getOutData(10000.0); //
	 
	   uint16_t num = (Data-DacOutData)/times; //每一个等分的大小
	         //多少等分
	 
	 uint16_t cishu = 0;
	 float  cjupress = 0.0;
	 cjupress = press - 10000.0;//1000;
	 cishu = cjupress /2000;
	 // for(i=1;i<=times;i++)
	 //   {
				
		//	 DAC8771_WRITE_CMD(0x05,i*num);
		//	}
		// DAC8771_WRITE_CMD(0x05,DacOutData+i*num);
	  // i++;
	  // if(i>= times)
		// {
		//	 ret = 1;
		 //  i = 1;
		// }
		
		 DAC8771_WRITE_CMD(0x05,getOutData(10000+2000*i));
		 i++;
		 if(i>=cishu)
		 {
		   i=1;
			 ret = 1;
		 }
		 return ret;
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
















































