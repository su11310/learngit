/*
 * File:   store.c
 * Author: jereh
 *
 * Created on 2014_02_23
 */

#include "../includes/global_def.h"

BOOL ostore_set_paras(UINT8 id, UINT8* vpara, UINT8 len)
{
    if( len == o24lcxxx_write_bytes(_SYSPARAS_EEP_ADDR+id*4, vpara,len)) return TRUE;
    return FALSE;
}

BOOL ostore_read_paras(UINT8 id, UINT8* vpara, UINT8 len)
{
    //o24lcxxx_read_bytes(_SYSPARAS_EEP_ADDR+id*4, vpara,len);
    o24lcxxx_read_bytes_ex(_SYSPARAS_EEP_ADDR+id*4, vpara,len);
    return TRUE;
}

double ostore_paras_rdfloat(UINT8 id)
{
    float frd = 0;
    ostore_read_paras(id,(UINT8*)&frd,4);
    return frd;
}

BOOL ostore_paras_wtfloat(UINT8 id, float fwt)
{
    //cur_un_float.dt_float = fwt;
    //return ostore_set_paras(id,(UINT8*)&cur_un_float.dt_uc[0],4);
    return ostore_set_paras(id,(UINT8*)&fwt,4);
}

UINT16 ostore_paras_rdint(UINT8 id)
{
    UINT16 rd = 0;
    ostore_read_paras(id,(UINT8*)&rd,2);
    return rd;
}

BOOL ostore_paras_wtint(UINT8 id, UINT16 wt)
{
    UINT16 rd = 0;
    return ostore_set_paras(id,(UINT8*)&wt,2);
}

UINT8 ostore_paras_rdchar(UINT8 id)
{
    UINT16 rd = 0;
    ostore_read_paras(id,(UINT8*)&rd,1);
    return rd;
}

BOOL ostore_paras_wtchar(UINT8 id, UINT8 wt)
{
    return ostore_set_paras(id,(UINT8*)&wt,1);
}