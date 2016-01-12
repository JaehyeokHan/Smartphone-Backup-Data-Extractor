#include "SBU.h"
#include "myFile.h"


//########################################### Patterns ###########################################//

//////// Based on Structure of Backup file ////////

// Contacts
unsigned char SBU_CONTACTS1[16] = {0xB8, 0x17, 0x5A, 0x8C, 0x86, 0x4C, 0x45, 0x06, 0x9B, 0x50, 0x0C, 0xC8, 0x88, 0x28, 0xEE, 0x2E};
unsigned char SBU_CONTACTS2[16] = {0xDC, 0xDD, 0xF4, 0x76, 0x76, 0x31, 0x41, 0xEF, 0x85, 0xB0, 0xD8, 0xA1, 0x56, 0xAB, 0xED, 0xFF};
unsigned char SBU_SPLANNER1[16] = {0xED, 0x25, 0x8D, 0xDE, 0xFF, 0x89, 0x4C, 0x43, 0x86, 0xFA, 0xBC, 0xAE, 0x90, 0x93, 0x19, 0x5E};
unsigned char SBU_SPLANNER2[16] = {0x31, 0xDC, 0x09, 0x40, 0x8E, 0x01, 0x4C, 0xB4, 0x91, 0xC4, 0x16, 0x68, 0x01, 0xF8, 0x3F, 0x17};
unsigned char SBU_MESSAGES[16]  = {0x04, 0x9B, 0xA2, 0xD7, 0xEA, 0x67, 0x4A, 0x23, 0xBA, 0xE4, 0xFD, 0x93, 0x10, 0x1F, 0xD9, 0xE0};
unsigned char SBU_SMEMO[16]     = {0x10, 0x95, 0xF4, 0xED, 0xCE, 0xE0, 0x45, 0xA0, 0xA9, 0xCC, 0xF6, 0xD4, 0x8F, 0xCF, 0x60, 0x35};
unsigned char SBU_MINIDIARY[16] = {0x1A, 0x1E, 0xE8, 0x34, 0xEF, 0xCE, 0x42, 0x5F, 0x9C, 0x57, 0xE7, 0x32, 0x3E, 0x0B, 0xDC, 0xAB};
unsigned char SBU_CALLLOG[16]   = {0x66, 0x3C, 0x6E, 0x54, 0xE2, 0xA3, 0x4A, 0x8D, 0xBE, 0x56, 0xB4, 0xCC, 0xE1, 0xA9, 0x93, 0x03};

char* SBU_CONTACTS1_FILENAME = "contact1";		char* SBU_CONTACTS1_EXTENSION = "vcf";
char* SBU_CONTACTS2_FILENAME = "contact2";		char* SBU_CONTACTS2_EXTENSION = "vcf";
char* SBU_SPLANNER1_FILENAME = "splanner2";		char* SBU_SPLANNER1_EXTENSION = "vcs";
char* SBU_SPLANNER2_FILENAME = "splanner2";		char* SBU_SPLANNER2_EXTENSION = "vcs";
char* SBU_MESSAGES_FILENAME  = "messages";		char* SBU_MESSAGES_EXTENSION  = "zip";
char* SBU_SMEMO_FILENAME	 = "smemo";			char* SBU_SMEMO_EXTENSION	 = "zip";
char* SBU_MINIDIARY_FILENAME = "minidiary";		char* SBU_MINIDIARY_EXTENSION = "zip";
char* SBU_CALLLOG_FILENAME	 = "calllog";		char* SBU_CALLLOG_EXTENSION	 = "zip";

// Content
unsigned char SBU_MUSIC[16]     = {0x88, 0x6C, 0x05, 0xF1, 0xC0, 0xCC, 0x40, 0x06, 0xB2, 0x84, 0x10, 0xB7, 0x79, 0x2D, 0x18, 0x39};
unsigned char SBU_PHOTO[16]    = {0x48, 0x05, 0x6F, 0x23, 0x10, 0x86, 0x4F, 0x53, 0xBB, 0x46, 0x46, 0x8D, 0x64, 0x79, 0xA8, 0x10};
unsigned char SBU_VIDEO[16]    = {0xCC, 0x19, 0x6A, 0x6A, 0x7D, 0xF3, 0x40, 0x33, 0x8C, 0x59, 0x15, 0x33, 0x61, 0x98, 0x76, 0xE3};
unsigned char SBU_MCONTENT[16]   = {0x69, 0x67, 0xFD, 0x04, 0x11, 0x27, 0x4D, 0x24, 0x91, 0x24, 0x6A, 0xC4, 0x8C, 0x5D, 0xDE, 0x1A};
	
char* SBU_MUSIC_FILENAME	 = "_music";					char* SBU_MUSIC_EXTENSION	 = NULL;
char* SBU_PHOTO_FILENAME	 = "_photo";					char* SBU_PHOTO_EXTENSION	 = NULL;
char* SBU_VIDEO_FILENAME	 = "_video";					char* SBU_VIDEO_EXTENSION	 = NULL;
char* SBU_MCONTENT_FILENAME	 = "_others";					char* SBU_MCONTENT_EXTENSION = NULL;	

// Account information and settings
unsigned char SBU_RINGTONE[16]  = {0x0B, 0xFF, 0xFE, 0xB4, 0x6D, 0x4B, 0x46, 0x8D, 0x83, 0x32, 0x50, 0x87, 0x7A, 0xBE, 0x56, 0x75};
unsigned char SBU_SETTINGS[16]  = {0x42, 0xF4, 0x12, 0xB8, 0xAC, 0xA4, 0x49, 0xF1, 0x8E, 0x92, 0x88, 0x23, 0xE3, 0x18, 0x03, 0x4D};
unsigned char SBU_EMAIL[16]     = {0xC7, 0x7C, 0x44, 0xB8, 0x7F, 0xAD, 0x4A, 0x74, 0x87, 0x31, 0xDC, 0xA0, 0xC3, 0x27, 0xB6, 0xFF};

char* SBU_RINGTONE_FILENAME	 = "ringtone";		char* SBU_RINGTONE_EXTENSION	 = "zip";
char* SBU_SETTINGS_FILENAME	 = "settings";		char* SBU_SETTINGS_EXTENSION	 = "zip";
char* SBU_EMAIL_FILENAME	 = "email";			char* SBU_EMAIL_EXTENSION		= "zip";

char SBU_END[16]     = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//########################################### GENERAL PATTERNS ###########################################//


//	JPEG image
unsigned char JPEG_START_KEY1[4] = {0xFF, 0xD8, 0xFF, 0xE0};
unsigned char JPEG_START_KEY2[4] = {0xFF, 0xD8, 0xFF, 0xE8};
unsigned char JPEG_END_KEY[2]	= {0xFF, 0xD9};
char* JPEG_EXTENSION = "jpg";

//	PNG image
unsigned char PNG_START_KEY[8]	= {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
unsigned char PNG_END_KEY[8]	= {0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
char* PNG_EXTENSION = "png";

///////////////////////////////////////////////  Functions  ///////////////////////////////////////////////

SBU::SBU()
{
} // Constructor

SBU::~SBU()
{
} // Destructor

char* SBU::MakeFolder(char* Path, char* folderName)
{
	char* folderPath1 = new char[256];

	char folderPath[256];
	memset(folderPath, 0, 256);

	sprintf_s(folderPath, "%s\\%s\\", Path, folderName, strlen(folderName));
	
	// 생성 폴더가 존재할 경우, 삭제
	if( !_access(folderPath, 0) )	remove(folderPath);

	int rfolder = _mkdir(folderPath);
	strcpy_s(folderPath1, 256, folderPath);
	
	if( rfolder == -1 ) {
		//perror(" The following error occurred");
		cout << " [ Directory already existed ]" << endl;
	}
	//cout << " [ Directory is created ]" << endl;
	return folderPath1;
}

int SBU::SBU_Extractor(char* inputPath, char* outputPath)
{
	int length=0, capture=0, fileCount=0;
	long offset=0;
	int start=-1, end=-1;
	char* dataPath;
	//memset(folderPath, 0, 256);

	FILE* sbufile;
	MyFile mysbu;
	
	// 백업파일 열기
	fopen_s(&sbufile, inputPath, "rb");
	if( sbufile == NULL ) {
		puts("ReadFile open Error");
		return 0;
	}

	// 데이터 저장용 폴더 생성
	dataPath = MakeFolder(outputPath, "data");
	
	while(1) {
		fseek(sbufile, 118+38*capture++, SEEK_SET);
		fread(Signature, 16, 1, sbufile);
		if(!strncmp(Signature, SBU_END, 8)) break;

		// 백업 데이터 출력
		StartingOffset = mysbu.readNum(sbufile, ftell(sbufile), 8);
		fseek(sbufile, StartingOffset+22, SEEK_SET);
		SizeOfData = mysbu.readNum(sbufile, ftell(sbufile), 8);

		//cout << " " << endl;for(int i=0;i<16;i++)printf("%02X ", Signature[i] & 0xff);
		//cout << endl << " Data Area : " << StartingOffset+54 << " ~ " << StartingOffset+54+SizeOfData << endl;
		
		fileName  = FileNameCheck(Signature);
		extension = ExtensionCheck(Signature);
		if(fileName == NULL) continue;
		    
		mysbu.WriteFile(0, StartingOffset+54, StartingOffset+54+SizeOfData, 0, inputPath, dataPath, fileName, fileCount++, extension);

		ContentProcess(fileName, outputPath);
	}
	return fileCount;
}

char* SBU::FileNameCheck(char* sig)
{
		if(!strncmp(sig, (char*)SBU_CONTACTS1, 8))			return SBU_CONTACTS1_FILENAME;
		else if(!strncmp(sig, (char*)SBU_CONTACTS2, 8))		return SBU_CONTACTS2_FILENAME;
		else if(!strncmp(sig, (char*)SBU_SPLANNER1, 8))		return SBU_SPLANNER1_FILENAME;
		else if(!strncmp(sig, (char*)SBU_SPLANNER2, 8))		return SBU_SPLANNER2_FILENAME;
		else if(!strncmp(sig, (char*)SBU_MESSAGES, 8))		return SBU_MESSAGES_FILENAME;
		else if(!strncmp(sig, (char*)SBU_SMEMO, 8))			return SBU_SMEMO_FILENAME;
		else if(!strncmp(sig, (char*)SBU_MINIDIARY, 8))		return SBU_MINIDIARY_FILENAME;
		else if(!strncmp(sig, (char*)SBU_CALLLOG, 8))		return SBU_CALLLOG_FILENAME;
		else if(!strncmp(sig, (char*)SBU_MUSIC, 8))			return SBU_MUSIC_FILENAME;
		else if(!strncmp(sig, (char*)SBU_PHOTO, 8))			return SBU_PHOTO_FILENAME;
		else if(!strncmp(sig, (char*)SBU_VIDEO, 8))			return SBU_VIDEO_FILENAME;
		else if(!strncmp(sig, (char*)SBU_MCONTENT, 8))		return SBU_MCONTENT_FILENAME;
		else if(!strncmp(sig, (char*)SBU_RINGTONE, 8))		return SBU_RINGTONE_FILENAME;
		else if(!strncmp(sig, (char*)SBU_SETTINGS, 8))		return SBU_SETTINGS_FILENAME;
		else if(!strncmp(sig, (char*)SBU_EMAIL, 8))			return SBU_EMAIL_FILENAME;
		
		// 시그니처가 없는 경우
		else return 0;
}

char* SBU::ExtensionCheck(char* sig)
{
		if(!strncmp(sig, (char*)SBU_CONTACTS1, 8))			return SBU_CONTACTS1_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_CONTACTS2, 8))		return SBU_CONTACTS2_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_SPLANNER1, 8))		return SBU_SPLANNER1_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_SPLANNER2, 8))		return SBU_SPLANNER2_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_MESSAGES, 8))		return SBU_MESSAGES_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_SMEMO, 8))			return SBU_SMEMO_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_MINIDIARY, 8))		return SBU_MINIDIARY_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_CALLLOG, 8))		return SBU_CALLLOG_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_MUSIC, 8))			return SBU_MUSIC_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_PHOTO, 8))			return SBU_PHOTO_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_VIDEO, 8))			return SBU_VIDEO_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_MCONTENT, 8))		return SBU_MCONTENT_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_RINGTONE, 8))		return SBU_RINGTONE_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_SETTINGS, 8))		return SBU_SETTINGS_EXTENSION;
		else if(!strncmp(sig, (char*)SBU_EMAIL, 8))			return SBU_EMAIL_EXTENSION;
		
		// 시그니처가 없는 경우
		else return 0;
}

int SBU::ContentProcess(char* addr, char* Path)
{
	MyFile mydiv;
	char* outContentPath;
	char imagePath[256], outContent[256];
	char dataPath1[256];
	sprintf_s(dataPath1, "%sdata", Path);

	if(fileName == SBU_MUSIC_FILENAME) {
		sprintf_s(imagePath, "%s\\%s", dataPath1, SBU_MUSIC_FILENAME);
		outContentPath = MakeFolder(dataPath1, "musics");
		sprintf_s(outContent, "%s\\%s", outContentPath, SBU_MUSIC_FILENAME);
		mydiv.fileCopy(imagePath, outContent);
		remove(imagePath);

		//cout << " [ Dividing..._music ]" << endl;
	}
	else if(fileName == SBU_PHOTO_FILENAME) {
		sprintf_s(imagePath, "%s\\%s", dataPath1, SBU_PHOTO_FILENAME);
		outContentPath = MakeFolder(dataPath1, "photos");
		sprintf_s(outContent, "%s\\%s", outContentPath, SBU_PHOTO_FILENAME);
		mydiv.fileCopy(imagePath, outContent);
		remove(imagePath); 

		cout << " [ Dividing... _photo ]" << endl;
		ImageFinder(Path, outContentPath);

	}
	else if(fileName == SBU_VIDEO_FILENAME) {
		sprintf_s(imagePath, "%s\\%s", dataPath1, SBU_VIDEO_FILENAME);
		outContentPath = MakeFolder(dataPath1, "videos");
		sprintf_s(outContent, "%s\\%s", outContentPath, SBU_VIDEO_FILENAME);
		mydiv.fileCopy(imagePath, outContent);
		remove(imagePath);

		//cout << " [ Dividing..._video ]" << endl;			
	}

	else if(fileName == SBU_MCONTENT_FILENAME) {
		sprintf_s(imagePath, "%s\\%s", dataPath1, SBU_MCONTENT_FILENAME);
		outContentPath = MakeFolder(dataPath1, "others");
		sprintf_s(outContent, "%s\\%s", outContentPath, SBU_MCONTENT_FILENAME);
		mydiv.fileCopy(imagePath, outContent);
		remove(imagePath);

		//cout << " [ Dividing..._others ]" << endl;
	}
	else return 0;

	return 1;
}

int SBU::ImageFinder(char* Path1, char* Path2)
{
	MyFile myimage;
	char src[256], dst[256];

	sprintf_s(src, "%sFMCarver.exe", Path1);
	sprintf_s(dst, "%sFMCarver.exe", Path2);
	
	myimage.fileCopy(src, dst);
	
	ShellExecute(NULL, _T("open"), _T("FMCarver.exe"), _T("1 _photo"), (CString)Path2, SW_HIDE );

	remove(dst);
	
	return 1;
}