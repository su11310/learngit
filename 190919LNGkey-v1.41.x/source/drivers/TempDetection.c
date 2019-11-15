#include "../includes/global_def.h"

void delay_us(UINT16 us)
{
     UINT32 i;
    UINT32 j;
    for(j =0; j < us; j++)
    {
        for(i = 0; i<8; i++) //1us
        {
            __asm__ __volatile__("NOP");
        }
    }
}

//复位DS18B20
void DS18B20_Rst(void)
{
	DS18B20_IO_OUT(); //SET PG11 OUTPUT
    DS18B20_DQ_OUTL; //拉低DQ
    delay_us(500);    //拉低750us
    DS18B20_DQ_OUTH; //DQ=1
	delay_us(15);     //15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
UINT8 DS18B20_Check(void)
{
	UINT8 retry=0;
	DS18B20_IO_IN();//SET PG11 INPUT
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
UINT8 DS18B20_Read_Bit(void) 			 // read one bit
{
    UINT8 data;
	DS18B20_IO_OUT();//SET PG11 OUTPUT
    DS18B20_DQ_OUTL;
	delay_us(2);
    DS18B20_DQ_OUTH;
	DS18B20_IO_IN();//SET PG11 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;
    delay_us(50);
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
UINT8 DS18B20_Read_Byte(void)    // read one byte
{
    UINT8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++)
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(UINT8 dat)
 {
    UINT8 j;
    UINT8 testb;
	DS18B20_IO_OUT();//SET PG11 OUTPUT;
    for (j=1;j<=8;j++)
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb)
        {
            DS18B20_DQ_OUTL;// Write 1
            delay_us(2);
            DS18B20_DQ_OUTH;
            delay_us(60);
        }
        else
        {
            DS18B20_DQ_OUTL;// Write 0
            delay_us(60);
            DS18B20_DQ_OUTH;
            delay_us(2);
        }
    }
}
//开始温度转换
void DS18B20_Start(void)// ds1820 start convert
{
    DS18B20_Rst();
	DS18B20_Check();
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
}
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在
UINT8 DS18B20_Init(void)
{
//	RCC->APB2ENR|=1<<8;    //使能PORTG口时钟
//	GPIOG->CRH&=0XFFFF0FFF;//PORTG.11 推挽输出
//	GPIOG->CRH|=0X00003000;
//	GPIOG->ODR|=1<<11;      //输出1
	DS18B20_Rst();
	return DS18B20_Check();
}
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250）
short DS18B20_Get_Temp(void)
{
    UINT8 temp;
    UINT8 TL,TH;
	short tem;
    DS18B20_Start ();                    // ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0xbe);// convert
    TL=DS18B20_Read_Byte(); // LSB
    TH=DS18B20_Read_Byte(); // MSB

    if(TH>7)
    {
        TH=~TH;
        TL=~TL;
        temp=0;//温度为负
    }else temp=1;//温度为正
    tem=TH; //获得高八位
    tem<<=8;
    tem+=TL;//获得底八位
    tem=(float)tem*0.0625;//转换
	if(temp)return tem; //返回温度值
	else return -tem;
}
