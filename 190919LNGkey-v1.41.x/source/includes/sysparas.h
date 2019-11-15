/* 
 * File:   sysparas.h
 * Author: felixluom
 *
 * Created on 2014年1月23日, 下午8:14
 */

#ifndef SYSPARAS_H
#define	SYSPARAS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SET_OLD 0
    enum _e_SysParas{
        P_PRICE_ID = 0,
        P_DENSITY_ID,
        P_FACTORY_ID,
        P_PZERO_ID,

    };
/*------------------------------------------------------------------------------
 * 0x0000 ~ 0x001F   : 系统初始化参数
 * 0x0020 ~ 0x009F   : 系统参数  （128字节）
 * 0x00A0 ~ 0x011F   : 系统信息1 （128字节）
 * 0x0120 ~ 0x019F   : 系统信息2 （128字节）
 * 0x01A0 ~ 0x021F   : 系统信息3 （128字节）
 * 0x0220 ~ 0x029F   : 系统信息4 （128字节）
 * 0x02A0 ~ 0x031F   : 系统信息5 （128字节）
 * 0x0320 ~ 0x039F   : 系统信息6 （128字节）
 * 0x03A0 ~ 0x041F   : 系统信息7 （128字节）
 * 0x0420 ~ 0x049F   : 系统信息8 （128字节）
 * 0x04A0 ~ 0x051F   : 系统信息9 （128字节）
 * 0x0520 ~ 0x059F   : 系统信息10（128字节）
 ------------------------------------------------------------------------------*/
    #define _SYSPARAS_INIT_ADDR         0x00
    #define _WAIT_TIM_ADDR              0x10///new wang
    #define _BUZZER_SW_ADDR             0x11///new wang
    #define _PRINT_SW_ADDR              0x12///new wang
    #define _CLASSNO_OFFWORK_ADDR       0x13///new wang
 // #define _STATION_NO_ADDR            0x13///new wang
    #define _TMP_ADD_ADDR              0x14///new wang
    #define _HARD_VER_ADDR              0x18///new wang 150906
    #define _POWER_DOWN_ADDR            0x1F
    

    #define _SYSPARAS_EEP_ADDR          0x20//0x100

    #define _REC_SYSINFO_PAGE_SZIE_     128
    #define _REC_SYSINFO_PAGES_         11

    /*store the system information in P0, every class information store the P1-P10 */
    #define _LNG_RUNTIME_ADDR               0x0090  //LNGruntime
    #define SOE_SAVE_ADDR_MAX                0x009C    //SOE max
    #define SOE_SAVE_ADDR                    0x00A0     //SOE add
    #define _REC_SYSINFO_EEP_ADDR           0x00A0
    #define _REC_SYSPARAS_EEP_ADDR_P0       _REC_SYSINFO_EEP_ADDR
    #define _REC_SYSPARAS_EEP_ADDR_P1       _REC_SYSPARAS_EEP_ADDR_P0 + _REC_SYSINFO_EEP_ADDR
    #define _REC_SYSPARAS_EEP_ADDR_P2       _REC_SYSPARAS_EEP_ADDR_P1 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P3       _REC_SYSPARAS_EEP_ADDR_P2 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P4       _REC_SYSPARAS_EEP_ADDR_P3 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P5       _REC_SYSPARAS_EEP_ADDR_P4 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P6       _REC_SYSPARAS_EEP_ADDR_P5 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P7       _REC_SYSPARAS_EEP_ADDR_P6 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P8       _REC_SYSPARAS_EEP_ADDR_P7 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P9       _REC_SYSPARAS_EEP_ADDR_P8 + _REC_SYSINFO_PAGE_SZIE_
    #define _REC_SYSPARAS_EEP_ADDR_P10      _REC_SYSPARAS_EEP_ADDR_P9 + _REC_SYSINFO_PAGE_SZIE_

    #define _REC_SYSPARAS_EEP_ADDR_END          _REC_SYSPARAS_EEP_ADDR_P10 + _REC_SYSINFO_PAGE_SZIE_

    #define _SHIFT_SYSINFO_PAGE_SZIE_     128
    #define _SHIFT_SYSINFO_PAGES_         10
    #define _SHIFT_SYSINFO_EEP_ADDR           _REC_SYSPARAS_EEP_ADDR_END
    #define _SHIFT_SYSPARAS_EEP_ADDR_P1       _SHIFT_SYSINFO_EEP_ADDR
    #define _SHIFT_SYSPARAS_EEP_ADDR_P2       _SHIFT_SYSPARAS_EEP_ADDR_P1 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P3       _SHIFT_SYSPARAS_EEP_ADDR_P2 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P4       _SHIFT_SYSPARAS_EEP_ADDR_P3 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P5       _SHIFT_SYSPARAS_EEP_ADDR_P4 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P6       _SHIFT_SYSPARAS_EEP_ADDR_P5 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P7       _SHIFT_SYSPARAS_EEP_ADDR_P6 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P8       _SHIFT_SYSPARAS_EEP_ADDR_P7 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P9       _SHIFT_SYSPARAS_EEP_ADDR_P8 + _SHIFT_SYSINFO_PAGE_SZIE_
    #define _SHIFT_SYSPARAS_EEP_ADDR_P10      _SHIFT_SYSPARAS_EEP_ADDR_P9 + _SHIFT_SYSINFO_PAGE_SZIE_

    #define _SHIFT_SYSPARAS_EEP_ADDR_END      0x1BFF

    #define CARD_PSW_MAIN_ADDR               0x2800  //主卡秘钥保存地址
    #define CARD_PSW_BACKUP_ADDR               0x280A  //备卡秘钥保存地址
    #define TOP_POWER                       0x281A     //首次上电标志保存地址
     #define info_print                       0x2820     //打印厂家信息保存地址
    #define info_print_len                   40
    #define info_print_END                 info_print+info_print_len     //打印厂家信息保存地址结束

     #define info_contact                       info_print_END+1     //打印联系方式保存地址
    #define info_contact_len                   40
    #define info_contact_END                 info_contact+info_contact_len     //打印厂家信息保存地址结束

    #define info_hard                       info_contact_END+1     //打印头保存地址
    #define info_hard_len                   40
    #define info_hard_END                 info_hard+info_hard_len     //打印头保存地址结束

    #define info_xs                       info_hard_END+1     //显示方式保存地址
    #define info_xs_len                   16
    #define info_xs_END                   info_xs+info_xs_len+1     //显示信息保存地址结束
    #define zk_power_addr  info_xs_END+1
    #define gass_class_addr zk_power_addr+1
//************************rg170712 温度控制***********************************************//
#define jr_power_addr           gass_class_addr+1   //rg161017  加热开关
#define Set_Wdcs_Addr     jr_power_addr+1 
#define Set_Wdcs_Len      4 
#define Set_Wdcs_End     Set_Wdcs_Addr+Set_Wdcs_Len+1

#define Set_Wderr_Addr   Set_Wdcs_End+1      //rg161103  报警温度设置
#define Set_Wderr_len    4
#define Set_Wderr_end    Set_Wderr_Addr + Set_Wderr_len+1
#define Set_Wdbj_err     Set_Wderr_end+1
#define Set_Wdbjerr_len    4
#define Set_Wdbjerr_end   Set_Wdbj_err+ Set_Wdbjerr_len+1
//***********************************************************************//    
#define Car_power_addr          Set_Wdbjerr_end+1  //rg170531无卡加气 
//#define zttz_power_addr         Car_power_addr+1  //rg170605停止/暂停
//#define Set_Psw_Addr            Car_power_addr+1       //rg161017 //rg170531无卡加气 
    #define Set_Zttz_Addr      Car_power_addr+1    //rg170605停止/ 暂停
#define Set_Zttz_Len       4                    //rg170605停止/ 暂停
#define Set_Zttz_End       Set_Zttz_Addr+Set_Zttz_Len       //rg170605停止/ 暂停
    #define minimoney_addr       Set_Zttz_End+1  //最小剩余金额标识地址 rg180118 
    #define minimoney_len   1 
    #define minimoney_end   minimoney_addr+minimoney_len
#define minimoneydat_addr       minimoney_end+1  //最小剩余金额数据地址 rg180118 
    #define minimoneydat_len   4 
    #define minimoneydat_end   minimoneydat_addr+minimoneydat_len
    #define  hqset_addr         minimoneydat_end+1      //回气打印设置
 #define smallminimoney_addr       hqset_addr+1  //子卡最小剩余金额标识地址 rg181210 
    #define smallminimoney_len   1 
    #define smallminimoney_end   smallminimoney_addr+smallminimoney_len
#define smallminimoneydat_addr       smallminimoney_end+1  //子卡最小剩余金额数据地址 rg181210 
    #define smallminimoneydat_len   4 
    #define smallminimoneydat_end   smallminimoneydat_addr+smallminimoneydat_len
    #define qxsz_min_addr   smallminimoneydat_end+1  //期限（分钟）地址//rg170531无卡加气 
    #define qxsz_min_len   4 
    #define qxsz_min_end   qxsz_min_addr+qxsz_min_len

    #define qxsz_yue_addr  qxsz_min_end+1    //期限（天）地址
    #define qxset_addr     qxsz_yue_addr+3   //期限（使能）地址  addr-0x28DE
//**************qxset_addr--0x28DE*******************************************//
    //班组信息存储位置  time:2014-3-13  rengang
    // #define CLASS_ADDR_P1 0x0620
    //在0x620开始，分10组，每组按组号、状态、长度、密码值存储，每组间隔16个字节空间，组长度13
    #define CLASS_ADDR_P1                       _SHIFT_SYSPARAS_EEP_ADDR_END
   #define CLASSLEN                        35
    #define CLASSSIZE                       40
    #define MAX_CLASSNUM                    10
/*_______________________________EEPROM_______________加气机参数_____________________________________________*/
//加气机参数，添加了几个变量  time:2014-3-13  rengang
      typedef struct _def_SysParas{
        float  p_Price;   /*单价*/
        float  p_Density; /*密度*/
        float  p_Factor;  /*修正系数*/
        float  p_Pzero;   /*压力零点*/
        float  p_PFactor; /*压力系数*/
        float  p_Pcur;    /*当前压力*/
        float  p_Psafety; /*安全压力*/

        float  p_Ptemp;             /*预冷温度*/
        float  p_PGain;             /*预冷增益*/
        float  p_PDelay;            /*预冷延时*/

        float  p_PDensityup;        /*密度上限*/
        float  p_PDensitydown;      /*密度下限*/
        float  p_Paerewait;         /*加气等待时间*/
        float  p_PumpFqy;        /*泵频率*/
        float  p_EndR;           /*停机流速*/
        float  p_EndP;           /*停机压力*/
        float  min_Gas;         //最小加气量
        float  min_money;       //最小加气金额

  //      UINT8  p_GID;           /*枪号*/
        UINT8   p_gid;          /*枪号*/
        unsigned int  p_SID; /*班号*/
        UINT32 p_curflow;   /*设置当前流水号*/
        UINT8  p_Prset;             /*打印设置：0-自动 1-手动*/

  //      UINT32      g_uid;   	   //枪流水号
  //      UINT32      sig_uid;   //登陆流水号
  //      UINT32      set_uid;    //设置流水号
        float  press_adc;
        float  press_parm_a;
        float  press_parm_b;
        float  p_ex[16];           /*预留*/
        UINT8  crc_h;
        UINT8  crc_l;
    }Sysparas;

/*_______________________________EEPROM_______________当前系统化信息______________________________*/
    typedef struct def_rec_SysInfo
    {
          UINT8       class_num;       //班组号
          UINT8       c_pw_len;        //密码的长度
          UINT8       class_pw[10];   //班组密码
          ///////////////////
          UINT32      g_uid;   	   //枪流水号
          UINT32      set_uid;    //设置流水号
          UINT32      sig_uid;   //登陆流水号
          float           c_sum;    //当班加气量
          float           c_money; //当班加气金额
          float           c_cash;  //当班现金
          UINT32           g_total;           //总加气次数
          double          gun_total;        //总枪累
          float           shift_cash;      //班现金//IC卡记账金
	  double	  gun_money;       //总金额
          ////end
	  unsigned char  info_crc16_hi;
	  unsigned char  info_crc16_low;

    }_rec_shift_info;
    /*----------------------------             班组上下班的记录                           ------------------*/
    typedef struct def_shift_loginInfo
    {
          UINT32   shift_rec_id;             //班组记录流水号
          UINT8    shift_card[15];            //班组卡号  add the card length
          UINT8    shift_id;                 //班组号
          UINT8    shift_gid;                //枪号
          UINT8    shift_op_time[6];         //操作时间
          float    shift_s_mount;            //开始枪累
          float    shift_e_mount;            //结束枪累
          UINT8     shift_op_type;           //上下班类型
          UINT32    recoder_num;             //流水号
          float     shift_cash;            //IC记账金额
    }_shift_loginfo;

    typedef union _def_unfloat
    {
        float          dt_float;
        unsigned char  dt_uc[4];
    }un_float;
 /**/
        //班组信息结构体  time:2014-3-13  rengang  for eeprom
      typedef struct _def_class
    {
        UINT8          class_num;       //班组号
        UINT8          class_state;     //班组状态 0-无效 1-有效
        UINT8          c_pw_len;
        UINT8          class_pw[11];     //班组密码
        UINT8          sun_f[8];
        UINT8          sun_m[10];
    }class_info;
/*---------------------------------------------修改记录存储结构体--------------------------------------------------*/
//time:14-03-20 rengang
typedef union _def_para
{
        float          para_float;
        unsigned char  para_uc[4];
 }Para_float;
 //time:14-03-20 rengang
typedef struct _def_paraup
{
     UINT32   para_rec_id;               //修改记录流水号
      UINT8    modi_card[10];            //修改人卡号
      UINT8    no[3];                   //消息编号
      float para_float_q;          //修改前
      float para_float_h;          //修改前
      UINT8    time[6];                 //修改时间
}un_paraup;
typedef struct
{
UINT32 FaultCount; //复位故障总数
UINT32 CurFaultNum; //当前故障序号
UINT8 FaultReason; //复位原因
UINT8 DateTime[6]; //故障记录时间
}RESETFAULTMSG;

UINT8             class_sum;       //班组总数 rengang
class_info        cur_class_info[MAX_CLASSNUM];//班组结构任刚


_rec_shift_info      cur_rec_sysinfo;            // current system information for store the add gass information
_rec_shift_info      cur_rec_shiftinfo;            // current shift information for store the add gass information
//_shift_Sysinfo    cur_shift_sysinfo;          
_shift_loginfo    cur_shift_loginfo;         //current class log  in  information
Sysparas          cur_sysparas;              //configure information for control the action 
un_float          cur_un_float;
//time:14-03-22 rengang
     #define _PARA_PAGE_SZIE_           64 //128
    #define _PARA_PAGES_                10
    #define _PARA_EEP_ADDR           0x2A9F
    #define _PARA_EEP_ADDR_P1       _PARA_EEP_ADDR
    #define _PARA_EEP_ADDR_P2       _PARA_EEP_ADDR_P1 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P3       _PARA_EEP_ADDR_P2 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P4       _PARA_EEP_ADDR_P3 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P5       _PARA_EEP_ADDR_P4 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P6       _PARA_EEP_ADDR_P5 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P7       _PARA_EEP_ADDR_P6 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P8       _PARA_EEP_ADDR_P7 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P9       _PARA_EEP_ADDR_P8 + _PARA_PAGE_SZIE_
    #define _PARA_EEP_ADDR_P10      _PARA_EEP_ADDR_P9 + _PARA_PAGE_SZIE_

    #define _PARA_EEP_ADDR_END          _PARA_EEP_ADDR_P10 + _PARA_PAGE_SZIE_

    #define _PASS_PAGE_SIZE                 1
    #define _PASS_EEP_PAGES                 5
    #define _PASS_EEP_ADDR                _PARA_EEP_ADDR_END
    #define _PASS_EEP_ADDR_P1            _PASS_EEP_ADDR
    #define _PASS_EEP_ADDR_P2             _PASS_EEP_ADDR_P1 + _PASS_PAGE_SIZE
    #define _PASS_EEP_ADDR_P3             _PASS_EEP_ADDR_P2 + _PASS_PAGE_SIZE
    #define _PASS_EEP_ADDR_P4            _PASS_EEP_ADDR_P3 + _PASS_PAGE_SIZE
    #define _PASS_EEP_ADDR_P5            _PASS_EEP_ADDR_P4 + _PASS_PAGE_SIZE
    #define _PASS_EEP_ADDR_END          _PASS_EEP_ADDR_P5 + _PASS_PAGE_SZIE_

   #define DEBUG_RECORD_MAXNUM          0x3000-1   //150730调试流水号
   #define DEBUG_RECORD_SAVE            0x3000   //150730,保存200条，每条16个字节 共3200
   #define DEBUG_RECORD_SAVE_END          0x3000+3201   //150730
//////////////////////////////rg160623///////////////////////////////////////////////////////////////
    #define _SYSEEPROM_ONCE         DEBUG_RECORD_SAVE_END+1    //系统E方第一次用地址 
    #define KeyReset_RECORD_MAX    DEBUG_RECORD_SAVE_END+2    
    #define KeyReset_RECORD_Addr   DEBUG_RECORD_SAVE_END+6     
    #define KeyReset_RECORD_Len     30
    #define KeyReset_RECORD_Size    16
    #define KeyReset_RECORD__END    KeyReset_RECORD_Addr+KeyReset_RECORD_Size*KeyReset_RECORD_Len   
//////////////////////////////////////////////////////////////////////////////////////////////
BOOL   ostore_set_paras(UINT8 id, UINT8* vpara, UINT8 len);
BOOL   ostore_read_paras(UINT8 id, UINT8* vpara, UINT8 len);
double ostore_paras_rdfloat(UINT8 id);
BOOL   ostore_paras_wtfloat(UINT8 id, float fwt);
BOOL   ostore_paras_wtchar(UINT8 id, UINT8 wt);
UINT8  ostore_paras_rdchar(UINT8 id);
BOOL   oset_system_init_chk(void);
UINT32 oset_system_get_max_rec_id(void);
UINT32 oset_system_get_max_shift_id(void);
#ifdef	__cplusplus
}
#endif

#endif	/* SYSPARAS_H */

