/*
 * File:   disp.c
 * Author: jereh
 *
 * Created on 2014_01_14
 */
#include "../includes/global_def.h"

#define     disp_enable()         mPORTGSetBits(BIT_15)
#define     disp_disable()        mPORTGClearBits(BIT_15)

#define     latch_enable()         mPORTGSetBits(BIT_15)
#define     latch_disable()        mPORTGClearBits(BIT_15)
#define     sda_high()            mPORTCSetBits(BIT_2)
#define     sda_low()             mPORTCClearBits(BIT_2)
#define     sck_high()            mPORTCSetBits(BIT_1)
#define     sck_low()             mPORTCClearBits(BIT_1)

unsigned char disp_num[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
//static const unsigned char  NUMCODETAB[12]={0x84,0x9F,0xC8,0x8A,0x93,0xA2,0xA0,0x8F,0x80,0x82,0xC1,0xFF};
static const unsigned char  NUMCODETAB[12]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x73,0x00};
//static const unsigned char  NUMCODETAB[12]={0xc0,0xf9,0xa4,0xb0, 0x99,0x92,0x82,0xf8,0x80,0x90,0x00,0xFF};//,0x88,0x83, 0xc6,0xa1,0x86,0x8e};
//static const UINT8 lable[16] = {2,3,4,5,6,7,1,0,11,10,9,8,12,13,14,15};
//static const UINT8 lable[16] = {6,7,8,9,10,11,0,1,2,3,4,5,12,13,14,15};
//static const UINT8 lable[16] = {15,14,13,12,5,4,3,2,1,0,11,10,9,8,7,6};
static const UINT8 lable[16] = {6,7,8,9,10,11,0,1,2,3,4,5,12,13,14,15};
#define  ODISP_CLK      50

static void odisp_transChar(unsigned char byte)
{
    unsigned char i,j;
     for(i=0;i<8;i++)
    {
         if(byte&0x80)              sda_high();
         else                       sda_low();
         sck_low();
         for(j=0;j<ODISP_CLK;j++);
         sck_high();//sck_low();
 //        for(j=0;j<ODISP_CLK;j++);
//         sck_low();
         byte<<=1;
     }
}
#if 0
static void odisp_transChar(unsigned char byte)
{
    unsigned char i,j;
     for(i=0;i<8;i++)
    {
         if(byte&0x01)              sda_high();
         else                       sda_low();
         sck_high();
         for(j=0;j<ODISP_CLK;j++);
         sck_low();
         for(j=0;j<ODISP_CLK;j++);
         sck_low();
         byte>>=1;
     }
}
#endif
static void odisp_senddispNum(void)
{
    unsigned char buf;
    int i;
    latch_disable();
 //   delay_ms(5);   //wang
//    disp_enable();
    for(i=0;i<16;i++)
//    for(i=15;i<0;i--)
    {
        //odisp_transChar(Disp_num.Integer_num[i]);
        odisp_transChar(disp_num[15-i]);
        // odisp_transChar(0x80);
    }
  //  delay_ms(5);   //wang
    //buf=0x00;
    //odisp_transChar(buf);
//    odisp_transChar(0x00);
    //disp_disable();
    latch_enable();

  //  delay_ms(15);//wang 15
    latch_disable();
}
static void odisp_sendone(void)
{
//   unsigned char buf;
  //  int i;
    latch_disable();
  //  delay_ms(5);   //wang
//    disp_enable();
#if 0
    for(i=0;i<16;i++)
    {
        odisp_transChar(disp_num[15-i]);
    }
#endif
    latch_enable();

  //  delay_ms(5);//wang 15
    latch_disable();
}

void odisp_clr(void)
{
	memset(&disp_num[0], 0xFF, 16);
	odisp_senddispNum();

}
void odisp_p(void)
{
  	memset(&disp_num[0], 0x73, 16);
	odisp_senddispNum();
}

void odisp_num(float fnum)
{
    UINT8 i, str[12];
    UINT32  int_data;
    UINT32 mDiv = 100000;
    UINT8  vMod = 0;
    BOOL   bOK = FALSE;

        sprintf(str,"%.02f",fnum);
        fnum = atof(str)*100;
	sprintf(str,"%.02f",fnum);
	int_data = atof(str);

    for(i = 0; i <6 ;i++)
    {
        vMod = int_data/mDiv;
        disp_num[lable[i]] = NUMCODETAB[vMod];
        if(vMod != 0 || i==3 ) bOK = TRUE;
        if(vMod == 0 && bOK == FALSE){
            disp_num[lable[i]] = 0x00;
        }
        int_data %= mDiv;
        mDiv /=10;
    }
 //   disp_num[5] &= 0x7F;
        disp_num[9] |= 0x80;
    //if(TRUE == bDisp)  odisp_senddispNum();
}


void odisp_sum(float fsum)
{
    UINT8 i, str[12];
    UINT32 int_data;
    UINT32 mDiv = 100000;
    UINT8  vMod = 0;
    BOOL  bOK = FALSE;
	sprintf(str,"%.02f",fsum);
	//int_data = atof(str)*100;
	fsum = atof(str)*100;
	sprintf(str,"%.02f",fsum);
	int_data = atof(str);
    for(i = 0; i <6 ;i++)
    {
        vMod = int_data/mDiv;
        disp_num[lable[6+i]] = NUMCODETAB[vMod];
        if(vMod != 0 || i==3 ) bOK = TRUE;
        if(vMod == 0 && bOK == FALSE){
            disp_num[lable[6+i]] = 0x00;
        }
        int_data %= mDiv;
        mDiv /=10;
    }
//    disp_num[10] &= 0x7F;
         disp_num[3] |= 0x80;
    //if(TRUE == bDisp)  odisp_senddispNum();
}

void odisp_sum2(float fsum)
{
    UINT8 i;//, str[12];
  //  UINT32 int_data;
    UINT32 mDiv = 100000;
    UINT8  vMod = 0;
    BOOL  bOK = FALSE;
    UINT32 mnum = (UINT32)(fsum*100);
	//sprintf(str,"%.02f",fsum);
	//int_data = atof(str)*100;
	//fsum = atof(str)*100;
	//sprintf(str,"%.02f",fsum);
	//int_data = atof(str);
    for(i = 0; i <6 ;i++)
    {
       // vMod = int_data/mDiv;
        vMod = (int)mnum/mDiv;
        disp_num[lable[6+i]] = NUMCODETAB[vMod];
        if(vMod != 0 || i==3 ) bOK = TRUE;
        if(vMod == 0 && bOK == FALSE){
            disp_num[lable[6+i]] = 0x00;
        }
       // int_data %= mDiv;
        mnum %= mDiv;
        mDiv /=10;
    }
//    disp_num[10] &= 0x7F;
         disp_num[3] |= 0x80;
    //if(TRUE == bDisp)  odisp_senddispNum();
}
void odisp_price(float fprice, BOOL bDisp)
{
    UINT8 i,str[12];
    UINT16 int_data ;//= vprice;//fprice*100;
    UINT16 mDiv = 1000;
    UINT8  vMod = 0;
    BOOL  bOK = FALSE;
    float f1;
//    sprintf(str,"%.02f",fprice);
 //       fprice = atof(str);
//	sprintf(str,"%.02f",fprice);
//	int_data = atof(str);
//    int_data =sys_get_float(fprice)*100;
//f1 = (atof(str)*10000)/100;
f1=(fprice*1000)/10;
    int_data = f1;
    for(i = 0; i <4 ;i++)
    {
        vMod = int_data/mDiv;
        disp_num[lable[12+i]] = NUMCODETAB[vMod];
        if(vMod != 0 || i==1 ) bOK = TRUE;
        if(vMod == 0 && bOK == FALSE){
            disp_num[lable[12+i]] = 0x00;
        }
        int_data %= mDiv;
        mDiv /=10;
    }
 //   disp_num[13] &= 0x7F;
       disp_num[13] |= 0x80;
    if(TRUE == bDisp)  odisp_senddispNum();
}

void odisp_disp(float fsum,float fnum, BOOL bEnd)
{
    odisp_num(fnum);
    odisp_sum(fsum);
    if( TRUE == bEnd)
    {
//	disp_num[0] = 0x73;
//	disp_num[6] = 0x73;
    }
    odisp_senddispNum();
}
void odisp2_disp(float fsum,float fnum, BOOL bEnd)
{
    odisp_num(fnum);
    odisp_sum2(fsum);
    if( TRUE == bEnd)
    {
//	disp_num[0] = 0x73;
//	disp_num[6] = 0x73;
    }
    odisp_senddispNum();
}
#define DISP_INIT_DELAY_CNT      10000//8500

void odisp_init(void)
{
//	UINT8 n = 0;
    PORTSetPinsDigitalOut(IOPORT_G, BIT_15);
    PORTSetPinsDigitalOut(IOPORT_C, BIT_1|BIT_2);
    mPORTCClearBits(BIT_1|BIT_2);
    mPORTGClearBits(BIT_15);
#if 0
    delay_ms(100);
    for(n=0; n<10; n++)
	{
		memset(&disp_num[0], NUMCODETAB[n], 16);
		odisp_senddispNum();
                olcm_dispprintf(0,3,"系统初始化");
		delay_ms(DISP_INIT_DELAY_CNT);
	}
	memset(&disp_num[0], 0xFF, 16);
//#else
        memset(&disp_num[0], NUMCODETAB[0], 16);
        odisp_senddispNum();
        olcm_dispprintf(5,2,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        delay_ms(2000);
        memset(&disp_num[0], NUMCODETAB[1], 16);
        odisp_senddispNum();
        olcm_dispprintf(6,2,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[2], 16);
        odisp_senddispNum();
        olcm_dispprintf(7,2,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[3], 16);
        odisp_senddispNum();
        olcm_dispprintf(0,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);

        memset(&disp_num[0], NUMCODETAB[4], 16);
        odisp_senddispNum();
        olcm_dispprintf(1,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[5], 16);
        odisp_senddispNum();
        olcm_dispprintf(2,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[6], 16);
        odisp_senddispNum();
        olcm_dispprintf(3,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[7], 16);
        odisp_senddispNum();
        olcm_dispprintf(4,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);

        memset(&disp_num[0], NUMCODETAB[8], 16);
        odisp_senddispNum();
        olcm_dispprintf(5,3,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[9], 16);
        odisp_senddispNum();
        olcm_dispprintf(6,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);

        memset(&disp_num[0], 0xFF, 16);

	odisp_price(cur_price, TRUE);
	odisp_disp(0, 0, TRUE);
#endif
}

void odisp_init_chk(void)
{

        UINT8 n = 0,i=0;
#if 0
        for(i=0;i<12;i++)
        {
        disp_num[i]=NUMCODETAB[i];}
        disp_num[12]=0x3f;//,0x06,0x5b,0x4f
        disp_num[13]=0x06;
        disp_num[14]=0x5b;
        disp_num[15]=0x4f;
        odisp_senddispNum();
        delay_ms(4000);
#endif
#if 1
        memset(&disp_num[0], NUMCODETAB[0], 16);
        odisp_senddispNum();
        olcm_dispprintf(5,2,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        delay_ms(2000);

        memset(&disp_num[0], NUMCODETAB[1], 16);
        odisp_senddispNum();
        olcm_dispprintf(6,2,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[2], 16);
        odisp_senddispNum();
        olcm_dispprintf(7,2,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[3], 16);
        odisp_senddispNum();
        olcm_dispprintf(0,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);

        memset(&disp_num[0], NUMCODETAB[4], 16);
        odisp_senddispNum();
        olcm_dispprintf(1,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[5], 16);
        odisp_senddispNum();
        olcm_dispprintf(2,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[6], 16);
        odisp_senddispNum();
        olcm_dispprintf(3,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[7], 16);
        odisp_senddispNum();
        olcm_dispprintf(4,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);

        memset(&disp_num[0], NUMCODETAB[8], 16);
        odisp_senddispNum();
        olcm_dispprintf(5,3,">>"); delay_ms(DISP_INIT_DELAY_CNT);
        memset(&disp_num[0], NUMCODETAB[9], 16);
        odisp_senddispNum();
        olcm_dispprintf(6,3,">>");  delay_ms(DISP_INIT_DELAY_CNT);

        memset(&disp_num[0], 0x00, 16);
        Runled_tick = gTick + 150; //防止出现请预冷的字样150730
	odisp_price(cur_price, TRUE);
	odisp_disp(0, 0, TRUE);
#endif
}
void dssp()
{
    odisp_senddispNum();
}

void dsspone()
{
    odisp_sendone();
}

//QingLing

BOOL qzql(void)
{
    UINT8 i = 0;
    UINT16 j;
    UINT8 len = 0;
    Send_Buf[0] = 0xcd;
    Send_Buf[1] = 0xfa;
    Send_Buf[2] = se_cmdnu;
    Send_Buf[3] = 9 + len;
    Send_Buf[4] = 0x06;
    Send_Buf[5] = 0x60;
    j = omodbus_crc16(Send_Buf, 6 + len);
    Send_Buf[6 + len] = (j >> 8);
    Send_Buf[7 + len] = j;
    Send_Buf[8 + len] = 0xdc;
    Companybufleng = 9 + len; //总长度
    uart_state = 1;
    do {
        re_over_tick = 0;
        INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
        Company_sendstr(9 + len, (UINT8 *) & Send_Buf[0]);
        i++;
wait0:
        if ((re_over_tick < COMPANY_OVERTIME) && (RecvUnit_ok == 0)) goto wait0;
    } while (((RecvUnit_ok == 0) || (Recv_Buf[4] != 0xaa) || (re_over_tick >= COMPANY_OVERTIME)) && (i < 3));
    RecvUnit_ok = 0;
    re_over_tick = 0;
    uart_state = 0;
    if (i >= 3)
    {
        return FALSE;
    } 
    else
    {
        if (se_cmdnu > 255)
            se_cmdnu = 0;
        else
            se_cmdnu++;
        return TRUE;
    }
}
//QingLing
void DisplayClear(void)
{
   if(TRUE !=qzql())
    {
       SOEACTION1(PRO422_ERR,eCurRunState);
    }
    if(FALSE == Sys_Input_Cp())//rg170619 输入车牌号
    {
	    	olcm_dispprintf(0,4,"输入失败        ");
		delay_ms(3000);
    }
    else
    {
	    	olcm_dispprintf(0,4,"输入成功请加气  ");
		delay_ms(3000);
    }
    eCurRunState = State_MainUI;
    eVirtualKey = _KEY_EXIT_EV_;
}
