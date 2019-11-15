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
        olcm_dispprintf(2,3,"�����");
    else
        olcm_dispprintf(2,3,"��Ԥ��");
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
  //           olcm_dispprintf(0,1,"    ��  ��");
             olcm_dispprintf(0,1,"1.ϵͳ  2.����");
             olcm_dispprintf(0,2,"3.����  4.Ԥ��");
             olcm_dispprintf(0,3,"5.ѹ��  6.��Կ");
	     olcm_dispprintf(0,4,"7.���к�      ");//rg190517 ��
}

void oui_main_xz_set(void)
{

   UINT8 len, vkey = 0,i=0;
   float tmp_xz,xzcs;
   UINT8  str[10] = {0};
   if(TRUE != qty_get_xz(&xzcs))
    {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
    olcd_clearsCreen();
   olcm_dispprintf(0,1,"��ֵ��Χ:0.5-1.5");
   olcm_dispprintf(0,2,"����ϵ��:%.04f",xzcs);

   cursor_x = 0;
   cursor_y = 3;
cs:   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
         tmp_xz = atof(str);
         if((tmp_xz>1.5)||(tmp_xz<0.5))
         {
             olcm_dispprintf(0,4,"��ֵ����Χ, ����");
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
                 olcm_dispprintf(0,1,"    ����ʧ��    ");
                 olcm_dispprintf(0,2,"  �����ļ��˳�  ");
                 return;
             }
         }
         if( TRUE!= Set_xzcs(tmp_xz,4))
              {
                //ͨ���쳣
               olcm_dispprintf(0,4,"    ����ʧ��    ");
               osys_getkey(_KEY_NULL_,300);
               SOEACTION1(PRO422_ERR,eCurRunState);
               return;
                }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
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
           olcm_dispprintf(0,1,"������������");
           olcm_dispprintf(0,2,"                ");
           olcm_dispprintf(0,3,"  �����ļ��˳�  ");
           olcm_dispprintf(0,4,"                ");
           ostatemachine_getkey();
          if(b_keyv == TRUE)
            { b_keyv = FALSE;
              eVirtualKey = _KEY_EXIT_EV_;
              return;
              }
        }
     olcd_clearsCreen();
     olcm_dispprintf(0,1,"���ڶ�ȡ����Ϣ");
     olcm_dispprintf(0,2,"���Եȡ�������");
     olng_operate_card_info();
     pinfo = ic_operate_info("CDT",global_ic_card_info, &len1);
    if(pinfo==NULL)
   {
        olcd_clearsCreen();
        olcm_dispprintf(1,1,"��Ч��");
        olcm_dispprintf(1,2,"���˳����²���");
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
   }
    if(memcmp(pinfo,"40000024",len1) == 0) // class group card//XIUGAI
 // if(memcmp(pinfo,"40000001",len1) == 0) // class group card
    {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//��ÿ�����

        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--����Ȩ����֤--");
        olcm_dispprintf(0,2,"�����뿨����  ");
        olcm_dispprintf(0,3,"����:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //�����ڲ��뿨ʱ�Ѿ����

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
                   //�������
                    olcd_clearsCreen();
                    olcm_dispprintf(1,1,"�������");
                    olcm_dispprintf(1,2,"���˳����²���");
                    osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_EXIT_EV_;
                  return;

            }
         else
           eVirtualKey = _KEY_EXIT_EV_;
    }

    else  if(memcmp(pinfo,"40000016",len1) == 0) // ���ÿ�
     {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//��ÿ�����

        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--����Ȩ����֤--");
        olcm_dispprintf(0,2,"�����뿨����  ");
        olcm_dispprintf(0,3,"����:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //�����ڲ��뿨ʱ�Ѿ����

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
                   //�������
                    olcd_clearsCreen();
                    olcm_dispprintf(1,1,"�������");
                    olcm_dispprintf(1,2,"���˳����²���");
                    osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_EXIT_EV_;
                  return;

            }
         else
           eVirtualKey = _KEY_EXIT_EV_;


    }
    else // if the card isn't the class group card,
    {
       //�����ʹ���
        olcd_clearsCreen();
        olcm_dispprintf(1,1,"�����ʹ���");
        olcm_dispprintf(1,2,"���˳����²���");
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
              olcm_dispprintf(0,1,"  ��ȡ��Կ");
              olcm_dispprintf(0,2,"���ڻ�ȡ��Կ....");
              if( down_get_password(CARD_PSW)==TRUE )
                {
                if(1 == Save_cardpsw(CARD_PSW))
                 {  olcm_dispprintf(0,2,"��Կ�ѻ�ȡ�ɹ�");//����
                    memcpy(KEY_CAR_PASS,CARD_PSW,8);
                 }
                 }
              else
              {
                  olcm_dispprintf(0,2,"��Կ��ȡʧ��");//����
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
    olcm_dispprintf(0,1,"����---LNG������",2); //cur_sysparas
    else
        olcm_dispprintf(0,1,Xs_Info,2);
 //   oprint_printf(0,1, Xs_Info,2);
 //      oprint_printf(0,1, Xs_Info);
 //   olcm_dispprintf(0,1,"����---LNG������",2);//hex2bcd(12));
    if(WKJQ == 0)//rg170531�޿�����
        {
            olcm_dispprintf(0,2,"  --�޿�����--",12.00);   
        }
    else if(WKJQ == 1)//rg170531�޿�����
        {
            olcm_dispprintf(0,2,"  --�п�����--",12.00);   
        }  
    else
	 {
            olcm_dispprintf(0,2,"  --�п�����--",12.00);   
        }  
    
 //   olcm_dispprintf(0,2,"  --��ӭʹ��--",12.00);
    if( gTick <  CanGasTime)
        olcm_dispprintf(2,3,"�����");
    else
        olcm_dispprintf(2,3,"��Ԥ��");
  ortcc_read_time((UINT8*)&sys_time[0]);
    _sys_tick_ = sys_time[5];
    simu_mm    = sys_time[4];
    olcm_dispprintf(0,4," %02d-%02d  %02d:%02d:%02d", sys_time[1], sys_time[2], sys_time[3], sys_time[4], sys_time[5]);
    b_mainui = TRUE;
}

void oui_main_ui_qry(void)//RG161220
{   
    olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"    ��  ѯ");
    olcm_dispprintf(0,1,"1.��¼  2.����");
    olcm_dispprintf(0,2,"3.����  4.ϵͳ");
    olcm_dispprintf(0,3,"5.Һ��  6.����");
    olcm_dispprintf(0,4,"7.����  8.�¶�");
//    olcm_dispprintf(0,4,"7.����  8.���帴");
    
}
void oui_main_ui_qry_soe(void)//rg160623
{   
    olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"    ��  ��");
    olcm_dispprintf(0,1,"1.�쳣��Ϣ      ");
    olcm_dispprintf(0,2,"2.���̸�λ��¼  ");
    olcm_dispprintf(0,3,"3.���帴λ��¼  ");
 //   olcm_dispprintf(0,4,"4.���к�        ");
}
void oqry_flow_l()
{
    UINT8 i=0;
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"Һ��������");
    olcm_dispprintf(0,2,"�¶�:");
    olcm_dispprintf(0,3,"����:");
    olcm_dispprintf(0,4,"����:");
     olcm_dispprintf(7,4,"��");
    UINT8 rdkey =0;
    float total;float temp;float gain;float Density;float ls;float yl;

    while(1)
    {
       if(TRUE != qty_get_l_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls ,(float *)&total,(float *)&yl))
       {
           SOEACTION1(PRO422_ERR,eCurRunState);//��ʱ�ȴ�Ҫ��һЩ
           // return;
           break;  //�˴���ͬ
       }
         {  rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey) break;
                   if(_KEY_EXIT_EV_ == rdkey) break;
                   if(_KEY_SW_EV_ == rdkey)
                   {
                        i=1;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"Һ��������");
//                        olcm_dispprintf(0,2,"�ۻ�:");
                        olcm_dispprintf(0,2,"�ܶ�:");
                        olcm_dispprintf(0,3,"ѹ��:");
                        olcm_dispprintf(7,4,"��");
                  }
                   if(_KEY_UP_EV_ == rdkey)
                   {
                        i=0;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"Һ��������");
                        olcm_dispprintf(0,2,"�¶�:");
                        olcm_dispprintf(0,3,"����:");
                        olcm_dispprintf(0,4,"����:");
                        olcm_dispprintf(7,4,"��");
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
    olcm_dispprintf(2,1,"����������");
    olcm_dispprintf(0,2,"�¶�:");
    olcm_dispprintf(0,3,"����:");
    olcm_dispprintf(0,4,"����:");
    olcm_dispprintf(7,4,"��");
    UINT8 rdkey =0;
    float total;float temp;float gain;float Density;float ls;float yl;
    while(1)
    {
       if(TRUE != qty_get_g_mod((float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls ,(float *)&total,(float *)&yl))
//        if(TRUE != qty_get_g_mod((float *)&total,(float *)&temp,(float *)&gain,(float *)&Density,(float *)&ls,(float *)&yl))
       {
           SOEACTION1(PRO422_ERR,eCurRunState);//��ʱ�ȴ�Ҫ��һЩ
          //  return;
           break;  //�˴���ͬ

       }
        {  rdkey = ostatemachine_getkey();
                   b_keyv = FALSE;
                   if(_KEY_STOP_EV_ == rdkey) break;
                   if(_KEY_EXIT_EV_ == rdkey) break;
                     if(_KEY_SW_EV_ == rdkey)
                   {
                        i=1;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"����������");
 //                       olcm_dispprintf(0,2,"�ۻ�:");
                        olcm_dispprintf(0,2,"�ܶ�:");
                        olcm_dispprintf(0,3,"����:");
                        olcm_dispprintf(7,4,"��");
                  }
                   if(_KEY_UP_EV_ == rdkey)
                   {
                        i=0;
                        olcd_clearsCreen();
                        olcm_dispprintf(2,1,"����������");
                        olcm_dispprintf(0,2,"�¶�:");
                        olcm_dispprintf(0,3,"����:");
                        olcm_dispprintf(0,4,"����:");
                        olcm_dispprintf(7,4,"��");
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
//    olcm_dispprintf(0,1,"    ѡ  ��");
    olcm_dispprintf(0,1,"1.Ԥ��  2.��ѯ");
    olcm_dispprintf(0,2,"3.����  4.����");
    olcm_dispprintf(0,3,"5.�쳣  6.�°�");
    olcm_dispprintf(0,4,"7.�޸Ŀ�����");
}

void oui_precool_ui(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ����Ԥ��");
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
    olcm_dispprintf(1,1,"��ѯ�����¶�");
    olcm_dispprintf(0,2,"�¶�:");
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
    olcm_dispprintf(0,1,"    ��  ѯ");
    olcm_dispprintf(0,2,"1.��ˮ  2.����");
    olcm_dispprintf(0,3,"3.����  4.ϵͳ");
#endif
    olcm_dispprintf(0,1,"1.������¼");
    olcm_dispprintf(0,2,"2.ϵͳ��Ϣ");
    olcm_dispprintf(0,3,"3.����Ϣ");
    olcm_dispprintf(0,4,"4.������Ϣ");

    //    //olcm_dispprintf(0,3,"2.�����¼");
}*/

