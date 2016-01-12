#include "myFile.h"

char* PK_EXTENSION = "zip";

MyFile::MyFile()
{
} // Constructor

MyFile::~MyFile()
{
} // Destructor

int MyFile::readNum(FILE* fp, long offset, int size)
{
	char ch;
	char hex[3] = {NULL};
	int dec = 0;

	offset += size - 1;
	fseek(fp, offset, SEEK_SET);

	for(int i=0;i< size;i++) {
		ch = fgetc(fp);

		if ((int)ch < 0)
			ch = (char)(256 + (int)ch);
		sprintf_s(hex, "%02X", (unsigned char)ch);

		if(hex[1] < '0')
			hex[1] = '0';

		dec += (int)(hex2dec(hex[0]) * pow(16, (size-i)*2-1));
		dec += (int)(hex2dec(hex[1]) * pow(16, (size-i)*2-2));

		fseek(fp, --offset, SEEK_SET);
		hex[0] = hex[1] = NULL;
	}
	fseek(fp, offset+size+1, SEEK_SET);
	return dec;
}

int MyFile::readNumBig(FILE* fp, long offset, int size)
{
	char ch;
	char hex[3] = {NULL};
	long dec = 0;

	fseek(fp, offset, SEEK_SET);

	for(int i=0;i< size;i++) {
		ch = fgetc(fp);

		if ((int)ch < 0)
			ch = (char)(256 + (int)ch);
		sprintf_s(hex, "%02X", (unsigned char)ch);

		if(hex[1] < '0')
			hex[1] = '0';

		dec += (long)(hex2dec(hex[0]) * pow(16, (size-i)*2-1));
		dec += (long)(hex2dec(hex[1]) * pow(16, (size-i)*2-2));

		//fseek(fp, --offset, SEEK_SET);
		hex[0] = hex[1] = NULL;
	}

	return dec;
}


string MyFile::readString(FILE* fp, long offset, int size)
{
	char ch;
	string str;

	fseek(fp, offset, SEEK_SET);

	for(int i=0;i< size;i++) {
		ch = fgetc(fp);
		
		str += ch;
	}
	
	return str;
}

string MyFile::readUnicode(FILE* fp, long offset, int size)
{
	if (size <= 0)
		return NULL;

	string result;
	wchar_t* buf = new wchar_t[size/2+1];
	char temp[256];
	
	for(int i=0;i<size/2+1;i++) {
		buf[i] = temp[i] = NULL;
	}
	
	fseek(fp, offset, SEEK_SET);
	
	fread(buf, sizeof(wchar_t), size/2, fp);
	
	int nLen = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, buf, -1, temp, nLen, NULL, NULL);
	
	result = temp;
	
	if (buf != NULL) {
		delete buf;
		buf = NULL;
	}

	return result;
}



int MyFile::hex2dec(char c)
{
	if(c > '9')
		return c - 'A' + 10; 
	return c - '0';
}

int* MyFile::hex2bin(char c, int* addr)
{
	int i = 0;
	int tmp[8] = {0,};
	int remain = c & 0xff;

	memset(addr, 0, 8);

	do {
		tmp[i] = remain % 2;
		remain /= 2;
		++i;
	} while (remain != 0);
	
	for (int j=0;j<i;j++)
		addr[7-j] = tmp[j];

	return addr;
}



int* MyFile::compute_prefix_function(char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int *pi = (int*)malloc(sizeof(int)*psize);

	if (!pi)
		return NULL;

	pi[0] = k;

	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}

int MyFile::KMP(char *target, int tsize, char *pattern, int psize)
{
	int i;
	int *pi = compute_prefix_function(pattern, psize);
	int k = -1;

	if (!pi)
		return -1;

	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			free(pi);
			return i-k;
		}
	}

	free(pi);
	return -1;
}



int MyFile::WriteFile(int wildcard_start, int startOffset, int endOffset, int wildcard_end, char* inPath, char* outPath, char* fileName, int count, char* fileType)
{

#define READ_SIZE 819200	// 메모리 버퍼 크기

	char outputFullPath[256];
	char file[100];
	int index = 1;
	count++;

	// 버퍼 설정
	char wbuf[READ_SIZE];
	memset(wbuf, NULL, sizeof(wbuf));

	int length1;

	FILE* bfile, *wfile;

	// 백업파일 열기
	fopen_s(&bfile, inPath, "rb");
	if( bfile == NULL ) {
		puts("Backup File open Error");
		return 0;
	}
	sprintf_s(outputFullPath, "%s\\%s.%s", outPath, fileName, fileType);
	sprintf_s(file, "%s.%s", fileName, fileType);

	if(fileType == NULL) {
		sprintf_s(outputFullPath, "%s\\%s", outPath, fileName);
		sprintf_s(file, "%s", fileName);
	}

	//if(!_access(outputFullPath, 0)) cout << " [ A file for write already existed]" <<  endl;
	do {
		if(!_access(outputFullPath, 0)) {
			sprintf_s(outputFullPath, "%s\\%s_%d.%s", outPath, fileName, index, fileType);
			sprintf_s(file, "%s_%d.%s", fileName, index++, fileType);
		}
	} while(!_access(outputFullPath, 0));
		
	if( (fileType == "vcf") || (fileType == "vcs") || (fileType == "zip") || (fileType == NULL) )
		cout << " [ Writing... " << file << "]" <<endl;

	// 파일 쓰기
	fopen_s(&wfile, outputFullPath, "w");
		if( wfile == NULL ) {
		puts("WriteFile open Error");
		return 0;
	}

	startOffset -= wildcard_start;
	endOffset += wildcard_end;

	_fseeki64(bfile, startOffset, SEEK_SET);
	endOffset -= startOffset;

	do {
		fread(wbuf, 1, READ_SIZE, bfile);

		if(endOffset < READ_SIZE)
			length1 = (int)endOffset;
		else length1 = READ_SIZE;

		for( int i = 0; i < length1; i++)
			fputc(wbuf[i], wfile);

		endOffset -= READ_SIZE;
	} while(endOffset > 0);
	
	// 파일 닫기
	fclose(wfile);
	fclose(bfile);

	return 1;
}

// 파일 복사 함수
int MyFile::fileCopy(const char* src, const char* dst) {
  FILE *in, *out;
  char* buf;
  size_t len;

  if (!_strcmpi(src, dst)) return 4; // 원본과 사본 파일이 동일하면 에러

  if ((in  = fopen(src, "rb")) == NULL) return 1; // 원본 파일 열기
  if ((out = fopen(dst, "wb")) == NULL) { fclose(in); return 2; } // 대상 파일 만들기

  if ((buf = (char *) malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // 버퍼 메모리 할당

  while ( (len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL )
    if (fwrite(buf, sizeof(char), len, out) == 0) {
      fclose(in); fclose(out);
      free(buf);
      _unlink(dst); // 에러난 파일 지우고 종료
      return 3;
    } 

  fclose(in); fclose(out);
  free(buf); // 메모리 할당 해제

  return 0;
}
