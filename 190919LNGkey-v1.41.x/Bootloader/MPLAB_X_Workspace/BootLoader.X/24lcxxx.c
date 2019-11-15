/*
 * File:   24lcxxx.c
 * Author: jereh
 *
 * Created on 2014_02_27
 */
//#include "../includes/global_def.h"
#include <p32xxxx.h>
#include <stdlib.h>
#include <plib.h>
#include "Include/24lcxxx.h"

#define EEPROM_BAUD         (400000)
#define EEPROM_WRITE_ADDR   (0xA2)
#define EEPROM_READ_ADDR    (0xA3)
void o24lcxxx_init(UINT pbclk)
{
    UINT32 brg_val;
    brg_val = (pbclk / (2 * EEPROM_BAUD));
    brg_val -= 2;
    OpenI2C2( I2C_EN | I2C_ACK_EN, brg_val );
}
UINT8 o24lcxxx_read(UINT16 addr)
{
    UINT8 data;
    // select the register
    //o24lcxxx_init();
    StartI2C2();
    IdleI2C2();

    MasterWriteI2C2(0xA2);//EEPROM_WRITE_ADDR);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    MasterWriteI2C2(addr/0x100);
    MasterWriteI2C2(addr%0x100);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    // Read the data
    RestartI2C2();
    IdleI2C2();

    MasterWriteI2C2(0xA3);//EEPROM_READ_ADDR);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    data = MasterReadI2C2();
    IdleI2C2();

    StopI2C2();
    IdleI2C2();

    return data;

}


UINT8 o24lcxxx_read_bytes(UINT16 addr, UINT8 *buff, UINT8 size)
{   UINT8 ONCE;
     ONCE = size;
    //o24lcxxx_init();
    StartI2C2();
    IdleI2C2();

    MasterWriteI2C2(EEPROM_WRITE_ADDR);
    IdleI2C2();
    while( I2C2STATbits.ACKSTAT )		;

    MasterWriteI2C2(addr/0x100);
    MasterWriteI2C2(addr%0x100);
    IdleI2C2();
    while( I2C2STATbits.ACKSTAT )		;

    // Read the data
    RestartI2C2();
    IdleI2C2();

    MasterWriteI2C2(EEPROM_READ_ADDR);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    while(size)
    {
        if(ONCE != size)
        {
          AckI2C2();
          IdleI2C2();
        }
        *buff = MasterReadI2C2();
        IdleI2C2();

	while( I2C2STATbits.ACKSTAT ) ;

        buff++;
        size--;
    }

    StopI2C2();
    IdleI2C2();
    return TRUE;
}

#if 0
UINT8 o24lcxxx_read_bytes(UINT16 addr, UINT8 *buff, UINT8 size)
{
    o24lcxxx_init();
    StartI2C2();
    IdleI2C2();

    MasterWriteI2C2(EEPROM_WRITE_ADDR);
    IdleI2C2();
    while( I2C2STATbits.ACKSTAT )		;

    MasterWriteI2C2(addr/0x100);
    MasterWriteI2C2(addr%0x100);
    IdleI2C2();
    while( I2C2STATbits.ACKSTAT )		;

    // Read the data
    RestartI2C2();
    IdleI2C2();

    MasterWriteI2C2(EEPROM_READ_ADDR);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    while(size)
    {
        AckI2C2();
        IdleI2C2();
        *buff = MasterReadI2C2();
        IdleI2C2();

	while( I2C2STATbits.ACKSTAT )
		    ;

        buff++;
        size--;
    }
    StopI2C2();
    IdleI2C2();
    return TRUE;
}
#endif
UINT8 o24lcxxx_read_bytes_ex(UINT16 addr, UINT8 *buff, UINT8 size)
{
#if 0
    UINT8 ret = 0;
    while(size--)
    {
        *buff++ == o24lcxxx_read(addr++);
        ret++;
        delay_ms(20);
    }
    return ret;
#else
    o24lcxxx_read_bytes(addr, buff, size);
    return size;
#endif
}
inline void AckPolling(void)
{
    while(1)
    {
        StartI2C2();
        IdleI2C2();

        MasterWriteI2C2(EEPROM_WRITE_ADDR);
        IdleI2C2();

	if( !I2C2STATbits.ACKSTAT )
		     break;

        StopI2C2();
        IdleI2C2();
    }

    StopI2C2();
    IdleI2C2();
}



UINT8 o24lcxxx_write(UINT16 addr, UINT8 data)
{
    //o24lcxxx_init();
    StartI2C2();
    IdleI2C2();

    MasterWriteI2C2(EEPROM_WRITE_ADDR);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    MasterWriteI2C2(addr/0x100);
    MasterWriteI2C2(addr%0x100);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;

    MasterWriteI2C2(data);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT )		;
    StopI2C2();
    IdleI2C2();

    AckPolling();
    return TRUE;
}

UINT8 o24lcxxx_write_bytes(UINT16 addr, UINT8 *buffer, UINT8 size)
{
    UINT8 bytes_written;

    bytes_written = 0;
    //o24lcxxx_init();
    StartI2C2();
    IdleI2C2();

    MasterWriteI2C2(EEPROM_WRITE_ADDR);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT );
    MasterWriteI2C2(addr/0x100);
    MasterWriteI2C2(addr%0x100);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT );

    do
    {
        MasterWriteI2C2(*buffer);
        IdleI2C2();
	    while( I2C2STATbits.ACKSTAT );
        addr++;
        buffer++;
        size--;
        bytes_written++;

    }while((addr & 0x07) && (size));
    StopI2C2();
    IdleI2C2();
    AckPolling();//EEPROM_LC01HWAcknowledgePolling();
    return bytes_written;
}
void delay_ms(UINT32 ms)  //1ms约为 ms/10
{
    UINT32 i;
    UINT32 j;
    for(j =0; j < ms; j++)
    {
        for(i = 0; i<800; i++) //1ms
        {
            __asm__ __volatile__("NOP");
        }
    }
}
UINT8 o24lcxxx_write_bytes_ex(UINT16 addr, UINT8 *buffer, UINT8 size)
{
    UINT8 ret = 0;
    while(size--)
    {
        o24lcxxx_write(addr++, *buffer++);
        ret++;
        delay_ms(5);
    }
    return ret;
}