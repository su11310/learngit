#include <plib.h>
#include "../includes/global_def.h"
//#include "hardware.h"
//#include "uart.h"
//#include "print.h"
#define    MAX_BUF_SIZE    256
static UINT8 uart1_index;
static UINT8 uart1_get_index;
static UINT8 uart1_recv[MAX_BUF_SIZE];

static UINT8 uart4_index;
static UINT8 uart4_get_index;
static UINT8 uart4_recv[MAX_BUF_SIZE];
/*********************************************************************************/
/*function: init the uart*/
void uart_init(UART_MODULE name, uart_config *config)
{

             UARTConfigure(name, UART_ENABLE_PINS_TX_RX_ONLY);
             UARTSetFifoMode(name, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
             UARTSetLineControl(name, config->d_num | config->p_type | config->s_num);
             UARTSetDataRate(name, GetPeripheralClock(), config->baud);
             UARTEnable(name, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

             INTDisableInterrupts();
            // Configure UART RX Interrupt
            INTEnable(INT_SOURCE_UART_RX(name), INT_ENABLED);
            INTSetVectorPriority(INT_VECTOR_UART(name), INT_PRIORITY_LEVEL_2);
            INTSetVectorSubPriority(INT_VECTOR_UART(name), INT_SUB_PRIORITY_LEVEL_0);

            // Enable multi-vector interrupts
            INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
            INTEnableInterrupts();
            switch(name)
            {
              //  case UART1:
                //{
              //      uart1_index = 0;
               //     uart1_get_index = 0;
              //      memset(uart1_recv, 0, sizeof(uart1_recv));
            //    }
                case UART4:
                {
                    uart4_index = 0;
                    uart4_get_index = 0;
                    memset(uart1_recv, 0, sizeof(uart4_recv));

                }
            }
}

// *****************************************************************************
// void UARTTxBuffer(char *buffer, UINT32 size)
// *****************************************************************************
UINT8 Uart_Send_Data(UART_MODULE name, UINT8 *buffer, UINT8 size)
{
     UINT8 count = 0;
    while(size)
    {
        while(!UARTTransmitterIsReady(name));
        UARTSendDataByte(name, *buffer);
        buffer++;
        count++;
        size--;
    }
    while(!UARTTransmissionHasCompleted(name));
    return count;
}

UINT32 Uart_Get_Data(UART_MODULE name, UINT8 *buffer, UINT32 len)
{
    UINT32 num_char;
    //UINT8 buf[30];
    switch(name)
    {
      /*  case UART1:
        {
            if(uart1_index > uart1_get_index)
            {
               num_char = uart1_index - uart1_get_index;
               memcpy(buffer, &uart1_recv[uart1_get_index], num_char);
               uart1_get_index += (num_char+1);
            }
            else if(uart1_index < uart1_get_index)
            {
                num_char = MAX_BUF_SIZE - uart1_get_index;
                memcpy(buffer, &uart1_recv[uart1_get_index], num_char);
                memcpy(buffer+num_char, uart1_recv, uart1_index+1);
                num_char += (uart1_index+1);
                uart1_get_index = (uart1_get_index+num_char-1) % MAX_BUF_SIZE;

            }
            else
                num_char = 0;
            break;
        } */
        case UART4:
        {
            if(uart4_index > uart4_get_index)
            {
               num_char = uart4_index - uart4_get_index;
               memcpy(buffer, &uart4_recv[uart4_get_index], num_char);
               uart4_get_index += num_char;
            }
            else if(uart4_index < uart4_get_index)
            {
                num_char = MAX_BUF_SIZE - uart4_get_index;
                memcpy(buffer, &uart4_recv[uart4_get_index], num_char);
                memcpy(buffer+num_char, uart4_recv, uart4_index+1);
                num_char += (uart4_index+1);
                uart4_get_index = (uart4_get_index+num_char-1) % MAX_BUF_SIZE;

            }
            else
                num_char = 0;
        }

    }
#if 0
    sprintf(buf,"\r\nrecv index is %d\r\n", uart4_index);
    print_send(buf, sizeof(buf));
     sprintf(buf,"\r\nrecv get_index is %d\r\n", uart4_get_index);
    print_send(buf, sizeof(buf));
    sprintf(buf,"\r\nrecv num_char is %d\r\n", num_char);
    print_send(buf, sizeof(buf));
#endif
    return num_char;
}
#if 0
//rember overfollow
// UART 1 interrupt handler, set at priority level 2
void __ISR(_UART_1_VECTOR, ipl2) IntUart1Handler(void)
{
	// Is this an RX interrupt?
	if(INTGetFlag(INT_SOURCE_UART_RX(UART1)))
	{
              uart1_recv[uart1_index%MAX_BUF_SIZE]  = UARTGetDataByte(UART1);
              uart1_index++;
               // Clear the RX interrupt Flag
	     INTClearFlag(INT_SOURCE_UART_RX(UART1));
	}

	//  don't care about TX interrupt
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART1)) )
	{
            INTClearFlag(INT_SOURCE_UART_TX(UART1));
	}
}
#endif
// UART 4 interrupt handler, set at priority level 2
void __ISR(_UART_4_VECTOR, ipl2) IntUart4Handler(void)
{
	// Is this an RX interrupt?
	if(INTGetFlag(INT_SOURCE_UART_RX(UART4)))
	{
              uart4_recv[uart4_index%MAX_BUF_SIZE]  = UARTGetDataByte(UART4);
              uart4_index++;
               // Clear the RX interrupt Flag
	     INTClearFlag(INT_SOURCE_UART_RX(UART4));          
	}

	// don't care about TX interrupt
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART4)) )
	{
            INTClearFlag(INT_SOURCE_UART_TX(UART4));
	}
}