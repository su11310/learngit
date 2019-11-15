/* 
 * File:   ic_card.h
 * Author: Administrator
 *
 * Created on 2014锟斤拷1锟斤拷4锟斤拷, 锟斤拷锟斤拷7:52
 */

#ifndef IC_CARD_H
#define	IC_CARD_H
#define APDU_SUCCESS	0x90
#define APDUC_SUCCESS	0x59
#define APDUC_SUCCESS1	0x90
#define APDUC_SUCCESS2	0x00
#define APDUC_FAILE	0x4E
#define APDUC_NO_CARD	0x45
#define SELECT_FILE	0xa4
#define READ_BINARY	0xb0
#define WRITE_BINARY	0xd0
#define UPDATE_BINARY	0xd6
#define ERASE_BINARY	0x0e
#define VERIFY_PIN	0x20
#define CHANGE_PIN	0x24
#define	CREATE_FILE	0xe0
#define	DELETE_FILE	0xe4
#define	INVALIDATE	0x04
#define	REHABILITATE	0x44
#define LOADKEY 	0xDA
#define GET_CHALLENGE	0x84
#define INTERN_AUTH	0x88
#define EXTERN_AUTH	0x82
#define GET_RESPONSE	0xC0
#define UPDATE_RECORD   0xdc


#define	BULL_CP8_CLA	0x80
#define	PHILIPS_DS_CLA	0x0

#define CARD_CLA	    card_class
#define Apdu_Comm_Num   0x07  
#define CARD_APDU_ERR   0xaa
#define CARD_READ_ERR   0xbb
#define CARD_ERR_NOCARD  0xCC
#define CARD_SELECT_ERR   0xb2
#define CARD_READ_OK        0xcc
#define CARD_Modifybin_ERR 0xb0
#define CARD_Modifybin_OK 0xb1
#define CARD_2LEN       10
#define File_Cardinfo     0x01
#define File_Memoy        0x02
#define File_Gas          0x03
#define File_State        0x04
#define File_Password      0x05

#if 0
#define ATMEL_WRITE_FILE	0xB0
#define ATMEL_READ_FILE		0xB2
#define ATMEL_WRITE_CONFIG	0xB4
#define ATMEL_READ_CONFIG	0xB6
#define ATMEL_AUTH		0xB8
#define ATMEL_VERIFY_PIN	0xBA

#define WRITE_PIN	0
#define READ_PIN	1
#endif

typedef struct ApduPack
{
    UINT8  cmd1 ;
    UINT8  cmd2 ;
    UINT8  apdulen[2];
    UINT8 cla;
    UINT8 ins;
    UINT8 p1;
    UINT8 p2;
    UINT8 p3;
    UINT8 pdata[128];
    UINT8 pack_len;
}apdu_pk;
#if 0
typedef enum CARD_STATUS
{
  HAVE_CARD,
  NO_CARD,
  NO_RECOGNISE,
  CPU_CONTACTOR,
  CPU_TYPE_A,
  CPU_TYPE_B,
  M1_CARD,
  AT88SC_CARD,
  SLE4442_CARD,
  POWER_DOWN_MODULE,
  SLEEP_MODULE,
  ACTICE_MODULE,
  BUSY_MODULE,
  POWER_ON,
  POWER_OFF
}CARD_STATUS;
#endif
typedef enum Card_State//rg170705
{
  HAVE_CARD=0,
  NO_CARD,
  NO_RECOGNISE,
  CPU_CONTACTOR,
  CPU_TYPE_A,
  CPU_TYPE_B,
  M1_CARD,
  AT88SC_CARD,
  SLE4442_CARD
}card_state;

typedef enum APDU_STATUS
{
    APDUS_SUCCESS,
    APDUS_FAILE,
    APDUS_ERROR,
    APDUS_NO_CARD,
    APDUS_OUT_BUF,
    APDUS_AUTH_ERR,
    APDUS_DKQERR
}apdu_status;

typedef enum CARD_STATUS
{
    CARDS_NORMAL = 0,
    CARDS_NULLIFY,
    CARDS_GREY,
    CARDS_ERR,
    CARDS_NO_CARD
}card_status;
typedef enum CARD_TYPE
{
    CARDT_CLASS = 1,
    CARDT_COMPANY,
    CARDT_PERSON,
    CARDT_WORKER,
    CARDT_ADMINI,
    CARDT_ERROR,
    CARDT_SMALL,      //rg170717  
     CARDT_MOTHER,     //rg170717   
}card_type;
#if 0
typedef enum CARD_TYPE
{
    CARDT_CLASS = 0,
    CARDT_COMPANY,
    CARDT_PERSON,
    CARDT_WORKER,
    CARDT_ERROR,
}card_type;
#endif
typedef enum _lng_op_type
{
    PREE_MONEY,
    PREE_GASE,
    ACCOUNT_MONEY,
    ACCOUNT_GASS,
    CONSUM_ERROR,
}card_csum_type;
void Mainui_Disp_Cardinfo(UINT8 cardtype,UINT8 *cn,float YUER,float YUQI,UINT8 XFLX);
BOOL Get_Cardpsw(void);
UINT8 Save_cardpsw(UINT8 *psw);
void  ic_card_init(UINT32 baud);
void ic_card_active_sp();    /// ss190307  
void ic_card_dece_sp();       /// ss190307  
void  ic_query_status1();
//int card_getchal(unsigned char *chal);
int card_getchal(unsigned char *chal,UINT8 len);
extern UINT8 card_readbin_selmu(UINT8 filenum,UINT8 offset ,UINT8 datalen);
int external_authentication(unsigned char secret, unsigned char *data, int datalen);
int internal_authentication(unsigned char kn, unsigned char *data,int datalen);
int card_get_response(int exp_len);
//BOOL card_select_file(unsigned short fident, unsigned char type);
int card_select_mf();
int GetInto_infofile();
UINT8 GetCard01_info();
UINT8 GetCardX(UINT8 filenum);
//BOOL ReadCard_info(UINT8 *card_type,UINT8 * cn, float *card_preM,float * card_preg,UINT8 * XFLX);//获得卡信息，返回值为1表示获得信息，0为未获得信息。
//BOOL ReadCard_info(UINT8 *card_type,UINT8 * cn, float *card_preM,float *card_preg,float *ml,float *gl,UINT8 *XFLX);//获得卡信息，返回值为1表示获得信息，0为未获得信息。
BOOL ReadCard_info(UINT8 *card_type,UINT8 * cn, float *card_preM,float *card_preg,INT32 *card_preM_int,INT32 *card_preg_int,float *ml,float *gl,UINT8 *XFLX,UINT8 *dj,float *zkl,UINT8 *zkqx,UINT8 *cpbh,UINT8 *gpbh);//获得卡信息，返回值为1表示获得信息，0为未获得信息。
extern void oqry_cardinfo(void);
extern BOOL machine_has_card();
extern card_status ic_card_get_status();
extern card_status ic_card_get_status_nosel();
extern BOOL ic_card_get_info_nosel(UINT8 *buf, UINT8 *len);
extern BOOL ic_card_get_info(UINT8 *buf, UINT8 *len);
extern BOOL ic_card_put_status(card_status status);
extern BOOL ic_card_get_money(float * money);
extern BOOL ic_card_put_money(INT32  money);
extern BOOL ic_card_get_gass(float * gass);
extern BOOL ic_card_put_gass(INT32  gass);
extern BOOL ic_card_get_password(UINT8 * password, UINT8 *len);
extern BOOL ic_card_put_password(UINT8 * password, UINT8 len);
extern void olng_operate_card(void);
extern UINT8 * ic_operate_info(UINT8 *name, UINT8 * pstr,UINT8 * len);
extern UINT8 * ic_operate_info_int(UINT8 * pstr,UINT8 * len);
extern card_type ic_card_get_type(UINT8 * mbuf, UINT8 len);
extern void omodule_ic_test(void);
extern void Get_Car_Info();
extern UINT8 * inttoa(INT32 ye);
extern card_status machine_status_card();//RG170705
#endif	/* IC_CARD_H */

