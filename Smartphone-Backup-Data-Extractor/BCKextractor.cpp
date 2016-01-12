#include "bck.h"
#include "myFile.h"


//########################################### LG Patterns ###########################################//

// Contacts
unsigned char BCK_CONTACTS_START[15] = {0x42, 0x45, 0x47, 0x49, 0x4E, 0x3A, 0x63, 0x6F, 0x6E, 0x74, 0x61, 0x63, 0x74, 0x0D, 0x0A}; // BEGIN:contact
unsigned char BCK_CONTACTS_END[13]    = {0x45, 0x4E, 0x44, 0x3A, 0x63, 0x6F, 0x6E, 0x74, 0x61, 0x63, 0x74, 0x0D, 0x0A}; // END:contact
char* BCK_CONTACTS_FILENAME  = "contacts";
char* BCK_CONTACTS_EXTENSION = "vcf";

// Memo
unsigned char BCK_MEMO_START[24] = {0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
								    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								    0x2C, 0x00, 0x2C, 0x00}; 
unsigned char BCK_MEMO_END[7]	 = {0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x42};
char* BCK_MEMO_FILENAME  = "memo";

// Planner
unsigned char BCK_PLANNER_START[16]  = {0x42, 0x45, 0x47, 0x49, 0x4E, 0x3A, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65, 0x0D, 0x0A}; // BEGIN:schedule
unsigned char BCK_PLANNER_END[14]    = {0x45, 0x4E, 0x44, 0x3A, 0x73, 0x63, 0x68, 0x65, 0x64, 0x75, 0x6C, 0x65, 0x0D, 0x0A}; // END:schedule
char* BCK_PLANNER_FILENAME   = "planner";
char* BCK_PLANNERS_EXTENSION = "vcs";

///////////////////////////////////////////////  Functions  ///////////////////////////////////////////////

BCK::BCK()
{
} // Constructor

BCK::~BCK()
{
} // Destructor

int BCK::Extract(char* inPath, char* outPath, char* pattern1, int size1, char* pattern2, int size2, char* name, char* extension, int wild1, int wild2, int only)
{
	int length=0, fileCount=0;
	long offset=0;
	int start=-1, end=-1;
	int onlyone = 0;

	FILE* bfile;
	MyFile mybck;

	// 백업파일 열기
	fopen_s(&bfile, inPath, "rb");
	if( bfile == NULL ) {
		puts("ReadFile open Error");
		return 0;
	}
	
	//버퍼 초기화
	char buffer[4096];
	memset(buffer, NULL, sizeof(buffer));

	while(1) {
		offset = ftell(bfile);

		// 버퍼 길이 체크
		length = fread(buffer, 1, sizeof(buffer), bfile);

		if(length < size1) {
			//cout << " [ Nothing to extract more ]" << endl;
			break;
		}

		// Signature 검색 (KMP알고리즘 활용)
		start = mybck.KMP(buffer, length, pattern1, size1);

		if(start != -1)
		{
			//cout << " [ Start Signature is found! ]" << endl;
			start += offset;
			fileCount++;
			while(1)
			{
				end = mybck.KMP(buffer, length, pattern2, size2);

				if(end == -1) {
					fseek(bfile, 1-size2, SEEK_CUR);
					offset = ftell(bfile);

					// 버퍼 길이 체크
					length = fread(buffer, 1, sizeof(buffer), bfile);

					if( length < size2 ) {
						//cout << " [ There is only start signature ]" << endl;
						fileCount--;
						break;
					}
				}

				else if(end != -1) {
					//cout << " [ End Signature is found! ]" << endl;
					end += offset;
					mybck.WriteFile(wild1, start, end+size2, wild2, inPath, outPath, name, fileCount, extension);
					fseek(bfile, end+size1+size2+wild2-1, SEEK_SET);
					if(only == 1) onlyone = 1;
					break;			
				}
			} // End of while_END signature
		}
		start = offset + 1;
		fseek(bfile, 1-size1, SEEK_CUR);
		if(onlyone == 1) break;
	} // End of while_Start signature

	fclose(bfile);

	return fileCount;
}

int BCK::BCK_Extractor(char* inputPath, char* outputPath)
{
	int nfile=0;
	
	// 전화번호부
	nfile += BCK::Extract(inputPath, outputPath, (char*)BCK_CONTACTS_START, sizeof(BCK_CONTACTS_START), (char*)BCK_CONTACTS_END, sizeof(BCK_CONTACTS_END), BCK_CONTACTS_FILENAME, BCK_CONTACTS_EXTENSION, 30, 23, 0);

	// 메모
	nfile += BCK::Extract(inputPath, outputPath, (char*)BCK_MEMO_START, sizeof(BCK_MEMO_START), (char*)BCK_MEMO_END, sizeof(BCK_MEMO_END), BCK_MEMO_FILENAME, PK_EXTENSION, 30, 22, 1);

	// 일정
	nfile += BCK::Extract(inputPath, outputPath, (char*)BCK_PLANNER_START, sizeof(BCK_PLANNER_START), (char*)BCK_PLANNER_END, sizeof(BCK_PLANNER_END), BCK_PLANNER_FILENAME, BCK_CONTACTS_EXTENSION, 30, 22, 1);

	return nfile;
}

