
/* 
 * File:   gas_log_sp.c
 * Author: sushuai 
 *
 * Created on 2019��1��29��, ����9:56
 */

//#include "drivers.h"
//#include "gas_log.h"
#include "../includes/global_def.h"

//void str_chan_u8_SP(UINT8 * date,UINT8 tdate)
//{
//    UINT8 buff1,buff2;
//    buff1 = (*(date+6))-0x30;
//    buff2 = (*(date+7))-0x30;
//    tdate = (buff1*10)+buff2;
//}
void  OnceRecordEEP_SP()                                                        //����Ĵ洢���� ss190128
{
    UINT8 OnceID;
    if(1 != o24lcxxx_read_bytes_ex(GAS_RECORD_SREIAL_FLAG_SP,&OnceID,1))          // ��ȡ�洢���кű�־
    {
        SOEACTION1(EEPROM_READ_KEY_ERR,eCurRunState);                                               // ��ȡ EEP ���ݴ���  
        return;
    }
    if( OnceID != 0x57)
    {
        
        Compa_u32 record_id;      
        OnceID = 0x57; 
        record_id.compa_u32 = 0;
        o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_FLAG_SP,&OnceID,1);              // д��洢��־
        o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_SP,record_id.compa_uc,4);        // д�����к�Ϊ��
    }
//    OnceID = 0x55; 
//    o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_FLAG,&OnceID,1);
}
UINT32 GasRecordMAX_SP()                                                        //��ȡ������к� �����
{
    Compa_u32 record_id;
    o24lcxxx_read_bytes_ex(GAS_RECORD_SREIAL_SP,record_id.compa_uc,4);                       // ��ȡ�洢���к�
    return record_id.compa_u32;                                                       /// ��ȡ�����̰������¼���к�
}
BOOL WriteRecordSerial_SP(UINT32 id)                                                  //  д����� 
{
    Compa_u32 record_id;
    record_id.compa_u32 = id;
    
    if(4 != o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_SP,record_id.compa_uc,4))                           // ��ȡ�洢���к�
    {
        if(4 != o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_SP,record_id.compa_uc,4))                       // ��ȡ�洢���к�
        {
            return FALSE;
        }
    }
    
    return TRUE;     
    
}
BOOL WriteRecordDate_SP(UINT32 id,GAS_log date)                                       //  �������쳣�ļ�¼�洢���̰�   30������
{
    UINT8 len;
    shift_type write_date;
    write_date.gas_record_query = date;
    len = sizeof(write_date.compa_uint8);
    if(len != o24lcxxx_write_bytes_ex((GAS_RECORD_ADD_SP+(((id-1)%100)*RECORD_LEN_SP)), write_date.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ
    {
        if(len != o24lcxxx_write_bytes_ex((GAS_RECORD_ADD_SP+(((id-1)%100)*RECORD_LEN_SP)), write_date.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ   30 -> 100  ss190308
        {
            
           return FALSE;
        }
    }
    
    return TRUE;
}
//void WiteRecorInfoOnce(GAS_log date)                                                 // д�� ������¼��Ϣ
//{
//    UINT32 id;
//    id = GasRecordMAX();    // ����¼���к�
//    id = id+1;                                                                  //д�� ID ���к�����
//    if(!WriteRecordSerial(id))                                                  // д�� ID ���
//    {
//        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
//        return;
//    }
//    if(!WriteRecordDate( id , date ))                                            // д�� ��¼��Ϣ��ָ����ַ
//    {
//        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
//        return;
//    }
//    
//}
void WiteRecorInfo_SP(GAS_log date)                                                 // д�� ������¼��Ϣ
{
    UINT32 id;
    id = GasRecordMAX_SP();    // ����¼���к�
    id = id+1;                                                                  //д�� ID ���к�����
    if(!WriteRecordSerial_SP(id))                                                  // д�� ID ���
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
        return;
    }
    if(!WriteRecordDate_SP( id , date ))                                            // д�� ��¼��Ϣ��ָ����ַ
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
        return;
    }
    
}
void WiteRecorInfo_AN(GAS_log date)                                           //�洢������¼��Ϣ
{
    WiteRecorInfo(date) ;                                                       //�����洢��������ļ�¼
    
//      if((date.gas_stop_way != MONEY_ALL)&&(date.gas_stop_way != PRESS_STOP)&& \
//            (date.gas_stop_way != BACKSTAGE_STOP)&&(date.gas_stop_way != VELOCIIY_LOW)) // ����������ֹͣ��������������ֹͣ������ֹ̨ͣ�����ٵͣ�    ss190215
//    {
//        WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
//        return;
//    }
    if(GAS_START_SEND_SUCC != (GAS_START_SEND_SUCC &date.gas_process))              //������ʼָ���ʧ��
    {
        WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
        return;
    }
    
    if(GAS_PRECOOL_SUCC != date.gas_precool)                                          //Ԥ��ʧ��             ss190215
    {
        WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
        return;
    }
    
//    if((shift_read.gas_record_query.grey_lock_inif.grey_status & 0xF0)== GAS_START_MORMAL)     //  �����������Ҫ����ָֹͣ��
//    {
//        if( GAS_STOP_SEND_SUCC != (date.gas_process & GAS_STOP_SEND_SUCC) )           // ����ָֹͣ���ʧ��
//        {
//            WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
//            return;
//        }   
//    }
    if(((WKJQ==1)&&(_CARD_TYPE < 7))||((WKJQ==0)&&(_CARD_TYPE == 2)||(_CARD_TYPE == 3)))     //����޿����������жϻ���״̬
    {
        if(GREY_LUCK_SUCC != (date.grey_lock_inif.grey_status & 0x03))    // ������¼   ����ǰ����״̬ʧ��
        {
            WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
            return;
        }

        if(GREY_GAS_LUCK_SUCC != (date.grey_lock_inif.grey_status & 0x0C))         // ������¼   �����������ٴζ�ȡ����״̬
        {
            WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
            return;
        } 

        if((date.grey_unlock_inif.grey_status & 0xF0) != GREY_UNLUCK_SUCC)          //���״̬ʧ��
        {
            WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
            return;
        }
    }
    
    if( GAS_ACCOUNTS_SEND_SUCC != (date.gas_process & GAS_ACCOUNTS_SEND_SUCC))         // ֪ͨ���屣�������Ϣ
    {
        WiteRecorInfo_SP(date) ;                                                    // �洢�����쳣����ļ�¼
        return;
    }
    
}
BOOL ReadRecordInfo_SP( UINT32 id)                                                  //  ��ȡ���̰������¼��Ϣ
{
//    shift_type shift_read;
    UINT8 len;
    len = sizeof(shift_read.compa_uint8);
    if(len != o24lcxxx_read_bytes_ex((GAS_RECORD_ADD_SP+(((id-1)%100)*RECORD_LEN)), shift_read.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ
    {
        if(len != o24lcxxx_read_bytes_ex((GAS_RECORD_ADD_SP+(((id-1)%100)*RECORD_LEN)), shift_read.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ
        {
            
           return FALSE;
        }
    }
    return TRUE;
}
void DispRecordInfo_SP(UINT32 id)                                                                   //��ʾ��ǰ ID ������ˮ����Ϣ
{
//    UINT8 card_id[8];
     UINT8 buffer[10];
    
    if(!ReadRecordInfo_SP( id))
    {
        SOEACTION1(EEPROM_READ_KEY_ERR,eCurRunState);                                               // ��ȡ EEP ���ݴ���  
        return;
    }
    olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"���:%d",id);
    olcm_dispprintf(0,1,"��ˮ�ţ�%d",shift_read.gas_record_query.gas_stream);                        // ��ˮ��
//    olcm_dispprintf(0,2,"���ţ�%s",shift_read.gas_record_query.card_id);        // ����
     itoa(buffer,shift_read.gas_record_query.card_id,10);
    olcm_dispprintf(0,2,"���ţ�%s",buffer);        // ����
    olcm_dispprintf(0,3,"���ࣺ%.2f",shift_read.gas_record_query.grey_unlock_inif.Balance_To);                                                                //�������
    olcm_dispprintf(0,4,"����:%02d-%02d",shift_read.gas_record_query.grey_unlock_inif.time[1],shift_read.gas_record_query.grey_unlock_inif.time[2]);
    olcm_dispprintf(6,4,"����");
}
void OprintRecordInfo_SP()
{
    UINT8 buffer[10];

    oprint_normal_cmd();
//    oprint_printf("��ӭʹ�ý���CNG������\r\n"); //cur_sysparas
    
    oprint_printf("LNG���̰������¼��ѯ��\r\n");
    oprint_printf("\r\n");
    oprint_printf("�� ˮ ��: %d\r\n", shift_read.gas_record_query.gas_stream);    
    switch(shift_read.gas_record_query.gas_start_way)
    {
        case CARD_DRIVER_F:
            oprint_printf("�� �� ��: ��˾��\r\n");
            break;
            
        case CARD_DRIVER_T:
            oprint_printf("�� �� ��: ��˾ĸ��\r\n");
            break;
            
        case CARD_DRIVER_C:
            oprint_printf("�� �� ��: ��˾�ӿ�\r\n");
            break;    
            
        case CARD_MANAGE:
            oprint_printf("�� �� ��: ����\r\n");
            break;    
            
        case CARD_STAFF:
            oprint_printf("�� �� ��: ���鿨\r\n");
            break;
            
        case CARD_SERVICE:
            oprint_printf("�� �� ��: ˽����\r\n");
            break;
            
        case CARD_OPERATION: 
            oprint_printf("�� �� ��: �޿�����\r\n");
            break;     
            
        default:
            oprint_printf("�� �� ��: δ֪��\r\n");
            break;
    }
//    memcpy(buffer,shift_read.gas_record_query.card_id,10);
//    if(strlen(shift_read.gas_record_query.card_id))                              // �޿�����״̬�²���Ҫ��ʾ������Ϣ
//    {
//        oprint_printf("IC �� ��: %s\r\n",shift_read.gas_record_query.card_id);
//    }
    itoa(buffer,shift_read.gas_record_query.card_id,10);                     ///  ss190306
    if(strlen(buffer))                              // �޿�����״̬�²���Ҫ��ʾ������Ϣ
    {
        oprint_printf("IC �� ��: %s\r\n",buffer);
        itoa(buffer,shift_read.gas_record_query.card_id_js,10);                     
        oprint_printf("IC �� ��: %s(J)\r\n", buffer); 
    }
     if(GREY_LUCK_SUCC == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x03))
    {
        if(GREY_GAS_LUCK_SUCC == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x0C))             // ������¼   �����������ٴζ�ȡ����״̬  ss190215
        {
            oprint_printf("�û�״̬: �ûҳɹ� (Y)\r\n" );
        }
        else if(GREY_GAS_LUCK_FAILL == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x0C))             // ������¼   �����������ٴζ�ȡ����״̬
                oprint_printf("�û�״̬: �ûҳɹ� (N)\r\n" );
            else 
                oprint_printf("�û�״̬: �ûҳɹ�\r\n" );
    }
    else  
        if(GREY_LUCK_FAILL == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x03))
            oprint_printf("�û�״̬: �û�ʧ�� \r\n" );
        else 
            oprint_printf("�û�״̬: δִ���ûҲ��� \r\n" );
     
    memcpy(buffer,shift_read.gas_record_query.grey_lock_inif.time,6);
    oprint_printf("�û�����: 20%02d��%02d��%02d��\r\n",buffer[0],buffer[1],buffer[2]);
    oprint_printf("�û�ʱ��: %02dʱ%02d��%02d��\r\n",buffer[3],buffer[4],buffer[5]);
    oprint_printf("��ǰ���: %.02fԪ\r\n", shift_read.gas_record_query.grey_lock_inif.cur_money);
    switch(shift_read.gas_record_query.grey_lock_inif.grey_status & 0xF0)
    {
        case GAS_START_FIX_M: 
            oprint_printf("������ʽ: �������\r\n");
            break;
        case GAS_START_FIX_V:
            oprint_printf("������ʽ: ��������\r\n");
            break;
        case GAS_START_MORMAL:
            oprint_printf("������ʽ: ��������\r\n");
            break;
            
        default:
            oprint_printf("������ʽ: ����������\r\n");
            break;
            
    }
     if(GAS_START_SEND_SUCC == (GAS_START_SEND_SUCC &shift_read.gas_record_query.gas_process))    //ss190215
    {
        oprint_printf("Ԥ�俪ʼ: ���ͳɹ�\r\n");
    }
    else
        oprint_printf("Ԥ�俪ʼ: ����ʧ��\r\n");
    
    if(GAS_PRECOOL_SUCC == shift_read.gas_record_query.gas_precool)                             //ss190215
    {
        oprint_printf("Ԥ��״̬: Ԥ��ɹ�\r\n");
    }
    else
        oprint_printf("Ԥ��״̬: Ԥ��ʧ��\r\n");

    switch(shift_read.gas_record_query.gas_stop_way)
    {
        case COMMUN_TIIMOUT:
            oprint_printf("ֹͣ��ʽ: ���ͨ�ų�ʱ(E1)\r\n");
            break;
        case FLOWMETER_ERR:
            oprint_printf("ֹͣ��ʽ:������ͨ�Ŵ���(E3)\r\n");
            break;
        case PRECOOL_ERR:
            oprint_printf("ֹͣ��ʽ:Ԥ�䳬ʱ(E4)\r\n");
            break;    
        case PRESSURE_ERR:
            oprint_printf("ֹͣ��ʽ: ѹ���쳣(E5)\r\n");
            break;     
        case VELOCITY_HIGH:
            oprint_printf("ֹͣ��ʽ: �����������(E6)\r\n");
            break;    
        case VELOCIIY_LOW:
            oprint_printf("ֹͣ��ʽ: ���ٵ���ͣ(E0)\r\n");
            break;    
        case BACKSTAGE_STOP:
            oprint_printf("ֹͣ��ʽ: ��̨Զ��ͣ��(E7)\r\n");
            break;
        case GAS_UNUSUAL:
            oprint_printf("ֹͣ��ʽ: �����쳣\r\n");
            break;
        case MONEY_ALL:
            oprint_printf("ֹͣ��ʽ: ������(1)\r\n");
            break;    
        case CARD_EXTRACT:
            oprint_printf("ֹͣ��ʽ: �����γ�\r\n");
            break;     
        case PRESS_STOP:
            oprint_printf("ֹͣ��ʽ: ��ֹͣ��\r\n");
            break;    
        case TRIPLE_COMMUN_FAILL:
            oprint_printf("ֹͣ��ʽ: �����޽�������\r\n");
            break;        
          case SYS_HARD_FAULT:
            oprint_printf("ֹͣ��ʽ: ϵͳӲ���쳣\r\n");
            break;     
        case SYS_FAULT:
            oprint_printf("ֹͣ��ʽ: ��Ҫ������Ϣʧ��\r\n");
            break;    
        case CARD_BALANCE_FAILL:
            oprint_printf("ֹͣ��ʽ: �����Ϳ��಻ͬ\r\n");
            break;  
        default:
             oprint_printf("ֹͣ��ʽ: ֹͣ��ʽ�쳣 \r\n");
            break;
    }
    if( GAS_STOP_SEND_SUCC == (shift_read.gas_record_query.gas_process & GAS_STOP_SEND_SUCC) )
    {
        oprint_printf("����ֹͣ: ���ͳɹ�\r\n");
    }
    else 
         oprint_printf("����ֹͣ: ����ʧ��\r\n");
    oprint_printf("��ѯ����: %d ��\r\n", (shift_read.gas_record_query.grey_unlock_inif.grey_status & 0x0F));
    oprint_printf("��ͣ����: %d ��\r\n", (shift_read.gas_record_query.gas_process & 0x0F));
    switch(shift_read.gas_record_query.grey_unlock_inif.grey_status & 0xF0)
    {
        case GREY_ACCOUNTS_FAILL:
            oprint_printf("���״̬: �ۿ�δ���\r\n");
            break;
        case GREY_UNLUCK_FAILL:
            oprint_printf("���״̬: �ۿ����δ���\r\n");
            break;
        case GREY_UNLUCK_SUCC:
            oprint_printf("���״̬: ��ҳɹ�\r\n");
            break;    
        case GREY_ACCOUNTS_STATU_FAILL:                                           //ss190306  ���Ӷ����ѷ�ʽ�쳣�Ĵ���
            oprint_printf("���״̬: ���ѷ�ʽ�쳣δ���\r\n");
            break;
        case GREY_CARD_CHEKE_FAILL:
            oprint_printf("���״̬: ���Ŵ�����ʧ��\r\n");
            break;
        default:
            oprint_printf("���״̬: ���ʧ��\r\n");
            break;
        
    }
    
    memcpy(buffer,shift_read.gas_record_query.grey_unlock_inif.time,6);
    oprint_printf("�������: 20%02d��%02d��%02d��\r\n",buffer[0],buffer[1],buffer[2]);
    oprint_printf("���ʱ��: %02dʱ%02d��%02d��\r\n",buffer[3],buffer[4],buffer[5]);
    if( GAS_ACCOUNTS_SEND_SUCC == (shift_read.gas_record_query.gas_process & GAS_ACCOUNTS_SEND_SUCC) )
    {
        oprint_printf("�ۿ���Ϣ: ���ͳɹ�\r\n");
    }
    else 
         oprint_printf("�ۿ���Ϣ: ����ʧ��\r\n");
    oprint_printf("���ѽ��: %.02fԪ\r\n", shift_read.gas_record_query.grey_unlock_inif.OKgas_money);
    oprint_printf("�������: %.02fԪ\r\n", shift_read.gas_record_query.grey_unlock_inif.Balance_To);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("******* ����ˮ�Ų�ѯ���� *******\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
}
void GasRecordQuery_SP(void)                       // ��ѯ���̰������¼��Ϣ
{
    UINT32 id; 
    UINT32 MAX_id;
    
    olcd_clearsCreen();                                                // �����Ļ��ʾ��Ϣ
    id = GasRecordMAX_SP();                                               // ����¼���к�
    if(id == 0)                                                         /// �ж����к��Ƿ���ȷ
    {
        olcm_dispprintf(0,1,"����ˮ��¼��");
        osys_getkey(_KEY_NULL_, 300);
        eVirtualKey = _KEY_VIRTUAL_EV_;
        return;
    }
    MAX_id = id;
    DispRecordInfo_SP(id);                                                // ��ʾ��ˮ��Ϣ
    
    while(1)
    {
        keyv = ostatemachine_getkey();
        b_keyv = FALSE;
      //  if(0 == keyv) continue;
        if(_KEY_EXIT_EV_ == keyv) break;
    //    if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
        else if(_KEY_UP_EV_ == keyv)
        {
            if(--id == 0)
            {
                id = 1;
                continue;
            }
            DispRecordInfo_SP(id);                                                // ��ʾ��ˮ��Ϣ
        }
        else  if(_KEY_SW_EV_ == keyv)
        {
            if(++id > MAX_id)
            {
                id = MAX_id;
                continue;
            }
            DispRecordInfo_SP(id);                                                // ��ʾ��ˮ��Ϣ
        }
        else  if(_KEY_STOP_EV_ == keyv)
        {
//            oprint_qry_easy_rec();
            OprintRecordInfo_SP();                                              //��ӡ������¼��Ϣ

        }
    }
    eVirtualKey = _KEY_VIRTUAL_EV_;
    
}
UINT32 IndexRecordData_SP(UINT32 id)
{
    UINT32 MAX_id,i; 
    MAX_id = GasRecordMAX_SP();                                               // ����¼���к�
     if(MAX_id > 30)
        i = MAX_id - 30;
//     MAX_id = (MAX_id % 30)+1;
    for(;i<=MAX_id;i++)                                                      //������ˮ��
    {
        ReadRecordInfo_SP(i);                                                  
        if(id == shift_read.gas_record_query.gas_stream)                       
        {
            return i;
        }
    }
    return 0xFFFF0000;
}
void GasRecordQueryIndex_SP(void)                       // ������ѯ���̰������¼��Ϣ
{
    UINT32 MAX_id,id; 
    UINT32 liushuinum = 0;
    UINT8 len, vkey = 0;
    INT8  str[20] = {0};
    olcd_clearsCreen();                                                // �����Ļ��ʾ��Ϣ
    MAX_id = GasRecordMAX_SP();                                               // ����¼���к�
 //   MAX_id = (MAX_id % 30);
//    MAX_id = id;
    olcm_dispprintf(0,1,"��������ˮ�ţ�");
    cursor_x = 0;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,FALSE,FALSE);
    
    if( vkey == _KEY_OK_EV_ && len>0)
   {
        liushuinum= atoi(str);
        id = IndexRecordData_SP(liushuinum);
        if(0xFFFF0000 != id) 
        {
            DispRecordInfo_SP(id);                                                // ��ʾ��ˮ��Ϣ
    
            while(1)
            {
                keyv = ostatemachine_getkey();
                b_keyv = FALSE;
              //  if(0 == keyv) continue;
                if(_KEY_EXIT_EV_ == keyv) break;
            //    if( _KEY_UP_EV_ != keyv && _KEY_SW_EV_ != keyv) continue;
                else if(_KEY_UP_EV_ == keyv)
                {
                    if(--id == 0)
                    {
                        id = 1;
                        continue;
                    }
                    DispRecordInfo_SP(id);                                                // ��ʾ��ˮ��Ϣ
                }
                else  if(_KEY_SW_EV_ == keyv)
                {
                    if(++id > MAX_id)
                    {
                        id = MAX_id;
                        continue;
                    }
                    DispRecordInfo_SP(id);                                                // ��ʾ��ˮ��Ϣ
                }
                else  if(_KEY_STOP_EV_ == keyv)
                {
        //            oprint_qry_easy_rec();
                    OprintRecordInfo_SP();                                              //��ӡ������¼��Ϣ

                }
            }
            eVirtualKey = _KEY_VIRTUAL_EV_;
         }
         else
         {//û�����������ˮ�ż�¼
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"���������ˮ��");
             olcm_dispprintf(0,2,"�޴��쳣��¼");
             olcm_dispprintf(0,3,"���¼�ѱ�����");
             osys_getkey(_KEY_NULL_,300);
             eVirtualKey = _KEY_VIRTUAL_EV_;
         }
   }
     eVirtualKey = _KEY_VIRTUAL_EV_;
}


