/* 
 * File:   24lcxxx.h
 * Author: 7464
 *
 * Created on February 7, 2017, 10:47 AM
 */

#ifndef _24LCXXX_H_
#define	_24LCXXX_H_

#ifdef	__cplusplus
extern "C" {
#endif

#define VerifyAddr 0x3FFB
    
extern UINT8 o24lcxxx_write_bytes_ex(UINT16 addr, UINT8 *buffer, UINT8 size);
extern UINT8 o24lcxxx_read_bytes_ex(UINT16 addr, UINT8 *buff, UINT8 size);
extern void  o24lcxxx_init(UINT pbclk);
#ifdef	__cplusplus
}
#endif

#endif	/* _24LCXXX_H_ */

