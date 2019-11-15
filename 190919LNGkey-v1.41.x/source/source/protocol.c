/* 
 * File:   protocol.c
 * Author: felixluom
 *
 * Created on 2014年2月6日, 下午1:22
 */
#if 0
#include "../includes/global_def.h"
void opotocol_port_init(unsigned long baud)
{
    PORTSetPinsDigitalOut(IOPORT_B, BIT_14);
    PC485_DIR_OUTPUT();

    UARTConfigure(PCTRANS_PORT, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(PCTRANS_PORT, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(PCTRANS_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(PCTRANS_PORT, GetPeripheralClock(), baud);
    UARTEnable(PCTRANS_PORT, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX)); //
    INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);

}


void opotocol_anlysis_pro(void)
{

}

void  Setshiftonce(void)
{
#if 0
     opotocol_SW = 1;
     heareat_flag =0;//不开心跳
     ORD_DATAPA = shift_flag; //设置参数更改
#endif
}

void __ISR(_UART_2_VECTOR, ipl4) IntUart2Handler(void)  //_UART_3A_VECTOR
{
    // Is this an RX interrupt?
        UINT8 n, u2recv = 0;
	if(INTGetFlag(INT_SOURCE_UART_RX(UART2)))
	{
             u2recv = UARTGetDataByte(UART2);
             if(u2recv == 0x0D || u2recv == 0x0A || u2recv>=0x20 )
             {
             }
             INTClearFlag(INT_SOURCE_UART_RX(UART2));
	}
	// don't care about TX interrupt
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) )
	{
            INTClearFlag(INT_SOURCE_UART_TX(UART2));
	}
}
#endif

#include "../includes/global_def.h"
 // extern  struct oparme;


 UINT16 Rec_shiftidnum = 0;
 UINT16 Rec_liushnum = 0;
 UINT16 Rec_setparanum = 0;
 extern  operate_parme oparme;
///////////////////////////////////////////////////////////////
void Configure_protocol (void)
{
   UINT8 i;
   
   for(i=0;i<combufleng;i++)
   {
       gComRF[i] = 0;
   }
   for(i=0;i<cominbufleng;i++)
   {
       gComIn[i] = 0;
   }
    Set_Clockask();//初始设置为时间请求
    gcombufleng = 0;  //发送缓冲区长度为0
    Com_Timeoutnum = 0;//超时次数
    Protocol_tick = 0;//超时滴答
    gComRec_OK = 0; //不接收
    crc_rece = 0;
    Result_card = 0;//卡验证结果初始化为0
}

void opotocol_port_init(unsigned long baud)
{
    PORTSetPinsDigitalOut(IOPORT_B, BIT_14);
    PC485_DIR_OUTPUT();
    UARTConfigure(PCTRANS_PORT, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(PCTRANS_PORT, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(PCTRANS_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(PCTRANS_PORT, GetPeripheralClock(), baud);
    UARTEnable(PCTRANS_PORT, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX)); //
    INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED); //INT_DISABLED
   // INTEnable(INT_SOURCE_UART_TX(PCTRANS_PORT), INT_DISABLED);//INT_DISABLED

}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
 //shift_flag
void  Setshiftonce(void)
{
     opotocol_SW = 1;
     heareat_flag =0;//不开心跳
     ORD_DATAPA = shift_flag; //设置参数更改
     pototime_flag = 0;
}
      ///////////////////
   void SetGasruning(void)
{      opotocol_SW = 1;//开发送
       heareat_flag =0; //关发送心跳
      ORD_DATAPA = lngGasruning_flag;//开发送加气过程
      pototime_flag = 0;

 }
   void  SetGasok(void)
    {   opotocol_SW = 1;//开发送
        heareat_flag =0; //关发送心跳
        ORD_DATAPA = lngstate_flag;//加气完成，状态标志
        pototime_flag = 0;
     } 
  void  Setliushuirec(void)
    {   opotocol_SW = 1;//开发送
        heareat_flag =0; //关发送心跳
        ORD_DATAPA = liushuirec_flag;//开发送加气完成，状态标志
        pototime_flag = 0;
     }
  void  Setcardverify(UINT8 *BUF,UINT8 LEN)
    {   opotocol_SW = 1;//开发送
        heareat_flag =0; //关发送心跳
        ORD_DATAPA = cardverify_flag;//开发送加气完成，状态标志
        pototime_flag = 0;
        if(LEN == 10)
         memcpy(VerCard, BUF, 10);
     }
void  SetParaOnce(void)
{
     opotocol_SW = 1;
     heareat_flag =0;//不开心跳
     ORD_DATAPA = setpara_flag; //设置参数更改
     pototime_flag = 0;
}
void  Set_Clockask(void)
{
     opotocol_SW = 1;
     heareat_flag =0;//不开心跳
     ORD_DATAPA = clockask_flag; //时间同步标识

}
void   set_heareat(void)
{
     opotocol_SW = 1;
     heareat_flag =1;
     ORD_DATAPA = MAX_NULL_FLAG;

}
void protocol_sendstr(UINT8 len, UINT8 *buf)
{
  unsigned int n;
  PC485_DIR_OUTPUT();
  delay_ms(20);
    sys_uart_send_str(PCTRANS_PORT, buf, len);//for (n = 0; n < len; n++) omodbus_l_sendchar(*buf++);
  //while( BusyUART1());//for (n = 0; n < 100; n++) asm("nop"); //1000
   PC485_DIR_INPUT();
  delay_ms(20);//delay_ms(1);//100);
  //asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");//__delay_cycles(5);
  //asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}
void PCset_shift_join(UINT8*strCN, UINT8 lenCN,UINT8*strTN,UINT8 lenTN,UINT8*strOTP,UINT8 lenOTP)
{
   // UINT8 *pinfo;
    UINT8 len;
    UINT8 info[20];
    UINT32  tmp_addr;
    _shift_loginfo    login_recod;

    memset(&login_recod, 0, sizeof(cur_shift_loginfo));
    memset(info, 0, sizeof(info));
 //   ortcc_read_time(info);
   // sprintf(login_recod.shift_op_time,"%02d-%02d %02d:%02d:%02d", strlen(info),info[1],info[2],info[3],info[4],info[5]);
 //   oprint_printf("the log on time is %s\r\n", login_recod.shift_op_time);
    if( b_shift_ok == -1 )
    {
          cur_max_recid   = oset_system_get_max_rec_id();  // max fllow number
           oprint_printf("hello world\r\n");
          cur_sysparas.p_curflow = cur_max_recid;

        //get  the class group  node form card info
        tmp_addr = (cur_max_recid%_SHIFT_SYSINFO_PAGES_)*_SHIFT_SYSINFO_PAGE_SZIE_ +_SHIFT_SYSPARAS_EEP_ADDR_P1;
        o24lcxxx_read_bytes_ex(tmp_addr, (UINT8 *)&cur_rec_sysinfo, sizeof(_rec_shift_info));
        cur_max_shiftid = cur_rec_sysinfo.sig_uid;
         oprint_printf("the log on time is %s, shift id is %d\r\n", login_recod.shift_op_time, cur_max_shiftid );


       //  pinfo = ic_operate_info("TN",global_ic_card_info, &len);//2. group class  number
       //  if(!pinfo) goto error;
         memset(info, 0, sizeof(info));
         memcpy(info, strTN, lenTN);
         login_recod.shift_id = atoi(info);

       //  pinfo = ic_operate_info("CN",global_ic_card_info, &len);// 3. group class card  number
       //  if(!pinfo) goto error;
         memset(login_recod.shift_card, 0, sizeof(login_recod.shift_card));
         memcpy(login_recod.shift_card, strCN, lenCN);

        login_recod.shift_op_type = 1; // 4. signal in type
        login_recod.shift_rec_id = cur_max_shiftid + 1;//5. recoder number
        login_recod.shift_s_mount = cur_rec_sysinfo.gun_total;  ;//6.班开始枪累 = 上班结束枪累
        login_recod.shift_e_mount = cur_rec_sysinfo.gun_total;//7.
        login_recod.recoder_num  = cur_max_recid; //8. max record id
        login_recod.shift_gid = cur_sysparas.p_gid;//cur_rec_sysinfo.g_uid;//9.gun id

        //store class group start working infomation in nand flash
        tmp_addr = (cur_max_shiftid)*SHIFT_NANDFLASH_SIZE + SHIFT_NANDFLASH_S_ADDR;
        onand_wtBuff(tmp_addr, (UINT8*)&login_recod, sizeof(_shift_loginfo));
        cur_max_shiftid += 1;
        cur_rec_sysinfo.sig_uid = cur_max_shiftid;


       //read the class group in  EEPROM_REC_SYSINFO_PAGE_SZIE_
       // tmp_addr = _REC_SYSINFO_EEP_ADDR + _REC_SYSINFO_PAGE_SZIE_ * login_recod.shift_id;
       // o24lcxxx_read_bytes_ex(tmp_addr, (UINT8 *)&cur_rec_shiftinfo, sizeof(_rec_shift_info));
        cur_rec_sysinfo.g_uid = cur_max_recid;
        //set the shift record for using in the class working
        memcpy(&cur_rec_shiftinfo, &cur_rec_sysinfo, sizeof(_rec_shift_info));
        cur_rec_shiftinfo.c_cash = 0;
        cur_rec_shiftinfo.c_money = 0;
        cur_rec_shiftinfo.c_sum = 0;

        //change the currnt class info for use in system
        memcpy(&cur_shift_loginfo, &login_recod, sizeof(_shift_loginfo));
        b_shift_ok = 1;
        Setshiftonce();//必不可少
        eCurRunState = State_MainUI;
        oui_main_ui();

        return;
   }

}



void  send_heareat (void)
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
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '1';//8 //9,10为空格

   memset(s, 0, sizeof(s));
   memset(slen, 0, sizeof(slen));
   sprintf(&gComRF[17], "SN:%08ld", id);
    c = strlen(gComRF);//流水号长度
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);//

   sprintf(slen, "%04d",cur_p_GID); //
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

    opotocol_SW = 0;  //心跳帧需关闭再发送，进行超时等待
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
   pototime_flag = 1;//心跳，必须开超时
   Protocol_tick = 0;//必须，计时滴答置0
   protocol_sendstr(c, gComRF);
  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //清2个接收字节防止误接收


}
void send_liushuirec(void)//每笔加气记录
{////////

   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[11];//数据临时
   //BYTE   ss[11]="0110000005";//数据临时先用统一用这个卡号
   BYTE   slen[4]={0};//数据长度临时
   BYTE   c,m;  //数据长度
   BYTE   d;//数据长度的尺寸
   /////////////以下变量为数据段收集所用
    UINT8  Banhao2;
    UINT8 Kahao4[11];
    float  Qiliang5;
    float  Danjia6;
    float  Jiner7;
    float  ICcar_bef8;
    float  ICcar_af9;
    float  IC_jisuan10;
    float  qianlei_bef11;
    float  qianlei_af12;
    float  yali_bef13;
    float  yali_af14;
    UINT8    Time[6];
    UINT8    CHARTime[20];
    UINT8    CHARTime2[20];
    UINT8  statime15[20];
    UINT8  endtime16[20];
    UINT8  huika17;

   _lcng_rec  tmp_rec;
   UINT32 id ;//= cur_sysinfo.g_uid;
   UINT32 maxid;// = cur_sysinfo.g_uid;
 if(Rec_liushnum == 0)
  id = maxid = cur_max_recid;//cur_sysinfo.g_uid;
  else
 { if(Rec_liushnum<=cur_max_recid)
       { id = Rec_liushnum;}
   else
      { id = maxid = cur_max_recid;}
   Rec_liushnum = 0;
 }
//   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
       onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_cardnum[0], sizeof(struct def_LCNG_Record));//id-1
       memset(s,0,sizeof(s));

        Banhao2 = tmp_rec.rec_shift_id;//2班号
     //   memcpy(Kahao4,ss,11);///卡号10位!!!!!!!!!临时!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        memcpy(s,(UINT8*)&tmp_rec.rec_cardnum[0],10);///卡号10位
          memcpy(Kahao4,s,11);
        //   Kahao4 = (UINT32)atoi(ss);//4卡号
        // memcpy(s,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        Qiliang5 = tmp_rec.rec_lcngnum;//5气量
    //     memcpy(s,(UINT8*)&tmp_rec.rec_lcnprice[0],8);
        Danjia6 =tmp_rec.rec_lcnprice;//6单价
     //    memcpy(s,(UINT8*)&tmp_rec.rec_lcnM[0],10);
        Jiner7 = tmp_rec.rec_lcnM;//7金额
        // memcpy(s,(UINT8*)&tmp_rec.rec_card_preM[0],10);
        ICcar_bef8 = tmp_rec.rec_card_preM;//8加气前金额
    //     memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        ICcar_af9 = tmp_rec.rec_card_endM;//9加气后金额
      //  memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        IC_jisuan10 =tmp_rec.rec_card_endM;//10计算金额=
     //    memcpy(s,(UINT8*)&tmp_rec.rec_sum_start[0],12);
        qianlei_bef11 =tmp_rec.rec_sum_start;//11前枪累
      //  memcpy(s,(UINT8*)&tmp_rec.rec_sum_end[0],12);
        qianlei_af12 = tmp_rec.rec_sum_end;//12后枪累
     //    memcpy(s,(UINT8*)&tmp_rec.rec_begin_Press[0],5);
        yali_bef13 = tmp_rec.rec_begin_Press;//13开始压力
     //   memcpy(s,(UINT8*)&tmp_rec.rec_end_Press[0],5);
        yali_af14 = tmp_rec.rec_end_Press;//14结束压力

         huika17 = tmp_rec.bErrCard; //17是否灰卡
  memcpy(Time,(UINT8*)&tmp_rec.rec_Stime,6);//????????????????????????????????????????????
         CHARTime[0]='2';  CHARTime[1]='0'; CHARTime[2]=(Time[0]/10)+0x30; CHARTime[3]=(Time[0]%10)+0x30; //年
         CHARTime[4]=' ';
         CHARTime[5]=(Time[1]/10)+0x30; CHARTime[6]=(Time[1]%10)+0x30;//月
         CHARTime[7]=' ';
         CHARTime[8]=(Time[2]/10)+0x30; CHARTime[9]=(Time[2]%10)+0x30;//日
         CHARTime[10]=' ';
         CHARTime[11]=Time[3]/10+0x30; CHARTime[12]=Time[3]%10+0x30;//时
         CHARTime[13]=' ';
         CHARTime[14]=Time[4]/10+0x30; CHARTime[15]=Time[4]%10+0x30;//分
         CHARTime[16]=' ';
         CHARTime[17]=Time[5]/10+0x30; CHARTime[18]=Time[5]%10+0x30;//秒
       memcpy(statime15,CHARTime,20);
 memcpy(Time,(UINT8*)&tmp_rec.rec_Etime,6);//????????????????????????????????????????????
         CHARTime2[0]='2';  CHARTime2[1]='0'; CHARTime2[2]=(Time[0]/10)+0x30; CHARTime2[3]=(Time[0]%10)+0x30; //年
         CHARTime2[4]=' ';
         CHARTime2[5]=(Time[1]/10)+0x30; CHARTime2[6]=(Time[1]%10)+0x30;//月
         CHARTime2[7]=' ';
         CHARTime2[8]=(Time[2]/10)+0x30; CHARTime2[9]=(Time[2]%10)+0x30;//日
         CHARTime2[10]=' ';
         CHARTime2[11]=Time[3]/10+0x30; CHARTime2[12]=Time[3]%10+0x30;//时
         CHARTime2[13]=' ';
         CHARTime2[14]=Time[4]/10+0x30; CHARTime2[15]=Time[4]%10+0x30;//分
         CHARTime2[16]=' ';
         CHARTime2[17]=Time[5]/10+0x30; CHARTime2[18]=Time[5]%10+0x30;//秒
         memcpy(endtime16,CHARTime2,20);
    memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '2';//8 //9,10为空格
      //sprintf(&cur_rec.rec_id[0],"%08ld", cur_max_recid);
        //rec_shift_id

  sprintf(&gComRF[17],"SN:%06ld;TN:%04d;CN:%s;GV:%.2f;PR:%.2f;AM:%.2f;EXB:%.2f;CUB:%.2f;SQL:%.2f;EQL:%.2f;SP:%.2f;EP:%.2f;ISL:%02d;ST:%s;ET:%s;",id,Banhao2,Kahao4,Qiliang5,Danjia6,Jiner7,ICcar_bef8,ICcar_af9,qianlei_bef11,qianlei_af12,yali_bef13,yali_af14,huika17,statime15,endtime16);
//  c = strlen(gComRF);//
  //  sprintf(&gComRF[17],"ET:%s;",statime15);
    c = strlen(gComRF);//
   m = c - 17;
   sprintf(s, "%06d",m);
  memcpy(&gComRF[11], s, 6);

  sprintf(slen, "%04d",cur_p_GID);
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//超时计时使能1，
  // Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();


}
/*
void send_liushuirec(void)//每笔加气记录,假数据验证
{////////

   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[11]={0};//数据临时
   BYTE   ss[11]="0110000005";//数据临时
   BYTE   slen[4]={0};//数据长度临时
   BYTE   c,m;  //数据长度
   BYTE   d;//数据长度的尺寸
   /////////////以下变量为数据段收集所用
    UINT8  Banhao2;
    UINT8 Kahao4[11];
    float  Qiliang5;
    float  Danjia6;
    float  Jiner7;
    float  ICcar_bef8;
    float  ICcar_af9;
    float  IC_jisuan10;
    float  qianlei_bef11;
    float  qianlei_af12;
    float  yali_bef13;
    float  yali_af14;
    UINT8  statime15[20]="2014 04 01 08 08 08";
    UINT8  endtime16[20]="2014 04 01 08 08 08";
    UINT8  huika17;

   _lcng_rec  tmp_rec;
   UINT32 id ;//= cur_sysinfo.g_uid;
   UINT32 maxid;// = cur_sysinfo.g_uid;
 if(Rec_liushnum == 0)
  id = maxid = cur_max_recid;//cur_sysinfo.g_uid;
  else
 { if(Rec_liushnum<=cur_max_recid)
       { id = Rec_liushnum;}
   else
      { id = maxid = cur_max_recid;}
   Rec_liushnum = 0;
 }
//   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
       onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_cardnum[0], sizeof(struct def_LCNG_Record));//id-1
       memset(s,0,sizeof(s));

        Banhao2 = tmp_rec.rec_shift_id;//2班号
        memcpy(Kahao4,ss,11);///卡号10位!!!!!!!!!临时!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //  memcpy(s,(UINT8*)&tmp_rec.rec_cardnum[0],10);///卡号10位
     //   Kahao4 = (UINT32)atoi(ss);//4卡号
        // memcpy(s,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        Qiliang5 = tmp_rec.rec_lcngnum;//5气量
    //     memcpy(s,(UINT8*)&tmp_rec.rec_lcnprice[0],8);
        Danjia6 =tmp_rec.rec_lcnprice;//6单价
     //    memcpy(s,(UINT8*)&tmp_rec.rec_lcnM[0],10);
        Jiner7 = tmp_rec.rec_lcnM;//7金额
        // memcpy(s,(UINT8*)&tmp_rec.rec_card_preM[0],10);
        ICcar_bef8 = tmp_rec.rec_card_preM;//8加气前金额
    //     memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        ICcar_af9 = tmp_rec.rec_card_endM;//9加气后金额
      //  memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        IC_jisuan10 =tmp_rec.rec_card_endM;//10计算金额=
     //    memcpy(s,(UINT8*)&tmp_rec.rec_sum_start[0],12);
        qianlei_bef11 =tmp_rec.rec_sum_start;//11前枪累
      //  memcpy(s,(UINT8*)&tmp_rec.rec_sum_end[0],12);
        qianlei_af12 = tmp_rec.rec_sum_end;//12后枪累
     //    memcpy(s,(UINT8*)&tmp_rec.rec_begin_Press[0],5);
        yali_bef13 = tmp_rec.rec_begin_Press;//13开始压力
     //   memcpy(s,(UINT8*)&tmp_rec.rec_end_Press[0],5);
        yali_af14 = tmp_rec.rec_end_Press;//14结束压力
    
    huika17 = tmp_rec.bErrCard; //17是否灰卡
  
    memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '2';//8 //9,10为空格
      //sprintf(&cur_rec.rec_id[0],"%08ld", cur_max_recid);
        //rec_shift_id
 
  sprintf(&gComRF[17],"SN:%06ld;TN:%02d;CN:%s;GV:%.2f;PR:%.2f;AM:%.2f;EXB:%.2f;CUB:%.2f;CAB:%.2f;SQL:%.2f;EQL:%.2f;SP:%.2f;EP:%.2f;ISL:%02d;ST:%s;ET:%s;",id,Banhao2,Kahao4,Qiliang5,Danjia6,Jiner7,ICcar_bef8,ICcar_af9,IC_jisuan10,qianlei_bef11,qianlei_af12,yali_bef13,yali_af14,huika17,statime15,endtime16);
//  c = strlen(gComRF);//
  //  sprintf(&gComRF[17],"ET:%s;",statime15);
    c = strlen(gComRF);//
   m = c - 17;
   sprintf(s, "%06d",m);
  memcpy(&gComRF[11], s, 6);

  sprintf(slen, "%04d",cur_p_GID);
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//超时计时使能1，
  // Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();


} */

    void send_lngstateGasruning(void)//加气中
    {
               static  UINT8 one=1 ;

               UINT16 k,j=0;
               UINT8  i=0;
               BYTE   s[11]={0};//数据临时
               BYTE   slen[4]={0};//数据长度临时
               UINT8   c,m;  //数据长度
               BYTE   d;//数据长度的尺寸
               /////////////以下变量为数据段收集所用

                float  Qiliang5;
                static float  Danjia6;
                float  Jiner7;

                _lcng_rec  tmp_rec;
                 UINT32 id ;//= cur_sysinfo.g_uid;
                 UINT32 maxid;// = cur_sysinfo.g_uid;
                id =maxid = cur_max_shiftid;
            //   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断

    if(one)
    {
     o24lcxxx_read_bytes_ex(_SYSPARAS_EEP_ADDR, (UINT8*)&cur_sysparas.p_Price, sizeof(struct _def_SysParas));
    Danjia6 = cur_sysparas.p_Price;
    one = 0;
    }
    memset(s,0,sizeof(s));
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0
   // gComRF[1] =  '1';//cur_sysparas.p_GID
    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '3';//8 //9,10为空格:%.02f
// sprintf(&gComRF[17],"CS:1;NM:%.02f;PRC:%.02f;TL:%.02f;",JQvolu,Danjia6, JQ_money);
 sprintf(&gComRF[17],"CS:1;NM:%.02f;PRC:%.02f;TL:%.02f",oparme.c_voluent,Danjia6, oparme.c_money);
 c = strlen(gComRF);//流水号长度
   m = c - 17;
   sprintf(s, "%06d",m);
 memcpy(&gComRF[11], s, 6);
     sprintf(slen, "%04d",cur_p_GID);//cur_p_GID
   memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);

    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

   opotocol_SW = 0;    //加气过程中依旧等待应答，关闭发送*****
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//打开计时
  // Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
   set_heareat();//此处为加气过程,也设心跳，等到加气函数处，会自动变为其他

}

    void send_lngstate(void)//加气机状态
    {
   UINT8  cs = 2 ;
   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[11]={0};//数据临时
   BYTE   slen[4]={0};//数据长度临时
   UINT8   c,m;  //数据长度
   BYTE   d;//数据长度的尺寸
   /////////////以下变量为数据段收集所用
    UINT16 liushui1;
    UINT8  Banhao2;
    float  Qiliang5;
    float  Danjia6;
    float  Jiner7;
    UINT8  isshanban;

    _lcng_rec  tmp_rec;
     UINT32 id ;//= cur_sysinfo.g_uid;
     UINT32 maxid;// = cur_sysinfo.g_uid;
    id = maxid = cur_max_recid;//cur_sysinfo.g_uid;
  //  INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
      // delay_ms(20);
       onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_cardnum[0], sizeof(struct def_LCNG_Record));//id-1
        memset(s,0,sizeof(s));
      //  memcpy(s,(UINT8*)&tmp_rec.rec_id[0],8);//++++++++++++++
      //  liushui1 = (UINT16)atoi(s);//流水//+++++++++++++++++
       // memcpy(s,(UINT8*)&tmp_rec.rec_shift_id[0],2);/////
        Banhao2 = tmp_rec.rec_shift_id;//2班号////////
      //  memcpy(s,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        Qiliang5 = tmp_rec.rec_lcngnum;//5气量

       Danjia6 =tmp_rec.rec_lcnprice;//6单价
     //    memcpy(s,(UINT8*)&tmp_rec.rec_lcnM[0],10);
        Jiner7 = tmp_rec.rec_lcnM;//7金额

        isshanban = b_shift_ok; //是否上班
        if(gComIn[8] =='3') //P003发cs：3
           cs =3 ;
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0
   // gComRF[1] =  '1';//cur_sysparas.p_GID
    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '3';//8 //9,10为空格
 sprintf(&gComRF[17],"SN:%06ld;CS:%d;NM:%.2f;PRC:%.02f;TL:%.02f;TP:LNG;CT:%04d;DS:%d",id,cs,Qiliang5,Danjia6,Jiner7,Banhao2,isshanban);
   c = strlen(gComRF);//流水号长度
   m = c - 17;
   sprintf(s, "%06d",m);
 memcpy(&gComRF[11], s, 6);
     sprintf(slen, "%04d",cur_p_GID);//cur_p_GID
   memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);

    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//超时计时使能1，
  // Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    if(gComIn[8] !='3')
     Setliushuirec();//加气完成后发L003，发完L003后发L002
    else
     set_heareat();

}
    void send_shift(void) //班组信息 某班或指定班等小林
     {
           UINT32 id ;//= cur_sysinfo.g_uid;
           UINT32 maxid;// = cur_sysinfo.g_uid;
           UINT16 j=0;
           UINT8  i=0;
           BYTE   s[11];//数据临时
           BYTE   slen[4]={0};//数据临时
           UINT8   c,m;  //数据长度
           BYTE   d;//数据长度的尺寸
     //    BYTE   kk[11]="0110000005";//数据临时
           /////////////以下变量为数据段收集所用
            UINT16 liushui1;
            UINT16  Banhao3;
            UINT8 Kahao2[10];

            float  qianlei_bef11;
            float  qianlei_af12;
            UINT8  isshanban;
            UINT8    Time[6];
            UINT8    CHARTime[20];
          //  UINT8 statime[20]="2014 04 01 09 20 50";
            UINT8 stime[20];
          _shift_loginfo  tmp_rec;
     //   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
        id =maxid = cur_max_shiftid;
         if(Rec_shiftidnum == 0)
          id = maxid = cur_max_shiftid;//cur_sysinfo.g_uid;
          else
         { id = Rec_shiftidnum;
             Rec_shiftidnum = 0;
         }
        onand_rdBuff(SHIFT_NANDFLASH_S_ADDR+(id-1)*SHIFT_NANDFLASH_SIZE, (UINT8*)&tmp_rec.shift_rec_id, sizeof(struct def_LCNG_shift_rec));
        memset(s,0,sizeof(s));
        memset(slen,0,sizeof(slen));
        Banhao3= tmp_rec.shift_id;//2班号
          
        memcpy(s,(UINT8*)&tmp_rec.shift_card[0],10);//
          memcpy(Kahao2,s,11);//
         qianlei_bef11 =tmp_rec.shift_s_mount;//11前枪累------------------------
          qianlei_af12 =tmp_rec.shift_e_mount;//12hou枪累------------------------
         // qianlei_bef11 =888.88;//11前枪累------------------------
         // qianlei_af12 =999.99;//12hou枪累------------------------
         //   isshanban = tmp_rec.shift_op_type; //是否上班//
            isshanban = tmp_rec.shift_op_type; //是否上班//
       memcpy(Time,(UINT8*)&tmp_rec.shift_op_time,6);//????????????????????????????????????????????
         CHARTime[0]='2';  CHARTime[1]='0'; CHARTime[2]=(Time[0]/10)+0x30; CHARTime[3]=(Time[0]%10)+0x30; //年
         CHARTime[4]=' ';
         CHARTime[5]=(Time[1]/10)+0x30; CHARTime[6]=(Time[1]%10)+0x30;//月
         CHARTime[7]=' ';
         CHARTime[8]=(Time[2]/10)+0x30; CHARTime[9]=(Time[2]%10)+0x30;//日
         CHARTime[10]=' ';
         CHARTime[11]=Time[3]/10+0x30; CHARTime[12]=Time[3]%10+0x30;//时
         CHARTime[13]=' ';
         CHARTime[14]=Time[4]/10+0x30; CHARTime[15]=Time[4]%10+0x30;//分
         CHARTime[16]=' ';
         CHARTime[17]=Time[5]/10+0x30; CHARTime[18]=Time[5]%10+0x30;//秒
       memcpy(stime,CHARTime,20);
           memset(gComRF, ' ', 17);//17_>26
            gComRF[0] = '@';//0
           // gComRF[1] =  '1';//cur_sysparas.p_GID
            gComRF[5]  = 'L';//5
            gComRF[6] = '0';
            gComRF[7] = '0';
            gComRF[8] = '4';//8 //9,10为空格

 sprintf(&gComRF[17],"SN:%06d;CN:%s;TN:%04d;SQL:%.2f;EQL:%.2f;OTP:%d;OT:%s;",id,Kahao2,Banhao3,qianlei_bef11,qianlei_af12,isshanban,stime);
 c = strlen(gComRF);//

 m = c - 17;
 sprintf(s, "%06d",m);
 memcpy(&gComRF[11], s, 6);
sprintf(slen, "%04d",cur_p_GID);
 memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//超时计时使能1，
  // Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
   {  opotocol_SW = 1;
      heareat_flag =0;
      ORD_DATAPA = clockask_flag;
    }

 }
 /*   void send_shift(void) //班组信息
     {

           UINT32 id ;//= cur_sysinfo.g_uid;
           UINT32 maxid;// = cur_sysinfo.g_uid;
             ///////////////////////////
           UINT16 k,j=0;
           UINT8  i=0;
           BYTE   s[10]={0};//数据临时
            BYTE   slen[4]={0};//数据临时
           UINT8   c,m;  //数据长度
           BYTE   d;//数据长度的尺寸
           /////////////以下变量为数据段收集所用
            UINT16 liushui1;
            UINT8  Banhao3;
            UINT32 Kahao2;

            float  qianlei_bef11;
            float  qianlei_af12;

            UINT8 statime[15];
            UINT8  isshanban;
          _shift_loginfo  tmp_rec;
     //   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
        id =maxid = cur_max_shiftid;
         if(Rec_shiftidnum == 0)
          id = maxid = cur_max_shiftid;//cur_sysinfo.g_uid;
          else
         { id = Rec_shiftidnum;
             Rec_shiftidnum = 0;
         }

         onand_rdBuff(SHIFT_NANDFLASH_S_ADDR+(id-1)*SHIFT_NANDFLASH_SIZE, (UINT8*)&tmp_rec.shift_rec_id, sizeof(struct def_LCNG_shift_rec));
        memset(s,0,sizeof(s));
        memset(slen,0,sizeof(slen));

        Banhao3= tmp_rec.shift_id;//2班号//-----------------???????

        memcpy(s,(UINT8*)&tmp_rec.shift_card[0],15);//
        Kahao2 = (UINT8)atoi(s);//4卡号//-------------------------------?????

          qianlei_bef11 =tmp_rec.shift_s_mount;//11前枪累------------------------
          qianlei_af12 =tmp_rec.shift_e_mount;//12hou枪累------------------------

        memcpy(statime,(UINT8*)&tmp_rec.shift_op_time[0],15);//

            isshanban = tmp_rec.shift_op_type; //是否上班//

           memset(gComRF, ' ', 17);//17_>26
            gComRF[0] = '@';//0
           // gComRF[1] =  '1';//cur_sysparas.p_GID
            gComRF[5]  = 'L';//5
            gComRF[6] = '0';
            gComRF[7] = '0';
            gComRF[8] = '4';//8 //9,10为空格
            sprintf(&gComRF[17],"SN:%06ld;CN:%15d;TN:%04d;SQL:%.2f;EQL:%.2f;OTP:%d;OT:%s",id,Kahao2,Banhao3,qianlei_bef11,qianlei_af12,isshanban,statime);
           c = strlen(gComRF);//流水号长度
           m = c - 17;
           sprintf(s, "%06d",m);
         memcpy(&gComRF[11], s, 6);//添加了slen
        sprintf(slen, "%04d",cur_p_GID);
          memcpy(&gComRF[1], slen, sizeof(slen));
            j= omodbus_crc16(gComRF,c);

            gComRF[c++] = (j>>8);//校验高
            gComRF[c++] = j;
            gComRF[c++] = '\r';
            gComRF[c++] = '\n';
            gcombufleng = c;       //总长度
            gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
 //  pototime_flag = 1;//超时计时使能1，
 //  Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧，不允许在无心跳帧时PC发送/////
    PC485_DIR_OUTPUT();
    delay_ms(20);
    { opotocol_SW = 1;
      heareat_flag =0;
      ORD_DATAPA = clockask_flag;
    }
 

 }  */

 void send_LNGparas(void)//加气机参数
  {

           UINT32 id ;//= cur_sysinfo.g_uid;
           UINT32 maxid;// = cur_sysinfo.g_uid;
             ///////////////////////////
           UINT16 k,j=0;
           UINT8  i=0;
           BYTE   s[6]={0};//数据临时
           BYTE   slen[4]={0};//数据临时
           UINT8   c,m;  //数据长度
           BYTE   d;//数据长度的尺寸
           /////////////以下变量为数据段收集所用
        float  _p_Price;   /*单价*/
        float  _p_Density; /*密度*/
        float  _p_Factor;  /*修正系数*/

        float  _p_Pzero;   /*压力零点*/
        float  _p_PFactor; /*压力系数*/
        float  _p_Pcur;    /*当前压力*/
        float  _p_Psafety; /*安全压力*/

        float  _p_Ptemp;             /*预冷温度*/
        float  _p_PGain;             /*预冷增益*/
        float  _p_PDelay;            /*预冷延时*/

        float  _p_PDensityup;        /*密度上限*/
        float  _p_PDensitydown;      /*密度下限*/

        float  _p_Paerewait;         /*加气等待时间*/

        float  _p_PumpFqy; /*泵频率*/
        float  _p_EndR;    /*停机流速*/
        float  _p_EndP;    /*停机压力*/
    // INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
        id = maxid = cur_max_shiftid;
      o24lcxxx_read_bytes_ex(_SYSPARAS_EEP_ADDR, (UINT8*)&cur_sysparas.p_Price, sizeof(struct _def_SysParas));

      _p_Price = cur_sysparas.p_Price;
      _p_Density = cur_sysparas.p_Density;
      _p_Ptemp  = cur_sysparas.p_Ptemp;
      _p_PGain = cur_sysparas.p_PGain;
      _p_EndR = cur_sysparas.p_EndR;
      _p_PDelay = cur_sysparas.p_PDelay;
      memset(slen,0,sizeof(slen));
      memset(s,0,sizeof(s));
            memset(gComRF, ' ', 17);//17_>26
            gComRF[0] = '@';//0
         //   gComRF[1] =  '1';//cur_sysparas.p_GID
            gComRF[5]  = 'L';//5
            gComRF[6] = '0';
            gComRF[7] = '0';
            gComRF[8] = '5';//8 //9,10为空格
            sprintf(&gComRF[17],"SN:%06ld;PR:%03.2f;UN:kg;DE:%02.2f;BR:9600;PT:-%02.1f;PG:%02.2f;SF:%02.2f;OPT:%02.2f",id,_p_Price,_p_Density,_p_Ptemp,_p_PGain,_p_EndR,_p_PDelay);
           c = strlen(gComRF);//流水号长度
           m = c - 17;
           sprintf(s, "%06d",m);
           memcpy(&gComRF[11], s, 6);

         sprintf(slen, "%04d",cur_p_GID);
          memcpy(&gComRF[1], slen, sizeof(slen));

           j= omodbus_crc16(gComRF,c);

            gComRF[c++] = (j>>8);//校验高
            gComRF[c++] = j;
            gComRF[c++] = '\r';
            gComRF[c++] = '\n';
            gcombufleng = c;       //总长度
            gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
 //  pototime_flag = 1;//超时计时使能1，
 //  Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
      //////以下为区别心跳帧，不允许在无心跳帧时PC发送/////
    PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();


 }

void send_setpara(void)  //单次修改记录发送
{

   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[10]={0};//数据临时
   BYTE   slen[4]={0};//数据长度临时
   BYTE   c,m;  //数据长度
   BYTE   d;//数据长度的尺寸
   /////////////以下变量为数据段收集所用

    UINT32 Kahao;
    UINT8  Type[3];
    float  Qiliang5;
    float  EXV;
    float  AFV;
   UINT8    Time[6];
   UINT8    CHARTime[20];

   un_paraup  tmp_rec;
   UINT32 id ;//
   UINT32 maxid;//;
 if(Rec_setparanum == 0)
          id = maxid = cur_max_paraid;
          else
         { id = Rec_setparanum;
             Rec_setparanum = 0;
         }

//   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//关中断
       onand_rdBuff(PARA_NANDFLASH_S_ADDR+(id-1)*PARA_LENGTH, (UINT8*)&tmp_rec. para_rec_id, sizeof(struct _def_paraup));//id-1
        memset(s,0,sizeof(s));
        memcpy(s,(UINT8*)&tmp_rec.modi_card[0],10);
        Kahao = (UINT32)atoi(s);//2卡号
        memcpy(Type,(UINT8*)&tmp_rec.no[0],3);

         EXV =tmp_rec.para_float_q;//修改前
         AFV =tmp_rec.para_float_h;//修改前
         memcpy(Time,(UINT8*)&tmp_rec.time,6);//????????????????????????????????????????????
         CHARTime[0]='2';  CHARTime[1]='0'; CHARTime[2]=(Time[0]/10)+0x30; CHARTime[3]=(Time[0]%10)+0x30; //年
         CHARTime[4]=' ';
         CHARTime[5]=(Time[1]/10)+0x30; CHARTime[6]=(Time[1]%10)+0x30;//月
         CHARTime[7]=' ';
         CHARTime[8]=(Time[2]/10)+0x30; CHARTime[9]=(Time[2]%10)+0x30;//日
         CHARTime[10]=' ';
         CHARTime[11]=Time[3]/10+0x30; CHARTime[12]=Time[3]%10+0x30;//时
         CHARTime[13]=' ';
         CHARTime[14]=Time[4]/10+0x30; CHARTime[15]=Time[4]%10+0x30;//分
         CHARTime[16]=' ';
         CHARTime[17]=Time[5]/10+0x30; CHARTime[18]=Time[5]%10+0x30;//秒
    memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '1';
    gComRF[8] = '2';//8 //9,10为空格
 sprintf(&gComRF[17],"SN:%d;CN:%10d;PN:%s;EXV:%.02f;AFV:%.02f;OT:%s ",id,Kahao,Type,EXV,AFV,CHARTime);

  c = strlen(gComRF);//流水号长度
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);

  sprintf(slen, "%04d",cur_p_GID);
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;
  opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//超时计时使能1，
 //  Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
   //////以下为区别心跳帧/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();
  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //清2个接收字节防止误接收




}
 void send_newblacklist(void)  //新增黑名单
  {}
 void send_blacklist(void)  //所有黑名单 一次十条
 {

   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//数据临时
   BYTE   slen[4]={0};//数据长度临时
   UINT8   c,m;  //数据长度
   UINT8   n,nn;  //10条1次，发送次数
   UINT8   P;  //发送状态
   UINT16 id ;
   UINT32 gblack[10] ;

       cur_max_blacklist = Get_max_black_id();
       id = cur_max_blacklist;
       if(id == 0)
       {   PC485_DIR_OUTPUT();
          delay_ms(20);
          set_heareat();
           return;
       }
       memset(gComRF, ' ', 17);//17_>26
                gComRF[0] = '@';//0
               // gComRF[1] =  '1';//
                gComRF[5]  = 'L';//5
                gComRF[6] = '0';
                gComRF[7] = '0';
                gComRF[8] = '6';//8 //9,10为空格
                nn = (UINT8)(id/10)+1;//用于状态字符的选择
                n = nn;  //分几次发送
                P='S';//开始为S
  for(;n>0;n--)
  {
      if( n == nn)
           P='S';//开始为S,传输中为M
      else if(n == 1)
           P='E';//结束为E
      else
           P='M';

         for(i=0;i<10;i++)
         { o24lcxxx_read_bytes_ex(ADDBLACK_SAVE +(id-1)*4, (UINT8*)&gblack[i], 4);

             if(id == 1 )
               {   i+=1;
                   for(;i<10;i++)
                    {gblack[i] = 0;}
                   break;
               }

          id--;
         }

               memset(s, 0, sizeof(s));
              sprintf(&gComRF[17], "SN:%06ld;%c;BL:%8d,%8d,%8d,%8d,%8d,%8d,%8d,%8d,%8d,%8d", id,P,gblack[0],gblack[1],gblack[2],gblack[3],gblack[4],gblack[5],gblack[6],gblack[7],gblack[8],gblack[9]);

               c = strlen(gComRF);//流水号长度
               m = c - 17;
               sprintf(s, "%06d",m);
               memcpy(&gComRF[11], s, 6);

              sprintf(slen, "%04d",cur_p_GID);
             memcpy(&gComRF[1], slen, sizeof(slen));
                j= omodbus_crc16(gComRF,c);
                gComRF[c++] = (j>>8);//校验高
                gComRF[c++] = j;
                gComRF[c++] = '\r';
                gComRF[c++] = '\n';
                gcombufleng = c;       //总长度
                gComRFPos = 0;

                opotocol_SW = 0;
               INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
               delay_ms(100);
             //  pototime_flag = 1;//超时计时使能1，
             //  Protocol_tick = 0;//计时滴答置0
               protocol_sendstr(c, gComRF);

   }
     //////以下为区别心跳帧，不允许在无心跳帧时PC发送/////
             PC485_DIR_OUTPUT();
                delay_ms(20);
                set_heareat();
 }
 void send_cardverify(void)//卡验证
 {
   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//数据临时
   BYTE   slen[4]={0};//数据长度临时
   UINT8   c,m;  //数据长度
   
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0
   // gComRF[1] =  '1';//
    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '7';//8 //9,10为空格

   memset(s, 0, sizeof(s));
   sprintf(&gComRF[17], "SN:12345;CN:%s",VerCard);//
    c = strlen(gComRF);//流水号长度
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);

  sprintf(slen, "%04d",cur_p_GID);
 memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
 //  pototime_flag = 1;//超时计时使能1，
 //  Protocol_tick = 0;//计时滴答置0
   protocol_sendstr(c, gComRF);
      //////以下为区别心跳帧，不允许在无心跳帧时PC发送/////
    PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();

  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //清2个接收字节防止误接收

 }


 void send_clockask(void)  //时间请求
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
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '1';
    gComRF[8] = '1';//8 //9,10为空格

   memset(s, 0, sizeof(s));
   memset(slen, 0, sizeof(slen));
   sprintf(&gComRF[17], "SN:%08ld", id);
    c = strlen(gComRF);//长度
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);//

  sprintf(slen, "%04d",cur_p_GID);
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//校验高
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //总长度
    gComRFPos = 0;

   opotocol_SW = 0; //时间同步帧须关掉发送，等待
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  pototime_flag = 1;//时间同步，必须开
  Protocol_tick = 0;//必须开，
   protocol_sendstr(c, gComRF);


 }
 ///////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////


void PCshift_JoinorExit(INT8 *buf, UINT8 len1,INT8 *buf2,UINT8 len2,INT8 *buf3,UINT8 len3)
{//后台上下班
    switch(buf3[0])
    {  case '1':   if(eCurRunState == State_log_in)//
                  {    b_shift_ok = -1;
                       PCset_shift_join(buf,len1,buf2,len2,buf3,len3);//格外注意卡的动作
                  }
                 else if(eCurRunState == State_MainUI)//
                   {    osel_offwork();//先下班
                        b_shift_ok = -1;
                        PCset_shift_join(buf,len1,buf2,len2,buf3,len3);//后台上班
                   }
                  break;
         case '2':   if(eCurRunState == State_log_in)//
                      {      //不用动作
                      }
                 else if(eCurRunState == State_MainUI)//
                   {    osel_offwork();//先下班
                      eCurRunState = State_log_in;
                      sign_startup();
                      
                   }
                 break;
        default:
                 break;
                 
    }
}
//返回值： *str_OK, strOK_len
void gComIn_get_str(UINT8 start_add, UINT8 *str,UINT8 num,UINT8 *str_OK)
{   UINT8 i, k;
    UINT8 len= 0;
     k = 0;
    for(i=start_add;i<gcomInbufleng;i++ ) //
      { if(num == 2)
          {if(( gComIn[i-2] ==str[0])&&( gComIn[i-1]==str[1])&&( gComIn[i]==':'))//
               {  i++;
                  k =i;
                  break;
                }
         }
        if(num == 3)
              {if(( gComIn[i-3] ==str[0])&&( gComIn[i-2]==str[1])&&( gComIn[i-1]==str[2])&&( gComIn[i]==':'))//卡号
                 {  i++;
                    k =i;
                    break;
                  }
              }
        if(num == 1)
          {if(( gComIn[i-1]==*(str))&&( gComIn[i]==':'))//
               {  i++;
                  k =i;
                  break;
                }
         }

       }

    for(i;i<gcomInbufleng;i++ ) //找到所有数据,及位数位置
      {
        if(gComIn[i]==';')
          {
            if(k !=0)
            { len = i- k;
              memcpy(str_OK, &gComIn[k], len);
              break;
            }

          }

      }

}

BOOL Receive_TIME(void)
{  UINT8 i;
   UINT8 time1[3];
   UINT8 time2[3];
    i = 17;  //时间格式CN：在gComIn[20]以后
                 set_heareat();//收到时间后发心跳
     for(i=17;i<gcomInbufleng;i++ )
       { if(( gComIn[i-2] =='C')&&( gComIn[i-1]=='T')&&( gComIn[i]==':'))
            {         sys_recPCtime[0] =  (gComIn[i+3]-0x30)*10 + (gComIn[i+4]-0x30);  //年
                      sys_recPCtime[1] =  (gComIn[i+6]-0x30)*10 + (gComIn[i+7]-0x30);  //月
                      sys_recPCtime[2] =  (gComIn[i+9]-0x30)*10 + (gComIn[i+10]-0x30);  //日
                      sys_recPCtime[3] =  (gComIn[i+12]-0x30)*10 + (gComIn[i+13]-0x30);  //时
                      sys_recPCtime[4] =  (gComIn[i+15]-0x30)*10 + (gComIn[i+16]-0x30); //分
                      sys_recPCtime[5] =  (gComIn[i+18]-0x30)*10 + (gComIn[i+19]-0x30);  //秒

                      if((sys_recPCtime[1]>12)||(sys_recPCtime[2]>31)||(sys_recPCtime[3]>24)||(sys_recPCtime[4]>59)||(sys_recPCtime[5]>59) )
                      {  return FALSE;}
                      memcpy(time1, &sys_recPCtime[3], 3);
                      memcpy(time2, &sys_recPCtime[0], 3);
                      ortcc_set_time(time1);//时分秒
                      ortcc_set_date(time2);//年月日
                      delay_ms(100);// UINT8 timestr[6] ;
                      ortcc_read_time((UINT8*)&sys_time[0]);
                      olcd_clearsCreen();
                       oui_main_ui();
                      return TRUE;
             }//end of IF ok
        } //end of FOR

}
BOOL Receive_resultCard(void)
{

    UINT8 i, k;
    UINT8 lenSN;
    INT8  strSN[16] = {0};
    UINT8 p = 'P';

   gComIn_get_str(17, &p,1,(INT8*)strSN);
    lenSN = strlen(strSN);
    if(lenSN >1) return FALSE;
    if(strSN[0]=='1')
        return 1;
    else
        return 0;

}
BOOL Receive_Setpara(void) //获得要发送的那条参数命令
{
    UINT8 i, k;
    UINT8 lenSN;
    INT8  strSN[16] = {0};
    UINT8 sn[2]={'S','N'};

   gComIn_get_str(17, (UINT8 *)sn,2,(INT8*)strSN);
    lenSN = strlen(strSN);
    if(lenSN >8) return FALSE;
    Rec_setparanum= atoi(strSN);
   return TRUE;


}
BOOL Receive_LNGparas(void)
{
    UINT8 i, k;
    UINT8 len, vkey = 0;
    INT8  str[10] = {0};
    float tmp_price = 0.0;
     UINT8  pr[2] = {'P','R'};
     gComIn_get_str(17, (UINT8 *)pr,2,(INT8*)str);
     len = strlen(str);
     if(len >6)
        {
         return FALSE;
          }
       tmp_price = atof(str);
      if( TRUE == ostore_paras_wtfloat(P_PRICE_ID, tmp_price))
        {    //目前后台参数修改只能改价格
               cur_sysparas.p_Price = tmp_price;
               cur_price = tmp_price;
               odisp_price(cur_price,TRUE);
            return TRUE;
        }
}


 BOOL Receive_blacklist(void)
 {  //UINT8 i, k;
    UINT8 lenCN,lenCS,lenOP;
    UINT32 kahao;
    UINT8  strCN[10] = {0};
    UINT8  saveCN[8] = {0};
    UINT8  strCS[10] = {0};
    UINT8  strOP[2] = {0};
    UINT8 cn[2]={'C','N'}; //CN:IC卡号
    UINT8 cs[2]={'C','S'}; //CS：IC卡状态  0下班，1上班
    UINT8 op[2]={'O','P'}; //OP：IC卡操作，操作类型：0、删除；1、增加


   gComIn_get_str(17, (UINT8 *)cn,2,(UINT8*)strCN);
   memcpy(saveCN, (UINT8*)(&strCN[2]), 8);//黑名单只处理8位

   kahao = (UINT32)atoi(saveCN);//4卡号
 //   i++;
 //   k = i;
   gComIn_get_str(17, (UINT8 *)cs,2,(UINT8*)strCS);
   lenCS = strlen(strCS);
 //  if(lenCS >2) return FALSE;
 //   i++;
//    k = i;
   gComIn_get_str(17, (UINT8 *)op,2,(UINT8*)strOP);
   lenOP = strlen(strOP);
  // if(lenOP >1) return FALSE;

    delay_ms(500);
 //  PCSet_blacklist((UINT8*)saveCN, 8,(UINT8)strOP[0]);//哈希算法
   if(SaveorDEL_blacklist(kahao,(UINT8)strOP[0]) == TRUE)//保存or删除黑名单记录处理
    return TRUE;
   else
    return FALSE;
 }
 BOOL Receive_befshiftid(void)
 {  UINT8 i, k;
    UINT8 lenSN;
    INT8  strSN[16] = {0};
    UINT8 sn[2]={'S','N'};

   gComIn_get_str(17, (UINT8 *)sn,2,(INT8*)strSN);
    lenSN = strlen(strSN);
    if(lenSN >8) return FALSE;
    Rec_shiftidnum= atoi(strSN);
   return TRUE;
 }
 BOOL Receive_liushuinum(void)/////
 {   UINT8 i, k;
    UINT8 lenSN;
    INT8  strSN[16] = {0};
    UINT8 sn[2]={'S','N'};

   gComIn_get_str(17, (UINT8 *)sn,2,(INT8*)strSN);
    lenSN = strlen(strSN);
    if(lenSN >8) return FALSE;
    Rec_liushnum= atoi(strSN);
   return TRUE;


 }

BOOL Receive_shiftid(void)  //后台交接班
{  
    UINT8 lenCN,lenTN,lenOTP;
    INT8  strCN[16] = {0};
    INT8  strTN[10] = {0};
    INT8  strOTP[4] = {0};
    UINT8 cn[2]={'C','N'};
    UINT8 tn[2]={'T','N'};
    UINT8 otp[3]={'O','T','P'};
    ///////////////////////

    /////////////////////////

   gComIn_get_str(17, (UINT8 *)cn,2,(INT8*)strCN);
    lenCN = strlen(strCN);
    if(lenCN >16) return FALSE;
   
   gComIn_get_str(17, (UINT8 *)tn,2,(INT8*)strTN);
   lenTN = strlen(strTN);
   if(lenTN >4) return FALSE;
   
   gComIn_get_str(17, (UINT8 *)otp,3,(INT8*)strOTP);
   lenOTP = strlen(strOTP);
   if(lenOTP >2) return FALSE;


  // oset_shift_join(); //上班
   PCshift_JoinorExit((INT8*)strCN, lenCN,(INT8*)strTN,lenTN,(INT8*)strOTP,lenOTP); //后台上下班
   return TRUE;
}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////



void opotocol_state(void)
{  ///////////////////////以下是接收处理机制//////////////////

     if (pototime_flag == 0) {  //未要求通信计时
       Protocol_tick = 0; //超时节拍清零
       Com_Timeoutnum = 0;//超时次数清零
       }
     else if(Protocol_tick >= PROTOCOL_TIMEOUT) //超时
        {
                if(ORD_DATAPA == clockask_flag)
                 { opotocol_SW = 1;
                   ORD_DATAPA = clockask_flag;
                   //pototime_flag = 0;
                  }
               else
               {  set_heareat();
                // pototime_flag = 0;//关掉超时
                 }
           Com_Timeoutnum++;
           if(Com_Timeoutnum>PROTOCOL_RESET_NUM)
              {     opotocol_port_init(9600);
                    delay_ms(200);
                    Com_Timeoutnum = 0;
               }

     }
     ///////////////////////gcomInbufleng = 4 + data_index
    if(gComRec_OK == 1)
     {    gComRec_OK = 0;
          opotocol_SW = 1;
          
      /*      crc_rece =omodbus_crc16((unsigned char*)&gComIn[0],gcomInbufleng-2);//gcomInbufleng含校验码，减掉2
         if(gComIn[gcomInbufleng-1] != (unsigned char)(crc_rece &0x00FF) || gComIn[gcomInbufleng-2] !=crc_rece>>8 )
              {  set_heareat();
               }

           else */if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='1'))/////此处注意else++++++++
             {  if( ORD_DATAPA == lngGasruning_flag)
                  { SetGasruning();
                   }

               else set_heareat();
             }
            else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='2'))//可能当前笔，可能某一笔
             {
                if( Receive_liushuinum()!= FALSE)//可能当前笔，可能某一笔
                    {
                     Setliushuirec();
                     }
                else
                     set_heareat();

             }
            else  if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='3'))
             { heareat_flag =0;
               ORD_DATAPA = lngstate_flag;

             }
              else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='4'))//  P004后台交接班
             {    //后台交接班，本机操作后再把当前班组状态L004发回

                  if( Receive_shiftid()!= FALSE)
                    {
                      heareat_flag =0;
                     ORD_DATAPA = shift_flag;

                     }
                  else set_heareat();
             }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='5'))//  P005回复L004，当前班组或某班记录
             {
                if( Receive_befshiftid()!= FALSE)//可能当前班组，可能前某一班組，根据日期要
                    { heareat_flag =0;
                     ORD_DATAPA = shift_flag;

                     }
                else
                    set_heareat();


             }
            else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='6'))//  P006修改参数
             {
                if( Receive_LNGparas()== TRUE) //修改成功重新发送
                {   heareat_flag =0;
                    ORD_DATAPA = LNGparas_flag;
                }
                else
                set_heareat();
             }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='7'))//  P007后台索要参数
             {  heareat_flag =0;
               ORD_DATAPA = LNGparas_flag;
               }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='8'))//  获得后台要操作黑名单列表
             {
                  if( Receive_blacklist()== FALSE)  //失败
                    {  set_heareat();
                     }
                  else
                     set_heareat();


             }
              else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='9'))//  P009后台索要黑名单L006回答
             {
                  heareat_flag =0;
                  ORD_DATAPA = blacklist_flag;//临时发状态调试


               /*    if( Receive_liushuinum()!= FALSE)//可能当前笔，可能某一笔
                    {
                     Setliushuirec();
                     }
                else
                     set_heareat();*/

             }
              else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='1')&&(gComIn[8] =='0'))//  L007的回应
             {
                  if( Receive_resultCard()!= FALSE)//收到后台正确的卡验证信息
                    {
                      Result_card = 1;//已验证该函数
                       Set_Clockask();
                  
                     }
                else
                    Set_Clockask();
                


               }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='1')&&(gComIn[8] =='1'))//  P011 时间
             {   set_heareat();//不能少，不能动
                if(Receive_TIME() == FALSE)
                {   heareat_flag =0;
                    ORD_DATAPA = clockask_flag;
                }

              } //end of P011

            else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='1')&&(gComIn[8] =='2'))//  P012要和后台确定内容
             {
                if( Receive_Setpara()!= FALSE)//可能当前笔，可能某一笔
                    {heareat_flag =0;
                     ORD_DATAPA = setpara_flag;

                     }
                else
                    set_heareat();

             }

     
     } //end of (gComRec_OK == 1)

    //////////////////////以下是发送机制///////////////////////////////////////////
    if(opotocol_SW == 1) //允许安排发送，主不问，从不答
    {    UINT16  i ;
        if(heareat_flag ==1)
        {
            if(heareat_time>=Heareat_Timeout)//10ms*Heareat_Timeout
            {
              send_heareat();//发送心跳
             heareat_time = 0;
             }

        }//END OF 心跳
       else  if(ORD_DATAPA)
       {
              switch (ORD_DATAPA)
                {//每个发送函数里都制定gcombufleng,及gComRFPos = 0；里面对gComRF[]组帧
                case liushuirec_flag:
                    send_liushuirec(); //流水记录
                    break;
                case lngstate_flag:
                    send_lngstate();  //状态L003
                    break;
                case lngGasruning_flag:
                    send_lngstateGasruning();  //加气过程中
                    break;
                case shift_flag:
                    send_shift() ;    //发送班组
                    break;
                case LNGparas_flag:
                    send_LNGparas();  //L005
                    break;
                case newblacklist_flag:
                  //  send_newblacklist();
                       send_lngstate();  //临时发状态方便调试
                    break;
                case blacklist_flag:
                   send_blacklist();

                    break;//
                case cardverify_flag:
                    send_cardverify(); //卡验证
                    break;
                case clockask_flag:
                    send_clockask();
                    break;
                  case setpara_flag:
                    send_setpara();

                    break;

                   default:       //MAX_NULL_FLAG 会跳过来
                    break;
                }

       }//end of 数据发送（非心跳）

      for(i=0;i<=gcomInbufleng;i++)  //发送完成再清接收缓冲区，在发送中可能用的接收缓冲区内容，比如L003
       { gComIn[i] = 0; }
        gcomInbufleng = 0;

    } //end of TX允许



}  //end of







void __ISR(_UART_2_VECTOR, ipl4) IntUart2Handler(void)  //_UART_3A_VECTOR
{
 if(INTGetFlag(INT_SOURCE_UART_RX(PCTRANS_PORT)))
  {
    static UINT8 isHeadRecved = 0; //头部是否收到
    static BYTE head[5] = {0, };  //头部
    static UINT8 data_index = 0;
    UINT8 c  = UARTGetDataByte(PCTRANS_PORT);
  if (!isHeadRecved)  //没有收到"@+枪号"
  {
      head[0] = head[1];
      head[1] = head[2];
      head[2] = head[3];
      head[3] = head[4];
      head[4] = c;

      if ((head[0] == '@') && (head[1] == sq[0]) && (head[2] ==sq[1]) && (head[3] ==sq[2]) && (head[4] ==sq[3]))
      {
        isHeadRecved = 1;
        //配置接收缓冲区头部  头部：‘@’+ 抢号  长度5
        gComIn[0] = head[0];
        gComIn[1] = head[1];
        gComIn[2] = head[2];
        gComIn[3] = head[3];
        gComIn[4] = head[4];

        //清空头部
        head[0] = 0;
        head[1] = 0;
        head[2] = 0;
        head[3] = 0;
        head[4] = 0;
        data_index = 0; //接收指针复位
       }
    }//end of 头部
  else  //收到头部
    {       gComIn[5+ data_index++] = c;
        if (gComIn[5+ data_index-1] == '\r')//命令、长度接收完毕
        {
            gcomInbufleng = 5 + data_index -1;//数据总长度(含校验，不含\R\N) data_index已在\n
            isHeadRecved = 0; //重新搜索头部
            pototime_flag = 0;// 不可少
            gComRec_OK = 1;

            INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);  //关闭接收中断
        }


      }  //end of else
 INTClearFlag(INT_SOURCE_UART_RX(PCTRANS_PORT));
}  //end of RX_INT

if ( INTGetFlag(INT_SOURCE_UART_TX(PCTRANS_PORT)) )
{      INTClearFlag(INT_SOURCE_UART_TX(PCTRANS_PORT));

  }
}


/*------------------------------------------------------------------------------
 * 获得黑名单总数
------------------------------------------------------------------------------*/
UINT16 Get_max_black_id(void)
{
    UINT16     _rec_maxblack;
    UINT16         addr;
    UINT16         maxid;
    addr = ADDBLACK_SAVE_MAX;///////

    o24lcxxx_read_bytes_ex(addr, (UINT8*)&_rec_maxblack, 2);

    maxid = _rec_maxblack ;

    return maxid;
}

BOOL AddRecord(UINT32 black)
 {    UINT16 id,M,N ;
      UINT32 xx;
      UINT8 K = 10;
      cur_max_blacklist += 1;
      id = cur_max_blacklist;
      xx = black;
      delay_ms(200);
     while(K)
      {  K--;
        
         if( 4 == o24lcxxx_write_bytes_ex(ADDBLACK_SAVE+(id-1)*4,(UINT8*)&black,4))
         {   delay_ms(100);
           o24lcxxx_read_bytes_ex(ADDBLACK_SAVE +(id-1)*4, (UINT8*)&xx, 4);
           if(xx ==black)
               {
                 delay_ms(100);
                  o24lcxxx_write_bytes(ADDBLACK_SAVE_MAX,(UINT8*)&id,2 ); //存黑卡最大数
                 delay_ms(500);
                 break;
                }
           delay_ms(10);
         }

     }
}


void DeleteRecord(UINT16 add) //删add位置
 {     UINT8 k;
       UINT16 id ;
       UINT32 blachlist;
       k = 0;
       id = cur_max_blacklist;

    //  memcpy((UINT8*)(ADDBLACK_SAVE+(add-1)*4),(UINT8*)(ADDBLACK_SAVE+add*4),id-add);//
    for(add;add<id;add++)
    {  o24lcxxx_read_bytes_ex(ADDBLACK_SAVE+add*4, (UINT8*)&blachlist,4);//读出来
       delay_ms(200);
       o24lcxxx_write_bytes_ex((ADDBLACK_SAVE+(add-1)*4),(UINT8*)&blachlist,4 ); //写前一个位置去
    }
     // delay_ms(200);
      cur_max_blacklist -= 1;
      id = cur_max_blacklist;
      o24lcxxx_write_bytes(ADDBLACK_SAVE_MAX,(UINT8*)&id,2 ); //存黑卡新最大数
 }

 BOOL SaveorDEL_blacklist(UINT32 kahao,UINT8 buf3) //卡号8位字符
 {     UINT16 id ;
       UINT32 gblack ;
       cur_max_blacklist = Get_max_black_id();
       id = cur_max_blacklist;

      for (;id >= 1;id--)
      {  o24lcxxx_read_bytes_ex(ADDBLACK_SAVE +(id-1)*4, (UINT8*)&gblack, 4);
           if(kahao == (UINT32)gblack) //本机已存该黑卡
           {
             if(buf3 != '0')//要求增加黑卡
               return 1;//   return 1;
             else //要求删除该卡
               {
                 DeleteRecord(id);
                 return 1;
               }

           }
      }
        //下列判断为本机没有该卡号的情况
          if(buf3 != '0')//增加黑卡
          {
            if(TRUE == AddRecord(kahao))
             return 1;
            else
            return 0;

          }
             else //删除黑卡不操作
               {
             return 1;//   return 4;
               }
 }
 // BKDR Hash Function
UINT16 BKDRHash(UINT8 *str,UINT8 len)
{
	UINT8 seed = 3;
	UINT16 hash = 0;
        UINT8  i =3;
	while (i <= len)
	{
		hash = hash * seed +(str[i] - 0x30);
                i++;
	}

	return hash  ;
}
 void PCSet_blacklist(UINT8 *buf, UINT8 len1,UINT8 buf3)
 {
     //  0x0AA0 ~ 0x1A9F   : 黑名单位段映射（4096字节）
    UINT16 hash;//输入卡计算哈希值
    UINT16 addhash;//映射地址
    UINT8 _HASH;//映射地址值
    UINT8 bitx;//映射位
    UINT8 bitD;//映射位状态（值）
    hash = BKDRHash((UINT8 *)buf,len1);//求得哈希值
    addhash = ADDBLACK_MAP + (UINT16)(hash/8);//映射地址
    bitx =  (UINT8)(hash%8);//映射位：0;bit0;   7：bit7
   _HASH = o24lcxxx_read(addhash);
   bitD = (_HASH >>bitx) & 0x1;//获得该位状态
   if(buf3 != '0')//增加该卡为黑
      {
        if (bitD != 0) return  ;//该卡已为黑卡
        else
         { _HASH |= (1 << bitx) ;
           o24lcxxx_write(addhash,_HASH);
         }
      }
    else   //解挂
         {
        if (bitD != 0)//该卡为黑卡,解掉
        {   _HASH  &= (~(1 << bitx)) ;
           o24lcxxx_write(addhash,_HASH);
        }

      }

 }
void Black_DELEALL(void)
{     UINT16 i,idmax;
      UINT8 id[16];
      memset(id,0x00,16);
      for(i=0;i<256;i++)
       {
           o24lcxxx_write_bytes(ADDBLACK_SAVE+(i*16),(UINT8*)&id,16 ); //写0

       }


      delay_ms(200);
      for(i=0;i<256;i++)
      {
          o24lcxxx_write_bytes(ADDBLACK_MAP+(i*16),(UINT8*)&id,16 ); //写0

      }
      delay_ms(200);
      cur_max_blacklist = 0;
      idmax = cur_max_blacklist;
      o24lcxxx_write_bytes(ADDBLACK_SAVE_MAX,(UINT8*)&idmax,2 ); //存黑卡新最大数
}