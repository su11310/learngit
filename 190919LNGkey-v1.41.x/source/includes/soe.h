/*
 * File:   buzzer.h
 * Author: wangzw
 *
 * Created on 2014-04-11  20:36
 */

#ifndef SOE_H
#define	SOE_H

#define SOE_SIZE               7          //SOE��С
#define SOEMAX_SIZE            500        //SOE�¼��ļ�¼���Χ����

#define  COOL_SERILBERR_STOP           0xE0 //��ѭ��422����
#define  COOL_PRELLBERR_STOP     0xE1//��ѭ����ȫѹ��
#define  COOL_SMALLBERR_STOP     0xE2//������ֹͣԤ��

#define MODBUS_ERR	                	00 //Һ��������ͨ���쳣
#define MOD_WRITE_ERR  	                	01 //Һ�����������Ʋ���д��ʧ��
#define MOD_NOFLOW_ERR                  	02 //δ��⵽Һ������������
#define MOD_ADD_ERR  	                	03 //Һ�����������Ƶ�ַ����
#define MOD_ERC_ERR  	                	04 //Һ����������������У�����
#define MOD_READNUM_ERR   	        	05 //Һ�����������ƶ�������

#define C_MODBUS_ERR 	               		10 //����������ͨ���쳣
#define C_MOD_WRITE_ERR  	               	11 //�������������Ʋ���д��ʧ��
#define C_MOD_NOFLOW_ERR                 	12 //δ��⵽��������������
#define C_MOD_ADD_ERR  	               		13 //�������������Ƶ�ַ����
#define C_MOD_ERC_ERR  	               		14 //������������������У�����
#define C_MOD_TIMEOUT_ERR   	       		15 //��������������ͨѶ��ʱ
#define C_HuiQi_ERR 	               		16 //�������쳣
#define C_JiaQi_fu 	               		17 //������Ϊ��

#define EEPROM_WRITE_ERR 	       		20 //EEPROMд�����(ָ����)
#define EEPROM_READ_ERR  	       		21 //EEPROM��ȡ����(ָ����)

#define DKQ_GREY_ERR                		30//������ͨ�Ŵ���
#define ICCARD_READ_ERR    		        31//��������

#define NOPRESSURE_ERR 	                	40 //ѹ���������쳣
#define ZDLS_ERR 	                	41 //�����������
#define KLXKY_ERR 	                	42 //�����Ϳ��಻ƥ��
#define PRO422_ERR	                	50 //���ͨѶ����
#define TXERR_KEY_TO_CONU 	                51 //�����м��̰嵽����ͨ�Ŵ���
#define TXERR_CONU_TO_KEY 	                52 //���������嵽���̰�ͨ�Ŵ���
#define PC_PRO_ERR	                        53 //��̨ͨ�Ŵ���

#define GAS_CHECK_GREYLOCK_ERR          58  // ���������� �жϻ�������

#define NAND_CONT_ERR				60//nand flash �洢���󳬴�����ֹͣ����
#define PSW_ERR                                 61 //�洢��Կ����
#define NAND_WRITE_ERR                                 62 //�洢��д����󣬱���
#define QxOver                     63//���޵���  //RG190705
#define CLOCK_READ_ERR				70//ʱ�Ӷ�������
#define CLOCK_WRITE_ERR				71//ʱ��д�����
#define CLOCK_TIME_ERR				72//ʱ���쳣����
#define ZKB_VER_ERR                             73//���ذ�汾�Ż�ȡ����
#define REC_NUM_ERR		        	80//��ˮ�Ų���������
#define kk_w_err                                90//д��ʧ��
#define kk_r_err                                91//����ʧ��
#define koukuan_err                             92//�ۿ�ʧ��
#define huicar_err                             93//���û�ʧ��
#define carcmp_err                             94//�ۿ�ʱ���Ų�һ��//rg170925
#define Zhu_Reset                               95//���帴λ  rg170406
////////////////////////////////////////////////////////////////////

//rg180613
#define Para_md                             100//��¼�޸��ܶ�
#define Para_lsh                            101//��¼�޸���ˮ��
#define Para_tjyl                           102//��¼�޸�ͣ��ѹ��



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

}soe_rec;//SOE��¼
*/



#endif	/* SOE_H */





