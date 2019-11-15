
#ifndef _DES_H_
#define _DES_H_

#define GET_BIT(p_array, bit_index)  \
			((p_array[(bit_index) >> 3] >> (7 - ((bit_index) & 0x07))) & 0x01)

#define SET_BIT(p_array, bit_index, bit_val) \
			if (1 == (bit_val)) \
			{\
				p_array[(bit_index) >> 3] |= 0x01 << (7 - ((bit_index) & 0x07));\
			}\
			else\
			{\
				p_array[(bit_index) >> 3] &= ~(0x01 << (7 - ((bit_index) & 0x07)));\
			}

typedef enum
{
	DES_ENCRYPT = 0,
	DES_DECRYPT = 1
}DES_MODE;

void des(char * p_data, char * p_key, char * p_output, DES_MODE mode);
#endif //#ifndef _DES_H_