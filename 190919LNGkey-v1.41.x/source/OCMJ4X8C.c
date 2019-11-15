#include "../includes/global_def.h"
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
#define uint  unsigned int
#define uchar unsigned char
#define xx1    0x80
#define xx2    0x88
#define yy     0x80
#define comm  0
#define dat   1

void wr_lcd (uchar dat_comm,uchar content);
void delay (uint us);
void delay1 (uint ms);

static const unsigned char  tab1[]={
"杰瑞-lng加气机"
"请预冷"
"1234567890"
"abcdefgABCDEF"
};

static const unsigned char  tab31[]={
"杰瑞-lng加气机"
"1234567890"
};

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
BOOL olcd_checkBusy( void )
{
#if 0
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
unsigned char olcd_readData( void )
{
     if(olcd_checkBusy())
     {
        olcd_writeByte(0xfe);            //11111,RW(1),RS(1),0
        return olcd_receiveByte();
     }
}
void olcd_writeCommand( unsigned char Cbyte )
{
#if 1
     CS_High;
     if(olcd_checkBusy())
     {
        olcd_writeByte(0xf8);            //11111,RW(0),RS(0),0
        olcd_writeByte(0xf0&Cbyte);      //???
        olcd_writeByte(0xf0&Cbyte<<4);   //???(???<<)
     }
     CS_Low;
#endif
 
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
/*------------------初始化-----------------*/
void olcd_init(void)
//void init_lcd (void)
{

    PORTSetPinsDigitalOut(IOPORT_G, BIT_12 | BIT_13| BIT_14);
    PORTSetPinsDigitalOut(IOPORT_A, BIT_7);
    PORTSetPinsDigitalOut(IOPORT_B, BIT_6| BIT_7);//背光,run

    PORTSetPinsDigitalOut(IOPORT_D, BIT_8 | BIT_9| BIT_10| BIT_11| BIT_12);//按键扫描输出
    PORTSetPinsDigitalIn(IOPORT_B, BIT_12 | BIT_13| BIT_14| BIT_15);//按键扫描输入
      mPORTBSetBits(BIT_6);//点亮
 
    mPORTAClearBits(BIT_7);
    delay_ms(35);
    mPORTASetBits(BIT_7);
    olcd_writeCommand(FUNC_BASE_SET);
    olcd_writeCommand(0x01);
    delay_ms(35);
    olcd_writeCommand(0x06);
    olcd_writeCommand(0x0b);
  delay1 (100);
  olcd_writeCommand(0x30);  /*30---基本指令动作*/
  olcd_writeCommand(0x01);  /*清屏，地址指针指向00H*/
  delay (100);
  olcd_writeCommand(0x06);  /*光标的移动方向*/
  olcd_writeCommand(0x0c);  /*开显示，关游标*/
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
          if((len+2*x) >16 ) len = 16-2*x;//time:14-04-09 rngang
    if(y>4 || y<0) return;
    olcd_writeCommand(y_offset[y-1]+x);
    while(len--)
    {
	olcd_writeData(*str++);
    }
}
/*---------------显示汉字或字符----------------*/
void chn_disp (const unsigned char *chn)
{
  uchar i,j;
  olcd_writeCommand(0x30);
  olcd_writeCommand(0x80);
  for (j=0;j<4;j++)
  {
    for (i=0;i<16;i++)
    olcd_writeData(chn[j*16+i]);
  }
}
/*-----------上半屏显示汉字或字符------------*/
void chn_disp1 (const unsigned char *chn)
{
  uchar i,j;
  olcd_writeCommand(0x30);
 olcd_writeCommand(0x80);
  j=0;
  for (i=0;i<16;i++)
  olcd_writeData(chn[j*16+i]);
  olcd_writeCommand(0x90);
  j=1;
  for (i=0;i<16;i++)
  olcd_writeData(chn[j*16+i]);
}
/*----------------显示图形-----------------*/
void img_disp (const unsigned char *img)
{
  uchar i,j;
  for(j=0;j<32;j++)
  {
    for(i=0;i<8;i++)
    {
      olcd_writeCommand(0x34);
      olcd_writeCommand(yy+j);
      olcd_writeCommand(xx1+i);
      olcd_writeCommand(0x30);
      olcd_writeData(img[j*16+i*2]);
      olcd_writeData(img[j*16+i*2+1]);
    }
  }
  for(j=32;j<64;j++)
  {
    for(i=0;i<8;i++)
    {
     olcd_writeCommand(0x34);
      olcd_writeCommand(yy+j-32);
     olcd_writeCommand(xx2+i);
      olcd_writeCommand(0x30);
      olcd_writeData(img[j*16+i*2]);
      olcd_writeData(img[j*16+i*2+1]);
    }
  }
  olcd_writeCommand(0x36);
}
/*-------------下半屏显示图形--------------*/
void img_disp1 (const unsigned char *img)
{
  uchar i,j;
  for(j=0;j<32;j++)
  {
    for(i=0;i<8;i++)
    {
      olcd_writeCommand(0x34);
      olcd_writeCommand(yy+j);
      olcd_writeCommand(xx2+i);
      olcd_writeCommand(0x30);
      olcd_writeData(img[j*16+i*2]);
      olcd_writeData(img[j*16+i*2+1]);
    }
  }
  olcd_writeCommand(0x36);
}
/*--------------显示点阵----------------*/
void lat_disp (uchar data1,uchar data2)
{
  uchar i,j,k,x;
  x=xx1;
  for(k=0;k<2;k++)
  {
    for(j=0;j<16;j++)
    {
      for(i=0;i<8;i++)
      {
        olcd_writeCommand(0x34);
       olcd_writeCommand(yy+j*2);
        olcd_writeCommand(x+i);
        olcd_writeCommand(0x30);
        olcd_writeData(data1);
        olcd_writeData(data1);
      }
      for(i=0;i<8;i++)
      {
        olcd_writeCommand(0x34);
        olcd_writeCommand(yy+j*2+1);
       olcd_writeCommand(x+i);
        olcd_writeCommand(0x30);
        olcd_writeData(data2);
        olcd_writeData(data2);
      }
    }
    x=xx2;
  }
  olcd_writeCommand(0x36);
}
/*-----------------------------------------------*/
//当data1=0xff,data2=0xff时,在x0,y0处反白显示16xl*yl.
void con_disp (uchar data1,uchar data2,uchar x0,uchar y0,uchar xl,uchar yl)
{
  uchar i,j;
  for(j=0;j<yl;j++)
  {
    for(i=0;i<xl;i++)
    {
      olcd_writeCommand(0x34);
      olcd_writeCommand(y0+j);
      olcd_writeCommand(x0+i);
      olcd_writeCommand(0x30);
      olcd_writeData(data1);
      olcd_writeData(data2);
    }
  }
  olcd_writeCommand(0x36);
}
/*--------------清DDRAM------------------*/
void clrram (void)
{
  olcd_writeCommand(0x30);
  olcd_writeCommand(0x01);
  delay1 (180);
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

/*-----------------------------------*/
void delay (uint us)   //delay time
{
  while(us--);
}
void delay1 (uint ms)
{
  uint i,j;
  for(i=0;i<ms;i++)
  for(j=0;j<15;j++)
  delay(1);
}
/*------------------主程序--------------------*/
void cce()
{
  olcd_init();
  clrram();
 	lat_disp (0x00,0x00);
	clrram();

	chn_disp (tab1);
	delay1 (4000);
    con_disp (0xff,0xff,0x8c,0x80,2,16);
      con_disp (0xff,0xff,0x80,0x80,8,64);
}
