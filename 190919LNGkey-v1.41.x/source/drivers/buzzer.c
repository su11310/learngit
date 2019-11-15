/*
 * File:   print.c
 * Author: jereh
 *
 * Created on 2014_01_16
 */
#include "../includes/global_def.h"

#define ALL_TIME 2000 //全拍的长度ms

//static const u16  _frequency[7]  = {262,294,330,349,391,440,494};

#define CAL_PSC(x) (20000000 / 10 / (x))

#define M6  CAL_PSC(440 * 2)
#define M7  CAL_PSC(494 * 2)
#define H1  CAL_PSC(262 * 4)
#define H5  CAL_PSC(391 * 4)



void buzzer_key_soud(void)
{
    play_note(450, 800);
    
}

void buzzer_power_up_sound(void)
{
    play_note(50, 600);
    delay_ms(1000);
    play_note(450, 3000);
    
  

}

void buzzer_power_down_sound(void)
{

    SOEACTION(2,State_MainUI,(pFunc)oui_main_ui);
}

 void play_note(UINT32 note, UINT16 time)
{
  OpenTimer2(T2_ON, 0x8000);
  OpenOC1( OC_ON | OC_TIMER_MODE32 | OC_TIMER2_SRC | OC_CONTINUE_PULSE | OC_LOW_HIGH , (UINT8)note, 0x500 );
  
 delay_ms(time);
  CloseOC1();
  CloseTimer2();


}

//**************************************************************************************************//
void buzzer_config(void)
{
    
  //PORTSetPinsDigitalOut(IOPORT_D, BIT_0);//背光
 // mPORTDSetBits(BIT_0);//点亮
 // mPORTDClearBits(BIT_0);


//OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_256, T2_TICK);
//  OpenTimer2(T2_ON, 0x550);
//  OpenOC1( OC_ON | OC_TIMER_MODE32 | OC_TIMER2_SRC | OC_CONTINUE_PULSE | OC_LOW_HIGH , 0x300, 0x500 );
// CloseOC1();
// CloseTimer2();

  
}

