/* 
 * File:   nand.h
 * Author: felixluom
 *
 * Created on 2014年1月22日, 下午9:50
 */

#ifndef NAND_H
#define	NAND_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef union __NAMD_ADDR_ARR3A
    {
        UINT8   addr[3];
        struct
        {
            UINT16  column: 8;
            UINT16  page:   5;
            UINT16  block:  10;
         };
    }NAND_ADDR_ARR3A;

    typedef struct __NAND_ADDR3A
    {
        UINT32  column: 9;
        UINT32  page:   5;
        UINT    block:  10;
    }NAND_ADDR3A;
    typedef struct Signature
    {
        UINT8    Manufacturer;
        UINT8    Device_code;
    }Signature_3A2B;

    //#pragma config FPLLMUL = MUL_24, FPLLIDIV = DIV_2, FPLLODIV = DIV_2, FWDTEN = OFF
    //#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
    //#define SYS_FREQ (48000000L)
    //#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
    //#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8
    #define CONFIG          (CN_ON)
    #define PINS            (CN16_ENABLE)
    #define PULLUPS         (CN15_PULLUP_ENABLE | CN16_PULLUP_ENABLE)
    #define INTERRUPT_NAND  (PMP_INT_OFF)//(CHANGE_INT_ON | CHANGE_INT_PRI_5 | PMP_INT_OFF)
    //#define SYS_FREQ 			(80000000L)

    // Commands

    #define NAND_CMD_PAGE_RD_C1             (0x00)
    #define NAND_CMD_PAGE_RD_C3             (0x01)
    #define NAND_CMD_PAGE_RD_C2             (0x30)
    #define NAND_CMD_PAGE_RD_CACHE_START    (0x31)
    #define NAND_CMD_PAGE_RD_CACHE_START_L  (0x3F)
    #define NAND_CMD_READ_INTERNAL_C1       (0x00)
    #define NAND_CMD_READ_INTERNAL_C2       (0x35)
    #define NAND_CMD_RAND_DATA_READ_C1      (0x05)
    #define NAND_CMD_RAND_DATA_READ_C2      (0xE0)
    #define NAND_CMD_READ_ID                (0x90)
    #define NAND_CMD_READ_STATUS            (0x70)
    //#define NAND_CMD_READ_STATUS            (0x90)
    #define NAND_CMD_PROGRAM_PAGE_C1        (0x80)
    #define NAND_CMD_PROGRAM_PAGE_C2        (0x10)
    #define NAND_CMD_PRGM_PAGE_CACHE_C1     (0x80)
    #define NAND_CMD_PRGM_PAGE_CACHE_C2     (0x15)
    #define NAND_CMD_PRGM_INTERNAL_C1       (0x85)
    #define NAND_CMD_PRGM_INTERNAL_C2       (0x10)
    #define NAND_CMD_RAND_DATA_PRGM         (0x85)
    #define NAND_CMD_BLOCK_ERASE_C1         (0x60)
    #define NAND_CMD_BLOCK_ERASE_C2         (0xD0)
    #define NAND_CMD_RESET                  (0xFF)

    //- Status Bits
     #define NAMD_STATUS_FAIL                (0x01)
    #define NAMD_STATUS_FAIL_N              (0x02)
    #define NAMD_STATUS_READY_BUSY          (0x60)
    #define NAMD_STATUS_WP                  (0x80)
    // Defines
     #define NAND_PAGE_SIZE                  (512l)
    #define NAND_SPARE_SIZE                 (16l)

    #define NAND_NUM_PAGES_PER_BLK          (32l)
    #define NAND_NUM_BLOCKS                 (1024l)
    #define NAND_SIZE                       0x1080000//(NAND_NUM_BLOCKS * NAND_NUM_PAGES_PER_BLK * NAND_PAGE_SIZE)
    // PMP Register Defines
    #define NAND_PMCON      (PMP_ON | PMP_CS2_CS1_OFF | PMP_READ_WRITE_EN)
    #define NAND_PMMODE     (PMP_IRQ_READ_WRITE | PMP_MODE_MASTER2 | (PMP_WAIT_BEG_1 | PMP_WAIT_MID_2 | PMP_WAIT_END_1))
    #define NAND_PMAEN      (PMP_PEN_OFF)
    #define CONTROL     (PMP_ON | PMP_IDLE_CON | PMP_MUX_OFF | PMP_READ_WRITE_EN |\
                         PMP_CS2_CS1_OFF | PMP_LATCH_POL_HI | PMP_CS2_POL_LO | PMP_CS1_POL_LO |\
                         PMP_WRITE_POL_LO | PMP_READ_POL_LO)
    #define MODE        (PMP_IRQ_OFF | PMP_AUTO_ADDR_OFF | PMP_DATA_BUS_8 | PMP_MODE_MASTER2 |\
                         PMP_WAIT_BEG_3 | PMP_WAIT_MID_7 | PMP_WAIT_END_3 )
    #define PORT        (PMP_PEN_ALL)
    //#define INTERRUPT   (PMP_INT_OFF)
    #define EXT_ADDRS               0x4000*1000
    //PINS SET
    #define NANDAddressLatchDirection()     (mPORTDSetPinsDigitalOut(BIT_3))
    #define NANDAddressLatchEnable()        (mPORTDSetBits(BIT_3))
    #define NANDAddressLatchDisable()       (mPORTDClearBits(BIT_3))

    #define NANDChipDirection()             (mPORTDSetPinsDigitalOut(BIT_1))
    #define NANDChipEnable()                (mPORTDClearBits(BIT_1))
    #define NANDChipDisable()               (mPORTDSetBits(BIT_1))

    #define NANDCommandLatchDirection()     (mPORTCSetPinsDigitalOut(BIT_3))//2
    #define NANDCommandLatchEnable()        (mPORTCSetBits(BIT_3))
    #define NANDCommandLatchDisable()       (mPORTCClearBits(BIT_3))

    #define NANDReadyBusyDirection()        (mPORTDSetPinsDigitalIn(BIT_2))
    #define NANDReady()                     (mPORTDReadBits(BIT_2))
    #define NANDBusy()                      (!mPORTDReadBits(BIT_2))

    #define WPDirection()        (mPORTBSetPinsDigitalOut(BIT_7))
    #define WPNOPROTECT()                     (mPORTBSetBits(BIT_7))
    #define WPPROTECT()                      (mPORTBClearBits(BIT_7))
    #define NAND_CS_HIGH            mPORTDSetBits(BIT_1)
    #define NAND_CS_LOW             mPORTDClearBits(BIT_1)

#ifdef	__cplusplus
}
#endif

#endif	/* NAND_H */

