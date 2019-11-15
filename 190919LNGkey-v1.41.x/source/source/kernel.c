/*
 * File:   kernel.c
 * Author: jereh
 *
 * Created on 2014_01_13
 */
#include "../includes/global_def.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void oGet_Sta_Cardpsw(void);
void omodule_ui_switch(void);
void olng_operate_fix_ui(void);
void omodule_modbus_flowrate_test(void);
void omodule_modbus_total_test(void);
void omodule_modbus_temp_test(void);
void omodule_modbus_gain_test(void);
void omodule_modbus_densty_test(void);
void omodule_modbus_clr_test(void);
void omodule_modbus_switch_test(void);
void omodule_auto_buff_test(void);

void omodule_vctrl_test_init(void);
void omodule_vctrl_test_end(void);

void omodule_vctrlopen_test(void);
void omodule_vctrlclose_test(void);
void omodule_pump_test(void);
void omodule_precool_test(void);

const EVENT_NODE_LNG   LNG_OPRTATE[]  = {
 //   { _KEY_STOP_EV_,        State_LngOperate,      ACTION_LNG_RUN_STOP ,  (pFunc)olng_operate_stop } ,
    { _KEY_EXIT_EV_,        State_MainUI,            ACTION_NOP ,  (pFunc)oui_main_ui},//无需检查退出
    { _KEY_VIRTUAL_EV_,     State_LngOperate,         ACTION_NOP ,        (pFunc)gas_finish },//定量加气的结账，和非定量加气的出错情况的结账
    { _KEY_ADDGAS_EXIT,     State_LngOperate,         ACTION_NOP ,  (pFunc)olng_operate_Isadd},
    {_KEY_VIRTUAL_2_EV_,    State_LngOperate ,      ACTION_LNG_Operate,   (pFunc)olng_LNG_Operate } ,//
  // { _KEY_VIRTUAL_2_EV_, State_LngOperate,     ACTION_NOP ,  (pFunc)olng_system_err_stop},
    {_KEY_VIRTUAL_3_EV_,     State_LngOperate,    ACTION_FIX_M ,          (pFunc)olng_start_act },
  //  { _EVENT_TRUE,        State_LngOperate,         ACTION_LNG_RUNNING, (pFunc)olng_operate_running } ,
};

/*----------------------------        待机界面执行动作-------------------------------------*/
const EVENT_NODE_LNG SYS_MAINUI[]  = {
  {_KEY_GAS_EV_,       State_LngOperate ,      ACTION_LNG_Operate,   (pFunc)olng_LNG_Operate } ,
  {_KEY_QRY_EV_,       State_Select ,          ACTION_NOP,         (pFunc)oui_main_ui_select } ,
  {_KEY_SET_EV_,       State_MainUI ,             ACTION_NOP,         (pFunc)oui_main_ui_setPSW } ,//pFun里指定下状态State_Set
  //{_KEY_UP_EV_,        State_LngOperate_fix ,  ACTION_NOP,         (pFunc)olng_operate_fix_ui } ,
 //qaz {_EVENT_TRUE,        State_MainUI,           ACTION_NOP,         (pFunc)olng_operate_main_ui},

//  {_KEY_5_EV_,          State_MainUI ,           ACTION_NOP,         (pFunc)osel_offwork },//下班
//  {_KEY_3_EV_,         State_MainUI,           ACTION_NOP ,     (pFunc)oqry_cardinfo } ,
//  {_KEY_7_EV_,         State_MainUI,             ACTION_NOP ,     (pFunc)oqry_downpass } ,
 // {_KEY_8_EV_,         State_MainUI,             ACTION_NOP ,     (pFunc)omodule_ic_put0 } ,
//  {_KEY_9_EV_,         State_MainUI,             ACTION_NOP ,     (pFunc)omodule_ic_put1 } ,
 // {_KEY_3_EV_,         State_MainUI,           ACTION_NOP,         (pFunc)buzzer_power_down_sound}, //外站卡验证测试，过后删除  wang
 { _KEY_STOP_EV_, State_MainUI, ACTION_NOP, (pFunc) oprint_qry_to_rec},//RG170620
  { _KEY_SW_EV_, State_MainUI, ACTION_NOP, (pFunc) omodule_sp_up},//rg170531锁屏
  { _KEY_1_EV_,          State_MainUI,           ACTION_NOP ,     (pFunc)DisplayClear},     //QingLing
  { _KEY_EXIT_EV_,      State_MainUI,            ACTION_NOP ,        (pFunc)oui_main_ui },//WANG
  { _KEY_VIRTUAL_EV_,   State_MainUI,           ACTION_NOP ,     (pFunc)oui_main_ui},
     { _EVENT_TRUE,   State_MainUI,           ACTION_LOGIN ,     (pFunc)Get_Car_Info},
};
/*-------------------------------------登陆函数--------------------------------------------*/
/* authoer: xiaolin  time 2013-3-14  18:00 *///登陆
const EVENT_NODE_LNG SYS_LOGINUI[]  = {
  {_KEY_LOGIN_HAVECARD,      State_log_in ,         ACTION_NOP,     (pFunc)sign_has_card } ,
  {_KEY_LOGIN_NOCARD,        State_log_in ,         ACTION_NOP,     (pFunc)sign_nocard } ,
  {_KEY_LOGIN_ERROE,         State_log_in,          ACTION_NOP,     (pFunc)sign_error},
  {_KEY_LOGIN_SUCCESS,       State_MainUI ,         ACTION_NOP,     (pFunc)oui_main_ui } ,
    { _KEY_COMBINATION_UP_DW, State_log_in, ACTION_NOP, (pFunc) oGet_Sta_Cardpsw},//ss190813   获取秘钥
  { _EVENT_TRUE,             State_log_in   ,       ACTION_LOGIN,   (pFunc)sign_startup } ,
};
/*******************************************************************************************/
/*------------------------------------系统选择---------------------------------------------*/
const EVENT_NODE_LNG SYS_SELECT[]  = {
  //{_KEY_1_EV_,          State_precool ,          ACTION_NOP,         (pFunc)olng_precool_start },
  {_KEY_1_EV_,          State_MainUI ,          ACTION_NOP,          (pFunc)omodule_precool_test },//预冷后为待机状态
  {_KEY_2_EV_,          State_Qry,               ACTION_NOP,         (pFunc)oui_main_ui_qry },
  {_KEY_3_EV_,          State_LngOperate,    ACTION_FIX_M ,          (pFunc)olng_start_act },
  {_KEY_4_EV_,          State_LngOperate,    ACTION_FIX_V ,          (pFunc)olng_start_act },
  { _KEY_5_EV_,	        State_soe,           ACTION_NOP ,         (pFunc)oui_main_ui_qry_soe } ,////rg160627
  { _KEY_6_EV_,	        State_MainUI,           ACTION_NOP ,         (pFunc)osel_offwork } ,//下班
  { _KEY_7_EV_,	        State_MainUI,           ACTION_NOP ,         (pFunc) oset_team_cardmm } ,//修改卡密码
//  {_KEY_5_EV_,          State_MainUI ,           ACTION_NOP,         (pFunc)osel_offwork },//下班
  { _KEY_EXIT_EV_,      State_MainUI,            ACTION_NOP ,        (pFunc)oui_main_ui },
  { _KEY_VIRTUAL_EV_,   State_Select,            ACTION_NOP ,        (pFunc)oui_main_ui_select},
//qaz  {_KEY_DENGLU_EV_,     State_log_in,            ACTION_LOGIN ,      (pFunc)sign_startup},
 // {_KEY_PRECOOL_SUCCESS,State_MainUI,            ACTION_NOP,         (pFunc)olng_precool_success }
};
/*-------------------------------------异常-----------------------------------------------*/
const EVENT_NODE_LNG   SYS_SOE[]  = { 
  { _KEY_1_EV_,         State_soe,    ACTION_NOP ,     (pFunc)oqry_soerec } ,//记录查询主界面
  { _KEY_2_EV_,         State_soe,           ACTION_NOP ,     (pFunc)oqry_key_reset } ,//键盘复位信息
  {_KEY_3_EV_,         State_soe,           ACTION_NOP ,     (pFunc)oqry_reset_info },
 // {_KEY_4_EV_,         State_soe,           ACTION_NOP ,     (pFunc)in_xlh },	//rg160726
// { _KEY_7_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_key_reset } ,//键盘复位查询rg160623
// { _KEY_8_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_reset_info } ,//主板复位查询rg160622
 { _KEY_EXIT_EV_,      State_Select,        ACTION_NOP ,     (pFunc)oui_main_ui_select } ,
  { _KEY_VIRTUAL_EV_,   State_soe,           ACTION_NOP ,     (pFunc)oui_main_ui_qry_soe},
};
//rg161220
const EVENT_NODE_LNG   Sys_Sw_state[]  = {
	{ _KEY_1_EV_, State_Sw_state, ACTION_NOP, (pFunc) oqry_key_sw}, ////rg161220
	{ _KEY_2_EV_, State_Sw_state, ACTION_NOP, (pFunc) oqry_zhu_sw}, ////rg161220
	{ _KEY_EXIT_EV_, State_Select, ACTION_NOP, (pFunc) oui_main_ui_select}, //rg161220
	{ _KEY_VIRTUAL_EV_, State_Sw_state, ACTION_NOP, (pFunc) oqry_sw_state}, //rg161220	  
};

const EVENT_NODE_LNG   Sys_Lsh_state[]  = {
    { _KEY_1_EV_,	State_Set_lsh   , ACTION_NOP ,  (pFunc)oset_curflow} ,//rg181129
    { _KEY_2_EV_,	State_Set_lsh   , ACTION_NOP ,  (pFunc)oset_qtotal} ,//rg181129
      { _KEY_3_EV_,	State_Set_lsh   , ACTION_NOP ,  (pFunc)   oset_curflowbz} ,//rg181129
//	{ _KEY_1_EV_, State_Sw_state, ACTION_NOP, (pFunc) oqry_key_sw}, ////rg190108
//	{ _KEY_2_EV_, State_Sw_state, ACTION_NOP, (pFunc) oqry_zhu_sw}, ////rg190108
//	{ _KEY_EXIT_EV_, State_Select, ACTION_NOP, (pFunc) oui_main_ui_select}, //rg190108
	{ _KEY_VIRTUAL_EV_, State_Set_lsh, ACTION_NOP, (pFunc) oqry_lsh_set}, //rg190108  
    { _KEY_EXIT_EV_,	State_Set         , ACTION_PARAS_SET_END ,  (pFunc)oui_main_ui_set } ,
};
/*-------------------------------------查询-----------------------------------------------*/
const EVENT_NODE_LNG   SYS_QRY[]  = { 
  { _KEY_1_EV_,         State_liushuiQry,    ACTION_NOP ,     (pFunc)oqry_rec } ,//记录查询主界面
  { _KEY_2_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_shift_iofo } ,//班组信息
  {_KEY_3_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_cardinfo },
  { _KEY_4_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_system } ,      // 系统信息
 { _KEY_5_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_flow_l } ,
 { _KEY_6_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_flow_g } ,
 { _KEY_0_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_get_jlerr } ,//错误数据获取
  { _KEY_7_EV_,         State_Sw_state,           ACTION_NOP ,     (pFunc)oqry_sw_state } ,//rg161220 查询拨码状态
  { _KEY_8_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_temp } ,//rg161017
 // { _KEY_7_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_key_reset } ,//键盘复位查询rg160623
// { _KEY_8_EV_,         State_Qry,           ACTION_NOP ,     (pFunc)oqry_reset_info } ,//主板复位查询rg160622
 { _KEY_EXIT_EV_,      State_Select,        ACTION_NOP ,     (pFunc)oui_main_ui_select } ,
  { _KEY_VIRTUAL_EV_,   State_Qry,           ACTION_NOP ,     (pFunc)oui_main_ui_qry},
};
const EVENT_NODE_LNG   SYS_liushuiQRY_SP[]  = {                //ss190201
    { _KEY_1_EV_,         State_liushuiQry_SP,      ACTION_NOP,     (pFunc)GasRecordQuery } ,                  //正常记录顺序
    { _KEY_2_EV_,         State_liushuiQry_SP,      ACTION_NOP,     (pFunc)GasRecordQueryIndex } ,            //正常记录检索
    { _KEY_3_EV_,         State_liushuiQry_SP,          ACTION_NOP ,     (pFunc)GasRecordQuery_SP } ,          //异常记录顺序
    { _KEY_4_EV_,         State_liushuiQry_SP,          ACTION_NOP ,     (pFunc)GasRecordQueryIndex_SP } ,     //异常记录检索
    { _KEY_EXIT_EV_,      State_liushuiQry,                 ACTION_NOP ,     (pFunc)oqry_rec } ,
    { _KEY_VIRTUAL_EV_,   State_liushuiQry_SP,          ACTION_NOP ,     (pFunc)oqry_GasRecordQuery}, 
};
/*------------------------------------记录查询主界面-------------------------------------*/
const EVENT_NODE_LNG   SYS_liushuiQRY[]  = { 
  { _KEY_1_EV_,         State_liushuiQry,      ACTION_NOP,     (pFunc)oqry_liushuirec } ,//顺序流水
  { _KEY_2_EV_,         State_liushuiQry,      ACTION_NOP,     (pFunc)oqry_searchliushuirec } ,//检索***
  { _KEY_3_EV_,         State_liushuiQry,          ACTION_NOP ,     (pFunc)oqry_shift } ,//班组总累计*****
  { _KEY_4_EV_,         State_liushuiQry,          ACTION_NOP ,     (pFunc)oqry_todayshift } ,//班组当日累计
  { _KEY_5_EV_,         State_liushuiQry,      ACTION_NOP,     (pFunc)oqry_Debug_liushuirec } ,//调试流水
    { _KEY_7_EV_,State_liushuiQry_SP, ACTION_NOP,  (pFunc)oqry_GasRecordQuery } ,//   ss190201 隐藏功能，可以查看键盘板加气记录信息
 //{ _KEY_6_EV_,State_liushuiQry, ACTION_NOP,  (pFunc)oqry_pararec},//RG190110
  { _KEY_EXIT_EV_,      State_Qry,                 ACTION_NOP ,     (pFunc)oui_main_ui_qry } ,
  { _KEY_VIRTUAL_EV_,   State_liushuiQry,          ACTION_NOP ,     (pFunc)oqry_rec},
};

const EVENT_NODE_LNG   SYS_SET[]  = { /*设置*/
    //  { _KEY_1_EV_,	State_team_Set,     ACTION_NOP ,           (pFunc)oset_team_ma } ,
      {  _KEY_1_EV_,	State_sys_sysset,   ACTION_SYS_SET_INIT ,  (pFunc)osys_set_ui_switch } , //
      {_KEY_2_EV_,      State_module_test,  ACTION_MODULE_INIT,     (pFunc)omodule_ui_switch } ,
 //     { _KEY_3_EV_,	State_Set,          ACTION_NOP,             (pFunc)oset_lngEndR } ,
      { _KEY_3_EV_,     State_ls_Set,          ACTION_CS_SET_INIT,             (pFunc)oprecool_cs_ui_switch } ,//RG160601//RG170712
      { _KEY_4_EV_,     State_paras_set  ,  ACTION_PARAS_SET_INIT , (pFunc)oprecool_set_ui_switch } ,//
      { _KEY_5_EV_,     State_Pressure_set, ACTION_NOP,             (pFunc)oset_Pressure_ma } ,      
      {_KEY_6_EV_,      State_Set,          ACTION_NOP,     (pFunc)oGet_Sta_Cardpsw } ,
      {_KEY_7_EV_,      State_Set,          ACTION_NOP,     (pFunc)in_xlh } ,//rg160726
      { _KEY_EXIT_EV_,	State_MainUI,       ACTION_NOP,             (pFunc)oui_main_ui } ,//?
      {_KEY_VIRTUAL_EV_,State_Set,          ACTION_NOP,             (pFunc)oui_main_ui_set},
};
/*----------------------------------------预冷参数设置------------------------------------*/
const EVENT_NODE_LNG   _SYS_PARAS_SET[]  = { /*预冷参数设置*/
    { _KEY_1_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_precool_gain } ,
    { _KEY_2_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_precool_temp } ,
    { _KEY_3_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_Density_up } ,
   // 
     { _KEY_4_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_tmpeAdd } ,//oset_lngEndP
    { _KEY_5_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_precool_delay } ,
   { _KEY_6_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_arcewait } ,//oset_lngEndP
   { _KEY_7_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_MinorCycleSucced_delay} ,//小循环成功等待//Mengfr 20161111
   { _KEY_8_EV_,	State_paras_set   , ACTION_NOP ,  (pFunc)oset_MajorCycleSucced_delay} ,//大循环成功等待//Mengfr 20161111
    { _KEY_UP_EV_,	State_paras_set   , ACTION_PARAS_SET_SWITCHUP ,  (pFunc)oprecool_set_ui_switch } ,
    { _KEY_SW_EV_,	State_paras_set   , ACTION_PARAS_SET_SWITCH ,  (pFunc)oprecool_set_ui_switch } ,
    { _KEY_EXIT_EV_,	State_Set         , ACTION_PARAS_SET_END ,  (pFunc)oui_main_ui_set } ,

    {_KEY_VIRTUAL_EV_,  State_paras_set   , ACTION_NOP ,  (pFunc)oprecool_set_ui_switch},
};
/*----------------------------------------班组设置----------------------------------------*/
const EVENT_NODE_LNG   team_SET[]  = { /*班组设置*/
    { _KEY_1_EV_,	State_team_Set, ACTION_NOP ,  (pFunc)oset_team_modi } ,
//    { _KEY_2_EV_,	State_team_Set, ACTION_NOP ,  (pFunc)oset_team_cardmm } ,
    { _KEY_2_EV_,	State_team_Set, ACTION_NOP ,  (pFunc)oset_team_add } ,
    { _KEY_3_EV_,	State_team_Set, ACTION_NOP ,  (pFunc)oset_team_del } ,
    { _KEY_EXIT_EV_,	State_Set,      ACTION_NOP ,  (pFunc)oui_main_ui_set } ,
    {_KEY_VIRTUAL_EV_,  State_team_Set, ACTION_NOP ,  (pFunc)oset_team_ma},
};
/*----------------------------------------系统设置---------------------------------------*/
const EVENT_NODE_LNG   SYSSET_SET[]  = { /*系统设置*/
//    { _KEY_1_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_price } ,
    { _KEY_1_EV_,	State_Set_pricex  ,  ACTION_PRICEX_SET_INIT , (pFunc)opricex_set_ui_switch } ,
    { _KEY_2_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_systime } ,
    { _KEY_3_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_sysdate } ,
//    { _KEY_4_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_sysset_print } ,
    { _KEY_4_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_sysset_power } ,
    { _KEY_5_EV_,	State_Set_lsh   , ACTION_NOP ,  (pFunc)oqry_lsh_set} ,//rg190108
    
    { _KEY_6_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_machine_id } ,
    { _KEY_7_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_system } ,
    { _KEY_8_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)systemclr_psw } ,
    { _KEY_9_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_keysound } ,//按键音
    { _KEY_0_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_statonno } ,//站号
    { _KEY_SET_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)Debud_record_clrAll_psw } ,
    // { _KEY_0_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_simrec } ,//存模拟流水
    { _KEY_POINT_EV_,	State_sys_sysset   , ACTION_NOP ,  (pFunc)oset_relaytime } ,//切阀延迟
    { _KEY_UP_EV_,	State_sys_sysset  , ACTION_SYS_SET_SWITCHUP ,  (pFunc)osys_set_ui_switch } ,
    { _KEY_SW_EV_,	State_sys_sysset   , ACTION_SYS_SET_SWITCH ,  (pFunc)osys_set_ui_switch } ,
    { _KEY_EXIT_EV_,	State_Set         , ACTION_SYS_SET_END ,  (pFunc)oui_main_ui_set } ,
    {_KEY_VIRTUAL_EV_,  State_sys_sysset   , ACTION_NOP ,  (pFunc)osys_set_ui_switch},
};
const EVENT_NODE_LNG   SYS_SETPOWER[]  = { /*开关设置*/
    { _KEY_1_EV_,	State_Set_power  ,  ACTION_NOP , (pFunc)oset_sysset_print } ,
    { _KEY_2_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_zkset } ,
    { _KEY_3_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_gassset } ,
    { _KEY_8_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_qxsz } ,//rg160726 rg190517
    { _KEY_4_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_jrset} , //rg161017
    { _KEY_5_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_sysset_wk} , //rg170531无卡加气
    { _KEY_6_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_hqset } ,//rg180131
    { _KEY_7_EV_,	State_Set_power   , ACTION_NOP ,  (pFunc)oset_djxs } ,//rg180327
     { _KEY_EXIT_EV_,	State_sys_sysset,      ACTION_NOP ,  (pFunc)osys_set_ui_switch } ,
    {_KEY_VIRTUAL_EV_,  State_Set_power, ACTION_NOP ,  (pFunc)oset_sysset_power },
};
const EVENT_NODE_LNG   SYS_ls_SET[]  = { /*流速设置*///RG160601
    { _KEY_1_EV_,	State_ls_Set  ,  ACTION_NOP , (pFunc)oset_lngEndR  } ,
    { _KEY_2_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_glbh } ,
    { _KEY_3_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_lsyspd } ,
    { _KEY_4_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_zttzset } , //rg170605停止/ 暂停
	{ _KEY_5_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_wdcsset } ,//rg161017
	{ _KEY_6_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_wdbjset } ,//rg161017
	{ _KEY_7_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_zxjqe } ,//rg180130
    #if  _F_ENABLE_ ==0
    { _KEY_8_EV_,	State_ls_Set  , ACTION_NOP ,  (pFunc)oset_smallzxjqe } ,//rg181210
    #endif
	#if  _F_ENABLE_  //rg170809 第5阀延时设置
	{ _KEY_8_EV_,	State_ls_Set   , ACTION_NOP ,  (pFunc)oset_fdelay } ,//rg170809 第5阀延时设置
	#endif
   { _KEY_UP_EV_,	State_ls_Set   , ACTION_CS_SET_SWITCHUP ,  (pFunc)oprecool_cs_ui_switch } ,
    { _KEY_SW_EV_,	State_ls_Set   , ACTION_CS_SET_SWITCH ,  (pFunc)oprecool_cs_ui_switch } ,
    { _KEY_EXIT_EV_,	State_Set,      ACTION_CS_SET_END ,  (pFunc)oui_main_ui_set } ,
    {_KEY_VIRTUAL_EV_,  State_ls_Set, ACTION_NOP ,  (pFunc)oprecool_cs_ui_switch  },
};

const EVENT_NODE_LNG   SYS_SETPRICEX[]  = { /*单价设置*/
    { _KEY_1_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price } ,
//    { _KEY_1_EV_,	State_Set_pricex  ,  ACTION_PRICEX_SET_INIT , (pFunc)opricex_set_ui_switch } ,
    { _KEY_2_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price2 } ,
    { _KEY_3_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price3 } ,
    { _KEY_4_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price4 } ,
    { _KEY_5_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price5} ,
    { _KEY_6_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price6 } ,
    { _KEY_7_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price7 } ,
    { _KEY_8_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price8 } ,
    { _KEY_9_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price9 } ,//按键音
    { _KEY_0_EV_,	State_Set_pricex   , ACTION_NOP ,  (pFunc)oset_price10 } ,//站号
    { _KEY_UP_EV_,	State_Set_pricex  , ACTION_PRICEX_SET_SWITCHUP ,  (pFunc)opricex_set_ui_switch } ,
    { _KEY_SW_EV_,	State_Set_pricex   , ACTION_PRICEX_SET_SWITCH ,  (pFunc)opricex_set_ui_switch } ,
    { _KEY_EXIT_EV_,	State_sys_sysset  , ACTION_PRICEX_SET_END ,  (pFunc)osys_set_ui_switch } ,
    {_KEY_VIRTUAL_EV_,  State_Set_pricex   , ACTION_NOP ,  (pFunc)opricex_set_ui_switch},
};

//---------------------------------------system测试-----------------------------------
const EVENT_NODE_LNG   _SYS_MODULE_TEST[]  = { //模块测试
    { _KEY_1_EV_,	State_module_modbus_test,   ACTION_NOP ,                (pFunc)omodule_modbus_ui },
    { _KEY_2_EV_,	State_module_vctrl_test,    ACTION_VCTRL_TEST_INIT ,    (pFunc)omodule_vctrl_ui },
    { _KEY_3_EV_,	State_module_test,          ACTION_NOP ,                (pFunc)omodule_print_test },
    { _KEY_4_EV_,	State_module_test,          ACTION_MODULE_SWITCH ,      (pFunc)omodule_key_test },
    { _KEY_5_EV_,	State_module_test,          ACTION_NOP ,                (pFunc)omodule_ic_test },
    { _KEY_6_EV_,	State_module_test,          ACTION_NOP ,                (pFunc)omodule_disp_test },
    { _KEY_7_EV_,	State_module_test,          ACTION_NOP ,               (pFunc)omodule_pressure_test },
    { _KEY_8_EV_,	State_module_test,          ACTION_NOP ,                (pFunc)omodule_memory_test },
    { _KEY_9_EV_,	State_module_test,          ACTION_NOP ,                (pFunc)omodule_tx_test },
    { _KEY_0_EV_,	State_module_test   ,       ACTION_NOP ,                (pFunc)SET_HARD_VER } ,
    { _KEY_SW_EV_,	State_module_test,          ACTION_MODULE_SWITCH ,      (pFunc)omodule_ui_switch },
    { _KEY_UP_EV_,	State_module_test,          ACTION_MODULE_SWITCHUP ,    (pFunc)omodule_ui_switch },
    { _KEY_EXIT_EV_,	State_Set,                  ACTION_MODULE_END ,         (pFunc)oui_main_ui_set },
    {_KEY_VIRTUAL_EV_,  State_module_test,          ACTION_NOP ,                (pFunc)omodule_ui_switch},
};
/*----------------------------------------压力设置-------------------------------------*/
const EVENT_NODE_LNG   Pressure_SET[]  = { /*压力设置*/
    { _KEY_1_EV_,	State_Pressure_set,      ACTION_NOP ,  (pFunc)oset_sysset_prezero } ,
    { _KEY_2_EV_,	State_Pressure_set,      ACTION_NOP ,  (pFunc)oset_sysset_precur } , //压力校正系数
    { _KEY_3_EV_,	State_Pressure_set,      ACTION_NOP ,  (pFunc)oset_sysset_safetypre } ,
    { _KEY_4_EV_,	State_Pressure_set,      ACTION_NOP ,  (pFunc)oset_sysset_ReferVoltage } ,  //Mengfr 20150717
    { _KEY_EXIT_EV_,	State_Set,               ACTION_NOP ,  (pFunc)oui_main_ui_set } ,
    {_KEY_VIRTUAL_EV_,  State_Pressure_set,      ACTION_NOP ,  (pFunc)oset_Pressure_ma},
};
//---------------------------------------流量计测试-----------------------------------
const EVENT_NODE_LNG   _SYS_MODULE_MODBUS_TEST[]  = { //流量计测试  //State_module_modbus_test //_KEY_SW_EV_  切换液相气相
    { _KEY_1_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_total_test } ,
    { _KEY_2_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_flowrate_test } ,
    { _KEY_3_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_temp_test } ,
    { _KEY_4_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_gain_test } ,
    { _KEY_5_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_densty_test } ,
    { _KEY_6_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_clr_test } ,
    { _KEY_8_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_auto_buff_test } ,
    { _KEY_SW_EV_,	State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_switch_test } ,
    { _KEY_EXIT_EV_,	State_module_test         , ACTION_NOP ,  (pFunc)omodule_ui_switch } ,
    {_KEY_VIRTUAL_EV_, State_module_modbus_test   , ACTION_NOP ,  (pFunc)omodule_modbus_ui},
};

//---------------------------------------电磁阀测试--------------------------------
const EVENT_NODE_LNG   _SYS_MODULE_VCTRL_TEST[]  = { //电磁阀测试  //State_module_vctrl_test
 //   { _KEY_1_EV_,	State_module_vctrl_test         , ACTION_NOP ,  (pFunc)omodule_vctrlopen_test } ,
	{ _KEY_1_EV_,	State_module_vctrl_test         , ACTION_NOP ,  (pFunc)vctrl_test_psw } ,//RG171229
    { _KEY_2_EV_,	State_module_vctrl_test         , ACTION_NOP ,  (pFunc)omodule_pump_test } ,
    { _KEY_3_EV_,	State_module_vctrl_test         , ACTION_NOP ,  (pFunc)omodule_precool_test } ,
    { _KEY_EXIT_EV_,	State_module_test         , ACTION_VCTRL_TEST_INIT ,  (pFunc)omodule_ui_switch } ,
    { _KEY_VIRTUAL_EV_,  State_module_vctrl_test   , ACTION_NOP ,  (pFunc)omodule_vctrl_ui},
};



/******************************************************************************************/
//_______________________        系统主状态       ________________________________________
const  STATE_DESC_LNG  RunMatrix[]  = {

   {State_MainUI,                   elements_of(SYS_MAINUI),              ( EVENT_NODE_LNG*)&SYS_MAINUI[0]},       //0
   {State_Qry,                      elements_of(SYS_QRY),                 ( EVENT_NODE_LNG*)&SYS_QRY[0]},//1
   {State_Set,                      elements_of(SYS_SET),                 ( EVENT_NODE_LNG*)&SYS_SET[0]},//2
   {State_Select,                   elements_of(SYS_SELECT),              ( EVENT_NODE_LNG*)&SYS_SELECT[0]},//3
   {State_paras_set,                elements_of(_SYS_PARAS_SET),          ( EVENT_NODE_LNG*)&_SYS_PARAS_SET[0]},//4
   {State_module_test,              elements_of(_SYS_MODULE_TEST),        ( EVENT_NODE_LNG*)&_SYS_MODULE_TEST[0]},//5
   {State_module_modbus_test,       elements_of(_SYS_MODULE_MODBUS_TEST), ( EVENT_NODE_LNG*)&_SYS_MODULE_MODBUS_TEST[0]},//6
  
   {State_module_vctrl_test,        elements_of(_SYS_MODULE_VCTRL_TEST) , ( EVENT_NODE_LNG*)&_SYS_MODULE_VCTRL_TEST[0]},//7
   {State_team_Set,                 elements_of(team_SET),                 ( EVENT_NODE_LNG*)&team_SET[0]},//8
   {State_sys_Set,                  elements_of(SYS_SET),                  ( EVENT_NODE_LNG*)&SYS_SET[0]},//9
   {State_sys_sysset,                  elements_of(SYSSET_SET),               ( EVENT_NODE_LNG*)&SYSSET_SET[0]},//10
  // {State_tj_Set,                   elements_of(TJ_SET),                   ( EVENT_NODE_LNG*)&TJ_SET[0]},//11
   {State_Pressure_set,             elements_of(Pressure_SET),             ( EVENT_NODE_LNG*)&Pressure_SET[0]},//12

 //qaz  {State_LngOperate_fix,    elements_of(LNG_OPRTATE_FIX),     (EVENT_NODE_LNG*)&LNG_OPRTATE_FIX[0]},//13
   {State_LngOperate ,       elements_of(LNG_OPRTATE),         (EVENT_NODE_LNG*)&LNG_OPRTATE[0]},//14
 //qaz  {State_LngOperate_end,    elements_of(LNG_OPRTATE_END),     (EVENT_NODE_LNG*)&LNG_OPRTATE_END[0]},//15
   {State_liushuiQry,        elements_of(SYS_liushuiQRY),      (EVENT_NODE_LNG*)&SYS_liushuiQRY[0]},//16****************
   {State_liushuiQry_SP,        elements_of(SYS_liushuiQRY_SP),      (EVENT_NODE_LNG*)&SYS_liushuiQRY_SP[0]},//16****************  异常加气记录查询
   {State_log_in ,           elements_of(SYS_LOGINUI),         (EVENT_NODE_LNG*)&SYS_LOGINUI[0]},//18  for frame structure of operation enevt TRUE
{State_Set_pricex ,           elements_of(SYS_SETPRICEX),         (EVENT_NODE_LNG*)&SYS_SETPRICEX[0]},
{State_Set_power ,           elements_of(SYS_SETPOWER),         (EVENT_NODE_LNG*)&SYS_SETPOWER[0]},
 {State_ls_Set,                      elements_of(SYS_ls_SET),                 ( EVENT_NODE_LNG*)&SYS_ls_SET[0]},//RG160601
 {State_soe,                      elements_of(SYS_SOE),                 ( EVENT_NODE_LNG*)&SYS_SOE[0]},
  {State_Sw_state,		elements_of(Sys_Sw_state),                 ( EVENT_NODE_LNG*)&Sys_Sw_state[0]},//rg161220
  {State_Set_lsh,       elements_of(Sys_Lsh_state),                 ( EVENT_NODE_LNG*)&Sys_Lsh_state[0]},//rg190108
//qaz {State_precool,           elements_of(LNG_PREE_COOL),       (EVENT_NODE_LNG*)&LNG_PREE_COOL[0]}, //19
};


UINT8 ostatemachine_keyscan(void)
{
 UINT8 tmpkey = 0;
 if(b_keyv == FALSE)
 {
   if((gTick > gScanKeyTick)/*&& (b_keyv == FALSE)*/&&(gTick > gReadKeyTick))
   {
       gScanKeyTick = gTick + 1;
       tmpkey = okey_scan_ex_io();

        if((tmpkey != KEY_NONE)/* && (b_keyv == FALSE)*//* &&(gTick > gReadKeyTick)*/&&(tmpkey!=KeyScan))
        {        Keyvol_num++;
                if(Keyvol_num>2)
                {
                    if(( tmpkey==Keyvol_PRE) &&(gTick < ok_ReadKeyTick))
                    {
                        keyv = tmpkey;
                        gReadKeyTick = gTick + 25;
                        ok_ReadKeyTick = 0;
                       KeyScan = keyv;
                        b_keyv = TRUE;
                       Keyvol_num = 0;
                        return ;
                    }
                    else
                    {

                       KeyScan = 0;
                        Keyvol_num = 0;
                         ok_ReadKeyTick = 0;
                        return ;
                    }
                }
                else if(Keyvol_num==1)
                {
                    Keyvol_PRE = tmpkey;
                    ok_ReadKeyTick =  gTick + 10;
                }


        }

         KeyScan = 0;
      return ;
  }
   if(b_keyv == FALSE)
   KeyScan = 0;
  return ;
}
}

UINT8 ostatemachine_getkey(void)
{
  delay_ms(200);  //不要删  20ms
  if((KeyScan != 0) &&(b_keyv == TRUE)) //b_keyv为假表示使用过，就不要响，不要返回了
    {
        if(cur_keysound) buzzer_key_soud();
        return KeyScan;
     }
  else
  {   
    KeyScan = 0;
    return KeyScan;
  }
}
/*
UINT8 osys_getkey_v(void)
{
    UINT8 tmpkey = 0;
    if(gTick > gScanKeyTick)
   {
        gScanKeyTick = gTick + 2;
       tmpkey = okey_scan_ex_io();
            if(tmpkey != KEY_NONE && (b_keyv == FALSE) )
            {
              //   gReadKeyTick = 0;
                 if(FALSE == b_keyv)
                     keyv = tmpkey;
                  {
                     if(( gTick <= gReadKeyTick)&&(Eeckey ==tmpkey)&&(tmpkey !=_KEY_SW_EV_))
                      {
                        return 0;
                      }
                     Eeckey = tmpkey;
                     gReadKeyTick = gTick + 35;
                     b_keyv = TRUE;
                     if(cur_keysound) buzzer_key_soud();
                     return keyv;

                 }
            }
            return 0;
    }
}
*/
BOOL osys_getkey(UINT keyv, UINT32 timeout)//rg160712
{
    UINT8    rdkey = 0;
    UINT32   cnt;
    UINT8	t1;
    cnt = gTick + timeout;

    while(1)
    {
        rdkey = ostatemachine_getkey();
        b_keyv = FALSE;
        if( rdkey == _KEY_EXIT_EV_)
        {
            //eVirtualKey = _KEY_VIRTUAL_EV_;
            return FALSE;
        }
        if( keyv == rdkey)
            return TRUE;
       
      //  if( timeout == 0 ) continue;
        if( gTick >= cnt )
        {
            return FALSE;
        }
        t1 = (UINT8)(((cnt -gTick)/100)%60);
        olcm_dispprintf(7,4,"%02d",t1);
        delay_ms(1);
    }
}
/* change by :xiaolin   time :2014-03-14  21:12*/
/* let break from the loop */
UINT8 osys_getkey_ex(void)
{
    UINT8    rdkey = 0;
    UINT32    timeout = 10;
    UINT32    cnt;
    while(1)
    {
        rdkey = ostatemachine_getkey();
        if(rdkey != 0) return rdkey;
       // delay_ms(1);
       // if(cnt++ > timeout)
            return 0;
    }
}

void ostatemachine_init(void)
{
      eCurRunState = State_log_in;//State_MainUI;
      b_fixmop = FALSE;
      b_fixnop = FALSE;
      b_keyv  = FALSE;
      _b_run_lng_flag = FALSE;
      _b_quota_err=TRUE;
      _b_quan_err=TRUE;
      _b_state_err=TRUE;
      _b_init_ok = FALSE;
      //_b_init_ok = TRUE;
      _gas_run_flag = FALSE;             //ss190218
      _b_precool_lng_flag = FALSE;
      _sys_tick_cnt_ = 0;
      eVirtualKey = 0;
      sys_info_page = 0;
      HUAIKUAI=FALSE;
      ostatemachine_getkey(); 
      b_keyv = FALSE;
      delay_ms(200);
    //  ostatemachine_getkey(); delay_ms(200);
    //  ostatemachine_getkey(); delay_ms(200);
    //  ostatemachine_getkey(); delay_ms(200);
     
      //odisp_cal(cur_lngnum, TRUE);
      if( oset_system_init_chk() == TRUE)
      {
            _b_init_ok = TRUE;
           

      }
      else
      {
          _b_init_ok = FALSE;
          odisp_p();
      }
   
}

void ostatemachine_action(unsigned char act)
{
  switch(act)
  {
    case    ACTION_RETURN:
            break;
    case    ACTION_MODULE_INIT:
          _ui_module_id = 1;
          break;
    case    ACTION_MODULE_SWITCH:
          _ui_module_id++;
          if(_ui_module_id >=4)
          {
               _ui_module_id = 1;
          }
          break;
   case    ACTION_MODULE_SWITCHUP:
       if(_ui_module_id ==0)
           _ui_module_id=3;
       else
         _ui_module_id--;
          break;
    case    ACTION_MODULE_END:
          _ui_module_id = 0;
          break;

    case    ACTION_PARAS_SET_INIT:
          _ui_paras_set_id = 1;
          break;
    
    case    ACTION_PARAS_SET_SWITCH:
          _ui_paras_set_id++;
          if(_ui_paras_set_id >=3)
          {
               _ui_paras_set_id = 1;
          }
          break;
    case    ACTION_PARAS_SET_SWITCHUP:
       if(_ui_paras_set_id ==0)
           _ui_paras_set_id=2;
       else
         _ui_paras_set_id--;
          break;

    case    ACTION_PARAS_SET_END:
          _ui_paras_set_id = 0;
          break;

    case    ACTION_PRICEX_SET_INIT:
          _ui_pricex_set_id = 1;
          break;
    case    ACTION_PRICEX_SET_SWITCH:
          _ui_pricex_set_id++;
          if(_ui_pricex_set_id >=4)
          {
               _ui_pricex_set_id = 1;
          }
          break;
    case    ACTION_PRICEX_SET_SWITCHUP:
      
        if(_ui_pricex_set_id ==1)
           _ui_pricex_set_id=3;
       else
         _ui_pricex_set_id--;
          break;
    case    ACTION_PRICEX_SET_END:
          _ui_pricex_set_id = 0;
          break;
case    ACTION_SYS_SET_INIT:
          _ui_sys_set_id = 1;
          break;
    case    ACTION_SYS_SET_SWITCH:
          _ui_sys_set_id++;
          if(_ui_sys_set_id >=4)
          {
               _ui_sys_set_id = 1;
          }
          break;
    case    ACTION_SYS_SET_SWITCHUP:

        if(_ui_sys_set_id ==1)
           _ui_sys_set_id=3;
       else
         _ui_sys_set_id--;
          break;
    case    ACTION_SYS_SET_END:
          _ui_sys_set_id = 0;
          break;
//************************rg170712 温度控制***************************************//
	  case    ACTION_CS_SET_INIT:
          _ui_cs_set_id = 1;
          break;
    case    ACTION_CS_SET_SWITCH:
          _ui_cs_set_id++;
          if(_ui_cs_set_id >=3)
          {
               _ui_cs_set_id = 1;
          }
          break;
    case    ACTION_CS_SET_SWITCHUP:

        if(_ui_cs_set_id ==1)
           _ui_cs_set_id=2;
       else
         _ui_cs_set_id--;
          break;
    case    ACTION_CS_SET_END:
          _ui_cs_set_id = 0;
          break;
//***************************************************************//	  
   case    ACTION_SYSCHK_SET_INIT:
          _ui_syschk_set_id = 1;
          break;
    case    ACTION_SYSCHK_SET_SWITCH:
          _ui_syschk_set_id++;
          if(_ui_syschk_set_id >=3)
          {
               _ui_syschk_set_id = 1;
          }
          break;
    case    ACTION_SYSCHK_SET_END:
          _ui_syschk_set_id = 0;
          break;
          
      case    ACTION_CARD_QTY_INIT:
          _ui_qry_cardinfo_id = 1;
          break;
    case    ACTION_CARD_QTY_SWITCH:
          _ui_qry_cardinfo_id++;
          if(_ui_qry_cardinfo_id >=4)
          {
               _ui_qry_cardinfo_id = 1;
          }
          break;
    case    ACTION_CARD_QTY_END:
          _ui_qry_cardinfo_id = 0;
          break;

//////////////////电磁阀测试///////////////
 
      case ACTION_VCTRL_TEST_INIT:
          omodule_vctrl_test_init();
          break;

      case ACTION_VCTRL_TEST_END:
          omodule_vctrl_test_end();
          break;
///////////////////////////////////////////
     case    ACTION_FIX_M:
             Operate_fixm = 1;
             break;
     case    ACTION_FIX_V:
            Operate_fixm = 2;
             break;
     case    ACTION_LNG_Operate:
             Operate_fixm = 0;
	  break;
 
    case   ACTION_LNG_RUN_ERR_STOP:
          break;
    //////////////////////////////////////////////////////////
    case ACTION_LOGIN:
          olng_operate_card();
          break;
    case ACTION_CARD_INFO:
         olng_operate_card_info();
	 break;
    default:
            break;
  }
}
static UINT8 init_step = 0;
void ostatemachine_core(void)
{
  unsigned  char  Evs = 0;
  unsigned  char  eRunningState = 0;
  unsigned  char  bEvents = 0;
  unsigned  char  eNums = 0;
  UINT8             car_stare;
  UINT8 i;
  UINT32 SysrunCoun = 0;
  static  UINT8           curkey = 0;
  
  EVENT_NODE_LNG *pENL = NULL;
  if(init_step == 0)
  {
    
  }
  eRunningState = eCurRunState;
  pENL  = RunMatrix[eCurRunState].pEventList;
  eNums = RunMatrix[eCurRunState].bNumEvents;
 //  oprint_printf("hello world 1\r\n");
 
  while(1)
  {
  Com_seril_task();
  ///////
  
       if(gTick > Runled_tick)  //运行灯
       {
           Runled_tick = gTick + 50;
       //   runled_fresh();//闪灯
          if(TRUE == b_mainui )
          {
            oui_mainui_fresh();//刷时间
          }
           
          if(gTick > ReadTemp_Tick) //间隔1min读取温度  //Mengfr 20150831
          {
                ReadTemp_Tick = gTick + 100 * 60 ;
		temperature = DS18B20_Get_Temp();
// 		temperature=-20;
				if(jr_power==0)//rg161017
		{
		temperature = DS18B20_Get_Temp();	
		if(temperature < WDKZ)//RG160824
                {
			wk_cont++;
			if(wk_cont>4)
			{ 
			wk_cont=0;
			JiaReMoOpen;
			delay_ms(100);
			i=mPORTGReadBits(BIT_7)>>7;
			i=i&0x01;
			if(i==1)
			{
			olcm_dispprintf(0,4,"  加热模块异常  ");	
			delay_ms(5000);
			olcm_dispprintf(0,4,"                ");
			}	
			}
                }
                else
                {
			wk_cont++;
			if (wk_cont > 3) {
							wk_cont = 0;
							JiaReMoClose;
							delay_ms(100);
							i = mPORTGReadBits(BIT_7) >> 7;
							i = i & 0x01;
							if (i == 0) {
								olcm_dispprintf(0, 4, "  加热模块异常  ");
								delay_ms(5000);
								olcm_dispprintf(0, 4, "                ");
							}
						}
                }
		}
		if(jr_power == 1)//rg161103
		{
			sdk_cont++;
			if(sdk_cont>2)
			{ 
			sdk_cont=0;
			jr_power = 0;
			JiaReMoClose;
			o24lcxxx_write_bytes(jr_power_addr,(UINT8*)&jr_power,1 );
			delay_ms(100);
			i=mPORTGReadBits(BIT_7)>>7;
			i=i&0x01;
			if(i==0)
			{olcm_dispprintf(0,4,"  加热模块异常  ");	
			delay_ms(5000);
			olcm_dispprintf(0,4,"                ");}	
			}
		}
		if(temperature >= WDBJ)
		{
			delay_ms(100);
			temperature = DS18B20_Get_Temp();
			if(temperature >= WDBJ)
			olcm_dispprintf(0,2,"    温度异常    ");
		}
/*                temperature = DS18B20_Get_Temp();
                if(temperature <= 0)
                {
                    JiaReMoOpen;
                }
                else
                {
                    JiaReMoClose;
                }*/
          }
#if 0
       if ( gTick > Carcheck_tick)
       {
         Carcheck_tick = gTick + 100 * 20;

         if( eCurRunState != State_log_in)
         {
              if(machine_has_card())
              {olcd_clearsCreen();
               olcm_dispprintf(0,1,"正在读卡信息"); 
               olcm_dispprintf(0,2,"请稍等。。。。"); 
  //              car_stare = Car_Experimental();
                car_stare =1;
                switch (car_stare)
                {
                    case 0:
                         olcm_dispprintf(0,2,"通讯错误");
                        break;
                    case 1:
                         olcm_dispprintf(0,2,"正常卡");
                        break;
                        case 2:
                             olcm_dispprintf(0,2,"错误卡，不能加气");
                        break;
                        case 0xad:
                             olcm_dispprintf(0,2,"读卡错误");
                        break;

                }
              }
              else
              {

              }
 //       _b_have_card = FALSE;

         }
        
       }
#endif
         if ( gTick > SysrunTick)//系统运行时间
	{
                 UINT8 qxset;
		 SysrunTick = gTick + 100 * 60 *5;//cs
                 SysrunCoun = Get_Sys_Runtime();
                 SysrunCoun++;
                 Sava_Sys_Runtime(SysrunCoun);
///////////////////////////rg160726//////////////////////////////////////////////		 
		 qxset = o24lcxxx_read(qxset_addr);//rg160726
		if(qxset == 0xaa )//rg160726
		{
		QX_RECORD = Get_Qx_Runtime();
//		QX_RECORD =2;//rg160726cs
		 if(QX_RECORD>=2)		
		 QX_RECORD --;	
		 else
		QX_RECORD=0;	 
		
		 Save_Qx_Runtime(QX_RECORD);	//rg160726
//		 if((QX_RECORD <= 0x0B40)&&(QX_RECORD >= 0x02))//rg160726  10天内报警
//		 {
//			 UINT8 rdkey;
//			 olcd_clearsCreen();
//                                   olcm_dispprintf(0,2,"  使用即将超期！");
//                                   olcm_dispprintf(0,3,"请及时联系厂家!");
//                                   olcm_dispprintf(0,4,"按更改键退出!");
//			 while(1)
//			 {
//                                   delay_ms(100);
//                                   rdkey = ostatemachine_getkey(); 
//                                   b_keyv = FALSE;
//                                   if(_KEY_EXIT_EV_ == rdkey) break;
//                                   delay_ms(100);	 
//			 }
//		 }
 		 if(QX_RECORD<0x02)//RG190705
		 {
			UINT8 rdkey;
			olcd_clearsCreen();
            SOEACTION1(QxOver,eCurRunState);//RG190705
//                                   olcm_dispprintf(0,2,"  使用已超期！");
//                                   olcm_dispprintf(1,3,"请联系厂家!");
                                   olcm_dispprintf(1,4,"按更改键退出!");
				      QX_OVER=1;
			 while(1)
			 {
                                      delay_ms(100);
                                      rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(100);	 
			 } 
		 }
		}
/////////////////////////////////////////////////////////////////////////////		 
                 if(gTick >0xFFFD40DF)  //系统滴答防溢出
                 {
                    if( eCurRunState != State_LngOperate)
                     {
                           gTick = 0;
                       Disp_AllErr_tick = 0;
                        SysrunTick  = 0;
                        Runled_tick = 0;
                        Carcheck_tick=0;
                        CanGasTime  = 0;
                        IsGasAdd_tick = 0;
                        Newdisp_tick2=0;
                        gReadKeyTick = 0;
                        gScanKeyTick = 0;
                        ReadTemp_Tick = 0;
                     }
                 }
           }
       }
      if( eCurRunState != eRunningState) return;
      ostatemachine_getkey();
      if( TRUE == b_keyv || eVirtualKey != 0)
      {
           b_keyv = FALSE;

           if(_KEY_STOP_EV_ == keyv)
           { //发送停止给主板
               Ocompany_stop();
           }

          if(eVirtualKey != 0)
          {
             keyv = eVirtualKey;
             eVirtualKey = 0;

          }     	  
          for(Evs = 0; Evs < eNums; Evs++)
           {
              if(  keyv == pENL[Evs].Event) //curkey
              {
                     eCurRunState = pENL[Evs].NextState;
                     ostatemachine_action(pENL[Evs].Action);
		     		 b_mainui = FALSE;	
                     pENL[Evs].SpecFunc();
    	             return;
              }
	   }
      }

      if( pENL[bEvents].Event == _EVENT_TRUE )
      {
     	    ostatemachine_action(pENL[bEvents].Action);
            //oprint_printf("inter running\r\n");
	    pENL[bEvents].SpecFunc();
	    //continue;
      }
    
  
        bEvents++;

        //oprint_printf("system bEvents is %d\r\n", bEvents);
        if(bEvents >= eNums) 	bEvents = 0;
    if(SendStop_False ==1) //需要再次发送停止，不用按键自动发
      {
         if(TRUE == Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
         SendStop_False  =0;
         else
         {    olcd_clearsCreen();
	      olcm_dispprintf(1,1,"通信线路异常");//
              olcm_dispprintf(1,2,"请断电检查");//

         }
       }
  }//end of while 1
}

void okernel_running(void)
{
      while(1)
      {
      }
}

void runled_fresh(void)
{    Runled_tick = gTick + 50;
     if(Runled)
     {// mPORTASetBits(BIT_1);
       // Runled=0;
     }
     else
    { //mPORTAClearBits(BIT_1);
     // Runled=1;
     }
}
  void Com_seril_task(void)
  {    UINT8 M = 10;
      UINT8 err,errb,err_cont,i;
      err=0;
      errb=0;
      err_cont=0;
      Compa_float zh;
     if((RecvUnit_ok == 1)&&(((Recv_Buf[4] == 0x55)&&(Recv_Buf[5] == 0x55))||((Recv_Buf[4] == 0x56)&&(Recv_Buf[5] == 0x56))))
      //  if((RecvUnit_ok == 1)&&(((Recv_Buf[4] == 0x55)||(Recv_Buf[4] == 0x56))&&((Recv_Buf[5] == 0x55))
      {
          if(eCurRunState !=State_LngOperate)//只有待机状态能进行后台上下班
          {   //后台上下班，键盘板只操作不发送信息
                  if(1 == b_shift_ok )   //已上班
                  {  //
                      if(Recv_Buf[4] == 0x56) //下班
                      {   //本地只进行状态变化，存储和后台通信由主控板完成
                        //  UINT8 M=100;
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
                           M = 10;
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
                      }
                  }

          }

      }
 //////(RecvUnit_ok==0)||(Recv_Buf[5]!=0x12)||(re_over_tick>=COMPANY_OVERTIME2)
#if 1
       if(err_ts(&err)==TRUE)
      {

      }
        if((gTick > Disp_AllErr_tick) &&(Rec_inxex>0))
        {     
            Disp_AllErr_tick = gTick +300;
            while(Rec_inxex)
            {  
                Rec_inxex--;
                SOEACTION1(Sys_Rec_Err[Rec_inxex],eCurRunState);
                if(Sys_Rec_Err[Rec_inxex] == 72)//rg170110
                {
                    DUISHI = 1;		//rg170110
                }
                if(Sys_Rec_Err[Rec_inxex] == NAND_CONT_ERR)//rg170807
                {
                   HUAIKUAI=TRUE;
                }
            }
            Rec_inxex = 0;
            memset(Sys_Rec_Err,0,10);
        }
              //******************************隔20分钟rg170724 对时**************************************************//
      if((RecvUnit_ok == 1)&&((Recv_Buf[4] == 0x05)&&(Recv_Buf[5] == 0x50)))//RG170724隔20分钟对时
      {
		revtime[5] = Recv_Buf[11]; 
		revtime[4] = Recv_Buf[10];
		revtime[3] = Recv_Buf[9];
		revtime[2] = Recv_Buf[8];
		revtime[1] = Recv_Buf[7];
		revtime[0] = Recv_Buf[6];
          if((revtime[5]<60)&&(revtime[4]<60)&&(revtime[3]<24)&&(revtime[2]>0)&&(revtime[2]<32)&&(revtime[1]>0)&&(revtime[1]<13))//rg180621
          {
            if (ortcc_set_date((UINT8*) & revtime[0]) == TRUE) {
					delay_ms(100);
				if (ortcc_set_time((UINT8*) & revtime[3]) == TRUE)
				{
					
				}
				else
				{
					olcd_clearsCreen();
				olcm_dispprintf(0, 1, "    设置失败    ");
				olcm_dispprintf(0, 2, "器件不能置入时间");
				olcm_dispprintf(0, 3, "  请检查    ");
				osys_getkey(_KEY_NULL_, 500);
				}
			}
			else
			{
				olcd_clearsCreen();
				olcm_dispprintf(0, 1, "    设置失败    ");
				olcm_dispprintf(0, 2, "器件不能置入时间");
				olcm_dispprintf(0, 3, "  请检查    ");
				osys_getkey(_KEY_NULL_, 500);
			}
          }
		RecvUnit_ok =0;
		memset(Recv_Buf,0,18);
      }
       //********************************************************************************//
       /////////////////////////rg170110/////////////////////////////////////////////
     	if (b_shift_ok == 1) {
		if ((Err_ZhuTime == 1)&&(Err_JPTime == 0))//rg170110
		{
			ortcc_read_time(GAS_Stime);
			if (TRUE == ocompany_duishi_jpzhu(GAS_Stime, 6)) {
				Err_ZhuTime = 0;
				DSCG = 1;
			} else
				SOEACTION1(PRO422_ERR, eCurRunState);
		}
		if (Err_JPTime == 1) {
			if(Err_ZhuTime == 0)
			{
			//如主板时间正确，用主板时间对时
				if (ortcc_set_date((UINT8*) & zhutime[0]) == TRUE) {
					delay_ms(100);
				if (ortcc_set_time((UINT8*) & zhutime[3]) == TRUE)
				{
					Err_JPTime = 0;
					DSCG = 1;
				}
				else
				{
					olcm_dispprintf(0, 4, "  时钟设置失败  ");
					Err_JPTime = 1;
					osys_getkey(_KEY_NULL_, 500);
				}
					
				}
				else
				{
					olcm_dispprintf(0, 4, "  时钟设置失败  ");
					Err_JPTime = 1;
					osys_getkey(_KEY_NULL_, 500);
				}
			}
			else
			{
				if (TRUE == oset_sysdatatime()) {
					delay_ms(50);
				ortcc_read_time(GAS_Stime);
				Err_JPTime = 0;
				if (TRUE == ocompany_duishi_jpzhu(GAS_Stime, 6)) {
					Err_ZhuTime = 0;
					DSCG = 1;
				} else
					SOEACTION1(PRO422_ERR, eCurRunState);
			} else {
				olcd_clearsCreen();
				olcm_dispprintf(0, 1, "    设置失败    ");
				olcm_dispprintf(0, 2, "请正确且完整设置");
				olcm_dispprintf(0, 3, "  请重新设置    ");
				osys_getkey(_KEY_NULL_, 500);
			}
			}
		}
		if((Err_JPTime == 0)&&(Err_ZhuTime == 0)&&(DSCG ==0))
		{
			//如主板时间正确，用主板时间对时
				if (ortcc_set_date((UINT8*) & zhutime[0]) == TRUE) {
					delay_ms(100);
				if (ortcc_set_time((UINT8*) & zhutime[3]) == TRUE)
				{
					Err_JPTime = 0;
					DSCG = 1;
				}
				else
				{
					olcm_dispprintf(0, 4, "  时钟设置失败  ");
					Err_JPTime = 1;
					osys_getkey(_KEY_NULL_, 500);
				}
					
				}
				else
				{
					olcm_dispprintf(0, 4, "  时钟设置失败  ");
					Err_JPTime = 1;
					osys_getkey(_KEY_NULL_, 500);
				}
		}
         if(hk_disp == TRUE)//RG190510
      {
          olcd_clearsCreen();
     olcm_dispprintf(0,1,"存储器件异常！");
     olcm_dispprintf(0,2,"  请尽快更换"); 
     hk_disp = FALSE;
          delay_ms(8000);
      }
	}
////////////////////////////////////////////////////////////////////////////////		
#endif
  if((RecvUnit_ok == 1)&&(Recv_Buf[4] == 0x92)&&(Recv_Buf[5] == 0x93))
  {
     memcpy(&zh.compa_uc,&Recv_Buf[6],4);
     PRICE = zh.compa_float;
     RecvUnit_ok =0;
     memset(Recv_Buf,0,18);
  }
      #if 1
  if((RecvUnit_ok == 1)&&(Recv_Buf[4] == 0xBD)&&(Recv_Buf[5] == 0xBD))
  {
     olcd_clearsCreen();
     olcm_dispprintf(0,1,"存储器件异常！");
     olcm_dispprintf(0,2,"  请尽快更换");
     HUAIKUAI=TRUE;
     RecvUnit_ok =0;
     memset(Recv_Buf,0,18);
     delay_ms(3000);
  }
#endif

  }