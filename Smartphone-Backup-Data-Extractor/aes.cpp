#include <stdio.h>
#include "aes.h"


#define ff_mult(a,b)    (a && b ? pow_tab[(log_tab[a] + log_tab[b]) % 255] : 0)

#define f_rn(bo, bi, n, k)                          \
	t1 = byte(bi[n],0);								\
	t2 = byte(bi[(n + 1) & 3],1);					\
	t3 = byte(bi[(n + 2) & 3],2);					\
	t4 = byte(bi[(n + 3) & 3],3);					\
    bo[n] =  ft_tab[0][t1] ^						\
             ft_tab[1][t2] ^						\
             ft_tab[2][t3] ^						\
             ft_tab[3][t4] ^ *(k + n)

#define i_rn(bo, bi, n, k)                          \
	t1 = byte(bi[n],0);								\
	t2 = byte(bi[(n + 3) & 3],1);					\
	t3 = byte(bi[(n + 2) & 3],2);					\
	t4 = byte(bi[(n + 1) & 3],3);					\
    bo[n] =  it_tab[0][t1] ^						\
             it_tab[1][t2] ^						\
             it_tab[2][t3] ^					    \
             it_tab[3][t4] ^ *(k + n)

#ifdef LARGE_TABLES

#define ls_box(x)                \
    ( fl_tab[0][byte(x, 0)] ^    \
      fl_tab[1][byte(x, 1)] ^    \
      fl_tab[2][byte(x, 2)] ^    \
      fl_tab[3][byte(x, 3)] )

#define f_rl(bo, bi, n, k)                          \
    bo[n] =  fl_tab[0][byte(bi[n],0)] ^             \
             fl_tab[1][byte(bi[(n + 1) & 3],1)] ^   \
             fl_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
             fl_tab[3][byte(bi[(n + 3) & 3],3)] ^ *(k + n)

#define i_rl(bo, bi, n, k)                          \
    bo[n] =  il_tab[0][byte(bi[n],0)] ^             \
             il_tab[1][byte(bi[(n + 3) & 3],1)] ^   \
             il_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
             il_tab[3][byte(bi[(n + 1) & 3],3)] ^ *(k + n)

#else

#define ls_box(x)                            \
    ((ULONG)sbx_tab[byte(x, 0)] <<  0) ^    \
    ((ULONG)sbx_tab[byte(x, 1)] <<  8) ^    \
    ((ULONG)sbx_tab[byte(x, 2)] << 16) ^    \
    ((ULONG)sbx_tab[byte(x, 3)] << 24)

#define f_rl(bo, bi, n, k)                                      \
    bo[n] = (ULONG)sbx_tab[byte(bi[n],0)] ^                    \
        rotl(((ULONG)sbx_tab[byte(bi[(n + 1) & 3],1)]),  8) ^  \
        rotl(((ULONG)sbx_tab[byte(bi[(n + 2) & 3],2)]), 16) ^  \
        rotl(((ULONG)sbx_tab[byte(bi[(n + 3) & 3],3)]), 24) ^ *(k + n)

#define i_rl(bo, bi, n, k)                                      \
    bo[n] = (ULONG)isb_tab[byte(bi[n],0)] ^                    \
        rotl(((ULONG)isb_tab[byte(bi[(n + 3) & 3],1)]),  8) ^  \
        rotl(((ULONG)isb_tab[byte(bi[(n + 2) & 3],2)]), 16) ^  \
        rotl(((ULONG)isb_tab[byte(bi[(n + 1) & 3],3)]), 24) ^ *(k + n)

#endif

void cist_aes::gen_tabs(void)
{   
	ULONG  i, t;
    UCHAR  p, q;

    /* log and power tables for GF(2**8) finite field with  */
    /* 0x011b as modular polynomial - the simplest prmitive */
    /* root is 0x03, used here to generate the tables       */

    for(i = 0,p = 1; i < 256; ++i)
    {
        pow_tab[i] = (UCHAR)p;
		log_tab[p] = (UCHAR)i;

        p = p ^ (p << 1) ^ (p & 0x80 ? 0x01b : 0);
    }


    log_tab[1] = 0; p = 1;

    for(i = 0; i < 10; ++i)
    {
        rco_tab[i] = p; 

        p = (p << 1) ^ (p & 0x80 ? 0x1b : 0);
    }

    /* note that the affine byte transformation matrix in   */
    /* rijndael specification is in big endian format with  */
    /* bit 0 as the most significant bit. In the remainder  */
    /* of the specification the bits are numbered from the  */
    /* least significant end of a byte.                     */

    for(i = 0; i < 256; ++i)
    {   
        p = (i ? pow_tab[255 - log_tab[i]] : 0); q = p; 
        q = (q >> 7) | (q << 1); p ^= q; 
        q = (q >> 7) | (q << 1); p ^= q; 
        q = (q >> 7) | (q << 1); p ^= q; 
        q = (q >> 7) | (q << 1); p ^= q ^ 0x63; 
        sbx_tab[i] = p; isb_tab[p] = (UCHAR)i; 
    }

    for(i = 0; i < 256; ++i)
    {
        p = sbx_tab[i]; 

#ifdef  LARGE_TABLES        
        
        t = p; 
		fl_tab[0][i] = t;
        fl_tab[1][i] = rotl(t,  8);
        fl_tab[2][i] = rotl(t, 16);
        fl_tab[3][i] = rotl(t, 24);
#endif
        t = ((ULONG)ff_mult(2, p)) |
            ((ULONG)p <<  8) |
            ((ULONG)p << 16) |
            ((ULONG)ff_mult(3, p) << 24);
        
        ft_tab[0][i] = t;
        ft_tab[1][i] = rotl(t,  8);
        ft_tab[2][i] = rotl(t, 16);
        ft_tab[3][i] = rotl(t, 24);

        p = isb_tab[i]; 

#ifdef  LARGE_TABLES        
        
        t = p; 
		il_tab[0][i] = t; 
        il_tab[1][i] = rotl(t,  8); 
        il_tab[2][i] = rotl(t, 16); 
        il_tab[3][i] = rotl(t, 24);
#endif 
        t = ((ULONG)ff_mult(14, p)) |
            ((ULONG)ff_mult( 9, p) <<  8) |
            ((ULONG)ff_mult(13, p) << 16) |
            ((ULONG)ff_mult(11, p) << 24);
        
        it_tab[0][i] = t; 
        it_tab[1][i] = rotl(t,  8); 
        it_tab[2][i] = rotl(t, 16); 
        it_tab[3][i] = rotl(t, 24); 
    }
    tab_gen = 1;
}

#define star_x(x) (((x) & 0x7f7f7f7f) << 1) ^ ((((x) & 0x80808080) >> 7) * 0x1b)

#define imix_col(y,x)       \
    u   = star_x(x);        \
    v   = star_x(u);        \
    w   = star_x(v);        \
    t   = w ^ (x);          \
   (y)  = u ^ v ^ w;        \
   (y) ^= rotr(u ^ t,  8) ^ \
          rotr(v ^ t, 16) ^ \
          rotr(t,24)

/* initialise the key schedule from the user supplied key   */

#define loop4(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[4 * i];     e_key[4 * i + 4] = t;    \
    t ^= e_key[4 * i + 1]; e_key[4 * i + 5] = t;    \
    t ^= e_key[4 * i + 2]; e_key[4 * i + 6] = t;    \
    t ^= e_key[4 * i + 3]; e_key[4 * i + 7] = t;    \
}

#define loop6(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[6 * i];     e_key[6 * i + 6] = t;    \
    t ^= e_key[6 * i + 1]; e_key[6 * i + 7] = t;    \
    t ^= e_key[6 * i + 2]; e_key[6 * i + 8] = t;    \
    t ^= e_key[6 * i + 3]; e_key[6 * i + 9] = t;    \
    t ^= e_key[6 * i + 4]; e_key[6 * i + 10] = t;   \
    t ^= e_key[6 * i + 5]; e_key[6 * i + 11] = t;   \
}

#define loop8(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[8 * i];     e_key[8 * i + 8] = t;    \
    t ^= e_key[8 * i + 1]; e_key[8 * i + 9] = t;    \
    t ^= e_key[8 * i + 2]; e_key[8 * i + 10] = t;   \
    t ^= e_key[8 * i + 3]; e_key[8 * i + 11] = t;   \
    t  = e_key[8 * i + 4] ^ ls_box(t);              \
    e_key[8 * i + 12] = t;                          \
    t ^= e_key[8 * i + 5]; e_key[8 * i + 13] = t;   \
    t ^= e_key[8 * i + 6]; e_key[8 * i + 14] = t;   \
    t ^= e_key[8 * i + 7]; e_key[8 * i + 15] = t;   \
}

//----------------------------------------------------------

cist_aes::cist_aes()
{
	tab_gen = 0;
}

cist_aes::~cist_aes()
{

}

void cist_aes::AES_KeySchedule(const UCHAR in_key[], const ULONG key_len)
{   
	ULONG  i, t, u, v, w;

    if(!tab_gen)
	   gen_tabs();

    k_len = (key_len + 31) / 32;

    e_key[0] = u4byte_in(in_key     ); 
	e_key[1] = u4byte_in(in_key +  4);
    e_key[2] = u4byte_in(in_key +  8); 
    e_key[3] = u4byte_in(in_key + 12);

    switch(k_len)
    {
        case 4: t = e_key[3];
                for(i = 0; i < 10; ++i) 
                    loop4(i);
                break;

        case 6: e_key[4] = u4byte_in(in_key + 16); t = e_key[5] = u4byte_in(in_key + 20);
                for(i = 0; i < 8; ++i) 
                    loop6(i);
                break;

        case 8: e_key[4] = u4byte_in(in_key + 16); e_key[5] = u4byte_in(in_key + 20);
                e_key[6] = u4byte_in(in_key + 24); t = e_key[7] = u4byte_in(in_key + 28);
                for(i = 0; i < 7; ++i) 
                    loop8(i);
                break;
    }

    d_key[0] = e_key[0]; d_key[1] = e_key[1];
    d_key[2] = e_key[2]; d_key[3] = e_key[3];

    for(i = 4; i < 4 * k_len + 24; ++i)
    {
        imix_col(d_key[i], e_key[i]);
    }

    return;
}

/* encrypt a block of text  */

#define f_nround(bo, bi, k) \
    f_rn(bo, bi, 0, k);     \
    f_rn(bo, bi, 1, k);     \
    f_rn(bo, bi, 2, k);     \
    f_rn(bo, bi, 3, k);     \
    k += 4

#define f_lround(bo, bi, k) \
    f_rl(bo, bi, 0, k);     \
    f_rl(bo, bi, 1, k);     \
    f_rl(bo, bi, 2, k);     \
    f_rl(bo, bi, 3, k)

void cist_aes::AES_ENC(const UCHAR in_blk[16], UCHAR out_blk[16])
{  
	ULONG  b0[4], b1[4], *kp;
	ULONG  t1, t2, t3, t4;
    b0[0] = u4byte_in(in_blk    ) ^ e_key[0]; 
	b0[1] = u4byte_in(in_blk +  4) ^ e_key[1];
    b0[2] = u4byte_in(in_blk + 8) ^ e_key[2]; 
	b0[3] = u4byte_in(in_blk + 12) ^ e_key[3];

    kp = e_key + 4;

    if(k_len > 6)
    {
        f_nround(b1, b0, kp); f_nround(b0, b1, kp);
    }

    if(k_len > 4)
    {
        f_nround(b1, b0, kp); f_nround(b0, b1, kp);
    }

    f_nround(b1, b0, kp); f_nround(b0, b1, kp);
    f_nround(b1, b0, kp); f_nround(b0, b1, kp);
    f_nround(b1, b0, kp); f_nround(b0, b1, kp);
    f_nround(b1, b0, kp); f_nround(b0, b1, kp);
    f_nround(b1, b0, kp); f_lround(b0, b1, kp);

    u4byte_out(out_blk,      b0[0]); u4byte_out(out_blk +  4, b0[1]);
    u4byte_out(out_blk +  8, b0[2]); u4byte_out(out_blk + 12, b0[3]);
}

/* decrypt a block of text  */

#define i_nround(bo, bi, k) \
    i_rn(bo, bi, 0, k);     \
    i_rn(bo, bi, 1, k);     \
    i_rn(bo, bi, 2, k);     \
    i_rn(bo, bi, 3, k);     \
    k -= 4

#define i_lround(bo, bi, k) \
    i_rl(bo, bi, 0, k);     \
    i_rl(bo, bi, 1, k);     \
    i_rl(bo, bi, 2, k);     \
    i_rl(bo, bi, 3, k)

void cist_aes::AES_DEC(const UCHAR in_blk[16], UCHAR out_blk[16])
{
	ULONG  b0[4], b1[4], *kp;
	ULONG  t1, t2, t3, t4;

    b0[0] = u4byte_in(in_blk     ) ^ e_key[4 * k_len + 24]; 
    b0[1] = u4byte_in(in_blk +  4) ^ e_key[4 * k_len + 25];
    b0[2] = u4byte_in(in_blk +  8) ^ e_key[4 * k_len + 26]; 
    b0[3] = u4byte_in(in_blk + 12) ^ e_key[4 * k_len + 27];

    kp = d_key + 4 * (k_len + 5);

    if(k_len > 6)
    {
        i_nround(b1, b0, kp); i_nround(b0, b1, kp);
    }

    if(k_len > 4)
    {
        i_nround(b1, b0, kp); i_nround(b0, b1, kp);
    }

    i_nround(b1, b0, kp); i_nround(b0, b1, kp);
    i_nround(b1, b0, kp); i_nround(b0, b1, kp);
    i_nround(b1, b0, kp); i_nround(b0, b1, kp);
    i_nround(b1, b0, kp); i_nround(b0, b1, kp);
    i_nround(b1, b0, kp); i_lround(b0, b1, kp);

    u4byte_out(out_blk,     b0[0]); u4byte_out(out_blk +  4, b0[1]);
    u4byte_out(out_blk + 8, b0[2]); u4byte_out(out_blk + 12, b0[3]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// o AES_CBC_ENC()	: CBC 모드에서의 WBAES 암호화 함수
// o 입력				: In		- 입력 (평문)
//						: Out		- 출력 (암호문)
//						: Length	- 길이
//						: IVEC		- 초기값
// o 출력				: Out		- 암호문
///////////////////////////////////////////////////////////////////////////////////////////////////
void cist_aes::AES_CBC_ENC(const unsigned char *In, unsigned char *Out, const unsigned long Length, unsigned char *IVEC)
{
	unsigned long i;
	unsigned long len = Length;
	const unsigned char *IV = IVEC;

	while (len >= 16)
	{
		for (i = 0; i < 16; i++)
			Out[i] = In[i] ^ IV[i];
			
		AES_ENC(Out, Out);
		
		IV = Out;
		
		len -= 16;
		In += 16;
		Out += 16;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// o AES_CBC_DEC()	: CBC 모드에서의 WBAES 복호화 함수
// o 입력				: In		- 입력 (암호문)
//						: Out		- 출력 (평문)
//						: Length	- 길이
//						: IVEC		- 초기값
// o 출력				: Out		- 평문
///////////////////////////////////////////////////////////////////////////////////////////////////
void cist_aes::AES_CBC_DEC(const unsigned char *In, unsigned char *Out, const unsigned long Length, unsigned char *IVEC)
{
	unsigned long i;
	unsigned long len = Length;
	const unsigned char *IV = IVEC;

	while (len >= 16)
	{
		AES_DEC(In, Out);
		
		for (i = 0; i < 16; ++i)
			Out[i] ^= IV[i];
			
		IV = In;
		
		len -= 16;
		In  += 16;
		Out += 16;
	}
}


