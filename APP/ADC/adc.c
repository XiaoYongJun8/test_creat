 //#include "adc.h"
 #include "uart.h"
 //#include "SysTick.h"
 #include "includes.h"
/*
1路ADC采样DMA传输
调用Adc_Init()函数初始化设备，ADC循环采样 
数据被DMA搬运到ADC_Value[ADC_CH_NUM]数组中
滤波后的数据在ADC_AfterFilter[ADC_CH_NUM]中
*/
	   		   	

u16 ADC_Value[ADC_CH_NUM] = {0};					
u16 ADC_AfterFilter[ADC_CH_NUM] = {0};
float ADCGetPress[10] = {0.0};


typedef struct
{
	uint8_t  bIsValid;
	uint16_t u16QueueLen;
	uint16_t u16ItermSize;
	uint16_t u1DdataLen;
	uint16_t  u16Data[16];
}fifo_t;

fifo_t adc_fifo[1];



void fifo_init(fifo_t* pFifo, uint16_t queueLength,uint16_t itermSize)
{
	
	uint16_t i = 0;
	uint16_t j = 0;
	if((pFifo == NULL) || (queueLength == 0) || (itermSize == 0))
	{
	}
	else
	{
		pFifo->u16QueueLen = queueLength;
		pFifo->u16ItermSize = itermSize;
		for( i = 0; i < pFifo->u16QueueLen; i++)
		{
			pFifo->bIsValid = 0;
			pFifo->u1DdataLen = 0;
			for(j = 0; j < itermSize; j++)
			{
				pFifo[i].u16Data[j] = 0;
			}
		}
	}
}




uint8_t fifo_set(fifo_t* pFifo,uint16_t* buf, uint16_t len)
{
	uint8_t ret = 0;
	uint16_t i = 0;
	uint16_t j = 0;
	if((len > 16) || (pFifo == NULL) || (buf == NULL))
	{
		ret = 0;
	}
	else
	{
		for( i = 0; i < pFifo->u16QueueLen; i++)
		{
			if(pFifo[i].bIsValid == 0)
			{
				pFifo[i].bIsValid = 1;
				if(len > pFifo[i].u16ItermSize)
				{
					len = pFifo[i].u16ItermSize;
				}
				pFifo[i].u1DdataLen = len;
				for( j = 0; j < pFifo[i].u1DdataLen; j++)
				{
					pFifo[i].u16Data[j] = buf[j];
				}
				ret = 1;
				break;
			}
		}
	}
	return ret;
}



uint8_t fifo_get(fifo_t* pFifo,uint16_t* buf, uint16_t* len)
{
	uint8_t ret = 0;
	uint16_t i = 0;
	uint16_t j = 0;
	
	if((pFifo == NULL) || (buf == NULL) || (len == NULL))
	{
		ret = 0;
	}
	else
	{
		for(i = 0; i < pFifo->u16QueueLen; i++)
		{
			if(pFifo[i].bIsValid == 1)
			{
				pFifo[i].bIsValid = 0;
				*len = pFifo[i].u1DdataLen;
				for( j = 0; j < pFifo[i].u1DdataLen; j++)
				{
					buf[j] = pFifo[i].u16Data[j];
				}
				ret = 1;
				break;
			}
		}
	}
	return ret;
}




static uint16_t CpVoltage_AdcFillter(const uint16_t *pData, uint16_t len)
{
	uint16_t min = 0, max = 0, verg = 0, invaild_count = 0,vaild_count = 0;
	uint32_t sum = 0;
	uint16_t tmp;
	uint16_t i;
	if(pData == NULL || len == 0)
	{
		return 0;
	}
	else
	{
		min = pData[0];
		max = pData[0];
		for(i = 0; i < len; i++)
	    {
			tmp = pData[i];
	        if(pData[i] != 0)
	        {
	        	if(min == 0)
	        	{
	        		min = pData[i];
	        	}
	            if(min > pData[i])
	            {
	                min = pData[i];
	            }
	            if(max < pData[i])
	            {
	                max = pData[i];
	            }
	        }
			else
	        {
	            invaild_count++;
	        }
			sum += pData[i];
	    }
		vaild_count = len - invaild_count;
		if(vaild_count > 2)
		{
			sum -= min;
			sum -= max;
			verg = sum / (vaild_count - 2);
		}
		else if(vaild_count == 2)
		{
			verg = sum / 2;
		}
		else if((vaild_count = 0) || (vaild_count = 1))
		{
			verg = 0;
		}
		else
		{
			verg = 0;
		}
	}
	return verg;
}



void  Adc_Init(void)
{ 	
    ADC_InitTypeDef ADC_InitStructure; 
    DMA_InitTypeDef  DMA_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1,ENABLE );	  //使能ADC1通道时钟

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

    //PA0-PA1 作为模拟通道输入引脚                         
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);		

    /* DMA channel1 configuration */
    DMA_DeInit(DMA1_Channel1);
    /*定义DMA外设基地址,即为存放转换结果的寄存器*/
    DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&(ADC1->DR);
    /*定义内存基地址*/
    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)ADC_Value;
    /*定义AD外设作为数据传输的来源*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    /*指定DMA通道的DMA缓存的大小,即需要开辟几个内存空间，由ADC_CH_NUM这个宏决定*/
    DMA_InitStructure.DMA_BufferSize = ADC_CH_NUM;
    /*设定寄存器地址固定*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /*设定内存地址递加，即每次DMA都是将该外设寄存器中的值传到开辟的内存空间中*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    /*设定外设数据宽度 半字*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    /*设定内存的的宽度 半字*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    /*设定DMA工作再循环缓存模式*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		
    /*设定DMA选定的通道软件优先级*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    /* Enable DMA channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);
		/*  使用DMA传输完成中断 */
 // DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); 

    ADC_DeInit(ADC1);  //复位ADC1 
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE ;	//模数转换工作在扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE ;	//模数转换工作在连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = ADC_CH_NUM;	//顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

    /*ADC通道编号*/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_7Cycles5);

    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1

    ADC_ResetCalibration(ADC1);	//使能复位校准  

    while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束

    ADC_StartCalibration(ADC1);	 //开启AD校准

    while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能 
}				  

//ADC采样值滤波
//ADC?????
u16 ADC_Filter(uint8_t ADC_Channel, u8 times)
{
    u8 t = 0;
  uint16_t ret = 0;

    switch(ADC_Channel)
    {
        case ADC_Channel_0:
            for(t = 0; t < times; t++)
            {
							  
                ret += ADC_Value[0];
							
            }
            break;
        case ADC_Channel_1:
            for(t = 0; t < times; t++)
            {
                ret+= ADC_Value[1];
            }
            break;
    }
    return ret/times;
}


u16 ADC_Filter1(uint8_t ADC_Channel, u8 times)
{
    u8 t = 0;
	  u8 i = 0;
	  u8 j = 0;
    uint16_t ret = 0;
	  uint16_t sum = 0;
	  uint16_t temp = 0;
	  uint16_t   ADC_Data[16] = {0};
    uint16_t   ADC_Data1[16] = {0};
   switch(ADC_Channel)
    {
        case ADC_Channel_0:
            for(t = 0; t < times; t++)
            {
					
                 ADC_Data[t] = ADC_Value[0];
                 ADC_Data[t] = 		ADC_Data[t]*1.065;				
            }
						for(j=0;j<times;j++){
							
							for(i=0;i<times-j;i++){
								
								if( ADC_Data[i] >  ADC_Data[i+1]){
									
									 temp =  ADC_Data[i];
									 ADC_Data[i] =  ADC_Data[i+1];
								   ADC_Data[i+1] = temp;	
								}	
					    }
						} for(i = 1;i<times-1;i++){
								  sum +=  ADC_Data[i];
							}

						break;
						
						
					
          
        case ADC_Channel_1:
           for(t = 0; t < times; t++)
            {
					
                 ADC_Data1[t] = ADC_Value[1];	
							//sum += ADC_Value[t];
            }
						
						for(j=0;j<times;j++){
							
							for(i=0;i<times-j;i++){
								
								if( ADC_Data1[i] >  ADC_Data1[i+1]){
									
									 temp =  ADC_Data1[i];
									 ADC_Data1[i] =  ADC_Data1[i+1];
								   ADC_Data1[i+1] = temp;	
								}	
					    }
						} for(i = 1;i<times-1;i++){
								  sum +=  ADC_Data1[i];
							}
						
					
            break;
    }
    return (sum/(times-2));
}
 
 

//   Mpa = 0.0625*(Ma-4);
void  ADC_ShowPres(uint8_t ADC_Channel,float*ret,uint8_t len)
 {
 
   uint32_t  data1 = 0;
	   uint32_t  data = 0;
	   uint8_t i = 0;
	   uint8_t j = 0;
	  float press = 0.0;
	  float pressarr[16] = {0.0};
	  float getMA = 0;
		float getMA1 = 0;
	  //884.736, 819,   //65.736.只要采集的数据大于65.736就会产生一次触发
    switch(ADC_Channel)
    {
        case ADC_Channel_0: 
                        	
			                    for(i=0;i<len;i++)
			                       {	
															 
														   data = ADC_Filter1(ADC_Channel_0,ADC_CH_NUM);//  
                                 															 
													 	 // printf("data=%d\r\n",data);		
														   getMA = (1000*data/4096*3.3)/100;        
													  //    printf("getMA=%0.2f\r\n",getMA);  
														   press = (0.625*getMA)-2.5;      //Bar  
														   pressarr[i] = press;
												
													//   printf(" pressarr[%d]=%0.2f\r\n",i,pressarr[i]);	
														 }
														 
										   for(j=0;j<len;j++){                                       //
							
						             	for(i=0;i<len-j;i++){
								
								            if( pressarr[i] >  pressarr[i+1]){
									
									             press =  pressarr[i];
									             pressarr[i] =  pressarr[i+1];
								               pressarr[i+1] =press;	
								         }	
					            }
						        }
										press = 0.0;
									 for(i=2;i<=len-3;i++)
                     {
										   press+=pressarr[i];
										 }						
									  *ret = press/(float)(len - 4);	
                    *ret = *ret - 0.4;		          //0.9   0.4
														 
											// *ret = 	 pressarr[2] 	;	 
                     if(*ret < 0)
										 {
										 *ret = 0.00;
										 }	
										 
										break;  			 
						

										 
              /*
  		            data = ADC_Filter1(ADC_Channel_0,ADC_CH_NUM); 
							//   printf("data=%d\r\n",data);		
								  getMA = (1000*data/4096*3.3)/165;      //得到真正的电流值      
									// printf("getMA=%0.2f\r\n",getMA);  
								  press = (0.625*getMA)-2.5;      //Bar  //得到要显示的压力
								  *ret = press;					  
								*/				

														                                  
        case ADC_Channel_1:

                              data1 = ADC_Filter1(ADC_Channel_1,ADC_CH_NUM);//    
													 	  // printf("data=%d\r\n",data1);		
														   getMA1 = (1000*data1/4096*3.3)/100; 
				                      // getMA1 = getMA1 - 1.1; //减去偏移量
													  //   printf("getMA1=%0.2f\r\n",getMA1); 
				                        if(getMA1 < 4.0)
																{
																getMA1 = 4.0;
																}
				                        press = (4.6875*getMA1)-18.75;      //Bar 
				                     //  printf("liuliang=%0.2f\r\n",press); 
				                       *ret = press;
														  
														  // pressarr[i] = press;




				                         break;
                
    }
		

 } 
 
 
 

 


 
 

	


	















