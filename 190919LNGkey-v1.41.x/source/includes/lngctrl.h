/* 
 * File:   lngctrl.h
 * Author: jereh
 *
 * Created on 2014-01-14  20:36
 */

#ifndef LNGCTRL_H
#define	LNGCTRL_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "ic_card.h"
  /////////////////加气用到的传递参数//////////////
    UINT8  State_g_p;//1:预冷中   2:加气中
    UINT8 Car_hui;
   UINT8 CARD_XIAOFEI;
   UINT8 _CARD_TYPE;
   UINT8  CN[10],CPBH[16],GPBH[16];
   UINT32 pr_lsh;
   float OKgas_GV;//加气完成扣款气量数
   float OKgas_money;//加气完成扣款金额
   float Rec_Card_PreM;//加气前卡余
   float Rec_Card_EndM;
   float Rec_Card_Preg;//加气前气量
   float Rec_Card_Endg;//加气后气量
   float car_prem;//加气前卡余
   float car_prel;//加气后卡余
   INT32 Rec_Card_PreM_int;//加气前卡余整形
   INT32 Rec_Card_EndM_int;//卡后余額整形
   INT32 Rec_Card_Preg_int;//加气前气量整形
   INT32 Rec_Card_Endg_int;//加气后气量整形
       float mlc,glc;
   float Rec_Sum_Start;
   float Rec_Sum_End;
   float Rec_Begin_Press;
   float Rec_End_Press;
   UINT8  GAS_Stime[6];
   UINT8  GAS_Etime[6];
   float GAS_BACKGV;//加气完成扣款回气量
   float FIX_Money;//定量加气最大数
//   float Get_Money;//定量加气量
   UINT8 FIX_RecOK;
   UINT8 GAS_MustStop_Err;//加气过程的报错
  /////////////////////////

  ////////////////////////
   float GAS_BACKGV;//加气完成扣款回气量
   float PRICE;
   float PRICE2;
   float PRICE3;
   float PRICE4;
   float PRICE5;
   float PRICE6;
   float PRICE7;
   float PRICE8;
   float PRICE9;
   float PRICE10;
   float Cur_Price;//执行单价
   UINT8 Qianghao;
   UINT8 GasBegin;
   UINT8 Graybegain;
   UINT8 Car_Hui_ok; 
   UINT8 SendStop_False;
   UINT8 GasCo;  //允许加气定时的标识
   UINT8 PrecoolCo;
   BOOL     send_sj_flag;
   BOOL     send_yl_flag;
#define OPEN    1
            #define CLOSE    0
            #define VK1    1
            #define VK2    2
            #define VK3    3
            #define VK4    4
            #define PLC1   5
            #define PLC2   6

 //              #define VK1    1
            #define EH    2
            #define EM    3
            #define EL    4
            #define PLC1   5
            #define PLC2   6
            #define ISADDTIME   900     //////15分钟 注意：此时间不能超过主板自动保存时间20分钟
 void Gas_para_init(void);
 BOOL get_price(float *PRICE,UINT8 *qh);
 void olng_LNG_Operate(void);
 void olng_operate_Isadd(void);
 void olng_start_act(void);
 void gas_finish(void);
 BOOL olng_operate_fixm(float* fix_money);
 BOOL olng_operate_fixv(float *fix_money);
  BOOL olng_operate_put_card();
  void Select_print(void);

        #define     _MODBUS_L_AUTO_RM_BUF_LEN		5
        #define MODBUS_LNG_L_ADDR                       1
        #define MODBUS_LNG_C_ADDR                       2


        #define SOLENOID_1_OPEN()   mPORTGSetBits(BIT_6)
        #define SOLENOID_1_CLOSE()  mPORTGClearBits(BIT_6)
        #define SOLENOID_2_OPEN()   mPORTGSetBits(BIT_7)
        #define SOLENOID_2_CLOSE()  mPORTGClearBits(BIT_7)
        #define SOLENOID_3_OPEN()   mPORTDSetBits(BIT_12)
        #define SOLENOID_3_CLOSE()  mPORTDClearBits(BIT_12)
        #define SOLENOID_4_OPEN()   mPORTDSetBits(BIT_13)
        #define SOLENOID_4_CLOSE()  mPORTDClearBits(BIT_13)
        #define SOLENOID_5_OPEN()   mPORTBSetBits(BIT_8)
        #define SOLENOID_5_CLOSE()  mPORTBClearBits(BIT_8)
        #define SOLENOID_6_OPEN()   mPORTBSetBits(BIT_9)
        #define SOLENOID_6_CLOSE()  mPORTBClearBits(BIT_9)

        #define SOLENOID_ALL_OPEN()   mPORTGSetBits(BIT_6)
        #define SOLENOID_ALL_CLOSE()  mPORTGClearBits(BIT_6)

         
           
#if 0
        #define VK1_OPEN()   SOLENOID_1_OPEN()
        #define VK1_CLOSE()  SOLENOID_1_CLOSE()
        #define VK2_OPEN()   SOLENOID_2_OPEN()
        #define VK2_CLOSE()  SOLENOID_2_CLOSE()
        #define VK3_OPEN()   SOLENOID_3_OPEN()
        #define VK3_CLOSE()  SOLENOID_3_CLOSE()
        #define VK4_OPEN()   SOLENOID_4_OPEN()
        #define VK4_CLOSE()  SOLENOID_4_CLOSE()
#endif
        #define VK1_OPEN()   SOLENOID_1_OPEN()
        #define VK1_CLOSE()  SOLENOID_1_CLOSE()
        #define EH_OPEN()   SOLENOID_2_OPEN()
        #define EH_CLOSE()  SOLENOID_2_CLOSE()
        #define EM_OPEN()   SOLENOID_3_OPEN()
        #define EM_CLOSE()  SOLENOID_3_CLOSE()
        #define EL_OPEN()   SOLENOID_4_OPEN()
        #define EL_CLOSE()  SOLENOID_4_CLOSE()

        #define PLC1_OPEN()   SOLENOID_5_OPEN()
        #define PLC1_CLOSE()  SOLENOID_5_CLOSE()
        #define PLC2_OPEN()   SOLENOID_6_OPEN()
        #define PLC2_CLOSE()  SOLENOID_6_CLOSE()

  //       #define VK1_OPEN()   SOLENOID_1_OPEN()
  //      #define VK1_CLOSE()   SOLENOID_1_CLOSE()
        #define VK2_OPEN()     EH_OPEN()
        #define VK2_CLOSE()     EH_CLOSE()
        #define VK3_OPEN()      EM_OPEN()
        #define VK3_CLOSE()     EM_CLOSE()
        #define VK4_OPEN()      EL_OPEN()
        #define VK4_CLOSE()     EL_CLOSE()

        #define PLC1_OPEN()   SOLENOID_5_OPEN()
        #define PLC1_CLOSE()  SOLENOID_5_CLOSE()
        #define PLC2_OPEN()   SOLENOID_6_OPEN()
        #define PLC2_CLOSE()  SOLENOID_6_CLOSE()

        #define CVK1_OPEN()  VK4_OPEN()
        #define CVK1_CLOSE()  VK4_CLOSE()
        #define CVK2_OPEN()  VK3_OPEN()
        #define CVK2_CLOSE()  VK3_CLOSE()

/*-------------------------------------------------------
 * PLC1  PLC2
 * 0      0   停机
 * 0      1   待机  0    1
 * 1      0   预冷  1    0
 * 1      1   加液
 -------------------------------------------------------*/
        //#define  PRECOOL_CTRL()   VK1_OPEN(); VK4_CLOSE(); VK3_OPEN(); PLC1_CLOSE(); PLC2_OPEN(); VK2_CLOSE()
        //#define  IDLE_CTRL()      VK1_OPEN(); VK4_OPEN(); VK3_CLOSE(); PLC1_OPEN(); PLC2_CLOSE(); VK2_CLOSE()
        // 0101
        #define  INIT_CLRT()            VK1_CLOSE(); CVK1_CLOSE(); CVK2_CLOSE(); PLC1_CLOSE(); PLC2_CLOSE(); VK2_CLOSE()//00000
        #define  IDLE_CTRL()            VK1_OPEN(); CVK1_CLOSE(); CVK2_OPEN(); PLC1_CLOSE(); PLC2_OPEN(); VK2_CLOSE()//0101
        #define  PRECOOL_CTRL()         VK1_OPEN(); CVK1_OPEN(); CVK2_CLOSE(); PLC1_OPEN(); PLC2_CLOSE(); VK2_CLOSE()//1010
        #define  PRECOOL_SUSSE()        VK1_OPEN(); CVK1_CLOSE(); CVK2_OPEN(); PLC1_OPEN(); PLC2_CLOSE(); VK2_CLOSE()//0110
        #define  PRECOOL_SMALL()        VK1_OPEN(); CVK1_CLOSE(); CVK2_OPEN(); PLC1_OPEN(); PLC2_OPEN(); VK2_CLOSE() //0110
        #define  LNG_ADD_GASS()         VK1_OPEN(); CVK1_OPEN(); CVK2_CLOSE(); PLC1_OPEN(); PLC2_OPEN(); VK2_CLOSE() //1011
        #define  OPERATE_SUCCESS()      VK1_OPEN(); CVK1_CLOSE(); CVK2_OPEN();; PLC1_OPEN(); PLC2_CLOSE(); VK2_CLOSE()//0110
        #define  OPERATE_SYOP()         VK1_OPEN(); CVK1_CLOSE(); CVK2_OPEN();; PLC1_OPEN(); PLC2_CLOSE(); VK2_CLOSE()//0111


typedef struct  debugcord_parme
{
      UINT8   deg_cor_id; //调试记录流水号
      UINT32   deg_card_id; //加气管理卡号
      float   deg_voluent;        //加气量
      UINT8   opera_rec_Time[6];   //开始时间，150729
  

}debugcord_parme;
debugcord_parme deg_oparme;

typedef struct  operate_parme
{
     UINT8   card_id[15];
     UINT8   time[6];
     BOOL   b_fixmop;
     BOOL   b_fixnop;
     BOOL   b_stop;
     card_status      card_status;           //IC卡的状态：有效卡，无效卡，灰卡
     card_type        card_type;       //IC 卡类型  班组卡，公司卡，私车卡
     card_csum_type   cst_type;       //消费类型
     float  maxmoney;
     float  c_voluent;        //当前的加气量
     float  c_money;         //当前的加气金额
     float  card_money;     //卡中金额
     float  card_gass;
     float  back_sum;      //回气量
     float  fix_voluent;   //定量加气的量
     float  fix_money;     //定量加气的金额
     float  begin_sum_v;  //加气前流量计的总量
     float  end_sum_v;    //加气后流量计的总量
     float  last_money;
     float  last_voluent;
     float  begin_press; //开始压力
     float  end_press;   //结束压力
}operate_parme;
       void    olng_psensor_init(void);
       UINT32  olng_psensor_read(void);
       float  olng_psensor_read_adc(UINT8 mCnt);
       void olng_vctrl_init(void);
       void olng_vctrl_switch_on(UINT8 sw);
       void olng_vctrl_switch_off(UINT8 sw);
       void olng_vctrl_pump_sw(UINT8 sw);

       
       void olng_operate_act(void);
       void olng_operate_running(void);
       void olng_operate_stop(void);
       void olng_operate_err_stop(void);
       void olng_operate_fix_stop(void);
       
       void deg_operate_save_end(void); //150730   150801
       void deg_operate_save_begi(void); //150801
       void deg_operate_save_gasing(float GV); //150801
       void olng_addgas_precool();
       void olng_precool_start(void);
       //void  olng_precool_runing(void);
       void olng_operate_precool(void);
       void  olng_precool_runing(void);
       //void olng_operate_precool(void);
       void olng_precool_success(void);
       void olng_precool_stop(void);
       void olng_operate_main_ui(void);
        void test_huika(void);//wang**************************************test
        
        void olng_operate_fixn(void);
        void olng_operate_fix_act(void);
        void olng_operate_fix_stop(void);
        void olng_system_err_stop(void);
        void olng_operate_repeat(void);
void offwork_print(UINT8 *car,UINT32 rec,UINT32 class_q,UINT32 class_h,UINT32 gain_q,UINT32 gain_h);

void show_operat_stop(float GV,float AM);
void olng_operate_disp(BOOL bInit,float gain,float ls,float temp);
void olng_operate_disp2(BOOL bInit,float GV,float desenty,float press);
//void olng_operate_disp(BOOL bInit,float gain,float ls,float temp,float gv,UINT8 fz);//rg170606密度电磁阀显示
//void olng_operate_disp2(BOOL bInit,float GV,float desenty,float press,float gain,UINT8 fz);//rg170606密度电磁阀显示

void olng_procool_disp(BOOL bInit);

void  show_money(UINT8 line, float money);
void show_time(BOOL flag);
void oprint_operate_recact(void);
BOOL Get_again_gas_money(float *max_mone);
void Get_gas_money();
BOOL olngctrl_juPSW(UINT8 *xx);
BOOL Judge_sct_Minimum(float *carprem);
    double CalcPCTimeAndLNGTime(void);
    unsigned long mktimesec (unsigned int year, unsigned int mon,unsigned int day, unsigned int hour,unsigned int min, unsigned int sec);
float Get_zk();
BOOL get_car_info();
double Get_Gp_Time(UINT8 *qx);//计算钢瓶是否到期
UINT8 * ic_conv_un_lj(UINT8 * pstr);//150824
void oprint_qry_to_rec(void);//rg170620
#ifdef	__cplusplus
}
#endif

#endif	/* LNGCTRL_H */