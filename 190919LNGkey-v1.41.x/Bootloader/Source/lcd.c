/*
 * File:   lcd.c
 * Author: jereh
 *
 * Created on 2014_01_14
 */
#include <p32xxxx.h>
#include <stdlib.h>
#include <plib.h>
#include "Include\Uart\Uart.h"
#include "HardwareProfile.h"
#include "Include\BootLoader.h"
#include "Include\Framework\Framework.h"

//PORTB.0-CS;
//PORTA-6:SDI;
//PORTA-7:SCK
#define SDI                   PORTGbits.RG13

#define SDI_High             mPORTGSetBits(BIT_13)
#define SDI_Low              mPORTGClearBits(BIT_13)
#define SCK_High             mPORTGSetBits(BIT_12)
#define SCK_Low              mPORTGClearBits(BIT_12)
#define CS_High              mPORTGSetBits(BIT_14)
#define CS_Low               mPORTGClearBits(BIT_14)

#define CLEAR_SCREEN              0x01
#define CLEAR_AC                  0x02
#define POINT_SET_RIGHT           0x06
#define FUNC_BASE_SET             0x30
#define FUNC_EXT_SET              0x34
#define DISPLAY_ON                0x0c
#define DISPLAY_OFF               0x08
#define GRAPHICS_ON               0x36
#define GRAPHICS_OFF              0x34

#define  CLK_CYCLE                200//200

//void WriteByte(unsigned char data)
static void olcd_writeByte(unsigned char data)
{
    unsigned char i,j;
    for(i=0;i<8;i++)
    {
        SCK_Low;
        for(j=0;j<CLK_CYCLE;j++);
        if(data&0x80)       SDI_High;
        else                SDI_Low;
        SCK_High;
//        for(j=0;j<CLK_CYCLE;j++);
        SCK_Low;
        data=data<<1;
    }
}

//unsigned char ReceiveByte(void)
static unsigned char olcd_receiveByte(void)
{
    unsigned char i,Temp0,k,Temp1,dummy,j;
    Temp0=0;
    Temp1=0;
    PORTSetPinsDigitalIn(IOPORT_G, BIT_13);
    for(i=0;i<8;i++)
    {
        Temp0<<=1;
        SCK_Low;
        for(j=0;j<CLK_CYCLE;j++);
        SCK_High;
        for(j=0;j<CLK_CYCLE;j++);
        SCK_Low;
        if(SDI==1) Temp0++;
    }

    for(i=0;i<8;i++)
    {
        Temp1<<=1;
        SCK_Low;
        for(j=0;j<CLK_CYCLE;j++);
        SCK_High;
        for(j=0;j<CLK_CYCLE;j++);
        SCK_Low;
        if(SDI==1)  Temp1++;
   }
   k=((0xf0 & Temp0)+(0x0f & Temp1));
   PORTSetPinsDigitalOut(IOPORT_G, BIT_13);
   return k;
}

//void CheckBusy( void )
BOOL olcd_checkBusy( void )
{
#if 1
     unsigned long waittime=0;
     delay_ms(10);//delay(10E3);
     do
     {
         olcd_writeByte(0xfc);      //11111,RW(1),RS(0),0
         if(waittime++ >100000) return FALSE;
     }
     while(0x80&olcd_receiveByte());//&&(waittime<10000));      //BF(.7)=1 Busy
#endif
     return TRUE;
}

void olcd_writeCommand( unsigned char Cbyte )
{
     CS_High;
     if(olcd_checkBusy())
     {
        olcd_writeByte(0xf8);            //11111,RW(0),RS(0),0
        olcd_writeByte(0xf0&Cbyte);      //???
        olcd_writeByte(0xf0&Cbyte<<4);   //???(???<<)
     }
     CS_Low;
}

static void olcd_writeData( UINT8 Dbyte )
{
     CS_High;
     if(olcd_checkBusy()){
         olcd_writeByte(0xfa);            //11111,RW(0),RS(1),0
         olcd_writeByte(0xf0&Dbyte);      //???
         olcd_writeByte(0xf0&Dbyte<<4);   //???(???<<)
     }
     CS_Low;
}

unsigned char olcd_readData( void )
{
     if(olcd_checkBusy())
     {
        olcd_writeByte(0xfe);            //11111,RW(1),RS(1),0
        return olcd_receiveByte();
     }
     return 0x00;
}

void olcd_clearsCreen(void)
{
     olcd_writeCommand(CLEAR_SCREEN);
}

void olcd_dispstr(INT8 x, INT8 y, UINT8 *str, UINT8 len)
{
    const UINT8   y_offset[4] = {0x80, 0x90, 0x88, 0x98};
    //if(y>4 || y<0 || (x+len)>16) return;
//    if(len >16 ) len = 16;
       if((len+2*x) >16 ) len = 16-2*x;//time:14-04-09 rngang
    if(y>4 || y<0) return;
    olcd_writeCommand(y_offset[y-1]+x);
    while(len--)
    {
	olcd_writeData(*str++);
    }
}
void olcd_dispstrhex(INT8 x, INT8 y, UINT8 *str, UINT8 len)
{
    const UINT8   y_offset[4] = {0x80, 0x90, 0x88, 0x98};
    //if(y>4 || y<0 || (x+len)>16) return;
//    if(len >16 ) len = 16;
       if((len+2*x) >16 ) len = 16-2*x;//time:14-04-09 rngang
    if(y>4 || y<0) return;
    olcd_writeCommand(y_offset[y-1]+x);
    while(len--)
    {
	olcd_writeData(*str++);
    }
}

void olcm_dispprintf(INT8 x, INT8 y, char *fmt,...)
{
    va_list ap;
    char str[30];
    va_start(ap,fmt);
    vsprintf(str,fmt,ap);
    //olcm_wrtstr(posx, posy, str, 1);
    olcd_dispstr(x,y,str,strlen(str));
    va_end(ap);
}

void olcd_init(void)
{
    //DDPCON = 0x00;
    PORTSetPinsDigitalOut(IOPORT_G, BIT_12 | BIT_13| BIT_14);
    PORTSetPinsDigitalOut(IOPORT_A, BIT_7);
    PORTSetPinsDigitalOut(IOPORT_B, BIT_6| BIT_7);//����,run

    PORTSetPinsDigitalOut(IOPORT_D, BIT_8 | BIT_9| BIT_10| BIT_11| BIT_12);//����ɨ�����
    PORTSetPinsDigitalIn(IOPORT_B, BIT_12 | BIT_13| BIT_14| BIT_15);//����ɨ������
   // if(mPORTGReadBits(BIT_1) !=0) //���Ϊ2��˵����������  2����Ϊû�й���pin��

     mPORTBSetBits(BIT_6);//����
     //   mPORTBClearBits(BIT_6);

    mPORTAClearBits(BIT_7);
    delay_ms(35);
    mPORTASetBits(BIT_7);
    olcd_writeCommand(FUNC_BASE_SET);
    olcd_writeCommand(0x03);
    olcd_writeCommand(0x0C);
    olcd_writeCommand(CLEAR_SCREEN);
    olcd_writeCommand(POINT_SET_RIGHT);
    olcd_writeCommand(0x80);
}