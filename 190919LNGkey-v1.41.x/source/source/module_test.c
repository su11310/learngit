/* 
 * File:   module_test.c
 * Author: felixluom
 *
 * Created on 2014年2月5日, 下午12:14
 */

#include "../includes/global_def.h"

void omodule_ui_p1(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.流量计测试");
    olcm_dispprintf(0,2,"2.电磁阀测试");
    olcm_dispprintf(0,3,"3.打印测试");
    olcm_dispprintf(0,4,"4.键盘测试");
    olcm_dispprintf(7,4,"↓");
}

void omodule_ui_p2(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"5.读卡器测试");
    olcm_dispprintf(0,2,"6.客显屏测试");
    olcm_dispprintf(0,3,"7.压力测试");
    olcm_dispprintf(0,4,"8.存储测试");
    olcm_dispprintf(6,4,"↓↑");
}
void omodule_ui_p3(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"9.通讯测试");
    
    olcm_dispprintf(0,2,"0.硬件类型");
    olcm_dispprintf(7,4,"↑");
//    olcm_dispprintf(0,3,"7.压力测试");
//    olcm_dispprintf(0,4,"8.存储测试");
}
void omodule_ui_switch(void)
{
    switch( _ui_module_id )
    {
        case 1:
            omodule_ui_p1();
            break;
        case 2:
            omodule_ui_p2();
            break;
        case 3:
            omodule_ui_p3();
            break;
        default:
            break;
    }
}

BOOL omodule_key_test_disp(UINT8 vkey)
{
   // olcm_dispprintf(0,3,"                ");
    switch(vkey)
    {
        case _KEY_0_EV_:
             olcm_dispprintf(0,3,"按键 0      ");
             break;
        case _KEY_1_EV_:
             olcm_dispprintf(0,3,"按键 1      ");
             break;
        case _KEY_2_EV_:
             olcm_dispprintf(0,3,"按键 2      ");
             break;
        case _KEY_3_EV_:
             olcm_dispprintf(0,3,"按键 3      ");
             break;   
        case _KEY_4_EV_:
             olcm_dispprintf(0,3,"按键 4      ");
             break;
        case _KEY_5_EV_:
             olcm_dispprintf(0,3,"按键 5      ");
             break;
        case _KEY_6_EV_:
             olcm_dispprintf(0,3,"按键 6      ");
             break;
        case _KEY_7_EV_:
             olcm_dispprintf(0,3,"按键 7      ");
             break;
        case _KEY_8_EV_:
             olcm_dispprintf(0,3,"按键 8      ");
             break;
        case _KEY_9_EV_:
             olcm_dispprintf(0,3,"按键 9      ");
             break;
        case _KEY_SET_EV_:
             olcm_dispprintf(0,3,"按键  设置  ");
             break;
        case _KEY_POINT_EV_:
             olcm_dispprintf(0,3,"按键 .      ");
             break;    
             
        case _KEY_QRY_EV_:
             olcm_dispprintf(0,3,"按键  选择  ");
             break;
        case _KEY_EXIT_EV_:
             olcm_dispprintf(0,3,"按键  退出  ");
             return TRUE;
        case _KEY_STOP_EV_:
             olcm_dispprintf(0,3,"按键  停止  ");
             break;
        case _KEY_GAS_EV_:
             olcm_dispprintf(0,3,"按键  加气  ");
             break;  
             
        case _KEY_COOL_EV_:
             olcm_dispprintf(0,3,"按键  预冷  ");
             break;
        case _KEY_SW_EV_:
             olcm_dispprintf(0,3,"按键  切换  ");
             break;
        case _KEY_ENTER_EV_:
             olcm_dispprintf(0,3,"按键  确定  ");
             break;
        case _KEY_UP_EV_:
             olcm_dispprintf(0,3,"按键  ↑   ");
             break;
        default:
            break;
    }
    return FALSE;
}
void omodule_key_test(void)
{
    UINT8 keyv = 0;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    键盘测试");
    olcm_dispprintf(0,2,"  按更改键退出");
    while(1)
    {
        keyv = ostatemachine_getkey();
        b_keyv = FALSE;
     //   if(_KEY_QRY_EV_ != keyv && keyv != NULL )
     //     oprint_printf("the key down is %d\r\n", keyv);
     //   if(0 == keyv) continue;
        if(TRUE == omodule_key_test_disp(keyv))
            break;
        
    }
    _ui_module_id--;
    eVirtualKey = _KEY_VIRTUAL_EV_;
}

BOOL modbus_lg_switch;

void omodule_modbus_ui(void)
{
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    olcm_dispprintf(0,1,"1.流量  2.流速");
    olcm_dispprintf(0,2,"3.温度  4.增益");
    olcm_dispprintf(0,3,"5.密度  6.清零");
//    olcm_dispprintf(0,4,"              ");
    olcm_dispprintf(0,4,"7.切除  8.缓冲");
}
//time:14--3-17 rengang
void omodule_modbus_ser_ui(void)
{
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    olcm_dispprintf(0,1,"1.流量  2.流速");
    olcm_dispprintf(0,2,"3.温度  4.增益");
    olcm_dispprintf(0,3,"5.密度        ");
}
extern UINT8 modbus_err_type;

void omodule_modbus_switch_test(void)
{
    //modbus_lg_switch = (modbus_lg_switch == TRUE) ? FALSE : TRUE;
    if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
    else                         modbus_lg_switch = TRUE;
}
void omodule_modbus_switch_disp(void)
{
    if(TRUE == modbus_lg_switch ){

        olcm_dispprintf(0,1,"    液  相");
      //  return MODBUS_LNG_L_ADDR;
    }
    else
    {

        olcm_dispprintf(0,1,"    气  相");
     //   return MODBUS_LNG_C_ADDR;
    }

}
//time:14-03-24 rengang
void omodule_modbus_flowrate_test(void)
{
   float total;float temp;float gain;float Density;float ls;float yl;

    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {         
                        if(TRUE == modbus_lg_switch )//液相
                        {
                             if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl)) //GL:1:YE 2：QI

                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    液  相");
                            olcm_dispprintf(0,3,"流速: %.02f", ls);
                        }
                        else//气相
                        {
                             if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    气  相");
                            olcm_dispprintf(0,3,"流速: %.02f", ls);
                          
                        }
                    
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
            if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
               
             }


          }
        eVirtualKey = _KEY_VIRTUAL_EV_;

    ////////////////////////////////////////////
   
}

//time:14-03-24 rengang
void omodule_modbus_total_test(void)
{
   float total;float temp;float gain;float Density;float ls;float yl;
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {         
                        if(TRUE == modbus_lg_switch )//液相
                        {
                             if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    液  相");
                            olcm_dispprintf(0,3,"流量: %.02f", total);
                        }
                        else//气相
                        {
                             if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    气  相");
                            olcm_dispprintf(0,3,"流量: %.02f", total);
                          
                        }
                    
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
            if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
               
             }


          }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
//time:14-03-24 rengang
void omodule_modbus_temp_test(void)
{
   float total;float temp;float gain;float Density;float ls;float yl;
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {
                        if(TRUE == modbus_lg_switch )//液相
                        {
                             if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    液  相");
                            olcm_dispprintf(0,3,"温度: %.02f", temp);
                        }
                        else//气相
                        {
                             if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    气  相");
                            olcm_dispprintf(0,3,"温度: %.02f", temp);

                        }

            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
            if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;

             }


          }
        eVirtualKey = _KEY_VIRTUAL_EV_;

    ////////////////////////////////////////////
   
}
//time:14-03-24 rengang
void omodule_modbus_gain_test(void)
{
   float total;float temp;float gain;float Density;float ls;float yl;
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {         
                        if(TRUE == modbus_lg_switch )//液相
                        {
                             if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    液  相");
                            olcm_dispprintf(0,3,"增益: %.02f", gain);
                        }
                        else//气相
                        {
                             if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                            olcm_dispprintf(0,1,"    气  相");
                            olcm_dispprintf(0,3,"增益: %.02f", gain);
                          
                        }
                    
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
            if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
               
             }


          }
        eVirtualKey = _KEY_VIRTUAL_EV_;


   
}

//time:14-03-24 rengang
void omodule_modbus_densty_test(void)
{
   float total;float temp;float gain;float Density;float ls;float yl;
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {         
                        if(TRUE == modbus_lg_switch )//液相
                        {
                             if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                              olcm_dispprintf(0,1,"    液  相");
                            olcm_dispprintf(0,3,"密度: %.02f", Density);
                        }
                        else//气相
                        {
                             if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&total,(float *)&yl))
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                             olcm_dispprintf(0,1,"    气  相");
                            olcm_dispprintf(0,3,"密度: %.02f", Density);
                          
                        }
                    
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
            if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
               
             }


          }
        eVirtualKey = _KEY_VIRTUAL_EV_;
   
}
void omodule_modbus_clr_test(void)
{
        BOOL bitwl,bitwc;
    olcd_clearsCreen();
    bitwl=FALSE;
    bitwc=FALSE;
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {
                        if((TRUE == modbus_lg_switch )&&(bitwl==FALSE))//液相
                        {
                             if(TRUE != Clear_modbus(1))  //液相
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                               olcm_dispprintf(0,1,"    液  相");
                             olcm_dispprintf(0,2,"清零成功");
                             bitwl=TRUE;
                             osys_getkey(_KEY_NULL_,300);
                        }
                        else if((TRUE != modbus_lg_switch )&&(bitwc==FALSE))//气相
                        {
                             if(TRUE != Clear_modbus(2))//气相
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                               olcm_dispprintf(0,1,"    气  相");
                             olcm_dispprintf(0,2,"清零成功");
                              bitwc=TRUE;
                              osys_getkey(_KEY_NULL_,300);
                        }
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(( bitwl==TRUE )&&( bitwc==TRUE )) break;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
           if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
              }
          }
        eVirtualKey = _KEY_VIRTUAL_EV_;
 }
void omodule_auto_buff_test(void)
{
    BOOL bitwl,bitwc;
    olcd_clearsCreen();
    bitwl=FALSE;
    bitwc=FALSE;
    modbus_lg_switch = TRUE;
    omodule_modbus_switch_disp();
       while(1)
        {
                        if((TRUE == modbus_lg_switch )&&(bitwl==FALSE))//液相
                        {
                             if(TRUE != Buff_modbus(1))  //液相
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                               olcm_dispprintf(0,1,"    液  相");
                             olcm_dispprintf(0,2,"液相写缓冲成功");
                             bitwl=TRUE;
                             osys_getkey(_KEY_NULL_,300);
                        }
                        else if((TRUE != modbus_lg_switch )&&(bitwc==FALSE))//气相
                        {
                             if(TRUE != Buff_modbus(2))//气相
                               {
                                   SOEACTION1(C_MODBUS_ERR,eCurRunState);//超时等待要长一些
                                    return;
                               }
                               olcm_dispprintf(0,1,"    气  相");
                             olcm_dispprintf(0,2,"气相写缓冲成功");
                              bitwc=TRUE;
                              osys_getkey(_KEY_NULL_,300);
                        }
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(( bitwl==TRUE )&&( bitwc==TRUE )) break;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
           if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
              }
          }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
#if 0
//time:14-03-24 rengang
void omodule_auto_buff_test(void)
{
    BOOL bok = TRUE;
    UINT8 n = 0;
    UINT16 rd[6] = {0};
    UINT8  addr = MODBUS_LNG_L_ADDR;
    olcd_clearsCreen();
    modbus_lg_switch = TRUE;
    addr = omodule_modbus_switch_disp();
         while(1)
        {
          for(n=0; n<_MODBUS_L_AUTO_RM_BUF_LEN; n++)
            {
             /*qaz   if( FALSE == omodbus_read_int(addr, 750+n, &rd[n]))
                {
                bok = FALSE;
                olcm_dispprintf(0,2,"err id:%x", n);
                break;
                }*/
            }
        if( bok == TRUE)
            {
                olcm_dispprintf(0,2,"%x %x %x %x %x", rd[0],rd[1],rd[2],rd[3],rd[4]);
             }
        if ( omobus_init_reg (addr, &n) == FALSE)
            {
                olcm_dispprintf(0,3,"写缓冲err:%d", n);
            }
        else
            {
                olcm_dispprintf(0,3,"写缓冲ok:%d", n);
            }
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_SW_EV_ != keyv && _KEY_UP_EV_ != keyv) continue;
            if((_KEY_SW_EV_ == keyv)||(_KEY_UP_EV_ == keyv))
            {
                if(modbus_lg_switch == TRUE) modbus_lg_switch = FALSE;
                else                         modbus_lg_switch = TRUE;
                addr = omodule_modbus_switch_disp();
              }
           }
    eVirtualKey = _KEY_VIRTUAL_EV_;
}
#endif
void omodule_vctrl_ui(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.电磁阀开启");
    olcm_dispprintf(0,2,"2.联动测试");
    olcm_dispprintf(0,3,"3.预冷测试");
}
static UINT8 vctrl_step;
static UINT8 pump_step;
void omodule_vctrl_test_init(void)
{
    vctrl_step = 1;
    pump_step = 0;
    SOLENOID_ALL_OPEN();
}

void omodule_vctrl_test_end(void)
{
    vctrl_step = 1;
    pump_step = 0;
    SOLENOID_ALL_CLOSE();
}

//time:14-03-21 rengang
void omodule_vctrlopen_test(void)
{
    UINT8 m1=0,m2=0,m3=1,m4=0,m5=0,m6=1;
      olcd_clearsCreen();
    olcm_dispprintf(0,1,"EH    EL    EM");
    olcm_dispprintf(0,2,"○    ○    ● ");
    olcm_dispprintf(0,3,"PLC1       PLC2");
    olcm_dispprintf(0,4,"○          ● ");
    if(TRUE != module_vctrl_start())
       {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
       while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
          //  if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
         //   if( _KEY_1_EV_ != keyv && _KEY_2_EV_ != keyv&&_KEY_3_EV_ != keyv && _KEY_4_EV_ != keyv && _KEY_5_EV_ != keyv&& _KEY_6_EV_ != keyv) continue;
            else if(_KEY_1_EV_ == keyv)
            {
                if(m1==0)
                {
                    m1=1;
                    if(TRUE !=module_vctrl(EH,OPEN))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                olcm_dispprintf(0,2,"●");
                 }
                else
                {
                    m1=0;
                  //  VK1_CLOSE();

                        if(TRUE !=module_vctrl(EH,CLOSE))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                 olcm_dispprintf(0,2,"○");
                }
             }
            else if(_KEY_2_EV_ == keyv)
            {
                if(m2==0)
                {
                    m2=1;
                   // VK2_OPEN();

                         if(TRUE != module_vctrl(EL,OPEN))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                olcm_dispprintf(3,2,"●");
                }
                else
                {
                    m2=0;
                   // VK2_CLOSE();

                        if(TRUE !=module_vctrl(EL,CLOSE))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                 olcm_dispprintf(3,2,"○");
                }
           }
            else  if(_KEY_3_EV_ == keyv)
            {
                if(m3==0)
                {
                  //  VK3_OPEN();

                         if(TRUE != module_vctrl(EM,OPEN))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                    m3=1;
                olcm_dispprintf(6,2,"●");
                }
                else
                {
                    m3=0;
                 //   VK3_CLOSE();

                        if(TRUE != module_vctrl(EM,CLOSE))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                 olcm_dispprintf(6,2,"○");
                }
             }
            else if(_KEY_4_EV_ == keyv)
            {
                if(m4==0)
                {
                    m4=1;
                   // VK4_OPEN();

                        if(TRUE != module_vctrl(PLC1,OPEN))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                olcm_dispprintf(0,4,"●");
                }
                else
                {
                    m4=0;
                 //    VK4_CLOSE();

                           if(TRUE !=  module_vctrl(PLC1,CLOSE))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                 olcm_dispprintf(0,4,"○");
                }
              }
            else if(_KEY_5_EV_ == keyv)
            {
                if(m6==0)
                {
                    m6=1;
                  //  PLC2_OPEN();

                        if(TRUE != module_vctrl(PLC2,OPEN))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                olcm_dispprintf(6,4,"●");
                }
                else
                {
                    m6=0;
                  //  PLC2_CLOSE();

                        if(TRUE !=module_vctrl(PLC2,CLOSE))
                     {//通信异常
                       SOEACTION1(PRO422_ERR,eCurRunState);
                       return;
                       }
                 olcm_dispprintf(6,4,"○");
                }
             }
          //  delay_ms(200);
        }
   if(TRUE !=  module_vctrl_quit())
      {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
  //    osys_getkey(_KEY_NULL_, 300);
 //   eVirtualKey = _KEY_VIRTUAL_EV_;
}
void omodule_vctrlclose_test(void)
{
    if(vctrl_step <= 6 && vctrl_step>1)
    {
  //qaz      olng_vctrl_switch_off(vctrl_step--);
    }
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"电磁阀测试");
    osys_getkey(_KEY_NULL_, 500);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}

//time:14-03-22 rengang
void omodule_pump_test(void)
{
    UINT8 e=4;
    UINT8 m1=0;
    UINT8 m2=0;
    UINT8 m3=0;
    UINT8 m4=0;
    UINT8 OPE_CLOSE = 0;
    olcd_clearsCreen();
    if(TRUE !=  module_vctrl_start())
      {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
    olcm_dispprintf(0,1,"泵联动测试");
    olcm_dispprintf(0,2,"低  预  加  待");
    olcm_dispprintf(0,3,"○  ○  ○  ●");
  //  olcm_dispprintf(0,3,"○  ○  ○  ○ ");

          while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
           // if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) 
            {
                break;

            }
         //   if( _KEY_1_EV_ != keyv && _KEY_2_EV_ != keyv&&_KEY_3_EV_ != keyv && _KEY_4_EV_ != keyv && _KEY_5_EV_ != keyv) continue;
          if(_KEY_1_EV_ == keyv)
            {
  
                    m1=1;
                    e =1; 
               
                olcm_dispprintf(0,3,"●  ○  ○  ○");

    
             }
          else if(_KEY_2_EV_ == keyv)
            {
 
                    m2=1;
                     e =2;
                 olcm_dispprintf(0,3,"○  ●  ○  ○");
    
              }
          else  if(_KEY_3_EV_ == keyv)
            {
 
                    e =3;
                    m3=1;

                olcm_dispprintf(0,3,"○  ○  ●  ○");
    
             }
          else if(_KEY_4_EV_ == keyv)
            {
 
                    m4=1;
                    e =4;

                 olcm_dispprintf(0,3,"○  ○  ○  ●");
    
              }

               if(TRUE != module_vctrl_pump_sw(e))//1：低 2：预冷 3：加注 4：待机
               {
                   SOEACTION1(PRO422_ERR,eCurRunState);
                   return;
               }
  
        }  //end of while (1)
     if(TRUE !=  module_vctrl_quit())
      {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }    
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
#if 0
void omodule_pump_test(void)
{
    UINT8 e=4;
    UINT8 m1=0;
    UINT8 m2=0;
    UINT8 m3=0;
    UINT8 m4=0;
    UINT8 OPE_CLOSE = 0;
    olcd_clearsCreen();
    if(TRUE !=  module_vctrl_start())
      {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
    olcm_dispprintf(0,1,"泵联动测试");
    olcm_dispprintf(0,2,"停  预  加  待");
    olcm_dispprintf(0,3,"○  ○  ○  ●");
  //  olcm_dispprintf(0,3,"○  ○  ○  ○ ");

          while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv)
            {
                break;

            }
            if( _KEY_1_EV_ != keyv && _KEY_2_EV_ != keyv&&_KEY_3_EV_ != keyv && _KEY_4_EV_ != keyv && _KEY_5_EV_ != keyv) continue;
          if(_KEY_1_EV_ == keyv)
            {
                if(m1==0)
                {
                    m1=1;
                    e =1;

                olcm_dispprintf(0,3,"●  ○  ○  ○");

                 }
                else
                {
                    m1=0;
                     e =0;

                 olcm_dispprintf(0,3,"○  ○  ○  ○ ");
                }
             }
            if(_KEY_2_EV_ == keyv)
            {
                if(m2==0)
                {
                    m2=1;
                     e =2;
                 olcm_dispprintf(0,3,"○  ●  ○  ○");
                }
                else
                {
                    m2=0;
                     e =0;
              olcm_dispprintf(0,3,"○  ○  ○  ○ ");
                }
              }
            if(_KEY_3_EV_ == keyv)
            {
                if(m3==0)
                {
                    e =3;
                    m3=1;

                olcm_dispprintf(0,3,"○  ○  ●  ○");
                }
                else
                {
                    m3=0;
                   e =0;
              olcm_dispprintf(0,3,"○  ○  ○  ○ ");
                }
             }
            if(_KEY_4_EV_ == keyv)
            {
                if(m4==0)
                {
                    m4=1;
                    e =4;

                 olcm_dispprintf(0,3,"○  ○  ○  ●");
                }
                else
                {
                    m4=0;
                    e =0;
              olcm_dispprintf(0,3,"○  ○  ○  ○ ");
                }
              }

               if(TRUE != module_vctrl_pump_sw(e))//1：停 2：预冷 3：加注 4：待机
               {
                   SOEACTION1(PRO422_ERR,eCurRunState);
                   return;
               }

        }  //end of while (1)
     if(TRUE !=  module_vctrl_quit())
      {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
#endif

/*
 预冷状态：
    当加气枪安插在加气枪座上时，系统进入预冷操作后，切断阀1开，切断阀2闭；
 * 系统给与PLC的信号为：“10”；预冷过程中实时监测温度、增益等参数是否满
 * 足加气条件，若满足，则进入到：预冷成功状态；若在一定时间段内（时间可
 * 设置，默认为无穷大），不能达到加气条件，则视为预冷失败，则进入到：
 * 上电待机状态；
预冷成功状态：
当系统遇冷成功之后，切断阀1关，切断阀2开；系统给与PLC的信号为：“10”；此时等待加气动作，若在设定时间段内（时间可设置，默认为5min；用于频繁加气时，减少预冷动作。）进行加气动作，则进入到：加气状态；若在设定时间内未进行任何动作，则进入到：上电待机状态；
加气状态：
系统预冷成功之后，进行加气动作，切断阀1开，切断阀2闭；系统给与PLC的信号为：“11”；加气过程中系统实时监控温度、增益等参数是否满足停机条件，若满足，则加气完成，进入到：预冷成功状态；若不满足，则继续加气。
停机条件：
 */
#define DRVGAIN_CHKLEN      50
void omodule_precool_test(void)
{
        BOOL  bok = TRUE;
        UINT8 errcnt = 0;
        UINT8 Rec_Pro;
        UINT8 precool_chk_cnt = 0;
        un_float  unvfrd;
        UINT32 rdkey = 0;
        UINT32 ecc = 0;
        UINT8 eccSW =0;
        PrecoolCo=0;
      
        float temp;float gain;float md;float ls;float yl;
        olcd_clearsCreen();
        //  PRECOOL_CTRL();
      if(TRUE != ocompany_precool_start())
       {
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
       olcm_dispprintf(1,1,"正在预冷");
       PrecoolCo=1;
  while(1)
    {
      if( send_yl_flag==1)  //1秒定时发送询问
                { send_ack_sj(0x88);
                  send_yl_flag=0;
                }
            Rec_Pro = ocompany_precool_getstate((float *)&temp,(float *)&gain,(float *)&md,(float *)&ls,(float *)&yl);//返回值：0：422通信出错；1：有效数值；2：ok;3:预冷超时；4：MOD通信错误
                //后
               {  rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey)
                   {
                       break;
                   }
               }
           if(Rec_Pro != 0)
           {    ecc = 0;   //很重要
               if(Rec_Pro == 1)
                  {
                            olcm_dispprintf(0,1,"  正在预冷      ");
                            olcm_dispprintf(0,2,"流速: %3.02f    ",ls);
                            olcm_dispprintf(0,3,"增益: %3.02f    ",gain );
                            olcm_dispprintf(0,4,"温度: %3.02f    ",temp);
                       
                  }/////
                  else  if(Rec_Pro == 2)
                  {
                            olcd_clearsCreen();
                            olcm_dispprintf(1,1,"预冷成功");
                            olcm_dispprintf(1,2,"请加气");
                            osys_getkey(_KEY_EXIT_EV_,800);//_KEY_EXIT_EV_ = 14,  //  osys_getkey(_KEY_NULL_,1000);
                            eVirtualKey = _KEY_VIRTUAL_EV_;
                            PrecoolCo=0;
                           CanGasTime = gTick  +100*60*CANGASMINUTE ; //半小时
                            return;
                  }/////
                  else if(Rec_Pro == 3)  //E0
                  {
                            olcd_clearsCreen();
                            olcm_dispprintf(1,1,"通信询问超时");
                            osys_getkey(_KEY_EXIT_EV_,800);//150908
                            break;
                  }/////
                  else if(Rec_Pro == 4)
                  {
                      SOEACTION1(MODBUS_ERR,eCurRunState);
                      break;
                  }
             else if(Rec_Pro == 5)  //E1
                  {
                            olcd_clearsCreen();
                            olcm_dispprintf(1,1,"压力超限");
                            osys_getkey(_KEY_EXIT_EV_,800);//150908
                            break;
                  }/////
               else if(Rec_Pro == 6)  //E2
                  {
                            olcd_clearsCreen();
                            olcm_dispprintf(1,1,"流速超低, 暂停");
                            osys_getkey(_KEY_EXIT_EV_,800);//150908
                            break;
                  }/////
           else if(Rec_Pro == 7)  //E3  rg180118
                  {
                            olcd_clearsCreen();
                            olcm_dispprintf(1,1,"流量计通信错误");
                            osys_getkey(_KEY_EXIT_EV_,800);//150908
                            break;
                  }/////
           }
   else if(Rec_Pro == 0)//无返回值且未定时
          {
              if(ecc !=0)
                  {
                    if(gTick > ecc)
                     { //  SOEACTION1(PRO422_ERR,eCurRunState);
                      //   break;
                        olcm_dispprintf(1,1,"超时!       ");
                        osys_getkey(_KEY_EXIT_EV_,300);
                        ecc = DWORDMAX;
                         break;
                      }
                   }
               else
                   ecc = gTick +600;

          }
      
            ///////////////////////
        }  //end of  while 1

     if(TRUE != ocompany_precool_stop()) //发出停止命令
       {
         PrecoolCo=0;
       //    SOEACTION1(62,eCurRunState);
             //GaoYi
             SOEACTION1(PRO422_ERR,eCurRunState);
        //   return;
       }
       PrecoolCo=0;
       send_yl_flag=0;
       // osys_getkey(_KEY_EXIT_EV_,80);//_KEY_EXIT_EV_ = 14,  //  osys_getkey(_KEY_NULL_,1000);
        eVirtualKey = _KEY_VIRTUAL_EV_;
}

void omodule_print_test(void)
{
    oprint_header_cmd();
    oprint_printf("    杰瑞LNG加参数\r\n");
    oprint_normal_cmd();
    oprint_printf("    杰瑞集团LNG加气机\r\n");
    oprint_printf("    杰瑞集团LNG加气机\r\n");
    oprint_printf("    杰瑞集团LNG加气机\r\n");
    oprint_printf("    杰瑞集团LNG加气机\r\n");
    osys_getkey(_KEY_NULL_, 500);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}


void omodule_ic_put0(void)
{
    UINT8 buf[150];
    memset(buf, 0, sizeof(buf));
   // sprintf(buf, "%s","CN:10000000001;TN:F0Q777;BCD:2015-10-10;BCAVD:2016-01-01;COUNT:4;CP:20.00;CDT:1;ML:10000.0000;GL:1000.0000;TN:100;" );
    sprintf(buf, "%s", "CN:1000000002;BCD:2015-10-10;BCAVD:2016-01-01;CONT:40000006;CP:20.00;CDT:40000001;ML:10.0000000;GL:1000.0000;TN:003;");
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"记账金额");
    olcm_dispprintf(1,2,"正在充值中...");
 //   oprint_printf("lenght is %d\r\n", strlen(buf));
//    oprint_printf("info is %s\r\n", buf);
    ic_card_put_info(buf, strlen(buf));
    if(ic_card_put_money(0))
  //      oprint_printf("Set money success\r\n");
    memcpy(buf, "123456", 6);
    if(ic_card_put_password(buf, 6))
    {
 //       oprint_printf("Set password success\r\n");
    }
    //ic_card_put_status(CARDS_GREY);
    ic_card_put_status(CARDS_NORMAL);
    ic_card_get_status();
    //olcm_dispprintf(0,1,"ic");
    olcm_dispprintf(1,2,"充值已完成   ");
    osys_getkey(_KEY_NULL_, 300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
  }
void omodule_ic_put1(void)
{
    UINT8 buf[150];
    memset(buf, 0, sizeof(buf));
   // sprintf(buf, "%s","CN:10000000001;TN:F0Q777;BCD:2015-10-10;BCAVD:2016-01-01;COUNT:4;CP:20.00;CDT:1;ML:10000.0000;GL:1000.0000;TN:100;" );
 //   sprintf(buf, "%s", "CN:1000000002;BCD:2015-10-10;BCAVD:2016-01-01;CONT:40000007;CP:20.00;CDT:40000001;ML:10.0000000;GL:1000.0000;TN:003;");
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"预购金额");
    olcm_dispprintf(1,2,"正在充值中...");
//    oprint_printf("lenght is %d\r\n", strlen(buf));
 //   oprint_printf("info is %s\r\n", buf);
 //   ic_card_put_info(buf, strlen(buf));
  //  if(ic_card_put_money(0))
 //        oprint_printf("Set money success\r\n");
  //      ic_card_put_gass(0);
 //   memcpy(buf, "123456", 6);
 //   if(ic_card_put_password(buf, 6))
 //   {
 //       oprint_printf("Set password success\r\n");
 //   }
    //ic_card_put_status(CARDS_GREY);
    ic_card_put_money(0x2710);
    ic_card_put_status(CARDS_NORMAL);
    ic_card_get_status();
    //olcm_dispprintf(0,1,"ic");
    olcm_dispprintf(1,2,"充值已完成   ");
    osys_getkey(_KEY_NULL_, 300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
  }
void omodule_disp_test(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  客显屏测试");
     if(TRUE != module_dispLcd_test())
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;
    }
    osys_getkey(_KEY_NULL_, 300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}
void omodule_pressure_test(void)
{
      float press;
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"  压力");
      olcm_dispprintf(0,2,"正在读取。。。");
    if(TRUE != get_press(&press))
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;

    }
    //olcm_dispprintf(0,2,"一二三四五六七八");
      olcm_dispprintf(0,2,"                ");
      olcm_dispprintf(0,2,"压力:%.2f MPa", press);

     osys_getkey(_KEY_NULL_, 300);
     eVirtualKey = _KEY_VIRTUAL_EV_;

}

void omodule_memory_test(void)
{

      UINT8 chk = 1;
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"  存储测试");
      olcm_dispprintf(0,2,"正在读取。。");
 //   if(TRUE != get_ModuleSave(&chk))
  //  {
  //       SOEACTION1(PRO422_ERR,eCurRunState);
  //        return;

 //   }
      delay_ms(10000);
      if(chk)
      olcm_dispprintf(0,2,"系统存储正常    ");
      else
      olcm_dispprintf(0,2,"系统存储异常    ");
     osys_getkey(_KEY_NULL_, 300);
     eVirtualKey = _KEY_VIRTUAL_EV_;

}
void omodule_sp_up(void)//rg170531锁屏
{
    UINT8 rdkey,sec;
    if(SP == 0)
    { 
	   SP_tick =gTick +100*5;  
     olcd_clearsCreen();
      olcm_dispprintf(0,2,"  按↑键锁屏....");
 		 while(1)
          {
             if(gTick > SP_tick)
             {   
		     SP_tick = 0;
               eVirtualKey = _KEY_VIRTUAL_EV_;//_KEY_EXIT_EV_;
                return;
              }
	     sec = (UINT8)((SP_tick -gTick)/100);
             olcm_dispprintf(2,3,"%2d秒退出设置",sec);
		 rdkey = osys_getkey_ex(); //是否有停止按键
            b_keyv = FALSE;
            if (_KEY_UP_EV_ == rdkey)
            {
		        olcd_clearsCreen();
		    SP=1;
		     olcm_dispprintf(1,1,"本机已锁屏...");
		     olcm_dispprintf(1,2,"请重新登录");
		     osys_getkey(_KEY_NULL_, 400);
		     eCurRunState = State_log_in;
			eVirtualKey = _EVENT_TRUE;
//		     eVirtualKey = _KEY_VIRTUAL_EV_;
			buzzer_power_up_sound();
                return;
            }
	    else if(rdkey == _KEY_EXIT_EV_)
	    { eVirtualKey = _KEY_EXIT_EV_;
                 return;
	    }
	}    
    }
  }    