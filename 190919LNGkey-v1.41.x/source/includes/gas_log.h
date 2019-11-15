/* 
 * File:   gas_log.h
 * Author: sushuai 
 *
 * Created on 2018��11��28��, ����9:56
 */

#ifndef GAS_LOG_H
#define	GAS_LOG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/**************   �洢���������д�������ݵ�EEP ��ַ*********/
#define GAS_RECORD_SREIAL_FLAG_SP      0x0E50                //0x21DE    //ss190308
#define GAS_RECORD_SREIAL_SP           0x0E51                //0x21DF
#define GAS_RECORD_ADD_SP              0x0E55                //0x21E3
#define RECORD_LEN_SP                  50                  // ʵ��ֻ��ʹ���� 41���ֽ�  ��ΪԤ���ռ�ʹ��  30�����ݣ�27BF��    
    
 /**************   �洢������Ϣ��EEP ��ַ*********/
#define GAS_RECORD_SREIAL_FLAG        0x21DE                //0x0E50
#define GAS_RECORD_SREIAL             0x21DF                 //0x0E51
#define GAS_RECORD_ADD                0x21E3                //0x0E55
#define RECORD_LEN                  50                  // ʵ��ֻ��ʹ���� 41���ֽ�  ��ΪԤ���ռ�ʹ��
    
#define EEPROM_WRITE_KEY_ERR 	       		22 //EEPROMд�����(ָ���̰�)          sushuai add
#define EEPROM_READ_KEY_ERR  	       		23 //EEPROM��ȡ����(ָ���̰�)
    
typedef struct grey_lock                   // ������¼ ��Ϣ
{
    UINT8   grey_status;                   // ����״̬  
    UINT8   time[6];                       // ����ʱ��
    float   cur_money;                     // ����ǰ���
  
}GREY_lock;   
typedef struct grey_unlock               // ��Ҽ�¼��Ϣ 
{
    UINT8   grey_status;                    // ���״̬
    UINT8   time[6];                       // ���ʱ��
    float   OKgas_money;                     // ������ɺ�ۿ���
    float   Balance_To;                      // ������ɺ����
  
}GREY_unlock; 
typedef struct gas_log
{
//    UINT8       number;                          // ���
    UINT32      gas_stream;                      //������ˮ��
//    UINT8       card_id[10];                     // ����     ss190306
     UINT32      card_id;                          // ����  
    UINT8       gas_start_way;                  // ������
    GREY_lock   grey_lock_inif;                  // �û�״̬��Ϣ
    UINT8       gas_process;                     // ����������Ϣ��¼
    UINT8       gas_stop_way;                    // ����ֹͣ��ʽ
    UINT8       gas_precool;                     // Ԥ��״̬    ss190215
    UINT32      card_id_js;                      // ����ʱ�Ŀ���      ss190306
    GREY_unlock grey_unlock_inif;                //���״̬��Ϣ
      
}GAS_log;
typedef union _shift_type//time:14-04-15 rengang
{
    GAS_log     gas_record_query;                  /// ������Ϣ��¼
    UINT8       compa_uint8[RECORD_LEN];
 }shift_type;    
 
GAS_log  gas_record;
shift_type shift_write;
shift_type shift_read;

/*********** Ԥ�� ״̬  ******/
#define GAS_PRECOOL_SUCC         0x01                      //Ԥ��ɹ�     //ss190215 add
//#define GAS_PRECOOL_FAILL        0x02                      //Ԥ��ʧ��

/*********** ������¼״̬  ******/
#define GAS_START_SEND_SUCC       0x80                      // ������ʼָ���״̬   �ɹ�                   bit7
#define GAS_START_SEND_FAILL      0x7F                      // ������ʼָ���״̬   ʧ��                   bit7
#define GAS_STOP_SEND_SUCC        0x40                      // ����ָֹͣ���״̬   �ɹ�                   bit6
#define GAS_STOP_SEND_FAILL       0xBF                      // ����ָֹͣ���״̬   ʧ��                   bit6
#define GAS_ACCOUNTS_SEND_SUCC    0x20                      // �ۿ������  ֪ͨ���屣����Ϣ״̬   ʧ��      bit5
#define GAS_ACCOUNTS_SEND_FAILL   0xDF                      // �ۿ������  ֪ͨ���屣����Ϣ״̬   ʧ��      bit5
#define GAS_GREY_LUCK_SUCC_AG     0x10                      // ������ɽ��ʧ��,�ٴζԿ������ûҳɹ�          bit4  ss190306
#define GAS_GREY_LUCK_FAILL_AG    0xEF                      // ������ɽ��ʧ��,�ٴζԿ������ûҳɹ�          bit4  ss190306
                                                            //                                              bit3~bit0   ��ʾΪ��ͣ��������
/************** ���� ״̬********/
#define GREY_LUCK_SUCC            0x01                      // ����״̬     �ɹ�                          bit0
#define GREY_LUCK_FAILL           0x02                      // ����״̬     ʧ��                          bit0
#define GREY_GAS_LUCK_SUCC        0x04                      // �����������ٴ��ж� ����״̬    �ɹ�         bit1
#define GREY_GAS_LUCK_FAILL       0x08                      // �����������ٴ��ж� ����״̬    ʧ��         bit1
#define GAS_START_FIX_M           0x10                      // ������ʽ     ����                          bit4 ~ bit7
#define GAS_START_FIX_V           0x20                      // ������ʽ     ����                          bit4 ~ bit7
#define GAS_START_MORMAL          0x40                      // ������ʽ     ��������                      bit4 ~ bit7

///********  ���״̬  *******/
//#define GREY_UNLUCK_SUCC          0x10                    // �ۿ�δ���                                  bit4 
//#define GREY_UNLUCK_FAILL         0xEF                    // �ۿ����  δ���                            bit4
//#define GREY_ACCOUNTS_FAILL         0x20                  // �ۿ�δ���                                  bit 5
//                                                          //  ��ʾ��ѯ���������Ϣ�����������             bit0 ~ bit3   
/********  ���״̬  bit4~bit7 *******/
#define GREY_UNLUCK_SUCC          0x10                    // �ۿ�δ���                                  
#define GREY_UNLUCK_FAILL         0x20                    // �ۿ����  δ���                            
#define GREY_ACCOUNTS_FAILL       0x30                   // �ۿ�δ���                                  
#define GREY_GET_MAC2_FAILL       0x40                   // ��ȡ MAC2 ʧ��                                
#define GREY_GET_GMAC_FAILL       0x50                   // ��ȡ GMAC ʧ��
#define GREY_GET_STATE_FAILL      0x60                   // ��ȡ���״̬ʧ��
#define GREY_ACCOUNTS_STATU_FAILL      0x70                   // ���ѷ�ʽ�쳣,δ���        ss190306
#define GREY_CARD_CHEKE_FAILL          0x80                   // ���ѷ�ʽ�쳣,δ���
                                                          //  ��ʾ��ѯ���������Ϣ�����������             bit0 ~ bit3   


//typedef union _shift_write//time:14-04-15 rengang
//{
//    GAS_log     gas_record_query_write;                  /// ������Ϣ��¼
//    UINT8       compa_write_uint8[41];
// }shift_write;
// 
//typedef union _shift_read//time:14-04-15 rengang
//{
//    GAS_log     gas_record_query_read;                  /// ������Ϣ��¼
//    UINT8       compa_read_uint8[41];
// }shift_read;
 
typedef enum                          // ͣ��״̬
{
    COMMUN_TIIMOUT = 1,               // ���ͨ�ų�ʱ
    FLOWMETER_ERR,                    // ������ͨ�Ŵ��� 
    PRECOOL_ERR,                      // Ԥ�䳬ʱ
    PRESSURE_ERR,                     // ѹ���쳣
    VELOCITY_HIGH,                    // ���������ˮ
    VELOCIIY_LOW,                     // ��ˮ����ͣ
    BACKSTAGE_STOP,                   // ��̨Զ��ͣ��
    GAS_UNUSUAL,                      // �����쳣
    MONEY_ALL,                        // ������
    CARD_EXTRACT,                     // �����γ�
    PRESS_STOP,                       // ��ֹͣ��
    TRIPLE_COMMUN_FAILL,              // �����޽�������
    SYS_HARD_FAULT,                   // ϵͳӲ���쳣  
    SYS_FAULT,                        // ϵͳ�쳣
    CARD_BALANCE_FAILL,               // �����Ϳ��಻ͬ
            
}Stop_flag;

typedef enum
{    
    CARD_STAFF = 0x01,           // ���鿨
    CARD_DRIVER_F = 0x02,      //��˾��   
    CARD_SERVICE = 0x03,                // ˽����
    CARD_DRIVER_C = 0x05,            // ��˾�ӿ� .
    CARD_MANAGE = 0x24,          // ����
    CARD_DRIVER_T = 0x55,            // ��˾ĸ�� .
    CARD_OPERATION = 0x56 ,
    CARD_NO
    
}Start_gas;

/**************  statement  function  SP********************/
void OnceRecordEEP_SP();
void GasRecordQuery_SP(void);                       // ��ѯ���̰������¼��Ϣ
void WiteRecorInfo_SP(GAS_log date);                  // д����̰������¼��Ϣ
void WiteRecorInfo_AN(GAS_log date);                    // �洢������¼��Ϣ
void GasRecordQueryIndex_SP(void);                         //����������¼��Ϣ
void oqry_GasRecordQuery(void);                         
/**************  statement  function  ********************/
void OnceRecordEEP();
void GasRecordQuery(void);                       // ��ѯ���̰������¼��Ϣ
void WiteRecorInfo(GAS_log date);                  // д����̰������¼��Ϣ
void WiteRecorInfoOnce(GAS_log date) ;              // д�� ������¼��Ϣ
void GasRecordQueryIndex(void);                         //����������¼��Ϣ
UINT8 str_chan_u8(UINT8 * date);           // ��׼��  ������ת����������;
#ifdef	__cplusplus
}
#endif

#endif	/* GAS_LOG_H */

