#include <stdio.h>
#include <stdlib.h>

#define FIND_NOT_FOUND -1
#define FIND_ERROR -2

class pattern_sp
{
private:
	char* make_KMP_Table(char* pattern, int pattern_size);
	int kmp_matching(char* strings, int strings_size, char* pattern, int pattern_size);

public:
	

	enum eFIND_machingMethod{ eMethod_KMP = 0, eMethod_KARFRABIN };
	enum eFIND_patternImportOption{ ePattern_No_Import = 10, ePattern_Both_Import, ePattern_1_Import, ePattern_2_Import };

	long extractPatternDataToFile( FILE* fd, long src_offset, char* outputFileName, char* pattern1, int pattern1_size, char* pattern2, int pattern2_size, int patternImportOption = ePattern_Both_Import, int eFIND_machingMethod = eMethod_KMP );
	long extractPatternDataToFile( FILE* fd, long src_offset, char* outputFileName, char* pattern, int pattern_size, long extractDataSize, int patternImportOption = ePattern_Both_Import, int eFIND_machingMethod = eMethod_KMP );
	
	int movePointerToPattern(  FILE* fd, char* outputFileName, long offset, char* pattern, int pattern_size) ;
	long patternFind( FILE* fd, long offset, char* pattern, int pattern_size, int eFIND_machingMethod = eMethod_KMP );
	long patternFind( char* byteArray, int byteArray_size, int offset, char* pattern, int pattern_size, int eFIND_machingMethod = eMethod_KMP );

};

