#pragma once

#include <iostream>

using namespace std;

class BCK
{
private:
public:
		BCK		();		// Constructor
	   ~BCK		();		// Destructor

	int Extract(char* inPath, char* outPath, char* pattern1, int size1, char* pattern2, int size2, char* name, char* extension, int wild1, int wild2, int only);
	int BCK_Extractor(char* inputPath, char* outputPath);
};