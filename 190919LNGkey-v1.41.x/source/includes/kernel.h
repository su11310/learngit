/* 
 * File:   kernel.h
 * Author: dell
 *
 * Created on 2014?1?14?, ??5:50
 */

#ifndef KERNEL_H
#define	KERNEL_H

#ifdef	__cplusplus
extern "C" {
#endif
#if 1
    typedef void   (*pFunc)(void);
    #define elements_of(a)  (sizeof(a)/sizeof(EVENT_NODE_LNG))
    /*get the offset of member of */
   // #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
   /**/
    typedef enum
    {
        State_MainUI = 0,
        State_Qry =1,
        State_Set =2,
        State_Select,
        State_paras_set,
  //       State_system_set,
        State_module_test,
        State_module_modbus_test,
        State_module_vctrl_test,
        State_team_Set,
        State_sys_Set,
        State_sys_sysset,
        //State_tj_Set,
        State_Pressure_set,
 //       State_sys_set,
 //       State_syschk_set,
     //qaz   State_LngOperate_fix,
	State_LngOperate,
	//qazState_LngOperate_end,
        State_liushuiQry,
                State_liushuiQry_SP,
      //  State_liushui_typeQry, wang 3-28
        State_log_in,
        State_Set_pricex,
        State_Set_power,
        State_ls_Set,
        State_soe,   
        State_Sw_state,
        State_Set_lsh,//rg190108
        State_precool,

    }STATE_LNG;
    typedef enum
    {
        ACTION_NOP   = 0,
        ACTION_MODULE_INIT,
        ACTION_MODULE_END,
        ACTION_MODULE_SWITCH,
        ACTION_MODULE_SWITCHUP,

        ACTION_SYSCHK_SET_INIT,
        ACTION_SYSCHK_SET_END,
        ACTION_SYSCHK_SET_SWITCH,
        ACTION_SYSCHK_SET_SWITCHUP,

        ACTION_SYS_SET_INIT,
        ACTION_SYS_SET_END,
        ACTION_SYS_SET_SWITCH,
        ACTION_SYS_SET_SWITCHUP,

        ACTION_PARAS_SET_INIT,
        ACTION_PARAS_SET_END,
        ACTION_PARAS_SET_SWITCH,
        ACTION_PARAS_SET_SWITCHUP,

        ACTION_PRICEX_SET_INIT,
        ACTION_PRICEX_SET_END,
        ACTION_PRICEX_SET_SWITCH,
        ACTION_PRICEX_SET_SWITCHUP,
                
        ACTION_CS_SET_INIT,//rg170712 温度控制
        ACTION_CS_SET_END,
        ACTION_CS_SET_SWITCH,
        ACTION_CS_SET_SWITCHUP,        

        ACTION_CARD_QTY_INIT,
        ACTION_CARD_QTY_END,
        ACTION_CARD_QTY_SWITCH,

        ACTION_VCTRL_TEST_INIT,
        ACTION_VCTRL_TEST_END,

        ACTION_LNG_START ,
        ACTION_LNG_RUNNING ,
        ACTION_LNG_FIX_STOP,
        ACTION_LNG_RUN_STOP,
        ACTION_LNG_RUN_ERR_STOP,
        ACTION_FIX_M,
        ACTION_FIX_V,
        ACTION_LNG_Operate,
        ACTION_RETURN,

        ACTION_LOGIN,
        ACTION_CARD_INFO
    }ACTIONS_LNG;
    typedef struct
    {
        unsigned char    Event;
        unsigned char    NextState;
        unsigned char    Action;
        pFunc            SpecFunc;
    }EVENT_NODE_LNG;

    typedef struct
    {
      unsigned char     eCurState;
      unsigned char     bNumEvents;
      EVENT_NODE_LNG   * pEventList;
    }STATE_DESC_LNG;


	enum  EVENT_SYS_ID{
		SYS_NOEVENT = 0,
                _KEY_0_EV_ = 1,
                _KEY_1_EV_,
                _KEY_2_EV_,
                _KEY_3_EV_,
                _KEY_4_EV_,
                _KEY_5_EV_,
                _KEY_6_EV_,
                _KEY_7_EV_,
                _KEY_8_EV_,
                _KEY_9_EV_,
                _KEY_SET_EV_ = 11,
                _KEY_POINT_EV_,
                _KEY_QRY_EV_,
                _KEY_EXIT_EV_ = 14,
                _KEY_STOP_EV_,
		_KEY_GAS_EV_,
		_KEY_COOL_EV_,
		_KEY_SW_EV_,
                _KEY_ENTER_EV_,
		_KEY_UP_EV_ = 20,
                _KEY_VIRTUAL_EV_ = 21,
                _KEY_VIRTUAL_1_EV_,
                _KEY_VIRTUAL_2_EV_,
                _KEY_VIRTUAL_3_EV_,
                _KEY_NULL_,
                _KEY_DENGLU_EV_,
                _KEY_LOGIN_HAVECARD,
                _KEY_LOGIN_NOCARD,
                _KEY_LOGIN_SUCCESS,
                _KEY_LOGIN_ERROE,
                _KEY_PRECOOL_SUCCESS,
                _KEY_ADDGAS_EXIT,
                
                _KEY_COMBINATION_UP_DW,
                ///////
                ///////
                MAX_EV_ID
        };

        #define OK              1
        #define ERROR           0

        #define EMPTY      0
        #define NORMAL    1
        #define FULL        -1

        
        #define _KEY_RET_EV_    _KEY_EXIT_EV_
        #define _KEY_OK_EV_     _KEY_ENTER_EV_
        #define                  _EVENT_TRUE    0
        void ostatemachine_init(void);
        void ostatemachine_core(void);
        void okernel_running(void);
        //BOOL osys_getkey(UINT keyv);
        BOOL  osys_getkey(UINT keyv, UINT32 timeout);
    //    UINT8 osys_getkey_ex(void);//UINT8 osys_getkey_v(void);
        UINT8 ostatemachine_getkey(void);
        UINT8 ostatemachine_keyscan(void);
        UINT8 okeyinput_getstr(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw );
        UINT8 okeyinput_GetstrPSW(INT8 *pstr,UINT8 * retlen, UINT8 nmax,BOOL bpt, BOOL bpsw );
        volatile UINT8 eCurRunState;
        volatile UINT8 eVirtualKey;
        UINT32  gReadKeyTick;
          UINT32  ok_ReadKeyTick;
        UINT32  gScanKeyTick;
        UINT32  EecKeynull;
        UINT8  Eeckey;
        UINT8 Operate_fixm;
        UINT8  KeyScan;
         UINT8  Keyvol_num;
          UINT8  Keyvol_PRE;
#endif
        void Com_seril_task(void);
        void ostatemachine_init(void);
        void okernel_running(void);
        UINT8 okeyinput_get_pass(INT8 *pstr,UINT8 * retlen, UINT8 nmax, UINT8 x, UINT8 y);
        void oset_sysset_wk(void);//rg170531无卡加气
#ifdef	__cplusplus
}
#endif

#endif	/* KERNEL_H */

