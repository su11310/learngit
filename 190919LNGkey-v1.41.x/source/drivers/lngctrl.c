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
    memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息
}



void deg_operate_save_begi(void)    //150730   150801  开始保存为完整保存
{   UINT8   saveCN[8];
    UINT16  addr;
    UINT8 kmm = 100;

               deg_oparme.deg_cor_id = MAX_dubug_recid_num + 1;//调试流水号
                memcpy(saveCN, (UINT8*)(&CN[2]), 8);//只处理8位
                deg_oparme.deg_card_id = (UINT32)atoi(saveCN);//4卡号
                deg_oparme.deg_voluent = 0;//开始气量为0
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

void deg_operate_save_gasing(float GVV)    //150730   150801  只是保存气量
{
    UINT16  addr;
    float Debug_save_vol;
    addr = DEBUG_RECORD_SAVE + (MAX_dubug_recid_num-1)*16;  //此处注意，和开始保存不一样，开始保存后已经自增了
   Debug_save_vol = GVV;
  o24lcxxx_write_bytes_ex(addr+offsetof(struct debugcord_parme,deg_voluent),(UINT8*)&Debug_save_vol,4);

}

void deg_operate_save_end(void)    //150730   150801  只是保存最后气量
{
    UINT16  addr;
    float Debug_save_vol;
    addr = DEBUG_RECORD_SAVE + (MAX_dubug_recid_num-1)*16;  //此处注意，和开始保存不一样，开始保存后已经自增了
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
    olcm_dispprintf(0,1,"    定量加气");
   
 while(1)
  {   
     if((WKJQ == 0)&&((_CARD_TYPE == 2) || (_CARD_TYPE == 3)|| (_CARD_TYPE == 5))||(WKJQ ==1))                                             //ss190409      (Operate_fixm != 0)||
       {
           car_status = machine_status_card();                          //增加判断卡是否被拔掉的判断    ss190409  
            if(car_status!=CPU_TYPE_A)//卡拔掉了
            {
                 eVirtualKey = _KEY_EXIT_EV_;
                 return FALSE;
            }
       }
     
     olcm_dispprintf(0,2,"加气气量:       ");
     cursor_x = 5;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
    if(vkey == _KEY_EXIT_EV_ )
    {
      eVirtualKey = _KEY_EXIT_EV_;
      return FALSE; //退出键
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
    olcm_dispprintf(0,1,"    定额加气");
    
  while(1)
  {   
      if((WKJQ == 0)&&((_CARD_TYPE == 2) || (_CARD_TYPE == 3)|| (_CARD_TYPE == 5))||(WKJQ ==1))                                             //ss190409      (Operate_fixm != 0)||
       {
           car_status = machine_status_card();                          //增加判断卡是否被拔掉的判断    ss190409  
            if(car_status!=CPU_TYPE_A)//卡拔掉了
            {
                 eVirtualKey = _KEY_EXIT_EV_;
                 return FALSE;
            }
       }
      
      olcm_dispprintf(0,2,"加气金额:       ");
      cursor_x = 5;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,TRUE,FALSE);
    if(vkey == _KEY_EXIT_EV_ )
    {
      eVirtualKey = _KEY_EXIT_EV_;
      return FALSE; //退出键
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
        //通信异常
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
 *   ss190306  卡置灰操作   
 *   为加气完成解灰失败后 再次强制写入灰锁状态
 **************************************************/
BOOL IC_card_put_grey_status(void)
{
    UINT8 j=3;
    
    while (j) 
    {
        
        if (TRUE == ic_card_put_status(CARDS_GREY))              //置灰RG160601
        {
            UINT8 grey_state;
            grey_state = ic_card_get_status_nosel();            // 再次获取置灰状态 
            if (grey_state == CARDS_GREY)                       // 置灰完成后 读取出状态再次判断置灰是否成功
            {
                break;
            }

        }
        delay_ms(50);
        j--;
    }
    if (j <= 0) 
    {

//        SOEACTION1(huicar_err, eCurRunState);                    // 置灰失败 异常提示
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
    UINT32 ecc_tick = 0;//通信超时用
    UINT8 ds;//rg170323
    UINT8 eccSW =0;
    UINT8 rdkey =0;
    UINT8 *qpx;//rg170608 气品选择
    UINT8 *cp;//rg170607 加气信息车牌号
    UINT8 car_status;//RG170705
    UINT8 carzl;//rg170717
    car_status=0;//rg170705
    if(QX_OVER==1)//rg160726
    {
	olcd_clearsCreen();
    SOEACTION1(QxOver,eCurRunState);//RG190705
//        olcm_dispprintf(0,1,"本机超过期限！");
//	olcm_dispprintf(0,2,"无法加气！");
//	olcm_dispprintf(0,3,"请尽快联系厂家");    
	osys_getkey(_KEY_NULL_,500);
        eVirtualKey = _KEY_EXIT_EV_;
        return;    
    }
if(GasBegin !=1)//如果是开始加气了,就不执行如下操作了（即：已经读过时间和卡信息了）
 {
    if(HUAIKUAI==TRUE)
    {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"存储器件错误！");
        olcm_dispprintf(0,2,"  请尽快更换");
        osys_getkey(_KEY_NULL_,500);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
      }
       olcd_clearsCreen();
 //       olcm_dispprintf(0,1,"读卡请稍等...");
		card_info_len = sizeof(global_ic_card_info);//rg170705
	memset(global_ic_card_info, 0, card_info_len);//rg170705
	car_status = machine_status_card();//rg170705
	if(car_status == HAVE_CARD)
		{
			olcm_dispprintf(0, 1, "  读卡器异常    ");
				olcm_dispprintf(0, 2, "    请检查      ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
		}
	else if (car_status > NO_CARD)//rg170705 判断卡是否有效
		{
			if (car_status == CPU_TYPE_A) {
				olng_operate_card_info(); //150730
				if (WKJQ == 0) {
					GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
					if (GUANLpinfo == NULL) {
						olcm_dispprintf(0, 1, "  无效卡    ");
						olcm_dispprintf(0, 2, "  请换正常卡  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					} else if ((memcmp(GUANLpinfo, "40000002", lenx) != 0)&&(memcmp(GUANLpinfo, "40000003", lenx) != 0)&&(memcmp(GUANLpinfo, "40000001", lenx) != 0)&&(memcmp(GUANLpinfo, "40000024", lenx) != 0)&&(memcmp(GUANLpinfo, "40000005", lenx) != 0))//rg170717
					{
						olcm_dispprintf(0, 1, "  无效卡    ");
						olcm_dispprintf(0, 2, "  请重新插卡  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			} else {
				olcm_dispprintf(0, 1, "  无效卡    ");
				olcm_dispprintf(0, 2, "  请重新插卡  ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
			}
		}
       ////////////////////////////管理卡识别//////////////
    //   olng_operate_card_info(); //150730
       		if (WKJQ == 1)//rg170531无卡加气
		{
			if (dkpd != APDUS_SUCCESS)//rg170531无卡加气
			{
				switch (dkpd) {
				case APDUS_NO_CARD:
						olcm_dispprintf(0, 1, "  卡信息查询    ");
						olcm_dispprintf(0, 2, "请先插卡，再查询");
						olcm_dispprintf(0, 3, "  谢谢！！      ");
						break;
				case APDUS_FAILE:
						olcm_dispprintf(0, 1, "  卡信息查询");
						olcm_dispprintf(0, 2, "读卡失败!!");
						SOEACTION1(ICCARD_READ_ERR, eCurRunState);
					break;
				case APDUS_DKQERR:
						olcm_dispprintf(0, 1, "  卡信息查询");
						olcm_dispprintf(0, 2, "读卡器错误!!");
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
//*********************//rg180416 判断班组号**************************************************//
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
						olcm_dispprintf(0, 2, "错误：禁止加气");
						olcm_dispprintf(0, 3, "请插本班组卡加气");
						osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			}
		}
//*********************//rg180416 判断班组号END**************************************************//		
//*********************//rg170608 气品选择**************************************************//	
	qpx = ic_operate_info("QPX", global_ic_card_info, &lenx);
	if (qpx != NULL)
	{
            if(memcmp(qpx, "2", lenx) == 0)
            {
                olcm_dispprintf(0, 2, "错误：此为CNG 卡");
                olcm_dispprintf(0, 3, "请换其它卡加气！");
 		osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;	
            }
	}
//**********************//rg170608 气品选择 end*************************************************//	
 	GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
	if(WKJQ == 1)//rg170531无卡加气
	{
            if (GUANLpinfo == NULL)
            {
                olcm_dispprintf(0, 2, "错误：禁止加气");
                olcm_dispprintf(0, 3, "请插卡加气！");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }
	}
	else
	{
            if (GUANLpinfo == NULL)
            {
                CARD_XIAOFEI = 2;//记账金额
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
//	if(memcmp(GUANLpinfo, "40000024", 8) == 0)// 管理卡  rg170531无卡加气
	if(GUANLpinfo != NULL)
	{
            UINT8 Type_date;
            Type_date = str_chan_u8(GUANLpinfo);                                   // 卡类型转换
            gas_record.gas_start_way = Type_date;                                 // 加气记录     加气卡的类型 
        if(memcmp(GUANLpinfo, "40000024", lenx) == 0)// 管理卡  150730wzw  
        {
            if (Is_debuggas_Read == 1) //配置为允许管理卡加气
            {
                olcm_dispprintf(0, 1, "读卡请稍等...   ");
                if (MAX_dubug_recid_num >= 200) //150730
                {
                    olcd_clearsCreen();
                    olcm_dispprintf(0, 1, "     警告    ");
                    olcm_dispprintf(0, 2, "调试加气已达上限");
                    olcm_dispprintf(0, 3, "不能继续调试加气");
                    osys_getkey(_KEY_NULL_, 300);
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                else
                {
                    IS_GUANLI_CARD_GAS = 1; //判断保存的条件
                    _CARD_TYPE = CARDT_ADMINI; //用于下面发送给主板150730wzw
                    CARD_XIAOFEI = ACCOUNT_MONEY; //下面用150730wzw
                }


                GUANLpinfo = ic_operate_info("CN", global_ic_card_info, &lenx);
                if (GUANLpinfo == NULL)
                {
                        olcm_dispprintf(0, 2, "错误：禁止加气");
                        olcm_dispprintf(0, 3, "请换其它卡加气！");
			osys_getkey(_KEY_NULL_, 300);
                        eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                memset(CN, 0, sizeof (CN));
                memcpy(CN, GUANLpinfo, lenx);
            } //薄码配置允许调试加气
            else //薄码未设置
            {
                    olcm_dispprintf(0, 1, "      警告      ");
                    olcm_dispprintf(0, 2, "不允许管理卡加气");
                    olcm_dispprintf(0, 3, "请更换其他类型卡");
                    olcm_dispprintf(0, 4, "      谢谢!     ");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }

        } //END OF 管理卡

            //////////////////////////////////////////////////////////////////
 //       else if(memcmp(GUANLpinfo, "40000001", lenx) == 0)//正常卡，非管理卡  150730wzw
	else
        {
            if (Is_debuggas_Read == 0) //正常加气配置，不允许管理卡加气
            {
                 olcm_dispprintf(0, 1, "读卡请稍等...   ");
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

                    if (Get_Gp_Time(pjyx) <= 1800)//判断钢瓶超期
                    {
                        olcd_clearsCreen();
                            olcm_dispprintf(1, 1, "钢瓶超期    ");
                            olcm_dispprintf(1, 2, "无法加气      ");
                            olcm_dispprintf(1, 3, "请更换加气卡  ");
                        osys_getkey(_KEY_NULL_, 300);
                        eVirtualKey = _KEY_EXIT_EV_;
                        return;
                    }
                }
		//************************//rg170607 加气信息车牌号*****************************************************************//	
	cp = ic_operate_info("CBH", global_ic_card_info, &lenx);//车牌号
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
//************************//rg170607 加气信息车牌号  END*****************************************************************//		

                    olcm_dispprintf(0, 1, "正在读卡...");
                if (TRUE != get_car_info())
                    //            if(TRUE == ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity,CPBH,GPBH))//获得卡信息
                {
                    SOEACTION1(ICCARD_READ_ERR, eCurRunState); //读卡信息错误
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
		else//rg170531无卡加气
		{
			GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
			if((memcmp(GUANLpinfo, "40000001", lenx) == 0)&&(WKJQ == 0))//rg170531无卡加气
			{
				CARD_XIAOFEI = 2;//记账金额
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
			//向后台要最大加气金额	
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
					     olcm_dispprintf(0, 1, "  主卡被注销    ");
					     olcm_dispprintf(0, 2, "  不可加气      ");
					     olcm_dispprintf(0, 3, "  请换卡        ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else if(carzl==2)
				    {
					     olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "  主卡额度较少  ");
					     olcm_dispprintf(0, 2, "副卡不能同时加气");
					     olcm_dispprintf(0, 3, "  请等待....    ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else 
				    {
					    olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "子卡状态错误  ");
					     olcm_dispprintf(0, 2, "  不能加气    ");
					     olcm_dispprintf(0, 3, "  请换卡      ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
			      }
			      else
			      {
				   olcd_clearsCreen();
					olcm_dispprintf(1, 2, "无法获取卡金额    ");
					olcm_dispprintf(1, 3, "无法加气      ");
				       osys_getkey(_KEY_NULL_, 300);
				    eVirtualKey = _KEY_EXIT_EV_;
				    return;
			      }
			}
//*********************************************************************************//			
		}
            }
            else //薄码设置允许调试时，正常卡不能用
            {
                olcm_dispprintf(0, 1, "      警告      ");
                olcm_dispprintf(0, 2, "不允许此类卡调试");
                olcm_dispprintf(0, 3, "请更换管理卡");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }


        } //end of esle(正常卡)
	}
    else if(WKJQ == 0)
    {
            gas_record.gas_start_way = CARD_OPERATION;                                // 无卡加气方式置位     加气记录 
    }
        
        if((gass_class==1)&&(_CARD_TYPE==1))
        {
         olcd_clearsCreen();
	olcm_dispprintf(0,2,"错误：禁止加气");
        olcm_dispprintf(0,3,"请换其它卡加气！");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }

               if((((fabs(Rec_Card_PreM))>=950000)||((fabs(Rec_Card_Preg))>=950000))&&(_CARD_TYPE==1))
        {
           olcd_clearsCreen();
        olcm_dispprintf(0,2,"错误：卡余超限");
        olcm_dispprintf(0,3,"请先结算再加气！");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }
      if(Get_zk()==0)//判断折扣 150901 rg
        {
          if(_CARD_TYPE != CARDT_ADMINI)
          {
           olcd_clearsCreen();
          olcm_dispprintf(1,1,"  单价异常    ");
          olcm_dispprintf(1,2,"请退出重新设置");
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
                    olcm_dispprintf(1,1,"无效卡        ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
  /*  150730wzw    case 2:     olcm_dispprintf(0,1,"  卡异常        ");
                    olcm_dispprintf(0,3,"管理卡，不能加气");
                    break;*/
        case 3:     olcm_dispprintf(0,1,"  卡异常      ");
                    olcm_dispprintf(0,3,"灰卡，不能加气");
                     break;
        case 8:     olcm_dispprintf(0,1,"  卡异常      ");
                    olcm_dispprintf(0,3,"注销卡，不能加气");
                     break;
        case 6:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"密码错误      ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
         case 10:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"通讯错误      ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
        case 12:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"错误卡，不能加气");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
        case 13:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"读卡错误      ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
	//rg170717	    
	 case 14:     olcd_clearsCreen();
                    olcm_dispprintf(0,1,"公司母卡不能加气");
                    olcm_dispprintf(0,2,"请退出重新操作  ");
                    break;	    
          default:break;
        }

        if(_CARD_TYPE != CARDT_ADMINI)  //剔除管理卡150730WZW
        {
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
         }
    }
#if 0
    if(TRUE != ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&mlc,&glc,&CARD_XIAOFEI))//获得卡信息
             {
              SOEACTION1(ICCARD_READ_ERR,eCurRunState);     //读卡信息错误
                 return;
             }
#endif
            Get_gas_money();

            {  rdkey = ostatemachine_getkey();  //是否有停止按键
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
  //       Mainui_Disp_Cardinfo(_CARD_TYPE,CN,car_prem,Rec_Card_Preg,CARD_XIAOFEI);//金额为余额，不管卡类型
          _station = (CN[0]-0x30)*10+(CN[1]-0x30);
             if(_station != Cur_StationNo)
             {  
                 if(_CARD_TYPE == 1)
                 {
                    olcd_clearsCreen();         // ss190904   异站的班组卡不可以加气    
                    olcm_dispprintf(0,1,"    提示");
                    olcm_dispprintf(0,2,"该异站卡不可加气");
                    osys_getkey(_KEY_NULL_,200);
                    eVirtualKey = _KEY_EXIT_EV_;
                   return;
                 }
//                 olcd_clearsCreen();
//                olcm_dispprintf(0,1,"  此卡非本站卡");
//                olcm_dispprintf(0,2,"请稍等！");
//                olcm_dispprintf(0,3,"正在等待后台验证");

             }
	if((WKJQ == 0)&&(_CARD_TYPE == 1))//rg170531无卡加气
	REC_START = Check_Card_info(cure_JQ_card, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);//rg170531无卡加气
	else
	REC_START = Check_Card_info(CN, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);	
    if(1!= REC_START )//返回值非1，0,2为不正常,3为异地卡可加气，4为异地卡不可加气,5为按键停止或退出。6为脱机状态，异站卡不可加气
     { 

        if(0 == REC_START )
               {//通信异常
                // SOEACTION1(31,eCurRunState);
//                olcd_clearsCreen();
//                olcm_dispprintf(0,1,"卡信息异常");
//                olcm_dispprintf(0,2,"请重新操作");
            SOEACTION1(PRO422_ERR,eCurRunState);
                eVirtualKey = _KEY_EXIT_EV_;
                  return;
              }
            else if(2  == REC_START )
                {//黑卡
                   olcd_clearsCreen();
                   olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"该卡为挂失卡！");
                   osys_getkey(_KEY_NULL_,200);
                   eVirtualKey = _KEY_EXIT_EV_;
                  return;
              }
            else if(3  == REC_START )
                {//异地卡可加气
//                   olcd_clearsCreen();
//                   olcm_dispprintf(0,1,"    提示");
//                   olcm_dispprintf(0,2,"该异站卡可加气");
//                   olcm_dispprintf(0,3,"正在继续....");

              }
            else if(4  == REC_START )
                {//异地卡可加气
                   olcd_clearsCreen();
                    olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"该卡为挂失卡！");
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
            {//异地卡可加气
               olcd_clearsCreen();
            olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"黑名单验证失败！");
             //  olcm_dispprintf(0,3,"正在继续....");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_EXIT_EV_;
              return;
          }
	else 
                {
		    olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"验卡不成功");
		   osys_getkey(_KEY_NULL_,300);
                  eVirtualKey = _KEY_EXIT_EV_;
                  return;
                }
#if 0
     if((CARD_XIAOFEI<2)&&((car_prem<PRICE)||(Rec_Card_Preg<1)))//正常卡、记账
         {
                    olcd_clearsCreen();
                    olcm_dispprintf(0,1,"卡余额不足");
                    olcm_dispprintf(0,2,"请充值");
                     osys_getkey(_KEY_NULL_,300);
                    eVirtualKey = _KEY_EXIT_EV_;
                      return;
         }
#endif
            }//end of if(1!= REC_START )
 } //end  of if(GasBegin ==1)    
    //////////////////////////////此处分解点，注意///////////////////////////////////////////////////
#if 0
    if((((_CARD_TYPE==2)||(_CARD_TYPE==3))&&(CARD_XIAOFEI>2))&&((car_prem<PRICE)&&(car_prel<1)))//正常卡 ,记账方式
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡余额不足");
                olcm_dispprintf(0,2,"请充值");
                 if(GasBegin ==1)
                 eVirtualKey = _KEY_ADDGAS_EXIT;//结账
                 else
                 eVirtualKey = _KEY_EXIT_EV_;//直接退出
                return;
     }
#endif
        if((_CARD_TYPE==CARDT_SMALL)&&(car_prem < smallMini_FD+Mini_Money))//rg181210
    {
         olcd_clearsCreen();
             olcm_dispprintf(0, 1, "卡余额不足");
            olcm_dispprintf(0, 2, "请充值");
          osys_getkey(_KEY_NULL_, 300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
    }
      if((CARD_XIAOFEI==PREE_GASE)&&(Rec_Card_Preg<3))//正常卡、气量
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡余额不足");
                olcm_dispprintf(0,2,"请充值");
                 osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_EXIT_EV_;
                  return;
     }
    if((CARD_XIAOFEI==PREE_MONEY)&&(Rec_Card_PreM<Mini_FD))//正常卡、金额
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡余额不足");
                olcm_dispprintf(0,2,"请充值");
                 osys_getkey(_KEY_NULL_,300);
                eVirtualKey = _KEY_EXIT_EV_;
                  return;
     }
    
     if(((_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL))&&((car_prem<Mini_FD)&&(car_prel<3)))//正常卡 ,记账方式不用判余额//rg170717 增加子卡类型判断
     {
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡余额不足");
                olcm_dispprintf(0,2,"请充值");
                  osys_getkey(_KEY_NULL_,300);
                 if(GasBegin ==1)
                 eVirtualKey = _KEY_ADDGAS_EXIT;//结账
                 else  
                 eVirtualKey = _KEY_EXIT_EV_;//直接退出
                return;
     }
    if((Get_again_gas_money(&max_money)==FALSE) &&(_CARD_TYPE != CARDT_ADMINI) )//获取发送金额150730wzw,排除管理卡
    {
                  olcd_clearsCreen();
                  olcm_dispprintf(0,1,"卡数据错误");
                  olcm_dispprintf(0,2,"请检查");
                    osys_getkey(_KEY_NULL_,300);
                   if(GasBegin ==1)
                   eVirtualKey = _KEY_ADDGAS_EXIT;//结账
                   else
                   eVirtualKey = _KEY_EXIT_EV_;//直接退出
                  return;
    }
    if(GasBegin == 0)
    {
        gas_record.grey_lock_inif.cur_money =  max_money;            //加气记录    加气前金额  
    }
 
    if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))   //150730WZW
    {
         max_money = -9000;
    }
        //**************************************************************************//
    if(((_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE==CARDT_SMALL))&&(CARD_XIAOFEI == PREE_MONEY))//rg170705//rg170606 //rg170717 增加子卡类型判断
    {
        if((max_money-Mini_FD)<=0.1)   
        {
            olcd_clearsCreen();
            olcm_dispprintf(0, 1, "卡余额不足");
            olcm_dispprintf(0, 2, "请充值");
            osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_EXIT_EV_;
            return; 
        }
    }
    //*************************************************************************//
// REC_START = Ocompany_Gas_noquan_start(max_money-10);//发送加气命令,包括最大加气金额，发出停止命令后，在停止就要进入结算函数
 
 //   REC_START = Ocompany_Gas_noquan_start(max_money-10,Pr_gr,Discounf,Cur_Price);
    if((WKJQ == 0)&&(_CARD_TYPE == 1))//rg170531无卡加气
        REC_START = Ocompany_Gas_noquan_start(999999, Pr_gr, Discounf, Cur_Price,CPH,GasBegin);//rg170531无卡加气//rg170607 加气信息车牌号
    else if(_CARD_TYPE == CARDT_SMALL)
        REC_START = Ocompany_Gas_noquan_start( max_money - smallMini_FD, Pr_gr, Discounf, Cur_Price,CPH,GasBegin);//rg181210
    else
        REC_START = Ocompany_Gas_noquan_start(max_money - Mini_FD, Pr_gr, Discounf, Cur_Price,CPH,GasBegin);//rg160627//rg170607 加气信息车牌号 rg170704 卡里剩5元//rg170606

    if(1 != REC_START )//!=1表示：0:通讯错误 1:可以加气2：未预冷
    {
        if(0  == REC_START )
        {//通信异常
            SOEACTION1(PRO422_ERR,eCurRunState);
            if(GasBegin ==1)
                eVirtualKey = _KEY_ADDGAS_EXIT;//结账
            else                                                                 //通信失败 发送解灰信息  sushuai add
            {
    //            OKgas_money = 0;
    //            if (olng_operate_put_card())                                    //解灰
    //            {
    //                olcm_dispprintf(0, 2, "解灰成功"); //扣款成功发送完整信息给主控板
    //            } 
    //            else {
    //
    //                    olcm_dispprintf(0, 2, "解灰失败");
    //                    olcm_dispprintf(0, 3, "请后台解灰");
    //                    osys_getkey(_KEY_EXIT_EV_,300); 
    //                }
                eVirtualKey = _KEY_EXIT_EV_;//直接退出
            }               
            return;

        }

        else if(2  == REC_START )
        {
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"未达预冷条件");
             olcm_dispprintf(0,2,"请先退出");
             olcm_dispprintf(0,3,"再进行预冷");
             osys_getkey(_KEY_EXIT_EV_,800);
             if(GasBegin ==1)//如果已经开始一次
             eVirtualKey = _KEY_ADDGAS_EXIT;//结账
             else  
             eVirtualKey = _KEY_EXIT_EV_;//直接退出
              return;
        }
	else//rg170807  加气命令增加判断
	{
		 olcd_clearsCreen();
	       olcm_dispprintf(0,1,"主板未正常返回  ");
	       olcm_dispprintf(0,2,"    无法加气    ");
	       olcm_dispprintf(0,3,"    请检查      ");
	       osys_getkey(_KEY_EXIT_EV_,800);
	       if(GasBegin ==1)//如果已经开始一次
	       eVirtualKey = _KEY_ADDGAS_EXIT;//结账
	       else  
	       eVirtualKey = _KEY_EXIT_EV_;//直接退出
		return;
	}

    }
    else
    {
        UINT8 stop_num;
        gas_record.gas_process |=  GAS_START_SEND_SUCC;                          //   加气记录 加气开始命令发送成功标志
        stop_num = ((gas_record.gas_process & 0x0F)+1);
        if(stop_num >15) stop_num =15;                                          // 支持最大停止次数  15次
        gas_record.gas_process &= 0xF0;                                          //  清空停止计数位
        gas_record.gas_process |= stop_num ;          
    }
    //rg171011屏蔽
    
     /////////////////////////////置灰/rg160602///////////////////////////////////////////////
    if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531无卡加气//rg170717 增加子卡类型判断 子卡不置灰
    {
  if(GasBegin ==0)  
   {
       if(Graybegain == 0)
            { 
           j=2;
            while(j)
            {
                if(TRUE ==ic_card_put_status(CARDS_GREY))  //置灰RG160601
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
            if (TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
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
////////////////////以下为加气操作/////////////////////////////////////////
 
olcd_clearsCreen();
olcm_dispprintf(2,1,"正在加气");
olng_operate_disp(TRUE,gain,ls,temp);
//GasBegin = 1;//加气开始
GasCo=1;
Car_hui=0;//0表示没有拔卡
// Car_Hui_ok=0;
Add_Gas_CS++;   //wzw150518
 UINT8 Save_pre_gasvol =0; //wzw150518
    BOOL Get_Grey_Statu = FALSE;                                                // 加气过程中再次判断是否为灰卡
 if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
 {
     deg_operate_save_begi();
 }//150801}
    
if(GasBegin == 0)                                                           //首次加气需要存储
{
    gas_record.grey_lock_inif.grey_status |=  GAS_START_MORMAL;                          // 加气记录  正常加气方式
    WiteRecorInfoOnce(gas_record);                                          // 首次将加气记录信息写入到存储中  ss181213
}
GasBegin = 1; //加气开始
    while(1)
    {//循环中只有STOP按键能到下面发送停止，

        if( send_sj_flag == 1)  //1秒定时发送询问
        {
            send_ack_sj(0x99);
            send_sj_flag=0;
            {                                                                   //询问主板的加气状态命令
               UINT8 loop_num;
               loop_num = ((gas_record.grey_unlock_inif.grey_status & 0x0F)+1);
               if(loop_num >15) loop_num =15;                                          // 支持最大停止次数  15次
               gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  清空停止计数位
               gas_record.grey_unlock_inif.grey_status |= loop_num ;          
            }
        }

        {  
            rdkey = ostatemachine_getkey();
            b_keyv = FALSE;
            if (_KEY_STOP_EV_ == rdkey)
            {
                gas_record.gas_stop_way = PRESS_STOP;                  // 加气记录   按键停止加气
                break;
            }
            if(_KEY_SW_EV_ == rdkey) SwPage=!SwPage;
        }
        if((WKJQ == 1)||((WKJQ==0)&&(_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//rg170531无卡加气//rg170717 
        { 
            car_status = machine_status_card();
            if(car_status!=CPU_TYPE_A)//卡拔掉了
            {
                gas_record.gas_stop_way = CARD_EXTRACT;                  //  加气记录  卡被拔出停止加气方式
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡已拔出!!");
                olcm_dispprintf(0,2,"加气停止");
                FIX_RecOK = 1;
                Car_hui = 1;
                if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
                {
                    gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          // 加气记录  发送停止命令失败
                    SendStop_False  =1;
                    break;
                }
                gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                          // 加气记录  发送停止命令成功
                eVirtualKey = _KEY_ADDGAS_EXIT;
                return;

            }
        }
               Rec_GasRun = Ocompany_Gas_noquan_run(&GV,&gain,&ls,&temp,&desenty,&press,&backgas,&isgasOK);
                //后
               {
                    rdkey = ostatemachine_getkey();
                    b_keyv = FALSE;
                    if(_KEY_STOP_EV_ == rdkey) 
                    {
                        gas_record.gas_stop_way = PRESS_STOP;                  // 加气记录  按键停止加气
                        break;
                    }
                    if(_KEY_SW_EV_ == rdkey) SwPage=!SwPage;
               }
          /* if((Rec_GasRun == FALSE)&&(Car_Hui_ok==1))  //rg160601
          {
               if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
            {
                SendStop_False  =1;
               SOEACTION1(PRO422_ERR,eCurRunState);
         //     if(ecc_tick == DWORDMAX)
               {//通信异常多次，直接到待机状态
                     olcd_clearsCreen();
                     olcm_dispprintf(0,1,"  系统硬件异常");
                     olcm_dispprintf(0,2,"  请断电检查  ");

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
 //            olcm_dispprintf(0,1,"  置灰不成功    ");
 //            olcm_dispprintf(0,2,"  请断电检查   ");
             SOEACTION1(huicar_err ,eCurRunState);
 //            delay_ms(1000);
             eVirtualKey = _KEY_EXIT_EV_;
             osys_getkey(_KEY_EXIT_EV_,300);
             return; }
          }*/
          if(Rec_GasRun == TRUE)      //重新确定定量和非定量加气isgasok的值的问题
        {
            ecc_tick = 0;
            gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  清空加气过程中的不断询问次数
                if(Save_pre_gasvol==0) //保存上一笔,默认第一次进来数据为上笔暂停数值
                {  if(Add_Gas_CS>1)   //第一笔Every_add_Gas[1]
                        {
                         Every_add_Gas[Add_Gas_CS-1] = GV - Pre_vol_add;
                         Pre_vol_add =  GV;//Pre_vol_add +Every_add_Gas[Add_Gas_CS-1]; //不包含本次循环的

                        }
                     Save_pre_gasvol = 1;
                }
              //   Every_add_Gas[Add_Gas_CS] = GV - Pre_vol_add;    //wzw150518
          
                if(isgasOK == 0xFD)//不足
                 {    olcd_clearsCreen();
		      olcm_dispprintf(1,1,"加满金额");//主板自动达到最大金额停止
                      olcm_dispprintf(1,2,"加气完成");//
                      FIX_RecOK = 1;
                    gas_record.gas_stop_way = MONEY_ALL;                  // 加气记录  加满金额停止加气
                      eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款
                    return;
                  }
                else if(isgasOK == 0xD0)                                         //  ss20190102 置灰失败  直接退出  
                {    
                    olcd_clearsCreen();
                    olcm_dispprintf(2,1,"置灰失败");//主板自动停止
                    olcm_dispprintf(2,2,"请重新插卡");//主板自动停止
                    osys_getkey(_KEY_EXIT_EV_,300); //错误主控板已停机，无需发送停止
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                else if(isgasOK == 0xE0)
                {    olcd_clearsCreen();
                     olcm_dispprintf(1,1,"流速低暂停");
                     olcm_dispprintf(1,2,"请退出");
                      gas_record.gas_stop_way = VELOCIIY_LOW;                  // 加气记录  流速低暂停停止加气
                     osys_getkey(_KEY_EXIT_EV_,300); //错误主控板已停机，无需发送停止
                     eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款，不需指定错误，可以询问累加
                         return;
                }
                else if(isgasOK > 0)    //记得定量整改后
                {
                    olcd_clearsCreen();
                    switch(isgasOK)
                      {   case  0xE1:   olcm_dispprintf(1,1,"板件通信超时"); 
                                       SOEACTION1(PRO422_ERR,eCurRunState);
                                 gas_record.gas_stop_way = COMMUN_TIIMOUT;                  // 加气记录  板间通信超时停止加气
                                        break;
                          case  0xE3:   olcm_dispprintf(1,1,"流量计通信错误"); 
                                        SOEACTION1(MOD_READNUM_ERR,eCurRunState);
                                gas_record.gas_stop_way = FLOWMETER_ERR;                  // 加气记录  流量计通信错误停止加气
                                        break;
                          case  0xE4:   olcm_dispprintf(1,1,"预冷超时");
                                gas_record.gas_stop_way = PRECOOL_ERR;                  // 加气记录  预冷超时停止加气
                                        break;
                          case  0xE5:  
                               olcm_dispprintf(1,1,"压力异常");
                               olcm_dispprintf(1,2,"请退出!!");
                               SOEACTION1(NOPRESSURE_ERR,eCurRunState);
  //160620                             osys_getkey(_KEY_EXIT_EV_,500); //错误主控板已停机，无需发送停止
                                gas_record.gas_stop_way = PRESSURE_ERR;                  // 加气记录  压力异常停止加气
                               eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款，不需指定错误，可以询问累加
                               return;
                         case  0xE6:
                                olcm_dispprintf(1,1,"超过最大流速");
                                olcm_dispprintf(1,2,"请退出!!");
                                SOEACTION1(ZDLS_ERR,eCurRunState);
  //160620                             osys_getkey(_KEY_EXIT_EV_,500); //错误主控板已停机，无需发送停止
                                gas_record.gas_stop_way = VELOCITY_HIGH;                  // 加气记录  超过最大流速停止加气
                                eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款，不需指定错误，可以询问累加
                                return;  
			case  0xE8://rg180115
                                olcm_dispprintf(0,1,"卡类型卡余不匹配");
                               olcm_dispprintf(1,2,"请退出!!");
	//		       osys_getkey(_KEY_EXIT_EV_,300);
                                 SOEACTION1(KLXKY_ERR ,eCurRunState);
                                 gas_record.gas_stop_way = CARD_BALANCE_FAILL;                  // 加气记录  卡类型卡余不匹配
                              break;        
                    default: olcm_dispprintf(1, 1, "加气异常");
                     gas_record.gas_stop_way = GAS_UNUSUAL;                  // 加气记录  加气异常停止加气
                     AddSOE(isgasOK);
                        break;
                      }
                  //错误主控板已停机，无需发送停止
                   GAS_MustStop_Err = 1;//上述错误必须停
                   osys_getkey(_KEY_EXIT_EV_,400);
                   eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款
                   return;
         }
     

         if(SwPage ==FALSE)
             olng_operate_disp(FALSE,gain,ls,temp);
         else
             olng_operate_disp2(FALSE,GV,desenty,press); ///

          if(gTick >Debugasing_rstsave_Tick)  //150801
          {  if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //在管理卡允许加气时，首先判断 MAX_dubug_recid_num  不能超过200方可加气
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
                        GAS_MustStop_Err = 1;     //超时未收到数此错误必须停
                        eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款
                        olcm_dispprintf(0,1,"键盘板3 秒无数据");
                        osys_getkey(_KEY_EXIT_EV_,200);
                        ecc_tick = DWORDMAX;
                        gas_record.gas_stop_way = TRIPLE_COMMUN_FAILL;                  // 加气记录  三秒无数据停止加气
                        break;
                      //  return;
                    }
                }
               else
                   ecc_tick = gTick +600;
          }
        if((gas_record.grey_lock_inif.grey_status & 0x03) ==  GREY_LUCK_SUCC)               //再次判断灰锁状态  //ss190215
        {
            if(Get_Grey_Statu == FALSE)                            // 进入到加气流程，再次判断卡是否为灰卡
            {
                Get_Grey_Statu = TRUE;

                    if(CARDS_GREY != ic_card_get_status_nosel() )                         // 获取灰锁状态 
                    {
                        SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // 加气过程中判断卡不为灰卡 进行提示
                        gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_FAILL;                          // 加气记录   加气过程中再次读取灰锁状态   ss190304
                        break;                                                                     // 当前卡不为灰锁状态 跳出加气 
                    }
                    gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // 加气记录   加气过程中再次读取灰锁状态

            }
        }
//               if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))
//               {
//       if(Get_Grey_Statu == FALSE)                            // 进入到加气流程，再次判断卡是否为灰卡
//        {
//            Get_Grey_Statu = TRUE;
//
//                if(CARDS_GREY != ic_card_get_status_nosel() )                         // 获取灰锁状态 
//                {
//                    SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // 加气过程中判断卡不为灰卡 进行提示
//                    gas_record.grey_lock_inif.grey_status &=  GREY_GAS_LUCK_FAILL;                          // 加气记录   加气过程中再次读取灰锁状态  
//                    break;                                                                     // 当前卡不为灰锁状态 跳出加气 
//                }
//                gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // 加气记录   加气过程中再次读取灰锁状态
//            
//        }
//               }
               ///////////////////////////////////
  }//end  of while(1)

 if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
     {
         SendStop_False  =1;
        SOEACTION1(PRO422_ERR,eCurRunState);
         gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          //   加气记录 加气停止命令发送成功标志 
       if(ecc_tick == DWORDMAX)
        {//通信异常多次，直接到待机状态
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"  系统硬件异常");
            olcm_dispprintf(0,2,"  请断电检查  ");
            gas_record.gas_stop_way = SYS_HARD_FAULT;                  // 加气记录  系统硬件异常停止加气
            gas_record.gas_stream = 0x00;                              // 加气记录   系统硬件异常流水号赋 零值
            ortcc_read_time(gas_record.grey_unlock_inif.time);                    // 加气记录   解灰时间   放置在此，解灰失败也是可以获取解灰时间的
            WiteRecorInfo_AN(gas_record);                                              // 加气记录  将加气记录信息写入到EEP中
            while(1);                                                            // 系统停止，等待断电重启
               Gas_para_init();
	       memset(CPH_IN,0x0,12);//rg170619 输入车牌号
	         memset(CPH,0x0,12);//rg170619 输入车牌号
		Cp_flag=0;//rg170619 输入车牌号
              ///////////////////////////
             eCurRunState = State_MainUI;
             eVirtualKey = 0;
             osys_getkey(_KEY_EXIT_EV_,300);
             return;
        }
    }
    gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                         // 加气记录  发送停止命令成功
// eVirtualKey = _KEY_ADDGAS_EXIT;
//    if(gas_record.gas_precool == GAS_PRECOOL_SUCC)             // 预冷成功 才可以进入到扣款状态   ss190312  
//    {
        eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款
//    }
//    else
//    {
//        eVirtualKey = _KEY_EXIT_EV_;//直接到扣款
//        WiteRecorInfo_AN(gas_record);                              //ss190213  // 加气记录  将加气记录信息写入到EEP中
//    }
    return;

}


void olng_start_act(void)
{    BOOL SwPage = FALSE;
    float GV; float AM;float gain;float ls;float temp;float backgas;UINT8 isgasOK;
 //   float mlc,glc,car_prem,car_prel;
    float press,desenty;
    float RepGV = 0; //上次GV
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
    UINT32 ecc_tick = 0;//通信超时用
     UINT8 lenx ;//150730wzw
      UINT8  *GUANLpinfo; //150730
    UINT8 eccSW =0;
    UINT8 rdkey =0;
    UINT8 car_status;//RG170705
    UINT8 *qpx;//rg170608 气品选择
    UINT8 *cp;//rg170607 加气信息车牌号
    UINT8 carzl;//rg170717
    BOOL Get_Grey_Statu = FALSE;
    car_status = 0;//rg170705
    if(QX_OVER==1)//rg160726
    {
	olcd_clearsCreen();
    SOEACTION1(QxOver,eCurRunState);//RG190705
//        olcm_dispprintf(0,1,"本机超过期限！");
//	olcm_dispprintf(0,2,"无法加气！");
//	olcm_dispprintf(0,3,"请尽快联系厂家");    
	osys_getkey(_KEY_NULL_,500);
        eVirtualKey = _KEY_EXIT_EV_;
        return;    
    }
 if(GasBegin != 1)//如果是开始加气了,就不执行如下操作了
 {   if(HUAIKUAI==TRUE)
    {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"存储器件错误！");
        olcm_dispprintf(0,2,"  请尽快更换");
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
      }
          olcd_clearsCreen();
   //        olcm_dispprintf(0,1,"读卡请稍等...");
	  	card_info_len = sizeof(global_ic_card_info);//rg170705
	memset(global_ic_card_info, 0, card_info_len);//rg170705
	car_status = machine_status_card();//rg170705
	if(car_status == HAVE_CARD)
		{
			olcm_dispprintf(0, 1, "  读卡器异常    ");
				olcm_dispprintf(0, 2, "    请检查      ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
		}
	else if (car_status > NO_CARD)//rg170705 判断卡是否有效
		{
			if (car_status == CPU_TYPE_A) {
				olng_operate_card_info(); //150730
				if (WKJQ == 0) {
					GUANLpinfo = ic_operate_info("CDT", global_ic_card_info, &lenx);
					if (GUANLpinfo == NULL) {
						olcm_dispprintf(0, 1, "  无效卡    ");
						olcm_dispprintf(0, 2, "  请换正常卡  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					} else if ((memcmp(GUANLpinfo, "40000002", lenx) != 0)&&(memcmp(GUANLpinfo, "40000003", lenx) != 0)&&(memcmp(GUANLpinfo, "40000001", lenx) != 0)&&(memcmp(GUANLpinfo, "40000024", lenx) != 0)&&(memcmp(GUANLpinfo, "40000005", lenx) != 0))//rg170717
					{
						olcm_dispprintf(0, 1, "  无效卡    ");
						olcm_dispprintf(0, 2, "  请重新插卡  ");
						osys_getkey(_KEY_NULL_, 500);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			} else {
				olcm_dispprintf(0, 1, "  无效卡    ");
				olcm_dispprintf(0, 2, "  请重新插卡  ");
				osys_getkey(_KEY_NULL_, 500);
				eVirtualKey = _KEY_EXIT_EV_;
				return;
			}
		}

  /*
        olcm_dispprintf(0,1,"读卡请稍等...");
                   if(TRUE !=get_car_info())
 //              if(TRUE != ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity))//获得卡信息
             {
              SOEACTION1(kk_r_err,eCurRunState);     //读卡信息错误
              eVirtualKey = _KEY_EXIT_EV_;
              return;
             }

   */
          ////////////////////////////管理卡识别//////////////
       olng_operate_card_info(); //150730
       		if (WKJQ == 1)//rg170531无卡加气
		{
			if (dkpd != APDUS_SUCCESS)//rg170531无卡加气
			{
				switch (dkpd) {
				case APDUS_NO_CARD:
						olcm_dispprintf(0, 1, "  卡信息查询    ");
						olcm_dispprintf(0, 2, "请先插卡，再查询");
						olcm_dispprintf(0, 3, "  谢谢！！      ");
					break;
				case APDUS_FAILE:
						olcm_dispprintf(0, 1, "  卡信息查询");
						olcm_dispprintf(0, 2, "读卡失败!!");
					SOEACTION1(ICCARD_READ_ERR, eCurRunState);
					break;
				case APDUS_DKQERR:
						olcm_dispprintf(0, 1, "  卡信息查询");
						olcm_dispprintf(0, 2, "读卡器错误!!");
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
//*********************//rg180416 判断班组号**************************************************//
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
						olcm_dispprintf(0, 2, "错误：禁止加气");
						olcm_dispprintf(0, 3, "请插本班组卡加气");
						osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
					}
				}
			}
		}
//*********************//rg180416 判断班组号END**************************************************//	
       //*********************//rg170608 气品选择**************************************************//	
	qpx = ic_operate_info("QPX", global_ic_card_info, &lenx);
	if (qpx != NULL)
	{
		if(memcmp(qpx, "2", lenx) == 0)
		{
                olcm_dispprintf(0, 2, "错误：此为CNG 卡");
                olcm_dispprintf(0, 3, "请换其它卡加气！");
		osys_getkey(_KEY_NULL_, 300);	
            eVirtualKey = _KEY_EXIT_EV_;
            return;	
		}
	}
//**********************//rg170608 气品选择 end*************************************************//
    GUANLpinfo = ic_operate_info("CDT",global_ic_card_info, &lenx);
	if(WKJQ == 1)//rg170531无卡加气
	{
	if (GUANLpinfo == NULL)
        {
                olcm_dispprintf(0, 2, "错误：禁止加气");
                olcm_dispprintf(0, 3, "请插卡加气！");
		osys_getkey(_KEY_NULL_, 300);	
            eVirtualKey = _KEY_EXIT_EV_;
            return;
        }
	}
	else
	{
		if (GUANLpinfo == NULL)
        {
				CARD_XIAOFEI = 2;//记账金额
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
//if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531无卡加气
//{
	if(GUANLpinfo != NULL)
	{
            UINT8 Type_date;
            Type_date = str_chan_u8(GUANLpinfo);                                   // 卡类型转换
            gas_record.gas_start_way = Type_date;                                 // 加气记录     加气卡的类型 
        if(memcmp(GUANLpinfo, "40000024", lenx) == 0)// 管理卡  150730wzw  
        {
            if (Is_debuggas_Read == 1) //配置为允许管理卡加气
            {
                    olcm_dispprintf(0, 1, "读卡请稍等...   ");
                if (MAX_dubug_recid_num >= 200) //150730
                {
                    olcd_clearsCreen();
                        olcm_dispprintf(0, 1, "     警告    ");
                        olcm_dispprintf(0, 2, "调试加气已达上限");
                        olcm_dispprintf(0, 3, "不能继续调试加气");
                    osys_getkey(_KEY_NULL_, 300);
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                else
                {
                    IS_GUANLI_CARD_GAS = 1; //判断保存的条件
                    _CARD_TYPE = CARDT_ADMINI; //用于下面发送给主板150730wzw
                    CARD_XIAOFEI = ACCOUNT_MONEY; //下面用150730wzw
                }


                GUANLpinfo = ic_operate_info("CN", global_ic_card_info, &lenx);
                if (GUANLpinfo == NULL)
                {
                        olcm_dispprintf(0, 2, "错误：禁止加气");
                        olcm_dispprintf(0, 3, "请换其它卡加气！");
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
                memset(CN, 0, sizeof (CN));
                memcpy(CN, GUANLpinfo, lenx);
            } //薄码配置允许调试加气
            else //薄码未设置
            {
                     olcm_dispprintf(0, 1, "      警告      ");
                    olcm_dispprintf(0, 2, "不允许管理卡加气");
                    olcm_dispprintf(0, 3, "请更换其他类型卡");
                    olcm_dispprintf(0, 4, "      谢谢!     ");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }

        } //END OF 管理卡

            //////////////////////////////////////////////////////////////////
 //       else if(memcmp(GUANLpinfo, "40000001", lenx) == 0)//正常卡，非管理卡  150730wzw
	else
        {
            if (Is_debuggas_Read == 0) //正常加气配置，不允许管理卡加气
            {
                     olcm_dispprintf(0, 1, "读卡请稍等...   ");
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

                    if (Get_Gp_Time(pjyx) <= 1800)//判断钢瓶超期
                    {
                        olcd_clearsCreen();
                            olcm_dispprintf(1, 1, "钢瓶超期    ");
                            olcm_dispprintf(1, 2, "无法加气      ");
                            olcm_dispprintf(1, 3, "请更换加气卡  ");
                       osys_getkey(_KEY_NULL_, 300);
                        eVirtualKey = _KEY_EXIT_EV_;
                        return;
                    }
                }
		//************************//rg170607 加气信息车牌号*****************************************************************//	
	cp = ic_operate_info("CBH", global_ic_card_info, &lenx);//车牌号
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
//************************//rg170607 加气信息车牌号  END*****************************************************************//		

                    olcm_dispprintf(0, 1, "正在读卡...");
                if (TRUE != get_car_info())
                    //            if(TRUE == ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity,CPBH,GPBH))//获得卡信息
                {
                    SOEACTION1(ICCARD_READ_ERR, eCurRunState); //读卡信息错误
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
		else//rg170531无卡加气
		{
			GUANLpinfo = ic_operate_info("CDT",global_ic_card_info, &lenx);
			if((memcmp(GUANLpinfo, "40000001", lenx) == 0)&&(WKJQ == 0))//rg170531无卡加气
			{
				CARD_XIAOFEI = 2;//记账金额
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
			//向后台要最大加气金额	
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
					     olcm_dispprintf(0, 1, "  主卡被注销    ");
					     olcm_dispprintf(0, 2, "  不可加气      ");
					     olcm_dispprintf(0, 3, "  请换卡        ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else if(carzl==2)
				    {
					     olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "  主卡额度较少  ");
					     olcm_dispprintf(0, 2, "副卡不能同时加气");
					     olcm_dispprintf(0, 3, "  请等待....    ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
				    else 
				    {
					    olcd_clearsCreen();
					     olcm_dispprintf(0, 1, "子卡状态错误  ");
					     olcm_dispprintf(0, 2, "  不能加气    ");
					     olcm_dispprintf(0, 3, "  请换卡      ");
					     osys_getkey(_KEY_NULL_, 300);
						eVirtualKey = _KEY_EXIT_EV_;
						return;
				    }
			      }
			      else
{
								olcd_clearsCreen();
								olcm_dispprintf(1, 2, "无法获取卡金额    ");
								olcm_dispprintf(1, 3, "无法加气      ");
								osys_getkey(_KEY_NULL_, 300);
								eVirtualKey = _KEY_EXIT_EV_;
								return;
			      }
			}
		}
            }
            else //薄码设置允许调试时，正常卡不能用
            {
                    olcm_dispprintf(0, 1, "      警告      ");
                    olcm_dispprintf(0, 2, "不允许此类卡调试");
                    olcm_dispprintf(0, 3, "请更换管理卡");
                osys_getkey(_KEY_NULL_, 300);
                eVirtualKey = _KEY_EXIT_EV_;
                return;
            }


        } //end of esle(正常卡)
	}
    else if(WKJQ == 0)
    {
            gas_record.gas_start_way = CARD_OPERATION;                                 // 无卡加气方式置位     加气记录 
    }

         if((gass_class==1)&&(_CARD_TYPE==1))
        {
         olcd_clearsCreen();
        olcm_dispprintf(0,2,"错误：禁止加气");
        olcm_dispprintf(0,3,"请换其它卡加气！");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }
        if(((fabs(Rec_Card_PreM)>=950000)||(fabs(Rec_Card_Preg)>=950000))&&(_CARD_TYPE==1))
        {
           olcd_clearsCreen();
        olcm_dispprintf(0,2,"错误：卡余超限");
        olcm_dispprintf(0,3,"请先结算再加气！");
         osys_getkey(_KEY_NULL_,300);
          eVirtualKey = _KEY_EXIT_EV_;
          return;
        }
        if(Get_zk()==0)//判断折扣 150901 rg
        {
          if(_CARD_TYPE != CARDT_ADMINI)
          {
            olcd_clearsCreen();
            olcm_dispprintf(1,1,"  单价异常    ");
            olcm_dispprintf(1,2,"请退出重新设置");
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
                    olcm_dispprintf(1,1,"无效卡        ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
      /*  150730wzw    case 2:     olcm_dispprintf(0,1,"  卡异常        ");
                    olcm_dispprintf(0,3,"管理卡，不能加气");
                    break;*/
        case 3:     olcm_dispprintf(0,1,"  卡异常      ");
                    olcm_dispprintf(0,3,"灰卡，不能加气");
                     break;
        case 6:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"密码错误      ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
        case 8:     olcm_dispprintf(0,1,"  卡异常      ");
                    olcm_dispprintf(0,3,"注销卡，不能加气");
                     break;
        
         case 10:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"通讯错误      ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
        case 12:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"错误卡，不能加气");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
        case 13:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"读卡错误      ");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;
		    //rg170717	    
	 case 14:     olcd_clearsCreen();
                    olcm_dispprintf(1,1,"公司母卡不能加气");
                    olcm_dispprintf(1,2,"请退出重新操作");
                    break;	    
          default:break;

        }
     if(_CARD_TYPE != CARDT_ADMINI)  //剔除管理卡150730WZW
        {
        osys_getkey(_KEY_NULL_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
     }
    }
#if 0
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
    if(memcmp(pinfo,"40000024",len1) == 0) // class group card
    {
    olcm_dispprintf(0,1,"  卡异常");
    olcm_dispprintf(0,3,"管理卡，不能加气");
    osys_getkey(_KEY_EXIT_EV_,300);
    eVirtualKey = _KEY_EXIT_EV_;
    return;
    }
     if(CARDS_GREY==ic_card_get_status())
     {
    olcm_dispprintf(0,1,"  卡异常");
    olcm_dispprintf(0,3,"灰卡，不能加气");
    osys_getkey(_KEY_EXIT_EV_,300);
    eVirtualKey = _KEY_EXIT_EV_;
    return;
     }
#endif
#if 0
      if(TRUE != ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&mlc,&glc,&CARD_XIAOFEI))//获得卡信息
      {
           SOEACTION1(ICCARD_READ_ERR,eCurRunState);
           return;
      }
#endif
    Get_gas_money();
    if(GasBegin == 0)              // 加气前余额   ss181213
    {
        gas_record.grey_lock_inif.cur_money =  car_prem;            //加气记录    加气前金额  
    } 
    
       {  rdkey = ostatemachine_getkey();  //是否有停止按键
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
//    Mainui_Disp_Cardinfo(_CARD_TYPE,CN,car_prem,car_prel,CARD_XIAOFEI);//显示卡信息
    RepInputFixm:
    if(Operate_fixm == 1)//定金额
    {
        if(TRUE !=olng_operate_fixm(&FIX_Money))//通过显示和输入获得加气金额
        {//输入金额时按了退出键，调至此处出去
            eVirtualKey = _KEY_EXIT_EV_;
            return;
        }
        gas_record.grey_lock_inif.grey_status |=  GAS_START_FIX_M;                          // 加气记录  定额加气
    }
    else if(Operate_fixm == 2)//定气量
    {
        if(TRUE !=olng_operate_fixv(&FIX_Money))//通过显示和输入、输入气量获得加气金额
        {//输入金额时按了退出键，调至此处出去
         eVirtualKey = _KEY_EXIT_EV_;
         return;
        }
        gas_record.grey_lock_inif.grey_status |=  GAS_START_FIX_V;                          // 加气记录  定量加气
    }
    if(FIX_Money < Cur_Price*3)//最小加气金额
    {//卡余小于加气金额
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"    提示");
       olcm_dispprintf(0,2,"输入值不合法");
       osys_getkey(_KEY_ENTER_EV_,300);
       goto RepInputFixm;
       }


 if(Judge_sct_Minimum(&carpre)==FALSE)
 {
     olcd_clearsCreen();
       olcm_dispprintf(0,1,"    提示");
       olcm_dispprintf(0,2,"卡余:%.02f",carpre);
       olcm_dispprintf(0,3,"余额不足！");
       osys_getkey(_KEY_EXIT_EV_,300);
       eVirtualKey = _KEY_EXIT_EV_;
       return;
   }

 _station = (CN[0]-0x30)*10+(CN[1]-0x30);
  if(_station != Cur_StationNo)
  {
        if(_CARD_TYPE == 1)
        {
            olcd_clearsCreen();         // ss190904   异站的班组卡不可以加气    
            olcm_dispprintf(0,1,"    提示");
            olcm_dispprintf(0,2,"该异站卡不可加气");
            osys_getkey(_KEY_NULL_,200);
            eVirtualKey = _KEY_EXIT_EV_;
           return;
        }
//             {  olcd_clearsCreen();
//                olcm_dispprintf(0,1,"  此卡非本站卡");
//                olcm_dispprintf(0,2,"请稍等！");
//                olcm_dispprintf(0,3,"正在等待后台验证");

             }
 //REC_START = Check_Card_info(CN,&Rec_Card_PreM_int,&Rec_Card_Preg_int,CARD_XIAOFEI);
 if((WKJQ == 0)&&(_CARD_TYPE == 1))//rg170531无卡加气
	REC_START = Check_Card_info(cure_JQ_card, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);//rg170531无卡加气
	else
	REC_START = Check_Card_info(CN, &Rec_Card_PreM_int, &Rec_Card_Preg_int, CARD_XIAOFEI);	
 if(1!= REC_START )//返回值非1，0,2,4均为不正常,3为异地卡成功。
{ if(0 == REC_START )
   {//通信异常
     SOEACTION1(PRO422_ERR,eCurRunState);
       eVirtualKey = _KEY_EXIT_EV_;
      return;
   }
else if(2  == REC_START )
  {//黑卡
       olcd_clearsCreen();
       olcm_dispprintf(0,1,"    提示");
       olcm_dispprintf(0,2,"该卡为挂失卡！");
       osys_getkey(_KEY_EXIT_EV_,300);
        eVirtualKey = _KEY_EXIT_EV_;
        return;
  }
 else if(3  == REC_START )
            {//异地卡可加气
//               olcd_clearsCreen();
//               olcm_dispprintf(0,1,"    提示");
//               olcm_dispprintf(0,2,"该异站卡可加气");
//               olcm_dispprintf(0,3,"正在继续....");
          }
        else if(4  == REC_START )
            {//异地卡可加气
               olcd_clearsCreen();
            olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"该卡为挂失卡！");
             //  olcm_dispprintf(0,3,"正在继续....");
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
            {//异地卡可加气
               olcd_clearsCreen();
            olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"黑名单验证失败！");
             //  olcm_dispprintf(0,3,"正在继续....");
               osys_getkey(_KEY_NULL_,300);
               eVirtualKey = _KEY_EXIT_EV_;
              return;
          }
	   else 
                {
		    olcm_dispprintf(0,1,"    提示");
                   olcm_dispprintf(0,2,"验卡不成功");
		   osys_getkey(_KEY_NULL_,300);
                  eVirtualKey = _KEY_EXIT_EV_;
                  return;
                }
   }  //end of 卡验证非1
}   //end of begin
////////////////////////////此处分界点，注意##############################/////////////
 //REC_START = Ocompany_Gas_Quan_start(FIX_Money - OKgas_money);//发送开始加气通信命令，收到返回信息
 
REC_START = Ocompany_Gas_Quan_start(FIX_Money - OKgas_money,Pr_gr,Discounf,Cur_Price,CPH,GasBegin);//发送开始加气通信命令，收到返回信息//rg160829//rg170607 加气信息车牌号rg181210
//输出参数：加气金额fix_money，输入参数：前枪总累Rec_Sum_Start；前压力Rec_Begin_Press；返回值：0:通讯错误 1:可以加气2: 未预冷

    if(1!= REC_START )//返回值非1，均为不正常。
   { 
        gas_record.gas_process &=  GAS_START_SEND_FAILL;                          // 加气记录  加气开始命令发送失败标志
        if(0 == REC_START )
        {//通信异常
            SOEACTION1(23,eCurRunState);
             if(GasBegin ==1)
            eVirtualKey = _KEY_VIRTUAL_EV_;//结账
            else
            eVirtualKey = _KEY_EXIT_EV_;//直接退出
           return;

        }
        if(2  == REC_START )
        {
           olcd_clearsCreen();
           olcm_dispprintf(0,1,"未预冷");
           olcm_dispprintf(0,2,"请先退出");
           olcm_dispprintf(0,3,"进行预冷");
           osys_getkey(_KEY_EXIT_EV_,400);
           if(GasBegin ==1)//如果已经开始一次GasBegin
           eVirtualKey = _KEY_ADDGAS_EXIT;//结账
           else
           eVirtualKey = _KEY_EXIT_EV_;//直接退出
            return;

        }
        else//rg170807  加气命令增加判断
	{
		 olcd_clearsCreen();
	       olcm_dispprintf(0,1,"主板未正常返回  ");
	       olcm_dispprintf(0,2,"    无法加气    ");
	       olcm_dispprintf(0,3,"    请检查      ");
	       osys_getkey(_KEY_EXIT_EV_,800);
	       if(GasBegin ==1)//如果已经开始一次
	       eVirtualKey = _KEY_ADDGAS_EXIT;//结账
	       else  
	       eVirtualKey = _KEY_EXIT_EV_;//直接退出
		return;
	}
    }
    else
    {
        UINT8 stop_num;
        gas_record.gas_process |=  GAS_START_SEND_SUCC;                          //   加气记录 加气开始命令发送成功标志
        stop_num = ((gas_record.gas_process & 0x0F)+1);
        if(stop_num >15) stop_num =15;                                          // 支持最大停止次数  15次
        gas_record.gas_process &= 0xF0;                                          //  清空停止计数位
        gas_record.gas_process |= stop_num ;          
    }

     /////////////////////////////置灰/rg160602///////////////////////////////////////////////
if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531无卡加气//rg170717 增加子卡类型判断 子卡不置灰 
//if(((WKJQ==1)&&(_CARD_TYPE ==CARDT_SMALL))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531无卡加气//rg170717
    {
  if(GasBegin ==0)  
   {
       if(Graybegain == 0)
            { 
//	       j=0;
           j=2;
            while(j)
            {
                if(TRUE ==ic_card_put_status(CARDS_GREY))  //置灰RG160601
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
            if (TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
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
////////////////////以下为正常卡操作/////////////////////////////////////////

 olcd_clearsCreen();
 //olcm_dispprintf(2,1,"正在加气");
 olng_operate_disp(TRUE,gain,ls,temp);
// GasBegin = 1;//    移植到下方  ss181213
 GasCo=1;
 Car_hui=0;
// Car_Hui_ok=0;
 Add_Gas_CS++;
  UINT8 Save_pre_gasvol =0; //wzw150518
  if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
  {
      deg_operate_save_begi();//150801
  }
  
if(GasBegin == 0)                                                           //首次加气需要存储
{
    WiteRecorInfoOnce(gas_record);                                          // 首次将加气记录信息写入到存储中  ss181213
}
GasBegin = 1; //加气开始

    while(1)
    {
            
             
               if( send_sj_flag==1)
                { 
                    send_ack_sj(0x99);
                    send_sj_flag=0;
                    {
                        UINT8 loop_num;
                        loop_num = ((gas_record.grey_unlock_inif.grey_status & 0x0F)+1);
                        if(loop_num >15) loop_num =15;                                          // 支持最大停止次数  15次
                        gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  清空停止计数位
                        gas_record.grey_unlock_inif.grey_status |= loop_num ;          
                    }
                }
                { 
                    rdkey = ostatemachine_getkey();
                    b_keyv = FALSE;
                    if(_KEY_STOP_EV_ == rdkey) 
                    {
                        gas_record.gas_stop_way = PRESS_STOP;                  // 加气记录   按键停止加气
                         break;
                    }
                       if(_KEY_SW_EV_ == rdkey)  SwPage=!SwPage;
                }
 		  if((WKJQ == 1)||((WKJQ==0)&&(_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//rg170531无卡加气//rg170717 
               { 
			  car_status = machine_status_card();
                    if(car_status!=CPU_TYPE_A)//卡拔掉了
                    {
                        olcd_clearsCreen();
                        olcm_dispprintf(0,1,"卡已拔出!!");
                        olcm_dispprintf(0,2,"加气停止");
                        FIX_RecOK = 1;
                        gas_record.gas_stop_way = CARD_EXTRACT;                  //  加气记录  卡被拔出停止加气方式
                        Car_hui = 1;
                        if(TRUE != Ocompany_Gas_Quan_stop(Car_hui)) //发出停止命令
                        {
                            SendStop_False  =1;
                            gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          // 加气记录  发送停止命令失败
                            break;                                              // 可再次发送停止
                        }
                        gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                          // 加气记录  发送停止命令成功
       //                return;
                        eVirtualKey = _KEY_VIRTUAL_EV_;
                       return;//rg160602
                    }
                }
            Rec_Pro = Ocompany_Gas_noquan_run(&GV,&gain,&ls,&temp,&desenty,&press,&backgas,&isgasOK);//用的飞定量
            {  
                rdkey = ostatemachine_getkey();
                b_keyv = FALSE;
                if(_KEY_STOP_EV_ == rdkey) 
                {
                    gas_record.gas_stop_way = PRESS_STOP;                  // 加气记录   按键停止加气
                     break;
                }
                if(_KEY_SW_EV_ == rdkey)  SwPage=!SwPage;
                  
            }
       /*   if((Rec_Pro == FALSE)&&(Car_Hui_ok==1))  
          {
             if(TRUE != Ocompany_Gas_noquan_stop(Car_hui)) //发出停止命令
            {
                SendStop_False  =1;
               SOEACTION1(PRO422_ERR,eCurRunState);
         //     if(ecc_tick == DWORDMAX)
                  //通信异常多次，直接到待机状态
                     olcd_clearsCreen();
                     olcm_dispprintf(0,1,"  系统硬件异常");
                     olcm_dispprintf(0,2,"  请断电检查  ");

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
   //          olcm_dispprintf(0,1,"  置灰不成功    ");
    //         olcm_dispprintf(0,2,"  请断电检查   ");
             SOEACTION1(huicar_err ,eCurRunState);
   //          delay_ms(1000);
                   eVirtualKey = _KEY_EXIT_EV_;
             osys_getkey(_KEY_EXIT_EV_,300);
             return; }
          }*/
          if(Rec_Pro == TRUE)      //重新确定定量和非定量加气isgasok的值的问题
          {      
                ecc_tick = 0;
                gas_record.grey_unlock_inif.grey_status &= 0xF0;                                          //  清空轮询发送次数
               if(Save_pre_gasvol==0) //保存上一笔,默认第一次进来数据为上笔暂停数值
                {  
                   if(Add_Gas_CS>1)   //第一笔Every_add_Gas[1]
                    {
                         Every_add_Gas[Add_Gas_CS-1] = GV - Pre_vol_add;
                         Pre_vol_add =  GV;//Pre_vol_add +Every_add_Gas[Add_Gas_CS-1]; //不包含本次循环的

                    }
                    Save_pre_gasvol = 1;
                }
              //   Every_add_Gas[Add_Gas_CS] = GV - Pre_vol_add;    //wzw150518

                if(isgasOK == 0xFD)//不足
                 {    olcd_clearsCreen();
		      olcm_dispprintf(1,1,"定额加满");//主板自动停止
                      olcm_dispprintf(1,2,"加气完成");//
                      gas_record.gas_stop_way = MONEY_ALL;                  // 加气记录  加满金额停止加气
                       FIX_RecOK = 1;
                      eVirtualKey = _KEY_VIRTUAL_EV_;
                    return;
                  }
                 else if(isgasOK == 0xD0)//   置灰失败  直接退出  
                {    
                    olcd_clearsCreen();
                    olcm_dispprintf(2,1,"置灰失败");//主板自动停止
                    olcm_dispprintf(2,2,"请重新插卡");//主板自动停止
                    osys_getkey(_KEY_EXIT_EV_,300); //错误主控板已停机，无需发送停止
                    eVirtualKey = _KEY_EXIT_EV_;
                    return;
                }
            else if(isgasOK == 0xE0)
          {
               olcm_dispprintf(1,1,"流速低暂停");
                gas_record.gas_stop_way = VELOCIIY_LOW;                  // 加气记录  流速低暂停停止加气
               osys_getkey(_KEY_EXIT_EV_,300); //错误主控板已停机，无需发送停止
               eVirtualKey = _KEY_VIRTUAL_EV_;//直接到扣款
                   return;
          }
         else  if(isgasOK > 0x0)    //记得定量整改后
        {  
            olcd_clearsCreen();
	            switch(isgasOK)
                      {   case  0xE1:   olcm_dispprintf(1,1,"板件通信超时");
                                       SOEACTION1(PRO422_ERR,eCurRunState);
                                    gas_record.gas_stop_way = COMMUN_TIIMOUT;                  // 加气记录  板间通信超时停止加气
                                         break;
                          case  0xE3:   olcm_dispprintf(1,1,"液相计读数错误");
                                         SOEACTION1(MOD_READNUM_ERR,eCurRunState);
                                    gas_record.gas_stop_way = FLOWMETER_ERR;                  // 加气记录  流量计通信错误停止加气
                                         break;
                          case  0xE4:   
                              olcm_dispprintf(1,1,"预冷超时");
                                    gas_record.gas_stop_way = PRECOOL_ERR;                  // 加气记录  预冷超时停止加气
                                        break;
                          case  0xE5:
                                olcm_dispprintf(1,1,"压力异常");
                               olcm_dispprintf(1,2,"请退出!!");
                                 SOEACTION1(NOPRESSURE_ERR,eCurRunState);
 //160620                              osys_getkey(_KEY_EXIT_EV_,500); //错误主控板已停机，无需发送停止
                                gas_record.gas_stop_way = PRESSURE_ERR;                  // 加气记录  压力异常停止加气
                               eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款，不需指定错误，可以询问累加
                               return;
                          case  0xE6:
                                olcm_dispprintf(1,1,"超过最大流速");
                                olcm_dispprintf(1,2,"请退出!!");
                                SOEACTION1(ZDLS_ERR,eCurRunState);
                                gas_record.gas_stop_way = VELOCITY_HIGH;                  // 加气记录  超过最大流速停止加气
        //160620                       osys_getkey(_KEY_EXIT_EV_,500); //错误主控板已停机，无需发送停止
                               eVirtualKey = _KEY_ADDGAS_EXIT;//直接到扣款，不需指定错误，可以询问累加
                               return;      
                          case  0xE8://rg180115
                                olcm_dispprintf(0,1,"卡类型卡余不匹配");
                                olcm_dispprintf(1,2,"请退出!!");
                                gas_record.gas_stop_way = CARD_BALANCE_FAILL;                  // 加气记录 卡类型卡余不匹配
	//		       osys_getkey(_KEY_EXIT_EV_,300);
                                 SOEACTION1(KLXKY_ERR ,eCurRunState);
                              break;     
                              default:     
                                  olcm_dispprintf(1,1,"加气异常");    
                                  gas_record.gas_stop_way = GAS_UNUSUAL;                  // 加气记录  加气异常
                                  AddSOE(isgasOK);
                              break;
                      }
                  //错误主控板已停机，无需发送停止
                   GAS_MustStop_Err = 1;//上述错误必须停
                   osys_getkey(_KEY_EXIT_EV_,400);
                   eVirtualKey = _KEY_VIRTUAL_EV_;//直接到扣款
                   return;
         }
#if 0
          if((isgasOK == 0)&&GV >=1)   //考虑定量达到满值的一种情况
          {   if(RepGV !=GV)
                 { RepGV =GV;
                   RecGverr = 0;
                 }
               else
                RecGverr++;
             if(RecGverr >20)
              {      olcd_clearsCreen();
		      olcm_dispprintf(1,1,"加气异常完成");//非正常情况的完成
                      FIX_RecOK = 1;
                     eVirtualKey = _KEY_VIRTUAL_EV_;
                     break;
              }

       }
#endif
       if(SwPage ==FALSE)
           olng_operate_disp(FALSE,gain,ls,temp);
       else
           olng_operate_disp2(FALSE,GV,desenty,press); /////改为压力，流量


        if(gTick >Debugasing_rstsave_Tick)  //150801
          {  if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //在管理卡允许加气时，首先判断 MAX_dubug_recid_num  不能超过200方可加气
                {
                deg_operate_save_gasing(GV); //150730  150801
                 }
             Debugasing_rstsave_Tick = gTick + 200;
            }

   // olng_operate_disp(FALSE,gain,ls,temp);
  }  //end of  TRUE

   else                //  没有接收到记录信息  ss181213
        { 
              if(ecc_tick !=0)
              {
                if(gTick > ecc_tick)
                 {   
                       GAS_MustStop_Err = 1;//此错误必须停
                       eVirtualKey = _KEY_VIRTUAL_EV_;//直接到扣款
                       olcm_dispprintf(0,1,"键盘板3 秒无数据");
                       osys_getkey(_KEY_EXIT_EV_,400);
                       ecc_tick = DWORDMAX;
                       gas_record.gas_stop_way = TRIPLE_COMMUN_FAILL;                  // 加气记录  三秒无数据停止加气
                       break;
                    // return;
                 }
               }
          else
            {  ecc_tick = gTick +600;
             }

          }
            
        if((gas_record.grey_lock_inif.grey_status & 0x03) ==  GREY_LUCK_SUCC)               //再次判断灰锁状态  //ss190215  置灰成功条件下再次判断
        {
            if(Get_Grey_Statu == FALSE)                            // 进入到加气流程，再次判断卡是否为灰卡
            {
                Get_Grey_Statu = TRUE;

                    if(CARDS_GREY != ic_card_get_status_nosel() )                         // 获取灰锁状态 
                    {
                        SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // 加气过程中判断卡不为灰卡 进行提示
                        gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_FAILL;                          // 加气记录   加气过程中再次读取灰锁状态   ss190304
                        break;                                                                     // 当前卡不为灰锁状态 跳出加气 
                    }
                    gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // 加气记录   加气过程中再次读取灰锁状态

            }
        }
//        if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//ss181213   对无卡 和子卡等特殊情况不做判断 灰锁状态  
//               {
//       if(Get_Grey_Statu == FALSE)                            // 进入到加气流程，再次判断卡是否为灰卡
//        {
//            Get_Grey_Statu = TRUE;
//
//                if(CARDS_GREY != ic_card_get_status_nosel() )                         // 获取灰锁状态 
//                {
//                    SOEACTION1(GAS_CHECK_GREYLOCK_ERR,eCurRunState);                      // 加气过程中判断卡不为灰卡 进行提示并做异常记录
//                    gas_record.grey_lock_inif.grey_status &=  GREY_GAS_LUCK_FAILL;                          // 加气记录   加气过程中再次读取灰锁状态  
//                    break;                                                                     // 当前卡不为灰锁状态 跳出加气 
//                }
//                gas_record.grey_lock_inif.grey_status |=  GREY_GAS_LUCK_SUCC;                          // 加气记录   加气过程中再次读取灰锁状态
//            
//
//        }
//               }
        
        }//end  of while(1)

      if(TRUE != Ocompany_Gas_Quan_stop(Car_hui)) //发出停止命令
       {
             SendStop_False  =1;
  //         SOEACTION1(25,eCurRunState);
             gas_record.gas_process &=  GAS_STOP_SEND_FAILL;                          //   加气记录 加气停止命令发送成功标志                          // 加气记录  发送停止命令失败
            if(ecc_tick == DWORDMAX)
                {//通信异常多次，直接到待机状态
                      olcd_clearsCreen();
                      olcm_dispprintf(0,1,"  系统硬件异常");
                      olcm_dispprintf(0,1,"  请断电检查  ");
                      
                     
                    memset(CPH_IN,0x0,12);//rg170619 输入车牌号
                    memset(CPH,0x0,12);//rg170619 输入车牌号
                    Cp_flag=0;//rg170619 输入车牌号
                    gas_record.gas_stop_way = SYS_HARD_FAULT;                  // 加气记录  系统硬件异常停止加气
                    gas_record.gas_stream = 0x00;                              // 加气记录   系统硬件异常流水号赋 零值
                    ortcc_read_time(gas_record.grey_unlock_inif.time);                    // 加气记录   解灰时间   放置在此，解灰失败也是可以获取解灰时间的
                    WiteRecorInfo_AN(gas_record);    
                    Gas_para_init();
                    while(1);  
                    eCurRunState = State_MainUI;
                    eVirtualKey = 0;
                    osys_getkey(_KEY_EXIT_EV_,400);
                    return;
                }
          
       }
        gas_record.gas_process |=  GAS_STOP_SEND_SUCC;                         // 加气记录  发送停止命令成功
//        eVirtualKey = _KEY_VIRTUAL_EV_;
//    if(gas_record.gas_precool == GAS_PRECOOL_SUCC)             // 预冷成功 才可以进入到扣款状态   ss190312  
//    {
        eVirtualKey = _KEY_VIRTUAL_EV_;//直接到扣款
//    }
//    else
//    {
//        eVirtualKey = _KEY_EXIT_EV_;//直接到扣款
//        WiteRecorInfo_AN(gas_record);                              //ss190213  // 加气记录  将加气记录信息写入到EEP中
//    }
    return;

}
//非定量加气的累加
void olng_operate_Isadd(void)
{   //按了停止
    UINT8 cou1 = 0;
    UINT8 cou2 = 0;
    UINT8 keyV;
   float GV; float AM; float back_gas;UINT8 EccType;
   UINT8 hq_state;
	UINT8 car_status;//RG170705
  
#if 0
 if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType))//查询
    {
     if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType))//查询
         {GAS_MustStop_Err = 1;
           olcd_clearsCreen();
           olcm_dispprintf(0,1,"    系统异常");
           olcm_dispprintf(0,2,"    加气停止");
           AddSOE(2);
         }
      }
     OKgas_GV = GV;   //获得的GV，在主板上已经扣除了回气量了
     GAS_BACKGV = back_gas;//回气,(已经扣除了回气量了)
     OKgas_money = AM;
#endif
 if((GAS_MustStop_Err ==0)&&(FIX_RecOK != 1))  //没有必须停止的，且没有OK标志
  {
       olcd_clearsCreen();
       if(Zttz_Time>0)//rg170605停止/ 暂停
       {
        if(State_g_p==1) olcm_dispprintf(0,1,"    预冷停止");
        else olcm_dispprintf(0,1,"    加气停止");
  //     olcm_dispprintf(0,1,"    加气暂停");
//       olcm_dispprintf(0,2,"是否继续加气？");
       olcm_dispprintf(0,3,"按加气--继续加气");
       olcm_dispprintf(0,4,"按停止--停止加气");
       }
       IsGasAdd_tick = gTick + 100 * Zttz_Time;//rg170605停止/ 暂停
      //IsGasAdd_tick =gTick +100*ISADDTIME;  //900S
         while(1)
          {
              if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
             {
                  olcm_dispprintf(0,3,"  调试加气完成  ");
                 olcm_dispprintf(0,4,"  正在保存数据  ");
                 break;
             }
                if(gTick > IsGasAdd_tick)
             {   IsGasAdd_tick = 0;
                 break;//跳出进行扣款
             }
	      if(Zttz_Time>0)//rg170605停止/ 暂停
	      {
             cou1 = (UINT8)(((IsGasAdd_tick -gTick)/100)/60);
             cou2 = (UINT8)(((IsGasAdd_tick -gTick)/100)%60);
          //   olcm_dispprintf(7,1,"%2d",cou);
               olcm_dispprintf(5,2,"%02dm%02ds",cou1,cou2);
              // olcm_dispprintf(0,2,"%3d 秒后自动结账",cou);
	      }
              if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531无卡加气 //rg170717
	{
		car_status = machine_status_card();
	  if(car_status!=CPU_TYPE_A)//卡拔掉了
            {   
                gas_record.gas_stop_way = CARD_EXTRACT;                        // 加气记录   卡被拔掉  停止加气
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡已拔出!!");
                olcm_dispprintf(0,2,"置为灰卡");
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
                  return;//累加，继续加气
                }
                if(keyV == _KEY_STOP_EV_)
                 break;//跳出进行扣款
              if(keyV == _KEY_POINT_EV_)
               {
                   if(!Ocompany_Gas_Qz())//取整
                   {
                       olcd_clearsCreen();
                       olcm_dispprintf(0,1,"    通讯异常");
                       osys_getkey(_KEY_NULL_,500);
                       break;
                       }
                 //发送给主控板取整，没有返回值
               }

          }//end  of while(1)

}
//////////////////////
    if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//查询
    {
        if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//查询
        {
            gas_record.gas_stop_way = SYS_FAULT;                           //加气记录   索要加气信息失败停止  ss181213
            GAS_MustStop_Err = 1;
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"    系统异常");
            olcm_dispprintf(0,2,"    加气停止");
            olcm_dispprintf(0,3,"    请后台解灰");//rg160817
            AddSOE(PRO422_ERR);//rg160817
            Gas_para_init();//该卡此次加气信息全部清空//rg160817
            memset(CPH_IN,0x0,12);//rg170619 输入车牌号
            memset(CPH,0x0,12);//rg170619 输入车牌号
            Cp_flag=0;//rg170619 输入车牌号
            WiteRecorInfo_AN(gas_record);                                              // 加气记录  将加气记录信息写入到EEP中
            memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息
            osys_getkey(_KEY_EXIT_EV_,400);//rg160817
            eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态//rg160817
            return;//rg160817
        }
    }
//     	if (hq_state == 0xFF)//RG170406                                /// 此处弃用  ss190218
//	{
//		OKgas_GV = 0; //获得的GV，在主板上已经扣除了回气量了
//		GAS_BACKGV = 0; //回气,(已经扣除了回气量了)
//		OKgas_money = 0;
//		olcd_clearsCreen();
//	        olcm_dispprintf(0,2,"请后台解灰");
//		SOEACTION1(Zhu_Reset, eCurRunState);
//		Gas_para_init(); //该卡此次加气信息全部清空
//		memset(CPH_IN,0x0,12);//rg170619 输入车牌号
//	         memset(CPH,0x0,12);//rg170619 输入车牌号
//		Cp_flag=0;//rg170619 输入车牌号
//		eVirtualKey = _KEY_EXIT_EV_; //指定为待机状态
//		return;
//	}	
     /*rg170330屏蔽回气量不扣钱，按正常流程走
     //////////////////rg160926//////////////////////////////////////
     if((hq_state==0x98)||(hq_state==0x99))//rg160926
     {
	OKgas_GV = 0;   //获得的GV，在主板上已经扣除了回气量了
     GAS_BACKGV = 0;//回气,(已经扣除了回气量了)
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
        {  SOEACTION1(PRO422_ERR,eCurRunState);//通信异常//6个实际有用的参数
        }
	   if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //在管理卡允许加气时，首先判断 MAX_dubug_recid_num  不能超过200方可加气
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
      Gas_para_init();//该卡此次加气信息全部清空
     eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
	return;  
     }
     ///////////////////////////////////////////////////////////////
      */
     OKgas_GV = GV;   //获得的GV，在主板上已经扣除了回气量了
     GAS_BACKGV = back_gas;//回气,(已经扣除了回气量了)
     OKgas_money = AM;

    if((AM<0.01)&(GV<0.01)&(hq_state == 0xFF)&( _gas_run_flag == TRUE))                  //金额、气量、回气量都为零  开始加气标志   满足条件不予以解灰ss190218 
    {
        OKgas_GV = 0; //获得的GV，在主板上已经扣除了回气量了
		GAS_BACKGV = 0; //回气,(已经扣除了回气量了)
		OKgas_money = 0;
        
        {                                                                       //获取加气记录
            UINT32 max_rec_id;
            max_rec_id = get_max_rec_id();                                        // 加气记录   获取主控板的加气流水号
            if(max_rec_id != 0xFFFF0000)
            {
                gas_record.gas_stream = max_rec_id;                             // 加气记录  加气流水号信息
            }
        }
        WiteRecorInfo_AN(gas_record);                                           //
        memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息
        Gas_para_init();//该卡此次加气信息全部清空
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"获取信息失败");
        olcm_dispprintf(0,2,"请后台解灰");
        osys_getkey(_KEY_NULL_, 300);
        memset(CPH_IN,0x0,12);//rg170619 输入车牌号
        memset(CPH,0x0,12);//rg170619 输入车牌号
        Cp_flag=0;//rg170619 输入车牌号
        eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
        return;
    }
     
     /////////////////////
          //此处以下为结账
    GasCo=0;
     if(OKgas_money < 0)
     {
    Rec_Card_EndM_int = Rec_Card_PreM_int - (INT32)(OKgas_money*100-0.5);//结束卡余=开始卡余-加气金额
     Rec_Card_Endg_int = Rec_Card_Preg_int - (INT32)(OKgas_GV*100-0.5);   //结束气量=开始气量-加气气量
     }
     else if(OKgas_money >= 0)
     {
       Rec_Card_EndM_int = Rec_Card_PreM_int - (INT32)(OKgas_money*100+0.5);//结束卡余=开始卡余-加气金额
     Rec_Card_Endg_int = Rec_Card_Preg_int - (INT32)(OKgas_GV*100+0.5);   //结束气量=开始气量-加气气量
     }
        Rec_Card_EndM = Rec_Card_PreM - OKgas_money;//结束卡余=开始卡余-加气金额
//     Rec_Card_Endg = Rec_Card_Preg - OKgas_GV;   //结束气量=开始气量-加气气量

   //  odisp_disp(OKgas_GV , OKgas_money, TRUE);
     show_operat_stop(OKgas_GV ,OKgas_money);
     gas_record.grey_unlock_inif.OKgas_money = OKgas_money;  
    if(OKgas_GV < 0)//rg170330
     {
	     OKgas_GV = 0;  //rg170330   
     }
 /*    if(OKgas_GV == 0)
     {    olcd_clearsCreen();
          olcm_dispprintf(0,1,"气量为0 ");
          olcm_dispprintf(0,2,"无须结账");
          olcm_dispprintf(0,3,"请退出！");
          ic_card_put_status(CARDS_NORMAL);
          Gas_para_init();//该卡此次加气信息全部清空
          osys_getkey(_KEY_EXIT_EV_,400);
         eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
         return;
     }*/
    //  ortcc_read_time(GAS_Etime); //得到结束加气时间
      CanGasTime = gTick  +100*60*CANGASMINUTE ; //半小时
      if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531无卡加气//rg170717
      {
            if(olng_operate_put_card() == TRUE)//扣款并且解灰
            {
                olcm_dispprintf(2,4,"扣款成功");//扣款成功发送完整信息给主控板
                Car_hui = 0;
                if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
                    //           if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
                {
                    SOEACTION1(PRO422_ERR, eCurRunState); //通信异常//6个实际有用的参数
                        gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // 加气记录   扣款信息发送失败
             //       return;
                }
                    else
                        gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // 加气记录   扣款信息发送成功
            }
            else                           //  解灰失败   
            {		
                if(_CARD_TYPE == CARDT_SMALL)//rg170717 
                {
                         Car_hui = 0;
                }
                else
                {
                    olcm_dispprintf(2,4,"扣款失败");
                    Car_hui = 1;
                    ic_card_active_sp();                                          // 重新激活卡机
                    if(IC_card_put_grey_status())                                 // 解灰失败，再次写入灰锁状态；    ss190306
                    {
                       gas_record.gas_process |= GAS_GREY_LUCK_SUCC_AG;                     // 再次置灰成功
                    }
                    else
                        gas_record.gas_process &= GAS_GREY_LUCK_FAILL_AG;                   // 再次置灰失败
                }
                if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
                {
                   SOEACTION1(PRO422_ERR, eCurRunState); //通信异常
                   gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // 加气记录   扣款信息发送失败
                //       return;
                }
                else
                   gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // 加气记录   扣款信息发送成功
            }
        }
        else////rg170531无卡加气
        {
            Car_hui = 0;
            if (TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE, CN, &OKgas_GV, &OKgas_money, &Rec_Card_PreM_int, &Rec_Card_EndM_int, &Rec_Card_Preg_int, &Rec_Card_Endg_int, &Rec_Sum_Start, &Rec_Sum_End, &Rec_Begin_Press, &Rec_End_Press, &Car_hui, GAS_Stime, GAS_Etime))
            {
                SOEACTION1(PRO422_ERR, eCurRunState); //通信异常//6个实际有用的参数
                gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // 加气记录   扣款信息发送失败
             //   return;
            }  
            else
                gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // 加气记录   扣款信息发送成功
            
            ortcc_read_time(gas_record.grey_unlock_inif.time);                    // 加气记录   解灰时间   放置在此，解灰失败也是可以获取解灰时间的
        }

    
      ///////////////////判别是否是管理卡进行调试加气///////////////////////////////150730
      if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //在管理卡允许加气时，首先判断 MAX_dubug_recid_num  不能超过200方可加气
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
      /////////////////////////////////////////////////////////////
         if((hq_state==0x99)||(hq_state==0x98))//rg170330
        {
            olcd_clearsCreen();
            if(hq_state==0x99)//回气量超500
            SOEACTION1(C_HuiQi_ERR,eCurRunState);
            if(hq_state==0x98)//加气量为负
            SOEACTION1(C_JiaQi_fu ,eCurRunState);	 
        }
     if((PRINT_SET ==1)&&(OKgas_GV != 0))//rg171127 气量为零不打印
      oprint_operate_rec();
  //   else//rg170606打印机设置
  //     Select_print();//手动打印选择//rg170606打印机设置
      
    {                                                                       //获取加气记录
         UINT32 max_rec_id;

         gas_record.grey_unlock_inif.Balance_To = Rec_Card_EndM;              //  加气记录     卡剩余额
         max_rec_id = get_max_rec_id();                                        // 加气记录   获取主控板的加气流水号
         if(max_rec_id != 0xFFFF0000)
         {
             gas_record.gas_stream = max_rec_id;                             // 加气记录  加气流水号信息
         }
    }
    WiteRecorInfo_AN(gas_record);                                              // 加气记录  将加气记录信息写入到EEP中
    memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息
    Gas_para_init();//该卡此次加气信息全部清空
    memset(CPH_IN,0x0,12);//rg170619 输入车牌号
    memset(CPH,0x0,12);//rg170619 输入车牌号
    Cp_flag=0;//rg170619 输入车牌号
    eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态

}
void Select_print(void)
{      UINT8  cou,keyV;
       olcd_clearsCreen();
       olcm_dispprintf(0,2,"  是否打印");
       olcm_dispprintf(0,3,"按确定--打印");
       olcm_dispprintf(0,4,"按更改--不打印");
       IsGasAdd_tick =gTick +100*10;  //10S
         while(1)
          {
             if(gTick > IsGasAdd_tick)
             {   IsGasAdd_tick = 0;
               return;//跳出进行扣款
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
                 olcm_dispprintf(0,2,"正在打印票据....");
                  return;//
                }
               else if(keyV == _KEY_EXIT_EV_)
                 return;

          }
}
//定量加气的停止
void gas_finish(void)
{    float GV; float AM; float back_gas;UINT8 EccType;
     UINT8 keyV;
     UINT8 cou1 = 0;
      UINT8 cou2 = 0;
      UINT8 hq_state;
      UINT8 car_status;//RG170705
     GasCo=0;
  if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//询问

   { 
        if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//查询
        {
            gas_record.gas_stop_way = SYS_FAULT;                           //加气记录   索要加气信息失败停止  ss181213
            GAS_MustStop_Err = 1;
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"    系统异常");
            olcm_dispprintf(0,2,"    加气停止");
            AddSOE(PRO422_ERR);
        }
     
    }
   
     OKgas_GV = GV;
     GAS_BACKGV = back_gas;//回气
    OKgas_money = AM;
   

  if((OKgas_money < FIX_Money)&& (GAS_MustStop_Err ==0)&&(FIX_RecOK != 1))//如果没有加气到定额，且不是主控板要求停止加气,还要不是加气完毕，询问是否继续加气
     {//FIX_RecOK:是为防止提高计量精度后，提前关阀，使气量微小于定额，那么就算完成。
        olcd_clearsCreen();
	if(Zttz_Time>0)//rg170605停止/ 暂停
	{
		olcm_dispprintf(0,1,"  加气停止");
       olcm_dispprintf(0,3,"按加气--继续加气");
       olcm_dispprintf(0,4,"按停止--停止加气");
	}
       IsGasAdd_tick = gTick + 100 * Zttz_Time;//rg170605停止/ 暂停
//       IsGasAdd_tick =gTick +100*ISADDTIME;  //900S
         while(1)
          {
              if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1))
             {   olcm_dispprintf(0,3,"  调试加气完成  ");
                 olcm_dispprintf(0,4,"  正在保存数据  ");
                 break;
             }
                if(gTick > IsGasAdd_tick)
             {   IsGasAdd_tick = 0;
                 break;//跳出进行扣款
             }
	      if(Zttz_Time>0)//rg170605停止/ 暂停
	      {
             cou1 = (UINT8)(((IsGasAdd_tick -gTick)/100)/60);
             cou2 = (UINT8)(((IsGasAdd_tick -gTick)/100)%60);
          //   olcm_dispprintf(7,1,"%2d",cou);
               olcm_dispprintf(5,2,"%02dm%02ds",cou1,cou2);
	      }
              if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531无卡加气//rg170717
	{
		car_status = machine_status_card();
            if(car_status!=CPU_TYPE_A)//卡拔掉了
            {  
                gas_record.gas_stop_way = CARD_EXTRACT;                        // 加气记录   卡被拔掉  停止加气
                olcd_clearsCreen();
                olcm_dispprintf(0,1,"卡已拔出!!");
                olcm_dispprintf(0,2,"置为灰卡");
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
                  return;//累加，继续加气
                }
                if(keyV == _KEY_STOP_EV_)
                 break;//跳出进行扣款
            if(keyV == _KEY_POINT_EV_)
               {
                   if(!Ocompany_Gas_Qz())//取整
                   {
                       olcd_clearsCreen();
                       olcm_dispprintf(0,1,"    通讯异常");
                       osys_getkey(_KEY_NULL_,500);
                       break;
                       }
                 //发送给主控板取整，没有返回值
               }

          }


     }

     if(GAS_MustStop_Err ==1)//主板有严重报错，不能继续加气
     {  olcd_clearsCreen();
       olcm_dispprintf(0,1,"  停止加气");
       olcm_dispprintf(0,1,"不能加气至定金额");
       olcm_dispprintf(0,1,"    抱歉       ");
      
     }
   //////////////////////////////////////////////////////////////
      if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//询问
   { 
        if(TRUE != Ocompany_GetGas_REC(&GV,&AM,&back_gas,&Rec_End_Press, &EccType,&pr_lsh,&hq_state))//查询
        {
            GAS_MustStop_Err = 1;
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"    系统异常");
            olcm_dispprintf(0,2,"    加气停止");
 //          AddSOE(2);
	    olcm_dispprintf(0,3,"    请后台解灰");//rg160817
           AddSOE(PRO422_ERR);//rg160817
	   Gas_para_init();//该卡此次加气信息全部清空//rg160817
	   memset(CPH_IN,0x0,12);//rg170619 输入车牌号
	         memset(CPH,0x0,12);//rg170619 输入车牌号
		Cp_flag=0;//rg170619 输入车牌号
          osys_getkey(_KEY_EXIT_EV_,400);//rg160817
         eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态//rg160817
            gas_record.gas_stop_way = SYS_FAULT;                           //加气记录   索要加气信息失败停止 ss181213
            WiteRecorInfo_AN(gas_record);                                              // 加气记录  将加气记录信息写入到EEP中
            memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息
         return;//rg160817
         }

    }
    
//    if (hq_state == 0xFF)//RG170406                                           //ss190218
//	{
//		OKgas_GV = 0; //获得的GV，在主板上已经扣除了回气量了
//		GAS_BACKGV = 0; //回气,(已经扣除了回气量了)
//		OKgas_money = 0;
//		olcd_clearsCreen();
//	        olcm_dispprintf(0,2,"请后台解灰");
//		SOEACTION1(Zhu_Reset, eCurRunState);
//		Gas_para_init(); //该卡此次加气信息全部清空
//		memset(CPH_IN,0x0,12);//rg170619 输入车牌号
//	         memset(CPH,0x0,12);//rg170619 输入车牌号
//		Cp_flag=0;//rg170619 输入车牌号
//		eVirtualKey = _KEY_EXIT_EV_; //指定为待机状态
//		return;
//	}
    /*rg170330屏蔽回气量不扣钱，按正常流程走
    ////////////////rg160926//////////////////////////////////////////
	if((hq_state==0x98)||(hq_state==0x99))//rg160926
     {
	OKgas_GV = 0;   //获得的GV，在主板上已经扣除了回气量了
     GAS_BACKGV = 0;//回气,(已经扣除了回气量了)
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
        {  SOEACTION1(PRO422_ERR,eCurRunState);//通信异常//6个实际有用的参数
        }
	   if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //在管理卡允许加气时，首先判断 MAX_dubug_recid_num  不能超过200方可加气
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
     Gas_para_init();//该卡此次加气信息全部清空
     eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
	return;  
     }
    ////////////////////////////////////////////////////////////////
     */
     OKgas_GV = GV;
     GAS_BACKGV = back_gas;//回气
     OKgas_money = AM;

    if((AM<0.01)&(GV<0.01)&(hq_state == 0xFF)&( _gas_run_flag == TRUE))                  //金额、气量、回气量都为零  开始加气标志   满足条件不予以解灰ss190218 
    {
        OKgas_GV = 0; //获得的GV，在主板上已经扣除了回气量了
		GAS_BACKGV = 0; //回气,(已经扣除了回气量了)
		OKgas_money = 0;
        
        {                                                                       //获取加气记录
            UINT32 max_rec_id;
            max_rec_id = get_max_rec_id();                                        // 加气记录   获取主控板的加气流水号
            if(max_rec_id != 0xFFFF0000)
            {
                gas_record.gas_stream = max_rec_id;                             // 加气记录  加气流水号信息
            }
        }
        WiteRecorInfo_AN(gas_record);                                           //
        memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息
        Gas_para_init();//该卡此次加气信息全部清空
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"获取信息失败");
        olcm_dispprintf(0,2,"请后台解灰");
        osys_getkey(_KEY_NULL_, 300);
        memset(CPH_IN,0x0,12);//rg170619 输入车牌号
        memset(CPH,0x0,12);//rg170619 输入车牌号
        Cp_flag=0;//rg170619 输入车牌号
        eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
        return;
    }
     
    ////////////////////////////////////////////////////////////////
     Rec_Card_EndM_int = Rec_Card_PreM_int - (INT32)(OKgas_money*100+0.5);//结束卡余=开始卡余-加气金额
     Rec_Card_Endg_int = Rec_Card_Preg_int - (INT32)(OKgas_GV*100+0.5);   //结束气量=开始气量-加气气量

     Rec_Card_EndM = Rec_Card_PreM - OKgas_money;//结束卡余=开始卡余-加气金额
 //    Rec_Card_Endg = Rec_Card_Preg - OKgas_GV;   //结束气量=开始气量-加气气量

     show_operat_stop(OKgas_GV,OKgas_money);
      gas_record.grey_unlock_inif.OKgas_money = OKgas_money;                   //  加气记录    消费金额
	if(OKgas_GV < 0)//rg170330
     {
	     OKgas_GV = 0;  //rg170330   
     }
   /*   if(OKgas_GV == 0)
     {    olcd_clearsCreen();
          olcm_dispprintf(0,1,"气量为0 ");
          olcm_dispprintf(0,2,"无须结账");
          olcm_dispprintf(0,3,"请退出！");
           ic_card_put_status(CARDS_NORMAL);
          Gas_para_init();//该卡此次加气信息全部清空
          osys_getkey(_KEY_EXIT_EV_,400);
         eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
         return;
     }*/
     
 //   ortcc_read_time(GAS_Etime);
      CanGasTime = gTick  +100*60*CANGASMINUTE ; //半小时
      if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)||(_CARD_TYPE == CARDT_SMALL)))//rg170531无卡加气//rg170717
      {
            if(olng_operate_put_card()==TRUE)//扣款并且解灰
           {
               olcm_dispprintf(2,4,"扣款成功");//扣款成功发送完整信息给主控板
               Car_hui = 0;
               
               if(TRUE != Ocompany_Gas_Quan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
               {  
                   SOEACTION1(PRO422_ERR,eCurRunState);//通信异常
                   gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // 加气记录   扣款信息发送失败
                //151229  return;
               }
               else
                   gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // 加气记录   扣款信息发送成功
           }
           else
               {	
                    if(_CARD_TYPE == CARDT_SMALL)//rg170717 
                   {
                        Car_hui = 0;
                   }
                   else
                   {
                       olcm_dispprintf(2,4,"扣款失败");
                       Car_hui = 1;
                        ic_card_active_sp();                                     // 重新激活卡机
                        if(IC_card_put_grey_status())                                 // 解灰失败，再次写入灰锁状态；    ss190306
                        {
                           gas_record.gas_process |= GAS_GREY_LUCK_SUCC_AG;                     // 再次置灰成功
                        }
                        else
                            gas_record.gas_process &= GAS_GREY_LUCK_FAILL_AG;                   // 再次置灰失败
                        
                   }
                if(TRUE != Ocompany_Gas_Quan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime ))
                  {  
                       SOEACTION1(PRO422_ERR,eCurRunState);//通信异常
                        gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // 加气记录   扣款信息发送失败
              //        return;
                   //151229   return;
                   }
                   else
                       gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // 加气记录   扣款信息发送成功
               }
      }
      else
      {
	    Car_hui = 0;
	  if (TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE, CN, &OKgas_GV, &OKgas_money, &Rec_Card_PreM_int, &Rec_Card_EndM_int, &Rec_Card_Preg_int, &Rec_Card_Endg_int, &Rec_Sum_Start, &Rec_Sum_End, &Rec_Begin_Press, &Rec_End_Press, &Car_hui, GAS_Stime, GAS_Etime))
            //           if(TRUE != Ocompany_Gas_noquan_finish(&_CARD_TYPE,CN,&OKgas_GV,&OKgas_money,&Rec_Card_PreM_int,&Rec_Card_EndM_int,&Rec_Card_Preg_int,&Rec_Card_Endg_int,&Rec_Sum_Start,&Rec_Sum_End,&Rec_Begin_Press,&Rec_End_Press,&Car_hui,GAS_Stime,GAS_Etime))
        {
            SOEACTION1(PRO422_ERR, eCurRunState); //通信异常//6个实际有用的参数
            gas_record.gas_process &= GAS_ACCOUNTS_SEND_FAILL;          // 加气记录   扣款信息发送失败
  //          return;
        }   
            else
            gas_record.gas_process |= GAS_ACCOUNTS_SEND_SUCC;              // 加气记录   扣款信息发送成功
            ortcc_read_time(gas_record.grey_unlock_inif.time);                    // 加气记录   解灰时间   放置在此，解灰失败也是可以获取解灰时间的
      }
        ///////////////////判别是否是管理卡进行调试加气///////////////////////////////150730
      if((CN[2] =='3')&&(IS_GUANLI_CARD_GAS == 1)) //在管理卡允许加气时，首先判断 MAX_dubug_recid_num  不能超过200方可加气
     {
          IS_GUANLI_CARD_GAS = 0;
           deg_operate_save_end(); //150730  150801

      }
      /////////////////////////////////////////////////////////////
   if((hq_state==0x99)||(hq_state==0x98))//rg170330
     {
	 olcd_clearsCreen();
	 if(hq_state==0x99)//回气量超500
         SOEACTION1(C_HuiQi_ERR,eCurRunState);
	 if(hq_state==0x98)//加气量为负
	SOEACTION1(C_JiaQi_fu ,eCurRunState);	 
      }
  if((PRINT_SET ==1)&&(OKgas_GV != 0))//rg171127 气量为零不打印
    oprint_operate_rec();
 //  else //rg170606打印机设置
  //   Select_print();//手动打印选择 //rg170606打印机设置
    {                                                                       //获取加气记录
         UINT32 max_rec_id;

         gas_record.grey_unlock_inif.Balance_To = Rec_Card_EndM;              //  加气记录     卡剩余额
         max_rec_id = get_max_rec_id();                                        // 加气记录   获取主控板的加气流水号
         if(max_rec_id != 0xFFFF0000)
         {
             gas_record.gas_stream = max_rec_id;                             // 加气记录  加气流水号信息
         }
    }
      WiteRecorInfo_AN(gas_record);                                              // 加气记录  将加气记录信息写入到EEP中
    memset(&gas_record,0x00,sizeof(gas_record));                            // 加气记录  清空加气过程产生的结构体缓存信息

  Gas_para_init();//该卡此次加气信息全部清空
  memset(CPH_IN,0x0,12);//rg170619 输入车牌号
	         memset(CPH,0x0,12);//rg170619 输入车牌号
		Cp_flag=0;//rg170619 输入车牌号
 eVirtualKey = _KEY_EXIT_EV_;//指定为待机状态
}

/*------------------------------------------加气过程中显示界----------------------------------------------------------*/
void olng_operate_disp(BOOL bInit,float gain,float ls,float temp)
{

    if( bInit )
	{
		    olcd_clearsCreen();
	//	    olcm_dispprintf(2,1,"正在加气");
		    olcm_dispprintf(0,2,"流速: %3.02f",0.00);
		    olcm_dispprintf(0,3,"增益: %3.02f",0.00);
                    olcm_dispprintf(0,4,"温度: %3.02f",0.00);
  	}
        else
	{
        	    olcm_dispprintf(0,2,"流速: %3.02f    ",ls );
		    olcm_dispprintf(0,3,"增益: %3.02f    ",gain);
                    olcm_dispprintf(0,4,"温度: %3.02f    ",(temp-(float)temp_add_vol));
  	}
}
void olng_operate_disp2(BOOL bInit,float GV,float desenty,float press)
{

		    olcm_dispprintf(0,2,"流量: %3.02f    ",GV);
		    olcm_dispprintf(0,3,"密度: %3.02f  ",desenty);
                    olcm_dispprintf(0,4,"压力: %3.02f    ",press);
     //               olcm_dispprintf(0,4,"                ");
}
void show_operat_stop(float GV,float AM)
{
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"加气结束");
    olcm_dispprintf(0,2,"气量：%.2f",GV);
    olcm_dispprintf(0,3,"金额：%.2f",AM);
}

BOOL olng_operate_put_card()//rg170717 
{
//    float pay;
     INT32 pay,jyje;
    UINT8 jy[20],qy[20];
    UINT8 len,i,*zz,len2;
    UINT8 * plen = &len;
    UINT8 car_state;//rg170713  解灰后判断状态，最多3次
    INT8     j;//rg170713  解灰后判断状态，最多3次
    	UINT8 test_cn[10];//RG170925
	UINT8 y,status,*pinfo,lenx;//RG170925
	y=1;//RG170925
	car_state=0;//rg170713  解灰后判断状态，最多3次
 //_10ms_tick2_=0;
        len = sizeof(jy);
        memset(jy,0,20);
    gas_record.grey_unlock_inif.grey_status &=  0x0F;                          // 加气记录   清空解灰状态
//***************//RG170925********扣款前先验证卡号是否一致*********************************************************************//	
	ortcc_read_time(gas_record.grey_unlock_inif.time);                    // 加气记录   解灰时间   放置在此，解灰失败也是可以获取解灰时间的
	olng_operate_card_info(); 
        pinfo = ic_operate_info("CN", global_ic_card_info, &lenx);
        if (pinfo != NULL)
        {
           memset(test_cn, 0, sizeof (test_cn));
            memcpy(test_cn, pinfo, lenx);
            gas_record.card_id_js = (UINT32)atoi(test_cn);                                             // 将卡号字符转换为整型  ss190306
        }
        else
        {
            
            memset(test_cn, '1', 10);                                                     // 卡号获取失败,将卡号赋予1 
            gas_record.card_id_js = (UINT32)atoi(test_cn);                                             // 将卡号字符转换为整型  ss190306
            gas_record.grey_unlock_inif.grey_status |=  GREY_CARD_CHEKE_FAILL;                          // 卡号错误异常 
            return FALSE;
        }
        
        y=memcmp(CN,test_cn,10);
        if(y != 0)
        { 
            SOEACTION1(carcmp_err,eCurRunState);
             gas_record.grey_unlock_inif.grey_status |=  GREY_CARD_CHEKE_FAILL;                          // 卡号错误异常 ss190306
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
                  gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败

                  return FALSE;
              }
                delay_ms(500);
                len = sizeof(jy);
                memset(jy,0,20);
                if(GetCard_info(02,jy,plen,10) == APDUS_SUCCESS)//金额
                        {
                  zz =ic_operate_info_int(jy,&len2);
                  jyje=atoi(zz);
                        }
                i++;		  
            }while((Rec_Card_EndM_int!=jyje)&&(i<4));
            if(i>=4)
            {
              SOEACTION1(kk_w_err,eCurRunState);
              olcm_dispprintf(2,4,"扣款校验失败");
              gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
              return FALSE;
            }
            break;
        case PREE_GASE:
            pay = Rec_Card_Endg_int;
            do
              {
                if(ic_card_put_gass(pay) == FALSE) 
                {
                    gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
                    return FALSE;
                }
                  delay_ms(500);
                  len = sizeof(qy);
                  memset(qy,0,20);
                  if(GetCard_info(03,qy,plen,10) == APDUS_SUCCESS)//金额
                          {
                            zz =ic_operate_info_int(qy,&len2);
                            jyje=atoi(zz);
                          }
                  i++;		  
              }while((Rec_Card_Endg_int!=jyje)&&(i<4));
                if(i>=4)
              {
                   SOEACTION1(kk_w_err,eCurRunState);
                olcm_dispprintf(2,4,"扣款校验失败");
                gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
                return FALSE;
              }
            break;
        case ACCOUNT_MONEY:
            pay = Rec_Card_EndM_int;//Rec_Card_PreM - OKgas_money;
               do
              {
                if(ic_card_put_money(pay) == FALSE)                // 扣款完成
                {
                    gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
                    return FALSE;
                }
                  delay_ms(500);
                  len = sizeof(jy);
                  memset(jy,0,20);
                  if(GetCard_info(02,jy,plen,10) == APDUS_SUCCESS)//金额
                          {
                            zz =ic_operate_info_int(jy,&len2);
                            jyje=atoi(zz);
                          }
                  i++;
               }while((Rec_Card_EndM_int!=jyje)&&(i<4));
                if(i>=4)
              {
                   SOEACTION1(kk_w_err,eCurRunState);
                olcm_dispprintf(2,4,"扣款校验失败");
                gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
                return FALSE;
              }
            break;
        case ACCOUNT_GASS:
             pay = Rec_Card_Endg_int;//Rec_Card_Preg - OKgas_GV;
                do
              {
                if(ic_card_put_gass(pay) == FALSE) 
                {
                    gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
                    return FALSE;
                }
                  delay_ms(500);
                  len = sizeof(qy);
                  memset(qy,0,20);
                  if(GetCard_info(03,qy,plen,10) == APDUS_SUCCESS)//金额
                          {
                             zz =ic_operate_info_int(qy,&len2);
                             jyje=atoi(zz);
                          }
                  i++;		  
              }while((Rec_Card_Endg_int!=jyje)&&(i<4));
                if(i>=4)
              {
                SOEACTION1(kk_w_err,eCurRunState);
                olcm_dispprintf(2,4,"扣款校验失败");
                gas_record.grey_unlock_inif.grey_status |=  GREY_ACCOUNTS_FAILL;                          // 加气记录  扣款失败
                return FALSE;
              }
            break;
            
             default :                                                           // ss190306  扣款异常情况处理
                gas_record.grey_unlock_inif.grey_status |= GREY_ACCOUNTS_STATU_FAILL;           // 小票信息保存消费方式异常情况 
                    return FALSE;
                break;
    }
//*****************//rg170713  解灰后判断状态，最多3次************************************************************//    
	j = 3;
	while (j) 
        {
            if (TRUE == ic_card_put_status(CARDS_NORMAL)) 
            {
                delay_ms(50);
                car_state = ic_card_get_status_nosel();
                if (car_state == CARDS_NORMAL) 
                {
                    ortcc_read_time(gas_record.grey_unlock_inif.time);                    // 加气记录   解灰时间       
                    gas_record.grey_unlock_inif.grey_status  |=  GREY_UNLUCK_SUCC;                          // 加气记录  解灰成功
                    return TRUE;
                }
            }
            j--;
            delay_ms(50);
	}

	if (j <= 0)
        {
            gas_record.grey_unlock_inif.grey_status |=  GREY_UNLUCK_FAILL;                          // 加气记录  扣款完成，未解灰
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
      if (TRUE != qty_get_sw(&num)) {//通信异常

				SOEACTION1(PRO422_ERR, eCurRunState);
//				return;
			}
    i = (num >> 5)&0x01;  
    /////////////////////////////////////////////////
     oprint_header_cmd();
    
   oprint_normal_cmd();
    oprint_printf("下班记录\r\n"); //cur_sysparas
 
    oprint_printf("\r\n");
    oprint_printf("站号:%d\r\n", Cur_StationNo);
    oprint_printf("枪号:%d\r\n", cur_sysparas.p_gid );//cur_shiftid
    oprint_printf("班组:%d\r\n", cur_shiftid );
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", carnum);
    oprint_printf("卡号:%s\r\n",buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", rec);
    oprint_printf("班流水号:%s\r\n",buf);

    oprint_printf("加气笔数:%d\r\n",class_q);
         if(i == 1)//rg170707
    { oprint_printf("当值班累:%d.%02d kg\r\n",class_h/100,class_h%100);
    oprint_printf("开始枪累:%d.%02d kg\r\n",gain_q/100,gain_q%100);
    oprint_printf("结束枪累:%d.%02d kg\r\n",gain_h/100,gain_h%100);}
    else if(i == 0)//rg170519
    {
	 oprint_printf("当值班累:%d.%02d m3\r\n",class_h/100,class_h%100);
    oprint_printf("开始枪累:%d.%02d m3\r\n",gain_q/100,gain_q%100);
    oprint_printf("结束枪累:%d.%02d m3\r\n",gain_h/100,gain_h%100);    
    }
    else//rg170519
    {
	 oprint_printf("当值班累:%d.%02d m3\r\n",class_h/100,class_h%100);
    oprint_printf("开始枪累:%d.%02d m3\r\n",gain_q/100,gain_q%100);
    oprint_printf("结束枪累:%d.%02d m3\r\n",gain_h/100,gain_h%100);      
    }
   // oprint_printf("开始枪累:%.02f kg\r\n",gain_q);
   // oprint_printf("结束枪累:%.02f kg\r\n",gain_h);
    if((Sign_Name[0]!=0x00)||(Sign_Name[1]!=0x00)||(Sign_Name[2]!=0x00))//rg170707
    {//rg160907
    memset(buf, 0, sizeof(buf));//rg160907
    sprintf(buf, "%s", Sign_Name);//rg160907
    oprint_printf("员工号:%s\r\n",buf);//rg160907
    }//rg160907
    oprint_printf("日期:20%02d年%02d月%02d日\r\n", sys_time[0],sys_time[1], sys_time[2]);
    oprint_printf("时间:%02d时%02d分%02d秒",sys_time[3], sys_time[4], sys_time[5]);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
       if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
       else
    oprint_printf("烟台杰瑞路第一加气站\r\n");
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
    if (TRUE != qty_get_sw(&num)) {//通信异常

				SOEACTION1(PRO422_ERR, eCurRunState);
//				return;
			}
    oprint_header_cmd();
    if(Hard_Info[0]==0)
    oprint_printf("欢迎使用杰瑞LNG加气机\r\n"); //cur_sysparas
    else
    oprint_printf(Hard_Info);
    oprint_normal_cmd();
    oprint_printf("\r\n");
 
    oprint_printf("站号:%d\r\n", Cur_StationNo);
    oprint_printf("枪号:%d\r\n", cur_sysparas.p_gid );
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN_PRINT);
    oprint_printf("卡号:%s\r\n",buf);
    sprintf(buf, "%s", CP_PRINT);//rg170607 加气信息车牌号
    oprint_printf("车牌号:%s\r\n",buf);//rg170607 加气信息车牌号
    
    oprint_printf("流水号:%d\r\n",ID_PRINT);
       i = (num >> 5)&0x01;//标记：rg170707
			if (i == 1)
			{ 
				oprint_printf("单价:%.02f 元/kg\r\n",DJ_PRINT);
				oprint_printf("加气量:%.02f kg\r\n",QL_PRINT);
			
			}
			else if (i == 0)
			{
				oprint_printf("单价:%.02f 元/m3\r\n",DJ_PRINT);	
			oprint_printf("加气量:%.02f m3\r\n",QL_PRINT);
			
			}
			else
			{
				oprint_printf("单价:%.02f 元/kg\r\n",DJ_PRINT);	
			oprint_printf("加气量:%.02f kg\r\n",QL_PRINT);
			
			}	
 //   oprint_printf("加气量:%.02f kg\r\n",QL_PRINT);
 //   oprint_printf("单价:%.02f 元/kg\r\n",DJ_PRINT);
    oprint_printf("金额:%.02f元\r\n",JE_PRINT);
    if(HQ_PRINT==0)//rg180131
    oprint_printf("回气量:%.02fkg\r\n",HQL_PRINT);//rg180131
    if(CN_PRINT[2] != 0x35)//rg170717
    {
        yp=inttoa(KY_PRINT);//rg170607 加气信息车牌号
        memset(yu,0x00,12);//rg170607 加气信息车牌号
        memcpy(yu,yp,10);//rg170607 加气信息车牌号
        oprint_printf("卡余:%s元\r\n",yu);//rg170607 加气信息车牌号
    }
         if(PR_YGH != 0)
    {
    oprint_printf("员工号:%03d\r\n",PR_YGH);//rg160907
    }
    oprint_printf("日期:20%02d年%02d月%02d日\r\n", RQ_PRINT[0],RQ_PRINT[1], RQ_PRINT[2]);
    oprint_printf("时间:%02d时%02d分%02d秒",RQ_PRINT[3], RQ_PRINT[4], RQ_PRINT[5]);

   oprint_printf("\r\n");
   oprint_printf("********查询票据联********\r\n");
    oprint_printf("\r\n");
    if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
    if(Contact_Info[0]!=0)
    {
    oprint_printf(Contact_Info);
    }
     oprint_printf("\r\n");
    oprint_printf("----欢迎下次光临----\r\n");
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
//	   if(TRUE != qty_get_serrec(pr_lsh,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq))//RG160907//rg170607 加气信息车牌号
    if(TRUE != qty_get_serrec(pr_lsh,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq,&wz))//RG160907//rg170607 加气信息车牌号
       {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
//           return;
       }  
	st=1;
	memcpy(get_time,edati,6);
     }
    oprint_header_cmd();
    if(Hard_Info[0]==0)
    oprint_printf("欢迎使用杰瑞LNG加气机\r\n"); //cur_sysparas
    else
    oprint_printf(Hard_Info);
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("站号:%d\r\n", Cur_StationNo);
    oprint_printf("枪号:%d\r\n", cur_sysparas.p_gid );
    oprint_printf("班组:%d\r\n", cur_shiftid );
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", pr_lsh);
      if(CN[2] !='3')
      {  oprint_printf("流水号:%s\r\n",buf);  }
      else
      {
          oprint_printf("调试流水号:%d\r\n",MAX_dubug_recid_num);
      }

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN);
    oprint_printf("卡号:%s\r\n",buf);

//    oprint_printf("出液量(液相):%.02f kg\r\n",OKgas_GV+GAS_BACKGV);
//    oprint_printf("回气量(气相):%.02f kg\r\n",GAS_BACKGV);
  //  zkk=(Discount[0]<<8)+Discount[1];
//    0,4,"%3d ％  %2x%02x%02x%02x",zk[1],qx[0],qx[1],qx[2],qx[3])
 //   sprintf(buf, "%2f",Discounf);
    if(Discounf!=100)
    {oprint_printf("折扣系数:%0.2f ％\r\n",Discounf);
  oprint_printf("折扣有效期:%02x%02x/%02x/%02x\r\n",Discount_validity[0],Discount_validity[1],Discount_validity[2],Discount_validity[3]);
    }
oprint_printf("执行单价:%.02f 元/kg\r\n",Cur_Price);

    oprint_printf("加气量:%.02f kg\r\n",OKgas_GV);
    if(HQ_PRINT==0)//rg180131
    oprint_printf("回气量:%.02fkg\r\n",GAS_BACKGV);//rg180131
//    oprint_printf("单价:%.02f 元/kg\r\n",PRICE);
    oprint_printf("金额:%.02f元\r\n",OKgas_money);
    if(_CARD_TYPE != CARDT_SMALL)//rg170717
    {
    if((CARD_XIAOFEI==0)||(CARD_XIAOFEI==2))
    {
	    yp=inttoa(Rec_Card_EndM_int);
      memset(yu,0x00,12);
      memcpy(yu,yp,10);
        oprint_printf("余额:%s元\r\n",yu);
    }
    else if((CARD_XIAOFEI==1)||(CARD_XIAOFEI==3))
    { 
	    yp=inttoa(Rec_Card_Endg_int);
      memset(yu,0x00,12);
      memcpy(yu,yp,10);
     oprint_printf("余额:%s kg\r\n",yu);
    }
    }
#if 1
/*    if((CPBH[0]!=0x00)&&(CPBH[1]!=0x00))
    {
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CPBH);
    oprint_printf("车牌号:%s\r\n",buf);
    }*/
                if(CPH[0]!=0x00)//rg170620
        {
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s", CPH);
        oprint_printf("车牌号:%s\r\n",buf);
        }
    //rg170620
/*    if(GPBH[0]!=0x00)
    {
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", GPBH);
    oprint_printf("钢瓶号:%s\r\n",buf);
    }*/
#endif
  //  pyygh=atoi(Sign_Name);//rg160907
  //  if(pyygh !=0)//rg160907
    if((Sign_Name[0]!=0x00)||(Sign_Name[1]!=0x00)||(Sign_Name[2]!=0x00))//rg170620
    {//rg160907
    memset(buf, 0, sizeof(buf));//rg160907
    sprintf(buf, "%s", Sign_Name);//rg160907
    oprint_printf("员工号:%s\r\n",buf);//rg160907
    }//rg160907
    if(st==0)
    {
	    oprint_printf("日期:20%02d年%02d月%02d日\r\n", sys_time[0],sys_time[1], sys_time[2]);
    oprint_printf("时间:%02d时%02d分%02d秒",sys_time[3], sys_time[4], sys_time[5]);
    }
    else
    {
	  oprint_printf("日期:20%02d年%02d月%02d日******\r\n", get_time[0],get_time[1], get_time[2]);
    oprint_printf("时间:%02d时%02d分%02d秒******",get_time[3], get_time[4], get_time[5]);  
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
    oprint_printf("****Random%02d%.02f%02d%.02f%d%02d*****\r\n", (sys_time[4]+1),(Cur_Price+OKgas_GV),(sys_time[1]*2),(OKgas_GV+111.11),(pr_lsh+10),(sys_time[2]+sys_time[5]));//分加1，执行单价加气量，月乘2,气量加111.11，流水号加10，日加秒；

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
//    oprint_printf("烟台杰瑞路第一加气站\r\n");
   
    oprint_printf("----欢迎下次光临----\r\n");
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
    oprint_printf("欢迎使用杰瑞LNG加气机\r\n"); //cur_sysparas
    else
    oprint_printf(Hard_Info);
//    oprint_printf("欢迎使用杰瑞LNG加气机\r\n"); //cur_sysparas
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");
       oprint_printf("站号:%d\r\n", Cur_StationNo);
    oprint_printf("枪号:%d\r\n", cur_sysparas.p_gid );

     memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", pr_lsh);
    oprint_printf("流水号:%s\r\n",buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN);
    oprint_printf("卡号:%s\r\n",buf);
        oprint_printf("折扣系数:%s\r\n",buf);
    sprintf(buf, "%s",Discount_validity);
    oprint_printf("折扣有效期:%s\r\n",buf);
 oprint_printf("执行单价:%.02f 元/kg\r\n",Cur_Price);

    oprint_printf("出液量:%.02fkg\r\n",OKgas_GV);
    oprint_printf("回气量:%.02fkg\r\n",GAS_BACKGV);

    oprint_printf("加气量:%.02fkg\r\n",OKgas_GV - GAS_BACKGV);
//    oprint_printf("单价:%.02f元/kg\r\n",PRICE);
    oprint_printf("金额:%.02f元\r\n",(OKgas_GV - GAS_BACKGV)*Cur_Price);
    oprint_printf("日期:20%02d年%02d月%02d日\r\n", sys_time[0],sys_time[1], sys_time[2]);
    oprint_printf("时间:%02d时%02d分%02d秒",sys_time[3], sys_time[4], sys_time[5]);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    if(Print_Info[0]!=0)
   oprint_printf(Print_Info);
if(Contact_Info[0]!=0)
    oprint_printf(Contact_Info);
 //   oprint_printf("烟台杰瑞路第一加气站\r\n");
    oprint_printf("----欢迎下次光临----\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
}
void Get_gas_money()
{
           if((CARD_XIAOFEI>=2)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)))//公司卡或私车卡的记账类型
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
        else if((CARD_XIAOFEI<2)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)))//公司卡或私车卡的预购类型
        {
           car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
        }
	 else if(_CARD_TYPE==CARDT_SMALL)//rg170717 后台传来的是额度+余额，直接可以用
	{
		car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
	}  
	   
        else if(_CARD_TYPE==1)                            //班组卡一定是记账类型
        {
            car_prem=Rec_Card_PreM;
            car_prel=Rec_Card_Preg;
        }
	
        else                                                //其它情况
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
       else if((car_prem-Mini_FD) < FIX_Money)//rg170606最小加气量
        {
          *carprem=car_prem;
          FIX_Money=car_prem-Mini_FD;//rg170606最小加气量
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
        else if((car_prel*Cur_Price-Mini_FD) < FIX_Money)//rg170606最小加气量
        {
          FIX_Money=car_prel*Cur_Price-Mini_FD;//rg170606最小加气量
          return TRUE;
        }
        else
            return TRUE;
    }
 
     else if((CARD_XIAOFEI==ACCOUNT_MONEY)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)))//用户卡记账金额
     {
         if((mlc-fabs(Rec_Card_PreM))<FIX_Money)
         {
             *carprem=Rec_Card_PreM;
//             FIX_Money=mlc-fabs(Rec_Card_PreM);
             return FALSE;
         }
         else if((mlc-fabs(Rec_Card_PreM)-Mini_FD)<FIX_Money)//rg170606最小加气量
         {
             *carprem=Rec_Card_PreM;
             FIX_Money=mlc-fabs(Rec_Card_PreM)-Mini_FD;//rg170606最小加气量
             return TRUE;
         }
         else
         { //*get_money=FIX_Money;
         return TRUE;}
     }
     else if((CARD_XIAOFEI==ACCOUNT_GASS)&&((_CARD_TYPE==3)||(_CARD_TYPE==2)))////用户卡记账气量
     {
         if((glc-fabs(Rec_Card_Preg))*Cur_Price<FIX_Money)
         {
             *carprem=Rec_Card_Preg;
             return FALSE;
         }
         else if(((glc-fabs(Rec_Card_Preg))*Cur_Price-Mini_FD)<FIX_Money)//rg170606最小加气量
         {
             *carprem=Rec_Card_Preg;
             FIX_Money=(glc-fabs(Rec_Card_Preg))*Cur_Price-Mini_FD;//rg170606最小加气量
             return TRUE;
         }
         else
         {
         return TRUE;}
     }
	else if((CARD_XIAOFEI==ACCOUNT_MONEY)&&(_CARD_TYPE==CARDT_SMALL))//用户卡记账金额 //rg170717  子卡
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
        else  if((car_prem-smallMini_FD) < FIX_Money)//rg170606最小加气量//rg181210
		{
		  *carprem=car_prem;
		  FIX_Money=car_prem-smallMini_FD;//rg170606最小加气量//rg181210
		 return TRUE;
		}
		else
		    return TRUE;
	}	
    else if(((CARD_XIAOFEI==ACCOUNT_GASS)||(CARD_XIAOFEI==ACCOUNT_MONEY))&&(_CARD_TYPE==1))////班组卡记账气量
    {
         //*get_money=FIX_Money;
        return TRUE;
    }
}
BOOL Get_again_gas_money(float *max_mone)//rg170717 增加子卡类型判断
{
     if((car_prel>1)&&( car_prem==0)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//正常气量卡，不分记账和预购 //rg170717 增加子卡类型判断
    {
     *max_mone= car_prel*Cur_Price- OKgas_money;
     return TRUE;
    }
    else if((car_prel==0)&&(car_prem>=Cur_Price)&&((_CARD_TYPE==2)||(_CARD_TYPE==3)||(_CARD_TYPE==CARDT_SMALL)))//正常金额卡，不分记账和预购 //rg170717 增加子卡类型判断
    {
    *max_mone = car_prem - OKgas_money;//可加气的金额 = 加气前卡余-本次加气量(累计量)
    return TRUE;
    }

    else if((_CARD_TYPE==1)&&(CARD_XIAOFEI==2))  //班组卡，记账金额
    {
    *max_mone = car_prem - OKgas_money;//可加气的金额 = 加气前卡余-本次加气量(累计量)
    return TRUE;
    }
    else if((_CARD_TYPE==1)&&(CARD_XIAOFEI==3))  //班组卡，记账气量
    {
    *max_mone = car_prel*Cur_Price - OKgas_money;//可加气的金额 = 加气前卡余-本次加气量(累计量)
    return TRUE;
    }
    else
    {
        *max_mone = 0;
        return FALSE;
    }
}
BOOL olngctrl_juPSW(UINT8 *xx)//rg170621  插卡先输密码
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
   if((WKJQ==1)||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))//rg170531无卡加气
    {
	   car_status = machine_status_card();
	    while(car_status!=CPU_TYPE_A)
        {
           olcm_dispprintf(0,1,"请插入加气卡    ");
           olcm_dispprintf(0,2,"                ");
           olcm_dispprintf(0,3,"  按更改键退出  ");
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
	    if(WKJQ==1)//rg170531无卡加气
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
		     if(((WKJQ ==0)&&(CARTYPE == CARDT_CLASS))||(CARTYPE == CARDT_SMALL))//rg170531无卡加气rg180322
			     return TRUE;
		     else
		     {  
			     *xx=3;
		            return FALSE;
		     }
            }
            if(carstate==CARDS_NULLIFY)
            {
		    if((WKJQ ==0)&&(CARTYPE == CARDT_CLASS))//rg170531无卡加气
			     return TRUE;
		    else
		    {
				    *xx=8;
				return FALSE;
		    }
            }
#if 1 //rg170607 插卡先验证密码
  if((memcmp(pinfo,"40000002",len1) == 0) ||(memcmp(pinfo,"40000003",len1) == 0)||(memcmp(pinfo,"40000005",len1) == 0))// class group card//r170717g
    {   memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//获得卡密码
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
		if(bj == 0)//rg170621  插卡先输密码
        {
            *xx=4;
           return TRUE;
        }
        else
        {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--加气验证--");
        olcm_dispprintf(0,2,"请输入卡密码  ");
        olcm_dispprintf(0,3,"密码:  ");
	memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //密码在插入卡时已经获得
		 bj=strcmp(pass, passbuf);
                 if((len2 == len1)&&(bj == 0))
                      {
                             *xx=5;
                                return TRUE;
                      }
                 else
                   //密码错误
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
        ic_card_get_password(passbuf,&len2);//获得卡密码
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
		if(bj == 0)//rg170621  插卡先输密码
        {
            *xx=4;
           return TRUE;
        }
        else
        {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"--加气验证--");
        olcm_dispprintf(0,2,"请输入卡密码  ");
        olcm_dispprintf(0,3,"密码:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //密码在插入卡时已经获得
		 bj=strcmp(pass, passbuf);
                 if((len2 == len1)&&(bj == 0))
                      {
                             *xx=5;
                                return TRUE;
                      }
                 else
                   //密码错误
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
double Get_Gp_Time(UINT8 *qx)//计算钢瓶是否到期
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
//计算秒
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
//    Pr_gr = 1;                    //价格等级
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
       Discounf=100.0;                  //折扣无效
  
    }
    Cur_Price=price_x*Discounf/100;
    Cur_Price = sys_get_float(Cur_Price); //4舍5入
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
   if(TRUE == ReadCard_info(&_CARD_TYPE,CN,&Rec_Card_PreM,&Rec_Card_Preg,&Rec_Card_PreM_int,&Rec_Card_Preg_int,&mlc,&glc,&CARD_XIAOFEI,&Pr_gr,&Discounf,Discount_validity,CPBH,GPBH))//获得卡信息
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
        {sumlen=i;//sumlen最大是9
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
    g_pf=sys_get_float(g_pf);//取个位整数与小数
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

      //   SOEACTION1(PRO422_ERR,eCurRunState);//后期关上
       //    return;
     olcd_clearsCreen();
      olcm_dispprintf(0,1,"正在与主板通信");
      cur_max_recid = get_max_rec_id();
     if(0xFFFF0000 ==cur_max_recid)
      {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
//        delay_ms(3000);
        id = maxid = cur_max_recid;//init里获得
        if( id == 0 ){
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"无流水记录！");
             osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_VIRTUAL_EV_;

            return;
        }
float dj;float je;float ql;UINT32 *recg;
float hq;
        UINT8 edati[6],cn[10];
	UINT16 ygh;//RG160907
	UINT32 ky;//rg170607 加气信息车牌号
	UINT8 cp[12],wz;//rg170607 加气信息车牌号
	memset(cp,0x0,12);//rg170607 加气信息车牌号
//       if(TRUE != qty_get_serrec(id,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq))//RG160907//rg170607 rg180131加气信息车牌号
     if(TRUE != qty_get_serrec(pr_lsh,&dj,&je,&ql,edati,cn,&ygh,&ky,cp,&hq,&wz))//RG160907//rg170607 加气信息车牌号
       {//通信异常
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
       memcpy(CP_PRINT,cp,12);//rg170607 加气信息车牌号
       KY_PRINT=ky;
 if (TRUE != qty_get_sw(&num)) {//通信异常

				SOEACTION1(PRO422_ERR, eCurRunState);
//				return;
			}
       olcm_dispprintf(0,1,"正在打印        ");
       oprint_normal_cmd();
 //   oprint_header_cmd();

    if(Hard_Info[0]==0)
    oprint_printf("欢迎使用杰瑞LNG加气机\r\n"); //cur_sysparas  由CNG 修改为LNG  
    else
    oprint_printf(Hard_Info);
    oprint_normal_cmd();
    oprint_printf("站号:%d\r\n", Cur_StationNo);
    oprint_printf("枪号:%d\r\n", cur_sysparas.p_gid );
        oprint_printf("流水号:%d\r\n",ID_PRINT);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", CN_PRINT);
    oprint_printf("卡号:%s\r\n",buf);
    sprintf(buf, "%s", CP_PRINT);//rg170607 加气信息车牌号
    oprint_printf("车牌号:%s\r\n",buf);//rg170607 加气信息车牌号
    i = (num >> 5)&0x01;
			if (i == 1)
			{ 
				oprint_printf("单价:%.02f 元/kg\r\n",DJ_PRINT);
				oprint_printf("加气量:%.02f kg\r\n",QL_PRINT);
			
			}
			else if (i == 0)
			{
				oprint_printf("单价:%.02f 元/m3\r\n",DJ_PRINT);	
			oprint_printf("加气量:%.02f m3\r\n",QL_PRINT);
			
			}
			else
			{
				oprint_printf("单价:%.02f 元/kg\r\n",DJ_PRINT);	
			oprint_printf("加气量:%.02f kg\r\n",QL_PRINT);
			
			}	
				
//    oprint_printf("单价:%.02f 元/kg\r\n",PRICE);
    oprint_printf("金额:%.02f元\r\n",JE_PRINT);
    if(HQ_PRINT==0)//rg180131
    oprint_printf("回气量:%.02fkg\r\n",HQL_PRINT);//rg180131
    if(CN_PRINT[2] != 0x35)//rg170717
    {
         yp=inttoa(KY_PRINT);//rg170620
        memset(yu,0x00,12);//rg170620
        memcpy(yu,yp,10);//rg170620
        oprint_printf("卡余:%s元\r\n",yu);//rg170620
    }
        if(PR_YGH != 0)
    {
    oprint_printf("员工号:%03d\r\n",PR_YGH);//rg160907
    }
    oprint_printf("日期:20%02d年%02d月%02d日\r\n", RQ_PRINT[0],RQ_PRINT[1], RQ_PRINT[2]);
    oprint_printf("时间:%02d时%02d分%02d秒",RQ_PRINT[3], RQ_PRINT[4], RQ_PRINT[5]);
    oprint_printf("\r\n");
oprint_printf("********查询票据联********\r\n");//rg170620
//oprint_printf("\r\n");
    if(Print_Info[0]!=0)
    oprint_printf(Print_Info);
    if(Contact_Info[0]!=0)
    {
    oprint_printf(Contact_Info);}
     oprint_printf("\r\n");
    oprint_printf("----欢迎下次光临----\r\n");
    oprint_printf("\r\n");
//Recv_PR_ok=0;
 //   memset(Recv_PR_Buf,0x00,80);
    eVirtualKey = _KEY_EXIT_EV_;
}
//    return TRUE;
//}
#if 0

#endif