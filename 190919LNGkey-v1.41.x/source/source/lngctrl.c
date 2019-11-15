/*
 * File:   lngctrl.c
 * Author: luom
 *
 * Created on 2014_01_15
 */
#include "../includes/global_def.h"
#define   ODD  0
#define   NEW  1
#define   SIMU_PREOOL             1
#define   ADD_GASS_NEED_CARD      1
#define   DRVGAIN_CHKLEN          10
#define   MAX_DATA_ERR_CNT        20
#define   MAX_MODBUS_ERR_CNT      10
#define   MAX_LNG_STOP_CNT        10
#define   TTUR_ADD_GASS           0
#define config_p1     ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
// ADC ref external | Disable offset test | Disable scan mode | Perform 2 samples | Use dual buffers | Use alternate mode
#define config_p2     ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON
// Use ADC internal clock | Set sample time
#define config_p3     ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
// Do not assign channels to scan
#define configscan  SKIP_SCAN_AN3
#define configport  ENABLE_AN3_ANA
enum _e_lng_op_err_
{
    _e_lng_op_err_noprecool = 1,
    _e_lng_op_err_modbus,
    _e_lng_op_init_err_modbus,
    _e_lng_op_data_err_modbus,
    _e_lng_op_err_shift,
    _e_lng_op_init_err,
    _e_lng_card_info,
    _e_lng_op_card_error,
    _e_lng_op_money_shift,
    _e_lng_op_fix_money,
};
typedef struct operate_time
{
 UINT8  time_m;
 UINT8  time_s;
}operate_time;
struct prcool_parament
{
 UINT8  chk_cnt;
 float  c_max_gain;
 float  c_min_gain;
 float  temp;
 float  gain;
 BOOL   show_up;
}prcool_parm;

operate_parme oparme;
static operate_time otime;
UINT8 simmoney = 50;
static UINT8 operata_modbus_err = 0;
static UINT8 _lng_stop_cnt = 0;
static UINT8 operata_data_err = 0;
static float cur_calnumbak = 0.0;
static UINT8 lng_op_err_type = 0;
static float back_voluent;
static BOOL preecool_check(BOOL binit);
void show_precool_success(void);
void olng_vctrl_switch_on(UINT8 sw)
{
    switch(sw)
    {
        case 1:
            SOLENOID_1_OPEN();
            break;
        case 2:
            SOLENOID_2_OPEN();
            break;
        case 3:
            SOLENOID_3_OPEN();
            break;
        case 4:
            SOLENOID_4_OPEN();
            break;
        case 5:
            SOLENOID_5_OPEN();
            break;
        case 6:
            SOLENOID_6_OPEN();
            break;
        default:
            break;
    }

}
void olng_vctrl_switch_off(UINT8 sw)
{
    switch(sw)
    {
        case 1:
            SOLENOID_1_CLOSE();
            break;
        case 2:
            SOLENOID_2_CLOSE();
            break;
        case 3:
            SOLENOID_3_CLOSE();
            break;
        case 4:
            SOLENOID_4_CLOSE();
            break;
        case 5:
            SOLENOID_5_CLOSE();
            break;
        case 6:
            SOLENOID_6_CLOSE();
            break;
        default:
            break;
    }
}
void olng_vctrl_pump_sw(UINT8 sw)
{

    switch(sw)
    {
        case 1:  //停
            VK1_CLOSE();
            PLC1_CLOSE();
            PLC2_CLOSE();
            break;
        case 2: //预冷
            VK1_OPEN();
            PLC1_OPEN();
            PLC2_CLOSE();
            break;
        case 3: //加注
            VK1_OPEN();
            //SOLENOID_5_OPEN();
            //SOLENOID_6_CLOSE();
            PLC1_OPEN();
            PLC2_OPEN();
            break;
        case 4: //待机
            VK1_OPEN();
            PLC1_CLOSE();
            PLC2_OPEN();
            //SOLENOID_5_OPEN();
            //SOLENOID_6_OPEN();
            break;

    }
}
void olng_vctrl_init(void)
{
   PORTSetPinsDigitalOut(IOPORT_G, BIT_6|BIT_7);
   PORTSetPinsDigitalOut(IOPORT_D, BIT_12|BIT_13);
   PORTSetPinsDigitalOut(IOPORT_B, BIT_8|BIT_9);
   //solenoid_open(SOLENOID_1);
   SOLENOID_1_CLOSE();
   SOLENOID_2_CLOSE();
   SOLENOID_3_CLOSE();
   SOLENOID_4_CLOSE();
   SOLENOID_5_CLOSE();
   SOLENOID_6_CLOSE();
}
/*------------------------------------------加气过程中显示界----------------------------------------------------------*/
void olng_operate_disp(BOOL bInit)
{
	if( bInit )
	{
		    olcd_clearsCreen();
		    olcm_dispprintf(1,1,"正在加气");
		    olcm_dispprintf(0,2,"流速:");
		    olcm_dispprintf(0,3,"压力:");
                    olcm_dispprintf(0,4,"温度:");
                    olcm_dispprintf(3, 2,"%3.02f",0.00);//cur_lngnum);
		    olcm_dispprintf(3, 3,"%3.02f",0.00);//cur_lngsum);
                    olcm_dispprintf(3, 4,"%3.02f",0.00);//cur_lngsum);
	}
        else
	{
                   // olcm_dispprintf(6,1,"%d", _sys_tick_);
		    olcm_dispprintf(3,2,"%3.02f",cur_lngrate);//cur_lngnum);
		    olcm_dispprintf(3,3,"%3.02f",cur_press);//cur_lngsum);
                    olcm_dispprintf(3,4,"%3.02f",cur_lngtemp);//cur_lngsum);

	}
}
void show_time(BOOL flag)
{
    if(_sys_tick_ == 60)
    {
        otime.time_m +=1;
        otime.time_s = 0;
        _sys_tick_ = 0;
    }
    else
        otime.time_s = _sys_tick_;
    if(flag)
    	{
    	  if(otime.time_s < 10)
            olcm_dispprintf(5,1," %2d:0%d", otime.time_m, otime.time_s );
          else
            olcm_dispprintf(5,1," %2d:%d", otime.time_m, otime.time_s );
    	}
    else
    	{
    	if(otime.time_s < 10)
          olcm_dispprintf(5,1," %2d 0%d", otime.time_m, otime.time_s );
         else
	  olcm_dispprintf(5,1," %2d %d", otime.time_m, otime.time_s );
    	}

}
void olng_procool_disp(BOOL bInit)
{
	if( bInit )
	{
                    olcd_clearsCreen();
		    olcm_dispprintf(1,1,"正在预冷");
		    olcm_dispprintf(0,2,"流速:");
                    olcm_dispprintf(0,3,"增益:");
		    olcm_dispprintf(0,4,"温度:");
                    olcm_dispprintf(3,2,"%3.02f",0.00);//cur_lngnum);
                    olcm_dispprintf(3,3,"%3.02f",0.00);
		    olcm_dispprintf(3,4,"%3.02f",0.00);//cur_lngsum);
	}
        else
	{
            olcm_dispprintf(3,2,"%3.02f",cur_lngrate);//，cur_lngtemp);//cur_lngnum);
            olcm_dispprintf(3,3,"%3.02f",cur_lnggain);
            olcm_dispprintf(3,4,"%3.02f",cur_lngtemp);//cur_lngdensty);//cur_lngsum);

                    //olcm_dispprintf(1,4,"%3.02f",cur_lngrate);//cur_lngsum);
                    //olcm_dispprintf(5,4,"%3.02f",cur_press);//cur_lngsum);
	}
}
void show_operat_stop()
{
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"加气结束");
    olcm_dispprintf(0,2,"气量：%.2f",oparme.c_voluent);
    olcm_dispprintf(0,3,"金额：%.2f",oparme.c_money);
}
void  show_money(UINT8 line, float money)
{
    UINT8   buf[16];
    memset(buf, 0, sizeof(buf));
    sprintf(buf,"%.2f", money);
    olcm_dispprintf(0,line,"余额：");
    olcm_dispprintf(3,line,buf);
    oprint_printf("max money is %f\r\n",money);
}
void show_constum_type(UINT8 line, card_csum_type type)
{
    switch(type)
    {
        case PREE_MONEY:
             olcm_dispprintf(2,line,"预付金额");
             break;
        case PREE_GASE:
             olcm_dispprintf(2,line,"预付气量");
            break;
        case ACCOUNT_MONEY:
             olcm_dispprintf(2,line,"记账金额");
             break;
        case ACCOUNT_GASS:
             olcm_dispprintf(2,line,"记账气量");
             break;
    }
}
void show_card_type(UINT8 line,card_type type)
{
    olcm_dispprintf(0,line,"卡类：");
    switch(type)
    {
        case CARDT_CLASS:
            olcm_dispprintf(3,line,"班组卡");
            break;
       case CARDT_COMPANY:
           olcm_dispprintf(3,line,"公司卡");
            break;
       case CARDT_PERSON:
           olcm_dispprintf(3,line,"用户卡");
            break;
       case CARDT_WORKER:
           olcm_dispprintf(3,line,"员工卡");
            break;
    }
}
void show_card_id(UINT8 line, UINT8 *id)
{
    UINT8 buf[30];
    sprintf(buf, "卡号:%s", id );
    //olcm_dispprintf(0,line,buf);
    olcd_dispstr(0, line, buf,16);
}
void oprint_operate_rec(void)
{
    oprint_header_cmd();
    oprint_printf("----欢迎使用LNG加气机----\r\n"); //cur_sysparas
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");

    oprint_printf("单价:%.02f\r\n", cur_sysparas.p_Price);
    oprint_printf("枪号:%02d\r\n", cur_sysparas.p_gid);
    oprint_printf("回气量:%02d\r\n", oparme.back_sum);
    oprint_printf("加气量:%.02f\r\n", oparme.c_voluent);
    oprint_printf("金额:%.02f\r\n", oparme.c_money);
    //oprint_printf("加气站编号:%.02f\r\n", cur_calsum);
    oprint_printf("\r\n");
    oprint_printf("\r\n");

    oprint_printf("--烟台市xxxx路xxxx加气站--\r\n");
    oprint_printf("------欢迎下次光临------\r\n");
 //   oprint_normal_cmd();

}

void show_precool_success(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"预冷成功");
    olcm_dispprintf(0,2,"流速:%3.02f", cur_lngrate);
    olcm_dispprintf(0,3,"增益:%3.02f", cur_lnggain);
    olcm_dispprintf(0,4,"温度:%3.02f", cur_lngtemp);
}

/*---------------------------------------------------------------------------------------------------------------------
 *                                        **********预冷过程***********
---------------------------------------------------------------------------------------------------------------------*/
/*
 预冷状态：
   当加气枪安插在加气枪座上时，系统进入预冷操作后，切断阀1开，切断阀2闭；系统给与PLC的信号为：“10”；
 * 预冷过程中实时监测温度、增益等参数是否满足加气条件，若满足，则进入到：预冷成功状态；若在一定时间段内
 * （时间可设置，默认为无穷大），不能达到加气条件，则视为预冷失败，则进入到：上电待机状态；
预冷成功状态：
当系统遇冷成功之后，切断阀1关，切断阀2开；系统给与PLC的信号为：“10”；此时等待加气动作，若在设定时间段内
（时间可设置，默认为5min；用于频繁加气时，减少预冷动作。）进行加气动作，则进入到：加气状态；若在设定时间内
 未进行任何动作，则进入到：上电待机状态；
加气状态：
系统预冷成功之后，进行加气动作，切断阀1开，切断阀2闭；系统给与PLC的信号为：“11”；加气过程中系统实时监控温度、
增益等参数是否满足停机条件，若满足，则加气完成，进入到：预冷成功状态；若不满足，则继续加气。
停机条件：
 */

BOOL preecool_check(BOOL binit)
{
    UINT8 cnt = 5;
    if(binit)
    {
       memset(&prcool_parm, 0, sizeof(prcool_parm));
#if __SIMU_DEBUG_
        prcool_parm.temp = cur_sysparas.p_Ptemp;
#else
        prcool_parm.temp = -cur_sysparas.p_Ptemp;
#endif
       prcool_parm.gain = cur_sysparas.p_PGain;
       prcool_parm.show_up = TRUE;

       //as the precoll success, check the add gress condition
       if(_b_run_lng_flag == TRUE)
       {
           while(1)
           {
               olng_operate_act();
               if(prcool_parm.temp < cur_lngtemp || prcool_parm.gain < cur_lnggain)
                   return FALSE;
               if(--cnt <= 0)  break;
           }
           return TRUE;
       }
       olng_procool_disp(TRUE);
       otime.time_m = otime.time_s = 0;

    }
    else
    {
       olng_procool_disp(FALSE);
      oprint_printf("YL->");sys_uart_debug_info();
      if( cur_lngtemp > prcool_parm.temp || cur_lnggain > prcool_parm.gain)  return FALSE;
      prcool_parm.c_min_gain = cur_lnggain;
      if( fabs(prcool_parm.c_max_gain - prcool_parm.c_min_gain) < 3.00)
      {
         if(++prcool_parm.chk_cnt > DRVGAIN_CHKLEN )
            return TRUE;
      }
      else
      {
              prcool_parm.c_max_gain = prcool_parm.c_min_gain;
              prcool_parm.chk_cnt = 0;
       }
    }
    return FALSE;
}
void  olng_precool_start(void)
{
    if(preecool_check(TRUE))
    {
        eVirtualKey = _KEY_PRECOOL_SUCCESS;
        return;
    }
    PRECOOL_CTRL();
    _sys_tick_ = 0;
    eVirtualKey = _EVENT_TRUE;
}
void  olng_precool_runing(void)
{
        if(preecool_check(FALSE))
        {
             eVirtualKey = _KEY_PRECOOL_SUCCESS;
             PRECOOL_SUSSE();
             return;
        }
        if(osys_getkey(_KEY_STOP_EV_,1) == TRUE)
        {
                eVirtualKey = _KEY_STOP_EV_;
                _b_run_lng_flag = FALSE;
                IDLE_CTRL();
                return;
          }
       show_time(TRUE);
       return;
}
void olng_precool_stop(void)
{
     olcm_dispprintf(0,1,"    预冷停止    ");
     _b_run_lng_flag = FALSE;
     IDLE_CTRL();
     osys_getkey(_KEY_EXIT_EV_, 5);
     oui_main_ui();
}
void olng_precool_success(void)
{
    show_precool_success();
     _b_run_lng_flag = TRUE;
     _run_lng_tick = 0;
     osys_getkey(_KEY_EXIT_EV_, 5);
     oui_main_ui();
     omodbus_read_g_flow();
     back_voluent = cur_cngnum;
     eVirtualKey = _EVENT_TRUE;
}

void olng_operate_main_ui(void)
{
     //oprint_printf("_precool_waitgas_time is %d\r\n",_precool_waitgas_time);
     if(_b_run_lng_flag)
     {
           olcm_dispprintf(2,3,"请加气");
           oprint_printf("please add gass\r\n");
     }
     else
      {
          oprint_printf("please pree cool \r\n");
          olcm_dispprintf(2,3,"请预冷");
       }
     eVirtualKey = _EVENT_TRUE;
}

/*加气状态
1.卡片判断：判断卡中的消费类型和判断卡中的余额。如果消费类型为扣款消费，则直接把气量换算为金额进行判断。如果消费类型为气量直接换算
 * 为金额进行判断。如果把数值提高若干倍数，可以增加计量的精度。
2.加气条件判断：对加气的条件进行判断，如果
3.加气结束判断：
4.回气量的计算：

 */
/*---------------------------------------------------------------------------------------------------------------------
 *                             **********加气前，检查IC卡的信息***********
---------------------------------------------------------------------------------------------------------------------*/
/* 1.如果用户没有卡，则用班组卡进行加气，加气的金额由加气员工收取；
 * 2. 最小加气量在卡中读取，如果卡中余额不足卡中最小的加气金额，则显示余额不足。
 * 3.如果用户定额加气，输入的值大于卡中余额，则也显示余额不足。
 */
BOOL olng_operate_get_card()
{
    float  min_money;
    float  min_gass;
    UINT8   len,*pinfo;
    UINT8   buf[20];
    card_info_len = sizeof(global_ic_card_info);
    memset(global_ic_card_info, 0, card_info_len);
    oparme.card_status = ic_card_get_status();
    if(CARDS_NORMAL != oparme.card_status)
    {
        eVirtualKey = _KEY_VIRTUAL_2_EV_;
        lng_op_err_type = _e_lng_op_card_error;
        return FALSE;
    }
    if(ic_card_get_info(global_ic_card_info, &card_info_len) == FALSE)
    {
        eVirtualKey = _KEY_VIRTUAL_2_EV_;
        lng_op_err_type = _e_lng_card_info;
        return FALSE;
    }
    pinfo = ic_operate_info("CN",global_ic_card_info, &len);
    memset(oparme.card_id, 0, sizeof(oparme.card_id));
    memcpy(oparme.card_id, pinfo, len);
    pinfo = ic_operate_info("CDT",global_ic_card_info, &len);
    oparme.card_type = ic_card_get_type(pinfo,len);
    pinfo = ic_operate_info("CONT",global_ic_card_info, &len);
    oparme.cst_type = card_get_cstype(pinfo, len);
    switch(oparme.cst_type)
    {
        case   PREE_MONEY:
              memset(buf, 0, sizeof(buf));
              pinfo = ic_operate_info("ML",global_ic_card_info, &len);
              memcpy(buf, pinfo,len);
              min_money = atof(buf);
             if(ic_card_get_money(&oparme.card_money))
             {
                 if(oparme.card_money < min_money)
                     goto error_m;
                oparme.maxmoney = oparme.card_money;
             }
            break;
        case PREE_GASE:
              memset(buf, 0, sizeof(buf));
              pinfo = ic_operate_info("GL",global_ic_card_info, &len);
              memcpy(buf, pinfo,len);
              min_gass = atof(buf);
             if(ic_card_get_gass(&oparme.card_gass))
             {
                 if(oparme.card_gass < min_gass)
                      goto error_m;
                 oparme.maxmoney = oparme.card_gass*cur_sysparas.p_Price;
             }
            break;
        case ACCOUNT_MONEY:
             memset(buf, 0, sizeof(buf));
             pinfo = ic_operate_info("ML",global_ic_card_info, &len);
             memcpy(buf, pinfo,len);
             min_money = atof(buf);
             if(ic_card_get_money(&oparme.card_money))
             {
                 if(oparme.card_money + min_money < 0)
                     goto error_m;
                oparme.maxmoney = oparme.card_money + min_money;
             }
            break;
        case ACCOUNT_GASS:
              memset(buf, 0, sizeof(buf));
              pinfo = ic_operate_info("GL",global_ic_card_info, &len);
              memcpy(buf, pinfo,len);
              min_gass = atof(buf);
             if(ic_card_get_gass(&oparme.card_gass))
             {
                 if(oparme.card_gass + min_gass < 0)
                      goto error_m;
                 oparme.maxmoney = (oparme.card_gass + min_gass)*cur_sysparas.p_Price;
             }
            break;
    }
    olcd_clearsCreen();
    show_constum_type(1,oparme.cst_type);
    show_card_type(2,oparme.card_type);
    show_money(3,oparme.maxmoney);
    show_card_id(4,oparme.card_id);
        //定额加气
    if(oparme.b_fixmop || oparme.b_fixnop)
    {
      if(oparme.fix_money > oparme.maxmoney ) //set the biggest money is the setting money
         goto error_m;
      else
         oparme.maxmoney = oparme.fix_money;
    }
   ic_card_put_status(CARDS_GREY);
   oprint_printf("check card success\r\n");
   return TRUE;
 error_m: memset(&oparme, 0 , sizeof(operate_parme));
          lng_op_err_type = _e_lng_op_money_shift;
          eVirtualKey = _KEY_VIRTUAL_2_EV_;
          return FALSE;
    }

BOOL olng_operate_put_card()
{
    float pay;
    switch(oparme.cst_type)
    {
        case   PREE_MONEY:
              pay =oparme.card_money - oparme.c_money;
            if(ic_card_put_money(pay) == FALSE) return FALSE;
            break;
        case PREE_GASE:
            pay =oparme.card_gass - oparme.c_voluent;
            if(ic_card_put_gass(pay)== FALSE) return FALSE;
            break;
        case ACCOUNT_MONEY:
            pay =oparme.card_money - oparme.c_money;
            if(ic_card_put_money(pay) == FALSE) return FALSE;
            break;
        case ACCOUNT_GASS:
             pay =oparme.card_gass - oparme.c_voluent;
            if(ic_card_put_gass(pay)== FALSE) return FALSE;
            break;
    }
    return ic_card_put_status(CARDS_NORMAL);
}
/*------------------------------------------加气结束，存储加气信息---------------------------------------------------*/
void olng_store_flowrecord(void)
{

     _lcng_rec  cur_rec;
     UINT16 addr;
     //oprint_printf("ADD GRASS cur_max_recid is %d\r\n", cur_max_recid);
     //cur_rec_shiftinfo.g_uid += 1;

     memset(cur_rec.rec_cardnum, 0, sizeof(_lcng_rec));
     memcpy(cur_rec.rec_cardnum, oparme.card_id, strlen(oparme.card_id));
     //cur_max_recid += 1;
     cur_rec.rec_id = cur_max_recid + 1;                 //枪流水号:4
     cur_rec.rec_shift_id  = cur_shift_loginfo.shift_id;          //班号rec_shift_id;：1
     cur_rec.rec_gid = cur_shift_loginfo.shift_gid;              //枪号  1

     cur_rec.rec_lcngnum = oparme.c_voluent;        //气量 99999.99    ---44
     cur_rec.rec_lcnprice =  cur_sysparas.p_Price;//单价 999.99       ---4
     cur_rec.rec_lcnM = oparme.c_money;         //金额 9999999.99``     ---4
     if(oparme.cst_type == PREE_MONEY || oparme.cst_type == ACCOUNT_MONEY )
     {
         cur_rec.rec_card_preM = oparme.card_money;                        //加气前IC金额余额 9999999.99  ---4
         cur_rec.rec_card_endM = oparme.card_money - oparme.c_money;     //加气后IC金额余额 9999999.99
     }
     if(oparme.cst_type == PREE_GASE || oparme.cst_type == ACCOUNT_GASS )
     {
         cur_rec.rec_card_preg = oparme.card_money;                       //加气前IC气量余额 9999999.99  ---4
         cur_rec.rec_card_endg = oparme.card_money - oparme.c_money;     //加气后IC气量余额 9999999.99
     }

     cur_rec.rec_sum_start = cur_shift_loginfo.shift_e_mount;    //加气开始枪累 999999999.99
     cur_rec_shiftinfo.gun_total += oparme.c_voluent;
     cur_rec.rec_sum_end =  cur_rec_shiftinfo.gun_total;      //加气结束枪累 999999999.99
     cur_rec.rec_begin_Press = oparme.begin_press;         //加气开始压力 99.99
     cur_rec.rec_end_Press = oparme.end_press;         //加气结束压力 99.99
     memcpy(cur_rec.rec_Stime, oparme.time, 6);
     ortcc_read_time(cur_rec.rec_Etime);

     addr = REC_NANDFLASH_S_ADDR+(cur_max_recid)*REC_NANDFLASH_SIZE;

     onand_wtBuff(addr, (UINT8 *)&cur_rec, sizeof(_lcng_rec));
     cur_max_recid += 1;
     cur_sysparas.p_curflow  =  cur_max_recid;

     cur_rec_shiftinfo.g_uid = cur_max_recid;
     cur_rec_shiftinfo.c_money += oparme.c_money;
     cur_rec_shiftinfo.c_sum += oparme.c_voluent;
     cur_rec_shiftinfo.g_total += 1;
     //cur_rec_shiftinfo.gun_total += oparme.c_voluent;//lin 0409
     //cur_rec_shiftinfo.
     cur_rec_shiftinfo.gun_money += oparme.c_money;
     if(oparme.card_type == CARDT_WORKER)
     {
         cur_rec_shiftinfo.c_cash += oparme.c_money;
     }
     addr = ((cur_max_recid%_SHIFT_SYSINFO_PAGES_)*_SHIFT_SYSINFO_PAGE_SZIE_) + _SHIFT_SYSPARAS_EEP_ADDR_P1;
     o24lcxxx_write_bytes_ex(addr,(UINT8*)&cur_rec_shiftinfo,sizeof(_rec_shift_info)); //

     o24lcxxx_write_bytes_ex(_REC_SYSPARAS_EEP_ADDR_P0,(UINT8*)&cur_sysparas,sizeof(Sysparas)); //
     //show_sys_recod(cur_rec_shiftinfo);
     oqry_rec_disp(cur_max_recid, TRUE);//wang3-31
 }
/*
  oprint_printf("ADD GASS store id is %d, money %f, voluent %f\r\n", cur_rec_shiftinfo.g_uid, oparme.c_money,  oparme.c_voluent);
  oprint_printf("RECORD  money %f, voluent %f\r\n",  cur_rec.rec_lcnM,cur_rec.rec_lcngnum);
 */
/*-----------------—       读取流量计和压力传感器信息                           ------------------*/
void olng_operate_act(void)
{
        float value;
        if( omodbus_read_auto_buffer(MODBUS_LNG_L_ADDR,_MODBUS_L_AUTO_RM_BUF_LEN) == FALSE)
        {
            if( ++operata_modbus_err > MAX_MODBUS_ERR_CNT)
            {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                lng_op_err_type = _e_lng_op_err_modbus;
                ////ERR
                return;
            }
        }
        value = olng_psensor_read_adc(10);
        cur_press = (cur_sysparas.press_parm_a*value+cur_sysparas.press_parm_b)/1000;
        operata_modbus_err = 0;
}
/*-------------------          加气条件不足预冷                                  ------------------*/
void olng_operate_precool(void)
{
    //olng_preesmall_disp(FALSE);

    if(preecool_check(FALSE))
    {
         oparme.begin_sum_v = cur_lngnum;
         _b_run_lng_flag = TRUE;
         _b_running_flag = TRUE;
         _run_lng_tick = 0;
         olng_operate_disp(TRUE);
         LNG_ADD_GASS();
         ortcc_read_time(oparme.time);
         eVirtualKey = _EVENT_TRUE;
        return;
    }
    eVirtualKey = _KEY_VIRTUAL_3_EV_;
    return;

}
void olng_start_act(void)
{
    operata_modbus_err = 0;
    _lng_stop_cnt      = 0;
    operata_data_err   = 0;
    oparme.c_money = 0;
    oparme.c_voluent = 0;
    oparme.b_stop = FALSE;
    lng_op_err_type = 0;
    cur_calnumbak = 0.00;
    #if  __SIMU_DEBUG_
          _simu_lngnum = 0;
          _simu_tick = 0;
         _b_simu_lng = TRUE;
    #endif

    if( FALSE == _b_init_ok)  //未初始化
    {
        eVirtualKey = _KEY_VIRTUAL_2_EV_;
        lng_op_err_type = _e_lng_op_init_err;
        return;
    }
    if(1 != b_shift_ok )   //未上班
    {
        eVirtualKey = _KEY_VIRTUAL_2_EV_;
        lng_op_err_type = _e_lng_op_err_shift;
        return;
    }
     if( _b_run_lng_flag == FALSE)  //未预冷
    {
        eVirtualKey = _KEY_VIRTUAL_2_EV_;
        lng_op_err_type = _e_lng_op_err_noprecool;
        return;
    }

    if(olng_operate_get_card() == FALSE) return; //  check the card inforametion, if the card error,show error
    if(preecool_check(TRUE))  // check the preecoll condition for   adding  gass
    {
         oparme.begin_sum_v = cur_lngnum;
         _b_run_lng_flag = TRUE;
         _b_running_flag = TRUE;
         _run_lng_tick = 0;
#if  __SIMU_DEBUG_
          _simu_lngnum = 0;
          _simu_tick = 0;
         _b_simu_lng = TRUE;
#endif
         olng_operate_disp(TRUE);
         LNG_ADD_GASS();          // execute the add gass action
        ortcc_read_time(oparme.time);
        eVirtualKey = _EVENT_TRUE;

    }
    else  //加气条件不满足，小循环预冷，CVK1加气阀关，CVK2待机阀开，给PLC的信号为10
    {
        _b_run_lng_flag = FALSE;
        _b_running_flag = FALSE;
        PRECOOL_SMALL();
        olng_procool_disp(TRUE);
        eVirtualKey = _KEY_VIRTUAL_3_EV_;
        return;
    }
}
/*------------------        正在加气，判断结束                                --------------------*/
void olng_operate_running(void)
{
    show_time(FALSE);
    if(eVirtualKey == _KEY_VIRTUAL_2_EV_)
        return;
    if(_b_running_flag)
    {
        oparme.end_sum_v = cur_lngnum;
 #if  __SIMU_DEBUG_
if(_simu_lngnum > oparme.c_voluent)
        {
            oparme.c_voluent = _simu_lngnum;
            oparme.c_money = oparme.c_voluent*cur_price;
         
        }
#else
        if(oparme.end_sum_v > oparme.begin_sum_v)
        {
                 oparme.c_voluent = oparme.end_sum_v - oparme.begin_sum_v;
                 cur_calnum = oparme.end_sum_v - oparme.begin_sum_v;
                 oparme.c_voluent = sys_get_float(oparme.c_voluent);
                
                if(cur_calnum < cur_calnumbak || fabs(cur_calnum-cur_calnumbak) > 10)  //流量计异常数据
                {
                    operata_data_err++;
                    cur_calnum = cur_calnumbak;
                    if(operata_data_err > MAX_DATA_ERR_CNT)
                    {
                        eVirtualKey = _KEY_VIRTUAL_EV_;
                        lng_op_err_type = _e_lng_op_data_err_modbus;
                        return;
                    }
                }
                cur_calnumbak = cur_calnum;
               oparme.c_money = oparme.c_voluent*cur_price;
               oparme.c_money = sys_get_float(oparme.c_money);
        }
#endif
        odisp_disp(oparme.c_voluent, oparme.c_money, FALSE);
        //oprint_printf("AG->");sys_uart_debug_info();
        olng_operate_disp(FALSE);
        //定量加满
        if(oparme.b_fixmop == TRUE || oparme.b_fixnop == TRUE) //定额加气
        {
            if( (oparme.c_money + 0.01) >= oparme.maxmoney )
            {
                OPERATE_SUCCESS();
                eVirtualKey = _KEY_STOP_EV_;
                return;
            }
         }
         if(( oparme.c_money + 0.5) > oparme.maxmoney )//余额不足
         {
            OPERATE_SUCCESS();
            eVirtualKey = _KEY_STOP_EV_;
            return;
         }
        if(cur_lngrate > cur_sysparas.p_EndR+10)  oparme.b_stop = TRUE;
         if(cur_lngrate < cur_sysparas.p_EndR && oparme.b_stop == TRUE)//模拟停机条件
         {
             OPERATE_SUCCESS();
             eVirtualKey = _KEY_VIRTUAL_1_EV_;//_KEY_VIRTUAL_1_EV_;
             return;
         }
        show_time(TRUE);
        if(osys_getkey(_KEY_STOP_EV_, 1))
             eVirtualKey = _KEY_STOP_EV_;
         eVirtualKey = _EVENT_TRUE;
     }

}

/*------------------        加气结束，判断累加                                 -----------------*/
void olng_operate_repeat(void)
{
     _b_running_flag = FALSE;
     //_simu_lngnum = 0;
#if __SIMU_DEBUG_
     _b_simu_lng = FALSE;
#endif
    show_operat_stop();
    odisp_disp(oparme.c_voluent, oparme.c_money, TRUE);
    olcm_dispprintf(0,4,"  累加请按确定");
    if(osys_getkey(_KEY_ENTER_EV_, 100))
    {
         olng_operate_disp(TRUE);
#if __SIMU_DEBUG_
         simmoney += 50;
         _b_simu_lng = TRUE;
#endif
         eVirtualKey =_EVENT_TRUE;
         LNG_ADD_GASS();
         return;
    }
    eVirtualKey =  _KEY_STOP_EV_;
}



/*-----------------         加气结束，结算金额                                  ----------------*/
void olng_operate_stop(void)
{
      OPERATE_SYOP();
     _b_running_flag = FALSE;
     _run_lng_tick = 0;
#if __SIMU_DEBUG_  //模拟
        _b_simu_lng = FALSE;
        _simu_lngnum = 0;
        simmoney = 0;
#endif
    show_operat_stop();
     omodbus_read_g_flow();
     oparme.back_sum = cur_cngnum - back_voluent;
     back_voluent = cur_cngnum;
    odisp_disp(oparme.c_voluent, oparme.c_money, TRUE);
    if(olng_operate_put_card())
    {
          olcm_dispprintf(2,4,"扣款成功");
          olng_operate_act();
          oparme.end_sum_v = cur_lngnum;
          olng_store_flowrecord();
         
    }
    else
          olcm_dispprintf(2,4,"扣款失败");
     oprint_operate_rec();
     oparme.c_money = 0.00;
     oparme.c_voluent = 0.00;
    _b_run_lng_flag = TRUE;
    _run_lng_tick = 0;
    eVirtualKey =  _KEY_EXIT_EV_;
}

void olng_system_err_stop(void)
{
        IDLE_CTRL();
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"----系统错误----");
        switch(lng_op_err_type)
        {
            case 1:
               olcm_dispprintf(0,2,"    未预冷");
               break;
            case _e_lng_op_err_shift:
               olcm_dispprintf(0,2,"    未上班");
               break;
            case _e_lng_op_card_error:
            {
               olcd_clearsCreen();
               olcm_dispprintf(0,1,"  卡类型错误");
               switch(oparme.card_status )
               {
                   case CARDS_GREY:
                        olcm_dispprintf(0,2,"  灰卡");
                        break;
                   case CARDS_ERR:
                        olcm_dispprintf(2,2,"请插卡!!");
                        break;
                   case CARDS_NULLIFY:
                       olcm_dispprintf(0,2,"  无效卡");
                       break;
               }
               break;
            }
            case _e_lng_op_money_shift:
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"  卡类型错误");
                olcm_dispprintf(2,2,"余额不足");
                break;
            case _e_lng_card_info:
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"  卡类型错误");
                olcm_dispprintf(2,2,"读取卡信息失败");
                break;
            case _e_lng_op_fix_money:
                olcd_clearsCreen();
                olcm_dispprintf(2,1,"定量错误");
                //olcm_dispprintf(1,2,"加气量错误");
                 olcm_dispprintf(1,2,"小于最小加气量");
                break;
       }
       olcm_dispprintf(0,3,"  错误代码:%d", lng_op_err_type);
       //ic_card_put_status(CARDS_NORMAL);
       //_precool_waitgas_time = cur_sysparas.p_PDelay;
       eVirtualKey = _KEY_EXIT_EV_;
    //_b_run_lng_flag = FALSE;
}

void olng_operate_err_stop(void)
{
           _run_lng_tick = 0;
           IDLE_CTRL();
           olcd_clearsCreen();
           olcm_dispprintf(0,1,"系统错误:%d", lng_op_err_type);
	   odisp_disp(oparme.c_money, oparme.c_voluent, TRUE);
           olng_store_flowrecord();
           //olng_operate_disp(FALSE);
           show_operat_stop();
#if  __SIMU_DEBUG_
	   _b_simu_lng = FALSE;
           _b_running_flag = FALSE;
           _simu_lngnum = 0;
#endif
            _b_run_lng_flag = FALSE;
            _b_running_flag = FALSE;
            ic_card_put_status(CARDS_NORMAL);
            oprint_operate_rec();
            //cur_lngnum = 0.00;
}
/*----------------------------------------------------------------------------------------------
                                         定量加气
 ----------------------------------------------------------------------------------------------*/

void olng_operate_fixm(void)
{
    UINT8 vkey = 0;
    UINT8 len = 0;
    INT8  str[20] = {0};
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    定额加气");
    olcm_dispprintf(0,2,"加气金额:");
    cursor_x = 5;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
    memset(&oparme, 0, sizeof(oparme)) ;
    if( vkey == _KEY_OK_EV_ && len>0)
    {
        oparme.b_fixmop = TRUE;
        oparme.b_fixnop = FALSE;
        oparme.fix_money = atof(str);
        oparme.fix_voluent = oparme.fix_money/cur_sysparas.p_Price;
        //oprint_printf("fix  money is %f\r\n",oparme.fix_money);
        return;
    }
}
void olng_operate_fixn(void)
{
    UINT8 vkey = 0;
    UINT8 len = 0;
    INT8  str[20] = {0};
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    定量加气");
    olcm_dispprintf(0,2,"预加气量:");
    cursor_x = 5;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
    memset(&oparme, 0, sizeof(oparme)) ;
    if( vkey == _KEY_OK_EV_ && len>0)
    {
        oparme.b_fixmop = FALSE;
        oparme.b_fixnop = TRUE;
        oparme.fix_voluent = atof(str);
        oparme.fix_money = oparme.fix_voluent*cur_sysparas.p_Price;
       // oprint_printf("fix  volument is %f\r\n",oparme.fix_voluent);
       // oprint_printf("fix  money is %f\r\n",oparme.fix_money);
        return;
    }
}
void olng_operate_fix_stop(void)
{

    OPERATE_SUCCESS();
    show_operat_stop();
    odisp_disp(oparme.c_voluent, oparme.c_money, TRUE);
    if(ic_card_put_money(oparme.card_money - oparme.c_money ))
    {
          olcm_dispprintf(2,4,"扣款成功");
          olng_store_flowrecord();
          ic_card_put_status(CARDS_NORMAL);
    }
    else
          olcm_dispprintf(2,4,"扣款失败");


#if  __SIMU_DEBUG_
    _b_simu_lng = FALSE;
    _b_running_flag = FALSE;
    _simu_lngnum = 0;
    _run_lng_tick = 0;
#endif
    memset(&oparme, 0, sizeof(oparme));
    _b_run_lng_flag = TRUE;
    _run_lng_tick = 0;
    oprint_operate_rec();
    cur_lngnum = 0.00;
    //delay_ms(100000);
    osys_getkey(_KEY_NULL_,1);
    eVirtualKey = _KEY_EXIT_EV_;
}

void olng_operate_fix_act(void)
{
    INT16  cnt = 0;
    UINT16 n = 0;
    float  vdiff = 0;
    IDLE_CTRL();
    if( b_fixmop == TRUE && cur_calnum < cur_fixn)
    {
         vdiff = cur_fixn - cur_calnum;//if( (cur_calsum + 4.0) >= cur_fixm )
         cnt = vdiff/0.01;
         for( n =0; n<cnt-2; n++)
         {
            cur_calnum += 0.01;
            cur_calsum = cur_calnum*cur_price;
            cur_calsum = sys_get_float(cur_calsum);
            odisp_disp(cur_calnum, cur_calsum, FALSE);
            olng_operate_disp(FALSE);
            delay_ms(500);
         }
         return;
    }
    if( b_fixnop == TRUE && cur_calnum < cur_fixn)
    {
         vdiff = cur_fixn - cur_calnum;//if( (cur_calsum + 4.0) >= cur_fixm )
         cnt = vdiff/0.01;
         for( n =0; n<cnt-3; n++)
         {
            cur_calnum += 0.01;
            cur_calsum = cur_calnum*cur_price;
            cur_calsum = sys_get_float(cur_calsum);
            odisp_disp(cur_calnum, cur_calsum, FALSE);
            olng_operate_disp(FALSE);
            delay_ms(500);
         }
         return;
    }

}




/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            压力传感器                                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
void olng_psensor_init(void)
{
    CloseADC10();   // Ensure the ADC is off before setting the configuration
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN3);
    OpenADC10( config_p1, config_p2, config_p3, configport, configscan );
    EnableADC10(); // Enable the ADC
}
UINT32  olng_psensor_read(void)
{
    UINT32 pressure;    // Connected to AN3
    UINT32 offset;     // Buffer offset to point to the base of the idle buffer
    while ( !mAD1GetIntFlag() ); // Wait for the first conversion to complete so there will be vaild data in ADC result registers
    // Determine which buffer is idle and create an offset
    //This function returns the buffer that is currently being filled by the ADC
    offset = 8 * ((~ReadActiveBufferADC10() & 0x01));
    pressure = ReadADC10(offset);  // Read the result of temperature sensor conversion from the idle buffer
    mAD1ClearIntFlag();
    return pressure;
}

float olng_psensor_read_adc(UINT8 mCnt)
{
       UINT32    rd  = 0;
       UINT8     n = 0;
       for(n = 0 ;n < mCnt; n++)
       {
            rd += olng_psensor_read();
       }
       return rd/mCnt;
}


