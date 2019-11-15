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

        #define combufleng    128    //���ڷ��ͻ���������////************************************
        #define cominbufleng  40  //���ڽ��ջ���������////************************************
        #define Heareat_Timeout  300 //������ʱ300*10ms
     
        #define PROTOCOL_TIMEOUT 5 //ͨѶ��ʱ5sPROTOCOL_RESET_NUM
        #define PROTOCOL_RESET_NUM 3 //��ʱ3�Σ���ʼ������

        //E�����������õ�ַ
        #define     ADDBLACK_MAP             0x0AA0
        #define     ADDBLACK_MAP_END         0x1A9F
        #define     ADDBLACK_SAVE_MAX        0x1AA0   //2�ֽڱ�������������
        #define     ADDBLACK_SAVE            0x1AA4
        #define     ADDBLACK_SAVE_END        0x2A9F

    void   opotocol_port_init(unsigned long baud);
    void   Configure_protocol (void);//��̨Э���ʼ��
    void   opotocol_state(void);//*******************************

    void  Set_Clockask(void);//����Ϊʱ��ͬ��
    void  Setshiftonce(void);
    void  SetGasruning(void);
    void  Setliushuirec(void);
    void  Setcardverify(UINT8 *BUF,UINT8 LEN);
    void  SetParaOnce(void);
    void  set_heareat(void);

    void protocol_sendstr(UINT8 len, UINT8 *buf);//fasong
    void send_heareat(void);    //��������
    void send_liushuirec(void);//ÿ�ʼ�����¼
    void send_lngstate(void);//������״̬
    void send_shift(void);    //�ְ���Ϣ
    void send_LNGparas(void); //����������
    void send_setpara(void);  //�����޸ķ���
    void send_newblacklist(void);  //����������
    void send_blacklist(void);  //���к����� һ��һ����
    void send_cardverify(void);//����֤
    void send_clockask(void);  //ʱ������/////send_DataErr
    void send_DataErr(void);  //���ʹ���

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
  volatile   UINT32    Protocol_tick;//���ж�ʱ�δ�
  volatile   UINT32  heareat_time;
   BOOL  opotocol_SW;     //��̨ͨ�ſ���
   BOOL  heareat_flag;
   UINT8  ORD_DATAPA;     //���ݰ�����
   UINT8 gcombufleng;  //���������ͽ�ֹλ��
   UINT8 gcomInbufleng;  //���������ս�ֹλ��
   UINT8 Com_Timeoutnum;
   BOOL  pototime_flag;     //��̨ͨ�ż�ʱ��־
   BOOL  pro_alarm;//��̨ͨ���쳣������־
   BYTE gComRF[combufleng];
   UINT16  crc_rece;
   BYTE gComIn[cominbufleng];
   UINT16 Rec_liushnum;//********
   UINT16 Rec_shiftidnum;//********
   UINT8 gComRFPos;
   UINT8   sq[4];//��̨ǹ����֤�ַ���
   UINT8 gComRec_OK;
   UINT16 cur_max_blacklist;    //��ǰ����������
   UINT8  cur_p_GID;//��ǰ����
   UINT8   sys_recPCtime[6];///////
   UINT8   VerCard[11];//��֤����10λ+1
   BOOL   Result_card;//��֤���
  float JQvolu;
  float JQ_money;

    typedef enum
  {
     MAX_NULL_FLAG = 0,
     liushuirec_flag,   //ÿ�ʼ�����¼���ޱ�ʶ
     lngGasruning_flag,  //������
    lngstate_flag ,     //������״̬���ޱ�ʶ
    shift_flag ,       //�ְ���Ϣ���ޱ�ʶ
    LNGparas_flag,     //�������������ޱ�ʶ
    newblacklist_flag, //�������������ޱ�ʶ
    blacklist_flag ,    //���к��������ޱ�ʶ    һ��һ����
    cardverify_flag,  //����֤���ޱ�ʶ
    clockask_flag,  //ʱ���������ޱ�ʶ
    setpara_flag

  }Protocol_state;



#endif	/* PROTOCOL_H */





