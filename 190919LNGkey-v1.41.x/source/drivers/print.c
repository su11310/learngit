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
  //0x1c 26:���뺺�ִ�ӡ��ʽ
  //0x1b 56 02:�����߶�������ӡ
  //0x1b 63 00:�ַ���������ķ����ӡ
  sys_uart_send_str(PRINT_PORT,buff,8);
}

void oprint_normal_cmd(void)
{
//  unsigned char cmd[14] = {0x1b, 0x40, 0x1c, 0x26, 0x1b, 0x31, 0x08,
//                           0x1b, 0x70, 0x02, 0x1b, 0x56, 0x02, 0x0D};
   unsigned char cmd[14] = {0x1b, 0x40, 0x1c, 0x26, 0x1b, 0x31, 0x08,
                           0x1b, 0x70, 0x02, 0x1b, 0x63, 0x00, 0x0D};
  //0x1c 26:���뺺�ִ�ӡ��ʽ
  //0x1b 56 02:�����߶�������ӡ
  //0x1b 63 00:�ַ���������ķ����ӡ
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
    oprint_printf("    LNG������ϵͳ����\r\n"); //cur_sysparas
    oprint_normal_cmd();
    oprint_printf("����:%.02f\r\n", cur_sysparas.p_Price);
    oprint_printf("Ԥ���¶�:%.02f\r\n", cur_sysparas.p_Ptemp);
    oprint_printf("Ԥ������:%.02f\r\n", cur_sysparas.p_PGain);
    oprint_printf("Ԥ����ʱ:%.02f\r\n", cur_sysparas.p_PDelay);
    oprint_printf("ͣ������:%.02f\r\n", cur_sysparas.p_EndR);
    oprint_printf("ͣ��ѹ��:%.02f\r\n", cur_sysparas.p_EndP);
    //oprint_printf("pumpƵ��hz:%.02f\r\n", cur_sysparas.p_Price);
}
/*
           UINT32   shift_rec_id;             //�����¼��ˮ��
          UINT8    shift_card[8];            //���鿨��
          UINT16   shift_id;                 //�����
          UINT8    shift_gid;                //ǹ��
          UINT8    shift_op_time[6];         //����ʱ��
          float    shift_s_mount;            //��ʼǹ��
          float    shift_e_mount;            //����ǹ��
          INT8     shift_op_type;             //����
          float    shift_cash;                //IC���˽��
 */
void oprint_operate_shift(void)
{
    oprint_header_cmd();
    oprint_printf("��̨�н���·��һ����վ\r\n");
    oprint_normal_cmd();
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("�����¼��:%ld\r\n",cur_shift_loginfo.shift_rec_id);
    oprint_printf("�����:%d\r\n",cur_shift_loginfo.shift_id);
    oprint_printf("ǹ��:%ld\r\n",cur_shift_loginfo.shift_gid);
    oprint_printf("���鿨��:%s\r\n", cur_shift_loginfo.shift_card); //,cur_shift_sysinfo.shift_card[0]
    oprint_printf("��ʼǹ��:%.02f\r\n",cur_shift_loginfo.shift_s_mount);
    oprint_printf("����ǹ��:%.02f\r\n",cur_shift_loginfo.shift_e_mount);
    //oprint_printf("�ֽ���:%.02f\r\n",cur_shift_sysinfo.shift_cash);
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    oprint_printf("\r\n");
    //oprint_printf("--��̨��xxxx·xxxx����վ--\r\n");
    //oprint_printf("------��ӭ�´ι���------\r\n");

}

