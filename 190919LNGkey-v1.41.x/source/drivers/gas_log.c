/* 
 * File:   gas_log.h
 * Author: sushuai 
 *
 * Created on 2018��11��28��, ����9:56
 */

//#include "drivers.h"
//#include "gas_log.h"
#include "../includes/global_def.h"
UINT8 str_chan_u8(UINT8 * date)
{
    UINT8 buff1,buff2,tdate;
    buff1 = (*(date+6))-0x30;
    buff2 = (*(date+7))-0x30;
    tdate = (buff1<<4)|buff2;
    return tdate;
}
void  OnceRecordEEP()
{
    UINT8 OnceID;
    if(1 != o24lcxxx_read_bytes_ex(GAS_RECORD_SREIAL_FLAG,&OnceID,1))          // ��ȡ�洢���кű�־
    {
        SOEACTION1(EEPROM_READ_KEY_ERR,eCurRunState);                                               // ��ȡ EEP ���ݴ���  
        return;
    }
    if( OnceID != 0x42)
    {
        Compa_u32 record_id;
        OnceID = 0x42; 
        record_id.compa_u32 = 0;
        o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_FLAG,&OnceID,1);
        o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4);
    }
//    OnceID = 0x55; 
//    o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL_FLAG,&OnceID,1);
}
UINT32 GasRecordMAX()
{
    Compa_u32 record_id;
    o24lcxxx_read_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4);                       // ��ȡ�洢���к�
    return record_id.compa_u32;                                                       /// ��ȡ�����̰������¼���к�
}
BOOL WriteRecordSerial(UINT32 id)                                                  //  д����� 
{
    Compa_u32 record_id;
    record_id.compa_u32 = id;
    
    if(4 != o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4))                           // ��ȡ�洢���к�
    {
        if(4 != o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4))                       // ��ȡ�洢���к�
        {
            return FALSE;
        }
    }
    
    return TRUE;     
    
}
BOOL WriteRecordDate(UINT32 id,GAS_log date)                                       //  д����̰������¼��Ϣ
{
    UINT8 len;
    shift_type write_date;
    write_date.gas_record_query = date;
    len = sizeof(write_date.compa_uint8);
    if(len != o24lcxxx_write_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), write_date.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ    100 -> 30
    {
        if(len != o24lcxxx_write_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), write_date.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ
        {
            
           return FALSE;
        }
    }
    
    return TRUE;
}
void WiteRecorInfoOnce(GAS_log date)                                                 // д�� ������¼��Ϣ
{
    UINT32 id;
    id = GasRecordMAX();    // ����¼���к�
    id = id+1;                                                                  //д�� ID ���к�����
    if(!WriteRecordSerial(id))                                                  // д�� ID ���
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
        return;
    }
    if(!WriteRecordDate( id , date ))                                            // д�� ��¼��Ϣ��ָ����ַ
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
        return;
    }
    
}
void WiteRecorInfo(GAS_log date)                                                 // д�� ������¼��Ϣ
{
    UINT32 id;
    id = GasRecordMAX();    // ����¼���к�
//    id = id+1;                                                                  //д�� ID ���к�����
//    if(!WriteRecordSerial(id))                                                  // д�� ID ���
//    {
//        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
//        return;
//    }
    if(!WriteRecordDate( id , date ))                                            // д�� ��¼��Ϣ��ָ����ַ
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // ��ȡ EEP ���ݴ���  
        return;
    }
    
}
BOOL ReadRecordInfo( UINT32 id)                                                  //  ��ȡ���̰������¼��Ϣ
{
//    shift_type shift_read;
    UINT8 len;
    len = sizeof(shift_read.compa_uint8);
    if(len != o24lcxxx_read_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), shift_read.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ  ss190308 100 -> 30
    {
        if(len != o24lcxxx_read_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), shift_read.compa_uint8,len))             // ��ȡ���̰������¼��Ϣ
        {
            
           return FALSE;
        }
    }
    return TRUE;
}
void DispRecordInfo(UINT32 id)                                                                   //��ʾ��ǰ ID ������ˮ����Ϣ
{
    UINT8 buffer[10];
    
    if(!ReadRecordInfo( id))
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
void OprintRecordInfo()
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
    itoa(buffer,shift_read.gas_record_query.card_id,10);                         ///  ss190306
    if(strlen(buffer))                                                               // �޿�����״̬�²���Ҫ��ʾ������Ϣ
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
    if(GAS_START_SEND_SUCC == (GAS_START_SEND_SUCC &shift_read.gas_record_query.gas_process))   //ss190215
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
void GasRecordQuery(void)                       // ��ѯ���̰������¼��Ϣ
{
    UINT32 id; 
    UINT32 MAX_id;
    
    olcd_clearsCreen();                                                // �����Ļ��ʾ��Ϣ
    id = GasRecordMAX();                                               // ����¼���к�
    if(id == 0)                                                         /// �ж����к��Ƿ���ȷ
    {
        olcm_dispprintf(0,1,"����ˮ��¼��");
        osys_getkey(_KEY_NULL_, 300);
        eVirtualKey = _KEY_VIRTUAL_EV_;
        return;
    }
    MAX_id = id;
    DispRecordInfo(id);                                                // ��ʾ��ˮ��Ϣ
    
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
            DispRecordInfo(id);                                                // ��ʾ��ˮ��Ϣ
        }
        else  if(_KEY_SW_EV_ == keyv)
        {
            if(++id > MAX_id)
            {
                id = MAX_id;
                continue;
            }
            DispRecordInfo(id);                                                // ��ʾ��ˮ��Ϣ
        }
        else  if(_KEY_STOP_EV_ == keyv)
        {
//            oprint_qry_easy_rec();
            OprintRecordInfo();

        }
    }
    eVirtualKey = _KEY_VIRTUAL_EV_;
    
}
void oqry_GasRecordQuery(void)
{

    olcd_clearsCreen();
    olcm_dispprintf(0,1,"1.��ȷ��¼˳��");
    olcm_dispprintf(0,2,"2.��ȷ��¼����");
    olcm_dispprintf(0,3,"3.�쳣��¼˳��");
    olcm_dispprintf(0,4,"4.�쳣��¼����");
}
UINT32 IndexRecordData(UINT32 id)
{
    UINT32 MAX_id,i; 
    MAX_id = GasRecordMAX();                                               // ����¼���к�
    if(MAX_id > 100)
        i = MAX_id - 100;
//     MAX_id = (MAX_id % 100)+1;
    for(;i<MAX_id;i++)                                                      //������ˮ��
    {
        ReadRecordInfo(i);                                                  
        if(id == shift_read.gas_record_query.gas_stream)                       
        {
            return i;
        }
    }
    return 0xFFFF0000;
}
void GasRecordQueryIndex(void)                       // ������ѯ���̰������¼��Ϣ
{
    UINT32 MAX_id,id; 
    UINT32 liushuinum = 0;
    UINT8 len, vkey = 0;
    INT8  str[20] = {0};
    olcd_clearsCreen();                                                // �����Ļ��ʾ��Ϣ
    MAX_id = GasRecordMAX();                                               // ����¼���к�
 //   MAX_id = (MAX_id % 100);
//    MAX_id = id;
    olcm_dispprintf(0,1,"��������ˮ�ţ�");
    cursor_x = 0;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,FALSE,FALSE);
    
    if( vkey == _KEY_OK_EV_ && len>0)
   {
        liushuinum= atoi(str);
        id = IndexRecordData(liushuinum);
        if(0xFFFF0000 != id) 
        {
            DispRecordInfo(id);                                                // ��ʾ��ˮ��Ϣ
    
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
                    DispRecordInfo(id);                                                // ��ʾ��ˮ��Ϣ
                }
                else  if(_KEY_SW_EV_ == keyv)
                {
                    if(++id > MAX_id)
                    {
                        id = MAX_id;
                        continue;
                    }
                    DispRecordInfo(id);                                                // ��ʾ��ˮ��Ϣ
                }
                else  if(_KEY_STOP_EV_ == keyv)
                {
        //            oprint_qry_easy_rec();
                    OprintRecordInfo();                                              //��ӡ������¼��Ϣ

                }
            }
            eVirtualKey = _KEY_VIRTUAL_EV_;
         }
         else
         {//û�����������ˮ�ż�¼
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"���������ˮ��");
             olcm_dispprintf(0,2,"�޴˼�����¼");
             olcm_dispprintf(0,3,"���¼�ѱ�����");
             osys_getkey(_KEY_NULL_,300);
             eVirtualKey = _KEY_VIRTUAL_EV_;
         }
   }
     eVirtualKey = _KEY_VIRTUAL_EV_;
}

