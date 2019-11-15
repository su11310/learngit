/*
 * File:   clock.h
 * Author: wangzw
 *
 * Created on 2014-04-11
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CLOCK_BUS            		I2C2
#define CLOCK_ADDR           		0xDE
#define CLOCK_MEM_ADDR           	0xAE
#define CLOCK_CLOCK_FREQ     		5000
        UINT32 Carcheck_tick;
        UINT32 SysrunTick;
        UINT32 Runled_tick;
        UINT32 Newdisp_tick2;
        BOOL Runled;
        UINT32 ReadTemp_Tick;   //Mengfr 20150831
        
        
        void runled_fresh(void);
       // void i2c_init(I2C_MODULE name, UINT8 addr, UINT32 freq);



#endif	/* CLOCK_H */





