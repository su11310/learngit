/*
 * File:   company.h
 * Author: Administrator
 *
 * Created on 2014��4��11��, ����10:46
 */

#ifndef COMPANY_H
#define	COMPANY_H

#ifdef	__cplusplus
extern "C" {
#endif
#define T_maxBuflen   128
#define R_maxBuflen   80
    #define _F_ENABLE_        0   //1:����Ч  0������Ч //rg170809 ��5����ʱ���� ����Ϊ0
//extern BOOL RecvUnit_ok;
//extern BOOL SendUnit_ok;
UINT8 Recv_Buf[R_maxBuflen];
UINT8 Send_Buf[T_maxBuflen];
   //      #define combufleng    128    //���ڷ��ͻ���������////************************************
  //      #define cominbufleng  40  //���ڽ��ջ���������////************************************
        #define Heareat_Timeout  300 //������ʱ300*10ms

        #define COMPANY_TIMEOUT 5 //ͨѶ��ʱ5sPROTOCOL_RESET_NUM
        #define COMPANY_RESET_NUM 3 //��ʱ3�Σ���ʼ������
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
//  volatile   UINT32    Company_tick;//��ʱ�δ�
  volatile   UINT32  heareat_time;
   volatile   UINT32    re_over_tick;//��ʱ�δ�
   volatile   UINT32    re_over_tick2;
   volatile   UINT32    TEST_tick;//��ʱ�δ�
   volatile   UINT32    TEST1_tick;
   volatile   UINT8    uart_state;//��ʱ״̬
   volatile   UINT8    uart_state2;//��ʱ״̬
   BOOL  opotocol_SW;     //��̨ͨ�ſ���
   BOOL  heareat_flag;
   UINT8  ORD_DATAPA;     //���ݰ�����
   UINT8 Companybufleng;  //���������ͽ�ֹλ��
   UINT8 CompanyInbufleng;  //���������ս�ֹλ��
   UINT8 Company_Timeoutnum;
   BOOL  Companytime_flag;     //��̨ͨ�ż�ʱ��־
   BOOL  Company_alarm;//ackͨ���쳣��־

 //  BYTE gComRF[combufleng];
   UINT16  Companycrc_rece;
 //  BYTE gComIn[cominbufleng];
//   UINT16 Rec_liushnum;//********
//   UINT16 Rec_shiftidnum;//********
   UINT8 CompanyPos;
   UINT8 re_cmdnu;//
   UINT8 se_cmdnu;

 //  UINT8   sq[4];//��̨ǹ����֤�ַ���
//   UINT8 gComRec_OK;
//   UINT16 cur_max_blacklist;    //��ǰ����������
//   UINT8  cur_p_GID;//��ǰ����
 //  UINT8   sys_recPCtime[6];///////

//   BOOL   Result_card;//��֤���
//  float JQvolu;
//  float JQ_money;
#if 0
    typedef enum
  {
     MAX_NULL_FLAG = 0,
     liushuirec_flag,   //ÿ�ʼ�����¼���ޱ�ʶ
     lngGasruning_flag,  //������
    lngstate_flag ,     //������״̬���ޱ�ʶ
    shift_flag ,       //�ְ���Ϣ���ޱ�ʶ
    LNGparas_flag,     //�������������ޱ�ʶ
    newblacklist_flag, //�������������ޱ�ʶ
    blacklist_flag ,    //���к��������ޱ�ʶ    һ��һ����
    cardverify_flag,  //����֤���ޱ�ʶ
    clockask_flag,  //ʱ���������ޱ�ʶ
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
// //ϵͳ����
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
//     UINT8 RevData[sizeof(struct Para)];   //ǿ������ͽṹ�����
// }SYSTEMPARA;
//Mengfr 20161111
//ϵͳ����
 #pragma pack(1) //����1byte����
 //#if  _F_ENABLE_				//rg170809 ��5����ʱ����
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
        #if  _F_ENABLE_				//rg170809 ��5����ʱ����
        float f_delay;//rg170809 ��5����ʱ����
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
//BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh);//rg160907;//��������ˮ-------------
//BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh,UINT32 *ye,UINT8 *cp,float *hq);//rg170607 rg180131������Ϣ���ƺ�
 BOOL qty_get_serrec(UINT32 data,float *dj,float *je,float *ql,UINT8 *rq,UINT8 *cn,UINT16 *ygh,UINT32 *ye,UINT8 *cp,float *hq,UINT8 *wz);//rg170607 rg180131������Ϣ���ƺ�
BOOL qty_get_mod(float *total,float *temp,float *gain,float *Density ,float *ls);//--------------
BOOL qty_get_gid(UINT32 *qid_total);//ǹ��--------------
BOOL qty_get_shift(UINT32 *s_total);//����---------------
BOOL qty_get_yl(float *yl);//----------------
void send_ack_sj(UINT8 cmdnum);
BOOL ocompany_precool_stop();
BOOL ocompany_precool_start();
//void ocompany_precool_getstate(float temp,float gain,float md,float ls,float yl);
void ocompany_precool_timeover();
void ocompany_precool_ok();
UINT8 ocompany_precool_getstate(float *temp,float *gain,float *md,float *ls,float *yl); //����ֵ��0����ʱ��1����Ч��ֵ��2��ok
BOOL ocompany_gass_stop();
void ocompany_gass_ok();
void ocompany_getgass(float *ql,float *ls,float *yl,float *temp);//----------------
BOOL ocompany_gass_amount(float data,UINT8 *carnum ,UINT8 len );
//UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time);//�����ϰ���Ϣ ��������ţ����ţ��ϰ�ʱ�䣬���أ�0���ɹ��ϰ� 1���ڿ� 2���ҿ� 3��ͨ���쳣
//BOOL off_work(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time);//�����°���Ϣ ��������ţ����ţ��ϰ�ʱ��
//rg160612
//UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT16 ygno);//�����ϰ���Ϣrg160907
UINT8 Shift_join(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT16 ygno,UINT8 *time);//�����ϰ���Ϣrg160907 rg170110
BOOL off_work(UINT8 shift_id, UINT8 * shift_card,UINT8 * shift_op_time,UINT32 *rec,UINT32 *class_q,UINT32 *class_h,UINT32 *gain_q,UINT32 *gain_h,UINT8 *xdsj);//�����°���Ϣ ��������ţ����ţ��ϰ�ʱ��
void ocompany_shift_ok();
void ocompany_offwork_ok();
//BOOL qty_get_sys(UINT8 *qid,float *price ,float *temp,\
//        float *gain,float *ls ,float *aqyl,float *zeroyl,float *ylxs,float *Density_up ,float *Density_do,float *ylys,float *gas_delay,float *RefVol,float *glbh,float *lspd);
BOOL qty_get_sys(SYSTEMPARA *ptr);  //Mengfr 20161111
BOOL Send_SOE_State(UINT8 *data) ;    // ss190912
//��ѯϵͳ��Ϣ
//----------------------
BOOL ocompany_Handshake();//����
BOOL module_vctrl(UINT8 Ctlnum,UINT8 ACTION);//Ctlnum:��ŷ�״̬������ֵ��1-4��ʾ��ŷ�1-4��5��PLC1��6��PLC2;
                                            //ACTION:����������ֵ��1��open��0��close��
BOOL module_vctrl_pump_sw(UINT8 ACTION);//��������//����1��ͣ 2��Ԥ�� 3����ע 4������
BOOL get_ModuleSave(UINT8 *chk);
BOOL get_press(float *press);//��õ�ǰѹ����������ֵ
//BOOL qty_get_g_mod(float *total,float *temp,float *gain,float *Density ,float *ls);  //GL:1:YE 2��QI--------
BOOL qty_get_g_mod(float *temp,float *gain,float *Density,float *ls ,float *total,float *yl);  //GL:1:YE 2��QI
BOOL qty_get_l_mod(float *temp,float *gain,float *Density,float *ls ,float *total,float *yl);  //GL:1:YE 2��QI
//BOOL qty_get_l_mod(float *total,float *temp,float *gain,float *Density ,float *ls);//------------------
BOOL ocompany_set_xz(UINT8 *num);
BOOL qty_get_xz(float *num);
BOOL Clear_modbus(UINT8 ModType);//���������� ������1��Һ�ࣻ2�����ࣻ
BOOL Set_gain(float rec,UINT8 len );
BOOL Set_pre_temp(float rec,UINT8 len );
BOOL Set_Density_up(float rec,UINT8 len );
BOOL Set_Density_down(float rec,UINT8 len );
BOOL Set_precool_delay(float rec,UINT8 len );
//*******************************************************************//
 BOOL Gets_SumandPress_start(float *Rec_Sum_Start,float *Rec_Begin_Press);//Ҫ
//BOOL Ocompany_GetGas_REC(float *GV, float *AM,float *back_gas,float *endPress,UINT8 *EccType);//����ֹͣ��:��������������
BOOL Ocompany_GetGas_REC(float *GV, float *AM,float *back_gas,float *endPress,UINT8 *EccType,UINT32 *rec,UINT8 *hq_state);
BOOL ocompany_zanhao_verify(UINT8 *num) ;
BOOL qty_get_zhanhao(UINT8 *num,float *relay,UINT8 *ver);
BOOL ocompany_relay_set(float num);
UINT8 Check_Card_info(UINT8 * cn,INT32 *car_m,INT32 *car_g,UINT8 xf);//�˶Կ���Ϣ���Ƿ��Ǻڿ�,//����ֵ��0��ͨ�Ŵ���1�������� 2���ڿ� 3Ϊ��ؿ��ɼ�����4Ϊ��ؿ����ɼ���
//UINT8 Ocompany_Gas_noquan_start(float money);//���������Ŀ�ʼ0:ͨѶ���� 1:���Լ���2��δԤ��

//UINT8 Ocompany_Gas_noquan_start(float money,UINT8 jgdj,float zkl,float curprice);
UINT8 Ocompany_Gas_noquan_start(float money,UINT8 jgdj,float zkl,float curprice,UINT8 *cp,UINT8 ks);//���������Ŀ�ʼ0:ͨѶ���� 1:���Լ���2��δԤ�� �۸�ȼ� �ۿ���//rg170607 ������Ϣ���ƺ�rg181210
BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK);
BOOL Ocompany_Gas_noquan_stop(UINT8 state);//�Ƕ���������ֹͣ
BOOL Ocompany_Gas_noquan_finish(UINT8 *card_type, UINT8 * cn,float *GV, float *AM,INT32 *rec_card_preM_int ,INT32 *rec_card_endM_int,INT32 *rec_card_preg_int,INT32 *rec_card_endg_int,float *rec_sum_start,float *rec_sum_end, float *rec_begin_Press,float *rec_end_Press,UINT8* Car_hui_L,UINT8 * gas_Stime,UINT8 * gas_Etime )//�Ƕ�������������:���������Ƿ������ɡ�isgasOKΪ1��ʾ������ɡ�
;
// UINT8 Ocompany_Gas_Quan_start(float money);//���������Ŀ�ʼ0:ͨѶ���� 1:���Լ���2�� δԤ��
//UINT8 Ocompany_Gas_Quan_start(float money,UINT8 jgdj,float zkl,float curprice);//���������Ŀ�ʼ0:ͨѶ���� 1:���Լ���2�� δԤ�� �۸�ȼ� �ۿ���
 UINT8 Ocompany_Gas_Quan_start(float money,UINT8 jgdj,float zkl,float curprice,UINT8 *cp,UINT8 ks);//���������Ŀ�ʼ0:ͨѶ���� 1:���Լ���2�� δԤ��//rg170607 rg181210
BOOL Ocompany_Gas_Quan_run(float *GV, float *AM,float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK)//��������������:���������Ƿ������ɡ�isgasOKΪ:1��ʾ�������;2����ʾ��������
;
//BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *press,float *backgas,UINT8 *isgasOK);//�Ƕ�������������:���������Ƿ������ɡ�isgasOKΪ:1��ʾ����;2����ʾ�����������ذ�������ֹͣ������
BOOL Ocompany_Gas_Quan_stop(UINT8 state);//����������ֹͣ
BOOL Set_gaswait(float rec,UINT8 len );
BOOL Ocompany_stop();//
BOOL Ocompany_Gas_Quan_finish(UINT8 *card_type, UINT8 * cn,float *GV, float * AM,INT32 * rec_card_preM_int ,
        \
        INT32 *rec_card_endM_int,INT32 *rec_card_preg_int,INT32 *rec_card_endg_int,float *rec_sum_start,float *rec_sum_end,
        \
        float *rec_begin_Press,float *rec_end_Press,UINT8 *Car_hui_L ,UINT8 * gas_Stime,UINT8 * gas_Etime)//�Ƕ�������������:���������Ƿ������ɡ�isgasOKΪ1��ʾ������ɡ�
;

BOOL err_ts(UINT8 *err);//������Ϣ��ʾ
//*******************************************************************//
BOOL Set_price2(UINT8 comm,float rec,UINT8 len );
void send_ack(UINT8 cmdnum);
void send_nck(UINT8 cmdnum);
BOOL down_get_password(UINT8 *num);  //������Կ
BOOL module_dispLcd_test();
BOOL Buff_modbus(UINT8 ModType);//���������� ������1��Һ�ࣻ2�����ࣻ
UINT8 Card_Verif(UINT8 * cn,UINT8 ed,float yue);
BOOL Ocompany_Gas_Qz();//ȡ��
BOOL qty_get_pricex(float *price2 ,float *price3,\
        float *price4,float *price5 ,float *price6,float *price7,float *price8,float *price9 ,float *price10);
BOOL qty_get_jlerr(float *num1,float *num2,float *num3,float *num4,float *num5,float *num6,float *num7,float *num8,float *num9,\
float *num10,float *num11,float *num12,float *num13,float *num14,float *num15);
BOOL Set_glbh(float rec,UINT8 len );//���ٱ���
BOOL qty_get_resetinfo(UINT32 data,UINT32 *maxdata,UINT32 *curdata,UINT8 *rq,UINT8 *no);//rg160622//������λ��¼
BOOL ocompany_duishi_jpzhu(UINT8 *data,UINT8 len );//rg170110
BOOL qty_get_sw(UINT8 *num);  //rg161220 �鲦�뿪��
BOOL TB_Send_YG(UINT8 *cn,UINT8 yg,UINT8 * tb_op_time);//���rg170701
BOOL  Get_ZiCard_info(UINT8 * cn,UINT8 *state,INT32 *car_m,float *cat_mf);//rg170717
void send_zh_state(UINT8 cmdnum);//rg171011
BOOL Set_fdelay(float rec,UINT8 len );//rg170809 ��5����ʱ����
BOOL ocompany_send_daxs(UINT8 cmdcode,UINT8 gn,UINT8 data);//rg180327
BOOL Set_qtotal(INT8 *curflow,UINT8 len);//rg181129
BOOL Set_stotal(UINT8 *curflow,UINT8 len);//rg181129
BOOL Set_curflowbz(UINT8 *curflow,UINT8 len);//rg181129
BOOL qty_get_shiftls(UINT32 *s_total);//rg181129
BOOL qty_get_zdls(UINT32 *lsh);//rg181129��ˮ��
//BOOL Ocompany_Gas_noquan_run(float *GV, float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK,UINT8 *fz);//rg170606�ܶȵ�ŷ���ʾ
//BOOL Ocompany_Gas_Quan_run(float *GV, float *AM,float *gain,float *ls,float *temp,float *desenty,float *press,float *backgas,UINT8 *isgasOK,UINT8 *fz)//��������������:���������Ƿ������ɡ�isgasOKΪ:1��ʾ�������;2����ʾ��������//rg170606�ܶȵ�ŷ���ʾ
#ifdef	__cplusplus
}
#endif

#endif	/* COMPANY_H */

