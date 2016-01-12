#include "StdAfx.h"
#pragma once
#include "utils.h"

int error_output( char* func, char* message )
{
	fprintf(stderr, "FUNC:[%s] - %s", func, message );
	return 0;
}

/* 데이터 추출 */
int getByteArray( char* dstArray, int dstArraySize, char* srcArray, int srcArraySize, unsigned int getSize, unsigned int startOffset )
{
	//예외 처리
	if( dstArraySize < getSize )				return -1;
	if( srcArraySize < startOffset )			return -1;
	if( srcArraySize < startOffset + getSize )	return -1;
	memcpy_s( dstArray, dstArraySize, srcArray + startOffset, srcArraySize - startOffset );

	return getSize;
}
int getByteArray( char* dstArray, int dstArraySize, FILE* fd, unsigned int getSize, long long startOffset, int opt )
{
	long long fileSize = 0;
	long long org_offset = 0;
	
	// 파일 정보 저장
	fileSize = getFileSize( fd );
	org_offset = _ftelli64( fd );

	/* 예외 처리 */
	if( dstArraySize < getSize )			return -1;
	if( fileSize < startOffset )			return -1;
	if( fileSize < startOffset + getSize )	return -1;
	
	/* 파일에서 Byte array 가져오기 */
	if( startOffset <= org_offset )
	{
		_fseeki64( fd, startOffset, SEEK_SET );
	}
	else
	{
		_fseeki64( fd, startOffset - org_offset, SEEK_CUR );
	}
	
	/* 파일 읽기 */
	int ret_val = fread_s( dstArray, dstArraySize, 1, getSize, fd );

	/* 후속 처리( opt ) */
	if( opt == getByteArray_Fix )
	{
		long long file_cur = 0;

		file_cur = _ftelli64( fd );
		if( org_offset > file_cur )
		{
			_fseeki64( fd, org_offset - file_cur, SEEK_CUR );
		}
		else
			_fseeki64(fd, org_offset, SEEK_SET );
	}

	return ret_val;
}

long long getFileSize( FILE* fd )
{
	long long fileSize = 0;
	long long org_offset = 0;
	
	//
	org_offset = _ftelli64( fd );

	//Get size of file with moving file pointer to end
	_fseeki64( fd, 0, SEEK_END );
	fileSize = _ftelli64( fd );
	
	//Retern of file Pointer to original offset
	if( org_offset != fileSize )
		_fseeki64( fd, org_offset, SEEK_SET );

	//Return value
	return fileSize;
}

/* Data extraction */
long extractDataToFileBySize( FILE* Dst_fd, FILE* Src_fd, long start_Offset, long extractDataSize )
{
	fseek( Src_fd, start_Offset, SEEK_SET );
	
	char buf[BUFSIZ] = {0, };

	long dataSize = extractDataSize;
	
	long remain = dataSize;
	int ret = 0;
	for( int i = 0; i < dataSize / BUFSIZ; ++ i)
	{
		ret = fread_s( buf, BUFSIZ, 1, BUFSIZ, Src_fd );
		if( ret == NULL )
			return dataSize - remain;
		fwrite( buf, 1, BUFSIZ, Dst_fd );
		remain -= ret;
	}
	
	ret = fread_s( buf, BUFSIZ, 1, remain, Src_fd );
	if( ret == NULL )
			return -1;
	fwrite( buf, 1, remain, Dst_fd );
	remain -= remain;

	return dataSize;
}
long extractDataToFileByOffset( FILE* Dst_fd, FILE* Src_fd, long start_Offset, long end_Offset )
{
	return extractDataToFileBySize( Dst_fd, Src_fd, start_Offset, end_Offset - start_Offset );
}


int hexCharTohexByte( char* Dst_buf, int Dst_buf_size, char* Src_buf, int Src_buf_size )
{
	if( Dst_buf_size < Src_buf_size * 2 )
		return __UTILS_ERROR__;

	int i = 0;
	for( i = 0; i < Dst_buf_size; ++i )
	{
		char headByte, tailByte;
		headByte = charToHex(Src_buf[2 * i]);
		tailByte = charToHex(Src_buf[2 * i + 1]);
		
		Dst_buf[i] = ( headByte << 4 ) | ( tailByte & 0x0f );
	}

	return i;
}

int charToHex( char c )
{
	if( '0' <= c && c <= '9' )	{return c-'0';}
	if( 'A' <= c && c <= 'F' )	{return c-'A'+0xA;}
	if( 'a' <= c && c <= 'f' )	{return c-'a'+0xA;}
	return c;
}