/*
 * File:   main_ui.c
 * Author: jereh
 *
 * Created on 2014_01_15
 */

#include "../includes/global_def.h"
void oui_main_ui(void);

static UINT8  fresh_tick = 0;
static UINT8  fresh_rtcc = 0;

static UINT8  simu_hh = 0;
static UINT8  simu_mm = 0;

void oui_mainui_fresh(void)
{
   // UINT8 rd_sec = 0;
//    olcd_clearsCreen();
  ortcc_read_time((UINT8*)&sys_time[0]);
  olcm_dispprintf(0,4," %02d-%02d  %02d:%02d:%02d", sys_time[1], sys_time[2], sys_time[3], sys_time[4], sys_time[5]);
 if( gTick <  CanGasTime)
        olcm_dispprintf(2,3,"请加气");
    else
        olcm_dispprintf(2,3,"请预冷");
/*
    if(_sys_tick_ >10){   //59
        fresh_tick = _sys_tick_ = 0;
        ortcc_read_time((UINT8*)&sys_time[0]);
        olcm_dispprintf(0,4," %02d-%02d  %02d:%02d:%02d", sys_time[1], sys_time[2], sys_time[3], sys_time[4], sys_time[5]);
        fresh_tick = _sys_tick_ = sys_time[5];
        return;
    }*/
  /*  if( b_mainui && _sys_tick_ >  fresh_tick) {

	   olcm_dispprintf(7,4,"%02d", fresh_tick);
	   fresh_tick = _sys_tick_;
           //opotocol_anlysis_pro();
    }*/
}

void oui_main_ui_set(void)
{
             olcd_clearsCreen();
  //           olcm_dispprintf(0,1,"    设  置");
             olcm_dispprintf(0,1,"1.系统  2.测试");
             olcm_dispprintf(0,2,"3.参数  4.预冷");
             olcm_dispprintf(0,3,"5.压力  6.秘钥");
	     olcm_dispprintf(0,4,"7.序列号      ");//rg190517 打开
}

void oui_main_xz_set(void)
{

   UINT8 len, vkey = 0,i=0;
   float tmp_xz,xzcs;
   UINT8  str[10] = {0};
   if(TRUE != qty_get_xz(&xzcs))
    {//通信异常
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
    olcd_clearsCreen();
   olcm_dispprintf(0,1,"数值范围:0.5-1.5");
   olcm_dispprintf(0,2,"请输系数:%.04f",xzcs);

   cursor_x = 0;
   cursor_y = 3;
cs:   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
         tmp_xz = atof(str);
         if((tmp_xz>1.5)||(tmp_xz<0.5))
         {
             olcm_dispprintf(0,4,"数值超范围, 重输");
             osys_getkey(_KEY_NULL_,400);
             i++;
             if(i<3)
             {
                  olcm_dispprintf(0,3,"                ");
                  olcm_dispprintf(0,4,"                ");
                  goto cs;
             }
             else
             {
                 olcd_clearsCreen();
                 olcm_dispprintf(0,1,"    设置失败    ");
                 olcm_dispprintf(0,2,"  按更改键退出  ");
                 return;
             }
         }
         if( TRUE!= Set_xzcs(tmp_xz,4))
              {
                //通信异常
               olcm_dispprintf(0,4,"    设置失败    ");
               osys_getkey(_KEY_NULL_,300);
               SOEACTION1(PRO422_ERR,eCurRunState);
               return;
                }
           olcm_dispprintf(0,4,"    设置成功    ");
            osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;

   }
       if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oui_main_ui_setPSW(void)
{

    UINT8 passbuf[10];
    UINT8 pass[10];
    UINT8 len1,len2 = 6;
    UINT8  *pinfo;
       while(machine_has_card()!=TRUE)
        {
           olcm_dispprintf(0,1,"请插入管理卡设置");
           olcm_dispprintf(0,2,"                ");
           olcm_dispprintf(0,3,"  按更改键退出  ");
           olcm_dispprintf(0,4,"                ");
           ostatemachine_getkey();
          if(b_keyv == TRUE)
            { b_keyv = FALSE;
              eVirtualKey = _KEY_EXIT_EV_;
              return;
              }
        }
     olcd_clearsCreen();
     olcm_dispprintf(0,1,"正在读取卡信息");
     olcm_dispprintf(0,2,"请稍等。。。。");
     olng_operate_card_info();
     pinfo = ic_operate_info("CDT",global_ic_card_info, &len1);
    if(pinfo==NULL)
   {
        olcd_clearsCreen();
        olcm_dispprintf(1,1,"无效卡");
        olcm_dispprintf(1,2,"请退出重新操作");
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
   }
    if(memcmp(pinfo,"40000024",len1) == 0) // class group card//XIUGAI
 // if(memcmp(pinfo,"40000001",len1) == 0) // class group card
    {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//获得卡密码

        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--设置权限验证--");
        olcm_dispprintf(0,2,"请输入卡密码  ");
        olcm_dispprintf(0,3,"密码:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //密码在插入卡时已经获得

                 if(len2 == len1)
                      {
                         if(strcmp(pass, passbuf) == 0)
                          {
                          pinfo = ic_operate_info("CN",global_ic_card_info, &len2);// 3. group class card  number
                           if(!pinfo)
                           {  eVirtualKey = _KEY_EXIT_EV_;
                               return;
                           }

                            memset(Setsys_Rec_card, 0, sizeof(Setsys_Rec_card));
                            memcpy(Setsys_Rec_card, pinfo, 10);

                               oui_main_ui_set();
                              eCurRunState = State_Set;
                              return;
                         }
                      }
                   //密码错误
                    olcd_clearsCreen();
                    olcm_dispprintf(1,1,"密码错误");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_EXIT_EV_;
                  return;

            }
         else
           eVirtualKey = _KEY_EXIT_EV_;
    }

    else  if(memcmp(pinfo,"40000016",len1) == 0) // 设置卡
     {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//获得卡密码

        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--设置权限验证--");
        olcm_dispprintf(0,2,"请输入卡密码  ");
        olcm_dispprintf(0,3,"密码:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //密码在插入卡时已经获得

                 if(len2 == len1)
                      {
                         if(strcmp(pass, passbuf) == 0)
                          {
                          pinfo = ic_operate_info("CN",global_ic_card_info, &len2);// 3. group class card  number
                           if(!pinfo)
                           {  eVirtualKey = _KEY_EXIT_EV_;
                               return;
                           }

                            memset(Setsys_Rec_card, 0, sizeof(Setsys_Rec_card));
                            memcpy(Setsys_Rec_card, pinfo, 10);

                               oui_main_xz_set();
                              eCurRunState = 0;
                              return;
                         }
                      }
                   //密码错误
                    olcd_clearsCreen();
                    olcm_dispprintf(1,1,"密码错误");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_EXIT_EV_;
                  return;

            }
         else
           eVirtualKey = _KEY_EXIT_EV_;


    }
    else // if the card isn't the class group card,
    {
       //卡类型错误
        olcd_clearsCreen();
        olcm_dispprintf(1,1,"卡类型错误");
        olcm_dispprintf(1,2,"请退出重新操作");
        osys_getkey(_KEY_NULL_,320);
        eVirtualKey = _KEY_EXIT_EV_;
    }
    return;

    ////////////////////////////////////////


}
void oui_main_ui(void)
{
    Gas_para_init();
#if 0
#if down_psw
    UINT8 i;
    UINT8 CARD_PSW[8];
    UINT8 CARD_PSW1[8];
    memset(CARD_PSW,0,8);
    memset(CARD_PSW1,0,8);
    i=o24lcxxx_read_bytes_ex(CARD_PSW_BACKUP_ADDR,(UINT8*)CARD_PSW,8);

   i= o24lcxxx_read_bytes_ex(CARD_PSW_BACKUP_ADDR, (UINT8*)CARD_PSW1, 8);
    if(memcmp(CARD_PSW,CARD_PSW1,8)!=0)
        {
              olcd_clearsCreen();
              olcm_dispprintf(0,1,"  获取秘钥");
              olcm_dispprintf(0,2,"正在获取秘钥....");
              if( down_get_password(CARD_PSW)==TRUE )
                {
                if(1 == Save_cardpsw(CARD_PSW))
                 {  olcm_dispprintf(0,2,"秘钥已获取成功");//保存
                    memcpy(KEY_CAR_PASS,CARD_PSW,8);
                 }
                 }
              else
              {
                  olcm_dispprintf(0,2,"秘钥获取失败");//保存
              }
    }
    else
    {
        memcpy(KEY_CAR_PASS,CARD_PSW,8);
    }
#endif
#endif
   b_mainui =TRUE;
    olcd_clearsCreen();
    if(Xs_Info[0]==0)
    olcm_dispprintf(0,1,"杰瑞---LNG加气机",2); //cur_sysparas
    else
        olcm_dispprintf(0,1,Xs_Info,2);
 //   oprint_printf(0,1, Xs_Info,2);
 //      oprint_printf(0,1, Xs_Info);
 //   olcm_dispprintf(0,1,"杰瑞---LNG加气机",2);//hex2bcd(12));
    if(WKJQ == 0)//rg170531无卡加气
        {
            olcm_dispprintf(0,2,"  --无卡加气--",12.00);   
        }
    else if(WKJQ == 1)//rg170531无卡加气
        {
            olcm_dispprintf(0,2,"  --有卡加气--",12.00);   
        }  
    else
	 {
            olcm_dispprintf(0,2,"  --有卡加气--",12.00);   
        }  
    
 //   olcm_dispprintf(0,2,"  --欢迎使用--",12.00);
    if( gTick <  CanGasTime)
        olcm_dispprintf(2,3,"请加气");
    else
        olcm_dispprintf(2,3,"请预冷");
  ortcc_read_time((UINT8*)&sys_time[0]);
    _sys_tick_ = sys_time[5];
    simu_mm    = sys_time[4];
    olcm_dispprintf(0,4," %02d-%02d  %02d:%02d:%02d", sys_time[1], sys_time[2], sys_time[3], sys_time[4], sys_time[5]);
    b_mainui = TRUE;
}

void oui_main_ui_qry(void)//RG161220
{   
    olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"    查  询");
    olcm_dispprintf(0,1,"1.记录  2.班组");
    olcm_dispprintf(0,2,"3.卡余  4.系统");
    olcm_dispprintf(0,3,"5.液相  6.气相");
    olcm_dispprintf(0,4,"7.拨码  8.温度");
//    olcm_dispprintf(0,4,"7.键复  8.主板复");
    
}
void oui_main_ui_qry_soe(void)//rg160623
{   
    olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"    异  常");
    olcm_dispprintf(0,1,"1.异常信息      ");
    olcm_dispprintf(0,2,"2.键盘复位记录  ");
    olcm_dispprintf(0,3,"3.主板复位记录  ");
 //   olcm_dispprintf(0,4,"4.序列号        ");
}
void oqry_flow_l()
{
    UINT8 i=0;
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"液相流量计");
    olcm_dispprintf(0,2,"温度:");
    olcm_dispprintf(0,3,"流速:");
    olcm_dispprintf(0,4,"增益:");
     olcm_dispprintf(7,4,"↓");
    UINT8 rdkey =0;
    float total;float temp;float gain;float Density;float ls;float yl;

    while(1)
    {
       if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls ,(float *)&total,(float *)&yl))
       {
           SOEACTION1(PRO422_ERR,eCurRunState);//超时等待要长一些
           // return;
           break;  //此处不同
       }
         {  rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey) break;
                   if(_KEY_EXIT_EV_ == rdkey) break;
                   if(_KEY_SW_EV_ == rdkey)
                   {
                        i=1;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"液相流量计");
//                        olcm_dispprintf(0,2,"累积:");
                        olcm_dispprintf(0,2,"密度:");
                        olcm_dispprintf(0,3,"压力:");
                        olcm_dispprintf(7,4,"↑");
                  }
                   if(_KEY_UP_EV_ == rdkey)
                   {
                        i=0;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"液相流量计");
                        olcm_dispprintf(0,2,"温度:");
                        olcm_dispprintf(0,3,"流速:");
                        olcm_dispprintf(0,4,"增益:");
                        olcm_dispprintf(7,4,"↓");
                   }
                   if(i==1)
                   {
 //                       olcm_dispprintf(3,2,"%.2f", total);
                        olcm_dispprintf(3,2,"%.2f", Density);
                        olcm_dispprintf(3,3,"%.2f", yl);
                     }
                  if(i==0)
                  {

                        olcm_dispprintf(3,2,"%.2f", temp);
                        olcm_dispprintf(3,3,"%.2f", ls);
                        olcm_dispprintf(3,4,"%.2f", gain);
                  }
         }

         delay_ms(2000);
  }
    eVirtualKey = _KEY_VIRTUAL_EV_;
    return;

}
void oqry_flow_g()
{
    UINT8 i=0;
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"气相流量计");
    olcm_dispprintf(0,2,"温度:");
    olcm_dispprintf(0,3,"流速:");
    olcm_dispprintf(0,4,"增益:");
    olcm_dispprintf(7,4,"↓");
    UINT8 rdkey =0;
    float total;float temp;float gain;float Density;float ls;float yl;
    while(1)
    {
       if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls ,(float *)&total,(float *)&yl))
//        if(TRUE != qty_get_g_mod((float *)&total,(float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&yl))
       {
           SOEACTION1(PRO422_ERR,eCurRunState);//超时等待要长一些
          //  return;
           break;  //此处不同

       }
        {  rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey) break;
                   if(_KEY_EXIT_EV_ == rdkey) break;
                     if(_KEY_SW_EV_ == rdkey)
                   {
                        i=1;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"气相流量计");
 //                       olcm_dispprintf(0,2,"累积:");
                        olcm_dispprintf(0,2,"密度:");
                        olcm_dispprintf(0,3,"回气:");
                        olcm_dispprintf(7,4,"↑");
                  }
                   if(_KEY_UP_EV_ == rdkey)
                   {
                        i=0;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"气相流量计");
                        olcm_dispprintf(0,2,"温度:");
                        olcm_dispprintf(0,3,"流速:");
                        olcm_dispprintf(0,4,"增益:");
                        olcm_dispprintf(7,4,"↓");
                   }
                   if(i==1)
                   {
 //                       olcm_dispprintf(3,2,"%.2f", total);
                        olcm_dispprintf(3,2,"%.2f", Density);
                        olcm_dispprintf(3,3,"%.2f", yl);
                     }
                  if(i==0)
                  {

                        olcm_dispprintf(3,2,"%.2f", temp);
                        olcm_dispprintf(3,3,"%.2f", ls);
                        olcm_dispprintf(3,4,"%.2f", gain);
                  }
         }
       delay_ms(2000);
  }
    eVirtualKey = _KEY_VIRTUAL_EV_;
    return;
}
void oui_main_ui_select(void)
{
    olcd_clearsCreen();
//    olcm_dispprintf(0,1,"    选  择");
    olcm_dispprintf(0,1,"1.预冷  2.查询");
    olcm_dispprintf(0,2,"3.定额  4.定量");
    olcm_dispprintf(0,3,"5.异常  6.下班");
    olcm_dispprintf(0,4,"7.修改卡密码");
}

void oui_precool_ui(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  正在预冷");
    olcm_dispprintf(0,2,"G:0.00");
    olcm_dispprintf(0,3,"F:0.00");
    olcm_dispprintf(0,4,"T:0.00");
}

void oui_precool_value_ui(float g,float t,float f)
{
    UINT8 buf[10];
    memset(buf,0,sizeof(buf));
    sprintf(buf, "G:%.2f", g);
    olcm_dispprintf(0,2,buf);
    memset(buf,0,sizeof(buf));
    sprintf(buf, "F:%.2f", f);
    olcm_dispprintf(0,3,buf);
    memset(buf,0,sizeof(buf));
    sprintf(buf, "T:%.2f", t);
    olcm_dispprintf(0,4,buf);
}
void oqry_temp()//rg161017
{
 UINT8 i=0;
 UINT8 rdkey =0;
    olcd_clearsCreen();
    olcm_dispprintf(1,1,"查询环境温度");
    olcm_dispprintf(0,2,"温度:");
    while(1)
    {
	  {  rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey) break;
                   if(_KEY_EXIT_EV_ == rdkey) break; 
		   temperature = DS18B20_Get_Temp();
                        olcm_dispprintf(3,2,"%.2f", temperature);
		    delay_ms(2000);
	}
    }
    eVirtualKey = _KEY_VIRTUAL_EV_;
    return;
}
/*
void oui_main_ui_qry(void)
{
    olcd_clearsCreen();
#if 0
    olcm_dispprintf(0,1,"    查  询");
    olcm_dispprintf(0,2,"1.流水  2.班组");
    olcm_dispprintf(0,3,"3.卡余  4.系统");
#endif
    olcm_dispprintf(0,1,"1.加气记录");
    olcm_dispprintf(0,2,"2.系统信息");
    olcm_dispprintf(0,3,"3.卡信息");
    olcm_dispprintf(0,4,"4.班组信息");

    //    //olcm_dispprintf(0,3,"2.班组记录");
}*/

