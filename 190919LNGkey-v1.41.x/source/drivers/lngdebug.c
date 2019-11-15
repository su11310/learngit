/*
 * File:  lngdebug.c
 * Author: jereh
 
 * Created on 2014_09_01
 */
#include "../includes/global_def.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
unsigned char infoprint[]="烟台市杰瑞加气机\r\n";
unsigned char infoxs[]="杰瑞---LNG加气机";
unsigned char infolx[]="0000000000\r\n";
unsigned char infott[]="欢迎使用杰瑞LNG加气机\r\n";
void lngdebugmode_init(void)
{
    PORTSetPinsDigitalOut(IOPORT_B, BIT_4 );//调试口电平输出
    PORTSetPinsDigitalIn(IOPORT_B, BIT_3 );//调试口电平输入
    mPORTBSetBits(BIT_4);//置高
}
void debug_uart_init(unsigned long baudrate)
{  
     UARTConfigure(LNGDEBUGM_PORT, UART_ENABLE_PINS_TX_RX_ONLY);
     UARTSetFifoMode(LNGDEBUGM_PORT, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
     UARTSetLineControl(LNGDEBUGM_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE |  UART_STOP_BITS_1);
     UARTSetDataRate(LNGDEBUGM_PORT, GetPeripheralClock(), baudrate);
     UARTEnable(LNGDEBUGM_PORT, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX  | UART_TX)); //
     INTEnable(INT_SOURCE_UART_RX(LNGDEBUGM_PORT), INT_ENABLED);
   
}
void __ISR(_UART_1_VECTOR, ipl3) IntUart1Handler(void)
{
 if(INTGetFlag(INT_SOURCE_UART_RX(LNGDEBUGM_PORT)))
  {
    static UINT8 AisHeadRecved = 0; //头部是否收到
    static BYTE  Ohead[2] = {0, };  //头部
    static UINT8 Sdata_index = 0;
    UINT8 c  = U1RXREG; //UARTGetDataByte(PCTRANS_PORT);
    UINT16 crc_vol;
    UINT8 ii;
  //  SWJSET_VALUE swjset_value;

 if (!AisHeadRecved)  //没有收到"@+枪号"
  {  
      Ohead[0] = Ohead[1];
      Ohead[1] = c;
    if ((Ohead[0] == 0xAA) && (Ohead[1] == 0x55))
      {
          AisHeadRecved = 1;
          Ohead[0] = 0;
          Ohead[1] = 0;
         Sdata_index = 0; //接收指针复位
       }
    }//end of 头部
  else  //收到头部
    {       AgComIn[Sdata_index++] = c;
       if ((AgComIn[Sdata_index-1] == '\r')&& (Sdata_index+3 == AgComIn[0] ))//命令、长度接收完毕13
          {
             crc_vol =omodbus_crc16((unsigned char*)&AgComIn[0],(Sdata_index-3));//gcomInbufleng含校验码，减掉2
                 if((AgComIn[Sdata_index-2] == (unsigned char)(crc_vol &0x00FF)) || (AgComIn[Sdata_index -3] ==(unsigned char)(crc_vol>>8))  )
                 {
                         Rec_debug_order = AgComIn[2]; //功能码
                         AisHeadRecved = 0; //重新搜索头部
                         Rec_debug_ok = 1; //接收到完整信息
                         /*
                         swjset_value.str[0] = AgComIn[3];
                         swjset_value.str[1] = AgComIn[4];
                         swjset_value.str[2] = AgComIn[5];
                         swjset_value.str[3] = AgComIn[6];
                         */
                         if(Rec_debug_order >= 9)
                         {
                            memcpy(swjset_value.str, &AgComIn[3], 4);
                         //   SetValue = swjset_value.value;
                         }
                         else
                         {
                              swjset_value.value = 0;
                         //   memcpy(swjset_value.str, 0, 4);
                              memset(swjset_value.str, 0, 4);
                         }
                         subfunc = AgComIn[6];
                 }
                 else //校验错误
                 {
                     for(ii=0;ii<32;ii++)
                           {
                               AgComIn[ii] = 0;
                           }
                 }
   }  //end of '\r'


}  //end of else

 INTClearFlag(INT_SOURCE_UART_RX(LNGDEBUGM_PORT));

}  //end of RX_INT
}
//UINT8 Hard_Info[40];
//UINT8 Contact_Info[16];
//UINT8 Xs_Info[16];
BOOL Get_info_xs(void)
{
    UINT8 k = 100;
    UINT8 psws[22],info_len;
    int y;
    while(k)
    {
        k--;
        if(1==o24lcxxx_read_bytes_ex(info_xs,&info_len,1))
        {
            if((info_len<=20)&&(info_len>0))
            {
            if(info_len==o24lcxxx_read_bytes_ex(info_xs+1,(UINT8*)psws,info_len))
           {
                memcpy(Xs_Info,psws,info_len);
                return TRUE;
              }
         else
        return FALSE;
            }
            else
        return FALSE;
        }
         else
        return FALSE;
    }
 }
BOOL Get_info_hard(void)
{
UINT8 k = 100;
    UINT8 psws[43],info_len;
    int y;

    while(k)
    {
        k--;
        if(1==o24lcxxx_read_bytes_ex(info_hard,&info_len,1))
        {
            if((info_len<=42)&&(info_len>0))
            {
            if(info_len==o24lcxxx_read_bytes_ex(info_hard+1,(UINT8*)psws,info_len))
           {
                memcpy(Hard_Info,psws,info_len);
                return TRUE;
              }
         else
        return FALSE;
            }
            else
        return FALSE;
        }
         else
        return FALSE;
    }
 }
BOOL Get_info_Contact(void)
{
    UINT8 k = 100;
    UINT8 psws[43];
    UINT8 info_len;

    while(k)
    {
        k--;
        if(1==o24lcxxx_read_bytes_ex(info_contact,&info_len,1))
        {
            if((info_len<=42)&&(info_len>0))
            {
            if(info_len==o24lcxxx_read_bytes_ex(info_contact+1,(UINT8*)psws,info_len))
           {
                memcpy(Contact_Info,psws,info_len);
                return TRUE;
              }
         else
        return FALSE;
            }
            else
        return FALSE;
        }
         else
        return FALSE;
    }
 }
BOOL Get_info_print(void)
{
UINT8 k = 100;
    UINT8 psws[43],info_len;
    int y;

    while(k)
    {
        k--;
        if(1==o24lcxxx_read_bytes_ex(info_print,&info_len,1))
        {
            if((info_len<=42)&&(info_len>0))
            {
            if(info_len==o24lcxxx_read_bytes_ex(info_print+1,(UINT8*)psws,info_len))
           {
                memcpy(Print_Info,psws,info_len);
                return TRUE;
              }
         else
        return FALSE;
            }
            else
        return FALSE;
        }
         else
        return FALSE;
    }
 }
#if 1
UINT8 Save_info_print(UINT8 *info,UINT8 *des,UINT16 addr,UINT8 len)
{  UINT8 K = 100;
    UINT8 pswread[43],psws[43];
    psws[0]=len+2;
       memcpy(&psws[1],info,len);
        memcpy(&psws[len+1],"\r",1);
        memcpy(&psws[len+2],"\n",1);
         int y;
    while(K)
      {  K--;
        if((len+3)==o24lcxxx_write_bytes_ex(addr,(UINT8*)psws,len+3))
          {   delay_ms(100);
              o24lcxxx_read_bytes_ex(addr, (UINT8*)pswread, len+3);
              y=memcmp(psws,pswread,len+3);
              if(memcmp(psws,pswread,len+3)==0)
                  {
                  memcpy(des,&psws[1],len+2);
                    return 1;
                    }
             }
         else
             return 0;

     }
}
UINT8 Save_info_xs(UINT8 *info,UINT8 *des,UINT16 addr,UINT8 len)
{  UINT8 K = 100;
    UINT8 pswread[43],psws[43];
    psws[0]=len;
       memcpy(&psws[1],info,len);
      int y;
    while(K)
      {  K--;
        if((len+1)==o24lcxxx_write_bytes_ex(addr,(UINT8*)psws,len+1))
          {   delay_ms(100);
              o24lcxxx_read_bytes_ex(addr, (UINT8*)pswread, len+1);
              y=memcmp(psws,pswread,len+1);
              if(memcmp(psws,pswread,len+1)==0)
                  {
                  memcpy(des,&psws[1],len);
                    return 1;
                    }
             }
         else
             return 0;

     }
}
#endif
UINT8 Clr_info_xs()
{  UINT8 K = 100;
    UINT8 psws[43];
    memset(&psws[0],0x00,17);
 //      psws[0]=16;
 //      memcpy(&psws[1],infoxs,16);
       if((17)!=o24lcxxx_write_bytes_ex(info_xs,(UINT8*)psws,17))
       {
           return 0;
       }
       memcpy(&Xs_Info[0],&psws[0],16);

       memset(&psws[0],0x00,info_contact_len);
//       psws[0]=sizeof(infolx);
 //      memcpy(&psws[1],infolx,sizeof(infolx));
       if(info_contact_len!=o24lcxxx_write_bytes_ex(info_contact,(UINT8*)psws,info_contact_len))
       {
           return 0;
       }
       memcpy(&Contact_Info[0],&psws[0],16);

       memset(&psws[0],0x00,info_hard_len);
 //      psws[0]=sizeof(infott);
 //      memcpy(&psws[1],infott,sizeof(infott));
       if(info_hard_len!=o24lcxxx_write_bytes_ex(info_hard,(UINT8*)psws,info_hard_len))
       {
           return 0;
       }
       memcpy(&Hard_Info[0],&psws[0],sizeof(infott));

       memset(&psws[0],0x00,info_print_len);
  //     psws[0]=sizeof(infoprint);
  //     memcpy(&psws[1],infoprint,sizeof(infoprint));
       if(info_print_len!=o24lcxxx_write_bytes_ex(info_print,(UINT8*)psws,info_print_len))
       {
           return 0;
       }
        memcpy(&Print_Info[0],&psws[0],sizeof(infoprint));
}

void lngdebug_task(void)
{
   olcd_clearsCreen();
   while(1)
   { 
       olcm_dispprintf(0,1,"    调试模式");
      if( Rec_debug_ok == 1)
      {
        switch(AgComIn[2]) // 功能码
         {
         case 1:
         Save_info_print(&AgComIn[3],&Hard_Info[0],info_hard,AgComIn[0]-9);
         Rec_debug_ok =0;
         memset(AgComIn,0x00,50);
         olcm_dispprintf(0,2,"打印题头存储成功");
         break;
         case 2:
         Save_info_xs(&AgComIn[3],&Xs_Info[0],info_xs,AgComIn[0]-9);
         Rec_debug_ok =0;
         memset(AgComIn,0x00,50);
         olcm_dispprintf(0,2,"显示题头存储成功");
         break;
          case 3:
         Save_info_print(&AgComIn[3],&Print_Info[0],info_print,AgComIn[0]-9);
         Rec_debug_ok =0;
         memset(AgComIn,0x00,50);
         olcm_dispprintf(0,2,"厂名存储成功    ");
         break;
         case 4:
         Save_info_print(&AgComIn[3],&Contact_Info[0],info_contact,AgComIn[0]-9);
         Rec_debug_ok =0;
         memset(AgComIn,0x00,50);
         olcm_dispprintf(0,2,"联系方式存储成功");
         break;
         case 5:    //流量计测试
         {
             Rec_debug_ok =0;
             subfunc = 0;
             memset(AgComIn,0x00,50);
             switch (subfunc)
             {
                 case 0x01: //缓冲测试
                 {
                     if(TRUE != Buff_modbus(1))  //液相
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                     olcm_dispprintf(0,1,"    液  相");
                                   olcm_dispprintf(0,2,"液相写缓冲失败");
                               }
                     else
                     {       olcm_dispprintf(0,1,"    液  相");
                             olcm_dispprintf(0,2,"液相写缓冲成功");
                     }
                    if(TRUE != Buff_modbus(2))  //液相
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                     olcm_dispprintf(0,1,"    气  相");
                                   olcm_dispprintf(0,2,"气相写缓冲失败");
                               }
                     else
                     {       olcm_dispprintf(0,1,"    气  相");
                             olcm_dispprintf(0,2,"气相写缓冲成功");
                     }


                 }break;
                 case 0x02: //清零测试
                 {
                            if(TRUE != Clear_modbus(1))  //液相
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                  olcm_dispprintf(0,1,"    液  相");
                                  olcm_dispprintf(0,2,"清零失败");
                               }
                            else
                            {  olcm_dispprintf(0,1,"    液  相");
                             olcm_dispprintf(0,2,"清零成功");
                            }
                      if(TRUE != Clear_modbus(2))  //气相
                               {
                                   SOEACTION1(MODBUS_ERR,eCurRunState);//超时等待要长一些
                                  olcm_dispprintf(0,1,"    气  相");
                                  olcm_dispprintf(0,2,"清零失败");
                               }
                            else
                            {  olcm_dispprintf(0,1,"    气  相");
                             olcm_dispprintf(0,2,"清零成功");
                            }


                 }break;
                 default:break;
             }
         }break;
         case 6:    //电磁阀开启测试
         {
             Rec_debug_ok =0;
             subfunc = 0;
             memset(AgComIn,0x00,50);
             switch (subfunc)
             {
                 case 0x01: //EH测试
                 {

                 }break;
                 case 0x02: //EL测试
                 {

                 }break;
                 case 0x03: //EM测试
                 {

                 }break;
                 case 0x04: //PLC1测试
                 {

                 }break;
                 case 0x05: //PLC2测试
                 {

                 }break;
                 default:break;
             }
         }break;
         case 7:    //泵联动测试
         {
            Rec_debug_ok =0;
            subfunc = 0;
            memset(AgComIn,0x00,50);
             switch (subfunc)
             {
                 case 0x01: //停机测试
                 {

                 }break;
                 case 0x02: //预冷测试
                 {

                 }break;
                 case 0x03: //加气测试
                 {

                 }break;
                 case 0x04: //等待测试
                 {

                 }break;
                 default:break;
             }
         }break;
         case 8:    //压力测试,去掉
         {
             Rec_debug_ok =0;
             subfunc = 0;
             memset(AgComIn,0x00,50);
         }break;
         case 9:    //停机流速设置
         {
                Rec_debug_ok =0;

                if( TRUE!= Set_lngEndR( swjset_value.value,4))//
                {
                    //通信异常
                   olcm_dispprintf(0,4,"    设置失败    ");

                   SOEACTION1(PRO422_ERR,eCurRunState);

                 }
                else  {
                    olcm_dispprintf(0,4,"    设置成功    ");
                       }
                memset(AgComIn,0x00,50);
         }break;
         case 0x0A:    //停机压力设置
         {
                Rec_debug_ok =0;
         if( TRUE!= Set_pressure(swjset_value.value,4))//
                {
                    //通信异常
                   olcm_dispprintf(0,4,"    设置失败    ");

                   SOEACTION1(PRO422_ERR,eCurRunState);

                 }
                else  {
                    olcm_dispprintf(0,4,"    设置成功    ");
                       }



                memset(AgComIn,0x00,50);
         }break;
         case 0x0B:    //安全压力设置
         {
                Rec_debug_ok =0;
          //        swjset_value.value
                memset(AgComIn,0x00,50);
         }break;
         default:break;
         }
      }

   }
    
}
