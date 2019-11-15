/*
 * File:   lngdebug.h
 * Author: jereh
 *
 * Created on 2014-09-01
 */

#ifndef LNGDEBNG_H
#define	LNGDEBNG_H
UINT8 Print_Info[40];
UINT8 Hard_Info[40];
UINT8 Contact_Info[16];
UINT8 Xs_Info[16];

BYTE AgComIn[50];
 UINT8 Rec_debug_ok;
 UINT8 Rec_debug_order;
 UINT8 subfunc;

union SWJSET_VALUE
 {
    UINT8 str[4];
    float  value;
 }swjset_value;
 float SetValue;
void lngdebugmode_init(void);
void lngdebug_task(void);
UINT8 Save_info_print(UINT8 *info,UINT8 *des,UINT16 addr,UINT8 len);
UINT8 Save_info_xs(UINT8 *info,UINT8 *des,UINT16 addr,UINT8 len);
BOOL Get_info_print(void);
BOOL Get_info_hard(void);
BOOL Get_info_Contact(void);
BOOL Get_info_xs(void);
UINT8 Clr_info_xs();
#endif	/* LNGDEBUG_H */





