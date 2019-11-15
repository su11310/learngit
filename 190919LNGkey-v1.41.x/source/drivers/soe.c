/*
 * File:  soe.c
 * Author: wangzw
 *include soe  and  sysruntime
 * Created on 2014_01_16
 */
#include "../includes/global_def.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

BOOL Save_Qx_Runtime(UINT32 new_runtime)//RG160726
 {    
      UINT32 readtime;
      UINT32 runtime;
      UINT8 K = 10;
      runtime = new_runtime;
     while(K)
      {  K--;
         if( 4==o24lcxxx_write_bytes_ex(qxsz_min_addr,(UINT8*)&runtime,4))
          {   delay_ms(100);
              o24lcxxx_read_bytes_ex(qxsz_min_addr, (UINT8*)&readtime, 4);
          
              if(readtime ==runtime)
                {
                return 1;
                }
             delay_ms(10);
          }

     }//end of while
      return 0;
 }

/*------------------------------------------------------------------------------
 * SOE事件响应
------------------------------------------------------------------------------*/
 BOOL Sava_Sys_Runtime(UINT32 new_runtime)
 {    
      UINT32 readtime;
      UINT32 runtime;
      UINT8 K = 10;
      runtime = new_runtime;
     while(K)
      {  K--;
         if( 4==o24lcxxx_write_bytes_ex(_LNG_RUNTIME_ADDR,(UINT8*)&runtime,4))
          {   delay_ms(100);
              o24lcxxx_read_bytes_ex(_LNG_RUNTIME_ADDR, (UINT8*)&readtime, 4);
          
              if(readtime ==runtime)
                {
                return 1;
                }
             delay_ms(10);
          }

     }//end of while
      return 0;
 }
  UINT32 Get_Qx_Runtime(void)
{
    UINT32     runtime;
   o24lcxxx_read_bytes_ex(qxsz_min_addr, (UINT8*)&runtime, 4);
   return runtime;
}
/*获得系统运行时间*/
 UINT32 Get_Sys_Runtime(void)
{
    UINT32     runtime;
   o24lcxxx_read_bytes_ex(_LNG_RUNTIME_ADDR, (UINT8*)&runtime, 4);
   return runtime;
}

 void ClearNameStation(void)
 {

 Clr_info_xs();

 }

void ClearSysRuntime(void)
{     UINT32 time=0;
      UINT32 runtime;
      UINT8 K =10;
    while(K--)
    {
        if(4 == o24lcxxx_write_bytes_ex(_LNG_RUNTIME_ADDR,(UINT8*)&time,4))
        {   delay_ms(100);
           o24lcxxx_read_bytes_ex(_LNG_RUNTIME_ADDR, (UINT8*)&runtime, 4);
           if(runtime ==time)
               break;
        }
    }
}
BOOL SOEACTION2(UINT8 *num,UINT8 err_cont,UINT8 cur_state)
{
#if 0
    UINT8 err[10],i;
    memset(err,0,10);
    memcpy(err,num,10);
    if(err_cont>0)
    {
        olcd_clearsCreen();
        olcm_dispprintf(0,1,"  系统异常代码");
      for(i=0;i<err_cont;i++)
      {
        AddSOE(err[err_cont]);
        olcm_dispprintf(0+2*i,2+(2*i)/8,"%d",err[i]);
      }
    }
    osys_getkey(_KEY_EXIT_EV_,320);
    keyv = _KEY_EXIT_EV_;
    b_keyv = TRUE;
    eCurRunState = cur_state;
    return TRUE;
#endif
}
BOOL SOEACTION1(UINT8 err_type,UINT8 cur_state)
{   if(err_type != 62)//rg170807
	AddSOE(err_type);
    olcd_clearsCreen();

    olcm_dispprintf(0,1,"  系统异常");
    olcm_dispprintf(0,2,"异常代码: %d",err_type);

    switch(err_type)
    {
        case 0:
	olcm_dispprintf(1,3,"液相流量计");	
	olcm_dispprintf(2,4,"通信异常");break;
	case 1:
	olcm_dispprintf(0,3,"液相流量计");	
        olcm_dispprintf(0,4,"参数写入失败");break;
	
        case 2:
	olcm_dispprintf(1,3,"未检测到");	
        olcm_dispprintf(1,4,"液相流量计");break;	
        case 3:
	olcm_dispprintf(1,3,"液相流量计");	
	olcm_dispprintf(1,4,"地址错误");break;
        case 4:
	olcm_dispprintf(0,3,"液相流量计");	
        olcm_dispprintf(0,4,"数据校验错误");break;
        case 5:
	olcm_dispprintf(1,3,"液相流量计");	
        olcm_dispprintf(1,4,"读数错误");break;
        
       case 10:
	olcm_dispprintf(1,3,"气相流量计");	
	olcm_dispprintf(1,4,"通信异常");break;       
       case 11:
	olcm_dispprintf(0,3,"气相流量计");	
        olcm_dispprintf(0,4,"参数写入失败");break;       
       case 12:
	olcm_dispprintf(1,3,"未检测到");	
        olcm_dispprintf(1,4,"气相流量计");break;       
       case 13:
	 olcm_dispprintf(1,3,"液相流量计");	
	olcm_dispprintf(1,4,"地址错误");break;      
       case 14:
	olcm_dispprintf(0,3,"液相流量计");	
        olcm_dispprintf(0,4,"数据校验错误");break;       
       case 15:
	olcm_dispprintf(1,3,"气相流量计");       
       olcm_dispprintf(1,4,"通讯超时");break;
       case 16://rg170330 
//	olcm_dispprintf(1,3,"回气量异常");  
//	olcm_dispprintf(0,4,"                ");
	break;
	case 17://rg170330 
//	olcm_dispprintf(1,3,"加气量为负");      
//       olcm_dispprintf(0,4,"                ");
	break;
       case 20:
       case 21:
        olcm_dispprintf(0,3,"主板EE错误");break;
       case 30:
	olcm_dispprintf(0,3,"读卡器通信错误");break;       
       case 31:
        olcm_dispprintf(0,3,"读卡错误");break;
      case 40:
       olcm_dispprintf(0,3,"压力传感器异常");break;
       case 41:
	olcm_dispprintf(0,3,"超过最大流速");break;      
	case 42:
	olcm_dispprintf(0,3,"卡类型卡余不匹配");break;  
       case 50:
	olcm_dispprintf(0,3,"板间通讯错误");break;       
       case 51:
	olcm_dispprintf(1,3,"加气中键盘板");       
	olcm_dispprintf(0,4,"到主板通信错误");break;        
       case 52:
	olcm_dispprintf(1,3,"加气中主板到");       
       olcm_dispprintf(0,4,"键盘板通信错误");break;
       case 53:
       olcm_dispprintf(0,3,"后台通信异常");break;
       
       case 58:     
       olcm_dispprintf(0,3,"加气过程中判断");
       olcm_dispprintf(0,4,"灰锁状态错误");break;
        case 60://rg170807
///	olcm_dispprintf(1,2,"NAND存储");      
       olcm_dispprintf(0,3,"NAND错误超次数");
       olcm_dispprintf(0,4,"  停止加气    ");
       break;
       case 61:
       olcm_dispprintf(0,3,"存储密钥错误");break;
       case 62:
       olcm_dispprintf(0,3,"  NAND存储错误");      //rg170807
       olcm_dispprintf(0,4,"  请尽快更换  ");break;
      case 70:
	olcm_dispprintf(0,3,"时钟读出错误");break;      
      case 71:
	olcm_dispprintf(0,3,"时钟写入错误");break;      
      case 72:
       olcm_dispprintf(0,3,"时间异常错误");break;
      case 73:
	 olcm_dispprintf(1,3,"主控板版本号");      
       olcm_dispprintf(1,4,"获取错误");break; 
      case 80:
       olcm_dispprintf(0,3,"流水号不连续");break;
       case 90:
       olcm_dispprintf(0,3,"写卡错误");break;
       case 91:
       olcm_dispprintf(0,3,"读卡错误");break;
       case 93:
       olcm_dispprintf(0,3,"卡置灰失败");
       olcm_dispprintf(0,4,"请断电检查");
       break;
         case 94://rg170925
       olcm_dispprintf(0,3,"非初始卡未能扣款");//rg170925
       olcm_dispprintf(0,4,"请后台处理");//rg170925
       break;
      default:
        olcm_dispprintf(0,3,"系统异常");break;
          break;

    }
    if((err_type ==53) ||(err_type ==72)||(err_type ==80)||(err_type ==50) )
    osys_getkey(_KEY_EXIT_EV_,320);
    else if(err_type ==5)
     osys_getkey(_KEY_EXIT_EV_,10);
        else if(err_type ==94)//rg170925
       osys_getkey(_KEY_EXIT_EV_,10);//rg170925
    else
    {olcm_dispprintf(0,4,"  按更改键退出  ");
       osys_getkey(_KEY_EXIT_EV_,500);}
    if(cur_state !=State_LngOperate)
    {  keyv = _KEY_EXIT_EV_;
       b_keyv = TRUE;
    }
    eCurRunState = cur_state;
}



BOOL SOEACTION(UINT8 err_type,UINT8 cur_state, pFunc SpecFunc)
{
    olcd_clearsCreen();
    olcm_dispprintf(0,1,"  系统异常");
    olcm_dispprintf(0,2,"异常代码: %d",err_type);
    switch(err_type)
    {
      case 1:
        olcm_dispprintf(0,3,"压力传感器异常");break;
      case 2:
        olcm_dispprintf(0,3,"板通信异常");break;
      default:
        olcm_dispprintf(0,3,"系统异常");break;
          break;

    }
    AddSOE(err_type);
    osys_getkey(_KEY_NULL_,300);
    eCurRunState = cur_state;
    SpecFunc();
}
/*------------------------------------------------------------------------------
 * SOE记录增加
------------------------------------------------------------------------------*/
 BOOL AddSOE(UINT8 ERR_TYPR)//rg180613
 {    
    UINT16 id ;
    UINT16_VAL Chan_Date;
    UINT8 SOEbuff[9];
    UINT8 Etime[6];
    UINT8 rdtime[6];
    UINT8 err_type;
    UINT8 Rerr_type;
    UINT8 K = 10;
      err_type = ERR_TYPR;
      cur_max_soe += 1;
      id = cur_max_soe;
      ortcc_read_time(Etime);
//      if((id >1000) &&(id <1100))
//       { SOE_DELEALL();//SOE清空
//         return;
//        }
     
    while(K)
      {  K--;
         if( 6 ==o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR+(id%500-1)*SOE_SIZE,(UINT8*)Etime,6))
          {   delay_ms(100);
           o24lcxxx_read_bytes_ex(SOE_SAVE_ADDR +(id%500-1)*SOE_SIZE, (UINT8*)rdtime, 6);
            // if(strcmp(rdtime, Etime) == 0)
           if((rdtime[0]==Etime[0])&&(rdtime[1]==Etime[1])&&(rdtime[2]==Etime[2])&&(rdtime[3]==Etime[3])&&(rdtime[4]==Etime[4])&&(rdtime[5]==Etime[5]))
                {
                 break;
                }
           delay_ms(10);
         }

     }
      K=10;
   while(K)
      {  K--;
      if(TRUE ==  o24lcxxx_write((SOE_SAVE_ADDR+(id%500-1)*SOE_SIZE + 6),err_type))
        {   delay_ms(100);
           o24lcxxx_read_bytes_ex(SOE_SAVE_ADDR +(id%500-1)*SOE_SIZE +6, (UINT8*)&Rerr_type, 1);
             if( err_type == Rerr_type)
               {
                 delay_ms(100);
                o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR_MAX,(UINT8*)&id,2 ); //存SOE最大数
                delay_ms(100);
                 break;
                }
           delay_ms(10);
         }

     }
    
      // ss190912  传输异常代码到主控板
//     if(err_type != 0x32)    //  屏蔽 50 异常代码 
     {
         memcpy(SOEbuff,Etime,6);
        memcpy(&SOEbuff[6],&err_type,1);
        memset(&SOEbuff[7],((id>>8)&0xff),1);
        memset(&SOEbuff[8],(id&0xff),1);
        Send_SOE_State(SOEbuff);
     }
 }


/*------------------------------------------------------------------------------
 * 获得SOE总数
------------------------------------------------------------------------------*/

 UINT16 Get_max_soe_id(void)
{
    UINT16     _rec_maxSOE;
    UINT16         addr;
    UINT16         maxid;
    addr = SOE_SAVE_ADDR_MAX;//////

    o24lcxxx_read_bytes_ex(addr, (UINT8*)&_rec_maxSOE, 2);

    maxid = _rec_maxSOE ;

    return maxid;
}
 
 UINT32 Get_max_reset_id(void)
{
    UINT32          _rec_maxReset;
    UINT16         addr;
    UINT32         maxid;
    addr = KeyReset_RECORD_MAX;//////

    o24lcxxx_read_bytes_ex(addr, (UINT8*)&_rec_maxReset,4);

    maxid = _rec_maxReset ;

    return maxid;
}
void SOE_DELEALL(void)
{     UINT16 i,idmax,idreadmax;
      UINT8 id[SOE_SIZE];
      UINT8  K=10;
      memset(id,0x00,SOE_SIZE);
      for(i=0;i<SOEMAX_SIZE;i++)
       {
           o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR+(i*SOE_SIZE),(UINT8*)&id,SOE_SIZE ); //写0

       }

      delay_ms(200);
      cur_max_soe = 0;
      idmax = cur_max_soe;
   while(K)
    {  K--;
    if(2 == o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR_MAX,(UINT8*)&idmax,2 )) //存SOE新最大数
    {
           delay_ms(100);
           o24lcxxx_read_bytes_ex(SOE_SAVE_ADDR_MAX, (UINT8*)&idreadmax, 2);
            if(idreadmax ==idmax)
            { break;
            }
      }
   }
}

void oqry_soerec(void)
{
        UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;


        id = maxid = cur_max_soe;//cur_sysinfo.g_uid;
  //      if((id == 0)||(id > 1000) ){
	if(id == 0){	//RG180613
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"无SOE 事件记录! ");
            osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_VIRTUAL_EV_;

            return;
        }
        Qry_Soerec_Disp(id);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

          //  if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
         //   if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            if(_KEY_UP_EV_ == keyv)
            {
		    if((cur_max_soe-id)<499)//rg180613 在一千以前地址重复不显示
		    {
			if(--id == 0){
			    id = 1;
			    continue;
			}
			  Qry_Soerec_Disp(id);
		    }
            }
            if(_KEY_SW_EV_ == keyv)
            {
                if(++id > maxid){
                    id = maxid;
                    continue;
                }
                 Qry_Soerec_Disp(id);
            }
      //      if(_KEY_ENTER_EV_ == keyv)
       //     {
       //         Qry_Soerec_Disp(id);
             
       //         continue;
       //     }
       //     Qry_Soerec_Disp(id);
          
        }
        eVirtualKey = _KEY_VIRTUAL_EV_;

}

void oqry_reset_info(void)//rg160622
{
          UINT32 id ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT32 maxid0,curid;
        UINT8  keyv = 0;
        BOOL   bdisp = FALSE;
//          float dj;float je;float ql;UINT32 *recg;
        UINT8 edati[6],cn[10];
        UINT8 no;
        id=0;
            olcd_clearsCreen();
      olcm_dispprintf(0,1,"正在与主板通信"); 
       if(TRUE != qty_get_resetinfo(id,&maxid0,&curid,edati,&no))
       {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
       id = maxid0 ;//init里获得
        if( id == 0 ){
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"无复位记录！");
             osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_VIRTUAL_EV_;

            return;
        }
        oqry_reset_disp(id, TRUE);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

          //  if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
        //    if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            else if(_KEY_UP_EV_ == keyv)
            {
                if(--id == 0){
                    id = 1;
                    continue;
                }
                oqry_reset_disp(id, TRUE);
            }
            else  if(_KEY_SW_EV_ == keyv)
            {
                if(++id > maxid0){
                    id = maxid0;
                    continue;
                }
             oqry_reset_disp(id, TRUE);
            }
          }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
void oqry_key_reset(void)//rg160623
{
        UINT32 keyid ;//= cur_sysinfo.g_uid;
        UINT32 maxid;// = cur_sysinfo.g_uid;
        UINT8  keyv = 0;
        UINT8 cont=0;
        BOOL   bdisp = FALSE;

        if(cur_max_reset >= KeyReset_RECORD_Len)
        {
            cont=KeyReset_RECORD_Len;
        }
        else
        {
           cont= cur_max_reset;
        }

        keyid =cur_max_reset;
        maxid = cur_max_reset;
        if((keyid == 0)){
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"无复位事件记录! ");
            osys_getkey(_KEY_NULL_, 300);
            eVirtualKey = _KEY_VIRTUAL_EV_;

            return;
        }
        Qry_Resetrec_Disp(keyid);
        while(1)
        {
            keyv = ostatemachine_getkey();
            b_keyv = FALSE;
            bdisp = FALSE;

          //  if(0 == keyv) continue;
            if(_KEY_EXIT_EV_ == keyv) break;
         //   if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
            if(_KEY_UP_EV_ == keyv)
            {
                if(cur_max_reset <= KeyReset_RECORD_Len)
                {
                    if(--keyid == 0)
                    {
                    keyid = 1;
                    continue;
                    }
                }
                else
                {
                   if(--keyid < cur_max_reset-KeyReset_RECORD_Len+1)
                    {
                    keyid = cur_max_reset-KeyReset_RECORD_Len+1;
                    continue;
                    }  
                }
                  Qry_Resetrec_Disp(keyid);
            }
            if(_KEY_SW_EV_ == keyv)
            {
                if(++keyid > cur_max_reset){
                    keyid = cur_max_reset;
                    continue;
                }
                 Qry_Resetrec_Disp(keyid);
            }
        }
        eVirtualKey = _KEY_VIRTUAL_EV_;
}
//
void Qry_Soerec_Disp(UINT16 id)   //
{
  UINT8 Etime[6];
      UINT8 err_type;

    o24lcxxx_read_bytes_ex(SOE_SAVE_ADDR +(id%500-1)*SOE_SIZE, (UINT8*)Etime, 6);//rg180613
    delay_ms(100);
    o24lcxxx_read_bytes_ex(SOE_SAVE_ADDR +(id%500-1)*SOE_SIZE +6, (UINT8*)&err_type, 1);//rg180613

            olcd_clearsCreen();
            olcm_dispprintf(0,1,"序号：%d",id);
            if((Etime[1]<13)|| (Etime[2]<32)  )
            {
		    switch(err_type)//rg180613
		    {
				case Para_md :
			    olcm_dispprintf(0,2,"操作：修改密度");
			    break;
				case Para_lsh:
			    olcm_dispprintf(0,2,"操作：修改流水号");
			    break;
			    case Para_tjyl:
			    olcm_dispprintf(0,2,"操作：改停机压力");
			    break;
			    default:
				 olcm_dispprintf(0,2,"异常代码:%d",err_type);
				 break;
		    }
              /*  switch(err_type)
                  {
                      case 1:
                        olcm_dispprintf(0,3,"流量计通信异常");break;
                      case 2:
                        olcm_dispprintf(0,3,"电磁阀动作异常");break;
                      default:
                        olcm_dispprintf(0,3,"系统异常");break;
                          break;

                    }*/

              olcm_dispprintf(0,3,"时间:%02d-%02d-%02d", Etime[0],Etime[1], Etime[2]);
              olcm_dispprintf(0,4,"     %02d:%02d:%02d", Etime[3], Etime[4], Etime[5]);
            }
            else
            {
                olcm_dispprintf(0,2,"无该异常信息记录");
            }
}
void Qry_Resetrec_Disp(UINT32 keyid)   //rg160623
{
     UINT8 Etime[6];
      UINT8 err_type;
      RESETFAULTMSG ResetFaultMsg;
    o24lcxxx_read_bytes_ex(KeyReset_RECORD_Addr +((keyid-1)% 30)*KeyReset_RECORD_Size, (UINT8*)&ResetFaultMsg.FaultCount, KeyReset_RECORD_Size);
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"序号：%d",keyid);
            if((Etime[1]<13)|| (Etime[2]<32)  )
            {
              switch(ResetFaultMsg.FaultReason)
                   {
                       case 1:olcm_dispprintf(0,2,"上电复位");
                               break;
                        case 2:olcm_dispprintf(0,2,"欠压复位");
                               break;
                        case 3:olcm_dispprintf(0,2,"外部引脚复位");
                               break;
                        case 4:olcm_dispprintf(0,2,"软件复位");
                               break;
                        case 5:olcm_dispprintf(0,2,"配置不匹配复位");
                               break;
                        case 6:olcm_dispprintf(0,2,"看门狗复位");
                               break;  
                        default:
                               break;       
                   }

                olcm_dispprintf(0,3,"时间:%02d-%02d-%02d", ResetFaultMsg.DateTime[0],ResetFaultMsg.DateTime[1], ResetFaultMsg.DateTime[2]);
                olcm_dispprintf(0,4,"    %02d:%02d:%02d", ResetFaultMsg.DateTime[3], ResetFaultMsg.DateTime[4], ResetFaultMsg.DateTime[5]);
                olcm_dispprintf(6,4,"↓↑");
            }
            else
            {
                olcm_dispprintf(0,2,"无复位信息记录");
            }
      
      
}
void car_disp(UINT8 dj,UINT8 tp,UINT8 *jy,UINT8 *qy,float zk,UINT8 q1,UINT8 q2,UINT8 q3,UINT8 q4,UINT8 xf,UINT8 *cp,UINT8 *pjyx)//150813
{
  UINT8 rdkey;
   UINT8 jye[10],qye[10],cph[16],pjy[4];
   float jin,jinh,qi,qih;
double ti;
  UINT8  infoxs[][8]={        "无效卡",
                              "班组卡",
                              "公司卡",
                              "私车卡",
			      "公司子",
				"公司母",
                                    };
  memset(jye,0x00,10);
  memset(qye,0x00,10);
  memcpy(jye,jy,10);
  memcpy(qye,qy,10);
  jin=(float)atof(jye);
  jinh=fabs(jin);
  qi=(float)atof(qye);
  qih=fabs(qi);
  memset(cph,0x00,16);
  memcpy(cph,cp,sizeof(cph));
  memset(pjy,0x00,4);
  memcpy(pjy,pjyx,4);
                                            if(Get_pr(dj)==0)
                                  {
                                               while(1)
                                      {
                                       olcd_clearsCreen();
                                   olcm_dispprintf(0,1,"错误：单价%02d为零",dj);
                                   olcm_dispprintf(0,2,"用此卡无法加气!");
                                      olcm_dispprintf(0,3,"请重新设置!");
                                      olcm_dispprintf(0,4,"按更改键退出!");
                                       delay_ms(8000);
                                         rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(8000);
                                     olcd_clearsCreen();
                                 olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));

                                      olcm_dispprintf(4,1,"单价%d",dj);
                                      if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"金余：");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"气余：");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((cph[0]==0)&&(cph[1]==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"折扣率：%06.02f％",zk);
                                       olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"折扣率：% 05.02f％",zk);
                                        olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"车牌：");
                                      olcd_dispstr(3,4,cph,strlen(cph));
                                      }
                                       
                                  delay_ms(8000);
                                       delay_ms(8000);
                                       rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                      }
                                               _b_cz_card=TRUE;
                                                eCurRunState = State_MainUI;
                                                eVirtualKey = _KEY_EXIT_EV_;
                                               return;
                                          }
                                            else if((pjy[0]!=0x00)&&(pjy[1]!=0x00))
                                            {     if(Get_Gp_Time(pjy)<1800)
                                            {
                                                 while(1)
                                      {
                                       olcd_clearsCreen();
                                   olcm_dispprintf(0,1,"错误：钢瓶超期！",dj);
                                   olcm_dispprintf(0,2,"用此卡无法加气!");
                                      olcm_dispprintf(0,3,"请换卡!");
                                      olcm_dispprintf(0,4,"按更改键退出!");
                                       delay_ms(8000);
                                         rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(8000);
                                     olcd_clearsCreen();
                                 olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));

                                      olcm_dispprintf(4,1,"单价%d",dj);
                                      if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"金余：");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"气余：");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((cph[0]==0)&&(cph[1]==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"折扣率：%06.02f％",zk);
                                       olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"折扣率：% 05.02f％",zk);
                                        olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"车牌：");
                                      olcd_dispstr(3,4,cph,strlen(cph));
                                      }

                                  delay_ms(8000);
                                       delay_ms(8000);
                                       rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                      }
                                               _b_cz_card=TRUE;
                                                eCurRunState = State_MainUI;
                                                eVirtualKey = _KEY_EXIT_EV_;
                                               return;
                                            }
                                            }
                                          else
                                          {
                                             olcd_clearsCreen();
                                      olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));
                                      olcm_dispprintf(4,1,"单价%d",dj);
                                       if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"金余：");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"气余：");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((*cp==0)&&(*(cp+1)==0)&&(*(cp+2)==0)&&(*(cp+3)==0))
                                      {
                                       if(zk==100)
                                       {olcm_dispprintf(0,3,"折扣率：%06.02f％",zk);
                                       olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"折扣率：% 05.02f％",zk);
                                        olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                        }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                     olcm_dispprintf(0,4,"车牌：");
                                      olcd_dispstr(3,4,cph,strlen(cph));
                                      }
                                        rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey)
                                   { _b_cz_card=TRUE;
                                    return;}
                                          }
  //                                  if(((fabs(jin))>=900000||(fabs(qi))>=900000)&&(tp==1))
                                      if(((jinh>=900000)||(qih>=900000))&&(tp==1))
                                      {
                                       while(1)
                                      {
                                       olcd_clearsCreen();
                                   olcm_dispprintf(0,1,"提示：卡余超限");
                                   olcm_dispprintf(0,2,"请尽快结算!");
                                      olcm_dispprintf(0,3,"否则无法加气！ ");
                                      olcm_dispprintf(0,4,"按更改键退出!");
                                       delay_ms(8000);
                                         rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(8000);
                                     olcd_clearsCreen();
                                    olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));
                                      olcm_dispprintf(4,1,"单价%d",dj);
                                       if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"金余：");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"气余：");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((*cp==0)&&(*(cp+1)==0)&&(*(cp+2)==0)&&(*(cp+3)==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"折扣率：%06.02f％",zk);
                                       olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"折扣率：% 05.02f％",zk);
                                        olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"车牌：");
                                      olcd_dispstr(3,4,cph,strlen(cph));
                                      }
                                  delay_ms(8000);
                                       delay_ms(8000);
                                       rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                      }
                                               _b_cz_card=TRUE;
                                                eCurRunState = State_MainUI;
                                                eVirtualKey = _KEY_EXIT_EV_;
                                               return;
                                      }
                                      else
                                      {
                                         olcd_clearsCreen();
                                      olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));
                                      olcm_dispprintf(4,1,"单价%d",dj);
                                       if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"金余：");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"气余：");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((*cp==0)&&(*(cp+1)==0)&&(*(cp+2)==0)&&(*(cp+3)==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"折扣率：%06.02f％",zk);
                                       olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"折扣率：% 05.02f％",zk);
                                        olcm_dispprintf(0,4,"有效期：%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f％%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"车牌：");
                                      olcd_dispstr(3,4,cph,strlen(cph));
                                      }
                                        rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey)
                                   { _b_cz_card=TRUE;
                                    return;}
                                      }
}