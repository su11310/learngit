/* 
 * File:   TempDetection.h
 * Author: Administrator
 *
 * Created on 2014��12��24��, ����8:20
 */

#ifndef TEMPDETECTION_H
#define	TEMPDETECTION_H

#ifdef	__cplusplus
extern "C" {
#endif

//IO��������
//#define DS18B20_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DS18B20_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
////IO��������
//#define	DS18B20_DQ_OUT PGout(11) //���ݶ˿�	PG11
//#define	DS18B20_DQ_IN  PGin(11)  //���ݶ˿�	PG11
#define DS18B20_IO_OUT()       (mPORTESetPinsDigitalOut(BIT_7))
#define DS18B20_IO_IN()           (mPORTESetPinsDigitalIn(BIT_7))

#define DS18B20_DQ_IN           (mPORTEReadBits(BIT_7))
#define	DS18B20_DQ_OUTL      (mPORTEClearBits(BIT_7))
#define	DS18B20_DQ_OUTH      (mPORTESetBits(BIT_7))


UINT8 DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(UINT8 dat);//д��һ���ֽ�
UINT8 DS18B20_Read_Byte(void);		//����һ���ֽ�
UINT8 DS18B20_Read_Bit(void);		//����һ��λ
UINT8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    


#ifdef	__cplusplus
}
#endif

#endif	/* TEMPDETECTION_H */

