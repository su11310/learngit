/*
 * File:   buzzer.h
 * Author: wangzw
 *
 * Created on 2014-04-11  20:36
 */

#ifndef BUZZER_H
#define	BUZZER_H

#define SYS_FREQ 	       (80000000L)
#define PB_DIV         		8
#define PRESCALE       		256
#define TOGGLES_PER_SEC		1
#define T2_TICK       		(SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)

UINT8 cur_keysound;
UINT8 Cur_StationNo;  //Õ¾ºÅ

 void play_note(UINT32 note, UINT16 time);

void buzzer_key_soud(void);

void buzzer_except_sound(void);


void buzzer_power_up_sound(void);


void buzzer_power_down_sound(void);



//**************************************************************************************************//
 void buzzer_config(void);


#endif	/* BUZZER_H */





