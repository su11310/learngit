/* 
 * File:   gas_log.h
 * Author: sushuai 
 *
 * Created on 2018年11月28日, 上午9:56
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
    if(1 != o24lcxxx_read_bytes_ex(GAS_RECORD_SREIAL_FLAG,&OnceID,1))          // 读取存储序列号标志
    {
        SOEACTION1(EEPROM_READ_KEY_ERR,eCurRunState);                                               // 获取 EEP 数据错误  
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
    o24lcxxx_read_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4);                       // 读取存储序列号
    return record_id.compa_u32;                                                       /// 获取最大键盘板加气记录序列号
}
BOOL WriteRecordSerial(UINT32 id)                                                  //  写入序号 
{
    Compa_u32 record_id;
    record_id.compa_u32 = id;
    
    if(4 != o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4))                           // 读取存储序列号
    {
        if(4 != o24lcxxx_write_bytes_ex(GAS_RECORD_SREIAL,record_id.compa_uc,4))                       // 读取存储序列号
        {
            return FALSE;
        }
    }
    
    return TRUE;     
    
}
BOOL WriteRecordDate(UINT32 id,GAS_log date)                                       //  写入键盘板加气记录信息
{
    UINT8 len;
    shift_type write_date;
    write_date.gas_record_query = date;
    len = sizeof(write_date.compa_uint8);
    if(len != o24lcxxx_write_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), write_date.compa_uint8,len))             // 读取键盘板加气记录信息    100 -> 30
    {
        if(len != o24lcxxx_write_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), write_date.compa_uint8,len))             // 读取键盘板加气记录信息
        {
            
           return FALSE;
        }
    }
    
    return TRUE;
}
void WiteRecorInfoOnce(GAS_log date)                                                 // 写入 加气记录信息
{
    UINT32 id;
    id = GasRecordMAX();    // 最大记录序列号
    id = id+1;                                                                  //写入 ID 序列号增加
    if(!WriteRecordSerial(id))                                                  // 写入 ID 序号
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // 获取 EEP 数据错误  
        return;
    }
    if(!WriteRecordDate( id , date ))                                            // 写入 记录信息到指定地址
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // 获取 EEP 数据错误  
        return;
    }
    
}
void WiteRecorInfo(GAS_log date)                                                 // 写入 加气记录信息
{
    UINT32 id;
    id = GasRecordMAX();    // 最大记录序列号
//    id = id+1;                                                                  //写入 ID 序列号增加
//    if(!WriteRecordSerial(id))                                                  // 写入 ID 序号
//    {
//        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // 获取 EEP 数据错误  
//        return;
//    }
    if(!WriteRecordDate( id , date ))                                            // 写入 记录信息到指定地址
    {
        SOEACTION1(EEPROM_WRITE_KEY_ERR,eCurRunState);                                      // 获取 EEP 数据错误  
        return;
    }
    
}
BOOL ReadRecordInfo( UINT32 id)                                                  //  读取键盘板加气记录信息
{
//    shift_type shift_read;
    UINT8 len;
    len = sizeof(shift_read.compa_uint8);
    if(len != o24lcxxx_read_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), shift_read.compa_uint8,len))             // 读取键盘板加气记录信息  ss190308 100 -> 30
    {
        if(len != o24lcxxx_read_bytes_ex((GAS_RECORD_ADD+(((id-1)%30)*RECORD_LEN)), shift_read.compa_uint8,len))             // 读取键盘板加气记录信息
        {
            
           return FALSE;
        }
    }
    return TRUE;
}
void DispRecordInfo(UINT32 id)                                                                   //显示当前 ID 加气流水号信息
{
    UINT8 buffer[10];
    
    if(!ReadRecordInfo( id))
    {
        SOEACTION1(EEPROM_READ_KEY_ERR,eCurRunState);                                               // 获取 EEP 数据错误  
        return;
    }
    olcd_clearsCreen();
 //   olcm_dispprintf(0,1,"序号:%d",id);
    olcm_dispprintf(0,1,"流水号：%d",shift_read.gas_record_query.gas_stream);                        // 流水号
//    olcm_dispprintf(0,2,"卡号：%s",shift_read.gas_record_query.card_id);        // 卡号
    itoa(buffer,shift_read.gas_record_query.card_id,10);
    olcm_dispprintf(0,2,"卡号：%s",buffer);        // 卡号
    olcm_dispprintf(0,3,"卡余：%.2f",shift_read.gas_record_query.grey_unlock_inif.Balance_To);                                                                //加气金额
    olcm_dispprintf(0,4,"日期:%02d-%02d",shift_read.gas_record_query.grey_unlock_inif.time[1],shift_read.gas_record_query.grey_unlock_inif.time[2]);
    olcm_dispprintf(6,4,"↓↑");
}
void OprintRecordInfo()
{
    UINT8 buffer[10];

    oprint_normal_cmd();
//    oprint_printf("欢迎使用杰瑞CNG加气机\r\n"); //cur_sysparas
    
    oprint_printf("LNG键盘板加气记录查询单\r\n");
    oprint_printf("\r\n");
    oprint_printf("流 水 号: %d\r\n", shift_read.gas_record_query.gas_stream);    
    switch(shift_read.gas_record_query.gas_start_way)
    {
        case CARD_DRIVER_F:
            oprint_printf("卡 类 型: 公司卡\r\n");
            break;
            
        case CARD_DRIVER_T:
            oprint_printf("卡 类 型: 公司母卡\r\n");
            break;
            
        case CARD_DRIVER_C:
            oprint_printf("卡 类 型: 公司子卡\r\n");
            break;    
            
        case CARD_MANAGE:
            oprint_printf("卡 类 型: 管理卡\r\n");
            break;    
            
        case CARD_STAFF:
            oprint_printf("卡 类 型: 班组卡\r\n");
            break;
            
        case CARD_SERVICE:
            oprint_printf("卡 类 型: 私车卡\r\n");
            break;
            
        case CARD_OPERATION: 
            oprint_printf("卡 类 型: 无卡加气\r\n");
            break;     
            
        default:
            oprint_printf("卡 类 型: 未知卡\r\n");
            break;
    }
//    memcpy(buffer,shift_read.gas_record_query.card_id,10);
//    if(strlen(shift_read.gas_record_query.card_id))                              // 无卡加气状态下不需要显示卡号信息
//    {
//        oprint_printf("IC 卡 号: %s\r\n",shift_read.gas_record_query.card_id);
//    }
    itoa(buffer,shift_read.gas_record_query.card_id,10);                         ///  ss190306
    if(strlen(buffer))                                                               // 无卡加气状态下不需要显示卡号信息
    {
        oprint_printf("IC 卡 号: %s\r\n",buffer);
        itoa(buffer,shift_read.gas_record_query.card_id_js,10);                     
        oprint_printf("IC 卡 号: %s(J)\r\n", buffer); 
    }
    
 if(GREY_LUCK_SUCC == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x03))
    {
        if(GREY_GAS_LUCK_SUCC == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x0C))             // 加气记录   加气过程中再次读取灰锁状态  ss190215
        {
            oprint_printf("置灰状态: 置灰成功 (Y)\r\n" );
        }
        else if(GREY_GAS_LUCK_FAILL == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x0C))             // 加气记录   加气过程中再次读取灰锁状态
                oprint_printf("置灰状态: 置灰成功 (N)\r\n" );
            else 
                oprint_printf("置灰状态: 置灰成功\r\n" );
    }
    else  
        if(GREY_LUCK_FAILL == (shift_read.gas_record_query.grey_lock_inif.grey_status & 0x03))
            oprint_printf("置灰状态: 置灰失败 \r\n" );
        else 
            oprint_printf("置灰状态: 未执行置灰操作 \r\n" );
    
    memcpy(buffer,shift_read.gas_record_query.grey_lock_inif.time,6);
    oprint_printf("置灰日期: 20%02d年%02d月%02d日\r\n",buffer[0],buffer[1],buffer[2]);
    oprint_printf("置灰时间: %02d时%02d分%02d秒\r\n",buffer[3],buffer[4],buffer[5]);
    oprint_printf("卡前余额: %.02f元\r\n", shift_read.gas_record_query.grey_lock_inif.cur_money);
    switch(shift_read.gas_record_query.grey_lock_inif.grey_status & 0xF0)
    {
        case GAS_START_FIX_M: 
            oprint_printf("加气方式: 定额加气\r\n");
            break;
        case GAS_START_FIX_V:
            oprint_printf("加气方式: 定量加气\r\n");
            break;
        case GAS_START_MORMAL:
            oprint_printf("加气方式: 正常加气\r\n");
            break;
            
        default:
            oprint_printf("加气方式: 非正常加气\r\n");
            break;
            
    }
    if(GAS_START_SEND_SUCC == (GAS_START_SEND_SUCC &shift_read.gas_record_query.gas_process))   //ss190215
    {
        oprint_printf("预冷开始: 发送成功\r\n");
    }
    else
        oprint_printf("预冷开始: 发送失败\r\n");
    
    if(GAS_PRECOOL_SUCC == shift_read.gas_record_query.gas_precool)                             //ss190215
    { 
        oprint_printf("预冷状态: 预冷成功\r\n");
    }
    else
        oprint_printf("预冷状态: 预冷失败\r\n");
    switch(shift_read.gas_record_query.gas_stop_way)
    {
        case COMMUN_TIIMOUT:
            oprint_printf("停止方式: 板间通信超时(E1)\r\n");
            break;
        case FLOWMETER_ERR:
            oprint_printf("停止方式:流量计通信错误(E3)\r\n");
            break;
        case PRECOOL_ERR:
            oprint_printf("停止方式:预冷超时(E4)\r\n");
            break;    
        case PRESSURE_ERR:
            oprint_printf("停止方式: 压力异常(E5)\r\n");
            break;     
        case VELOCITY_HIGH:
            oprint_printf("停止方式: 超出最大流速(E6)\r\n");
            break;    
        case VELOCIIY_LOW:
            oprint_printf("停止方式: 流速低暂停(E0)\r\n");
            break;    
        case BACKSTAGE_STOP:
            oprint_printf("停止方式: 后台远程停机(E7)\r\n");
            break;
        case GAS_UNUSUAL:
            oprint_printf("停止方式: 加气异常\r\n");
            break;
        case MONEY_ALL:
            oprint_printf("停止方式: 金额加满(1)\r\n");
            break;    
        case CARD_EXTRACT:
            oprint_printf("停止方式: 卡被拔出\r\n");
            break;     
        case PRESS_STOP:
            oprint_printf("停止方式: 按停止键\r\n");
            break;    
        case TRIPLE_COMMUN_FAILL:
            oprint_printf("停止方式: 三秒无接收数据\r\n");
            break;        
          case SYS_HARD_FAULT:
            oprint_printf("停止方式: 系统硬件异常\r\n");
            break;     
        case SYS_FAULT:
            oprint_printf("停止方式: 索要加气信息失败\r\n");
            break;    
        case CARD_BALANCE_FAILL:
            oprint_printf("停止方式: 卡类型卡余不同\r\n");
            break;  
        default:
             oprint_printf("停止方式: 停止方式异常 \r\n");
            break;
    }
    if( GAS_STOP_SEND_SUCC == (shift_read.gas_record_query.gas_process & GAS_STOP_SEND_SUCC) )
    {
        oprint_printf("加气停止: 发送成功\r\n");
    }
    else 
         oprint_printf("加气停止: 发送失败\r\n");
    oprint_printf("轮询次数: %d 次\r\n", (shift_read.gas_record_query.grey_unlock_inif.grey_status & 0x0F));
    oprint_printf("暂停次数: %d 次\r\n", (shift_read.gas_record_query.gas_process & 0x0F));
    switch(shift_read.gas_record_query.grey_unlock_inif.grey_status & 0xF0)
    { 
        case GREY_ACCOUNTS_FAILL:
            oprint_printf("解灰状态: 扣款未完成\r\n");
            break;
        case GREY_UNLUCK_FAILL:
            oprint_printf("解灰状态: 扣款完成未解灰\r\n");
            break;
        case GREY_UNLUCK_SUCC:
            oprint_printf("解灰状态: 解灰成功\r\n");
            break;    
        case GREY_ACCOUNTS_STATU_FAILL:                                           //ss190306  增加对消费方式异常的处理
            oprint_printf("解灰状态: 消费方式异常未解灰\r\n");
            break;
        case GREY_CARD_CHEKE_FAILL:
            oprint_printf("解灰状态: 卡号错误解灰失败\r\n");
            break;
        default:
            oprint_printf("解灰状态: 解灰失败\r\n");
            break;
        
    }
    
    memcpy(buffer,shift_read.gas_record_query.grey_unlock_inif.time,6);
    oprint_printf("解灰日期: 20%02d年%02d月%02d日\r\n",buffer[0],buffer[1],buffer[2]);
    oprint_printf("解灰时间: %02d时%02d分%02d秒\r\n",buffer[3],buffer[4],buffer[5]);
    if( GAS_ACCOUNTS_SEND_SUCC == (shift_read.gas_record_query.gas_process & GAS_ACCOUNTS_SEND_SUCC) )
    {
        oprint_printf("扣款信息: 发送成功\r\n");
    }
    else 
         oprint_printf("扣款信息: 发送失败\r\n");
    oprint_printf("消费金额: %.02f元\r\n", shift_read.gas_record_query.grey_unlock_inif.OKgas_money);
    oprint_printf("卡后余额: %.02f元\r\n", shift_read.gas_record_query.grey_unlock_inif.Balance_To);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("******* 此流水号查询结束 *******\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
}
void GasRecordQuery(void)                       // 查询键盘板加气记录信息
{
    UINT32 id; 
    UINT32 MAX_id;
    
    olcd_clearsCreen();                                                // 清空屏幕显示信息
    id = GasRecordMAX();                                               // 最大记录序列号
    if(id == 0)                                                         /// 判断序列号是否正确
    {
        olcm_dispprintf(0,1,"无流水记录！");
        osys_getkey(_KEY_NULL_, 300);
        eVirtualKey = _KEY_VIRTUAL_EV_;
        return;
    }
    MAX_id = id;
    DispRecordInfo(id);                                                // 显示流水信息
    
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
            DispRecordInfo(id);                                                // 显示流水信息
        }
        else  if(_KEY_SW_EV_ == keyv)
        {
            if(++id > MAX_id)
            {
                id = MAX_id;
                continue;
            }
            DispRecordInfo(id);                                                // 显示流水信息
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
    olcm_dispprintf(0,1,"1.正确记录顺序");
    olcm_dispprintf(0,2,"2.正确记录检索");
    olcm_dispprintf(0,3,"3.异常记录顺序");
    olcm_dispprintf(0,4,"4.异常记录检索");
}
UINT32 IndexRecordData(UINT32 id)
{
    UINT32 MAX_id,i; 
    MAX_id = GasRecordMAX();                                               // 最大记录序列号
    if(MAX_id > 100)
        i = MAX_id - 100;
//     MAX_id = (MAX_id % 100)+1;
    for(;i<MAX_id;i++)                                                      //遍历流水号
    {
        ReadRecordInfo(i);                                                  
        if(id == shift_read.gas_record_query.gas_stream)                       
        {
            return i;
        }
    }
    return 0xFFFF0000;
}
void GasRecordQueryIndex(void)                       // 索引查询键盘板加气记录信息
{
    UINT32 MAX_id,id; 
    UINT32 liushuinum = 0;
    UINT8 len, vkey = 0;
    INT8  str[20] = {0};
    olcd_clearsCreen();                                                // 清空屏幕显示信息
    MAX_id = GasRecordMAX();                                               // 最大记录序列号
 //   MAX_id = (MAX_id % 100);
//    MAX_id = id;
    olcm_dispprintf(0,1,"请输入流水号：");
    cursor_x = 0;
    cursor_y = 2;
    vkey = okeyinput_getstr(str,&len ,6,FALSE,FALSE);
    
    if( vkey == _KEY_OK_EV_ && len>0)
   {
        liushuinum= atoi(str);
        id = IndexRecordData(liushuinum);
        if(0xFFFF0000 != id) 
        {
            DispRecordInfo(id);                                                // 显示流水信息
    
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
                    DispRecordInfo(id);                                                // 显示流水信息
                }
                else  if(_KEY_SW_EV_ == keyv)
                {
                    if(++id > MAX_id)
                    {
                        id = MAX_id;
                        continue;
                    }
                    DispRecordInfo(id);                                                // 显示流水信息
                }
                else  if(_KEY_STOP_EV_ == keyv)
                {
        //            oprint_qry_easy_rec();
                    OprintRecordInfo();                                              //打印加气记录信息

                }
            }
            eVirtualKey = _KEY_VIRTUAL_EV_;
         }
         else
         {//没有您输入的流水号记录
             olcd_clearsCreen();
             olcm_dispprintf(0,1,"您输入的流水号");
             olcm_dispprintf(0,2,"无此加气记录");
             olcm_dispprintf(0,3,"或记录已被覆盖");
             osys_getkey(_KEY_NULL_,300);
             eVirtualKey = _KEY_VIRTUAL_EV_;
         }
   }
     eVirtualKey = _KEY_VIRTUAL_EV_;
}

