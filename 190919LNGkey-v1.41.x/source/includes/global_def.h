/* 
 * File:   global_def.h
 * Author: jereh
 *
 * Created on 2014_01_13
 */

#ifndef GLOBAL_DEF_H
#define	GLOBAL_DEF_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define _I2C2

    #include <p32xxxx.h>
    #include <stdio.h>
    #include <math.h>
    #include <plib.h>
    #include "kernel.h"
    #include "drivers.h"
    #include "ui.h"
    #include "sysparas.h"
    #include "store.h"
    #include "lngctrl.h"
    #include "ic_card.h"
    #include "uart.h"
    #include "sign.h"
    #include "sysset.h"
    #include "protocol.h"
    #include "des.h"
    #include "clock.h"
    #include "buzzer.h"
    #include "soe.h"
    #include "lngdebug.h"
    #include "company.h"
    #include "TempDetection.h"  //Mengfr 20150831
    #include "time.h"
    #include "gas_log.h"
    #define  SYS_FREQ                           (80000000L)
    #define  GetSystemClock() 			(80000000ul)
    #define  GetPeripheralClock()		(GetSystemClock()/(1 << OSCCONbits.PBDIV)) //(SYS_FREQ/1)
    #define  GetInstructionClock()		(SYS_FREQ)
    #define  DWORDMAX                           0xFFFFFFFF
    #define KEY_NONE                               0xFF

  #define   KEY_VERSION_         41    //���� //��Ʒ�汾�еļ��̰�汾��ȡֵ��Χ��0~99��rg160907
// #define   KEY_VERSION_         17    //���� //��Ʒ�汾�еļ��̰�汾��ȡֵ��Χ��0~99��rg160907//
    //#define   KEY_VERSION_CHAR         M     //��Ʒ�汾�еļ��̰�汾

#if 0
    #define  _UART1
    #define  _UART2
    #define  _UART3
    #define  _UART4
    #define  _UART5
    #define  _UART6
#endif

/*
 * UART5   //pin39/40  U5TX  U5RX
 * UART4   //pin48/47  U4TX  U4RX
 */
    #define PRINT_PORT       UART5
    #define CPUCARD_PORT     UART4
/*
 U8: pin50/49  U2TX U2RX
 */
   // #define PCTRANS_PORT     UART2  //
/*
 U9: pin53/52  U1TX U1RX
 */
    #define LNGDEBUGM_PORT     UART1 // UART1
   
    #define   HARD_VERSION_     "Ӳ���汾:V1.0"
    #define   _VERSION_UART_    "JEREH_LNG_0226_v0.01"
    #define   __SIMU_DEBUG_	1
    #define   down_psw     1

    UINT8  HARDKEYCERA4;//150906
     UINT8  temp_add_vol;
     UINT8  CANGASMINUTE;     
    #define PCCOMPANY_PORT     UART2
    #define LED_OPEN()   mPORTASetBits(BIT_1)
    #define LED_CLOSE()  mPORTAClearBits(BIT_1)

#define PSWSELDirection()        (mPORTCSetPinsDigitalIn(BIT_4))
#define PSWSEL_1()                     (mPORTCReadBits(BIT_4))
#define PSWSEL_0()                      (!mPORTCReadBits(BIT_4))
     
//    #define JiaReMoCtlInit      (mPORTBSetPinsDigitalOut(BIT_9))  //����Ĥ�������ų�ʼ��    //Mengfr 20150831
//    #define JiaReMoOpen     (mPORTBSetBits(BIT_9))                  //����Ĥ��        //Mengfr 20150831
//      #define JiaReMoClose    (mPORTBClearBits(BIT_9))                //����Ĥ�ر�        //Mengfr 20150831
 //***********************170704������������CNG*************************************************************//
 #define Mini_Money     10 //rg170606��С������
#define Mini_Gas     3   //rg170606��С������ 
#define Mini_Money1     10 //rg180118��С������
#define Mini_Money2     20 //rg180118��С������
#define Mini_Money3     30 //rg180118��С������ 
#define Mini_UP     30 //rg180118��С������ 
#define Mini_DO     5 //rg180118��С������ 
#define smallMini_Money     200 //rg181210 �ӿ���С������    
#define SMALL_Mini_UP   300    //rg181210
#define SMALL_Mini_DO   50     //rg181210   
float      smallMini_FD ;//�ӿ���С������� rg181210
        float       Mini_FD ;//��С������� rg180118     
     UINT8 SCS;        //1:�ϰ�����֤����  0���ϰ�δ��֤���� rg170531����
     volatile   UINT32 SP_tick;//rg170531����
    UINT8 SP;//1:���� 0:����  rg170531����
    UINT8 WKJQ; //1���п� 0���޿�   rg170531�޿�����
    UINT8 dkpd; //����״̬          rg170531�޿�����
    UINT8 cure_JQ_card[10];//�������� rg170531�޿�����
        UINT8 CPH[12];      //rg170607 ������Ϣ���ƺ�
    UINT8 CPH_IN[12];      //rg170619 
    UINT8 Cp_flag;      //rg170619
    UINT8 cure_yz_card[10];//rg170621  �忨��������
    float Zttz_Time;//rg170605ֹͣ/ ��ͣ
     UINT8  CP_PRINT[12];//rg170607 ������Ϣ���ƺ�
     UINT32 KY_PRINT;//rg170607 ������Ϣ���ƺ�
     UINT8 revtime[10];//rg170724
//************************************************************************************// 
     #define JiaReMoCtlInit      (mPORTGSetPinsDigitalOut(BIT_8))  //����Ĥ�������ų�ʼ�� //RG160824
#define JiaReMoReadInit        (mPORTGSetPinsDigitalIn(BIT_7))                     //RG160824
#define JiaReMoOpen     (mPORTGSetBits(BIT_8))                  //����Ĥ��        //RG160824
#define JiaReMoClose    (mPORTGClearBits(BIT_8))                //����Ĥ�ر�        //RG160824  

   float WDKZ; //RG160824 
    UINT8 wk_cont; //RG160824 
    float WDBJ;             //RG161103  �¶ȱ���
    UINT8 sdk_cont;          //RG161103 
    UINT8 jr_power;          //1:�ֶ��� 2���ֶ��ر�  0���Զ� rg161017
//************************************************************************************//     
     UINT8 DUISHI; //���̰��ʱ rg170110
    UINT8 zhutime[6]; //rg170110
    UINT8 Err_ZhuTime, Err_JPTime; //rg170110
    UINT8 DSCG; //rg170110
    UINT8 KEY_CAR_PASS[8];
    UINT8 VER_MasterBoard; //���ذ����汾����ΧΪ0~99
    BOOL HUAIKUAI;
    BOOL hk_disp;//rg190510
    UINT8 led;
    UINT8 global_ic_card_info[210];//150120//150813//RG160907
    UINT8 card_info_len;
    UINT8 PRINT_SET;
    UINT8 ZK_POWER;
    UINT8 HQ_PRINT;  //0-����  1-��ֹ
    UINT8 gass_class;//���鿨�������� 1-���ܼ���  0-�ܼ���
    UINT8 ReadTn;
    UINT8 Pr_gr;                    //�۸�ȼ�
//    UINT8       Discount[2];        //�ۿ�
    float   temperature;    //�¶�ֵ    //Mengfr 20150831
    float       Discounf;
    UINT8       Discount_validity[4];//�ۿ���Ч��
     UINT32 ID_PRINT;
     float  DJ_PRINT;
     float  QL_PRINT;
     float  JE_PRINT;
     float  HQL_PRINT;
     UINT16 PR_YGH;//RG160907
     UINT8  RQ_PRINT[6];
     UINT8  CN_PRINT[10];
     UINT32 QX_RECORD;//rg160726
     UINT8  QX_OVER;    //rg160726
     float Every_add_Gas[50]; //��������ͣ��������¼�ֶ� //wzw150518
     UINT8 Add_Gas_CS;     ////wzw150518
     float  Pre_vol_add;
     UINT8  Sign_Name[3];//rg160907  �ϰ��˱��
     UINT8           read_keyv_CS;
     UINT8        Is_debuggas_Read;
    BOOL            b_keyv;
    BOOL            b_mainui;
    BOOL            b_fixmop;
    BOOL            b_fixnop;  //b_fixop
    INT8            b_shift_ok;
    UINT8           keyv;
    UINT8           sys_info_page;
    UINT8           sys_time[6];
    //UINT16          cur_rec_info_addr;
    //UINT16          cur_shift_info_addr;
    UINT8    Sys_Rec_Err[10];     //���ü�¼����
    UINT8     Rec_inxex;
     UINT8    Setsys_Rec_card[10];     //���ü�¼����
    UINT8          cur_shiftid;
    UINT8           cure_shift_card[10];
    UINT32          cur_max_recid;
//    UINT32          cur_max_resetid;//rg160622
    UINT8          MAX_dubug_recid_num;  //150730
    UINT8          IS_GUANLI_CARD_GAS;  //150730
    UINT32         cur_max_recid0;
    UINT32          cur_max_shiftid;
    UINT32          cur_max_paraid;
    volatile   BOOL     _gas_run_flag;
    volatile   UINT8    _ui_module_id;
    volatile   UINT8    _ui_paras_set_id;
    volatile   UINT8    _ui_cs_set_id;//rg170712
    volatile   UINT8    _ui_pricex_set_id;
    volatile   UINT8    _ui_qry_cardinfo_id;

    volatile   UINT8    _ui_sys_set_id;
    volatile   UINT8    _ui_precool_set_id;
    volatile   UINT8    _ui_syschk_set_id;

    volatile   UINT32   gTick;
    volatile   UINT32   _10ms_tick_;
    volatile   UINT32   _10ms_tick2_;
    volatile   UINT32    _sys_tick_;//8->32
    volatile   UINT32   _sys_tick_cnt_;

     volatile   UINT32 Debugasing_rstsave_Tick;  //150801

    volatile   UINT32   heareat_time;/////wang
    volatile   UINT32   CanGasTime;
    volatile   UINT32 IsGasAdd_tick;
    volatile   UINT32 Disp_AllErr_tick;
    float         cur_price;
    float         cur_card_money;
    float         cur_init_lngnum; //��ʼ����
/**--------------  Һ�������Ʋ���   ------------*/
    float         cur_lngnum;      //����
    float         cur_lngrate;     //����
    float         cur_lngtemp;     //�¶�
    float         cur_lnggain;     //����
    float         cur_lngdensty;   //�ܶ�
    
    float         cur_calnum;      //����
    float         cur_calsum;      //����


    float         cur_init_cngnum; //��ʼ����
    float         cur_cngnum;      //����
    float         cur_cngrate;     //����
    float         cur_cngtemp;     //�¶�
    float         cur_cngdensty;   //�ܶ�
    float         cur_cnggain;     //����
    float         cur_calnum_c;      //����
    float         cur_calsum_c;      //����
    float         cur_press;
    float         cur_fixm;
    float         cur_fixn;
       UINT8   FLASH_W_BUF[512];
    UINT8   FLASH_R_BUF[512];
//   
//    BOOL PRECOOL_FALG_CH;   // SS20190102 Ԥ��ɹ���־
         
    volatile  BOOL           _b_run_lng_flag;
    volatile  BOOL           _b_running_flag;
    volatile  BOOL           _b_init_ok;
    volatile  BOOL           _b_quan_err;
    volatile  BOOL           _b_quota_err;
    volatile  BOOL           _b_state_err;
  volatile   UINT32 KEY422_ERRBYTE_Tick;  //150819
volatile  UINT8            _b_have_cont;
    volatile  BOOL            _b_cz_card;//tj
    volatile  BOOL            _b_have_card;
    volatile  BOOL           _b_precool_lng_flag;
#if  __SIMU_DEBUG_
    volatile  UINT16         _simu_iic_step;
    volatile  UINT16         _simu_tick;
    volatile  float         _simu_lngnum;
    volatile  BOOL           _b_simu_lng;

    #endif

     void backdisp(void);
    void sys_init(void);
    void sys_interface_init(void);
    void sys_verion_output(void);
    void sys_uart_init(unsigned char ch, unsigned long baudrate);
    //void Uart_Send_Data(UART_MODULE ch, UINT8 *buffer, UINT32 size);
    float sys_get_float(float vfdt);
    unsigned long hex2bcd(unsigned long sdt);
    BOOL checkdate(unsigned char * str);
    BOOL checktime(unsigned char * str);
    void delay_ms(UINT32 ms);

void omodule_key_test(void);
void omodule_modbus_ui(void);
void omodule_memory_test(void);
void omodule_print_test(void);
void omodule_vctrl_ui(void);
void omodule_pressure_test(void);

UINT32 get_max_rec_id(void);
void oset_shift_join(void);
void oset_shift_Exit(void);
void oset_shift_exit(void);
void oset_precool_temp(void);
void oset_precool_gain(void);
void oset_precool_delay(void);
void oset_lngEndR(void);
void oset_lngEndP(void);
void osysparas_set_ui_switch(void);
extern UINT8 Current();

extern void show_sys_recod(_rec_shift_info info);
/////////////////////rg160726/////////////////////////////////////
BOOL Sava_Sys_Runtime(UINT32 new_runtime);
BOOL Save_Qx_Runtime(UINT32 new_runtime);//RG160726
UINT32 Get_Qx_Runtime(void);
UINT32 Get_Sys_Runtime(void);
BOOL Save_QxSet_Bit(UINT8 new_bit);//RG160726

void oset_MinorCycleSucced_delay(void); //Mengfr 20161111
void oset_MajorCycleSucced_delay(void); //Mengfr 20161111
/////////////////////////////////////////////////////////////////////
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_DEF_H */

