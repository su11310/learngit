/* 
 * File:   TempDetection.h
 * Author: Administrator
 *
 * Created on 2014年12月24日, 上午8:20
 */

#ifndef TEMPDETECTION_H
#define	TEMPDETECTION_H

#ifdef	__cplusplus
extern "C" {
#endif

//IO方向设置
//#define DS18B20_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DS18B20_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO操作函数
//#define	DS18B20_DQ_OUT PGout(11) //数据端口	PG11
//#define	DS18B20_DQ_IN  PGin(11)  //数据端口	PG11
#define DS18B20_IO_OUT()       (mPORTESetPinsDigitalOut(BIT_7))
#define DS18B20_IO_IN()           (mPORTESetPinsDigitalIn(BIT_7))

#define DS18B20_DQ_IN           (mPORTEReadBits(BIT_7))
#define	DS18B20_DQ_OUTL      (mPORTEClearBits(BIT_7))
#define	DS18B20_DQ_OUTH      (mPORTESetBits(BIT_7))


UINT8 DS18B20_Init(void);			//初始化DS18B20
short DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(UINT8 dat);//写入一个字节
UINT8 DS18B20_Read_Byte(void);		//读出一个字节
UINT8 DS18B20_Read_Bit(void);		//读出一个位
UINT8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20    


#ifdef	__cplusplus
}
#endif

#endif	/* TEMPDETECTION_H */

