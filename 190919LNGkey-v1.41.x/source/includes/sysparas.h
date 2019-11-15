/* 
 * File:   sysparas.h
 * Author: felixluom
 *
 * Created on 2014��1��23��, ����8:14
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
 * 0x0000 ~ 0x001F   : ϵͳ��ʼ������
 * 0x0020 ~ 0x009F   : ϵͳ����  ��128�ֽڣ�
 * 0x00A0 ~ 0x011F   : ϵͳ��Ϣ1 ��128�ֽڣ�
 * 0x0120 ~ 0x019F   : ϵͳ��Ϣ2 ��128�ֽڣ�
 * 0x01A0 ~ 0x021F   : ϵͳ��Ϣ3 ��128�ֽڣ�
 * 0x0220 ~ 0x029F   : ϵͳ��Ϣ4 ��128�ֽڣ�
 * 0x02A0 ~ 0x031F   : ϵͳ��Ϣ5 ��128�ֽڣ�
 * 0x0320 ~ 0x039F   : ϵͳ��Ϣ6 ��128�ֽڣ�
 * 0x03A0 ~ 0x041F   : ϵͳ��Ϣ7 ��128�ֽڣ�
 * 0x0420 ~ 0x049F   : ϵͳ��Ϣ8 ��128�ֽڣ�
 * 0x04A0 ~ 0x051F   : ϵͳ��Ϣ9 ��128�ֽڣ�
 * 0x0520 ~ 0x059F   : ϵͳ��Ϣ10��128�ֽڣ�
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

    #define CARD_PSW_MAIN_ADDR               0x2800  //������Կ�����ַ
    #define CARD_PSW_BACKUP_ADDR               0x280A  //������Կ�����ַ
    #define TOP_POWER                       0x281A     //�״��ϵ��־�����ַ
     #define info_print                       0x2820     //��ӡ������Ϣ�����ַ
    #define info_print_len                   40
    #define info_print_END                 info_print+info_print_len     //��ӡ������Ϣ�����ַ����

     #define info_contact                       info_print_END+1     //��ӡ��ϵ��ʽ�����ַ
    #define info_contact_len                   40
    #define info_contact_END                 info_contact+info_contact_len     //��ӡ������Ϣ�����ַ����

    #define info_hard                       info_contact_END+1     //��ӡͷ�����ַ
    #define info_hard_len                   40
    #define info_hard_END                 info_hard+info_hard_len     //��ӡͷ�����ַ����

    #define info_xs                       info_hard_END+1     //��ʾ��ʽ�����ַ
    #define info_xs_len                   16
    #define info_xs_END                   info_xs+info_xs_len+1     //��ʾ��Ϣ�����ַ����
    #define zk_power_addr  info_xs_END+1
    #define gass_class_addr zk_power_addr+1
//************************rg170712 �¶ȿ���***********************************************//
#define jr_power_addr           gass_class_addr+1   //rg161017  ���ȿ���
#define Set_Wdcs_Addr     jr_power_addr+1 
#define Set_Wdcs_Len      4 
#define Set_Wdcs_End     Set_Wdcs_Addr+Set_Wdcs_Len+1

#define Set_Wderr_Addr   Set_Wdcs_End+1      //rg161103  �����¶�����
#define Set_Wderr_len    4
#define Set_Wderr_end    Set_Wderr_Addr + Set_Wderr_len+1
#define Set_Wdbj_err     Set_Wderr_end+1
#define Set_Wdbjerr_len    4
#define Set_Wdbjerr_end   Set_Wdbj_err+ Set_Wdbjerr_len+1
//***********************************************************************//    
#define Car_power_addr          Set_Wdbjerr_end+1  //rg170531�޿����� 
//#define zttz_power_addr         Car_power_addr+1  //rg170605ֹͣ/��ͣ
//#define Set_Psw_Addr            Car_power_addr+1       //rg161017 //rg170531�޿����� 
    #define Set_Zttz_Addr      Car_power_addr+1    //rg170605ֹͣ/ ��ͣ
#define Set_Zttz_Len       4                    //rg170605ֹͣ/ ��ͣ
#define Set_Zttz_End       Set_Zttz_Addr+Set_Zttz_Len       //rg170605ֹͣ/ ��ͣ
    #define minimoney_addr       Set_Zttz_End+1  //��Сʣ�����ʶ��ַ rg180118 
    #define minimoney_len   1 
    #define minimoney_end   minimoney_addr+minimoney_len
#define minimoneydat_addr       minimoney_end+1  //��Сʣ�������ݵ�ַ rg180118 
    #define minimoneydat_len   4 
    #define minimoneydat_end   minimoneydat_addr+minimoneydat_len
    #define  hqset_addr         minimoneydat_end+1      //������ӡ����
 #define smallminimoney_addr       hqset_addr+1  //�ӿ���Сʣ�����ʶ��ַ rg181210 
    #define smallminimoney_len   1 
    #define smallminimoney_end   smallminimoney_addr+smallminimoney_len
#define smallminimoneydat_addr       smallminimoney_end+1  //�ӿ���Сʣ�������ݵ�ַ rg181210 
    #define smallminimoneydat_len   4 
    #define smallminimoneydat_end   smallminimoneydat_addr+smallminimoneydat_len
    #define qxsz_min_addr   smallminimoneydat_end+1  //���ޣ����ӣ���ַ//rg170531�޿����� 
    #define qxsz_min_len   4 
    #define qxsz_min_end   qxsz_min_addr+qxsz_min_len

    #define qxsz_yue_addr  qxsz_min_end+1    //���ޣ��죩��ַ
    #define qxset_addr     qxsz_yue_addr+3   //���ޣ�ʹ�ܣ���ַ  addr-0x28DE
//**************qxset_addr--0x28DE*******************************************//
    //������Ϣ�洢λ��  time:2014-3-13  rengang
    // #define CLASS_ADDR_P1 0x0620
    //��0x620��ʼ����10�飬ÿ�鰴��š�״̬�����ȡ�����ֵ�洢��ÿ����16���ֽڿռ䣬�鳤��13
    #define CLASS_ADDR_P1                       _SHIFT_SYSPARAS_EEP_ADDR_END
   #define CLASSLEN                        35
    #define CLASSSIZE                       40
    #define MAX_CLASSNUM                    10
/*_______________________________EEPROM_______________����������_____________________________________________*/
//����������������˼�������  time:2014-3-13  rengang
      typedef struct _def_SysParas{
        float  p_Price;   /*����*/
        float  p_Density; /*�ܶ�*/
        float  p_Factor;  /*����ϵ��*/
        float  p_Pzero;   /*ѹ�����*/
        float  p_PFactor; /*ѹ��ϵ��*/
        float  p_Pcur;    /*��ǰѹ��*/
        float  p_Psafety; /*��ȫѹ��*/

        float  p_Ptemp;             /*Ԥ���¶�*/
        float  p_PGain;             /*Ԥ������*/
        float  p_PDelay;            /*Ԥ����ʱ*/

        float  p_PDensityup;        /*�ܶ�����*/
        float  p_PDensitydown;      /*�ܶ�����*/
        float  p_Paerewait;         /*�����ȴ�ʱ��*/
        float  p_PumpFqy;        /*��Ƶ��*/
        float  p_EndR;           /*ͣ������*/
        float  p_EndP;           /*ͣ��ѹ��*/
        float  min_Gas;         //��С������
        float  min_money;       //��С�������

  //      UINT8  p_GID;           /*ǹ��*/
        UINT8   p_gid;          /*ǹ��*/
        unsigned int  p_SID; /*���*/
        UINT32 p_curflow;   /*���õ�ǰ��ˮ��*/
        UINT8  p_Prset;             /*��ӡ���ã�0-�Զ� 1-�ֶ�*/

  //      UINT32      g_uid;   	   //ǹ��ˮ��
  //      UINT32      sig_uid;   //��½��ˮ��
  //      UINT32      set_uid;    //������ˮ��
        float  press_adc;
        float  press_parm_a;
        float  press_parm_b;
        float  p_ex[16];           /*Ԥ��*/
        UINT8  crc_h;
        UINT8  crc_l;
    }Sysparas;

/*_______________________________EEPROM_______________��ǰϵͳ����Ϣ______________________________*/
    typedef struct def_rec_SysInfo
    {
          UINT8       class_num;       //�����
          UINT8       c_pw_len;        //����ĳ���
          UINT8       class_pw[10];   //��������
          ///////////////////
          UINT32      g_uid;   	   //ǹ��ˮ��
          UINT32      set_uid;    //������ˮ��
          UINT32      sig_uid;   //��½��ˮ��
          float           c_sum;    //���������
          float           c_money; //����������
          float           c_cash;  //�����ֽ�
          UINT32           g_total;           //�ܼ�������
          double          gun_total;        //��ǹ��
          float           shift_cash;      //���ֽ�//IC�����˽�
	  double	  gun_money;       //�ܽ��
          ////end
	  unsigned char  info_crc16_hi;
	  unsigned char  info_crc16_low;

    }_rec_shift_info;
    /*----------------------------             �������°�ļ�¼                           ------------------*/
    typedef struct def_shift_loginInfo
    {
          UINT32   shift_rec_id;             //�����¼��ˮ��
          UINT8    shift_card[15];            //���鿨��  add the card length
          UINT8    shift_id;                 //�����
          UINT8    shift_gid;                //ǹ��
          UINT8    shift_op_time[6];         //����ʱ��
          float    shift_s_mount;            //��ʼǹ��
          float    shift_e_mount;            //����ǹ��
          UINT8     shift_op_type;           //���°�����
          UINT32    recoder_num;             //��ˮ��
          float     shift_cash;            //IC���˽��
    }_shift_loginfo;

    typedef union _def_unfloat
    {
        float          dt_float;
        unsigned char  dt_uc[4];
    }un_float;
 /**/
        //������Ϣ�ṹ��  time:2014-3-13  rengang  for eeprom
      typedef struct _def_class
    {
        UINT8          class_num;       //�����
        UINT8          class_state;     //����״̬ 0-��Ч 1-��Ч
        UINT8          c_pw_len;
        UINT8          class_pw[11];     //��������
        UINT8          sun_f[8];
        UINT8          sun_m[10];
    }class_info;
/*---------------------------------------------�޸ļ�¼�洢�ṹ��--------------------------------------------------*/
//time:14-03-20 rengang
typedef union _def_para
{
        float          para_float;
        unsigned char  para_uc[4];
 }Para_float;
 //time:14-03-20 rengang
typedef struct _def_paraup
{
     UINT32   para_rec_id;               //�޸ļ�¼��ˮ��
      UINT8    modi_card[10];            //�޸��˿���
      UINT8    no[3];                   //��Ϣ���
      float para_float_q;          //�޸�ǰ
      float para_float_h;          //�޸�ǰ
      UINT8    time[6];                 //�޸�ʱ��
}un_paraup;
typedef struct
{
UINT32 FaultCount; //��λ��������
UINT32 CurFaultNum; //��ǰ�������
UINT8 FaultReason; //��λԭ��
UINT8 DateTime[6]; //���ϼ�¼ʱ��
}RESETFAULTMSG;

UINT8             class_sum;       //�������� rengang
class_info        cur_class_info[MAX_CLASSNUM];//����ṹ�θ�


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

   #define DEBUG_RECORD_MAXNUM          0x3000-1   //150730������ˮ��
   #define DEBUG_RECORD_SAVE            0x3000   //150730,����200����ÿ��16���ֽ� ��3200
   #define DEBUG_RECORD_SAVE_END          0x3000+3201   //150730
//////////////////////////////rg160623///////////////////////////////////////////////////////////////
    #define _SYSEEPROM_ONCE         DEBUG_RECORD_SAVE_END+1    //ϵͳE����һ���õ�ַ 
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

