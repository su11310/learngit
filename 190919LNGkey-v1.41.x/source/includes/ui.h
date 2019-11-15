/* 
 * File:   ui.h
 * Author: dell
 *
 * Created on 2014?1?14?, ??10:16
 */

#ifndef UI_H
#define	UI_H

#ifdef	__cplusplus
extern "C" {
#endif


    enum __eTIPS_ID_
    {
        _eMSG_SET_OK_,
        _eMSG_SET_FAIL_,
        _eMSG_INPUT_PSW_,
        _eMSG_INPUT_TIME_,
        _eMSG_DATE_,
        _eMSG_TIME_,
        _eMSG_INPUT_ERR_,
        _eMSG_TEST_END_,
    };

    void oui_main_ui(void);
    void oui_main_ui_set(void);
    void oui_main_ui_setPSW(void);
    void oui_mainui_fresh(void);
    void oui_main_ui_select(void);
    void oui_main_ui_qry(void);
    void oqry_rec(void);
    void oqry_liushuirec(void);//*******
    void oqry_Debug_liushuirec(void);//*******150730
    void oqry_searchliushuirec(void);//************
    void oqry_liushui_typerec(void);//***********
    void oqry_shift(void);//班组总累计
 //   void oqry_xz(void);
    void oqry_todayshift(void);//班组今天累计
    void oqry_shift_iofo(void);//****班组信息 不同于班组加气记录
    void oqry_rec_ex(void);
    void oqry_system(void);
//    void oqry_switch(void);
    void oqry_switch(UINT8 key);
    void oqry_cardinfo(void);
    void oqry_downpass();
    void oqry_card_Recharge();
    UINT8 Card_Solution();
    UINT8 Card_Ash();
    float getatof(UINT8 *p);
    UINT8 getatoi(UINT8 *p);
    void oset_system(void);
    void oset_price(void);
    void oset_price2(void);
    void oset_price3(void);
    void oset_price4(void);
    void oset_price5(void);
    void oset_price6(void);
    void oset_price7(void);
    void oset_price8(void);
    void oset_price9(void);
    void oset_price10(void);
    void opricex_set_ui_switch(void);
    void oset_sysset_power(void);
    void oset_zkset(void);//折扣开关
    void oset_systime(void);
    void oset_machine_id(void);
    void oset_syschk_ma1(void);
    void oset_syschk_ma2(void);
    void oset_syschk_ma3(void);
    void oset_Pressure_ma(void);
    void oset_tj_ma(void);
    void oset_precool_ma2(void);
    void oset_precool_ma1(void);
    void oset_sys_ma3(void);
    void oset_sys_ma2(void);
    void oset_sys_ma1(void);
    void oset_team_ma(void);
    void oprecool_set_ui_switch(void);
    void osyschk_set_ui_switch(void);
    void osys_set_ui_switch(void);
    void oset_system_ui(void);
void oset_sysset_aerad(void);
void oset_sysset_print(void);
void oset_team_modi(void);
void oset_team_cardmm(void);
void oset_team_add(void);
void oset_team_del(void);
void oset_tj_minif(void);
void oset_tj_minim(void);
void oset_sysset_safetypre(void);
void oset_sysset_ReferVoltage(void);    //Mengfr 20150717
void oset_sysset_precur(void);
void oset_sysset_prezero(void);
void oset_Density_up(void);
void oset_Density_down(void);
void oset_arcewait(void);
void oset_tmpeAdd(void);
//void oset_sysbuf(void);
//void omodule_ic_test(void);
void omodule_ic_put0(void);
void omodule_ic_put1(void);
void omodule_disp_test(void);
void omodule_tx_test(void);
void omodule_clock_test(void);
void oset_keysound(void);
void oset_statonno(void);
void oset_relaytime(void);
void oset_curflow(void);
void oui_main_xz_set(void);
void osel_precoo(void);
void oset_sysdate(void);
UINT8 chk_card();
void oset_getclassxx(void);
    BOOL oset_init_str_chk(void);
UINT8 para_sav(UINT8 *pa,float float_q,float float_h);
void oset_clrsav(void);
BOOL systemclr(void);
BOOL Clr_debudjilu_die(void);  //150730
void systemclr_psw(void);
void Debud_record_clrAll_psw(void);   //150730
void SET_HARD_VER(void);   //150906
void oset_simrec();
void omodule_modbus_ser_ui(void);
    void oui_precool_ui(void);
    void oui_precool_value_ui(float g,float t,float f);
    UINT8 cursor_x, cursor_y;

  extern   void oqry_flow_l(void);
  extern   void oqry_flow_g(void);
  void oqry_get_jlerr(void);   //错误数据获取
  void oset_gassset(void);//班组卡加气开关
  void oset_Ls_set_ma(void);
  void oset_glbh(void);
  void oqry_reset_disp(UINT32 id, BOOL bDisp);   //rg160622
  void oui_main_ui_qry_soe(void);
  void oset_lsyspd(void);//RG160704
  void oset_qxsz(void);//RG160726
  void in_xlh(void);//rg160726
  BOOL oset_sysdatatime(void);//rg170110
  void oqry_sw_state(void);//rg161220
  void oqry_key_sw(void);//rg161220
  void oqry_zhu_sw(void);//rg161220
   void omodule_sp_up(void);//rg170531锁屏
  void omodule_sp_sw(void);//rg170531锁屏
 // void oset_sysset_tzzt(void);//rg170605停止/ 暂停
  void oset_zttzset(void);//rg170605停止/ 暂停
  //BOOL oqry_Leaktotal(LEAKMSG *ptr);  //Mengfr 20170616
 // void oset_Leak_reset(void); //Mengfr 20170616
//void oset_Leak_Err(void);   //Mengfr 20170616
//void oqry_Leaktotal_disp(void); //Mengfr 20170616
 UINT8 okeyinput_get_cp(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw );//rg170619 输入车牌号
  BOOL Sys_Input_Cp();//rg170619 输入车牌号
  //******************rg170712 温度控制*************************************************************//
   void oset_wdcsset(void);//温度参数//rg160824
void oset_wdbjset(void);//温度报警//rg161103
  void oqry_temp();       //rg161017
void oset_jrset(void);//加热开关rg161017
void oset_Ls_set_ma2(void);
void oprecool_cs_ui_switch(void);
void vctrl_test_psw(void);//rg171229
void oset_mini_set(void);//最小加气金额  rg180118
void oset_zxjqe(void);//rg180130 最小加气金额
void oset_hqset(void);//回气量打印开关 rg180131
void oset_fdelay(void);	//rg170809 第5阀延时
void oset_djxs(void);//单价显示选择//RG180327
 void oset_smallzxjqe(void);//rg181210 子卡最小加气金额
     void oset_qtotal(void);//rg181129
void oset_stotal(void);//rg181129
void strtoint(UINT8 *str,UINT8 *des,UINT8 len);//rg181129
UINT8 okeyinput_getstrbl(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw );//rg181129
void oset_curflowbz(void);//rg181129
void oqry_lsh_set(void);//rg190108
//*******************************************************************************//
#ifdef	__cplusplus
}
#endif

#endif	/* UI_H */

