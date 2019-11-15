/*
 * File:   init.c
 * Author: jereh
 *
 * Created on 2014_01_13
 */
#include "../includes/global_def.h"
//#include<string.h>
#define  CORE_TICK_RATE               400000//(10ms)

void sys_init(void)
{
     SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
}

void sys_coretime_init(void)
{
    INTDisableInterrupts();
    OpenCoreTimer(CORE_TICK_RATE);
    INTSetVectorPriority(INT_CORE_TIMER_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_CORE_TIMER_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTClearFlag(INT_CT);
    INTEnable(INT_CT, INT_ENABLED);


    INTEnable(INT_SOURCE_UART_RX(LNGDEBUGM_PORT), INT_DISABLED);
    INTEnable(INT_SOURCE_UART_TX(LNGDEBUGM_PORT), INT_DISABLED);
    INTSetVectorPriority(INT_VECTOR_UART(LNGDEBUGM_PORT), INT_PRIORITY_LEVEL_3);
    INTSetVectorSubPriority(INT_VECTOR_UART(LNGDEBUGM_PORT), INT_SUB_PRIORITY_LEVEL_0);
    INTClearFlag(INT_SOURCE_UART_TX(LNGDEBUGM_PORT));
    INTClearFlag(INT_SOURCE_UART_RX(LNGDEBUGM_PORT));
    INTEnable(INT_SOURCE_UART_RX(LNGDEBUGM_PORT), INT_ENABLED);

    INTEnable(INT_SOURCE_UART_RX(PCCOMPANY_PORT), INT_DISABLED);
    INTEnable(INT_SOURCE_UART_TX(PCCOMPANY_PORT), INT_DISABLED);
    INTSetVectorPriority(INT_VECTOR_UART(PCCOMPANY_PORT), INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_VECTOR_UART(PCCOMPANY_PORT), INT_SUB_PRIORITY_LEVEL_0);
    INTClearFlag(INT_SOURCE_UART_TX(PCCOMPANY_PORT));
    INTClearFlag(INT_SOURCE_UART_RX(PCCOMPANY_PORT));


    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    // enable interrupts
    INTEnableInterrupts();
    delay_ms(100);

}
void jrm()
{
    ortcc_read_time((UINT8*)&sys_time[0]);
    if((sys_time[1]==11)||(sys_time[1]==12)||(sys_time[1]==1)||(sys_time[1]==2)||(sys_time[1]==3))
    {   MO_High;
  //   MO1_High;
    }
    else
    { MO_Low;
//    MO1_Low;
    }
    
}
void backdisp(void)
{  UINT32 id;
   float dj;
   float je;
   float ql;
   UINT16 addr;
   UINT8 n,pass[5][8];
   UINT32 *recg;
   if(TRUE != get_price(&PRICE,&cur_sysparas.p_gid))
   {
          SOEACTION1(PRO422_ERR,eCurRunState);
           return;
   }
   if(TRUE != qty_get_pricex(&PRICE2 ,&PRICE3,&PRICE4,&PRICE5 ,&PRICE6,&PRICE7, &PRICE8,&PRICE9 ,&PRICE10))
   {
       SOEACTION1(PRO422_ERR,eCurRunState);
           return;
   }
   //*************************************************************************//
#if 0
   for(n=0;n<5;n++)
   {
   addr = (n*_PASS_PAGE_SIZE) + _PASS_EEP_ADDR;
             o24lcxxx_read_bytes(addr,(UINT8*)&pass[n],8);
   }
   if(strcmp(pass[0],pass[1])==0)
   {
       memcpy(KEY_CAR_PASS,pass[0],8);
   }
#endif
//***************************************************************************//
 //odisp_price(PRICE, TRUE);
 
// id = get_max_rec_id();//wangqaz
/* if(TRUE != qty_get_serrec(id,&dj,&je,&ql))
       {//通信异常
           SOEACTION1(PRO422_ERR,eCurRunState);
           return;
       }
odisp_disp(ql, je, TRUE);*/

}
UINT8 top_state(void)
{  UINT8  ReadEE = 100;
   UINT8 once1,once2;
   
    while(ReadEE--)
    {
        o24lcxxx_read_bytes(TOP_POWER,(UINT8*)&once1,1);
        o24lcxxx_read_bytes(TOP_POWER,(UINT8*)&once2,1);
         if(once1 ==once2)
           return once1;
    }
   
}
void sys_interface_init(void)
{
  //  PORTSetPinsDigitalOut(IOPORT_A, BIT_1);
  //  mPORTAClearBits(BIT_1);

     PORTSetPinsDigitalIn(IOPORT_C, BIT_3 );
  if((mPORTCReadBits(BIT_3) >> 3) ==0 )
  {
      Is_debuggas_Read =1;//150813
  } //允许调试加气
  else //1
  {
      Is_debuggas_Read =0;
  }
    //

    PORTSetPinsDigitalOut(IOPORT_B, BIT_9);
//     odisp_init();              delay_ms(200);
//     onand_init();              delay_ms(200);
     oprint_init(9600);         delay_ms(200);
     debug_uart_init(9600);     delay_ms(200);
     sys_coretime_init();
    ocompany_port_init(115200); delay_ms(200);
           
   //  olng_psensor_init();
  //   olng_vctrl_init();
    // IDLE_CTRL();               delay_ms(100);
     // INIT_CLRT() ;   delay_ms(200);
     lcd_key_init();    delay_ms(200);
     
 
     delay_ms(10000);
     olcm_dispprintf(0,2,"系统启动>>");
     odisp_init_chk();//odisp_init();
     
     ic_card_init(9600);        delay_ms(100);     //wang移植此处
     Get_info_print();          delay_ms(100);
     Get_info_Contact();    delay_ms(100);
     Get_info_hard();       delay_ms(100);
     Get_info_xs();         delay_ms(100);
     lngdebugmode_init();
            WKJQ = o24lcxxx_read(Car_power_addr);//RG170531无卡加气
    if(WKJQ !=0)  //RG170531无卡加气
	WKJQ=1;	   //RG170531无卡加气 
	o24lcxxx_read_bytes_ex(Set_Zttz_Addr, (UINT8 *)&Zttz_Time, 4);//rg170605停止/ 暂停
	if(Zttz_Time>900)
    {
	    Zttz_Time=900 ;  
    o24lcxxx_write_bytes_ex(Set_Zttz_Addr,(UINT8*)&Zttz_Time,4);
    }
	 if(Zttz_Time<0)
    {
	    Zttz_Time=0 ;  
    o24lcxxx_write_bytes_ex(Set_Zttz_Addr,(UINT8*)&Zttz_Time,4);
    }
	memset(CPH,0x0,12);//rg170607 加气信息车牌号
    //U3和U5配置为输入    //Mfr 20150325
	SP = 0;//rg170531 锁屏
	SCS=0;//rg170531 锁屏
     //DS18B20初始化 //Mengfr 20150831
     (mPORTESetPinsDigitalOut(BIT_7));
     DS18B20_Init();
     //加热膜控制引脚   //Mengfr 20150831
     JiaReMoCtlInit;
}
/*------------------------------------------------------------------------------
 * 数据校验机制： 1. 流水号连续
 *                2. EEPROM块数据校验匹配
 *                3. 系统时间连续
 ------------------------------------------------------------------------------*/
void sys_data_chk(void)
{

}

void show_sysconfig(Sysparas   info)
{
     oprint_printf("SYS_CONFIG  current p_Price is %f\r\n", info.p_Price);
     oprint_printf("SYS_CONFIG  current p_Ptemp is %f\r\n", info.p_Ptemp);
     oprint_printf("SYS_CONFIG  current p_PGain is %f\r\n", info.p_PGain);
     oprint_printf("SYS_CONFIG  current p_PDelay is %f\r\n", info.p_PDelay);
     oprint_printf("SYS_CONFIG  current p_EndR is %f\r\n", info.p_EndR);
     oprint_printf("SYS_CONFIG  current min_Gas is %f\r\n", info.min_Gas);
     oprint_printf("SYS_CONFIG  current min_money is %f\r\n", info.min_money);
     oprint_printf("SYS_CONFIG  current p_curflow is %d\r\n", info.p_curflow);
}

void show_sys_recod(_rec_shift_info info)
{
     oprint_printf("SYS_RECORD  current g_uid is %f\r\n", info.g_uid);
     oprint_printf("SYS_RECORD  current set_uid is %f\r\n", info.set_uid);
     oprint_printf("SYS_RECORD  current sig_uid is %f\r\n", info.sig_uid);
     oprint_printf("SYS_RECORD  current g_sum is %f\r\n", info.gun_total);
     oprint_printf("SYS_RECORD  current g_total is %f\r\n", info.g_total);
     oprint_printf("SYS_RECORD  current shift_cash is %f\r\n", info.shift_cash);
     oprint_printf("SYS_RECORD  current g_money is %f\r\n", info.gun_money);
}


/*        ----------------                    检查本系统的各种 流水号                   -----------------*/
BOOL oset_system_init_chk(void)
{
    BOOL bok = FALSE;
     UINT8 stationNo;
     float _relay;
     //////////////////////////150730/////////////////////
     UINT8 K =100;
     UINT8 kkmm =100;  //150730
     UINT8 save_debugjl =0; ////150730写零清调试保存
     UINT8 read_debugmax_save1 ;
     UINT8 read_debugmax_save2 ;
     UINT8 qxset,qx;
     UINT8 minimoney,smallminimoney;
     float wdcs;//rg180130
    OnceRecordEEP();                                                     // 键盘板存储加气记录信息标志
    OnceRecordEEP_SP();                                                   //键盘板存储异常加气信息标志  ss190201
     if( 0x55 !=Read_OnceEE()) //非首次上电
     {
         ResetFaultReasonRecInit();//rg160623
	 qx=0;
	 o24lcxxx_write_bytes(qxsz_yue_addr,(UINT8*)&qx,1 );
	 QX_RECORD=0;//RG160726
	Save_Qx_Runtime(QX_RECORD);//RG160726	
	qxset=0x0;//RG160726
	o24lcxxx_write_bytes(qxset_addr,(UINT8*)&qxset,1 );//RG160726
	WKJQ = 1;//rg171127
	o24lcxxx_write_bytes(Car_power_addr,(UINT8*)&WKJQ,1 );//rg171127
	HQ_PRINT=1;//rg180131
	o24lcxxx_write_bytes(hqset_addr,(UINT8*)&HQ_PRINT,1 );
     }
    o24lcxxx_write(_SYSEEPROM_ONCE,0x55); //非首次上电标志 
  while(K--)    //150730
    {  o24lcxxx_read_bytes_ex(DEBUG_RECORD_MAXNUM, (UINT8 *) &read_debugmax_save1, 1);//
    delay_ms(100);
    o24lcxxx_read_bytes_ex(DEBUG_RECORD_MAXNUM, (UINT8 *) &read_debugmax_save2, 1);//
    if(read_debugmax_save1 == read_debugmax_save2)
      { K = 100;
       break;
      }
    }
     //end of while 1
   MAX_dubug_recid_num =  read_debugmax_save1; //150730获得调试记录数目
   if(MAX_dubug_recid_num > 201)   //150730,201仅用作判别初始为FF的情况，和最大笔数200不牵扯
   { MAX_dubug_recid_num = 0;
      while(kkmm--)
       {
         if ( TRUE == o24lcxxx_write_bytes_ex(DEBUG_RECORD_MAXNUM,&save_debugjl,1))    //1121
             {
             break;
             }

        }

   }

    HARDKEYCERA4 = o24lcxxx_read(_HARD_VER_ADDR); //
    if(HARDKEYCERA4!=1) HARDKEYCERA4 = 0; //强制非零即1
   
    cur_keysound = o24lcxxx_read(_BUZZER_SW_ADDR); //
    if(cur_keysound!=1) cur_keysound = 0; //强制非零即1
    CANGASMINUTE = o24lcxxx_read(_WAIT_TIM_ADDR);
    if((CANGASMINUTE >240) || (CANGASMINUTE <1)) CANGASMINUTE = 20; //强制非零即1

     temp_add_vol = o24lcxxx_read(_TMP_ADD_ADDR);
     if((temp_add_vol >100) )
     {   temp_add_vol = 0;
         o24lcxxx_write_bytes(_TMP_ADD_ADDR,(UINT8*)&temp_add_vol,1 );
     }
  if( 0x27 ==top_state()) //判断秘钥
  {//用户秘钥
       if(Get_Cardpsw()==FALSE)
         {
           SOEACTION1(PSW_ERR,eCurRunState);
             return ;
         }
   }
  else
  { //初始秘钥
                memset(KEY_CAR_PASS,0x01,8);
#if 0
                if(1 != Save_cardpsw(KEY_CAR_PASS))
                 {
                 SOEACTION1(PSW_ERR,eCurRunState);
                 return ;
                 }
#endif
  }
#if 0
    if(PSWSEL_1())
    {
        delay_ms(1000);
        if(PSWSEL_1())
    {
       
    }
    else
    {
       
    }
    }
#endif
#if 0
#if down_psw
 if(Get_Cardpsw()==FALSE)
 {
   SOEACTION1(PSW_ERR,eCurRunState);
     return ;
 }
#endif
#endif
    PRINT_SET = o24lcxxx_read(_PRINT_SW_ADDR); //
   if(PRINT_SET !=0)
     PRINT_SET = 1;//非零即1,1为自动打印
        ZK_POWER = o24lcxxx_read(zk_power_addr);

  if(ZK_POWER !=0)
     ZK_POWER = 1;//非零即1,1为禁止折扣

	HQ_PRINT = o24lcxxx_read(hqset_addr);//rg180131
	if(HQ_PRINT !=0)
	HQ_PRINT = 1;//非零即1,1为禁止打印
	
    gass_class = o24lcxxx_read(gass_class_addr);

  if(gass_class !=1)
  {  gass_class = 0;//非零即1,1为禁止加气
     o24lcxxx_write_bytes(gass_class_addr,(UINT8*)&gass_class,1 ); //150804
  }
    ////////////////////rg180118///////////rg180130//////////////////////////////////////
	minimoney = o24lcxxx_read(minimoney_addr);
	if(minimoney!=0xA5)
	{
		minimoney=0xA5;
		o24lcxxx_write_bytes(minimoney_addr,(UINT8*)&minimoney,1 );
		Mini_FD = Mini_Money;
		o24lcxxx_write_bytes_ex(minimoneydat_addr,(UINT8*)&Mini_FD,4);
	}	
	else
	{
		o24lcxxx_read_bytes_ex(minimoneydat_addr, (UINT8 *)&wdcs, 4);
		Mini_FD = wdcs;
	}
	if((Mini_FD>Mini_UP)||(Mini_FD<Mini_DO))
	{
		Mini_FD = Mini_Money;
		o24lcxxx_write_bytes_ex(minimoneydat_addr,(UINT8*)&Mini_FD,4);
		delay_ms(50);
		minimoney=0xA5;
		o24lcxxx_write_bytes(minimoney_addr,(UINT8*)&minimoney,1 );
	}
/*	if((minimoney!=0x98)&&(minimoney!=0x99)&&(minimoney!=0x9a))
	{
		minimoney=0x99;
		o24lcxxx_write_bytes(minimoney_addr,(UINT8*)&minimoney,1 );
	}
			if(minimoney==0x98)
			  {
				Mini_FD = Mini_Money1;
			    }
			  else if(minimoney==0x99)
			  {
				Mini_FD = Mini_Money2;
			    }
			else if(minimoney==0x9a)
			  {
				Mini_FD = Mini_Money3;
			    }
			else
			  {
				Mini_FD = Mini_Money2;
			    }*/
	////////////////////rg180118 rg180130 END///////////////////////////////////////////////
          ////////////////////rg181210///////////////////////////////////////////////
	smallminimoney = o24lcxxx_read(smallminimoney_addr);
	if(smallminimoney!=0xA5)
	{
		smallminimoney=0xA5;
		o24lcxxx_write_bytes(smallminimoney_addr,(UINT8*)&smallminimoney,1 );
		smallMini_FD = smallMini_Money;
		o24lcxxx_write_bytes_ex(smallminimoneydat_addr,(UINT8*)&smallMini_FD,4);
	}	
	else
	{
		o24lcxxx_read_bytes_ex(smallminimoneydat_addr, (UINT8 *)&wdcs, 4);
		smallMini_FD = wdcs;
	}
	if((smallMini_FD>SMALL_Mini_UP)||(smallMini_FD<SMALL_Mini_DO))
	{
		smallMini_FD = smallMini_Money;
		o24lcxxx_write_bytes_ex(smallminimoneydat_addr,(UINT8*)&smallMini_FD,4);
		delay_ms(50);
		smallminimoney=0xA5;
		o24lcxxx_write_bytes(smallminimoney_addr,(UINT8*)&smallminimoney,1 );
	}
	////////////////////rg181210 END///////////////////////////////////////////////
    b_shift_ok = -1;
    cur_max_soe = Get_max_soe_id();   //4-15  wang  SOE  此3句临时从下面拿上来
    cur_max_reset = Get_max_reset_id();
    //**********************RG170712  温度控制*******************************************//
       JiaReMoCtlInit;
    delay_ms(20);
       JiaReMoClose;//rg160824
    o24lcxxx_read_bytes_ex(Set_Wdcs_Addr, (UINT8 *)&WDKZ, 4);
    if((WDKZ>10)||(WDKZ<-30))//RG160824
	    WDKZ=0;
    o24lcxxx_read_bytes_ex(Set_Wderr_Addr, (UINT8 *)&WDBJ, 4);//RG161103
       if(WDBJ <= 30)//RG170228  报警温度小于10，非法，改为默认值50
    {WDBJ = 50;  
    o24lcxxx_write_bytes_ex(Set_Wderr_Addr,(UINT8*)&WDBJ,4);//rg170228
    }
    
    jr_power = o24lcxxx_read(jr_power_addr);//rg161017
    if(jr_power >2)//rg161017
    {
	    jr_power=0;   //rg161017
		o24lcxxx_write_bytes(jr_power_addr,(UINT8*)&jr_power,1 ) ;//rg161017
    }
    //*****************************************************************//
    delay_ms(20);
    ResetFaultReasonStore();//rg160623
 if(TRUE != qty_get_zhanhao((UINT8*)&stationNo,(float*)&_relay,&VER_MasterBoard))
   {
     SOEACTION1(PRO422_ERR,eCurRunState);
     return ;
   }
	
  Cur_StationNo = stationNo;  //得到当前站号
//  Cur_StationNo=2;//rgrg
  if(Cur_StationNo>100) Cur_StationNo = 1; //非法强制即1
  if((VER_MasterBoard>99)&&(VER_MasterBoard<0))
  {
       VER_MasterBoard = 99;
       SOEACTION1(ZKB_VER_ERR,eCurRunState);
     return ;
  }
  QX_OVER=0;//RG160726
  qxset = o24lcxxx_read(qxset_addr);
  if(qxset == 0xaa )
  { 
	QX_RECORD = Get_Qx_Runtime();
	if(QX_RECORD<=1)
	      {
		QX_OVER=1;
	      }
  }
  
  
  
  
  
  //  b_shift_ok = -1;//WANGqaz
   // bok = oset_init_str_chk();
   
}
void sys_uart_send_str(UART_MODULE ch, UINT8 *buff, UINT32 size)
{
    while(size)
    {
        while(!UARTTransmitterIsReady(ch));
        UARTSendDataByte(ch, *buff);
        buff++;
        size--;
    }
    while(!UARTTransmissionHasCompleted(ch));
}

void sys_uart_send_char(UART_MODULE ch, UINT8 c)
{
    while(!UARTTransmitterIsReady(ch));
    UARTSendDataByte(ch, c);
    while(!UARTTransmissionHasCompleted(ch));
}

void sys_uart_printf(UART_MODULE ch, char *fmt,...)
{
    va_list ap;
    char str[128];//128]; //64
    va_start(ap,fmt);
    vsprintf(str,fmt,ap);
    sys_uart_send_str(ch,str,strlen(str));
    va_end(ap);
}

void sys_uart_init(unsigned char ch, unsigned long baudrate)
{
     UARTConfigure(ch, UART_ENABLE_PINS_TX_RX_ONLY);
     UARTSetFifoMode(ch, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
     UARTSetLineControl(ch, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE |  UART_STOP_BITS_1);
     UARTSetDataRate(ch, GetPeripheralClock(), baudrate);
     UARTEnable(ch, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX  | UART_TX )); //
}

float sys_get_float(float vfdt)
{
    UINT8  str[16];
    sprintf(str,"%.02f",vfdt);
    vfdt = atof(str)*100;
    sprintf(str,"%.02f",(float)(vfdt/100));
    return atof(str);
}

void sys_set_tick(UINT32 vset)
{
    _sys_tick_cnt_ = vset;
}
//
UINT32 sys_get_tick(void)
{
    return _sys_tick_cnt_; // = vset;
}

void sys_uart_debug_info(void)
{
    UINT16 rdPv = 0;
    UINT32 tick = 0;
 //qaz   rdPv = olng_psensor_read_adc(64);
    tick = sys_get_tick();
   // PC485_DIR_OUTPUT(); delay_ms(10);
    //sys_uart_printf(PCTRANS_PORT, "T:%06.2f  G:%06.2f  R:%06.2f  N:%6.2f P:%04d t:%ld\r\n", cur_lngtemp, cur_lnggain, cur_lngrate, cur_lngnum, rdPv,tick);
 //   oprint_printf("T:%06.2f  G:%06.2f  R:%06.2f  N:%6.2f P:%f D:%06.2f t:%ld\r\n", cur_lngtemp, cur_lnggain, cur_lngrate, cur_lngnum, cur_press, cur_lngdensty,tick);
   // PC485_DIR_INPUT(); delay_ms(10);
}

void delay_ms(UINT32 ms)
{
    UINT32 i;
    UINT32 j;
    for(j =0; j < ms; j++)
    {
        for(i = 0; i<800; i++) 
        {
            __asm__ __volatile__("NOP");
        }
    }
}

void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
{
    UINT8 tmpkey = 0;
    
    mCTClearIntFlag();
    _10ms_tick_++;
//    _10ms_tick2_++;
    heareat_time++;
    gTick++;
 
  //  TEST_tick++;

    #if  __SIMU_DEBUG_
	   if( (TRUE == _b_simu_lng)  &&  (++_simu_tick > 10))
           {
			_simu_lngnum += 0.01;
			_simu_tick = 0;
	   }
    #endif
#if 0
        if( _10ms_tick2_ > 20)
        {
            if(uart_state2==1)
                    {
                    re_over_tick2++;
                    }
            _10ms_tick2_=0;
        }
#endif
    if( _10ms_tick_ > 100) {

        
          Protocol_tick++;
               if(uart_state==1)
            {
            re_over_tick++;
            }
          
          if(PrecoolCo)//rg521
            {
                           send_yl_flag=1;
            }
             if(GasCo)//rg521
            {
                           send_sj_flag=1;
            }
          if(led==1)
          {
              led=0;
  //          
  //             LED_OPEN();
          }
          else
          {
              led=1;
 //             mPORTBClearBits(BIT_7);
  //            LED_CLOSE();
          }
            _sys_tick_++;
            _sys_tick_cnt_++;
	    _10ms_tick_ = 0;
    }
    ostatemachine_keyscan();
    // update the period
    UpdateCoreTimer(CORE_TICK_RATE);
}

