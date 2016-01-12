#include "KiesBNR.h"
#include "base64.h"



KiesBNR::KiesBNR()
{
} // Constructor
KiesBNR::~KiesBNR()
{
} // Destructor

unsigned char* KiesBNR::AES256_CBC_Decryption(unsigned char* stream256)
{
	unsigned char key[32] = {0x00, };
	unsigned char iv[16]  = {0x00, };
	
	// allocate output buffer
	unsigned char*  out = (unsigned char* )malloc(256+1);
	//out = (unsigned char* )realloc(out, 512); // + NULL char	
	out[256] = 0x00;

	// decrypt decoded data
	cist_aes aes;
	aes.AES_KeySchedule(key, 256);	// AES 256 bits
	aes.AES_CBC_DEC(stream256, out, 256, iv);

	return out;
}

int KiesBNR::KIES_DecryptorInfo(char* inputPath, char* outputPath, char* filename)
{
	FILE* file;
	unsigned char datastream[256] = {0, };
	unsigned char*decrypted = NULL;

	char outputFullPath[256] = {0,};
	char outputfileName[128] = {0,};
	sprintf_s(outputFullPath, "%s\\%sInfo.xml", outputPath, filename);
	sprintf_s(outputfileName, "%sInfo.xml", filename);

	// open a backup file
	fopen_s(&file, inputPath, "rb");
	if( file == NULL ) {
		puts("ReadFile open Error");
		return 0;
	}

	cout << " [ Extracting..." << outputfileName <<" ] " << endl;

	fread(datastream, 256, 1, file);
	decrypted = AES256_CBC_Decryption(datastream);
	streamWritetoFile(decrypted, outputFullPath);

	fseek(file, 16, SEEK_CUR);
	fread(datastream, 256, 1, file);
	decrypted = AES256_CBC_Decryption(datastream);
	streamWritetoFile(decrypted, outputFullPath);

	fclose(file);

	return 1;
}

int KiesBNR::KIES_DecryptorData(char* inputPath, char* outputPath, char* filename)
{
	FILE* file;
	unsigned char datastream[256] = {0, };
	unsigned char*decrypted = NULL;
	//m_pArk = NULL;

	char outputFullPath[256] = {0,};
	char outputfileName[128] = {0,};
	char outputXmlFilePath[256] = {0,};
	char* DecryptedFileName = NULL;
	char CheckName[256] = {0,};
	sprintf_s(outputFullPath, "%s%s.xml.gz", outputPath, filename);
	sprintf_s(outputfileName, "%s.gz", filename);


	// open a backup file
	fopen_s(&file, inputPath, "rb");
	if( file == NULL ) {
		puts("ReadFile open Error");
		return 0;
	}

	cout << " [ Extracting..." << outputfileName <<" ] " << endl;

	fseek(file, 272+272, SEEK_SET);
	int length = 0;
	while(1) {
		length = fread(datastream, 1, 256, file);
		if(length == 256) {
			decrypted = AES256_CBC_Decryption(datastream);
			streamWritetoFile(decrypted, outputFullPath);
			fseek(file, 16, SEEK_CUR);
		}
		else break;
	}
	fclose(file);

	CArkLib ark;

	// decompression
	if(ark.Create(ARK_DLL_RELEASE_FILE_NAME)!=ARKERR_NOERR)
		return 0;
	if(ark.Open(outputFullPath) == FALSE)
		return 0;
	ark.ExtractAllTo(outputPath);

	for(int a = 0 ; a < ark.GetFileItemCount() ; a++)
		DecryptedFileName = ark.GetFileItem(a)->fileName;

	sprintf_s(outputXmlFilePath, "%s%s", outputPath, DecryptedFileName);

	ark.Destroy();

	
	char Dirpath[256] = {0,}, name[64] = {0, }, ext[6] = {0,};
	splitPath(outputXmlFilePath, Dirpath, name, ext);

	sprintf_s(CheckName, "%s.%s", name,ext); 

	// check file format
	if(!strcmp(CheckName,"message_body.xml"))
		MessageFiletoDecode(outputXmlFilePath, Dirpath);
	else if(!strcmp(CheckName,"SMemo.xml"))
		SMemoFiletoDecode(outputXmlFilePath, Dirpath);
	else
		OtherFilestoDecode(outputXmlFilePath, Dirpath, CheckName);//calllog, alarm, wallpaper, wifi, lockscreen

	return 1;
}

int KiesBNR::streamWritetoFile(unsigned char* stream, char* wfilePath)
{

#define WRITE_SIZE 256	// size of memory buffer

	// set the buffer
	char wbuf[WRITE_SIZE];
	memset(wbuf, NULL, sizeof(wbuf));

	FILE* wfile;

	// open the output file
	fopen_s(&wfile, wfilePath, "a+b");
	if( wfile == NULL ) {
		puts("Stream to Write File open Error");
		return 0;
	}

	for( int i = 0; i < WRITE_SIZE; i++)
		fputc(stream[i], wfile);

	// close the file
	fclose(wfile);

	return 1;
}

int KiesBNR::MessageFiletoDecode(char* inputPath, char* outputPath){
	//Read Input File
	CString inputPathString = (CString)inputPath;
	if(!PathFileExists((LPCWSTR)inputPathString))
		return 0;

	UINT XMLDataOffset = 0;

	CFile input;
	if ( !input.Open((LPCWSTR)inputPathString, CFile::modeRead | CFile::modeNoTruncate | CFile::typeBinary) )
	{
		return false;
	}

	//XML 데이터 크기만큼의 버퍼 생성;
	int nBufSize = input.GetLength();
	char* XMLData = new char[nBufSize+1];
	ZeroMemory(XMLData, nBufSize+1);

	//버퍼에 XML 내용을 읽어들인다.;
	input.Seek(XMLDataOffset, input.begin);
	input.Read(XMLData, nBufSize+1);

	//XML 데이터가 NULL일경우 False 반환;
	if (XMLData == NULL) 
		return false;  

	//메모리상에 있는 XML 데이터를 오픈 (Parse);
	TiXmlDocument m_Document;
	m_Document.Parse(XMLData);	// xml open

	// 루트노드 접근.;
	TiXmlElement* pRoot = m_Document.FirstChildElement("MessageData"); 
	if (!pRoot) 
		goto END_PROCESS;

	// 값을 읽고자 하는 Welcome 엘리먼트로 접근.;
	TiXmlElement* pElem  = pRoot->FirstChildElement("SMSList")->FirstChildElement();
	TiXmlElement* pElem2 = pRoot->FirstChildElement("MMSList")->FirstChildElement();//HextoString

	if (!pElem) 
		goto END_PROCESS;

	while(pElem)
	{
		CString str1=_T("");
		CString str2=_T("");
		CString str3=_T("");
		CString str4=_T("");
		CString element=_T("");
		DWORD str_Len = 0;
		TCHAR * dstTCHAR = NULL;

		char *psNode = (char*)pElem->Value();

		str_Len = MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), NULL, NULL);
		dstTCHAR = new TCHAR[str_Len + 1];
		memset(dstTCHAR, 0x00, str_Len * 2 + 2);

		MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), dstTCHAR, str_Len);
		element.Format(L"%s",dstTCHAR);
		delete [] dstTCHAR;


		if(element.Find(L"SMSStoreItem") != -1)
		{
			TiXmlElement* pElem_1=pElem->FirstChildElement();

			//pElem1=pElem1->FirstChildElement();
			while(pElem_1)
			{
				CString str_1	   = _T("");
				CString element_1  = _T("");
				DWORD str_Len_1    = 0;
				TCHAR * dstTCHAR_1 = NULL;
				//	test.Format(L"%s", pElem->GetText()); 

				char *psNode_1 = (char*)pElem_1->Value();

				str_Len = MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), NULL, NULL);
				dstTCHAR_1 = new TCHAR[str_Len + 1];
				memset(dstTCHAR_1, 0x00, str_Len * 2 + 2);

				MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), dstTCHAR_1, str_Len);
				element_1.Format(L"%s",dstTCHAR_1);
				delete [] dstTCHAR_1;

				// CreateDate
				if(element_1.Find(_T("CreateDate"))!= -1) {
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text != NULL) {
						
						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str1.Format((L"%s"),dstTch);
						str1 = ConvertUTC(str1, 9); // UTC 시간 적용

						delete []dstTch;
					}
				}
				
				// Sender
				else if(element_1.Find(_T("Sender"))!= -1) {
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text != NULL) {
						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str2.Format((L"%s"),dstTch);
						delete []dstTch;
					}
					else
						str2 = L"NULL";
				}
				
				// Receivers
				else if(element_1.Find(_T("Receivers"))!= -1) {

					TiXmlElement* pElem_2 = pElem_1->FirstChildElement();
					const char *text = pElem_2->GetText();

					if(text != NULL) {
						TCHAR* dstTch = NULL;
						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str3.Format((L"%s"), dstTch);
						delete []dstTch;
					}
					else
						str3 = L"NULL";
				}
				
				else if(element_1.Find(_T("MsgState"))!= -1){
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text == NULL) break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch = new TCHAR[str_Len + 1];
					memset(dstTch, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

					str4.Format((L"%s"),dstTch);
					delete []dstTch;
				}
				
				// Encoded Content
				else if(element_1.Find(_T("EncodedContent"))!= -1)
				{
					const char *text = pElem_1->GetText();

					if(text == NULL) break;

					string cipher(text);
					PBYTE buf_cipher = (PBYTE)malloc(cipher.size()+1);
					buf_cipher[cipher.size()] = 0x00;
					memcpy(buf_cipher, cipher.c_str(), cipher.size());

					INT length = base64_decode((PCHAR)buf_cipher, buf_cipher, cipher.size());

					wchar_t strUnicode[256] = {0,};

					int nLen = MultiByteToWideChar(CP_UTF8, 0, (const char*)buf_cipher, strlen((const char*)buf_cipher), NULL, NULL);
					MultiByteToWideChar(CP_UTF8, 0, (const char*)buf_cipher, strlen((const char*)buf_cipher), strUnicode, nLen);// utf-8 to unicode
					
					//strUnicode 바꿔 저장
					stMessageXml.createDate		= str1;
					stMessageXml.sender			= str2;
					stMessageXml.receivers		= str3;
					stMessageXml.msgState		= str4;
					stMessageXml.encodedContent = strUnicode;
					mMessageXml.insert(pair_MessageXml(stMessageXml.createDate, stMessageXml));

					stMessageXml.createDate.Empty();
					stMessageXml.msgState.Empty();
					stMessageXml.sender.Empty();
					stMessageXml.receivers.Empty();
					stMessageXml.encodedContent.Empty();
				}

				pElem_1 = pElem_1->NextSiblingElement();
			}
		}
		pElem = pElem->NextSiblingElement();
	}

	while(pElem2)
	{
		CString str1=_T("");
		CString str2=_T("");
		CString str3=_T("");
		CString str4=_T("");
		CString str5=_T("");
		CString str6=_T("");
		CString element=_T("");
		DWORD str_Len = 0;
		TCHAR * dstTCHAR = NULL;

		char *psNode = (char*)pElem2->Value();

		str_Len = MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), NULL, NULL);
		dstTCHAR = new TCHAR[str_Len + 1];
		memset(dstTCHAR, 0x00, str_Len * 2 + 2);

		MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), dstTCHAR, str_Len);
		element.Format(L"%s",dstTCHAR);
		delete [] dstTCHAR;


		if(element.Find(L"MMSStoreItem") != -1)
		{
			TiXmlElement* pElem_1=pElem2->FirstChildElement();

			while(pElem_1)
			{
				CString str_1=_T("");
				CString element_1=_T("");
				DWORD str_Len_1 = 0;
				TCHAR * dstTCHAR_1 = NULL;

				char *psNode_1 = (char*)pElem_1->Value();

				str_Len = MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), NULL, NULL);
				dstTCHAR_1 = new TCHAR[str_Len + 1];
				memset(dstTCHAR_1, 0x00, str_Len * 2 + 2);

				MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), dstTCHAR_1, str_Len);
				element_1.Format(L"%s",dstTCHAR_1);
				delete [] dstTCHAR_1;

				if(element_1.Compare(_T("Folder")) == 0) {
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text != NULL) {
						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str1.Format((L"%s"),dstTch);
						delete []dstTch;
					}
				}

				// Sender
				else if(element_1.Find(_T("Sender"))!= -1) {
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text != NULL) {
						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str2.Format((L"%s"),dstTch);
						delete []dstTch;
					}
					else
						str2 = L"NULL";
						
				}

				// Receivers
				else if(element_1.Find(_T("Receivers"))!= -1) {

					TiXmlElement* pElem_2 = pElem_1->FirstChildElement();
					const char *text = pElem_2->GetText();

					if(text != NULL) {
						TCHAR* dstTch = NULL;
						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str3.Format((L"%s"), dstTch);
						delete []dstTch;
					}
					else
						str3 = L"NULL";
				}


				// CreateDate
				else if(element_1.Find(_T("CreateDate"))!= -1)
				{
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text != NULL) {

						str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
						dstTch = new TCHAR[str_Len + 1];
						memset(dstTch, 0x00, str_Len * 2 + 2);

						MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

						str5.Format((L"%s"),dstTch);
						str5 = ConvertUTC(str5, 9); // UTC 시간 적용

						delete []dstTch;
					}
				}
				
				else if(element_1.Find(_T("MMSBody"))!= -1)
				{
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();
					std::string newString;


					if(text == NULL)
						break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch = new TCHAR[str_Len + 1];
					memset(dstTch, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

					str6.Format((L"%s"),dstTch);
					delete []dstTch;

					CT2CA pszConvertedAnsiString (str6);

					string tmp(pszConvertedAnsiString);
					
					for(int i = 0; i < tmp.length() - 0x0c*2; i +=2)
					{
						string byte = tmp.substr(i+0x0c*2,2);
						char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
						newString.push_back(chr);
					}

					wchar_t strUnicode[20480] = {0,};
					
					int nLen = MultiByteToWideChar(CP_UTF8, 0, (const char*)newString.c_str(), strlen((const char*)newString.c_str()), NULL, NULL);
					MultiByteToWideChar(CP_UTF8, 0, (const char*)newString.c_str(), strlen((const char*)newString.c_str()), strUnicode, nLen);// utf-8 to unicode
					

					//strUnicode 바꿔 저장
					stMMSMessageXml.folder     = str1;
					stMMSMessageXml.sender     = str2;
					stMMSMessageXml.receivers  = str3;
					stMMSMessageXml.createDate = str5;
					stMMSMessageXml.mMsbody    = strUnicode;
					mMMSMessageXml.insert(pair_MMSMessageXml(stMMSMessageXml.folder, stMMSMessageXml));

					stMMSMessageXml.folder.Empty();
					stMMSMessageXml.sender.Empty();
					stMMSMessageXml.receivers.Empty();
					stMMSMessageXml.createDate.Empty();
					stMMSMessageXml.mMsbody.Empty();
				}

				pElem_1 = pElem_1->NextSiblingElement();
			}
		}
		pElem2 = pElem2->NextSiblingElement();
	}


END_PROCESS:
	m_Document.Clear();
	if(XMLData)
		delete XMLData;
	CreateWriteSMSMessageXmlCSVFile((CString)outputPath);
	CreateWriteMMSMessageXmlCSVFile((CString)outputPath);
	return 1;
}

BOOL KiesBNR::CreateWriteSMSMessageXmlCSVFile(CString dstPath){
	pair<multimap<CString, _MessageXml>::iterator, multimap<CString, _MessageXml>::iterator>iter_messagexml;
	multimap<CString, _MessageXml>::iterator iterMessageXml;

	CFile cFile;
	CString CSVFileName;
	CString DstFile;

	CSVFileName = dstPath + L"\\SMSMessageXml.csv";	

	if ( !PathFileExists(CSVFileName) )	
	{
		if( cFile.Open( CSVFileName, CFile::modeCreate | CFile::modeWrite ) == FALSE )
			return FALSE;

		USHORT nUniSig = 0xfeff;
		cFile.Write(&nUniSig, 2);

		CString ColHeader = _T("CreateDate\tSender\tReceivers\tMsgState\tDecoded Message\n");
		cFile.Write(ColHeader.GetBuffer(), ColHeader.GetLength()*2);
		cFile.Close();
	}
	CString WriteString;
	for ( iterMessageXml = mMessageXml.begin() ; iterMessageXml != mMessageXml.end(); ++iterMessageXml	)
	{
		//CSV 파일 존재 하면 데이터 쓰기
		if ( cFile.Open( CSVFileName, CFile::modeReadWrite | CFile::modeNoTruncate ) == FALSE )
			return FALSE;

		stMessageXml.createDate = iterMessageXml->second.createDate; 
		stMessageXml.sender		= iterMessageXml->second.sender;

		iterMessageXml->second.receivers.Replace(',', '\n'); // 문자열이 포함하는 쉼표 처리
		stMessageXml.receivers	= iterMessageXml->second.receivers;

		stMessageXml.msgState	= iterMessageXml->second.msgState;

		iterMessageXml->second.encodedContent.Replace('\"', '\''); // 문자열이 포함하는 따옴표 처리
		stMessageXml.encodedContent = iterMessageXml->second.encodedContent;

		//입력할 데이터를 쌍따음표로 묶음
		stMessageXml.createDate		= L"\"" + stMessageXml.createDate	  + L"\"";
		stMessageXml.sender			= L"\"" + stMessageXml.sender		  + L"\"";
		stMessageXml.receivers		= L"\"" + stMessageXml.receivers	  + L"\"";
		stMessageXml.msgState		= L"\"" + stMessageXml.msgState	 	  + L"\"";
		stMessageXml.encodedContent = L"\"" + stMessageXml.encodedContent + L"\"";

		WriteString = stMessageXml.createDate + L"\t" + stMessageXml.sender + L"\t" + stMessageXml.receivers  + L"\t" + stMessageXml.msgState + L"\t" + stMessageXml.encodedContent + L"\n";

		cFile.SeekToEnd();
		cFile.Write(WriteString.GetBuffer(), WriteString.GetLength()*2);
		WriteString.Empty();
		cFile.Close();
	} 

	return TRUE;
}

BOOL KiesBNR::CreateWriteMMSMessageXmlCSVFile(CString dstPath){
	pair<multimap<CString, _MMSMessageXml>::iterator, multimap<CString, _MMSMessageXml>::iterator>iter_mmsmessagexml;
	multimap<CString, _MMSMessageXml>::iterator iterMMSMessageXml;

	CFile cFile;
	CString CSVFileName;
	CString DstFile;

	CSVFileName = dstPath + L"\\MMSMessageXml.csv";	

	if ( !PathFileExists(CSVFileName) )	
	{
		if( cFile.Open( CSVFileName, CFile::modeCreate | CFile::modeWrite ) == FALSE )
			return FALSE;

		USHORT nUniSig = 0xfeff;
		cFile.Write(&nUniSig, 2);

		CString ColHeader = _T("CreateDate\t수발신 상태\tSender\tReciver Number\tMMSMessage\n");
		cFile.Write(ColHeader.GetBuffer(), ColHeader.GetLength()*2);
		cFile.Close();
	}
	CString WriteString;
	for ( iterMMSMessageXml = mMMSMessageXml.begin() ; iterMMSMessageXml != mMMSMessageXml.end(); ++iterMMSMessageXml	)
	{
		//CSV 파일 존재 하면 데이터 쓰기
		if ( cFile.Open( CSVFileName, CFile::modeReadWrite | CFile::modeNoTruncate ) == FALSE )
			return FALSE;

		stMMSMessageXml.folder     = iterMMSMessageXml->second.folder; 
		stMMSMessageXml.sender     = iterMMSMessageXml->second.sender;
		stMMSMessageXml.receivers  = iterMMSMessageXml->second.receivers;

		iterMMSMessageXml->second.receivers.Replace(',', '\n'); // 문자열이 포함하는 쉼표 처리
		stMMSMessageXml.receivers	= iterMMSMessageXml->second.receivers;

		stMMSMessageXml.createDate = iterMMSMessageXml->second.createDate;

		iterMMSMessageXml->second.mMsbody.Replace('\"', '\''); // 문자열이 포함하는 따옴표 처리
		stMMSMessageXml.mMsbody    = iterMMSMessageXml->second.mMsbody;

		//입력할 데이터를 쌍따음표로 묶음
		stMMSMessageXml.folder	   = L"\"" + stMMSMessageXml.folder + L"\"";
		stMMSMessageXml.sender     = L"\"" + stMMSMessageXml.sender + L"\"";
		stMMSMessageXml.receivers  = L"\"" + stMMSMessageXml.receivers + L"\"";
		stMMSMessageXml.createDate = L"\"" + stMMSMessageXml.createDate + L"\"";
		stMMSMessageXml.mMsbody    = L"\"" + stMMSMessageXml.mMsbody + L"\"";

		WriteString = stMMSMessageXml.createDate+ L"\t" + stMMSMessageXml.folder + L"\t" + stMMSMessageXml.sender + L"\t" + stMMSMessageXml.receivers + L"\t" + stMMSMessageXml.mMsbody  + L"\n";

		cFile.SeekToEnd();
		cFile.Write(WriteString.GetBuffer(), WriteString.GetLength()*2);
		WriteString.Empty();
		cFile.Close();
	} 

	return TRUE;
}

int KiesBNR::SMemoFiletoDecode(char* inputPath, char* outputPath){
	CString inputPathString = (CString)inputPath;
	if(!PathFileExists((LPCWSTR)inputPathString))
		return 0;

	UINT XMLDataOffset = 0;

	CFile input;
	if ( !input.Open((LPCWSTR)inputPathString, CFile::modeRead | CFile::modeNoTruncate | CFile::typeBinary) )
	{
		return false;
	}

	//XML 데이터 크기만큼의 버퍼 생성;
	int nBufSize = input.GetLength();
	char* XMLData = new char[nBufSize+1];
	ZeroMemory(XMLData, nBufSize+1);
	
	//버퍼에 XML 내용을 읽어들인다.;
	input.Seek(XMLDataOffset, input.begin);
	input.Read(XMLData, nBufSize+1);

	//XML 데이터가 NULL일경우 False 반환;
	if (XMLData == NULL) 
		return false;  

	//메모리상에 있는 XML 데이터를 오픈 (Parse);
	TiXmlDocument m_Document;
	m_Document.Parse(XMLData);	// xml open

	// 루트노드 접근.;
	TiXmlElement* pRoot = m_Document.FirstChildElement("SMemoItems"); 
	if (!pRoot) 
		goto END_PROCESS;

	// 값을 읽고자 하는 Welcome 엘리먼트로 접근.;
	TiXmlElement* pElem = pRoot->FirstChildElement("Items")->FirstChildElement();
	
	if (!pElem) 
		goto END_PROCESS;

	while(pElem)
	{
		CString str1 = _T("");
		CString str2 = _T("");
		CString str3 = _T("");
		CString str4 = _T("");
		CString element = _T("");
		DWORD str_Len = 0;
		TCHAR * dstTCHAR = NULL;

		char *psNode = (char*)pElem->Value();

		str_Len = MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), NULL, NULL);
		dstTCHAR = new TCHAR[str_Len + 1];
		memset(dstTCHAR, 0x00, str_Len * 2 + 2);

		MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), dstTCHAR, str_Len);
		element.Format(L"%s",dstTCHAR);
		delete [] dstTCHAR;


		if(element.Find(L"SMemoItem")!=-1)//SMemoItem이 들어옴..
		{
			TiXmlElement* pElem_1=pElem->FirstChildElement();

			while(pElem_1)
			{
				CString str_1=_T("");
				CString element_1=_T("");
				DWORD str_Len_1 = 0;
				TCHAR * dstTCHAR_1 = NULL;

				char *psNode_1 = (char*)pElem_1->Value();

				str_Len = MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), NULL, NULL);
				dstTCHAR_1 = new TCHAR[str_Len + 1];
				memset(dstTCHAR_1, 0x00, str_Len * 2 + 2);

				MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), dstTCHAR_1, str_Len);
				element_1.Format(L"%s",dstTCHAR_1);
				delete [] dstTCHAR_1;

				if(element_1.Find(_T("RecordID"))!= -1){
					TCHAR* dstTch1 = NULL;
					const char *text = pElem_1->GetText();

					if(text == NULL)
						break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch1 = new TCHAR[str_Len + 1];
					memset(dstTch1, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch1, str_Len);

					str1.Format((L"%s"),dstTch1);
					delete [] dstTch1;
				}else if(element_1.Find(_T("CreateDate"))!= -1){
					TCHAR* dstTch2 = NULL;
					const char *text = pElem_1->GetText();

					if(text == NULL)
						break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch2 = new TCHAR[str_Len + 1];
					memset(dstTch2, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch2, str_Len);

					str2.Format((L"%s"),dstTch2);
					str2.Format((L"%s"),UnixTimeToStrTime(str2.Left(10)));
					delete [] dstTch2;
				}else if(element_1.Find(_T("ModifiedDate"))!= -1){
					TCHAR* dstTch3 = NULL;
					const char *text = pElem_1->GetText();

					if(text == NULL)
						break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch3 = new TCHAR[str_Len + 1];
					memset(dstTch3, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch3, str_Len);

					str3.Format((L"%s"),dstTch3);
					str3.Format((L"%s"),UnixTimeToStrTime(str3.Left(10)));
					delete [] dstTch3;
				}else if((element_1.Right(8) == _T("Location") ))
				{
					TCHAR* dstTch4 = NULL;
					const char *text = pElem_1->GetText();

					if(text == NULL)
						break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch4 = new TCHAR[str_Len + 1];
					memset(dstTch4, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch4, str_Len);

					str4.Format((L"%s"),dstTch4);
					delete []dstTch4;
				}else if(element_1.Find(_T("LocationDecode"))!= -1){
					
					const char *text = pElem_1->GetText();

					if(text == NULL){
						stSMemoXml.recordID = str1;
						stSMemoXml.createDate = str2;
						stSMemoXml.modifiedDate = str3;
						stSMemoXml.location_ = str4;
						stSMemoXml.locationDecode = L"NULL";
						mSMemoXml.insert(pair_SMemoXml(stSMemoXml.recordID, stSMemoXml));
						stSMemoXml.recordID.Empty();
						stSMemoXml.createDate.Empty();
						stSMemoXml.modifiedDate.Empty();
						stSMemoXml.location_.Empty();
						stSMemoXml.locationDecode.Empty();
						break;
					}

					std::string cipher(text);
					PBYTE buf_cipher_ = (PBYTE)malloc(cipher.size()+1);
					buf_cipher_[cipher.size()] = 0x00;
					memcpy(buf_cipher_, cipher.c_str(), cipher.size());

					INT length = base64_decode((PCHAR)buf_cipher_, (unsigned char*)buf_cipher_, cipher.size()-8 );

					wchar_t *patt[4] = {L"<ThumbData>", L"<Text>", L"</ThumbData>", L"</Text>"};
					wchar_t strUnicode[256] = {0,};

					for(int i = 0 ; i < 2 ; i++){
						long startOffset = ps.patternFind((char*)buf_cipher_, length, 0, (char *)patt[i], wcslen(patt[i])*2, pattern_sp::eMethod_KMP) + wcslen(patt[i])*2;

						long endOffset = ps.patternFind((char*)buf_cipher_, length, 0, (char *)patt[i+2], wcslen(patt[i+2])*2, pattern_sp::eMethod_KMP);

						char* buf;int sizes = endOffset - startOffset;
						buf = new char[sizes];

						memcpy_s( buf, sizes, (char*)(buf_cipher_+startOffset), sizes );
						
						for(int a = 0 ; a < sizes ; a+=2){
							buf[a/2] = buf[a];
						}
						int halfsize = sizes/2;
						INT length2 = base64_decode(buf, (unsigned char*)buf, halfsize );

						if(i == 0){
							CFile file_;
							CString PNGFileName = NULL;
							PNGFileName.Format(L"%s%s%s", (CString)outputPath, str1, L"_memo.png");
							if ( !PathFileExists(PNGFileName) )	
							{
								if( file_.Open( PNGFileName, CFile::modeCreate | CFile::modeWrite ) == FALSE )
									return FALSE;
								file_.Write(buf,sizes/2);
								file_.Close();
							}
						}else{
							//int nLen = MultiByteToWideChar(CP_UTF8, 0, (const char*)buf, strlen((char*)buf), NULL, NULL);
							//MultiByteToWideChar(CP_UTF8, 0, (const char*)buf, strlen((const char*)buf), strUnicode, strlen((char*)buf)+10);// utf-8 to unicode
						} delete []buf;
					}
					
					stSMemoXml.recordID = str1;
					stSMemoXml.createDate = str2;
					stSMemoXml.modifiedDate = str3;
					stSMemoXml.location_ = str4;
					stSMemoXml.locationDecode = L"";
					mSMemoXml.insert(pair_SMemoXml(stSMemoXml.recordID, stSMemoXml));
					stSMemoXml.recordID.Empty();
					stSMemoXml.createDate.Empty();
					stSMemoXml.modifiedDate.Empty();
					stSMemoXml.location_.Empty();
					stSMemoXml.locationDecode.Empty();
				}
				pElem_1 = pElem_1->NextSiblingElement();
			}
		}
		pElem = pElem->NextSiblingElement();
	}


END_PROCESS:
	m_Document.Clear();
	if(XMLData)
		delete XMLData;
	CreateWriteSMemoXmlCSVFile((CString)outputPath);
	return 1;
}

BOOL KiesBNR::CreateWriteSMemoXmlCSVFile(CString dstPath){
	pair<multimap<CString, _SMemoXml>::iterator, multimap<CString, _SMemoXml>::iterator>iter_smemoxml;
	multimap<CString, _SMemoXml>::iterator iterSMemoXml;

	CFile cFile;
	CString CSVFileName;
	CString DstFile;

	CSVFileName = dstPath + L"\\SMemoXml.csv";	

	if ( !PathFileExists(CSVFileName) )	
	{
		if( cFile.Open( CSVFileName, CFile::modeCreate | CFile::modeWrite ) == FALSE )
			return FALSE;

		USHORT nUniSig = 0xfeff;
		cFile.Write(&nUniSig, 2);

		CString ColHeader = _T("MemoNum\tCreateDate\tModifiedDate\tLocation\n");
		cFile.Write(ColHeader.GetBuffer(), ColHeader.GetLength()*2);
		cFile.Close();
	}
	CString WriteString;
	for ( iterSMemoXml = mSMemoXml.begin() ; iterSMemoXml != mSMemoXml.end(); ++iterSMemoXml	)
	{
		//CSV 파일 존재 하면 데이터 쓰기
		if ( cFile.Open( CSVFileName, CFile::modeReadWrite | CFile::modeNoTruncate ) == FALSE )
			return FALSE;

		stSMemoXml.recordID = iterSMemoXml->second.recordID; 
		stSMemoXml.createDate = iterSMemoXml->second.createDate;
		stSMemoXml.modifiedDate = iterSMemoXml->second.modifiedDate;
		stSMemoXml.location_ = iterSMemoXml->second.location_;
		stSMemoXml.locationDecode = iterSMemoXml->second.locationDecode;

		//입력할 데이터를 쌍따음표로 묶음
		stSMemoXml.recordID = L"\"" + stSMemoXml.recordID + L"\"";
		stSMemoXml.createDate = L"\"" + stSMemoXml.createDate + L"\"";
		stSMemoXml.modifiedDate = L"\"" + stSMemoXml.modifiedDate + L"\"";
		stSMemoXml.location_ = L"\"" + stSMemoXml.location_ + L"\"";
		stSMemoXml.locationDecode = L"\"" + stSMemoXml.locationDecode + L"\"";

		WriteString = stSMemoXml.recordID + L"\t" + stSMemoXml.createDate + L"\t" + stSMemoXml.modifiedDate + L"\t" + stSMemoXml.location_ + L"\t" + stSMemoXml.locationDecode + L"\n";

		cFile.SeekToEnd();
		cFile.Write(WriteString.GetBuffer(), WriteString.GetLength()*2);
		WriteString.Empty();
		cFile.Close();
	} 

	return TRUE;
}

int KiesBNR::OtherFilestoDecode(char* inputPath, char* outputPath, char* fileName){
	//Read Input File
	CString inputPathString = (CString)inputPath;
	if(!PathFileExists((LPCWSTR)inputPathString))
		return 0;

	UINT XMLDataOffset = 0;

	CFile input;
	if ( !input.Open((LPCWSTR)inputPathString, CFile::modeRead | CFile::modeNoTruncate | CFile::typeBinary) )
	{
		return false;
	}

	//XML 데이터 크기만큼의 버퍼 생성;
	int nBufSize = input.GetLength();
	char* XMLData = new char[nBufSize+1];
	ZeroMemory(XMLData, nBufSize+1);

	//버퍼에 XML 내용을 읽어들인다.;
	input.Seek(XMLDataOffset, input.begin);
	input.Read(XMLData, nBufSize+1);

	//XML 데이터가 NULL일경우 False 반환;
	if (XMLData == NULL) 
		return false;  

	//메모리상에 있는 XML 데이터를 오픈 (Parse);
	TiXmlDocument m_Document;
	m_Document.Parse(XMLData);	// xml open

	// 루트노드 접근.;
	TiXmlElement* pRoot = m_Document.FirstChildElement("MtpUtilItems"); 
	if (!pRoot) 
		goto END_PROCESS;

	// 값을 읽고자 하는 Welcome 엘리먼트로 접근.;
	TiXmlElement* pElem = pRoot->FirstChildElement("Items")->FirstChildElement();

	if (!pElem) 
		goto END_PROCESS;

	while(pElem)
	{
		CString str1=_T("");
		CString element=_T("");
		DWORD str_Len = 0;
		TCHAR * dstTCHAR = NULL;

		char *psNode = (char*)pElem->Value();

		str_Len = MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), NULL, NULL);
		dstTCHAR = new TCHAR[str_Len + 1];
		memset(dstTCHAR, 0x00, str_Len * 2 + 2);

		MultiByteToWideChar(CP_ACP, 0, psNode, strlen(psNode), dstTCHAR, str_Len);
		element.Format(L"%s",dstTCHAR);
		delete [] dstTCHAR;


		if(element.Find(L"MtpUtilItem")!=-1)
		{
			TiXmlElement* pElem_1=pElem->FirstChildElement();

			while(pElem_1)
			{
				CString str_1=_T("");
				CString element_1=_T("");
				DWORD str_Len_1 = 0;
				TCHAR * dstTCHAR_1 = NULL;

				char *psNode_1 = (char*)pElem_1->Value();

				str_Len = MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), NULL, NULL);
				dstTCHAR_1 = new TCHAR[str_Len + 1];
				memset(dstTCHAR_1, 0x00, str_Len * 2 + 2);

				MultiByteToWideChar(CP_ACP, 0, psNode_1, strlen(psNode_1), dstTCHAR_1, str_Len);
				element_1.Format(L"%s",dstTCHAR_1);
				delete [] dstTCHAR_1;

				if(element_1.Find(_T("FileContent"))!= -1){
					TCHAR* dstTch = NULL;
					const char *text = pElem_1->GetText();

					if(text == NULL)
						break;

					str_Len = MultiByteToWideChar(CP_ACP, 0, text, strlen(text), NULL, NULL);
					dstTch = new TCHAR[str_Len + 1];
					memset(dstTch, 0x00, str_Len * 2 + 2);

					MultiByteToWideChar(CP_ACP, 0, text, strlen(text), dstTch, str_Len);

					str1.Format((L"%s"),dstTch);
					delete [] dstTch;
					//base64 Decoding
					string cipher(text);
					PBYTE buf_cipher = (PBYTE)malloc(cipher.size()+1);
					buf_cipher[cipher.size()] = 0x00;
					memcpy(buf_cipher, cipher.c_str(), cipher.size());

					INT length = base64_decode((PCHAR)buf_cipher, buf_cipher, cipher.size());
					strcat_s(outputPath, strlen(outputPath)+8, "Decode_");
					strcat_s(outputPath, strlen(outputPath)+strlen(fileName)+1, fileName);
					
					CFile decodefileoutput;

					if ( !PathFileExists((CString)outputPath) )	
					{
						if( decodefileoutput.Open((CString)outputPath, CFile::modeCreate | CFile::modeWrite ) == FALSE)
							return FALSE;
						decodefileoutput.Write(buf_cipher, length);
						decodefileoutput.Close();
					}

					CArkLib ark;

					if(ark.Create(ARK_DLL_RELEASE_FILE_NAME)!=ARKERR_NOERR)
						return 0;
					if(ark.Open(outputPath) == FALSE)
						return 0;
					int len = strlen(outputPath)+2;
					strcat_s(outputPath, len + 2, "_");
					ark.ExtractAllTo(outputPath);
					ark.Destroy();
					
				}
				pElem_1 = pElem_1->NextSiblingElement();
			}
		}
		pElem = pElem->NextSiblingElement();
	}



END_PROCESS:
	m_Document.Clear();
	if(XMLData)
		delete XMLData;
	return 1;
}

void KiesBNR::splitPath(char* str, char* path, char* name, char* ext)
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

CString KiesBNR::UnixTimeToStrTime(CString UnixTime)
{
	__int64 fftime;
	CTime ct;
	CString YYMM;

	//시스템의 GMT시간 설정 불러오기
	TIME_ZONE_INFORMATION timezone;
	GetTimeZoneInformation( &timezone );
	int gmt = timezone.Bias/60;
	gmt = ( 0xffffffff^gmt )+1;

	//유니코드이므로 _tstoi()를 사용한다.
	fftime = (__int64) _tstoi(UnixTime);

	//CTime은 시스템의 GMT 시간을 적용하기 때문에 그 시간 만끔 빼줘야 한다. -gmt*60*60;
	fftime = fftime - gmt*60*60;
	ct = CTime(fftime);

	YYMM.Format(TEXT("%0.4d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d"),ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	return YYMM;
}

CString KiesBNR::ConvertUTC(CString date, int added_hour){
	struct tm tm;

	swscanf((const wchar_t*)date, L"%d-%d-%dT%d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
	CTime time(tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	time += CTimeSpan(0,added_hour,0,0);
	
	return time.Format(L"%Y-%m-%dT%H:%M:%S");
}
