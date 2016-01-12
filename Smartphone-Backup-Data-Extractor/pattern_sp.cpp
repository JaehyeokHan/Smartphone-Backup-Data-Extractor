#include "pattern_sp.h"
#include "utils.h"

/* 파일 읽는 크기에 대한 오버 에러 추가하자 */
long pattern_sp::extractPatternDataToFile( FILE* fd, long src_offset, char* outputFileName, char* pattern, int pattern_size, long extractDataSize, int patternImportOption, int eFIND_machingMethod  )
{
	FILE* ofd = NULL;

	/* 패턴 찾기 */
	long Pattern_Offset = patternFind( fd, src_offset, pattern, pattern_size, eFIND_machingMethod );
	if( Pattern_Offset == FIND_NOT_FOUND )
		return FIND_ERROR;
	
	/* 시작 패턴 위치 조절 */
	long startOffset = 0;
	if( patternImportOption == pattern_sp::ePattern_Both_Import || patternImportOption == pattern_sp::ePattern_1_Import )
		startOffset = Pattern_Offset;
	else if( patternImportOption == pattern_sp::ePattern_No_Import )
		startOffset = Pattern_Offset + pattern_size;

	/* 데이터 파일 출력 */
	fopen_s( &ofd, outputFileName, "wb" );
	if( ofd == NULL )
	{
		error_output( "pattern_sp::extractPatternDataToFile", "outputFIle Open Error" );
		return FIND_ERROR;
	}

	long extract_size = extractDataSize;
	long ret = extractDataToFileBySize( ofd, fd, startOffset, extract_size );

	fclose( ofd );

	return ret;
}
/* 테스트 필요 */
long pattern_sp::extractPatternDataToFile( FILE* fd, long src_offset, char* outputFileName, char* pattern1, int pattern1_size, char* pattern2, int pattern2_size, int patternImportOption, int eFIND_machingMethod )
{
	FILE* ofd = NULL;

	long start_Pattern = patternFind( fd, src_offset, pattern1, pattern1_size, eFIND_machingMethod );
	if( start_Pattern == FIND_NOT_FOUND )
		return FIND_ERROR;

	long end_Pattern = patternFind( fd, start_Pattern + pattern1_size, pattern2, pattern2_size, eFIND_machingMethod ) + start_Pattern + pattern1_size;
	if( end_Pattern == FIND_NOT_FOUND )
		return FIND_ERROR;

	/* 추출할 데이터의 시작 & 끝 지정 */
	long startOffset = 0, endOffset = 0;
	if( patternImportOption == pattern_sp::ePattern_Both_Import || patternImportOption == pattern_sp::ePattern_1_Import )
		startOffset = start_Pattern;
	else if( patternImportOption == pattern_sp::ePattern_No_Import || patternImportOption == pattern_sp::ePattern_2_Import )
		startOffset = start_Pattern + pattern1_size;

	if( patternImportOption == pattern_sp::ePattern_Both_Import || patternImportOption == pattern_sp::ePattern_2_Import )
		endOffset = end_Pattern + pattern2_size;
	else if( patternImportOption == pattern_sp::ePattern_No_Import || patternImportOption == pattern_sp::ePattern_1_Import )
		endOffset = end_Pattern;

	long extractDataSize = endOffset - startOffset;

	
	/* 데이터 파일 출력 */
	fopen_s( &ofd, outputFileName, "wb" );
	if( ofd == NULL )
	{
		error_output( "pattern_sp::extractPatternDataToFile", "outputFIle Open Error" );
		return FIND_ERROR;
	}

	long extract_size = extractDataSize;
	int ret_extractDataSize = extractDataToFileBySize( ofd, fd, startOffset, extract_size );
	fclose( ofd );

	return ret_extractDataSize;
}

long pattern_sp::patternFind( FILE* fd, long offset, char* pattern, int pattern_size, int maching_Method )
{
	/* get File size */
	long file_size = getFileSize( fd );

	/* Error */
	if( offset > file_size )
		return FIND_NOT_FOUND;
	if( offset + pattern_size > file_size )
		return FIND_NOT_FOUND;
	
	long foffset = 0;

	fseek( fd, offset, SEEK_SET );

	char buf[BUFSIZ] = {NULL,};

	int ret = 0, read_size = 0;
	foffset = 0;

	while( ( read_size = fread_s( buf, BUFSIZ, 1, BUFSIZ, fd ) ) != NULL )
	{
		ret = patternFind( buf, BUFSIZ, 0, pattern, pattern_size, maching_Method );

		if( ret == FIND_NOT_FOUND )
		{
			foffset += ( BUFSIZ - ( pattern_size - 1 ) );
			fseek( fd, - ( pattern_size - 1 ), SEEK_CUR );
		}
		else
		{
			foffset += ret;
			break;
		}
	}

	return foffset;
}

long pattern_sp::patternFind( char* byteArray, int byteArray_size, int offset, char* pattern, int pattern_size, int maching_Method )
{
	if( offset > byteArray_size - 1 )
		return FIND_ERROR;

	char* pPoint = NULL;
	int ret = FIND_NOT_FOUND;

	pPoint = &byteArray[offset];

	if( maching_Method == eMethod_KMP )
		ret = kmp_matching( pPoint, byteArray_size - offset, pattern, pattern_size );
	
	return ret;
}



////////////////////////////////////////////////////////////////////////////////////////
/* KMP */
char* pattern_sp::make_KMP_Table(char* pattern, int pattern_size)
{
	int i = 1,  j = -1;
	char* Table = new char[ pattern_size ];
	
	Table[ 0 ] = j;
	for( i = 1; i < pattern_size; ++i )
	{
		while( j > -1 && pattern[ j + 1 ] != pattern[ i ] )
		{
			j = Table[ j ];
		}
		if( pattern[ i ]==pattern[ j + 1 ] )
		{
			j++;
		}
		Table[ i ] = j;
	}
	
	return Table;
}
int pattern_sp::kmp_matching(char* strings, int strings_size, char* pattern, int pattern_size)
{
	int str_point, pat_point;
	char* Table = pattern_sp::make_KMP_Table(pattern, pattern_size);
	str_point = 0, pat_point = -1;

	for( str_point = 0; str_point < strings_size; ++str_point )
	{
		while( pat_point > -1 && pattern[pat_point+1] != strings[str_point] )
		{
			pat_point = Table[pat_point];
		}
		if( strings[str_point] == pattern[pat_point+1] )
		{
			pat_point++;
		}
		if( pat_point == pattern_size-1 )
		{
			return str_point - pat_point;
		}
	}

	return -1;

	delete Table;
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////