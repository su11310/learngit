/* 
 * File:   gas_log.h
 * Author: sushuai 
 *
 * Created on 2018年11月28日, 上午9:56
 */

#ifndef GAS_LOG_H
#define	GAS_LOG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/**************   存储加气过程中错误的数据的EEP 地址*********/
#define GAS_RECORD_SREIAL_FLAG_SP      0x0E50                //0x21DE    //ss190308
#define GAS_RECORD_SREIAL_SP           0x0E51                //0x21DF
#define GAS_RECORD_ADD_SP              0x0E55                //0x21E3
#define RECORD_LEN_SP                  50                  // 实际只是使用了 41个字节  作为预留空间使用  30组数据（27BF）    
    
 /**************   存储加气信息的EEP 地址*********/
#define GAS_RECORD_SREIAL_FLAG        0x21DE                //0x0E50
#define GAS_RECORD_SREIAL             0x21DF                 //0x0E51
#define GAS_RECORD_ADD                0x21E3                //0x0E55
#define RECORD_LEN                  50                  // 实际只是使用了 41个字节  作为预留空间使用
    
#define EEPROM_WRITE_KEY_ERR 	       		22 //EEPROM写入错误(指键盘板)          sushuai add
#define EEPROM_READ_KEY_ERR  	       		23 //EEPROM读取错误(指键盘板)
    
typedef struct grey_lock                   // 灰锁记录 信息
{
    UINT8   grey_status;                   // 灰锁状态  
    UINT8   time[6];                       // 灰锁时间
    float   cur_money;                     // 加气前金额
  
}GREY_lock;   
typedef struct grey_unlock               // 解灰记录信息 
{
    UINT8   grey_status;                    // 解灰状态
    UINT8   time[6];                       // 解灰时间
    float   OKgas_money;                     // 加气完成后扣款金额
    float   Balance_To;                      // 加气完成后余额
  
}GREY_unlock; 
typedef struct gas_log
{
//    UINT8       number;                          // 序号
    UINT32      gas_stream;                      //加气流水号
//    UINT8       card_id[10];                     // 卡号     ss190306
     UINT32      card_id;                          // 卡号  
    UINT8       gas_start_way;                  // 卡类型
    GREY_lock   grey_lock_inif;                  // 置灰状态信息
    UINT8       gas_process;                     // 加气过程信息记录
    UINT8       gas_stop_way;                    // 加气停止方式
    UINT8       gas_precool;                     // 预冷状态    ss190215
    UINT32      card_id_js;                      // 结算时的卡号      ss190306
    GREY_unlock grey_unlock_inif;                //解灰状态信息
      
}GAS_log;
typedef union _shift_type//time:14-04-15 rengang
{
    GAS_log     gas_record_query;                  /// 加气信息记录
    UINT8       compa_uint8[RECORD_LEN];
 }shift_type;    
 
GAS_log  gas_record;
shift_type shift_write;
shift_type shift_read;

/*********** 预冷 状态  ******/
#define GAS_PRECOOL_SUCC         0x01                      //预冷成功     //ss190215 add
//#define GAS_PRECOOL_FAILL        0x02                      //预冷失败

/*********** 加气记录状态  ******/
#define GAS_START_SEND_SUCC       0x80                      // 加气开始指令发送状态   成功                   bit7
#define GAS_START_SEND_FAILL      0x7F                      // 加气开始指令发送状态   失败                   bit7
#define GAS_STOP_SEND_SUCC        0x40                      // 加气停止指令发送状态   成功                   bit6
#define GAS_STOP_SEND_FAILL       0xBF                      // 加气停止指令发送状态   失败                   bit6
#define GAS_ACCOUNTS_SEND_SUCC    0x20                      // 扣款解灰完成  通知主板保存信息状态   失败      bit5
#define GAS_ACCOUNTS_SEND_FAILL   0xDF                      // 扣款解灰完成  通知主板保存信息状态   失败      bit5
#define GAS_GREY_LUCK_SUCC_AG     0x10                      // 加气完成解灰失败,再次对卡进行置灰成功          bit4  ss190306
#define GAS_GREY_LUCK_FAILL_AG    0xEF                      // 加气完成解灰失败,再次对卡进行置灰成功          bit4  ss190306
                                                            //                                              bit3~bit0   表示为暂停加气次数
/************** 灰锁 状态********/
#define GREY_LUCK_SUCC            0x01                      // 灰锁状态     成功                          bit0
#define GREY_LUCK_FAILL           0x02                      // 灰锁状态     失败                          bit0
#define GREY_GAS_LUCK_SUCC        0x04                      // 加气过程中再次判断 灰锁状态    成功         bit1
#define GREY_GAS_LUCK_FAILL       0x08                      // 加气过程中再次判断 灰锁状态    失败         bit1
#define GAS_START_FIX_M           0x10                      // 加气方式     定额                          bit4 ~ bit7
#define GAS_START_FIX_V           0x20                      // 加气方式     定量                          bit4 ~ bit7
#define GAS_START_MORMAL          0x40                      // 加气方式     正常加气                      bit4 ~ bit7

///********  解灰状态  *******/
//#define GREY_UNLUCK_SUCC          0x10                    // 扣款未完成                                  bit4 
//#define GREY_UNLUCK_FAILL         0xEF                    // 扣款完成  未解灰                            bit4
//#define GREY_ACCOUNTS_FAILL         0x20                  // 扣款未完成                                  bit 5
//                                                          //  表示轮询主板加气信息发送命令次数             bit0 ~ bit3   
/********  解灰状态  bit4~bit7 *******/
#define GREY_UNLUCK_SUCC          0x10                    // 扣款未完成                                  
#define GREY_UNLUCK_FAILL         0x20                    // 扣款完成  未解灰                            
#define GREY_ACCOUNTS_FAILL       0x30                   // 扣款未完成                                  
#define GREY_GET_MAC2_FAILL       0x40                   // 获取 MAC2 失败                                
#define GREY_GET_GMAC_FAILL       0x50                   // 获取 GMAC 失败
#define GREY_GET_STATE_FAILL      0x60                   // 获取解灰状态失败
#define GREY_ACCOUNTS_STATU_FAILL      0x70                   // 消费方式异常,未解灰        ss190306
#define GREY_CARD_CHEKE_FAILL          0x80                   // 消费方式异常,未解灰
                                                          //  表示轮询主板加气信息发送命令次数             bit0 ~ bit3   


//typedef union _shift_write//time:14-04-15 rengang
//{
//    GAS_log     gas_record_query_write;                  /// 加气信息记录
//    UINT8       compa_write_uint8[41];
// }shift_write;
// 
//typedef union _shift_read//time:14-04-15 rengang
//{
//    GAS_log     gas_record_query_read;                  /// 加气信息记录
//    UINT8       compa_read_uint8[41];
// }shift_read;
 
typedef enum                          // 停机状态
{
    COMMUN_TIIMOUT = 1,               // 板间通信超时
    FLOWMETER_ERR,                    // 流量计通信错误 
    PRECOOL_ERR,                      // 预冷超时
    PRESSURE_ERR,                     // 压力异常
    VELOCITY_HIGH,                    // 超出最大流水
    VELOCIIY_LOW,                     // 流水低暂停
    BACKSTAGE_STOP,                   // 后台远程停机
    GAS_UNUSUAL,                      // 加气异常
    MONEY_ALL,                        // 金额加满
    CARD_EXTRACT,                     // 卡被拔出
    PRESS_STOP,                       // 按停止键
    TRIPLE_COMMUN_FAILL,              // 三秒无接收数据
    SYS_HARD_FAULT,                   // 系统硬件异常  
    SYS_FAULT,                        // 系统异常
    CARD_BALANCE_FAILL,               // 卡类型卡余不同
            
}Stop_flag;

typedef enum
{    
    CARD_STAFF = 0x01,           // 班组卡
    CARD_DRIVER_F = 0x02,      //公司卡   
    CARD_SERVICE = 0x03,                // 私车卡
    CARD_DRIVER_C = 0x05,            // 公司子卡 .
    CARD_MANAGE = 0x24,          // 管理卡
    CARD_DRIVER_T = 0x55,            // 公司母卡 .
    CARD_OPERATION = 0x56 ,
    CARD_NO
    
}Start_gas;

/**************  statement  function  SP********************/
void OnceRecordEEP_SP();
void GasRecordQuery_SP(void);                       // 查询键盘板加气记录信息
void WiteRecorInfo_SP(GAS_log date);                  // 写入键盘板加气记录信息
void WiteRecorInfo_AN(GAS_log date);                    // 存储加气记录信息
void GasRecordQueryIndex_SP(void);                         //索引加气记录信息
void oqry_GasRecordQuery(void);                         
/**************  statement  function  ********************/
void OnceRecordEEP();
void GasRecordQuery(void);                       // 查询键盘板加气记录信息
void WiteRecorInfo(GAS_log date);                  // 写入键盘板加气记录信息
void WiteRecorInfoOnce(GAS_log date) ;              // 写入 加气记录信息
void GasRecordQueryIndex(void);                         //索引加气记录信息
UINT8 str_chan_u8(UINT8 * date);           // 标准版  卡类型转换数据类型;
#ifdef	__cplusplus
}
#endif

#endif	/* GAS_LOG_H */

