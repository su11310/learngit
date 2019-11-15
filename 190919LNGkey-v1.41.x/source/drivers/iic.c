/*
 * File:   main.c
 * Author: jereh
 *
 * Created on 2014_01_14
 */
#include "../includes/global_def.h"
#define  I2C_SEND_LEN   10
#define  I2C_RECV_LEN   10
void i2c_init(I2C_MODULE name, UINT8 addr, UINT32 freq)
{
    I2CSetFrequency(name, GetPeripheralClock(), freq);
    I2CConfigure(name, I2C_STOP_IN_IDLE|I2C_ENABLE_HIGH_SPEED|I2C_ENABLE_SMB_SUPPORT|I2C_ENABLE_SLAVE_CLOCK_STRETCHING);
    I2CSetSlaveAddress(name, addr, 0, I2C_USE_7BIT_ADDRESS);
     // Enable the I2C bus
    I2CEnable(name, TRUE);
}

/*******************************************************************************
  Function:
    void StopTransfer( void )

  Summary:
    Stops a transfer to/from the EEPROM.

  Description:
    This routine Stops a transfer to/from the EEPROM, waiting (in a
    blocking loop) until the Stop condition has completed.

  Precondition:
    The I2C module must have been initialized & a transfer started.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    StopTransfer();
    </code>

  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
  *****************************************************************************/

void StopTransfer( I2C_MODULE name )
{
    I2C_STATUS  status;
    // Send the Stop signal
    I2CStop(name);
    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(name);
    } while ( !(status & I2C_STOP) );
}
/*******************************************************************************
  Function:
    BOOL TransmitOneByte( UINT8 data
  Summary:
    This transmits one byte to the EEPROM.
  Description:
    This transmits one byte to the EEPROM, and reports errors for any bus
    collisions.
  Precondition:
    The transfer must have been previously started.
  Parameters:
    data    - Data byte to transmit
  Returns:
    TRUE    - Data was sent successfully
    FALSE   - A bus collision occured
  Example:
    <code>
    TransmitOneByte(0xAA);
    </code>
  Remarks:
    This is a blocking routine that waits for the transmission to complete.
  *****************************************************************************/

BOOL TransmitOneByte(I2C_MODULE name, UINT8 data )
{
    // Wait for the transmitter to be ready
    while(!I2CTransmitterIsReady(name));
    // Transmit the byte
    if(I2CSendByte(name, data) == I2C_MASTER_BUS_COLLISION)
        return FALSE;
    // Wait for the transmission to finish
    while(!I2CTransmissionHasCompleted(name));
    return TRUE;
}
/*******************************************************************************
  Function:
    BOOL StartTransfer( BOOL restart )
  Summary:
    Starts (or restarts) a transfer to/from the KEY.
  Description:
    This routine starts (or restarts) a transfer to/from the KEY, waiting (in
    a blocking loop) until the start (or re-start) condition has completed.
  Precondition:
    The I2C module must have been initialized.
  Parameters:
    restart - If FALSE, send a "Start" condition
            - If TRUE, send a "Restart" condition
  Returns:
    TRUE    - If successful
    FALSE   - If a collision occured during Start signaling
  Example:
    <code>
    StartTransfer(FALSE);
    </code>
  Remarks:
    This is a blocking routine that waits for the bus to be idle and the Start
    (or Restart) signal to complete.
  *****************************************************************************/
BOOL StartTransfer(I2C_MODULE name, BOOL restart )
{
    I2C_STATUS  status;
    // Send the Start (or Restart) signal
    if(restart)
    {
        I2CRepeatStart(name);
    }
    else
    {
        // Wait for the bus to be idle, then start the
        while( !I2CBusIsIdle(name) );
        if(I2CStart(name) != I2C_SUCCESS)
        {
            //print_send("\r\ni2c start fail\r\n", 18);
            return FALSE;
        }
    }
    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(name);
        //print_send("\r\ni2c wait start\r\n", 18);
    } while ( !(status & I2C_START) );
    return TRUE;
}

void i2c_write(I2C_MODULE name,UINT8 dev_addr, UINT8 reg_addr, UINT8 data)
{
     UINT8  i2c_send_buf[I2C_SEND_LEN];
     int    Index;
     BOOL  Success = TRUE;
     //I2C_7_BIT_ADDRESS   SlaveAddress;
     //I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, addr, I2C_WRITE);

     memset(i2c_send_buf, 0, sizeof(i2c_send_buf));
     i2c_send_buf[0] = dev_addr & 0xFE;//SlaveAddress.byte;// ;0x70;
     i2c_send_buf[1] = reg_addr;
     i2c_send_buf[2] = data;

     // Transmit all data
    Index = 0;
    //print_send("i2c begin\r\n", 11);
    while(!StartTransfer(name,FALSE));
    //print_send("i2c begin2\r\n", 12);
    while( Success && (Index < 3) )
    {
        // Transmit a byte
        //delay_ms(350);
       // print_send("i2c send\r\n", 10);
        if (TransmitOneByte(name, i2c_send_buf[Index]))
        {
            // Advance to the next byte
            // Verify that the byte was acknowledged
            if(I2CByteWasAcknowledged(name))
            {
                //print_send("ack success\r\n", 13);
                Index++;
            }
            else
                 Success = FALSE;
        }
        else
            Success = FALSE;

    }

    // End the transfer (hang here if an error occured)
    StopTransfer(name);
    //print_send("**i2c end\r\n", 11);
    delay_ms(1);
}
UINT8 i2c_read(I2C_MODULE name,UINT8 dev_addr, UINT8 reg_addr)
{
    UINT8               i2c_send_data[I2C_SEND_LEN];
    I2C_7_BIT_ADDRESS   SlaveAddress;
    int                 Index;
    int                 DataSz;
    BOOL                Success = TRUE;
    UINT8               i2cbyte;
    // Read the data back from the device.
    // Initialize the data buffer
    //print_send("read wite1\r\n", 12);
    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, dev_addr, I2C_WRITE);
    memset(i2c_send_data, 0, sizeof(i2c_send_data));
    i2c_send_data[0] =  dev_addr & 0xFE;//SlaveAddress.byte;//0x70;
    i2c_send_data[1] =  reg_addr;
    DataSz = 2;
    // Start the transfer to read the EEPROM.
    //if( !StartTransfer(name,FALSE) )
    //{
    //    while(1);
    //}
    while(!StartTransfer(name,FALSE));
    // Address the device.
    Index = 0;
    while( Success & (Index < DataSz) )
    {   // Transmit a byte
        if (TransmitOneByte(name, i2c_send_data[Index]))
            Index++;
        else
            Success = FALSE;
        // Verify that the byte was acknowledged
        if(I2CByteWasAcknowledged(name))
            Success = TRUE;
        else
            Success = FALSE;

    }
    //print_send("read write2\r\n", 12);
    // if(Success == FALSE)
    //      print_send("read write cmd failed\r\n", 23);
    // Restart and send the internal address to switch to a read transfer
    if(Success)
    {
        // Send a Repeated Started condition
        while(!StartTransfer(name, TRUE) );
        // Transmit the address with the READ bit set
        I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, dev_addr, I2C_READ);
        if (TransmitOneByte(name, 0x01|dev_addr))//SlaveAddress.byte))
        { // Verify that the byte was acknowledged
            if(I2CByteWasAcknowledged(name))
                Success = TRUE;
            else
                Success = FALSE;
        }
        else
               Success = FALSE;
    }
    // Read the data from the desired address
    if(Success)
    {
        if(I2CReceiverEnable(name, TRUE) == I2C_RECEIVE_OVERFLOW)
            Success = FALSE;
        else
        {
            while(!I2CReceivedDataIsAvailable(name));
            i2cbyte = I2CGetByte(name);
        }

    }
    StopTransfer(name);
   // print_send("\r\ni2c read success\r\n", 20);
   // delay_ms(1);//1000wang
    return i2cbyte;
}
//Mengfr 20170110 //修改RTC获取时间方式
UINT8 RTCread_bytes(UINT16 addr, UINT8 *buff, UINT8 size)
{   
    UINT8 ONCE;
    ONCE = size;
    o24lcxxx_init();
    StartI2C2();
    IdleI2C2();

    MasterWriteI2C2(0xDE);
    IdleI2C2();
    while( I2C2STATbits.ACKSTAT );

    //MasterWriteI2C2(addr/0x100);
    //MasterWriteI2C2(addr%0x100);
    MasterWriteI2C2(addr & 0xFF);
    IdleI2C2();
    while( I2C2STATbits.ACKSTAT );

    // Read the data
    RestartI2C2();
    IdleI2C2();

    MasterWriteI2C2(0xDF);
    IdleI2C2();

    while( I2C2STATbits.ACKSTAT );

    while(size)
    {
        if(ONCE != size)
        {
          AckI2C2();
          IdleI2C2();
        }
        *buff = MasterReadI2C2();
        IdleI2C2();

        while( I2C2STATbits.ACKSTAT );

        buff++;
        size--;
    }

    StopI2C2();
    IdleI2C2();
    return TRUE;
}