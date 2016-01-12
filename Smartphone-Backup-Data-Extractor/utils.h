#ifndef __UTILSH__
#define __UTILSH__
#define __UTILS_ERROR__	0

#pragma once
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atlstr.h>
#include <io.h>
#include <direct.h>

int error_output( char* func, char* message);

enum ENUM_getByteArrayOpt { getByteArray_None, getByteArray_Fix };
int getByteArray( char* dstArray, int dstArraySize, char* srcArray, int srcArraySize, unsigned int getSize, unsigned int startOffset = 0 );
int getByteArray( char* dstArray, int dstArraySize, FILE* fd, unsigned int getSize, long long startOffset = 0, int opt = getByteArray_None );
long long getFileSize( FILE* fd );

/* Data extraction */
long extractDataToFileByOffset( FILE* Dst_fd, FILE* Src_fd, long start_Offset, long end_Offset );
long extractDataToFileBySize( FILE* Dst_fd, FILE* Src_fd, long start_Offset, long extractDataSize );

/* string to hex */
/* Function	: Hexadecimal(char) -> Hexadecimal(char)
 * return	: Length of hexByte(error : -1)
*/
int hexCharTohexByte( char* Dst_buf, int Dst_buf_size, char* hexChar_buf, int hexChar_buf_size );
int hexByteToChar( char* Dst_buf, int Dst_buf_size, char* hexByte_buf, int hexByte_buf_size );
int charToHex( char c );
#endif