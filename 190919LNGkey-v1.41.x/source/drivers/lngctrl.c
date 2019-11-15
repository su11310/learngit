/*
 * File:   lngctrl.c
 * Author: jereh
 *
 * Created on 2014_01_15
 */
#include "../includes/global_def.h"

void Gas_para_init(void)
{    UINT8  e = 0;
    CARD_XIAOFEI = 0;
     _CARD_TYPE = 0;
     memset(CN, 0, 10);
     OKgas_GV = 0;
     OKgas_money = 0;
     Rec_Card_PreM = 0;
     Rec_Card_EndM = 0;
     Rec_Card_Preg = 0;
     Rec_Card_Endg = 0;
     Rec_Sum_Start = 0;
    Rec_Sum_End = 0;
    Rec_Begin_Press = 0;
    Rec_End_Press = 0;
    memset(GAS_Stime, 0, 6);
    memset(GAS_Etime, 0, 6);
   GasBegin = 0;
   Graybegain = 0;
   GasCo=0;
   send_sj_flag=0;
   GAS_MustStop_Err = 0;
     FIX_RecOK = 0;
     SendStop_False = 0;
     IS_GUANLI_CARD_GAS = 0;//150730
      _gas_run_flag = FALSE;               //ss190218
     ////////////////wzw150518
     for(e=0;e<=Add_Gas_CS;e++)
     { Every_add_Gas[e] = 0;
     }
    Add_Gas_CS = 0;
    Pre_vol_add = 0;
    memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ
}



void deg_operate_save_begi(void)    //150730   150801  ��ʼ����Ϊ��������
{   UINT8   saveCN[8];
    UINT16  addr;
    UINT8 kmm = 100;

               deg_oparme.deg_cor_id = MAX_dubug_recid_num + 1;//������ˮ��
                memcpy(saveCN, (UINT8*)(&CN[2]), 8);//ֻ����8λ
                deg_oparme.deg_card_id = (UINT32)atoi(saveCN);//4����
                deg_oparme.deg_voluent = 0;//��ʼ����Ϊ0
          ortcc_read_time(deg_oparme.opera_rec_Time); //qaz  150729

          addr = DEBUG_RECORD_SAVE + MAX_dubug_recid_num*16;

    o24lcxxx_write_bytes_ex(addr,(UINT8*)&deg_oparme,sizeof(debugcord_parme));
     MAX_dubug_recid_num++;

     while(kmm--)
       {
         if ( TRUE == o24lcxxx_write_bytes_ex(DEBUG_RECORD_MAXNUM,&MAX_dubug_recid_num,1))    //1121
             {
               break;
             }

        }

//   memset((UINT8*)&deg_oparme, 0, sizeof(debugcord_parme));

}

void deg_operate_save_gasing(float GVV)    //150730   150801  ֻ�Ǳ�������
{
    UINT16  addr;
    float Debug_save_vol;
    addr = DEBUG_RECORD_SAVE + (MAX_dubug_recid_num-1)*16;  //�˴�ע�⣬�Ϳ�ʼ���治һ������ʼ������Ѿ�������
   Debug_save_vol = GVV;
  o24lcxxx_write_bytes_ex(addr+offsetof(struct debugcord_parme,deg_voluent),(UINT8*)&Debug_save_vol,4);

}

void deg_operate_save_end(void)    //150730   150801  ֻ�Ǳ����������
{
    UINT16  addr;
    float Debug_save_vol;
    addr = DEBUG_RECORD_SAVE + (MAX_dubug_recid_num-1)*16;  //�˴�ע�⣬�Ϳ�ʼ���治һ������ʼ������Ѿ�������
   Debug_save_vol = OKgas_GV;
  o24lcxxx_write_bytes_ex(addr+offsetof(struct debugcord_parme,deg_voluent),(UINT8*)&Debug_save_vol,4);

   memset((UINT8*)&deg_oparme, 0, sizeof(debugcord_parme));


}

BOOL olng_operate_fixv(float *fix_money)
{
    float fix_voluent;
    UINT8 vkey = 0;
    UINT8 len = 0;
    UINT8 car_status;
    INT8  str[20] = {0};
// /   UINT16 zkk;
    float price_x;
    switch (Pr_gr)
    {
     case 1:price_x=PRICE;
            break;
     case 2:price_x=PRICE2;
            break;
     case 3:price_x=PRICE3;
            break;
     case 4:price_x=PRICE4;
            break;
     case 5:price_x=PRICE5;
            break;
     case 6:price_x=PRICE6;
            break;
     case 7:price_x=PRICE7;
            break;
     case 8:price_x=PRICE8;
            break;
     case 9:price_x=PRICE9;
            break;
     case 10:price_x=PRICE10;
            break;
     default:
            price_x=PRICE;
            break;
    }
     //       zkk=(Discount[0]<<8)+Discount[1];

    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    ��������");
   
 while(1)
  {   
     if((WKJQ == 0)&&((_CARD_TYPE == 2) || (_CARD_TYPE == 3)|| (_CARD_TYPE == 5))||(WKJQ ==1))                                             //ss190409      (Operate_fixm != 0)||
       {
           car_status = machine_status_card();                          //�����жϿ��Ƿ񱻰ε����ж�    ss190409  
            if(car_status!=CPU_TYPE_A)//���ε���
            {
                 eVirtualKey = _KEY_EXIT_EV_;
                 return FALSE;
            }
       }
     
     olcm_dispprintf(0,2,"��������:       ");
     cursor_x = 5;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
    if(vkey == _KEY_EXIT_EV_ )
    {
      eVirtualKey = _KEY_EXIT_EV_;
      return FALSE; //�˳���
    }

    if( vkey == _KEY_OK_EV_ && len>0)
    { fix_voluent = atof(str);
 //    *fix_money = fix_voluent*PRICE;
 //   Cur_Price=price_x*zkk/100;
     *fix_money = fix_voluent*price_x*Discounf/100;
     if(*fix_money <9999)
        return TRUE;
    }
  }
}


BOOL olng_operate_fixm(float * fix_money)
{   
   
    UINT8 vkey = 0;
    UINT8 len = 0;
    UINT8 car_status;
    INT8  str[20] = {0};
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    �������");
    
  while(1)
  {   
      if((WKJQ == 0)&&((_CARD_TYPE == 2) || (_CARD_TYPE == 3)|| (_CARD_TYPE == 5))||(WKJQ ==1))                                             //ss190409      (Operate_fixm != 0)||
       {
           car_status = machine_status_card();                          //�����жϿ��Ƿ񱻰ε����ж�    ss190409  
            if(car_status!=CPU_TYPE_A)//���ε���
            {
                 eVirtualKey = _KEY_EXIT_EV_;
                 return FALSE;
            }
       }
      
      olcm_dispprintf(0,2,"�������:       ");
      cursor_x = 5;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
    if(vkey == _KEY_EXIT_EV_ )
    {
      eVirtualKey = _KEY_EXIT_EV_;
      return FALSE; //�˳���
    }
  
    if( vkey == _KEY_OK_EV_ && len>0)
    {
       
        *fix_money = atof(str);
        if(*fix_money <9999)
        return TRUE;
    }
  }
}

BOOL get_price(float *PRICE_, UINT8 *qiang) 
{
    //    UINT8 qid;float temp;float price;float gas_delay ;
    //    float gain;float ls;float yl;float aqyl;float zeroyl;float ylxs;float Density_up;float Density_do;float ylys;float RefVol;
    //  //if(TRUE != qty_get_sys(qid,temp,price,Density ,gain,ls ,yl,aqyl,Density_up ,Density_do,ylys))
    //   float glbh;
    //   float lspd;
    SYSTEMPARA systempara; //Mengfr 20161111
    //    if(TRUE != qty_get_sys((UINT8 *)&qid,(float *)&price,(float *)&temp,(float *)&gain,(float *)&ls ,(float *)&aqyl,(float *)&zeroyl,(float *)&ylxs,(float *)&Density_up ,(float *)&Density_do,(float *)&ylys,(float *)&gas_delay,(float *)&RefVol,(float *)&glbh,(float *)&lspd))
    if (TRUE != qty_get_sys(&systempara)) //Mengfr 20161111
    {
        //ͨ���쳣
        SOEACTION1(PRO422_ERR, eCurRunState);
        return FALSE;
    }
    //    *PRICE_ = price;
    //    *qiang = qid;
    *PRICE_ = systempara.price; //Mengfr 20161111
    *qiang = systempara.qid; //Mengfr 20161111
    return TRUE;
}
/***************************************************
 *   ss190306  ���ûҲ���   
 *   Ϊ������ɽ��ʧ�ܺ� �ٴ�ǿ��д�����״̬
 **************************************************/
BOOL IC_card_put_grey_status(void)
{
    UINT8 j=3;
    
    while (j) 
    {
        
        if (TRUE == ic_card_put_status(CARDS_GREY))              //�û�RG160601
        {
            UINT8 grey_state;
            grey_state = ic_card_get_status_nosel();            // �ٴλ�ȡ�û�״̬ 
            if (grey_state == CARDS_GREY)                       // �û���ɺ� ��ȡ��״̬�ٴ��ж��û��Ƿ�ɹ�
            {
                break;
            }

        }
        delay_ms(50);
        j--;
    }
    if (j <= 0) 
    {

//        SOEACTION1(huicar_err, eCurRunState);                    // �û�ʧ�� �쳣��ʾ
        return FALSE;
    }
    return TRUE;
}
void olng_LNG_Operate(void)
{
//    BOOL SwPage = TRUE; //WZW 20150603
    BOOL SwPage = FALSE;; //WZW 20150603
    UINT8 len1 = 6;
     UINT8 lenx ;//150730wzw
    UINT8  *pinfo;
   UINT8  *GUANLpinfo; //150730
    UINT8 CARTYPE,XXH;
    UINT8 *gpyx,pjyx[4],men[20],i;//150813
    INT8  j;
    float fix_money;
    float max_money;
    float aaa,bbb;

    float GV; float AM;float gain;float ls;float temp;float backgas;UINT8 isgasOK;

    float desenty,press;
    UINT8 REC_START,_station;
    BOOL Rec_GasRun;
    UINT32 ecc_tick = 0;//ͨ�ų�ʱ��
    UINT8 ds;//rg170323
    UINT8 eccSW =0;
    UINT8 rdkey =0;
    UINT8 *qpx;//rg170608 ��Ʒѡ��
    UINT8 *cp;//rg170607 ������Ϣ���ƺ�
    UINT8 car_status;//RG170705
    UINT8 carzl;//rg170717
    car_status=0;//rg170705
    if(QX_OVER==1)//rg160726
    {
	olcd_clearsCreen();
    SOEACTION1(QxOver,eCurRunState);//RG190705
//        olcm_dispprintf(0,1,"�����������ޣ�");
//	olcm_dispprintf(0,2,"�޷�������");
//	olcm_dispprintf(0,3,"�뾡����ϵ����");    
	osys_getkey(_KEY_NULL_,500);
        eVirtualKey = _KEY_EXIT_EV_;
        return;    
    }
if(GasBegin !=1)//����ǿ�ʼ������,�Ͳ�ִ�����²����ˣ������Ѿ�����ʱ��Ϳ���Ϣ�ˣ�
 {
    if(HUAIKUAI==TRUE)
    {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"�洢��������");
        olcm_dispprintf(0,2,"  �뾡�����");
        osys_getkey(_KEY_NULL_,500);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
      }
       olcd_clearsCreen();
 //       olcm_dispprintf(0,1,"�������Ե�...");
		card_info_len = sizeof(global_ic_card_info);//rg170705
	memset(global_ic_card_info, 0, card_info_len);//rg170705
	car_status = machine_status_card();//rg170705
	if(car_status == HAVE_CARD)
		{
			olcm_dispprintf(0, 1, "  �������쳣    ");
				olcm_dispprintf(0, 2, "    ����      ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
		}
	else if (car_status > NO_CARD)//rg170705 �жϿ��Ƿ���Ч
		{
			if (car_status == CPU_TYPE_A) {
				olng_operate_card_info(); //150730
				if (WKJQ == 0) {
					GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
					if (GUANLpinfo == NULL) {
						olcm_dispprintf(0, 1, "  ��Ч��    ");
						olcm_dispprintf(0, 2, "  �뻻������  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					} else if ((memcmp(GUANLpinfo, "40000002", lenx) != 0)&&(memcmp(GUANLpinfo, "40000003", lenx) != 0)&&(memcmp(GUANLpinfo, "40000001", lenx) != 0)&&(memcmp(GUANLpinfo, "40000024", lenx) != 0)&&(memcmp(GUANLpinfo, "40000005", lenx) != 0))//rg170717
					{
						olcm_dispprintf(0, 1, "  ��Ч��    ");
						olcm_dispprintf(0, 2, "  �����²忨  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			} else {
				olcm_dispprintf(0, 1, "  ��Ч��    ");
				olcm_dispprintf(0, 2, "  �����²忨  ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
			}
		}
       ////////////////////////////����ʶ��//////////////
    //   olng_operate_card_info(); //150730
       		if (WKJQ == 1)//rg170531�޿�����
		{
			if (dkpd != APDUS_SUCCESS)//rg170531�޿�����
			{
				switch (dkpd) {
				case APDUS_NO_CARD:
						olcm_dispprintf(0, 1, "  ����Ϣ��ѯ    ");
						olcm_dispprintf(0, 2, "���Ȳ忨���ٲ�ѯ");
						olcm_dispprintf(0, 3, "  лл����      ");
						break;
				case APDUS_FAILE:
						olcm_dispprintf(0, 1, "  ����Ϣ��ѯ");
						olcm_dispprintf(0, 2, "����ʧ��!!");
						SOEACTION1(ICCARD_READ_ERR, eCurRunState);
					break;
				case APDUS_DKQERR:
						olcm_dispprintf(0, 1, "  ����Ϣ��ѯ");
						olcm_dispprintf(0, 2, "����������!!");
						SOEACTION1(DKQ_GREY_ERR, eCurRunState);
					break;
				default:
					break;
				}
				dkpd = 0;
				osys_getkey(_KEY_NULL_, 200);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
			}
		}
//*********************//rg180416 �жϰ����**************************************************//
		UINT8 *TNfo;
		UINT8 len, worTn;
		UINT8 Tinfo[4];
		GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
		if (GUANLpinfo != NULL) {
			if (WKJQ == 1) {
				if (memcmp(GUANLpinfo, "40000001", lenx) == 0) {

					TNfo = ic_operate_info("TN", global_ic_card_info, &lenx); //2. group class  number
					memset(Tinfo, 0, sizeof(Tinfo));
					memcpy(Tinfo, TNfo, lenx);
					worTn = atoi(Tinfo);

					if (worTn != ReadTn) {
						olcm_dispprintf(0, 2, "���󣺽�ֹ����");
						olcm_dispprintf(0, 3, "��屾���鿨����");
						osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			}
		}
//*********************//rg180416 �жϰ����END**************************************************//		
//*********************//rg170608 ��Ʒѡ��**************************************************//	
	qpx = ic_operate_info("QPX", global_ic_card_info, &lenx);
	if (qpx != NULL)
	{
            if(memcmp(qpx, "2", lenx) == 0)
            {
                olcm_dispprintf(0, 2, "���󣺴�ΪCNG ��");
                olcm_dispprintf(0, 3, "�뻻������������");
 		osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;	
            }
	}
//**********************//rg170608 ��Ʒѡ�� end*************************************************//	
 	GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
	if(WKJQ == 1)//rg170531�޿�����
	{
            if (GUANLpinfo == NULL)
            {
                olcm_dispprintf(0, 2, "���󣺽�ֹ����");
                olcm_dispprintf(0, 3, "��忨������");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }
	}
	else
	{
            if (GUANLpinfo == NULL)
            {
                CARD_XIAOFEI = 2;//���˽��
                _CARD_TYPE = 1;
                memcpy(CN,cure_JQ_card,10);
                memcpy(CPH,CPH_IN,10);
                memset(GPBH,0x0,16);
                Rec_Card_PreM_int=0;
                Rec_Card_Preg_int=0;	
                Cur_Price= PRICE;
                Discounf=100.0;
                car_prem=Rec_Card_PreM;
                car_prel=Rec_Card_Preg;	
            }	
	}
//	if(memcmp(GUANLpinfo, "40000024", 8) == 0)// ����  rg170531�޿�����
	if(GUANLpinfo != NULL)
	{
            UINT8 Type_date;
            Type_date = str_chan_u8(GUANLpinfo);                                   // ������ת��
            gas_record.gas_start_way = Type_date;                                 // ������¼     ������������ 
        if(memcmp(GUANLpinfo, "40000024", lenx) == 0)// ����  150730wzw  
        {
            if (Is_debuggas_Read == 1) //����Ϊ�����������
            {
                olcm_dispprintf(0, 1, "�������Ե�...   ");
                if (MAX_dubug_recid_num >= 200) //150730
                {
                    olcd_clearsCreen();
                    olcm_dispprintf(0, 1, "     ����    ");
                    olcm_dispprintf(0, 2, "���Լ����Ѵ�����");
                    olcm_dispprintf(0, 3, "���ܼ������Լ���");
                    osys_getkey(_KEY_NULL_, 300);
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                else
                {
                    IS_GUANLI_CARD_GAS = 1; //�жϱ��������
                    _CARD_TYPE = CARDT_ADMINI; //�������淢�͸�����150730wzw
                    CARD_XIAOFEI = ACCOUNT_MONEY; //������150730wzw
                }


                GUANLpinfo = ic_operate_info("CN", global_ic_card_info, &lenx);
                if (GUANLpinfo == NULL)
                {
                        olcm_dispprintf(0, 2, "���󣺽�ֹ����");
                        olcm_dispprintf(0, 3, "�뻻������������");
			osys_getkey(_KEY_NULL_, 300);
                        eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                memset(CN, 0, sizeof (CN));
                memcpy(CN, GUANLpinfo, lenx);
            } //��������������Լ���
            else //����δ����
            {
                    olcm_dispprintf(0, 1, "      ����      ");
                    olcm_dispprintf(0, 2, "�������������");
                    olcm_dispprintf(0, 3, "������������Ϳ�");
                    olcm_dispprintf(0, 4, "      лл!     ");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }

        } //END OF ����

            //////////////////////////////////////////////////////////////////
 //       else if(memcmp(GUANLpinfo, "40000001", lenx) == 0)//���������ǹ���  150730wzw
	else
        {
            if (Is_debuggas_Read == 0) //�����������ã��������������
            {
                 olcm_dispprintf(0, 1, "�������Ե�...   ");
                 gpyx = ic_operate_info("BCAVD", global_ic_card_info, &lenx); //150813
                if (gpyx != NULL)
                {
                    memset(men, 0, 10);
                    memset(pjyx, 0x00, 4);
                    memcpy(men, gpyx, lenx);

                    for (i = 0; i < 2; i++)
                    {
                        pjyx[i] = ((men[2 * i] - 0x30) << 4)+(men[2 * i + 1] - 0x30);
                    }
                    pjyx[2] = ((men[5] - 0x30) << 4)+(men[6] - 0x30);
                    pjyx[3] = ((men[8] - 0x30) << 4)+(men[9] - 0x30);

                    if (Get_Gp_Time(pjyx) <= 1800)//�жϸ�ƿ����
                    {
                        olcd_clearsCreen();
                            olcm_dispprintf(1, 1, "��ƿ����    ");
                            olcm_dispprintf(1, 2, "�޷�����      ");
                            olcm_dispprintf(1, 3, "�����������  ");
                        osys_getkey(_KEY_NULL_, 300);
                        eVirtualKey = _KEY_EXIT_EV_;
                        return;
                    }
                }
		//************************//rg170607 ������Ϣ���ƺ�*****************************************************************//	
	cp = ic_operate_info("CBH", global_ic_card_info, &lenx);//���ƺ�
                                if(cp==NULL)
                                {
					if(Cp_flag==1)
					{
					memcpy(CPH,CPH_IN,12);
					}
					else
					memset(CPH,0x0,12);
                                }
                                else
                                {
                                memcpy(CPH,cp,lenx);
                                }
//************************//rg170607 ������Ϣ���ƺ�  END*****************************************************************//		

                    olcm_dispprintf(0, 1, "���ڶ���...");
                if (TRUE != get_car_info())
                    //            if(TRUE == ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity,CPBH,GPBH))//��ÿ���Ϣ
                {
                    SOEACTION1(ICCARD_READ_ERR, eCurRunState); //������Ϣ����
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
		else//rg170531�޿�����
		{
			GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
			if((memcmp(GUANLpinfo, "40000001", lenx) == 0)&&(WKJQ == 0))//rg170531�޿�����
			{
				CARD_XIAOFEI = 2;//���˽��
				_CARD_TYPE = 1;
				memcpy(CN,cure_JQ_card,10);
				memcpy(CPH,CPH_IN,10);
				memset(GPBH,0x0,16);
				 Rec_Card_PreM_int=0;
				Rec_Card_Preg_int=0;	
				Cur_Price= PRICE;
				 Discounf=100.0;
				 car_prem=Rec_Card_PreM;
				car_prel=Rec_Card_Preg;	
			}
//*************************************//RG170717**********************************************//			
			if((memcmp(GUANLpinfo, "40000005", lenx)== 0)&&(_CARD_TYPE == CARDT_SMALL)) 
			{
			//���̨Ҫ���������	
			      if(Get_ZiCard_info(CN,&carzl,&Rec_Card_PreM_int,&Rec_Card_PreM)==TRUE)
			      {
				    if(carzl==0)
				      {
					      car_prem=Rec_Card_PreM;
						car_prel=0;
						Rec_Card_Preg_int=0;
				      }
				      else if(carzl==1)
				    {
					     olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "  ������ע��    ");
					     olcm_dispprintf(0, 2, "  ���ɼ���      ");
					     olcm_dispprintf(0, 3, "  �뻻��        ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else if(carzl==2)
				    {
					     olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "  ������Ƚ���  ");
					     olcm_dispprintf(0, 2, "��������ͬʱ����");
					     olcm_dispprintf(0, 3, "  ��ȴ�....    ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else 
				    {
					    olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "�ӿ�״̬����  ");
					     olcm_dispprintf(0, 2, "  ���ܼ���    ");
					     olcm_dispprintf(0, 3, "  �뻻��      ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
			      }
			      else
			      {
				   olcd_clearsCreen();
					olcm_dispprintf(1, 2, "�޷���ȡ�����    ");
					olcm_dispprintf(1, 3, "�޷�����      ");
				       osys_getkey(_KEY_NULL_, 300);
				    eVirtualKey = _KEY_EXIT_EV_;
				    return;
			      }
			}
//*********************************************************************************//			
		}
            }
            else //���������������ʱ��������������
            {
                olcm_dispprintf(0, 1, "      ����      ");
                olcm_dispprintf(0, 2, "��������࿨����");
                olcm_dispprintf(0, 3, "���������");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }


        } //end of esle(������)
	}
    else if(WKJQ == 0)
    {
            gas_record.gas_start_way = CARD_OPERATION;                                // �޿�������ʽ��λ     ������¼ 
    }
        
        if((gass_class==1)&&(_CARD_TYPE==1))
        {
         olcd_clearsCreen();
	olcm_dispprintf(0,2,"���󣺽�ֹ����");
        olcm_dispprintf(0,3,"�뻻������������");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }

               if((((fabs(Rec_Card_PreM))>=950000)||((fabs(Rec_Card_Preg))>=950000))&&(_CARD_TYPE==1))
        {
           olcd_clearsCreen();
        olcm_dispprintf(0,2,"���󣺿��೬��");
        olcm_dispprintf(0,3,"���Ƚ����ټ�����");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }
      if(Get_zk()==0)//�ж��ۿ� 150901 rg
        {
          if(_CARD_TYPE != CARDT_ADMINI)
          {
           olcd_clearsCreen();
          olcm_dispprintf(1,1,"  �����쳣    ");
          olcm_dispprintf(1,2,"���˳���������");
           osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
          }
          else
          {
            Cur_Price=PRICE;   
          }
        } 

     if(olngctrl_juPSW(&XXH)==FALSE)
    {
        switch(XXH)
        {
        case 1:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"��Ч��        ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
  /*  150730wzw    case 2:     olcm_dispprintf(0,1,"  ���쳣        ");
                    olcm_dispprintf(0,3,"���������ܼ���");
                    break;*/
        case 3:     olcm_dispprintf(0,1,"  ���쳣      ");
                    olcm_dispprintf(0,3,"�ҿ������ܼ���");
                     break;
        case 8:     olcm_dispprintf(0,1,"  ���쳣      ");
                    olcm_dispprintf(0,3,"ע���������ܼ���");
                     break;
        case 6:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"�������      ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
         case 10:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"ͨѶ����      ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
        case 12:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"���󿨣����ܼ���");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
        case 13:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"��������      ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
	//rg170717	    
	 case 14:     olcd_clearsCreen();
                    olcm_dispprintf(0,1,"��˾ĸ�����ܼ���");
                    olcm_dispprintf(0,2,"���˳����²���  ");
                    break;	    
          default:break;
        }

        if(_CARD_TYPE != CARDT_ADMINI)  //�޳�����150730WZW
        {
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
         }
    }
#if 0
    if(TRUE != ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&mlc,&glc,&CARD_XIAOFEI))//��ÿ���Ϣ
             {
              SOEACTION1(ICCARD_READ_ERR,eCurRunState);     //������Ϣ����
                 return;
             }
#endif
            Get_gas_money();

            {  rdkey = ostatemachine_getkey();  //�Ƿ���ֹͣ����
               b_keyv = FALSE;
               if(_KEY_STOP_EV_ == rdkey)
               {eVirtualKey = _KEY_EXIT_EV_;
                 return;
               }
                if(_KEY_EXIT_EV_ == rdkey)
               {
                    eVirtualKey = _KEY_EXIT_EV_;
                 return;
               }
             }
  //       Mainui_Disp_Cardinfo(_CARD_TYPE,CN,car_prem,Rec_Card_Preg,CARD_XIAOFEI);//���Ϊ�����ܿ�����
          _station = (CN[0]-0x30)*10+(CN[1]-0x30);
             if(_station != Cur_StationNo)
             {  
                 if(_CARD_TYPE == 1)
                 {
                    olcd_clearsCreen();         // ss190904   ��վ�İ��鿨�����Լ���    
                    olcm_dispprintf(0,1,"    ��ʾ");
                    olcm_dispprintf(0,2,"����վ�����ɼ���");
                    osys_getkey(_KEY_NULL_,200);
                    eVirtualKey = _KEY_EXIT_EV_;
                   return;
                 }
//                 olcd_clearsCreen();
//                olcm_dispprintf(0,1,"  �˿��Ǳ�վ��");
//                olcm_dispprintf(0,2,"���Եȣ�");
//                olcm_dispprintf(0,3,"���ڵȴ���̨��֤");

             }
	if((WKJQ == 0)&&(_CARD_TYPE == 1))//rg170531�޿�����
	REC_START = Check_Card_info(cure_JQ_card, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);//rg170531�޿�����
	else
	REC_START = Check_Card_info(CN, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);	
    if(1!= REC_START )//����ֵ��1��0,2Ϊ������,3Ϊ��ؿ��ɼ�����4Ϊ��ؿ����ɼ���,5Ϊ����ֹͣ���˳���6Ϊ�ѻ�״̬����վ�����ɼ���
     { 

        if(0 == REC_START )
               {//ͨ���쳣
                // SOEACTION1(31,eCurRunState);
//                olcd_clearsCreen();
//                olcm_dispprintf(0,1,"����Ϣ�쳣");
//                olcm_dispprintf(0,2,"�����²���");
            SOEACTION1(PRO422_ERR,eCurRunState);
                eVirtualKey = _KEY_EXIT_EV_;
                  return;
              }
            else if(2  == REC_START )
                {//�ڿ�
                   olcd_clearsCreen();
                   olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"�ÿ�Ϊ��ʧ����");
                   osys_getkey(_KEY_NULL_,200);
                   eVirtualKey = _KEY_EXIT_EV_;
                  return;
              }
            else if(3  == REC_START )
                {//��ؿ��ɼ���
//                   olcd_clearsCreen();
//                   olcm_dispprintf(0,1,"    ��ʾ");
//                   olcm_dispprintf(0,2,"����վ���ɼ���");
//                   olcm_dispprintf(0,3,"���ڼ���....");

              }
            else if(4  == REC_START )
                {//��ؿ��ɼ���
                   olcd_clearsCreen();
                    olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"�ÿ�Ϊ��ʧ����");
                   osys_getkey(_KEY_NULL_,200);
                   eVirtualKey = _KEY_EXIT_EV_;
                  return;
                }
            else if(5 == REC_START )
                {
                  eVirtualKey = _KEY_EXIT_EV_;
                  return;
                }
        else if(6  == REC_START )
            {//��ؿ��ɼ���
               olcd_clearsCreen();
            olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"��������֤ʧ�ܣ�");
             //  olcm_dispprintf(0,3,"���ڼ���....");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_EXIT_EV_;
              return;
          }
	else 
                {
		    olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"�鿨���ɹ�");
		   osys_getkey(_KEY_NULL_,300);
                  eVirtualKey = _KEY_EXIT_EV_;
                  return;
                }
#if 0
     if((CARD_XIAOFEI<2)&&((car_prem<PRICE)||(Rec_Card_Preg<1)))//������������
         {
                    olcd_clearsCreen();
                    olcm_dispprintf(0,1,"������");
                    olcm_dispprintf(0,2,"���ֵ");
                     osys_getkey(_KEY_NULL_,300);
                    eVirtualKey = _KEY_EXIT_EV_;
                      return;
         }
#endif
            }//end of if(1!= REC_START )
 } //end  of if(GasBegin ==1)    
    //////////////////////////////�˴��ֽ�㣬ע��///////////////////////////////////////////////////
#if 0
    if((((_CARD_TYPE==2)||(_CARD_TYPE==3))&&(CARD_XIAOFEI>2))&&((car_prem<PRICE)&&(car_prel<1)))//������ ,���˷�ʽ
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"������");
                olcm_dispprintf(0,2,"���ֵ");
                 if(GasBegin ==1)
                 eVirtualKey = _KEY_ADDGAS_EXIT;//����
                 else
                 eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
                return;
     }
#endif
        if((_CARD_TYPE==CARDT_SMALL)&&(car_prem < smallMini_FD+Mini_Money))//rg181210
    {
         olcd_clearsCreen();
             olcm_dispprintf(0, 1, "������");
            olcm_dispprintf(0, 2, "���ֵ");
          osys_getkey(_KEY_NULL_, 300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
    }
      if((CARD_XIAOFEI==PREE_GASE)&&(Rec_Card_Preg<3))//������������
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"������");
                olcm_dispprintf(0,2,"���ֵ");
                 osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_EXIT_EV_;
                  return;
     }
    if((CARD_XIAOFEI==PREE_MONEY)&&(Rec_Card_PreM<Mini_FD))//�����������
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"������");
                olcm_dispprintf(0,2,"���ֵ");
                 osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_EXIT_EV_;
                  return;
     }
    
     if(((_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL))&&((car_prem<Mini_FD)&&(car_prel<3)))//������ ,���˷�ʽ���������//rg170717 �����ӿ������ж�
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"������");
                olcm_dispprintf(0,2,"���ֵ");
                  osys_getkey(_KEY_NULL_,300);
                 if(GasBegin ==1)
                 eVirtualKey = _KEY_ADDGAS_EXIT;//����
                 else  
                 eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
                return;
     }
    if((Get_again_gas_money(&max_money)==FALSE) &&(_CARD_TYPE != CARDT_ADMINI) )//��ȡ���ͽ��150730wzw,�ų�����
    {
                  olcd_clearsCreen();
                  olcm_dispprintf(0,1,"�����ݴ���");
                  olcm_dispprintf(0,2,"����");
                    osys_getkey(_KEY_NULL_,300);
                   if(GasBegin ==1)
                   eVirtualKey = _KEY_ADDGAS_EXIT;//����
                   else
                   eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
                  return;
    }
    if(GasBegin == 0)
    {
        gas_record.grey_lock_inif.cur_money =  max_money;            //������¼    ����ǰ���  
    }
 
    if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))   //150730WZW
    {
         max_money = -9000;
    }
        //**************************************************************************//
    if(((_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE==CARDT_SMALL))&&(CARD_XIAOFEI == PREE_MONEY))//rg170705//rg170606 //rg170717 �����ӿ������ж�
    {
        if((max_money-Mini_FD)<=0.1)   
        {
            olcd_clearsCreen();
            olcm_dispprintf(0, 1, "������");
            olcm_dispprintf(0, 2, "���ֵ");
            osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_EXIT_EV_;
            return; 
        }
    }
    //*************************************************************************//
// REC_START = Ocompany_Gas_noquan_start(max_money-10);//���ͼ�������,����������������ֹͣ�������ֹͣ��Ҫ������㺯��
 
 //   REC_START = Ocompany_Gas_noquan_start(max_money-10,Pr_gr,Discounf,Cur_Price);
    if((WKJQ == 0)&&(_CARD_TYPE == 1))//rg170531�޿�����
        REC_START = Ocompany_Gas_noquan_start(999999, Pr_gr, Discounf, Cur_Price,CPH,GasBegin);//rg170531�޿�����//rg170607 ������Ϣ���ƺ�
    else if(_CARD_TYPE == CARDT_SMALL)
        REC_START = Ocompany_Gas_noquan_start( max_money - smallMini_FD, Pr_gr, Discounf, Cur_Price,CPH,GasBegin);//rg181210
    else
        REC_START = Ocompany_Gas_noquan_start(max_money - Mini_FD, Pr_gr, Discounf, Cur_Price,CPH,GasBegin);//rg160627//rg170607 ������Ϣ���ƺ� rg170704 ����ʣ5Ԫ//rg170606

    if(1 != REC_START )//!=1��ʾ��0:ͨѶ���� 1:���Լ���2��δԤ��
    {
        if(0  == REC_START )
        {//ͨ���쳣
            SOEACTION1(PRO422_ERR,eCurRunState);
            if(GasBegin ==1)
                eVirtualKey = _KEY_ADDGAS_EXIT;//����
            else                                                                 //ͨ��ʧ�� ���ͽ����Ϣ  sushuai add
            {
    //            OKgas_money = 0;
    //            if (olng_operate_put_card())                                    //���
    //            {
    //                olcm_dispprintf(0, 2, "��ҳɹ�"); //�ۿ�ɹ�����������Ϣ�����ذ�
    //            } 
    //            else {
    //
    //                    olcm_dispprintf(0, 2, "���ʧ��");
    //                    olcm_dispprintf(0, 3, "���̨���");
    //                    osys_getkey(_KEY_EXIT_EV_,300); 
    //                }
                eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
            }               
            return;

        }

        else if(2  == REC_START )
        {
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"δ��Ԥ������");
             olcm_dispprintf(0,2,"�����˳�");
             olcm_dispprintf(0,3,"�ٽ���Ԥ��");
             osys_getkey(_KEY_EXIT_EV_,800);
             if(GasBegin ==1)//����Ѿ���ʼһ��
             eVirtualKey = _KEY_ADDGAS_EXIT;//����
             else  
             eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
              return;
        }
	else//rg170807  �������������ж�
	{
		 olcd_clearsCreen();
	       olcm_dispprintf(0,1,"����δ��������  ");
	       olcm_dispprintf(0,2,"    �޷�����    ");
	       olcm_dispprintf(0,3,"    ����      ");
	       osys_getkey(_KEY_EXIT_EV_,800);
	       if(GasBegin ==1)//����Ѿ���ʼһ��
	       eVirtualKey = _KEY_ADDGAS_EXIT;//����
	       else  
	       eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
		return;
	}

    }
    else
    {
        UINT8 stop_num;
        gas_record.gas_process |=  GAS_START_SEND_SUCC;                          //   ������¼ ������ʼ����ͳɹ���־
        stop_num = ((gas_record.gas_process & 0x0F)+1);
        if(stop_num >15) stop_num =15;                                          // ֧�����ֹͣ����  15��
        gas_record.gas_process &= 0xF0;                                          //  ���ֹͣ����λ
        gas_record.gas_process |= stop_num ;          
    }
    //rg171011����
    
     /////////////////////////////�û�/rg160602///////////////////////////////////////////////
    if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531�޿�����//rg170717 �����ӿ������ж� �ӿ����û�
    {
  if(GasBegin ==0)  
   {
       if(Graybegain == 0)
            { 
           j=2;
            while(j)
            {
                if(TRUE ==ic_card_put_status(CARDS_GREY))  //�û�RG160601
              {
                    delay_ms(50);//rg170323
		           ds=ic_card_get_status_nosel();//rg170323
			   if(ds==CARDS_GREY)//rg170323
			   {
				   Graybegain = 1;//rg170323
				break;   //rg170323
			   }
              }
		j--;
                delay_ms(50);
            }
//	       osys_getkey(_KEY_EXIT_EV_,900);
            if(j <= 0)
            {
		FIX_RecOK = 1;     
            Car_hui = 1;
            if (TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //����ֹͣ����
            {
		    SendStop_False = 1;
                eVirtualKey = _KEY_ADDGAS_EXIT;
            }    
	     SOEACTION1(huicar_err ,eCurRunState);
	     eVirtualKey = _KEY_ADDGAS_EXIT;
 //           eVirtualKey = _KEY_EXIT_EV_;
 //            osys_getkey(_KEY_EXIT_EV_,200);
             return;
            }
            } 
   }  
    }
    
    ///////////////////////////////////////////////////////////////
////////////////////����Ϊ��������/////////////////////////////////////////
 
olcd_clearsCreen();
olcm_dispprintf(2,1,"���ڼ���");
olng_operate_disp(TRUE,gain,ls,temp);
//GasBegin = 1;//������ʼ
GasCo=1;
Car_hui=0;//0��ʾû�аο�
// Car_Hui_ok=0;
Add_Gas_CS++;   //wzw150518
 UINT8 Save_pre_gasvol =0; //wzw150518
    BOOL Get_Grey_Statu = FALSE;                                                // �����������ٴ��ж��Ƿ�Ϊ�ҿ�
 if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
 {
     deg_operate_save_begi();
 }//150801}
    
if(GasBegin == 0)                                                           //�״μ�����Ҫ�洢
{
    gas_record.grey_lock_inif.grey_status |=  GAS_START_MORMAL;                          // ������¼  ����������ʽ
    WiteRecorInfoOnce(gas_record);                                          // �״ν�������¼��Ϣд�뵽�洢��  ss181213
}
GasBegin = 1; //������ʼ
    while(1)
    {//ѭ����ֻ��STOP�����ܵ����淢��ֹͣ��

        if( send_sj_flag == 1)  //1�붨ʱ����ѯ��
        {
            send_ack_sj(0x99);
            send_sj_flag=0;
            {                                                                   //ѯ������ļ���״̬����
               UINT8 loop_num;
               loop_num = ((gas_record.grey_unlock_inif.grey_status & 0x0F)+1);
               if(loop_num >15) loop_num =15;                                          // ֧�����ֹͣ����  15��
               gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  ���ֹͣ����λ
               gas_record.grey_unlock_inif.grey_status |= loop_num ;          
            }
        }

        {  
            rdkey = ostatemachine_getkey();
            b_keyv = FALSE;
            if (_KEY_STOP_EV_ == rdkey)
            {
                gas_record.gas_stop_way = PRESS_STOP;                  // ������¼   ����ֹͣ����
                break;
            }
            if(_KEY_SW_EV_ == rdkey) SwPage=!SwPage;
        }
        if((WKJQ == 1)||((WKJQ==0)&&(_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//rg170531�޿�����//rg170717 
        { 
            car_status = machine_status_card();
            if(car_status!=CPU_TYPE_A)//���ε���
            {
                gas_record.gas_stop_way = CARD_EXTRACT;                  //  ������¼  �����γ�ֹͣ������ʽ
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"���Ѱγ�!!");
                olcm_dispprintf(0,2,"����ֹͣ");
                FIX_RecOK = 1;
                Car_hui = 1;
                if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //����ֹͣ����
                {
                    gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          // ������¼  ����ֹͣ����ʧ��
                    SendStop_False  =1;
                    break;
                }
                gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                          // ������¼  ����ֹͣ����ɹ�
                eVirtualKey = _KEY_ADDGAS_EXIT;
                return;

            }
        }
               Rec_GasRun = Ocompany_Gas_noquan_run(&GV,&gain,&ls,&temp,&desenty,&press,&backgas,&isgasOK);
                //��
               {
                    rdkey = ostatemachine_getkey();
                    b_keyv = FALSE;
                    if(_KEY_STOP_EV_ == rdkey) 
                    {
                        gas_record.gas_stop_way = PRESS_STOP;                  // ������¼  ����ֹͣ����
                        break;
                    }
                    if(_KEY_SW_EV_ == rdkey) SwPage=!SwPage;
               }
          /* if((Rec_GasRun == FALSE)&&(Car_Hui_ok==1))  //rg160601
          {
               if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //����ֹͣ����
            {
                SendStop_False  =1;
               SOEACTION1(PRO422_ERR,eCurRunState);
         //     if(ecc_tick == DWORDMAX)
               {//ͨ���쳣��Σ�ֱ�ӵ�����״̬
                     olcd_clearsCreen();
                     olcm_dispprintf(0,1,"  ϵͳӲ���쳣");
                     olcm_dispprintf(0,2,"  ��ϵ���  ");

                      Gas_para_init();
                     ///////////////////////////
                    eCurRunState = State_MainUI;
                    eVirtualKey = 0;
                    osys_getkey(_KEY_EXIT_EV_,300);
                    return;
               }
               }
               else
               { Gas_para_init();
 //              olcd_clearsCreen();
 //            olcm_dispprintf(0,1,"  �ûҲ��ɹ�    ");
 //            olcm_dispprintf(0,2,"  ��ϵ���   ");
             SOEACTION1(huicar_err ,eCurRunState);
 //            delay_ms(1000);
             eVirtualKey = _KEY_EXIT_EV_;
             osys_getkey(_KEY_EXIT_EV_,300);
             return; }
          }*/
          if(Rec_GasRun == TRUE)      //����ȷ�������ͷǶ�������isgasok��ֵ������
        {
            ecc_tick = 0;
            gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  ��ռ��������еĲ���ѯ�ʴ���
                if(Save_pre_gasvol==0) //������һ��,Ĭ�ϵ�һ�ν�������Ϊ�ϱ���ͣ��ֵ
                {  if(Add_Gas_CS>1)   //��һ��Every_add_Gas[1]
                        {
                         Every_add_Gas[Add_Gas_CS-1] = GV - Pre_vol_add;
                         Pre_vol_add =  GV;//Pre_vol_add +Every_add_Gas[Add_Gas_CS-1]; //����������ѭ����

                        }
                     Save_pre_gasvol = 1;
                }
              //   Every_add_Gas[Add_Gas_CS] = GV - Pre_vol_add;    //wzw150518
          
                if(isgasOK == 0xFD)//����
                 {    olcd_clearsCreen();
		      olcm_dispprintf(1,1,"�������");//�����Զ��ﵽ�����ֹͣ
                      olcm_dispprintf(1,2,"�������");//
                      FIX_RecOK = 1;
                    gas_record.gas_stop_way = MONEY_ALL;                  // ������¼  �������ֹͣ����
                      eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ�
                    return;
                  }
                else if(isgasOK == 0xD0)                                         //  ss20190102 �û�ʧ��  ֱ���˳�  
                {    
                    olcd_clearsCreen();
                    olcm_dispprintf(2,1,"�û�ʧ��");//�����Զ�ֹͣ
                    olcm_dispprintf(2,2,"�����²忨");//�����Զ�ֹͣ
                    osys_getkey(_KEY_EXIT_EV_,300); //�������ذ���ͣ�������跢��ֹͣ
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                else if(isgasOK == 0xE0)
                {    olcd_clearsCreen();
                     olcm_dispprintf(1,1,"���ٵ���ͣ");
                     olcm_dispprintf(1,2,"���˳�");
                      gas_record.gas_stop_way = VELOCIIY_LOW;                  // ������¼  ���ٵ���ֹͣͣ����
                     osys_getkey(_KEY_EXIT_EV_,300); //�������ذ���ͣ�������跢��ֹͣ
                     eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ����ָ�����󣬿���ѯ���ۼ�
                         return;
                }
                else if(isgasOK > 0)    //�ǵö������ĺ�
                {
                    olcd_clearsCreen();
                    switch(isgasOK)
                      {   case  0xE1:   olcm_dispprintf(1,1,"���ͨ�ų�ʱ"); 
                                       SOEACTION1(PRO422_ERR,eCurRunState);
                                 gas_record.gas_stop_way = COMMUN_TIIMOUT;                  // ������¼  ���ͨ�ų�ʱֹͣ����
                                        break;
                          case  0xE3:   olcm_dispprintf(1,1,"������ͨ�Ŵ���"); 
                                        SOEACTION1(MOD_READNUM_ERR,eCurRunState);
                                gas_record.gas_stop_way = FLOWMETER_ERR;                  // ������¼  ������ͨ�Ŵ���ֹͣ����
                                        break;
                          case  0xE4:   olcm_dispprintf(1,1,"Ԥ�䳬ʱ");
                                gas_record.gas_stop_way = PRECOOL_ERR;                  // ������¼  Ԥ�䳬ʱֹͣ����
                                        break;
                          case  0xE5:  
                               olcm_dispprintf(1,1,"ѹ���쳣");
                               olcm_dispprintf(1,2,"���˳�!!");
                               SOEACTION1(NOPRESSURE_ERR,eCurRunState);
  //160620                             osys_getkey(_KEY_EXIT_EV_,500); //�������ذ���ͣ�������跢��ֹͣ
                                gas_record.gas_stop_way = PRESSURE_ERR;                  // ������¼  ѹ���쳣ֹͣ����
                               eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ����ָ�����󣬿���ѯ���ۼ�
                               return;
                         case  0xE6:
                                olcm_dispprintf(1,1,"�����������");
                                olcm_dispprintf(1,2,"���˳�!!");
                                SOEACTION1(ZDLS_ERR,eCurRunState);
  //160620                             osys_getkey(_KEY_EXIT_EV_,500); //�������ذ���ͣ�������跢��ֹͣ
                                gas_record.gas_stop_way = VELOCITY_HIGH;                  // ������¼  �����������ֹͣ����
                                eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ����ָ�����󣬿���ѯ���ۼ�
                                return;  
			case  0xE8://rg180115
                                olcm_dispprintf(0,1,"�����Ϳ��಻ƥ��");
                               olcm_dispprintf(1,2,"���˳�!!");
	//		       osys_getkey(_KEY_EXIT_EV_,300);
                                 SOEACTION1(KLXKY_ERR ,eCurRunState);
                                 gas_record.gas_stop_way = CARD_BALANCE_FAILL;                  // ������¼  �����Ϳ��಻ƥ��
                              break;        
                    default: olcm_dispprintf(1, 1, "�����쳣");
                     gas_record.gas_stop_way = GAS_UNUSUAL;                  // ������¼  �����쳣ֹͣ����
                     AddSOE(isgasOK);
                        break;
                      }
                  //�������ذ���ͣ�������跢��ֹͣ
                   GAS_MustStop_Err = 1;//�����������ͣ
                   osys_getkey(_KEY_EXIT_EV_,400);
                   eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ�
                   return;
         }
     

         if(SwPage ==FALSE)
             olng_operate_disp(FALSE,gain,ls,temp);
         else
             olng_operate_disp2(FALSE,GV,desenty,press); ///

          if(gTick >Debugasing_rstsave_Tick)  //150801
          {  if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //�ڹ����������ʱ�������ж� MAX_dubug_recid_num  ���ܳ���200���ɼ���
                {
                deg_operate_save_gasing(GV); //150730  150801
                 }
             Debugasing_rstsave_Tick = gTick + 200;
            }

     }/////end  of if(Rec_Pro == TRUE)
          else
          {   
                if(ecc_tick !=0)
                {  
                    if(gTick > ecc_tick)
                    {  
                        GAS_MustStop_Err = 1;     //��ʱδ�յ����˴������ͣ
                        eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ�
                        olcm_dispprintf(0,1,"���̰�3 ��������");
                        osys_getkey(_KEY_EXIT_EV_,200);
                        ecc_tick = DWORDMAX;
                        gas_record.gas_stop_way = TRIPLE_COMMUN_FAILL;                  // ������¼  ����������ֹͣ����
                        break;
                      //  return;
                    }
                }
               else
                   ecc_tick = gTick +600;
          }
        if((gas_record.grey_lock_inif.grey_status & 0x03) ==  GREY_LUCK_SUCC)               //�ٴ��жϻ���״̬  //ss190215
        {
            if(Get_Grey_Statu == FALSE)                            // ���뵽�������̣��ٴ��жϿ��Ƿ�Ϊ�ҿ�
            {
                Get_Grey_Statu = TRUE;

                    if(CARDS_GREY != ic_card_get_status_nosel() )                         // ��ȡ����״̬ 
                    {
                        SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // �����������жϿ���Ϊ�ҿ� ������ʾ
                        gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_FAILL;                          // ������¼   �����������ٴζ�ȡ����״̬   ss190304
                        break;                                                                     // ��ǰ����Ϊ����״̬ �������� 
                    }
                    gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // ������¼   �����������ٴζ�ȡ����״̬

            }
        }
//               if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))
//               {
//       if(Get_Grey_Statu == FALSE)                            // ���뵽�������̣��ٴ��жϿ��Ƿ�Ϊ�ҿ�
//        {
//            Get_Grey_Statu = TRUE;
//
//                if(CARDS_GREY != ic_card_get_status_nosel() )                         // ��ȡ����״̬ 
//                {
//                    SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // �����������жϿ���Ϊ�ҿ� ������ʾ
//                    gas_record.grey_lock_inif.grey_status &=  GREY_GAS_LUCK_FAILL;                          // ������¼   �����������ٴζ�ȡ����״̬  
//                    break;                                                                     // ��ǰ����Ϊ����״̬ �������� 
//                }
//                gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // ������¼   �����������ٴζ�ȡ����״̬
//            
//        }
//               }
               ///////////////////////////////////
  }//end  of while(1)

 if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //����ֹͣ����
     {
         SendStop_False  =1;
        SOEACTION1(PRO422_ERR,eCurRunState);
         gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          //   ������¼ ����ֹͣ����ͳɹ���־ 
       if(ecc_tick == DWORDMAX)
        {//ͨ���쳣��Σ�ֱ�ӵ�����״̬
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"  ϵͳӲ���쳣");
            olcm_dispprintf(0,2,"  ��ϵ���  ");
            gas_record.gas_stop_way = SYS_HARD_FAULT;                  // ������¼  ϵͳӲ���쳣ֹͣ����
            gas_record.gas_stream = 0x00;                              // ������¼   ϵͳӲ���쳣��ˮ�Ÿ� ��ֵ
            ortcc_read_time(gas_record.grey_unlock_inif.time);                    // ������¼   ���ʱ��   �����ڴˣ����ʧ��Ҳ�ǿ��Ի�ȡ���ʱ���
            WiteRecorInfo_AN(gas_record);                                              // ������¼  ��������¼��Ϣд�뵽EEP��
            while(1);                                                            // ϵͳֹͣ���ȴ��ϵ�����
               Gas_para_init();
	       memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
	         memset(CPH,0x0,12);//rg170619 ���복�ƺ�
		Cp_flag=0;//rg170619 ���복�ƺ�
              ///////////////////////////
             eCurRunState = State_MainUI;
             eVirtualKey = 0;
             osys_getkey(_KEY_EXIT_EV_,300);
             return;
        }
    }
    gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                         // ������¼  ����ֹͣ����ɹ�
// eVirtualKey = _KEY_ADDGAS_EXIT;
//    if(gas_record.gas_precool == GAS_PRECOOL_SUCC)             // Ԥ��ɹ� �ſ��Խ��뵽�ۿ�״̬   ss190312  
//    {
        eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ�
//    }
//    else
//    {
//        eVirtualKey = _KEY_EXIT_EV_;//ֱ�ӵ��ۿ�
//        WiteRecorInfo_AN(gas_record);                              //ss190213  // ������¼  ��������¼��Ϣд�뵽EEP��
//    }
    return;

}


void olng_start_act(void)
{    BOOL SwPage = FALSE;
    float GV; float AM;float gain;float ls;float temp;float backgas;UINT8 isgasOK;
 //   float mlc,glc,car_prem,car_prel;
    float press,desenty;
    float RepGV = 0; //�ϴ�GV
    float carpre;
    UINT8 RecGverr = 0;
     UINT8 *gpyx,pjyx[4],men[20],i;//150813
     INT8  j;
    UINT8 REC_START,_station,XXH;
    BOOL Rec_Pro;
    UINT8 len1 = 6;
    UINT8  *pinfo;
    UINT8 Car_hui=0;
    UINT8 ds;//rg170323
  //   OKgas_money=0;
    UINT32 ecc_tick = 0;//ͨ�ų�ʱ��
     UINT8 lenx ;//150730wzw
      UINT8  *GUANLpinfo; //150730
    UINT8 eccSW =0;
    UINT8 rdkey =0;
    UINT8 car_status;//RG170705
    UINT8 *qpx;//rg170608 ��Ʒѡ��
    UINT8 *cp;//rg170607 ������Ϣ���ƺ�
    UINT8 carzl;//rg170717
    BOOL Get_Grey_Statu = FALSE;
    car_status = 0;//rg170705
    if(QX_OVER==1)//rg160726
    {
	olcd_clearsCreen();
    SOEACTION1(QxOver,eCurRunState);//RG190705
//        olcm_dispprintf(0,1,"�����������ޣ�");
//	olcm_dispprintf(0,2,"�޷�������");
//	olcm_dispprintf(0,3,"�뾡����ϵ����");    
	osys_getkey(_KEY_NULL_,500);
        eVirtualKey = _KEY_EXIT_EV_;
        return;    
    }
 if(GasBegin != 1)//����ǿ�ʼ������,�Ͳ�ִ�����²�����
 {   if(HUAIKUAI==TRUE)
    {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"�洢��������");
        olcm_dispprintf(0,2,"  �뾡�����");
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
      }
          olcd_clearsCreen();
   //        olcm_dispprintf(0,1,"�������Ե�...");
	  	card_info_len = sizeof(global_ic_card_info);//rg170705
	memset(global_ic_card_info, 0, card_info_len);//rg170705
	car_status = machine_status_card();//rg170705
	if(car_status == HAVE_CARD)
		{
			olcm_dispprintf(0, 1, "  �������쳣    ");
				olcm_dispprintf(0, 2, "    ����      ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
		}
	else if (car_status > NO_CARD)//rg170705 �жϿ��Ƿ���Ч
		{
			if (car_status == CPU_TYPE_A) {
				olng_operate_card_info(); //150730
				if (WKJQ == 0) {
					GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
					if (GUANLpinfo == NULL) {
						olcm_dispprintf(0, 1, "  ��Ч��    ");
						olcm_dispprintf(0, 2, "  �뻻������  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					} else if ((memcmp(GUANLpinfo, "40000002", lenx) != 0)&&(memcmp(GUANLpinfo, "40000003", lenx) != 0)&&(memcmp(GUANLpinfo, "40000001", lenx) != 0)&&(memcmp(GUANLpinfo, "40000024", lenx) != 0)&&(memcmp(GUANLpinfo, "40000005", lenx) != 0))//rg170717
					{
						olcm_dispprintf(0, 1, "  ��Ч��    ");
						olcm_dispprintf(0, 2, "  �����²忨  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			} else {
				olcm_dispprintf(0, 1, "  ��Ч��    ");
				olcm_dispprintf(0, 2, "  �����²忨  ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
			}
		}

  /*
        olcm_dispprintf(0,1,"�������Ե�...");
                   if(TRUE !=get_car_info())
 //              if(TRUE != ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity))//��ÿ���Ϣ
             {
              SOEACTION1(kk_r_err,eCurRunState);     //������Ϣ����
              eVirtualKey = _KEY_EXIT_EV_;
              return;
             }

   */
          ////////////////////////////����ʶ��//////////////
       olng_operate_card_info(); //150730
       		if (WKJQ == 1)//rg170531�޿�����
		{
			if (dkpd != APDUS_SUCCESS)//rg170531�޿�����
			{
				switch (dkpd) {
				case APDUS_NO_CARD:
						olcm_dispprintf(0, 1, "  ����Ϣ��ѯ    ");
						olcm_dispprintf(0, 2, "���Ȳ忨���ٲ�ѯ");
						olcm_dispprintf(0, 3, "  лл����      ");
					break;
				case APDUS_FAILE:
						olcm_dispprintf(0, 1, "  ����Ϣ��ѯ");
						olcm_dispprintf(0, 2, "����ʧ��!!");
					SOEACTION1(ICCARD_READ_ERR, eCurRunState);
					break;
				case APDUS_DKQERR:
						olcm_dispprintf(0, 1, "  ����Ϣ��ѯ");
						olcm_dispprintf(0, 2, "����������!!");
					SOEACTION1(DKQ_GREY_ERR, eCurRunState);
					break;
				default:
					break;
				}
				dkpd = 0;
				osys_getkey(_KEY_NULL_, 200);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
			}
		}
//*********************//rg180416 �жϰ����**************************************************//
		UINT8 *TNfo;
		UINT8 len, worTn;
		UINT8 Tinfo[4];
		GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
		if (GUANLpinfo != NULL) {
			if (WKJQ == 1) {
				if (memcmp(GUANLpinfo, "40000001", lenx) == 0) {

					TNfo = ic_operate_info("TN", global_ic_card_info, &lenx); //2. group class  number
					memset(Tinfo, 0, sizeof(Tinfo));
					memcpy(Tinfo, TNfo, lenx);
					worTn = atoi(Tinfo);
					if (worTn != ReadTn) {
						olcm_dispprintf(0, 2, "���󣺽�ֹ����");
						olcm_dispprintf(0, 3, "��屾���鿨����");
						osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			}
		}
//*********************//rg180416 �жϰ����END**************************************************//	
       //*********************//rg170608 ��Ʒѡ��**************************************************//	
	qpx = ic_operate_info("QPX", global_ic_card_info, &lenx);
	if (qpx != NULL)
	{
		if(memcmp(qpx, "2", lenx) == 0)
		{
                olcm_dispprintf(0, 2, "���󣺴�ΪCNG ��");
                olcm_dispprintf(0, 3, "�뻻������������");
		osys_getkey(_KEY_NULL_, 300);	
            eVirtualKey = _KEY_EXIT_EV_;
            return;	
		}
	}
//**********************//rg170608 ��Ʒѡ�� end*************************************************//
    GUANLpinfo = ic_operate_info("CDT",global_ic_card_info, &lenx);
	if(WKJQ == 1)//rg170531�޿�����
	{
	if (GUANLpinfo == NULL)
        {
                olcm_dispprintf(0, 2, "���󣺽�ֹ����");
                olcm_dispprintf(0, 3, "��忨������");
		osys_getkey(_KEY_NULL_, 300);	
            eVirtualKey = _KEY_EXIT_EV_;
            return;
        }
	}
	else
	{
		if (GUANLpinfo == NULL)
        {
				CARD_XIAOFEI = 2;//���˽��
				_CARD_TYPE = 1;
				memcpy(CN,cure_JQ_card,10);
				memcpy(CPH,CPH_IN,10);
				 Rec_Card_PreM_int=0;
				Rec_Card_Preg_int=0;	
				Cur_Price= PRICE;
				 Discounf=100.0;
				 car_prem=Rec_Card_PreM;
				car_prel=Rec_Card_Preg;	
        }	
	}
//if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531�޿�����
//{
	if(GUANLpinfo != NULL)
	{
            UINT8 Type_date;
            Type_date = str_chan_u8(GUANLpinfo);                                   // ������ת��
            gas_record.gas_start_way = Type_date;                                 // ������¼     ������������ 
        if(memcmp(GUANLpinfo, "40000024", lenx) == 0)// ����  150730wzw  
        {
            if (Is_debuggas_Read == 1) //����Ϊ�����������
            {
                    olcm_dispprintf(0, 1, "�������Ե�...   ");
                if (MAX_dubug_recid_num >= 200) //150730
                {
                    olcd_clearsCreen();
                        olcm_dispprintf(0, 1, "     ����    ");
                        olcm_dispprintf(0, 2, "���Լ����Ѵ�����");
                        olcm_dispprintf(0, 3, "���ܼ������Լ���");
                    osys_getkey(_KEY_NULL_, 300);
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                else
                {
                    IS_GUANLI_CARD_GAS = 1; //�жϱ��������
                    _CARD_TYPE = CARDT_ADMINI; //�������淢�͸�����150730wzw
                    CARD_XIAOFEI = ACCOUNT_MONEY; //������150730wzw
                }


                GUANLpinfo = ic_operate_info("CN", global_ic_card_info, &lenx);
                if (GUANLpinfo == NULL)
                {
                        olcm_dispprintf(0, 2, "���󣺽�ֹ����");
                        olcm_dispprintf(0, 3, "�뻻������������");
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                memset(CN, 0, sizeof (CN));
                memcpy(CN, GUANLpinfo, lenx);
            } //��������������Լ���
            else //����δ����
            {
                     olcm_dispprintf(0, 1, "      ����      ");
                    olcm_dispprintf(0, 2, "�������������");
                    olcm_dispprintf(0, 3, "������������Ϳ�");
                    olcm_dispprintf(0, 4, "      лл!     ");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }

        } //END OF ����

            //////////////////////////////////////////////////////////////////
 //       else if(memcmp(GUANLpinfo, "40000001", lenx) == 0)//���������ǹ���  150730wzw
	else
        {
            if (Is_debuggas_Read == 0) //�����������ã��������������
            {
                     olcm_dispprintf(0, 1, "�������Ե�...   ");
                gpyx = ic_operate_info("BCAVD", global_ic_card_info, &lenx); //150813
                if (gpyx != NULL)
                {
                    memset(men, 0, 10);
                    memset(pjyx, 0x00, 4);
                    memcpy(men, gpyx, lenx);

                    for (i = 0; i < 2; i++)
                    {
                        pjyx[i] = ((men[2 * i] - 0x30) << 4)+(men[2 * i + 1] - 0x30);
                    }
                    pjyx[2] = ((men[5] - 0x30) << 4)+(men[6] - 0x30);
                    pjyx[3] = ((men[8] - 0x30) << 4)+(men[9] - 0x30);

                    if (Get_Gp_Time(pjyx) <= 1800)//�жϸ�ƿ����
                    {
                        olcd_clearsCreen();
                            olcm_dispprintf(1, 1, "��ƿ����    ");
                            olcm_dispprintf(1, 2, "�޷�����      ");
                            olcm_dispprintf(1, 3, "�����������  ");
                       osys_getkey(_KEY_NULL_, 300);
                        eVirtualKey = _KEY_EXIT_EV_;
                        return;
                    }
                }
		//************************//rg170607 ������Ϣ���ƺ�*****************************************************************//	
	cp = ic_operate_info("CBH", global_ic_card_info, &lenx);//���ƺ�
                                if(cp==NULL)
                                {
					if(Cp_flag==1)
					{
					memcpy(CPH,CPH_IN,12);
					}
					else
					memset(CPH,0x0,12);
                                }
                                else
                                {
                                memcpy(CPH,cp,lenx);
                                }
//************************//rg170607 ������Ϣ���ƺ�  END*****************************************************************//		

                    olcm_dispprintf(0, 1, "���ڶ���...");
                if (TRUE != get_car_info())
                    //            if(TRUE == ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity,CPBH,GPBH))//��ÿ���Ϣ
                {
                    SOEACTION1(ICCARD_READ_ERR, eCurRunState); //������Ϣ����
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
		else//rg170531�޿�����
		{
			GUANLpinfo = ic_operate_info("CDT",global_ic_card_info, &lenx);
			if((memcmp(GUANLpinfo, "40000001", lenx) == 0)&&(WKJQ == 0))//rg170531�޿�����
			{
				CARD_XIAOFEI = 2;//���˽��
				_CARD_TYPE = 1;
				memcpy(CN,cure_JQ_card,10);
				memcpy(CPH,CPH_IN,10);
				 Rec_Card_PreM_int=0;
				Rec_Card_Preg_int=0;	
				Cur_Price= PRICE;
				 Discounf=100.0;
				 car_prem=Rec_Card_PreM;
				car_prel=Rec_Card_Preg;	
			}
			if((memcmp(GUANLpinfo, "40000005", lenx)== 0)&&(_CARD_TYPE == CARDT_SMALL)) 
			//			if(_CARD_TYPE == CARDT_SMALL)//RG170717
			{
			//���̨Ҫ���������	
			      if(Get_ZiCard_info(CN,&carzl,&Rec_Card_PreM_int,&Rec_Card_PreM)==TRUE)
			      {
				      if(carzl==0)
				      {
					      car_prem=Rec_Card_PreM;
						car_prel=0;
						Rec_Card_Preg_int=0;
				      }
				      else if(carzl==1)
				    {
					     olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "  ������ע��    ");
					     olcm_dispprintf(0, 2, "  ���ɼ���      ");
					     olcm_dispprintf(0, 3, "  �뻻��        ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else if(carzl==2)
				    {
					     olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "  ������Ƚ���  ");
					     olcm_dispprintf(0, 2, "��������ͬʱ����");
					     olcm_dispprintf(0, 3, "  ��ȴ�....    ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else 
				    {
					    olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "�ӿ�״̬����  ");
					     olcm_dispprintf(0, 2, "  ���ܼ���    ");
					     olcm_dispprintf(0, 3, "  �뻻��      ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
			      }
			      else
{
								olcd_clearsCreen();
								olcm_dispprintf(1, 2, "�޷���ȡ�����    ");
								olcm_dispprintf(1, 3, "�޷�����      ");
								osys_getkey(_KEY_NULL_, 300);
								eVirtualKey = _KEY_EXIT_EV_;
								return;
			      }
			}
		}
            }
            else //���������������ʱ��������������
            {
                    olcm_dispprintf(0, 1, "      ����      ");
                    olcm_dispprintf(0, 2, "��������࿨����");
                    olcm_dispprintf(0, 3, "���������");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }


        } //end of esle(������)
	}
    else if(WKJQ == 0)
    {
            gas_record.gas_start_way = CARD_OPERATION;                                 // �޿�������ʽ��λ     ������¼ 
    }

         if((gass_class==1)&&(_CARD_TYPE==1))
        {
         olcd_clearsCreen();
        olcm_dispprintf(0,2,"���󣺽�ֹ����");
        olcm_dispprintf(0,3,"�뻻������������");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }
        if(((fabs(Rec_Card_PreM)>=950000)||(fabs(Rec_Card_Preg)>=950000))&&(_CARD_TYPE==1))
        {
           olcd_clearsCreen();
        olcm_dispprintf(0,2,"���󣺿��೬��");
        olcm_dispprintf(0,3,"���Ƚ����ټ�����");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }
        if(Get_zk()==0)//�ж��ۿ� 150901 rg
        {
          if(_CARD_TYPE != CARDT_ADMINI)
          {
            olcd_clearsCreen();
            olcm_dispprintf(1,1,"  �����쳣    ");
            olcm_dispprintf(1,2,"���˳���������");
             osys_getkey(_KEY_NULL_,300);
            eVirtualKey = _KEY_EXIT_EV_;
            return;
          }
          else
          {
            Cur_Price=PRICE;   
          }
        } 
     if(olngctrl_juPSW(&XXH)==FALSE)
    {
        switch(XXH)
        {
       case 1:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"��Ч��        ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
      /*  150730wzw    case 2:     olcm_dispprintf(0,1,"  ���쳣        ");
                    olcm_dispprintf(0,3,"���������ܼ���");
                    break;*/
        case 3:     olcm_dispprintf(0,1,"  ���쳣      ");
                    olcm_dispprintf(0,3,"�ҿ������ܼ���");
                     break;
        case 6:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"�������      ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
        case 8:     olcm_dispprintf(0,1,"  ���쳣      ");
                    olcm_dispprintf(0,3,"ע���������ܼ���");
                     break;
        
         case 10:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"ͨѶ����      ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
        case 12:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"���󿨣����ܼ���");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
        case 13:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"��������      ");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;
		    //rg170717	    
	 case 14:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"��˾ĸ�����ܼ���");
                    olcm_dispprintf(1,2,"���˳����²���");
                    break;	    
          default:break;

        }
     if(_CARD_TYPE != CARDT_ADMINI)  //�޳�����150730WZW
        {
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
     }
    }
#if 0
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
    if(memcmp(pinfo,"40000024",len1) == 0) // class group card
    {
    olcm_dispprintf(0,1,"  ���쳣");
    olcm_dispprintf(0,3,"���������ܼ���");
    osys_getkey(_KEY_EXIT_EV_,300);
    eVirtualKey = _KEY_EXIT_EV_;
    return;
    }
     if(CARDS_GREY==ic_card_get_status())
     {
    olcm_dispprintf(0,1,"  ���쳣");
    olcm_dispprintf(0,3,"�ҿ������ܼ���");
    osys_getkey(_KEY_EXIT_EV_,300);
    eVirtualKey = _KEY_EXIT_EV_;
    return;
     }
#endif
#if 0
      if(TRUE != ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&mlc,&glc,&CARD_XIAOFEI))//��ÿ���Ϣ
      {
           SOEACTION1(ICCARD_READ_ERR,eCurRunState);
           return;
      }
#endif
    Get_gas_money();
    if(GasBegin == 0)              // ����ǰ���   ss181213
    {
        gas_record.grey_lock_inif.cur_money =  car_prem;            //������¼    ����ǰ���  
    } 
    
       {  rdkey = ostatemachine_getkey();  //�Ƿ���ֹͣ����
               b_keyv = FALSE;
               if(_KEY_STOP_EV_ == rdkey)
               {eVirtualKey = _KEY_EXIT_EV_;
                 return;
               }
               if(_KEY_EXIT_EV_ == rdkey)
               {eVirtualKey = _KEY_EXIT_EV_;
                 return;
               }
             }

//	odisp_price(PRICE, TRUE);
//    Mainui_Disp_Cardinfo(_CARD_TYPE,CN,car_prem,car_prel,CARD_XIAOFEI);//��ʾ����Ϣ
    RepInputFixm:
    if(Operate_fixm == 1)//�����
    {
        if(TRUE !=olng_operate_fixm(&FIX_Money))//ͨ����ʾ�������ü������
        {//������ʱ�����˳����������˴���ȥ
            eVirtualKey = _KEY_EXIT_EV_;
            return;
        }
        gas_record.grey_lock_inif.grey_status |=  GAS_START_FIX_M;                          // ������¼  �������
    }
    else if(Operate_fixm == 2)//������
    {
        if(TRUE !=olng_operate_fixv(&FIX_Money))//ͨ����ʾ�����롢����������ü������
        {//������ʱ�����˳����������˴���ȥ
         eVirtualKey = _KEY_EXIT_EV_;
         return;
        }
        gas_record.grey_lock_inif.grey_status |=  GAS_START_FIX_V;                          // ������¼  ��������
    }
    if(FIX_Money < Cur_Price*3)//��С�������
    {//����С�ڼ������
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"    ��ʾ");
       olcm_dispprintf(0,2,"����ֵ���Ϸ�");
       osys_getkey(_KEY_ENTER_EV_,300);
       goto RepInputFixm;
       }


 if(Judge_sct_Minimum(&carpre)==FALSE)
 {
     olcd_clearsCreen();
       olcm_dispprintf(0,1,"    ��ʾ");
       olcm_dispprintf(0,2,"����:%.02f",carpre);
       olcm_dispprintf(0,3,"���㣡");
       osys_getkey(_KEY_EXIT_EV_,300);
       eVirtualKey = _KEY_EXIT_EV_;
       return;
   }

 _station = (CN[0]-0x30)*10+(CN[1]-0x30);
  if(_station != Cur_StationNo)
  {
        if(_CARD_TYPE == 1)
        {
            olcd_clearsCreen();         // ss190904   ��վ�İ��鿨�����Լ���    
            olcm_dispprintf(0,1,"    ��ʾ");
            olcm_dispprintf(0,2,"����վ�����ɼ���");
            osys_getkey(_KEY_NULL_,200);
            eVirtualKey = _KEY_EXIT_EV_;
           return;
        }
//             {  olcd_clearsCreen();
//                olcm_dispprintf(0,1,"  �˿��Ǳ�վ��");
//                olcm_dispprintf(0,2,"���Եȣ�");
//                olcm_dispprintf(0,3,"���ڵȴ���̨��֤");

             }
 //REC_START = Check_Card_info(CN,&Rec_Card_PreM_int,&Rec_Card_Preg_int,CARD_XIAOFEI);
 if((WKJQ == 0)&&(_CARD_TYPE == 1))//rg170531�޿�����
	REC_START = Check_Card_info(cure_JQ_card, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);//rg170531�޿�����
	else
	REC_START = Check_Card_info(CN, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);	
 if(1!= REC_START )//����ֵ��1��0,2,4��Ϊ������,3Ϊ��ؿ��ɹ���
{ if(0 == REC_START )
   {//ͨ���쳣
     SOEACTION1(PRO422_ERR,eCurRunState);
       eVirtualKey = _KEY_EXIT_EV_;
      return;
   }
else if(2  == REC_START )
  {//�ڿ�
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"    ��ʾ");
       olcm_dispprintf(0,2,"�ÿ�Ϊ��ʧ����");
       osys_getkey(_KEY_EXIT_EV_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
  }
 else if(3  == REC_START )
            {//��ؿ��ɼ���
//               olcd_clearsCreen();
//               olcm_dispprintf(0,1,"    ��ʾ");
//               olcm_dispprintf(0,2,"����վ���ɼ���");
//               olcm_dispprintf(0,3,"���ڼ���....");
          }
        else if(4  == REC_START )
            {//��ؿ��ɼ���
               olcd_clearsCreen();
            olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"�ÿ�Ϊ��ʧ����");
             //  olcm_dispprintf(0,3,"���ڼ���....");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_EXIT_EV_;
              return;
          }
       else if(5 == REC_START )
            {  
           eVirtualKey = _KEY_EXIT_EV_;
           return;
           }
        else if(6  == REC_START )
            {//��ؿ��ɼ���
               olcd_clearsCreen();
            olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"��������֤ʧ�ܣ�");
             //  olcm_dispprintf(0,3,"���ڼ���....");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_EXIT_EV_;
              return;
          }
	   else 
                {
		    olcm_dispprintf(0,1,"    ��ʾ");
                   olcm_dispprintf(0,2,"�鿨���ɹ�");
		   osys_getkey(_KEY_NULL_,300);
                  eVirtualKey = _KEY_EXIT_EV_;
                  return;
                }
   }  //end of ����֤��1
}   //end of begin
////////////////////////////�˴��ֽ�㣬ע��##############################/////////////
 //REC_START = Ocompany_Gas_Quan_start(FIX_Money - OKgas_money);//���Ϳ�ʼ����ͨ������յ�������Ϣ
 
REC_START = Ocompany_Gas_Quan_start(FIX_Money - OKgas_money,Pr_gr,Discounf,Cur_Price,CPH,GasBegin);//���Ϳ�ʼ����ͨ������յ�������Ϣ//rg160829//rg170607 ������Ϣ���ƺ�rg181210
//����������������fix_money�����������ǰǹ����Rec_Sum_Start��ǰѹ��Rec_Begin_Press������ֵ��0:ͨѶ���� 1:���Լ���2: δԤ��

    if(1!= REC_START )//����ֵ��1����Ϊ��������
   { 
        gas_record.gas_process &=  GAS_START_SEND_FAILL;                          // ������¼  ������ʼ�����ʧ�ܱ�־
        if(0 == REC_START )
        {//ͨ���쳣
            SOEACTION1(23,eCurRunState);
             if(GasBegin ==1)
            eVirtualKey = _KEY_VIRTUAL_EV_;//����
            else
            eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
           return;

        }
        if(2  == REC_START )
        {
           olcd_clearsCreen();
           olcm_dispprintf(0,1,"δԤ��");
           olcm_dispprintf(0,2,"�����˳�");
           olcm_dispprintf(0,3,"����Ԥ��");
           osys_getkey(_KEY_EXIT_EV_,400);
           if(GasBegin ==1)//����Ѿ���ʼһ��GasBegin
           eVirtualKey = _KEY_ADDGAS_EXIT;//����
           else
           eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
            return;

        }
        else//rg170807  �������������ж�
	{
		 olcd_clearsCreen();
	       olcm_dispprintf(0,1,"����δ��������  ");
	       olcm_dispprintf(0,2,"    �޷�����    ");
	       olcm_dispprintf(0,3,"    ����      ");
	       osys_getkey(_KEY_EXIT_EV_,800);
	       if(GasBegin ==1)//����Ѿ���ʼһ��
	       eVirtualKey = _KEY_ADDGAS_EXIT;//����
	       else  
	       eVirtualKey = _KEY_EXIT_EV_;//ֱ���˳�
		return;
	}
    }
    else
    {
        UINT8 stop_num;
        gas_record.gas_process |=  GAS_START_SEND_SUCC;                          //   ������¼ ������ʼ����ͳɹ���־
        stop_num = ((gas_record.gas_process & 0x0F)+1);
        if(stop_num >15) stop_num =15;                                          // ֧�����ֹͣ����  15��
        gas_record.gas_process &= 0xF0;                                          //  ���ֹͣ����λ
        gas_record.gas_process |= stop_num ;          
    }

     /////////////////////////////�û�/rg160602///////////////////////////////////////////////
if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531�޿�����//rg170717 �����ӿ������ж� �ӿ����û� 
//if(((WKJQ==1)&&(_CARD_TYPE ==CARDT_SMALL))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531�޿�����//rg170717
    {
  if(GasBegin ==0)  
   {
       if(Graybegain == 0)
            { 
//	       j=0;
           j=2;
            while(j)
            {
                if(TRUE ==ic_card_put_status(CARDS_GREY))  //�û�RG160601
              {
                    delay_ms(50);//rg170323
		           ds=ic_card_get_status_nosel();//rg170323
			   if(ds==CARDS_GREY)//rg170323
			   {
				   Graybegain = 1;//rg170323
				break;   //rg170323
			   }
              }
		j--;
                delay_ms(50);
            }
//	       osys_getkey(_KEY_EXIT_EV_,900);
            if(j <= 0)
            {
		FIX_RecOK = 1;     
            Car_hui = 1;
            if (TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //����ֹͣ����
            {
		    SendStop_False = 1;
                eVirtualKey = _KEY_ADDGAS_EXIT;
            }    
	     SOEACTION1(huicar_err ,eCurRunState);
	     eVirtualKey = _KEY_ADDGAS_EXIT;
 //           eVirtualKey = _KEY_EXIT_EV_;
 //            osys_getkey(_KEY_EXIT_EV_,200);
             return;
            }
            } 
   }  
    }
 
    ///////////////////////////////////////////////////////////////
////////////////////����Ϊ����������/////////////////////////////////////////

 olcd_clearsCreen();
 //olcm_dispprintf(2,1,"���ڼ���");
 olng_operate_disp(TRUE,gain,ls,temp);
// GasBegin = 1;//    ��ֲ���·�  ss181213
 GasCo=1;
 Car_hui=0;
// Car_Hui_ok=0;
 Add_Gas_CS++;
  UINT8 Save_pre_gasvol =0; //wzw150518
  if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
  {
      deg_operate_save_begi();//150801
  }
  
if(GasBegin == 0)                                                           //�״μ�����Ҫ�洢
{
    WiteRecorInfoOnce(gas_record);                                          // �״ν�������¼��Ϣд�뵽�洢��  ss181213
}
GasBegin = 1; //������ʼ

    while(1)
    {
            
             
               if( send_sj_flag==1)
                { 
                    send_ack_sj(0x99);
                    send_sj_flag=0;
                    {
                        UINT8 loop_num;
                        loop_num = ((gas_record.grey_unlock_inif.grey_status & 0x0F)+1);
                        if(loop_num >15) loop_num =15;                                          // ֧�����ֹͣ����  15��
                        gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  ���ֹͣ����λ
                        gas_record.grey_unlock_inif.grey_status |= loop_num ;          
                    }
                }
                { 
                    rdkey = ostatemachine_getkey();
                    b_keyv = FALSE;
                    if(_KEY_STOP_EV_ == rdkey) 
                    {
                        gas_record.gas_stop_way = PRESS_STOP;                  // ������¼   ����ֹͣ����
                         break;
                    }
                       if(_KEY_SW_EV_ == rdkey)  SwPage=!SwPage;
                }
 		  if((WKJQ == 1)||((WKJQ==0)&&(_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//rg170531�޿�����//rg170717 
               { 
			  car_status = machine_status_card();
                    if(car_status!=CPU_TYPE_A)//���ε���
                    {
                        olcd_clearsCreen();
                        olcm_dispprintf(0,1,"���Ѱγ�!!");
                        olcm_dispprintf(0,2,"����ֹͣ");
                        FIX_RecOK = 1;
                        gas_record.gas_stop_way = CARD_EXTRACT;                  //  ������¼  �����γ�ֹͣ������ʽ
                        Car_hui = 1;
                        if(TRUE != Ocompany_Gas_Quan_stop(Car_hui)) //����ֹͣ����
                        {
                            SendStop_False  =1;
                            gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          // ������¼  ����ֹͣ����ʧ��
                            break;                                              // ���ٴη���ֹͣ
                        }
                        gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                          // ������¼  ����ֹͣ����ɹ�
       //                return;
                        eVirtualKey = _KEY_VIRTUAL_EV_;
                       return;//rg160602
                    }
                }
            Rec_Pro = Ocompany_Gas_noquan_run(&GV,&gain,&ls,&temp,&desenty,&press,&backgas,&isgasOK);//�õķɶ���
            {  
                rdkey = ostatemachine_getkey();
                b_keyv = FALSE;
                if(_KEY_STOP_EV_ == rdkey) 
                {
                    gas_record.gas_stop_way = PRESS_STOP;                  // ������¼   ����ֹͣ����
                     break;
                }
                if(_KEY_SW_EV_ == rdkey)  SwPage=!SwPage;
                  
            }
       /*   if((Rec_Pro == FALSE)&&(Car_Hui_ok==1))  
          {
             if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //����ֹͣ����
            {
                SendStop_False  =1;
               SOEACTION1(PRO422_ERR,eCurRunState);
         //     if(ecc_tick == DWORDMAX)
                  //ͨ���쳣��Σ�ֱ�ӵ�����״̬
                     olcd_clearsCreen();
                     olcm_dispprintf(0,1,"  ϵͳӲ���쳣");
                     olcm_dispprintf(0,2,"  ��ϵ���  ");

                      Gas_para_init();
                     ///////////////////////////
                    eCurRunState = State_MainUI;
                    eVirtualKey = 0;
                    osys_getkey(_KEY_EXIT_EV_,300);
                    return;
               }
               else
               { Gas_para_init();
  //             olcd_clearsCreen();
   //          olcm_dispprintf(0,1,"  �ûҲ��ɹ�    ");
    //         olcm_dispprintf(0,2,"  ��ϵ���   ");
             SOEACTION1(huicar_err ,eCurRunState);
   //          delay_ms(1000);
                   eVirtualKey = _KEY_EXIT_EV_;
             osys_getkey(_KEY_EXIT_EV_,300);
             return; }
          }*/
          if(Rec_Pro == TRUE)      //����ȷ�������ͷǶ�������isgasok��ֵ������
          {      
                ecc_tick = 0;
                gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  �����ѯ���ʹ���
               if(Save_pre_gasvol==0) //������һ��,Ĭ�ϵ�һ�ν�������Ϊ�ϱ���ͣ��ֵ
                {  
                   if(Add_Gas_CS>1)   //��һ��Every_add_Gas[1]
                    {
                         Every_add_Gas[Add_Gas_CS-1] = GV - Pre_vol_add;
                         Pre_vol_add =  GV;//Pre_vol_add +Every_add_Gas[Add_Gas_CS-1]; //����������ѭ����

                    }
                    Save_pre_gasvol = 1;
                }
              //   Every_add_Gas[Add_Gas_CS] = GV - Pre_vol_add;    //wzw150518

                if(isgasOK == 0xFD)//����
                 {    olcd_clearsCreen();
		      olcm_dispprintf(1,1,"�������");//�����Զ�ֹͣ
                      olcm_dispprintf(1,2,"�������");//
                      gas_record.gas_stop_way = MONEY_ALL;                  // ������¼  �������ֹͣ����
                       FIX_RecOK = 1;
                      eVirtualKey = _KEY_VIRTUAL_EV_;
                    return;
                  }
                 else if(isgasOK == 0xD0)//   �û�ʧ��  ֱ���˳�  
                {    
                    olcd_clearsCreen();
                    olcm_dispprintf(2,1,"�û�ʧ��");//�����Զ�ֹͣ
                    olcm_dispprintf(2,2,"�����²忨");//�����Զ�ֹͣ
                    osys_getkey(_KEY_EXIT_EV_,300); //�������ذ���ͣ�������跢��ֹͣ
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
            else if(isgasOK == 0xE0)
          {
               olcm_dispprintf(1,1,"���ٵ���ͣ");
                gas_record.gas_stop_way = VELOCIIY_LOW;                  // ������¼  ���ٵ���ֹͣͣ����
               osys_getkey(_KEY_EXIT_EV_,300); //�������ذ���ͣ�������跢��ֹͣ
               eVirtualKey = _KEY_VIRTUAL_EV_;//ֱ�ӵ��ۿ�
                   return;
          }
         else  if(isgasOK > 0x0)    //�ǵö������ĺ�
        {  
            olcd_clearsCreen();
	            switch(isgasOK)
                      {   case  0xE1:   olcm_dispprintf(1,1,"���ͨ�ų�ʱ");
                                       SOEACTION1(PRO422_ERR,eCurRunState);
                                    gas_record.gas_stop_way = COMMUN_TIIMOUT;                  // ������¼  ���ͨ�ų�ʱֹͣ����
                                         break;
                          case  0xE3:   olcm_dispprintf(1,1,"Һ��ƶ�������");
                                         SOEACTION1(MOD_READNUM_ERR,eCurRunState);
                                    gas_record.gas_stop_way = FLOWMETER_ERR;                  // ������¼  ������ͨ�Ŵ���ֹͣ����
                                         break;
                          case  0xE4:   
                              olcm_dispprintf(1,1,"Ԥ�䳬ʱ");
                                    gas_record.gas_stop_way = PRECOOL_ERR;                  // ������¼  Ԥ�䳬ʱֹͣ����
                                        break;
                          case  0xE5:
                                olcm_dispprintf(1,1,"ѹ���쳣");
                               olcm_dispprintf(1,2,"���˳�!!");
                                 SOEACTION1(NOPRESSURE_ERR,eCurRunState);
 //160620                              osys_getkey(_KEY_EXIT_EV_,500); //�������ذ���ͣ�������跢��ֹͣ
                                gas_record.gas_stop_way = PRESSURE_ERR;                  // ������¼  ѹ���쳣ֹͣ����
                               eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ����ָ�����󣬿���ѯ���ۼ�
                               return;
                          case  0xE6:
                                olcm_dispprintf(1,1,"�����������");
                                olcm_dispprintf(1,2,"���˳�!!");
                                SOEACTION1(ZDLS_ERR,eCurRunState);
                                gas_record.gas_stop_way = VELOCITY_HIGH;                  // ������¼  �����������ֹͣ����
        //160620                       osys_getkey(_KEY_EXIT_EV_,500); //�������ذ���ͣ�������跢��ֹͣ
                               eVirtualKey = _KEY_ADDGAS_EXIT;//ֱ�ӵ��ۿ����ָ�����󣬿���ѯ���ۼ�
                               return;      
                          case  0xE8://rg180115
                                olcm_dispprintf(0,1,"�����Ϳ��಻ƥ��");
                                olcm_dispprintf(1,2,"���˳�!!");
                                gas_record.gas_stop_way = CARD_BALANCE_FAILL;                  // ������¼ �����Ϳ��಻ƥ��
	//		       osys_getkey(_KEY_EXIT_EV_,300);
                                 SOEACTION1(KLXKY_ERR ,eCurRunState);
                              break;     
                              default:     
                                  olcm_dispprintf(1,1,"�����쳣");    
                                  gas_record.gas_stop_way = GAS_UNUSUAL;                  // ������¼  �����쳣
                                  AddSOE(isgasOK);
                              break;
                      }
                  //�������ذ���ͣ�������跢��ֹͣ
                   GAS_MustStop_Err = 1;//�����������ͣ
                   osys_getkey(_KEY_EXIT_EV_,400);
                   eVirtualKey = _KEY_VIRTUAL_EV_;//ֱ�ӵ��ۿ�
                   return;
         }
#if 0
          if((isgasOK == 0)&&GV >=1)   //���Ƕ����ﵽ��ֵ��һ�����
          {   if(RepGV !=GV)
                 { RepGV =GV;
                   RecGverr = 0;
                 }
               else
                RecGverr++;
             if(RecGverr >20)
              {      olcd_clearsCreen();
		      olcm_dispprintf(1,1,"�����쳣���");//��������������
                      FIX_RecOK = 1;
                     eVirtualKey = _KEY_VIRTUAL_EV_;
                     break;
              }

       }
#endif
       if(SwPage ==FALSE)
           olng_operate_disp(FALSE,gain,ls,temp);
       else
           olng_operate_disp2(FALSE,GV,desenty,press); /////��Ϊѹ��������


        if(gTick >Debugasing_rstsave_Tick)  //150801
          {  if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //�ڹ����������ʱ�������ж� MAX_dubug_recid_num  ���ܳ���200���ɼ���
                {
                deg_operate_save_gasing(GV); //150730  150801
                 }
             Debugasing_rstsave_Tick = gTick + 200;
            }

   // olng_operate_disp(FALSE,gain,ls,temp);
  }  //end of  TRUE

   else                //  û�н��յ���¼��Ϣ  ss181213
        { 
              if(ecc_tick !=0)
              {
                if(gTick > ecc_tick)
                 {   
                       GAS_MustStop_Err = 1;//�˴������ͣ
                       eVirtualKey = _KEY_VIRTUAL_EV_;//ֱ�ӵ��ۿ�
                       olcm_dispprintf(0,1,"���̰�3 ��������");
                       osys_getkey(_KEY_EXIT_EV_,400);
                       ecc_tick = DWORDMAX;
                       gas_record.gas_stop_way = TRIPLE_COMMUN_FAILL;                  // ������¼  ����������ֹͣ����
                       break;
                    // return;
                 }
               }
          else
            {  ecc_tick = gTick +600;
             }

          }
            
        if((gas_record.grey_lock_inif.grey_status & 0x03) ==  GREY_LUCK_SUCC)               //�ٴ��жϻ���״̬  //ss190215  �ûҳɹ��������ٴ��ж�
        {
            if(Get_Grey_Statu == FALSE)                            // ���뵽�������̣��ٴ��жϿ��Ƿ�Ϊ�ҿ�
            {
                Get_Grey_Statu = TRUE;

                    if(CARDS_GREY != ic_card_get_status_nosel() )                         // ��ȡ����״̬ 
                    {
                        SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // �����������жϿ���Ϊ�ҿ� ������ʾ
                        gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_FAILL;                          // ������¼   �����������ٴζ�ȡ����״̬   ss190304
                        break;                                                                     // ��ǰ����Ϊ����״̬ �������� 
                    }
                    gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // ������¼   �����������ٴζ�ȡ����״̬

            }
        }
//        if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//ss181213   ���޿� ���ӿ���������������ж� ����״̬  
//               {
//       if(Get_Grey_Statu == FALSE)                            // ���뵽�������̣��ٴ��жϿ��Ƿ�Ϊ�ҿ�
//        {
//            Get_Grey_Statu = TRUE;
//
//                if(CARDS_GREY != ic_card_get_status_nosel() )                         // ��ȡ����״̬ 
//                {
//                    SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // �����������жϿ���Ϊ�ҿ� ������ʾ�����쳣��¼
//                    gas_record.grey_lock_inif.grey_status &=  GREY_GAS_LUCK_FAILL;                          // ������¼   �����������ٴζ�ȡ����״̬  
//                    break;                                                                     // ��ǰ����Ϊ����״̬ �������� 
//                }
//                gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // ������¼   �����������ٴζ�ȡ����״̬
//            
//
//        }
//               }
        
        }//end  of while(1)

      if(TRUE != Ocompany_Gas_Quan_stop(Car_hui)) //����ֹͣ����
       {
             SendStop_False  =1;
  //         SOEACTION1(25,eCurRunState);
             gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          //   ������¼ ����ֹͣ����ͳɹ���־                          // ������¼  ����ֹͣ����ʧ��
            if(ecc_tick == DWORDMAX)
                {//ͨ���쳣��Σ�ֱ�ӵ�����״̬
                      olcd_clearsCreen();
                      olcm_dispprintf(0,1,"  ϵͳӲ���쳣");
                      olcm_dispprintf(0,1,"  ��ϵ���  ");
                      
                     
                    memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
                    memset(CPH,0x0,12);//rg170619 ���복�ƺ�
                    Cp_flag=0;//rg170619 ���복�ƺ�
                    gas_record.gas_stop_way = SYS_HARD_FAULT;                  // ������¼  ϵͳӲ���쳣ֹͣ����
                    gas_record.gas_stream = 0x00;                              // ������¼   ϵͳӲ���쳣��ˮ�Ÿ� ��ֵ
                    ortcc_read_time(gas_record.grey_unlock_inif.time);                    // ������¼   ���ʱ��   �����ڴˣ����ʧ��Ҳ�ǿ��Ի�ȡ���ʱ���
                    WiteRecorInfo_AN(gas_record);    
                    Gas_para_init();
                    while(1);  
                    eCurRunState = State_MainUI;
                    eVirtualKey = 0;
                    osys_getkey(_KEY_EXIT_EV_,400);
                    return;
                }
          
       }
        gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                         // ������¼  ����ֹͣ����ɹ�
//        eVirtualKey = _KEY_VIRTUAL_EV_;
//    if(gas_record.gas_precool == GAS_PRECOOL_SUCC)             // Ԥ��ɹ� �ſ��Խ��뵽�ۿ�״̬   ss190312  
//    {
        eVirtualKey = _KEY_VIRTUAL_EV_;//ֱ�ӵ��ۿ�
//    }
//    else
//    {
//        eVirtualKey = _KEY_EXIT_EV_;//ֱ�ӵ��ۿ�
//        WiteRecorInfo_AN(gas_record);                              //ss190213  // ������¼  ��������¼��Ϣд�뵽EEP��
//    }
    return;

}
//�Ƕ����������ۼ�
void olng_operate_Isadd(void)
{   //����ֹͣ
    UINT8 cou1 = 0;
    UINT8 cou2 = 0;
    UINT8 keyV;
   float GV; float AM; float back_gas;UINT8 EccType;
   UINT8 hq_state;
	UINT8 car_status;//RG170705
  
#if 0
 if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType))//��ѯ
    {
     if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType))//��ѯ
         {GAS_MustStop_Err = 1;
           olcd_clearsCreen();
           olcm_dispprintf(0,1,"    ϵͳ�쳣");
           olcm_dispprintf(0,2,"    ����ֹͣ");
           AddSOE(2);
         }
      }
     OKgas_GV = GV;   //��õ�GV�����������Ѿ��۳��˻�������
     GAS_BACKGV = back_gas;//����,(�Ѿ��۳��˻�������)
     OKgas_money = AM;
#endif
 if((GAS_MustStop_Err ==0)&&(FIX_RecOK != 1))  //û�б���ֹͣ�ģ���û��OK��־
  {
       olcd_clearsCreen();
       if(Zttz_Time>0)//rg170605ֹͣ/ ��ͣ
       {
        if(State_g_p==1) olcm_dispprintf(0,1,"    Ԥ��ֹͣ");
        else olcm_dispprintf(0,1,"    ����ֹͣ");
  //     olcm_dispprintf(0,1,"    ������ͣ");
//       olcm_dispprintf(0,2,"�Ƿ����������");
       olcm_dispprintf(0,3,"������--��������");
       olcm_dispprintf(0,4,"��ֹͣ--ֹͣ����");
       }
       IsGasAdd_tick = gTick + 100 * Zttz_Time;//rg170605ֹͣ/ ��ͣ
      //IsGasAdd_tick =gTick +100*ISADDTIME;  //900S
         while(1)
          {
              if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
             {
                  olcm_dispprintf(0,3,"  ���Լ������  ");
                 olcm_dispprintf(0,4,"  ���ڱ�������  ");
                 break;
             }
                if(gTick > IsGasAdd_tick)
             {   IsGasAdd_tick = 0;
                 break;//�������пۿ�
             }
	      if(Zttz_Time>0)//rg170605ֹͣ/ ��ͣ
	      {
             cou1 = (UINT8)(((IsGasAdd_tick -gTick)/100)/60);
             cou2 = (UINT8)(((IsGasAdd_tick -gTick)/100)%60);
          //   olcm_dispprintf(7,1,"%2d",cou);
               olcm_dispprintf(5,2,"%02dm%02ds",cou1,cou2);
              // olcm_dispprintf(0,2,"%3d ����Զ�����",cou);
	      }
              if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531�޿����� //rg170717
	{
		car_status = machine_status_card();
	  if(car_status!=CPU_TYPE_A)//���ε���
            {   
                gas_record.gas_stop_way = CARD_EXTRACT;                        // ������¼   �����ε�  ֹͣ����
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"���Ѱγ�!!");
                olcm_dispprintf(0,2,"��Ϊ�ҿ�");
                Car_hui = 1;
                  break;
            }
        }
                 keyV = osys_getkey_ex(); //Sys_GetKey();
              //   if(keyV != 0)
                  b_keyv = FALSE;
                 if(keyV == _KEY_GAS_EV_)
                {
                  eVirtualKey = _KEY_VIRTUAL_2_EV_;
                  return;//�ۼӣ���������
                }
                if(keyV == _KEY_STOP_EV_)
                 break;//�������пۿ�
              if(keyV == _KEY_POINT_EV_)
               {
                   if(!Ocompany_Gas_Qz())//ȡ��
                   {
                       olcd_clearsCreen();
                       olcm_dispprintf(0,1,"    ͨѶ�쳣");
                       osys_getkey(_KEY_NULL_,500);
                       break;
                       }
                 //���͸����ذ�ȡ����û�з���ֵ
               }

          }//end  of while(1)

}
//////////////////////
    if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//��ѯ
    {
        if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//��ѯ
        {
            gas_record.gas_stop_way = SYS_FAULT;                           //������¼   ��Ҫ������Ϣʧ��ֹͣ  ss181213
            GAS_MustStop_Err = 1;
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"    ϵͳ�쳣");
            olcm_dispprintf(0,2,"    ����ֹͣ");
            olcm_dispprintf(0,3,"    ���̨���");//rg160817
            AddSOE(PRO422_ERR);//rg160817
            Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����//rg160817
            memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
            memset(CPH,0x0,12);//rg170619 ���복�ƺ�
            Cp_flag=0;//rg170619 ���복�ƺ�
            WiteRecorInfo_AN(gas_record);                                              // ������¼  ��������¼��Ϣд�뵽EEP��
            memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ
            osys_getkey(_KEY_EXIT_EV_,400);//rg160817
            eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬//rg160817
            return;//rg160817
        }
    }
//     	if (hq_state == 0xFF)//RG170406                                /// �˴�����  ss190218
//	{
//		OKgas_GV = 0; //��õ�GV�����������Ѿ��۳��˻�������
//		GAS_BACKGV = 0; //����,(�Ѿ��۳��˻�������)
//		OKgas_money = 0;
//		olcd_clearsCreen();
//	        olcm_dispprintf(0,2,"���̨���");
//		SOEACTION1(Zhu_Reset, eCurRunState);
//		Gas_para_init(); //�ÿ��˴μ�����Ϣȫ�����
//		memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
//	         memset(CPH,0x0,12);//rg170619 ���복�ƺ�
//		Cp_flag=0;//rg170619 ���복�ƺ�
//		eVirtualKey = _KEY_EXIT_EV_; //ָ��Ϊ����״̬
//		return;
//	}	
     /*rg170330���λ���������Ǯ��������������
     //////////////////rg160926//////////////////////////////////////
     if((hq_state==0x98)||(hq_state==0x99))//rg160926
     {
	OKgas_GV = 0;   //��õ�GV�����������Ѿ��۳��˻�������
     GAS_BACKGV = 0;//����,(�Ѿ��۳��˻�������)
     OKgas_money = 0;
     Rec_Card_EndM_int = Rec_Card_PreM_int;
     Rec_Card_Endg_int = Rec_Card_Preg_int;
      olcd_clearsCreen();
      if(hq_state==0x99)
      {    
      SOEACTION1(C_MODBUS_ERR,eCurRunState);
      }
          ic_card_put_status(CARDS_NORMAL);
	  if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
        {  SOEACTION1(PRO422_ERR,eCurRunState);//ͨ���쳣//6��ʵ�����õĲ���
        }
	   if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //�ڹ����������ʱ�������ж� MAX_dubug_recid_num  ���ܳ���200���ɼ���
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
      Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
     eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
	return;  
     }
     ///////////////////////////////////////////////////////////////
      */
     OKgas_GV = GV;   //��õ�GV�����������Ѿ��۳��˻�������
     GAS_BACKGV = back_gas;//����,(�Ѿ��۳��˻�������)
     OKgas_money = AM;

    if((AM<0.01)&(GV<0.01)&(hq_state == 0xFF)&( _gas_run_flag == TRUE))                  //����������������Ϊ��  ��ʼ������־   �������������Խ��ss190218 
    {
        OKgas_GV = 0; //��õ�GV�����������Ѿ��۳��˻�������
		GAS_BACKGV = 0; //����,(�Ѿ��۳��˻�������)
		OKgas_money = 0;
        
        {                                                                       //��ȡ������¼
            UINT32 max_rec_id;
            max_rec_id = get_max_rec_id();                                        // ������¼   ��ȡ���ذ�ļ�����ˮ��
            if(max_rec_id != 0xFFFF0000)
            {
                gas_record.gas_stream = max_rec_id;                             // ������¼  ������ˮ����Ϣ
            }
        }
        WiteRecorInfo_AN(gas_record);                                           //
        memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ
        Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"��ȡ��Ϣʧ��");
        olcm_dispprintf(0,2,"���̨���");
        osys_getkey(_KEY_NULL_, 300);
        memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
        memset(CPH,0x0,12);//rg170619 ���복�ƺ�
        Cp_flag=0;//rg170619 ���복�ƺ�
        eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
        return;
    }
     
     /////////////////////
          //�˴�����Ϊ����
    GasCo=0;
     if(OKgas_money < 0)
     {
    Rec_Card_EndM_int = Rec_Card_PreM_int - (INT32)(OKgas_money*100-0.5);//��������=��ʼ����-�������
     Rec_Card_Endg_int = Rec_Card_Preg_int - (INT32)(OKgas_GV*100-0.5);   //��������=��ʼ����-��������
     }
     else if(OKgas_money >= 0)
     {
       Rec_Card_EndM_int = Rec_Card_PreM_int - (INT32)(OKgas_money*100+0.5);//��������=��ʼ����-�������
     Rec_Card_Endg_int = Rec_Card_Preg_int - (INT32)(OKgas_GV*100+0.5);   //��������=��ʼ����-��������
     }
        Rec_Card_EndM = Rec_Card_PreM - OKgas_money;//��������=��ʼ����-�������
//     Rec_Card_Endg = Rec_Card_Preg - OKgas_GV;   //��������=��ʼ����-��������

   //  odisp_disp(OKgas_GV , OKgas_money, TRUE);
     show_operat_stop(OKgas_GV ,OKgas_money);
     gas_record.grey_unlock_inif.OKgas_money = OKgas_money;  
    if(OKgas_GV < 0)//rg170330
     {
	     OKgas_GV = 0;  //rg170330   
     }
 /*    if(OKgas_GV == 0)
     {    olcd_clearsCreen();
          olcm_dispprintf(0,1,"����Ϊ0 ");
          olcm_dispprintf(0,2,"�������");
          olcm_dispprintf(0,3,"���˳���");
          ic_card_put_status(CARDS_NORMAL);
          Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
          osys_getkey(_KEY_EXIT_EV_,400);
         eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
         return;
     }*/
    //  ortcc_read_time(GAS_Etime); //�õ���������ʱ��
      CanGasTime = gTick  +100*60*CANGASMINUTE ; //��Сʱ
      if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531�޿�����//rg170717
      {
            if(olng_operate_put_card() == TRUE)//�ۿ�ҽ��
            {
                olcm_dispprintf(2,4,"�ۿ�ɹ�");//�ۿ�ɹ�����������Ϣ�����ذ�
                Car_hui = 0;
                if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
                    //           if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
                {
                    SOEACTION1(PRO422_ERR, eCurRunState); //ͨ���쳣//6��ʵ�����õĲ���
                        gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // ������¼   �ۿ���Ϣ����ʧ��
             //       return;
                }
                    else
                        gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // ������¼   �ۿ���Ϣ���ͳɹ�
            }
            else                           //  ���ʧ��   
            {		
                if(_CARD_TYPE == CARDT_SMALL)//rg170717 
                {
                         Car_hui = 0;
                }
                else
                {
                    olcm_dispprintf(2,4,"�ۿ�ʧ��");
                    Car_hui = 1;
                    ic_card_active_sp();                                          // ���¼����
                    if(IC_card_put_grey_status())                                 // ���ʧ�ܣ��ٴ�д�����״̬��    ss190306
                    {
                       gas_record.gas_process |= GAS_GREY_LUCK_SUCC_AG;                     // �ٴ��ûҳɹ�
                    }
                    else
                        gas_record.gas_process &= GAS_GREY_LUCK_FAILL_AG;                   // �ٴ��û�ʧ��
                }
                if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
                {
                   SOEACTION1(PRO422_ERR, eCurRunState); //ͨ���쳣
                   gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // ������¼   �ۿ���Ϣ����ʧ��
                //       return;
                }
                else
                   gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // ������¼   �ۿ���Ϣ���ͳɹ�
            }
        }
        else////rg170531�޿�����
        {
            Car_hui = 0;
            if (TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE, CN, &OKgas_GV, &OKgas_money, &Rec_Card_PreM_int, &Rec_Card_EndM_int, &Rec_Card_Preg_int, &Rec_Card_Endg_int, &Rec_Sum_Start, &Rec_Sum_End, &Rec_Begin_Press, &Rec_End_Press, &Car_hui, GAS_Stime, GAS_Etime))
            {
                SOEACTION1(PRO422_ERR, eCurRunState); //ͨ���쳣//6��ʵ�����õĲ���
                gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // ������¼   �ۿ���Ϣ����ʧ��
             //   return;
            }  
            else
                gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // ������¼   �ۿ���Ϣ���ͳɹ�
            
            ortcc_read_time(gas_record.grey_unlock_inif.time);                    // ������¼   ���ʱ��   �����ڴˣ����ʧ��Ҳ�ǿ��Ի�ȡ���ʱ���
        }

    
      ///////////////////�б��Ƿ��ǹ������е��Լ���///////////////////////////////150730
      if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //�ڹ����������ʱ�������ж� MAX_dubug_recid_num  ���ܳ���200���ɼ���
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
      /////////////////////////////////////////////////////////////
         if((hq_state==0x99)||(hq_state==0x98))//rg170330
        {
            olcd_clearsCreen();
            if(hq_state==0x99)//��������500
            SOEACTION1(C_HuiQi_ERR,eCurRunState);
            if(hq_state==0x98)//������Ϊ��
            SOEACTION1(C_JiaQi_fu ,eCurRunState);	 
        }
     if((PRINT_SET ==1)&&(OKgas_GV != 0))//rg171127 ����Ϊ�㲻��ӡ
      oprint_operate_rec();
  //   else//rg170606��ӡ������
  //     Select_print();//�ֶ���ӡѡ��//rg170606��ӡ������
      
    {                                                                       //��ȡ������¼
         UINT32 max_rec_id;

         gas_record.grey_unlock_inif.Balance_To = Rec_Card_EndM;              //  ������¼     ��ʣ���
         max_rec_id = get_max_rec_id();                                        // ������¼   ��ȡ���ذ�ļ�����ˮ��
         if(max_rec_id != 0xFFFF0000)
         {
             gas_record.gas_stream = max_rec_id;                             // ������¼  ������ˮ����Ϣ
         }
    }
    WiteRecorInfo_AN(gas_record);                                              // ������¼  ��������¼��Ϣд�뵽EEP��
    memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ
    Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
    memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
    memset(CPH,0x0,12);//rg170619 ���복�ƺ�
    Cp_flag=0;//rg170619 ���복�ƺ�
    eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬

}
void Select_print(void)
{      UINT8  cou,keyV;
       olcd_clearsCreen();
       olcm_dispprintf(0,2,"  �Ƿ��ӡ");
       olcm_dispprintf(0,3,"��ȷ��--��ӡ");
       olcm_dispprintf(0,4,"������--����ӡ");
       IsGasAdd_tick =gTick +100*10;  //10S
         while(1)
          {
             if(gTick > IsGasAdd_tick)
             {   IsGasAdd_tick = 0;
               return;//�������пۿ�
              }
             cou = (UINT8)((IsGasAdd_tick -gTick)/100);
             olcm_dispprintf(7,1,"%2d",cou);
               keyV = osys_getkey_ex(); //
               //  if(keyV != 0)
                  b_keyv = FALSE;
                 if(keyV == _KEY_ENTER_EV_)
                {
                 oprint_operate_rec();
                 olcd_clearsCreen();
                 olcm_dispprintf(0,2,"���ڴ�ӡƱ��....");
                  return;//
                }
               else if(keyV == _KEY_EXIT_EV_)
                 return;

          }
}
//����������ֹͣ
void gas_finish(void)
{    float GV; float AM; float back_gas;UINT8 EccType;
     UINT8 keyV;
     UINT8 cou1 = 0;
      UINT8 cou2 = 0;
      UINT8 hq_state;
      UINT8 car_status;//RG170705
     GasCo=0;
  if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//ѯ��

   { 
        if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//��ѯ
        {
            gas_record.gas_stop_way = SYS_FAULT;                           //������¼   ��Ҫ������Ϣʧ��ֹͣ  ss181213
            GAS_MustStop_Err = 1;
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"    ϵͳ�쳣");
            olcm_dispprintf(0,2,"    ����ֹͣ");
            AddSOE(PRO422_ERR);
        }
     
    }
   
     OKgas_GV = GV;
     GAS_BACKGV = back_gas;//����
    OKgas_money = AM;
   

  if((OKgas_money < FIX_Money)&& (GAS_MustStop_Err ==0)&&(FIX_RecOK != 1))//���û�м���������Ҳ������ذ�Ҫ��ֹͣ����,��Ҫ���Ǽ�����ϣ�ѯ���Ƿ��������
     {//FIX_RecOK:��Ϊ��ֹ��߼������Ⱥ���ǰ�ط���ʹ����΢С�ڶ����ô������ɡ�
        olcd_clearsCreen();
	if(Zttz_Time>0)//rg170605ֹͣ/ ��ͣ
	{
		olcm_dispprintf(0,1,"  ����ֹͣ");
       olcm_dispprintf(0,3,"������--��������");
       olcm_dispprintf(0,4,"��ֹͣ--ֹͣ����");
	}
       IsGasAdd_tick = gTick + 100 * Zttz_Time;//rg170605ֹͣ/ ��ͣ
//       IsGasAdd_tick =gTick +100*ISADDTIME;  //900S
         while(1)
          {
              if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
             {   olcm_dispprintf(0,3,"  ���Լ������  ");
                 olcm_dispprintf(0,4,"  ���ڱ�������  ");
                 break;
             }
                if(gTick > IsGasAdd_tick)
             {   IsGasAdd_tick = 0;
                 break;//�������пۿ�
             }
	      if(Zttz_Time>0)//rg170605ֹͣ/ ��ͣ
	      {
             cou1 = (UINT8)(((IsGasAdd_tick -gTick)/100)/60);
             cou2 = (UINT8)(((IsGasAdd_tick -gTick)/100)%60);
          //   olcm_dispprintf(7,1,"%2d",cou);
               olcm_dispprintf(5,2,"%02dm%02ds",cou1,cou2);
	      }
              if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531�޿�����//rg170717
	{
		car_status = machine_status_card();
            if(car_status!=CPU_TYPE_A)//���ε���
            {  
                gas_record.gas_stop_way = CARD_EXTRACT;                        // ������¼   �����ε�  ֹͣ����
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"���Ѱγ�!!");
                olcm_dispprintf(0,2,"��Ϊ�ҿ�");
                Car_hui = 1;
                break;
            }
        }
                 keyV = osys_getkey_ex(); //Sys_GetKey();
               //  if(keyV != 0)
                  b_keyv = FALSE;
                 if(keyV == _KEY_GAS_EV_)
                {
                  eVirtualKey = _KEY_VIRTUAL_3_EV_;
                  return;//�ۼӣ���������
                }
                if(keyV == _KEY_STOP_EV_)
                 break;//�������пۿ�
            if(keyV == _KEY_POINT_EV_)
               {
                   if(!Ocompany_Gas_Qz())//ȡ��
                   {
                       olcd_clearsCreen();
                       olcm_dispprintf(0,1,"    ͨѶ�쳣");
                       osys_getkey(_KEY_NULL_,500);
                       break;
                       }
                 //���͸����ذ�ȡ����û�з���ֵ
               }

          }


     }

     if(GAS_MustStop_Err ==1)//���������ر������ܼ�������
     {  olcd_clearsCreen();
       olcm_dispprintf(0,1,"  ֹͣ����");
       olcm_dispprintf(0,1,"���ܼ����������");
       olcm_dispprintf(0,1,"    ��Ǹ       ");
      
     }
   //////////////////////////////////////////////////////////////
      if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//ѯ��
   { 
        if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//��ѯ
        {
            GAS_MustStop_Err = 1;
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"    ϵͳ�쳣");
            olcm_dispprintf(0,2,"    ����ֹͣ");
 //          AddSOE(2);
	    olcm_dispprintf(0,3,"    ���̨���");//rg160817
           AddSOE(PRO422_ERR);//rg160817
	   Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����//rg160817
	   memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
	         memset(CPH,0x0,12);//rg170619 ���복�ƺ�
		Cp_flag=0;//rg170619 ���복�ƺ�
          osys_getkey(_KEY_EXIT_EV_,400);//rg160817
         eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬//rg160817
            gas_record.gas_stop_way = SYS_FAULT;                           //������¼   ��Ҫ������Ϣʧ��ֹͣ ss181213
            WiteRecorInfo_AN(gas_record);                                              // ������¼  ��������¼��Ϣд�뵽EEP��
            memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ
         return;//rg160817
         }

    }
    
//    if (hq_state == 0xFF)//RG170406                                           //ss190218
//	{
//		OKgas_GV = 0; //��õ�GV�����������Ѿ��۳��˻�������
//		GAS_BACKGV = 0; //����,(�Ѿ��۳��˻�������)
//		OKgas_money = 0;
//		olcd_clearsCreen();
//	        olcm_dispprintf(0,2,"���̨���");
//		SOEACTION1(Zhu_Reset, eCurRunState);
//		Gas_para_init(); //�ÿ��˴μ�����Ϣȫ�����
//		memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
//	         memset(CPH,0x0,12);//rg170619 ���복�ƺ�
//		Cp_flag=0;//rg170619 ���복�ƺ�
//		eVirtualKey = _KEY_EXIT_EV_; //ָ��Ϊ����״̬
//		return;
//	}
    /*rg170330���λ���������Ǯ��������������
    ////////////////rg160926//////////////////////////////////////////
	if((hq_state==0x98)||(hq_state==0x99))//rg160926
     {
	OKgas_GV = 0;   //��õ�GV�����������Ѿ��۳��˻�������
     GAS_BACKGV = 0;//����,(�Ѿ��۳��˻�������)
     OKgas_money = 0;
     Rec_Card_EndM_int = Rec_Card_PreM_int;
     Rec_Card_Endg_int = Rec_Card_Preg_int;
      olcd_clearsCreen();
          if(hq_state== 0x99 )
      {  
      SOEACTION1(C_MODBUS_ERR,eCurRunState);
      }
          ic_card_put_status(CARDS_NORMAL);
	  if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
        {  SOEACTION1(PRO422_ERR,eCurRunState);//ͨ���쳣//6��ʵ�����õĲ���
        }
	   if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //�ڹ����������ʱ�������ж� MAX_dubug_recid_num  ���ܳ���200���ɼ���
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
     Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
     eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
	return;  
     }
    ////////////////////////////////////////////////////////////////
     */
     OKgas_GV = GV;
     GAS_BACKGV = back_gas;//����
     OKgas_money = AM;

    if((AM<0.01)&(GV<0.01)&(hq_state == 0xFF)&( _gas_run_flag == TRUE))                  //����������������Ϊ��  ��ʼ������־   �������������Խ��ss190218 
    {
        OKgas_GV = 0; //��õ�GV�����������Ѿ��۳��˻�������
		GAS_BACKGV = 0; //����,(�Ѿ��۳��˻�������)
		OKgas_money = 0;
        
        {                                                                       //��ȡ������¼
            UINT32 max_rec_id;
            max_rec_id = get_max_rec_id();                                        // ������¼   ��ȡ���ذ�ļ�����ˮ��
            if(max_rec_id != 0xFFFF0000)
            {
                gas_record.gas_stream = max_rec_id;                             // ������¼  ������ˮ����Ϣ
            }
        }
        WiteRecorInfo_AN(gas_record);                                           //
        memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ
        Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"��ȡ��Ϣʧ��");
        olcm_dispprintf(0,2,"���̨���");
        osys_getkey(_KEY_NULL_, 300);
        memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
        memset(CPH,0x0,12);//rg170619 ���복�ƺ�
        Cp_flag=0;//rg170619 ���복�ƺ�
        eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
        return;
    }
     
    ////////////////////////////////////////////////////////////////
     Rec_Card_EndM_int = Rec_Card_PreM_int - (INT32)(OKgas_money*100+0.5);//��������=��ʼ����-�������
     Rec_Card_Endg_int = Rec_Card_Preg_int - (INT32)(OKgas_GV*100+0.5);   //��������=��ʼ����-��������

     Rec_Card_EndM = Rec_Card_PreM - OKgas_money;//��������=��ʼ����-�������
 //    Rec_Card_Endg = Rec_Card_Preg - OKgas_GV;   //��������=��ʼ����-��������

     show_operat_stop(OKgas_GV,OKgas_money);
      gas_record.grey_unlock_inif.OKgas_money = OKgas_money;                   //  ������¼    ���ѽ��
	if(OKgas_GV < 0)//rg170330
     {
	     OKgas_GV = 0;  //rg170330   
     }
   /*   if(OKgas_GV == 0)
     {    olcd_clearsCreen();
          olcm_dispprintf(0,1,"����Ϊ0 ");
          olcm_dispprintf(0,2,"�������");
          olcm_dispprintf(0,3,"���˳���");
           ic_card_put_status(CARDS_NORMAL);
          Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
          osys_getkey(_KEY_EXIT_EV_,400);
         eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
         return;
     }*/
     
 //   ortcc_read_time(GAS_Etime);
      CanGasTime = gTick  +100*60*CANGASMINUTE ; //��Сʱ
      if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531�޿�����//rg170717
      {
            if(olng_operate_put_card()==TRUE)//�ۿ�ҽ��
           {
               olcm_dispprintf(2,4,"�ۿ�ɹ�");//�ۿ�ɹ�����������Ϣ�����ذ�
               Car_hui = 0;
               
               if(TRUE != Ocompany_Gas_Quan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
               {  
                   SOEACTION1(PRO422_ERR,eCurRunState);//ͨ���쳣
                   gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // ������¼   �ۿ���Ϣ����ʧ��
                //151229  return;
               }
               else
                   gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // ������¼   �ۿ���Ϣ���ͳɹ�
           }
           else
               {	
                    if(_CARD_TYPE == CARDT_SMALL)//rg170717 
                   {
                        Car_hui = 0;
                   }
                   else
                   {
                       olcm_dispprintf(2,4,"�ۿ�ʧ��");
                       Car_hui = 1;
                        ic_card_active_sp();                                     // ���¼����
                        if(IC_card_put_grey_status())                                 // ���ʧ�ܣ��ٴ�д�����״̬��    ss190306
                        {
                           gas_record.gas_process |= GAS_GREY_LUCK_SUCC_AG;                     // �ٴ��ûҳɹ�
                        }
                        else
                            gas_record.gas_process &= GAS_GREY_LUCK_FAILL_AG;                   // �ٴ��û�ʧ��
                        
                   }
                if(TRUE != Ocompany_Gas_Quan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime ))
                  {  
                       SOEACTION1(PRO422_ERR,eCurRunState);//ͨ���쳣
                        gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // ������¼   �ۿ���Ϣ����ʧ��
              //        return;
                   //151229   return;
                   }
                   else
                       gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // ������¼   �ۿ���Ϣ���ͳɹ�
               }
      }
      else
      {
	    Car_hui = 0;
	  if (TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE, CN, &OKgas_GV, &OKgas_money, &Rec_Card_PreM_int, &Rec_Card_EndM_int, &Rec_Card_Preg_int, &Rec_Card_Endg_int, &Rec_Sum_Start, &Rec_Sum_End, &Rec_Begin_Press, &Rec_End_Press, &Car_hui, GAS_Stime, GAS_Etime))
            //           if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
        {
            SOEACTION1(PRO422_ERR, eCurRunState); //ͨ���쳣//6��ʵ�����õĲ���
            gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // ������¼   �ۿ���Ϣ����ʧ��
  //          return;
        }   
            else
            gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // ������¼   �ۿ���Ϣ���ͳɹ�
            ortcc_read_time(gas_record.grey_unlock_inif.time);                    // ������¼   ���ʱ��   �����ڴˣ����ʧ��Ҳ�ǿ��Ի�ȡ���ʱ���
      }
        ///////////////////�б��Ƿ��ǹ������е��Լ���///////////////////////////////150730
      if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //�ڹ����������ʱ�������ж� MAX_dubug_recid_num  ���ܳ���200���ɼ���
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
      /////////////////////////////////////////////////////////////
   if((hq_state==0x99)||(hq_state==0x98))//rg170330
     {
	 olcd_clearsCreen();
	 if(hq_state==0x99)//��������500
         SOEACTION1(C_HuiQi_ERR,eCurRunState);
	 if(hq_state==0x98)//������Ϊ��
	SOEACTION1(C_JiaQi_fu ,eCurRunState);	 
      }
  if((PRINT_SET ==1)&&(OKgas_GV != 0))//rg171127 ����Ϊ�㲻��ӡ
    oprint_operate_rec();
 //  else //rg170606��ӡ������
  //   Select_print();//�ֶ���ӡѡ�� //rg170606��ӡ������
    {                                                                       //��ȡ������¼
         UINT32 max_rec_id;

         gas_record.grey_unlock_inif.Balance_To = Rec_Card_EndM;              //  ������¼     ��ʣ���
         max_rec_id = get_max_rec_id();                                        // ������¼   ��ȡ���ذ�ļ�����ˮ��
         if(max_rec_id != 0xFFFF0000)
         {
             gas_record.gas_stream = max_rec_id;                             // ������¼  ������ˮ����Ϣ
         }
    }
      WiteRecorInfo_AN(gas_record);                                              // ������¼  ��������¼��Ϣд�뵽EEP��
    memset(&gas_record,0x00,sizeof(gas_record));                            // ������¼  ��ռ������̲����Ľṹ�建����Ϣ

  Gas_para_init();//�ÿ��˴μ�����Ϣȫ�����
  memset(CPH_IN,0x0,12);//rg170619 ���복�ƺ�
	         memset(CPH,0x0,12);//rg170619 ���복�ƺ�
		Cp_flag=0;//rg170619 ���복�ƺ�
 eVirtualKey = _KEY_EXIT_EV_;//ָ��Ϊ����״̬
}

/*------------------------------------------������������ʾ��----------------------------------------------------------*/
void olng_operate_disp(BOOL bInit,float gain,float ls,float temp)
{

    if( bInit )
	{
		    olcd_clearsCreen();
	//	    olcm_dispprintf(2,1,"���ڼ���");
		    olcm_dispprintf(0,2,"����: %3.02f",0.00);
		    olcm_dispprintf(0,3,"����: %3.02f",0.00);
                    olcm_dispprintf(0,4,"�¶�: %3.02f",0.00);
  	}
        else
	{
        	    olcm_dispprintf(0,2,"����: %3.02f    ",ls );
		    olcm_dispprintf(0,3,"����: %3.02f    ",gain);
                    olcm_dispprintf(0,4,"�¶�: %3.02f    ",(temp-(float)temp_add_vol));
  	}
}
void olng_operate_disp2(BOOL bInit,float GV,float desenty,float press)
{

		    olcm_dispprintf(0,2,"����: %3.02f    ",GV);
		    olcm_dispprintf(0,3,"�ܶ�: %3.02f  ",desenty);
                    olcm_dispprintf(0,4,"ѹ��: %3.02f    ",press);
     //               olcm_dispprintf(0,4,"                ");
}
void show_operat_stop(float GV,float AM)
{
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"��������");
    olcm_dispprintf(0,2,"������%.2f",GV);
    olcm_dispprintf(0,3,"��%.2f",AM);
}

BOOL olng_operate_put_card()//rg170717 
{
//    float pay;
     INT32 pay,jyje;
    UINT8 jy[20],qy[20];
    UINT8 len,i,*zz,len2;
    UINT8 * plen = &len;
    UINT8 car_state;//rg170713  ��Һ��ж�״̬�����3��
    INT8     j;//rg170713  ��Һ��ж�״̬�����3��
    	UINT8 test_cn[10];//RG170925
	UINT8 y,status,*pinfo,lenx;//RG170925
	y=1;//RG170925
	car_state=0;//rg170713  ��Һ��ж�״̬�����3��
 //_10ms_tick2_=0;
        len = sizeof(jy);
        memset(jy,0,20);
    gas_record.grey_unlock_inif.grey_status &=  0x0F;                          // ������¼   ��ս��״̬
//***************//RG170925********�ۿ�ǰ����֤�����Ƿ�һ��*********************************************************************//	
	ortcc_read_time(gas_record.grey_unlock_inif.time);                    // ������¼   ���ʱ��   �����ڴˣ����ʧ��Ҳ�ǿ��Ի�ȡ���ʱ���
	olng_operate_card_info(); 
        pinfo = ic_operate_info("CN", global_ic_card_info, &lenx);
        if (pinfo != NULL)
        {
           memset(test_cn, 0, sizeof (test_cn));
            memcpy(test_cn, pinfo, lenx);
            gas_record.card_id_js = (UINT32)atoi(test_cn);                                             // �������ַ�ת��Ϊ����  ss190306
        }
        else
        {
            
            memset(test_cn, '1', 10);                                                     // ���Ż�ȡʧ��,�����Ÿ���1 
            gas_record.card_id_js = (UINT32)atoi(test_cn);                                             // �������ַ�ת��Ϊ����  ss190306
            gas_record.grey_unlock_inif.grey_status |=  GREY_CARD_CHEKE_FAILL;                          // ���Ŵ����쳣 
            return FALSE;
        }
        
        y=memcmp(CN,test_cn,10);
        if(y != 0)
        { 
            SOEACTION1(carcmp_err,eCurRunState);
             gas_record.grey_unlock_inif.grey_status |=  GREY_CARD_CHEKE_FAILL;                          // ���Ŵ����쳣 ss190306
           return FALSE;	
        }
//********************************************************************************************//
    i=0;
    if(_CARD_TYPE==CARDT_SMALL)//rg170717 
	 return FALSE;   
    
    switch(CARD_XIAOFEI)
    {
        case   PREE_MONEY:
            pay =Rec_Card_EndM_int;//Rec_Card_PreM - (OKgas_GV - GAS_BACKGV)*Cur_Price;
            do
            {
              if(ic_card_put_money(pay) == FALSE) 
              {
                  gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��

                  return FALSE;
              }
                delay_ms(500);
                len = sizeof(jy);
                memset(jy,0,20);
                if(GetCard_info(02,jy,plen,10) == APDUS_SUCCESS)//���
                        {
                  zz =ic_operate_info_int(jy,&len2);
                  jyje=atoi(zz);
                        }
                i++;		  
            }while((Rec_Card_EndM_int!=jyje)&&(i<4));
            if(i>=4)
            {
              SOEACTION1(kk_w_err,eCurRunState);
              olcm_dispprintf(2,4,"�ۿ�У��ʧ��");
              gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
              return FALSE;
            }
            break;
        case PREE_GASE:
            pay = Rec_Card_Endg_int;
            do
              {
                if(ic_card_put_gass(pay) == FALSE) 
                {
                    gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
                    return FALSE;
                }
                  delay_ms(500);
                  len = sizeof(qy);
                  memset(qy,0,20);
                  if(GetCard_info(03,qy,plen,10) == APDUS_SUCCESS)//���
                          {
                            zz =ic_operate_info_int(qy,&len2);
                            jyje=atoi(zz);
                          }
                  i++;		  
              }while((Rec_Card_Endg_int!=jyje)&&(i<4));
                if(i>=4)
              {
                   SOEACTION1(kk_w_err,eCurRunState);
                olcm_dispprintf(2,4,"�ۿ�У��ʧ��");
                gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
                return FALSE;
              }
            break;
        case ACCOUNT_MONEY:
            pay = Rec_Card_EndM_int;//Rec_Card_PreM - OKgas_money;
               do
              {
                if(ic_card_put_money(pay) == FALSE)                // �ۿ����
                {
                    gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
                    return FALSE;
                }
                  delay_ms(500);
                  len = sizeof(jy);
                  memset(jy,0,20);
                  if(GetCard_info(02,jy,plen,10) == APDUS_SUCCESS)//���
                          {
                            zz =ic_operate_info_int(jy,&len2);
                            jyje=atoi(zz);
                          }
                  i++;
               }while((Rec_Card_EndM_int!=jyje)&&(i<4));
                if(i>=4)
              {
                   SOEACTION1(kk_w_err,eCurRunState);
                olcm_dispprintf(2,4,"�ۿ�У��ʧ��");
                gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
                return FALSE;
              }
            break;
        case ACCOUNT_GASS:
             pay = Rec_Card_Endg_int;//Rec_Card_Preg - OKgas_GV;
                do
              {
                if(ic_card_put_gass(pay) == FALSE) 
                {
                    gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
                    return FALSE;
                }
                  delay_ms(500);
                  len = sizeof(qy);
                  memset(qy,0,20);
                  if(GetCard_info(03,qy,plen,10) == APDUS_SUCCESS)//���
                          {
                             zz =ic_operate_info_int(qy,&len2);
                             jyje=atoi(zz);
                          }
                  i++;		  
              }while((Rec_Card_Endg_int!=jyje)&&(i<4));
                if(i>=4)
              {
                SOEACTION1(kk_w_err,eCurRunState);
                olcm_dispprintf(2,4,"�ۿ�У��ʧ��");
                gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // ������¼  �ۿ�ʧ��
                return FALSE;
              }
            break;
            
             default :                                                           // ss190306  �ۿ��쳣�������
                gas_record.grey_unlock_inif.grey_status |= GREY_ACCOUNTS_STATU_FAILL;           // СƱ��Ϣ�������ѷ�ʽ�쳣��� 
                    return FALSE;
                break;
    }
//*****************//rg170713  ��Һ��ж�״̬�����3��************************************************************//    
	j = 3;
	while (j) 
        {
            if (TRUE == ic_card_put_status(CARDS_NORMAL)) 
            {
                delay_ms(50);
                car_state = ic_card_get_status_nosel();
                if (car_state == CARDS_NORMAL) 
                {
                    ortcc_read_time(gas_record.grey_unlock_inif.time);                    // ������¼   ���ʱ��       
                    gas_record.grey_unlock_inif.grey_status  |=  GREY_UNLUCK_SUCC;                          // ������¼  ��ҳɹ�
                    return TRUE;
                }
            }
            j--;
            delay_ms(50);
	}

	if (j <= 0)
        {
            gas_record.grey_unlock_inif.grey_status |=  GREY_UNLUCK_FAILL;                          // ������¼  �ۿ���ɣ�δ���
		return FALSE;
        }
//******************************************************************************//	
}
void offwork_print(UINT8 *car,UINT32 rec,UINT32 class_q,UINT32 class_h,UINT32 gain_q,UINT32 gain_h)
{
         char buf[50];
         UINT8 carnum[11];
 //     _shift_loginfo  pr_sysinfo;
         memset(carnum,0,11);
         memcpy(carnum,car,10);
	 	 UINT8 num,i;//rg170707
     ortcc_read_time((UINT8*)&sys_time[0]);
         //////////////////rg170707////////////////////////////////
      if (TRUE != qty_get_sw(&num)) {//ͨ���쳣

				SOEACTION1(PRO422_ERR, eCurRunState);
//				return;
			}
    i = (num >> 5)&0x01;  
    /////////////////////////////////////////////////
     oprint_header_cmd();
    
   oprint_normal_cmd();
    oprint_printf("�°��¼\r\n"); //cur_sysparas
 
    oprint_printf("\r\n");
    oprint_printf("վ��:%d\r\n", Cur_StationNo);
    oprint_printf("ǹ��:%d\r\n", cur_sysparas.p_gid );//cur_shiftid
    oprint_printf("����:%d\r\n", cur_shiftid );
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", carnum);
    oprint_printf("����:%s\r\n",buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", rec);
    oprint_printf("����ˮ��:%s\r\n",buf);

    oprint_printf("��������:%d\r\n",class_q);
         if(i == 1)//rg170707
    { oprint_printf("��ֵ����:%d.%02d kg\r\n",class_h/100,class_h%100);
    oprint_printf("��ʼǹ��:%d.%02d kg\r\n",gain_q/100,gain_q%100);
    oprint_printf("����ǹ��:%d.%02d kg\r\n",gain_h/100,gain_h%100);}
    else if(i == 0)//rg170519
    {
	 oprint_printf("��ֵ����:%d.%02d m3\r\n",class_h/100,class_h%100);
    oprint_printf("��ʼǹ��:%d.%02d m3\r\n",gain_q/100,gain_q%100);
    oprint_printf("����ǹ��:%d.%02d m3\r\n",gain_h/100,gain_h%100);    
    }
    else//rg170519
    {
	 oprint_printf("��ֵ����:%d.%02d m3\r\n",class_h/100,class_h%100);
    oprint_printf("��ʼǹ��:%d.%02d m3\r\n",gain_q/100,gain_q%100);
    oprint_printf("����ǹ��:%d.%02d m3\r\n",gain_h/100,gain_h%100);      
    }
   // oprint_printf("��ʼǹ��:%.02f kg\r\n",gain_q);
   // oprint_printf("����ǹ��:%.02f kg\r\n",gain_h);
    if((Sign_Name[0]!=0x00)||(Sign_Name[1]!=0x00)||(Sign_Name[2]!=0x00))//rg170707
    {//rg160907
    memset(buf, 0, sizeof(buf));//rg160907
    sprintf(buf, "%s", Sign_Name);//rg160907
    oprint_printf("Ա����:%s\r\n",buf);//rg160907
    }//rg160907
    oprint_printf("����:20%02d��%02d��%02d��\r\n", sys_time[0],sys_time[1], sys_time[2]);
    oprint_printf("ʱ��:%02dʱ%02d��%02d��",sys_time[3], sys_time[4], sys_time[5]);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
       if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
       else
    oprint_printf("��̨����·��һ����վ\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");


}
void oprint_qry_easy_rec(void)
{
	UINT8 yu[12],*yp;//rg170607
	UINT8 num,i;//rg170607
    UINT8 buf[20];
    //rg170607
    if (TRUE != qty_get_sw(&num)) {//ͨ���쳣

				SOEACTION1(PRO422_ERR, eCurRunState);
//				return;
			}
    oprint_header_cmd();
    if(Hard_Info[0]==0)
    oprint_printf("��ӭʹ�ý���LNG������\r\n"); //cur_sysparas
    else
    oprint_printf(Hard_Info);
    oprint_normal_cmd();
    oprint_printf("\r\n");
 
    oprint_printf("վ��:%d\r\n", Cur_StationNo);
    oprint_printf("ǹ��:%d\r\n", cur_sysparas.p_gid );
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN_PRINT);
    oprint_printf("����:%s\r\n",buf);
    sprintf(buf, "%s", CP_PRINT);//rg170607 ������Ϣ���ƺ�
    oprint_printf("���ƺ�:%s\r\n",buf);//rg170607 ������Ϣ���ƺ�
    
    oprint_printf("��ˮ��:%d\r\n",ID_PRINT);
       i = (num >> 5)&0x01;//��ǣ�rg170707
			if (i == 1)
			{ 
				oprint_printf("����:%.02f Ԫ/kg\r\n",DJ_PRINT);
				oprint_printf("������:%.02f kg\r\n",QL_PRINT);
			
			}
			else if (i == 0)
			{
				oprint_printf("����:%.02f Ԫ/m3\r\n",DJ_PRINT);	
			oprint_printf("������:%.02f m3\r\n",QL_PRINT);
			
			}
			else
			{
				oprint_printf("����:%.02f Ԫ/kg\r\n",DJ_PRINT);	
			oprint_printf("������:%.02f kg\r\n",QL_PRINT);
			
			}	
 //   oprint_printf("������:%.02f kg\r\n",QL_PRINT);
 //   oprint_printf("����:%.02f Ԫ/kg\r\n",DJ_PRINT);
    oprint_printf("���:%.02fԪ\r\n",JE_PRINT);
    if(HQ_PRINT==0)//rg180131
    oprint_printf("������:%.02fkg\r\n",HQL_PRINT);//rg180131
    if(CN_PRINT[2] != 0x35)//rg170717
    {
        yp=inttoa(KY_PRINT);//rg170607 ������Ϣ���ƺ�
        memset(yu,0x00,12);//rg170607 ������Ϣ���ƺ�
        memcpy(yu,yp,10);//rg170607 ������Ϣ���ƺ�
        oprint_printf("����:%sԪ\r\n",yu);//rg170607 ������Ϣ���ƺ�
    }
         if(PR_YGH != 0)
    {
    oprint_printf("Ա����:%03d\r\n",PR_YGH);//rg160907
    }
    oprint_printf("����:20%02d��%02d��%02d��\r\n", RQ_PRINT[0],RQ_PRINT[1], RQ_PRINT[2]);
    oprint_printf("ʱ��:%02dʱ%02d��%02d��",RQ_PRINT[3], RQ_PRINT[4], RQ_PRINT[5]);

   oprint_printf("\r\n");
   oprint_printf("********��ѯƱ����********\r\n");
    oprint_printf("\r\n");
    if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
    if(Contact_Info[0]!=0)
    {
    oprint_printf(Contact_Info);
    }
     oprint_printf("\r\n");
    oprint_printf("----��ӭ�´ι���----\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
 
}
void oprint_operate_rec(void)
{
       UINT8 e =0;
       UINT8 st;
       float i_ls_add = 0;
      char buf[50];
      UINT16 zkk;
      UINT8 yu[12],*yp,get_time[6];
  //    ortcc_read_time((UINT8*)&sys_time[0]);
      BOOL str;
      st=0;
      str=TRUE;
      str=ortcc_read_time((UINT8*)&sys_time[0]);
     if(FALSE==str)
     {//rg180523
	     delay_ms(1000);
	      float dj;float je;float ql;
	float hq;
        UINT8 edati[6],cn[10];
	UINT16 ygh;
	UINT32 ky;
	UINT8 cp[12],wz;
	memset(cp,0x0,12);
//	   if(TRUE != qty_get_serrec(pr_lsh,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq))//RG160907//rg170607 ������Ϣ���ƺ�
    if(TRUE != qty_get_serrec(pr_lsh,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq,&wz))//RG160907//rg170607 ������Ϣ���ƺ�
       {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
//           return;
       }  
	st=1;
	memcpy(get_time,edati,6);
     }
    oprint_header_cmd();
    if(Hard_Info[0]==0)
    oprint_printf("��ӭʹ�ý���LNG������\r\n"); //cur_sysparas
    else
    oprint_printf(Hard_Info);
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("վ��:%d\r\n", Cur_StationNo);
    oprint_printf("ǹ��:%d\r\n", cur_sysparas.p_gid );
    oprint_printf("����:%d\r\n", cur_shiftid );
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", pr_lsh);
      if(CN[2] !='3')
      {  oprint_printf("��ˮ��:%s\r\n",buf);  }
      else
      {
          oprint_printf("������ˮ��:%d\r\n",MAX_dubug_recid_num);
      }

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN);
    oprint_printf("����:%s\r\n",buf);

//    oprint_printf("��Һ��(Һ��):%.02f kg\r\n",OKgas_GV+GAS_BACKGV);
//    oprint_printf("������(����):%.02f kg\r\n",GAS_BACKGV);
  //  zkk=(Discount[0]<<8)+Discount[1];
//    0,4,"%3d ��  %2x%02x%02x%02x",zk[1],qx[0],qx[1],qx[2],qx[3])
 //   sprintf(buf, "%2f",Discounf);
    if(Discounf!=100)
    {oprint_printf("�ۿ�ϵ��:%0.2f ��\r\n",Discounf);
  oprint_printf("�ۿ���Ч��:%02x%02x/%02x/%02x\r\n",Discount_validity[0],Discount_validity[1],Discount_validity[2],Discount_validity[3]);
    }
oprint_printf("ִ�е���:%.02f Ԫ/kg\r\n",Cur_Price);

    oprint_printf("������:%.02f kg\r\n",OKgas_GV);
    if(HQ_PRINT==0)//rg180131
    oprint_printf("������:%.02fkg\r\n",GAS_BACKGV);//rg180131
//    oprint_printf("����:%.02f Ԫ/kg\r\n",PRICE);
    oprint_printf("���:%.02fԪ\r\n",OKgas_money);
    if(_CARD_TYPE != CARDT_SMALL)//rg170717
    {
    if((CARD_XIAOFEI==0)||(CARD_XIAOFEI==2))
    {
	    yp=inttoa(Rec_Card_EndM_int);
      memset(yu,0x00,12);
      memcpy(yu,yp,10);
        oprint_printf("���:%sԪ\r\n",yu);
    }
    else if((CARD_XIAOFEI==1)||(CARD_XIAOFEI==3))
    { 
	    yp=inttoa(Rec_Card_Endg_int);
      memset(yu,0x00,12);
      memcpy(yu,yp,10);
     oprint_printf("���:%s kg\r\n",yu);
    }
    }
#if 1
/*    if((CPBH[0]!=0x00)&&(CPBH[1]!=0x00))
    {
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CPBH);
    oprint_printf("���ƺ�:%s\r\n",buf);
    }*/
                if(CPH[0]!=0x00)//rg170620
        {
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s", CPH);
        oprint_printf("���ƺ�:%s\r\n",buf);
        }
    //rg170620
/*    if(GPBH[0]!=0x00)
    {
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", GPBH);
    oprint_printf("��ƿ��:%s\r\n",buf);
    }*/
#endif
  //  pyygh=atoi(Sign_Name);//rg160907
  //  if(pyygh !=0)//rg160907
    if((Sign_Name[0]!=0x00)||(Sign_Name[1]!=0x00)||(Sign_Name[2]!=0x00))//rg170620
    {//rg160907
    memset(buf, 0, sizeof(buf));//rg160907
    sprintf(buf, "%s", Sign_Name);//rg160907
    oprint_printf("Ա����:%s\r\n",buf);//rg160907
    }//rg160907
    if(st==0)
    {
	    oprint_printf("����:20%02d��%02d��%02d��\r\n", sys_time[0],sys_time[1], sys_time[2]);
    oprint_printf("ʱ��:%02dʱ%02d��%02d��",sys_time[3], sys_time[4], sys_time[5]);
    }
    else
    {
	  oprint_printf("����:20%02d��%02d��%02d��******\r\n", get_time[0],get_time[1], get_time[2]);
    oprint_printf("ʱ��:%02dʱ%02d��%02d��******",get_time[3], get_time[4], get_time[5]);  
    }
 //  oprint_printf("\r\n");
    st=0;
    oprint_printf("\r\n");
    if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
    if(Contact_Info[0]!=0)
    { 
    oprint_printf(Contact_Info);
    }
    oprint_printf("\r\n");
//rg170620
 /*   oprint_printf("********************\r\n");
    oprint_printf("****Random%02d%.02f%02d%.02f%d%02d*****\r\n", (sys_time[4]+1),(Cur_Price+OKgas_GV),(sys_time[1]*2),(OKgas_GV+111.11),(pr_lsh+10),(sys_time[2]+sys_time[5]));//�ּ�1��ִ�е��ۼ��������³�2,������111.11����ˮ�ż�10���ռ��룻

    if(Add_Gas_CS >1)
    {
      
        oprint_printf("==%d==", Add_Gas_CS-1);

     for(e=1;e<=Add_Gas_CS;e++)
     { 
         if(e<Add_Gas_CS-1)
          {
             oprint_printf("%.02f/%.02f/",Every_add_Gas[e],Every_add_Gas[++e]);
             i_ls_add =  i_ls_add +Every_add_Gas[e]+Every_add_Gas[e-1];
          }
          else if(e==Add_Gas_CS-1)
          { oprint_printf("%.02f/",Every_add_Gas[e]);
             i_ls_add =  i_ls_add +Every_add_Gas[e];
          }

          else if(e>Add_Gas_CS-1)
          oprint_printf("%.02f \r\n",OKgas_GV- i_ls_add);
     }

    }*/
//    oprint_printf("��̨����·��һ����վ\r\n");
   
    oprint_printf("----��ӭ�´ι���----\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");


}
void oprint_operate_recact(void)
{
        char buf[50];
 //     _shift_loginfo  pr_sysinfo;
     ortcc_read_time((UINT8*)&sys_time[0]);
    oprint_header_cmd();
    oprint_header_cmd();
   if(Hard_Info[0]==0)
    oprint_printf("��ӭʹ�ý���LNG������\r\n"); //cur_sysparas
    else
    oprint_printf(Hard_Info);
//    oprint_printf("��ӭʹ�ý���LNG������\r\n"); //cur_sysparas
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");
       oprint_printf("վ��:%d\r\n", Cur_StationNo);
    oprint_printf("ǹ��:%d\r\n", cur_sysparas.p_gid );

     memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", pr_lsh);
    oprint_printf("��ˮ��:%s\r\n",buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN);
    oprint_printf("����:%s\r\n",buf);
        oprint_printf("�ۿ�ϵ��:%s\r\n",buf);
    sprintf(buf, "%s",Discount_validity);
    oprint_printf("�ۿ���Ч��:%s\r\n",buf);
 oprint_printf("ִ�е���:%.02f Ԫ/kg\r\n",Cur_Price);

    oprint_printf("��Һ��:%.02fkg\r\n",OKgas_GV);
    oprint_printf("������:%.02fkg\r\n",GAS_BACKGV);

    oprint_printf("������:%.02fkg\r\n",OKgas_GV - GAS_BACKGV);
//    oprint_printf("����:%.02fԪ/kg\r\n",PRICE);
    oprint_printf("���:%.02fԪ\r\n",(OKgas_GV - GAS_BACKGV)*Cur_Price);
    oprint_printf("����:20%02d��%02d��%02d��\r\n", sys_time[0],sys_time[1], sys_time[2]);
    oprint_printf("ʱ��:%02dʱ%02d��%02d��",sys_time[3], sys_time[4], sys_time[5]);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    if(Print_Info[0]!=0)
   oprint_printf(Print_Info);
if(Contact_Info[0]!=0)
    oprint_printf(Contact_Info);
 //   oprint_printf("��̨����·��һ����վ\r\n");
    oprint_printf("----��ӭ�´ι���----\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
}
void Get_gas_money()
{
           if((CARD_XIAOFEI>=2)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)))//��˾����˽�����ļ�������
        {
                if((CARD_XIAOFEI==2)&&(mlc>0))
                {
                car_prem=mlc-fabs(Rec_Card_PreM);
                car_prel=0;
                }
                else if((CARD_XIAOFEI==3)&&(glc>0))
                {
                car_prel=glc-fabs(Rec_Card_Preg);
                car_prem=0;
                }
                else
                {
                    if(Rec_Card_PreM!=0)
                    {
                 car_prem=Rec_Card_PreM;
                 car_prel=0;}
                    else if(Rec_Card_Preg!=0)
                    {
                 car_prel=Rec_Card_Preg;
                 car_prem=0;
                    }
                    else
                    {
                        car_prel=0;
                        car_prem=0;
                    }
                 }
        }
        else if((CARD_XIAOFEI<2)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)))//��˾����˽������Ԥ������
        {
           car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
        }
	 else if(_CARD_TYPE==CARDT_SMALL)//rg170717 ��̨�������Ƕ��+��ֱ�ӿ�����
	{
		car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
	}  
	   
        else if(_CARD_TYPE==1)                            //���鿨һ���Ǽ�������
        {
            car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
        }
	
        else                                                //�������
        {
            car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
        }
}
BOOL Judge_sct_Minimum(float *carprem)
{
    if(CARD_XIAOFEI==PREE_MONEY)
    {
        if(car_prem < FIX_Money)
        {
        *carprem=car_prem;
         return FALSE;
        }
       else if((car_prem-Mini_FD) < FIX_Money)//rg170606��С������
        {
          *carprem=car_prem;
          FIX_Money=car_prem-Mini_FD;//rg170606��С������
         return TRUE;
        }
        else
            return TRUE;
    }

    else if(CARD_XIAOFEI==PREE_GASE)
    {
        if(car_prel*Cur_Price < FIX_Money)
        {
        *carprem=car_prel*Cur_Price;
          return FALSE;
        }
        else if((car_prel*Cur_Price-Mini_FD) < FIX_Money)//rg170606��С������
        {
          FIX_Money=car_prel*Cur_Price-Mini_FD;//rg170606��С������
          return TRUE;
        }
        else
            return TRUE;
    }
 
     else if((CARD_XIAOFEI==ACCOUNT_MONEY)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)))//�û������˽��
     {
         if((mlc-fabs(Rec_Card_PreM))<FIX_Money)
         {
             *carprem=Rec_Card_PreM;
//             FIX_Money=mlc-fabs(Rec_Card_PreM);
             return FALSE;
         }
         else if((mlc-fabs(Rec_Card_PreM)-Mini_FD)<FIX_Money)//rg170606��С������
         {
             *carprem=Rec_Card_PreM;
             FIX_Money=mlc-fabs(Rec_Card_PreM)-Mini_FD;//rg170606��С������
             return TRUE;
         }
         else
         { //*get_money=FIX_Money;
         return TRUE;}
     }
     else if((CARD_XIAOFEI==ACCOUNT_GASS)&&((_CARD_TYPE==3)||(_CARD_TYPE==2)))////�û�����������
     {
         if((glc-fabs(Rec_Card_Preg))*Cur_Price<FIX_Money)
         {
             *carprem=Rec_Card_Preg;
             return FALSE;
         }
         else if(((glc-fabs(Rec_Card_Preg))*Cur_Price-Mini_FD)<FIX_Money)//rg170606��С������
         {
             *carprem=Rec_Card_Preg;
             FIX_Money=(glc-fabs(Rec_Card_Preg))*Cur_Price-Mini_FD;//rg170606��С������
             return TRUE;
         }
         else
         {
         return TRUE;}
     }
	else if((CARD_XIAOFEI==ACCOUNT_MONEY)&&(_CARD_TYPE==CARDT_SMALL))//�û������˽�� //rg170717  �ӿ�
	{
		if(car_prem <= FIX_Money)
		{
		*carprem=car_prem;
		 return FALSE;
		}
        else if(car_prem <= smallMini_FD)
        {
            *carprem=car_prem;
		 return FALSE;
        }
        else  if((car_prem-smallMini_FD) < FIX_Money)//rg170606��С������//rg181210
		{
		  *carprem=car_prem;
		  FIX_Money=car_prem-smallMini_FD;//rg170606��С������//rg181210
		 return TRUE;
		}
		else
		    return TRUE;
	}	
    else if(((CARD_XIAOFEI==ACCOUNT_GASS)||(CARD_XIAOFEI==ACCOUNT_MONEY))&&(_CARD_TYPE==1))////���鿨��������
    {
         //*get_money=FIX_Money;
        return TRUE;
    }
}
BOOL Get_again_gas_money(float *max_mone)//rg170717 �����ӿ������ж�
{
     if((car_prel>1)&&( car_prem==0)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//���������������ּ��˺�Ԥ�� //rg170717 �����ӿ������ж�
    {
     *max_mone= car_prel*Cur_Price- OKgas_money;
     return TRUE;
    }
    else if((car_prel==0)&&(car_prem>=Cur_Price)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//�����������ּ��˺�Ԥ�� //rg170717 �����ӿ������ж�
    {
    *max_mone = car_prem - OKgas_money;//�ɼ����Ľ�� = ����ǰ����-���μ�����(�ۼ���)
    return TRUE;
    }

    else if((_CARD_TYPE==1)&&(CARD_XIAOFEI==2))  //���鿨�����˽��
    {
    *max_mone = car_prem - OKgas_money;//�ɼ����Ľ�� = ����ǰ����-���μ�����(�ۼ���)
    return TRUE;
    }
    else if((_CARD_TYPE==1)&&(CARD_XIAOFEI==3))  //���鿨����������
    {
    *max_mone = car_prel*Cur_Price - OKgas_money;//�ɼ����Ľ�� = ����ǰ����-���μ�����(�ۼ���)
    return TRUE;
    }
    else
    {
        *max_mone = 0;
        return FALSE;
    }
}
BOOL olngctrl_juPSW(UINT8 *xx)//rg170621  �忨��������
{
    UINT8 passbuf[10],CARTYPE,carstate;
    UINT8 pass[10],passy[10];
    UINT8 len1,len2 = 6;
    UINT8  *pinfo,*p;//rg170619
    UINT8 car_state;
    UINT8 kh[10];
    UINT8 bj;
    UINT8 car_status;//RG170705
    bj=0;
    *xx=0;
    memset(passy,0x0,10);
    memset(passy,0x30,6);
    memset(kh,0x0,10);
   if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531�޿�����
    {
	   car_status = machine_status_card();
	    while(car_status!=CPU_TYPE_A)
        {
           olcm_dispprintf(0,1,"����������    ");
           olcm_dispprintf(0,2,"                ");
           olcm_dispprintf(0,3,"  �����ļ��˳�  ");
           olcm_dispprintf(0,4,"                ");
           ostatemachine_getkey();
          if(b_keyv == TRUE)
            { b_keyv = FALSE;
                return FALSE;
              }
        }
    }

      olng_operate_card_info_nosel();
     pinfo = ic_operate_info("CDT",global_ic_card_info, &len1);
    if(pinfo==NULL)
   {
	    if(WKJQ==1)//rg170531�޿�����
	    {
		    *xx=1;
		    return FALSE;
	    }
   }
      if(pinfo !=NULL)
      {
         CARTYPE= ic_card_get_type(pinfo,len1);
	if(CARTYPE == CARDT_ADMINI)
	{
		if(Is_debuggas_Read != 1)//RG170705
		{
			*xx=2;
			return FALSE;
		}
		else
			return TRUE;//RG170705
	}
	 else if(CARTYPE == CARDT_MOTHER)//r170717g
	{
			*xx=14;
			return FALSE;
	}	
         carstate=ic_card_get_status_nosel();
             if(carstate==CARDS_GREY)
            {
		     if(((WKJQ ==0)&&(CARTYPE == CARDT_CLASS))||(CARTYPE == CARDT_SMALL))//rg170531�޿�����rg180322
			     return TRUE;
		     else
		     {  
			     *xx=3;
		            return FALSE;
		     }
            }
            if(carstate==CARDS_NULLIFY)
            {
		    if((WKJQ ==0)&&(CARTYPE == CARDT_CLASS))//rg170531�޿�����
			     return TRUE;
		    else
		    {
				    *xx=8;
				return FALSE;
		    }
            }
#if 1 //rg170607 �忨����֤����
  if((memcmp(pinfo,"40000002",len1) == 0) ||(memcmp(pinfo,"40000003",len1) == 0)||(memcmp(pinfo,"40000005",len1) == 0))// class group card//r170717g
    {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//��ÿ�����
	if(strcmp(passy, passbuf) == 0)
        {
            *xx=4;
           return TRUE;
        }
	          p = ic_operate_info("CN",global_ic_card_info, &len1);
                                                       if(p==NULL)
                               {
                                    *xx=1;
				return FALSE;
                               }
                                                       else
                                                       {
                                                           memcpy(kh,p,10);
                                                       }
		  bj=strcmp(cure_yz_card, kh);
		if(bj == 0)//rg170621  �忨��������
        {
            *xx=4;
           return TRUE;
        }
        else
        {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--������֤--");
        olcm_dispprintf(0,2,"�����뿨����  ");
        olcm_dispprintf(0,3,"����:  ");
	memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //�����ڲ��뿨ʱ�Ѿ����
		 bj=strcmp(pass, passbuf);
                 if((len2 == len1)&&(bj == 0))
                      {
                             *xx=5;
                                return TRUE;
                      }
                 else
                   //�������
                 {
                    *xx=6;
                  return FALSE;
                 }
            }
         else
         {*xx=7;
           return FALSE;}
        }
        }
  else if((memcmp(pinfo,"40000001",len1) == 0)&&(WKJQ==1))// class group card
    {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//��ÿ�����
	if(strcmp(passy, passbuf) == 0)
        {
            *xx=4;
           return TRUE;
        }
	         p = ic_operate_info("CN",global_ic_card_info, &len1);
                                                       if(p==NULL)
                               {
                                    *xx=1;
				return FALSE;
                               }
                                                       else
                                                       {
                                                           memcpy(kh,p,10);
                                                       }
		 bj=strcmp(cure_yz_card, kh);
		if(bj == 0)//rg170621  �忨��������
        {
            *xx=4;
           return TRUE;
        }
        else
        {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--������֤--");
        olcm_dispprintf(0,2,"�����뿨����  ");
        olcm_dispprintf(0,3,"����:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //�����ڲ��뿨ʱ�Ѿ����
		 bj=strcmp(pass, passbuf);
                 if((len2 == len1)&&(bj == 0))
                      {
                             *xx=5;
                                return TRUE;
                      }
                 else
                   //�������
                 {
                    *xx=6;
                  return FALSE;
                 }
            }
         else
         {*xx=7;
           return FALSE;}
        }
        }
#endif
      }
      else if(WKJQ==0)
	      return TRUE;
    }
double Get_Gp_Time(UINT8 *qx)//�����ƿ�Ƿ���
{
    double data;
    time_t TM1_t,TM2_t;
    UINT8 zh[4],qq[4];
    memset(qq,0x00,4);
    memcpy(qq,qx,4);
    ortcc_read_time(GAS_Stime);
    zh[0]=(((qq[0]&0xf0)>>4)*10)+(qq[0]&0x0f);
    zh[1]=(((qq[1]&0xf0)>>4)*10)+(qq[1]&0x0f);
    zh[2]=(((qq[2]&0xf0)>>4)*10)+(qq[2]&0x0f);
    zh[3]=(((qq[3]&0xf0)>>4)*10)+(qq[3]&0x0f);

    tm1.tm_sec = 0x00;
    tm1.tm_min = 0x00;
    tm1.tm_hour = 0x00;
    tm1.tm_mday = zh[3];
    tm1.tm_mon = zh[2];
    tm1.tm_year = zh[0]*100 + zh[1];

    tm2.tm_sec = GAS_Stime[5];
    tm2.tm_min = GAS_Stime[4];
    tm2.tm_hour = GAS_Stime[3];
    tm2.tm_mday = GAS_Stime[2];
    tm2.tm_mon = GAS_Stime[1];
    tm2.tm_year = 2000 + GAS_Stime[0];

    TM1_t = mktimesec(tm1.tm_year,tm1.tm_mon,tm1.tm_mday,tm1.tm_hour,tm1.tm_min,tm1.tm_sec);
    TM2_t = mktimesec(tm2.tm_year,tm2.tm_mon,tm2.tm_mday,tm2.tm_hour,tm2.tm_min,tm2.tm_sec);
    data = TM1_t - TM2_t;
    return data;
}
double CalcPCTimeAndLNGTime(void)
{
    double data;
    time_t TM1_t,TM2_t;
    UINT8 zh[4];
    ortcc_read_time(GAS_Stime);
    zh[0]=(((Discount_validity[0]&0xf0)>>4)*10)+(Discount_validity[0]&0x0f);
    zh[1]=(((Discount_validity[1]&0xf0)>>4)*10)+(Discount_validity[1]&0x0f);
    zh[2]=(((Discount_validity[2]&0xf0)>>4)*10)+(Discount_validity[2]&0x0f);
    zh[3]=(((Discount_validity[3]&0xf0)>>4)*10)+(Discount_validity[3]&0x0f);

    tm1.tm_sec = 0x00;
    tm1.tm_min = 0x00;
    tm1.tm_hour = 0x00;
    tm1.tm_mday = zh[3];
    tm1.tm_mon = zh[2];
    tm1.tm_year = zh[0]*100 + zh[1];

    tm2.tm_sec = GAS_Stime[5];
    tm2.tm_min = GAS_Stime[4];
    tm2.tm_hour = GAS_Stime[3];
    tm2.tm_mday = GAS_Stime[2];
    tm2.tm_mon = GAS_Stime[1];
    tm2.tm_year = 2000 + GAS_Stime[0];

    TM1_t = mktimesec(tm1.tm_year,tm1.tm_mon,tm1.tm_mday,tm1.tm_hour,tm1.tm_min,tm1.tm_sec);
    TM2_t = mktimesec(tm2.tm_year,tm2.tm_mon,tm2.tm_mday,tm2.tm_hour,tm2.tm_min,tm2.tm_sec);
    data = TM1_t - TM2_t;
    return data;
 //   return labs(data);

}
//������
//Mengfr 2014.11.26 //mfr1104
unsigned long mktimesec (unsigned int year, unsigned int mon,unsigned int day, unsigned int hour,unsigned int min, unsigned int sec)
{
    if (0 >= (int) (mon -= 2)) {    /* 1..12 -> 11,12,1..10 */
         mon += 12;      /* Puts Feb last since it has leap day */
         year -= 1;
    }

    return (((
             (unsigned long) (year/4 - year/100 + year/400 + 367*mon/12 + day) +
             year*365 - 719499
          )*24 + hour /* now have hours */
       )*60 + min /* now have minutes */
    )*60 + sec; /* finally seconds */
}
float Get_zk()
{
    double tii;
     UINT16 zkk;
    float price_x;
//    Pr_gr = 1;                    //�۸�ȼ�
       switch (Pr_gr)
    {
     case 1:price_x=PRICE;
            break;
     case 2:price_x=PRICE2;
            break;
     case 3:price_x=PRICE3;
            break;
     case 4:price_x=PRICE4;
            break;
     case 5:price_x=PRICE5;
            break;
     case 6:price_x=PRICE6;
            break;
     case 7:price_x=PRICE7;
            break;
     case 8:price_x=PRICE8;
            break;
     case 9:price_x=PRICE9;
            break;
     case 10:price_x=PRICE10;
            break;
     default:
            price_x=PRICE;
            break;
    }
    tii=CalcPCTimeAndLNGTime();
    if((tii<3600)||(ZK_POWER>=1))
    {
       Discounf=100.0;                  //�ۿ���Ч
  
    }
    Cur_Price=price_x*Discounf/100;
    Cur_Price = sys_get_float(Cur_Price); //4��5��
    return Cur_Price;
}

BOOL get_car_info()
{
    UINT8 i = 4;
    UINT8 pswread[8],psws[8],type,xf,pr;
    int y;
    INT32 m_int;
   INT32 g_int;
   float m_f,g_f;
    while(i)
    {
        i--;
   if(TRUE == ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity,CPBH,GPBH))//��ÿ���Ϣ
           {   delay_ms(400);
                if(TRUE ==  ReadCard_info(&type,CN,&m_f,&g_f,&m_int,&g_int,&mlc,&glc,&xf,&pr,&Discounf,Discount_validity,CPBH,GPBH))
                {
                    if((_CARD_TYPE==type)&&(Rec_Card_PreM==m_f)&&(Rec_Card_Preg==g_f)&&(Rec_Card_PreM_int==m_int)\
                      &&(Rec_Card_Preg_int==g_int)&&(CARD_XIAOFEI==xf)&&(Pr_gr==pr))
                      {
                         return TRUE;
                      }
                      delay_ms(400);
                    }
         }
    }
    return FALSE;
}
UINT8 * ic_conv_un_lj(UINT8 * pstr)//150824
{
    UINT8 lenb;
    UINT8 * p1, * p2,* pb;
    UINT8 pint,sumlen,szcx;
    UINT8 bock[10],zh[10],i=0,j=0;
    UINT8 in[10],g_p[10],g_pb[10];
    float g_pf;
     pint=0;sumlen=0;
    pb=pstr;
    lenb=sizeof(pstr);
    memset(in,0x00,10);
    memset(g_pb,0x00,10);
    memset(g_p,0x00,10);
    memset(zh,0x00,10);
    memcpy(zh,pstr,10);
    p1 = strchr(pstr, '.');
    while(i<=10)
    {
        if(*(pb+j) == 0x2e)
        {pint=j;
            j++;}
        if(*(pb+j) == 0x00)
        {sumlen=i;//sumlen�����9
            break;}
        bock[i]=*(pb+j);
        j++;
        i++;
    }
    szcx=sumlen-pint;
    if(pint>=1)
    {
    memcpy(in,zh,pint-1);
    memcpy(g_p,&zh[pint-1],szcx+2);
    g_pf=(float)atof(g_p);
    g_pf=sys_get_float(g_pf);//ȡ��λ������С��
    sprintf(g_pb,"%.02f",g_pf);
    memcpy(&in[pint-1],g_pb,4);
    }
    else
     memcpy(in,zh,10);   
     p2=&in[0];
     return p2;
}
void oprint_qry_to_rec(void)//RG170620
{
UINT8 yu[12],*yp;//rg170620
 UINT8 buf[20];
 UINT8 num,i;
 UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;

      //   SOEACTION1(PRO422_ERR,eCurRunState);//���ڹ���
       //    return;
     olcd_clearsCreen();
      olcm_dispprintf(0,1,"����������ͨ��");
      cur_max_recid = get_max_rec_id();
     if(0xFFFF0000 ==cur_max_recid)
      {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
//        delay_ms(3000);
        id = maxid = cur_max_recid;//init����
        if( id == 0 ){
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"����ˮ��¼��");
             osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_VIRTUAL_EV_;

            return;
        }
float dj;float je;float ql;UINT32 *recg;
float hq;
        UINT8 edati[6],cn[10];
	UINT16 ygh;//RG160907
	UINT32 ky;//rg170607 ������Ϣ���ƺ�
	UINT8 cp[12],wz;//rg170607 ������Ϣ���ƺ�
	memset(cp,0x0,12);//rg170607 ������Ϣ���ƺ�
//       if(TRUE != qty_get_serrec(id,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq))//RG160907//rg170607 rg180131������Ϣ���ƺ�
     if(TRUE != qty_get_serrec(pr_lsh,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq,&wz))//RG160907//rg170607 ������Ϣ���ƺ�
       {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }	
	 ID_PRINT = id;
       DJ_PRINT = dj;
       QL_PRINT = je;
       JE_PRINT =  ql;
       HQL_PRINT = hq;//rg180131
       PR_YGH  = ygh;//RG160907
       memcpy(RQ_PRINT,edati,6);
       memcpy(CN_PRINT,cn,10);
       memcpy(CP_PRINT,cp,12);//rg170607 ������Ϣ���ƺ�
       KY_PRINT=ky;
 if (TRUE != qty_get_sw(&num)) {//ͨ���쳣

				SOEACTION1(PRO422_ERR, eCurRunState);
//				return;
			}
       olcm_dispprintf(0,1,"���ڴ�ӡ        ");
       oprint_normal_cmd();
 //   oprint_header_cmd();

    if(Hard_Info[0]==0)
    oprint_printf("��ӭʹ�ý���LNG������\r\n"); //cur_sysparas  ��CNG �޸�ΪLNG  
    else
    oprint_printf(Hard_Info);
    oprint_normal_cmd();
    oprint_printf("վ��:%d\r\n", Cur_StationNo);
    oprint_printf("ǹ��:%d\r\n", cur_sysparas.p_gid );
        oprint_printf("��ˮ��:%d\r\n",ID_PRINT);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN_PRINT);
    oprint_printf("����:%s\r\n",buf);
    sprintf(buf, "%s", CP_PRINT);//rg170607 ������Ϣ���ƺ�
    oprint_printf("���ƺ�:%s\r\n",buf);//rg170607 ������Ϣ���ƺ�
    i = (num >> 5)&0x01;
			if (i == 1)
			{ 
				oprint_printf("����:%.02f Ԫ/kg\r\n",DJ_PRINT);
				oprint_printf("������:%.02f kg\r\n",QL_PRINT);
			
			}
			else if (i == 0)
			{
				oprint_printf("����:%.02f Ԫ/m3\r\n",DJ_PRINT);	
			oprint_printf("������:%.02f m3\r\n",QL_PRINT);
			
			}
			else
			{
				oprint_printf("����:%.02f Ԫ/kg\r\n",DJ_PRINT);	
			oprint_printf("������:%.02f kg\r\n",QL_PRINT);
			
			}	
				
//    oprint_printf("����:%.02f Ԫ/kg\r\n",PRICE);
    oprint_printf("���:%.02fԪ\r\n",JE_PRINT);
    if(HQ_PRINT==0)//rg180131
    oprint_printf("������:%.02fkg\r\n",HQL_PRINT);//rg180131
    if(CN_PRINT[2] != 0x35)//rg170717
    {
         yp=inttoa(KY_PRINT);//rg170620
        memset(yu,0x00,12);//rg170620
        memcpy(yu,yp,10);//rg170620
        oprint_printf("����:%sԪ\r\n",yu);//rg170620
    }
        if(PR_YGH != 0)
    {
    oprint_printf("Ա����:%03d\r\n",PR_YGH);//rg160907
    }
    oprint_printf("����:20%02d��%02d��%02d��\r\n", RQ_PRINT[0],RQ_PRINT[1], RQ_PRINT[2]);
    oprint_printf("ʱ��:%02dʱ%02d��%02d��",RQ_PRINT[3], RQ_PRINT[4], RQ_PRINT[5]);
    oprint_printf("\r\n");
oprint_printf("********��ѯƱ����********\r\n");//rg170620
//oprint_printf("\r\n");
    if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
    if(Contact_Info[0]!=0)
    {
    oprint_printf(Contact_Info);}
     oprint_printf("\r\n");
    oprint_printf("----��ӭ�´ι���----\r\n");
    oprint_printf("\r\n");
//Recv_PR_ok=0;
 //   memset(Recv_PR_Buf,0x00,80);
    eVirtualKey = _KEY_EXIT_EV_;
}
//    return TRUE;
//}
#if 0

#endif