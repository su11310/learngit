/*
 * File:   buzzer.h
 * Author: wangzw
 *
 * Created on 2014-04-11  20:36
 */

#ifndef SOE_H
#define	SOE_H

#define SOE_SIZE               7          //SOE大小
#define SOEMAX_SIZE            500        //SOE事件的记录最大范围个数

#define  COOL_SERILBERR_STOP           0xE0 //大循环422错误
#define  COOL_PRELLBERR_STOP     0xE1//大循环安全压力
#define  COOL_SMALLBERR_STOP     0xE2//低流速停止预冷

#define MODBUS_ERR	                	00 //液相流量计通信异常
#define MOD_WRITE_ERR  	                	01 //液相质量流量计参数写入失败
#define MOD_NOFLOW_ERR                  	02 //未检测到液相质量流量计
#define MOD_ADD_ERR  	                	03 //液相质量流量计地址错误
#define MOD_ERC_ERR  	                	04 //液相质量流量计数据校验错误
#define MOD_READNUM_ERR   	        	05 //液相质量流量计读数错误

#define C_MODBUS_ERR 	               		10 //气相流量计通信异常
#define C_MOD_WRITE_ERR  	               	11 //气相质量流量计参数写入失败
#define C_MOD_NOFLOW_ERR                 	12 //未检测到气相质量流量计
#define C_MOD_ADD_ERR  	               		13 //气相质量流量计地址错误
#define C_MOD_ERC_ERR  	               		14 //气相质量流量计数据校验错误
#define C_MOD_TIMEOUT_ERR   	       		15 //气相质量流量计通讯超时
#define C_HuiQi_ERR 	               		16 //回气量异常
#define C_JiaQi_fu 	               		17 //加气量为负

#define EEPROM_WRITE_ERR 	       		20 //EEPROM写入错误(指主板)
#define EEPROM_READ_ERR  	       		21 //EEPROM读取错误(指主板)

#define DKQ_GREY_ERR                		30//读卡器通信错误
#define ICCARD_READ_ERR    		        31//读卡错误

#define NOPRESSURE_ERR 	                	40 //压力传感器异常
#define ZDLS_ERR 	                	41 //超过最大流速
#define KLXKY_ERR 	                	42 //卡类型卡余不匹配
#define PRO422_ERR	                	50 //板间通讯错误
#define TXERR_KEY_TO_CONU 	                51 //加气中键盘板到主板通信错误
#define TXERR_CONU_TO_KEY 	                52 //加气中主板到键盘板通信错误
#define PC_PRO_ERR	                        53 //后台通信错误

#define GAS_CHECK_GREYLOCK_ERR          58  // 加气过程中 判断灰锁错误

#define NAND_CONT_ERR				60//nand flash 存储错误超次数，停止加气
#define PSW_ERR                                 61 //存储密钥错误
#define NAND_WRITE_ERR                                 62 //存储器写入错误，报错
#define QxOver                     63//期限到期  //RG190705
#define CLOCK_READ_ERR				70//时钟读出错误
#define CLOCK_WRITE_ERR				71//时钟写入错误
#define CLOCK_TIME_ERR				72//时间异常错误
#define ZKB_VER_ERR                             73//主控板版本号获取错误
#define REC_NUM_ERR		        	80//流水号不连续错误
#define kk_w_err                                90//写卡失败
#define kk_r_err                                91//读卡失败
#define koukuan_err                             92//扣款失败
#define huicar_err                             93//卡置灰失败
#define carcmp_err                             94//扣款时卡号不一致//rg170925
#define Zhu_Reset                               95//主板复位  rg170406
////////////////////////////////////////////////////////////////////

//rg180613
#define Para_md                             100//记录修改密度
#define Para_lsh                            101//记录修改流水号
#define Para_tjyl                           102//记录修改停机压力



UINT16 cur_max_soe;
UINT32  cur_max_reset;//rg160623
void ClearSysRuntime(void);
void ClearNameStation(void);
UINT32 Get_Sys_Runtime(void);
UINT16 Get_max_soe_id(void);
BOOL AddSOE(UINT8 err_type);
void SOE_DELEALL(void);
void oqry_soerec(void);
void Qry_Soerec_Disp(UINT16 id);
BOOL SOEACTION1(UINT8 err_type,UINT8 cur_state);
BOOL SOEACTION(UINT8 err_type,UINT8 cur_state, pFunc SpecFunc);
BOOL SOEACTION2(UINT8 *num,UINT8 err_cont,UINT8 cur_state);
void car_disp(UINT8 dj,UINT8 tp,UINT8 *jy,UINT8 *qy,float zk,UINT8 q1,UINT8 q2,UINT8 q3,UINT8 q4,UINT8 xf,UINT8 *cp,UINT8 *pjyx);//150813
void oqry_reset_info(void);//rg160622
UINT32 Get_max_reset_id(void);//rg160622
void oqry_key_reset(void);
void Qry_Resetrec_Disp(UINT32 id);
//BOOL Save_Qx_Runtime(UINT32 new_runtime);//RG160726
/* typedef struct def_SOE_Record
{
    UINT8   rec_Stime[6];
    UINT8   Err_type;

}soe_rec;//SOE记录
*/



#endif	/* SOE_H */





