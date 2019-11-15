/*
 * File:   company.h
 * Author: Administrator
 *
 * Created on 2014年4月11日, 上午10:46
 */

#ifndef COMPANY_H
#define	COMPANY_H

#ifdef	__cplusplus
extern "C" {
#endif
#define T_maxBuflen   128
#define R_maxBuflen   80
    #define _F_ENABLE_        0   //1:阀有效  0：阀无效 //rg170809 第5阀延时设置 正常为0
//extern BOOL RecvUnit_ok;
//extern BOOL SendUnit_ok;
UINT8 Recv_Buf[R_maxBuflen];
UINT8 Send_Buf[T_maxBuflen];
   //      #define combufleng    128    //串口发送缓冲区长度////************************************
  //      #define cominbufleng  40  //串口接收缓冲区长度////************************************
        #define Heareat_Timeout  300 //心跳定时300*10ms

        #define COMPANY_TIMEOUT 5 //通讯超时5sPROTOCOL_RESET_NUM
        #define COMPANY_RESET_NUM 3 //超时3次，初始化串口
        #define COMPANY_OVERTIME   1//20//5
        #define COMPANY_OVERTIME2   2//20//5
        #define COMPANY_OVERTIME3   3//20//5
        #define COMPANY_OVERTIME4   4//20//5
        #define COMPANY_OVERTIME5   5//20//5
        #define COMPANY_OVERTIME10 10//30//10
        #define COMPANY_OVERTIME15  15//50// 15
        #define COMPANY_OVERTIME20  20//50// 15
        #define COMPANY_OVERTIME300  60*5//50// 15
UINT16  crc_rece;
BOOL RecvUnit_ok;
BOOL SendUnit_ok;
BOOL Precool_ok;
BOOL Precool_over;
BOOL gass_ok;
BOOL gass_stop;
BOOL shift_ok;
BOOL offwork_ok;
//  volatile   UINT32    Company_tick;//超时滴答
  volatile   UINT32  heareat_time;
   volatile   UINT32    re_over_tick;//超时滴答
   volatile   UINT32    re_over_tick2;
   volatile   UINT32    TEST_tick;//超时滴答
   volatile   UINT32    TEST1_tick;
   volatile   UINT8    uart_state;//超时状态
   volatile   UINT8    uart_state2;//超时状态
   BOOL  opotocol_SW;     //后台通信开关
   BOOL  heareat_flag;
   UINT8  ORD_DATAPA;     //数据包命令
   UINT8 Companybufleng;  //缓冲区发送截止位置
   UINT8 CompanyInbufleng;  //缓冲区接收截止位置
   UINT8 Company_Timeoutnum;
   BOOL  Companytime_flag;     //后台通信计时标志
   BOOL  Company_alarm;//ack通信异常标志

 //  BYTE gComRF[combufleng];
   UINT16  Companycrc_rece;
 //  BYTE gComIn[cominbufleng];
//   UINT16 Rec_liushnum;//********
//   UINT16 Rec_shiftidnum;//********
   UINT8 CompanyPos;
   UINT8 re_cmdnu;//
   UINT8 se_cmdnu;

 //  UINT8   sq[4];//后台枪号验证字符串
//   UINT8 gComRec_OK;
//   UINT16 cur_max_blacklist;    //当前最大黑名单数
//   UINT8  cur_p_GID;//当前抢号
 //  UINT8   sys_recPCtime[6];///////

//   BOOL   Result_card;//验证结果
//  float JQvolu;
//  float JQ_money;
#if 0
    typedef enum
  {
     MAX_NULL_FLAG = 0,
     liushuirec_flag,   //每笔加气记录有无标识
     lngGasruning_flag,  //加气中
    lngstate_flag ,     //加气机状态有无标识
    shift_flag ,       //轮班信息有无标识
    LNGparas_flag,     //加气机参数有无标识
    newblacklist_flag, //新增黑名单有无标识
    blacklist_flag ,    //所有黑名单有无标识    一次一百条
    cardverify_flag,  //卡验证有无标识
    clockask_flag,  //时间请求有无标识
    setpara_flag

  }Protocol_state;
#endif
  typedef union zh32to8
  {
      UINT8 zh[4];
      UINT32 sou;
  }Zh328;
typedef struct CompanyPack
{
    UINT8  cmd ;
    UINT8  cmdcont ;
    UINT8  cmdlen;
    UINT8 fun;
    UINT8 Operation;
//    UINT8 pack_len;
    UINT8 pdata[128];

}company_pk;
typedef enum{
            reack=0,
            restate,
            resige,
            repre,
            regass,
            reqty,
            reset,
            retest,
            recardvie
}ReveFlag;
typedef union _def_compa//time:14-04-15 rengang
{
        float          compa_float;
        UINT8           compa_uc[4];
        UINT32          compa_u32;
        INT32           compa_int32;
 }Compa_float;
 typedef union _def_compau32//time:14-04-15 rengang
{
        UINT32          compa_u32;
        unsigned char  compa_uc[4];
 }Compa_u32;
 
// //Mengfr 20161111
// //系统参数
// typedef union
// {
//     struct
//     {
//        UINT8 qid;
//        float price;
//        float temp;
//        float gain;
//        float ls;
//        float aqyl;
//        float zeroyl;
//        float ylxs;
//        float Density_up;
//        float Density_do;
//        float ylys;
//        float gas_delay;
//        float RefVol;
//        float glbh;
//        UINT16 lspd;
//        float MinorCycleDelay;
//        float MajorCycleDelay; 
//     }Para;
//     UINT8 RevData[sizeof(struct Para)];   //强制数组和结构体对齐
// }SYSTEMPARA;
//Mengfr 20161111
//系统参数
 #pragma pack(1) //按照1byte对齐
 //#if  _F_ENABLE_				//rg170809 第5阀延时设置
 typedef struct SYSTEMPARA
 {
        UINT8 qid;
        float price;
        float temp;
        float gain;
        float ls;
        float aqyl;
        float zeroyl;
        float ylxs;
        float Density_up;
        float Density_do;
        float ylys;
        float gas_delay;
        float RefVol;
        float glbh;
        UINT16 lspd;
        float MinorCycleDelay;
        float MajorCycleDelay;     
        UINT8 djxs;//rg180327
        #if  _F_ENABLE_				//rg170809 第5阀延时设置
        float f_delay;//rg170809 第5阀延时设置
        #endif
}SYSTEMPARA;
/*#else
 typedef struct SYSTEMPARA
 {
        UINT8 qid;
        float price;
        float temp;
        float gain;
        float ls;
        float aqyl;
        float zeroyl;
        float ylxs;
        float Density_up;
        float Density_do;
        float ylys;
        float gas_delay;
        float RefVol;
        float glbh;
        UINT16 lspd;
        float MinorCycleDelay;
        float MajorCycleDelay;     
}SYSTEMPARA;
#endif*/
#pragma pack()
UINT16 omodbus_crc16(UINT8 *buf, UINT16 Len);
void ocompany_recv();
void ocompany_port_init(unsigned long baud);
void Company_sendstr(UINT8 len, UINT8 *buf);
void ocom_send_shift(void);
void  ocom_send_heareat (void);
void Configure_company(void);
void  company_Answer (void);
void ocompany_send_clockask(void);
BOOL ocompany_compack(UINT8 cmdcode,UINT8 gn,float data,UINT8 len );
BOOL ocompany_set_uint(UINT8 cmdcode,UINT8 gn,UINT8 *rec,UINT8 len );
 BOOL qty_get_rec(float *dj,float *je,float *ql);//,UINT32 *recg );-------------
//BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh);//rg160907;//检索查流水-------------
//BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh,UINT32 *ye,UINT8 *cp,float *hq);//rg170607 rg180131加气信息车牌号
 BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh,UINT32 *ye,UINT8 *cp,float *hq,UINT8 *wz);//rg170607 rg180131加气信息车牌号
BOOL qty_get_mod(float *total,float *temp,float *gain,float *Density ,float *ls);//--------------
BOOL qty_get_gid(UINT32 *qid_total);//枪累--------------
BOOL qty_get_shift(UINT32 *s_total);//班累---------------
BOOL qty_get_yl(float *yl);//----------------
void send_ack_sj(UINT8 cmdnum);
BOOL ocompany_precool_stop();
BOOL ocompany_precool_start();
//void ocompany_precool_getstate(float temp,float gain,float md,float ls,float yl);
void ocompany_precool_timeover();
void ocompany_precool_ok();
UINT8 ocompany_precool_getstate(float *temp,float *gain,float *md,float *ls,float *yl); //返回值：0：超时；1：有效数值；2：ok
BOOL ocompany_gass_stop();
void ocompany_gass_ok();
void ocompany_getgass(float *ql,float *ls,float *yl,float *temp);//----------------
BOOL ocompany_gass_amount(float data,UINT8 *carnum ,UINT8 len );
//UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time);//发送上班信息 参数：班号，卡号，上班时间，返回：0：成功上班 1：黑客 2：灰卡 3：通信异常
//BOOL off_work(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time);//发送下班信息 参数：班号，卡号，上班时间
//rg160612
//UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT16 ygno);//发送上班信息rg160907
UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT16 ygno,UINT8 *time);//发送上班信息rg160907 rg170110
BOOL off_work(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT32 *rec,UINT32 *class_q,UINT32 *class_h,UINT32 *gain_q,UINT32 *gain_h,UINT8 *xdsj);//发送下班信息 参数：班号，卡号，上班时间
void ocompany_shift_ok();
void ocompany_offwork_ok();
//BOOL qty_get_sys(UINT8 *qid,float *price ,float *temp,\
//        float *gain,float *ls ,float *aqyl,float *zeroyl,float *ylxs,float *Density_up ,float *Density_do,float *ylys,float *gas_delay,float *RefVol,float *glbh,float *lspd);
BOOL qty_get_sys(SYSTEMPARA *ptr);  //Mengfr 20161111
BOOL Send_SOE_State(UINT8 *data) ;    // ss190912
//查询系统信息
//----------------------
BOOL ocompany_Handshake();//握手
BOOL module_vctrl(UINT8 Ctlnum,UINT8 ACTION);//Ctlnum:电磁阀状态。参数值：1-4标示电磁阀1-4；5：PLC1；6：PLC2;
                                            //ACTION:动作。参数值：1：open；0：close；
BOOL module_vctrl_pump_sw(UINT8 ACTION);//联动测试//参数1：停 2：预冷 3：加注 4：待机
BOOL get_ModuleSave(UINT8 *chk);
BOOL get_press(float *press);//获得当前压力传感器数值
//BOOL qty_get_g_mod(float *total,float *temp,float *gain,float *Density ,float *ls);  //GL:1:YE 2：QI--------
BOOL qty_get_g_mod(float *temp,float *gain,float *Density,float *ls ,float *total,float *yl);  //GL:1:YE 2：QI
BOOL qty_get_l_mod(float *temp,float *gain,float *Density,float *ls ,float *total,float *yl);  //GL:1:YE 2：QI
//BOOL qty_get_l_mod(float *total,float *temp,float *gain,float *Density ,float *ls);//------------------
BOOL ocompany_set_xz(UINT8 *num);
BOOL qty_get_xz(float *num);
BOOL Clear_modbus(UINT8 ModType);//流量计清零 参数：1：液相；2：气相；
BOOL Set_gain(float rec,UINT8 len );
BOOL Set_pre_temp(float rec,UINT8 len );
BOOL Set_Density_up(float rec,UINT8 len );
BOOL Set_Density_down(float rec,UINT8 len );
BOOL Set_precool_delay(float rec,UINT8 len );
//*******************************************************************//
 BOOL Gets_SumandPress_start(float *Rec_Sum_Start,float *Rec_Begin_Press);//要
//BOOL Ocompany_GetGas_REC(float *GV, float *AM,float *back_gas,float *endPress,UINT8 *EccType);//加气停止后:气量、金额、回气量
BOOL Ocompany_GetGas_REC(float *GV, float *AM,float *back_gas,float *endPress,UINT8 *EccType,UINT32 *rec,UINT8 *hq_state);
BOOL ocompany_zanhao_verify(UINT8 *num) ;
BOOL qty_get_zhanhao(UINT8 *num,float *relay,UINT8 *ver);
BOOL ocompany_relay_set(float num);
UINT8 Check_Card_info(UINT8 * cn,INT32 *car_m,INT32 *car_g,UINT8 xf);//核对卡信息，是否是黑卡,//返回值：0：通信错误，1：正常卡 2：黑卡 3为异地卡可加气，4为异地卡不可加气
//UINT8 Ocompany_Gas_noquan_start(float money);//定量加气的开始0:通讯错误 1:可以加气2：未预冷

//UINT8 Ocompany_Gas_noquan_start(float money,UINT8 jgdj,float zkl,float curprice);
UINT8 Ocompany_Gas_noquan_start(float money,UINT8 jgdj,float zkl,float curprice,UINT8 *cp,UINT8 ks);//定量加气的开始0:通讯错误 1:可以加气2：未预冷 价格等级 折扣率//rg170607 加气信息车牌号rg181210
BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK);
BOOL Ocompany_Gas_noquan_stop(UINT8 state);//非定量加气的停止
BOOL Ocompany_Gas_noquan_finish(UINT8 *card_type, UINT8 * cn,float *GV, float *AM,INT32 *rec_card_preM_int ,INT32 *rec_card_endM_int,INT32 *rec_card_preg_int,INT32 *rec_card_endg_int,float *rec_sum_start,float *rec_sum_end, float *rec_begin_Press,float *rec_end_Press,UINT8* Car_hui_L,UINT8 * gas_Stime,UINT8 * gas_Etime )//非定量加气过程中:气量、金额、是否加气完成。isgasOK为1表示加气完成。
;
// UINT8 Ocompany_Gas_Quan_start(float money);//定量加气的开始0:通讯错误 1:可以加气2： 未预冷
//UINT8 Ocompany_Gas_Quan_start(float money,UINT8 jgdj,float zkl,float curprice);//定量加气的开始0:通讯错误 1:可以加气2： 未预冷 价格等级 折扣率
 UINT8 Ocompany_Gas_Quan_start(float money,UINT8 jgdj,float zkl,float curprice,UINT8 *cp,UINT8 ks);//定量加气的开始0:通讯错误 1:可以加气2： 未预冷//rg170607 rg181210
BOOL Ocompany_Gas_Quan_run(float *GV, float *AM,float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK)//定量加气过程中:气量、金额、是否加气完成。isgasOK为:1表示加气完成;2：表示加气错误
;
//BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *press,float *backgas,UINT8 *isgasOK);//非定量加气过程中:气量、金额、是否加气完成。isgasOK为:1表示余额不足;2：表示加气错误，主控板已自主停止加气。
BOOL Ocompany_Gas_Quan_stop(UINT8 state);//定量加气的停止
BOOL Set_gaswait(float rec,UINT8 len );
BOOL Ocompany_stop();//
BOOL Ocompany_Gas_Quan_finish(UINT8 *card_type, UINT8 * cn,float *GV, float * AM,INT32 * rec_card_preM_int ,
        \
        INT32 *rec_card_endM_int,INT32 *rec_card_preg_int,INT32 *rec_card_endg_int,float *rec_sum_start,float *rec_sum_end,
        \
        float *rec_begin_Press,float *rec_end_Press,UINT8 *Car_hui_L ,UINT8 * gas_Stime,UINT8 * gas_Etime)//非定量加气过程中:气量、金额、是否加气完成。isgasOK为1表示加气完成。
;

BOOL err_ts(UINT8 *err);//错误信息提示
//*******************************************************************//
BOOL Set_price2(UINT8 comm,float rec,UINT8 len );
void send_ack(UINT8 cmdnum);
void send_nck(UINT8 cmdnum);
BOOL down_get_password(UINT8 *num);  //下载秘钥
BOOL module_dispLcd_test();
BOOL Buff_modbus(UINT8 ModType);//流量计清零 参数：1：液相；2：气相；
UINT8 Card_Verif(UINT8 * cn,UINT8 ed,float yue);
BOOL Ocompany_Gas_Qz();//取整
BOOL qty_get_pricex(float *price2 ,float *price3,\
        float *price4,float *price5 ,float *price6,float *price7,float *price8,float *price9 ,float *price10);
BOOL qty_get_jlerr(float *num1,float *num2,float *num3,float *num4,float *num5,float *num6,float *num7,float *num8,float *num9,\
float *num10,float *num11,float *num12,float *num13,float *num14,float *num15);
BOOL Set_glbh(float rec,UINT8 len );//过速保护
BOOL qty_get_resetinfo(UINT32 data,UINT32 *maxdata,UINT32 *curdata,UINT8 *rq,UINT8 *no);//rg160622//检索复位记录
BOOL ocompany_duishi_jpzhu(UINT8 *data,UINT8 len );//rg170110
BOOL qty_get_sw(UINT8 *num);  //rg161220 查拨码开关
BOOL TB_Send_YG(UINT8 *cn,UINT8 yg,UINT8 * tb_op_time);//替班rg170701
BOOL  Get_ZiCard_info(UINT8 * cn,UINT8 *state,INT32 *car_m,float *cat_mf);//rg170717
void send_zh_state(UINT8 cmdnum);//rg171011
BOOL Set_fdelay(float rec,UINT8 len );//rg170809 第5阀延时设置
BOOL ocompany_send_daxs(UINT8 cmdcode,UINT8 gn,UINT8 data);//rg180327
BOOL Set_qtotal(INT8 *curflow,UINT8 len);//rg181129
BOOL Set_stotal(UINT8 *curflow,UINT8 len);//rg181129
BOOL Set_curflowbz(UINT8 *curflow,UINT8 len);//rg181129
BOOL qty_get_shiftls(UINT32 *s_total);//rg181129
BOOL qty_get_zdls(UINT32 *lsh);//rg181129流水号
//BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK,UINT8 *fz);//rg170606密度电磁阀显示
//BOOL Ocompany_Gas_Quan_run(float *GV, float *AM,float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK,UINT8 *fz)//定量加气过程中:气量、金额、是否加气完成。isgasOK为:1表示加气完成;2：表示加气错误//rg170606密度电磁阀显示
#ifdef	__cplusplus
}
#endif

#endif	/* COMPANY_H */

