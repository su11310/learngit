/*
 * File:   qry.c
 * Author: luom
 *
 * Created on 2014_01_15
 */

#include "../includes/global_def.h"
//CARD01_INFO card01_info;
#define OLD_QRY 0
UINT8 keynum,keynumc=0;
void oxscardxx(UINT8 key);
float getatof(UINT8 *p)
{
    return atof(p);
}
UINT8 getatoi(UINT8 *p)
{
    return atoi(p);
}

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void oqry_rec_disp(UINT32 id, BOOL bDisp)   //
{

        float dj;float je;float ql;UINT32 *recg;
       if(TRUE != qty_get_serrec(id,dj,je,ql))
       {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
        if(bDisp == TRUE)
        {
             olcd_clearsCreen();
            olcm_dispprintf(0,1,"��ˮ��:%ld",id);
            if(cur_max_recid0 == id)   //417
            {
                olcm_dispprintf(0,2,"���ۣ�%.2f",dj);
                olcm_dispprintf(0,3,"������%.2f",ql);
                olcm_dispprintf(0,4,"��%.2f",je);
                olcm_dispprintf(6,4,"����");
            }
            else
            {
                olcm_dispprintf(0,2,"�޸ñʼ�����¼!");
            }
        }
        else
        {
            oprint_header_cmd();
            //oprint_printf("---��ӭʹ��LNG������(Q)---\r\n"); //cur_sysparas
            oprint_printf("��ˮ��:%ld",id);
            oprint_normal_cmd();
            oprint_printf("\r\n");
            oprint_printf("\r\n");
             if(cur_max_recid0 == id)

             {  oprint_printf("����:%.2f\r\n", dj);
                oprint_printf("����:%.2f\r\n", ql);
                oprint_printf("���:%.2f\r\n", je);

             }
             else{
                  olcm_dispprintf(0,2,"�޸ñʼ�����¼!");
             }
        }
}


void oqry_rec(void)
{

    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  ������¼��ѯ");
    olcm_dispprintf(0,2,"1.˳��  2.����");
    olcm_dispprintf(0,3,"3.ǹ��  4.����");
   // olcm_dispprintf(0,4,"3.���鵱���ۼ�");


}
void oqry_liushui_typerec(void)
{

    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.��˳���ѯ");
    olcm_dispprintf(0,2,"2.������ˮ�Ų�ѯ");



}

void oqry_liushuirec(void)
{
        UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;

      //   SOEACTION1(PRO422_ERR,eCurRunState);//���ڹ���
       //    return;
     olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
      cur_max_recid = get_max_rec_id();//wangqaz
     if(0xFFFF0000 ==cur_max_recid)
      {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
        id = maxid = cur_max_recid;//init����
        if( id == 0 ){
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"����ˮ��¼��");
             osys_getkey(_KEY_NULL_, 2000);
            eVirtualKey = _KEY_VIRTUAL_EV_;

            return;
        }
        oqry_rec_disp(id, TRUE);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            if(_KEY_UP_EV_ == keyv)
            {
                if(--id == 0){
                    id = 1;
                    continue;
                }
            }
            if(_KEY_SW_EV_ == keyv)
            {
                if(++id > maxid){
                    id = maxid;
                    continue;
                }

            }
            if(_KEY_ENTER_EV_ == keyv)
            {
                oqry_rec_disp(id, FALSE);
                oqry_rec_disp(id, TRUE);
                continue;
            }
            oqry_rec_disp(id, TRUE);
            oqry_rec_disp(id, FALSE);
        }
        eVirtualKey = _KEY_VIRTUAL_EV_;





}
UINT32 get_max_rec_id(void)
{   float dj;float je;float ql;

 if(TRUE==qty_get_rec(dj,je,ql))//,reci))
      {
       // cur_max_recid= ((*reci)<<24|| (*(reci+1))<<16||(*(reci+2))<<8||(*(reci+3)));
          cur_max_recid=cur_max_recid0;
      }
      else
         return 0xFFFF0000;
 
}
void oqry_searchliushuirec(void)
{
   UINT8 len, vkey = 0;
   INT8  str[20] = {0};
  UINT32 liushuinum = 0;

 UINT32 id ;
 UINT32 maxid;
 BOOL   bdisp = FALSE;
     olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
      cur_max_recid = get_max_rec_id();//wangqaz
     if(0xFFFF0000 ==cur_max_recid)
      {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
  id = maxid = cur_max_recid;
   olcd_clearsCreen();
    olcm_dispprintf(0,1,"��������ˮ�ţ�");
  // olcm_dispprintf(0,1,"���䵥��: %.02f",cur_sysparas.p_Price );//3.56);
   cursor_x = 0;
   cursor_y = 2;
   vkey = okeyinput_getstr(str,&len ,6,FALSE,FALSE);
   if( vkey == _KEY_OK_EV_ && len>0)
   {
         liushuinum= atoi(str);
         if((liushuinum <= id) && liushuinum >= 0 )
         {
             oqry_rec_disp(liushuinum, TRUE);
             ////////
              while(1)
                {
                    keyv = ostatemachine_getkey();
                    b_keyv = FALSE;
                    bdisp = FALSE;

                    if(0 == keyv) continue;
                    if(_KEY_EXIT_EV_ == keyv) break;
                    if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
                    if(_KEY_UP_EV_ == keyv)
                    {
                        if(--liushuinum == 0){
                            id = 1;
                            continue;
                        }
                    }
                    if(_KEY_SW_EV_ == keyv)
                    {
                        if(++liushuinum > maxid){
                            liushuinum = maxid;
                            continue;
                        }

                    }
                    if(_KEY_ENTER_EV_ == keyv)
                    {
                        oqry_rec_disp(liushuinum, FALSE);
                        oqry_rec_disp(liushuinum, TRUE);
                        continue;
                    }
                    oqry_rec_disp(liushuinum, TRUE);
                    oqry_rec_disp(liushuinum, FALSE);
                }
             ///////
           // osys_getkey(_KEY_NULL_,1000);
         }
         else
         {//û�����������ˮ�ż�¼
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"���������ˮ��");
             olcm_dispprintf(0,2,"û�м�������");
             osys_getkey(_KEY_NULL_,1000);
         }

   }

   eVirtualKey = _KEY_VIRTUAL_EV_;
}


/*//******WANGZONGWEN
void oqry_rec(void)
{
        UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;
        id =maxid = cur_max_recid;//cur_sysinfo.g_uid;
        if( id == 0 ){
            eVirtualKey = _KEY_VIRTUAL_EV_;
            return;
        }
        oqry_rec_disp(id, TRUE);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            if(_KEY_UP_EV_ == keyv)
            {
                if(--id == 0){
                    id = 1;
                    continue;
                }
            }
            if(_KEY_SW_EV_ == keyv)
            {
                if(++id > maxid){
                    id = maxid;
                    continue;
                }

            }
            if(_KEY_ENTER_EV_ == keyv)
            {
                oqry_rec_disp(id, FALSE);
                continue;
            }
            oqry_rec_disp(id, TRUE);
        }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
*/

void oqry_shift_disp(UINT32 id, BOOL bDisp)
{
        _lng_shift_rec  tmp_rec;
        UINT8  str[16] = {0};
        float  fvrd = 0;
        olcd_clearsCreen();
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,1,"����ˮ:%ld",id);
        }
        else
        {
            oprint_header_cmd();
            oprint_printf("---xxxx�����¼(Q)---\r\n"); //cur_sysparas
            oprint_normal_cmd();
            oprint_printf("\r\n");
            oprint_printf("\r\n");
        }

        //onand_rdBuff

        onand_rdBuff(SHIFT_NANDFLASH_S_ADDR+(id-1)*SHIFT_NANDFLASH_SIZE, (UINT8*)&tmp_rec.shift_rec_id, sizeof(struct def_LCNG_shift_rec));
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,2,"�ֽ�%.02f",tmp_rec.shift_cash);
        }
        else
        {
            oprint_printf("�ֽ�%.02f",tmp_rec.shift_cash);
        }
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,3,"��ʼǹ�ۣ�%.02f",tmp_rec.shift_s_mount);
            olcm_dispprintf(0,4,"����ǹ�ۣ�%.02f",tmp_rec.shift_e_mount);
        }
        else
        {
            oprint_printf("��ʼǹ�ۣ�%.02f",tmp_rec.shift_s_mount);
            oprint_printf("����ǹ�ۣ�%.02f",tmp_rec.shift_e_mount);
        }
}

#if OLD_QRY
void oqry_shift(void)   //�������ۼ�**********
{
        UINT32 id ;
        UINT32 maxid;
       _lcng_rec  tmp_rec;
         id =maxid = cur_max_recid;//cur_sysinfo.g_uid;
         float  fvrdsum = 0;
        UINT8  str[16] = {0};
        float  fvrd = 0;
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"��ֵ����");
        olcm_dispprintf(0,2,"--------------");


      for (;id >= 1;id--)
        {   onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_id[0], sizeof(struct def_LCNG_Record));
           if (tmp_rec.rec_shift_id == 0)  //Ԥ�����ţ��Ժ�ͨ����ð��鿨����ʵʱ��Ҫ��
           {
             memcpy(str,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
             fvrd = atof(str);
             fvrdsum += fvrd;

            }
        if (id -1 == 0) break;
        }

     olcm_dispprintf(0,2,"���ۼ�������%.02f",fvrdsum);


    osys_getkey(_KEY_NULL_,1000);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}
#endif
#if OLD_QRY
void oqry_todayshift(void)   //����������ۼ�**********
{
        UINT32 id ;
        UINT32 maxid;
       _lcng_rec  tmp_rec;
         id =maxid = cur_max_recid;//cur_sysinfo.g_uid;
         float  fvrdsum = 0;
        UINT8  str[16] = {0};
        float  fvrd = 0;
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"��ֵ����");
        olcm_dispprintf(0,2,"--------------");


      for (;id >= 1;id--)
        {   onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_id[0], sizeof(struct def_LCNG_Record));
           if (tmp_rec.rec_shift_id == 0)  //Ԥ�����ţ��Ժ�ͨ����ð��鿨����ʵʱ��Ҫ��
           {
             memcpy(str,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
             fvrd = atof(str);
             fvrdsum += fvrd;

            }
        if (id -1 == 0) break;
        }

     olcm_dispprintf(0,2,"���ۼ�������%.02f",fvrdsum);
    osys_getkey(_KEY_NULL_,1000);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}
#endif

//BOOL ortcc_read_min(UINT8 *rdtime);
//UINT8 EEPROM_ReadByte(UINT16 addr);
void oqry_rec_ex(void)
{
#if 0
       UINT8  hh = 0;
       UINT8  mm = 0;
       UINT8  ss = 0;
  /*     if( ortcc_read_time(&rd))
       {
            rd = ocomm_bcd2dec(rd&0x7F);
            odisp_disp(22.22,rd,FALSE);
       }
       else
       {
           odisp_disp(33.33,rd,FALSE);

        } */
       ortcc_read_time(&ss);
       ortcc_read_min(&mm);
       ss = ocomm_bcd2dec(ss&0x7F);
       mm = ocomm_bcd2dec(mm&0x7F);
       odisp_disp(mm,ss,FALSE);
       //ortcc_read_time(&rd)
//

     //  UINT8 rd = EEPROM_ReadByte(0x13);
     //  odisp_disp(rd,rd,FALSE);
//#else
        float  f_temp = 0.00;
        ostore_read_paras(P_PRICE_ID,(UINT8*)&cur_un_float.dt_uc[0],4);

        odisp_disp(cur_un_float.dt_float,cur_un_float.dt_float,FALSE);
//
//#else
        UINT8 rd_str[10] = {0};

        if( o24lcxxx_read_bytes(0x3003, rd_str, 4 ))
        {
            odisp_disp(rd_str[2],rd_str[3],FALSE);
        }
        else
        {
            odisp_disp(33.33,_simu_iic_step,FALSE);
        }
//#else
        float  f_temp = 0.0;
        f_temp = ostore_paras_rdfloat(P_PRICE_ID);
        odisp_disp(f_temp,f_temp,FALSE);
        odisp_disp(f_temp,f_temp,FALSE);
#else

#endif
}

void putclassxx()
{
UINT8 z[10];
    UINT8 s[10];
    UINT8 i;
    olcd_clearsCreen();
    i=1;
    olcm_dispprintf(0,1,"��ţ�");
    olcm_dispprintf(0,2,"״̬��");
    olcm_dispprintf(0,3,"���룺");
         sprintf(z, "%d", cur_class_info[keynumc-1].class_num);
        sprintf(s, "%d", cur_class_info[keynumc-1].class_state);
        olcm_dispprintf(3,1,z);
        olcm_dispprintf(3,2,s);
        olcm_dispprintf(3,3,&cur_class_info[keynumc-1].class_pw[0]);
        olcm_dispprintf(6,4,"����");

}
//��ѯ��Ϣ����Ӱ�����Ϣ��ʾ  time:2014-3-13  rengang
void oqry_shift_iofo(void)
{     UINT32  id;
      UINT8 Classnum,n,keyV;
      UINT32 maxid;
      UINT8  str[16] = {0};
      float  fvrd = 0;
      Classnum=0;
      id =maxid = cur_max_shiftid;
//////////////////////////////////////////////////
        oset_getclassxx();
      for(n=0;n<10;n++)
      {
          if(cur_class_info[n].class_state==1)
           Classnum++;
      }
        memset(str,0,sizeof(str));
        memcpy(str,(UINT8*)& cur_shift_loginfo.shift_card[0],6);
        fvrd = atof(str);
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"��ֵ����:%d", cur_shift_loginfo.shift_id);//�����νṹ��qaz
        olcm_dispprintf(0,2,"��ֵ���鿨��:");
        olcm_dispprintf(0,3,"%s",cur_shift_loginfo.shift_card);
        olcm_dispprintf(0,4,"�ڲ������:%ld",Classnum);
        olcm_dispprintf(7,4,"��");
        while(1)
            {
              keyv = ostatemachine_getkey();
              b_keyv = FALSE;
              if(0 == keyv) continue;
              if(_KEY_EXIT_EV_ == keyv) break;
              if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
              if(_KEY_SW_EV_ == keyv)
                {
                    while(++keynumc<=10)
                        {
                        if(cur_class_info[keynumc-1].class_state==1)
                            {
                                putclassxx();
                                break;
                            }
                        }
                        if(keynumc>10)
                        {
                            keynumc=0;
                        olcd_clearsCreen();
                        olcm_dispprintf(0,1,"��ֵ����:%d", cur_shift_loginfo.shift_id);//���Դ�cur_shift_sysinfo��ȡ������IC��Ҫ�������ݵ������ṹ
                        olcm_dispprintf(0,2,"��ֵ���鿨��:");
                        olcm_dispprintf(0,3,"%s",cur_shift_loginfo.shift_card);
                        olcm_dispprintf(0,4,"�ڲ������:%ld",Classnum);
                        olcm_dispprintf(7,4,"��");
                        }
                            continue;
                }
                         if(_KEY_UP_EV_ == keyv)
                {
                             
#if 0
                        if(keynumc<=1)
                        {
                           keynumc=10;
                           if(cur_class_info[keynumc-1].class_state==1)
                            {
                                putclassxx();
                                continue;
                            }
                         }
#endif
                        if(keynumc==0)
                             {
                              olcd_clearsCreen();
                        olcm_dispprintf(0,1,"��ֵ����:%d", cur_shift_loginfo.shift_id);//���Դ�cur_shift_sysinfo��ȡ������IC��Ҫ�������ݵ������ṹ
                        olcm_dispprintf(0,2,"��ֵ���鿨��:");
                        olcm_dispprintf(0,3,"%s",cur_shift_loginfo.shift_card);
                        olcm_dispprintf(0,4,"�ڲ������:%ld",Classnum);
                        olcm_dispprintf(7,4,"��");
                        keynumc=11;
                        continue;
                             }
                     while(--keynumc>=1)
                        {
                        if(cur_class_info[keynumc-1].class_state==1)
                            {
                                putclassxx();
                                break;
                            }
                        }
                                if(keynumc==0)
                             {
                              olcd_clearsCreen();
                        olcm_dispprintf(0,1,"��ֵ����:%d", cur_shift_loginfo.shift_id);//���Դ�cur_shift_sysinfo��ȡ������IC��Ҫ�������ݵ������ṹ
                        olcm_dispprintf(0,2,"��ֵ���鿨��:");
                        olcm_dispprintf(0,3,"%s",cur_shift_loginfo.shift_card);
                        olcm_dispprintf(0,4,"�ڲ������:%ld",Classnum);
                        olcm_dispprintf(7,4,"��");
                        keynumc=11;
                        continue;
                             }
                        
                }
            }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}

void oqry_system(void)
{
#if 0
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"%s",_VERSION_);
    olcm_dispprintf(0,2,"ǹ��:%d",cur_sysparas.p_GID);
    osys_getkey(_KEY_NULL_,1000);
    eVirtualKey = _KEY_VIRTUAL_EV_;
#else
    UINT8 keyv = 0;
    BOOL  bprt = FALSE;
    UINT8 SW_id = 1;
    UINT8 qid;float temp;float price;float Density ;
    float gain;float ls;float yl;float aqyl;float Density_up;float Density_do;float ylys;
  if(TRUE != qty_get_sys(qid,temp,price,Density ,gain,ls ,yl,aqyl,Density_up ,Density_do,ylys))
  {//ͨ���쳣

   SOEACTION1(PRO422_ERR,eCurRunState);
     return;

  }
  while(1)
  {
    if( SW_id == 1 )
    {   olcd_clearsCreen();
        olcm_dispprintf(0,1,"%s",_VERSION_);
        olcm_dispprintf(0,2,"%s",HARD_VERSION_);
        olcm_dispprintf(0,3,"��ǰǹ��:%4d",qid);
        olcm_dispprintf(0,4,"��1/7 ҳ��");
       
    }
    if(SW_id == 2)
     {
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"�趨�¶�:-%.02f",temp);
      olcm_dispprintf(0,2,"�趨����:%.02f",price);
      olcm_dispprintf(0,3,"�趨�ܶ�:%.02f",Density);
      olcm_dispprintf(0,4,"��2/7 ҳ����");
      
    }
      if(SW_id == 3)
     {
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"Ԥ������: %.02f",gain);
      olcm_dispprintf(0,2,"ͣ������: %.02f",ls);
      olcm_dispprintf(0,3,"ͣ��ѹ��: %.02f",yl);
      olcm_dispprintf(0,4,"��3/7 ҳ����");
    
     
   
    }
     if(SW_id == 4)
     {
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"��ȫѹ��: %.02f",(float)aqyl);
      olcm_dispprintf(0,4,"��4/7 ҳ����");
    }
     if(SW_id == 5)
     {
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"�ܶ�����: %.02f",Density_up);
      olcm_dispprintf(0,2,"�ܶ�����: %.02f",Density_do);
      olcm_dispprintf(0,3,"Ԥ����ʱ: %.02f",ylys);
      olcm_dispprintf(0,4,"��5/7 ҳ����");
    }
     if(SW_id == 6)
     {
      olcd_clearsCreen();
   
      olcm_dispprintf(0,1,"�ڿ���Ŀ: 0");//???????????????????????
      olcm_dispprintf(0,2,"�ҿ�����: 0");///?????????????????????????
      olcm_dispprintf(0,4,"��6/7 ҳ����");
    }
     if(SW_id == 7)
     {  UINT32 readT;
        UINT16 day;
        UINT8 hour,minute;
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"�з�����: 0 ");
      olcm_dispprintf(0,2,"��Ӫʱ��: ");
      readT= Get_Sys_Runtime();
      day = (UINT16)(readT*5/60/24);
      hour =(UINT8)(readT*5/60%24);
      minute=(UINT8)(readT*5%60);
      olcm_dispprintf(0,3,"%4d��%2dʱ%2d��",day,hour,minute);
      
      olcm_dispprintf(0,4,"��7/7 ҳ��");

    }

    
    while(1)
    {
        keyv = ostatemachine_getkey();
        b_keyv = FALSE;

            if(_KEY_SW_EV_ == keyv)
            {
             SW_id ++;
             if(SW_id > 7)
                SW_id = 1;
             break;
            }
        if(_KEY_UP_EV_ == keyv)
            {
             SW_id --;
             if(SW_id < 1)
                SW_id = 7;
             break;
            }
        if(_KEY_EXIT_EV_ == keyv || _KEY_ENTER_EV_ == keyv)
        {
            eVirtualKey = _KEY_VIRTUAL_EV_;
            return;
        }
    }
  }
#endif
}

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/*
void oqry_rec_disp(UINT32 id, BOOL bDisp)
{
        //UINT32 id = cur_sysinfo.g_uid;
        _lcng_rec  tmp_rec;
        UINT8  str[16] = {0};
        float  fvrd = 0;
        olcd_clearsCreen();
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,1,"��ˮ��:%ld",id);
        }
        else
        {
            oprint_header_cmd();
            oprint_printf("---��ӭʹ��LNG������(Q)---\r\n"); //cur_sysparas
            oprint_normal_cmd();
            oprint_printf("\r\n");
            oprint_printf("\r\n");
        }
        //onand_rdBuff
//onand_rdBuff(SHIFT_NANDFLASH_S_ADDR+(id-1)*SHIFT_NANDFLASH_SIZE, (UINT8*)&tmp_rec.shift_rec_id, sizeof(struct def_LCNG_shift_rec));
         onand_rdBuff(REC_NANDFLASH_S_ADDR+(id-1)*128, &tmp_rec.rec_id[0], sizeof(struct def_LCNG_Record));
        memset(str,0,sizeof(str));
        memcpy(str,(UINT8*)&tmp_rec.rec_lcngprice[0],6);
        fvrd = atof(str);
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,2,"���ۣ�%.02f",fvrd);
        }
        else
        {
            oprint_printf("����:%.02f\r\n", fvrd);
        }
        memset(str,0,sizeof(str));
        memcpy(str,(UINT8*)&tmp_rec.rec_lcngnum[0],8);
        fvrd = atof(str);
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,3,"������%.02f",fvrd);
        }
        else
        {
            oprint_printf("����:%.02f\r\n", fvrd);
        }

        memset(str,0,sizeof(str));
        memcpy(str,(UINT8*)&tmp_rec.rec_lcngM[0],10);
        fvrd = atof(str);
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,4,"��%.02f",fvrd);
        }
        else
        {
            oprint_printf("���:%.02f\r\n", fvrd);
            oprint_printf("\r\n");
            oprint_printf("\r\n");
            //ʱ��
            oprint_printf("--��̨��xxxx·xxxx����վ--\r\n");
            oprint_printf("------��ӭ�´ι���------\r\n");
        }
}*/
/*
void oqry_rec(void)
{
        UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;
        id =maxid = cur_max_recid;//cur_sysinfo.g_uid;
        if( id == 0 ){
            eVirtualKey = _KEY_VIRTUAL_EV_;
            return;
        }
        oqry_rec_disp(id, TRUE);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            if(_KEY_UP_EV_ == keyv)
            {
                if(--id == 0){
                    id = 1;
                    continue;
                }
            }
            if(_KEY_SW_EV_ == keyv)
            {
                if(++id > maxid){
                    id = maxid;
                    continue;
                }

            }
            if(_KEY_ENTER_EV_ == keyv)
            {
                oqry_rec_disp(id, FALSE);
                continue;
            }
            oqry_rec_disp(id, TRUE);
        }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}*/
/*
void oqry_shift_disp(UINT32 id, BOOL bDisp)
{
        _lng_shift_rec  tmp_rec;
        UINT8  str[16] = {0};
        float  fvrd = 0;
        olcd_clearsCreen();
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,1,"����ˮ:%ld",id);
        }
        else
        {
            oprint_header_cmd();
            oprint_printf("---xxxx�����¼(Q)---\r\n"); //cur_sysparas
            oprint_normal_cmd();
            oprint_printf("\r\n");
            oprint_printf("\r\n");
        }

        //onand_rdBuff
        
        onand_rdBuff(SHIFT_NANDFLASH_S_ADDR+(id-1)*SHIFT_NANDFLASH_SIZE, (UINT8*)&tmp_rec.shift_rec_id, sizeof(struct def_LCNG_shift_rec));
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,2,"�ֽ�%.02f",tmp_rec.shift_cash);
        }
        else
        {
            oprint_printf("�ֽ�%.02f",tmp_rec.shift_cash);
        }
        if(bDisp == TRUE)
        {
            olcm_dispprintf(0,3,"��ʼǹ�ۣ�%.02f",tmp_rec.shift_s_mount);
            olcm_dispprintf(0,4,"����ǹ�ۣ�%.02f",tmp_rec.shift_e_mount);
        }
        else
        {
            oprint_printf("��ʼǹ�ۣ�%.02f",tmp_rec.shift_s_mount);
            oprint_printf("����ǹ�ۣ�%.02f",tmp_rec.shift_e_mount);
        }
}*/
/*
void oqry_shift(void)
{
        UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;
        id =maxid = cur_max_shiftid;//cur_sysinfo.g_uid;
        if( id == 0 ){
            eVirtualKey = _KEY_VIRTUAL_EV_;
            return;
        }
        oqry_shift_disp(id, TRUE);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

            if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
            if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            if(_KEY_UP_EV_ == keyv)
            {
                if(--id == 0){
                    id = 1;
                    continue;
                }
            }
            if(_KEY_SW_EV_ == keyv)
            {
                if(++id > maxid){
                    id = maxid;
                    continue;
                }

            }
            if(_KEY_ENTER_EV_ == keyv)
            {
                oqry_shift_disp(id, FALSE);
                continue;
            }
            oqry_shift_disp(id, TRUE);
        }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}*/

//BOOL ortcc_read_min(UINT8 *rdtime);
//UINT8 EEPROM_ReadByte(UINT16 addr);

/*
void oqry_system(void)
{
#if 0
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"%s",_VERSION_);
    olcm_dispprintf(0,2,"ǹ��:%d",cur_sysparas.p_GID);
    osys_getkey(_KEY_NULL_,1000);
    eVirtualKey = _KEY_VIRTUAL_EV_;
#else
    UINT8 keyv = 0;
    BOOL  bprt = FALSE;
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"%s",_VERSION_);
    olcm_dispprintf(0,2,"ǹ��:%d",cur_sysparas.p_GID);
    olcm_dispprintf(0,3,":%ld",cur_max_recid);
    olcm_dispprintf(0,4,":%ld %d",cur_max_shiftid, b_shift_ok);
    while(1)
    {
        keyv = ostatemachine_getkey();
        b_keyv = FALSE;
        if(_KEY_EXIT_EV_ == keyv || _KEY_ENTER_EV_ == keyv)
        {
            break;
        }
    }
    if(_KEY_ENTER_EV_ == keyv)
    {
        oprint_sys_paras();
    }
    //osys_getkey(_KEY_NULL_,1000);
    eVirtualKey = _KEY_VIRTUAL_EV_;
#endif
}*/
//��ʾ����Ϣ1  time:2014-3-13  rengang
void oqry_cardinfo_ui_p1()
{
#if 0
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"״̬:");
        olcm_dispprintf(0,2,"����:");
        olcm_dispprintf(0,3,"����:");
        olcm_dispprintf(0,4,"����:");
        olcm_dispprintf(3,2,card01_info.M_Balance);
        olcm_dispprintf(3,3,card01_info.F_Balance);
        olcm_dispprintf(3,1,card01_info.CardState);
        olcm_dispprintf(2,4,&card01_info.cnn[0]);
#endif
}
//��ʾ����Ϣ2  time:2014-3-13  rengang
void oqry_cardinfo_ui_p2()
{
    #if 0
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"ƿ��:");
        olcm_dispprintf(0,2,"��Ч��");
        olcm_dispprintf(0,3,"����:");
        olcm_dispprintf(0,4,"Э���:");
        olcm_dispprintf(3,1,&card01_info.bcd[0]);
        olcm_dispprintf(3,2,&card01_info.bcavd[0]);
        olcm_dispprintf(3,3,&card01_info.cont[0]);
        olcm_dispprintf(4,4,&card01_info.cp[0]);
        osys_getkey(0,2000);
   #endif
}
//��ʾ����Ϣ3  time:2014-3-13  rengang
void oqry_cardinfo_ui_p3()
{
#if 0
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"������:");
        olcm_dispprintf(0,2,"����");
        olcm_dispprintf(0,3,"�����");
        olcm_dispprintf(0,4,"�����:");
        olcm_dispprintf(4,1,&card01_info.cdt[0]);
        olcm_dispprintf(3,2,&card01_info.ml[0]);
        olcm_dispprintf(3,3,&card01_info.gl[0]);
        olcm_dispprintf(4,4,&card01_info.tn[0]);
        osys_getkey(0,2000);
#endif
}
//ѡ��ֲ˵�  time:2014-3-13  rengang
void oqry_switch(UINT8 key)
{
       switch( keynum )
    {
        case 0:
            oqry_cardinfo_ui_p1();
            break;
        case 1:
            oqry_cardinfo_ui_p2();
            break;
        case 2:
            oqry_cardinfo_ui_p3();
            break;
        default:
            break;
    }
}

void oqry_switchc(UINT8 key)
{
 //   oqry_cardinfo_ui_c1();
 //   switch( _ui_qry_cardinfo_id )
#if 0
       switch( keynumc )
    {
        case 0:
            oqry_cardinfo_ui_c1();
            break;
        case 1:
            oqry_cardinfo_ui_c2();
            break;
        case 2:
            oqry_cardinfo_ui_p3();
            break;
        default:
            break;
    }
#endif
}
//��ʾ����Ϣ��һҳ��ֵ  time:2014-3-13  rengang
void odispcardinfo()
{
#if 0
    UINT8 filenum,k;
    olcm_dispprintf(3,2,card01_info.M_Balance);
    olcm_dispprintf(3,3,card01_info.F_Balance);
    olcm_dispprintf(3,4,card01_info.CardPassword);
#endif
}
//��ʾ����Ϣ��2\3ҳ��ֵ  time:2014-3-13  rengang
void oxscardxx(UINT8 key)
{
#if 0
     if(key==0)
    {
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"״̬:");
      olcm_dispprintf(0,2,"����:");
      olcm_dispprintf(0,3,"����:");
      olcm_dispprintf(0,4,"����:");

      olcm_dispprintf(3,2,card01_info.M_Balance);
      olcm_dispprintf(3,3,card01_info.F_Balance);
      olcm_dispprintf(3,1,card01_info.CardState);
      olcm_dispprintf(2,4,&card01_info.cnn[0]);
    }
    if(key==1)
    {
        olcd_clearsCreen();
        olcm_dispprintf(4,1,&card01_info.bcd[0]);
        olcm_dispprintf(6,2,&card01_info.bcavd[0]);
        olcm_dispprintf(6,3,&card01_info.cont[0]);
        olcm_dispprintf(8,4,&card01_info.cp[0]);
    }
    if(key==2)
    {
        olcd_clearsCreen();
        olcm_dispprintf(6,1,&card01_info.cdt[0]);
        olcm_dispprintf(6,2,&card01_info.ml[0]);
        olcm_dispprintf(6,3,&card01_info.gl[0]);
        olcm_dispprintf(6,4,&card01_info.tn[0]);
    }
#endif
}
//��ȡ��01�ļ���Ϣ  time:2014-3-13  rengang
UINT8 ogetcard_info()
{
#if 0
    UINT8 k,*p,len;
    delay_ms(20);
     k=GetCard01();
    p = strtok(data_01, ";");
    len=strlen(p);
    if((*p==0x4e)||(*(p+1)==0x3a))
        memcpy(card01_info.cnn,p+2,len-2);
    else
        return CARD_READ_ERR;
     p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x42)||(*(p+1)==0x43)||(*(p+2)==0x44)||(*(p+3)==0x3a))
        memcpy(card01_info.bcd,p+4,len-4);
    else
        return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x42)||(*(p+1)==0x43)||(*(p+2)==0x41)||(*(p+3)==0x56)\
        ||(*(p+4)==0x44)||(*(p+5)==0x3a))
    memcpy(card01_info.bcavd,p+6,len-6);
    else
         return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x43)||(*(p+1)==0x4f)||(*(p+2)==0x55)||(*(p+3)==0x4e)\
        ||(*(p+4)==0x54)||(*(p+5)==0x3a))
        memcpy(card01_info.cont,p+6,len-6);
    else
         return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x43)||(*(p+1)==0x50)||(*(p+2)==0x3a))
        memcpy(card01_info.cp,p+3,len-3);
    else
        return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x43)||(*(p+1)==0x44)||(*(p+2)==0x54)||(*(p+3)==0x3a))
        memcpy(card01_info.cdt,p+4,len-4);
    else
        return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x4d)||(*(p+1)==0x4c)||(*(p+2)==0x3a))
        memcpy(card01_info.ml,p+3,len-3);
    else
        return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x47)||(*(p+1)==0x4c)||(*(p+2)==0x3a))
        memcpy(card01_info.gl,p+3,len-3);
    else
        return CARD_READ_ERR;

    p = strtok(NULL, ";");
    len=strlen(p);
    if((*p==0x54)||(*(p+1)==0x4e)||(*(p+2)==0x3a))
        memcpy(card01_info.tn,p+3,len-3);
    else
        return CARD_READ_ERR;
  return CARD_READ_OK;
#endif
}
//��ȡ������ļ���Ϣ  time:2014-3-13  rengang
UINT8 ogetcard_m()
{
#if 0
    UINT8 k;
    delay_ms(20);
    k=GetCardX(File_Memoy);
    if(k==CARD_READ_ERR)
       return CARD_READ_ERR;
    memcpy(card01_info.M_Balance,dataX[0],11);
#endif
    return CARD_READ_OK;
}
//��ȡ�������ļ���Ϣ  time:2014-3-13  rengang
UINT8 ogetcard_f()
{
    #if 0
    UINT8 k;
    delay_ms(20);
    k=GetCardX(File_Gas);
    if(k==CARD_READ_ERR)
     return CARD_READ_ERR;
    memcpy(card01_info.F_Balance,dataX[1],11);
    return CARD_READ_OK;
#endif
}

void osel_precoo()
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"Ԥ��");
    osys_getkey(_KEY_NULL_,1000);
    eVirtualKey = _KEY_VIRTUAL_EV_;
}
//��ȡ��״̬�ļ���Ϣ  time:2014-3-13  rengang
#if 0
UINT8 ogetcard_state()
{
    UINT8 k;
    delay_ms(20);
    k=GetCardX(File_State);
    if(k==CARD_READ_ERR)
    return CARD_READ_ERR;
    memcpy(card01_info.CardState,dataX[2],11);
    return CARD_READ_OK;
}
//��ȡ�������ļ���Ϣ  time:2014-3-13  rengang
UINT8 ogetcard_password()
{
    UINT8 k;
    delay_ms(20);
    k=GetCardX(File_Password);
    if(k==CARD_READ_ERR)
      return CARD_READ_ERR;
    memcpy(card01_info.CardPassword,dataX[3],11);
    return CARD_READ_OK;
}

//��01�ļ�������Ϣ
UINT8 check_card(void)
{
    int i;
    delay_ms(20);
    i= GetInto();
#if 1
   if(i<0)
   {
       return CARD_SELECT_ERR;
   }
#endif
  i=ogetcard_info();
   if(i==CARD_READ_OK)
       return i;
}


void oqry_cardinfo(void)
{
       UINT8 keyV,i,k,filenum,l,len;//,keynum;
       UINT8 *p;
       keynum=0;
       olcd_clearsCreen();
       ic_query_status1();
       olcd_clearsCreen();
       olcm_dispprintf(1,2,"�������Ժ�...");
       i= GetInto();
       if(i<0)
        {
            olcd_clearsCreen();
            olcm_dispprintf(0,2,"�Ǳ����������˳�");
        }
   
      if(ogetcard_info()!=CARD_READ_ERR)
        {
        if((ogetcard_m()==CARD_READ_OK)&&(ogetcard_f()==CARD_READ_OK)&&(ogetcard_state()==CARD_READ_OK))
            {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"״̬:");
                olcm_dispprintf(0,2,"����:");
                olcm_dispprintf(0,3,"����:");
                olcm_dispprintf(0,4,"����:");
                odispcardinfo();//��ʾ��������״̬
                olcm_dispprintf(2,1,&card01_info.CardState[0]);
                olcm_dispprintf(2,4,&card01_info.cnn[0]);
                while(1)
                    {
                        b_keyv = FALSE;
                        keyV=okey_scan_ex();
                        if(keyV == _KEY_EXIT_EV_)
                            {
                                b_keyv = FALSE;
                                goto t1;
                            }

                        if(keyV == _KEY_SW_EV_)
                            {
                             if(keynum==2)
                                 keynum=0;
                             else
                                keynum++;
                         oqry_switch(keynum);
                         osys_getkey(0,4000);
                         b_keyv = FALSE;
                         delay_ms(20);
                            }
                        if(keyV == _KEY_UP_EV_)
                            {
                             if(keynum>0)
                               keynum--;
                             oqry_switch(keynum);
                             osys_getkey(0,4000);
                             b_keyv = FALSE;
                             delay_ms(20);
                            }
                    }
t1:     osys_getkey(0,5000);
        delay_ms(20);
        eVirtualKey = _KEY_VIRTUAL_EV_;
        }
     }
 }
#endif
void oqry_card_Recharge()
{
    UINT8 filenum,re[10],j,datalen;
  //  float ss,dd;
  //  double ds;
   // filenum=0x02;                  //�ļ���ʶ��Ϊ01

  //  datalen=CARD_2LEN;
    re[0]=0x30;
 re[1]=0x30;
 re[2]=0x35;
 re[3]=0x30;
 re[4]=0x30;
 re[5]=0x30;
 re[6]=0x2e;
  re[7]=0x30;
 re[8]=0x30;
 re[9]=0x00;
 //dd=getatof(re);
 //ss=atof(re);
 //ds=atof(re);
 j=card_writebin_selmu(File_Memoy,0x00, re,CARD_2LEN);//�޸�
// j=card_readbin_selmu(filenum,0x00 ,re,datalen );//����
  re[0]=0x30;
 re[1]=0x30;
 re[2]=0x30;
 re[3]=0x34;
 re[4]=0x30;
 re[5]=0x30;
 re[6]=0x2e;
 re[7]=0x30;
 re[8]=0x30;
    re[9]=0x00;
 j=card_writebin_selmu(File_Gas,0x00, re, CARD_2LEN);//�޸�
// j=card_readbin_selmu(filenum,0x00 ,re,datalen );//����
 olcm_dispprintf(0,1,"OK");
}
//ʹ��  time:2014-3-13  rengang
UINT8 Card_Ash()
{
    UINT8 filenum,re[10];
    int j;
     re[0]=0x33;
    re[1]=0x00;
    re[2]=0x00;
    re[3]=0x00;
    re[4]=0x00;
    re[5]=0x00;
    re[6]=0x00;
    re[7]=0x00;
    re[8]=0x00;
    re[9]=0x00;
 //dd=getatof(re);
 //ss=atof(re);
 //ds=atof(re);
           j=3;
           while((card_writebin_selmu(File_State,0x00, re,CARD_2LEN)<0)&&(j>=0))//�޸�
           {
               j--;
           }
           if(j<0)
               return CARD_Modifybin_ERR;
           return CARD_Modifybin_OK;
// j=card_writebin_selmu(File_State,0x00, re,CARD_2LEN);//�޸�
 //Card_Solution();
// return 1;
}
//���
UINT8 Card_Solution()
{
    UINT8 filenum,re[10];
    int j;
 //   filenum=0x04;
 re[0]=0x31;
 re[1]=0x00;
 re[2]=0x00;
 re[3]=0x00;
 re[4]=0x00;
 re[5]=0x00;
 re[6]=0x00;
  re[7]=0x00;
 re[8]=0x00;
 re[9]=0x00;
 //dd=getatof(re);
 //ss=atof(re);
 //ds=atof(re);
           j=3;
           while((card_writebin_selmu(File_State,0x00, re,CARD_2LEN)<0)&&(j>=0))//�޸�
           {
               j--;
           }
           if(j<0)
               return CARD_Modifybin_ERR;
           return CARD_Modifybin_OK;
 //j=card_writebin_selmu(File_State,0x00, re,CARD_2LEN);//�޸�
 //return 1;
}


void oset_getclasum(UINT8 k)//time:14-03-14 rengang
{
 //       UINT8 n;
        UINT16 addr;
        addr=_SHIFT_SYSPARAS_EEP_ADDR_END+CLASSSIZE*(k-1);
  //      for( n = 0; n < 10 ; n++ )
  //      {
            memset((UINT8*)&cur_class_info[k-1].class_num,0x00,CLASSLEN);
            o24lcxxx_read_bytes_ex(addr, (UINT8*)&cur_class_info[k-1].class_num, CLASSLEN);
 //           addr +=CLASSSIZE;
  //      }
}
void oqry_shift(void)   //�������ۼ�**********time:14-3-14 rengang
{
      float qid_total;
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"��ǹ��: ");

    if(TRUE !=  qty_get_gid(qid_total))
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;

    }
      olcm_dispprintf(0,2,"��ǰ:%.02f",qid_total);
   

     osys_getkey(_KEY_NULL_, 500);
     eVirtualKey = _KEY_VIRTUAL_EV_;
}

void oqry_todayshift(void)   //����������ۼ�**********time:14-3-14 rengang
{      float s_total;
      olcd_clearsCreen();
      olcm_dispprintf(0,1,"��������� ");
    
        if(TRUE !=  qty_get_shift(s_total))
    {
         SOEACTION1(PRO422_ERR,eCurRunState);
          return;

    }
      olcm_dispprintf(0,2,"��ǰ:%.02f",s_total);
        osys_getkey(_KEY_NULL_,1000);
        eVirtualKey = _KEY_VIRTUAL_EV_;

   /*
        UINT32 id ;
        UINT32 maxid;
        UINT16 addr;
         UINT16 class;
       _lcng_rec  tmp_rec;
         id =maxid = cur_max_recid;//cur_sysinfo.g_uid;
         float  fvrdsum = 0,fvrmsum = 0;
        UINT8  str[16] = {0};
        float  fvrd=0,fvrm = 0;
        //UINT8 Cur_class=1;
         class = cur_shift_loginfo.shift_id;
          olcd_clearsCreen();
        olcm_dispprintf(0,1,"��ֵ����:%d",class);
        addr=_SHIFT_SYSPARAS_EEP_ADDR_END+CLASSSIZE*(class-1);
        o24lcxxx_read_bytes_ex(addr, (UINT8*)&cur_class_info[class-1].class_num, sizeof(struct _def_class));
        memcpy(str,(UINT8*)&cur_class_info[class-1].sun_f,8);
        fvrd = atof(str);
        olcm_dispprintf(0,2,"��������%.02f",fvrd);
 //       memset(str,0x00,sizeof(str));
 //       memcpy(str,(UINT8*)&cur_class_info[Cur_class-1].sun_m,10);
 //       fvrm = atof(str);
 //       olcm_dispprintf(0,3,"���۽�%.02f",fvrm); */
     
}
