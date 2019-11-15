/* 
 * File:   store.h
 * Author: felixluom
 *
 * Created on 2014年1月29日, 上午12:50
 */

#ifndef STORE_H
#define	STORE_H

#ifdef	__cplusplus
extern "C" {
#endif
    //块大小  16K = 16*1024 = 128*128
    //块数    1024
    //地址    0x000000 ~ 0xFFFFFF
    #define  REC_NANDFLASH_S_ADDR        0x0000
    #define  REC_NANDFLASH_END_ADDR      0xC35000  //以10万滚动存储  128 * 100000
    #define  REC_NANDFLASH_PAGES         782
    #define  REC_NANDFLASH_SIZE           128

    #define  SHIFT_NANDFLASH_S_ADDR      0xC3C000 //
    #define  SHIFT_NANDFLASH_PAGES       10
    #define  SHIFT_NANDFLASH_E_ADDR      0xE10C00
    #define  SHIFT_NANDFLASH_SIZE        128

    //time:14-03-20 rengang
    #define  PARA_NANDFLASH_S_ADDR      0xE1C000 //10000*32 1万条(5000)
    #define  PARA_NANDFLASH_PAGES       10
    #define  PARA_LENGTH                128
    #define  PARA_NANDFLASH_E_ADDR      0xFFFFFF           //4E200+0xC64000
#if 1
    UINT8 data_01[1024];
    UINT8 dataX[4][11];
    UINT8 signfun;
/*----------------------------               流水记录        80        ------------------------------------------*/
  typedef struct def_LCNG_Record
  {

    UINT8   rec_cardnum[16];       //IC卡号rec_cardnum[12];  15
    UINT32  rec_id;                 //枪流水号:4
    UINT32  rec_shift_id;          //班号rec_shift_id;：1
    UINT32  rec_gid;               //枪号  1

      float   rec_lcngnum;        //气量 99999.99    ---44
      float   rec_lcnprice;	     //单价 999.99       ---4
      float   rec_lcnM;         //金额 9999999.99``     ---4
      float   rec_card_preM;     //加气前IC余额 9999999.99  ---4
      float   rec_card_endM;     //加气后IC余额 9999999.99
      float   rec_card_preg;     //加气后计算余额 9999999.99
      float   rec_card_endg;     //加气后计算余额 9999999.99
      float   rec_sum_start;    //加气开始枪累 999999999.99
      float   rec_sum_end;      //加气开始枪累 999999999.99
      float   rec_begin_Press;         //加气开始压力 99.99
      float   rec_end_Press;         //加气结束压力 99.99
      UINT8   rec_Stime[6];          //开始时间 xx xx xx xx xx xx xx    15
      UINT8   rec_Etime[6];          //开始时间 xx xx xx xx xx xx xx
      UINT8   bErrCard;              //卡类型
      UINT8   rec_crc_hi;
      UINT8   rec_crc_low;
}_lcng_rec;//流水记录

/*----------------------------               班组记录  总长：40  BYTE           -----------------------------------*/
typedef struct def_LCNG_shift_rec
{
    UINT32   shift_rec_id;             //班组记录流水号：4
    UINT8    shift_card[15];           //班组卡号:15
    UINT8    shift_id;                 //班组号:1
    UINT8    shift_gid;                //枪号：1
    UINT8    shift_op_time[6];         //操作时间:6
    float    shift_s_mount;            //开始枪累：4
    float    shift_e_mount;            //结束枪累:4
    UINT8    shift_op_type;             //枪号:1
    float    shift_cash;                //IC记账金额:4
    }_lng_shift_rec;

 typedef struct
    {
     unsigned char    cardcn[15];       //插入卡号
     unsigned char    cardpassword[15]; //输入密码
     UINT8 CardState;                   //卡状态
 }pword;
#else

#endif


#endif	/* STORE_H */

