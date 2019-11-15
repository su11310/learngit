/*
 * File:   colck.c
 * Author: jerehjereh
 *
 * Created on 2014_01_16
 */

/***/
#include "../includes/global_def.h"

UINT8 bcd2dec(unsigned char vbcd)
{
    return (((vbcd & 0xf0)>>4)*10 + (vbcd & 0x0f));
}
BOOL checkdate(unsigned char * str)
{
    unsigned char DayOfMon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    unsigned char y,m,d;
    y=str[0];
    m=str[1];
    d=str[2];

    if (((y%4) == 0 &&(y%100 != 0))||(y%400 == 0)) DayOfMon[1]+=1;//年
    if ((m>12)||(m < 1))  return FALSE;//月
    if (d>DayOfMon[m-1])  return FALSE;//日
    return TRUE;
}

BOOL checktime(unsigned char * str)
{
  if(*str++>23 || *str++>=60 || *str++>=60)
    return FALSE;
  return TRUE;
}

char* ltostr (char *str,unsigned long val, unsigned char base)
{
    ldiv_t r;
    r = ldiv (labs(val), base);
    if (r.quot > 0)  str = ltostr (str, r.quot, base);
    *str++ = "0123456789abcdefghijklmnopqrstuvwxyz"[(int)r.rem];
    *str   = '\0';
    return str;
}
unsigned long hex2bcd(unsigned long sdt)
{
  char buf[12];
  memset(buf,0,sizeof(buf));
  ltostr(buf,sdt, 10);
  return strtoul((char*)&buf[0],NULL,16);
}
//Mengfr 20170110
BOOL ortcc_read_time(UINT8 *rdtime)
{
//	INT8 m;
//	m=3;
//        UINT8 rd = 0;
//	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ); 
//	rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)&0x7F;
//        rdtime[5] = bcd2dec(rd);  //秒
//	rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x01)&0x7F;
//        rdtime[4] = bcd2dec(rd);  //分
//	rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x02)&0x3F; //PM
//        rdtime[3] = bcd2dec(rd);  //时
//
//	rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x04)&0x3F;
//        rdtime[2] = bcd2dec(rd);  //日
//	rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x05)&0x1F;
//        rdtime[1] = bcd2dec(rd);  //月
//	rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x06);
//        rdtime[0] = bcd2dec(rd);  //年
//        I2CEnable(CLOCK_BUS, FALSE);
//        return TRUE;
	INT8 m;
        UINT8 rd[7];
	m=3;
	while(m--)//rg180523
	{
		if(m<1)
		return FALSE;
		RTCread_bytes(0x00,&rd[0],7);
		rdtime[5] = bcd2dec((rd[0]) &0x7F);       //sec
		rdtime[4] = bcd2dec((rd[1]) &0x7F);     //min
		rdtime[3] = bcd2dec((rd[2]) &0x3F);     //h

		rdtime[2] = bcd2dec((rd[4]) &0x7F);     //day
		rdtime[1] = bcd2dec((rd[5]) &0x1F);     //mon
		rdtime[0] = bcd2dec((rd[6]));           //year
		if((rdtime[5]<60)&&(rdtime[4]<60)&&(rdtime[3]<24)&&(rdtime[2]>0)&&(rdtime[2]<32)&&(rdtime[1]>0)&&(rdtime[1]<13))
		{
			m=1;
			break;
		}
		delay_ms(200);
	}
	 return TRUE;
}
#if 0
BOOL ortcc_set_time(UINT8 *stime)
{
        UINT8 rd = 0;
        UINT8 wt = 0;
 	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)&0x7F;  //disable
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);

        wt = hex2bcd(stime[5])&0x7F;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, wt);//hex2bcd(stime[5])); //秒
        
        wt = hex2bcd(stime[4])&0x7F; //分
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x01, wt);//分  hex2bcd(stime[4]));//ortcc_write(0x01, ocomm_hex2bcd(stime[5]));
        
        wt = hex2bcd(stime[3])&0x3F;//时 &1F
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x02, wt);//hex2bcd(stime[3]));//ortcc_write(0x02, ocomm_hex2bcd(stime[4]));

        wt = hex2bcd(stime[2])&0x3F;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x04, wt);//hex2bcd(stime[2]));//ortcc_write(0x04, ocomm_hex2bcd(stime[2])); //时分秒
        wt = hex2bcd(stime[1])&0x1F;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x05, wt);//hex2bcd(stime[1]));//ortcc_write(0x05, ocomm_hex2bcd(stime[1]));
        wt = hex2bcd(stime[0])&0xFF;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x06, wt);//hex2bcd(stime[0]));//ortcc_write(0x06, ocomm_hex2bcd(stime[0]));

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x03)|0x08;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x03, rd);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)|0x80;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);
        I2CEnable(CLOCK_BUS, FALSE);
        return TRUE;
}
#endif


#if 0
BOOL ortcc_read_min(UINT8 *rdtime)
{
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
	*rdtime = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x01);
        return TRUE;
}

BOOL ortcc_read_time(UINT8 *rdtime)
{
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
	*rdtime = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00);
        return TRUE;
}
BOOL ortcc_write_time(UINT8* wttime)
{
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, 0x10);
        return TRUE;
}

BOOL ortcc_write(UINT8 reg, UINT8 wt)
{
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
	i2c_write(CLOCK_BUS, CLOCK_ADDR, reg, wt);
        return TRUE;

}

UINT8 ortcc_read(UINT8 reg)
{
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
	return i2c_read(CLOCK_BUS, CLOCK_ADDR, reg);
}

BOOL ortcc_stop(void)
{
        UINT8 rd = 0;
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)&0x7F;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);

}

BOOL ortcc_start(void)
{
        UINT8 rd = 0;
	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)&0x7F;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);
////////////////
        ortcc_write(0x00, 0x11);
        ortcc_write(0x01, 0x11);
        ortcc_write(0x02, 0x11);

        ortcc_write(0x04, 0x27);
        ortcc_write(0x05, 0x01);
        ortcc_write(0x06, 0x14);
////////////////
        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x03)|0x08;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x03, rd);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)|0x80;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);
        //rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x07)&0xF7;
        //i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x07, rd);
        return TRUE;
    
}
#endif

BOOL  ortcc_read_memory(UINT8 *rdmem,UINT8 addr,  UINT8 len)
{
	i2c_init(CLOCK_BUS, CLOCK_MEM_ADDR, CLOCK_CLOCK_FREQ);
	while(len--)
	{
		*rdmem++ = i2c_read(CLOCK_BUS, CLOCK_MEM_ADDR, addr);
	}
	return TRUE;
}

BOOL  ortcc_write_memory(UINT8 *wtmem,UINT8 addr,  UINT8 len)
{
	i2c_init(CLOCK_BUS, CLOCK_MEM_ADDR, CLOCK_CLOCK_FREQ);
	while(len--)
	{
		i2c_write(CLOCK_BUS, CLOCK_MEM_ADDR, addr,*wtmem++);
	}
	return TRUE;
}
BOOL ortcc_set_time(UINT8 *stime)
{
        UINT8 rd = 0;
        UINT8 wt = 0;
 	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)&0x7F;  //disable
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);

        wt = hex2bcd(stime[2])&0x7F;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, wt);//hex2bcd(stime[5])); //秒

        wt = hex2bcd(stime[1])&0x7F; //分
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x01, wt);//分  hex2bcd(stime[4]));//ortcc_write(0x01, ocomm_hex2bcd(stime[5]));

        wt = hex2bcd(stime[0])&0x3F;//时 &1F
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x02, wt);//hex2bcd(stime[3]));//ortcc_write(0x02, ocomm_hex2bcd(stime[4]));

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x03)|0x08;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x03, rd);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)|0x80;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);
        I2CEnable(CLOCK_BUS, FALSE);
        return TRUE;
}
BOOL ortcc_set_date(UINT8 *stime)
{
        UINT8 rd = 0;
        UINT8 wt = 0;
 	i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)&0x7F;  //disable
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);

         wt = hex2bcd(stime[2])&0x3F;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x04, wt);//hex2bcd(stime[2]));//ortcc_write(0x04, ocomm_hex2bcd(stime[2])); //时分秒
        wt = hex2bcd(stime[1])&0x1F;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x05, wt);//hex2bcd(stime[1]));//ortcc_write(0x05, ocomm_hex2bcd(stime[1]));
        wt = hex2bcd(stime[0])&0xFF;
        i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x06, wt);//hex2bcd(stime[0]));//ortcc_write(0x06, ocomm_hex2bcd(stime[0]));

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x03)|0x08;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x03, rd);

        rd = i2c_read(CLOCK_BUS, CLOCK_ADDR, 0x00)|0x80;
	i2c_write(CLOCK_BUS, CLOCK_ADDR, 0x00, rd);
        I2CEnable(CLOCK_BUS, FALSE);
        return TRUE;
}

