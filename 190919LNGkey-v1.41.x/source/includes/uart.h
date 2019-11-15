/* 
 * File:   uart.h
 * Author: Administrator
 *
 * Created on 2014骞���, 涓婂崍9:24
 */

#ifndef UART_H
#define	UART_H
#include <plib.h>
//涓插彛閰嶇疆
#ifdef SHOW_INFO
typedef enum {
  UART1 = 0,
  UART2,
  UART3,
  UART4,
  UART5,
  UART6,
  UART_NUMBER_OF_MODULES
} UART_MODULE;
typedef enum {
  UART_DATA_SIZE_8_BITS,
  UART_DATA_SIZE_9_BITS,
  UART_PARITY_ODD,
  UART_PARITY_EVEN,
  UART_PARITY_NONE,
  UART_STOP_BITS_2,
  UART_STOP_BITS_1
} UART_LINE_CONTROL_MODE;
#endif
typedef struct uart_config
{
    UINT32  baud;
    UART_LINE_CONTROL_MODE   d_num;
    UART_LINE_CONTROL_MODE   s_num;
    UART_LINE_CONTROL_MODE   p_type;
}uart_config;
extern void   uart_init(UART_MODULE name, uart_config *config);
extern UINT8  Uart_Send_Data(UART_MODULE name, UINT8 *buffer, UINT8 size);
extern UINT32 Uart_Get_Data(UART_MODULE name, UINT8 *buffer, UINT32 len);
#endif	/* UART_H */

