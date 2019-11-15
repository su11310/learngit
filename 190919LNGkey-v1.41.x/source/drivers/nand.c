/*
 * File:   colck.c
 * Author: jereh
 *
 * Created on 2014_02_22
 */

#include "../includes/global_def.h"

void ConvertAddr(UINT32 addr, NAND_ADDR_ARR3A *nand_addr);

UINT8 nandGetData(void)
{
    return (UINT8)PMPMasterRead();
}
void nandWriteData(UINT8 data)
{
    PMPMasterWrite(data);
	while(mIsPMPBusy());
}
void nandWriteCommand(UINT8 cmd)
{
    NANDAddressLatchDisable();
    NANDCommandLatchEnable();
    PMPMasterWrite(cmd);
    while(mIsPMPBusy());
    NANDCommandLatchDisable();
}
void nandWriteAddress(NAND_ADDR_ARR3A addr)
{
    NANDCommandLatchDisable();
    NANDAddressLatchEnable();
    PMPMasterWrite(addr.addr[0]);
    PMPMasterWrite(addr.addr[1]);
    PMPMasterWrite(addr.addr[2]);
//    PMPMasterWrite(addr.addr[3]);
 // PMPMasterWrite(0x00);
//    PMPMasterWrite(addr.addr[4]);
	while(mIsPMPBusy());
    NANDAddressLatchDisable();
}
void WriteBlockAddress(NAND_ADDR_ARR3A addr)
{
    NANDCommandLatchDisable();
    NANDAddressLatchEnable();
    PMPMasterWrite(addr.addr[1]);
    PMPMasterWrite(addr.addr[2]);
//    PMPMasterWrite(addr.addr[3]);
//    PMPMasterWrite(addr.addr[4]);
	while(mIsPMPBusy());
    NANDAddressLatchDisable();
}

void _NANDRead(NAND_ADDR_ARR3A addr)
{
    nandWriteCommand(NAND_CMD_PAGE_RD_C1);
    nandWriteAddress(addr);
//    WriteCommand(NAND_CMD_PAGE_RD_C2);
    while(NANDBusy())
        ;
    // burn a byte read
    nandGetData();
}
void _NANDc2Read(NAND_ADDR_ARR3A addr)
{
    nandWriteCommand(NAND_CMD_PAGE_RD_C3);
    nandWriteAddress(addr);
//    WriteCommand(NAND_CMD_PAGE_RD_C2);
    while(NANDBusy());
    // burn a byte read
    nandGetData();
}
/*Signature_3A2B NANDGetStatus(void)
{
    UINT8 status1,status2;
    UINT ctrl, mode, address,status;
    Signature_3A2B pp;
     HWP_NANDChipEnable();
    WriteCommand(NAND_CMD_READ_STATUS);
    pp.Manufacturer = GetData();
    pp.Device_code = GetData();
    HWP_NANDChipDisable();
 //   status=status1<<8+status2;
    return pp;
}*/
UINT8 NANDGetStatus0(void)
{
    UINT8 status1,status2;
    UINT ctrl, mode, address,status;
    NANDChipEnable();
    nandWriteCommand(NAND_CMD_READ_STATUS);
    nandGetData();
    status1 = nandGetData();
//    status2 = GetData();
    NANDChipDisable();
 //   status=(status1<<8)|status2;
    return status1;
}
BOOL _NANDWrite(NAND_ADDR_ARR3A addr, UINT8 *dat, UINT32 size)
{
    UINT32 i;
    nandWriteCommand(NAND_CMD_PROGRAM_PAGE_C1);
    nandWriteAddress(addr);
    for(i = 0; i < size; i++)
    {
        nandWriteData(*dat);
        dat++;
    }
    nandWriteCommand(NAND_CMD_PROGRAM_PAGE_C2);


    while(NANDBusy())
        ;

    if(NANDGetStatus0() & NAMD_STATUS_FAIL)
        return FALSE;

    return TRUE;

}

UINT16 onand_getID(void)
//UINT16 NANDGetID(void)
{
    UINT8 status1,status2;
    UINT ctrl, mode, address,status;
    NANDChipEnable();
    nandWriteCommand(NAND_CMD_READ_ID);
    nandGetData();
    status1 = nandGetData();
    status2 = nandGetData();
    NANDChipDisable();
    status=(status1<<8)|status2;
    return status;
}

UINT32 onand_wtBuff_ex(UINT32 addr, UINT8 *data, UINT32 size)
{
    UINT32  num_bytes = 0;
    UINT ctrl, mode, address;

    if((!size) || (addr >= NAND_SIZE))
        return 0;

     while(size)
    {
        NAND_ADDR_ARR3A   nand_addr;
        UINT32          page_bytes;

        NANDChipEnable();

        ConvertAddr(addr, &nand_addr);

        page_bytes = addr & (NAND_PAGE_SIZE - 1);
        page_bytes = NAND_PAGE_SIZE - page_bytes;

        if(size < page_bytes)
            page_bytes = size;

        if(!_NANDWrite(nand_addr, data, page_bytes))
            break;

        size -= page_bytes;
        num_bytes += page_bytes;
        addr += page_bytes;
    }

    NANDChipDisable();

     return num_bytes;
}
UINT32 onand_wtBuff(UINT32 addr, UINT8 *data, UINT32 size)
{
//    UINT32  num_bytes = 0;
//    UINT ctrl, mode, address;
    UINT8 k;
    UINT8 flashw[512];
    memset(flashw,0xff,512);
    k=(addr/128)%4;
    if((k==0)||(k==1))
    {
        onand_wtBuff_ex(addr, data, size);
    }
    if(k==2)
    {
        onand_rdBuff(addr-256, FLASH_R_BUF, 256);
        memcpy(FLASH_R_BUF+256,data,128);
        onand_wtBuff_ex(addr-256, FLASH_R_BUF, 384);
    }
    if(k==3)
    {
        onand_rdBuff(addr-384, FLASH_R_BUF, 384);
        memcpy(FLASH_R_BUF+384,data,128);
        onand_wtBuff_ex(addr-384,  FLASH_R_BUF, 512);
    }
    delay_ms(100);
         return size;
}
UINT32 onand_rdBuff(UINT32 addr, unsigned char *data, UINT32 size)
{
    UINT32  num_bytes = 0;
    UINT ctrl, mode, address;
    UINT8 k;
    delay_ms(100);
    if((!size) || (addr >= NAND_SIZE))
        return 0;
     NANDChipEnable();
    while(size)
    {
        NAND_ADDR_ARR3A   nand_addr;
        UINT32          page_bytes;
        UINT32          i;
        ConvertAddr(addr, &nand_addr);
        k=(addr/128)%4;
//              k=cur_max_recid%4;//找出在页中位置
        if((k==0)||(k==1))
        { _NANDRead(nand_addr);    }
        if((k==2)||(k==3))
        {_NANDc2Read(nand_addr); }

        page_bytes = addr & (NAND_PAGE_SIZE - 1);
        page_bytes = NAND_PAGE_SIZE - page_bytes;

        if(size < page_bytes)
            page_bytes = size;
        for(i = 0; i < page_bytes; i++)
        {
            *data = nandGetData();
            data++;
        }
        size -= page_bytes;
        num_bytes += page_bytes;
        addr += page_bytes;
    }

    NANDChipDisable();
     return num_bytes;
}



BOOL onand_BlockErase(UINT32 addr)
//BOOL NANDBlockErase(UINT32 addr)
{
    NAND_ADDR_ARR3A   nand_addr;
    UINT ctrl, mode, address;

    ConvertAddr(addr, &nand_addr);

    NANDChipEnable();
    nandWriteCommand(NAND_CMD_BLOCK_ERASE_C1);
    WriteBlockAddress(nand_addr);
    nandWriteCommand(NAND_CMD_BLOCK_ERASE_C2);

    while(NANDBusy());

    NANDChipDisable();

    if(NANDGetStatus0() & NAMD_STATUS_FAIL)
        return FALSE;

    return TRUE;
}

UINT32 NANDGetPageSize(void)
{
    return NAND_PAGE_SIZE;
}

UINT32 NANDGetSpareSize(void)
{
    return NAND_SPARE_SIZE;
}

UINT32 NANDGetNumberofPagesPerBlock(void)
{
    return NAND_NUM_PAGES_PER_BLK;
}

UINT32 NANDGetNumberofBlocks(void)
{
    return NAND_NUM_BLOCKS;
}

UINT32 NANDGetSize(void)
{
    return NAND_SIZE;
}


void NANDReset(void)
{
}

void ConvertAddr(UINT32 addr, NAND_ADDR_ARR3A *nand_addr)
{
    NAND_ADDR3A   *__addr;

    __addr = (NAND_ADDR3A *)&addr;

    nand_addr->addr[0] = 0;
    nand_addr->addr[1] = 0;
    nand_addr->addr[2] = 0;
//    nand_addr->addr[3] = 0;
//    nand_addr->addr[4] = 0;

    nand_addr->column    = __addr->column;
    nand_addr->page      = __addr->page;
     nand_addr->block     = __addr->block;
//    nand_addr->block     = __addr->block & 0x3FF;
//    nand_addr->block_upp = __addr->block >> 10;
}

//void NAND128W3A2B_INIT()
void onand_init(void)
{
    //SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    mCNOpen(CONFIG, PINS, PULLUPS);
    mPMPOpen(NAND_PMCON, NAND_PMMODE, NAND_PMAEN, INTERRUPT_NAND);
    WPDirection();
    WPNOPROTECT();
    NANDAddressLatchDisable();
    NANDChipDisable();
    NANDCommandLatchDisable();
    NANDAddressLatchDirection();
    NANDChipDirection();
    NANDCommandLatchDirection();
    NANDReadyBusyDirection();
    NANDReset();
}
