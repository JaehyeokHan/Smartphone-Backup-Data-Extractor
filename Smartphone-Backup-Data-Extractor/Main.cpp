/*
@Project Name		Backup File Extractor
@author				Jaehyeok Han (one01h@gmail.com)
@affiliation		Digital Forensic Research Center @ Korea University
*/

#include <iostream>

#include "KiesBNR.h"
#include "SBU.h"
#include "LBF.h"
#include "BCK.h"

#include "Define.h"

using namespace std;

#define VERSION "0.2"

int Usage(void);
int CheckBackupFileSize(char* backupfile);
int CheckExtension(char* vender);
void splitPath(char* arg, char* path, char* name, char* ext);

int total = 0;

int main(int argc, char* argv[])
{
	//argc -= (argc > 0); argv += (argc > 0);
	
	if (argc != 2)
		return Usage();

	char* inPath = argv[1]; // 백업파일
	//char* inPath  = "D:\\dd\\_Android Backup File\\sbu_Test\\Test\\20140822T100801.sbu"; 
		
	char Dirpath[256] = {0,}, name[64] = {0, }, ext[6] = {0,};
	splitPath(inPath, Dirpath, name, ext);

	cout << " *** Start scanning for extract ***" << endl;
	CheckBackupFileSize(inPath);

	switch(CheckExtension(ext)) {

	case SAMSUNG1 :
		{
		SBU sbu;
		total = sbu.SBU_Extractor(inPath, Dirpath);
		break;
		}

	case SAMSUNG2 :
		{
		KiesBNR kies;
		total += kies.KIES_DecryptorInfo(inPath, Dirpath, name);
		total += kies.KIES_DecryptorData(inPath, Dirpath, name);
		break;
		}

	case LG : // Optimus G3
		{
		LBF lbf;
		total = lbf.LBF_Extractor(inPath, Dirpath);
		break;
		}

	case PANTECH :
		{
		BCK bck;
		total = bck.BCK_Extractor(inPath, Dirpath);
		break;
		}

	default :
		cout << " This Backup file is not supported ! " << endl;
		break;
	}

	cout << endl << "   - The Number of Extracted File is " << total << endl;
	cout << endl <<" *** Extracting is ended. Thank you ***" << endl;

	return 0;
}

int Usage(void)
{
	cout << endl;
	cout << " --------------------------------------------" << endl << endl;
	cout << "    Bakcup File Extractor  ( " << VERSION << " ver )" << endl << endl;
	//cout << "    by Jaehyeok Han (one01h@korea.ac.kr)" << endl << endl;
	cout << " --------------------------------------------" << endl;
	cout << "  * Usage : BackupFileExtractor.exe  < Backup File >" << endl;
	cout << "       (ex) BackupFileExtractor.exe  \"C:\\Users\\DFRC\\Samsung\\Kies\\Contacts.spb\"" << endl << endl;
	cout << "  * Support Files" << endl;
	cout << "    - Samsung : .spb .ssm .ssc scl .sme .sal .swp .swi .ssn / .sbu" << endl;
	cout << "    - LG      : .lbf" << endl;
	cout << "    - PANTECH : .bck" << endl <<  endl;

	return 1;
}

int CheckBackupFileSize(char* backupfile)
{
	FILE* file;

	// 백업파일 열기
	fopen_s(&file, backupfile, "rb");
	if( file == NULL ) {
		puts("BackupFile open Error");
		return 0;
	}

	// 백업파일 크기 체크
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	cout << " [ Backup File Size : " << (float)fileSize/(1024*1024) << " MB ]" << endl << endl;

	fclose(file);

	return 1;
}

int CheckExtension(char* ext)
{
		 if(!strcmp(ext, TYPE_SAMSUNG))			return SAMSUNG1;
	else if(!strcmp(ext, TYPE_LG)) 				return LG;
	else if(!strcmp(ext, TYPE_PANTECH))			return PANTECH;

	else if(!strcmp(ext, TYPE_KIES_CONTACTS))	return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_SMEMO))		return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_SPLANNER))	return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_MESSAGE))	return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_CALLLOG))	return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_ALARM))		return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_WALLPAPER))	return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_WIFI))		return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_LOCKSCREEN))	return SAMSUNG2;
	else if(!strcmp(ext, TYPE_KIES_SNOTE))		return SAMSUNG2;
	
	return 0;
}

void splitPath(char* str, char* path, char* name, char* ext)
{
	char* tmp = NULL;
	char* cur;

	tmp = (char*)malloc(sizeof(char)*strlen(str)+1);

	strcpy_s( tmp, strlen(str)+1, str );

	// extension
	for( int i = strlen(tmp)-1; i >= 0; --i ) {
		cur = &tmp[i];
		if( tmp[i] == '.' ) {
			tmp[i] = NULL;
			strcpy_s( ext, strlen(cur+1)+1, cur+1 );
			break;
		}
	}

	// filename
	for( int i = strlen(tmp)-1; i >= 0; --i ) {
		cur = &tmp[i];
		if( tmp[i] == '\\' ) {
			strcpy_s( name, strlen(cur+1)+1, cur+1 );
			tmp[i+1] = NULL;
			break;
		}
	}

	// path
	strcpy_s( path, strlen(tmp)+1, tmp );

	free(tmp);
}
