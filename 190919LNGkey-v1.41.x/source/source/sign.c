/*
 author: xiaolin
 time: 2014-4-1  last version
 */



#include "../includes/global_def.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum sigin_error
{
    SIG_PASS_ERROR,
    CARD_TYPE_ERROR,
    CARD_STATION_ERROR,
    CARD_CurStationNo_ERROR,
	SIG_time_over,//RG170701
}sigin_error;
sigin_error sig_err;
/**authorv : xiaolin time 2014-03-14  14:24*/
void show_get_sppass()//rg170531无卡加气
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    锁屏状态    ");
    olcm_dispprintf(0,2,"请插卡解锁  ");
    olcm_dispprintf(0,3,"密码:  ");
}
void show_get_pass()
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"    欢迎登录    ");
    olcm_dispprintf(0,2,"请输入卡密码  ");
    olcm_dispprintf(0,3,"密码:  ");
}
/**authorv : xiaolin time 2014-03-14  14:24*/
void show_get_card()
{
    // olcd_clearsCreen();  去闪屏
     olcm_dispprintf(0,1,"    欢迎登录    ");
     olcm_dispprintf(0,2,"  请插入班组卡  ");
     olcm_dispprintf(0,3,"                ");  //不可省掉，因无提前的刷屏olcd_clearsCreen();
     olcm_dispprintf(0,4,"                ");  //不可省掉，因无提前的刷屏olcd_clearsCreen();
}
/**authorv : xiaolin time 2014-03-14  14:24*/
void show_zhan_error()
{
     olcd_clearsCreen();
     olcm_dispprintf(2,1,"    欢迎登录");
     olcm_dispprintf(0,2,"请更换本站班组卡");
}
void show_zhan_ling()
{
     olcd_clearsCreen();
     olcm_dispprintf(2,1,"欢迎登录");
     olcm_dispprintf(0,2,"  获取信息错误");
     olcm_dispprintf(0,3,"请断电检查通讯线");
}
void show_pass_error()
{
     olcd_clearsCreen();
     olcm_dispprintf(2,1,"    欢迎登录");
     olcm_dispprintf(0,2,"密码错误请重输！");
}
void show_card_type_error()
{
    olcd_clearsCreen();
    olcm_dispprintf(2,1,"欢迎登录");
    olcm_dispprintf(1,2,"卡类型错误");
    olcm_dispprintf(1,3,"请插入班组卡");
}
/**author :       xiaolin 
 * time:          2014-03-14     14:25*/
/* Interduction:
 * function for  sign on the system; Cycle check the card, change the show window by the the status that the the machine has card or not;
 * IF the machine has card, get the user inputing password in a certain time. In the certain time putting key event has't been happen,
 * the system  while get into next loop; If the user put into password,check the password and system stored;IF its words value and length  equal,
 * the system will init the begin status and allow the user log in the system;
 *
 *
 *  */
/* authoer: xiaolin  time 2013-3-14  18:00 */
void sign_startup(void)
{
   // olcd_clearsCreen();  wang
    if(_b_have_card)
    {   olcd_clearsCreen();
       olcm_dispprintf(0,1,"正在读卡信息"); //显示此条信息，为解决系统调度造成的白屏。
       olcm_dispprintf(0,2,"请稍等。。。。"); //显示此条信息，为解决系统调度造成的白屏。
        eVirtualKey = _KEY_LOGIN_HAVECARD;
     
    }
    else
    {
         read_keyv_CS = 0;
        eVirtualKey = _KEY_LOGIN_NOCARD;
       
    }
}
/* authoer: xiaolin  time 2013-3-14  18:00 */
void sign_nocard(void)
{
    show_get_card();
    eVirtualKey = _EVENT_TRUE;
}
void olng_operate_card_info()
{
    card_info_len = sizeof(global_ic_card_info);
    memset(global_ic_card_info, 0, card_info_len);
    ic_card_get_info(global_ic_card_info, &card_info_len); 
}
void olng_operate_card_info_nosel()
{
    card_info_len = sizeof(global_ic_card_info);
    memset(global_ic_card_info, 0, card_info_len);
    ic_card_get_info_nosel(global_ic_card_info, &card_info_len);
}
/* authoer: xiaolin  time 2013-3-14  18:00 */
void sign_has_card(void)
{   UINT8 *TNfo;
    UINT8 Is_offwork;
    UINT8 passbuf[10];
    UINT8 pass[10];
    UINT8 Tinfo[4];
    UINT8 len1,len2 = 6;
    UINT8 len;
    UINT8  *pinfo;
    UINT8 _station;
    UINT8  shift_CN[10];
     UINT8  bpc1[10],bpc2[10];
      UINT8  *name;//RG160907
    UINT8 Tname[16];//RG160907
    UINT8 bj;//rg170531
        UINT8 yg,TB_op_time[6];//rg170701
    BOOL  tbjoin;//rg170701
    memset(Sign_Name, 0x00, 3);//rg160907
    olng_operate_card_info();
#if 0
    pinfo = ic_operate_info("BCD",global_ic_card_info, &len);
         if(pinfo==NULL)
           {
                sig_err = CARD_TYPE_ERROR;
       //         eVirtualKey = _KEY_LOGIN_ERROE;
      //          return;
           }
         memset(bpc1, 0, sizeof(bpc1));
         memcpy(bpc1, pinfo, len);
  pinfo = ic_operate_info("BCAVD",global_ic_card_info, &len);
         if(pinfo==NULL)
           {
                sig_err = CARD_TYPE_ERROR;
     //           eVirtualKey = _KEY_LOGIN_ERROE;
    //            return;
           }
         memset(bpc2, 0, sizeof(bpc2));
         memcpy(bpc2, pinfo, len);
#endif
        pinfo = ic_operate_info("CN",global_ic_card_info, &len);
         if(pinfo==NULL)
           {
                sig_err = CARD_TYPE_ERROR;
                eVirtualKey = _KEY_LOGIN_ERROE;
                return;
           }
         memset(shift_CN, 0, sizeof(shift_CN));
         memcpy(shift_CN, pinfo, len);
       _station = (shift_CN[0]-0x30)*10+(shift_CN[1]-0x30);
//       Cur_StationNo=2;
#if 1
       if( (Cur_StationNo==0) &&(Is_debuggas_Read!=1) )   //150817 调试加气开关不判站号
       {
        sig_err = CARD_CurStationNo_ERROR;//SIG_PASS_ERROR;
                  eVirtualKey = _KEY_LOGIN_ERROE;
                  return;
       }
             if( (_station != Cur_StationNo)&&(Is_debuggas_Read!=1) )  //150817 调试加气开关不判站号
             {
                sig_err = CARD_STATION_ERROR;//SIG_PASS_ERROR;
                  eVirtualKey = _KEY_LOGIN_ERROE;
                  return;
             }

#endif
    pinfo = ic_operate_info("CDT",global_ic_card_info, &len1);
    if(pinfo==NULL)
   {
        sig_err = CARD_TYPE_ERROR;
        eVirtualKey = _KEY_LOGIN_ERROE;
        return;
   }
  if(memcmp(pinfo,"40000001",len1) == 0) // class group card 
  {
     ///////////////////////////////////////////////////////
      TNfo = ic_operate_info("TN",global_ic_card_info, &len);//2. group class  number
         memset(Tinfo, 0, sizeof(Tinfo));
         memcpy(Tinfo, TNfo, len);
         ReadTn = atoi(Tinfo);
	 if(((ReadTn<1) || (ReadTn>10))&&(SP==0))//rg170531无卡加气
 //        if((ReadTn>10)||(ReadTn<1))//rg160910
      {
         olcd_clearsCreen();
        olcm_dispprintf(0,1,"    提示    ");
        olcm_dispprintf(0,2,"该班组非法");
        olcm_dispprintf(0,3,"无法登录");
        osys_getkey(_KEY_EXIT_EV_, 300);  
        eVirtualKey = _KEY_LOGIN_ERROE; 
         return;
        }
         Is_offwork = o24lcxxx_read(_CLASSNO_OFFWORK_ADDR); //
 if(SP==0)//rg170531无卡加气
	 {
    if( (Is_offwork == 0) || (Is_offwork >10) ||(Is_offwork == ReadTn)  )
//         if(1)
     {
         show_get_pass();
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {
                 memset(passbuf, 0, sizeof(passbuf));
                 if(ic_card_get_password(passbuf,&len2))
                 {
                      if(len2 == len1)
                      {
                         if(strcmp(pass, passbuf) == 0)
                         {
                          //    olcm_dispprintf(0,4,"正在读取卡信息..");//规避通信迟缓的问题
                              oset_shift_join(); //上班
                              return;
                         }
                      }
                   sig_err = SIG_PASS_ERROR;
                  eVirtualKey = _KEY_LOGIN_ERROE;
                  return;
                }
            }
          }    //end of if( (Is_offwork >10) ||(Is_offwork == ReadTn)  )
    else
    {
         olcd_clearsCreen();
        olcm_dispprintf(0,1,"    提示    ");
        olcm_dispprintf(0,2,"该班组暂不能登录");
        olcm_dispprintf(0,3,"请用%2d组登录",Is_offwork);
        osys_getkey(_KEY_EXIT_EV_, 300);
         return;
    }
 }//END SP==0
	//*************************//rg170531无卡加气***********************************************************//	 
	 else if(SP==1)//rg170531无卡加气
	 {
		         show_get_sppass();
			 ortcc_read_time(TB_op_time);
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {
                 memset(passbuf, 0, sizeof(passbuf));
                 if(ic_card_get_password(passbuf,&len2))
                 {
                      if(len2 == len1)
                      {
			      bj=strcmp(pass, passbuf);
                         if(bj == 0)
                         {
				if((SP==1)&&(b_shift_ok ==1))//rg170531无卡加气
				{
//					SP=0;
///////////////////////////////////rg170701/////////////////////////////////////////////////////
				       pinfo = ic_operate_info("YGH",global_ic_card_info, &len);//rg160907
	 if(pinfo!=NULL)
	{
         memset(Sign_Name, 0, 3);	//rg160907
	 memcpy(Sign_Name, pinfo, len);		//rg160907
	 }
	   yg= atoi(Sign_Name);//rg160907
	   tbjoin = TB_Send_YG(shift_CN,yg,TB_op_time);//RG170701
  //        tbjoin = Shift_join(shift_id,(UINT8 * )shift_card,(UINT8 *)shift_op_time,ygh,zhutime); //发送上班信息rg160907 rg170110
	 if(tbjoin!=TRUE)
	 {
		SOEACTION1(PRO422_ERR,eCurRunState);//通信异常  
		sig_err = SIG_time_over;
                  eVirtualKey = _KEY_LOGIN_ERROE;
		return;
	 }
             
////////////////////////////////////////////////////////////////////////////////////////
					SP=0;
									      memcpy(cure_JQ_card, shift_CN, 10);//rg170531无卡加气
				      memcpy(cure_shift_card, shift_CN, 10);//rg170531无卡加气
				       memcpy(cure_yz_card, shift_CN, 10);//rg170531无卡加气
				      buzzer_power_up_sound();//rg170531无卡加气
				      eVirtualKey = _KEY_LOGIN_SUCCESS;//rg170531无卡加气
				      return;//rg170531无卡加气
				}
//***********************//rg170531无卡加气 END*********************************************************//  
				                         }
                      }
                   sig_err = SIG_PASS_ERROR;
                  eVirtualKey = _KEY_LOGIN_ERROE;
                  return;
                }
            }
	 }
//*************************//rg170531无卡加气***end********************************************************//
    } //end of  if(memcmp(pinfo,"40000001",len1) == 0) // class group card
    else // if the card isn't the class group card,
    {
        sig_err = CARD_TYPE_ERROR;
        eVirtualKey = _KEY_LOGIN_ERROE;
    }
    return;
}
/* authoer: xiaolin  time 2013-3-14  18:50 */
void sign_error(void)
{
    switch(sig_err)
    {
        case CARD_TYPE_ERROR:
            show_card_type_error();
            break;
        case SIG_PASS_ERROR:
             show_pass_error();
             break;
        case CARD_STATION_ERROR:
             show_zhan_error();
             break;
        case CARD_CurStationNo_ERROR:
             show_zhan_ling();
             break;
	case    SIG_time_over://rg170701
	    show_time_over();//rg170701
	    break;//rg170701     
    }
    osys_getkey(_KEY_EXIT_EV_, 320); //wang414
    eVirtualKey = _EVENT_TRUE;
}


/*-------------------------------------------------------------------------------------------------------------------*/
/*_________________________________     上班函数        ___________________________________________________________*/
void print_shift( _shift_loginfo  tmp_shift_sysinfo)
{
    char buf[50];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", tmp_shift_sysinfo.shift_rec_id);
    oprint_printf("shift_rec_id is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", tmp_shift_sysinfo.shift_card);
    oprint_printf("shift_card is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", tmp_shift_sysinfo.shift_id);
    oprint_printf("shift_id is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", tmp_shift_sysinfo.shift_gid);
    oprint_printf("shift_gid is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
     sprintf(buf, "%s", tmp_shift_sysinfo.shift_op_time);
    oprint_printf("shift_op_time is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%f", tmp_shift_sysinfo.shift_s_mount);
    oprint_printf("shift_s_mount is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%f", tmp_shift_sysinfo.shift_e_mount);
    oprint_printf("shift_e_mount is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d", tmp_shift_sysinfo.shift_op_type);
    oprint_printf("shift_op_type is %s\r\n",buf);

    memset(buf, 0, sizeof(buf));
     sprintf(buf, "%d", tmp_shift_sysinfo.recoder_num);
    oprint_printf("recoder_num is %s\r\n",buf);
}
void oset_shift_Exit(void)
{
    UINT8 M =10;
    UINT8  MAX8 =0xFF;
    UINT8  REDMAX8;
    UINT8 *pinfo;
    UINT8 len;
    UINT8 info[20];
    UINT8 celen;
    UINT32  tmp_addr,rec;
    UINT8 Recvjoin;
   //_shift_loginfo    login_recod;
   // _shift_loginfo    login_recod2;
    UINT8    shift_op_time[6];
     UINT8    xdsj[6];
    UINT8    shift_id;
    UINT8    shift_card[10];
    UINT32 class_q,class_h,gain_q,gain_h;
    memset(info, 0, sizeof(info));
    ortcc_read_time(shift_op_time);
       olcd_clearsCreen();
        olcm_dispprintf(0,1,"----下    班----");
        olcm_dispprintf(0,2,"下班准备中。。。");
    if( b_shift_ok != -1 )//未下班
    {
         pinfo = ic_operate_info("TN",global_ic_card_info, &len);//2. group class  number
         if(!pinfo) goto error;
         memset(info, 0, sizeof(info));
         memcpy(info, pinfo, len);
         shift_id = atoi(info);
         cur_shiftid = shift_id;///qaz

         pinfo = ic_operate_info("CN",global_ic_card_info, &len);// 3. group class card  number
         if(!pinfo) goto error;
         memset(shift_card, 0, sizeof(shift_card));
         memcpy(shift_card, pinfo, len);
        if(TRUE != off_work(shift_id,(UINT8 * )shift_card,(UINT8 *)shift_op_time,&rec,&class_q,&class_h,&gain_q,&gain_h,xdsj))
         {//YICHANG//RG3133
             SOEACTION1(PRO422_ERR,eCurRunState);//通信异常
             return;
         }
        offwork_print(shift_card,rec,class_q,class_h,gain_q,gain_h);
         olcm_dispprintf(3,4,"下班成功");
        b_shift_ok = -1;
	memset(Sign_Name, 0x00, 3);//rg160907
        if((xdsj[0]==0x0b)&&(xdsj[1]==0x0b)&&(xdsj[2]==0x0b)&&(xdsj[3]==0x0b)&&(xdsj[4]==0x0b)&&(xdsj[5]==0x0b))//rg160612
        {
          olcm_dispprintf(0,2,"    未对时    ");  
        }
        else
        {
		if((xdsj[5]<60)&&(xdsj[4]<60)&&(xdsj[3]<24)&&(xdsj[2]>0)&&(xdsj[2]<32)&&(xdsj[1]>0)&&(xdsj[1]<13))//rg180621
		{
		if( ortcc_set_date((UINT8*)&xdsj[0]) != TRUE)
		   {
			olcm_dispprintf(0,2,"    对时失败    ");
		    }
		delay_ms(100);
		if( ortcc_set_time((UINT8*)&xdsj[3]) != TRUE)
		    {
			olcm_dispprintf(0,2,"    对时失败    ");
		    }      
		}
        }
        delay_ms(100);
        while(M--)
         {  if ( 1 == o24lcxxx_write_bytes(_CLASSNO_OFFWORK_ADDR,(UINT8*)&MAX8,1 ) )
             { REDMAX8 = o24lcxxx_read(_CLASSNO_OFFWORK_ADDR);
                if(REDMAX8 == MAX8 ) 
                   break;
             }
         }
        eCurRunState = State_log_in;
        eVirtualKey = _EVENT_TRUE;
        buzzer_power_up_sound();
        return;
   }
error:
  eVirtualKey = _KEY_EXIT_EV_;      //临时，调试  wang！！！！1


}
void oset_shift_join(void)
{
    UINT8 *pinfo;
    UINT8 len;
    UINT8 M = 10;
    UINT8 info[20];
    //UINT8 celen;
    UINT8 _station;
    UINT32  tmp_addr;
    UINT8 Recvjoin;
    UINT8 i;//rg160907
    UINT8 *name;////rg160907
    time_t TM3_t,TM4_t,TM5_t;//rg170110
     double data;//rg170110
   //_shift_loginfo    login_recod;
   // _shift_loginfo    login_recod2;
    UINT8    shift_op_time[6];
    UINT8    ygy[16];//rg160907
    UINT16   ygh;//rg160907
    UINT8    shift_id;
    UINT8    shift_card[15];
    memset(info, 0, sizeof(info));
    ortcc_read_time(shift_op_time);
    ygh=0;//rg160907
     tm3.tm_sec = shift_op_time[5];//rg170110
		tm3.tm_min = shift_op_time[4];//rg170110
		tm3.tm_hour = shift_op_time[3];//rg170110
		tm3.tm_mday = shift_op_time[2];//rg170110
		tm3.tm_mon = shift_op_time[1];//rg170110
		tm3.tm_year = 2000 + shift_op_time[0];//rg170110
 //   memset(ygh,0,2);//rg160907
//    ygh=atoi(Sign_Name);//rg160907
#if 0
    for(i=0;i<16;i++)
    {
	   ygy[i]= atoi(Sign_Name);
	   ygh=ygh+(ygy[i]>>i)*(2*i);
    }
#endif
    if( b_shift_ok == -1 )
    {
         pinfo = ic_operate_info("TN",global_ic_card_info, &len);//2. group class  number
         if(!pinfo) goto error;
         memset(info, 0, sizeof(info));
         memcpy(info, pinfo, len);
         shift_id = atoi(info);
         cur_shiftid = shift_id;///qaz
         while(M--)
         {  if ( 1 == o24lcxxx_write_bytes(_CLASSNO_OFFWORK_ADDR,(UINT8*)&cur_shiftid,1 ) )
              break;
         }
         pinfo = ic_operate_info("CN",global_ic_card_info, &len);// 3. group class card  number
         if(!pinfo) goto error;
         memset(shift_card, 0, sizeof(shift_card));
         memcpy(shift_card, pinfo, len);
         memcpy(cure_shift_card, pinfo, len);
	 memcpy(cure_JQ_card,pinfo, len);//rg170531无卡加气
	  memcpy(cure_yz_card,pinfo, len);//rg170621  插卡先输密码
	 pinfo = ic_operate_info("YGH",global_ic_card_info, &len);//rg160907
	 if(pinfo!=NULL)
	{
         memset(Sign_Name, 0, 3);	//rg160907
	 memcpy(Sign_Name, pinfo, len);		//rg160907
	 }
	   ygh= atoi(Sign_Name);//rg160907
      /*
         _station = (shift_card[0]-0x30)*10+(shift_card[1]-0x30);
         if(_station != Cur_StationNo)
         { olcd_clearsCreen();
            olcm_dispprintf(0,1,"  此卡非本站卡");
            olcm_dispprintf(0,2,"  请拔卡");
            osys_getkey(_KEY_EXIT_EV_, 300);
           sig_err = CARD_STATION_ERROR;
           eVirtualKey = _KEY_LOGIN_ERROE;
             return;
         }*/
                 //////////////////////rg170110/////////////////////////////////////////////////////////////
         Recvjoin = Shift_join(shift_id,(UINT8 * )shift_card,(UINT8 *)shift_op_time,ygh,zhutime); //发送上班信息rg160907 rg170110
		Err_JPTime = 0;
		tm2.tm_sec = zhutime[5];
		tm2.tm_min = zhutime[4];
		tm2.tm_hour = zhutime[3];
		tm2.tm_mday = zhutime[2];
		tm2.tm_mon = zhutime[1];
		tm2.tm_year = 2000 + zhutime[0];
		
		tm1.tm_sec = 0x0;//rg170110
		tm1.tm_min = 0x0;
		tm1.tm_hour = 0x0;
		tm1.tm_mday = 0x1;
		tm1.tm_mon = 0x1;
		tm1.tm_year = 2000 + 17;
		TM3_t = mktimesec(tm1.tm_year,tm1.tm_mon,tm1.tm_mday,tm1.tm_hour,tm1.tm_min,tm1.tm_sec);
		TM4_t = mktimesec(tm2.tm_year,tm2.tm_mon,tm2.tm_mday,tm2.tm_hour,tm2.tm_min,tm2.tm_sec);
		TM5_t = mktimesec(tm3.tm_year,tm3.tm_mon,tm3.tm_mday,tm3.tm_hour,tm3.tm_min,tm3.tm_sec);
		data=TM4_t-TM3_t;
		if((zhutime[5]<60)&&(zhutime[4]<60)&&(zhutime[3]<24)&&(zhutime[2]>0)&&(zhutime[2]<32)&&(zhutime[1]>0)&&(zhutime[1]<13))//rg180621
		{
		if(data <= 0)//判主板时间在2017年后
		{
			Err_ZhuTime = 1;
		}
		else
		{
			Err_ZhuTime = 0;
		}
		}
		data=TM5_t-TM3_t;
		if(data <= 0)//判键盘板时间在2017年后
		{
			Err_JPTime = 1;
		}
		else
		{
			Err_JPTime = 0;
		}
	/////////////////end/////////////////////////////////////////////////////////////////////	
	 switch(Recvjoin)
            {  
              case 0: //成功
                 break;
              case 1: //黑卡;
                 return;
              case 2: //灰卡;
                 return;
              case 3: SOEACTION1(PRO422_ERR,eCurRunState);//通信异常
                 return;
             default:
               break;
            }
  
        b_shift_ok = 1;
   
        buzzer_power_up_sound();
        eVirtualKey = _KEY_LOGIN_SUCCESS;
        return;
   }
error:
  if(cur_keysound)  buzzer_power_up_sound();
     sig_err = CARD_TYPE_ERROR;
    eVirtualKey = _KEY_LOGIN_ERROE;
 //    eVirtualKey = _KEY_LOGIN_SUCCESS;      //临时，调试
}

#if 0
void oset_shift_join(void)
{
    UINT8 *pinfo;
    UINT8 len;
    UINT8 info[20];
    UINT8 celen;
    UINT32  tmp_addr;
    _shift_loginfo    login_recod;
    _shift_loginfo    login_recod2;
   
    memset(&login_recod, 0, sizeof(cur_shift_loginfo));
    memset(info, 0, sizeof(info));
    ortcc_read_time(login_recod.shift_op_time);
    if( b_shift_ok == -1 )
    {
      //   cur_max_recid   = oset_system_get_max_rec_id();  // init里已经获得
         cur_sysparas.p_curflow = cur_max_recid;
          
        //get  the class group  node form card info
        tmp_addr = (cur_max_recid%_SHIFT_SYSINFO_PAGES_)*_SHIFT_SYSINFO_PAGE_SZIE_ +_SHIFT_SYSPARAS_EEP_ADDR_P1;
        o24lcxxx_read_bytes_ex(tmp_addr, (UINT8 *)&cur_rec_sysinfo, sizeof(_rec_shift_info));
        cur_max_shiftid = cur_rec_sysinfo.sig_uid;
        
         //保留当前班组qaz
         pinfo = ic_operate_info("TN",global_ic_card_info, &len);//2. group class  number
         if(!pinfo) goto error;
         memset(info, 0, sizeof(info));
         memcpy(info, pinfo, len);
         login_recod.shift_id = atoi(info);
         cur_shiftid = login_recod.shift_id;///qaz
         
         pinfo = ic_operate_info("CN",global_ic_card_info, &len);// 3. group class card  number
         if(!pinfo) goto error;
         memset(login_recod.shift_card, 0, sizeof(login_recod.shift_card));
         memcpy(login_recod.shift_card, pinfo, len);

        login_recod.shift_op_type = 1; // 4. signal in type
        login_recod.shift_rec_id = cur_max_shiftid + 1;//5. recoder number
        login_recod.shift_s_mount = cur_rec_sysinfo.gun_total;  ;//6.班开始枪累 = 上班结束枪累
        login_recod.shift_e_mount = cur_rec_sysinfo.gun_total;//7.
        login_recod.recoder_num  = cur_max_recid; //8. max record id
        login_recod.shift_gid = cur_sysparas.p_gid;//cur_rec_sysinfo.g_uid;//9.gun id

        //store class group start working infomation in nand flash
        tmp_addr = (cur_max_shiftid)*SHIFT_NANDFLASH_SIZE + SHIFT_NANDFLASH_S_ADDR;
        celen=sizeof(_shift_loginfo);
        onand_wtBuff(tmp_addr, (UINT8*)&login_recod, sizeof(_shift_loginfo));
        delay_ms(1000);
        onand_rdBuff(tmp_addr, (UINT8*)&login_recod2, sizeof(_shift_loginfo) );
        print_shift(login_recod);
        print_shift(login_recod2);
        cur_max_shiftid += 1;
        cur_rec_sysinfo.sig_uid = cur_max_shiftid;

       
       //read the class group in  EEPROM_REC_SYSINFO_PAGE_SZIE_
       // tmp_addr = _REC_SYSINFO_EEP_ADDR + _REC_SYSINFO_PAGE_SZIE_ * login_recod.shift_id;
       // o24lcxxx_read_bytes_ex(tmp_addr, (UINT8 *)&cur_rec_shiftinfo, sizeof(_rec_shift_info));
        cur_rec_sysinfo.g_uid = cur_max_recid;
        //set the shift record for using in the class working
        memcpy(&cur_rec_shiftinfo, &cur_rec_sysinfo, sizeof(_rec_shift_info));
        cur_rec_shiftinfo.c_cash = 0;
        cur_rec_shiftinfo.c_money = 0;
        cur_rec_shiftinfo.c_sum = 0;

        //change the currnt class info for use in system
        memcpy(&cur_shift_loginfo, &login_recod, sizeof(_shift_loginfo));
        b_shift_ok = 1;
      //  Setshiftonce();
        //IDLE_CTRL();
        buzzer_power_up_sound();
        eVirtualKey = _KEY_LOGIN_SUCCESS;
        return;
   }       
error:
  if(cur_keysound)  buzzer_power_up_sound();
   eVirtualKey = _KEY_LOGIN_SUCCESS;      //临时，调试  wang！！！！1
 // eVirtualKey = _KEY_LOGIN_ERROE;
}
#endif
/*
         //memset(&tmp_shift_sysinfo2.shift_rec_id, 0, sizeof(tmp_shift_sysinfo));
        //onand_rdBuff(tmp_addr, (UINT8*)&tmp_shift_sysinfo2.shift_rec_id, sizeof(struct def_shift_SysInfo));
       // oprint_printf("*********************SHANG  BAN 22WRITE********************\r\n");
        //print_shift(tmp_shift_sysinfo2);
 **/

/*_________________________________     下班函数        ________________________________________*/

void osel_offwork()
{   UINT8 *TNfo;
    UINT8 len,offworTn;
    UINT8 Tinfo[4];
    UINT8 passbuf[10];
    UINT8 pass[10];
    UINT8 len1,len2 = 6;
    UINT8  *pinfo;
       while(machine_has_card()!=TRUE)
        {
          // olcd_clearsCreen();
           olcm_dispprintf(0,1,"请插入班组卡下班");
           olcm_dispprintf(0,2,"                ");
           olcm_dispprintf(0,3,"  任意键退出    ");
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
     olcm_dispprintf(0,2,"请稍等。。");
     olng_operate_card_info();
     pinfo = ic_operate_info("CDT",global_ic_card_info, &len1);
     if(pinfo==NULL)
   {
        sig_err = CARD_TYPE_ERROR;
        eVirtualKey = _KEY_LOGIN_ERROE;
        return;
   }
    if(memcmp(pinfo,"40000001",len1) == 0) // class group card   =====
    {

        TNfo = ic_operate_info("TN",global_ic_card_info, &len);//2. group class  number
         memset(Tinfo, 0, sizeof(Tinfo));
         memcpy(Tinfo, TNfo, len);
         offworTn = atoi(Tinfo);

         if(offworTn != ReadTn)
         {         olcd_clearsCreen();
                     olcm_dispprintf(0,1,"    提示    ");
                    olcm_dispprintf(0,2,"该班组暂不能登录");
                    olcm_dispprintf(0,3,"请用%2d组登录",ReadTn);

                    osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_EXIT_EV_;
                      return;   //150525
             
         }

        memset(passbuf, 0, sizeof(passbuf));
        ic_card_get_password(passbuf,&len2);//获得卡密码
       
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"----下    班----");
        olcm_dispprintf(0,2,"请输入卡密码  ");
        olcm_dispprintf(0,3,"密码:  ");
         memset(pass, 0, sizeof(pass));
         if(okeyinput_get_pass(pass, &len1, 6, 3, 3) > 0)
            {   //密码在插入卡时已经获得
               
                 if(len2 == len1)
                      {
                         if(strcmp(pass, passbuf) == 0)
                     //   if((pass[0]==passbuf[0])&&(pass[1]==passbuf[1])&&(pass[2]==passbuf[2])&&(pass[3]==passbuf[3])&&(pass[4]==passbuf[4])&&(pass[5]==passbuf[5])  )
                         {
                          
                              oset_shift_Exit(); //下班
                              return;
                         }
                      }
                   //密码错误
                    olcd_clearsCreen();
                    olcm_dispprintf(1,1,"密码错误");
                    olcm_dispprintf(1,2,"请退出重新下班");
                    osys_getkey(_KEY_NULL_,320);
                    eVirtualKey = _KEY_EXIT_EV_;
                  return;
      
            }
         else //未输入密码（退出键、ENTER）
          // olcd_clearsCreen();
          // olcm_dispprintf(0,1,"----下    班----");
          // olcm_dispprintf(0,2,"没有输入密码");
         //  olcm_dispprintf(0,3,"退出");
          // osys_getkey(_KEY_NULL_,100);
           eVirtualKey = _KEY_EXIT_EV_;

               
    }
    else // if the card isn't the class group card,
    {
       //卡类型错误
        olcd_clearsCreen();
        olcm_dispprintf(1,1,"卡类型错误");
        olcm_dispprintf(1,2,"请退出重新下班");
        osys_getkey(_KEY_NULL_,320);
        eVirtualKey = _KEY_EXIT_EV_;
    }
    return;

    ////////////////////////////////////////
    
}
#if 0
void osel_offwork()
{
    UINT16 offset_id;
    UINT32 tmp_addr;
    UINT8 info[10];
     _shift_loginfo    login_recod2;
    //cur_max_shiftid = oset_system_get_max_shift_id()
    memset(info, 0, sizeof(info));
    if(b_shift_ok == 1 || b_shift_ok == 0)
    {
        olcd_clearsCreen();
        olcm_dispprintf(0,2,"----下    班----");

        //store the off work info to nand flash

        cur_shift_loginfo.shift_rec_id   = cur_max_shiftid + 1;
       // cur_shift_loginfo.shift_gid = cur_rec_shiftinfo.sig_uid;
        cur_shift_loginfo.shift_op_type  = 2;
        cur_shift_loginfo.shift_e_mount = cur_rec_shiftinfo.gun_total;
        cur_shift_loginfo.shift_cash     += cur_shift_loginfo.shift_cash;
        cur_shift_loginfo.recoder_num = cur_max_recid;
        ortcc_read_time(cur_shift_loginfo.shift_op_time);

        tmp_addr = SHIFT_NANDFLASH_S_ADDR+cur_max_shiftid*SHIFT_NANDFLASH_SIZE;
 //       onand_wtBuff(tmp_addr, (UINT8*)&cur_shift_loginfo, sizeof(_shift_loginfo));
               onand_wtBuff(tmp_addr, (UINT8*)&cur_shift_loginfo,SHIFT_NANDFLASH_SIZE);
        onand_rdBuff(tmp_addr, (UINT8*)&login_recod2, sizeof(_shift_loginfo));

         oprint_printf("----------------------long  OFF------------------\r\n");
        print_shift(cur_shift_loginfo);
        print_shift(login_recod2);
        cur_max_shiftid += 1;


       cur_rec_shiftinfo.sig_uid = cur_max_shiftid;
       tmp_addr = ((cur_max_recid%_SHIFT_SYSINFO_PAGES_)*_SHIFT_SYSINFO_PAGE_SZIE_) + _SHIFT_SYSPARAS_EEP_ADDR_P1;
       o24lcxxx_write_bytes_ex(tmp_addr,(UINT8*)&cur_rec_shiftinfo,sizeof(_rec_shift_info)); //
       //show_sys_recod();
#if 0
       // store the total number of system
        cur_rec_sysinfo.set_uid = cur_rec_shiftinfo.set_uid;
        cur_rec_sysinfo.g_uid = cur_rec_shiftinfo.g_uid;
        cur_rec_sysinfo.sig_uid =  cur_rec_sysinfo.sig_uid;
        cur_rec_sysinfo.gun_total +=  cur_rec_sysinfo.c_sum;
        cur_rec_sysinfo.shift_cash +=  cur_rec_sysinfo.shift_cash;
        cur_rec_sysinfo.g_sum +=  cur_rec_sysinfo.c_sum;
        cur_rec_sysinfo.g_money +=  cur_rec_sysinfo.c_money;
        cur_rec_sysinfo.g_total +=  cur_rec_sysinfo.g_total;
        o24lcxxx_write_bytes_ex(_REC_SYSPARAS_EEP_ADDR_P0, (UINT8*)&cur_rec_sysinfo, sizeof(_rec_shift_info));
#endif
        ///打印记录
        oprint_operate_shift();
     //   Setshiftonce();
        olcm_dispprintf(3,4,"下班成功");
        b_shift_ok = -1;
        eVirtualKey = _EVENT_TRUE;

        //osys_getkey(_KEY_EXIT_EV_,1000);  //_KEY_VIRTUAL_DENGLU_EV_
         return;
   }
}
#endif
void show_time_over()//rg170701
{
     olcd_clearsCreen();
     olcm_dispprintf(0,2,"  替班错误      ");
     olcm_dispprintf(0,3,"请断电检查通讯线");
}