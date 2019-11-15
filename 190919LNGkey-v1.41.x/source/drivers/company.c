#include "../includes/global_def.h"

UINT16 omodbus_crc16(UINT8 *buf, UINT16 Len)
{
  UINT16 IX, IY, CRC;
  CRC = 0xFFFF;
  if (Len <= 0)    return 0;
  for (IX = 0; IX < Len; IX++)
  {
      CRC = CRC ^ (unsigned int)(buf[IX]);
      for (IY = 0; IY < 8; IY++)
      {
        if ((CRC &1) != 0)
          CRC = (CRC >> 1) ^ 0xA001;
        else
          CRC = CRC >> 1;
      }
  }
  return CRC;
}
void send_zh_state(UINT8 cmdnum)//rg171011
{
          UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =0x05;
          Send_Buf[3] =2+1+2+4+1;
          Send_Buf[4] =0x04;
          Send_Buf[5] =0x06;
	  Send_Buf[6] =cmdnum;
            j= omodbus_crc16(Send_Buf,7);
            Send_Buf[7] = (j>>8);
            Send_Buf[8] = j;
            Send_Buf[9] = 0xdc;
           Company_sendstr(10, (UINT8 *)&Send_Buf[0]);
}
void send_ack(UINT8 cmdnum)
{
          UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =cmdnum;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0xaa;
          Send_Buf[5] =0xaa;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
}
#if 0
void send_com_shift()
{
          UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =0x11;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0x55;
          Send_Buf[5] =0x56;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
}
#endif
void send_ack_sj(UINT8 cmdnum)
{
          UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =cmdnum;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =cmdnum;
          Send_Buf[5] =cmdnum;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
}
void send_nck(UINT8 cmdnum)
{
          UINT16 j;
         Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =cmdnum;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0xbb;
          Send_Buf[5] =0xbb;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
 //           Send_Buf[8] = '\n';
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
}

void  ocom_send_heareat (void)
{
   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//数据临时
   BYTE   slen[4]={0};//数据长度临时
   UINT8   c,m;  //数据长度
   UINT32 id ;//= cur_sysinfo.g_uid;
   UINT32 maxid;// = cur_sysinfo.g_uid;
   id = maxid = cur_max_recid;//cur_sysinfo.g_uid;
 //  INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
   memset(Recv_Buf, ' ', 17);//17_>26
    Recv_Buf[0] = '@';//0

    Recv_Buf[5]  = 'L';//5
    Recv_Buf[6] = '0';
    Recv_Buf[7] = '0';
    Recv_Buf[8] = '1';//8 //9,10为空格

   memset(s, 0, sizeof(s));
   memset(slen, 0, sizeof(slen));
   sprintf(&Recv_Buf[17], "SN:%08ld", id);
    c = strlen(Recv_Buf);//流水号长度
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&Recv_Buf[11], s, 6);//

   sprintf(slen, "%04d",cur_p_GID); //
   memcpy(&Recv_Buf[1], slen, sizeof(slen));

    j= omodbus_crc16(Recv_Buf,c);
    Recv_Buf[c++] = (j>>8);//校验高
    Recv_Buf[c++] = j;
    Recv_Buf[c++] = '\r';
    Recv_Buf[c++] = '\n';
    Companybufleng = c;       //总长度
    CompanyPos = 0;

   opotocol_SW = 0;  //心跳帧需关闭再发送，进行超时等待
   INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
   delay_ms(100);
   Companytime_flag = 1;//心跳，必须开超时
   re_over_tick = 0;//必须，计时滴答置0
   Company_sendstr(c, Recv_Buf);
  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //清2个接收字节防止误接收
}
void  company_Answer (void)
{

 //  INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
    opotocol_SW = 0;  //心跳帧需关闭再发送，进行超时等待

   Companytime_flag = 0;//心跳，必须开超时
   re_over_tick = 0;//必须，计时滴答置0
   Company_sendstr(CompanyInbufleng, Recv_Buf);
   memset(Recv_Buf,0,CompanyInbufleng);
   CompanyInbufleng = 0;
   delay_ms(50);
   INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
   delay_ms(50);
  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //清2个接收字节防止误接收
}
BOOL ocompany_precool_start()
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j;
         UINT8 rdkey;

        Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;//+3?
          Send_Buf[4] =0x03;
          Send_Buf[5] =0x01;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;

             Companybufleng = 9;       //总长度
            CompanyPos = 0;
         Company_alarm=0;
         RecvUnit_ok=0;
         uart_state=1;
        do  {
          INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
           re_over_tick=0;
           RecvUnit_ok=0;
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
               { rdkey = ostatemachine_getkey();
                  b_keyv = FALSE;
                  if(_KEY_STOP_EV_ == rdkey) break;
                }
           i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));   //151110  Oxaa
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)   //151110
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
                Precool_ok=FALSE;    //清预冷成功位
                return TRUE;
           }
     }
void ocompany_precool_ok()
{
    if((RecvUnit_ok==1)&&(Recv_Buf[3]==0x03)&&(Recv_Buf[4]==0x11))
    {
        Precool_ok=TRUE;
    }
    send_ack(Recv_Buf[1]);
}
void ocompany_precool_timeover()
{
    if((RecvUnit_ok==1)&&(Recv_Buf[3]==0x03)&&(Recv_Buf[4]==0x03))
    {
        Precool_ok=TRUE;
    }
}
#if 0
void ocompany_precool_getstate(float temp,float gain,float md,float ls,float yl)
{
            Compa_float zh;
    if((RecvUnit_ok==0)&&(Recv_Buf[2]==0x03)&&(Recv_Buf[3]==0x04))
    {
           memcpy(&zh.compa_uc,&Recv_Buf[5],4);
            temp=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[9],4);
            gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[13],4);
            md=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[17],4);
            ls=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[21],4);
            yl=zh.compa_float;

    }
            if((RecvUnit_ok==1)&&(Recv_Buf[2]==0x03)&&(Recv_Buf[3]==0x03))
    {
  //      Precool_ok=TRUE;
        return 2;
    }
}
#endif
BOOL ocompany_precool_stop()
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j;

          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;//+3?
          Send_Buf[4] =0x03;
          Send_Buf[5] =0x02;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8]= 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
            CompanyPos = 0;
         Company_alarm=0;
         RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
                return TRUE;
           }
     }

BOOL ocompany_car_verify(UINT8 *num,UINT8 len)
{
        Compa_float zh;
         UINT8 i=0;
         UINT32 recv;
         UINT16 j;
        UINT8 carnu[10];
        Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9+len;
          Send_Buf[4] =0x08;
          Send_Buf[5] =0x01;
          if(len>0)
              memcpy(&Send_Buf[6],num,len);
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
 //            delay_ms(40000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[3]!=0x08)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
           if(Recv_Buf[4]==0x12)
               return FALSE;
           if(Recv_Buf[4]==0x11)
            return TRUE;
        }
}

BOOL ocompany_gass_quan(float data,UINT8 *carnum ,UINT8 len)
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?7
          Send_Buf[4] =0x03;
          Send_Buf[5] =0x04;
          if(len>0)
         zh.compa_float=data;
         memcpy(&Send_Buf[6], &zh.compa_uc[0], 0x04);
         memcpy(&Send_Buf[6],carnum,(len-4));

           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
//            Send_Buf[8+len] = '\n';
            Companybufleng = 9+len;       //总长度
            uart_state=1;
         RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
//             delay_ms(5000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL ocompany_gass_noquan(float data,UINT8 *carnum ,UINT8 len)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x03;
          Send_Buf[5] =0x06;
          if(len>0)
         zh.compa_float=data;
         memcpy(&Send_Buf[6], &zh.compa_uc[0], 0x04);
         memcpy(&Send_Buf[6],carnum,(len-4));

           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = '\r';
            Companybufleng = 9+len;       //总长度
            uart_state=1;
         RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
//             delay_ms(5000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
       }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
       RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
       if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL ocompany_gass_amount(float data,UINT8 *carnum ,UINT8 len )
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x03;
          Send_Buf[5] =0x05;
          if(len>0)
         zh.compa_float=data;
         memcpy(&Send_Buf[6], &zh.compa_uc[0], 0x04);
         memcpy(&Send_Buf[6],carnum,(len-4));

           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            uart_state=1;
         RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
//             delay_ms(5000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
       }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
        RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
       if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
void ocompany_getgass(float *ql,float *ls,float *yl,float *temp)
{
            Compa_float zh;
    if((RecvUnit_ok==0)&&(Recv_Buf[3]==0x04)&&(Recv_Buf[4]==0x03))
    {
           memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *ql=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *ls=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *yl=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *temp=zh.compa_float;
     }
}
void ocompany_gass_ok()
{
    if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x11))
    {
        gass_ok=TRUE;
    }
    send_ack(Recv_Buf[2]);
}
BOOL ocompany_gass_stop()
{
         UINT8 i=0;
         UINT16 j;
         Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0x03;
          Send_Buf[5] =0x04;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
         RecvUnit_ok=0;
         do  {
             RecvUnit_ok=0;
             re_over_tick=0;
             INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
             //             delay_ms(5000);
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}

UINT8 ocompany_precool_getstate(float *temp,float *gain,float *md,float *ls,float *yl) //返回值：0：通信超时；1：有效数值；2：ok;3:预冷超时；4：MOD通信错误
{
        Compa_float zh;
       UINT16  crc_rece0;
       INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
       if(RecvUnit_ok==1)
       {
crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
 if(Recv_Buf[Recv_Buf[3] -2] == (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] ==crc_rece0>>8 )
 {
    if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x03)&&(Recv_Buf[5]==0x11))
    {
        gass_ok=TRUE;
        RecvUnit_ok=0;
        re_over_tick=0;
        uart_state=0;
 //   send_ack(Recv_Buf[2]);
    return 2;
    }
    else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x03)&&(Recv_Buf[5]==0x03))
    {
        Precool_ok=TRUE;
   //     send_ack(Recv_Buf[2]);
        RecvUnit_ok=0;
        re_over_tick=0;
         uart_state=0;
        if(Recv_Buf[7]==COOL_SERILBERR_STOP)
        {
        return 3;
        }
         if(Recv_Buf[7]==COOL_PRELLBERR_STOP)
        {
        return 5;
         }
          if(Recv_Buf[7]==COOL_SMALLBERR_STOP)
        {
        return 6;
         } 
	  if(Recv_Buf[7]==0xe3)//rg180118
        {
        return 7;
         } 
     }
    else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x03)&&(Recv_Buf[5]==0x04))
    {
           memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *md=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *yl=zh.compa_float;
            RecvUnit_ok=0;
             uart_state=0;
             re_over_tick=0;
            return 1;
        }
        else
        return 0;
        }
        else
        return 0;
        }
        else
        return 0;
}
#if 0
UINT8 ocompany_precool_getstate(float *temp,float *gain,float *md,float *ls,float *yl) //返回值：0：通信超时；1：有效数值；2：ok;3:预冷超时；4：MOD通信错误
{
    Compa_float zh;
    uart_state=1;
    RecvUnit_ok=0;
    INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
    re_over_tick=0;

wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;

    if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x03)&&(Recv_Buf[5]==0x11))
    {
        gass_ok=TRUE;
        RecvUnit_ok=0;
        re_over_tick=0;
        uart_state=0;
    send_ack(Recv_Buf[2]);
    return 2;
    }
    else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x03)&&(Recv_Buf[5]==0x03))
    {
        Precool_ok=TRUE;
        send_ack(Recv_Buf[2]);
        RecvUnit_ok=0;
        re_over_tick=0;
         uart_state=0;
        return 3;
     }
    else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x03)&&(Recv_Buf[5]==0x04))
    {
           memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *md=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *yl=zh.compa_float;
            RecvUnit_ok=0;
             uart_state=0;
             re_over_tick=0;
            return 1;
    }
    else
        return 0;
}
#endif
BOOL ocompany_compack(UINT8 cmdcode,UINT8 gn,float data,UINT8 len )
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len+10;
          Send_Buf[4] =cmdcode;
          Send_Buf[5] =gn;
          memcpy(&Send_Buf[6],Setsys_Rec_card,10);
         zh.compa_float=data;
         memcpy(&Send_Buf[16], &zh.compa_uc[0], len);

           j= omodbus_crc16(Send_Buf,6+len+10);
            Send_Buf[6+len+10] = (j>>8);
            Send_Buf[7+len+10] = j;
            Send_Buf[8+len+10] = 0xdc;
            Companybufleng = 9+len+10;       //总长度
            CompanyPos = 0;
         Company_alarm=0;
         uart_state=1;
         RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
         Company_sendstr(9+len+10, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
     }
BOOL ocompany_set_uint(UINT8 cmdcode,UINT8 gn,UINT8 *rec,UINT8 len )
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j;

          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =cmdcode;
          Send_Buf[5] =gn;
          if(len>0)
           memcpy(&Send_Buf[6],rec,len);
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;

         Company_alarm=0;
            uart_state=1;
         RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<120)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=120))&&(i<3));
           RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=3)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
     }
BOOL Set_price(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x11,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_price2(UINT8 comm,float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,comm,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_gaswait(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x32,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_precool_delay(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x25,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_Density_down(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x24,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_Density_up(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x23,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_pre_temp(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x21,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_gain(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x22,rec,len ))
      return TRUE;
    else
      return FALSE;
}

BOOL Set_curflow(UINT8 *curflow,UINT8 len)
{  if(TRUE == ocompany_set_uint(6,0x12,(UINT8 *)curflow,len ))
     return TRUE;
   else
    return FALSE;
}
BOOL Set_machineid(UINT8 *curflow,UINT8 len)
{  if(TRUE == ocompany_set_uint(6,0x13,(UINT8 *)curflow,len ))
     return TRUE;
   else
    return FALSE;
}

BOOL defConfig(void)
{if(TRUE == ocompany_set_uint(6,0x15,0,0 ))
     return TRUE;
   else
    return FALSE;
}
BOOL Sysclear(void)
{if(TRUE == ocompany_set_uint(6,0x16,0,0 ))
     return TRUE;
   else
    return FALSE;
}
BOOL Set_pressure(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x14,rec,4 ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_ReferVoltage(float rec,UINT8 len ) //Mengfr 20150717
{
    if(TRUE == ocompany_compack(6,0x2A,rec,4 ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_zeropressure(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x28,rec,4 ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_xzcs(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x33,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_pressurejzxs(float rec,UINT8 len )
{
    if(TRUE == ocompany_compack(6,0x29,rec,4 ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_lngEndR(float rec,UINT8 len )//停机流速
{
    if(TRUE == ocompany_compack(6,0x26,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_glbh(float rec,UINT8 len )//过速保护
{
    if(TRUE == ocompany_compack(6,0x2b,rec,len ))
      return TRUE;
    else
      return FALSE;
}
BOOL Set_lspd(float rec,UINT8 len )//流速判断
{
    if(TRUE == ocompany_compack(6,0x2c,rec,len ))
      return TRUE;
    else
      return FALSE;
}
//Mengfr 20161111
//设置小循环成功后延迟时间
BOOL Set_MinCycleDelay(float delay,UINT8 len)
{
    if(TRUE == ocompany_compack(6,0x34,delay,len ))
      return TRUE;
    else
      return FALSE;
}
//Mengfr 20161111
//设置大循环成功后延迟时间
BOOL Set_MajCycleDelay(float delay,UINT8 len)
{
    if(TRUE == ocompany_compack(6,0x35,delay,len ))
      return TRUE;
    else
      return FALSE;
}

BOOL qty_get_rec(float *dj,float *je,float *ql)//,UINT32 *reci)
{
         Compa_float zh;
         Compa_u32 zz;
         UINT8 i=0;
         UINT16 j,crc_rece0;
         delay_ms(50);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x01;
          memset(Recv_Buf,0,50);
           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
 //           ocompany_port_init(9600);
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
            RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x11)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
           RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(zz.compa_uc,&Recv_Buf[6],4);
            cur_max_recid0=zz.compa_u32;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *dj=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *je=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ql=zh.compa_float;
 //           memcpy(rq,&Recv_Buf[22],6);
            delay_ms(3000);
            return TRUE;
        }
}
//rg160907
BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh,UINT32 *ye,UINT8 *cp,float *hq,UINT8 *wz)//rg170607 rg180131 加气信息车牌号
//BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh,UINT32 *ye,UINT8 *cp,float *hq)//rg170607 rg180131 加气信息车牌号
//BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh)//,UINT32 *recg)//检索查流水
{
        Zh328 z328;
        Compa_u32 zz;
        Compa_float zh;
        UINT8 i=0;
        UINT16 j,crc_rece0;
        delay_ms(50);
        Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9+4;     //带查询流水号4位
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x02;
          z328.sou=data;
          memcpy(&Send_Buf[6], &z328.zh[0], 0x04);
          memset(Recv_Buf,0,50);
          j= omodbus_crc16(Send_Buf,10);
            Send_Buf[6+4] = (j>>8);
            Send_Buf[7+4] = j;
            Send_Buf[8+4] = 0xdc;
            Companybufleng = 9+4;       //总长度
            uart_state=1;
            RecvUnit_ok==0;
        do  {
            re_over_tick=0;
             INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(13, (UINT8 *)&Send_Buf[0]);
             i++;
 wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
        }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x12)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<3));
        RecvUnit_ok=0;
                 re_over_tick=0;
                uart_state=0;
        if(i>=3)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
                memcpy(zz.compa_uc,&Recv_Buf[6],4);
                cur_max_recid0=zz.compa_u32;
 //           cur_max_recid0=(Recv_Buf[6]<<24)|(Recv_Buf[7]<<16)|(Recv_Buf[8]<<8)|Recv_Buf[9];
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *dj=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *je=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ql=zh.compa_float;
           memcpy(rq,&Recv_Buf[22],6);
           memcpy(cn,&Recv_Buf[28],10);
	   *ygh = Recv_Buf[49]*256+Recv_Buf[48];
	   memcpy(z328.zh,&Recv_Buf[50],4);
	   *ye=z328.sou;
	   memcpy(cp,&Recv_Buf[54],12);//rg170607 加气信息车牌号
	   memcpy(&zh.compa_uc,&Recv_Buf[66],4);//rg180131
            *hq=zh.compa_float;
            *wz=Recv_Buf[70];
            return TRUE;
        }
}

BOOL qty_get_resetinfo(UINT32 data,UINT32 *maxdata,UINT32 *curdata,UINT8 *rq,UINT8 *no)//rg160622//检索复位记录
{
        Zh328 z328;
        Compa_u32 zz;
        Compa_float zh;
        UINT8 i=0;
        UINT16 j,crc_rece0;
        delay_ms(50);
        Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9+4;     //带查询流水号4位
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x0e;
          z328.sou=data;
          memcpy(&Send_Buf[6], &z328.zh[0], 0x04);
          memset(Recv_Buf,0,50);
          j= omodbus_crc16(Send_Buf,10);
            Send_Buf[6+4] = (j>>8);
            Send_Buf[7+4] = j;
            Send_Buf[8+4] = 0xdc;
            Companybufleng = 9+4;       //总长度
            uart_state=1;
            RecvUnit_ok==0;
        do  {
            re_over_tick=0;
             INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(13, (UINT8 *)&Send_Buf[0]);
             i++;
 wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
        }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x1e)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
        RecvUnit_ok=0;
                 re_over_tick=0;
                uart_state=0;
        if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               
                memcpy(zz.compa_uc,&Recv_Buf[6],4);
                *maxdata=zz.compa_u32;
                memcpy(zz.compa_uc,&Recv_Buf[10],4);
                *curdata=zz.compa_u32;
                memcpy(rq,&Recv_Buf[14],6);
                *no=Recv_Buf[20];
            return TRUE;
        }
}
BOOL qty_get_mod(float *total,float *temp,float *gain,float *Density ,float *ls)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x01;
           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            uart_state=1;
            RecvUnit_ok==0;
            Companybufleng = 9;       //总长度
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x15)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *total=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *Density=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *ls=zh.compa_float;
            return TRUE;
        }
}
//rg170110 增加获取主板时间
UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT16 ygno,UINT8 *time)//发送上班信息rg160907 参数：班号，卡号，上班时间，返回：0：成功上班 1：黑客 2：灰卡 3：通信异常
{
         UINT8 i=0,i0=0;
         UINT16 j;
         UINT8 len=17+2;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =3+1+2+3+len;
          Send_Buf[4] =0x02;
          Send_Buf[5] =0x01;
          Send_Buf[6]=shift_id;
          memcpy(&Send_Buf[7],shift_card,10);
          memcpy(&Send_Buf[17],shift_op_time,6);
//	  memcpy(&Send_Buf[23],ygno,2);
	  Send_Buf[23] = ygno;//rg160907
	  Send_Buf[24] = ygno >> 8;//rg160907
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            uart_state=1;
         RecvUnit_ok=0;
       do  {
             re_over_tick=0;
             RecvUnit_ok=0;
             INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
wait:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));

            RecvUnit_ok=0;
       do  {
             re_over_tick=0;
             RecvUnit_ok=0;
             i0++;
             INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
 wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0x02)||(Recv_Buf[5]!=0x11)||(re_over_tick>=COMPANY_OVERTIME))&&(i0<4));
                RecvUnit_ok=0;
                uart_state=0;
                re_over_tick=0;
            if(i0>=4)
           {
               return 3;
           }
           else
           {
                if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
		memcpy(time,&Recv_Buf[6],6);
               return 0;
           }
}
//rg170110
BOOL ocompany_duishi_jpzhu(UINT8 *data,UINT8 len )
{
	Compa_float zh;
	UINT8 i = 0;
	UINT16 j;
	Send_Buf[0] = 0xcd;
	Send_Buf[1] = 0xfa;
	Send_Buf[2] = se_cmdnu;
	Send_Buf[3] = 2 + 1 + 2 + 4 + len;
	Send_Buf[4] = 0x02;
	Send_Buf[5] = 0x21;
	memcpy(&Send_Buf[6], data, 6);
	j = omodbus_crc16(Send_Buf, 6 + len);
	Send_Buf[6 + len] = (j >> 8);
	Send_Buf[7 + len] = j;
	Send_Buf[8 + len] = 0xdc;
	Companybufleng = 9 + len; //总长度
	CompanyPos = 0;
	Company_alarm = 0;
	uart_state = 1;
	RecvUnit_ok = 0;
	INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
	do {
		re_over_tick = 0;
		RecvUnit_ok = 0;
		Company_sendstr(9 + len, (UINT8 *) & Send_Buf[0]);
		i++;
wait0:
		if ((re_over_tick < COMPANY_OVERTIME)&&(RecvUnit_ok == 0)) goto wait0;
	} while (((RecvUnit_ok == 0) || (Recv_Buf[2] != se_cmdnu) || (Recv_Buf[5] != 0xaa) || (Recv_Buf[4] != 0xaa) || (re_over_tick >= COMPANY_OVERTIME))&&(i < 4));
	RecvUnit_ok = 0;
	re_over_tick = 0;
	uart_state = 0;
	if (i >= 4) {
		return FALSE;
	} else {
		if (se_cmdnu > 255)
			se_cmdnu = 0;
		else
			se_cmdnu++;
		return TRUE;
	}
     }
BOOL TB_Send_YG(UINT8 *cn,UINT8 yg,UINT8 * tb_op_time)//替班rg170701
{
         UINT8 i=0,type;
         UINT16 j,rdkey;
         UINT8 len=17;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x02;
          Send_Buf[5] =0x04;
           memcpy(&Send_Buf[6],cn,10);
	   Send_Buf[16]=yg;
 //          memcpy(&Send_Buf[16],nbh,5);
           memcpy(&Send_Buf[17],tb_op_time,6);
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
                 //14-5-20 添加
               {  rdkey = ostatemachine_getkey();
                 b_keyv = FALSE;
                if(_KEY_STOP_EV_ == rdkey)
                return 5;
                 if(_KEY_EXIT_EV_ == rdkey)
                return 5;
              }
            RecvUnit_ok=0;
           re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<5)&&(RecvUnit_ok==0))
                    {
                          {  rdkey = ostatemachine_getkey();
                             b_keyv = FALSE;
                            if(_KEY_STOP_EV_ == rdkey)
                            return 5;
                             if(_KEY_EXIT_EV_ == rdkey)
                            return 5;
                          }
                          goto wait0;
                    }
       }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=2))&&(i<5));
            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=5)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
//rg160612
BOOL off_work(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT32 *rec,UINT32 *class_q,UINT32 *class_h,UINT32 *gain_q,UINT32 *gain_h, UINT8 *xdsj)//发送下班信息 参数：班号，卡号，上班时间
{
         Compa_float zh;
         UINT8 i2=0;
         UINT16 j;
         UINT8 len=17;

          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x02;
          Send_Buf[5] =0x02;
          Send_Buf[6]=shift_id;
          memset(Recv_Buf,0,50);
          memcpy(&Send_Buf[7],shift_card,10);
          memcpy(&Send_Buf[17],shift_op_time,6);
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            uart_state=1;
            Companybufleng = 9+len;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i2++;
wait:             if((re_over_tick<COMPANY_OVERTIME4)&&(RecvUnit_ok==0)) goto wait;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0x02)||(Recv_Buf[5]!=0x13)||(re_over_tick>=COMPANY_OVERTIME4))&&(i2<4));
             if(i2>=4)
           {
               return FALSE;
           }
           else
           {  RecvUnit_ok=0;
           uart_state=0;
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *rec=*rec=Recv_Buf[6]+Recv_Buf[7]*256+Recv_Buf[8]*256*256+Recv_Buf[9]*256*256*256;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);

            *class_q=zh.compa_u32;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *class_h=zh.compa_u32;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *gain_q=zh.compa_u32;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *gain_h=zh.compa_u32;
            memcpy(xdsj,&Recv_Buf[26],6);
               return TRUE;
           }
}
void ocompany_shift_ok()
{
    if((RecvUnit_ok==0)&&(Recv_Buf[3]==0x02)&&(Recv_Buf[4]==0x11))
    {
        shift_ok=TRUE;
    }
    send_ack(Recv_Buf[2]);
}
BOOL Set_fdelay(float rec,UINT8 len )//rg170809 第5阀延时设置
{
    if(TRUE == ocompany_compack(6,0x61,rec,len ))
      return TRUE;
    else
      return FALSE;
}
void ocompany_offwork_ok()
{
    if((RecvUnit_ok==0)&&(Recv_Buf[2]==0x02)&&(Recv_Buf[3]==0x12))
    {
        offwork_ok=TRUE;
    }
    send_ack(Recv_Buf[2]);
}
BOOL ocompany_Handshake()
{
     Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0x0a;
          Send_Buf[5] =0x0a;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            uart_state=1;
            Companybufleng = 9;       //总长度
           RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
//             delay_ms(5000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
           if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
                return TRUE;
           }
}
/*********************************
 *     将键盘存储的SOE 
 *   传输到主控板
 *    ss190912
 ******************************************/
BOOL Send_SOE_State(UINT8 *data) 
{
    Compa_float zh;
    UINT8 i = 0;
    UINT16 j, crc_rece0;
    Send_Buf[0] = 0xcd;
    Send_Buf[1] = 0xfa;
    Send_Buf[2] = se_cmdnu;
    Send_Buf[3] = 9+9;
    Send_Buf[4] = 0x77;
    Send_Buf[5] = 0x77;
    memcpy(&Send_Buf[6],data,9); 
    j = omodbus_crc16(Send_Buf, 6+9);
    Send_Buf[15] = (j >> 8);
    Send_Buf[16] = j;
    Send_Buf[17] = 0xdc;
    memset(Recv_Buf, 0, 50);
    uart_state = 1;
    Companybufleng = 9+9; //总长度
    RecvUnit_ok = 0;
    
       INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
        Company_sendstr(9+9, (UINT8 *) & Send_Buf[0]);
        
        uart_state = 0;
        if (se_cmdnu > 255)
            se_cmdnu = 0;
        else
            se_cmdnu++;
        return TRUE;
        
#if 0       
    do {
        RecvUnit_ok = 0;
        re_over_tick = 0;
        INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
        Company_sendstr(9+7, (UINT8 *) & Send_Buf[0]);
        i++;
wait0:
        if ((re_over_tick < COMPANY_OVERTIME2)&&(RecvUnit_ok == 0)) goto wait0;
        if (RecvUnit_ok == 1) 
        {
            crc_rece0 = omodbus_crc16((unsigned char*) &Recv_Buf[2], (Recv_Buf[3] - 5));
            if (Recv_Buf[Recv_Buf[3] - 2] != (unsigned char) (crc_rece0 & 0x00FF) || Recv_Buf[Recv_Buf[3] - 3] != crc_rece0 >> 8) {
                RecvUnit_ok = 0;
                re_over_tick = 0;
            }
        }
    } while (((RecvUnit_ok == 0) || (Recv_Buf[5] != 0x77) || (re_over_tick >= COMPANY_OVERTIME2))&&(i < 4));
    RecvUnit_ok = 0;
    re_over_tick = 0;
    uart_state = 0;
    if (i >= 4) {
        return FALSE;
    } else {
        if (se_cmdnu > 255)
            se_cmdnu = 0;
        else
            se_cmdnu++;

//        memcpy(ptr, &Recv_Buf[6], sizeof (SYSTEMPARA));
        return TRUE;
    }
#endif
}

//BOOL qty_get_sys(UINT8 *qid,float *price ,float *temp,\
//        float *gain,float *ls ,float *aqyl,float *zeroyl,float *ylxs,float *Density_up ,float *Density_do,float *ylys,float *gas_delay,float *refvol,float *glbh,float *lspd)   //Mengfr 20150717
BOOL qty_get_sys(SYSTEMPARA *ptr) 
{
    Compa_float zh;
    UINT8 i = 0;
    UINT16 j, crc_rece0;
    Send_Buf[0] = 0xcd;
    Send_Buf[1] = 0xfa;
    Send_Buf[2] = se_cmdnu;
    Send_Buf[3] = 9;
    Send_Buf[4] = 0x05;
    Send_Buf[5] = 0x08;

    j = omodbus_crc16(Send_Buf, 6);
    Send_Buf[6] = (j >> 8);
    Send_Buf[7] = j;
    Send_Buf[8] = 0xdc;
    memset(Recv_Buf, 0, 50);
    uart_state = 1;
    Companybufleng = 9; //总长度
    RecvUnit_ok = 0;
    do {
        RecvUnit_ok = 0;
        re_over_tick = 0;
        INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
        Company_sendstr(9, (UINT8 *) & Send_Buf[0]);
        i++;
wait0:
        if ((re_over_tick < COMPANY_OVERTIME2)&&(RecvUnit_ok == 0)) goto wait0;
        if (RecvUnit_ok == 1) {
            crc_rece0 = omodbus_crc16((unsigned char*) &Recv_Buf[2], (Recv_Buf[3] - 5));
            if (Recv_Buf[Recv_Buf[3] - 2] != (unsigned char) (crc_rece0 & 0x00FF) || Recv_Buf[Recv_Buf[3] - 3] != crc_rece0 >> 8) {
                RecvUnit_ok = 0;
                re_over_tick = 0;
            }
        }
    } while (((RecvUnit_ok == 0) || (Recv_Buf[5] != 0x18) || (re_over_tick >= COMPANY_OVERTIME2))&&(i < 4));
    RecvUnit_ok = 0;
    re_over_tick = 0;
    uart_state = 0;
    if (i >= 4) {
        return FALSE;
    } else {
        if (se_cmdnu > 255)
            se_cmdnu = 0;
        else
            se_cmdnu++;
        memcpy(ptr, &Recv_Buf[6], sizeof (SYSTEMPARA));
        
//        *qid = Recv_Buf[6];
//
//        memcpy(&zh.compa_uc, &Recv_Buf[7], 4);
//        *price = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[11], 4);
//        *temp = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[15], 4);
//        *gain = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[19], 4);
//        *ls = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[23], 4);
//        //           *yl=zh.compa_float;
//        //           memcpy(&zh.compa_uc,&Recv_Buf[31],4);
//        *aqyl = zh.compa_float;
//
//        memcpy(&zh.compa_uc, &Recv_Buf[27], 4);
//        *zeroyl = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[31], 4);
//        *ylxs = zh.compa_float;
//
//        memcpy(&zh.compa_uc, &Recv_Buf[35], 4);
//        *Density_up = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[39], 4);
//        *Density_do = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[43], 4);
//        *ylys = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[47], 4);
//        *gas_delay = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[51], 4); //Mengfr 20150717
//        *refvol = zh.compa_float;
//        memcpy(&zh.compa_uc, &Recv_Buf[55], 4); //Mengfr 20150717
//        *glbh = zh.compa_float;
//        *lspd = (Recv_Buf[60]*256 + Recv_Buf[59])*0.01; //rg160704
        return TRUE;
    }
}
BOOL qty_get_pricex(float *price2 ,float *price3,\
        float *price4,float *price5 ,float *price6,float *price7,float *price8,float *price9 ,float *price10)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x0d;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            memset(Recv_Buf,0,50);
            uart_state=1;
            Companybufleng = 9;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x1d)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
             RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
           if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
             memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *price2=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *price3=zh.compa_float;
             memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *price4=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *price5=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *price6=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
            *price7=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[30],4);
            *price8=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[34],4);
            *price9=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[38],4);
            *price10=zh.compa_float;
            return TRUE;
        }
}

BOOL qty_get_gid(UINT32 *qid_total)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x03;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            RecvUnit_ok==0;
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x13)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *qid_total=zh.compa_u32;
            return TRUE;
        }
}
//BOOL qty_get_g_mod(float *total,float *temp,float *gain,float *Density ,float *ls)  //GL:1:YE 2：QI

BOOL qty_get_l_mod(float *temp,float *gain,float *Density,float *ls ,float *total,float *yl)  //GL:1:YE 2：QI
{
           Compa_float zh;
           UINT8 i=0;
           UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x05;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            memset(Recv_Buf,0,50);
            uart_state=1;
            Companybufleng = 9;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x15)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
 //          *qid=Recv_Buf[6];

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *Density=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *total=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
             *yl=zh.compa_float;
              return TRUE;
        }
}
BOOL qty_get_g_mod(float *temp,float *gain,float *Density,float *ls ,float *total,float *yl) //GL:1:YE 2：QI
//BOOL qty_get_l_mod(float *total,float *temp,float *gain,float *Density ,float *ls)
{
           Compa_float zh;
           UINT8 i=0;
           UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x06;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            memset(Recv_Buf,0,50);
            uart_state=1;
            Companybufleng = 9;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x16)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *Density=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *total=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
             *yl=zh.compa_float;
#if 0
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *total=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *Density=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
             *ls=zh.compa_float;
#endif
             return TRUE;
        }
}


BOOL qty_get_shift(UINT32 *s_total)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x04;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            RecvUnit_ok==0;
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x14)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *s_total=zh.compa_u32;
            return TRUE;
        }
}
BOOL qty_get_yl(float *yl)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x03;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            RecvUnit_ok==0;
            uart_state=1;
            Companybufleng = 9;       //总长度
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
 wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0x16)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *yl=zh.compa_float;
            return TRUE;
        }
}

BOOL module_vctrl_start()
{
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x01;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
          RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
               re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL module_vctrl_quit()
{
          UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x04;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
          RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
               re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL module_vctrl(UINT8 Ctlnum,UINT8 ACTION)//Ctlnum:电磁阀序号。参数值：1-4标示电磁阀1-4；5：PLC1；6：PLC2;
                                            //ACTION:动作。参数值：0xa1：open；0x1a：close；
{
         UINT8 i=0;
         UINT16 j;
         UINT8 len=2;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x02;
          Send_Buf[6]=Ctlnum;
          if(ACTION==0)
          Send_Buf[7]=0x1a;
          if(ACTION==1)
          Send_Buf[7]=0xa1;
           j= omodbus_crc16(Send_Buf,8);
            Send_Buf[8] = (j>>8);
            Send_Buf[9] = j;
            Send_Buf[10] = 0xdc;
            Companybufleng = 11;       //总长度
            uart_state=1;
          RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(10+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
               re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL module_vctrl_pump_sw(UINT8 ACTION)//联动测试//参数1：停 2：预冷 3：加注 4：待机
{
         UINT8 i=0;
         UINT16 j;
         UINT8 len=1;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x03;
          switch (ACTION)
          {
              case 1:
             Send_Buf[6]=0x13;
            break;
            case 2:
             Send_Buf[6]=0x14;
            break;
            case 3:
             Send_Buf[6]=0x16;
            break;
             case 4:
             Send_Buf[6]=0x17;
            break;
            default:
             Send_Buf[6]=0x11;
            break;
          }
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
            uart_state=1;
         Company_alarm=0;

       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
              RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL Set_qtotal(INT8 *curflow,UINT8 len)//rg181129
{  if(TRUE == ocompany_set_uint(6,0x66,(UINT8 *)curflow,len ))
     return TRUE;
   else
    return FALSE;
}
BOOL Set_stotal(UINT8 *curflow,UINT8 len)//rg181129
{  if(TRUE == ocompany_set_uint(6,0x67,(UINT8 *)curflow,len ))
     return TRUE;
   else
    return FALSE;
}
BOOL Set_curflowbz(UINT8 *curflow,UINT8 len)//rg181129
{  if(TRUE == ocompany_set_uint(6,0x68,(UINT8 *)curflow,len ))
     return TRUE;
   else
    return FALSE;
}
BOOL qty_get_shiftls(UINT32 *s_total)//rg181129
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x22;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            RecvUnit_ok==0;
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x22)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *s_total=zh.compa_u32;
            return TRUE;
        }
}
BOOL qty_get_zdls(UINT32 *lsh)//rg181129流水号
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x24;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            RecvUnit_ok==0;
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x24)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *lsh=zh.compa_u32;
            return TRUE;
        }
}
BOOL get_ModuleSave(UINT8 *chk)////获得当前系统存储测试结果  CHK：1：存储成功；0：存储不成功，函数返回值：TRUE：通信正常
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
         UINT8 len=0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x07;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;

       do  {
            RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
            re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
                *chk=Recv_Buf[6];
                return TRUE;
           }
}

BOOL module_dispLcd_test()
{
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x08;
            j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
          RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
               re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
}
BOOL Clear_modbus(UINT8 ModType)//流量计清零 参数：1：液相；2：气相；
{
          Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
         UINT8 len=1;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x05;
          Send_Buf[6]=ModType;
            j= omodbus_crc16(Send_Buf,7);
            Send_Buf[7] = (j>>8);
            Send_Buf[8] = j;
            Send_Buf[9] = 0xdc;
            Companybufleng = 10;       //总长度
            uart_state=1;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(10, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
 //           memcpy(&zh.compa_uc,&Recv_Buf[5],4);
                return TRUE;
            }
}
BOOL Buff_modbus(UINT8 ModType)//流量计清零 参数：1：液相；2：气相；
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
         UINT8 len=1;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x07;
          Send_Buf[5] =0x06;
          Send_Buf[6]=ModType;
            j= omodbus_crc16(Send_Buf,7);
            Send_Buf[7] = (j>>8);
            Send_Buf[8] = j;
            Send_Buf[9] = 0xdc;
            Companybufleng = 10;       //总长度
            uart_state=1;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(10, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
 //           memcpy(&zh.compa_uc,&Recv_Buf[5],4);
                return TRUE;
            }
}

BOOL get_press(float *press)//获得当前压力传感器数值
{
       Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x07;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            uart_state=1;

            Companybufleng = 9;       //总长度
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
 //            delay_ms(40000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x17)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
           * press=zh.compa_float;
            return TRUE;
        }
}
 BOOL Gets_SumandPress_start(float *Rec_Sum_Start,float *Rec_Begin_Press)
 { //       切记此函数参数前枪累为整型。
           Compa_float zh;
         UINT8 rdkey,i=0;
         UINT16 j,crc_rece0;

          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x09;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            uart_state=1;

           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
            Companybufleng = 9;       //总长度
    do  {
           //14-5-20 添加
          {  rdkey = ostatemachine_getkey();
             b_keyv = FALSE;
            if(_KEY_STOP_EV_ == rdkey)
            return FALSE;
          }

           RecvUnit_ok=0;
           re_over_tick=0;
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x19)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
              RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
           * Rec_Sum_Start=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[10],4);
           * Rec_Begin_Press=zh.compa_float;
            return TRUE;
        }
 }
BOOL Ocompany_GetGas_REC(float *GV, float *AM,float *back_gas,float *endPress,UINT8 *EccType,UINT32 *rec,UINT8 *hq_state)//加气停止后:气量、金额、回气量
{
          Compa_float zh;
          UINT8 i=0;
          UINT16 j,crc_rece0;
          delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x0A;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            uart_state=1;
          INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
            Companybufleng = 9;       //总长度

       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
//           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
            //************************************
  //          olcd_clearsCreen();
 //          olcm_dispprintf(0,1,"通信中....");
 //          olcm_dispprintf(0,2,"稍等！");
            //***************************************


wait0:             if((re_over_tick<COMPANY_OVERTIME5)&&(RecvUnit_ok==0)) goto wait0;
            if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }

            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x1a)||(re_over_tick>=COMPANY_OVERTIME5))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;

            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
           * GV=zh.compa_float;

           memcpy(&zh.compa_uc,&Recv_Buf[10],4);
           * AM=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[14],4);
           * back_gas=zh.compa_float;
 //          memcpy(&zh.compa_uc,&Recv_Buf[18],4);
 //          * EccType=zh.compa_float;
           *rec=Recv_Buf[18]+Recv_Buf[19]*256+Recv_Buf[20]*256*256+Recv_Buf[21]*256*256*256;
   //        *rec = Recv_Buf[18]||(Recv_Buf[19]<<8)||(Recv_Buf[20]<<16)||(Recv_Buf[21]<<24);
	   *hq_state=0;
	   *hq_state=Recv_Buf[22];
           return TRUE;
        }
}

BOOL qty_get_zhanhao(UINT8 *num,float *relay,UINT8 *ver)  //查站号
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x0b;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            memset(Recv_Buf,0,50);
            uart_state=1;
            Companybufleng = 9;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x1b)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
             RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
           if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
           *num=Recv_Buf[6];
            memcpy(&zh.compa_uc,&Recv_Buf[7],4);
           * relay=zh.compa_float;
           *ver=Recv_Buf[11];
              return TRUE;
        }
}
BOOL qty_get_sw(UINT8 *num)  //rg161220 查拨码开关状态
{
	Compa_float zh;
	UINT8 i = 0;
	UINT16 j, crc_rece0;
	Send_Buf[0] = 0xcd;
	Send_Buf[1] = 0xfa;
	Send_Buf[2] = se_cmdnu;
	Send_Buf[3] = 9;
	Send_Buf[4] = 0x05;
	Send_Buf[5] = 0x0f;

	j = omodbus_crc16(Send_Buf, 6);
	Send_Buf[6] = (j >> 8);
	Send_Buf[7] = j;
	Send_Buf[8] = 0xdc;
	memset(Recv_Buf, 0, 50);
	uart_state = 1;
	Companybufleng = 9; //总长度
	RecvUnit_ok = 0;
	do {
		RecvUnit_ok = 0;
		re_over_tick = 0;
		INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
		Company_sendstr(9, (UINT8 *) & Send_Buf[0]);
		i++;
wait0:
		if ((re_over_tick < COMPANY_OVERTIME)&&(RecvUnit_ok == 0)) goto wait0;
		if (RecvUnit_ok == 1) {
			crc_rece0 = omodbus_crc16((unsigned char*) &Recv_Buf[2], (Recv_Buf[3] - 5));
			if (Recv_Buf[Recv_Buf[3] - 2] != (unsigned char) (crc_rece0 & 0x00FF) || Recv_Buf[Recv_Buf[3] - 3] != crc_rece0 >> 8) {
				RecvUnit_ok = 0;
				re_over_tick = 0;
			}
		}
	} while (((RecvUnit_ok == 0) || (Recv_Buf[5] != 0x1f) || (re_over_tick >= COMPANY_OVERTIME))&&(i < 4));
	RecvUnit_ok = 0;
	re_over_tick = 0;
	uart_state = 0;
	if (i >= 4) {
		return FALSE;
	} else {
		if (se_cmdnu > 255)
			se_cmdnu = 0;
		else
			se_cmdnu++;
		*num = Recv_Buf[6];
		return TRUE;
	}
}
BOOL qty_get_xz(float *num)  //查校正系数
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x0c;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            memset(Recv_Buf,0,50);
            uart_state=1;
            Companybufleng = 9;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x1c)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
             RecvUnit_ok=0;
           re_over_tick=0;
                uart_state=0;
           if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               memcpy(&zh.compa_uc,&Recv_Buf[6],4);
           * num=zh.compa_float;
               return TRUE;
        }
}

BOOL ocompany_zanhao_verify(UINT8 *num)  //设站号命令
{
    Compa_float zh;
         UINT8 i=0;
         UINT16 j;
         UINT8 len=1;
        Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9+len;
          Send_Buf[4] =0x06;
          Send_Buf[5] =0x30;

          if(len>0)
              memcpy(&Send_Buf[6],num,len);
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
 //            delay_ms(40000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
             return TRUE;
        }
}
BOOL ocompany_relay_set(float num)  //设余量命令
{
    Compa_float zh;
         UINT8 i=0;
         UINT16 j;
         UINT8 len=4;
        Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9+len;
          Send_Buf[4] =0x06;
          Send_Buf[5] =0x31;
                zh.compa_float=num;
         memcpy(&Send_Buf[6], &zh.compa_uc[0], len);
//          if(len>0)
//              memcpy(&Send_Buf[6],num,len);
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            uart_state=1;
       do  {
           re_over_tick=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
             i++;
 //            delay_ms(40000);
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
           RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
                return TRUE;
        }
}
BOOL  Get_ZiCard_info(UINT8 * cn,UINT8 *state,INT32 *car_m,float *car_mf)//rg170717
{
	Compa_float zh;
         UINT8 i=0,type;
         UINT16 j,rdkey;
         UINT8 len=10;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x08;
          Send_Buf[5] =0x09;
            memcpy(&Send_Buf[6],cn,10);
 //           zh.compa_int32=car_m;
            j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
                 //14-5-20 添加
               {  rdkey = ostatemachine_getkey();
                 b_keyv = FALSE;
                if(_KEY_STOP_EV_ == rdkey)
                return 5;
                 if(_KEY_EXIT_EV_ == rdkey)
                return 5;
              }

            RecvUnit_ok=0;
           re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<5)&&(RecvUnit_ok==0))
                    {
                          {  rdkey = ostatemachine_getkey();
                             b_keyv = FALSE;
                            if(_KEY_STOP_EV_ == rdkey)
                            return 5;
                             if(_KEY_EXIT_EV_ == rdkey)
                            return 5;
                          }
                          goto wait0;
                    }
       }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0x08)||(Recv_Buf[5]!=0x19)||(re_over_tick>=5))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               *state=Recv_Buf[6];
	       zh.compa_uc[3]=Recv_Buf[7];
	       zh.compa_uc[2]=Recv_Buf[8];
	       zh.compa_uc[1]=Recv_Buf[9];
	       zh.compa_uc[0]=Recv_Buf[10];
//	       memcpy(&zh.compa_uc,&Recv_Buf[7],4);
            *car_m=zh.compa_int32;
	    *car_mf=(zh.compa_uc[3]*256*256*256+zh.compa_uc[2]*256*256+zh.compa_uc[1]*256+zh.compa_uc[0])*0.01;
//	    *car_mf=zh.compa_float;
         return TRUE;
           }
}
UINT8 Check_Card_info(UINT8 * cn,INT32 *car_m,INT32 *car_g,UINT8 xf)//核对卡信息，是否是黑卡,//返回值：0：通信错误，1：正常卡 2：黑卡,3为异地卡可加气，4为异地卡不可加气
{
         Compa_float zh;
         UINT8 i=0,type;
         UINT16 j,rdkey;
         UINT8 len=10+4+4+1;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x08;
          Send_Buf[5] =0x07;
            memcpy(&Send_Buf[6],cn,10);
 //           zh.compa_int32=car_m;
            memcpy(&Send_Buf[16],car_m,4);
 //           zh.compa_int32=car_g;
            memcpy(&Send_Buf[20],car_g,4);
            Send_Buf[24] =xf;
           j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
                 //14-5-20 添加
               {  rdkey = ostatemachine_getkey();
                 b_keyv = FALSE;
                if(_KEY_STOP_EV_ == rdkey)
                return 5;
                 if(_KEY_EXIT_EV_ == rdkey)
                return 5;
              }

            RecvUnit_ok=0;
           re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<5)&&(RecvUnit_ok==0))
                    {
                          {  rdkey = ostatemachine_getkey();
                             b_keyv = FALSE;
                            if(_KEY_STOP_EV_ == rdkey)
                            return 5;
                             if(_KEY_EXIT_EV_ == rdkey)
                            return 5;
                          }
                          goto wait0;
                    }
       }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0x08)||(Recv_Buf[5]!=0x17)||(Recv_Buf[6]>6)||(re_over_tick>=5))&&(i<5));
            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=5)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               type=Recv_Buf[6];
         return type;
           }
}

UINT8 Ocompany_Gas_noquan_start(float money,UINT8 jgdj,float zkl,float curprice,UINT8 *cp,UINT8 ks)//定量加气的开始0:通讯错误 1:可以加气2：未预冷 价格等级 折扣率//rg170607 加气信息车牌号rg181210
{
         Compa_float zh;
         UINT8 i=0,rdkey,type;
         UINT16 j;
         UINT8 len=9+4+12+1;
         delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x04;//cmdcode;
          Send_Buf[5] =0x01;//gn;
          zh.compa_float=money;
          memcpy(&Send_Buf[6], &zh.compa_uc[0], 4);
          Send_Buf[10]= jgdj;
          zh.compa_float=zkl;
          memcpy(&Send_Buf[11], &zh.compa_uc[0], 4);
 //         memcpy(&Send_Buf[11],zkl,2);
          zh.compa_float=curprice;
          memcpy(&Send_Buf[15], &zh.compa_uc[0], 4);
	  memcpy(&Send_Buf[19], cp, 12);
      Send_Buf[31]= ks;
          j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
//              {  rdkey = ostatemachine_getkey();      //移除
//                 b_keyv = FALSE;
//                if(_KEY_STOP_EV_ == rdkey)
//                return 5;
//              }
         RecvUnit_ok=0;
         re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0))
                   {
                            goto wait0;
                   }
            } 
            while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<6));

            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=6)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
  //             type=Recv_Buf[6];
         return 1;
           }
}

BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK)//非定量加气过程中:气量、金额、是否加气完成。isgasOK为:1表示余额不足;2：表示加气错误，主控板已自主停止加气。
{
       Compa_float zh;
       UINT16  crc_rece0;
       static float old_gv = 0;
       INT8 i;
       i=2;
       INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
  if(RecvUnit_ok==1)
 {
crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
 if(Recv_Buf[Recv_Buf[3] -2] == (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] ==crc_rece0>>8 )
              {
    if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x03))
    {   /* 
        if(Graybegain == 0)
            { 
            while(i)
            {
                 i--;
  //               if(0)
                if(TRUE ==ic_card_put_status(CARDS_GREY))  //置灰RG160601
              {
                    Car_Hui_ok=0;
                    Graybegain = 1;
                    break;
              }
                delay_ms(10);
            }
            if(i<=0)
            {
             Car_Hui_ok=1;
             return FALSE;
            }
            }*/
           olcm_dispprintf(0,1,"    正在加气    ");
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[14],4);
           *desenty=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[22],4);
           *GV=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[26],4);
           *press=zh.compa_float;
//	   *fz = Recv_Buf[30];//rg170606密度电磁阀显示
            //密度、压力不处理
 //           *AM=zh.compa_float*PRICE;

            *isgasOK=0;
            RecvUnit_ok=0;
            State_g_p=2;
            
             if(_gas_run_flag == FALSE)
            {
                if(old_gv < *GV)                          // 表示已经加气  ss190220
                {
                    old_gv = 0;
                    _gas_run_flag = TRUE;                  //ss190218
                }
                if(old_gv == 0)
                    old_gv = *GV;

            }
            return TRUE;
     }
       else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x04))
    {
                   olcm_dispprintf(0,1,"    正在预冷    ");
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *desenty=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *GV=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
           *press=zh.compa_float;
            //密度、压力不处理
 //           *AM=zh.compa_float*PRICE;
            *isgasOK=0;
            RecvUnit_ok=0;
            State_g_p=1;
            return TRUE;
     }
   
//*********************** //rg171011***********************************************************************************//    
    if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x05)&&(Recv_Buf[6]==0xaa)&&(Recv_Buf[7]==0xbb))
    {
       gas_record.gas_precool = GAS_PRECOOL_SUCC;                          //预冷成功    //ss190215 add
 //       if(!((WKJQ == 0)&&(_CARD_TYPE == 1)))//rg171127如果无卡加气，班组卡不置灰不扣款
	  if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg171127如果无卡加气，班组卡不置灰不扣款rg180322
	    {
            if(Graybegain == 0)
            { 
                
                while(i)
                {
//                    i--;
                    if(TRUE ==ic_card_put_status(CARDS_GREY))  //置灰RG160601
                    {
                        UINT8 grey_state;
                        delay_ms(50);                                          // 增加读取等待延时  ss20190102
                        grey_state = ic_card_get_status_nosel();                    // 读取置灰后的状态
                        if (grey_state == CARDS_GREY)                       // 置灰完成后 读取出状态再次判断置灰是否成功
                        {
                            Car_Hui_ok=1;
                            Graybegain = 1;
                            send_zh_state(Car_Hui_ok);
                            delay_ms(100);
                            send_zh_state(Car_Hui_ok);
//                             memcpy(gas_record.card_id,CN,10);                                 //  加气记录  卡号
                             gas_record.card_id = (UINT32)atoi(CN);                                        //  加气记录  卡号  ss190306
        //                                gas_record.gas_start_way = card_info_22.type;                              //加气记录   加气卡的类型 
                            gas_record.grey_lock_inif.grey_status |=  GREY_LUCK_SUCC;                          // 加气记录  置灰成功
//                            gas_record.grey_lock_inif.grey_status |=  GAS_START_MORMAL;                          // 加气记录  正常加气方式  因定量定额加气也会进入到此处 移出
                    //                    memcpy(gas_record.grey_lock_inif.time,&jy_num.JY_DATI[1],6);        //置灰时间
                            ortcc_read_time(gas_record.grey_lock_inif.time);                    // 置灰时间

                            break;
                        }
                    }
                    delay_ms(10);
                    i--;
                }
                if(i<=0)
                {
                    
                    Car_Hui_ok=2;
                    send_zh_state(Car_Hui_ok);
                    delay_ms(100);
                    send_zh_state(Car_Hui_ok);
                    ortcc_read_time(gas_record.grey_lock_inif.time);                                    // 置灰时间
//                    gas_record.grey_lock_inif.grey_status |=  GAS_START_MORMAL;                          // 加气记录  正常加气方式
                    gas_record.grey_lock_inif.grey_status |=  GREY_LUCK_FAILL;                          // 加气记录  置灰失败
//                 return FALSE;     SS20190102 对置灰失败的处理
                   *isgasOK = 0xD0;                                             //  ss20190102 置灰失败  直接退出  
                   return TRUE;                                                  //  ss20190102 置灰失败  直接退出  
                }
            }
            else
            {
                Car_Hui_ok=1;
                send_zh_state(Car_Hui_ok);
            }
	}
	    else
	    {//rg171127如果无卡加气，班组卡不置灰不扣款
                Car_Hui_ok=1;
                Graybegain = 1;
                send_zh_state(Car_Hui_ok);
                delay_ms(100);
                send_zh_state(Car_Hui_ok);
//                memcpy(gas_record.card_id,CN,10);                                 //  加气记录  卡号
                 gas_record.card_id = (UINT32)atoi(CN);                                        //  加气记录  卡号  ss190306
//                shift_write.gas_record_query.gas_start_way =  CARD_OPERATION;       // 无卡加气方式置位     加气记录
                gas_record.grey_lock_inif.grey_status |=  GAS_START_MORMAL;         // 加气记录  正常加气方式
//                gas_record.grey_lock_inif.cur_money =  max_money;                   //加气记录    加气前金额  
                ortcc_read_time(gas_record.grey_lock_inif.time);                    // 置灰时间   表示加气时间
                Graybegain = 1;
    
	    }
            *isgasOK=0;
            RecvUnit_ok=0;
            State_g_p=3;
            return TRUE;
     }
//**********************************************************************************************************//    
       else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x11))
    {
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *GV=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *backgas=zh.compa_float;

            *isgasOK=0xFD;
            RecvUnit_ok=0;
            State_g_p=0;
            return TRUE;
     }
       else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x12))  //???????确定一下是否是主控板的错误发送（exit）
    {
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *GV=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[16],4);
            *backgas=zh.compa_float;
            *isgasOK=Recv_Buf[7];
            RecvUnit_ok=0;
            State_g_p=0;
            return TRUE;
     }
       else
           RecvUnit_ok=0;
           return FALSE;
   }
 }
  else
    return FALSE;
}
BOOL Ocompany_Gas_noquan_stop(UINT8 state)//非定量加气的停止
{         Compa_float zh;
         UINT8 i=0;
         UINT16 j;
         UINT8 len=1;
         delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x04;//cmdcode;
          Send_Buf[5] =0x02;//gn;
          Send_Buf[6] =state;
            j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
  //         INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;

       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;

    wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;

            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<7));
            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=7)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
          return TRUE;
           }
}

BOOL Ocompany_Gas_noquan_finish(UINT8 *card_type, UINT8 * cn,float *GV, float *AM,INT32 *rec_card_preM_int ,INT32 *rec_card_endM_int,\
        INT32 *rec_card_preg_int,INT32 *rec_card_endg_int,float *rec_sum_start,float *rec_sum_end, float *rec_begin_Press,\
        float *rec_end_Press,UINT8 *Car_hui_L ,UINT8 * gas_Stime,UINT8 * gas_Etime)//非定量加气过程中:气量、金额、是否加气完成。isgasOK为1表示加气完成。
{
          Compa_float zh;
         UINT8 i=0,type;
         UINT16 j;
         UINT8 len=64;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x09;//cmdcode;
          Send_Buf[5] =0x01;//gn;
          Send_Buf[6]=*card_type;
          memcpy(&Send_Buf[7], cn, 10);
            zh.compa_float=*GV;
         memcpy(&Send_Buf[17], &zh.compa_uc[0], 4);
            zh.compa_float=*AM;
         memcpy(&Send_Buf[21], &zh.compa_uc[0], 4);

         memcpy(&Send_Buf[25], rec_card_preM_int, 4);
         memcpy(&Send_Buf[29], rec_card_endM_int, 4);
         memcpy(&Send_Buf[33], rec_card_preg_int, 4);
         memcpy(&Send_Buf[37], rec_card_endg_int, 4);

                     zh.compa_float=*rec_sum_start;
         memcpy(&Send_Buf[41], &zh.compa_uc[0], 4);
         zh.compa_float=*rec_sum_end;
         memcpy(&Send_Buf[45], &zh.compa_uc[0], 4);
                     zh.compa_float=*rec_begin_Press;
         memcpy(&Send_Buf[49], &zh.compa_uc[0], 4);

                             zh.compa_float=*rec_end_Press;
         memcpy(&Send_Buf[53], &zh.compa_uc[0], 4);
         Send_Buf[57]=*Car_hui_L;
         memcpy(&Send_Buf[58], gas_Stime, 6);
  //                   zh.compa_float=* gas_Stime;
  //       memcpy(&Send_Buf[58], &zh.compa_uc[0], 3);

 //                    zh.compa_float=* gas_Etime;
         memcpy(&Send_Buf[64], gas_Etime, 6);
 //        memcpy(&Send_Buf[61], &zh.compa_uc[0], 3);

            j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
            Company_alarm=0;
            uart_state=1;
            RecvUnit_ok=0;
       do  {
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
           re_over_tick=0;
           Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
           i++;
wait0:     if((re_over_tick<COMPANY_OVERTIME3)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME4))&&(i<4));
            RecvUnit_ok=0;
            re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
      //         type=Recv_Buf[6];
               return TRUE;
           }
}
UINT8 Ocompany_Gas_Quan_start(float money,UINT8 jgdj,float zkl,float curprice,UINT8 *cph,UINT8 ks)//定量加气的开始0:通讯错误 1:可以加气2： 未预冷//rg170607 加气信息车牌号rg181210
// UINT8 Ocompany_Gas_Quan_start(float money,UINT8 jgdj,float zkl,float curprice)//定量加气的开始0:通讯错误 1:可以加气2： 未预冷 价格等级 折扣率
 {
             Compa_float zh;
         UINT8 i=0,type;
         UINT16 j;
         UINT8 len=4+1+4+4+12+1;
         delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x04;//cmdcode;
          Send_Buf[5] =0x01;//gn;
            zh.compa_float=money;
         memcpy(&Send_Buf[6], &zh.compa_uc[0], 4);
         Send_Buf[10] = jgdj;
         zh.compa_float=zkl;
         memcpy(&Send_Buf[11], &zh.compa_uc[0], 4);
 //        memcpy(&Send_Buf[11],zkl,2);
            zh.compa_float=curprice;
         memcpy(&Send_Buf[15], &zh.compa_uc[0], 4);
	 memcpy(&Send_Buf[19],cph,12);//rg170607 加气信息车牌号
     Send_Buf[31] = ks ;
         j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
         RecvUnit_ok=0;
           re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }//while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0x04)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));

            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
      //         type=Recv_Buf[6];
         return 1;
           }
 }
BOOL Ocompany_Gas_Quan_run(float *GV, float *AM,float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK)//定量加气过程中:气量、金额、是否加气完成。isgasOK为:1表示加气完成;2：表示加气错误
// BOOL Ocompany_Gas_Quan_run(float *GV, float *AM,float *gain,float *ls,float *temp,float *backgas,UINT8 *isgasOK)//定量加气过程中:气量、金额、是否加气完成。isgasOK为:1表示加气完成;2：表示加气错误
{
    Compa_float zh;
    UINT16 crc_rece0;
    INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
        if(RecvUnit_ok==1)
       {
crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
 if(Recv_Buf[Recv_Buf[3] -2] == (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] ==crc_rece0>>8 )
              {
    if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x03))
    {
        olcm_dispprintf(0,1,"    正在加气    ");
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *desenty=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *GV=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
            *press=zh.compa_float;
            //密度、压力不处理
            *AM=zh.compa_float*PRICE;
            *isgasOK=0;
            RecvUnit_ok=0;
//            send_ack(0x98);
            return TRUE;
     }
    else if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x04))
    {
        olcm_dispprintf(0,1,"    正在预冷    ");
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *temp=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *gain=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *desenty=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *ls=zh.compa_float;
           memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *GV=zh.compa_float;
             memcpy(&zh.compa_uc,&Recv_Buf[26],4);
            *press=zh.compa_float;
            //密度、压力不处理
            *AM=zh.compa_float*PRICE;

            *isgasOK=0;
            RecvUnit_ok=0;
 //           send_ack(0x99);
            return TRUE;
     }
    else  if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x11))
    {
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *GV=zh.compa_float;

            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *AM=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *backgas=zh.compa_float;

            *isgasOK=1;
            RecvUnit_ok=0;
            return TRUE;
     }
     else  if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x04)&&(Recv_Buf[5]==0x12))
    {
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *GV=zh.compa_float;

            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *backgas=zh.compa_float;
//            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
//            *ls=zh.compa_float;
//           memcpy(&zh.compa_uc,&Recv_Buf[18],4);
//            *GV=zh.compa_float;
//            *AM=zh.compa_float*5.6;
            *isgasOK=Recv_Buf[14];
                RecvUnit_ok=0;
                return TRUE;
     }
     else
          RecvUnit_ok=0;
         return FALSE;
 }
        }

}
BOOL err_ts(UINT8 *err)
{
      Compa_float zh;
    UINT16 crc_rece0;
    INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
        if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x12))
       {
        crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
        if(Recv_Buf[Recv_Buf[3] -2] == (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] ==crc_rece0>>8 )
              {
                if((RecvUnit_ok==1)&&(Recv_Buf[4]==0x12))
                {    Sys_Rec_Err[Rec_inxex++]= Recv_Buf[5];
                    *err=Recv_Buf[5];
                    RecvUnit_ok=0;
                    return TRUE;
                 }
                else
                RecvUnit_ok=0;
                return FALSE;
         }
        }
        else
       return FALSE;
}

BOOL Ocompany_stop()
{
         UINT8 i=0;
         UINT16 j;
         UINT8 len=0;
         delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x04;//cmdcode;
          Send_Buf[5] =0x02;//gn;
              j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
       do  {
           Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
           i++;
            }while(i<2);
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
         return TRUE;

}
BOOL Ocompany_Gas_Quan_stop(UINT8 state)//定量加气的停止
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j;
         UINT8 len=1;
         delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x04;//cmdcode;
          Send_Buf[5] =0x02;//gn;
          Send_Buf[6] =state;
 //         zh.compa_float=*Rec_End_Press;
 //        memcpy(&Send_Buf[6], &zh.compa_uc[0], len);
              j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
 //          INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
            Company_alarm=0;
            uart_state=1;
       do  {
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
           RecvUnit_ok=0;
           re_over_tick=0;
           Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
           i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<7));
            RecvUnit_ok=0;
            re_over_tick=0;
            uart_state=0;
            if(i>=7)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
//          memcpy(zh.compa_uc,&Recv_Buf[6],4);
//          *Rec_End_Press=zh.compa_float;
         return TRUE;
           }
}
BOOL Ocompany_Gas_Quan_finish(UINT8 *card_type, UINT8 * cn,float *GV, float * AM,INT32 * rec_card_preM_int ,\
        INT32 *rec_card_endM_int,INT32 *rec_card_preg_int,INT32 *rec_card_endg_int,float *rec_sum_start,float *rec_sum_end,\
         float *rec_begin_Press,float *rec_end_Press,UINT8 *Car_hui_L,UINT8 * gas_Stime,UINT8 * gas_Etime )//非定量加气过程中:气量、金额、是否加气完成。isgasOK为1表示加气完成。
{
        Compa_float zh;
         UINT8 i=0,type;
         UINT16 j;
         UINT8 len=58;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;//+3?
          Send_Buf[4] =0x09;//cmdcode;
          Send_Buf[5] =0x01;//gn;
          Send_Buf[6]=*card_type;
          memcpy(&Send_Buf[7], cn, 10);
            zh.compa_float=*GV;
         memcpy(&Send_Buf[17], &zh.compa_uc[0], 4);
            zh.compa_float=*AM;
         memcpy(&Send_Buf[21], &zh.compa_uc[0], 4);
         memcpy(&Send_Buf[25], rec_card_preM_int, 4);
         memcpy(&Send_Buf[29], rec_card_endM_int, 4);
         memcpy(&Send_Buf[33], rec_card_preg_int, 4);
         memcpy(&Send_Buf[37], rec_card_endg_int, 4);
                     zh.compa_float=*rec_sum_start;
         memcpy(&Send_Buf[41], &zh.compa_uc[0], 4);
         zh.compa_float=*rec_sum_end;
         memcpy(&Send_Buf[45], &zh.compa_uc[0], 4);
                     zh.compa_float=*rec_begin_Press;
         memcpy(&Send_Buf[49], &zh.compa_uc[0], 4);

                             zh.compa_float=*rec_end_Press;
         memcpy(&Send_Buf[53], &zh.compa_uc[0], 4);
         Send_Buf[57]=*Car_hui_L;
   //                  zh.compa_float=* gas_Stime;
         memcpy(&Send_Buf[58], gas_Stime, 6);
         memcpy(&Send_Buf[64], gas_Etime, 6);
  //       memcpy(&Send_Buf[58], &zh.compa_uc[0], 3);

   //                  zh.compa_float=* gas_Etime;
  //       memcpy(&Send_Buf[61], &zh.compa_uc[0], 3);

            j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
         RecvUnit_ok=0;
           re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME3)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME4))&&(i<4));
              RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=4)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
     //          type=Recv_Buf[6];
         return TRUE;
           }
}
BOOL down_get_password(UINT8 *num)  //下载秘钥
{
        UINT8 password[8];
         UINT8 i=0;
         UINT16 j,crc_rece0;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x08;
          Send_Buf[5] =0x02;

           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            memset(Recv_Buf,0,50);
            uart_state=1;
            Companybufleng = 9;       //总长度
            RecvUnit_ok=0;
       do  {
           RecvUnit_ok=0;
           re_over_tick=0;
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
             Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME10)&&(RecvUnit_ok==0)) goto wait0;
           if(RecvUnit_ok==1)
            {
            crc_rece0 =omodbus_crc16((unsigned char*)&Recv_Buf[2],(Recv_Buf[3] -5));
            if(Recv_Buf[Recv_Buf[3] -2] != (unsigned char)(crc_rece0 &0x00FF) || Recv_Buf[Recv_Buf[3] -3] !=crc_rece0>>8 )
              {
                RecvUnit_ok=0;
                re_over_tick=0;
               }
            }
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x12)||(re_over_tick>=COMPANY_OVERTIME10))&&(i<4));
             RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
           if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               memcpy(password,&Recv_Buf[6],8);
               memcpy(num,&Recv_Buf[6],8);
//           num=&password[0];
               return TRUE;
        }
}
BOOL Ocompany_Gas_Qz()//取整
{
         Compa_float zh;
         UINT8 i=0;
         UINT16 j;
         UINT8 len=1;
         delay_ms(500);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x0b;
          Send_Buf[5] =0x01;
          Send_Buf[6] =0xaa;
            j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
            Company_alarm=0;
            uart_state=1;
       do  {
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
           RecvUnit_ok=0;
           re_over_tick=0;
           Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
           i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[4]!=0xaa)||(Recv_Buf[5]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<5));
            RecvUnit_ok=0;
            re_over_tick=0;
            uart_state=0;
            if(i>=5)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
         return TRUE;
           }
}
void Configure_company(void)
{
   UINT8 i;
     memset(Recv_Buf,0, R_maxBuflen );
     memset(Send_Buf,0, T_maxBuflen );

 //   Set_Clockask();//初始设置为时间请求
    Companybufleng = 0;  //发送缓冲区长度为0
    Company_Timeoutnum = 0;//超时次数
    re_over_tick = 0;//超时滴答
    RecvUnit_ok = 0; //不接收
    Companycrc_rece = 0;
    uart_state=0;
//    Result_card = 0;//卡验证结果初始化为0
}
UINT8 Card_Verif(UINT8 * cn,UINT8 ed,float yue)//核对卡信息，发卡号，额度、卡余//返回值：0：通信错误，1：正常卡 2：验证失败不可加气
{
         Compa_float zh;
         UINT8 i=0,type;
         UINT16 j,rdkey;
         UINT8 len=10+4+1;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+len;
          Send_Buf[4] =0x08;
          Send_Buf[5] =0x08;
            memcpy(&Send_Buf[6],cn,10);
            Send_Buf[16]=ed;
            zh.compa_float=yue;
            memcpy(&Send_Buf[17],zh.compa_uc,4);
            j= omodbus_crc16(Send_Buf,6+len);
            Send_Buf[6+len] = (j>>8);
            Send_Buf[7+len] = j;
            Send_Buf[8+len] = 0xdc;
            Companybufleng = 9+len;       //总长度
            CompanyPos = 0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
         Company_alarm=0;
            uart_state=1;
       do  {
                 //14-5-20 添加
               {  rdkey = ostatemachine_getkey();
                 b_keyv = FALSE;
                if(_KEY_STOP_EV_ == rdkey)
                return 5;
                 if(_KEY_EXIT_EV_ == rdkey)
                return 5;
              }

            RecvUnit_ok=0;
           re_over_tick=0;
         Company_sendstr(9+len, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<5)&&(RecvUnit_ok==0))
                    {
                          {  rdkey = ostatemachine_getkey();
                             b_keyv = FALSE;
                            if(_KEY_STOP_EV_ == rdkey)
                            return 5;
                             if(_KEY_EXIT_EV_ == rdkey)
                            return 5;
                          }
                          goto wait0;
                    }
       }while(((RecvUnit_ok==0)||(Recv_Buf[4]!=0x08)||(Recv_Buf[5]!=0x18)||(Recv_Buf[6]>5)||(re_over_tick>=5))&&(i<5));
            RecvUnit_ok=0;
           re_over_tick=0;
            uart_state=0;
            if(i>=5)
           {
               return 0;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               type=Recv_Buf[6];
         return type;
           }
}
BOOL qty_get_jlerr(float *num1,float *num2,float *num3,float *num4,float *num5,float *num6,float *num7,float *num8,float *num9,\
float *num10,float *num11,float *num12,float *num13,float *num14,float *num15)
{
         Compa_float zh;
         Compa_u32 zz;
         UINT8 i=0;
         UINT16 j,crc_rece0;
         delay_ms(50);
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =9;
          Send_Buf[4] =0x05;
          Send_Buf[5] =0x99;
          memset(Recv_Buf,0,50);
           j= omodbus_crc16(Send_Buf,6);
            Send_Buf[6] = (j>>8);
            Send_Buf[7] = j;
            Send_Buf[8] = 0xdc;
            Companybufleng = 9;       //总长度
            uart_state=1;
 //           ocompany_port_init(9600);
            INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
            RecvUnit_ok=0;
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
           Company_sendstr(9, (UINT8 *)&Send_Buf[0]);
             i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME2)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[5]!=0x99)||(re_over_tick>=COMPANY_OVERTIME2))&&(i<4));
           RecvUnit_ok=0;
                re_over_tick=0;
                uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
            memcpy(&zh.compa_uc,&Recv_Buf[6],4);
            *num1=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[10],4);
            *num2=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[14],4);
            *num3=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[18],4);
            *num4=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[22],4);
            *num5=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[26],4);
            *num6=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[30],4);
            *num7=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[34],4);
            *num8=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[38],4);
            *num9=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[42],4);
            *num10=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[46],4);
            *num11=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[50],4);
            *num12=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[54],4);
            *num13=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[58],4);
            *num14=zh.compa_float;
            memcpy(&zh.compa_uc,&Recv_Buf[62],4);
            *num15=zh.compa_float;

            delay_ms(3000);
            return TRUE;
        }
}
BOOL ocompany_send_daxs(UINT8 cmdcode,UINT8 gn,UINT8 data)
{
        Compa_float zh;
         UINT8 i=0;
         UINT16 j;
          Send_Buf[0] =0xcd;
          Send_Buf[1] =0xfa;
          Send_Buf[2] =se_cmdnu;
          Send_Buf[3] =2+1+2+4+1+10;
          Send_Buf[4] =cmdcode;
          Send_Buf[5] =gn;
          memcpy(&Send_Buf[6],Setsys_Rec_card,10);
         Send_Buf[16]=data;
//         memcpy(&Send_Buf[16], &zh.compa_uc[0], len);

           j= omodbus_crc16(Send_Buf,6+1+10);
            Send_Buf[6+1+10] = (j>>8);
            Send_Buf[7+1+10] = j;
            Send_Buf[8+1+10] = 0xdc;
            Companybufleng = 9+1+10;       //总长度
            CompanyPos = 0;
         Company_alarm=0;
         uart_state=1;
         RecvUnit_ok=0;
           INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED);
       do  {
           re_over_tick=0;
           RecvUnit_ok=0;
         Company_sendstr(9+1+10, (UINT8 *)&Send_Buf[0]);
         i++;
wait0:             if((re_over_tick<COMPANY_OVERTIME)&&(RecvUnit_ok==0)) goto wait0;
            }while(((RecvUnit_ok==0)||(Recv_Buf[2]!=se_cmdnu)||(Recv_Buf[5]!=0xaa)||(Recv_Buf[4]!=0xaa)||(re_over_tick>=COMPANY_OVERTIME))&&(i<4));
            RecvUnit_ok=0;
           re_over_tick=0;
           uart_state=0;
            if(i>=4)
           {
               return FALSE;
           }
           else
           {
               if(se_cmdnu>255)
                se_cmdnu=0;
                else
                se_cmdnu++;
               return TRUE;
           }
     }
void ocompany_port_init(unsigned long baud)
{
#if 0
    uart_config is_config;
    is_config.baud = baud;
    is_config.d_num = UART_DATA_SIZE_8_BITS;
    is_config.p_type = UART_PARITY_NONE;
    is_config.s_num  = UART_STOP_BITS_1;
    uart_init(PCCOMPANY_PORT, &is_config);
#endif
#if 1
    PORTSetPinsDigitalOut(IOPORT_B, BIT_14);
    PC485_DIR_OUTPUT();
    UARTConfigure(PCCOMPANY_PORT, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(PCCOMPANY_PORT, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(PCCOMPANY_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(PCCOMPANY_PORT, GetPeripheralClock(), baud);
    UARTEnable(PCCOMPANY_PORT, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX)); //
    INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_DISABLED); //INT_DISABLED
    INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_ENABLED); //INT_DISABLED
   // INTEnable(INT_SOURCE_UART_TX(PCTRANS_PORT), INT_DISABLED);//INT_DISABLED
#endif
}
void Company_sendstr(UINT8 len, UINT8 *buf)
{
  unsigned int n;
  PC485_DIR_OUTPUT();
  delay_ms(20);
    sys_uart_send_str(PCCOMPANY_PORT, buf, len);//for (n = 0; n < len; n++) omodbus_l_sendchar(*buf++);
  //while( BusyUART1());//for (n = 0; n < 100; n++) asm("nop"); //1000
   PC485_DIR_INPUT();
  delay_ms(20);//delay_ms(1);//100);
  //asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");//__delay_cycles(5);
  //asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}
#if 1
void __ISR(_UART_2_VECTOR, ipl4) IntUart2Handler(void)  //_UART_3A_VECTOR
{
 if(INTGetFlag(INT_SOURCE_UART_RX(PCCOMPANY_PORT)))
  {
    static UINT8 isHeadRecved = 0; //头部是否收到
    static BYTE head[2] = {0, };  //头部
    static UINT8 data_index = 0;
    UINT8 c  = UARTGetDataByte(PCCOMPANY_PORT);
  if (!isHeadRecved)  //没有收到"J+R"
  {
      head[0] = head[1];
      head[1] = c;

      if ((head[0] == 0xcd) && (head[1] ==0xfa))
      {
        isHeadRecved = 1;
        //帧头
        Recv_Buf[0] = head[0];
        Recv_Buf[1] = head[1];
         //清空头部
        head[0] = 0;
        head[1] = 0;
        data_index = 0; //接收指针复位
         KEY422_ERRBYTE_Tick = gTick +100*5; //150819
       }
    }//end of 头部
  else  //收到头部
    {       Recv_Buf[2+ data_index++] = c;
          if(gTick>KEY422_ERRBYTE_Tick)
           {
           isHeadRecved = 0; //重新搜索头部
           // Companytime_flag = 0;// 不可少
           // RecvUnit_ok=0;
           data_index = 0; //150819
            KEY422_ERRBYTE_Tick = DWORDMAX; //150819
            }

  //     if ((Recv_Buf[2+ data_index-1] == 0xdc)&&(Recv_Buf[3]==(2+ data_index)))//命令、长度接收完毕
           if ((Recv_Buf[2+ data_index-1] == 0xdc))//命令、长度接收完毕
        {
            if(Recv_Buf[3]==(2+ data_index))
            {
                 KEY422_ERRBYTE_Tick = DWORDMAX; //150819
                isHeadRecved = 0; //重新搜索头部
            Companytime_flag = 0;// 不可少
            RecvUnit_ok=1;
            if((Recv_Buf[4] == 0x60)&&(Recv_Buf[5] == 0x61))   //150731
            {
  //                SoftReset( );
                delay_ms(10);   //20160630
                WDTCONSET=0x8000;
                while(1);
            }
            if((Recv_Buf[4] == 0x0F)&&(Recv_Buf[5] == 0x00))    //20170221
            {
                UINT8 Temp[4];
                o24lcxxx_write_bytes_ex(0x3FFB,&Recv_Buf[6],4);
                o24lcxxx_read_bytes_ex(0x3FFB,&Temp[0],4);
                if(!memcmp(&Recv_Buf[16],&Temp[0],4));
                {    
                    WDTCONSET=0x8000;
                    while(1);
                }
            }
            if((Recv_Buf[4] == 0x12)&&(Recv_Buf[5] == 0x3c))//rg190510
            {
                HUAIKUAI=TRUE;
                hk_disp=TRUE;
            }
            }
   //     crc_rece =omodbus_crc16((unsigned char*)&Recv_Buf[2],data_index -3);//gcomInbufleng含校验码，减掉2
// if(Recv_Buf[data_index] == (unsigned char)(crc_rece &0x00FF) || Recv_Buf[data_index-1] ==crc_rece>>8 )
  //            {
   //         CompanyInbufleng = 2 + data_index -1;//数据总长度(含校验，不含\R\N) data_index已在\n
      //l      isHeadRecved = 0; //重新搜索头部
       //l     Companytime_flag = 0;// 不可少
      //l      RecvUnit_ok=1;
        }
      }
 INTClearFlag(INT_SOURCE_UART_RX(PCCOMPANY_PORT));
}
if ( INTGetFlag(INT_SOURCE_UART_TX(PCCOMPANY_PORT)) )
{      INTClearFlag(INT_SOURCE_UART_TX(PCCOMPANY_PORT));

  }
}
#endif
