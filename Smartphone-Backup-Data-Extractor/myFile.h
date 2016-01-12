#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <io.h>

using namespace std;

#define MSIZE 16777216  // 16메가로 메모리 버퍼 지정

extern char* PK_EXTENSION;

class MyFile 
{
public:
			MyFile		();		// Constructor
		   ~MyFile		();		// Destructor

	int	readNum		(FILE* fp, long offset, int size);
	int	readNumBig	(FILE* fp, long offset, int size);

	string	readString	(FILE* fp, long offset, int size);
	string	readUnicode	(FILE* fp, long offset, int size);
	
	int		hex2dec		(char c);
	int*	hex2bin		(char c, int* addr);

	int *compute_prefix_function(char *pattern, int psize);
	int KMP(char *target, int tsize, char *pattern, int psize);

	int WriteFile(int wildcard_start, int startOffset, int endOffset, int wildcard_end,
				  char* inPath, char* outPath, char* fileName, int count, char* fileType);

	int fileCopy(const char* src, const char* dst);
};