/* 
 * File:   store.h
 * Author: felixluom
 *
 * Created on 2014��1��29��, ����12:50
 */

#ifndef STORE_H
#define	STORE_H

#ifdef	__cplusplus
extern "C" {
#endif
    //���С  16K = 16*1024 = 128*128
    //����    1024
    //��ַ    0x000000 ~ 0xFFFFFF
    #define  REC_NANDFLASH_S_ADDR        0x0000
    #define  REC_NANDFLASH_END_ADDR      0xC35000  //��10������洢  128 * 100000
    #define  REC_NANDFLASH_PAGES         782
    #define  REC_NANDFLASH_SIZE           128

    #define  SHIFT_NANDFLASH_S_ADDR      0xC3C000 //
    #define  SHIFT_NANDFLASH_PAGES       10
    #define  SHIFT_NANDFLASH_E_ADDR      0xE10C00
    #define  SHIFT_NANDFLASH_SIZE        128

    //time:14-03-20 rengang
    #define  PARA_NANDFLASH_S_ADDR      0xE1C000 //10000*32 1����(5000)
    #define  PARA_NANDFLASH_PAGES       10
    #define  PARA_LENGTH                128
    #define  PARA_NANDFLASH_E_ADDR      0xFFFFFF           //4E200+0xC64000
#if 1
    UINT8 data_01[1024];
    UINT8 dataX[4][11];
    UINT8 signfun;
/*----------------------------               ��ˮ��¼        80        ------------------------------------------*/
  typedef struct def_LCNG_Record
  {

    UINT8   rec_cardnum[16];       //IC����rec_cardnum[12];  15
    UINT32  rec_id;                 //ǹ��ˮ��:4
    UINT32  rec_shift_id;          //���rec_shift_id;��1
    UINT32  rec_gid;               //ǹ��  1

      float   rec_lcngnum;        //���� 99999.99    ---44
      float   rec_lcnprice;	     //���� 999.99       ---4
      float   rec_lcnM;         //��� 9999999.99``     ---4
      float   rec_card_preM;     //����ǰIC��� 9999999.99  ---4
      float   rec_card_endM;     //������IC��� 9999999.99
      float   rec_card_preg;     //������������ 9999999.99
      float   rec_card_endg;     //������������ 9999999.99
      float   rec_sum_start;    //������ʼǹ�� 999999999.99
      float   rec_sum_end;      //������ʼǹ�� 999999999.99
      float   rec_begin_Press;         //������ʼѹ�� 99.99
      float   rec_end_Press;         //��������ѹ�� 99.99
      UINT8   rec_Stime[6];          //��ʼʱ�� xx xx xx xx xx xx xx    15
      UINT8   rec_Etime[6];          //��ʼʱ�� xx xx xx xx xx xx xx
      UINT8   bErrCard;              //������
      UINT8   rec_crc_hi;
      UINT8   rec_crc_low;
}_lcng_rec;//��ˮ��¼

/*----------------------------               �����¼  �ܳ���40  BYTE           -----------------------------------*/
typedef struct def_LCNG_shift_rec
{
    UINT32   shift_rec_id;             //�����¼��ˮ�ţ�4
    UINT8    shift_card[15];           //���鿨��:15
    UINT8    shift_id;                 //�����:1
    UINT8    shift_gid;                //ǹ�ţ�1
    UINT8    shift_op_time[6];         //����ʱ��:6
    float    shift_s_mount;            //��ʼǹ�ۣ�4
    float    shift_e_mount;            //����ǹ��:4
    UINT8    shift_op_type;             //ǹ��:1
    float    shift_cash;                //IC���˽��:4
    }_lng_shift_rec;

 typedef struct
    {
     unsigned char    cardcn[15];       //���뿨��
     unsigned char    cardpassword[15]; //��������
     UINT8 CardState;                   //��״̬
 }pword;
#else

#endif


#endif	/* STORE_H */

