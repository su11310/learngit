/* 
 * File:   modbus.c
 * Author: felixluom
 *
 * Created on 2014年2月6日, 上午11:51
 */
#include "../includes/global_def.h"

#define  MODBUS_OK				1
#define  MODBUS_ERR_TIMEOUT                 2
#define  MODBUS_ERR_CRC                     3
#define  MODBUS_ERR				4

#define MODBUS_TIMEOUT_MAX                  1000

//volatile UINT8 _modbus_l_buf[MODBUS_MAX_RESPONSE_LEN];
//volatile UINT8 _modbus_response_l_len;
UINT32		modbus_err_rd_cnt;
UINT32          modbus_chk_cnt ;
UINT8           modbus_err_type ;
UINT16          anlysis_cnt = 0;
UINT8           tick_r = 0;
void __ISR(_UART_1_VECTOR, ipl3) IntUart1Handler(void)
{
        UINT8 u1recv = 0;
	// Is this an RX interrupt?
	if(INTGetFlag(INT_SOURCE_UART_RX(UART1)))
	{
             if(_modbus_response_len >= MODBUS_MAX_RESPONSE_LEN)
             {
                _modbus_response_len = 0;
             }
             _modbus_response_buf[_modbus_response_len++]  = U1RXREG;//UARTGetDataByte(UART1);
             INTClearFlag(INT_SOURCE_UART_RX(UART1));
	}
	//  don't care about TX interrupt
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART1)) )
	{
            INTClearFlag(INT_SOURCE_UART_TX(UART1));
	}
}

UINT16 omodbus_crc16(UINT8 *buf, UINT16 Len)
{
  UINT16 IX, IY, CRC;
  CRC = 0xFFFF;
  if (Len <= 0)    return 0;
  for (IX = 0; IX < Len; IX++)
  {
      CRC = CRC ^ (unsigned int)(buf[IX]);
      for (IY = 0; IY < 8; IY++)
      {
        if ((CRC &1) != 0)
          CRC = (CRC >> 1) ^ 0xA001;
        else
          CRC = CRC >> 1;
      }
  }
  return CRC;
}

void omodbus_sendstr(UINT8 len, UINT8 *buf)
{
  unsigned int n;
  MODBUS_DIR_OUTPUT();//SET_PORT_BIT(PORTB, PB6); //L
  delay_ms(20);
  sys_uart_send_str(MODBUS_PORT, buf, len);//for (n = 0; n < len; n++) omodbus_l_sendchar(*buf++);
  //while( BusyUART1());//for (n = 0; n < 100; n++) asm("nop"); //1000
  MODBUS_DIR_INPUT();//CLR_PORT_BIT(PORTB, PB6);
  delay_ms(20);//delay_ms(1);//100);
  //asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");//__delay_cycles(5);
  //asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}

void omodbus_init(unsigned long baudrate)
{
     PORTSetPinsDigitalOut(IOPORT_B, BIT_15);
    // PC485_DIR_OUTPUT();

     UARTConfigure(MODBUS_PORT, UART_ENABLE_PINS_TX_RX_ONLY);
     UARTSetFifoMode(MODBUS_PORT, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
     UARTSetLineControl(MODBUS_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_EVEN |  UART_STOP_BITS_1);
     //UARTSetLineControl(MODBUS_PORT, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE |  UART_STOP_BITS_1);
     UARTSetDataRate(MODBUS_PORT, GetPeripheralClock(), baudrate);
     UARTEnable(MODBUS_PORT, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX  | UART_TX)); //
     INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_ENABLED);
     //INTEnable(INT_SOURCE_UART_TX(MODBUS_PORT), INT_DISABLED);
}

UINT8 omodbus_read_reg(UINT8 addr ,UINT16 reg_id, UINT8 regnum )
{
  UINT8   _modbus_buf[10]    = {0};
  UINT8    ret_len  = 0 ,ret = 0; //addr = 0 , regcoil  = 0,
  UINT16  crc = 0;
  int	  timeout = MODBUS_TIMEOUT_MAX*2;
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_DISABLED);//关中断
  _modbus_buf[0] = addr ; //247;           //DEFAULT_ADDR;     //247
  _modbus_buf[1] = 0x03;  //regcoil ; //0x03; 		  //写寄存器的功能代码

  _modbus_buf[2] = reg_id >> 8;     //寄存器高位
  _modbus_buf[3] = reg_id & 0xFF;   //寄存器低位

  _modbus_buf[4] = 0;                //number of registers
  _modbus_buf[5] = regnum;		   //2;//regnum;

  crc = omodbus_crc16(_modbus_buf, 6);//FLOW_CRC16//进行CRC校验

  _modbus_buf[6] = (UINT8)(crc &0xFF);//校验值低位
  _modbus_buf[7] = crc >>8;
  ret_len =  3+2*regnum+2; //

  timeout = MODBUS_TIMEOUT_MAX*2;
  _modbus_response_len = 0;
  memset((unsigned char*)_modbus_response_buf,0,sizeof(_modbus_response_buf));
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_ENABLED);//开中断
  //asm("nop");//asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
  omodbus_sendstr(8, _modbus_buf);
  while(timeout--)
  {
       delay_ms(1);
       if(_modbus_response_len >= ret_len)	 break;
  }
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_DISABLED);
  if(timeout <= 0)	return MODBUS_ERR_TIMEOUT;

  if(_modbus_response_buf[0] != addr || _modbus_response_buf[1] != 0x03)//regcoil)
      return MODBUS_ERR;
   crc =omodbus_crc16((unsigned char*)&_modbus_response_buf[0],ret_len-2);
   if(_modbus_response_buf[ret_len-2] != (unsigned char)(crc &0x00FF) || _modbus_response_buf[ret_len-1] != crc >>8 )
   {
            	return  MODBUS_ERR_CRC;
   }
   return MODBUS_OK;
}

UINT8 omodbus_write_reg(UINT8 addr, UINT16 reg_id,UINT8 modbus_coil, UINT16 v_value)
{
  UINT8    ret, _modbus_buf[10]    = {0};
  UINT16   crc = 0;
  UINT32   timeout = 0;
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_DISABLED);//关中断
  _modbus_buf[0] = addr;//modbus_addr;
  _modbus_buf[1] = modbus_coil;//0x05;//RM:0x05  E+H:0x10 //modbus_coil;
  _modbus_buf[2] = reg_id >> 8;     //寄存器高位
  _modbus_buf[3] = reg_id & 0xFF;   //寄存器低位

  _modbus_buf[4] = v_value >> 8; 	//值高位
  _modbus_buf[5] = v_value &0x00FF; //值低位

  crc = omodbus_crc16(_modbus_buf, 6);//FLOW_CRC16//进行CRC校验

  _modbus_buf[6] = (unsigned char)(crc &0x00FF);//校验值低位
  _modbus_buf[7] = crc >>8;
  /*
return: F7   06    08 13   00 01   AF 39
       addr  code   reg     val    crc
PC_SendStr(CNGMASS_TRANS,index);
  */
  _modbus_response_len = 0;
  memset((unsigned char*)_modbus_response_buf,0,sizeof(_modbus_response_buf));
  timeout = MODBUS_TIMEOUT_MAX*2;
//  memset((unsigned char*)_modbus_l_buf,0,sizeof(_modbus_l_buf));
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_ENABLED);//开中断
  //asm("nop");//asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
  omodbus_sendstr(8, _modbus_buf);
  while(timeout--)
  {
       delay_ms(1);
       if(_modbus_response_len >= 8)	 break;
  }
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_DISABLED);//关中断
  ret = MODBUS_OK;
  if(timeout <=0 ) return MODBUS_ERR_TIMEOUT;
  if(_modbus_response_buf[0] != addr || _modbus_response_buf[1] != modbus_coil)   return MODBUS_ERR;
  crc =omodbus_crc16((unsigned char*)&_modbus_response_buf[0],6);
  if(_modbus_response_buf[6] != (unsigned char)(crc &0x00FF) || _modbus_response_buf[7] != crc >>8 ) return MODBUS_ERR_CRC;
  return MODBUS_OK;
}


UINT8 omodbus_write_reg_float(UINT8 addr, UINT16 reg_id, float vfwt)
{
//	unsigned char _modbus_buf[14]    = {0xF7,0x10,0x14,0x11,0x00, 0x02,0x04,0x00,0x00,0x40,0xD0,0xE1,0xB8};
  un_float unvfrd;
  UINT8    ret, _modbus_buf[13]    = {0};
  UINT16   crc = 0;
  UINT32   timeout = 0;
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_DISABLED);//关中断
  unvfrd.dt_float  = vfwt;
  _modbus_buf[0] = addr;
  _modbus_buf[1] = 0x05;
  _modbus_buf[2] = reg_id >> 8;     //寄存器高位
  _modbus_buf[3] = reg_id & 0xFF;   //寄存器低位
  _modbus_buf[4] = 0;
  _modbus_buf[5] = 2;
  _modbus_buf[6] = 4;
  _modbus_buf[7] =  unvfrd.dt_uc[1] ;
  _modbus_buf[8] =  unvfrd.dt_uc[0] ;
  _modbus_buf[9] =  unvfrd.dt_uc[3] ;
  _modbus_buf[10] = unvfrd.dt_uc[2] ;

  crc = omodbus_crc16(_modbus_buf, 11);//FLOW_CRC16//进行CRC校验

  _modbus_buf[11] = (unsigned char)(crc &0x00FF);//校验值低位
  _modbus_buf[12] = crc >>8;
  /*
return: F7   06    08 13   00 01   AF 39
       addr  code   reg     val    crc
PC_SendStr(CNGMASS_TRANS,index);
  */


  _modbus_response_len = 0;
  memset((unsigned char*)_modbus_response_buf,0,sizeof(_modbus_response_buf));
  timeout = MODBUS_TIMEOUT_MAX*2;
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_ENABLED);//开中断
  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
  omodbus_sendstr(13, _modbus_buf);
  while(timeout--)
  {
//	osys_opower_chk(); //掉电检测
	if(_modbus_response_len >= 8) break;
	delay_ms(1);
  }
  INTEnable(INT_SOURCE_UART_RX(MODBUS_PORT), INT_DISABLED);
  ret = MODBUS_OK;
  if(timeout <= 0) return MODBUS_ERR_TIMEOUT;
  if(_modbus_response_buf[0] != addr || _modbus_response_buf[1] != 0x05) return MODBUS_ERR;
  crc =omodbus_crc16((unsigned char*)&_modbus_response_buf[0],6);
  if(_modbus_response_buf[6] != (unsigned char)(crc &0x00FF) || _modbus_response_buf[7] != crc >>8 )
		return MODBUS_ERR_CRC;
  return MODBUS_OK;
}

BOOL omodbus_write_float(UINT8 addr, UINT16 reg, float vfrd)
{
	BOOL           ret = FALSE;
	if(omodbus_write_reg_float(addr, reg,vfrd) == MODBUS_OK)
	{
		ret = TRUE;
	}
	return ret;
}

BOOL omodbus_read_float(UINT8 addr, UINT16 reg, float* vfrd)
{
	un_float       unvfrd;
	unvfrd.dt_float  = 0.0;
	if(omodbus_read_reg(addr, reg, 2) == MODBUS_OK)
	{
            unvfrd.dt_uc[0] = _modbus_response_buf[4];
            unvfrd.dt_uc[1] = _modbus_response_buf[3];
            unvfrd.dt_uc[2] = _modbus_response_buf[6];
            unvfrd.dt_uc[3] = _modbus_response_buf[5];
            *vfrd = unvfrd.dt_float;
	    return TRUE;
	}
	return FALSE;
}

BOOL omodbus_read_int_ex(UINT8 addr, UINT16 reg, UINT8* vrd)
{
	BOOL	ret = FALSE;
	if(omodbus_read_reg(addr, reg,1) == MODBUS_OK)
	{
		vrd[0] = _modbus_response_buf[3];
		vrd[1] = _modbus_response_buf[4];
		ret = TRUE;
	}
	return ret;
}
BOOL omodbus_read_int(UINT8 addr, UINT16 reg, UINT16* vrd)
{
	UINT16    temp = 0;
	BOOL	  ret;
	ret  = FALSE;
	if(omodbus_read_reg(addr, reg,1) == MODBUS_OK)
	{
		temp  = _modbus_response_buf[3];
		temp  = temp*0x100;
		*vrd  = temp + _modbus_response_buf[4];
		ret = TRUE;
	}
	return ret;
}


BOOL omodbus_clrtotalreg(UINT8 addr)
{
	BOOL    ret = TRUE;
	float   vfrd = 0;
	if(omodbus_write_reg(addr, 55, 0x05, 0xFF00) == MODBUS_OK)
	{
		delay_ms(100);//	ocomm_delay_ms(10);
		if(omodbus_read_float(addr, 258, &vfrd))
		{
			if(vfrd <0.01 ) return TRUE;
		}
	}
	return FALSE;
}

BOOL omodbus_write_multi_reg(UINT8 addr, UINT16 regaddr, UINT16 reg)
{
	BOOL ret = FALSE;
	//OS_DISABLE_KEYSCAN();
	if(omodbus_write_reg(addr,regaddr,6,reg) == MODBUS_OK) ret = TRUE;
	//OS_ENABLE_KEYSCAN();
	return ret;
}
BOOL omodbus_read_auto_buffer(UINT8 addr, UINT8 regnum)
{
        un_float  unvfrd;
        //oprint_printf("omodbus_read_reg\r\n");
        modbus_err_type = omodbus_read_reg(addr,782,regnum*2);
        if( modbus_err_type == MODBUS_OK){
            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[3];
            unvfrd.dt_uc[0] = _modbus_response_buf[4];
            unvfrd.dt_uc[3] = _modbus_response_buf[5];
            unvfrd.dt_uc[2] = _modbus_response_buf[6];
            if(addr == MODBUS_LNG_L_ADDR)
            {
                cur_lngrate = unvfrd.dt_float;                //1.流速  //sys_get_float
                cur_lngrate = sys_get_float(cur_lngrate);
            }
            else //if(addr == MODBUS_LNG_C_ADDR)
            {
                cur_cngrate = unvfrd.dt_float;  //流速  //sys_get_float
                cur_cngrate = sys_get_float(cur_cngrate);
            }

            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[7];
            unvfrd.dt_uc[0] = _modbus_response_buf[8];
            unvfrd.dt_uc[3] = _modbus_response_buf[9];
            unvfrd.dt_uc[2] = _modbus_response_buf[10];
            if(addr == MODBUS_LNG_L_ADDR)
            {
                cur_lngnum = unvfrd.dt_float;                   //2. 流量
                cur_lngnum = sys_get_float(cur_lngnum);
            }
            else if(addr == MODBUS_LNG_C_ADDR)
            {
                cur_cngnum = unvfrd.dt_float;  //流速  //sys_get_float
                cur_cngnum = sys_get_float(cur_cngnum);
            }

            unvfrd.dt_float  = 0.0;                    //3.温度
            unvfrd.dt_uc[1] = _modbus_response_buf[11];
            unvfrd.dt_uc[0] = _modbus_response_buf[12];
            unvfrd.dt_uc[3] = _modbus_response_buf[13];
            unvfrd.dt_uc[2] = _modbus_response_buf[14];
            if(addr == MODBUS_LNG_L_ADDR)
            {
                cur_lngtemp = unvfrd.dt_float;
                cur_lngtemp = sys_get_float(cur_lngtemp);
            }
            else if(addr == MODBUS_LNG_C_ADDR)
            {
               cur_cngtemp = unvfrd.dt_float;
               cur_cngtemp = sys_get_float(cur_cngtemp);
            }                                                //4.增益
            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[15];
            unvfrd.dt_uc[0] = _modbus_response_buf[16];
            unvfrd.dt_uc[3] = _modbus_response_buf[17];
            unvfrd.dt_uc[2] = _modbus_response_buf[18];
            if(addr == MODBUS_LNG_L_ADDR)
            {
                cur_lnggain = unvfrd.dt_float;
                cur_lnggain = sys_get_float(cur_lnggain);
            }
            else if(addr == MODBUS_LNG_C_ADDR)
            {
                cur_cnggain = unvfrd.dt_float;
                cur_cnggain = sys_get_float(cur_cnggain);
               // cur_cngtemp = unvfrd.dt_float;
               // cur_cngtemp = sys_get_float(cur_cngtemp);
            }

            unvfrd.dt_float  = 0.0;                       //5. 密度
            unvfrd.dt_uc[1] = _modbus_response_buf[19];
            unvfrd.dt_uc[0] = _modbus_response_buf[20];
            unvfrd.dt_uc[3] = _modbus_response_buf[21];
            unvfrd.dt_uc[2] = _modbus_response_buf[22];
            if(addr == MODBUS_LNG_L_ADDR)
            {
                cur_lngdensty = unvfrd.dt_float;
                cur_lngdensty = sys_get_float(cur_lngdensty);
            }
            else //if(addr == MODBUS_LNG_C_ADDR)
            {
                cur_cngdensty = unvfrd.dt_float;
                cur_cngdensty = sys_get_float(cur_cngdensty);
            }
            return TRUE;
        }
	return FALSE;
}
BOOL omodbus_read_g_flow(void)
{
     un_float  unvfrd;
     modbus_err_type = omodbus_read_reg(MODBUS_LNG_C_ADDR,782,10);
     if( modbus_err_type == MODBUS_OK)
     {
            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[3];
            unvfrd.dt_uc[0] = _modbus_response_buf[4];
            unvfrd.dt_uc[3] = _modbus_response_buf[5];
            unvfrd.dt_uc[2] = _modbus_response_buf[6];
            cur_cngrate = unvfrd.dt_float;                //1.流速  //sys_get_float
            cur_cngrate = sys_get_float(cur_cngrate);


            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[7];
            unvfrd.dt_uc[0] = _modbus_response_buf[8];
            unvfrd.dt_uc[3] = _modbus_response_buf[9];
            unvfrd.dt_uc[2] = _modbus_response_buf[10];

            cur_cngnum = unvfrd.dt_float;                   //2. 流量
            cur_cngnum = sys_get_float(cur_cngnum);


            unvfrd.dt_float  = 0.0;                    //3.温度
            unvfrd.dt_uc[1] = _modbus_response_buf[11];
            unvfrd.dt_uc[0] = _modbus_response_buf[12];
            unvfrd.dt_uc[3] = _modbus_response_buf[13];
            unvfrd.dt_uc[2] = _modbus_response_buf[14];

            cur_cngtemp = unvfrd.dt_float;
            cur_cngtemp = sys_get_float(cur_cngtemp);

                                                      //4.增益
            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[15];
            unvfrd.dt_uc[0] = _modbus_response_buf[16];
            unvfrd.dt_uc[3] = _modbus_response_buf[17];
            unvfrd.dt_uc[2] = _modbus_response_buf[18];

            cur_cnggain = unvfrd.dt_float;
            cur_cnggain = sys_get_float(cur_cnggain);


            unvfrd.dt_float  = 0.0;                       //5. 密度
            unvfrd.dt_uc[1] = _modbus_response_buf[19];
            unvfrd.dt_uc[0] = _modbus_response_buf[20];
            unvfrd.dt_uc[3] = _modbus_response_buf[21];
            unvfrd.dt_uc[2] = _modbus_response_buf[22];

            cur_cngdensty = unvfrd.dt_float;
            cur_cngdensty = sys_get_float(cur_cngdensty);

            return TRUE;
        }
	return FALSE;
}
BOOL omodbus_read_l_flow(void)
{
     un_float  unvfrd;
     modbus_err_type = omodbus_read_reg(MODBUS_LNG_L_ADDR,782,10);
     if( modbus_err_type == MODBUS_OK)
     {
            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[3];
            unvfrd.dt_uc[0] = _modbus_response_buf[4];
            unvfrd.dt_uc[3] = _modbus_response_buf[5];
            unvfrd.dt_uc[2] = _modbus_response_buf[6];
            cur_lngrate = unvfrd.dt_float;                //1.流速  //sys_get_float
            cur_lngrate = sys_get_float(cur_lngrate);


            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[7];
            unvfrd.dt_uc[0] = _modbus_response_buf[8];
            unvfrd.dt_uc[3] = _modbus_response_buf[9];
            unvfrd.dt_uc[2] = _modbus_response_buf[10];

            cur_lngnum = unvfrd.dt_float;                   //2. 流量
            cur_lngnum = sys_get_float(cur_lngnum);


            unvfrd.dt_float  = 0.0;                    //3.温度
            unvfrd.dt_uc[1] = _modbus_response_buf[11];
            unvfrd.dt_uc[0] = _modbus_response_buf[12];
            unvfrd.dt_uc[3] = _modbus_response_buf[13];
            unvfrd.dt_uc[2] = _modbus_response_buf[14];

            cur_lngtemp = unvfrd.dt_float;
            cur_lngtemp = sys_get_float(cur_lngtemp);

                                                      //4.增益
            unvfrd.dt_float  = 0.0;
            unvfrd.dt_uc[1] = _modbus_response_buf[15];
            unvfrd.dt_uc[0] = _modbus_response_buf[16];
            unvfrd.dt_uc[3] = _modbus_response_buf[17];
            unvfrd.dt_uc[2] = _modbus_response_buf[18];

            cur_lnggain = unvfrd.dt_float;
            cur_lnggain = sys_get_float(cur_lnggain);


            unvfrd.dt_float  = 0.0;                       //5. 密度
            unvfrd.dt_uc[1] = _modbus_response_buf[19];
            unvfrd.dt_uc[0] = _modbus_response_buf[20];
            unvfrd.dt_uc[3] = _modbus_response_buf[21];
            unvfrd.dt_uc[2] = _modbus_response_buf[22];

            cur_lngdensty = unvfrd.dt_float;
            cur_lngdensty = sys_get_float(cur_lngdensty);

            return TRUE;
        }
	return FALSE;
}
#if 0
float omodbus_read_auto_float_value(UINT8 addr, UINT8 id)
{
	un_float  unvfrd;
	//OS_DISABLE_KEYSCAN();
	unvfrd.dt_float  = 0.0;
	unvfrd.dt_uc[0] = _modbus_response_buf[4+id*4];
	unvfrd.dt_uc[1] = _modbus_response_buf[3+id*4];
	unvfrd.dt_uc[2] = _modbus_response_buf[6+id*4];
	unvfrd.dt_uc[3] = _modbus_response_buf[5+id*4];
	//OS_ENABLE_KEYSCAN();
	return 	unvfrd.dt_float;
}
#endif

UINT16 omodbus_read_auto_uint_value(UINT8 sw, UINT8 id)
{
	unsigned int  tmp = 0;;
	//OS_DISABLE_KEYSCAN();
	tmp = _modbus_response_buf[3+id*4];
	tmp *= 0x100;
	tmp += _modbus_response_buf[4+id*4];
	return 	tmp;
}

//const UINT16 _MODBUS_G_AUTO_RM_BUF[]      = {0/*流速*/,2/*总量*/,1/*温度*/,3/*密度*/};
const UINT16 _MODBUS_L_AUTO_RM_BUF[]     = {0/*流速*/,2/*总量*/,1/*温度*/,47/*增益*/,3/*密度*/}; //,3/*密度*/
BOOL omobus_init_reg(UINT8 addr, UINT8* nstep)
{
    UINT8 n = 0;
    //UINT8 reg = 0;
    //BOOL  bret = FALSE;
    for(n=0; n<_MODBUS_L_AUTO_RM_BUF_LEN; n++)
    {
        /*
        if( addr == MODBUS_LNG_L_ADDR)
        {
            reg = _MODBUS_L_AUTO_RM_BUF[n];
        }
        else
        {
            reg = _MODBUS_G_AUTO_RM_BUF[n];
        }*/
        //bret = omodbus_write_multi_reg(addr, 750+n, _MODBUS_L_AUTO_RM_BUF[n]);
        //bret = omodbus_write_multi_reg(addr, 750+n, reg);
        //if( bret == FALSE)
        if( FALSE == omodbus_write_multi_reg(addr, 750+n, _MODBUS_L_AUTO_RM_BUF[n]))
	{
                *nstep = n;
		return FALSE;
        }
    }
    return TRUE;
}