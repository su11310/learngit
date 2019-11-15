/*
 * File:   print.c
 * Author: jereh
 *
 * Created on 2014_01_16
 */
#include "../includes/global_def.h"

void oprint_init(unsigned long baudrate)
{
     UARTConfigure(PRINT_PORT, UART_ENABLE_PINS_TX_RX_ONLY);
     UARTSetFifoMode(PRINT_PORT, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
     UARTSetLineControl(PRINT_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE |  UART_STOP_BITS_1);
     UARTSetDataRate(PRINT_PORT, GetPeripheralClock(), baudrate);
     UARTEnable(PRINT_PORT, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX )); //
     //INTEnable(INT_SOURCE_UART_RX(PRINT_PORT), INT_DISABLED);
     //INTEnable(INT_SOURCE_UART_TX(PRINT_PORT), INT_DISABLED);
}

void oprint_header_cmd(void)
{
  UINT8 buff[8] = {0x1c, 0x26, 0x1b, 0x56, 0x02, 0x1b, 0x63, 0x00};
  //0x1c 26:进入汉字打印方式
  //0x1b 56 02:正常高度两倍打印
  //0x1b 63 00:字符从右向左的反向打印
  sys_uart_send_str(PRINT_PORT,buff,8);
}

void oprint_normal_cmd(void)
{
//  unsigned char cmd[14] = {0x1b, 0x40, 0x1c, 0x26, 0x1b, 0x31, 0x08,
//                           0x1b, 0x70, 0x02, 0x1b, 0x56, 0x02, 0x0D};
   unsigned char cmd[14] = {0x1b, 0x40, 0x1c, 0x26, 0x1b, 0x31, 0x08,
                           0x1b, 0x70, 0x02, 0x1b, 0x63, 0x00, 0x0D};
  //0x1c 26:进入汉字打印方式
  //0x1b 56 02:正常高度两倍打印
  //0x1b 63 00:字符从右向左的反向打印
  sys_uart_send_str(PRINT_PORT,cmd,14);
}
void oprint_printf(char *fmt,...)
{
    va_list ap;
    char str[256];
    va_start(ap,fmt);
    vsprintf(str,fmt,ap);
    sys_uart_send_str(PRINT_PORT, str, strlen(str));
    va_end(ap);
}

void oprint_sys_paras(void)
{
    oprint_header_cmd();
    oprint_printf("    LNG加气机系统参数\r\n"); //cur_sysparas
    oprint_normal_cmd();
    oprint_printf("单价:%.02f\r\n", cur_sysparas.p_Price);
    oprint_printf("预冷温度:%.02f\r\n", cur_sysparas.p_Ptemp);
    oprint_printf("预冷增益:%.02f\r\n", cur_sysparas.p_PGain);
    oprint_printf("预冷延时:%.02f\r\n", cur_sysparas.p_PDelay);
    oprint_printf("停机流速:%.02f\r\n", cur_sysparas.p_EndR);
    oprint_printf("停机压力:%.02f\r\n", cur_sysparas.p_EndP);
    //oprint_printf("pump频率hz:%.02f\r\n", cur_sysparas.p_Price);
}
/*
           UINT32   shift_rec_id;             //班组记录流水号
          UINT8    shift_card[8];            //班组卡号
          UINT16   shift_id;                 //班组号
          UINT8    shift_gid;                //枪号
          UINT8    shift_op_time[6];         //操作时间
          float    shift_s_mount;            //开始枪累
          float    shift_e_mount;            //结束枪累
          INT8     shift_op_type;             //类型
          float    shift_cash;                //IC记账金额
 */
void oprint_operate_shift(void)
{
    oprint_header_cmd();
    oprint_printf("烟台市杰瑞路第一加气站\r\n");
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("班组记录号:%ld\r\n",cur_shift_loginfo.shift_rec_id);
    oprint_printf("班组号:%d\r\n",cur_shift_loginfo.shift_id);
    oprint_printf("枪号:%ld\r\n",cur_shift_loginfo.shift_gid);
    oprint_printf("班组卡号:%s\r\n", cur_shift_loginfo.shift_card); //,cur_shift_sysinfo.shift_card[0]
    oprint_printf("开始枪累:%.02f\r\n",cur_shift_loginfo.shift_s_mount);
    oprint_printf("结束枪累:%.02f\r\n",cur_shift_loginfo.shift_e_mount);
    //oprint_printf("现金金额:%.02f\r\n",cur_shift_sysinfo.shift_cash);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    //oprint_printf("--烟台市xxxx路xxxx加气站--\r\n");
    //oprint_printf("------欢迎下次光临------\r\n");

}

