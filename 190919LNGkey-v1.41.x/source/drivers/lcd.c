/*
 * File:   lcd.c
 * Author: jereh
 *
 * Created on 2014_01_14
 */
#include "../includes/global_def.h"

//PORTB.0-CS;
//PORTA-6:SDI;
//PORTA-7:SCK
#define CONFIG               (CN_ON)
#define PINS                 (CN16_ENABLE)
#define PULLUPS              (CN15_PULLUP_ENABLE | CN16_PULLUP_ENABLE)
#define INTERRUPT            (CHANGE_INT_ON | CHANGE_INT_PRI_2)
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
#if 0
void DispBytes(unsigned char *p,unsigned char row,unsigned char col )
{
    unsigned char i,len;
    len=strlen(p);
    PutStr(row,col);
    for(i=0;i<len;i++)
    {
        olcd_writeData(*p);
        p++;
    }
}





void PutStr(unsigned char row,unsigned char col)
{
    unsigned char DISP_TABLE[]={
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,      //line1
        0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,      //line2
        0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,       //line3
        0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,       //line4
    };

    olcd_writeCommand(0x30);      //8BitMCU,??????
     olcd_writeCommand(DISP_TABLE[8*row+col]);      //????
     if(row==4) row=0;      //?????,??????
     olcd_writeCommand(DISP_TABLE[8*row+col]);
}


void DispBytes(unsigned char *p,unsigned char row,unsigned char col )
{
    unsigned char i,len;
    len=strlen(p);
    PutStr(row,col);
    for(i=0;i<len;i++)
    {
        olcd_writeData(*p);
        p++;
    }
}
void White(unsigned char r0,unsigned char r1)
{
        olcd_writeCommand(FUNC_EXT_SET);      //??????
        olcd_writeCommand((r0&0xFE)|((r1&0xFE)<<1));
}


unsigned char* TransNum(unsigned char * buf,unsigned long int bbb)
{
        unsigned char i,k;
        unsigned char back0=0;
	unsigned char base=0x30;
	unsigned char num[5];
        unsigned char index=0;

	num[4]= bbb % 10;
	num[3]=(bbb % 100)/10;
	num[2]=(bbb % 1000)/100;
	num[1]=(bbb % 10000)/1000;
	num[0]=bbb/10000;
	for (i=0;i<5;i++)
	{
                if (num[i]!=0||back0==1)
		{   back0=1;
 			buf[index++]=num[i]+base;
		}
	}
	buf[index]='\0';
	if (bbb==0) {buf[0]=0x30;buf[1]='\0';}
        return buf;
}
//???
void delay(unsigned int count)
{
    while(--count);
}
void Set_Draw(void)
{
	delay(20);				//??
	olcd_writeCommand(0x36);
	delay(20);					//??
}
void Draw_Pic(unsigned char x, unsigned char y, unsigned char *Draw)
{
	unsigned char i, j, temp_x, temp_y;
	temp_x = x;
        temp_y = y;
	temp_x |= 0x80;					//
	temp_y |= 0x80;					//
	for(i=0;i<32;i++ )				//???32?
	{
		olcd_writeCommand(temp_y++);		//??????Y????0
		olcd_writeCommand(temp_x);		//??????X????0
		for(j=0;j<16;j++)			//
		{
			 WriteData(*Draw++);	//
		}
	}

	temp_x = 0x88;					//
	temp_y = 0x80;					//
	j = 0; 	 						//
	for(;i<64;i++ )
	{
		olcd_writeCommand(temp_y++);		//??????Y????
		olcd_writeCommand(temp_x);	 	//??????X????
		for(j=0;j<16;j++)
		{
			 WriteData(*Draw++);	//
		}
	}

}



void Set_White(unsigned char x,unsigned char y,unsigned char end_x,unsigned char clear)
{
    unsigned char i,j,white_x,white_y,white_end_x,clr_x,clr_y;//??
    white_end_x=(end_x-x+1);
    white_end_x<<=1;
    if(y==1)
    {
        white_x=(0x80+x-1);
        white_y=0x80;
        clr_x=0x80;
        clr_y=0x80;
    }
    else if(y==2)
    {
        white_x=(0x80+x-1);
        white_y=0x90;
        clr_x=0x80;
        clr_y=0x90;
    }
    else if(y==3)
    {
    white_x=(0x88+x-1);
    white_y=0x80;
    clr_x=0x88;
    clr_y=0x80;}
    else if(y==4)
    {
    white_x=(0x88+x-1);
    white_y=0x90;
    clr_x=0x88;
    clr_y=0x90;}
    if(clear==0)//????????????????????????y?
    {
      for(i=0;i<16;i++) //16?
      {
        olcd_writeCommand(clr_y++);//??????Y????0
        olcd_writeCommand(clr_x);  //??????X????0
        for(j=0;j<16;j++)
        {
        WriteData(0x00);//?????
        }
       }
    }
   for(i=0;i<16;i++) //16?????16*16??
   {
    olcd_writeCommand(white_y++);//??????Y????0
    olcd_writeCommand(white_x);//??????X????0
        for(j=0;j<white_end_x;j++)
        {if(clear==1)
            {
            WriteData(0x00);//??????8?????????????1
                            //??????????????????
            }
        else
            {
            WriteData(0xff);//??????8??????????1
                    //??????????????????
            }
         }
    }
 }
#endif
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

void lcd_key_init(void)
{   //190909
    //DDPCON = 0x00;
    PORTSetPinsDigitalOut(IOPORT_G, BIT_12 | BIT_13| BIT_14);
    PORTSetPinsDigitalOut(IOPORT_A, BIT_7);
    PORTSetPinsDigitalOut(IOPORT_B, BIT_6| BIT_7);//背光,run

    PORTSetPinsDigitalOut(IOPORT_D, BIT_8 | BIT_9| BIT_10| BIT_11| BIT_12);//按键扫描输出
    PORTSetPinsDigitalIn(IOPORT_B, BIT_12 | BIT_13| BIT_14| BIT_15);//按键扫描输入
   // if(mPORTGReadBits(BIT_1) !=0) //检测为2，说明是正常启动  2是因为没有过滤pin脚

     mPORTBSetBits(BIT_6);//点亮
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

const INT8  UI_TIPS[][16]={
  "设置成功",
  "设置失败",
  "请输入密码",
  "请输入时间",
  "__年__月__日",
  "__时__分__秒",
  "输入有误",
  "测试结束",
};

void olcd_tip_msg(UINT8 x, UINT8 y, UINT8 id)
{
   olcd_dispstr(x, y, (UINT8 *)&UI_TIPS[id][0], strlen((UINT8 *)&UI_TIPS[id][0]));
}