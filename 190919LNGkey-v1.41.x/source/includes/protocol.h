/*
 * File:   protocol.h
 * Author: wangzw
 *
 * Created on 2014-03-21  20:36
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

        #define combufleng    128    //串口发送缓冲区长度////************************************
        #define cominbufleng  40  //串口接收缓冲区长度////************************************
        #define Heareat_Timeout  300 //心跳定时300*10ms
     
        #define PROTOCOL_TIMEOUT 5 //通讯超时5sPROTOCOL_RESET_NUM
        #define PROTOCOL_RESET_NUM 3 //超时3次，初始化串口

        //E方黑名单所用地址
        #define     ADDBLACK_MAP             0x0AA0
        #define     ADDBLACK_MAP_END         0x1A9F
        #define     ADDBLACK_SAVE_MAX        0x1AA0   //2字节保存黑名单最大数
        #define     ADDBLACK_SAVE            0x1AA4
        #define     ADDBLACK_SAVE_END        0x2A9F

    void   opotocol_port_init(unsigned long baud);
    void   Configure_protocol (void);//后台协议初始化
    void   opotocol_state(void);//*******************************

    void  Set_Clockask(void);//配置为时间同步
    void  Setshiftonce(void);
    void  SetGasruning(void);
    void  Setliushuirec(void);
    void  Setcardverify(UINT8 *BUF,UINT8 LEN);
    void  SetParaOnce(void);
    void  set_heareat(void);

    void protocol_sendstr(UINT8 len, UINT8 *buf);//fasong
    void send_heareat(void);    //发心跳包
    void send_liushuirec(void);//每笔加气记录
    void send_lngstate(void);//加气机状态
    void send_shift(void);    //轮班信息
    void send_LNGparas(void); //加气机参数
    void send_setpara(void);  //单次修改发送
    void send_newblacklist(void);  //新增黑名单
    void send_blacklist(void);  //所有黑名单 一次一百条
    void send_cardverify(void);//卡验证
    void send_clockask(void);  //时间请求/////send_DataErr
    void send_DataErr(void);  //发送错误

    BOOL Receive_TIME(void);////
    BOOL Receive_LNGparas(void);/////
    BOOL Receive_Setpara(void);
    BOOL Receive_resultCard(void);
    BOOL Receive_shiftid(void);/////
    BOOL Receive_liushuinum(void);/////
    BOOL Receive_befshiftid(void);/////
    BOOL Receive_blacklist(void);/////
    void PCshift_JoinorExit(INT8 *buf, UINT8 len1,INT8 *buf2,UINT8 len2,INT8 *buf3,UINT8 len3);
    void PCSet_blacklist(UINT8 *buf, UINT8 len1,UINT8 buf3);
    UINT16 BKDRHash(UINT8 *str,UINT8 len);
    BOOL SaveorDEL_blacklist(UINT32 buf, UINT8 buf3);
    void Black_DELEALL(void);
    void DeleteRecord(UINT16 add) ;
    BOOL AddRecord(UINT32 black);
    UINT16 Get_max_black_id(void);
    void PCset_shift_join(UINT8*strCN, UINT8 lenCN,UINT8*strTN,UINT8 lenTN,UINT8*strOTP,UINT8 lenOTP);
    //   unsigned int crc16(unsigned char *puchMsg, unsigned char usDataLen);
  volatile   UINT32    Protocol_tick;//超市定时滴答
  volatile   UINT32  heareat_time;
   BOOL  opotocol_SW;     //后台通信开关
   BOOL  heareat_flag;
   UINT8  ORD_DATAPA;     //数据包命令
   UINT8 gcombufleng;  //缓冲区发送截止位置
   UINT8 gcomInbufleng;  //缓冲区接收截止位置
   UINT8 Com_Timeoutnum;
   BOOL  pototime_flag;     //后台通信计时标志
   BOOL  pro_alarm;//后台通信异常报警标志
   BYTE gComRF[combufleng];
   UINT16  crc_rece;
   BYTE gComIn[cominbufleng];
   UINT16 Rec_liushnum;//********
   UINT16 Rec_shiftidnum;//********
   UINT8 gComRFPos;
   UINT8   sq[4];//后台枪号验证字符串
   UINT8 gComRec_OK;
   UINT16 cur_max_blacklist;    //当前最大黑名单数
   UINT8  cur_p_GID;//当前抢号
   UINT8   sys_recPCtime[6];///////
   UINT8   VerCard[11];//验证卡，10位+1
   BOOL   Result_card;//验证结果
  float JQvolu;
  float JQ_money;

    typedef enum
  {
     MAX_NULL_FLAG = 0,
     liushuirec_flag,   //每笔加气记录有无标识
     lngGasruning_flag,  //加气中
    lngstate_flag ,     //加气机状态有无标识
    shift_flag ,       //轮班信息有无标识
    LNGparas_flag,     //加气机参数有无标识
    newblacklist_flag, //新增黑名单有无标识
    blacklist_flag ,    //所有黑名单有无标识    一次一百条
    cardverify_flag,  //卡验证有无标识
    clockask_flag,  //时间请求有无标识
    setpara_flag

  }Protocol_state;



#endif	/* PROTOCOL_H */





