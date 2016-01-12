#ifndef __AES_H__
#define __AES_H__ 100
	
/* system independent types */

#ifndef ULONG
typedef unsigned long ULONG;
//typedef ULONG* ULONG_PTR;
#endif

#ifndef SLONG
typedef signed long SLONG;
typedef SLONG* SLONG_PTR;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
typedef USHORT* USHORT_PTR;
#endif

#ifndef SSHORT
typedef signed short SSHORT;
typedef SSHORT* SSHORT_PTR;
#endif

#ifndef UINT
typedef unsigned int UINT;
//typedef UINT* UINT_PTR;
#endif

#ifndef SINT
typedef signed int SINT;
typedef SINT* SINT_PTR;
#endif

#ifndef UCHAR
typedef unsigned char UCHAR;
typedef UCHAR* UCHAR_PTR;
#endif

#ifndef SCHAR
typedef char SCHAR;
typedef SCHAR* SCHAR_PTR;
#endif

/* system dependent types */

#ifndef UINT8
typedef unsigned char  UINT8;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef UINT32
typedef unsigned int   UINT32;
#endif

#define SUCCESS	1
#define FAIL	0

#define BITMASK_LONG        0xffffffff
#define BITMASK_HIGHER_LONG 0xffff0000 
#define BITMASK_LOWER_LONG  0x0000ffff
#define HIGHER_MSB_ONE		0x80000000
#define LOWER_MSB_ONE		0x00008000
#define HIGHER_LSB_ONE		0x00010000
#define LOWER_LSB_ONE		0x00000001
#define LONG_BITS			32
#define HALF_LONG_BITS		16

#define LITTLE_ENDIAN

#ifdef _MSC_VER

	#include <stdlib.h>
	#pragma intrinsic(_lrotr,_lrotl)
	#define rotr(x,n) _lrotr(x,n)
	#define rotl(x,n) _lrotl(x,n)

#else

	#define rotr(x,n)   (((x) >> ((int)(n))) | ((x) << (32 - (int)(n))))
	#define rotl(x,n)   (((x) << ((int)(n))) | ((x) >> (32 - (int)(n))))

#endif

// Invert byte order in a 32 bit variable
#define bswap(x)    (rotl(x, 8) & 0x00ff00ff | rotr(x, 8) & 0xff00ff00)

// Extract byte from a 32 bit quantity (little endian notation)
#define byte(x,n)   ((UCHAR)((x) >> (8 * n)))

//Input or output a 32 bit word in machine order
#ifdef  LITTLE_ENDIAN

	#define u4byte_in(x)            (*(ULONG*)(x))
	#define u4byte_out(x, v)        (*(ULONG*)(x) = (v)) 

#else

	#define u4byte_in(x)            bswap(*(ULONG*)(x))
	#define u4byte_out(x, v)        (*(ULONG*)(x) = bswap(v))

#endif


#define LARGE_TABLES

//-----------------------------

class cist_aes
{
public:
	cist_aes();
	~cist_aes();


public:
	UCHAR  pow_tab[256];
	UCHAR  log_tab[256];
	UCHAR  sbx_tab[256];
	UCHAR  isb_tab[256];
	ULONG  rco_tab[ 10];
	ULONG  ft_tab[4][256];
	ULONG  it_tab[4][256];

#ifdef  LARGE_TABLES
	ULONG  fl_tab[4][256];
	ULONG  il_tab[4][256];
#endif

	ULONG  tab_gen;

	ULONG  k_len;
	ULONG  e_key[80];
	ULONG  d_key[80];


public:
	void AES_KeySchedule(const UCHAR in_key[], const ULONG key_len);
	void AES_ENC(const UCHAR in_blk[16], UCHAR out_blk[16]);
	void AES_DEC(const UCHAR in_blk[16], UCHAR out_blk[16]);

	void AES_CBC_ENC(const unsigned char *In, unsigned char *Out, const unsigned long Length, unsigned char *IVEC);
	void AES_CBC_DEC(const unsigned char *In, unsigned char *Out, const unsigned long Length, unsigned char *IVEC);


private:
	void gen_tabs(void);
};

#endif

