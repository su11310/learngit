 /*
 * File:   sysset.c
 * Author: jereh
 *
 * Created on 2014_02_23
 */

#include "../includes/global_def.h"
//static UINT8 prstep;
UINT8    stword[6]={"370602"};//��ʼ����  time:2014-3-13  rengang
const UINT8 default_init_str[] = {"jerehlng"};
const float default_float_paras[] = {//time:14-3-14 rengang
                               4.00, /*����*/
                               1.00, /*�ܶ�*/
                               1.00, /*����ϵ��*/
                               147,  /*ѹ�����*/
                               3.56, /*ѹ��ϵ��*/
                               1.2, /*��ǰѹ��*/
                               1.2, /*��ȫѹ��*/
                               162.00,/*Ԥ���¶�*/
                               5.0,   /*Ԥ������*/
                               3000,  /*Ԥ����ʱ*/
                               2.5,  /*�ܶ�����*/
                               1.8,  /*�ܶ�����*/
                               40000,/*�����ȴ�ʱ��*/
                               30,    /*pumpƵ��hz*/
                               1.43,  /*ͣ������*/
                               1.5,   /*ͣ��ѹ��*/
                               0.8,   //��С������
                               10,      //��С�������
                               1,   /*��ӡ���ã�0-�Զ� 1-�ֶ�*/
                               };
void oset_price(void)
{
   UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
   SYSTEMPARA systempara; //Mengfr 20161111
   
//   UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//   float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
   {//ͨ���쳣
    SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price = systempara.price;
   olcm_dispprintf(0,1,"���䵥��: %.02f",systempara.price);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);
        
        if( TRUE!= Set_price(tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           PRICE=tmp_price;
           odisp_price(PRICE, TRUE);
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price2(void)
{
   UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price2;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price2);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);
        
        if( TRUE!= Set_price2(0x50,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==2)
           PRICE2=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price3(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price3;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price3);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x51,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==3)
           PRICE3=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price4(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price4;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price4);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x52,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==4)
           PRICE4=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price5(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price5;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price5);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x53,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==5)
           PRICE5=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price6(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price6;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price6);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x54,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==6)
           PRICE6=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price7(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price7;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price7);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x55,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==7)
           PRICE7=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price8(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price8;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price8);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x56,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==8)
           PRICE8=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price9(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price9;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price9);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x57,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==9)
           PRICE9=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_price10(void)
{
      UINT8 len, vkey = 0;
   INT8  str[20] = {0};
   float tmp_price = 0.0,tmv_price = 0.0;
    float price2,price3,price4,price5,price6,price7,price8,price9,price10;
        if(TRUE != qty_get_pricex((float *)&price2 ,(float *)&price3,\
        (float *)&price4,(float *)&price5 ,(float *)&price6,(float *)&price7, (float *)&price8,(float *)&price9 ,(float *)&price10))
     {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
   olcd_clearsCreen();
   tmv_price=price10;
   olcm_dispprintf(0,1,"���䵥��: %.02f",price10);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        tmp_price = atof(str);

        if( TRUE!= Set_price2(0x58,tmp_price,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
//           if(Pr_gr==0x0a)
           PRICE10=tmp_price;
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
  }
   if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_machine_id(void)
{
   UINT8 len, vkey = 0;
   UINT8 id = 0;
   UINT8  str[10] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   
//     UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//  float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
    if (TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
    {//ͨ���쳣
        SOEACTION1(PRO422_ERR, eCurRunState);
        return;
    }
      //////////////
   olcd_clearsCreen();
   olcm_dispprintf(0,1,"����ǹ��: %d",systempara.qid);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,2,FALSE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        id = (UINT8)atoi(str);

            if( TRUE != Set_machineid((UINT8*)&id,len))//
               {
                //ͨ���쳣
               olcm_dispprintf(0,4,"    ����ʧ��    ");
               osys_getkey(_KEY_NULL_,300);
               SOEACTION1(PRO422_ERR,eCurRunState);
               return;
                }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
            cur_sysparas.p_gid = id;//qid;//Mengfr 20161111
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;

   }
       if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
BOOL oset_sysdatatime(void)//RG170110
{
	UINT8 timestr[6];
	while (1) {
		memset(timestr, 0, sizeof(timestr));
		if (TRUE == okey_timestr(timestr)) {
			if (ortcc_set_time((UINT8*) & timestr[0]) == TRUE) {
				olcm_dispprintf(0, 4, "    ���óɹ�    ");
				break;
			} else {
				olcm_dispprintf(0, 4, "    ����ʧ��    ");
				return FALSE;
			}
		} else
			return FALSE;
	}

	while (1) {
		memset(timestr, 0, sizeof(timestr));
		if (TRUE == okey_datestr(timestr)) {
			if (ortcc_set_date((UINT8*) & timestr[0]) == TRUE) {
				olcm_dispprintf(0, 4, "    ���óɹ�    ");
				return TRUE;
			} else {
				olcm_dispprintf(0, 4, "    ����ʧ��    ");
				return FALSE;
			}
		} else
			return FALSE;
	}
}
void oset_systime(void)
{
     UINT8 timestr[6] ;
     UINT8 qxset;
     qxset = o24lcxxx_read(qxset_addr);//rg160726
		if(qxset == 0xaa )//rg160726
		{
		olcd_clearsCreen();
		olcm_dispprintf(1, 2, "����������");
		olcm_dispprintf(1, 3, "�޷��޸�");
		osys_getkey(_KEY_NULL_, 300);
		eVirtualKey = _KEY_VIRTUAL_EV_;	
		return;
		}
     while(1)
     {
        memset(timestr,0,sizeof(timestr));
        if(TRUE == okey_timestr(timestr))
        {
            if( ortcc_set_time((UINT8*)&timestr[0]) == TRUE)
            {
                olcm_dispprintf(0,2,"    ���óɹ�    ");
                break;
            }
            else
            {
                olcm_dispprintf(0,2,"    ����ʧ��    ");
                break;
            }
        }
        break;
     }
     osys_getkey(_KEY_EXIT_EV_,300);
     eVirtualKey = _KEY_VIRTUAL_EV_;
}

//time:14-03-22 rengang
void oset_precool_temp(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

   if(TRUE != qty_get_sys(&systempara))   //Mengfr 20161111  
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
  //////////////
    olcm_dispprintf(0,1,"    �¶�����");
   olcm_dispprintf(0,2,"��ǰ:-%.02f",systempara.temp);
   olcm_dispprintf(6,2,"��");
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"���뷶Χ:0-120  ");//rg170629 
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);
         if(fEndr>120)//rg170629 
        {
           olcm_dispprintf(0,4,"  ��ֵ��Χ����  ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
           return;
        }
        if( TRUE!= Set_pre_temp(fEndr,4))//
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

//time:14-03-22 rengang
void oset_precool_gain(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//  float glbh;
//   float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
   {
       //ͨ���쳣
       SOEACTION1(PRO422_ERR,eCurRunState);
      return;
  }
  //////////////
   olcm_dispprintf(0,1,"    ��������    ");
   olcm_dispprintf(0,2,"��ǰ:%.02f",systempara.gain);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,2,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_gain(fEndr,4))//
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
//////////////
   
}
//time:14-03-22 rengang
void oset_lngEndR(void)
{
   UINT8 len, vkey = 0;
   float fEndr = 0,fqEndr = 0,fzEndr = 0;
   INT8  str[20] = {0};
   UINT16 addr,offset_id = 0;
   UINT8 types[3];
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
   {
       //ͨ���쳣
        SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
  //////////////
   olcm_dispprintf(0,1,"  ͣ����������");
   olcm_dispprintf(0,2,"��ǰ:%.01f kg/min",systempara.ls);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_lngEndR(fEndr,4))//
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
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_glbh(void)//RG160601
{
   UINT8 len, vkey = 0;
   float fEndr = 0,fqEndr = 0,fzEndr = 0;
   INT8  str[20] = {0};
   UINT16 addr,offset_id = 0;
   UINT8 types[3];
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//    float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
   olcm_dispprintf(0,1,"  ������������");
   olcm_dispprintf(0,2,"��ǰ:%.02f kg/min",systempara.glbh);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_glbh(fEndr,4))//
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
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
void oset_smallzxjqe(void)//rg181210 �ӿ���С�������
{
    UINT8 len,vkey = 0;
    INT8  str[20] = {0};
       UINT8 ce,CE;
       UINT8  zfk,zkkg;
       float wdcs,fEndr;
       UINT8 wbu;
       olcd_clearsCreen();
       zkkg = o24lcxxx_read(smallminimoney_addr);
       if(zkkg==0xA5)
  o24lcxxx_read_bytes_ex(smallminimoneydat_addr, (UINT8 *)&wdcs, 4);
       else
	wdcs=smallMini_Money;       

	olcm_dispprintf(0,1,"  �ӿ���Сʣ��  ");
   olcm_dispprintf(0,2,"��ǰ:           ");
   olcm_dispprintf(3,2,"%.02f   ",wdcs);
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"��Χ:50-300 Ԫ    ");  
   cursor_x = 4;
   cursor_y = 3;
      cxsr: olcm_dispprintf(3,3,"            ");
     vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
	   fEndr = (float)atof(str);
	   if(fEndr <SMALL_Mini_DO || fEndr > SMALL_Mini_UP) 
		{
		   olcm_dispprintf(0,4,"��ֵ����, ������");
		   osys_getkey(_KEY_NULL_,200);
		   olcm_dispprintf(0,4,"��Χ:50-300 Ԫ    ");
		goto cxsr;  
		}    
	  if(4 != o24lcxxx_write_bytes_ex(smallminimoneydat_addr,(UINT8*)&fEndr,4))
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           return;
         }
	   
	   wbu=0xA5;
	   if ( 1 != o24lcxxx_write_bytes(smallminimoney_addr,(UINT8*)&wbu,1 ) )
              {
                           olcm_dispprintf(0,4,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
			   return;
              }
             smallMini_FD=fEndr;
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
 }
void oset_djxs(void)//RG180327
{
      UINT8 len,vkey = 0;
    INT8  str[2] = {0};
//     if(ZK_POWER!=1) ZK_POWER = 0; //ǿ�Ʒ��㼴1
       UINT8 djset;
       SYSTEMPARA systempara;
    if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
    while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ������ʾ����");
    if(systempara.djxs>=1)
    olcm_dispprintf(0,2,"��ǰ��ִ�е���");
    if(systempara.djxs==0)
    olcm_dispprintf(0,2,"��ǰ��Ĭ�ϵ���");
//       olcm_dispprintf(0,2,"��ǰ��%d",zkkg);
       olcm_dispprintf(0,3,"����:");
       olcm_dispprintf(1,4," 0Ĭ�� 1ִ��");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,1,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
          if(str[0] < '2')
          {
              djset = (UINT8)atoi(str);
                          if(djset>=1)
              olcm_dispprintf(0,2,"��ǰ��ִ�е���");
            if(djset==0)
                olcm_dispprintf(0,2,"��ǰ��Ĭ�ϵ���");
              if( TRUE!= ocompany_send_daxs(6,0x63,djset))
              {			
		      olcm_dispprintf(0,4,"    ����ʧ��    ");
                           osys_getkey(_KEY_NULL_,300);
				SOEACTION1(PRO422_ERR,eCurRunState);
              }
              else
              {
                olcm_dispprintf(4,3,"���óɹ�");
                osys_getkey(_KEY_NULL_,320);
              }
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
          }
        }
        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }
   
}
void oset_lsyspd(void)//RG160704
{
	   UINT8 len  = 0;
     UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
     UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     ortcc_read_time(shift_op_time);

     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //Сʱ*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //Сʱ*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //��
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //��

     INT8 passbuf[6] = {psw1,psw2,'4','1',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ����������ʱ");
    olcm_dispprintf(0,2,"����������: ");
      while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
            }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                      //  if(strcmp(tmpbuf, passbuf) == 0)
                if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                {
 UINT8 len, vkey = 0;
   float fEndr = 0,fqEndr = 0,fzEndr = 0;
   INT8  str[20] = {0};
   UINT16 addr,offset_id = 0;
   UINT8 types[3];
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//    float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
   olcm_dispprintf(0,1,"  ������ʱ�ж�  ");
   //olcm_dispprintf(0,2,"��ǰ:%.02f",systempara.lspd);
   olcm_dispprintf(0,2,"��ǰ:%02d.%02d",systempara.lspd / 100,systempara.lspd % 100);
   olcm_dispprintf(5,2,"��");
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"��Χ��10��--30��");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,5,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
       
        fEndr = (float)atof(str);
        if(fEndr < 10 || fEndr > 30)  //ֵ����
        {
            olcm_dispprintf(0,4,"    ���ó���    ");
	    
            osys_getkey(_KEY_NULL_,320);
	    eVirtualKey = _KEY_VIRTUAL_EV_;
	    eCurRunState = State_ls_Set;
            return;
        }
        if( TRUE!= Set_lspd(fEndr,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           SOEACTION1(PRO422_ERR,eCurRunState);
	   eCurRunState = State_ls_Set;
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
	   eCurRunState = State_ls_Set;
	   return;
   }
	else if ( vkey == _KEY_EXIT_EV_)
       {eVirtualKey = _KEY_VIRTUAL_EV_;
       eCurRunState = State_ls_Set;
       return;
       }
                  }
                            else
                          {   
                              len = 0;
                               olcd_clearsCreen();
                              olcm_dispprintf(0,2,"�������������");
                               KeyEccgtick = gTick+100;
                          }     
                     }
          }
  //    }
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
            eCurRunState = State_ls_Set;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
     
  
}
void oset_qxsz(void)//RG160726
{
	   UINT8 len  = 0;
     UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
     UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     UINT8 vkey = 0;
   float fEndr = 0,fqEndr = 0,fzEndr = 0;
   INT8  str[20] = {0};
   UINT16 addr,offset_id = 0;
   UINT8 types[3];
   UINT8 qx,qxset,qxco;
   UINT32 qx_min;
     ortcc_read_time(shift_op_time);

     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //Сʱ*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //Сʱ*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //��
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //��

     INT8 passbuf[6] = {psw1,psw2,'4','4',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ��������");
    olcm_dispprintf(0,2,"����������: ");
      while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
            }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                {
 
   olcd_clearsCreen();
   
   qx = o24lcxxx_read(qxsz_yue_addr);
//   qx2 = o24lcxxx_read(zk_power_addr);
   //////////////
   olcm_dispprintf(0,1,"  ��������  ");
   olcm_dispprintf(0,2,"��ǰ:%02d",qx);
   olcm_dispprintf(5,2,"��");
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"��Χ��1--12");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,2,FALSE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
       qxco=(UINT8)atoi(str);
       fEndr = (float)atof(str);
        if( (qxco < 1) || (qxco > 12))  //ֵ����
        {
            olcm_dispprintf(4,3,"���ó���");
	    
            osys_getkey(_KEY_NULL_,320);
	    eVirtualKey = _KEY_VIRTUAL_EV_;
	    eCurRunState = State_Set_power;
            return;
        }
	if ( 1 != o24lcxxx_write_bytes(qxsz_yue_addr,(UINT8*)&qxco,1 ) )
              {
		
                           olcm_dispprintf(4,3,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
              }
              else
              {
		fqEndr = fEndr*30*24*12;  //5���ӵĸ���
        //
		qx_min=(UINT32)(fqEndr);
		QX_RECORD=qx_min;
		if(1 == Save_Qx_Runtime(QX_RECORD))	
                {
		qxset=0xaa;
		if(1 == Save_QxSet_Bit(qxset))
		olcm_dispprintf(4, 3, "���óɹ�");
		else
		olcm_dispprintf(4, 3, "д��ʧ��");
                osys_getkey(_KEY_NULL_,320);
		}
		else
		{
		olcm_dispprintf(4,3,"����ʧ��");
                osys_getkey(_KEY_NULL_,320);	
		}
		
		
              }
		eVirtualKey = _KEY_VIRTUAL_EV_;
		eCurRunState = State_Set_power;
		break;
   }
	else if ( vkey == _KEY_EXIT_EV_)
       {eVirtualKey = _KEY_VIRTUAL_EV_;
       eCurRunState = State_Set_power;
       return;
       }
                  }
                            else
                          {   
                              len = 0;
                               olcd_clearsCreen();
                              olcm_dispprintf(0,2,"�������������");
                               KeyEccgtick = gTick+100;
                          }     
                     }
          }
  //    }
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
            eCurRunState = State_Set_power;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
     
  
}
void oset_lngEndP(void)
{
   UINT8 len, vkey = 0;
   float fEndp = 0;
   INT8  str[20] = {0};
   olcd_clearsCreen();
   olcm_dispprintf(0,1,"  ͣ��ѹ������");
   olcm_dispprintf(0,2,"��ǰ:%.01f MPa",(float)cur_sysparas.p_EndP);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,3,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndp = (float)atof(str);
        if(4 == o24lcxxx_write_bytes(_SYSPARAS_EEP_ADDR+offsetof(struct _def_SysParas,p_EndP),(UINT8*)&fEndp,4))
        {
            cur_sysparas.p_EndP = fEndp;
            olcm_dispprintf(0,4,"    ���óɹ�    ");
            osys_getkey(_KEY_NULL_,300);
        }
   }
   eVirtualKey = _KEY_VIRTUAL_EV_;
}


void oset_system_ui(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ϵ    ͳ");
    olcm_dispprintf(0,2,"1.�°�    2.�ϰ�");
    olcm_dispprintf(0,3,"3.ϵͳ");
}



BOOL oset_init_str_chk(void)
{
    UINT8 str[12] ={0};
    //o24lcxxx_read_bytes(_SYSPARAS_INIT_ADDR, (UINT8*)&str[0], sizeof((UINT8*)&default_init_str[0]));
    o24lcxxx_read_bytes_ex(_SYSPARAS_INIT_ADDR, (UINT8*)&str[0], sizeof((UINT8*)&default_init_str[0]));
    if( memcmp( (UINT8*)&str[0], (UINT8*)&default_init_str[0],sizeof((UINT8*)&default_init_str[0]) ) == 0)
    {
        return TRUE;
    }
    return FALSE;
}
void oclear_class()
{
    UINT8 cn;
    for(cn=1;cn<11;cn++)
    {      cur_class_info[cn-1].class_state=0;
           cur_class_info[cn-1].c_pw_len=0;
           memset(&cur_class_info[cn-1].class_pw,0x0,11);
            o24lcxxx_write_bytes_ex(_SHIFT_SYSPARAS_EEP_ADDR_END+CLASSSIZE*(cn-1),(UINT8*)&cur_class_info[cn-1].class_num,CLASSLEN);             }
}
void oset_system(void)
{
    BOOL bok = TRUE;
    UINT16 len = 0;
    UINT16 i,addr = 0;
    UINT8  m, n = 0;
    UINT8  cnt = 0;
    UINT8  clr[128];// = 0;
    UINT8  rdkey = 0;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"�ָ���������");
    olcm_dispprintf(0,2,"ȷ�ϼ��ָ�");
    olcm_dispprintf(0,3,"���ļ�����");
while(1)
 {
 rdkey = ostatemachine_getkey();
      b_keyv = FALSE;

  if(_KEY_ENTER_EV_ == rdkey)
    {
       if(TRUE != defConfig())
      {//ͨ���쳣
         SOEACTION1(PRO422_ERR,eCurRunState);
         return;

      }
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"���óɹ�");

    osys_getkey(_KEY_NULL_,300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
     return;
    }

  if(_KEY_EXIT_EV_ == rdkey)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
        return;
   }
 }
}
void SET_HARD_VER(void)    //150906
{    UINT8 len  = 0;
     UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
     UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     ortcc_read_time(shift_op_time);

     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //Сʱ*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //Сʱ*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //��
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //��

     INT8 passbuf[6] = {psw1,psw2,'3','7',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"����Ӳ���汾��Ϣ");
    olcm_dispprintf(0,2,"����������: ");

    while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
           }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                      //  if(strcmp(tmpbuf, passbuf) == 0)
                          if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                          {
                             // olcm_dispprintf(0,2,"������յ��Լ�¼");
                            //  olcm_dispprintf(0,3,"���Ե�....");
                              oset_Density_down();
                             
                              
                               eCurRunState = State_module_test;
                              eVirtualKey = _KEY_VIRTUAL_EV_;
                              return;
                          }
                          else
                          {   
                              len = 0;
                              olcm_dispprintf(0,2,"�������������");
                              olcm_dispprintf(0,3,"                ");
                              KeyEccgtick = gTick+100;
                          }     
                     }

                 }
           
        
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
  
}

void Debud_record_clrAll_psw(void)    //150730 
{    UINT8 len  = 0;
     UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
     UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     ortcc_read_time(shift_op_time);

     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //Сʱ*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //Сʱ*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //��
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //��

     INT8 passbuf[6] = {psw1,psw2,'3','6',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"��յ��Լ�����¼");
    olcm_dispprintf(0,2,"����������: ");

    while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
           }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                      //  if(strcmp(tmpbuf, passbuf) == 0)
                          if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                          {
                              olcm_dispprintf(0,2,"������յ��Լ�¼");
                              olcm_dispprintf(0,3,"���Ե�....");
                              if(Clr_debudjilu_die()==TRUE) //��ʱʱ���賤һ��
                              { delay_ms(20000);//2s
                                olcd_clearsCreen();
                                olcm_dispprintf(0,1,"    ��ռ�¼");
                                
                                while(1)
                                {
                                    olcm_dispprintf(0,2,"  ��ճɹ�!!  ");
                                    olcm_dispprintf(0,3,"  ��ϵ�����ϵͳ");
                                }
                               // olcm_dispprintf(0,4,"  ���˳�!       ");
                              }
                              else
                              {
                                 olcd_clearsCreen();
                                olcm_dispprintf(0,1,"  ��ռ�¼");
                                olcm_dispprintf(0,2,"  ���ʧ��!!");
                                olcm_dispprintf(0,3,"������·!");
                              }
                              osys_getkey(_KEY_NULL_,500);
                              eVirtualKey = _KEY_VIRTUAL_EV_;
                              return;
                          }
                          else
                          {   
                              len = 0;
                              olcm_dispprintf(0,2,"�������������");
                              olcm_dispprintf(0,3,"                ");
                              KeyEccgtick = gTick+100;
                          }     
                     }

                 }
           
        
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
  
}
void vctrl_test_psw(void)    //RG171229 
{    UINT8 len  = 0;
     UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
     UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     ortcc_read_time(shift_op_time);

     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //Сʱ*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //Сʱ*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //��
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //��

     INT8 passbuf[6] = {psw1,psw2,'4','2',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ��ŷ�����  ");
    olcm_dispprintf(0,2,"����������: ");

    while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
           }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                      //  if(strcmp(tmpbuf, passbuf) == 0)
                          if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                          {
				  omodule_vctrl_test_init();
				  delay_ms(200);
                             omodule_vctrlopen_test();
                   //           osys_getkey(_KEY_NULL_,500);
                              eVirtualKey = _KEY_VIRTUAL_EV_;
                              return;
                          }
                          else
                          {   
                              len = 0;
                              olcm_dispprintf(0,2,"�������������");
                              olcm_dispprintf(0,3,"                ");
                              KeyEccgtick = gTick+100;
                          }     
                     }

                 }
           
        
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
}
void systemclr_psw(void)
{    UINT8 len  = 0;
     UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
     UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     ortcc_read_time(shift_op_time);

     psw1 = (UINT8)(shift_op_time[3]*2/10)+0x30;  //Сʱ*2/10
     psw2 = (UINT8)(shift_op_time[3]*2%10)+0x30;  //Сʱ*2
     psw5 = (UINT8)(shift_op_time[2]/10)+0x30;  //��
     psw6 = (UINT8)(shift_op_time[2]%10)+0x30;  //��

     INT8 passbuf[6] = {psw1,psw2,'3','5',psw5,psw6};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ������¼");
    olcm_dispprintf(0,2,"����������: ");

    while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
           }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                      //  if(strcmp(tmpbuf, passbuf) == 0)
                          if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                          {
                              olcm_dispprintf(0,2,"���ڲ���    ");
                              olcm_dispprintf(0,3,"���Ե�....");
                              if(systemclr()==TRUE) //��ʱʱ���賤һ��
                              { delay_ms(200000);//20s
                                olcd_clearsCreen();
                                olcm_dispprintf(0,1,"    ������¼");
                                
                                while(1)
                                {
                                    olcm_dispprintf(0,2,"  �����ɹ�!!  ");
                                    olcm_dispprintf(0,3,"  ��ϵ�����ϵͳ");
                                }
                               // olcm_dispprintf(0,4,"  ���˳�!       ");
                              }
                              else
                              {
                                 olcd_clearsCreen();
                                olcm_dispprintf(0,1,"  ������¼");
                                olcm_dispprintf(0,2,"  ����ʧ��!!");
                                olcm_dispprintf(0,3,"������·!");
                              }
                              osys_getkey(_KEY_NULL_,500);
                              eVirtualKey = _KEY_VIRTUAL_EV_;
                              return;
                          }
                          else
                          {   
                              len = 0;
                              olcm_dispprintf(0,2,"�������������");
                              olcm_dispprintf(0,3,"                ");
                              KeyEccgtick = gTick+100;
                          }     
                     }

                 }
           
        
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
  
}

BOOL Clr_debudjilu_die(void)
{
    BOOL bok = TRUE;
    UINT16 addr = 0;
    UINT8  m, n = 0;
    UINT8  cnt = 0;
   UINT16 addrFA = DEBUG_RECORD_SAVE; //��ַ
    UINT8 idnum = 0;
  UINT8 save_debugjl =0; //д������Ա���
      UINT8 kmm=10;
      float resetsave_vol = 0;
   ///////////////////�������Լ�¼�����//////////////////////////////
      while(kmm--)
       {
         if ( TRUE == o24lcxxx_write_bytes_ex(DEBUG_RECORD_MAXNUM,&save_debugjl,1))    //1121
             {   break;
             }

        }
///////////////////////�������Լ�����¼////////////////
      idnum = 0;
       for(addrFA=DEBUG_RECORD_SAVE; addrFA<DEBUG_RECORD_SAVE_END; addrFA++)  //0x3E7F
        {
            o24lcxxx_write_bytes_ex(addrFA, (UINT8*)&idnum, 1); //1121
        }

///////////////////////////////
  
  MAX_dubug_recid_num=0;  //���������150730
 
    eVirtualKey = _KEY_VIRTUAL_EV_;
    return TRUE;
}

BOOL systemclr(void)
{
    BOOL bok = TRUE;
    UINT16 addr = 0;
    UINT8  m, n = 0;
    UINT8  cnt = 0;
    UINT8  clr[128];// = 0;
 //   ClearNameStation();
    SOE_DELEALL();//SOE���
   Clr_debudjilu_die();   //150730 ��յ��Լ�����¼
    oclear_class();//����
    ClearSysRuntime();//ϵͳ����ʱ�����
    ResetFaultReasonRecInit();//rg160623
//    ClearNameStation();
  cur_max_recid=0;
  cur_max_reset=0;
  cur_max_shiftid=0;
  cur_max_paraid=0;
       if(TRUE != Sysclear())
      {//ͨ���쳣
      //   SOEACTION1(PRO422_ERR,eCurRunState);
         return FALSE;

      }
   // osys_getkey(_KEY_NULL_,300);
    eVirtualKey = _KEY_VIRTUAL_EV_;
    return TRUE;
}
/*------------------------------------------------------------------------------
 * ��ˮ��¼�ĺϷ�����֤
------------------------------------------------------------------------------*/
BOOL oset_system_data_chk(UINT32 maxid)
{
    return TRUE;
}
/*------------------------------------------------------------------------------
 * 
------------------------------------------------------------------------------*/
void init_eeprom_shift_info(void)
{
    UINT32 addr;
    UINT8  n;
    UINT32         maxid = 0;
    addr = _SHIFT_SYSPARAS_EEP_ADDR_P1;
   // o24lcxxx_read_bytes_ex(addr, (UINT8*)&tmp_rec_info, len);
    for( n = 0; n < _REC_SYSINFO_PAGES_ ; n++ )
    {
            //o24lcxxx_read_bytes(addr, (UINT8*)&tmp_rec_info.g_uid, len);
            o24lcxxx_write_bytes_ex(addr+offsetof(_rec_shift_info, g_uid), (UINT8*)&maxid, 4); 
            o24lcxxx_write_bytes_ex(addr+offsetof(_rec_shift_info, sig_uid), (UINT8*)&maxid, 4);
            addr += _SHIFT_SYSINFO_PAGE_SZIE_; 
    }
    
    
}
UINT32 oset_system_get_max_rec_id(void)
{
    _rec_shift_info   tmp_rec_info;
    UINT16         len = sizeof( _rec_shift_info);
    UINT16         n, addr;
    UINT32         maxid = 0;
    addr = _SHIFT_SYSPARAS_EEP_ADDR_P1;
    for( n = 0; n < _SHIFT_SYSINFO_PAGES_ ; n++ )
    {
            //o24lcxxx_read_bytes(addr, (UINT8*)&tmp_rec_info.g_uid, len);
            o24lcxxx_read_bytes_ex(addr+offsetof(_rec_shift_info, g_uid), (UINT8*)&tmp_rec_info.g_uid, 4);
           // o24lcxxx_read_bytes_ex(addr, (UINT8*)&tmp_rec_info, len);
            addr += _SHIFT_SYSINFO_PAGE_SZIE_;
            if(tmp_rec_info.g_uid > maxid ) 
                maxid = tmp_rec_info.g_uid;
    }
    return maxid;
}
/*---------------------------       ��õ�ǰ������°�ļ�¼��        ---------------------------------------*/
UINT32 oset_system_get_max_login_id(void)
{
    _rec_shift_info   tmp_rec_info;
    UINT16         len = sizeof( _rec_shift_info);
    UINT16         n, addr;
    //UINT32         gIDs[_REC_SYSINFO_PAGES_ + 1] = {0};
    UINT32         maxid;
    addr = _SHIFT_SYSPARAS_EEP_ADDR_P1;
   // o24lcxxx_read_bytes_ex(addr, (UINT8*)&tmp_rec_info, len);
    for( n = 0; n < _REC_SYSINFO_PAGES_ ; n++ )
    {
            //o24lcxxx_read_bytes(addr, (UINT8*)&tmp_rec_info.g_uid, len);
            o24lcxxx_read_bytes_ex(addr+offsetof(_rec_shift_info, sig_uid), (UINT8*)&tmp_rec_info.sig_uid, len);
            addr += _REC_SYSINFO_PAGE_SZIE_;
           // gIDs[n] = tmp_rec_info.g_uid;
            oprint_printf("current max id id %d\r\n\r\n",tmp_rec_info.sig_uid);
            if(tmp_rec_info.sig_uid > maxid ) maxid = tmp_rec_info.sig_uid;
    }
    return maxid;
}

UINT32 oset_system_get_max_shift_id(void)
{
#if 0
    _rec_shift_info tmp_shift_info;
    UINT16          len = sizeof(_rec_shift_info);
    UINT16          n, addr;
    UINT32          gIDs[_SHIFT_SYSINFO_PAGES_ + 1] = {0};
    UINT32          maxid = 0;
    addr = _SHIFT_SYSINFO_EEP_ADDR;
    for( n = 0; n < _SHIFT_SYSINFO_PAGES_ ; n++ )
    {
            //o24lcxxx_read_bytes(addr, (UINT8*)&tmp_shift_info.shift_rec_id, len);
            o24lcxxx_read_bytes_ex(addr+offsetof(_rec_shift_info, sig_uid), (UINT8*)&tmp_shift_info.sig_uid, len);
            addr += _SHIFT_SYSINFO_PAGE_SZIE_;
            gIDs[n] = tmp_shift_info.sig_uid;
            if(gIDs[n] > maxid)
                maxid = gIDs[n];
    }
    return maxid;
#endif
}
//ȡ�õ�ǰ����޸ļ�¼�� time:14-03-22 rengang
UINT32 oset_system_get_max_para_id(void)
{
    un_paraup   tmp_para_info;
    UINT16         len = sizeof(struct _def_paraup);
    UINT16         n, addr;
    UINT32         gIDs[_PARA_PAGES_ + 1] = {0};
    UINT32         maxid;
    addr = _PARA_EEP_ADDR;
    for( n = 0; n < _PARA_PAGES_ ; n++ )
    {
            o24lcxxx_read_bytes_ex(addr, (UINT8*)&tmp_para_info.para_rec_id, len);
            addr += _PARA_PAGE_SZIE_;
            gIDs[n] = tmp_para_info.para_rec_id;
    }
    maxid = gIDs[0];
    for( n = 0; n < _PARA_PAGES_ ; n++ )
    {
        if(maxid < gIDs[n])
        {
            maxid = gIDs[n];
        }
    }
    return maxid;
}


void osysparas_set_ui_p1(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.Ԥ���¶�");
    olcm_dispprintf(0,2,"2.Ԥ������");
    olcm_dispprintf(0,3,"3.Ԥ����ʱ");
    olcm_dispprintf(0,4,"4.ͣ������");
    olcm_dispprintf(7,4,"��");
}

void osysparas_set_ui_p2(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"5.����ϵ��");
    olcm_dispprintf(0,2,"6.ѹ��ϵ��");
    olcm_dispprintf(7,4,"��");
}


void osysparas_set_ui_switch(void)
{
    switch( _ui_paras_set_id )
    {
        case 1:
            osysparas_set_ui_p1();
            break;
        case 2:
            osysparas_set_ui_p2();
            break;
        default:
            break;
    }
}
void oset_team_ma(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.�޸İ�������");
 //   olcm_dispprintf(0,2,"2.�޸Ŀ�����");
    olcm_dispprintf(0,2,"2.���Ӱ���");
    olcm_dispprintf(0,3,"3.ɾ������");
}
void omenu_team_modipw()
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  �޸İ�������");
    olcm_dispprintf(0,2,"����:");
    olcm_dispprintf(0,3,"����:");
}
void omenu_car_modipw()
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  �޸Ŀ�����");
    olcm_dispprintf(0,2,"������:");
}
void omenu_team_addclass()
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ���Ӱ���");
    olcm_dispprintf(0,2,"����:");
    olcm_dispprintf(0,3,"����:");
}
void omenu_team_delclass()
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ɾ������");
    olcm_dispprintf(0,2,"����:");
    olcm_dispprintf(0,3,"����:");
}
void oset_team_modi(void)
{
     olcd_clearsCreen();
     UINT8 len, vkeycn,vkeypw,j;
     UINT8 cn,getnum,n;
     UINT16 addr;
     class_sum=10;
      j=0;
      vkeycn=0;
      vkeypw=0;
      UINT8  strcn[2] = {0};
      UINT8  strpw[6] = {0};
      oset_getclassxx();
      omenu_team_modipw();
          while(1)
             {
getkeycn:    cursor_x=3;
             cursor_y=2;
             olcm_dispprintf(3,2,"    ");
              vkeycn = okeyinput_getstr(strcn,&len ,2,FALSE,FALSE);
            if( vkeycn == _KEY_EXIT_EV_ )
             {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
                }
            cn=atoi(strcn);
            if(cur_class_info[cn-1].class_state!=1)
            {
               j=j+1;
               olcm_dispprintf(3,2,"          ");
               olcm_dispprintf(0,4,"��Ч���飬����  ");
               if (j<3)
               goto getkeycn;
               else
               olcm_dispprintf(0,4,"    �������    ");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_VIRTUAL_EV_;
               return ;
            }
            if((vkeycn==_KEY_ENTER_EV_)&&cn<=class_sum)
            {
  getkey1:    cursor_x=3;
              cursor_y=3;
              olcm_dispprintf(3,3,"      ");
              vkeypw = okeyinput_getstr(strpw,&len ,10,FALSE,FALSE);
             if( vkeypw == _KEY_EXIT_EV_ )
            {
              eVirtualKey = _KEY_VIRTUAL_EV_;
              return ;
            }
            if((strcmp(strpw,cur_class_info[cn-1].class_pw)!=0)&&(strcmp(strpw,stword)!=0))
            {
                j=j+1;
                olcm_dispprintf(3,3,"          ");
            if (j<3)
            {
                olcm_dispprintf(0,4,"�����������  ");
                goto getkey1;
            }
            else
                olcm_dispprintf(0,4,"    ���˳�    ");
                osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
            }
       else
       {
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"  ����������  ");
             olcm_dispprintf(0,2,"���룺");
getkeyn:     cursor_x=3;
             cursor_y=2;
             vkeypw = okeyinput_getstr(strpw,&len ,10,FALSE,FALSE);
            if( vkeypw == _KEY_EXIT_EV_ )
            {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
            }
            if( vkeypw == _KEY_OK_EV_ )
            {
                memset(cur_class_info[cn-1].class_pw,0x00,11);
                cur_class_info[cn-1].class_num=cn;
                cur_class_info[cn-1].class_state=1;
                cur_class_info[cn-1].c_pw_len=len;
                memcpy(cur_class_info[cn-1].class_pw,strpw,len);
                if ( getnum= o24lcxxx_write_bytes_ex(_SHIFT_SYSPARAS_EEP_ADDR_END+CLASSSIZE*(cn-1),(UINT8*)&cur_class_info[cn-1].class_num,CLASSLEN))
                    {
                        olcm_dispprintf(0,4,"    �޸ĳɹ�    ");

                    }
                oset_getclassxx();
                osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
                 }
                }
            }
        else
        {
          olcm_dispprintf(3,2,"            ");
          olcm_dispprintf(0,4,"����Ŵ������䣡");
        }
        }
                 osys_getkey(_KEY_NULL_,300);
                 eVirtualKey = _KEY_VIRTUAL_EV_;
  }
void oset_team_cardmm(void)
{
        olcd_clearsCreen();
     UINT8 len, vkeycn,vkeypw,j;
     UINT8 cn,getnum,n;
     UINT16 addr;
     UINT8 passbuf[10];
    UINT8 pass[10];
    UINT8 len1,len2 = 6;
     class_sum=10;
      j=0;
      vkeycn=0;
      vkeypw=0;
      UINT8  strcn[2] = {0};
      UINT8  strpw[6] = {0};
  //    oset_getclassxx();
      omenu_car_modipw();
          while(1)
             {
#if 0
getkeycn:    cursor_x=3;
             cursor_y=2;
             olcm_dispprintf(3,2,"    ");
              vkeycn = okeyinput_getstr(strcn,&len ,2,FALSE,FALSE);
            if( vkeycn == _KEY_EXIT_EV_ )
             {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
                }
            cn=atoi(strcn);
            if(cur_class_info[cn-1].class_state!=1)
            {
               j=j+1;
               olcm_dispprintf(3,2,"          ");
               olcm_dispprintf(0,4,"��Ч���飬����  ");
               if (j<3)
               goto getkeycn;
               else
               olcm_dispprintf(0,4,"    �������    ");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_VIRTUAL_EV_;
               return ;
            }
#endif
 //           if((vkeycn==_KEY_ENTER_EV_)&&cn<=class_sum)
  //          {
  getkey1:    cursor_x=4;
              cursor_y=2;
              olcm_dispprintf(4,2,"      ");
              vkeypw = okeyinput_getstr(strpw,&len ,6,FALSE,FALSE);
             if( vkeypw == _KEY_EXIT_EV_ )
            {
              eVirtualKey = _KEY_VIRTUAL_EV_;
              return ;
            }
              ic_card_get_password(passbuf,&len2);//��ÿ�����
  //            if(len2 == len1)
  //                    {
                         if(memcmp(strpw, passbuf,6) != 0)
                          {
                            j=j+1;
                            olcm_dispprintf(4,2,"          ");
                            if (j<3)
                            {
                            olcm_dispprintf(0,4,"�����������  ");
                            goto getkey1;
                               }
                             else
                             {
                                olcm_dispprintf(0,4,"    ���˳�    ");
                            osys_getkey(_KEY_NULL_,300);
                            eVirtualKey = _KEY_VIRTUAL_EV_;
                            return ;
                             }
                            }
        else
       {
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"  ����������  ");
             olcm_dispprintf(0,2,"�����룺");
getkeyn:     cursor_x=4;
             cursor_y=2;
             vkeypw = okeyinput_getstr(strpw,&len ,6,FALSE,FALSE);
            if( vkeypw == _KEY_EXIT_EV_ )
            {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
            }
            if( vkeypw == _KEY_OK_EV_ )
            {
                 if ( TRUE== ic_card_put_password(strpw, len))
                    {
                        olcm_dispprintf(0,4,"    �޸ĳɹ�    ");
                    }
                oset_getclassxx();
                osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
                 }
                }
 //           }
 //       else
  //      {
  //        olcm_dispprintf(3,2,"            ");
  //        olcm_dispprintf(0,4,"����Ŵ������䣡");
 //       }
        }
                 osys_getkey(_KEY_NULL_,300);
                 eVirtualKey = _KEY_VIRTUAL_EV_;
}
//��Ӱ���  time:2013-3-13  rengang
void oset_team_add(void)
{
       UINT8 len, vkeycn,vkeypw,j;
       UINT8 cn,getnum,cslen;
       class_sum=10;
      j=0;
      vkeycn=0;
      vkeypw=0;
      UINT8  strcn[2] = {0};
      UINT8  strpw[6] = {0};
      UINT16 n,addr;
      omenu_team_addclass();
      oset_getclassxx();
      while(1)
     {
getkeyadd:  cursor_x=3;
            cursor_y=2;
            olcm_dispprintf(3,2,"        ");
            vkeycn = okeyinput_getstr(strcn,&len ,2,FALSE,FALSE);
            if( vkeycn == _KEY_EXIT_EV_ )
            {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
            }
            cn=atoi(strcn);
            if(cur_class_info[cn-1].class_state==1)
            {
               olcm_dispprintf(0,4,"�����Ѵ���, ����");
               osys_getkey(_KEY_NULL_,300);
               olcm_dispprintf(0,4,"                ");
              continue;
             }
            if((vkeycn==_KEY_ENTER_EV_)&&(cn<=class_sum)&&(cur_class_info[cn-1].class_state!=1))
            {
getkeya:       cursor_x=3;
               cursor_y=3;
               vkeypw = okeyinput_getstr(strpw,&len ,10,FALSE,FALSE);
            if(len>10)
            {
               olcm_dispprintf(0,4,"  ����10 λ��������  ");
               olcm_dispprintf(3,2,"                ");
               goto getkeya;
            }
           if( vkeypw == _KEY_EXIT_EV_ )
            {
               eVirtualKey = _KEY_VIRTUAL_EV_;
               return ;
            }
           if(vkeypw == _KEY_ENTER_EV_ )
            {
               memset(cur_class_info[cn-1].class_pw,0x00,11);
               cur_class_info[cn-1].class_num=cn;
               cur_class_info[cn-1].class_state=1;
               cur_class_info[cn-1].c_pw_len=len;
               memcpy(cur_class_info[cn-1].class_pw,strpw,len);
                if ( getnum= o24lcxxx_write_bytes_ex(_SHIFT_SYSPARAS_EEP_ADDR_END+CLASSSIZE*(cn-1),(UINT8*)&cur_class_info[cn-1].class_num,CLASSLEN))
                  {
                      olcm_dispprintf(0,4,"    ���ӳɹ�    ");
                   }
                osys_getkey(_KEY_NULL_,280);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
                }
            }
            else
            {
                j=j+1;
                olcm_dispprintf(3,2,"            ");
                olcm_dispprintf(0,4,"����Ŵ�������");
                if (j<3)
                goto getkeyadd;
                else
                olcm_dispprintf(0,4,"����Ŵ���, �˳�");
   //            osys_getkey(_KEY_NULL_,280);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
             }
     }
     osys_getkey(_KEY_NULL_,280);
     eVirtualKey = _KEY_VIRTUAL_EV_;
  }
//ɾ������  time:2013-3-13  rengang
void oset_team_del(void)
{
        olcd_clearsCreen();
        UINT8 len, vkeycn,vkeypw,j,getnum;
        UINT8 cn,pn[6];
        UINT8  strcn[2] = {0};
        UINT8  strpw[10] = {0};
        UINT16 n,addr;
        class_sum=10;
        j=0;
        vkeycn=0;
        vkeypw=0;
        omenu_team_delclass();
        oset_getclassxx();
         while(1)
        {
getkeydel:  cursor_x=3;
            cursor_y=2;
            olcm_dispprintf(3,2,"        ");
            vkeycn = okeyinput_getstr(strcn,&len ,2,FALSE,FALSE);
            cn=atoi(strcn);
            if( vkeycn == _KEY_EXIT_EV_ )
            {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
         }
       if(cur_class_info[cn-1].class_state!=1)
        {
            olcm_dispprintf(0,4,"  ��Ч���飬����");
            osys_getkey(_KEY_NULL_,300);
            olcm_dispprintf(0,4,"                ");
            continue;
        }
        if((vkeycn==_KEY_ENTER_EV_)&&cn<=class_sum)
          {
            cursor_x=3;
            cursor_y=3;
getkeyb:    vkeypw = okeyinput_getstr(strpw,&len ,10,FALSE,FALSE);
            if( vkeypw == _KEY_EXIT_EV_ )
              {
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
                }
        if((strcmp(strpw,cur_class_info[cn-1].class_pw)!=0)&&(strcmp(strpw,stword)!=0))
          {
            j=j+1;
            olcm_dispprintf(3,3,"          ");
            olcm_dispprintf(0,4,"�����������  ");
            if (j<2)
                goto getkeyb;
            else
                olcm_dispprintf(0,4,"    ���˳�    ");
            osys_getkey(_KEY_NULL_,320);
            eVirtualKey = _KEY_VIRTUAL_EV_;
            return ;
            }
       else
            {
              cur_class_info[cn-1].class_state=0;
              cur_class_info[cn-1].c_pw_len=0;
              memset(&cur_class_info[cn-1].class_pw,0x0,11);
            if( getnum= o24lcxxx_write_bytes_ex(_SHIFT_SYSPARAS_EEP_ADDR_END+CLASSSIZE*(cn-1),(UINT8*)&cur_class_info[cn-1].class_num,CLASSLEN))
              {
                olcm_dispprintf(0,4,"    ɾ���ɹ�    ");
                }
             osys_getkey(_KEY_NULL_,320);
            eVirtualKey = _KEY_VIRTUAL_EV_;
            return ;
            }
        }
        else
            {
                j=j+1;
                olcm_dispprintf(3,2,"            ");
                olcm_dispprintf(0,4,"����Ŵ������䣡");
                if (j<3)
                    goto getkeydel;
                else
                olcm_dispprintf(0,4,"    �������    ");
                osys_getkey(_KEY_NULL_,320);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return ;
            }
        }
          osys_getkey(_KEY_NULL_,320);
          eVirtualKey = _KEY_VIRTUAL_EV_;
  }

//time:14-03-24 rengang
void oset_sys_ma1(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1 ��������");
    olcm_dispprintf(0,2,"2 ʱ������");
    olcm_dispprintf(0,3,"3 ��������");
    olcm_dispprintf(0,4,"4 ��������");
    olcm_dispprintf(7,4,"��");
}
void oset_sys_ma2(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"5 ����Ԥ��");
    olcm_dispprintf(0,2,"6 ǹ������");
    olcm_dispprintf(0,3,"7 �ָ���������");
    olcm_dispprintf(0,4,"8 ����ϵͳ��¼");
    olcm_dispprintf(7,4,"��");
}
void oset_sys_ma3(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"9 ����������");
    olcm_dispprintf(0,2,"0 վ��");
    olcm_dispprintf(0,3,". �з��ӳ�");
    olcm_dispprintf(0,4,"S ���Ҳ������");
    olcm_dispprintf(7,4,"��");
}
void osys_set_ui_switch(void)
{
    switch( _ui_sys_set_id )
    {
        case 1:
            oset_sys_ma1();
            break;
        case 2:
            oset_sys_ma2();
             break;
         case 3:
            oset_sys_ma3();
             break;
        default:
            break;
    }
}
void oset_precool_ma1(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.Ԥ������");
    olcm_dispprintf(0,2,"2.Ԥ���¶�");
    olcm_dispprintf(0,3,"3.�ܶ�����");
    olcm_dispprintf(0,4,"4.�¶Ȳ���"); //150906
    olcm_dispprintf(7,4,"��");
}
void oset_precool_ma2(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"5.Ԥ�䳬ʱ");
    olcm_dispprintf(0,2,"6.�����ȴ�");
    olcm_dispprintf(0,3,"7.Сѭ���ɹ��ȴ�");    //Mengfr 20161111
    olcm_dispprintf(0,4,"8.��ѭ���ɹ��ȴ�");    //Mengfr 20161111
    olcm_dispprintf(7,4,"��");
}

void oprecool_set_ui_switch(void)
{
    switch( _ui_paras_set_id )
    {
        case 1:
            oset_precool_ma1();
            break;
        case 2:
            oset_precool_ma2();
            break;
        default:
            break;
    }
}
void oprecool_cs_ui_switch(void)
{
    switch( _ui_cs_set_id )
    {
        case 1:
            oset_Ls_set_ma();
            break;
        case 2:
            oset_Ls_set_ma2();
            break;
        default:
            break;
    }
}
void oset_pricex_ma1(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.����һ");
    olcm_dispprintf(0,2,"2.���۶�");
    olcm_dispprintf(0,3,"3.������");
    olcm_dispprintf(0,4,"4.������");
    olcm_dispprintf(7,4,"��");
}
void oset_pricex_ma2(void)
{
    olcd_clearsCreen();
     olcm_dispprintf(0,1,"5.������");
    olcm_dispprintf(0,2,"6.������");
    olcm_dispprintf(0,3,"7.������");
    olcm_dispprintf(0,4,"8.���۰�");
    olcm_dispprintf(7,4,"��");
}
void oset_pricex_ma3(void)
{
    olcd_clearsCreen();
     olcm_dispprintf(0,1,"9.���۾�");
    olcm_dispprintf(0,2,"0.����ʮ");
  //  olcm_dispprintf(0,3,"3.������");
  //  olcm_dispprintf(0,4,"4.������");
    olcm_dispprintf(7,4,"��");
}
void opricex_set_ui_switch(void)
{
    switch( _ui_pricex_set_id )
    {
        case 1:
            oset_pricex_ma1();
            break;
        case 2:
            oset_pricex_ma2();
            break;
        case 3:
            oset_pricex_ma3();
            break;
        default:
            break;
    }
}
void oset_tj_ma(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.ͣ������");
    olcm_dispprintf(0,2,"2.ͣ��ѹ��");
   // olcm_dispprintf(0,3,"3.��С������");
   // olcm_dispprintf(0,4,"4.��С�������");
}
//��С������  time:2014-3-18  rengang
void oset_tj_minif(void)
{
       UINT8 len, vkey = 0;
       float fEndr = 0,fEndm = 0;
       INT8  str[20] = {0};
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ��С������");
       olcm_dispprintf(0,2,"��ǰ:%.02f kg",(float)cur_sysparas.min_Gas);
       olcm_dispprintf(0,3,"���룺");
       cursor_x = 3;
       cursor_y = 3;
       if(cur_sysparas.p_Price<=0)
       {
                olcm_dispprintf(0,4,"    ���۴���");
                osys_getkey(_KEY_NULL_,320);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return;
       }
       vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
       if( vkey == _KEY_OK_EV_ && len>0)
        {

            fEndr = (float)atof(str);
            fEndm=fEndr*cur_sysparas.p_Price;
            if((4 == o24lcxxx_write_bytes(_SYSPARAS_EEP_ADDR+offsetof(struct _def_SysParas,min_Gas),(UINT8*)&fEndr,4))\
                &&(4 == o24lcxxx_write_bytes(_SYSPARAS_EEP_ADDR+offsetof(struct _def_SysParas,min_money),(UINT8*)&fEndm,4)))
              {

                cur_sysparas.min_Gas = fEndr;
                cur_sysparas.min_money = fEndm;
                olcm_dispprintf(0,4,"    ���óɹ�    ");
                osys_getkey(_KEY_NULL_,320);
              }
         }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
//��С�������  time:2014-3-18  rengang
void oset_tj_minim(void)
{
   UINT8 len, vkey = 0;
   float fEndr = 0,fEndm = 0;
   INT8  str[20] = {0};
   olcd_clearsCreen();
   olcm_dispprintf(0,1,"  ��С���������");
   olcm_dispprintf(0,2,"��ǰ:%.02f ",(float)cur_sysparas.min_money);
   olcm_dispprintf(6,2,"Ԫ");
   olcm_dispprintf(0,3,"���룺");
   if(cur_sysparas.p_Price<=0)
       {
                olcm_dispprintf(0,4,"    ���۴���");
                osys_getkey(_KEY_NULL_,320);
                eVirtualKey = _KEY_VIRTUAL_EV_;
                return;
       }
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {

        fEndr = (float)atof(str);
        fEndm=fEndr/cur_sysparas.p_Price;
        if((4 == o24lcxxx_write_bytes(_SYSPARAS_EEP_ADDR+offsetof(struct _def_SysParas,min_Gas),(UINT8*)&fEndr,4))\
                &&(4 == o24lcxxx_write_bytes(_SYSPARAS_EEP_ADDR+offsetof(struct _def_SysParas,min_money),(UINT8*)&fEndm,4)))
        {
            cur_sysparas.min_money = fEndr;
            cur_sysparas.min_Gas = fEndm;
            olcm_dispprintf(0,4,"    ���óɹ�    ");
            osys_getkey(_KEY_NULL_,320);
        }
   }
   eVirtualKey = _KEY_VIRTUAL_EV_;
}
void oset_Ls_set_ma(void)
{
     olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"    ��    ��");
   olcm_dispprintf(0,1,"1.ͣ������  ");
   olcm_dispprintf(0,2,"2.��������");
   olcm_dispprintf(0,3,"3.������ʱ�ж�ֵ");
   olcm_dispprintf(0,4,"4.��ͣʱ������");//rg170605ֹͣ/ ��ͣ
   olcm_dispprintf(7,4,"��");
}
void oset_Ls_set_ma2(void)//rg170712
{
     olcd_clearsCreen();
     olcm_dispprintf(0,1,"5.�����¶�����");
	olcm_dispprintf(0,2,"6.�����¶�����");
	olcm_dispprintf(0,3,"7.��Сʣ����");//rg180118
    #if  _F_ENABLE_	== 0			//rg181210
	olcm_dispprintf(0,4,"8.�ӿ���Сʣ��");//rg181210 
	#endif
	#if  _F_ENABLE_				//rg170809 ��5����ʱ����
	olcm_dispprintf(0,4,"8.����ʱ����");//rg170809 ��5����ʱ����
	#endif
	olcm_dispprintf(7,4,"��");
}
void oset_Pressure_ma(void)
{
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ѹ    ��");
 //   olcm_dispprintf(0,2,"1.���");
 //   olcm_dispprintf(0,3,"2.ѹ��ϵ��");
 //   olcm_dispprintf(0,4,"3.ͣ��ѹ��");
   olcm_dispprintf(0,2,"1.���  2.ϵ��");
   olcm_dispprintf(0,3,"3.ͣ��ѹ��");
   olcm_dispprintf(0,4,"4.�ο���ѹ     "); //Mengfr 20150717
}
void oset_syschk_ma1(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.�̵���");
    olcm_dispprintf(0,2,"2.������");
    olcm_dispprintf(0,3,"3.ѹ������");
    olcm_dispprintf(0,3,"4.��ӡ����");
    olcm_dispprintf(7,4,"��");
}
void oset_syschk_ma2(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"5.CPU������");
    olcm_dispprintf(0,2,"6.��ʾ����");
    olcm_dispprintf(0,3,"7.��������");
    olcm_dispprintf(0,3,"8.�洢����");
    olcm_dispprintf(7,4,"��");
}
void oset_syschk_ma3(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"9.ͨѶ����");
    olcm_dispprintf(0,2,"0.ʱ�Ӳ���");
    olcm_dispprintf(7,4,"��");
}
void osyschk_set_ui_switch(void)
{
    switch( _ui_syschk_set_id )
    {
        case 1:
            oset_syschk_ma1();
            break;
        case 2:
            oset_syschk_ma2();
            break;
        case 3:
            oset_syschk_ma3();
            break;
        default:
            break;
    }
}
//��ӡ����  time:2014-3-13  rengang
void oset_sysset_power(void)
{
	olcd_clearsCreen();
	olcm_dispprintf(0, 1, "1.��ӡ    2.�ۿ�");
	olcm_dispprintf(0, 2, "3.���鿨  4.����");
	olcm_dispprintf(0, 3, "5.���޿�  6.����");
//	olcm_dispprintf(0, 4, "6.������ӡ����  ");
	olcm_dispprintf(0, 4, "7.����    8.����");//rg190517
}

void in_xlh(void)//rg160726
{
UINT8 len, vkey = 0;
	UINT8 str[8]= {0};
	UINT8 ke[2] = {0};
    UINT8 qq[2] = {0};
	UINT32 qx_min;
	UINT8 qxset;
	UINT8 qxco;
	float sq, sh;
	UINT8 shift_op_time[6];
	UINT8 psw1, psw2, psw5, psw6, psw3, psw4;
	ortcc_read_time(shift_op_time);
	psw1 = (UINT8) ((90 - shift_op_time[1]) / 10) + 0x30;
	psw2 = (UINT8) ((90 - shift_op_time[1]) % 10) + 0x30;
	psw3 = (UINT8) ((80 - shift_op_time[2]) / 10) + 0x30;
	psw4 = (UINT8) ((80 - shift_op_time[2]) % 10) + 0x30;
	psw5 = (UINT8) ((70 - shift_op_time[3]) / 10) + 0x30;
	psw6 = (UINT8) ((70 - shift_op_time[3]) % 10) + 0x30;
	INT8 passbuf[6] = {psw1, psw2, psw3, psw4, psw5, psw6};
	 qxset = o24lcxxx_read(qxset_addr);//rg160726
		if(qxset != 0xaa )//rg160726
		{
		olcd_clearsCreen();
		olcm_dispprintf(1, 2, "δ��������");
		olcm_dispprintf(1, 3, "���˳�");
		osys_getkey(_KEY_NULL_, 300);
		eVirtualKey = _KEY_VIRTUAL_EV_;	
		return;
		}
	while (1) {
		olcd_clearsCreen();
		olcm_dispprintf(0, 1, "  �������к�");  

		olcm_dispprintf(0, 2, "������(8λ):");
		cursor_x = 2;
		cursor_y = 3;
		vkey = okeyinput_getstr(str, &len, 8, FALSE, FALSE);
		if (vkey == _KEY_OK_EV_ && len > 0) {
			if (len >= 8) {
				if ((str[0] == passbuf[0]) && (str[1] == passbuf[1])&&(str[2] == passbuf[2])&&(str[3] == passbuf[3])&&(str[4] == passbuf[4])&&(str[5] == passbuf[5])) {
					if ((str[6] == 0x30)&&(str[7] == 0x30)) {
						QX_OVER = 0;
						QX_RECORD = 0x0FFFFFFFF;
						if (1 == Save_Qx_Runtime(QX_RECORD)) {
							qxco=(UINT8)atoi(&str[6]);
							o24lcxxx_write_bytes(qxsz_yue_addr,(UINT8*)&qxco,1 ) ;
							qxset = 0x0;
							if(1 == Save_QxSet_Bit(qxset))
							olcm_dispprintf(1, 4, "�����ѽ��");
							else
							olcm_dispprintf(1, 4, "д��ʧ��");
							
						} else {
							olcm_dispprintf(1, 4, "����ʧ��");

						}
						osys_getkey(_KEY_NULL_, 1000);
						eVirtualKey = _KEY_VIRTUAL_EV_;
						break;
					} else 
                        if((str[6] > 0x30)||(str[7] > 0x30)){
                            memcpy(qq,&str[6],2);
						QX_OVER = 0;
						sq = (float) atof(qq);
                        if((sq<1)||(sq>15))
                        {
                          olcm_dispprintf(0, 4, "���볬�ޣ�������");
                        osys_getkey(_KEY_NULL_, 200);
                        eVirtualKey = _KEY_VIRTUAL_EV_;
                        break;		  
                        }
						sh = sq  *30* 24 * 12;  //  ����ӵĸ���
						qx_min = (UINT32) (sh);
						QX_RECORD = qx_min;
						if (1 == Save_Qx_Runtime(QX_RECORD))
						{
							qxco=(UINT8)atoi(&str[6]);
							o24lcxxx_write_bytes(qxsz_yue_addr,(UINT8*)&qxco,1 ) ;
							qxset = 0xaa;
							if(1 == Save_QxSet_Bit(qxset))
							olcm_dispprintf(1, 4, "���óɹ�");
							else
							olcm_dispprintf(0, 4, "д��ʧ��");
					
							eVirtualKey = _KEY_VIRTUAL_EV_;
							osys_getkey(_KEY_NULL_, 500);
							break;
						} else {
							olcm_dispprintf(1, 4, "����ʧ��");
							osys_getkey(_KEY_NULL_, 90);
							eVirtualKey = _KEY_VIRTUAL_EV_;
							break;
						}
					}
					else
					{
					olcm_dispprintf(0, 4, "�������������");
					osys_getkey(_KEY_NULL_, 200);
					eVirtualKey = _KEY_VIRTUAL_EV_;
					break;		
					}
				}
				else
				{
				olcm_dispprintf(0, 4, "�������������");
				osys_getkey(_KEY_NULL_, 200);
				eVirtualKey = _KEY_VIRTUAL_EV_;
				break;	
				}
			}
			else
			{
				olcm_dispprintf(0, 4, "�������������");
				osys_getkey(_KEY_NULL_, 200);
				eVirtualKey = _KEY_VIRTUAL_EV_;
				break;		
			}
		}
		if (vkey == _KEY_EXIT_EV_) {
			eVirtualKey = _KEY_VIRTUAL_EV_;
			return;
		}
	}
}
void oset_zkset(void)//�ۿۿ���
{
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
//     if(ZK_POWER!=1) ZK_POWER = 0; //ǿ�Ʒ��㼴1
       UINT8 qyty,ljkg,zkkg;
    zkkg = o24lcxxx_read(zk_power_addr);
       if(zkkg!=0) zkkg = 1; //ǿ�Ʒ��㼴1
    while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  �ۿ�����");
    if(zkkg>=1)
    olcm_dispprintf(0,2,"��ǰ����ֹ�ۿ�");
    if(zkkg==0)
    olcm_dispprintf(0,2,"��ǰ�������ۿ�");
//       olcm_dispprintf(0,2,"��ǰ��%d",zkkg);
       olcm_dispprintf(0,3,"����:");
       olcm_dispprintf(2,4," 0���� 1��ֹ");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,1,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
          if(str[0] < '2')
          {
              ZK_POWER = (UINT8)atoi(str);
                          if(ZK_POWER>=1)
              olcm_dispprintf(0,2,"��ǰ����ֹ�ۿ�");
            if(ZK_POWER==0)
                olcm_dispprintf(0,2,"��ǰ�������ۿ�");
              if ( 1 != o24lcxxx_write_bytes(zk_power_addr,(UINT8*)&ZK_POWER,1 ) )
              {
                           olcm_dispprintf(0,4,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
              }
              else
              {
                olcm_dispprintf(4,3,"���óɹ�");
                osys_getkey(_KEY_NULL_,320);
              }
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
          }
        }
        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }
 }
void oset_hqset(void)//��������ӡ���� rg180131
{
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
//     if(ZK_POWER!=1) ZK_POWER = 0; //ǿ�Ʒ��㼴1
       UINT8 qyty,ljkg,zkkg;
    zkkg = o24lcxxx_read(hqset_addr);
       if(zkkg!=0) zkkg = 1; //ǿ�Ʒ��㼴1
    while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ������ӡ����");
    if(zkkg>=1)
    olcm_dispprintf(0,2,"��ǰ����ֹ��ӡ");
    if(zkkg==0)
    olcm_dispprintf(0,2,"��ǰ�������ӡ");
//       olcm_dispprintf(0,2,"��ǰ��%d",zkkg);
       olcm_dispprintf(0,3,"����:");
       olcm_dispprintf(2,4," 0���� 1��ֹ");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,1,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
          if(str[0] < '2')
          {
              HQ_PRINT = (UINT8)atoi(str);
                          if(HQ_PRINT>=1)
              olcm_dispprintf(0,2,"��ǰ����ֹ��ӡ");
            if(HQ_PRINT==0)
                olcm_dispprintf(0,2,"��ǰ�������ӡ");
              if ( 1 != o24lcxxx_write_bytes(hqset_addr,(UINT8*)&HQ_PRINT,1 ) )
              {
                           olcm_dispprintf(0,4,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
              }
              else
              {
                olcm_dispprintf(4,3,"���óɹ�");
                osys_getkey(_KEY_NULL_,320);
              }
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
          }
        }
        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }
 }
void oset_mini_set(void)//��С�������  rg180118
{
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
       UINT8 inp,zkkg,wbu;
    zkkg = o24lcxxx_read(minimoney_addr);
    if((zkkg!=0x98)&&(zkkg!=0x99)&&(zkkg!=0x9a))
	zkkg=0x99;    
    while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ��Сʣ����  ");
          
    if(zkkg==0x98)
    olcm_dispprintf(0,2,"��ǰ��%d Ԫ",Mini_Money1);
       else if(zkkg==0x99)
    olcm_dispprintf(0,2,"��ǰ��%dԪ",Mini_Money2);
   else if(zkkg==0x9a)
    olcm_dispprintf(0,2,"��ǰ��%dԪ",Mini_Money3);
       else 
	 olcm_dispprintf(0,2,"��ǰ��%dԪ",Mini_Money2);    
//       olcm_dispprintf(0,2,"��ǰ��%d",zkkg);
       olcm_dispprintf(0,3,"����:");
       olcm_dispprintf(1,4,"0-%d 1-%d 2-%d",Mini_Money1,Mini_Money2,Mini_Money3);
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,1,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
          if(str[0] < '3')
          {
           //   Mini_FD 
		      inp= (UINT8)atoi(str);
                          if(inp==0)
			  {
				olcm_dispprintf(0,2,"��ǰ��%d Ԫ ",Mini_Money1);
				Mini_FD = Mini_Money1;
				wbu=0x98;
			    }
			  else if(inp==1)
			  {
				olcm_dispprintf(0,2,"��ǰ��%dԪ",Mini_Money2);
				Mini_FD = Mini_Money2;
				wbu=0x99;
			    }
		      else if(inp==2)
			  {
				olcm_dispprintf(0,2,"��ǰ��%dԪ",Mini_Money3);
				Mini_FD = Mini_Money3;
				wbu=0x9a;
			    }
		      else
			  {
				olcm_dispprintf(0,2,"��ǰ��%dԪ",Mini_Money2);
				Mini_FD = Mini_Money2;
				wbu=0x99;
			    }
		      
              if ( 1 != o24lcxxx_write_bytes(minimoney_addr,(UINT8*)&wbu,1 ) )
              {
                           olcm_dispprintf(0,4,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
              }
              else
              {
                olcm_dispprintf(4,3,"���óɹ�");
                osys_getkey(_KEY_NULL_,320);
              }
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
          }
        }
        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }
 }
void oset_gassset(void)//���鿨��������
{
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
//     if(ZK_POWER!=1) ZK_POWER = 0; //ǿ�Ʒ��㼴1
       UINT8 qyty,ljkg,zkkg;
    zkkg = o24lcxxx_read(gass_class_addr);
       if(zkkg!=1) zkkg = 0; //ǿ�Ʒ�1��0
    while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ���鿨��������");
    if(zkkg>=1)
    olcm_dispprintf(0,2,"��ǰ����ֹ����");
    if(zkkg==0)
    olcm_dispprintf(0,2,"��ǰ���������");
//       olcm_dispprintf(0,2,"��ǰ��%d",zkkg);
       olcm_dispprintf(0,3,"����:");
       olcm_dispprintf(2,4," 0���� 1��ֹ");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,1,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
          if(str[0] < '2')
          {
              gass_class = (UINT8)atoi(str);
                          if(gass_class>=1)
              olcm_dispprintf(0,2,"��ǰ����ֹ����");
            if(gass_class==0)
                olcm_dispprintf(0,2,"��ǰ���������");
              if ( 1 != o24lcxxx_write_bytes(gass_class_addr,(UINT8*)&gass_class,1 ) )
              {
                           olcm_dispprintf(0,4,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
              }
              else
              {
                olcm_dispprintf(4,3,"���óɹ�");
                osys_getkey(_KEY_NULL_,320);
              }
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
          }
        }
        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }
 }
void oset_sysset_print(void)//rg170606��ӡ������
{

    UINT8 rdkey,num=0;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ��ӡ����");
    num = o24lcxxx_read(_PRINT_SW_ADDR);
    if(num>=1)
    olcm_dispprintf(0,2,"��ǰ��������ӡ");
    olcm_dispprintf(0,4,"���л����޸�����");
    if(num==0)
    {  
    olcm_dispprintf(0,2,"��ǰ���رմ�ӡ");
    olcm_dispprintf(0,4,"���л����޸�����");
    }
    while(1)
    {
        rdkey = ostatemachine_getkey();
        b_keyv = FALSE;
        if( rdkey == _KEY_SW_EV_)
         {
            num++;
            if(num>=2)
              num=0;
            if(num==1)
            { 
              olcm_dispprintf(0,2,"��ǰ��������ӡ");
                 }
            if(num==0)
            {
              olcm_dispprintf(0,2,"��ǰ���رմ�ӡ");}
        }
        if( rdkey == _KEY_ENTER_EV_)
        {
          if ( 1 == o24lcxxx_write_bytes(_PRINT_SW_ADDR,(UINT8*)&num,1 ) )
          {
                PRINT_SET = num;
               // cur_sysparas.p_Prset = num;
           olcm_dispprintf(0,4,"    ���óɹ�    ");
                osys_getkey(_KEY_NULL_,320);
                break;
            }
        }
         if( rdkey == _KEY_EXIT_EV_)
             break;
       
    }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
/*
 void oset_sysset_print(void)
{

    UINT8 rdkey,num=0;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ��ӡ����");
     num = o24lcxxx_read(_PRINT_SW_ADDR);
    if(num>=1)
    olcm_dispprintf(0,2,"��ǰ���Զ���ӡ");
    if(num==0)
    olcm_dispprintf(0,2,"��ǰ���ֶ���ӡ");
    olcm_dispprintf(0,4,"���л����޸�����");
    while(1)
    {
        rdkey = ostatemachine_getkey();
        b_keyv = FALSE;
        if( rdkey == _KEY_SW_EV_)
         {
            num++;
            if(num>=2)
              num=0;
            if(num==1)
              olcm_dispprintf(0,2,"��ǰ���Զ���ӡ");
            if(num==0)
                olcm_dispprintf(0,2,"��ǰ���ֶ���ӡ");
        }
        if( rdkey == _KEY_ENTER_EV_)
        {
          if ( 1 == o24lcxxx_write_bytes(_PRINT_SW_ADDR,(UINT8*)&num,1 ) )
          {
                PRINT_SET = num;
               // cur_sysparas.p_Prset = num;
                olcm_dispprintf(0,4,"    ���óɹ�    ");
                osys_getkey(_KEY_NULL_,320);
                break;
            }
        }
         if( rdkey == _KEY_EXIT_EV_)
             break;
       
    }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
*/
void oset_sysset_aerad(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"����");
    osys_getkey(_KEY_NULL_,300);
}
UINT8 waitexit(void)
{
      while(1)
    {
        keyv = ostatemachine_getkey();
        b_keyv = FALSE;
        if(_KEY_ENTER_EV_ == keyv)
        {
            return _KEY_ENTER_EV_;
        }
        if(_KEY_EXIT_EV_ == keyv)
        {
            return _KEY_EXIT_EV_;
        }
    }
 }
/*-----------------------------------���ѹ����������-----------------------------*/
//ѹ������  time:2014-3-13  rengang
void oset_sysset_prezero(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Menfr 20161111 
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;
  }
  //////////////
   olcm_dispprintf(0,1,"  ���ѹ������");
   olcm_dispprintf(0,2,"��ǰ:%.04f",systempara.zeroyl);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_zeropressure(fEndr,len))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }

}
//��ǰѹ������  time:2014-3-13  rengang
void oset_sysset_precur(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111 
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
   olcm_dispprintf(0,1,"  ѹ��ϵ������");
   olcm_dispprintf(0,2,"��ǰ:%.03f",systempara.ylxs);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_pressurejzxs(fEndr,len))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
  if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
//��ȫѹ������  time:2014-3-13  rengang
void oset_sysset_safetypre(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara))     //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
   olcm_dispprintf(0,1,"    ��ȫѹ������");
   olcm_dispprintf(0,2,"��ǰ:%.01f MPa",systempara.aqyl);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_pressure(fEndr,len))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
	AddSOE(Para_tjyl);//rg180613
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
//�ο���ѹ����  //Mengfr 20150717
void oset_sysset_ReferVoltage(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//  //if(TRUE != qty_get_sys(qid,temp,price,Density ,gain,ls ,yl,aqyl,Density_up ,Density_do,ylys))
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara))    //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
//    if(cn_en==0)
//    {
        olcm_dispprintf(0,1,"  �ο���ѹ����");
        olcm_dispprintf(0,2,"��ǰ:%.03f V ",systempara.RefVol);
        olcm_dispprintf(0,3,"����:");
        olcm_dispprintf(0,4,"��Χ:2--4V");
//    }
//    else
//    {
//        olcm_dispprintf(0,1,"Refer Voltage.");
//        olcm_dispprintf(0,2,"Cur:%.03f V",RefVol);
//        olcm_dispprintf(0,3,"Input:");
//        olcm_dispprintf(0,4,"range:2---4V");
//    }
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,5,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);
        if(fEndr < 2.0 || fEndr > 4.0)  //ֵ����
        {
            olcm_dispprintf(0,4,"    ���ó���    ");
            osys_getkey(_KEY_NULL_,320);
            return;
        }

        if( TRUE!= Set_ReferVoltage(fEndr,len))//
        {
            //ͨ���쳣
//           if(cn_en==0)
           olcm_dispprintf(0,4,"    ����ʧ��    ");
//         else
//            olcm_dispprintf(0,4,"Setup Failure");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }

//if(cn_en==0)
           olcm_dispprintf(0,4,"    ���óɹ�    ");
 //        else
 //           olcm_dispprintf(0,4,"Successful");

           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }

}
//�ܶ���������  time:2014-3-21  rengang
void oset_Density_up(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara)) //Mengfr 20161111 
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
      olcm_dispprintf(0,1,"    �ܶ���������");
   olcm_dispprintf(0,2,"��ǰ: %.02f g/cm3",systempara.Density_up);
   olcm_dispprintf(0,3,"���룺");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_Density_up(fEndr,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
	AddSOE(Para_md);//rg180613
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
//Ӳ���汾  ��  �ܶ���������  time:2014-3-21  rengang
void oset_Density_down(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();
      ///////////// /////////////

//    UINT8 qid;float temp;float price;float gas_delay ;
//    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
//   float glbh;
//    float lspd;
//    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
   if(TRUE != qty_get_sys(&systempara))     //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  //////////////
      olcm_dispprintf(0,1,"  Ӳ���汾����");
   olcm_dispprintf(0,2,"��ǰ: %.02f",systempara.Density_do);
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"A4�棺������4.4");  //
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);

        if( TRUE!= Set_Density_down(fEndr,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
        ///////////���̰�Ӳ������///////////////////
        if((fEndr>4.3)&&(fEndr<4.5))
        {  HARDKEYCERA4 = 1; 
             if(HARDKEYCERA4 == 1)
              {
                  Is_debuggas_Read =0; //��������Լ���   //150906
               }
        
        
        }
        else
        {  HARDKEYCERA4 = 0;  }    
         if ( 1 == o24lcxxx_write_bytes(_HARD_VER_ADDR,(UINT8*)&HARDKEYCERA4,1 ) )
               {
                 
                olcm_dispprintf(0,4,"    ���óɹ�    ");
                }
              else
                {
                    olcm_dispprintf(4,3,"����ʧ��");
                }
        ////////////////////////////
        
        
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}

void omodule_clock_test(void)
{
    UINT8 rdkey;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"clock");
    osys_getkey(_KEY_NULL_,320);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}
//���Բ˵���ͨѶ��������ܴ����  time:2014-3-13  rengang
void omodule_tx_test(void)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"TX");
    osys_getkey(_KEY_NULL_,320);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}

//ȡ�ð�����Ϣ������cur_class_info�� time:2014-3-13  rengang
void oset_getclassxx()
{
        UINT8 n;
        UINT16 addr;
        addr=_SHIFT_SYSPARAS_EEP_ADDR_END;
        for( n = 0; n < 10 ; n++ )
        {
            memset((UINT8*)&cur_class_info[n].class_num,0x00,CLASSLEN);
            o24lcxxx_read_bytes_ex(addr, (UINT8*)&cur_class_info[n].class_num, CLASSLEN);
            addr +=CLASSSIZE;
        }
}
void oset_tmpeAdd(void)
{

  UINT8 len,waitim, vkey = 0;

   float ylti;
   INT8  str[20] = {0};
   olcd_clearsCreen();
    waitim = o24lcxxx_read(_TMP_ADD_ADDR);
    olcm_dispprintf(0,1,"  �²�����");
   olcm_dispprintf(0,2,"��ǰ:%d",waitim);
   olcm_dispprintf(0,3,"����:");
   olcm_dispprintf(0,4,"��Ч��Χ:0-100");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,3,FALSE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        waitim = (UINT8)atoi(str);
        if(waitim >=100) waitim = 100;

          if ( 1 == o24lcxxx_write_bytes(_TMP_ADD_ADDR,(UINT8*)&waitim,1 ) )
               {
                  temp_add_vol = waitim;
                 olcm_dispprintf(4,3,"���óɹ�");
                 osys_getkey(_KEY_NULL_,320);
                 eVirtualKey = _KEY_VIRTUAL_EV_;
                }
         else
                {
                    olcm_dispprintf(4,3,"����ʧ��");
                     osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_VIRTUAL_EV_;
                }

   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
//�����ȴ�ʱ������  time:2014-3-13  rengang
void oset_arcewait(void)
{

  UINT8 len,waitim, vkey = 0;
 
   float ylti;
   INT8  str[20] = {0};
   olcd_clearsCreen();
    waitim = o24lcxxx_read(_WAIT_TIM_ADDR);
    olcm_dispprintf(0,1,"  �����ȴ�ʱ��");
   olcm_dispprintf(0,2,"��ǰ:%d min",waitim);
   olcm_dispprintf(0,3,"����:");
   olcm_dispprintf(0,4,"��Ч��Χ:1-240");
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,3,FALSE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        waitim = (UINT8)atoi(str);
        if(waitim >=240) waitim = 240;

          if ( 1 == o24lcxxx_write_bytes(_WAIT_TIM_ADDR,(UINT8*)&waitim,1 ) )
               {
                  CANGASMINUTE = waitim;
                 olcm_dispprintf(4,3,"���óɹ�");
                 osys_getkey(_KEY_NULL_,320);
                 eVirtualKey = _KEY_VIRTUAL_EV_;
                }
         else
                {
                    olcm_dispprintf(4,3,"����ʧ��");
                     osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_VIRTUAL_EV_;
                }
     
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}
//Mengfr 20161111
//Сѭ���ɹ����ӳ�
void oset_MinorCycleSucced_delay(void)
{
    UINT8 len, vkey = 0;
    float fEndr = 0;
    INT8 str[20] = {0};
    SYSTEMPARA systempara;           
    olcd_clearsCreen();
    ///////////// /////////////    
    if (TRUE != qty_get_sys(&systempara))
    {
        //ͨ���쳣
        SOEACTION1(PRO422_ERR, eCurRunState);
        return;
    }
    //////////////
    olcm_dispprintf(0, 1, "  Сѭ���ɹ��ȴ�");
    olcm_dispprintf(0, 2, "��ǰ:%.02f S",systempara.MinorCycleDelay);
    olcm_dispprintf(0, 3, "����:");

    vkey = okeyinput_getstr(str, &len, 4, TRUE, FALSE);
    if (vkey == _KEY_OK_EV_ && len > 0) 
    {
        fEndr = (float) atof(str);

        if (TRUE != Set_MinCycleDelay(fEndr, 4))//
        {
            //ͨ���쳣
            olcm_dispprintf(0, 4, "    ����ʧ��    ");
            osys_getkey(_KEY_NULL_, 320);
            SOEACTION1(PRO422_ERR, eCurRunState);
            return;
        }
        olcm_dispprintf(0, 4, "    ���óɹ�    ");
        osys_getkey(_KEY_NULL_, 320);
        eVirtualKey = _KEY_VIRTUAL_EV_;
    }
    if (vkey == _KEY_EXIT_EV_) 
    {
        eVirtualKey = _KEY_VIRTUAL_EV_;
    }
}

//��ѭ���ɹ����ӳ�  //Mengfr 20161111
void oset_MajorCycleSucced_delay(void)
{
    UINT8 len, vkey = 0;
    float fEndr = 0;
    INT8 str[20] = {0};
    SYSTEMPARA systempara;
            
    olcd_clearsCreen();
    ///////////// /////////////    
    if (TRUE != qty_get_sys(&systempara))
    {
        //ͨ���쳣
        SOEACTION1(PRO422_ERR, eCurRunState);
        return;
    }
    //////////////
    olcm_dispprintf(0, 1, "  ��ѭ���ɹ��ȴ�");
    olcm_dispprintf(0, 2, "��ǰ:%.02f S",systempara.MajorCycleDelay);
    olcm_dispprintf(0, 3, "����:");

    vkey = okeyinput_getstr(str, &len, 4, TRUE, FALSE);
    if (vkey == _KEY_OK_EV_ && len > 0) 
    {
        fEndr = (float) atof(str);

        if (TRUE != Set_MajCycleDelay(fEndr, 4))//
        {
            //ͨ���쳣
            olcm_dispprintf(0, 4, "    ����ʧ��    ");
            osys_getkey(_KEY_NULL_, 320);
            SOEACTION1(PRO422_ERR, eCurRunState);
            return;
        }
        olcm_dispprintf(0, 4, "    ���óɹ�    ");
        osys_getkey(_KEY_NULL_, 320);
        eVirtualKey = _KEY_VIRTUAL_EV_;
    }
    if (vkey == _KEY_EXIT_EV_) 
    {
        eVirtualKey = _KEY_VIRTUAL_EV_;
    }
}

//Ԥ����ʱʱ������  time:2014-3-22  rengang
void oset_precool_delay(void)
{
    UINT8 len, vkey = 0;
   float fEndr = 0;
   float ylti;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; //Mengfr 20161111
   olcd_clearsCreen();

  if(TRUE != qty_get_sys(&systempara))  //Mengfr 20161111
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
    ylti = systempara.ylys/60;
  //////////////
     olcm_dispprintf(0,1,"  Ԥ�䳬ʱʱ��");
   olcm_dispprintf(0,2,"��ǰ:%.02f min",(float)ylti);
   olcm_dispprintf(0,3,"����:");
olcm_dispprintf(0,4,"��Χ:0-5��      ");//rg170629 
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);
        if(fEndr > 5)  //ֵ����//rg170629 
        {
            olcm_dispprintf(0,4,"    ���ó���    ");//rg170629 
            osys_getkey(_KEY_NULL_,320);//rg170629 
            return;//rg170629 
        }

        if( TRUE!= Set_precool_delay(fEndr,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
}

void oset_relaytime(void)
{    UINT8 stationNo;
     float _relay;
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
   if(TRUE != qty_get_zhanhao((UINT8*)&stationNo,(float*)&_relay,&VER_MasterBoard))
   {
     SOEACTION1(PRO422_ERR,eCurRunState);
     return ;

   }
   if(_relay>5)  _relay = 0.5;
   while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  �з��ӳ�");
       olcm_dispprintf(0,2,"��ǰ��%.03fS",_relay);
       olcm_dispprintf(0,3,"����:");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,5,TRUE,FALSE);
   
       if( vkey == _KEY_OK_EV_ && len>0)
        {

                _relay = (float)atof(str);
                //if(TRUE ==ocompany_compack(6,0x31,_relay,4 ))
                if(TRUE ==ocompany_relay_set(_relay))
                  {
                
                   olcm_dispprintf(2,4,"���óɹ�");
                  }
                else
                {
                     olcm_dispprintf(2,4,"����ʧ��");
                }

             osys_getkey(_KEY_NULL_,320);
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;

        }//end of  vkeyok

        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }//end of while 1

}
void oset_statonno(void)
{    UINT8 stationNo;
     float _relay;
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
   if(TRUE != qty_get_zhanhao((UINT8*)&stationNo,(float*)&_relay,&VER_MasterBoard))
   {
     SOEACTION1(PRO422_ERR,eCurRunState);
     return ;

   }
   if(stationNo>100)  stationNo = 1;
   while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  վ��");
       olcm_dispprintf(0,2,"��ǰ��%d",stationNo);
       olcm_dispprintf(0,3,"����:");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,2,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
        
              stationNo = (UINT8)atoi(str);
              
                if(TRUE == ocompany_zanhao_verify((UINT8*)&stationNo))
                  {
                   Cur_StationNo = stationNo;
                   olcm_dispprintf(2,4,"���óɹ�");
                  }
                else
                {
                     olcm_dispprintf(2,4,"����ʧ��");
                }
  
             osys_getkey(_KEY_NULL_,320);
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
      
        }//end of  vkeyok

        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }//end of while 1

}
//�������� 13-04-12 wangzw
void oset_keysound(void)
{   UINT8 key_sound;
    UINT8 len,vkey = 0;
    INT8  str[2] = {0};
     key_sound = o24lcxxx_read(_BUZZER_SW_ADDR);
     if(key_sound!=1) key_sound = 0; //ǿ�Ʒ��㼴1

   while(1)
   {
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ������");
      // olcm_dispprintf(0,2,"��ǰ��%d",cur_sysparas.p_curflow);
       olcm_dispprintf(0,2,"��ǰ��%d",key_sound);
       olcm_dispprintf(0,3,"ѡ��:");
       olcm_dispprintf(2,4," 1���� 0����");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,1,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
          if(str[0] < '2')
          {
              key_sound = (UINT8)atoi(str);

              if ( 1 == o24lcxxx_write_bytes(_BUZZER_SW_ADDR,(UINT8*)&key_sound,1 ) )
               {
                  cur_keysound = key_sound;
                olcm_dispprintf(4,3,"���óɹ�");
                }
              else
                {
                    olcm_dispprintf(4,3,"����ʧ��");
                }
               osys_getkey(_KEY_NULL_,320);
            eVirtualKey = _KEY_VIRTUAL_EV_;
             break;
          }//end of <'2'


        }//end of  vkeyok

        if(vkey == _KEY_EXIT_EV_)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
          return;
        }
  }//end of while 1

}
//������ˮ������  time:2014-3-13  rengang
void oset_curflow(void)
{
   UINT8 len, vkey = 0;
   UINT32 flowwate = 0;
   UINT8 key;
   INT8  str[20] = {0};
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
      cur_max_recid = get_max_rec_id();//wangqaz
     if(0xFFFF0000 ==cur_max_recid)
      {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           eVirtualKey = _KEY_VIRTUAL_EV_;
           return;
       }
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ������ˮ��");
      // olcm_dispprintf(0,2,"��ǰ��%d",cur_sysparas.p_curflow);
       olcm_dispprintf(0,2,"��ǰ��%d",cur_max_recid);
       olcm_dispprintf(0,3,"����:");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,6,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
              flowwate = (UINT32)atoi(str);
              if(flowwate <= cur_max_recid)                                     // ���Ӷ���ˮ��������Ϣ�뵱ǰ��ˮ�ŵ��ж�    ss190415 
              {
                    olcd_clearsCreen();
                    olcm_dispprintf(0,1,"    ����ʧ��    ");
                    olcm_dispprintf(0,2,"����Ӧ���ڵ�ǰֵ");
                    olcm_dispprintf(0,3,"������洢��Ϣ");
                   // SOEACTION1(PRO422_ERR,eCurRunState);
                    osys_getkey(_KEY_NULL_,430);
                    eVirtualKey = _KEY_1_EV_;
                    return;
              }
              cur_max_recid = flowwate;

            if( TRUE != Set_curflow((UINT8*)&flowwate,4))//
               {
                //ͨ���쳣
               olcm_dispprintf(0,4,"    ����ʧ��    ");
               osys_getkey(_KEY_NULL_,330);
               SOEACTION1(PRO422_ERR,eCurRunState);
               eVirtualKey = _KEY_VIRTUAL_EV_;
               return;
                }
	      AddSOE(Para_lsh);//rg180613
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,330);
           eVirtualKey = _KEY_VIRTUAL_EV_;
        }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
  
}
//time:14-03-17 rengang
void oset_sysdate(void)
{
     UINT8 timestr[6] ;
     UINT8 qxset;
     qxset = o24lcxxx_read(qxset_addr);//rg160726
		if(qxset == 0xaa )//rg160726
		{
		olcd_clearsCreen();
		olcm_dispprintf(1, 2, "����������");
		olcm_dispprintf(1, 3, "�޷��޸�");
		osys_getkey(_KEY_NULL_, 300);
		eVirtualKey = _KEY_VIRTUAL_EV_;	
		return;
		}
     while(1)
     {
        memset(timestr,0,sizeof(timestr));
        if(TRUE == okey_datestr(timestr))
        {
            if( ortcc_set_date((UINT8*)&timestr[0]) == TRUE)
            {
                olcm_dispprintf(0,2,"    ���óɹ�    ");
                break;
            }
            else
            {
                olcm_dispprintf(0,2,"    ����ʧ��    ");
                break;
            }
        }
        break;
     }
     osys_getkey(_KEY_EXIT_EV_, 320);
     eVirtualKey = _KEY_VIRTUAL_EV_;
}
//time 14-03-22 rengang
UINT8 para_sav(UINT8 *pa,float float_q,float float_h)
{
            un_paraup         chk_para;
            un_paraup         cur_paraup;
            int i;
            ortcc_read_time((UINT8*)&cur_paraup.time[0]);
            cur_paraup.para_float_q=float_q;
            cur_paraup.para_float_h=float_h;
            cur_paraup.no[0]=*pa;
            cur_paraup.no[1]=*(pa+1);
            cur_paraup.no[2]=*(pa+2);
            cur_paraup.para_rec_id=cur_max_paraid;
            i=4;
            do
            {
                onand_wtBuff(PARA_NANDFLASH_S_ADDR+(cur_max_paraid-1)*PARA_LENGTH, (UINT8 *)&cur_paraup.para_rec_id, sizeof(struct _def_paraup));
                onand_rdBuff(PARA_NANDFLASH_S_ADDR+(cur_max_paraid-1)*PARA_LENGTH, (UINT8 *)&chk_para.para_rec_id, sizeof(struct _def_paraup));
                i--;
            } while(((cur_paraup.para_rec_id!=chk_para.para_rec_id)||strcmp(cur_paraup.no,chk_para.no)!=0||(cur_paraup.para_float_h!=chk_para.para_float_h)||(cur_paraup.para_float_q!=chk_para.para_float_q))&&(i>=0));
        if(i<0)
        {
         return 2;
         }
            return 1;
}
void oset_clrsav(void)
{
    UINT32 i,addr,k;
    k=0;
    BOOL    state;
    UINT8  m, n = 0;
    UINT8  cnt = 0;
    UINT8  clr[128];// = 0;
    BOOL bok = TRUE;
#if 1
    

    for(i=0;i<1024;i++) //nand flash eraseall
    {
       state=onand_BlockErase(REC_NANDFLASH_S_ADDR+16*1024*i);
       if(state==FALSE)
       {
           k+=1;
           olcm_dispprintf(0,4,"ʧ�� %d  %d", i, k );
           delay_ms(1000);
       }
       else
       olcm_dispprintf(0,4,"OK: %d", i );
    }
#endif
       addr = _REC_SYSINFO_EEP_ADDR;
        memset(clr,0,128);
        for( n = 0; n < _REC_SYSINFO_PAGES_ ; n++ )
        {
            //o24lcxxx_write_bytes(addr, (UINT8*)&cur_sysinfo.g_uid, len);
            for(m=0; m<16; m++)
            {
                cnt = o24lcxxx_write_bytes(addr, (UINT8*)&clr[0], 8);
                if( 8 != cnt)
                {
                        bok = FALSE;
                    olcm_dispprintf(0,4,"ʧ�� %d %d", n, cnt );
                    break;
                }
                addr += 8;
            }
            if(bok == FALSE) break;
        }
        cur_max_recid=0;
}
#if 1
void oset_simrec()
{
       _lcng_rec  cur_rec;
     UINT16 offset_id = 0;
     UINT32 i,addrn;
     UINT32 addr,addre;
     UINT8  buf[40];
      float  maxmoney=0;
     float  c_voluent=0; //��ǰ�ļ�����
     float  c_money=0;   //��ǰ�ļ������
      for(i=0;i<500;i++)
     {
        cur_max_recid=i;
         maxmoney=maxmoney+0.01;
         c_voluent=c_voluent+0.01;
         c_money=c_money+0.01;

         offset_id = cur_max_recid%_REC_SYSINFO_PAGES_;//_SYSINFO_PAGES_;
         addr = (offset_id*_REC_SYSINFO_PAGE_SZIE_) + _REC_SYSINFO_EEP_ADDR;
          memset(cur_rec.rec_cardnum, 0, sizeof(_lcng_rec));
         cur_rec.rec_lcngnum = c_voluent;        //���� 99999.99    ---44
         cur_rec.rec_lcnprice =  3.4;//���� 999.99       ---4
         cur_rec.rec_lcnM = c_money;         //��� 9999999.99``     ---4
         cur_rec.rec_card_preM = 500;     //����ǰIC��� 9999999.99  ---4
         cur_rec.rec_card_endM = 470;     //������IC��� 9999999.99
         cur_rec.rec_card_preg;     //������������ 9999999.99
         cur_rec.rec_card_endg;     //������������ 9999999.99
         cur_rec.rec_sum_start = 1200;    //������ʼǹ�� 999999999.99
         cur_rec.rec_sum_end =  1300;      //��������ǹ�� 999999999.99
         cur_rec.rec_begin_Press;         //������ʼѹ�� 99.99
         cur_rec.rec_end_Press;         //��������ѹ�� 99.99

         o24lcxxx_write_bytes(addr+offsetof(struct def_rec_SysInfo, g_uid ),(UINT8*)&cur_max_recid,4 ); //��ǹ��ˮ��
         addrn = REC_NANDFLASH_S_ADDR+(cur_max_recid)*128;
         onand_wtBuff(REC_NANDFLASH_S_ADDR+(cur_max_recid)*128, cur_rec.rec_cardnum, 128);
         cur_max_recid += 1;
   }
         olcm_dispprintf(0,4,"���");
}
#endif
BOOL Save_QxSet_Bit(UINT8 new_bit)//RG160726
 {    
      UINT8 readtime;
      UINT8 runtime;
      UINT8 K = 10;
      runtime = new_bit;
     while(K)
      {  K--;
         if( 1==o24lcxxx_write_bytes_ex(qxset_addr,(UINT8*)&runtime,1))
          {   delay_ms(100);
              o24lcxxx_read_bytes_ex(qxset_addr, (UINT8*)&readtime, 1);
          
              if(readtime ==runtime)
                {
                return 1;
                }
             delay_ms(10);
          }

     }//end of while
      return 0;
 }
void oset_sysset_wk(void)//rg170531�޿�����
{
    UINT8 rdkey,num=0;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ����������");
    num = o24lcxxx_read(Car_power_addr);
    if(num>=1)
    {
	    olcm_dispprintf(0,2,"��ǰ���п�����");
    olcm_dispprintf(0,4,"���л����޸�����");
	        }
    if(num==0)
    {  
    olcm_dispprintf(0,2,"��ǰ���޿�����");
    olcm_dispprintf(0,4,"���л����޸�����");
    }
    while(1)
    {
        rdkey = ostatemachine_getkey();
        b_keyv = FALSE;
        if( rdkey == _KEY_SW_EV_)
         {
            num++;
            if(num>=2)
              num=0;
            if(num==1)
            { 
              olcm_dispprintf(0,2,"��ǰ���п�����");
                 }
            if(num==0)
            {
              olcm_dispprintf(0,2,"��ǰ���޿�����");
	    }
        }
        if( rdkey == _KEY_ENTER_EV_)
        {
		if ( 1 == o24lcxxx_write_bytes(Car_power_addr,(UINT8*)&num,1 ) )
          {
                WKJQ = num;
                olcm_dispprintf(0,4,"    ���óɹ�    ");
                osys_getkey(_KEY_NULL_,320);
                break;
            }
		if(WKJQ == 0)
		memset(CPH,0x0,10);//rg170619
        }
         if( rdkey == _KEY_EXIT_EV_)
             break;
       
    }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
void oset_zttzset(void)//rg170605ֹͣ/ ��ͣ
{
    UINT8 len,vkey = 0;
    INT8  str[20] = {0};
       UINT8 ce,CE;
       UINT8  zfk;
       float wdcs,fEndr;
       olcd_clearsCreen();
  o24lcxxx_read_bytes_ex(Set_Zttz_Addr, (UINT8 *)&wdcs, 4);

	olcm_dispprintf(0,1,"  ��ͣʱ������  ");
   olcm_dispprintf(0,2,"��ǰ:           ");
   olcm_dispprintf(3,2,"%.02f   ",wdcs);
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"��Χ:0-900��");  //160720//rg170228
   cursor_x = 4;
   cursor_y = 3;
      cxsr: olcm_dispprintf(3,3,"            ");
     vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
	   fEndr = (float)atof(str);
	   if(fEndr > 900) //10.0  //160720//rg206//rg170228
		{
		   olcm_dispprintf(0,4,"��ֵ����, ������");
		   osys_getkey(_KEY_NULL_,200);
		   olcm_dispprintf(0,4,"��Χ:0-900��");//rg170228
		goto cxsr;  
		}       
	   if(4 != o24lcxxx_write_bytes_ex(Set_Zttz_Addr,(UINT8*)&fEndr,4))
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           return;
         }
	   Zttz_Time=fEndr;
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
 }
void oset_zxjqe(void)//rg180130 ��С�������
{
    UINT8 len,vkey = 0;
    INT8  str[20] = {0};
       UINT8 ce,CE;
       UINT8  zfk,zkkg;
       float wdcs,fEndr;
       UINT8 wbu;
       olcd_clearsCreen();
       zkkg = o24lcxxx_read(minimoney_addr);
       if(zkkg==0xA5)
  o24lcxxx_read_bytes_ex(minimoneydat_addr, (UINT8 *)&wdcs, 4);
       else
	wdcs=Mini_Money;       

	olcm_dispprintf(0,1,"  ��Сʣ����  ");
   olcm_dispprintf(0,2,"��ǰ:           ");
   olcm_dispprintf(3,2,"%.02f   ",wdcs);
   olcm_dispprintf(0,3,"���룺");
   olcm_dispprintf(0,4,"��Χ:5-30 Ԫ    ");  //160720//rg170228
   cursor_x = 4;
   cursor_y = 3;
      cxsr: olcm_dispprintf(3,3,"            ");
     vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
	   fEndr = (float)atof(str);
	   if(fEndr < Mini_DO || fEndr > Mini_UP) 
		{
		   olcm_dispprintf(0,4,"��ֵ����, ������");
		   osys_getkey(_KEY_NULL_,200);
		   olcm_dispprintf(0,4,"��Χ:5-30 Ԫ    ");
		goto cxsr;  
		}    
	  if(4 != o24lcxxx_write_bytes_ex(minimoneydat_addr,(UINT8*)&fEndr,4))
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           return;
         }
	   
	   wbu=0xA5;
	   if ( 1 != o24lcxxx_write_bytes(minimoney_addr,(UINT8*)&wbu,1 ) )
              {
                           olcm_dispprintf(0,4,"����ʧ��");
                           osys_getkey(_KEY_NULL_,90);
			   return;
              }
 	   Mini_FD=fEndr;
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
 }
BOOL Select_YorNo(void)
{      UINT8  cou,keyV;
       olcm_dispprintf(0,2,"�¶ȵͣ����عر�");
       olcm_dispprintf(0,3,"��ȷ��--�ر�");
       olcm_dispprintf(0,4,"������--�˳�");
         while(1)
          {
               keyV = osys_getkey_ex(); //
                  b_keyv = FALSE;
                 if(keyV == _KEY_ENTER_EV_)
                {
                  return TRUE;//
                }
               else if(keyV == _KEY_EXIT_EV_)
                 return FALSE;
          }
}
void oset_wdcsset(void)//�¶Ȳ���//rg160824
{
    UINT8 len,vkey = 0;
    INT8  str[20] = {0};
       UINT8 ce,CE;
       UINT8  zfk;
       float wdcs,fEndr;
  o24lcxxx_read_bytes_ex(Set_Wdcs_Addr, (UINT8 *)&wdcs, 4);
 //  olcm_dispprintf(0,1,"    ͣ������    ");
   olcm_dispprintf(0,1,"��ǰ:           ");
   olcm_dispprintf(3,1,"%.02f   ",wdcs);
   olcm_dispprintf(0,2,"���룺");
   olcm_dispprintf(0,3,"��Χ: -30--+10��");  //160720
   olcm_dispprintf(0,4,"ѡ���--�����л�");
   cursor_x = 4;
   cursor_y = 2;
 cxsr: olcm_dispprintf(3,2,"          ");
     vkey = okeyinput_getstr_zf(str,&len ,4,TRUE,FALSE,&zfk);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
	   fEndr = (float)atof(str);
	   if(zfk==0)
	   {
		if(fEndr>10.0) //10.0  //160720//rg206
		{
		   olcm_dispprintf(0,4,"��ֵ����, ������");
		   osys_getkey(_KEY_NULL_,200);
		   olcm_dispprintf(0,4,"ѡ���--�����л�");
		goto cxsr;  
		}       
	   }
	   if(zfk==0x01)
	   {
		if(fEndr>30.0)   //160720
		{
		   olcm_dispprintf(0,4,"��ֵ����, ������");
		   osys_getkey(_KEY_NULL_,200);
		   olcm_dispprintf(0,4,"ѡ���--�����л�");
		goto cxsr;  
		}       
	   }
           if(zfk==1)
        {  fEndr =-fEndr ; 
         }
        //if( TRUE!= Set_glbh(fEndr,4))
	   if(4 != o24lcxxx_write_bytes_ex(Set_Wdcs_Addr,(UINT8*)&fEndr,4))
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
//           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
	   WDKZ=fEndr;
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
 }
void oset_jrset(void)//���ȿ���rg161017  161103
{
	UINT8 len, i, vkey = 0;
	INT8 str[2] = {0};
	UINT8 ce, CE;
	   ce = o24lcxxx_read(jr_power_addr);
	      if(ce>2) ce = 0; //ǿ�Ʒ��㼴1
//	ce = 0;
	while (1) {
		olcd_clearsCreen();
			olcm_dispprintf(0, 1, "    ����      ");
		if (ce == 1) {
				olcm_dispprintf(0, 2, "��ǰ���ֶ���");
		}
		if (ce == 2) {
				olcm_dispprintf(0, 2, "��ǰ���ֶ���");
		}
		if (ce == 0) {
				olcm_dispprintf(0, 2, "��ǰ���Զ�  ");
		}

			olcm_dispprintf(0, 3, "����:");
			olcm_dispprintf(0, 4, " 0�� 1�ֿ� 2�ֹ�");
			cursor_x = 3;
			cursor_y = 3;
		vkey = okeyinput_getstr(str, &len, 1, FALSE, FALSE);
		if (vkey == _KEY_OK_EV_ && len > 0) {
			if (str[0] < '3') {
				CE = (UINT8) atoi(str);
				if (CE == 1) {
					JiaReMoOpen;
					jr_power = 1;
						olcm_dispprintf(0, 2, "��ǰ���ֶ���");
					delay_ms(100);
					i = mPORTGReadBits(BIT_7) >> 7;
					i = i & 0x01;
					if (i == 1) {
						olcm_dispprintf(0, 4, "  ����ģ���쳣  ");
					}
				}
				if (CE == 2) {
					temperature = DS18B20_Get_Temp();
				
					if(temperature <= -15)
					{
						       olcd_clearsCreen();
						olcm_dispprintf(0,1,"��ǰ�¶�:%.02f",temperature);
						if(TRUE == Select_YorNo())
					{	
					JiaReMoClose;
					jr_power = 2;
					 olcd_clearsCreen();
						olcm_dispprintf(0, 2, "��ǰ���ֶ���");
					delay_ms(100);
					i = mPORTGReadBits(BIT_7) >> 7;
					i = i & 0x01;
					if (i == 0) {
						olcm_dispprintf(0, 4, "  ����ģ���쳣  ");
						olcm_dispprintf(0, 4, "                ");
					}
				}
					else
					{
						eVirtualKey = _KEY_VIRTUAL_EV_;
						break;
					}
					}//end temperature
					else
					{
					JiaReMoClose;
					jr_power = 2;
						olcm_dispprintf(0, 2, "��ǰ���ֶ���");
					delay_ms(100);
					i = mPORTGReadBits(BIT_7) >> 7;
					i = i & 0x01;
					if (i == 0) {
						olcm_dispprintf(0, 4, "  ����ģ���쳣  ");
						olcm_dispprintf(0, 4, "                ");
					}	
					}
				}
				if (CE == 0) {
					JiaReMoClose;
					jr_power = 0;
						olcm_dispprintf(0, 2, "��ǰ���Զ�  ");
				}
				
				if ( 1 != o24lcxxx_write_bytes(jr_power_addr,(UINT8*)&CE,1 ) )
				{
					  olcm_dispprintf(0,4,"    ����ʧ��    ");
					     osys_getkey(_KEY_NULL_,320);
				}
				else
				{

				      olcm_dispprintf(0,4,"    ���óɹ�    ");
					  jr_power=CE;
				  osys_getkey(_KEY_NULL_,320);
				}
				 
				eVirtualKey = _KEY_VIRTUAL_EV_;
				break;
			}
		}
		if (vkey == _KEY_EXIT_EV_) {
			eVirtualKey = _KEY_VIRTUAL_EV_;
			return;
		}
	}
 }
BOOL Sys_Input_Cp()//rg170619 ���복�ƺ�
{
	 UINT8 vkey;
	 UINT8 len = 0;
    UINT8  str[12] = {0};
    olcd_clearsCreen();
     olcm_dispprintf(0,1,"    ���ƺ�����");
    olcm_dispprintf(0,2,"���룺");
    olcm_dispprintf(0,4,"�10λ  *-����");
     cursor_x=0;
	cursor_y=3;		
     vkey = okeyinput_get_cp(str,&len ,10,TRUE,FALSE);
      if(vkey == _KEY_EXIT_EV_ )
    {
 // memset(CPH,0x0,12);
      return FALSE; //�˳���
    }

    if( vkey == _KEY_OK_EV_ && len>0)
    {
	    memset(CPH_IN,0x0,12);
	memcpy(CPH_IN,str,len) ;   
	Cp_flag=1;
     return TRUE; 
    }
}
void oset_wdbjset(void)//�¶ȱ���//rg161103
{
    UINT8 len,vkey = 0;
    INT8  str[20] = {0};
       UINT8 ce,CE;
       UINT8  zfk;
       float wdcs,fEndr;
       olcd_clearsCreen();
  o24lcxxx_read_bytes_ex(Set_Wderr_Addr, (UINT8 *)&wdcs, 4);
   olcm_dispprintf(0,1,"��ǰ:           ");
   olcm_dispprintf(3,1,"%.02f   ",wdcs);
   olcm_dispprintf(0,2,"���룺");
   olcm_dispprintf(0,4,"��Χ: ����30��");  //160720//rg170228
   cursor_x = 4;
   cursor_y = 2;
      cxsr: olcm_dispprintf(3,2,"            ");
     vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
	   fEndr = (float)atof(str);
	   if(fEndr <= 30.0) //10.0  //160720//rg206//rg170228
		{
		   olcm_dispprintf(0,4,"��ֵ����, ������");
		   osys_getkey(_KEY_NULL_,200);
		   olcm_dispprintf(0,4,"��Χ: ����30��");//rg170228
		goto cxsr;  
		}       
	   if(4 != o24lcxxx_write_bytes_ex(Set_Wderr_Addr,(UINT8*)&fEndr,4))
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,300);
           return;
         }
	   WDBJ=fEndr;
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,300);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    else if ( vkey == _KEY_EXIT_EV_)
   {eVirtualKey = _KEY_VIRTUAL_EV_;
   }
 }
void oset_fdelay(void)	//rg170809 ��5����ʱ
{
     UINT8 len, vkey = 0;
   float fEndr = 0;
   float ylti;
   INT8  str[20] = {0};
   SYSTEMPARA systempara; 
   olcd_clearsCreen();

  if(TRUE != qty_get_sys(&systempara))  
   {//ͨ���쳣
   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  #if  _F_ENABLE_				//rg170809 ��5����ʱ����
	ylti = systempara.f_delay;
#endif 
  //////////////
     olcm_dispprintf(0,1,"  ����ʱʱ��");
   olcm_dispprintf(0,2,"��ǰ:%.02f sec",(float)ylti);
   olcm_dispprintf(0,3,"����:");
olcm_dispprintf(0,4,"��Χ:0-900��      "); 
   cursor_x = 3;
   cursor_y = 3;
   vkey = okeyinput_getstr(str,&len ,4,TRUE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
        fEndr = (float)atof(str);
        if(fEndr > 900)  //ֵ����//rg170629 
        {
            olcm_dispprintf(0,4,"    ���ó���    ");
            osys_getkey(_KEY_NULL_,320); 
            return;
        }

        if( TRUE!= Set_fdelay(fEndr,4))//
        {
            //ͨ���쳣
           olcm_dispprintf(0,4,"    ����ʧ��    ");
           osys_getkey(_KEY_NULL_,320);
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
         }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,320);
           eVirtualKey = _KEY_VIRTUAL_EV_;
   }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   }
 }
void strtoint(UINT8 *str,UINT8 *des,UINT8 len)
{
    UINT8 ch[20],i,j,dh[20],point;
    memset(ch,0x0,20);
    memset(dh,0x0,20);
    memcpy(ch,str,20);
    j=0;
    point=0;
    for(i=0;i<len;i++)
    {//dhȥ����
        if(ch[i]==0x2e)
        {
            point = i;
            if(ch[i+1] != 0x00)
            {
                dh[j]=ch[i+1];  
                if(ch[i+2] != 0x0)
                  dh[j+1]=ch[i+2];
                else
                   dh[j+1] = 0x30; 
                break;
            }
            else
            {
                dh[j++]=0x30;
            dh[j++]=0x30;
            break; 
            }
        }
            else
        {
            dh[j]=ch[i];
            j++;
        }
    }
    if(point == 0)
    {
       dh[j]=0x30;
        dh[j+1]=0x30; 
        memcpy(des,dh,20);
        return;
    }
     else if(len == point+1)
    {
        memcpy(des,dh,20);
        return;
    }
    else if(len == point+2)
    {
//        dh[j]=0x30;
        memcpy(des,dh,20);
        return;
    }
    else if(len == point+3)
    {
        memcpy(des,dh,20);
        return;
    }
    else
    {
        memcpy(des,dh,20);
        return;
    }
}
void oset_stotal(void)//rg181129
{
      UINT8 keyV,len=0;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
    
      INT8 passbuf[6] = {'1','1','1','1','1','1'};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ���ð���");
    olcm_dispprintf(0,2,"����������: ");
      while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
            }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                {
                     UINT8 len, vkey = 0;
   UINT32 s_total = 0;
   UINT32 flowwate = 0;
   UINT8 key;
   float num;
   UINT8  str[20] = {0};
   UINT8  des[20] = {0};
    UINT16 addr,offset_id = 0;
   UINT8 types[3];
   olcd_clearsCreen();
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
       if(TRUE !=  qty_get_shift(&s_total))//RG3133
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;
    }
 //     olcm_dispprintf(0,1,"��ǰ:%d.%02d",s_total/100,s_total%100);
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"��ǰ:%d.%02d",s_total/100,s_total%100);
       olcm_dispprintf(0,2,"��ΧС�ڶ�ǧ��");
       cursor_x = 0;
       cursor_y = 3;
       vkey = okeyinput_getstrbl(str,&len ,11,TRUE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
                      strtoint(str,des,len);
            flowwate = atoi(des);
            if(flowwate >= (2000000000))
            { 
                olcm_dispprintf(0,4,"    ���ó���    ");
            osys_getkey(_KEY_NULL_,320);
	    eVirtualKey = _KEY_VIRTUAL_EV_;
	    eCurRunState = State_Set_power;
            return;
            }
 
            if( TRUE != Set_stotal((UINT8*)&flowwate,4))//
               {
                //ͨ���쳣
               olcm_dispprintf(0,4,"    ����ʧ��    ");
               osys_getkey(_KEY_NULL_,330);
               SOEACTION1(PRO422_ERR,eCurRunState);
               eCurRunState = State_Set_power;
               return;
                }
//	      AddSOE(Para_lsh);//rg180613
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,330);
           eVirtualKey = _KEY_VIRTUAL_EV_;
           eCurRunState = State_Set_power;
           return;
        }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
       eCurRunState = State_Set_power;
           return;
   }
                  }
                            else
                          {   
                              len = 0;
                               olcd_clearsCreen();
                              olcm_dispprintf(0,2,"�������������");
                               KeyEccgtick = gTick+100;
                          }     
                     }
          }
  //    }
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
            eCurRunState = State_Set_power;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
}
void oset_qtotal(void)//rg181129
{
      UINT8 keyV,len=0;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
    
      INT8 passbuf[6] = {'2','2','2','2','2','2'};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ����ǹ��");
    olcm_dispprintf(0,2,"����������: ");
      while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
            }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                {
                     UINT8 len, vkey = 0;
   UINT32 s_total = 0;
   UINT32 flowwate = 0;
   INT32 aaaa=123;////////////////
   UINT8 key;
   float num;
   UINT8  str[20] = {0};
   UINT8  des[20] = {0};
    UINT16 addr,offset_id = 0;
   UINT8 types[3];
   olcd_clearsCreen();
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
       if(TRUE !=  qty_get_gid(&s_total))
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;
    }
 //     olcm_dispprintf(0,1,"��ǰ:%d.%02d",s_total/100,s_total%100);
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"��ǰ:%d.%02d",s_total/100,s_total%100);
       olcm_dispprintf(0,2,"��ΧС�ڶ�ǧ��");
       cursor_x = 0;
       cursor_y = 3;
       vkey = okeyinput_getstrbl(str,&len ,11,TRUE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
                      strtoint(str,des,len);
            flowwate = atoi(des);
            if(flowwate >= (2000000000))
            //    if(aaaa >= (40000))
            { 
                olcm_dispprintf(0,4,"    ���ó���    ");
            osys_getkey(_KEY_NULL_,320);
	    eVirtualKey = _KEY_VIRTUAL_EV_;
	//    eCurRunState = State_Set_power;
            return;
            }
 
            if( TRUE != Set_qtotal((UINT8*)&flowwate,4))//
               {
                //ͨ���쳣
               olcm_dispprintf(0,4,"    ����ʧ��    ");
               osys_getkey(_KEY_NULL_,330);
               SOEACTION1(PRO422_ERR,eCurRunState);
               eVirtualKey = _KEY_VIRTUAL_EV_;
       //        eCurRunState = State_Set_power;
               return;
                }
//	      AddSOE(Para_lsh);//rg180613
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,330);
           eVirtualKey = _KEY_VIRTUAL_EV_;
       //    eCurRunState = State_Set_power;
           return;
        }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
   //    eCurRunState = State_Set_power;
           return;
   }
                  }
                            else
                          {   
                              len = 0;
                               olcd_clearsCreen();
                              olcm_dispprintf(0,2,"�������������");
                               KeyEccgtick = gTick+100;
                          }     
                     }
          }
  //    }
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
//            eCurRunState = State_Set_power;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
}
void oset_curflowbz(void)//rg181129
{
      UINT8 keyV;
     UINT8 slen1,slen2;
     UINT8  bDot = 1;
     UINT32 KeyEccgtick = 0;
     INT8 tmpbuf[6];
    UINT8    shift_op_time[6];
     UINT8 psw1,psw2,psw5,psw6;
     UINT8 len, vkey = 0;
   UINT32 qid_total = 0;
   UINT32 flowwate = 0;
   UINT32 lsh;
   float num;
   UINT8 key;
   float fEndr = 0,fqEndr = 0,fzEndr = 0;
   UINT16 addr,offset_id = 0;
   UINT8 types[3]; 
   UINT8  str[20] = {0};
   UINT8  des[20] = {0};
     INT8 passbuf[6] = {'3','3','3','3','3','3'};
     olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ���ð���ˮ��");
    olcm_dispprintf(0,2,"����������: ");
      while(1)
    {     keyV = osys_getkey_ex(); //Sys_GetKey();
           b_keyv = FALSE;
           
           if(gTick > KeyEccgtick)
           { KeyEccgtick = 0;
            olcm_dispprintf(0,2,"����������:     ");
            }
          if(keyV == _KEY_ENTER_EV_)
                {
                     if(len >= 6)
                     {
                if((tmpbuf[0] == passbuf[0]) && (tmpbuf[1] == passbuf[1])&&(tmpbuf[2] == passbuf[2])&&(tmpbuf[3] == passbuf[3])&&(tmpbuf[4] == passbuf[4])&&(tmpbuf[5] == passbuf[5]) )
                {

   olcd_clearsCreen();
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
   if(TRUE !=  qty_get_shiftls(&lsh))//RG3133
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;

    }
 //     olcm_dispprintf(0,1,"��ǰ:%d.%02d",qid_total/100,qid_total%100);
       olcd_clearsCreen();
    olcm_dispprintf(0,1,"  �������ˮ��");
      // olcm_dispprintf(0,2,"��ǰ��%d",cur_sysparas.p_curflow);
       olcm_dispprintf(0,2,"��ǰ��%d",lsh);
       olcm_dispprintf(0,3,"����:");
       cursor_x = 3;
       cursor_y = 3;
       vkey = okeyinput_getstr(str,&len ,6,FALSE,FALSE);
        if( vkey == _KEY_OK_EV_ && len>0)
        {
                      flowwate = (UINT32)atoi(str);
            if( TRUE != Set_curflowbz((UINT8*)&flowwate,4))//
               {
                //ͨ���쳣
               olcm_dispprintf(0,4,"    ����ʧ��    ");
               osys_getkey(_KEY_NULL_,330);
               SOEACTION1(PRO422_ERR,eCurRunState);
               eVirtualKey = _KEY_VIRTUAL_EV_;
               return;
                }
           olcm_dispprintf(0,4,"    ���óɹ�    ");
           osys_getkey(_KEY_NULL_,330);
           eVirtualKey = _KEY_VIRTUAL_EV_;
	//    eCurRunState = State_Set_power;
            return;
        }
    if( vkey == _KEY_EXIT_EV_)
   {
       eVirtualKey = _KEY_VIRTUAL_EV_;
	//    eCurRunState = State_Set_power;
            return;
   }
                  }
                            else
                          {   
                              len = 0;
                               olcd_clearsCreen();
                              olcm_dispprintf(0,2,"�������������");
                               KeyEccgtick = gTick+100;
                          }     
                     }
          }
  //    }
        if(keyV == _KEY_EXIT_EV_)
        {   
            eVirtualKey = _KEY_VIRTUAL_EV_;
    //        eCurRunState = State_Set_power;
          return;
        }
        if(_KEY_SW_EV_ == keyV)
        {
          if(len == 0) continue;
          len -= 1;
          tmpbuf[len] = 0;
         
        }
        if( keyV >= _KEY_0_EV_ && keyV <= _KEY_9_EV_)
        {
          if (len >= 6) continue;
           
            tmpbuf[ len++] = keyV-1+'0';
           
        }
     keyV = 0;
  
     if(len < 7)
     {
       if(gTick >Runled_tick)
       {
         runled_fresh();//ˢ���е�
         slen1 = len%2;
         slen2 = len/2;
         if(bDot)
         {
             if(slen1 == 0)
             { olcd_dispstr(0+slen2,3,"_      ",6);
               if(slen2 ==3) //����6λ
                 olcd_dispstr(0+slen2,3," ",1);
             }
              else
              olcd_dispstr(0+slen2,3,"*_    ",6);
              if(slen2 > 0)
                 olcd_dispstr(0+slen2-1,3,"**",2);
              if(slen2 > 1)
                 olcd_dispstr(0+slen2-2,3,"****",4);//�ֲ����ٰ�����*��ʾ
             bDot = 0;
         }
         else
         {

             if(slen1 == 0)
                 olcd_dispstr(0+slen2,3,"      ",6);

              else
              olcd_dispstr(0+slen2,3,"*     ",6);
            if(slen2 > 0)
             olcd_dispstr(0+slen2-1,3,"**",2);
             bDot = 1;
         }
       }
     } //end of  if len <7
    }
}
