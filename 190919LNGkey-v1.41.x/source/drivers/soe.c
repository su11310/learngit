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
 * SOE�¼���Ӧ
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
/*���ϵͳ����ʱ��*/
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
        olcm_dispprintf(0,1,"  ϵͳ�쳣����");
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

    olcm_dispprintf(0,1,"  ϵͳ�쳣");
    olcm_dispprintf(0,2,"�쳣����: %d",err_type);

    switch(err_type)
    {
        case 0:
	olcm_dispprintf(1,3,"Һ��������");	
	olcm_dispprintf(2,4,"ͨ���쳣");break;
	case 1:
	olcm_dispprintf(0,3,"Һ��������");	
        olcm_dispprintf(0,4,"����д��ʧ��");break;
	
        case 2:
	olcm_dispprintf(1,3,"δ��⵽");	
        olcm_dispprintf(1,4,"Һ��������");break;	
        case 3:
	olcm_dispprintf(1,3,"Һ��������");	
	olcm_dispprintf(1,4,"��ַ����");break;
        case 4:
	olcm_dispprintf(0,3,"Һ��������");	
        olcm_dispprintf(0,4,"����У�����");break;
        case 5:
	olcm_dispprintf(1,3,"Һ��������");	
        olcm_dispprintf(1,4,"��������");break;
        
       case 10:
	olcm_dispprintf(1,3,"����������");	
	olcm_dispprintf(1,4,"ͨ���쳣");break;       
       case 11:
	olcm_dispprintf(0,3,"����������");	
        olcm_dispprintf(0,4,"����д��ʧ��");break;       
       case 12:
	olcm_dispprintf(1,3,"δ��⵽");	
        olcm_dispprintf(1,4,"����������");break;       
       case 13:
	 olcm_dispprintf(1,3,"Һ��������");	
	olcm_dispprintf(1,4,"��ַ����");break;      
       case 14:
	olcm_dispprintf(0,3,"Һ��������");	
        olcm_dispprintf(0,4,"����У�����");break;       
       case 15:
	olcm_dispprintf(1,3,"����������");       
       olcm_dispprintf(1,4,"ͨѶ��ʱ");break;
       case 16://rg170330 
//	olcm_dispprintf(1,3,"�������쳣");  
//	olcm_dispprintf(0,4,"                ");
	break;
	case 17://rg170330 
//	olcm_dispprintf(1,3,"������Ϊ��");      
//       olcm_dispprintf(0,4,"                ");
	break;
       case 20:
       case 21:
        olcm_dispprintf(0,3,"����EE����");break;
       case 30:
	olcm_dispprintf(0,3,"������ͨ�Ŵ���");break;       
       case 31:
        olcm_dispprintf(0,3,"��������");break;
      case 40:
       olcm_dispprintf(0,3,"ѹ���������쳣");break;
       case 41:
	olcm_dispprintf(0,3,"�����������");break;      
	case 42:
	olcm_dispprintf(0,3,"�����Ϳ��಻ƥ��");break;  
       case 50:
	olcm_dispprintf(0,3,"���ͨѶ����");break;       
       case 51:
	olcm_dispprintf(1,3,"�����м��̰�");       
	olcm_dispprintf(0,4,"������ͨ�Ŵ���");break;        
       case 52:
	olcm_dispprintf(1,3,"���������嵽");       
       olcm_dispprintf(0,4,"���̰�ͨ�Ŵ���");break;
       case 53:
       olcm_dispprintf(0,3,"��̨ͨ���쳣");break;
       
       case 58:     
       olcm_dispprintf(0,3,"�����������ж�");
       olcm_dispprintf(0,4,"����״̬����");break;
        case 60://rg170807
///	olcm_dispprintf(1,2,"NAND�洢");      
       olcm_dispprintf(0,3,"NAND���󳬴���");
       olcm_dispprintf(0,4,"  ֹͣ����    ");
       break;
       case 61:
       olcm_dispprintf(0,3,"�洢��Կ����");break;
       case 62:
       olcm_dispprintf(0,3,"  NAND�洢����");      //rg170807
       olcm_dispprintf(0,4,"  �뾡�����  ");break;
      case 70:
	olcm_dispprintf(0,3,"ʱ�Ӷ�������");break;      
      case 71:
	olcm_dispprintf(0,3,"ʱ��д�����");break;      
      case 72:
       olcm_dispprintf(0,3,"ʱ���쳣����");break;
      case 73:
	 olcm_dispprintf(1,3,"���ذ�汾��");      
       olcm_dispprintf(1,4,"��ȡ����");break; 
      case 80:
       olcm_dispprintf(0,3,"��ˮ�Ų�����");break;
       case 90:
       olcm_dispprintf(0,3,"д������");break;
       case 91:
       olcm_dispprintf(0,3,"��������");break;
       case 93:
       olcm_dispprintf(0,3,"���û�ʧ��");
       olcm_dispprintf(0,4,"��ϵ���");
       break;
         case 94://rg170925
       olcm_dispprintf(0,3,"�ǳ�ʼ��δ�ܿۿ�");//rg170925
       olcm_dispprintf(0,4,"���̨����");//rg170925
       break;
      default:
        olcm_dispprintf(0,3,"ϵͳ�쳣");break;
          break;

    }
    if((err_type ==53) ||(err_type ==72)||(err_type ==80)||(err_type ==50) )
    osys_getkey(_KEY_EXIT_EV_,320);
    else if(err_type ==5)
     osys_getkey(_KEY_EXIT_EV_,10);
        else if(err_type ==94)//rg170925
       osys_getkey(_KEY_EXIT_EV_,10);//rg170925
    else
    {olcm_dispprintf(0,4,"  �����ļ��˳�  ");
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
    olcm_dispprintf(0,1,"  ϵͳ�쳣");
    olcm_dispprintf(0,2,"�쳣����: %d",err_type);
    switch(err_type)
    {
      case 1:
        olcm_dispprintf(0,3,"ѹ���������쳣");break;
      case 2:
        olcm_dispprintf(0,3,"��ͨ���쳣");break;
      default:
        olcm_dispprintf(0,3,"ϵͳ�쳣");break;
          break;

    }
    AddSOE(err_type);
    osys_getkey(_KEY_NULL_,300);
    eCurRunState = cur_state;
    SpecFunc();
}
/*------------------------------------------------------------------------------
 * SOE��¼����
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
//       { SOE_DELEALL();//SOE���
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
                o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR_MAX,(UINT8*)&id,2 ); //��SOE�����
                delay_ms(100);
                 break;
                }
           delay_ms(10);
         }

     }
    
      // ss190912  �����쳣���뵽���ذ�
//     if(err_type != 0x32)    //  ���� 50 �쳣���� 
     {
         memcpy(SOEbuff,Etime,6);
        memcpy(&SOEbuff[6],&err_type,1);
        memset(&SOEbuff[7],((id>>8)&0xff),1);
        memset(&SOEbuff[8],(id&0xff),1);
        Send_SOE_State(SOEbuff);
     }
 }


/*------------------------------------------------------------------------------
 * ���SOE����
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
           o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR+(i*SOE_SIZE),(UINT8*)&id,SOE_SIZE ); //д0

       }

      delay_ms(200);
      cur_max_soe = 0;
      idmax = cur_max_soe;
   while(K)
    {  K--;
    if(2 == o24lcxxx_write_bytes_ex(SOE_SAVE_ADDR_MAX,(UINT8*)&idmax,2 )) //��SOE�������
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
             olcm_dispprintf(0,1,"��SOE �¼���¼! ");
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
		    if((cur_max_soe-id)<499)//rg180613 ��һǧ��ǰ��ַ�ظ�����ʾ
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
      olcm_dispprintf(0,1,"����������ͨ��"); 
       if(TRUE != qty_get_resetinfo(id,&maxid0,&curid,edati,&no))
       {//ͨ���쳣
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
       id = maxid0 ;//init����
        if( id == 0 ){
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"�޸�λ��¼��");
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
             olcm_dispprintf(0,1,"�޸�λ�¼���¼! ");
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
            olcm_dispprintf(0,1,"��ţ�%d",id);
            if((Etime[1]<13)|| (Etime[2]<32)  )
            {
		    switch(err_type)//rg180613
		    {
				case Para_md :
			    olcm_dispprintf(0,2,"�������޸��ܶ�");
			    break;
				case Para_lsh:
			    olcm_dispprintf(0,2,"�������޸���ˮ��");
			    break;
			    case Para_tjyl:
			    olcm_dispprintf(0,2,"��������ͣ��ѹ��");
			    break;
			    default:
				 olcm_dispprintf(0,2,"�쳣����:%d",err_type);
				 break;
		    }
              /*  switch(err_type)
                  {
                      case 1:
                        olcm_dispprintf(0,3,"������ͨ���쳣");break;
                      case 2:
                        olcm_dispprintf(0,3,"��ŷ������쳣");break;
                      default:
                        olcm_dispprintf(0,3,"ϵͳ�쳣");break;
                          break;

                    }*/

              olcm_dispprintf(0,3,"ʱ��:%02d-%02d-%02d", Etime[0],Etime[1], Etime[2]);
              olcm_dispprintf(0,4,"     %02d:%02d:%02d", Etime[3], Etime[4], Etime[5]);
            }
            else
            {
                olcm_dispprintf(0,2,"�޸��쳣��Ϣ��¼");
            }
}
void Qry_Resetrec_Disp(UINT32 keyid)   //rg160623
{
     UINT8 Etime[6];
      UINT8 err_type;
      RESETFAULTMSG ResetFaultMsg;
    o24lcxxx_read_bytes_ex(KeyReset_RECORD_Addr +((keyid-1)% 30)*KeyReset_RECORD_Size, (UINT8*)&ResetFaultMsg.FaultCount, KeyReset_RECORD_Size);
            olcd_clearsCreen();
            olcm_dispprintf(0,1,"��ţ�%d",keyid);
            if((Etime[1]<13)|| (Etime[2]<32)  )
            {
              switch(ResetFaultMsg.FaultReason)
                   {
                       case 1:olcm_dispprintf(0,2,"�ϵ縴λ");
                               break;
                        case 2:olcm_dispprintf(0,2,"Ƿѹ��λ");
                               break;
                        case 3:olcm_dispprintf(0,2,"�ⲿ���Ÿ�λ");
                               break;
                        case 4:olcm_dispprintf(0,2,"�����λ");
                               break;
                        case 5:olcm_dispprintf(0,2,"���ò�ƥ�临λ");
                               break;
                        case 6:olcm_dispprintf(0,2,"���Ź���λ");
                               break;  
                        default:
                               break;       
                   }

                olcm_dispprintf(0,3,"ʱ��:%02d-%02d-%02d", ResetFaultMsg.DateTime[0],ResetFaultMsg.DateTime[1], ResetFaultMsg.DateTime[2]);
                olcm_dispprintf(0,4,"    %02d:%02d:%02d", ResetFaultMsg.DateTime[3], ResetFaultMsg.DateTime[4], ResetFaultMsg.DateTime[5]);
                olcm_dispprintf(6,4,"����");
            }
            else
            {
                olcm_dispprintf(0,2,"�޸�λ��Ϣ��¼");
            }
      
      
}
void car_disp(UINT8 dj,UINT8 tp,UINT8 *jy,UINT8 *qy,float zk,UINT8 q1,UINT8 q2,UINT8 q3,UINT8 q4,UINT8 xf,UINT8 *cp,UINT8 *pjyx)//150813
{
  UINT8 rdkey;
   UINT8 jye[10],qye[10],cph[16],pjy[4];
   float jin,jinh,qi,qih;
double ti;
  UINT8  infoxs[][8]={        "��Ч��",
                              "���鿨",
                              "��˾��",
                              "˽����",
			      "��˾��",
				"��˾ĸ",
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
                                   olcm_dispprintf(0,1,"���󣺵���%02dΪ��",dj);
                                   olcm_dispprintf(0,2,"�ô˿��޷�����!");
                                      olcm_dispprintf(0,3,"����������!");
                                      olcm_dispprintf(0,4,"�����ļ��˳�!");
                                       delay_ms(8000);
                                         rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(8000);
                                     olcd_clearsCreen();
                                 olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));

                                      olcm_dispprintf(4,1,"����%d",dj);
                                      if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((cph[0]==0)&&(cph[1]==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"�ۿ��ʣ�%06.02f��",zk);
                                       olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"�ۿ��ʣ�% 05.02f��",zk);
                                        olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"���ƣ�");
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
                                   olcm_dispprintf(0,1,"���󣺸�ƿ���ڣ�",dj);
                                   olcm_dispprintf(0,2,"�ô˿��޷�����!");
                                      olcm_dispprintf(0,3,"�뻻��!");
                                      olcm_dispprintf(0,4,"�����ļ��˳�!");
                                       delay_ms(8000);
                                         rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(8000);
                                     olcd_clearsCreen();
                                 olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));

                                      olcm_dispprintf(4,1,"����%d",dj);
                                      if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((cph[0]==0)&&(cph[1]==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"�ۿ��ʣ�%06.02f��",zk);
                                       olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"�ۿ��ʣ�% 05.02f��",zk);
                                        olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"���ƣ�");
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
                                      olcm_dispprintf(4,1,"����%d",dj);
                                       if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((*cp==0)&&(*(cp+1)==0)&&(*(cp+2)==0)&&(*(cp+3)==0))
                                      {
                                       if(zk==100)
                                       {olcm_dispprintf(0,3,"�ۿ��ʣ�%06.02f��",zk);
                                       olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"�ۿ��ʣ�% 05.02f��",zk);
                                        olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                        }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                     olcm_dispprintf(0,4,"���ƣ�");
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
                                   olcm_dispprintf(0,1,"��ʾ�����೬��");
                                   olcm_dispprintf(0,2,"�뾡�����!");
                                      olcm_dispprintf(0,3,"�����޷������� ");
                                      olcm_dispprintf(0,4,"�����ļ��˳�!");
                                       delay_ms(8000);
                                         rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey) break;
                                       delay_ms(8000);
                                     olcd_clearsCreen();
                                    olcd_dispstr(0,1,&infoxs[tp][0],strlen((UINT8 *)&infoxs[tp][0]));
                                      olcm_dispprintf(4,1,"����%d",dj);
                                       if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((*cp==0)&&(*(cp+1)==0)&&(*(cp+2)==0)&&(*(cp+3)==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"�ۿ��ʣ�%06.02f��",zk);
                                       olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"�ۿ��ʣ�% 05.02f��",zk);
                                        olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"���ƣ�");
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
                                      olcm_dispprintf(4,1,"����%d",dj);
                                       if((xf==0)||(xf==2))
                                      {
                                          olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,jy,strlen(jy));
                                      }
                                      if((xf==1)||(xf==3))
                                      {
                                      olcm_dispprintf(0,2,"���ࣺ");
                                      olcd_dispstr(3,2,qy,strlen(qy));
                                      }

                                      if((*cp==0)&&(*(cp+1)==0)&&(*(cp+2)==0)&&(*(cp+3)==0))
                                      {
                                      if(zk==100)
                                       {olcm_dispprintf(0,3,"�ۿ��ʣ�%06.02f��",zk);
                                       olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);}
                                        else
                                        { olcm_dispprintf(0,3,"�ۿ��ʣ�% 05.02f��",zk);
                                        olcm_dispprintf(0,4,"��Ч�ڣ�%2x%02x%02x%02x",q1,q2,q3,q4);
                                        }
                                      }
                                      else
                                      {
                                       if(zk==100)
                                       olcm_dispprintf(0,3,"%06.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                        else
                                       olcm_dispprintf(0,3,"% 05.02f��%2x%02x%02x%02x",zk,q1,q2,q3,q4);
                                      olcm_dispprintf(0,4,"���ƣ�");
                                      olcd_dispstr(3,4,cph,strlen(cph));
                                      }
                                        rdkey = ostatemachine_getkey();
                                   b_keyv = FALSE;
                                    if(_KEY_EXIT_EV_ == rdkey)
                                   { _b_cz_card=TRUE;
                                    return;}
                                      }
}