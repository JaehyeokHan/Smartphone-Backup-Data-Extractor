#pragma once

#include <iostream>
#include <direct.h>

#include <stdlib.h>
#include "atlstr.h"
using namespace std;

class SBU
{
private:
	char* backupContents;
	char* fileName;
	char* extension;

	char Signature[16];
	int StartingOffset;
	int SizeOfData;
	int NumberOfContent;
	int TypeOfData;

private:
	char* MakeFolder(char* Path, char* folderName);
	char* FileNameCheck(char* sig);
	char* ExtensionCheck(char* sig);
	int ContentProcess(char* addr, char* Path);
	int ImageFinder(char* Path1, char* Path2);

public:
	SBU		();		// Constructor
   ~SBU		();		// Destructor

	int SBU_Extractor(char* inputPath, char* outputPath);
};