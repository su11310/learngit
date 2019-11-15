/* 
 * File:   protocol.c
 * Author: felixluom
 *
 * Created on 2014��2��6��, ����1:22
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
     heareat_flag =0;//��������
     ORD_DATAPA = shift_flag; //���ò�������
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
    Set_Clockask();//��ʼ����Ϊʱ������
    gcombufleng = 0;  //���ͻ���������Ϊ0
    Com_Timeoutnum = 0;//��ʱ����
    Protocol_tick = 0;//��ʱ�δ�
    gComRec_OK = 0; //������
    crc_rece = 0;
    Result_card = 0;//����֤�����ʼ��Ϊ0
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
     heareat_flag =0;//��������
     ORD_DATAPA = shift_flag; //���ò�������
     pototime_flag = 0;
}
      ///////////////////
   void SetGasruning(void)
{      opotocol_SW = 1;//������
       heareat_flag =0; //�ط�������
      ORD_DATAPA = lngGasruning_flag;//�����ͼ�������
      pototime_flag = 0;

 }
   void  SetGasok(void)
    {   opotocol_SW = 1;//������
        heareat_flag =0; //�ط�������
        ORD_DATAPA = lngstate_flag;//������ɣ�״̬��־
        pototime_flag = 0;
     } 
  void  Setliushuirec(void)
    {   opotocol_SW = 1;//������
        heareat_flag =0; //�ط�������
        ORD_DATAPA = liushuirec_flag;//�����ͼ�����ɣ�״̬��־
        pototime_flag = 0;
     }
  void  Setcardverify(UINT8 *BUF,UINT8 LEN)
    {   opotocol_SW = 1;//������
        heareat_flag =0; //�ط�������
        ORD_DATAPA = cardverify_flag;//�����ͼ�����ɣ�״̬��־
        pototime_flag = 0;
        if(LEN == 10)
         memcpy(VerCard, BUF, 10);
     }
void  SetParaOnce(void)
{
     opotocol_SW = 1;
     heareat_flag =0;//��������
     ORD_DATAPA = setpara_flag; //���ò�������
     pototime_flag = 0;
}
void  Set_Clockask(void)
{
     opotocol_SW = 1;
     heareat_flag =0;//��������
     ORD_DATAPA = clockask_flag; //ʱ��ͬ����ʶ

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
        login_recod.shift_s_mount = cur_rec_sysinfo.gun_total;  ;//6.�࿪ʼǹ�� = �ϰ����ǹ��
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
        Setshiftonce();//�ز�����
        eCurRunState = State_MainUI;
        oui_main_ui();

        return;
   }

}



void  send_heareat (void)
{
   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   UINT8   c,m;  //���ݳ���
   UINT32 id ;//= cur_sysinfo.g_uid;
   UINT32 maxid;// = cur_sysinfo.g_uid;
   id = maxid = cur_max_recid;//cur_sysinfo.g_uid;
 //  INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '1';//8 //9,10Ϊ�ո�

   memset(s, 0, sizeof(s));
   memset(slen, 0, sizeof(slen));
   sprintf(&gComRF[17], "SN:%08ld", id);
    c = strlen(gComRF);//��ˮ�ų���
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);//

   sprintf(slen, "%04d",cur_p_GID); //
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

    opotocol_SW = 0;  //����֡��ر��ٷ��ͣ����г�ʱ�ȴ�
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
   pototime_flag = 1;//���������뿪��ʱ
   Protocol_tick = 0;//���룬��ʱ�δ���0
   protocol_sendstr(c, gComRF);
  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //��2�������ֽڷ�ֹ�����


}
void send_liushuirec(void)//ÿ�ʼ�����¼
{////////

   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[11];//������ʱ
   //BYTE   ss[11]="0110000005";//������ʱ����ͳһ���������
   BYTE   slen[4]={0};//���ݳ�����ʱ
   BYTE   c,m;  //���ݳ���
   BYTE   d;//���ݳ��ȵĳߴ�
   /////////////���±���Ϊ���ݶ��ռ�����
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
//   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
       onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_cardnum[0], sizeof(struct def_LCNG_Record));//id-1
       memset(s,0,sizeof(s));

        Banhao2 = tmp_rec.rec_shift_id;//2���
     //   memcpy(Kahao4,ss,11);///����10λ!!!!!!!!!��ʱ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        memcpy(s,(UINT8*)&tmp_rec.rec_cardnum[0],10);///����10λ
          memcpy(Kahao4,s,11);
        //   Kahao4 = (UINT32)atoi(ss);//4����
        // memcpy(s,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        Qiliang5 = tmp_rec.rec_lcngnum;//5����
    //     memcpy(s,(UINT8*)&tmp_rec.rec_lcnprice[0],8);
        Danjia6 =tmp_rec.rec_lcnprice;//6����
     //    memcpy(s,(UINT8*)&tmp_rec.rec_lcnM[0],10);
        Jiner7 = tmp_rec.rec_lcnM;//7���
        // memcpy(s,(UINT8*)&tmp_rec.rec_card_preM[0],10);
        ICcar_bef8 = tmp_rec.rec_card_preM;//8����ǰ���
    //     memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        ICcar_af9 = tmp_rec.rec_card_endM;//9��������
      //  memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        IC_jisuan10 =tmp_rec.rec_card_endM;//10������=
     //    memcpy(s,(UINT8*)&tmp_rec.rec_sum_start[0],12);
        qianlei_bef11 =tmp_rec.rec_sum_start;//11ǰǹ��
      //  memcpy(s,(UINT8*)&tmp_rec.rec_sum_end[0],12);
        qianlei_af12 = tmp_rec.rec_sum_end;//12��ǹ��
     //    memcpy(s,(UINT8*)&tmp_rec.rec_begin_Press[0],5);
        yali_bef13 = tmp_rec.rec_begin_Press;//13��ʼѹ��
     //   memcpy(s,(UINT8*)&tmp_rec.rec_end_Press[0],5);
        yali_af14 = tmp_rec.rec_end_Press;//14����ѹ��

         huika17 = tmp_rec.bErrCard; //17�Ƿ�ҿ�
  memcpy(Time,(UINT8*)&tmp_rec.rec_Stime,6);//????????????????????????????????????????????
         CHARTime[0]='2';  CHARTime[1]='0'; CHARTime[2]=(Time[0]/10)+0x30; CHARTime[3]=(Time[0]%10)+0x30; //��
         CHARTime[4]=' ';
         CHARTime[5]=(Time[1]/10)+0x30; CHARTime[6]=(Time[1]%10)+0x30;//��
         CHARTime[7]=' ';
         CHARTime[8]=(Time[2]/10)+0x30; CHARTime[9]=(Time[2]%10)+0x30;//��
         CHARTime[10]=' ';
         CHARTime[11]=Time[3]/10+0x30; CHARTime[12]=Time[3]%10+0x30;//ʱ
         CHARTime[13]=' ';
         CHARTime[14]=Time[4]/10+0x30; CHARTime[15]=Time[4]%10+0x30;//��
         CHARTime[16]=' ';
         CHARTime[17]=Time[5]/10+0x30; CHARTime[18]=Time[5]%10+0x30;//��
       memcpy(statime15,CHARTime,20);
 memcpy(Time,(UINT8*)&tmp_rec.rec_Etime,6);//????????????????????????????????????????????
         CHARTime2[0]='2';  CHARTime2[1]='0'; CHARTime2[2]=(Time[0]/10)+0x30; CHARTime2[3]=(Time[0]%10)+0x30; //��
         CHARTime2[4]=' ';
         CHARTime2[5]=(Time[1]/10)+0x30; CHARTime2[6]=(Time[1]%10)+0x30;//��
         CHARTime2[7]=' ';
         CHARTime2[8]=(Time[2]/10)+0x30; CHARTime2[9]=(Time[2]%10)+0x30;//��
         CHARTime2[10]=' ';
         CHARTime2[11]=Time[3]/10+0x30; CHARTime2[12]=Time[3]%10+0x30;//ʱ
         CHARTime2[13]=' ';
         CHARTime2[14]=Time[4]/10+0x30; CHARTime2[15]=Time[4]%10+0x30;//��
         CHARTime2[16]=' ';
         CHARTime2[17]=Time[5]/10+0x30; CHARTime2[18]=Time[5]%10+0x30;//��
         memcpy(endtime16,CHARTime2,20);
    memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '2';//8 //9,10Ϊ�ո�
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
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//��ʱ��ʱʹ��1��
  // Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();


}
/*
void send_liushuirec(void)//ÿ�ʼ�����¼,��������֤
{////////

   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[11]={0};//������ʱ
   BYTE   ss[11]="0110000005";//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   BYTE   c,m;  //���ݳ���
   BYTE   d;//���ݳ��ȵĳߴ�
   /////////////���±���Ϊ���ݶ��ռ�����
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
//   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
       onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_cardnum[0], sizeof(struct def_LCNG_Record));//id-1
       memset(s,0,sizeof(s));

        Banhao2 = tmp_rec.rec_shift_id;//2���
        memcpy(Kahao4,ss,11);///����10λ!!!!!!!!!��ʱ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //  memcpy(s,(UINT8*)&tmp_rec.rec_cardnum[0],10);///����10λ
     //   Kahao4 = (UINT32)atoi(ss);//4����
        // memcpy(s,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        Qiliang5 = tmp_rec.rec_lcngnum;//5����
    //     memcpy(s,(UINT8*)&tmp_rec.rec_lcnprice[0],8);
        Danjia6 =tmp_rec.rec_lcnprice;//6����
     //    memcpy(s,(UINT8*)&tmp_rec.rec_lcnM[0],10);
        Jiner7 = tmp_rec.rec_lcnM;//7���
        // memcpy(s,(UINT8*)&tmp_rec.rec_card_preM[0],10);
        ICcar_bef8 = tmp_rec.rec_card_preM;//8����ǰ���
    //     memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        ICcar_af9 = tmp_rec.rec_card_endM;//9��������
      //  memcpy(s,(UINT8*)&tmp_rec.rec_card_endM[0],10);
        IC_jisuan10 =tmp_rec.rec_card_endM;//10������=
     //    memcpy(s,(UINT8*)&tmp_rec.rec_sum_start[0],12);
        qianlei_bef11 =tmp_rec.rec_sum_start;//11ǰǹ��
      //  memcpy(s,(UINT8*)&tmp_rec.rec_sum_end[0],12);
        qianlei_af12 = tmp_rec.rec_sum_end;//12��ǹ��
     //    memcpy(s,(UINT8*)&tmp_rec.rec_begin_Press[0],5);
        yali_bef13 = tmp_rec.rec_begin_Press;//13��ʼѹ��
     //   memcpy(s,(UINT8*)&tmp_rec.rec_end_Press[0],5);
        yali_af14 = tmp_rec.rec_end_Press;//14����ѹ��
    
    huika17 = tmp_rec.bErrCard; //17�Ƿ�ҿ�
  
    memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '2';//8 //9,10Ϊ�ո�
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
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//��ʱ��ʱʹ��1��
  // Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();


} */

    void send_lngstateGasruning(void)//������
    {
               static  UINT8 one=1 ;

               UINT16 k,j=0;
               UINT8  i=0;
               BYTE   s[11]={0};//������ʱ
               BYTE   slen[4]={0};//���ݳ�����ʱ
               UINT8   c,m;  //���ݳ���
               BYTE   d;//���ݳ��ȵĳߴ�
               /////////////���±���Ϊ���ݶ��ռ�����

                float  Qiliang5;
                static float  Danjia6;
                float  Jiner7;

                _lcng_rec  tmp_rec;
                 UINT32 id ;//= cur_sysinfo.g_uid;
                 UINT32 maxid;// = cur_sysinfo.g_uid;
                id =maxid = cur_max_shiftid;
            //   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�

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
    gComRF[8] = '3';//8 //9,10Ϊ�ո�:%.02f
// sprintf(&gComRF[17],"CS:1;NM:%.02f;PRC:%.02f;TL:%.02f;",JQvolu,Danjia6, JQ_money);
 sprintf(&gComRF[17],"CS:1;NM:%.02f;PRC:%.02f;TL:%.02f",oparme.c_voluent,Danjia6, oparme.c_money);
 c = strlen(gComRF);//��ˮ�ų���
   m = c - 17;
   sprintf(s, "%06d",m);
 memcpy(&gComRF[11], s, 6);
     sprintf(slen, "%04d",cur_p_GID);//cur_p_GID
   memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);

    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

   opotocol_SW = 0;    //�������������ɵȴ�Ӧ�𣬹رշ���*****
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//�򿪼�ʱ
  // Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
   set_heareat();//�˴�Ϊ��������,Ҳ���������ȵ����������������Զ���Ϊ����

}

    void send_lngstate(void)//������״̬
    {
   UINT8  cs = 2 ;
   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[11]={0};//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   UINT8   c,m;  //���ݳ���
   BYTE   d;//���ݳ��ȵĳߴ�
   /////////////���±���Ϊ���ݶ��ռ�����
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
  //  INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
      // delay_ms(20);
       onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_cardnum[0], sizeof(struct def_LCNG_Record));//id-1
        memset(s,0,sizeof(s));
      //  memcpy(s,(UINT8*)&tmp_rec.rec_id[0],8);//++++++++++++++
      //  liushui1 = (UINT16)atoi(s);//��ˮ//+++++++++++++++++
       // memcpy(s,(UINT8*)&tmp_rec.rec_shift_id[0],2);/////
        Banhao2 = tmp_rec.rec_shift_id;//2���////////
      //  memcpy(s,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        Qiliang5 = tmp_rec.rec_lcngnum;//5����

       Danjia6 =tmp_rec.rec_lcnprice;//6����
     //    memcpy(s,(UINT8*)&tmp_rec.rec_lcnM[0],10);
        Jiner7 = tmp_rec.rec_lcnM;//7���

        isshanban = b_shift_ok; //�Ƿ��ϰ�
        if(gComIn[8] =='3') //P003��cs��3
           cs =3 ;
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0
   // gComRF[1] =  '1';//cur_sysparas.p_GID
    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '3';//8 //9,10Ϊ�ո�
 sprintf(&gComRF[17],"SN:%06ld;CS:%d;NM:%.2f;PRC:%.02f;TL:%.02f;TP:LNG;CT:%04d;DS:%d",id,cs,Qiliang5,Danjia6,Jiner7,Banhao2,isshanban);
   c = strlen(gComRF);//��ˮ�ų���
   m = c - 17;
   sprintf(s, "%06d",m);
 memcpy(&gComRF[11], s, 6);
     sprintf(slen, "%04d",cur_p_GID);//cur_p_GID
   memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);

    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//��ʱ��ʱʹ��1��
  // Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    if(gComIn[8] !='3')
     Setliushuirec();//������ɺ�L003������L003��L002
    else
     set_heareat();

}
    void send_shift(void) //������Ϣ ĳ���ָ�����С��
     {
           UINT32 id ;//= cur_sysinfo.g_uid;
           UINT32 maxid;// = cur_sysinfo.g_uid;
           UINT16 j=0;
           UINT8  i=0;
           BYTE   s[11];//������ʱ
           BYTE   slen[4]={0};//������ʱ
           UINT8   c,m;  //���ݳ���
           BYTE   d;//���ݳ��ȵĳߴ�
     //    BYTE   kk[11]="0110000005";//������ʱ
           /////////////���±���Ϊ���ݶ��ռ�����
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
     //   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
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
        Banhao3= tmp_rec.shift_id;//2���
          
        memcpy(s,(UINT8*)&tmp_rec.shift_card[0],10);//
          memcpy(Kahao2,s,11);//
         qianlei_bef11 =tmp_rec.shift_s_mount;//11ǰǹ��------------------------
          qianlei_af12 =tmp_rec.shift_e_mount;//12houǹ��------------------------
         // qianlei_bef11 =888.88;//11ǰǹ��------------------------
         // qianlei_af12 =999.99;//12houǹ��------------------------
         //   isshanban = tmp_rec.shift_op_type; //�Ƿ��ϰ�//
            isshanban = tmp_rec.shift_op_type; //�Ƿ��ϰ�//
       memcpy(Time,(UINT8*)&tmp_rec.shift_op_time,6);//????????????????????????????????????????????
         CHARTime[0]='2';  CHARTime[1]='0'; CHARTime[2]=(Time[0]/10)+0x30; CHARTime[3]=(Time[0]%10)+0x30; //��
         CHARTime[4]=' ';
         CHARTime[5]=(Time[1]/10)+0x30; CHARTime[6]=(Time[1]%10)+0x30;//��
         CHARTime[7]=' ';
         CHARTime[8]=(Time[2]/10)+0x30; CHARTime[9]=(Time[2]%10)+0x30;//��
         CHARTime[10]=' ';
         CHARTime[11]=Time[3]/10+0x30; CHARTime[12]=Time[3]%10+0x30;//ʱ
         CHARTime[13]=' ';
         CHARTime[14]=Time[4]/10+0x30; CHARTime[15]=Time[4]%10+0x30;//��
         CHARTime[16]=' ';
         CHARTime[17]=Time[5]/10+0x30; CHARTime[18]=Time[5]%10+0x30;//��
       memcpy(stime,CHARTime,20);
           memset(gComRF, ' ', 17);//17_>26
            gComRF[0] = '@';//0
           // gComRF[1] =  '1';//cur_sysparas.p_GID
            gComRF[5]  = 'L';//5
            gComRF[6] = '0';
            gComRF[7] = '0';
            gComRF[8] = '4';//8 //9,10Ϊ�ո�

 sprintf(&gComRF[17],"SN:%06d;CN:%s;TN:%04d;SQL:%.2f;EQL:%.2f;OTP:%d;OT:%s;",id,Kahao2,Banhao3,qianlei_bef11,qianlei_af12,isshanban,stime);
 c = strlen(gComRF);//

 m = c - 17;
 sprintf(s, "%06d",m);
 memcpy(&gComRF[11], s, 6);
sprintf(slen, "%04d",cur_p_GID);
 memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//��ʱ��ʱʹ��1��
  // Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
   {  opotocol_SW = 1;
      heareat_flag =0;
      ORD_DATAPA = clockask_flag;
    }

 }
 /*   void send_shift(void) //������Ϣ
     {

           UINT32 id ;//= cur_sysinfo.g_uid;
           UINT32 maxid;// = cur_sysinfo.g_uid;
             ///////////////////////////
           UINT16 k,j=0;
           UINT8  i=0;
           BYTE   s[10]={0};//������ʱ
            BYTE   slen[4]={0};//������ʱ
           UINT8   c,m;  //���ݳ���
           BYTE   d;//���ݳ��ȵĳߴ�
           /////////////���±���Ϊ���ݶ��ռ�����
            UINT16 liushui1;
            UINT8  Banhao3;
            UINT32 Kahao2;

            float  qianlei_bef11;
            float  qianlei_af12;

            UINT8 statime[15];
            UINT8  isshanban;
          _shift_loginfo  tmp_rec;
     //   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
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

        Banhao3= tmp_rec.shift_id;//2���//-----------------???????

        memcpy(s,(UINT8*)&tmp_rec.shift_card[0],15);//
        Kahao2 = (UINT8)atoi(s);//4����//-------------------------------?????

          qianlei_bef11 =tmp_rec.shift_s_mount;//11ǰǹ��------------------------
          qianlei_af12 =tmp_rec.shift_e_mount;//12houǹ��------------------------

        memcpy(statime,(UINT8*)&tmp_rec.shift_op_time[0],15);//

            isshanban = tmp_rec.shift_op_type; //�Ƿ��ϰ�//

           memset(gComRF, ' ', 17);//17_>26
            gComRF[0] = '@';//0
           // gComRF[1] =  '1';//cur_sysparas.p_GID
            gComRF[5]  = 'L';//5
            gComRF[6] = '0';
            gComRF[7] = '0';
            gComRF[8] = '4';//8 //9,10Ϊ�ո�
            sprintf(&gComRF[17],"SN:%06ld;CN:%15d;TN:%04d;SQL:%.2f;EQL:%.2f;OTP:%d;OT:%s",id,Kahao2,Banhao3,qianlei_bef11,qianlei_af12,isshanban,statime);
           c = strlen(gComRF);//��ˮ�ų���
           m = c - 17;
           sprintf(s, "%06d",m);
         memcpy(&gComRF[11], s, 6);//�����slen
        sprintf(slen, "%04d",cur_p_GID);
          memcpy(&gComRF[1], slen, sizeof(slen));
            j= omodbus_crc16(gComRF,c);

            gComRF[c++] = (j>>8);//У���
            gComRF[c++] = j;
            gComRF[c++] = '\r';
            gComRF[c++] = '\n';
            gcombufleng = c;       //�ܳ���
            gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
 //  pototime_flag = 1;//��ʱ��ʱʹ��1��
 //  Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡����������������֡ʱPC����/////
    PC485_DIR_OUTPUT();
    delay_ms(20);
    { opotocol_SW = 1;
      heareat_flag =0;
      ORD_DATAPA = clockask_flag;
    }
 

 }  */

 void send_LNGparas(void)//����������
  {

           UINT32 id ;//= cur_sysinfo.g_uid;
           UINT32 maxid;// = cur_sysinfo.g_uid;
             ///////////////////////////
           UINT16 k,j=0;
           UINT8  i=0;
           BYTE   s[6]={0};//������ʱ
           BYTE   slen[4]={0};//������ʱ
           UINT8   c,m;  //���ݳ���
           BYTE   d;//���ݳ��ȵĳߴ�
           /////////////���±���Ϊ���ݶ��ռ�����
        float  _p_Price;   /*����*/
        float  _p_Density; /*�ܶ�*/
        float  _p_Factor;  /*����ϵ��*/

        float  _p_Pzero;   /*ѹ�����*/
        float  _p_PFactor; /*ѹ��ϵ��*/
        float  _p_Pcur;    /*��ǰѹ��*/
        float  _p_Psafety; /*��ȫѹ��*/

        float  _p_Ptemp;             /*Ԥ���¶�*/
        float  _p_PGain;             /*Ԥ������*/
        float  _p_PDelay;            /*Ԥ����ʱ*/

        float  _p_PDensityup;        /*�ܶ�����*/
        float  _p_PDensitydown;      /*�ܶ�����*/

        float  _p_Paerewait;         /*�����ȴ�ʱ��*/

        float  _p_PumpFqy; /*��Ƶ��*/
        float  _p_EndR;    /*ͣ������*/
        float  _p_EndP;    /*ͣ��ѹ��*/
    // INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
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
            gComRF[8] = '5';//8 //9,10Ϊ�ո�
            sprintf(&gComRF[17],"SN:%06ld;PR:%03.2f;UN:kg;DE:%02.2f;BR:9600;PT:-%02.1f;PG:%02.2f;SF:%02.2f;OPT:%02.2f",id,_p_Price,_p_Density,_p_Ptemp,_p_PGain,_p_EndR,_p_PDelay);
           c = strlen(gComRF);//��ˮ�ų���
           m = c - 17;
           sprintf(s, "%06d",m);
           memcpy(&gComRF[11], s, 6);

         sprintf(slen, "%04d",cur_p_GID);
          memcpy(&gComRF[1], slen, sizeof(slen));

           j= omodbus_crc16(gComRF,c);

            gComRF[c++] = (j>>8);//У���
            gComRF[c++] = j;
            gComRF[c++] = '\r';
            gComRF[c++] = '\n';
            gcombufleng = c;       //�ܳ���
            gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
 //  pototime_flag = 1;//��ʱ��ʱʹ��1��
 //  Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
      //////����Ϊ��������֡����������������֡ʱPC����/////
    PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();


 }

void send_setpara(void)  //�����޸ļ�¼����
{

   UINT16 k,j=0;
   UINT8  i=0;
   BYTE   s[10]={0};//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   BYTE   c,m;  //���ݳ���
   BYTE   d;//���ݳ��ȵĳߴ�
   /////////////���±���Ϊ���ݶ��ռ�����

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

//   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
       onand_rdBuff(PARA_NANDFLASH_S_ADDR+(id-1)*PARA_LENGTH, (UINT8*)&tmp_rec. para_rec_id, sizeof(struct _def_paraup));//id-1
        memset(s,0,sizeof(s));
        memcpy(s,(UINT8*)&tmp_rec.modi_card[0],10);
        Kahao = (UINT32)atoi(s);//2����
        memcpy(Type,(UINT8*)&tmp_rec.no[0],3);

         EXV =tmp_rec.para_float_q;//�޸�ǰ
         AFV =tmp_rec.para_float_h;//�޸�ǰ
         memcpy(Time,(UINT8*)&tmp_rec.time,6);//????????????????????????????????????????????
         CHARTime[0]='2';  CHARTime[1]='0'; CHARTime[2]=(Time[0]/10)+0x30; CHARTime[3]=(Time[0]%10)+0x30; //��
         CHARTime[4]=' ';
         CHARTime[5]=(Time[1]/10)+0x30; CHARTime[6]=(Time[1]%10)+0x30;//��
         CHARTime[7]=' ';
         CHARTime[8]=(Time[2]/10)+0x30; CHARTime[9]=(Time[2]%10)+0x30;//��
         CHARTime[10]=' ';
         CHARTime[11]=Time[3]/10+0x30; CHARTime[12]=Time[3]%10+0x30;//ʱ
         CHARTime[13]=' ';
         CHARTime[14]=Time[4]/10+0x30; CHARTime[15]=Time[4]%10+0x30;//��
         CHARTime[16]=' ';
         CHARTime[17]=Time[5]/10+0x30; CHARTime[18]=Time[5]%10+0x30;//��
    memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '1';
    gComRF[8] = '2';//8 //9,10Ϊ�ո�
 sprintf(&gComRF[17],"SN:%d;CN:%10d;PN:%s;EXV:%.02f;AFV:%.02f;OT:%s ",id,Kahao,Type,EXV,AFV,CHARTime);

  c = strlen(gComRF);//��ˮ�ų���
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);

  sprintf(slen, "%04d",cur_p_GID);
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;
  opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  // pototime_flag = 1;//��ʱ��ʱʹ��1��
 //  Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
   //////����Ϊ��������֡/////
   PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();
  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //��2�������ֽڷ�ֹ�����




}
 void send_newblacklist(void)  //����������
  {}
 void send_blacklist(void)  //���к����� һ��ʮ��
 {

   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   UINT8   c,m;  //���ݳ���
   UINT8   n,nn;  //10��1�Σ����ʹ���
   UINT8   P;  //����״̬
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
                gComRF[8] = '6';//8 //9,10Ϊ�ո�
                nn = (UINT8)(id/10)+1;//����״̬�ַ���ѡ��
                n = nn;  //�ּ��η���
                P='S';//��ʼΪS
  for(;n>0;n--)
  {
      if( n == nn)
           P='S';//��ʼΪS,������ΪM
      else if(n == 1)
           P='E';//����ΪE
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

               c = strlen(gComRF);//��ˮ�ų���
               m = c - 17;
               sprintf(s, "%06d",m);
               memcpy(&gComRF[11], s, 6);

              sprintf(slen, "%04d",cur_p_GID);
             memcpy(&gComRF[1], slen, sizeof(slen));
                j= omodbus_crc16(gComRF,c);
                gComRF[c++] = (j>>8);//У���
                gComRF[c++] = j;
                gComRF[c++] = '\r';
                gComRF[c++] = '\n';
                gcombufleng = c;       //�ܳ���
                gComRFPos = 0;

                opotocol_SW = 0;
               INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
               delay_ms(100);
             //  pototime_flag = 1;//��ʱ��ʱʹ��1��
             //  Protocol_tick = 0;//��ʱ�δ���0
               protocol_sendstr(c, gComRF);

   }
     //////����Ϊ��������֡����������������֡ʱPC����/////
             PC485_DIR_OUTPUT();
                delay_ms(20);
                set_heareat();
 }
 void send_cardverify(void)//����֤
 {
   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   UINT8   c,m;  //���ݳ���
   
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0
   // gComRF[1] =  '1';//
    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '0';
    gComRF[8] = '7';//8 //9,10Ϊ�ո�

   memset(s, 0, sizeof(s));
   sprintf(&gComRF[17], "SN:12345;CN:%s",VerCard);//
    c = strlen(gComRF);//��ˮ�ų���
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);

  sprintf(slen, "%04d",cur_p_GID);
 memcpy(&gComRF[1], slen, sizeof(slen));
    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

    opotocol_SW = 0;
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
 //  pototime_flag = 1;//��ʱ��ʱʹ��1��
 //  Protocol_tick = 0;//��ʱ�δ���0
   protocol_sendstr(c, gComRF);
      //////����Ϊ��������֡����������������֡ʱPC����/////
    PC485_DIR_OUTPUT();
    delay_ms(20);
    set_heareat();

  //  gComIn[0] = 0;
   // gComIn[1] = 0;	  //��2�������ֽڷ�ֹ�����

 }


 void send_clockask(void)  //ʱ������
 {
   UINT16 j=0;
   UINT8  i=0;
   BYTE   s[6]={0};//������ʱ
   BYTE   slen[4]={0};//���ݳ�����ʱ
   UINT8   c,m;  //���ݳ���
   UINT32 id ;//= cur_sysinfo.g_uid;
   UINT32 maxid;// = cur_sysinfo.g_uid;
   id = maxid = cur_max_recid;//cur_sysinfo.g_uid;
 //  INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);//���ж�
   memset(gComRF, ' ', 17);//17_>26
    gComRF[0] = '@';//0

    gComRF[5]  = 'L';//5
    gComRF[6] = '0';
    gComRF[7] = '1';
    gComRF[8] = '1';//8 //9,10Ϊ�ո�

   memset(s, 0, sizeof(s));
   memset(slen, 0, sizeof(slen));
   sprintf(&gComRF[17], "SN:%08ld", id);
    c = strlen(gComRF);//����
   m = c - 17;
   sprintf(s, "%06d",m);
   memcpy(&gComRF[11], s, 6);//

  sprintf(slen, "%04d",cur_p_GID);
   memcpy(&gComRF[1], slen, sizeof(slen));

    j= omodbus_crc16(gComRF,c);
    gComRF[c++] = (j>>8);//У���
    gComRF[c++] = j;
    gComRF[c++] = '\r';
    gComRF[c++] = '\n';
    gcombufleng = c;       //�ܳ���
    gComRFPos = 0;

   opotocol_SW = 0; //ʱ��ͬ��֡��ص����ͣ��ȴ�
   INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_ENABLED);
   delay_ms(100);
  pototime_flag = 1;//ʱ��ͬ�������뿪
  Protocol_tick = 0;//���뿪��
   protocol_sendstr(c, gComRF);


 }
 ///////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////


void PCshift_JoinorExit(INT8 *buf, UINT8 len1,INT8 *buf2,UINT8 len2,INT8 *buf3,UINT8 len3)
{//��̨���°�
    switch(buf3[0])
    {  case '1':   if(eCurRunState == State_log_in)//
                  {    b_shift_ok = -1;
                       PCset_shift_join(buf,len1,buf2,len2,buf3,len3);//����ע�⿨�Ķ���
                  }
                 else if(eCurRunState == State_MainUI)//
                   {    osel_offwork();//���°�
                        b_shift_ok = -1;
                        PCset_shift_join(buf,len1,buf2,len2,buf3,len3);//��̨�ϰ�
                   }
                  break;
         case '2':   if(eCurRunState == State_log_in)//
                      {      //���ö���
                      }
                 else if(eCurRunState == State_MainUI)//
                   {    osel_offwork();//���°�
                      eCurRunState = State_log_in;
                      sign_startup();
                      
                   }
                 break;
        default:
                 break;
                 
    }
}
//����ֵ�� *str_OK, strOK_len
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
              {if(( gComIn[i-3] ==str[0])&&( gComIn[i-2]==str[1])&&( gComIn[i-1]==str[2])&&( gComIn[i]==':'))//����
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

    for(i;i<gcomInbufleng;i++ ) //�ҵ���������,��λ��λ��
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
    i = 17;  //ʱ���ʽCN����gComIn[20]�Ժ�
                 set_heareat();//�յ�ʱ�������
     for(i=17;i<gcomInbufleng;i++ )
       { if(( gComIn[i-2] =='C')&&( gComIn[i-1]=='T')&&( gComIn[i]==':'))
            {         sys_recPCtime[0] =  (gComIn[i+3]-0x30)*10 + (gComIn[i+4]-0x30);  //��
                      sys_recPCtime[1] =  (gComIn[i+6]-0x30)*10 + (gComIn[i+7]-0x30);  //��
                      sys_recPCtime[2] =  (gComIn[i+9]-0x30)*10 + (gComIn[i+10]-0x30);  //��
                      sys_recPCtime[3] =  (gComIn[i+12]-0x30)*10 + (gComIn[i+13]-0x30);  //ʱ
                      sys_recPCtime[4] =  (gComIn[i+15]-0x30)*10 + (gComIn[i+16]-0x30); //��
                      sys_recPCtime[5] =  (gComIn[i+18]-0x30)*10 + (gComIn[i+19]-0x30);  //��

                      if((sys_recPCtime[1]>12)||(sys_recPCtime[2]>31)||(sys_recPCtime[3]>24)||(sys_recPCtime[4]>59)||(sys_recPCtime[5]>59) )
                      {  return FALSE;}
                      memcpy(time1, &sys_recPCtime[3], 3);
                      memcpy(time2, &sys_recPCtime[0], 3);
                      ortcc_set_time(time1);//ʱ����
                      ortcc_set_date(time2);//������
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
BOOL Receive_Setpara(void) //���Ҫ���͵�������������
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
        {    //Ŀǰ��̨�����޸�ֻ�ܸļ۸�
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
    UINT8 cn[2]={'C','N'}; //CN:IC����
    UINT8 cs[2]={'C','S'}; //CS��IC��״̬  0�°࣬1�ϰ�
    UINT8 op[2]={'O','P'}; //OP��IC���������������ͣ�0��ɾ����1������


   gComIn_get_str(17, (UINT8 *)cn,2,(UINT8*)strCN);
   memcpy(saveCN, (UINT8*)(&strCN[2]), 8);//������ֻ����8λ

   kahao = (UINT32)atoi(saveCN);//4����
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
 //  PCSet_blacklist((UINT8*)saveCN, 8,(UINT8)strOP[0]);//��ϣ�㷨
   if(SaveorDEL_blacklist(kahao,(UINT8)strOP[0]) == TRUE)//����orɾ����������¼����
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

BOOL Receive_shiftid(void)  //��̨���Ӱ�
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


  // oset_shift_join(); //�ϰ�
   PCshift_JoinorExit((INT8*)strCN, lenCN,(INT8*)strTN,lenTN,(INT8*)strOTP,lenOTP); //��̨���°�
   return TRUE;
}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////



void opotocol_state(void)
{  ///////////////////////�����ǽ��մ������//////////////////

     if (pototime_flag == 0) {  //δҪ��ͨ�ż�ʱ
       Protocol_tick = 0; //��ʱ��������
       Com_Timeoutnum = 0;//��ʱ��������
       }
     else if(Protocol_tick >= PROTOCOL_TIMEOUT) //��ʱ
        {
                if(ORD_DATAPA == clockask_flag)
                 { opotocol_SW = 1;
                   ORD_DATAPA = clockask_flag;
                   //pototime_flag = 0;
                  }
               else
               {  set_heareat();
                // pototime_flag = 0;//�ص���ʱ
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
          
      /*      crc_rece =omodbus_crc16((unsigned char*)&gComIn[0],gcomInbufleng-2);//gcomInbufleng��У���룬����2
         if(gComIn[gcomInbufleng-1] != (unsigned char)(crc_rece &0x00FF) || gComIn[gcomInbufleng-2] !=crc_rece>>8 )
              {  set_heareat();
               }

           else */if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='1'))/////�˴�ע��else++++++++
             {  if( ORD_DATAPA == lngGasruning_flag)
                  { SetGasruning();
                   }

               else set_heareat();
             }
            else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='2'))//���ܵ�ǰ�ʣ�����ĳһ��
             {
                if( Receive_liushuinum()!= FALSE)//���ܵ�ǰ�ʣ�����ĳһ��
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
              else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='4'))//  P004��̨���Ӱ�
             {    //��̨���Ӱ࣬�����������ٰѵ�ǰ����״̬L004����

                  if( Receive_shiftid()!= FALSE)
                    {
                      heareat_flag =0;
                     ORD_DATAPA = shift_flag;

                     }
                  else set_heareat();
             }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='5'))//  P005�ظ�L004����ǰ�����ĳ���¼
             {
                if( Receive_befshiftid()!= FALSE)//���ܵ�ǰ���飬����ǰĳһ��M����������Ҫ
                    { heareat_flag =0;
                     ORD_DATAPA = shift_flag;

                     }
                else
                    set_heareat();


             }
            else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='6'))//  P006�޸Ĳ���
             {
                if( Receive_LNGparas()== TRUE) //�޸ĳɹ����·���
                {   heareat_flag =0;
                    ORD_DATAPA = LNGparas_flag;
                }
                else
                set_heareat();
             }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='7'))//  P007��̨��Ҫ����
             {  heareat_flag =0;
               ORD_DATAPA = LNGparas_flag;
               }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='8'))//  ��ú�̨Ҫ�����������б�
             {
                  if( Receive_blacklist()== FALSE)  //ʧ��
                    {  set_heareat();
                     }
                  else
                     set_heareat();


             }
              else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='0')&&(gComIn[8] =='9'))//  P009��̨��Ҫ������L006�ش�
             {
                  heareat_flag =0;
                  ORD_DATAPA = blacklist_flag;//��ʱ��״̬����


               /*    if( Receive_liushuinum()!= FALSE)//���ܵ�ǰ�ʣ�����ĳһ��
                    {
                     Setliushuirec();
                     }
                else
                     set_heareat();*/

             }
              else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='1')&&(gComIn[8] =='0'))//  L007�Ļ�Ӧ
             {
                  if( Receive_resultCard()!= FALSE)//�յ���̨��ȷ�Ŀ���֤��Ϣ
                    {
                      Result_card = 1;//����֤�ú���
                       Set_Clockask();
                  
                     }
                else
                    Set_Clockask();
                


               }
             else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='1')&&(gComIn[8] =='1'))//  P011 ʱ��
             {   set_heareat();//�����٣����ܶ�
                if(Receive_TIME() == FALSE)
                {   heareat_flag =0;
                    ORD_DATAPA = clockask_flag;
                }

              } //end of P011

            else if((gComIn[5] =='P')&&(gComIn[6] =='0')&&(gComIn[7] =='1')&&(gComIn[8] =='2'))//  P012Ҫ�ͺ�̨ȷ������
             {
                if( Receive_Setpara()!= FALSE)//���ܵ�ǰ�ʣ�����ĳһ��
                    {heareat_flag =0;
                     ORD_DATAPA = setpara_flag;

                     }
                else
                    set_heareat();

             }

     
     } //end of (gComRec_OK == 1)

    //////////////////////�����Ƿ��ͻ���///////////////////////////////////////////
    if(opotocol_SW == 1) //�����ŷ��ͣ������ʣ��Ӳ���
    {    UINT16  i ;
        if(heareat_flag ==1)
        {
            if(heareat_time>=Heareat_Timeout)//10ms*Heareat_Timeout
            {
              send_heareat();//��������
             heareat_time = 0;
             }

        }//END OF ����
       else  if(ORD_DATAPA)
       {
              switch (ORD_DATAPA)
                {//ÿ�����ͺ����ﶼ�ƶ�gcombufleng,��gComRFPos = 0�������gComRF[]��֡
                case liushuirec_flag:
                    send_liushuirec(); //��ˮ��¼
                    break;
                case lngstate_flag:
                    send_lngstate();  //״̬L003
                    break;
                case lngGasruning_flag:
                    send_lngstateGasruning();  //����������
                    break;
                case shift_flag:
                    send_shift() ;    //���Ͱ���
                    break;
                case LNGparas_flag:
                    send_LNGparas();  //L005
                    break;
                case newblacklist_flag:
                  //  send_newblacklist();
                       send_lngstate();  //��ʱ��״̬�������
                    break;
                case blacklist_flag:
                   send_blacklist();

                    break;//
                case cardverify_flag:
                    send_cardverify(); //����֤
                    break;
                case clockask_flag:
                    send_clockask();
                    break;
                  case setpara_flag:
                    send_setpara();

                    break;

                   default:       //MAX_NULL_FLAG ��������
                    break;
                }

       }//end of ���ݷ��ͣ���������

      for(i=0;i<=gcomInbufleng;i++)  //�������������ջ��������ڷ����п����õĽ��ջ��������ݣ�����L003
       { gComIn[i] = 0; }
        gcomInbufleng = 0;

    } //end of TX����



}  //end of







void __ISR(_UART_2_VECTOR, ipl4) IntUart2Handler(void)  //_UART_3A_VECTOR
{
 if(INTGetFlag(INT_SOURCE_UART_RX(PCTRANS_PORT)))
  {
    static UINT8 isHeadRecved = 0; //ͷ���Ƿ��յ�
    static BYTE head[5] = {0, };  //ͷ��
    static UINT8 data_index = 0;
    UINT8 c  = UARTGetDataByte(PCTRANS_PORT);
  if (!isHeadRecved)  //û���յ�"@+ǹ��"
  {
      head[0] = head[1];
      head[1] = head[2];
      head[2] = head[3];
      head[3] = head[4];
      head[4] = c;

      if ((head[0] == '@') && (head[1] == sq[0]) && (head[2] ==sq[1]) && (head[3] ==sq[2]) && (head[4] ==sq[3]))
      {
        isHeadRecved = 1;
        //���ý��ջ�����ͷ��  ͷ������@��+ ����  ����5
        gComIn[0] = head[0];
        gComIn[1] = head[1];
        gComIn[2] = head[2];
        gComIn[3] = head[3];
        gComIn[4] = head[4];

        //���ͷ��
        head[0] = 0;
        head[1] = 0;
        head[2] = 0;
        head[3] = 0;
        head[4] = 0;
        data_index = 0; //����ָ�븴λ
       }
    }//end of ͷ��
  else  //�յ�ͷ��
    {       gComIn[5+ data_index++] = c;
        if (gComIn[5+ data_index-1] == '\r')//������Ƚ������
        {
            gcomInbufleng = 5 + data_index -1;//�����ܳ���(��У�飬����\R\N) data_index����\n
            isHeadRecved = 0; //��������ͷ��
            pototime_flag = 0;// ������
            gComRec_OK = 1;

            INTEnable(INT_SOURCE_UART_RX(PCTRANS_PORT), INT_DISABLED);  //�رս����ж�
        }


      }  //end of else
 INTClearFlag(INT_SOURCE_UART_RX(PCTRANS_PORT));
}  //end of RX_INT

if ( INTGetFlag(INT_SOURCE_UART_TX(PCTRANS_PORT)) )
{      INTClearFlag(INT_SOURCE_UART_TX(PCTRANS_PORT));

  }
}


/*------------------------------------------------------------------------------
 * ��ú���������
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
                  o24lcxxx_write_bytes(ADDBLACK_SAVE_MAX,(UINT8*)&id,2 ); //��ڿ������
                 delay_ms(500);
                 break;
                }
           delay_ms(10);
         }

     }
}


void DeleteRecord(UINT16 add) //ɾaddλ��
 {     UINT8 k;
       UINT16 id ;
       UINT32 blachlist;
       k = 0;
       id = cur_max_blacklist;

    //  memcpy((UINT8*)(ADDBLACK_SAVE+(add-1)*4),(UINT8*)(ADDBLACK_SAVE+add*4),id-add);//
    for(add;add<id;add++)
    {  o24lcxxx_read_bytes_ex(ADDBLACK_SAVE+add*4, (UINT8*)&blachlist,4);//������
       delay_ms(200);
       o24lcxxx_write_bytes_ex((ADDBLACK_SAVE+(add-1)*4),(UINT8*)&blachlist,4 ); //дǰһ��λ��ȥ
    }
     // delay_ms(200);
      cur_max_blacklist -= 1;
      id = cur_max_blacklist;
      o24lcxxx_write_bytes(ADDBLACK_SAVE_MAX,(UINT8*)&id,2 ); //��ڿ��������
 }

 BOOL SaveorDEL_blacklist(UINT32 kahao,UINT8 buf3) //����8λ�ַ�
 {     UINT16 id ;
       UINT32 gblack ;
       cur_max_blacklist = Get_max_black_id();
       id = cur_max_blacklist;

      for (;id >= 1;id--)
      {  o24lcxxx_read_bytes_ex(ADDBLACK_SAVE +(id-1)*4, (UINT8*)&gblack, 4);
           if(kahao == (UINT32)gblack) //�����Ѵ�úڿ�
           {
             if(buf3 != '0')//Ҫ�����Ӻڿ�
               return 1;//   return 1;
             else //Ҫ��ɾ���ÿ�
               {
                 DeleteRecord(id);
                 return 1;
               }

           }
      }
        //�����ж�Ϊ����û�иÿ��ŵ����
          if(buf3 != '0')//���Ӻڿ�
          {
            if(TRUE == AddRecord(kahao))
             return 1;
            else
            return 0;

          }
             else //ɾ���ڿ�������
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
     //  0x0AA0 ~ 0x1A9F   : ������λ��ӳ�䣨4096�ֽڣ�
    UINT16 hash;//���뿨�����ϣֵ
    UINT16 addhash;//ӳ���ַ
    UINT8 _HASH;//ӳ���ֵַ
    UINT8 bitx;//ӳ��λ
    UINT8 bitD;//ӳ��λ״̬��ֵ��
    hash = BKDRHash((UINT8 *)buf,len1);//��ù�ϣֵ
    addhash = ADDBLACK_MAP + (UINT16)(hash/8);//ӳ���ַ
    bitx =  (UINT8)(hash%8);//ӳ��λ��0;bit0;   7��bit7
   _HASH = o24lcxxx_read(addhash);
   bitD = (_HASH >>bitx) & 0x1;//��ø�λ״̬
   if(buf3 != '0')//���Ӹÿ�Ϊ��
      {
        if (bitD != 0) return  ;//�ÿ���Ϊ�ڿ�
        else
         { _HASH |= (1 << bitx) ;
           o24lcxxx_write(addhash,_HASH);
         }
      }
    else   //���
         {
        if (bitD != 0)//�ÿ�Ϊ�ڿ�,���
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
           o24lcxxx_write_bytes(ADDBLACK_SAVE+(i*16),(UINT8*)&id,16 ); //д0

       }


      delay_ms(200);
      for(i=0;i<256;i++)
      {
          o24lcxxx_write_bytes(ADDBLACK_MAP+(i*16),(UINT8*)&id,16 ); //д0

      }
      delay_ms(200);
      cur_max_blacklist = 0;
      idmax = cur_max_blacklist;
      o24lcxxx_write_bytes(ADDBLACK_SAVE_MAX,(UINT8*)&idmax,2 ); //��ڿ��������
}