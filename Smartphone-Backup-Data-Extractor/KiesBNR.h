#pragma once

#include <map>
#include <iostream>
#include "aes.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "ArkLib.h"
#include "pattern_sp.h"
#include "utils.h"

using namespace std;

class KiesBNR {

public:
	typedef struct _MessageXml_
	{
		CString createDate;
		CString sender;
		CString receivers;
		CString msgState;
		CString encodedContent;
	}_MessageXml;
	_MessageXml stMessageXml;

	typedef multimap <CString, _MessageXml> map_MessageXml;
	typedef pair <CString, _MessageXml> pair_MessageXml;

	map_MessageXml mMessageXml;

	typedef struct _MMSMessageXml_
	{
		CString folder;
		CString sender;
		CString receivers;
		CString strings;
		CString createDate;
		CString mMsbody;
	}_MMSMessageXml;
	_MMSMessageXml stMMSMessageXml;

	typedef multimap <CString, _MMSMessageXml> map_MMSMessageXml;
	typedef pair <CString, _MMSMessageXml> pair_MMSMessageXml;

	map_MMSMessageXml mMMSMessageXml;

	typedef struct _SMemoXml_
	{
		CString recordID;
		CString createDate;
		CString modifiedDate;
		CString location_;
		CString locationDecode;
	}_SMemoXml;
	_SMemoXml stSMemoXml;

	typedef multimap <CString, _SMemoXml> map_SMemoXml;
	typedef pair <CString, _SMemoXml> pair_SMemoXml;

	map_SMemoXml mSMemoXml;

public:
	KiesBNR();
	~KiesBNR();

	pattern_sp ps;

	unsigned char* AES256_CBC_Decryption(unsigned char* stream256);
	int KIES_DecryptorInfo(char* inputPath, char* outputPath, char* filename);
	int KIES_DecryptorData(char* inputPath, char* outputPath, char* filename);

	int streamWritetoFile(unsigned char* stream, char* wfile);

	int MessageFiletoDecode(char* inputPath, char* outputPath);
	BOOL CreateWriteSMSMessageXmlCSVFile(CString dstPath);
	BOOL CreateWriteMMSMessageXmlCSVFile(CString dstPath);

	int SMemoFiletoDecode(char* inputPath, char* outputPath);
	BOOL CreateWriteSMemoXmlCSVFile(CString dstPath);

	int OtherFilestoDecode(char* inputPath, char* outputPath, char* fileName);
	
	void splitPath(char* str, char* path, char* name, char* ext);
	CString UnixTimeToStrTime(CString UnixTime);
	CString ConvertUTC(CString date, int added_hour);
};