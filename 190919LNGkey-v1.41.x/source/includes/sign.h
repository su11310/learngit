/* 
 * File:   sign.h
 * Author: Administrator
 *
 * Created on 2014年2月26日, 上午10:32
 */

#ifndef SIGN_H
#define	SIGN_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void sign_start(void);
extern void sign_startup(void);
extern void sign_nocard(void);
extern void sign_has_card(void);
extern void sign_error(void);
extern void osel_offwork(void);
extern void oset_shift_join(void);
extern void oset_shift_Exit(void);
void oset_shift_exit(void);
void olng_operate_card_info();
void init_eeprom_shift_info();
void olng_operate_card_info_nosel();
void show_time_over();//rg170701
#ifdef	__cplusplus
}
#endif

#endif	/* SIGN_H */

