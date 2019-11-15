/*********************************************************************
 *
 *                  PIC32 Boot Loader
 *
 *********************************************************************
 * FileName:        Bootloader.c
 * Dependencies:
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the 閿熺春ompany閿燂拷) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company閿熺氮 customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 閿熺锤S IS閿燂拷 CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id:  $
 * $Name: $
 *
 **********************************************************************/
#include "Include\GenericTypeDefs.h"
#include "Include\HardwareProfile\HardwareProfile.h"
#include "Include\Bootloader.h"
#include "Include\FrameWork\Framework.h"
//#include "Include\24lcxxx.h"
#include <stdlib.h>
#include <plib.h>


// Configuring the Device Configuration Registers
// 80Mhz Core/Periph, Pri Osc w/PLL, Write protect Boot Flash
#if defined(TRANSPORT_LAYER_USB) || defined(TRANSPORT_LAYER_USB_HOST)
//    #pragma config UPLLEN   = ON        // USB PLL Enabled
//    #pragma config UPLLIDIV = DIV_2     // USB PLL Input Divider = Divide by 2
#endif

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

#if defined(__PIC32MX1XX_2XX__)
    // For PIC32MX1xx, PIC32MX2xx devices there are jumpers on PIM to choose from PGx1/PGx2.
    #pragma config ICESEL = ICS_PGx1    // ICE pins configured on PGx1 (PGx2 is multiplexed with USB D+ and D- pins).
#elif defined(__PIC32MX3XX_7XX__)
    // For PIC32MX3xx, PIC32MX4xx, PIC32MX5xx, PIC32MX6xx and PIC32MX7xx 
    // devices the ICE connection is on PGx2. .
    //#pragma config ICESEL = ICS_PGx2    // ICE pins configured on PGx2, Boot write protect OFF.
#endif
    
#if defined(TRANSPORT_LAYER_ETH)
	#pragma config FMIIEN = OFF, FETHIO = OFF	// external PHY in RMII/alternate configuration. Applicable for devices with internal MAC only.
#endif

#define SWITCH_PRESSED 0

#if KEY_ZKB
    #define BOOTLOAD_INIT PORTSetPinsDigitalIn(IOPORT_F, BIT_0)    //SW7
    #define BOOTLOAD_Enable  ((PORTF & (1 << 0)) == 0)
    #define BOOTLOAD_Disable  ((PORTF & (1 << 0)) == 1)
    #define LED_INIT PORTSetPinsDigitalOut(IOPORT_D, BIT_9)
    #define LED_OFF mPORTDSetBits(BIT_9)
    #define LED_ON mPORTDClearBits(BIT_9)
    #define LED_BLINK   (((PORTD & (1 << 9)) == 0)?(LED_OFF):(LED_ON))
#else
    #define BOOTLOAD_INIT PORTSetPinsDigitalIn(IOPORT_C, BIT_4)     //SW7
    #define BOOTLOAD_Enable  ((PORTC & (1 << 4)) == 0)
    #define BOOTLOAD_Disable  ((PORTC & (1 << 4)) == 1)
//    #define LED_INIT  PORTSetPinsDigitalOut(IOPORT_A, BIT_1)  //(TRISACLR = (1 << 1))
//    #define LED_OFF  mPORTASetBits(BIT_1) //(LATASET = (1 << 1))
//    #define LED_ON mPORTAClearBits(BIT_1) //(LATACLR = (1 << 1))
//    #define LED_BLINK   (((PORTA & (1 << 1)) == 0)?(LED_OFF):(LED_ON))
#endif



#ifdef __cplusplus
extern "C" {
#endif
BOOL CheckTrigger(void);
void JumpToApp(void);
BOOL ValidAppPresent(void);

UINT32 Count = 0;
#ifdef __cplusplus
}
#endif
/********************************************************************
* Function: 	main()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Main entry function. If there is a trigger or 
*				if there is no valid application, the device 
*				stays in firmware upgrade mode.
*
*			
* Note:		 	None.
********************************************************************/
INT main(void)
{
	UINT pbClk;
	// Setup configuration
	pbClk = SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    SPI2CONbits.ON = 0;
    BOOTLOAD_INIT;

    TRANS_LAYER_Init(pbClk);

    while (!FRAMEWORK_ExitFirmwareUpgradeMode()) // Be in loop till framework recieves "run application" command from PC
    {
        // Enter firmware upgrade mode.
        // Be in loop, looking for commands from PC
        TRANS_LAYER_Task(); // Run Transport layer tasks  
        FRAMEWORK_FrameWorkTask(); // Run frame work related tasks (Handling Rx frame, process frame and so on)
        //LED_BLINK; //(Indicates the user that bootloader is running).
        Count++;
        if (Count > 3000000)//20000000) 
        {
            break;
        }
    }
    // Close trasnport layer.
    TRANS_LAYER_Close();
    JumpToApp();

    return 0;
}			


/********************************************************************
* Function: 	CheckTrigger()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		TRUE: If triggered
				FALSE: No trigger
*
* Side Effects:	None.
*
* Overview: 	Checks if there is a trigger to enter 
				firmware upgrade mode.
*
*			
* Note:		 	None.
********************************************************************/
BOOL  CheckTrigger(void)
{
	UINT SwitchStatus;
	SwitchStatus = ReadSwitchStatus();
	if(SwitchStatus == SWITCH_PRESSED)
	{
		// Switch is pressed
		return TRUE;		
	}	
	else
	{
		// Switch is not pressed.
		return FALSE;	
	}	
}	


/********************************************************************
* Function: 	JumpToApp()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		
*
* Side Effects:	No return from here.
*
* Overview: 	Jumps to application.
*
*			
* Note:		 	None.
********************************************************************/
void JumpToApp(void)
{	
	void (*fptr)(void);
	fptr = (void (*)(void))USER_APP_RESET_ADDRESS;
        //fptr = (void (*)(void))Appmain;
        
	fptr();
}	


/********************************************************************
* Function: 	ValidAppPresent()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		TRUE: If application is valid.
*
* Side Effects:	None.
*
* Overview: 	Logic: Check application vector has 
				some value other than "0xFFFFFFFF"
*
*			
* Note:		 	None.
********************************************************************/
BOOL ValidAppPresent(void)
{
	DWORD *AppPtr;
	AppPtr = (DWORD *)USER_APP_RESET_ADDRESS;
	if(*AppPtr == 0xFFFFFFFF)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}			

/*********************End of File************************************/


