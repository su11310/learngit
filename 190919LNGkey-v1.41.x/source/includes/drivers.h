/* 
 * File:   drivers.h
 * Author: jereh
 *
 * Created on 2014-01-14  08:36
 */

#ifndef DRIVERS_H
#define	DRIVERS_H

#ifdef	__cplusplus
extern "C" {
#endif
    #include "flash.h"


    #define PC485_DIR_OUTPUT()       mPORTBSetBits(BIT_14)
    #define PC485_DIR_INPUT()        mPORTBClearBits(BIT_14)
    #define MODBUS_DIR_OUTPUT()       mPORTBSetBits(BIT_15)
    #define MODBUS_DIR_INPUT()        mPORTBClearBits(BIT_15)
    //#define  LNG_L_SW
#define MO_High              mPORTBSetBits(BIT_9)
#define MO_Low               mPORTBClearBits(BIT_9)
#define MO1_High              mPORTBSetBits(BIT_8)
#define MO1_Low               mPORTBClearBits(BIT_8)
    #define MODBUS_MAX_RESPONSE_LEN		32
    volatile UINT8 _modbus_response_buf[MODBUS_MAX_RESPONSE_LEN];  //
    volatile UINT8 _modbus_response_len;                           //volatile

    void sys_set_tick(UINT32 vset);
    UINT32 sys_get_tick(void);
    void sys_uart_printf(UART_MODULE ch, char *fmt,...);
    void sys_uart_send_str(UART_MODULE ch, UINT8 *buff, UINT32 size);
    void sys_uart_send_char(UART_MODULE ch, UINT8 c);
    void sys_uart_debug_info(void);
    void lcd_key_init(void);
    //void olcd_dispstr(unsigned char x, unsigned char y, unsigned char *str);
    //void olcd_dispstr(unsigned char x, unsigned char y, unsigned char *str, unsigned char len);
    //void olcd_dispstr(INT8 x, INT8 y, UINT8 *str, UINT8 len);
    void olcd_dispstr(INT8 x, INT8 y, UINT8 *str, UINT8 len);
    void olcd_clearsCreen(void);
    void olcm_dispprintf(INT8 x, INT8 y, char *fmt,...);
    void olcd_tip_msg(UINT8 x, UINT8 y, UINT8 id);
void olcd_dispstrhex(INT8 x, INT8 y, UINT8 *str, UINT8 len);
    void odisp_init(void);
    void odisp_init_chk(void);
    void odisp_p(void);
    void odisp_clr(void);
    void odisp_num(float fnum);//void odisp_num(float fnum, BOOL bDisp);
    void odisp_sum(float fsum);//void odisp_sum(float fsum, BOOL bDisp);
    void odisp_price(float fprice, BOOL bDisp);//void odisp_price(UINT32 vprice, BOOL bDisp);
    void odisp_disp( float fsum,float fnum, BOOL bEnd);//void odisp_cal(float fnum, BOOL bInit);
    void odisp_sum2(float fsum);
       void odisp2_disp( float fsum,float fnum, BOOL bEnd);
//    static void odisp_senddispNum(void);
    void dssp();
    void dsspone();
    void   okey_init(void);
    UINT8  okey_read_data(UINT8 addr);
    //void okey_scan(void);
    UINT8  okey_scan(void);
    UINT8  okey_scan_ex(void);
    UINT8  okey_scan_ex_io(void);
    BOOL   okey_timestr(UINT8 * tpstr);

/*-----------------Ê±¼ä----------------------*/
    BOOL  ortcc_start(void);
    BOOL  ortcc_stop(void);
    //UINT8 ortcc_read(UINT8 reg);
    //BOOL  ortcc_write(UINT8 reg, UINT8 wt);
    //BOOL  ortcc_write_time(UINT8* wttime);
    //BOOL  ortcc_read_time(UINT8 *rdtime);
    BOOL  ortcc_read_memory(UINT8 *rdmem,UINT8 addr,  UINT8 len);
    BOOL  ortcc_write_memory(UINT8 *wtmem,UINT8 addr,  UINT8 len);
    BOOL ortcc_set_time(UINT8 *stime);
    BOOL ortcc_read_time(UINT8 *rdtime);

    void  i2c_init(I2C_MODULE name, UINT8 addr, UINT32 freq);
    void  i2c_write(I2C_MODULE name,UINT8 dev_addr, UINT8 reg_addr, UINT8 data);
    UINT8 i2c_read(I2C_MODULE name,UINT8 dev_addr, UINT8 reg_addr);

    //BOOL  o24lcxxx_write_bytes(UINT16 addr, UINT8* wtbuf, UINT8 len);
    //UINT8 o24lcxxx_read_bytes(UINT16 addr, UINT8* rdbuf, UINT8 len);
    UINT8  o24lcxxx_read_bytes_ex(UINT16 addr, UINT8 *buff, UINT8 size);
    UINT8  o24lcxxx_read_bytes(UINT16 addr, UINT8 *buff, UINT8 size);
    UINT8  o24lcxxx_write_bytes(UINT16 addr, UINT8 *buffer, UINT8 size);
    UINT8  o24lcxxx_write_bytes_ex(UINT16 addr, UINT8 *buffer, UINT8 size);

    
    void   onand_init(void);
    UINT16 onand_getID(void);
    BOOL   onand_BlockErase(UINT32 addr);
    UINT32 onand_wtBuff(UINT32 addr, UINT8 *data, UINT32 size);
    UINT32 onand_wtBuff_ex(UINT32 addr, UINT8 *data, UINT32 size);
    UINT32 onand_rdBuff(UINT32 addr, unsigned char *data, UINT32 size);

    void   oprint_init(unsigned long baudrate);
    void   oprint_operate_rec(void);//
    void   oprint_qry_easy_rec(void);//
    void   oprint_operate_shift(void);
    void   oprint_header_cmd(void);
    void   oprint_printf(char *fmt,...);

    void   omodbus_init(unsigned long baudrate);
    BOOL   omobus_init_reg(UINT8 addr, UINT8* nstep);
    BOOL   omodbus_read_auto_buffer(UINT8 addr, UINT8 regnum);
    BOOL   omodbus_read_g_flow(void);

    
    void   opotocol_port_init(unsigned long baudrate);
    void   opotocol_anlysis_pro(void);
    UINT8  ocomm_bcd2dec(unsigned char vbcd);
    void jrm();
    void DisplayClear(void);    //QingLing
    BOOL qzql(void);        //QingLing
#ifdef	__cplusplus
}
#endif

#endif	/* DRIVERS_H */

