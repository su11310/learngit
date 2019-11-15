/*
 * File:   key.c
 * Author: jereh
 *
 * Created on 2014_01_14
 */
#include "../includes/global_def.h"

#define  OLD_KEY 0

#define KEY_I2C_BUS              I2C1
#define KEY_ADDRESS              0x70
#define I2C_CLOCK_FREQ           6000
static const UINT8 _key_row_pin[] =  {15,14,13,12};  //读

static const UINT8 _key_col_pin[] = { 8, 9, 10, 11,12};//写
void   okey_write_data(UINT8 addr, UINT8 data)
{
    i2c_init(KEY_I2C_BUS, KEY_ADDRESS, I2C_CLOCK_FREQ);
    i2c_write(KEY_I2C_BUS, KEY_ADDRESS, addr, data);
}
UINT8  okey_read_data(UINT8 addr)
{
    i2c_init(KEY_I2C_BUS, KEY_ADDRESS, I2C_CLOCK_FREQ);
    return i2c_read(KEY_I2C_BUS, KEY_ADDRESS, addr);
}

void okey_operat_mod()
{

    //okey_write_data(0x01, 0x0F);  //debunce time
    //okey_write_data(0x01, 0x00);  //debunce time 00-->0x0F
    okey_write_data(0x01, 0x1F);  //debunce time 00-->0x0F
    //okey_write_data(0x02, 0x99);  //
    okey_write_data(0x02, 0x00);  // okey_write_data(0x02, 0x80);   okey_write_data(0x02, 0x81);
    //okey_write_data(0x03, 0x08);
    okey_write_data(0x03, 0x00);
    //okey_write_data(0x05, 0x0E);
    //okey_write_data(0x04, 0xB9);
    okey_write_data(0x04, 0x81);
}
///OK  00 80 00 80 0E
void okey_init(void)
{
   // PORTSetPinsDigitalIn(IOPORT_E, BIT_9);
 //   i2c_init(KEY_I2C_BUS, KEY_ADDRESS, I2C_CLOCK_FREQ);
 //   okey_operat_mod();
    //IEC0CLR = 0x00000800;        // disable INT2
    //INTDisableInterrupts();
}
#if 0
const UINT8 KEY_MAP[]={
    0x0B /*KEY_0*/, 0x00/*KEY_1*/, 0x08/*KEY_2*/ , 0x10/*KEY_3*/ , 0x01/*KEY_4*/
    , 0x09/*KEY_5*/, 0x11/*KEY_6*/, 0x02/*KEY_7*/, 0x0A/*KEY_8*/, 0x12/*KEY_9*/
    , 0x1B/*KEY_SET*/, 0x03/*KEY_POINT*/, 0x22/*KEY_QRY*/, 0x21/*KEY_EXIT*/, 0x20/*KEY_STOP*/
    , 0x19/*KEY_GAS*/, 0x18/*KEY_COOL*/, 0x1A/*KEY_SWITCH*/, 0x13/*KEY_ENTER*/, 0x23/*KEY_UP*/,
};
#else
const UINT8 KEY_MAP[]={
    0x0B /*KEY_0*/, 0x00/*KEY_1*/, 0x08/*KEY_2*/ , 0x10/*KEY_3*/ , 0x01/*KEY_4*/
    , 0x09/*KEY_5*/, 0x11/*KEY_6*/, 0x02/*KEY_7*/, 0x0A/*KEY_8*/, 0x12/*KEY_9*/
    , 0x1B/*KEY_SET*/, 0x03/*KEY_POINT*/, 0x22/*KEY_QRY*/, 0x21/*KEY_EXIT*/, 0x20/*KEY_STOP*/
    , 0x19/*KEY_GAS*/, 0x18/*KEY_COOL*/, 0x1A/*KEY_SWITCH*/, 0x13/*KEY_ENTER*/, 0x23/*KEY_UP*/,
};
#endif
UINT8 okey_scan_ex_io(void)    //返回的值必须是确定的，读到1次的不能返回
{


    static UINT8 pre_key = KEY_NONE;
    UINT8 key = KEY_NONE;
    UINT8 key1 = KEY_NONE;
    UINT8 count = 0;
    UINT8 i = 0;
    UINT32 matrix = 0;


    //matrix key scan
    for (i = 0; i < 5; ++i)
    {
      UINT8 j;
      for (j = 0; j < 5; ++j)
      {
        if (j == i)
            mPORTDSetBits((1 << _key_col_pin[j]));//拉高
       //   GPIO_setBits(_key_row_port[j], _key_row_pin[j]);
        else
            mPORTDClearBits((1 << _key_col_pin[j]));
        //  GPIO_ReSetBits(_key_row_port[j], _key_row_pin[j]);
      }
      for(j = 0; j < 4; ++j)
      {
        matrix <<= 1;
      //  matrix |= GPIO_ReadInputDataBit(_key_col_port[j], _key_row_pin[j]);
         matrix |=(mPORTBReadBits((1 << _key_row_pin[j])) >> _key_row_pin[j]); //???????是否为：“1”“0”
      //  matrix =mPORTBReadBits((1 << _key_row_pin[j]));
      }
    }
    for (i = 0; i < 5; ++i)
     // GPIO_ResetBits(_key_row_port[i], _key_row_pin[i]);
       mPORTDSetBits((1 << _key_col_pin[i]));//拉高
    for (i = 0; i < 20; ++i){
        if (matrix & 1){
            switch(count)
            {
                case 0:
                    key = i;
                    break;
                case 1:
                    key1 = i;
                    break;
                default:
                    key = i;
                    break;
            }
            ++count;
        }
        matrix >>= 1;
    }
////////键值如下

  //   16 /*KEY_1*/, 17/*KEY_2*/,18/*KEY_3*/ , 19/*KEY_复显*/ ,
  //   12/*KEY_4*/ , 13/*KEY_5*/, 14/*KEY_6*/, 15/*KEY_GAS*/,
  //   8/*KEY_7*/, 9/*KEY_8*/ , 10/*KEY_9*/, 11/*KEY_STOP*/,
  //   4/*KEY_POINT*/, 5/*KEY_0*/, 6/*KEY_ENT*/, 7/*KEY_更改*/,
 //    0/*KEY_SET*/, 1/*KEY_UP*/, 2/*KEY_DOWN*/, 3/*KEY_SELECT*/,

    //此处向下，验证值和两次进入为准

    switch (count) {
    case 0:
            pre_key = KEY_NONE; //上一次
            key  = KEY_NONE;  //返回值
        	break;
    case 1:
        if (pre_key != KEY_NONE)
        {
           if(key!=KEY_NONE)
            {  switch(key)
                {
                 case 16: key = 0x02;break; //1
                 case 17: key = 0x03;break; //2
                 case 18: key = 0x04;break;//3
                 case 12: key = 0x05;break;//4
                 case 13: key = 0x06;break;//5
                 case 14: key = 0x07;break; //6
                 case 8: key = 0x08;break; //7
                 case 9: key = 0x09;break; //8
                 case 10: key = 0x0A;break; //9
                 case 4: key = 0x0C;break; //.
                 case 5: key = 0x01;break; //0
                 case 6: key = 0x13;break; //ENT
                 case 0: key = 0x0B;break; //set
                 case 1: key = 0x14;break; //up
                 case 2: key = 0x12;break; //down
                 case 15: key = 0x10;break; //gas
                 case 11: key = 0x0F;break; //stop
                 case 7: key = 0x0E;break; //exit
                 case 3: key = 0x0D;break;  //select
                    default :break;

                }
            pre_key = KEY_NONE;
           return key;
            }

        }
        else
        {
          pre_key = key;
          key = KEY_NONE;
          return key;
        }
           
        break;
        
    case 2:
        if (pre_key != KEY_NONE)
        {
           if(key!=KEY_NONE)
            {  
                if(((key == 1)&&(key1 == 2))||((key == 2)&&(key1 == 1)))
                {
                    key = 0x21;
                }
                 pre_key = KEY_NONE;
                return key;
            }

        }
        else
        {
          pre_key = key;
          key = KEY_NONE;
          return key;
        }
        break;
        
    default: //ignore multiple key pressing simultaneously
        pre_key = KEY_NONE;
        key = KEY_NONE;
    }
    ///////////////////////////////////////////
    ///////////////////////////////////

      
      
         
           
 }
UINT8 okey_scan_ex(void)
{
    UINT8 keyreg = 0;
    UINT8 prekey =0;//
    UINT32 keyscanTIME =0;
    UINT8 n, rdkeyv = 0;
    delay_ms(200);
 keyreg = okey_read_data(0x03);
 if(keyreg & 0x20)
  {
     rdkeyv = (okey_read_data(0x00)&0x3F);
      for(n=0; n<20; n++)
      {
         if(rdkeyv == KEY_MAP[n])// return n+1;
         prekey = n+1;
      }
   keyscanTIME =gTick +15;
   while(gTick < keyscanTIME)
     {  keyreg = okey_read_data(0x03);
        if(keyreg & 0x20)
        {
            rdkeyv = (okey_read_data(0x00)&0x3F);
            for(n=0; n<20; n++)
            {
                if(rdkeyv == KEY_MAP[n])// return n+1;
                prekey = n+1;
            }
        }
        else
        {
            if(prekey!=0)
            {  switch(prekey)
                {
                 case 0x0C: prekey = 0x02;break; //1
                 case 0x08: prekey = 0x03;break; //2
                 case 0x05: prekey = 0x04;break;//3
                 case 0x01: prekey = 0x05;break;//4
                 case 0x09: prekey = 0x06;break;//5
                 case 0x06: prekey = 0x07;break; //6
                 case 0x13: prekey = 0x08;break; //7
                 case 0x0A: prekey = 0x09;break; //8
                 case 0x07: prekey = 0x0A;break; //9
                 case 0x0B: prekey = 0x0C;break; //.
                 case 0x12: prekey = 0x01;break; //0
                 case 0x10: prekey = 0x13;break; //ENT
                 case 0x14: prekey = 0x0B;break; //set
                 case 0x0D: prekey = 0x14;break; //up
                 case 0x0E: prekey = 0x12;break; //down
                 case 0x03: prekey = 0x10;break; //gas
                 case 0x04: prekey = 0x0F;break; //stop
                 case 0x11: prekey = 0x0E;break; //exit
                 case 0x0F: prekey = 0x0D;break;  //select
                    default :break;

                }

           return prekey;
            }
            else
               return 0;

        }

    }// end of while 1
   }//end of if
   return 0;
 }
#if 0
UINT8 okey_scan(void)
{
        UINT8 n,cnt = 0;
        UINT8 iicrd = 0;
        UINT8 keyreg = 0;
        keyreg = okey_read_data(0x03);
        //if(keyreg & 0xA0)
        if(keyreg & 0x20)
        {
            //for(n=0; n<8; n++)
            do{
                iicrd = okey_read_data(0x00);
                if(0 == (iicrd & 0x40))   break;
                keyv = iicrd&0x3F;
            } while(1);
            for(n=0; n<20; n++)
            {
                if(KEY_MAP[n] == keyv )    return n+1;//okernel_putevent(n+1,1);
            }
        }
        return 0;
}
#endif


#if 0
void __ISR(_EXTERNAL_2_VECTOR, ipl2) Int2Handler(void)
{
 /*   UINT8 cnt = 0;
    UINT8 iicrd = 0;
    for(cnt = 0; cnt<8; cnt++)
    {
        iicrd = okey_read_data(0x00);
        if(!(iicrd & 0x40))   break;
        keyv = iicrd;
    } */
    //b_keyv = TRUE;
    //INTClearFlag(INT_INT2);
    mINT2ClearIntFlag();
    b_keyv = TRUE;
}
#endif



/*************************************************************************
功能：  键盘输入
参数:   pstr    - 键盘输入返回
	nmax    - 最大输入数
	bpoint  - 是否允许输入小数点
	bpsw    - 显示屏蔽为'*'
返回值：当前键值
备注：  长度nmax参数要求小于等于16
*************************************************************************/
UINT8 okeyinput_getstr(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw )
{
  UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV;
  UINT8 car_status;
  BOOL  bDot = FALSE;

  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 16 ) nmax = 16;
  //posy = ucursor.y;
  keyV = osys_getkey_ex();
   b_keyv = FALSE;
  while(1)
  {
    if((WKJQ == 0)&&((_CARD_TYPE == 2) || (_CARD_TYPE == 3)|| (_CARD_TYPE == 5))||((WKJQ ==1)&&(_CARD_TYPE < 7)&&(_CARD_TYPE>0)))                     //ss190409      (Operate_fixm != 0)|||| (_CARD_TYPE == 0)
    {
        car_status = machine_status_card();                          //增加判断卡是否被拔掉的判断    ss190409  
        if(car_status!=CPU_TYPE_A)//卡拔掉了
        {
            eVirtualKey = _KEY_EXIT_EV_;
            return FALSE;
        }
    }
      
         keyV = osys_getkey_ex(); //Sys_GetKey();
         b_keyv = FALSE;
#if 1
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
            return keyV;
        }

        if(keyV == _KEY_RET_EV_)   //exit
        {
          *retlen = len;
          return keyV;
        }
        if(keyV == _KEY_POINT_EV_ && bpt == TRUE)
        {
          if(bDot == TRUE) continue;
          tmpbuf[strlen(tmpbuf)] = '.';
          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
          bDot = TRUE;
          len += 1;
        }

        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          if (tmpbuf[len] == '.')
          {
            bDot = FALSE;
          }
          tmpbuf[len] = ' ';//tmpbuf[len] = 0; //14-02-15

          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
          tmpbuf[len] = 0x00;
        }

        //if(okey_benum(nKeyV))
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[len-1] = '*';    //14-02-15 //tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[len-1] = (keyV-1)+'0'; //14-02-15 //tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmppswbuf);
          }
          else
          {
            tmpbuf[len-1] = (keyV-1)+'0';////14-02-15//tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';//tmpbuf[strlen(tmpbuf)] = okeyinput_getvalue(nKeyV)+'0';
            strcpy(pstr,tmpbuf);
          }
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
        }
#else
     if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
     {
         tmpbuf[strlen(tmpbuf)] = '*';
     }
     else
     {
         tmpbuf[strlen(tmpbuf)] = '1';
     }
#endif
    // olcm_dispprintf(ucursor.x, posy, tmpbuf);
    //olcm_dispprintf(0, 2, tmpbuf);
 //   olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
    //__delay_cycles(73728);//delay_ms(10);
    delay_ms(20);
  }

}

#if  OLD_KEY
BOOL okey_timestr(UINT8 * tpstr)
{
   INT8 strbuf[4];
   UINT8 rdkey, len = 0,index = 0,time[6];
   cursor_x=0, cursor_y=2;
   olcd_clearsCreen();//olcm_clrscr();
   olcd_tip_msg(0,1,_eMSG_INPUT_TIME_);//otip_message(1,1,TIPS_INPUTTIME);//olcm_dispprintf(1,1,"请输入时间:");
   olcd_tip_msg(0,3,_eMSG_DATE_);////otip_message(3,1,TIPS_DATE);//olcm_dispprintf(3,1,"__年__月__日");
   olcd_tip_msg(0,4,_eMSG_TIME_);//otip_message(4,1,TIPS_TIME);//olcm_dispprintf(4,1,"__时__分__秒");

   delay_ms(100);
   //ucursor.x = 2;
   //ucursor.y = 1;
   //ucursor.eable = true;
   //ucursor.ctrl = true;
   while(index<6)
   {
      memset(strbuf, 0, sizeof(strbuf));
      rdkey = okeyinput_getstr(strbuf,&len ,2,FALSE,FALSE);
      //if(okeyinput_getstr(strbuf,&len ,2,FALSE,FALSE) == _KEY_OK_EV_ && len>0)
      if(rdkey == _KEY_OK_EV_ && len>0)
      {
        time[index] = (unsigned char)atoi(strbuf);
        memset(strbuf, 0, sizeof(strbuf));
        sprintf(strbuf,"%02d",time[index]);
        if(index<3) olcd_dispstr(0+index*2,3,strbuf,2);//olcm_wrtstr(3,1+index*2,strbuf,0);
        else        olcd_dispstr(0+(index-3)*2,4,strbuf,2);//olcm_wrtstr(4,1+(index-3)*2,strbuf,0);
        olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
        index++;

        if(index == 3)
        {
          if(!checkdate(&time[0]))
          {
            olcd_tip_msg(0,2,_eMSG_INPUT_ERR_);////olcm_dispprintf(2,1,"日期输入有误");
            olcd_tip_msg(0,3,_eMSG_DATE_);//olcm_dispprintf(3,1,"__年__月__日");
            osys_getkey(_KEY_EXIT_EV_, 1000);//okey_wait_timeout(KEY_OK_EV,2);
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            index = 0;
            continue;
          }
         }
        if(index == 6)
        {
          if(!checktime(&time[3]))
          {
            olcd_tip_msg(0,2,_eMSG_INPUT_ERR_);//olcm_dispprintf(2,1,"时间输入有误");
            olcd_tip_msg(0,4,_eMSG_TIME_);    //olcm_dispprintf(4,1,"__时__分__秒");
            osys_getkey(_KEY_EXIT_EV_, 1000);//okey_wait_timeout(KEY_OK_EV,2);
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            index = 3;
            continue;
          }
        }
        continue;
      }
      return FALSE;
   }
   memcpy(tpstr,time,6);
   return TRUE;
}
#endif


UINT8 okeyinput_getstrcn(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw )
{
  UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV;
  BOOL  bDot = FALSE;

  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 16 ) nmax = 16;
  //posy = ucursor.y;

  while(1)
  {
         keyV = osys_getkey_ex(); //Sys_GetKey();
         b_keyv = FALSE;
#if 1
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
            return keyV;
        }

        if(keyV == _KEY_RET_EV_)
        {
          *retlen = len;
          return keyV;
        }
        if(keyV == _KEY_POINT_EV_ && bpt == TRUE)
        {
          if(bDot == TRUE) continue;
          tmpbuf[strlen(tmpbuf)] = '.';
          strcpy(pstr,tmpbuf);
          bDot = TRUE;
          len += 1;
        }

        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          if (tmpbuf[len] == '.')
          {
            bDot = FALSE;
          }

          tmpbuf[len] = 0;
          strcpy(pstr,tmpbuf);
        }

        //if(okey_benum(nKeyV))
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmppswbuf);
          }
          else
          {
            tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';//tmpbuf[strlen(tmpbuf)] = okeyinput_getvalue(nKeyV)+'0';
            strcpy(pstr,tmpbuf);
          }
        }
#else
     if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
     {
         tmpbuf[strlen(tmpbuf)] = '*';
     }
     else
     {
         tmpbuf[strlen(tmpbuf)] = '1';
     }
#endif
    // olcm_dispprintf(ucursor.x, posy, tmpbuf);
    olcm_dispprintf(3, 2, tmpbuf);
    //__delay_cycles(73728);//delay_ms(10);
    delay_ms(20);
  }

}
/*author :xiaolin  time 2014-03-14  15:50*/
UINT8 okeyinput_get_pass(INT8 *pstr,UINT8 * retlen, UINT8 nmax, UINT8 x, UINT8 y)
{
   UINT8 MAX8 =0xFF;
    UINT8 M = 10;
  UINT8 len  = 0;
  UINT8 err,keyV;
  UINT8 slen1,slen2;
  UINT8  bDot = 1;
//  UINT32 timeout = 3000;//wang  原来为100
  UINT32 cnt = 0;
  UINT8 point[11] = "**********";
  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
 // oprint_printf("okeyinput_get_pass\r\n");
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 10 ) nmax = 100;
   keyV = osys_getkey_ex(); //先清一下
 //  if(keyV != 0)
   b_keyv = FALSE;
  while(1)
  {
#if 1
      if(err_ts(&err)==TRUE)
      {

      }
#endif
      ////**********************************************************************************/////
       if((RecvUnit_ok == 1)&&(((Recv_Buf[4] == 0x55)&&(Recv_Buf[5] == 0x55))||((Recv_Buf[4] == 0x56)&&(Recv_Buf[5] == 0x56))))
      //  if((RecvUnit_ok == 1)&&(((Recv_Buf[4] == 0x55)||(Recv_Buf[4] == 0x56))&&((Recv_Buf[5] == 0x55))
      {
          if(eCurRunState !=State_LngOperate)//只有待机状态能进行后台上下班
          {   //后台上下班，键盘板只操作不发送信息
                  if(1 == b_shift_ok )   //已上班
                  {  //
                      if(Recv_Buf[4] == 0x56) //下班
                      {   //本地只进行状态变化，存储和后台通信由主控板完成

                          UINT8 REDMAX8;
                          UINT8 MAX8 =0xFF;
                          b_shift_ok = -1;
                          cur_shiftid=Recv_Buf[6];//:班组
                           ReadTn = Recv_Buf[6];
                          memcpy(cure_shift_card,&Recv_Buf[7],10);
                            eCurRunState = State_log_in;
                        while(M--)
                         {  if ( 1 == o24lcxxx_write_bytes(_CLASSNO_OFFWORK_ADDR,(UINT8*)&MAX8,1 ) )
                             { REDMAX8 = o24lcxxx_read(_CLASSNO_OFFWORK_ADDR);
                                if(REDMAX8 == MAX8 )
                                   break;
                             }
                         }
                            eVirtualKey = _KEY_LOGIN_HAVECARD;
                            buzzer_power_up_sound();
                          RecvUnit_ok =0;
                          memset(Recv_Buf,0,20);
                          return 0;
                      }
                  }
                  else if(1 != b_shift_ok )   //没上班
                  {  //
                      if(Recv_Buf[4] == 0x55) //上班
                      {   //本地只进行状态变化，存储和后台通信由主控板完成
                           b_shift_ok = 1;
                           buzzer_power_up_sound();
                           cur_shiftid=Recv_Buf[6];//:班组
                            ReadTn = Recv_Buf[6]; //ReadTn代表从卡里读上的班组，此处无影响
                      M=10;
                      while(M--)
                         {  if ( 1 == o24lcxxx_write_bytes(_CLASSNO_OFFWORK_ADDR,(UINT8*)&cur_shiftid,1 ) )
                              break;
                         }
                            memcpy(cure_shift_card,&Recv_Buf[7],10);
                           eCurRunState = State_MainUI;
                     //      eRunningState = State_log_in;
                           eVirtualKey = _KEY_VIRTUAL_EV_;
                             RecvUnit_ok =0;
                             memset(Recv_Buf,0,10);
                             return 0;
                      }
                  }

          }

      }
      ///********************************************************************************////////////
        // if( eCurRunState == State_MainUI)//wang 3-28后台交接班完成跳出，不用移动
        //   return;

      if(machine_has_card()!=TRUE)//卡拔掉了
      {   olcd_clearsCreen();
          olcm_dispprintf(0,1,"卡已拔出!!");
          olcm_dispprintf(0,2,"请重新操作");
          osys_getkey(_KEY_NULL_,500);
          return 0;

      }

         keyV = osys_getkey_ex(); //Sys_GetKey();
        // if(keyV != 0)
         
         b_keyv = FALSE;
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
//            oprint_printf("ENTER BUTTON\r\n");
            break;
        }
        if(keyV == _KEY_EXIT_EV_)
        {
            *retlen = len;
            //break;//return keyV;
            return 0;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
          strcpy(pstr,tmpbuf);
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
            len++;
            tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmpbuf);
        }
     keyV = 0;
     olcd_dispstr(x,y,point,len);
     if(len < nmax)
     {
         slen1 = len%2;
         slen2 = len/2;
         if(gTick >Runled_tick)
         {   runled_fresh();//刷运行灯
             if(bDot)
             {
                 if(slen1 == 0)
                  olcd_dispstr(x+slen2,y,"_   ",4);
                  else
                  olcd_dispstr(x+slen2,y,"*_  ",4);//望
                  bDot = 0;
             }
             else
             {
                  if(slen1 == 0)
                  olcd_dispstr(x+slen2,y,"    ",4);
                  else
                  olcd_dispstr(x+slen2,y,"*   ",4);
                  bDot = 1;
             }
       }
     }
    //delay_ms(1000);
 //   if(cnt++ > timeout)  wang 414
  //  {
  //     break;
 //   }
  }
  return len;
}
UINT8 okeyinput_getstrpw(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw )
{
  UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV;
  BOOL  bDot = FALSE;

  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 16 ) nmax = 16;
  //posy = ucursor.y;
  while(1)
  {
         keyV = osys_getkey_ex(); //Sys_GetKey();
         b_keyv = FALSE;
#if 1
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
            return keyV;
        }
        if(keyV == _KEY_RET_EV_)
        {
          *retlen = len;
          return keyV;
        }
        if(keyV == _KEY_POINT_EV_ && bpt == TRUE)
        {
          if(bDot == TRUE) continue;
          tmpbuf[strlen(tmpbuf)] = '.';
          strcpy(pstr,tmpbuf);
          bDot = TRUE;
          len += 1;
        }

        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          if (tmpbuf[len] == '.')
          {
            bDot = FALSE;
          }
          tmpbuf[len] = 0;
          strcpy(pstr,tmpbuf);
        }

        //if(okey_benum(nKeyV))
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmppswbuf);
          }
          else
          {
            tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';//tmpbuf[strlen(tmpbuf)] = okeyinput_getvalue(nKeyV)+'0';
            strcpy(pstr,tmpbuf);
          }
        }
#else
     if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
     {
         tmpbuf[strlen(tmpbuf)] = '*';
     }
     else
     {
         tmpbuf[strlen(tmpbuf)] = '1';
     }
#endif
    // olcm_dispprintf(ucursor.x, posy, tmpbuf);
    olcm_dispprintf(3, 3, tmpbuf);
    //__delay_cycles(73728);//delay_ms(10);
    delay_ms(20);
  }

}
////////////////////////////////////////////////////////////////*****************************
/*************************************************************************
功能：  键盘输入
参数:   pstr    - 键盘输入返回
	nmax    - 最大输入数
	bpoint  - 是否允许输入小数点
	bpsw    - 显示屏蔽为'*'
返回值：当前键值
备注：  长度nmax参数要求小于等于16
*************************************************************************/
UINT8 okeyinput_GetstrPSW(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw )
{
  UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV;
  BOOL  bDot = FALSE;
  BOOL  focus;
  UINT8 gtick = heareat_time;//临时本函数借用后台通信节拍heareat_time
  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 6 ) nmax = 6;//***********
  //posy = ucursor.y;
 olcm_dispprintf(3,3,"      ");
  while(1)
  {

    while(1)
    {
        keyV = ostatemachine_getkey();
        if(keyV != 0) break;
        delay_ms(1);
        if(  heareat_time > gtick)
       {   gtick = heareat_time+80;
        if(focus)
            { focus = 0;
             switch(len)
                 {
                  case  0:  olcm_dispprintf(3+0, 3, "  "); break;
                  case  1:  olcm_dispprintf(3+0, 3, "* "); break;
                  case  2:  olcm_dispprintf(3+1, 3, "  "); break;
                  case  3:  olcm_dispprintf(3+1, 3, "* "); break;
                  case  4:  olcm_dispprintf(3+2, 3, "  "); break;
                  case  5:  olcm_dispprintf(3+2, 3, "* "); break;
                  default:       break;
                 }

             }//end of if focus ==1
          else  //focus ==0
            {   focus = 1;
                switch(len)
                 {
                  case  0:  olcm_dispprintf(3+0, 3, "_ "); break;
                  case  1:  olcm_dispprintf(3+0, 3, "*_"); break;
                  case  2:  olcm_dispprintf(3+1, 3, "_ "); break;
                  case  3:  olcm_dispprintf(3+1, 3, "*_"); break;
                  case  4:  olcm_dispprintf(3+2, 3, "_ "); break;
                  case  5:  olcm_dispprintf(3+2, 3, "*_"); break;
                  default:       break;
                 }


       } //end of else(focus =0)
     }  //end of if(  heareat_time > gtick)

    }  //end of keywhile1
         ////////////
         b_keyv = FALSE;

         if(keyV == _KEY_ENTER_EV_)
        {
             if (len == 6) //输入完成
             {  strcpy(pstr,tmppswbuf);//调至此处正常。。。
                return  ;
             }

        }
         if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[len-1] = '*';    //14-02-15 //tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[len-1] = (keyV-1)+'0'; //14-02-15 //tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
          //   strcpy(pstr,tmppswbuf);*************
          }

        }
  olcm_dispprintf(3, 3, "%s", tmpbuf);


  }//end of while 1

}
#if 0
//time:14-03-13 rengang
   BOOL okey_timestr(UINT8 * tpstr)
{
   INT8 strbuf[4];
   UINT8 rdkey, len = 0,index = 0,time[6];
   cursor_x=4, cursor_y=2;
    delay_ms(100);
   while(index<6)
   {
       if(index==0)
       {
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"    更改日期    ");
             olcm_dispprintf(0,2,"请输入：  ");
             olcm_dispprintf(1,3,"__年__月__日");
       }
       if(index==3)
       {
          olcd_clearsCreen();
             olcm_dispprintf(0,1,"    更改时间    ");
             olcm_dispprintf(0,2,"请输入：  ");
             olcm_dispprintf(1,3,"__时__分__秒");
       }
      memset(strbuf, 0, sizeof(strbuf));
      rdkey = okeyinput_getstr(strbuf,&len ,2,FALSE,FALSE);
      if(rdkey == _KEY_OK_EV_ && len>0)
      {
        time[index] = (unsigned char)atoi(strbuf);
        memset(strbuf, 0, sizeof(strbuf));
        sprintf(strbuf,"%02d",time[index]);
        if(index<3) olcd_dispstr(1+index*2,3,strbuf,2);//olcm_wrtstr(3,1+index*2,strbuf,0);
        else        olcd_dispstr(1+(index-3)*2,3,strbuf,2);//olcm_wrtstr(4,1+(index-3)*2,strbuf,0);
        olcm_dispprintf(4,2,"        ");//olcm_clrrow(2);
        index++;
        if(index == 3)
        {
             if(!checkdate(&time[0]))
          {
               olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            olcd_tip_msg(2,2,_eMSG_INPUT_ERR_);////olcm_dispprintf(2,1,"日期输入有误");
            olcm_dispprintf(0,3,"                ");//olcm_dispprintf(3,1,"__年__月__日");
            osys_getkey(_KEY_EXIT_EV_, 200);//okey_wait_timeout(KEY_OK_EV,2);
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            index = 0;
            continue;
          }
           }
        if(index == 6)
        {
          if(!checktime(&time[3]))
          {
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            olcd_tip_msg(2,2,_eMSG_INPUT_ERR_);//olcm_dispprintf(2,1,"时间输入有误");
            olcm_dispprintf(0,3,"                ");//olcm_dispprintf(3,1,"__年__月__日");
            osys_getkey(_KEY_EXIT_EV_, 200);//okey_wait_timeout(KEY_OK_EV,2);
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            index = 3;
            continue;
          }
        }
        continue;
      }
      return FALSE;
   }
   memcpy(tpstr,time,6);
   return TRUE;
}
#endif
//
 //time:14-03-17 rengang
   BOOL okey_timestr(UINT8 * tpstr)
{
   INT8 strbuf[4];
   UINT8 rdkey, len = 0,index = 0,time[6];
   cursor_x=4, cursor_y=2;
   delay_ms(100);
   while(index<3)
   {
       if(index==0)
       {
          olcd_clearsCreen();
             olcm_dispprintf(0,1,"    更改时间    ");
             olcm_dispprintf(0,2,"请输入：  ");
             olcm_dispprintf(1,3,"__时__分__秒");
       }
      memset(strbuf, 0, sizeof(strbuf));
      rdkey = okeyinput_getstr(strbuf,&len ,2,FALSE,FALSE);
      if(rdkey == _KEY_OK_EV_ && len>0)
      {
        time[index] = (unsigned char)atoi(strbuf);
        memset(strbuf, 0, sizeof(strbuf));
        sprintf(strbuf,"%02d",time[index]);
        olcd_dispstr(1+index*2,3,strbuf,2);//olcm_wrtstr(3,1+index*2,strbuf,0);
        olcm_dispprintf(4,2,"        ");//olcm_clrrow(2);
        index++;
        if(index == 3)
        {
             if(!checktime(&time[0]))
          {
               olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            olcd_tip_msg(2,2,_eMSG_INPUT_ERR_);////olcm_dispprintf(2,1,"日期输入有误");
            olcm_dispprintf(0,3,"                ");//olcm_dispprintf(3,1,"__年__月__日");
            osys_getkey(_KEY_EXIT_EV_, 300);//okey_wait_timeout(KEY_OK_EV,2);
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            index = 0;
            continue;
          }
           }
        continue;
      }
      return FALSE;
   }
   memcpy(tpstr,time,3);
   return TRUE;
}
   //time:14-03-17 rengang
  BOOL okey_datestr(UINT8 * tpstr)
{
   INT8 strbuf[4];
   UINT8 rdkey, len = 0,index = 0,time[6];
   cursor_x=4, cursor_y=2;
    delay_ms(100);
   while(index<3)
   {
       if(index==0)
       {
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"    更改日期    ");
             olcm_dispprintf(0,2,"请输入：  ");
             olcm_dispprintf(1,3,"__年__月__日");
       }
       memset(strbuf, 0, sizeof(strbuf));
      rdkey = okeyinput_getstr(strbuf,&len ,2,FALSE,FALSE);
      if(rdkey == _KEY_OK_EV_ && len>0)
      {
        time[index] = (unsigned char)atoi(strbuf);
        memset(strbuf, 0, sizeof(strbuf));
        sprintf(strbuf,"%02d",time[index]);
        olcd_dispstr(1+index*2,3,strbuf,2);//olcm_wrtstr(3,1+index*2,strbuf,0);
         olcm_dispprintf(4,2,"        ");//olcm_clrrow(2);//190909
        index++;
        if(index == 3)
        {
             if(!checkdate(&time[0]))
          {
               olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            olcd_tip_msg(2,2,_eMSG_INPUT_ERR_);////olcm_dispprintf(2,1,"日期输入有误");
            olcm_dispprintf(0,3,"                ");//olcm_dispprintf(3,1,"__年__月__日");
            osys_getkey(_KEY_EXIT_EV_,300);//okey_wait_timeout(KEY_OK_EV,2);
            olcm_dispprintf(0,2,"                ");//olcm_clrrow(2);
            index = 0;
            continue;
          }
           }
        continue;
      }
      return FALSE;
   }
   memcpy(tpstr,time,3);
   return TRUE;
}
   UINT8 okeyinput_get_cp(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw )//rg170619 输入车牌号
 {
 UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV;
  BOOL  bDot = FALSE;

  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 12 ) nmax = 12;
  keyV = osys_getkey_ex();
   b_keyv = FALSE;
  while(1)
  {
         keyV = osys_getkey_ex(); //Sys_GetKey();
         b_keyv = FALSE;
#if 1
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
            return keyV;
        }

        if(keyV == _KEY_RET_EV_)   //exit
        {
          *retlen = len;
          return keyV;
        }
        if(keyV == _KEY_POINT_EV_ && bpt == TRUE)
        {
  //        if(bDot == TRUE) continue;
		if (len >= nmax) continue;
          tmpbuf[strlen(tmpbuf)] = '*';
          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
 //         bDot = TRUE;
          len += 1;
        }

        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          if (tmpbuf[len] == '*')
          {
            bDot = FALSE;
          }
          tmpbuf[len] = ' ';//tmpbuf[len] = 0; //14-02-15

          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
          tmpbuf[len] = 0x00;
        }
        if(( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_))
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[len-1] = '*';    //14-02-15 //tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[len-1] = (keyV-1)+'0'; //14-02-15 //tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmppswbuf);
          }
          else
          {
            tmpbuf[len-1] = (keyV-1)+'0';////14-02-15//tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';//tmpbuf[strlen(tmpbuf)] = okeyinput_getvalue(nKeyV)+'0';
            strcpy(pstr,tmpbuf);
          }
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
        }
#else
     if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
     {
         tmpbuf[strlen(tmpbuf)] = '*';
     }
     else
     {
         tmpbuf[strlen(tmpbuf)] = '1';
     }
#endif
    delay_ms(20);
  }
}
   UINT8 okeyinput_getstr_zf(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw,UINT8 * zfh )
{
  UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV,js;
  BOOL  bDot = FALSE;

  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 16 ) nmax = 16;
  //posy = ucursor.y;
  keyV = osys_getkey_ex();
   b_keyv = FALSE;
   js=0;
   *zfh=js;
  olcm_dispprintf(cursor_x-1, cursor_y, "+");
  while(1)
  {
         keyV = osys_getkey_ex(); //Sys_GetKey();
         b_keyv = FALSE;
#if 1
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
            return keyV;
        }

        if(keyV == _KEY_RET_EV_)   //exit
        {
          *retlen = len;
          return keyV;
        }
        if(keyV == _KEY_POINT_EV_ && bpt == TRUE)
        {
          if(bDot == TRUE) continue;
          tmpbuf[strlen(tmpbuf)] = '.';
          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
          bDot = TRUE;
          len += 1;
        }

        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          if (tmpbuf[len] == '.')
          {
            bDot = FALSE;
          }
          tmpbuf[len] = ' ';//tmpbuf[len] = 0; //14-02-15

          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
          tmpbuf[len] = 0x00;
        }
     if(_KEY_QRY_EV_ == keyV)
        {
         js++;
         if(js>1)
             js=0;
          if(len > 0) continue;
         if(js==0)
           olcm_dispprintf(cursor_x-1, cursor_y, "+");
         else
          olcm_dispprintf(cursor_x-1, cursor_y, "-");   
         *zfh=js;
        }
        //if(okey_benum(nKeyV))
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[len-1] = '*';    //14-02-15 //tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[len-1] = (keyV-1)+'0'; //14-02-15 //tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmppswbuf);
          }
          else
          {
            tmpbuf[len-1] = (keyV-1)+'0';////14-02-15//tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';//tmpbuf[strlen(tmpbuf)] = okeyinput_getvalue(nKeyV)+'0';
            strcpy(pstr,tmpbuf);
          }
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
        }
#else
     if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
     {
         tmpbuf[strlen(tmpbuf)] = '*';
     }
     else
     {
         tmpbuf[strlen(tmpbuf)] = '1';
     }
#endif
     delay_ms(20);
  }

}
    UINT8 okeyinput_getstrbl(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw )//rg181129
{
  UINT8 posy = 0;
  UINT8 len  = 0;
  UINT8 keyV;
  BOOL  bDot = FALSE;

  INT8 tmpbuf[20];
  INT8 tmppswbuf[20];
  memset(tmpbuf, 0, sizeof(tmpbuf));
  memset(tmppswbuf, 0, sizeof(tmppswbuf));
  if(nmax > 16 ) nmax = 16;
  //posy = ucursor.y;
  keyV = osys_getkey_ex();
   b_keyv = FALSE;
  while(1)
  {
         keyV = osys_getkey_ex(); //Sys_GetKey();
         b_keyv = FALSE;
#if 1
         if(keyV == _KEY_ENTER_EV_)
        {
            *retlen = len;
            return keyV;
        }

        if(keyV == _KEY_RET_EV_)   //exit
        {
          *retlen = len;
          return keyV;
        }
        if(keyV == _KEY_POINT_EV_ && bpt == TRUE)
        {
          if(bDot == TRUE) continue;
          tmpbuf[strlen(tmpbuf)] = '.';
          strcpy(pstr,tmpbuf);
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
          bDot = TRUE;
          len += 1;
        }

//        if(_KEY_SW_EV_ == keyV)
//        {
//          if(len == 0) continue;
//          len -= 1;
//          if (tmpbuf[len] == '.')
//          {
//            bDot = FALSE;
//          }
//          tmpbuf[len] = ' ';//tmpbuf[len] = 0; //14-02-15
//
//          strcpy(pstr,tmpbuf);
//           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
//          tmpbuf[len] = 0x00;
//        }

        //if(okey_benum(nKeyV))
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= nmax) continue;
          len++;
          if (TRUE == bpsw)
          {
            tmpbuf[len-1] = '*';    //14-02-15 //tmpbuf[strlen(tmpbuf)] = '*';
            //tmppswbuf[strlen(tmppswbuf)] = okeyinput_getvalue(nKeyV)+'0';
            tmppswbuf[len-1] = (keyV-1)+'0'; //14-02-15 //tmppswbuf[strlen(tmppswbuf)] = (keyV-1)+'0';
            strcpy(pstr,tmppswbuf);
          }
          else
          {
            tmpbuf[len-1] = (keyV-1)+'0';////14-02-15//tmpbuf[strlen(tmpbuf)] = (keyV-1)+'0';//tmpbuf[strlen(tmpbuf)] = okeyinput_getvalue(nKeyV)+'0';
            strcpy(pstr,tmpbuf);
          }
           olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
        }
#else
     if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
     {
         tmpbuf[strlen(tmpbuf)] = '*';
     }
     else
     {
         tmpbuf[strlen(tmpbuf)] = '1';
     }
#endif
    // olcm_dispprintf(ucursor.x, posy, tmpbuf);
    //olcm_dispprintf(0, 2, tmpbuf);
 //   olcm_dispprintf(cursor_x, cursor_y, "%s", tmpbuf);
    //__delay_cycles(73728);//delay_ms(10);
    delay_ms(20);
  }

}