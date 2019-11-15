//2014-9-18  调试软件接口增加流量计缓冲、压力、流速等
//2014-12-16  将联动测试里的停改为低，只改了一个汉字。
//2015-04-07  压力异常，由停止改为暂停。
//2015-05-04  修改键盘驱动
//2015-05-13   修改1.增加秘钥错误不锁卡（拔卡后二次插卡则锁卡），并显示提醒，WZW
            //修改2.加气完成小票增加打印随机码备注和暂停分段计量 wzw键盘版版本为6
//2015-06-02  增加手动清零功能；版本为：LNG1.7.7
//150717  增加压力->参考电压功能    标记"Mengfr 20150717"   版本号1.8.8
//150729  1、班组卡加气权限设置  2、读、写卡校验，确保数据正确  3、IC卡增加车牌号，钢瓶号，小票打印车牌号，钢瓶号
//150730  增加调试加气功能（含薄码、存储<键盘板>、设置、查询、）标记：150730；此功能IC修改部分标记为：150730wzw；
//150731  增加被动复位和刷屏走字（闪屏）标记：150731     软件版本：1.8.8
//150813  增加钢瓶号、车牌号、判断钢瓶有效期  标记150813
//150817  增加调试加气开关的第二功能，调试加气不判站号  标记：150817
//150819  增加板件通信的防误 标记：150819
//150824  修改读卡小数点2位以上错误 标记：150824
//150831  增加加熱膜控制功能  密度下限的显示（设置改为硬件版本）改为温度显示  標記：150831
//150901  管理卡判断折扣 150901 rg
//150906  设置中密度下限改为硬件版本150906
//150908  设置预冷的低流速判定150908
//151015  管理卡调试加气时，不允许暂停。标记151015
             //秘钥获取，增加一级确认
//151110  大循环预冷，增加0xaa。标记151110
//151229标记：151229，加气结账属于加气状态，板件通信报错函数中key值指定无效，无下一事件指定，故取消return
//160601   增加过流保护设置、查询//RG160601
//160602   卡置灰位置改为加气前置灰  定量、定额加气中间拔卡处理跳转改为发停止后结账，与非定量相同
//20160612 标记：rg160612 下班命令中增加主板发送时间供键盘板校时，在主板与后台对时后起作用，否则发111111111111.有效时键盘板更新时间
//20160620 标记 160620 异常报错，解决退出键需要2个才能退出的问题.
//20160622 标记 rg160622 查询主板复位序号
//20160623 标记 rg160623 保存、查询键盘板复位序号
//20160704 标记 rg160704  设置查询流速延时判断值,添加流速延时输入密码
//20160726 标记 rg160726  设置期限、解除期限,版本增加为11
//20160817 标记 rg160817   加气暂停按停止键不解灰跳出  
//20160907 标记 rg160907   增加加气完成打印员工号功能，在卡里增加YGH字段。
//20160926 标记：rg160926  加气结束时发现回气流量计错误，保存错误信息，不扣款，返回。
//20161111 标记: 20161111  增加小循环、大循环成功后延迟时间；修改键盘板询问主板参数的程序
//20161220 标记: 161220  查询拨码开关状态（键盘、主板）  版本号升级为86（本安）
//20170110 标记:20170110    修改RTC获取时间的方式
//20170110 标记：rg1701101、主板、键盘对时：1、主板无时间，键盘有，键盘传给主板
//2、主板有时间，键盘无，键盘按主板对时。3、均无时间，由键盘输入，设置主板和键盘时间
//20170221  标记:20170221 修改bootloader实现远程升级
//20170323  标记：rg170323  加气置灰后再判断卡状态（是否置灰成功），09 01 等待主板AA应答时间改为4秒
//20170330 标记：rg170330   回气量异常只报错不处理，扣款按正常流程走.0x99报错（16），0x98报加气量为负（17）.气量大于等于零按正常流程处理;气量为负时强制等于0
//20170406 标记：rg170406  加气值主板复位键盘板未跟随复位，主板再次待机后如果键盘板仍发05 0a查询命令，主板回应回气状态为0xff,键盘板不扣款，提示错误、保存错误号95，退回待机
//20170612 标记：rg170612 班组卡余额小于1的处理（原来是将分抹去）
//20170626  标记：rg170626 1：如置灰不成功，发停止命令，退出 2：置灰次数改为2次，缩短操作卡时间 
			//3：无卡时将读卡错误标志（read_keyv_CS）清零，防止插入坏卡后次标志位一直不清，此后插卡无法使用
//20170629  标记：rg170629 预冷超时设置小于5分钟 预冷温度设置大于-120

//20170531  标记：rg170531无卡加气 功能：加气机上班需要登录，插入员工卡后，键盘板记录班组号和员工卡号。当中途断电或重启或锁屏后需要再次插入
//员工卡进行登录，键盘板需要保存新插入的员工卡卡号，班组号不变。等到员工操作下班后，再重新插入员工卡，
//键盘板再需要更新班组号和员工卡卡号。键盘板保存的员工卡号后所有的操作员一栏都保持使用这个操作员记录加气记录
//20170531  标记：rg170531锁屏  按SW键再5秒内按UP键，机器锁屏。再插班组卡解锁
//20170605  标记：rg170605停止/暂停 设置停止/暂停时间
//20170606  标记：rg170606打印机设置  开启与关闭两种状态，上电从ep中读取。关闭则加气结束不打印小票
//20170606  标记：rg170606最小加气量  从10改为5
//20170607  标记：rg170607 加气信息车牌号  加气命令（04 01）中加上12位车牌号
//20170612  标记：rg170612 班组卡余额小于1的处理（原来是将分抹去）为避免其它问题，单独判断此种情况。
//20170619  标记：rg170619 手动输入车牌号：按1键手动输入最长10位车牌号，汉字用.代替
//20170620  标记：rg170620 按停止键打印最后加气记录 打印余额扩大100倍问题 加气记录打印员工号
//20170621  标记：rg170621  插卡先输密码
//20170626  标记：rg170626 1：如置灰不成功，发停止命令，退出 2：置灰次数改为2次，缩短操作卡时间 
			//3：无卡时将读卡错误标志（read_keyv_CS）清零，防止插入坏卡后次标志位一直不清，此后插卡无法使用
//20170701  标记：rg170701  锁屏后再插班组卡，将员工号、卡号、时间发给主板
//20170704  标记：rg170704 卡里剩5元
//20170705  标记：rg170705 1：判断读卡器有无卡 2：管理卡加气判断   3：屏蔽 加气量为0情况跳出处理，按正常流程走，与LNG相同
//20170707  标记：rg170707  下班记录选择kg或m3。
//20170713  标记：rg170713  解灰后判断状态，最多3次
//20170717  标记：rg170717 子母卡功能
//20170807  标记：rg170807  加气命令增加判断
//20170807  标记：rg170807  nand错误报警
//20170809  标记：rg170809 第5阀延时设置
//20170925  标记：RG170925 问题：CNG经常发现卡钱不对，用户卡钱变为负值。原因：卡置灰时拔卡--置灰不成功--跳到扣款界面--插新卡--按旧卡应扣钱扣给新卡,lng可能也会有此问题
//解决：1、扣款前先验证卡号是否一致 3、版本号改为V1.24.X
//20171011  标记：rg171011 按加气键后，键盘板发04 01命令，然后隔一秒询问（0x99,0x99）,主板可以加气时应答04 05 0xaa 0xbb，通知键盘板置灰，等待收到键盘板返回的04 06命令，根据是否成功标志进行加气或停止。
//1、发加气命令 2、等主板回置灰信息  3、置灰，如不成，发停止命令，退出。4、扣款验卡号是否一致。5、气量为零，不解灰，一直走完流程
//20171127  标记：rg171127  1、 气量为零不打印加气记录 2、无卡加气且为班组卡或不插卡，不置灰 3、首次上电，默认为有卡加气 4、版本号改为25
//20171229  标记：RG171229  测试开关电磁阀输入密码，中间“42” 版本号改为26
//20180118   标记：RG180118  修改预冷时键盘板不判断0xe3问题  2:设置最小加气金额 分3档：6、10、12
//20180130   标记：RG180130   最小剩余金额可以设置，如果未设置，默认10元。版本号改为27
//20180131   标记：rg180131   回气量是否打印设置 是-打印回气量。版本号改为28
//20180322   标记：rg180322   修改子卡置灰错误、加气前不判子卡灰状态;版本改为29
//20180327   标记：rg180327   增加单价显示选择功能
//20180416   标记：rg180416 判断班组号 版本改为30
////20180523   标记：rg180523 读时间判断范围，如不对，加气完打印加气记录里时间，时间、日期后加*号  版本号改为 31
//20180621  标记：rg180621 时间范围判断，上下班对时判断，
//20180625 标记：rg180613 1、增加soe中项目：1、记录修改密度 2、记录修改停机流速 3、修改流水号 版本号改为 32
//20181210 标记：rg181210 1、子卡加气剩余金额 2、加气命令带是否开始加气标志。版本号改为 33
//20181212 标记 加气记录  1、增加加气开始前置灰再次判断置灰状态 ；2、在加气循环中再次读取置灰状态 
//                       3、增加加气过程与卡、主板交互的记录存储、查询。
//20190102  标记: ss20190102   1，增加对加气前的置灰失败做处理，置灰失败直接退出        
//                             2，将加气过程中再次判断卡是否被置灰移除          版本号升为1.34
//20190108 标记：rg181129 rg190108 增加设置枪累、班流水号功能，版本号改为1.35
//20190220 标记:ss190220   1、获取加气完成信息异常的处理，出现获取信息异常不扣款、不解灰
//                         2、增加对加气异常记录信息的存储和索引功能；（按键 7 ）        版本更改为1.36
//20190309 标记ss190306    1、增加对加气异常记录信息的存储和索引功能；（按键 7 ）
//                         2、键盘板异常加气记录更给为100条，正常记录更改为30条，
//                         3、键盘板加气记录信息增加将扣款前卡号显示，并对卡号异常进行记录
//                         4、在解灰失败后，增加对卡机复位的命令，并对卡进行再次置灰操作，保证卡状态与后台状态的一致性；
//              ss190313   5、修改预冷过程无数据相应,跳转到结算状态的BUG                      
//                         6、增加显示主控板存储加气记录的方式　SP/ND       版本更改为 1.37
//20190410  标志: ss190409    1、解决在定额定量时换卡不退回待机界面不进行清空卡片信息的BUG  会出现加气卡与结算卡号不一致   版本更改为 1.38
//20190415  标志：ss190415    1、增加设置流水号与当前流水号的判断 
//20190517  标志：rg190517  rg190510  1、打开设置期限功能  2、中断接收主板nand坏块提示并主程序中报警。版本升级为1.x.39
//20190705  标志：rg190705  期限到期不提示，显示错误代码63
//20190813  标志：ss190813  1、增加在未登入状态下，按压组合键（向上、向下）获取IC卡秘钥功能，   版本升级为1.40.x.
//20190916  标志：ss190913  1、增加将SOE异常信息传输到后台的功能
//20190917  标志：ss190917  1、查看卡余额时出现班组卡的班组号错误    缺少缓存清空  导致 班组号错误
///////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
/*
 * File:   main.c
 * Author: jereh
 *
 * Created on 2014_01_13
 */
///*qaz
//qaz
#include "../includes/global_def.h"

#if 0
    // SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
    #pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
    #pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#else
    #include <xc.h>
//#pragma config DEBUG = ON               // Background Debugger Enable (Debugger is enabled)
//#pragma config ICESEL = ICS_PGx1
    // DEVCFG3
    // USERID = No Setting
    #pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
    #pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
    #pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
    #pragma config FCANIO = ON              // CAN I/O Pin Select (Default CAN I/O)
    #pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
    #pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

    // DEVCFG2
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
    #pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
    #pragma config UPLLIDIV = DIV_2 //DIV_12        // USB PLL Input Divider (12x Divider)
    #pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
    #pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

    // DEVCFG1
    #pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
    #pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
    #pragma config IESO = ON                // Internal/External Switch Over (Enabled)
    #pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
    #pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
    #pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
    #pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
    #pragma config WDTPS = PS1    //PS1048576        // Watchdog Timer Postscaler (1:1048576)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

    // DEVCFG0
    #pragma config DEBUG = ON              // Background Debugger Enable (Debugger is disabled)
    #pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (ICE EMUC1/EMUD1 pins shared with PGC1/PGD1)
    #pragma config PWP = OFF                // Program Flash Write Protect (Disable)
    #pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
    #pragma config CP = ON //OFF                 // Code Protect (Protection Disabled)
#endif

void test_disp(void)
{
    while(1);
}
int main(int argc, char** argv)
{
    UINT8 cur_evid = 0;
    void (*funcAddr)(void);
    float bb,cc,fprice,pri;
  //  UINT8 stn[4];
 //   stn[0]=0x37;
    Rec_inxex = 0;
    Disp_AllErr_tick = 0;
    SysrunTick  = 0;
     Keyvol_num = 0;
    Runled_tick = DWORDMAX;
    KEY422_ERRBYTE_Tick = DWORDMAX; //150819
    Debugasing_rstsave_Tick = 0; //150801
    Carcheck_tick=0;
    CanGasTime  = 0;
    IsGasAdd_tick = 0;
    Newdisp_tick2=0;
    gReadKeyTick = 0;
     ok_ReadKeyTick = 0;
    gScanKeyTick = 0;
    SendStop_False = 0;
    Runled = 1;
     read_keyv_CS = 0;
    b_keyv = FALSE;
    b_mainui = TRUE;
    Rec_debug_ok = 0;
    VER_MasterBoard = 0;
    Err_ZhuTime = 0;//rg170110
    Err_JPTime =0;//rg170110
    DUISHI = 0;//rg170110
    DSCG = 0;//rg170110
    IS_GUANLI_CARD_GAS = 0;  //150730
    Is_debuggas_Read = 0;//150730
     _b_have_cont=0;
     SP_tick = 0;//rg170531锁屏
     Cp_flag=0;//rg170619
     hk_disp=FALSE;//RG190510
     /*
     if(stn[0] != 0x37)
     {
      VER_MasterBoard = 0;   
     }
     else
     {
       VER_MasterBoard = 1;  
     }*/
    sys_init();
    sys_interface_init();
 //   i2c_init(CLOCK_BUS, CLOCK_ADDR, CLOCK_CLOCK_FREQ);
    ostatemachine_init();
    if(HARDKEYCERA4 == 1)
    {
         Is_debuggas_Read =0; //不允许调试加气   //150906
    }
    //////////////////////////////
    Gas_para_init();
#if 1
     if((mPORTBReadBits(BIT_3) >> 3) ==0 )
   {
       while(1)
         {
           lngdebug_task();
         }

   }
#endif
 //   sys_verion_output();
    
    buzzer_config();
    backdisp();
    jrm();      //使能加热膜
   //    olcd_dispstrhex(0,0,dishex,8);
//    oGet_Sta_Cardpsw();
#if 0
    i=o24lcxxx_read_bytes_ex(_BUZZER_SW_ADDR,(UINT8*)CARD_PSW,1);

   i= o24lcxxx_read_bytes_ex(CARD_PSW_BACKUP_ADDR, (UINT8*)CARD_PSW1, 8);
    if(memcmp(CARD_PSW,CARD_PSW1,8)!=0)
 //    if(CARD_PSW !=CARD_PSW1)
        {
              olcd_clearsCreen();
              olcm_dispprintf(0,1,"  获取秘钥");
              olcm_dispprintf(0,2,"正在获取秘钥....");
              if( down_get_password(CARD_PSW)==TRUE )
   {
                if(1 == Save_cardpsw(CARD_PSW))
                 {  olcm_dispprintf(0,2,"秘钥已获取成功");//保存

                 }
         }
    }
#endif
  
     while(1)
    {
        ostatemachine_core();
       
      //  okernel_running();
       // odisp_disp(123, 456, TRUE);
    }
}
 //Mengfr 20160622 //ResetFault
UINT8 Read_OnceEE (void)
{  UINT8  ReadEE = 100;
   UINT8 once1,once2;
    while(ReadEE--)
    { 
        o24lcxxx_read_bytes(_SYSEEPROM_ONCE,(UINT8*)&once1,1);
        o24lcxxx_read_bytes(_SYSEEPROM_ONCE,(UINT8*)&once2,1);
         if(once1 ==once2)
           return once1;

    }

}
 void ResetFaultReasonStore(void)
 {
     UINT8 SendData[100] = {0};
    RESETFAULTMSG ResetReason,ResetReason0;
    
    
    if(RCON & 0x0080)
    {
        // execute a Master Clear Reset handler
        ResetReason.FaultReason = 3;
        RCONCLR = 0x0080;
    }
    else if(RCON & 0x0040)
    {
        // execute a Software Reset handler
        ResetReason.FaultReason = 4;
        RCONCLR = 0x0040;
    }
    else if (RCON & 0x0200)
    {
        // execute a Configuration Mismatch Reset handler
        ResetReason.FaultReason = 5;
        RCONCLR = 0x0200;
    }
    else if (RCON & 0x0010)
    {
        // execute Watchdog Timeout Reset handler
        ResetReason.FaultReason = 6;
        RCONCLR = 0x0010;
    }
    else if(RCON & 0x0003)  //20160630
    {
        // execute a Power-on-Reset handler
        ResetReason.FaultReason = 1;
        RCONCLR = 0x0003;
    }
    else if(RCON & 0x0002)
    {
        // execute a Brown-out-Reset handler
        ResetReason.FaultReason = 2;
        RCONCLR = 0x0002;
    }
    else
    {
        return;
    }
    RCONCLR = 0x0FFFFFFFF;  //clear state bits; //20160630
    cur_max_reset++;
    ResetReason.FaultCount=cur_max_reset;
    ResetReason.CurFaultNum = cur_max_reset;
    ortcc_read_time(ResetReason.DateTime);
    
    o24lcxxx_write_bytes_ex(KeyReset_RECORD_MAX,(UINT8 *)&cur_max_reset,4);
    o24lcxxx_write_bytes_ex(KeyReset_RECORD_Addr + ((cur_max_reset - 1) % 30) * KeyReset_RECORD_Size,(UINT8 *)&ResetReason.FaultCount,KeyReset_RECORD_Size);
 }
 
  //Mengfr 20160622 //ResetFault
 RESETFAULTMSG ResetFaultReasonSearch(UINT32 Index)
 {
     RESETFAULTMSG ResetFaultMsg;
     RESETFAULTMSG ResetFaultMsg2 = {0,0,0,0,0,0,0,0,0};
     o24lcxxx_read_bytes_ex(KeyReset_RECORD_MAX,(UINT8 *)&ResetFaultMsg.FaultCount,4);
     if((Index > ResetFaultMsg.FaultCount) || ((Index < ResetFaultMsg.FaultCount - 30) && (ResetFaultMsg.FaultCount > 30)))
     {
         return ResetFaultMsg2;
     }
     
     o24lcxxx_read_bytes_ex(KeyReset_RECORD_Addr + ((Index - 1) % 30) * KeyReset_RECORD_Size,(UINT8 *)&ResetFaultMsg.CurFaultNum,KeyReset_RECORD_Size);
     if(Index == ResetFaultMsg.CurFaultNum)
     {
         return ResetFaultMsg;
     }
     else
     {
         return ResetFaultMsg2;
     }
 }
 //Mengfr 20160622 //ResetFault
 RESETFAULTMSG ResetFaultReasonLastRec(void)
 {
     RESETFAULTMSG ResetFaultMsg;
     o24lcxxx_read_bytes_ex(KeyReset_RECORD_MAX,(UINT8 *)&ResetFaultMsg.FaultCount,4);
     
     return ResetFaultReasonSearch(ResetFaultMsg.FaultCount);
 }
    //Mengfr 20160622 //ResetFault
 void ResetFaultReasonRecEarse(void)
 {
     UINT32 m = 0;
     UINT8 data[16] = {0};
     memset(data,0,4);
     
     o24lcxxx_write_bytes_ex(KeyReset_RECORD_MAX,(UINT8 *)&data[0],4);
     for(m = 0;m < 30;m++)
     {
         o24lcxxx_write_bytes_ex(KeyReset_RECORD_Addr + m* KeyReset_RECORD_Size,&data[0],KeyReset_RECORD_Size);
     }
 }
    //Mengfr 20160622 //ResetFault 
 void  ResetFaultReasonRecInit(void)
 {
     ResetFaultReasonRecEarse();
     RCONCLR = 0x02DF;  //clear state bits
 }

