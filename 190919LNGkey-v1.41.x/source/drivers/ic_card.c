#include <plib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/global_def.h"
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#define     IC_CARD_DEBUG   0
#define     IC_CARD_PORT    UART4
/******************  macro for sign mark in transportats message ***********/
#define     STX             0x02
#define     ETX             0x03
#define     ENQ             0x05
#define     ACK             0x06
#define     NAK             0x15
#define     SW1_SUUESS      0x90
#define     SW1_FAILE       1

#define    CPU_CARD_A       0x34
#define    A_ACTIVE         0x40
#define    A_COMUNITE       0x41
#define    A_DESELECT       0x42
#define    REVE01_LEN       50
/******************************************************************************/
#define  ICMACHINE_MSG_EXTERN 5
/******************************************************************************/
#define  ACK_REPONSE   1
#define  NCK_REPONSE   2
#define  FAIL_REPONSE  0

/*******************      macros for send message as  cmd       ***************/
#define     MSG_MACHINE1  0x30
#define     MSG_MACHINE2  0x40
#define     APDU_CMD_M    0x34
#define     APDU_CMD_L    0x41
#define     APDU_WRITE_BINARY  0xD6
#define     APDU_FILE_HIGH     0x1F
#define     APDU_FILE_LOW    0x80
#define     ic_card_delay()  delay_ms(1000) //1500wang
#define     ic_delay_normal()  delay_ms(200)
/********************   macros for read binary file to get the ic card info ****/
#define     IC_MFDIR_FILENO            0x3F00
#define     IC_INFODIR_FILENO          0x0011
#define     IC_INFO_FILENO          0x01
#define     IC_MEM_FILENO           0x02
#define     IC_GAS_FILENO           0x03
#define     IC_STA_FILENO           0x04
#define     IC_PAS_FILENO           0x05
#define     IC_READ_BINARY_TYPE     0x00
#define     IC_MAX_READ_LEN         128
/****************************************************************************/

typedef enum IC_CARD_STATUS
{
    IC_CARD_IDLE,
    IC_CARD_SNED_MSG,
    IC_CARD_WAIT_XCK,
    IC_CARD_WAIT_REPLY,
    IC_CARD_ACK,
    IC_CARD_NCK,
    IC_CARD_SEND_ENQ,
}IC_CARD_STATUS;
/******************************************************************************/
typedef enum IC_CARD_CMD
{
    IC_RESET_CMD,
    IC_SET_BARD_CMD,

}IC_CARD_CMD;
/*****************************************************************************/
typedef UINT8       (*pfic_card_send)(UINT8 *buffer, UINT8 size);
typedef UINT32      (*pfic_card_recv)(UINT8 *buf, UINT8 size);
typedef BOOL        (*pfic_card_get_reponse)();
typedef apdu_status (*pfic_papdu_reponse)(UINT8 * dest,UINT8 *source, UINT8 *rlen);
struct IC_CARD_FUNCTION
{
    pfic_card_send   ic_send;
    pfic_card_send   ic_machine_send;
    pfic_card_recv   ic_recv;
    pfic_card_get_reponse ic_get_rep;
    pfic_papdu_reponse    ic_proc_arep;
}ic_card;
void status_process1();
typedef struct ic_machine_msg
{
    UINT8  begin;
    UINT8  len_m;
    UINT8  len_l;
    UINT8  pmsg[128];
    UINT8  end;
    UINT8  bcc;
    UINT8  msg_len;
}ic_machine_msg;
/*****************************************************************************/
static UINT8 send_count;
static UINT8 send_len;
static UINT8 recv_len;

static UINT8 send_data[100];
static UINT8 local_data[100];
static UINT8 recv_data[100];
static UINT8 recv_adpu[100];

IC_CARD_STATUS ic_status;
ic_machine_msg  msg;
apdu_pk apdupack =
{  .cmd1 = APDU_CMD_M,
   .cmd2 = APDU_CMD_L,
};
static unsigned long errstat;


static BOOL   ic_card_get_reponse();
static UINT8  ic_card_send(UINT8 *buffer, UINT8 size);
static UINT32 ic_card_recv(UINT8 *buf, UINT8 size);
apdu_status process_apdu_reponse(UINT8 * dest,UINT8 *source, UINT8 *rlen);
/******************************************************************************/
void Mainui_Disp_Cardinfo(UINT8 cardtype,UINT8 *cn,float YUER,float YUQI,UINT8 XFLX)
{           olcd_clearsCreen();
                               switch(cardtype)
                                {
                                  case 1:

                                      olcm_dispprintf(0,1,"    班组卡      ");
                                      olcm_dispprintf(0,2,"卡号：%s",cn);
                        //              olcm_dispprintf(0,3,"权限: 设置  查询");
                        //              olcm_dispprintf(0,4,"      上下班    ");
                                        olcm_dispprintf(0,3,"余额：%.2f",YUER);
                                      olcm_dispprintf(0,4,"权限: 加气上下班");
                                      break;
                                  case 2:
                                      olcm_dispprintf(0,1,"    公司卡      ");
                                      olcm_dispprintf(0,2,"卡号：%s",cn);
                                      olcm_dispprintf(0,3,"余额：%.2f",YUER);
                                      olcm_dispprintf(0,4,"权限: 加气  查询");
                                      break;
                                  case  3:
                                      olcm_dispprintf(0,1,"    私车卡      ");
                                      olcm_dispprintf(0,2,"卡号：%s",cn);
                                      olcm_dispprintf(0,3,"余额：%.2f",YUER);
                                      olcm_dispprintf(0,4,"权限: 加气      ");
                                      break;
                                  case  4:
                                      olcm_dispprintf(0,1,"    管理卡      ");
                                      olcm_dispprintf(0,2,"卡号：%s",cn);
                                      olcm_dispprintf(0,3,"余额：%.2f",YUER);
                                      olcm_dispprintf(0,4,"权限: 设置      ");
                                      break;

                                  default:
                                               break;
                              }
                          


}
BOOL Get_Cardpsw(void)
{
UINT8 k = 100;
    UINT8 pswread[8],psws[8];
    int y;
    while(k)
    {
        k--;
    if(8==o24lcxxx_read_bytes_ex(CARD_PSW_MAIN_ADDR,(UINT8*)psws,8))
           {   delay_ms(100);
              o24lcxxx_read_bytes_ex(CARD_PSW_BACKUP_ADDR, (UINT8*)pswread, 8);

              y=memcmp(psws,pswread,8);
              if(memcmp(psws,pswread,8)==0)
              {
                  memcpy(KEY_CAR_PASS,psws,8);
                      return TRUE;
              }
              delay_ms(10);
            }
    }
    return FALSE;
}
UINT8 Save_cardpsw(UINT8 *psw)
{  UINT8 K = 100;
    UINT8 pswread[8],psws[8];
        memcpy(psws,psw,8);
//   UINT32 pswread = 0;
        int y;
    while(K)
      {  K--;
         if( 8==o24lcxxx_write_bytes_ex(CARD_PSW_MAIN_ADDR,(UINT8*)psws,8))
          {   delay_ms(100);
#if 1
              o24lcxxx_read_bytes_ex(CARD_PSW_MAIN_ADDR, (UINT8*)pswread, 8);
              y=memcmp(psws,pswread,8);
              if(memcmp(psws,pswread,8)==0)
                  { K=100;
                       while(K)
                          {  K--;
                             if( 8==o24lcxxx_write_bytes_ex(CARD_PSW_BACKUP_ADDR,(UINT8*)psws,8))
                              {   delay_ms(100);
                                  o24lcxxx_read_bytes_ex(CARD_PSW_BACKUP_ADDR, (UINT8*)pswread, 8);
                                     if(memcmp(psws,pswread,8)==0)
      //                            if(psw ==pswread)
                                    {
                                    return 1;
                                    }
                                 delay_ms(10);
                              }

                         }//end of while


                return 0;
                }
             delay_ms(10);
              return 0;
#endif
          }
         else
             return 0;

     }//end of while
}
/*
 *   使用时间验证秘钥
 *    ss190813  
 */
BOOL Check_Set_Pws_Data(void)
{
    UINT8 keyV;
    UINT8 len  = 0;
    UINT8 slen1,slen2;
    UINT8  bDot = 1;
    UINT8 psw1,psw2,psw5,psw6;
    UINT8    shift_op_time[6];
    INT8 tmpbuf[6];
     UINT32 KeyEccgtick = 0;
    
    ortcc_read_time(shift_op_time);
     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //小时*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //小时*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //日
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //日
     INT8 passbuf[6] = {psw1,psw2,'1','2',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(1,1,"获取IC秘钥");
    olcm_dispprintf(0,2,"请输入密码: ");
     while(1)
    {    
         keyV = osys_getkey_ex(); //Sys_GetKey();
        b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"请输入密码:     ");
            }
        if(keyV == _KEY_ENTER_EV_)
        {
            if(len >= 6)
            {
                if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                {
                    return TRUE;
                }
                else
                {   
                    len = 0;
                     olcd_clearsCreen();
                    olcm_dispprintf(0,2,"密码错误，请重输");
                     KeyEccgtick = gTick+100;
//                     return FALSE;
                }     
            }
        }
        if(keyV == _KEY_EXIT_EV_)
        {   
//            eVirtualKey = _KEY_EXIT_EV_;
            return FALSE;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
        keyV = 0;

        if(len < 7)
        {
            if(gTick >Runled_tick)
            {
                runled_fresh();//刷运行灯
                slen1 = len%2;
                slen2 = len/2;
                if(bDot)
                {
                    if(slen1 == 0)
                    { olcd_dispstr(0+slen2,3,"_      ",6);
                      if(slen2 ==3) //超过6位
                        olcd_dispstr(0+slen2,3," ",1);
                    }
                     else
                     olcd_dispstr(0+slen2,3,"*_    ",6);
                     if(slen2 > 0)
                        olcd_dispstr(0+slen2-1,3,"**",2);
                     if(slen2 > 1)
                        olcd_dispstr(0+slen2-2,3,"****",4);//弥补快速按键的*显示
                    bDot = 0;
                }
                else
                {

                    if(slen1 == 0)
                        olcd_dispstr(0+slen2,3,"      ",6);
                     else
                        olcd_dispstr(0+slen2,3,"*     ",6);
                    
                    if(slen2 > 0)
                        olcd_dispstr(0+slen2-1,3,"**",2);
                     bDot = 1;
                }
            }
        } //end of  if len <7
    }
     
     
}

void oGet_Sta_Cardpsw(void)
{
    UINT32 cardpsw;
    UINT8 psw[8];
     UINT8  rdkey = 0;
      olcd_clearsCreen();
    olcm_dispprintf(0,1,"是否获取IC秘钥");
    olcm_dispprintf(0,2,"确认键获取");
    olcm_dispprintf(0,3,"更改键返回");
    while(1)   //判断是否获取151015my
    {
      rdkey = ostatemachine_getkey();
         b_keyv = FALSE;

      if(_KEY_ENTER_EV_ == rdkey)
        {
           break;
         }
       if(_KEY_EXIT_EV_ == rdkey)
        {
           eVirtualKey = _KEY_VIRTUAL_EV_;
            return;
         }
     }
    
//    if(!Check_Set_Pws_Data())                   // 密码验证  ss190813     不需要验证秘钥
//    {
//        eVirtualKey = _KEY_VIRTUAL_EV_;
//            return;
//    }
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  获取秘钥");
    olcm_dispprintf(0,2,"正在获取秘钥....");
   if( down_get_password(psw)==TRUE )
   {
       if(1 == Save_cardpsw(psw))
         {
           memcpy(KEY_CAR_PASS,psw,8);
             olcm_dispprintf(0,2,"秘钥已获取成功");//保存
               o24lcxxx_write(TOP_POWER,0x27); //非首次上电标志
             osys_getkey(_KEY_EXIT_EV_,300);
             eVirtualKey = _KEY_VIRTUAL_EV_;
         }
   }
   else
   {
       olcm_dispprintf(0,2,"秘钥获取失败");//保存
     osys_getkey(_KEY_EXIT_EV_,300);
     eVirtualKey = _KEY_VIRTUAL_EV_;
   }
#if 0
    if(down_get_password(&psw[0])==TRUE )
    {

//    cardpsw = Get_Cardpswbypc();
 if(1 == Save_cardpsw(psw))
// if(1 == Save_cardpsw(cardpsw))
 {
     olcm_dispprintf(0,2,"秘钥已获取成功");//保存
     osys_getkey(_KEY_EXIT_EV_,300);
     eVirtualKey = _KEY_VIRTUAL_EV_;
     
 }
    }
#endif
}
static UINT8 bcc_check(UINT8 *data, UINT8 len)
{
    UINT8 result;
    UINT8 i;
    result = *data;
    data++;
    for(i =1; i<len; i++)
    {
        result ^= *data;
        data++;
    }
    return result;
}
/******************************************************************************/
/*interduction : the union function for ic card send and recv message         */
/******************************************************************************/
static UINT8  ic_card_send(UINT8 *buffer, UINT8 size)
{
    return Uart_Send_Data(UART4, buffer, size);
}
/**
 * 
 * @param data
 * @param len
 * @return
 */
static UINT8  ic_card_send_cmd( UINT8 *data, UINT8 len)
{
    
    if(ic_status == IC_CARD_IDLE)
    {
        recv_len = 0;
        send_len  = 0;
        ic_status = IC_CARD_SNED_MSG;
        msg.begin = STX;
        msg.len_m = 0x00;
        msg.len_l = len & 0xFF;
        memcpy(msg.pmsg, data, len);
        msg.end = ETX;
        msg.pmsg[len] = ETX;
        msg.msg_len  = len + ICMACHINE_MSG_EXTERN;
        msg.bcc = bcc_check((UINT8 *)&msg.begin, msg.msg_len -1);
        msg.pmsg[len+1] = msg.bcc;
        send_len = ic_card.ic_send((UINT8 *)&msg.begin, msg.msg_len);
        #if IC_CARD_DEBUG
        UINT8 i, *p;
        p = (UINT8 *)&msg.begin;
        oprint_printf("\r\n%d is %s\r\n",msg.msg_len, "ic_Card send:");
        for(i = 0; i < msg.msg_len; i++)
        oprint_printf("send %d data id 0x%x\r\n", i, *(p++));
        oprint_printf("\r\n");
         #endif
        //ic_card_delay();
        ic_delay_normal();
        ic_status = IC_CARD_WAIT_XCK;
    }
    ic_status = IC_CARD_WAIT_XCK;
    return send_len;
}
/**
 *
 * @param buf
 * @param size
 * @return
 */
static UINT32 ic_card_recv(UINT8 *buf, UINT8 size)
{
    return Uart_Get_Data(UART4, buf, size);
}
/**
 *
 * @return
 */
static   UINT8  recv_xck()
{
    UINT8 ack;
    ic_card.ic_recv(&ack, 1);
    //oprint_printf("machine get ack is ------0x%x\r\n", ack);
    if(ack == ACK) return ACK_REPONSE;
    if(ack == NAK) return NCK_REPONSE;
    return FAIL_REPONSE;
}
/**
 *
 */
static void  send_enq()
{
    UINT8 data = ENQ;
    ic_card.ic_send(&data, 1);
}
/*
 */
static BOOL  ic_card_get_reponse()
 {
	 UINT8 xck;
	 send_count = 0;
         UINT8 co;
	 switch(ic_status)
	 {
		 case IC_CARD_WAIT_XCK:
                 
repeat_send:     xck = recv_xck();
                  // oprint_printf("machine get ack is %d!!!\r\n", xck);
                 if(xck == ACK_REPONSE)
                 {
                   // oprint_printf("machine send ack!!!\r\n");
                    send_enq();
                 }
                 else //if(xck == NCK_REPONSE)
                 {
                         if(send_count < 3)
                         {
                             //ic_card.ic_send(send_data, send_count);
                             ic_status = IC_CARD_IDLE;
                             ic_card.ic_send((UINT8 *)&msg.begin, msg.msg_len);
                             send_count++;
                             ic_card_delay();
                            //oprint_printf("machine get NCK!!!\r\n");
                             goto  repeat_send;
                         }
                         else
                        {
                          //oprint_printf("machine get NCK!!!\r\n");
                          ic_status = IC_CARD_IDLE;
                          return FALSE;
                        }
                 }
		 case IC_CARD_WAIT_REPLY:
		 {
			 ic_card_delay();
			 if((recv_len = ic_card.ic_recv(recv_data, sizeof(recv_data))) > 0 )
                         {
                            ic_status = IC_CARD_IDLE;
                             #if IC_CARD_DEBUG
			      oprint_printf("\r\n%d is %s\r\n",recv_len, "ic_Card recv:");
			     for(co = 0; co < recv_len; co++)
				  oprint_printf("recv %d data id 0x%x\r\n", co,recv_data[co]);
			     oprint_printf("\r\n");
			     #endif
                            return TRUE;
                         }
			 break;
		 }
	 }
	  ic_status = IC_CARD_IDLE;
	  return FALSE;
 }

/**
 *
 * @param dest
 * @param source
 * @param rlen
 * @return
 */
apdu_status process_apdu_reponse(UINT8 * dest,UINT8 *source, UINT8 *rlen)
{
     UINT16 len;
     apdu_status status;
    if((source[0] == STX) && ((source[3] = APDU_CMD_M) &&(source[4] = APDU_CMD_L) ))
    {
        if(source[5] == APDUC_SUCCESS)
        {
           // len = (source[6] << 8)|source[7];
            len = source[7];
           // oprint_printf("len is %d\r\n", len);
            if(len > 0)
            {
               // oprint_printf("sw1 is 0x%x, sw2 is 0x%x\r\n",source[len+6], (source[len+7]));
                if(((source[len+6] == APDUC_SUCCESS1 )&&(source[len+7] == APDUC_SUCCESS2)))
                {                  
                     if(dest != NULL)
                     {
                         memcpy(dest, &source[8], len-2);
                        // oprint_printf("recv is %s\r\n",dest );
                         *rlen = len-2;
                     }
                     status = APDUS_SUCCESS;
                     return status;
                }
                else
                     status = APDUS_ERROR;
            }

        }
        else if(source[5] == APDUC_FAILE )   status = APDUS_FAILE;
        else if(source[5] == APDUC_NO_CARD)  status = APDUS_NO_CARD;
    }
     *rlen = 0;
     return status;
}

/************************************************************************************************/

 static BOOL ic_card_reset(void)
{
    UINT8 data[2] = {0x30, 0x40};//{MSG_MACHINE1,MSG_MACHINE2}; //0x30 0x40
    ic_card.ic_machine_send(data, 2);
    if(ic_card.ic_get_rep())
            {
              if((recv_data[3] == 0x30)&&(recv_data[4] == 0x40))
                    return TRUE;
            }
    return FALSE;
   
}
 static BOOL ic_card_active()
 {
    UINT8 data[2] = {MSG_MACHINE1+4,MSG_MACHINE2}; //0x30 0x40
    ic_card.ic_machine_send(data, 2);
    if(ic_card.ic_get_rep())
            {
              if((recv_data[3] == MSG_MACHINE1+4)&&(recv_data[4] == MSG_MACHINE2))
                    return TRUE;
            }
    return FALSE;
 }
 static BOOL ic_card_dece()     /// ss190307  
{
  UINT8 data[2] = {MSG_MACHINE1+4,MSG_MACHINE2+2}; //0x30 0x40
  ic_card.ic_machine_send(data, 2);
  if(ic_card.ic_get_rep())
          {
            if((recv_data[3] == MSG_MACHINE1+4)&&(recv_data[4] == MSG_MACHINE2+2))
                  return TRUE;
          }
  return FALSE;
}
void ic_card_active_sp()    /// ss190307  
{
 
//      if(ic_card_active())
//         olcm_dispprintf(0,4,"卡机复位中.....  ");
//    else  
//        olcm_dispprintf(0,4,"卡机复位失败 ");  
    ic_card_active();
    delay_ms(3000);

}
void ic_card_dece_sp()     /// ss190307  
{
//    if(ic_card_dece())
//         olcm_dispprintf(0,4,"卡机下电中.....  ");
//    else  
//        olcm_dispprintf(0,4,"卡机下电失败 ");
    ic_card_dece();
    delay_ms(3000);
//    eCurRunState = State_MainUI;
//    eVirtualKey = _KEY_EXIT_EV_;
}
static  void ic_card_set_baud(UINT32 baud)
{
    UINT8 baud_data[3];
    baud_data[0] = 0x36;
    baud_data[1] = (baud/4800)+0x31;
    ic_card_send_cmd(baud_data, 2);
    ic_card.ic_get_rep();
}
void  ic_card_init(UINT32 baud)
{
    UINT8 i;
    uart_config is_config;
    is_config.baud = baud;
    is_config.d_num = UART_DATA_SIZE_8_BITS;
    is_config.p_type = UART_PARITY_NONE;
    is_config.s_num  = UART_STOP_BITS_1;
    uart_init(IC_CARD_PORT, &is_config);
    ic_card.ic_send = ic_card_send;
    ic_card.ic_recv = ic_card_recv;
    ic_card.ic_machine_send = ic_card_send_cmd;
    ic_card.ic_get_rep = ic_card_get_reponse;
    ic_card.ic_proc_arep = process_apdu_reponse;
    ic_status = IC_CARD_IDLE;
    send_count = 0;
    send_len  = 0;
    recv_len = 0;
    delay_ms(2000);
    //ic_card_set_baud(9600);
    for(i =0; i < 10; i++)
    {
        if( ic_card_reset())
        {
            //oprint_printf("ic card reset success\r\n");
            break;
        }
    }
   // ic_card_active();
}

BOOL machine_has_card()
{
    // oprint_printf("log on have card  1111\r\n");
    UINT8 msg[2];
    msg[0] = MSG_MACHINE1+1;
    msg[1] = MSG_MACHINE2+1;
    ic_card.ic_machine_send(msg, 2);
    if(ic_card.ic_get_rep())
    {
        // oprint_printf("log on have card 222222\r\n");
         if(recv_data[3] ==  msg[0] && recv_data[4] == msg[1])
         {
           //oprint_printf("log on have card 3333333\r\n");
            if(recv_data[6] == 0x33)
            {
               return TRUE;
            }
         }
    }
    
    return FALSE;
}
card_status machine_status_card()//RG170705 
{
     UINT8 msg[2];
    msg[0] = MSG_MACHINE1+1;
    msg[1] = MSG_MACHINE2+1;
    ic_card.ic_machine_send(msg, 2);
    if(ic_card.ic_get_rep())
    {
         if(recv_data[3] ==  msg[0] && recv_data[4] == msg[1])
         {
		 if((recv_data[5] == 0x31)||(recv_data[6] == 0x30))
			 return NO_CARD;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x3f))
			 return NO_RECOGNISE;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x31))
			 return CPU_CONTACTOR;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x32))
			 return CPU_TYPE_B;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x33))
			 return CPU_TYPE_A;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x34))
			 return M1_CARD;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x35))
			 return AT88SC_CARD;
		 else if((recv_data[5] == 0x30)&&(recv_data[6] == 0x36))
			 return SLE4442_CARD;
		 else 
			 return HAVE_CARD;
		}
		else
		return HAVE_CARD;
    }
    else
    return HAVE_CARD;
}
/**
 *
 * @param fident
 * @param type
 * @return
 */
static apdu_status card_select_file(UINT16 fident, UINT8 type)
{
        apdu_status status = APDUS_ERROR;
        UINT8 len;
        apdupack.apdulen[0] = 0;
        apdupack.apdulen[1] = 7;
        apdupack.cla=0x00;
        apdupack.ins=SELECT_FILE;
        apdupack.p1=type;
        apdupack.p2=0x00;
        apdupack.p3=0x02;
        apdupack.pdata[0] =  (fident >> 8) & 0xFF;
        apdupack.pdata[1] =  fident & 0xFF;
        if(ic_card.ic_machine_send((UINT8 *)&apdupack.cmd1,11))
        {
            if(ic_card.ic_get_rep())
                status = ic_card.ic_proc_arep(NULL, recv_data, &len);
            else//rg623
                    status = APDUS_DKQERR;
	}
	return status;
}
static apdu_status ic_goto_dir()
{
    UINT8 i,j;
    apdu_status status,status2;
    for(i = 3; i>0; i--)
    {
      status = card_select_file(IC_MFDIR_FILENO, IC_READ_BINARY_TYPE);
      if( status  == APDUS_SUCCESS  )
      {
           for(j = 3; j>0; j--)
            {
                status = APDUS_ERROR;
                status = card_select_file(IC_INFODIR_FILENO, IC_READ_BINARY_TYPE);
                if(status  == APDUS_SUCCESS)
                {
                    status2=Current();
                   if( status2  != APDUS_AUTH_ERR  )
                        {
                           if( status2  != APDUS_ERROR  )
                           {return status;}
                           else
                            return APDUS_ERROR;
                         }
                }
            }         
      }
      else        // ss190108  遗漏dkpd状态， 现已增加
      {
          dkpd = status;
      }
     
    }
    return status;
 }
/**
 *
 * @param filenum
 * @param offset
 * @param sdata
 * @param len
 * @return
 */
UINT8 ic_card_readbin_selmu(UINT8 filenum,UINT8 offset ,UINT8 *sdata,UINT8 len)
{
        apdupack.apdulen[0] = 0;
        apdupack.apdulen[1] = 5;
        apdupack.cla=0x00;
        apdupack.ins=0xb0;
        apdupack.p1=(filenum & 0x1F)|0x80;
        apdupack.p2=offset & 0xFF;
        apdupack.p3=len&0xff;
        if(ic_card.ic_machine_send((UINT8 *)&apdupack.cmd1,9))
        {
             if(ic_card.ic_get_rep())
                 ic_card.ic_proc_arep(sdata, recv_data, &len);
        }
	return len ;
}


#define MAX_OPERATE_LEN 100
/**
 *
 * @param filename
 * @param offset
 * @param data
 * @param len
 * @return
 */
apdu_status card_writebin_selmu(UINT8 filename,UINT8 offset, UINT8 *data, UINT8 len)
{
        apdu_status statue = APDUS_ERROR;
	if(len > MAX_OPERATE_LEN)
		return -1;
        apdupack.apdulen[0] = 0;
        apdupack.apdulen[1] = 5+len;
        apdupack.cla = 0x00;
        apdupack.ins = APDU_WRITE_BINARY;
        apdupack.p1 = (filename & APDU_FILE_HIGH)| APDU_FILE_LOW;
        apdupack.p2 = offset & 0xff;
        apdupack.p3 = len;
        memcpy(apdupack.pdata, data, len);
        apdupack.pack_len = 9 + len;
         if(ic_card.ic_machine_send((UINT8 *)&apdupack.cmd1,apdupack.pack_len))
         {
            if(ic_card.ic_get_rep())
            {
                statue =  ic_card.ic_proc_arep(NULL, recv_data, &len);
                return statue;
            }
         }      
}




/**
 * name:
 * function:
 * @param name
 * @param pstr
 * @param len
 * @return
 */
UINT8 * ic_operate_info(UINT8 *name, UINT8 * pstr,UINT8 * len)
{
    UINT8 *pbegin;
    UINT8 * p1, * p2;
    if((pbegin = strstr(pstr, name)))
    {
        if((p1 = strchr(pbegin, ':')) && (p2 = strchr(pbegin, ';')))
        {
              p1 = strchr(pbegin, ':');
              p2 = strchr(pbegin, ';');
              *len =  (p2 - p1-1);
              //oprint_printf("the info len is %d\r\n", *len);
              return ++p1;
        }
    }
    return NULL;
}
UINT8 * ic_operate_info_int(UINT8 * pstr,UINT8 * len)
{
    UINT8 *pbegin,lenn,lenb,lenj;
    UINT8 * p1, * p2,* pb;
    UINT8 pint,sumlen,szcx;
    UINT8 bock[10],zh[10],i=0,j=0;
    pint=0;sumlen=0;
    pb=pstr;
    lenb=sizeof(pstr);
    memset(bock,0x00,10);
    memset(zh,0x00,10);
    memcpy(zh,pstr,10);
    p1 = strchr(pstr, '.');
    while(i<=10)
    {
        if(*(pb+j) == 0x2e)
        {pint=j;
            j++;}
        if(*(pb+j) == 0x00)
        {sumlen=i;
            break;}
        bock[i]=*(pb+j);
        j++;
        i++;
    }
    szcx=sumlen-pint;
    if((szcx==0x01)&&(sumlen<10))
        bock[i]=0x30;
    if((pint==0)&&(sumlen==9))
    {
        bock[i]=0x30;
    }
      if((pint==0)&&(sumlen<=8))
    {
        bock[i]=0x30;
        bock[i+1]=0x30;
    }
     *len = sumlen;
     p2=&bock[0];
     return p2;
}
/**
 * function:read infomation from the ic card file
 * @param fn:   the name of the file
 * @param buf:  the buf for storeing the information from the card
 * @param len:  if the function be called the param repsent the length of buf.
 *               if the function return ,the len respent the read length of information from the ic card
 * @param maxlen: every time the max len read from the card,avoid the waset of time
 * @return:apdu_status stand for the result;
 *          1.if the buf enough to store the read information,return APDUS_SUCCESS;
 *          2.if the buffer is small,return APDUS_OUT_BUF;
 *          3.if read failed, return APDUS_FAILE;
 */

apdu_status GetCard_info(UINT16 fn,UINT8 *buf,UINT8 *len, UINT8 maxlen)
{
    UINT8 i,recvlen = 0;
    UINT8 buf2[IC_MAX_READ_LEN];
    UINT8 count = 0;
    UINT8 buflen  = *len;
    //oprint_printf("sizeof buf is %d\r\n", sizeof(buf));
    for(i=0;i<10;i++)
     {
          memset(buf2,0,sizeof(buf2));
          ic_card_readbin_selmu(fn,i*maxlen,buf2,maxlen );
          recvlen = strlen(buf2);
          //oprint_printf("APDU recv len :%d\r\n",recvlen);
          //oprint_printf("buflen  len :%d\r\n",buflen);
          //oprint_printf("count  len :%d\r\n",count);
          if(buflen >=  (count + recvlen))
          {
             memcpy(buf+ count, buf2, recvlen);
             count += recvlen;
             if((maxlen > 50) &&(recvlen < (maxlen - 5 ))||((recvlen < maxlen)))
             {
                  *len = count;
                  return APDUS_SUCCESS;
             }              
          }
          else
          {
               *len = count;
               return APDUS_OUT_BUF;
          }        
     }
    return APDUS_FAILE;
}
/*************************************************************************************************/
/*******************        public  function for extern use     ***********************************/
/*************************************************************************************************/

/*************************      query information from the card     ******************************/
/*
 * author:   xiaolin  time:2013-3-12 21:24
 * Function: this function for being call by query the information of if card, when read the information
 *           success, the system while show the ic card information in display;
 *           when the exit key been pressed,the show window will return the query page;
 */
void oqry_downpass(void)
{
    UINT8 pass[8],pass0[8];
    UINT8 n;
    UINT16 addr;
    memset(pass,0,8);
    memset(pass0,0,8);
    if(TRUE == down_get_password(pass))
    {
        for(n=0;n<5;n++)
        {
            addr = (n*_PASS_PAGE_SIZE) + _PASS_EEP_ADDR;
            o24lcxxx_write_bytes(addr,(UINT8*)&pass,8 ); //存修改记录流水号
            delay_ms(100);
   //         o24lcxxx_read_bytes(addr,(UINT8*)&pass0,8);
            olcd_clearsCreen();
         olcm_dispprintf(0,1,"  下载成功    ");
        }
    }
    else
    {
        olcd_clearsCreen();
         olcm_dispprintf(0,1,"  下载失败    ");
    }
}
/* ------------------------获得卡的消费方式----------------------------*/
card_csum_type card_get_cstype(UINT8 * mbuf, UINT8 len)
{
      card_csum_type status = CONSUM_ERROR;

      if(memcmp(mbuf,"40000004",len) == 0)
      {
          status = PREE_MONEY;
       //  oprint_printf("the card is PREE_MONEY card\r\n");
      }
      if(memcmp(mbuf,"40000005",len) == 0)
      {
          status = PREE_GASE;
       //   oprint_printf("the card is PREE_GASE card\r\n");
      }
     if(memcmp(mbuf,"40000006",len) ==0)
      {
          status = ACCOUNT_MONEY;
    //      oprint_printf("the card is ACCOUNT_MONEY card\r\n");
      }
       if(memcmp(mbuf,"40000007",len) ==0)
      {
          status = ACCOUNT_GASS;
       //   oprint_printf("the card is ACCOUNT_GASS card\r\n");
      }
      return status;
}

void oqry_cardinfo(void)//150813
{
  UINT8 ibuf[200],mbuf[20];
  UINT8 jy[20],qy[20];
  UINT8 kh[10];
  UINT8 jxy[20],qxy[20],*zl;//150824
  UINT8 len,men[20],rdkey;
  UINT8 *p,dj,i,qx[4],xflx,cbh[16],gph[16];
  UINT8 * plen = &len;
  UINT8 jlh=0,bzh,bzh1[4];
  const UINT8 timeout = 0;
  UINT8 count;
  float ZK;
  UINT8 kk[10];//rg170621  插卡先输密码
  memset(kk,0x88,10);//rg170621  插卡先输密码 管理卡定为88
   apdu_status  status;
     UINT8  infoxs[][10]={
                              "号班组卡",
                              "公司卡",
                              "私车卡",
			      "管理卡",
			       "公司子卡",//rg170717
			       "公司母卡",//rg170717
                                    };

    UINT8  xfxs[][10]= {"预购金额","预购气量","记账金额","记账气量"};
      memset(cbh,0,16);
  memset(gph,0,16);
  while(1)
  {
          status = ic_goto_dir();
          olcd_clearsCreen();
          switch(status)
          {
              case APDUS_NO_CARD:
                   olcm_dispprintf(0,1,"  卡信息查询    ");
                   olcm_dispprintf(0,2,"请先插卡，再查询");
                   olcm_dispprintf(0,3,"  谢谢！！      ");
                   count += 10;
                   if(count > timeout)
                      break;
                   else
                      continue;

                   break;
              case APDUS_FAILE:
                   olcm_dispprintf(0,1,"  卡信息查询");
                   olcm_dispprintf(0,2,"读卡失败!!");
                   break;
              case APDUS_DKQERR:
                   olcm_dispprintf(0,1,"  卡信息查询");
                   olcm_dispprintf(0,2,"读卡器错误!!    ");
                    SOEACTION1(DKQ_GREY_ERR,eCurRunState);
                   break;
              case APDUS_SUCCESS:
              {

                  len = sizeof(ibuf);
                      memset(ibuf, 0, sizeof(ibuf));
                      if(GetCard_info(IC_INFO_FILENO,ibuf,plen,70) == APDUS_SUCCESS)
                      {
                                                     olcd_clearsCreen();
                                                      p = ic_operate_info("CN", ibuf, plen);
                                                       if(p==NULL)
                               {
                                   olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                               }
                                                                                                             else
                                                       {//rg170621  插卡先输密码
							       
                                                           memcpy(kh,p,10);
							   if(memcmp(kk,cure_yz_card,10) !=0)
							   {   
							    if(memcmp(kh,cure_yz_card,10) !=0)
							    {
								olcm_dispprintf(1,2,"密码未验证!");  
								olcm_dispprintf(1,3,"请重新插卡!");
								osys_getkey(_KEY_NULL_, 300);
								eVirtualKey = _KEY_VIRTUAL_EV_; 
								eCurRunState = State_MainUI;
								return;
							    }
						       }
							   
                                                       }
                               p = ic_operate_info("CONT",ibuf, &len);
                               if(p==NULL)
                               {
                                olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                               }
                               else
                               {
                               xflx = card_get_cstype(p, len);
                               }
                                 p = ic_operate_info("TN", ibuf, &len);
                                 if(p==NULL)
                               {
                                     olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                                 }
                                 else
                                 {
                                     memset(bzh1,0,sizeof(bzh1));   ///  ss190917  缺少缓存清空  导致 班组号错误
                                     memcpy(bzh1, p, len);
                                     bzh=atoi(bzh1);
                                 }

                                p = ic_operate_info("CDT", ibuf, &len);
                               if(p==NULL)
                               {
                                   olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                               }
                               else
                               {
				if(memcmp(p,"40000001",len) == 0)
				{
					jlh=0;
				}
				else if(memcmp(p,"40000002",len) == 0)
				{
					jlh=1;
				}
				else if(memcmp(p,"40000003",len) == 0)
				{
					jlh=2;
				}
				else if(memcmp(p,"40000024",len) == 0)
				{
					jlh=3;
				}
				else if(memcmp(p,"40000005",len) == 0)
				{
					jlh=4;
				}
				else if(memcmp(p,"40000055",len) == 0)
				{
					jlh=5;
				}
				else
					jlh=6;
				/*
                               switch(*(p+len-1))
                                {
                                  case '1':
                                      jlh=0;
                                      break;
                                  case '2':
                                      jlh=1;
                                      break;
                                  case '3':
                                        jlh=2;
                                      break;
                                  case '4':
                                      jlh=3;
                                      break;
				   case '7'://rg170717
                                      jlh=4;//rg170717
                                      break;  //rg170717
				      case '8'://rg170717
                                      jlh=5;//rg170717
                                      break;//rg170717
                                  default:
                                       jlh=6;
                                               break;
                              }
				  */
                               }
                             p = ic_operate_info("PT", ibuf, &len);
                               if(p==NULL)
                               {
                                   olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                                 }
                               else
                               {
                                     memset(men,0,4);
                                     memcpy(men,p,len);
                                     dj = (UINT8)atoi(men);
                               }
                             p = ic_operate_info("DR",ibuf, &len);
                               if(p==NULL)
                               {
                                   olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                                     }
                               else
                               {
                                  memset(men,0,4);
                                memcpy(men,p,len);
                                ZK=(float)atof(men);
                                }
                              p = ic_operate_info("VD",ibuf, &len);
                              if(p==NULL)
                               {
                                 olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                               }
                              else
                              {
                                       memset(men,0,8);
                                       memcpy(men,p,len);
                                       for(i=0;i<4;i++)
                                       {
                                       qx[i]=((men[2*i]-0x30)<<4)+(men[2*i+1]-0x30);
                                       }
                              }
#if 1
                             p = ic_operate_info("CBH",ibuf, &len);//车牌号
                              if(p==NULL)
                               {
                                 }
                              else
                              {

                                       memcpy(cbh,p,len);
                              }
                             p = ic_operate_info("GP",ibuf, &len);//钢瓶号
                              if(p==NULL)
                               {
                                 }
                              else
                              {
                                         memcpy(gph,p,len);
                              }
#endif
                      }
                      else
                      {olcm_dispprintf(1,2,"读卡失败!!");
                      break;}
                          len = sizeof(jy);
                          memset(jy, 0, sizeof(jy));
                          memset(jxy, 0, sizeof(jxy));//150824
			  if(jlh<3)//rg170717
			  {
                          if(GetCard_info(IC_MEM_FILENO,jy,plen,10) == APDUS_SUCCESS)
                          {

                           }
                          zl=ic_conv_un_lj(jy);//150824
                          memcpy(jxy,zl,10);//150824
                          len = sizeof(qy);
                          memset(qy, 0, sizeof(qy));
                          memset(qxy, 0, sizeof(qxy));//150824
                          if(GetCard_info(IC_GAS_FILENO,qy,plen,10) == APDUS_SUCCESS)
                          {
                          }
                          zl=ic_conv_un_lj(qy);//150824
                          memcpy(qxy,zl,10);//150824
			  }
			  else if((jlh == 4)||(jlh == 5))
			  {
				  jxy[0]=0x30;
				  qxy[0]=0x30;
			  }
                           if(jlh>=6)//rg170717
                   {
                               olcd_clearsCreen();
                           olcd_dispstr(2,2,"无效卡",6);
   //                        olcm_dispprintf(0,3,"权限: 仅限设置  ");
                   }
                           else  if(jlh==3)
                   {
                               olcd_clearsCreen();
                           olcd_dispstr(2,1,"管理卡",6);
                           olcm_dispprintf(0,3,"权限: 仅限设置  ");
                   }
 
                          else
                          {
                        olcd_clearsCreen();
                         olcm_dispprintf(0,1,"卡号：");
                         olcd_dispstr(3,1,kh,strlen(kh));
                          olcm_dispprintf(0,2,"类型：");
                           if(jlh==0)
                           {   
                               olcm_dispprintf(3,2,"%d",bzh);
                               olcd_dispstr(4,2,&infoxs[jlh][0],strlen((UINT8 *)&infoxs[jlh][0]));
                            }
                           else
                           olcd_dispstr(3,2,&infoxs[jlh][0],strlen((UINT8 *)&infoxs[jlh][0]));
                          if((xflx==0)||(xflx==2))
                          {olcm_dispprintf(0,3,"金余：");
                          olcd_dispstr(3,3,jxy,strlen(jxy));//150824
                          }
                          if((xflx==1)||(xflx==3))
                          {olcm_dispprintf(0,3,"气余：");
                          olcd_dispstr(3,3,qxy,strlen(qxy));//150824
                          }
                          olcm_dispprintf(0,4,"结算：");
                          olcd_dispstr(3,4,&xfxs[xflx][0],strlen((UINT8 *)&xfxs[xflx][0]));
                          olcm_dispprintf(7,4,"↓");
                          }
                          while(1)
                          {      rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey) break;
                   if(_KEY_EXIT_EV_ == rdkey) break;

                   if((_KEY_SW_EV_ == rdkey)&&((jlh<=2)||(jlh==4)))
                   {
                        i=1;
                        olcd_clearsCreen();
 
                        olcm_dispprintf(0,1,"单价%d",dj);
                        if(ZK==100)
                        olcm_dispprintf(4,1,"%06.02f％",ZK);
                        else
                        olcm_dispprintf(4,1,"% 05.02f％",ZK);
                        olcm_dispprintf(0,2,"有效期：%2x%02x%02x%02x",qx[0],qx[1],qx[2],qx[3]);

                        if((cbh[0]==0)&&(cbh[1]==0))
                        {

                        }
                        else
                        {
                             olcm_dispprintf(0,3,"车牌：");
                             olcd_dispstr(3,3,cbh,strlen(cbh));

                        }
#if 0
                         if(gph[0]==0)
                        {

                        }
                        else
                        {
                             olcm_dispprintf(0,4,"钢瓶：");
                             olcd_dispstr(3,4,gph,strlen(gph));

                        }
#endif
                        olcm_dispprintf(7,4,"↑");
                  }
                   if((_KEY_UP_EV_ == rdkey)&&((jlh<=2)||(jlh==4)))
                   {
                        i=0;
                        olcd_clearsCreen();
                         olcm_dispprintf(0,1,"卡号：");
                         olcd_dispstr(3,1,kh,strlen(kh));
                           olcm_dispprintf(0,2,"类型：");
                           if(jlh==0)
                           {  
                                olcm_dispprintf(3,2,"%d",bzh);
                               olcd_dispstr(4,2,&infoxs[jlh][0],strlen((UINT8 *)&infoxs[jlh][0]));}
                           else
                           olcd_dispstr(3,2,&infoxs[jlh][0],strlen((UINT8 *)&infoxs[jlh][0]));
                            if((xflx==0)||(xflx==2))
                          {olcm_dispprintf(0,3,"金余：");
                          olcd_dispstr(3,3,jxy,strlen(jxy));//150824
                          }
                          if((xflx==1)||(xflx==3))
                          {olcm_dispprintf(0,3,"气余：");
                          olcd_dispstr(3,3,qxy,strlen(qxy));//150824
                          }
                          olcm_dispprintf(0,4,"结算：");
                          olcd_dispstr(3,4,&xfxs[xflx][0],strlen((UINT8 *)&xfxs[xflx][0]));
                         olcm_dispprintf(7,4,"↓");
                   }
                          }
                      break;
              }

      }
     break;
  }

     while(osys_getkey(_KEY_EXIT_EV_,50));
     eVirtualKey = _KEY_VIRTUAL_EV_;
}
BOOL ic_card_get_info(UINT8 *buf, UINT8 *len)
{
     UINT8 ibuf[200];
     UINT8 rlen = sizeof(ibuf);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        memset(ibuf, 0, sizeof(ibuf));
        if(GetCard_info(IC_INFO_FILENO,ibuf,&rlen,70) == APDUS_SUCCESS)
        {
            if(rlen >0 && *len > rlen)
            {
                memcpy(buf, ibuf, rlen);
                *len = rlen;
                return TRUE;
            }
        }
    }
     return FALSE;
}
BOOL ic_card_get_info_nosel(UINT8 *buf, UINT8 *len)
{
     UINT8 ibuf[200];
     UINT8 rlen = sizeof(ibuf);
         memset(ibuf, 0, sizeof(ibuf));
        if(GetCard_info(IC_INFO_FILENO,ibuf,&rlen,70) == APDUS_SUCCESS)
        {
            if(rlen >0 && *len > rlen)
            {
                memcpy(buf, ibuf, rlen);
                *len = rlen;
                return TRUE;
            }
        }
}
/******************        get money from ic card        **********************/
#define IC_WRITE_LEN  10
BOOL ic_card_get_money(float * money)
{
    UINT8 mbuf[10];
    UINT8 len = sizeof(mbuf);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        memset(mbuf, 0, sizeof(mbuf));
        if(GetCard_info(IC_MEM_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        { 
            if(len > 0)
              * money = (float)atof(mbuf);
            else
                return FALSE;
            return TRUE;
        }
    }
    return FALSE;
}
#if 0
BOOL ic_card_Direct_get_money(float * money)
{
    UINT8 mbuf[10];
    UINT8 len = sizeof(mbuf);
        memset(mbuf, 0, sizeof(mbuf));
        if(GetCard_info(IC_MEM_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(len > 0)
              * money = (float)atof(mbuf);
            else
                return FALSE;
            return TRUE;
        }
    return FALSE;
}
#endif
BOOL ic_card_Direct_get_money(float * money,INT32 * m_int,UINT8 *lenn)
{
    UINT8 mbuf[12];
    UINT8 len = sizeof(mbuf);
    UINT8 len2;
    UINT8 zh[10],*zz,*zl;
        memset(mbuf, 0, sizeof(mbuf));
        memset(zh, 0, sizeof(zh));
        if(GetCard_info(IC_MEM_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(len > 0)
            {   
            * money = (float)atof(mbuf);//150824
            zl=ic_conv_un_lj(mbuf);//150824
            memcpy(zh,zl,10);//150824
            zz =ic_operate_info_int(zh,&len2);
            * m_int=atoi(zz);
            *lenn=len2;
            }
            else
                return FALSE;
            return TRUE;
        }
    return FALSE;
}
UINT8 * inttoa(INT32 ye)
{
   UINT8 mbuf[10],nbuf[10],i;
   UINT8 *p;
    memset(mbuf, 0, sizeof(mbuf));
    memset(nbuf, 0, sizeof(nbuf));
    itoa(mbuf,ye,10);
    i=0;
    while(mbuf[i]!=0x00)
    {
        nbuf[i]=mbuf[i];
        i++;
    }
    //*****************//rg170612 班组卡余额小于1的处理（原来是将分抹去）*************//      
    //Mengfr 20170616
    if ((mbuf[0] == 0x2d)&&(i == 3)) {
		nbuf[0] = 0x2d;
		nbuf[1] = 0x30;
		nbuf[2] = 0x2e;
		nbuf[3] = mbuf[1];
		nbuf[4] = mbuf[2];
		
		p=nbuf;
		return p;
	}
    if ((mbuf[0] == 0x2d)&&(i == 2)) {//rg170626
			nbuf[0] = mbuf[0];
			nbuf[1] = 0x30;
			nbuf[2] = 0x2e;
			nbuf[3] = 0x30;
			nbuf[4] = mbuf[1];
			p=nbuf;
			return p;
		}
    //*****************//rg170612 班组卡余额小于1的处理（原来是将分抹去）*************//   

   if(i>2)
   {
    nbuf[i-2]=0x2e;
    nbuf[i-1]=mbuf[i-2];
    nbuf[i]=mbuf[i-1];
   }
    p=nbuf;
    return p;
}
BOOL ic_card_put_money(INT32  money)
{
    UINT8 mbuf[10],nbuf[10],i;
    memset(mbuf, 0, sizeof(mbuf));
    memset(nbuf, 0, sizeof(nbuf));
    itoa(mbuf,money,10);
    i=0;
    while(mbuf[i]!=0x00)
    {
        nbuf[i]=mbuf[i];
        i++;
    }
//*****************//rg170612 班组卡余额小于1的处理（原来是将分抹去）*************//   
		if ((mbuf[0] == 0x2d)&&(i == 3)) {
			nbuf[0] = 0x2d;
			nbuf[1] = 0x30;
			nbuf[2] = 0x2e;
			nbuf[3] = mbuf[1];
			nbuf[4] = mbuf[2];
			goto kk;
		}
    if ((mbuf[0] == 0x2d)&&(i == 2)) {
			nbuf[0] = mbuf[0];
			nbuf[1] = 0x30;
			nbuf[2] = 0x2e;
			nbuf[3] = 0x30;
			nbuf[4] = mbuf[1];
			goto kk;
		}
//*****************//rg170612 班组卡余额小于1的处理（原来是将分抹去）end****************************************//       
 
   if(i>2)
   {nbuf[i-2]=0x2e;
    nbuf[i-1]=mbuf[i-2];
    nbuf[i]=mbuf[i-1];}
       else if(i==2)
   {nbuf[0]=0x30;
        nbuf[1]=0x2e;
    nbuf[2]=mbuf[0];
    nbuf[3]=mbuf[1];}
    else if(i==1)
    {nbuf[0]=0x30;
     nbuf[1]=0x2e;
    nbuf[2]=mbuf[0];
    }
 kk:   if(ic_goto_dir() == APDUS_SUCCESS)
    {
        if( card_writebin_selmu(IC_MEM_FILENO, 0, nbuf, IC_WRITE_LEN)== APDUS_SUCCESS)
            return TRUE;
    }
    return FALSE;
}
BOOL ic_card_get_gass(float * gass)
{
    UINT8 mbuf[10];
    UINT8 len = sizeof(mbuf);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        memset(mbuf, 0, sizeof(mbuf));
        if(GetCard_info(IC_GAS_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(len > 0)
              * gass = (float)atof(mbuf);
            else
                return FALSE;
            return TRUE;
        }
    }
    return FALSE;
}
BOOL ic_card_Direct_get_gass(float * gass,INT32 * m_int,UINT8 *lenn)
{
    UINT8 mbuf[12];
    UINT8 len = sizeof(mbuf);
    UINT8 len2;
    UINT8 zh[10],*zz,*zl;
        memset(mbuf, 0, sizeof(mbuf));
        memset(zh, 0, sizeof(zh));
        if(GetCard_info(IC_GAS_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(len > 0)
            {  
             * gass = (float)atof(mbuf);//150824
            zl=ic_conv_un_lj(mbuf);//150824
            memcpy(zh,zl,10);//150824
            zz =ic_operate_info_int(zh,&len2);
            * m_int=atoi(zz);
            *lenn=len2;
            }
            else
                return FALSE;
            return TRUE;
        }
    return FALSE;
}
#if 0
BOOL ic_card_put_gass(float  gass)
{
    UINT8 mbuf[10];
    memset(mbuf, 0, sizeof(mbuf));
    sprintf(mbuf, "%.2f", gass);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        if( card_writebin_selmu(IC_GAS_FILENO, 0, mbuf, IC_WRITE_LEN)== APDUS_SUCCESS)
            return TRUE;
    }
    return FALSE;
}
#endif
#if 0
BOOL ic_card_Direct_get_gass(float * gass)
{
    UINT8 mbuf[10];
    UINT8 len = sizeof(mbuf);
        memset(mbuf, 0, sizeof(mbuf));
        if(GetCard_info(IC_GAS_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(len > 0)
              * gass = (float)atof(mbuf);
            else
                return FALSE;
            return TRUE;
        }
    return FALSE;
}
#endif
BOOL ic_card_put_gass(INT32  gass)
{
    UINT8 mbuf[10],nbuf[10],i;
    memset(mbuf, 0, sizeof(mbuf));
    memset(nbuf, 0, sizeof(nbuf));
    itoa(mbuf,gass,10);
    i=0;
    while(mbuf[i]!=0x00)
    {
        nbuf[i]=mbuf[i];
        i++;
    }
 //*****************//rg170612 班组卡余额小于1的处理（原来是将分抹去）*************//   
		if ((mbuf[0] == 0x2d)&&(i == 3)) {
			nbuf[0] = 0x2d;
			nbuf[1] = 0x30;
			nbuf[2] = 0x2e;
			nbuf[3] = mbuf[1];
			nbuf[4] = mbuf[2];
			goto kk;
		}
    if ((mbuf[0] == 0x2d)&&(i == 2)) {
			nbuf[0] = mbuf[0];
			nbuf[1] = 0x30;
			nbuf[2] = 0x2e;
			nbuf[3] = 0x30;
			nbuf[4] = mbuf[1];
			goto kk;
		}
//*****************//rg170612 班组卡余额小于1的处理（原来是将分抹去）end****************************************//       
    if(i>2)
   {nbuf[i-2]=0x2e;
    nbuf[i-1]=mbuf[i-2];
    nbuf[i]=mbuf[i-1];}
   else if(i==2)
   {nbuf[0]=0x30;
        nbuf[1]=0x2e;
    nbuf[2]=mbuf[0];
    nbuf[3]=mbuf[1];}
    else if(i==1)
    {nbuf[0]=0x30;
     nbuf[1]=0x2e;
    nbuf[2]=mbuf[0];
    }
 kk:   if(ic_goto_dir() == APDUS_SUCCESS)
    {
        if( card_writebin_selmu(IC_GAS_FILENO, 0, nbuf, IC_WRITE_LEN)== APDUS_SUCCESS)
            return TRUE;
    }
    return FALSE;
}
BOOL ic_card_get_password(UINT8 * password, UINT8 *len)
{
    UINT8 rlen = *len;
    if(*len > IC_WRITE_LEN)
        return FALSE;
    memset(password, 0, rlen);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        if(GetCard_info(IC_PAS_FILENO,password,len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(*len > 0)
              return TRUE;
        }
    }
    return FALSE;
}
BOOL ic_card_put_password(UINT8 * password, UINT8 len)
{
    UINT8 mbuf[10];
    if(len > 10) return FALSE;
    memset(mbuf, 0, sizeof(mbuf));
    memcpy(mbuf, password, len);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        if( card_writebin_selmu(IC_PAS_FILENO, 0, mbuf, IC_WRITE_LEN)== APDUS_SUCCESS)
            return TRUE;
    }
    return FALSE;
}
card_status ic_card_get_status()
{
    UINT8 mbuf[10];
    card_status status = CARDS_ERR;
    UINT8 len = sizeof(mbuf);
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
        memset(mbuf, 0, sizeof(mbuf));
        if(GetCard_info(IC_STA_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(mbuf==NULL)
   {
        status = CARDS_NO_CARD;
        return status;
   }
            if(len > 0)
            {
                  if(memcmp(mbuf,"40000010",len) == 0)
                  {
                      status = CARDS_NORMAL;
                  }
                  else if(memcmp(mbuf,"40000012",len) == 0) 
                  {
                      status = CARDS_NULLIFY;
                  }
                  else if(memcmp(mbuf,"40000013",len) ==0)
                  {
                      status = CARDS_GREY;
                  }
            }
        }
    }
    else
    {
        status = CARDS_NO_CARD;
    }
    return status;
}
card_status ic_card_get_status_nosel()//rg 1011
{
    UINT8 mbuf[10];
    card_status status = CARDS_ERR;
    UINT8 len = sizeof(mbuf);
        memset(mbuf, 0, sizeof(mbuf));
        if(GetCard_info(IC_STA_FILENO,mbuf,&len,IC_WRITE_LEN) == APDUS_SUCCESS)
        {
            if(mbuf==NULL)
   {
        status = CARDS_NO_CARD;
        return status;
   }
            if(len > 0)
            {
                  if(memcmp(mbuf,"40000010",len) == 0)
                  {
                      status = CARDS_NORMAL;
                  }
                  else if(memcmp(mbuf,"40000012",len) == 0)
                  {
                      status = CARDS_NULLIFY;
                  }
                  else if(memcmp(mbuf,"40000013",len) ==0)
                  {
                      status = CARDS_GREY;
                  }
            }
        }
     return status;
}
BOOL ic_card_put_status(card_status status)
{
    UINT8 mbuf[IC_WRITE_LEN];
    memset(mbuf, 0, sizeof(mbuf));
    switch(status)
    {
        case CARDS_NORMAL:
            memcpy(mbuf,"40000010",8 );
            break;
        case CARDS_GREY:
             memcpy(mbuf,"40000013",8 );
            break;
        case CARDS_NULLIFY:
            memcpy(mbuf,"40000012",8 );
            break;
    }
     if(ic_goto_dir() == APDUS_SUCCESS)
     {
        if( card_writebin_selmu(IC_STA_FILENO, 0, mbuf, IC_WRITE_LEN)== APDUS_SUCCESS)
            return TRUE;
      }
    return FALSE;
}

BOOL ic_card_put_info(UINT8 * info, UINT8 len )
{
    UINT8 mbuf[40];
    UINT8 len2 = (len+10)/5;
    UINT8 i;
    if(ic_goto_dir() == APDUS_SUCCESS)
    {
       for(i =0; i < 5;i++)
      {           
        memset(mbuf, 0, sizeof(mbuf));
        memcpy(mbuf, info+len2*i, len2);
        //oprint_printf("write info 1 len is %d\r\n", len2);
        card_writebin_selmu(IC_INFO_FILENO, len2*i, mbuf, len2);
        //oprint_printf("info 1 is %s\r\n", mbuf);
       }
    }
    return FALSE;
}

card_type ic_card_get_type(UINT8 * mbuf, UINT8 len)//rg170717
{
      card_type status = CARDT_ERROR;
      if(memcmp(mbuf,"40000001",len) == 0)
      {
          status = CARDT_CLASS;
      }
      else if(memcmp(mbuf,"40000002",len) == 0)
      {
          status = CARDT_COMPANY;
      }
     else if(memcmp(mbuf,"40000003",len) ==0)
      {
          status = CARDT_PERSON;
      }
       else if(memcmp(mbuf,"40000004",len) ==0)
      {
          status = CARDT_WORKER;
      }
      else if(memcmp(mbuf,"40000024",len) ==0)
      {
          status = CARDT_ADMINI;
      }
      else if(memcmp(mbuf,"40000005",len) ==0)
      {
          status = CARDT_SMALL;
      }
      else if(memcmp(mbuf,"40000055",len) ==0)
      {
          status = CARDT_MOTHER;
      }
      else
	     status = CARDT_ERROR; 
      return status;
}
BOOL ReadCard_info(UINT8 *card_type,UINT8 * cn, float *card_preM,float *card_preg,INT32 *card_preM_int,INT32 *card_preg_int,float *ml,float *gl,UINT8 *XFLX,UINT8 *dj,float *zkl,UINT8 *zkqx,UINT8 *cpbh,UINT8 *gpbh)//获得卡信息，返回值为1表示获得信息，0为未获得信息。
{
    Compa_float zh;
  UINT8 ibuf[200],mbuf[20];
  UINT8 men[10],qx[4],cbh[16],gph[16],mem[20];
  UINT8 *p;
//  UINT8 *zkqx;
  UINT8 len,i;
//  UINT8 DD[10];
  INT32 M_INT,G_INT;
  UINT8 m_len,g_len;
  UINT8 * plen = &len;
  UINT8 numlen;
//  float zkl;
  apdu_status  status;
                    status = ic_goto_dir();
                   if(status==APDUS_SUCCESS)
                    {
                        len = sizeof(ibuf);
                      memset(ibuf, 0, sizeof(ibuf));
                      if(GetCard_info(IC_INFO_FILENO,ibuf,plen,70) == APDUS_SUCCESS)
                      {
                              p = ic_operate_info("CN",ibuf, &len);
                              if(p==NULL)
                               {
                                 return FALSE;
                               }
                              else
                              {memset(cn, 0, 10);
                               memcpy(cn, p, 10);}
                               p = ic_operate_info("CDT", ibuf, &len);
                               if(p==NULL)
                               {
                                 return FALSE;
                               }
                               else
                               {
//************************************rg170717 子母卡********************************************//				       
				       if(memcmp(p,"40000001",len) == 0)
					  *card_type=1;   
				       else if(memcmp(p,"40000002",len) == 0)
					  *card_type=2;    
				       else if(memcmp(p,"40000003",len) == 0)
					  *card_type=3;   
				       else if(memcmp(p,"40000024",len) == 0)
					  *card_type=5; 
				       else if(memcmp(p,"40000005",len) == 0)
					  *card_type=7;   
				       else if(memcmp(p,"40000055",len) == 0)
					  *card_type=8; 
				       else 
					       *card_type=6;
                        /*       switch(*(p+len-1))
                                {
                                  case '1':
                                      *card_type=1;
                                       break;
                                  case '2':
                                      *card_type=2;
                                      break;
                                  case '3':
                                      *card_type=3;
                                       break;
                                  case '4':
                                      *card_type=4;
                                      break;
                                  default:
                                               break;
                              }*/
//*******************************************************************************//					       
                               }
                               p = ic_operate_info("ML",ibuf, &len);
                               if(p!=NULL)
                               {
                                   if(len>0)
                                   {
                                       memset(men,0,10);
                                       memcpy(men,p,len);
                                       * ml = (float)atof(men);
                                   }
                                    else
                                       * ml = 0;
                               }
                               else
                                       * ml = 0;
                               p = ic_operate_info("GL",ibuf, &len);
                                 if(p!=NULL)
                               {
                                   if(len>0)
                                   {
                                       memset(men,0,10);
                                       memcpy(men,p,len);
                                       * gl = (float)atof(men);
                                   }
                                    else
                                     * gl =0;
                               }
                               else
                                 * gl =0;
                               p = ic_operate_info("CONT",ibuf, &len);
                               if(p==NULL)
                               {
                                 return FALSE;
                               }
                               else
                               {
                               *XFLX = card_get_cstype(p, len);
                               }
                             p = ic_operate_info("PT", ibuf, &len);
                               if(p==NULL)
                               {
                                 return FALSE;
                               }
                               else
                               {
                                     memset(men,0,4);
                                     memcpy(men,p,len);
                                     * dj = (UINT8)atoi(men);
                               }
                             p = ic_operate_info("DR",ibuf, &len);
                               if(p==NULL)
                               {
                                 return FALSE;
                               }
                               else
                               {
                                  memset(men,0,4);
                                memcpy(men,p,len);
                                *zkl=(float)atof(men);
                                }
#if 1
			     //rg170607 加气信息车牌号  前面已读过，忽略此处车牌号
   /*                         p = ic_operate_info("CBH",ibuf, &len);//车牌号
                              if(p==NULL)
                               {
                                 memset(cpbh,0,16);

                                 }
                              else
                              {
                                       memset(cpbh,0,16);
                                       memcpy(cpbh,p,len);
     //                                  cpbh=cbh;
                              }*/
			     memset(cpbh,0,16);//rg170607 加气信息车牌号
                             p = ic_operate_info("GP",ibuf, &len);//钢瓶号
                              if(p==NULL)
                               {
                                  memset(gpbh,0,16);
                                 }
                              else
                              {
                                       memset(gpbh,0,16);
                                       memcpy(gpbh,p,len);
//                                       gpbh=gph;
                              }
#endif
                             p = ic_operate_info("VD",ibuf, &len);
                              if(p==NULL)
                               {
                                 return FALSE;
                               }
                              else
                              {
                                       memset(men,0,8);
                                       memcpy(men,p,len);
                                       for(i=0;i<4;i++)
                                       {
                                       qx[i]=((men[2*i]-0x30)<<4)+(men[2*i+1]-0x30);
                                       }
                                       memcpy(zkqx,qx,4);
                              }
                          }
                        ic_card_Direct_get_gass(card_preg,&G_INT,&g_len);
                        ic_card_Direct_get_money(card_preM,&M_INT,&m_len);//rd_preM);
                        *card_preM_int=M_INT;
                        *card_preg_int=G_INT;
                           return TRUE;
                   }
                   else
                       return FALSE;
 }

void olng_operate_card(void)
{
      if(machine_has_card())
    { _b_have_card = TRUE;
     }
    else
    {_b_have_card = FALSE;
    _b_cz_card=FALSE;
    memset(cure_yz_card,0x0,10);//rg170619
    read_keyv_CS = 0;//rg170626
    }
  //    b_mainui =TRUE;
#if 0
    if(machine_has_card())
        _b_have_card = TRUE;
    else
        _b_have_card = FALSE;
    eVirtualKey = _EVENT_TRUE;
#endif
}
int card_getchal(unsigned char *chal,UINT8 len)
{
 //       delay_ms(20);
        apdupack.apdulen[0] = 0;
        apdupack.apdulen[1] = 5;
        apdupack.cla=0x00;
        apdupack.ins=0x84;
        apdupack.p1=0x00;
        apdupack.p2=0x00;
        apdupack.p3=0x04;
        apdupack.pack_len = 0x09+0x08;

         if(ic_card.ic_machine_send((UINT8 *)&apdupack.cmd1,9))
        {
             if(ic_card.ic_get_rep())
                 ic_card.ic_proc_arep(chal, recv_data, &len);
        }
	return len ;
}


int external_authentication(unsigned char secret, unsigned char *data, int datalen)
{
    apdu_status statud = APDUS_AUTH_ERR;
        UINT8 len=0x08;
        apdupack.apdulen[0] = 0;
        apdupack.apdulen[1] = 5+len;
        apdupack.cla=0x00;
        apdupack.ins=EXTERN_AUTH;
        apdupack.p1=0x00;
        apdupack.p2=secret;
        apdupack.p3=0x08;

        memcpy(apdupack.pdata, data, 0x08);
        apdupack.pack_len = 9 + 0x08;

        if(read_keyv_CS <5)
        {
         if(ic_card.ic_machine_send((UINT8 *)&apdupack.cmd1,apdupack.pack_len))
         {
            if(ic_card.ic_get_rep())
            {
                statud =  ic_card.ic_proc_arep(NULL, recv_data, &len);

                if(statud == 0x02)
                {
                    read_keyv_CS++;
                    olcd_clearsCreen();
                    olcm_dispprintf(0,1,"此卡秘钥错误");
                     olcm_dispprintf(0,2,"或卡已损坏");//rg170626   修改提示

                    osys_getkey(_KEY_EXIT_EV_,320);
                    return statud;
                }
                 read_keyv_CS = 0;
                return statud;
            }

         }
        }

    return statud;
}
UINT8 Car_Experimental()
{
    UINT8 Num_Verif,ed;
    UINT8 carnum[10];
    float yue;
   if((CARD_XIAOFEI==ACCOUNT_MONEY)||(CARD_XIAOFEI==PREE_MONEY))//金额
     {
        ed=1;
        yue=Rec_Card_PreM;
        Num_Verif=Card_Verif(CN,ed,yue);
        return Num_Verif;
     }
     else if((CARD_XIAOFEI==ACCOUNT_GASS)||(CARD_XIAOFEI==PREE_GASE))////气量
     {
         ed=2;
         yue=Rec_Card_Preg;
         Num_Verif=Card_Verif(carnum,ed,yue);
         return Num_Verif;
     }
     else
     return 0xad;
}
void omodule_ic_test(void)
{
     UINT8 ibuf[200],mbuf[20];
  UINT8 len;
  UINT8 *p;
  UINT8 * plen = &len;
  const UINT8 timeout = 0;
  UINT8 count;
  apdu_status  status;
  while(1)
  {
          status = ic_goto_dir();
          olcd_clearsCreen();
          switch(status)
          {
              case APDUS_NO_CARD:
                   olcm_dispprintf(0,1,"  读卡器测试    ");
                   olcm_dispprintf(0,2,"请先插卡，再测试");
                   olcm_dispprintf(0,3,"  谢谢！！      ");
                   count += 10;
                   if(count > timeout)
                      break;
                   else
                      continue;

                   break;
              case APDUS_FAILE:
                   olcm_dispprintf(0,1,"  读卡器测试");
                   olcm_dispprintf(0,2,"读卡失败!!");
                   break;
              case APDUS_DKQERR:
                   olcm_dispprintf(0,1,"  读卡器测试");
                   olcm_dispprintf(0,2,"读卡器错误!!    ");
                   SOEACTION1(DKQ_GREY_ERR,eCurRunState);
                   break;
              case APDUS_SUCCESS:
              {
                  olcm_dispprintf(1,2,"读卡器正常!!  ");
                  break;
                  #if 0
                  len = sizeof(ibuf);
                      memset(ibuf, 0, sizeof(ibuf));
                      if(GetCard_info(IC_INFO_FILENO,ibuf,plen,70) == APDUS_SUCCESS)
                      {
                          len = sizeof(mbuf);
                          memset(mbuf, 0, sizeof(mbuf));

          //                if(GetCard_info(IC_MEM_FILENO,mbuf,plen,10) == APDUS_SUCCESS)
           //               {
                               olcd_clearsCreen();
                               p = ic_operate_info("CDT", ibuf, &len);
                               if(p==NULL)
                               {
                                   olcm_dispprintf(1,2,"读卡失败!!");
                                    break;
                               }
                               else
                               {
                               switch(*(p+len-1))
                                {
                                  case '1':
                                      olcd_dispstr(2,1,"班组卡",6);
                                      p = ic_operate_info("TN", ibuf, &len);
                          //            oprint_printf("class number is%d\r\n", len);
                                      olcm_dispprintf(0,2,"班组:");
                                      olcd_dispstr(2,2,p,len);
                                      break;
                                  case '2':
                                      olcd_dispstr(2,1,"公司卡",6);
                                      break;
                                  case '3':
                                      olcd_dispstr(2,1,"私车卡",6);
                                      break;
                                  case '4':
                                      olcd_dispstr(2,1,"管理卡",6);
                                      break;

                                  default:
                                               break;
                              }
                               }
        //                      olcd_dispstr(0,3,"余额",4);
         //                     olcd_dispstr(2,3,mbuf,strlen(mbuf));
         //                 }

                          p = ic_operate_info("CN", ibuf, plen);
                          if(p==NULL)
                          {
                              olcm_dispprintf(1,2,"读卡失败!!");
                            break;
                          }
                          else
                          {
                          olcd_dispstr(0,4,"卡号",4);
                          if(len > 0)
                             olcd_dispstr(2,4,p,len);}
                      }
                      else
                        olcm_dispprintf(1,2,"读卡失败!!");
                     break;
                     #endif
              }
              olcm_dispprintf(1,3,"读卡器正常!!  ");

      }
     osys_getkey(_KEY_NULL_, 300);
     break;
  }

#if 0
    UINT8 buf[150];
    memset(buf, 0, sizeof(buf));
   // sprintf(buf, "%s","CN:10000000001;TN:F0Q777;BCD:2015-10-10;BCAVD:2016-01-01;COUNT:4;CP:20.00;CDT:1;ML:10000.0000;GL:1000.0000;TN:100;" );
    sprintf(buf, "%s", "CN:1000000002;BCD:2015-10-10;BCAVD:2016-01-01;CONT:40000004;CP:20.00;CDT:40000001;ML:10.0000000;GL:1000.0000;TN:003;");
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"IC卡测试");
    olcm_dispprintf(1,2,"正在充值中...");
    oprint_printf("lenght is %d\r\n", strlen(buf));
    oprint_printf("info is %s\r\n", buf);
    ic_card_put_info(buf, strlen(buf));
    if(ic_card_put_money(9999))
        oprint_printf("Set money success\r\n");
    memcpy(buf, "123456", 6);
    if(ic_card_put_password(buf, 6))
    {
        oprint_printf("Set password success\r\n");
    }
    //ic_card_put_status(CARDS_GREY);
    ic_card_put_status(CARDS_NORMAL);
    ic_card_get_status();
    //olcm_dispprintf(0,1,"ic");
    olcm_dispprintf(1,2,"充值已完成   ");
#endif
    osys_getkey(_KEY_NULL_, 300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
    ///////////////////////////////////////////////////////
  /*  olcd_clearsCreen();
    olcm_dispprintf(2,1,"IC卡测试");
    if(machine_has_card()==TRUE)
     olcm_dispprintf(0,2,"已检测到卡！");
   else
     olcm_dispprintf(0,2,"未检测到卡！");
     osys_getkey(_KEY_NULL_, 300);
     eVirtualKey = _KEY_VIRTUAL_EV_;  */
   /*
    memset(buf, 0, sizeof(buf));
   // sprintf(buf, "%s","CN:10000000001;TN:F0Q777;BCD:2015-10-10;BCAVD:2016-01-01;COUNT:4;CP:20.00;CDT:1;ML:10000.0000;GL:1000.0000;TN:100;" );
    sprintf(buf, "%s", "CN:1000000002;BCD:2015-10-10;BCAVD:2016-01-01;CONT:40000004;CP:20.00;CDT:40000001;ML:10.0000000;GL:1000.0000;TN:003;");
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"IC卡测试");
    olcm_dispprintf(1,2,"正在充值中...");
    oprint_printf("lenght is %d\r\n", strlen(buf));
    oprint_printf("info is %s\r\n", buf);
    ic_card_put_info(buf, strlen(buf));
    if(ic_card_put_money(999.99))
        oprint_printf("Set money success\r\n");
    memcpy(buf, "123456", 6);
    if(ic_card_put_password(buf, 6))
    {
        oprint_printf("Set password success\r\n");
    }
    //ic_card_put_status(CARDS_GREY);
    ic_card_put_status(CARDS_NORMAL);
    ic_card_get_status();
    //olcm_dispprintf(0,1,"ic");
    olcm_dispprintf(1,2,"充值已完成   ");

    osys_getkey(_KEY_NULL_, 300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
    */
}
float Get_pr(UINT8 n)
{
    float price_x;
       switch (n)
    {
     case 1:price_x=PRICE;
            break;
     case 2:price_x=PRICE2;
            break;
     case 3:price_x=PRICE3;
            break;
     case 4:price_x=PRICE4;
            break;
     case 5:price_x=PRICE5;
            break;
     case 6:price_x=PRICE6;
            break;
     case 7:price_x=PRICE7;
            break;
     case 8:price_x=PRICE8;
            break;
     case 9:price_x=PRICE9;
            break;
     case 10:price_x=PRICE10;
            break;
     default:
            price_x=PRICE;
            break;
    }
      return price_x;
}
void Get_Car_Info()
{
  UINT8 ibuf[200],mbuf[20];
  UINT8 pass[6],passbuf[6],len1,len2,passy[10],bj;//rg170607 插卡先验证密码
  UINT8 jy[20],qy[20];
  UINT8 jxy[20],qxy[20],*zl;//151118
  UINT8 len,men[20];
  UINT8 *p,dj,i,qx[4],zk[2],cbh[16],gph[16],pjyxq[4];//151118
  UINT8 * plen = &len;
  const UINT8 timeout = 0;
  UINT8 count,xflx;
  float ZK;
  apdu_status  status;
  UINT8 rdkey;
  INT32 kyint;//rg170717
  float kyfloat;//rg170717
  UINT8 carzl,*yp;//rg170717
UINT8 infoxs[][8]={
"班组卡",
"公司卡",
"私车卡",
"公司子",
"公司母卡",
};
//len2=6;//rg170607 插卡先验证密码
memset(cbh,0,16);
memset(gph,0,16);
memset(pjyxq,0,4);
memset(passy,0x0,10);//rg170607 插卡先验证密码
memset(passy,0x30,6);//rg170607 插卡先验证密码
  if((_b_have_card==FALSE)&& (_b_have_cont==0))
 {
     oui_main_ui();
     _b_have_cont=1;
     return;
 }
if((_b_have_card)&&(_b_cz_card==FALSE))
  {
       _b_cz_card=TRUE;
       _b_have_cont=0;
        status = ic_goto_dir();
          olcd_clearsCreen();
          switch(status)
          {
              case APDUS_NO_CARD:
		        olcm_dispprintf(0,1,"  卡信息查询    ");
                                   olcm_dispprintf(0,2,"请先插卡，再查询");
                                   olcm_dispprintf(0,3,"  谢谢！！      ");
                   count += 10;

                   break;
              case APDUS_FAILE:
			 olcm_dispprintf(0,1,"  卡信息查询");
                   olcm_dispprintf(0,2,"读卡失败!!");
                   break;
              case APDUS_DKQERR:
		olcm_dispprintf(0,1,"  卡信息查询");
                   olcm_dispprintf(0,2,"读卡器错误!!    ");
                        SOEACTION1(DKQ_GREY_ERR,eCurRunState);
                   break;
              case APDUS_SUCCESS:
              {
//***************************//rg170607 插卡先验证密码********************************************************//
#if 1
                      len = sizeof(ibuf);
                      memset(ibuf, 0, sizeof(ibuf));
		      if(GetCard_info(IC_INFO_FILENO,ibuf,plen,70) == APDUS_SUCCESS)
                      {
                          len = sizeof(mbuf);
                          memset(mbuf, 0, sizeof(mbuf));
			p = ic_operate_info("CDT", ibuf, &len);
			if (p == NULL) {
				{
						olcm_dispprintf(0, 2, "    读卡错误  ");
					break;
				}

			} else {
				//去除管理卡
				if ((*(p + len - 1) == '1') || (*(p + len - 1) == '2') || (*(p + len - 1) == '3')|| (*(p + len - 1) == '5')) {
					if (SCS == 1)
						SCS = 0;
					else {
						memset(passbuf, 0, sizeof(passbuf));
						//       ic_card_get_password(passbuf,&len2);//获得卡密码
						len2=6;
						if (GetCard_info(IC_PAS_FILENO, passbuf, &len2, IC_WRITE_LEN) != APDUS_SUCCESS) {
							olcm_dispprintf(0, 2, "读卡密码失败  ");
							_b_cz_card=TRUE;
							oui_main_ui();
							break;
		//					return;
						}
						bj=strcmp(passy, passbuf);
						if(bj != 0)
						{
            						olcd_clearsCreen();
							olcm_dispprintf(0, 1, "  --密码验证--  ");
							olcm_dispprintf(0, 2, "请输卡密码  ");
							olcm_dispprintf(0, 3, "密码:  ");
						memset(pass, 0, sizeof(pass));
						if (okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0) { //密码在插入卡时已经获得
							if (len2 != len1) {
									olcd_clearsCreen();
										olcm_dispprintf(1, 1, "密码错误");
										olcm_dispprintf(1, 2, "请重新插卡");
									osys_getkey(_KEY_NULL_, 320);
									_b_cz_card=TRUE;
									oui_main_ui();
									break;
									//return;
							} else if (memcmp(pass, passbuf,len1)) {
								olcd_clearsCreen();
									olcm_dispprintf(1, 1, "密码错误");
									olcm_dispprintf(1, 2, "请重新插卡");
								osys_getkey(_KEY_NULL_, 320);
								_b_cz_card=TRUE;
								oui_main_ui();
								break;
							}
						} else
						{	_b_cz_card=TRUE;
							oui_main_ui();
							break;
								}
					}
					}	
				}
			}
		      }
		      else
		      {
                                olcm_dispprintf(0,2,"    读卡错误  ");
		      }
#endif
//***************************//rg170607 插卡先验证密码 end********************************************************//       

                                    b_mainui =FALSE;
                                    
                                    len = sizeof(qy);
                        memset(qy,0,20);
                        memset(qxy,0,20);
                        if(GetCard_info(IC_GAS_FILENO,qy,plen,10) == APDUS_SUCCESS)
                        {
                        }
                        zl=ic_conv_un_lj(qy);//150824
                        memcpy(qxy,zl,10);//150824
                        len = sizeof(jy);
                        memset(jy,0,20);
                        memset(jxy,0,20);
                        if(GetCard_info(IC_MEM_FILENO,jy,plen,10) == APDUS_SUCCESS)
                        {
                        }
                        zl=ic_conv_un_lj(jy);//150824
                        memcpy(jxy,zl,10);//150824
                             len = sizeof(ibuf);
                      memset(ibuf, 0, sizeof(ibuf));
                      if(GetCard_info(IC_INFO_FILENO,ibuf,plen,70) == APDUS_SUCCESS)
                      {
                          len = sizeof(mbuf);
                          memset(mbuf, 0, sizeof(mbuf));
                          p = ic_operate_info("PT", ibuf, &len);
                               if(p==NULL)
                               {

                               }
                               else
                               {
                                     memset(men,0,4);
                                     memcpy(men,p,len);
                                     dj = (UINT8)atoi(men);
                               }
			 
                             p = ic_operate_info("DR",ibuf, &len);
                               if(p==NULL)
                               {
                                 }
                               else
                               {
                                  memset(men,0,4);
                                memcpy(men,p,len);
                                ZK=(float)atof(men);
                                }
                                         p = ic_operate_info("VD",ibuf, &len);
                              if(p==NULL)
                               {
                                 }
                              else
                              {
                                       memset(men,0,8);
                                       memcpy(men,p,len);
                                       for(i=0;i<4;i++)
                                       {
                                       qx[i]=((men[2*i]-0x30)<<4)+(men[2*i+1]-0x30);
                                       }
                              }
                                      p = ic_operate_info("CONT",ibuf, &len);
                                if(p==NULL)
                                {
                                }
                                else
                                {
                                xflx = card_get_cstype(p, len);
                                }
                                #if 1//150813
                                p = ic_operate_info("CBH",ibuf, &len);//车牌号
                                if(p==NULL)
                                {
                                }
                                else
                                {

                                memcpy(cbh,p,len);
                                }
                                p = ic_operate_info("GP",ibuf, &len);//钢瓶号
                                if(p==NULL)
                                {
                                }
                                else
                                {
                                memcpy(gph,p,len);
                                }
                                p = ic_operate_info("BCAVD",ibuf, &len);//钢瓶检验有效日期
                                if(p==NULL)
                                {
                                }
                                else
                                {
                                memset(men,0,10);
                                memcpy(men,p,len);

                                for(i=0;i<2;i++)
                                {
                                pjyxq[i]=((men[2*i]-0x30)<<4)+(men[2*i+1]-0x30);
                                }
                                pjyxq[2]=((men[5]-0x30)<<4)+(men[6]-0x30);
                                pjyxq[3]=((men[8]-0x30)<<4)+(men[9]-0x30);
                                }
                                #endif   
                             p = ic_operate_info("CDT", ibuf, &len);
                               if(p==NULL)
                               {
                                     olcm_dispprintf(0,2,"    读卡错误  ");
                                  break;
                               }
                               else
                               {
                           //    switch(*(p+len-1))
      //                          {
                           //      case '1':
					if(memcmp(p,"40000001",len) == 0)
//************************************rg170531无卡加气*******************************************************************//					 
					{
					 p = ic_operate_info("CN",ibuf, &len);//rg170531无卡加气
					if(p==NULL)//rg170531无卡加气
					  {
					       }
					else//rg170531无卡加气
					{
						 if(SP == 1)//rg170531无卡加气
						 {
							 memset(cure_JQ_card, 0, sizeof(cure_JQ_card));//rg170531无卡加气
						 memcpy(cure_JQ_card, p, len);//rg170531无卡加气
						 SP=0;//rg170531无卡加气
						 olcd_clearsCreen();//rg170531无卡加气
						 olcm_dispprintf(0,1,"卡号：");//rg170531无卡加气
						 olcd_dispstr(3,1,cure_JQ_card,strlen(cure_JQ_card));//rg170531无卡加气
						olcm_dispprintf(0,2,"本机已解锁");//rg170531无卡加气
						delay_ms(1000);//rg170531无卡加气
						 }
					}
					 
					
//***************************rg170531无卡加气  END****************************************************************************//					 
                                         memcpy(cure_yz_card, p, sizeof(cure_yz_card));
					 car_disp(dj,1,jxy,qxy,ZK,qx[0],qx[1],qx[2],qx[3],xflx,cbh,pjyxq);//150824
       //                                 break;
					}
                 //                       case '2':
					else if(memcmp(p,"40000002",len) == 0){
						 p = ic_operate_info("CN",ibuf, &len);//rg170531无卡加气
					if(p==NULL)//rg170621  插卡先输密码
					  {
					       }
					else//rg170621  插卡先输密码
					{
					memset(cure_yz_card, 0, sizeof(cure_JQ_card));//rg170621  插卡先输密码
					memcpy(cure_yz_card, p, len);//rg170621  插卡先输密码
					}
                                        car_disp(dj,2,jxy,qxy,ZK,qx[0],qx[1],qx[2],qx[3],xflx,cbh,pjyxq);//150824
                      //                  break;
					}
                     //                   case '3':
					else if(memcmp(p,"40000003",len) == 0){
						 p = ic_operate_info("CN",ibuf, &len);//rg170531无卡加气
					if(p==NULL)//rg170621  插卡先输密码
					  {
					       }
					else//rg170621  插卡先输密码
					{
					memset(cure_yz_card, 0, sizeof(cure_JQ_card));//rg170621  插卡先输密码
					memcpy(cure_yz_card, p, len);//rg170621  插卡先输密码
					}
                                        car_disp(dj,3,jxy,qxy,ZK,qx[0],qx[1],qx[2],qx[3],xflx,cbh,pjyxq);//150824
               //                         break;
					}
                        //          case '4':
					else  if(memcmp(p,"40000024",len) == 0){
					       olcd_clearsCreen();
					      memset(cure_yz_card,0x88,10);//rg170621  插卡先输密码
					       olcd_dispstr(2,1,"管理卡",6);
                                      olcm_dispprintf(0,2,"权限：设置");
                                      olcm_dispprintf(0,4,"按设置键进行设置");
                      //                break;
					  }
					//rg170717
					else if(memcmp(p,"40000005",len) == 0){
					       p = ic_operate_info("CN",ibuf, &len);//rg170531无卡加气
					if(p==NULL)//rg170621  插卡先输密码
					  {
					       }
					else//rg170621  插卡先输密码
					{
						memset(jxy,0x00,20);
						memset(qxy,0x00,20);
						jxy[0]=0x30;
						qxy[0]=0x30;
					memset(cure_yz_card, 0, sizeof(cure_JQ_card));
					memcpy(cure_yz_card, p, len);//rg170621  插卡先输密码
					car_disp(dj,4,jxy,qxy,ZK,qx[0],qx[1],qx[2],qx[3],xflx,cbh,pjyxq);
	//					if(_CARD_TYPE == CARDT_SMALL)//RG170717
//			{
			//向后台要最大加气金额	
#if 0
			      if(Get_ZiCard_info(CN,&carzl,&kyint,&kyfloat)==TRUE)
			      {
				     yp=inttoa(kyint);
					memset(jxy,0x00,20);
					memcpy(jxy,yp,10);
					memset(qxy,0x00,20);
					memset(cure_yz_card, 0, sizeof(cure_JQ_card));
					memcpy(cure_yz_card, p, len);//rg170621  插卡先输密码
					car_disp(dj,2,jxy,qxy,ZK,qx[0],qx[1],qx[2],qx[3],xflx,cbh,pjyxq);
			      }
			      else
			      {
				   olcd_clearsCreen();
                            olcm_dispprintf(1, 2, "无法获取卡金额    ");
                            olcm_dispprintf(1, 3, "无法加气      ");
			      }
#endif
//			}
			}
                                        
					  }
					else if(memcmp(p,"40000055",len) == 0){
					       olcd_clearsCreen();
					      memset(cure_yz_card,0x88,10);//rg170621  插卡先输密码
					       olcm_dispprintf(2,1,"公司母卡");
                                      olcm_dispprintf(0,2,"权限：充值");
                                      olcm_dispprintf(0,4,"仅限后台使用");
                      //                break;
					  }
					
  //                                default:
    //                                           break;
    //                          }
                               }
                      }
                      else
                      {
				olcm_dispprintf(0,2,"    读卡错误  ");
                        }

                     _b_cz_card=TRUE;
                     break;

              }
      }
  }
      return;
}
#if 0
int external_authentication(unsigned char secret, unsigned char *data, int datalen)
{
	unsigned char sw1,sw2;
	int len;
        apdupack.cla=0x00;
        apdupack.ins=EXTERN_AUTH;
        apdupack.p1=0x00;
        apdupack.p2=secret;
        apdupack.p3=0x08;
	if(apdu_pack(apdupack, 0x8, data)<0){
		return -1;
	}
	if(len=ic_card_adpu_reponse(&sw1, &sw2, NULL)<0)
        {
            return -1;
        }

	if(sw1 != APDU_SUCCESS) {
		return -1;
	}

	return 0;
}

int internal_authentication(unsigned char kn, unsigned char *data,
		int datalen)
{

	unsigned char sw1,sw2;
	int len;
    apdupack.cla=0x00;
    apdupack.ins=INTERN_AUTH;
    apdupack.p1=0x00;
    apdupack.p2=kn;
    apdupack.p3=datalen;
	if(apdu_pack(apdupack, datalen, data)<0){
		return -1;
	}
	if(len=ic_card_adpu_reponse(&sw1, &sw2, NULL)<0)
        {
            return -1;
        }

	if(sw1 != APDU_SUCCESS) {
		return -1;
	}
	return len;
}
#endif
#if 0
int card_getchal(unsigned char *chal)
{
	unsigned char sw1, sw2;
        delay_ms(20);
        apdupack.cla=0x00;
        apdupack.ins=0x84;
        apdupack.p1=0x00;
        apdupack.p2=0x00;
        apdupack.p3=0x04;
        apdupack.pack_len = 0x0005;
       if(alpar_send(apdupack.pack_len+2, (UINT8 *)&apdupack.pack_len) == apdupack.pack_len+2)
       {
        if(ic_card_adpu_reponse(&sw1, &sw2)>0)
            return 0;
       }
           return -1;
}

int gemcard_getbin(unsigned char *chal)
{
	unsigned char sw1, sw2;
    apdupack.cla = 0x00;
    apdupack.ins = 0xb2;
    apdupack.p1 = 0x00;
    apdupack.p2 = 0x10;
    apdupack.p3 = 0x30;
    apdupack.pack_len = 0x0005;
    alpar_send(apdupack.pack_len+2,(UINT8 *)&apdupack.pack_len);
    if(ic_card_adpu_reponse(&sw1, &sw2)<0)
       return -1;
    return 0;
}

int card_verify(UINT8 scn, char *pin, int pinlen)
{
	unsigned char sw1,sw2;
        delay_ms(20);
        apdupack.cla = 0x00;
        apdupack.ins = 0x20;
        apdupack.p1 = 0x00;
        apdupack.p2 = scn&0xff;
        apdupack.p3 = pinlen;
        memcpy(apdupack.pdata, pin, pinlen);
        apdupack.pack_len = 0x0005+pinlen;
        alpar_send(apdupack.pack_len+2,(UINT8 *)&apdupack.pack_len);
        if((ic_card_adpu_reponse(&sw1, &sw2)<0) ||((sw1 != APDU_SUCCESS)))
            return -1;
	return 0;
}
#endif

#if 0

int card_readbin_crycks(UINT16 offset)
{
	unsigned char sw1, sw2;
        apdupack.cmd1 = APDU_CMD_M;
        apdupack.cmd2 = APDU_CMD_L;
        apdupack.cla=0x00;
        apdupack.ins=0xb0;
        apdupack.p1=(offset>>8)&0xff;
        apdupack.p2=offset&0xff;
        apdupack.p3=0x00;
        apdupack.pack_len = 5;
        if(alpar_send(apdupack.pack_len+2, (UINT8 *)&apdupack.pack_len) == (apdupack.pack_len+2) )
        {
            if(ic_card_adpu_reponse(&sw1, &sw2))
            {
                if(sw1 == 0x90)
                    return 0;
            }
        }
 	return -1;
}
#endif