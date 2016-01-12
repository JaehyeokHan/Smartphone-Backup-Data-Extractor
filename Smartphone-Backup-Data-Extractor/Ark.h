////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
///                                      Ark Library 5
/// 
/// �� ���� ������ ���������� ���ؼ� �� ������ �����Ͽ��� �ϴ� ��찡 �߻��� ��� 
///    ���� ������ �� �˷��ֽñ� �ٶ��ϴ�. 
///    �˷��ֽø� �Ź� ������Ʈ���� ����ڴ��� ��������� �����ϴ� ������ �߻����� �ʵ��� 
///    ��ó������� �߰��ϵ��� �ϰڽ��ϴ�.
///
/// @author   parkkh
/// @date     Tuesday, December 22, 2009  9:22:23 AM
/// 
/// Copyright(C) 2008-2014 Bandisoft, All rights reserved.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _ARK_H_
#define _ARK_H_

// ArkLibrary ���� (Ark.h �� ArkXX.dll ������ ������ �������� ���� �Ǵܿ�)
#define ARK_LIBRARY_VERSION								(0x50000000 + 0x00130424)


// �����ڵ�
enum ARKERR 
{
	ARKERR_NOERR										= 0x00,
	ARKERR_CANT_OPEN_FILE								= 0x01,		// ���� ���� ����
	ARKERR_CANT_READ_SIG								= 0x02,		// signature �б� ����
	ARKERR_AT_READ_CONTAINER_HEADER						= 0x03,		// �����̳� ����� �ջ�Ǿ���
	ARKERR_INVALID_FILENAME_LENGTH						= 0x04,		// ���ϸ� ���̿� ����
	ARKERR_READ_FILE_NAME_FAILED						= 0x05,		// �����̸� �б� ����
	ARKERR_INVALID_EXTRAFIELD_LENGTH					= 0x06,		// extra field �б�
	ARKERR_READ_EXTRAFILED_FAILED						= 0x07,		// extra field �б� ����
	ARKERR_CANT_READ_CENTRAL_DIRECTORY_STRUCTURE		= 0x08,		// (zip) Central Directory ������ �дµ� �����Ͽ���
	ARKERR_INVALID_FILENAME_SIZE						= 0x09,		// ���ϸ� ���� ������ �߸��Ǿ���
	ARKERR_INVALID_EXTRAFIELD_SIZE						= 0x10,		// (zip) ExtraField ���� ���̰� �߸��Ǿ���
	ARKERR_INVALID_FILECOMMENT_SIZE						= 0x11,		// Comment ���� ���̰� �߸��Ǿ���
	ARKERR_CANT_READ_CONTAINER_HEADER					= 0x12,		// �����̳��� ����� ������ ����
	ARKERR_MEM_ALLOC_FAILED								= 0x13,		// �޸� �Ҵ� ����
	ARKERR_CANT_READ_DATA								= 0x15,		// ���� ����Ÿ �б� ����
	ARKERR_INFLATE_FAILED								= 0x16,		// Inflate �Լ� ȣ���� ���� �߻�
	ARKERR_USER_ABORTED									= 0x17,		// ����� ����
	ARKERR_INVALID_FILE_CRC								= 0x18,		// ���� ������ CRC ���� �߻�
	ARKERR_UNKNOWN_COMPRESSION_METHOD					= 0x19,		// �𸣴�(Ȥ�� �������� �ʴ�) ������
	ARKERR_PASSWD_NOT_SET								= 0x20,		// ��ȣ�ɸ� �����ε� ��ȣ�� �������� �ʾ���
	ARKERR_INVALID_PASSWD								= 0x21,		// ��ȣ�� Ʋ����
	ARKERR_WRITE_FAIL									= 0x30,		// ���� ���ٰ� ����
	ARKERR_CANT_OPEN_DEST_FILE							= 0x31,		// ��� ������ ���� �� ����
	ARKERR_BZIP2_ERROR									= 0x32,		// BZIP2 ���������� ���� �߻�
	ARKERR_INVALID_DEST_PATH							= 0x33,		// ��θ� ../ �� ���Ե� ���, ��� ��ο� ������ �Ұ����� ���
	ARKERR_CANT_CREATE_FOLDER							= 0x34,		// ��� ���� ����
	ARKERR_DATA_CORRUPTED								= 0x35,		// ����Ǫ�µ� ����Ÿ�� �ջ�� or RAR ���� ���������� �޺κ��� ����
	ARKERR_CANT_OPEN_FILE_TO_WRITE						= 0x36,		// ��������� ���� ���� ����
	ARKERR_INVALID_INDEX								= 0x37,		// ����Ǯ ����� index �Ķ���Ͱ� �߸���
	ARKERR_CANT_READ_CODEC_HEADER						= 0x38,		// ���� �ڵ��� ����� �дµ� ����
	ARKERR_CANT_INITIALIZE_CODEC						= 0x39,		// �ڵ� �ʱ�ȭ ����
	ARKERR_LZMA_ERROR									= 0x40,		// LZMA ���� ������ ���� �߻�
	ARKERR_PPMD_ERROR									= 0x41,		// ppmd ����
	ARKERR_CANT_SET_OUT_FILE_SIZE						= 0x42,		// ��������� SetSize() ����
	ARKERR_NOT_MATCH_FILE_SIZE							= 0x43,		// ������ Ǭ ���� ũ�Ⱑ ���� ����
	ARKERR_NOT_A_FIRST_VOLUME_FILE						= 0x44,		// ���� ���������� ù��° ������ �ƴ�
	ARKERR_NOT_OPENED									= 0x45,		// ������ �������� ����
	ARKERR_NOT_SUPPORTED_ENCRYPTION_METHOD				= 0x46,		// �������� �ʴ� ��ȣ ���
	ARKERR_INTERNAL										= 0x47,		// ���� ����
	ARKERR_NOT_SUPPORTED_FILEFORMAT						= 0x48,		// �������� �ʴ� ���� ����
	ARKERR_UNKNOWN_FILEFORMAT							= 0x49,		// ���������� �ƴ�
	ARKERR_FILENAME_EXCED_RANGE							= 0x50,		// ��θ��� �ʹ� �� �����̳� ������ ���� �� ����
	ARKERR_LZ_ERROR										= 0x52,		// lz ����
	ARKERR_NOTIMPL										= 0x53,		// not implemented
	ARKERR_DISK_FULL									= 0x54,		// ���� ���ٰ� ����
	ARKERR_FILE_TRUNCATED								= 0x55,		// ������ �޺κ��� �߷���
	ARKERR_CANT_DO_THAT_WHILE_WORKING					= 0x56,		// ���� ���� �۾��߿��� ������ ���ų� ���� �� ����
	ARKERR_CANNOT_FIND_NEXT_VOLUME						= 0x57,		// ���� ����� ������ ���� ������ ã�� �� ����
	ARKERR_NOT_ARCHIVE_FILE								= 0x58,		// ���������� �ƴ� (Open() ȣ��� ����� ���������� �ƴ� ��� �߻�)
	ARKERR_USER_SKIP									= 0x59,		// ����ڰ� �ǳʶ�� ����.
	ARKERR_INVALID_PASSWD_OR_BROKEN_ARCHIVE				= 0x60,		// ��ȣ�� Ʋ���ų� ������ �ջ�Ǿ��� (rar ����)
	ARKERR_ZIP_LAST_VOL_ONLY							= 0x61,		// ���� zip �ε� ������ zip ���ϸ� ������ ����
	ARKERR_ACCESS_DENIED_TO_DEST_PATH					= 0x62,		// ��� ������ ���ؼ� ���� ������ ����
	ARKERR_NOT_ENOUGH_MEMORY							= 0x63,		// �޸𸮰� ������
	ARKERR_NOT_ENOUGH_MEMORY_LZMA_ENCODE				= 0x64,		// LZMA ������ �޸𸮰� ������
	ARKERR_CANT_OPEN_SHARING_VIOLATION					= 0x65,		// ������ ����־ �� �� ���� (ERROR_SHARING_VIOLATION, WIN32 ����)
	ARKERR_CANT_OPEN_ERROR_LOCK_VIOLATION				= 0x66,		// ������ ����־ �� �� ���� (ERROR_LOCK_VIOLATION, WIN32 ����)
	ARKERR_CANT_LOAD_UNACE								= 0x67,		// unace32.exe Ȥ�� unacev2.dll ������ �ε��� �� ���� (WIN32 ����)
	ARKERR_NOT_SUPPORTED_OPERATION						= 0x68,		// �������� �ʴ� �۵��Դϴ�. (ACE ������ IArkSimpleOutStream �� �̿��� ���������� ��� �߻�)
	ARKERR_CANT_CONVERT_FILENAME						= 0x69,		// ���ϸ��� �߸��Ǿ �����ڵ� ���ϸ����� �ٲ� �� ����(posix ȯ�濡�� iconv ���� �ڵ��������� �߸��� ��� ����� �� ���� ���� ������ �߻�)
	ARKERR_TOO_LONG_FILE_NAME							= 0x70,		// ���ϸ��� �ʹ� �� ó���� �� ����
	ARKERR_TOO_LONG_FILE_NAME_AND_TRUNCATED				= 0x71,		// ���ϸ��� �ʹ� �� �޺κ��� �߷Ƚ��ϴ�.
	ARKERR_TOO_MANY_FILE_COUNT							= 0x72,		// ���� ������ �ʹ� �� ó���� �� ����
	ARKERR_CANT_OPEN_SRC_FILE_TO_COPY					= 0x73,		// ������ �����ϱ� ���� ���� ������ �� �� ���� (rar5 redirect ó����)

	ARKERR_CORRUPTED_FILE								= 0x100,	// ������ �ջ�Ǿ���
	ARKERR_INVALID_FILE									= 0x101,	// ������ �ٸ���
	ARKERR_CANT_READ_FILE								= 0x102,	// ������ ���� �� ����

	ARKERR_INVALID_VERSION								= 0x200,	// ������ϰ� dll �� ������ ���� ����
	ARKERR_ENCRYPTED_BOND_FILE							= 0x201,	// ���� ���� �Ұ�(��ȣȭ�� bond ������)

	ARKERR_7ZERR_BROKEN_ARCHIVE							= 0x300,	// 7z.dll ���� ���� ������ �߻�(��������)
	ARKERR_LOAD_7Z_DLL_FAILED							= 0x301,	// 7z.dll ���ٰ� ���� �߻�

	ARKERR_CANT_CREATE_FILE								= 0x401,	// ������ ��������� �������� ����
	ARKERR_INIT_NOT_CALLED								= 0x402,	// Init() �Լ��� ȣ����� �ʾ���
	ARKERR_INVALID_PARAM								= 0x403,	// �߸��� �Ķ���ͷ� ȣ���Ͽ���
	ARKERR_CANT_OPEN_INPUT_SFX							= 0x404,	// SFX ������ ���� ����
	ARKERR_SFX_SIZE_OVER_4GB							= 0x405,	// SFX ������ ũ�Ⱑ 4GB�� �Ѿ���
	ARKERR_CANT_LOAD_ARKLGPL							= 0x406,	// ArkXXLgpl.dll ������ ���� ����
	ARKERR_CANT_STORE_FILE_SIZE_OVER_4GB				= 0x407,	// ���� ũ�Ⱑ 4GB�� �Ѿ ������ �� ����

	ARKERR_ALREADY_DLL_CREATED							= 0x902,	// (CArkLib) �̹� ARK DLL ������ �ε��Ͽ���
	ARKERR_LOADLIBRARY_FAILED							= 0x903,	// (CArkLib) LoadLibrary() ȣ�� ����
	ARKERR_GETPROCADDRESS_FAILED						= 0x904,	// (CArkLib) GetProcAddress() ȣ�� ����
	ARKERR_UNSUPPORTED_OS								= 0x905,	// (CArkLib) �������� �ʴ� os 
	ARKERR_LIBRARY_NOT_LOADED							= 0x906,	// (CArkLib) ���̺귯���� �ε����� �ʾҰų� �ε��ϴµ� �����Ͽ���
};


// ARK FILE FORMAT
enum ARK_FF
{
	ARK_FF_ZIP,								// zip, zipx
	ARK_FF_ZIP_LASTVOLONLY,					// ���� zip ������ ������ ���� (������ �ϳ��� ������ ���)
	ARK_FF_ZIP_BANDIZIP_SFX,				// �ݵ��� sfx 
	ARK_FF_ALZ,
	ARK_FF_ALZ_SECONDVOL,					// ���� alz ������ 2��° ���� ��������
	ARK_FF_LZH,
	ARK_FF_RAR,
	ARK_FF_RAR5,
	ARK_FF_RAR_SECONDVOL,					// ���� RAR ������ 2��° ���� ��������
	ARK_FF_7Z,
	ARK_FF_7ZSPLIT,							// 7z ������ �޺κ��� �߷Ȱ� Ȯ���ڰ� .001 �� ���� (.7z.001 ~ .7z.NNN)
	ARK_FF_7ZBROKEN,						// 7z ������ �޺κ��� �߷Ȱų� ����� �ջ�� ����
	ARK_FF_TAR,
	ARK_FF_CAB,
	ARK_FF_CAB_NOTFIRSTVOL,					// 
	ARK_FF_ISO,								// iso, joliet
	ARK_FF_IMG,								// clone cd img (img, ccd)
	ARK_FF_UDF,
	ARK_FF_UDFBROKEN,						// �޺κ��� �߸� UDF 
	ARK_FF_SPLIT,							// Ȯ���ڰ� .001 �� ���� (.001 ~ .NNN)
	ARK_FF_BOND,							// hv3
	ARK_FF_GZ,
	ARK_FF_BZ2,
	ARK_FF_LZMA,
	ARK_FF_BH,								// blakhole
	ARK_FF_EGG,
	ARK_FF_EGG_NOTFIRSTVOL,					// ���� ������ ù��° ������ �ƴ� ����
	ARK_FF_XZ,
	ARK_FF_WIM,								// raw �� ����ϴ� wim
	ARK_FF_WIM_COMPRESSED,					// ����� wim, Windows ������ ����
	ARK_FF_FREEARC,							// FreeArc - ���� ��Ͽ��⸸ ����
	ARK_FF_Z,								// .Z (unix compress)
	ARK_FF_ARJ,								// arj 
	ARK_FF_BAMSFX,							// ������ sfx
	ARK_FF_BAMSFX_NOTFIRSTVOL,				// 
	ARK_FF_TGZ,								// .tar.gz
	ARK_FF_TBZ,								// .tar.bz2
	ARK_FF_J2J,								// .j2j
	ARK_FF_J2JBROKEN,						// �޺κ��� �߸� j2j
	ARK_FF_K2K,								// .k2k
	ARK_FF_NSIS,							// nsis exe

	ARK_FF_UNKNOWN				= 0x00ff,	// �� �� ���� ���� ����

	ARK_FF_UNSUPPORTED_FIRST	= 0x0100,	// �������� �ʴ� �������� ����
	ARK_FF_SIT					= 0x0100,	// sit
	ARK_FF_BPE					= 0x0101,	// bpe
	ARK_FF_ACE					= 0x0102,	// ace
	ARK_FF_PAE					= 0x0104,	// PowerArchiver Encryption
	ARK_FF_XEF					= 0x0105,	// Winace Encryption
	ARK_FF_COMPOUND				= 0x0106,	// MSI, XLS, PPT, DOC ...
	ARK_FF_UNSUPPORTED_LAST		= 0x01FF,

	ARK_FF_NOTARCHIVE_FIRST		= 0x0200,	// ����� ���������� �ƴ� ���� (��������, �̹������� ���..)
	ARK_FF_NULL					= 0x0201,	// ������ �պκ��� ���� 0 ���� ä���� �ִ� ����
	ARK_FF_RIFF					= 0x0202,	// avi, wav
	ARK_FF_EXE					= 0x0203,	// sfx �� �ƴ� �Ϲ� PE ��������
	ARK_FF_HTML					= 0x0204,	// HTML(��Ȯ������ ����)
	ARK_FF_JPG					= 0x0205,	// 
	ARK_FF_PNG					= 0x0206,	// 
	ARK_FF_GIF					= 0x0207,	// 
	ARK_FF_OGGS					= 0x0208,	// OggS
	ARK_FF_MATROSKA				= 0x0209,	// MKV
	ARK_FF_PDF					= 0x020a,	// PDF
	ARK_FF_NOTARCHIVE_LAST		= 0x020a,

};

// ��ȣȭ ���
enum ARK_ENCRYPTION_METHOD
{
	ARK_ENCRYPTION_METHOD_NONE				= 0x00,
	ARK_ENCRYPTION_METHOD_ZIP				= 0x01,	// ZipCrypto
	ARK_ENCRYPTION_METHOD_AES128			= 0x02,	// zip
	ARK_ENCRYPTION_METHOD_AES192			= 0x03,	
	ARK_ENCRYPTION_METHOD_AES256			= 0x04,
											
	ARK_ENCRYPTION_METHOD_EGG_ZIP			= 0x05,	// EGG ���˿��� ���
	ARK_ENCRYPTION_METHOD_EGG_AES128		= 0x06,
	ARK_ENCRYPTION_METHOD_EGG_AES256		= 0x07,

	ARK_ENCRYPTION_METHOD_RAR				= 0x08,	// RAR ��ȣ ���
	ARK_ENCRYPTION_METHOD_ACE				= 0x09,	// ACE ��ȣ

	ARK_ENCRYPTION_METHOD_ETC				= 0x99,	

	ARK_ENCRYPTION_METHOD_NOTSUPPORTED_FIRST= 0x100,	// Not supported encryption method
	ARK_ENCRYPTION_METHOD_GARBLE,						// ARJ ��ȣ ���
	ARK_ENCRYPTION_METHOD_DES,
	ARK_ENCRYPTION_METHOD_RC2,
	ARK_ENCRYPTION_METHOD_3DES168,
	ARK_ENCRYPTION_METHOD_3DES112,
	ARK_ENCRYPTION_METHOD_PKAES128,
	ARK_ENCRYPTION_METHOD_PKAES192,
	ARK_ENCRYPTION_METHOD_PKAES256,
	ARK_ENCRYPTION_METHOD_RC2_2,
	ARK_ENCRYPTION_METHOD_BLOWFISH,
	ARK_ENCRYPTION_METHOD_TWOFISH,
	ARK_ENCRYPTION_METHOD_RC4,
	ARK_ENCRYPTION_METHOD_UNKNOWN,
};

// ���� ���
enum ARK_COMPRESSION_METHOD
{
	/////////////////////////////////////////////////////////////////
	// zip ���� ����ϴ°͵�, zip ���˿� ���ǵ� ���� �����ϴ�.
	// (http://www.pkware.com/documents/casestudies/APPNOTE.TXT ����)
	ARK_COMPRESSION_METHOD_STORE		=	0,
	ARK_COMPRESSION_METHOD_SHRINK		=	1,
	ARK_COMPRESSION_METHOD_IMPLODE		=	6,
	ARK_COMPRESSION_METHOD_DEFLATE		=	8,

	ARK_COMPRESSION_METHOD_DEFLATE64	=	9,
	ARK_COMPRESSION_METHOD_BZIP2		=	12,
	ARK_COMPRESSION_METHOD_LZMA			=	14,		// zipx, 7zip ...
	ARK_COMPRESSION_METHOD_JPEG			=	96,		// zipx
	ARK_COMPRESSION_METHOD_WAVPACK		=	97,		// zipx
	ARK_COMPRESSION_METHOD_PPMD			=	98,		// zipx, 7zip
	ARK_COMPRESSION_METHOD_AES			=	99,		// aes �� ��ȣȭ�� zip ����. ���� ���� ����� �ٸ����� ����ȴ�.
	// 
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// ETC
	ARK_COMPRESSION_METHOD_FUSE			=	300,	// bh ���� ��� 
	ARK_COMPRESSION_METHOD_FUSE6		=	301,	// bh ���� ��� 
	ARK_COMPRESSION_METHOD_AZO			=	302,	// egg ���� ���
	ARK_COMPRESSION_METHOD_COMPRESS		=	303,	// .Z ���� ���

	ARK_COMPRESSION_METHOD_RAR15		=	400,	// RAR 1.5
	ARK_COMPRESSION_METHOD_RAR20		=	401,	// RAR 2.X
	ARK_COMPRESSION_METHOD_RAR26		=	402,	// RAR 2.X & 2GB �̻�
	ARK_COMPRESSION_METHOD_RAR29		=	403,	// RAR 3.X
	ARK_COMPRESSION_METHOD_RAR36		=	404,	// RAR 3.X alternative hash
	ARK_COMPRESSION_METHOD_RAR50		=	405,	// RAR 5.0
	ARK_COMPRESSION_METHOD_REDIR		=	406,	// Redirect (RAR5)

	ARK_COMPRESSION_METHOD_MSZIP		=	500,	// CAB
	ARK_COMPRESSION_METHOD_LHA			=	501,	// lzh
	ARK_COMPRESSION_METHOD_LZMA2		=	502,	// 7z
	ARK_COMPRESSION_METHOD_BCJ			=	503,	// 7z
	ARK_COMPRESSION_METHOD_BCJ2			=	504,	// 7z
	ARK_COMPRESSION_METHOD_LZX			=	505,	// CAB
	ARK_COMPRESSION_METHOD_LZXWIM		=	506,	// wim
	ARK_COMPRESSION_METHOD_OBDEFLATE	=	508,	// Obfuscated deflate (alz)
	ARK_COMPRESSION_METHOD_DELTA		=	509,	// 7z
	ARK_COMPRESSION_METHOD_XPRESS		=	510,	// wim - xpress

	ARK_COMPRESSION_METHOD_LH0			=	600,	// -lh0-
	ARK_COMPRESSION_METHOD_LH1			=	601,	// -lh1-
	ARK_COMPRESSION_METHOD_LH2			=	602,	// -lh2-
	ARK_COMPRESSION_METHOD_LH3			=	603,	// -lh3-
	ARK_COMPRESSION_METHOD_LH4			=	604,	// -lh4-
	ARK_COMPRESSION_METHOD_LH5			=	605,	// -lh5-
	ARK_COMPRESSION_METHOD_LH6			=	606,	// -lh6-
	ARK_COMPRESSION_METHOD_LH7			=	607,	// -lh7-
	ARK_COMPRESSION_METHOD_LZS			=	608,	// -lzs-
	ARK_COMPRESSION_METHOD_LZ5			=	609,	// -lz5-
	ARK_COMPRESSION_METHOD_LZ4			=	610,	// -lz4-
	ARK_COMPRESSION_METHOD_LHD			=	611,	// -lhd-
	ARK_COMPRESSION_METHOD_PM0			=	612,	// -pm0-
	ARK_COMPRESSION_METHOD_PM2			=	613,	// -pm2-

	ARK_COMPRESSION_METHOD_LZX15		=	715,	// LZX (WINDOW SIZE 15bit)
	ARK_COMPRESSION_METHOD_LZX16		=	716,	// 
	ARK_COMPRESSION_METHOD_LZX17		=	717,	// 
	ARK_COMPRESSION_METHOD_LZX18		=	718,	// 
	ARK_COMPRESSION_METHOD_LZX19		=	719,	// 
	ARK_COMPRESSION_METHOD_LZX20		=	720,	// 
	ARK_COMPRESSION_METHOD_LZX21		=	721,	// LZX (WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_QUANTUM10	=	810,	// QTMD(WINDOW SIZE 10bit)
	ARK_COMPRESSION_METHOD_QUANTUM11	=	811,	//
	ARK_COMPRESSION_METHOD_QUANTUM12	=	812,	//
	ARK_COMPRESSION_METHOD_QUANTUM13	=	813,	//
	ARK_COMPRESSION_METHOD_QUANTUM14	=	814,	//
	ARK_COMPRESSION_METHOD_QUANTUM15	=	815,	//
	ARK_COMPRESSION_METHOD_QUANTUM16	=	816,	//
	ARK_COMPRESSION_METHOD_QUANTUM17	=	817,	//
	ARK_COMPRESSION_METHOD_QUANTUM18	=	818,	//
	ARK_COMPRESSION_METHOD_QUANTUM19	=	819,	//
	ARK_COMPRESSION_METHOD_QUANTUM20	=	820,	//
	ARK_COMPRESSION_METHOD_QUANTUM21	=	821,	// QTMD(WINDOW SIZE 21bit)

	ARK_COMPRESSION_METHOD_ARJ1			=	901,	// Arj Method 1
	ARK_COMPRESSION_METHOD_ARJ2			=	902,	//            2
	ARK_COMPRESSION_METHOD_ARJ3			=	903,	//            3
	ARK_COMPRESSION_METHOD_ARJ4			=	904,	//            4

	ARK_COMPRESSION_METHOD_ACELZ77		=	910,	// ace lz77
	ARK_COMPRESSION_METHOD_ACE20		=	911,	// ace v20
	ARK_COMPRESSION_METHOD_ACE			=	912,	// ace �ֽ�?

	// 
	/////////////////////////////////////////////////////////////////

	ARK_COMPRESSION_METHOD_UNKNOWN		=	9999,	// unknown
};

// ���� ���� ��Ÿ��
enum ARK_MULTIVOL_STYLE
{
	ARK_MULTIVOL_STYLE_NONE,			// ���� ���������� �ƴ�
	ARK_MULTIVOL_STYLE_001,				// 7zip �� 001, 002, .. ��Ÿ��
	ARK_MULTIVOL_STYLE_WINZIP,			// winzip ��Ÿ��  (z01, z02 ..... zip)
	ARK_MULTIVOL_STYLE_ZIPX,			// winzip zipx ��Ÿ��  (zx01, zx02 ..... zipx)
	ARK_MULTIVOL_STYLE_ALZ,				// alzip �� alz, a00, a01, a02, .. ��Ÿ��
	ARK_MULTIVOL_STYLE_EGG,				// vol1.egg vol2.egg vol3.egg ... ��Ÿ��
	ARK_MULTIVOL_STYLE_RAR,				// part1.rar part2.rar ... ��Ÿ��
	ARK_MULTIVOL_STYLE_R00,				// .rar .r00 .r01 ��Ÿ��
	ARK_MULTIVOL_STYLE_ARJ,				// .arj .a01 .a02 ��Ÿ��
	ARK_MULTIVOL_STYLE_BAMSFX,			// ������ sfx (exe, .002 .003 ...)
	ARK_MULTIVOL_STYLE_BDZSFX,			// �ݵ��� SFX (exe, .e01 .e02 ...)
	ARK_MULTIVOL_STYLE_CAB,				// ���� cab ����
};


// ���� �Ӽ�
#define ARK_FILEATTR					unsigned int
#define ARK_FILEATTR_NONE				0x00
#define ARK_FILEATTR_READONLY			0x01	// FILE_ATTRIBUTE_READONLY
#define ARK_FILEATTR_HIDDEN				0x02	// FILE_ATTRIBUTE_HIDDEN
#define ARK_FILEATTR_SYSTEM				0x04	// FILE_ATTRIBUTE_SYSTEM
#define ARK_FILEATTR_DIRECTORY			0x10	// FILE_ATTRIBUTE_DIRECTORY
#define ARK_FILEATTR_FILE				0x20	// FILE_ATTRIBUTE_ARCHIVE

// �ڵ� ������
#define ARK_CP_ACP						0		// == CP_ACP
#define ARK_CP_OEM						1		// == CP_OEMCP
#define ARK_CP_KOR						949		// EUC-KR, CP949 
#define ARK_CP_JPN						932		// SHIFT-JIS, CP932
#define ARK_CP_UTF8						65001	// == CP_UTF8
#define ARK_CP_UTF8_MAC					65002	// �ƿ� utf8 �ڵ� ������


// ��Ÿ ����
#define ARK_FILESIZE_UNKNOWN			(0xffffffffffffffffLL)	// ���� ũ�⸦ �� �� ������ ���Ǵ� ��

// WIN32 �̿��� �ý����� ��� �⺻ Ÿ�� ����
#ifndef TRUE
	#define FALSE               0
	#define TRUE                1
	typedef char				CHAR;
	typedef wchar_t				WCHAR;
	typedef unsigned int		UINT32;
	typedef const char*			LPCSTR;
	typedef const wchar_t*		LPCWSTR;
#endif

// BOOL ��� BOOL32 �� ����Ѵ�.
typedef int				BOOL32;
typedef unsigned char   ARKBYTE;


#ifndef PURE
#	define PURE                = 0
#endif

#ifdef _WIN32
	typedef signed __int64      INT64;
	#define WINAPI				__stdcall
#else
	typedef signed long long	INT64;
	#define WINAPI				
	#define THREAD_PRIORITY_NORMAL 0
#endif

// use os default packing
#ifndef __APPLE__
#	pragma pack()
#endif

// �������̽� �޽�� Ÿ�� ����
#define ARKMETHOD(type)	virtual type WINAPI

#define ARK_TIME_T			INT64					// time_t �� ����
struct SArkFileTime									// FILETIME(ntfs)�� ����
{
	UINT32 dwLowDateTime;
	UINT32 dwHighDateTime;
};
struct SArkNtfsFileTimes							// NTSF ���� �ð� ����
{
	SArkFileTime	mtime;							// ������ ���� �ð�
	SArkFileTime	ctime;							// ������ ������ �ð�
	SArkFileTime	atime;							// ���������� ���Ͽ� ������ �ð�
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� ������ ����
//
struct SArkFileItem
{
	CHAR*					fileName;					// �������Ͽ� ����� ���ϸ� (�� �̸��� ���� ��θ� �����Ѵ�)
	WCHAR*					fileNameW;
	WCHAR*					fileCommentW;
	ARK_TIME_T				fileTime;					// last modified(write) time
	INT64					compressedSize;
	INT64					uncompressedSize;
	ARK_ENCRYPTION_METHOD	encryptionMethod;
	ARK_FILEATTR			attrib;
	UINT32					crc32;
	ARK_COMPRESSION_METHOD	compressionMethod;
	SArkNtfsFileTimes*		ntfsFileTimes;				// NTFS ���� �ð� ����. �������Ͽ� NTFS ���������� ������ NULL��
	BOOL32					isUnicodeFileName;			// �����ڵ带 �����ϴ� ���������� ���ؼ� ������ ���� �̸��ΰ�? (��, fileNameW�� 100% ���� �� �ִ°�)

	BOOL32					IsFolder() const { return attrib & ARK_FILEATTR_DIRECTORY ? TRUE : FALSE;}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� �� ���� ���� ���� ��Ȳ ����
//
struct SArkProgressInfo
{
	float		fCurPercent;		// ���� ������ ���� ���� ������(%)
	float		fTotPercent;		// ��ü ������ ���� ���� ������(%)
	BOOL32		bCompleting;		// ������ ���ΰ�?
	float		fCompletingPercent;	// ������ ���϶� ������(%)
	int			_processed;			// undocumented - do not use
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ark �ɼ� ����
//
struct SArkGlobalOpt
{
	SArkGlobalOpt()
	{
		bPrintAssert = TRUE;
		bTreatTGZAsSolidArchive = FALSE;
		bTreatTBZAsSolidArchive = FALSE;
		bAzoSupport = FALSE;
		bTreatUnixZipFileNameAsUTF8 = TRUE;
		bConvertNFD2NFCWhenMacOS = FALSE;
		bIgnoreMacOSXMetaFolder = FALSE;
		bUseLongPathName = FALSE;
		bOpenArchiveWithShareDelete = FALSE;
	}
	BOOL32 bPrintAssert;				// ASSERT �߻��� stdout �� ��� ���� ����(posix ����)
	BOOL32 bTreatTGZAsSolidArchive;		// TGZ ������ �ָ��� ����� ����ó�� ó���ϱ�
	BOOL32 bTreatTBZAsSolidArchive;		// TBZ ������ �ָ��� ����� ����ó�� ó���ϱ�
	BOOL32 bAzoSupport;					// azo �˰��� ���� ����
	BOOL32 bTreatUnixZipFileNameAsUTF8;	// zip ������ unix ���� ����� ��� ������ utf8 �ڵ������� ó��
	BOOL32 bConvertNFD2NFCWhenMacOS;	// MAC OS ���� ������ ������ ��� NFD�� NFC�� �ڵ� ��ȯ
	BOOL32 bIgnoreMacOSXMetaFolder;		// zip ������ __MACOSX/ ������ �����Ѵ�.
	BOOL32 bUseLongPathName;			// ��θ��� 260�ڰ� �Ѿ �����̳� ������ �����ϱ�(Win32 ����)
	BOOL32 bOpenArchiveWithShareDelete;	// �������� ���� FILE_SHARE_DELETE �Ӽ����� ����(Win32 ����)
};

// �ڵ������� ����
struct SArkDetectCodepage
{
	SArkDetectCodepage()
	{ fileCount2Detect=100; codePage = 0; codePageName[0] = 0; confidence=0; have2change=FALSE; }
	int		fileCount2Detect;			// [in] �տ��� ���� ��� ���ϸ��� ������ ó���� ���ΰ�?
	int		codePage;					// [out] windows �� codepage ����
	char	codePageName[128];			// [out] codepage ���ڿ� �̸�
	int		confidence;					// [out] �νĵ� �ڵ��������� �ŷڵ� (0~100)
	BOOL32	have2change;				// [out] ���� �ڵ��������� ������ �ִµ� �ϴ�. confidence ��ġ�� ���Ƶ� �ٲٴ°� ������.
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� ���� ���� ��Ȳ
//
enum ARK_OVERWRITE_MODE				// ���� ����� ������ ���� ����� ���
{
	ARK_OVERWRITE_MODE_OVERWRITE,
	ARK_OVERWRITE_MODE_SKIP, 
	ARK_OVERWRITE_MODE_RENAME,
};
enum ARK_PASSWORD_RET				// ���� ��ȣ ������ ���� ����� ���
{
	ARK_PASSWORD_RET_OK,
	ARK_PASSWORD_RET_CANCEL, 
};
enum ARK_PASSWORD_ASKTYPE			// OnAskPassword() ȣ�� ����
{
	ARK_PASSWORD_ASKTYPE_PASSWDNOTSET,	// ��ȣ�� �������� �ʾ���
	ARK_PASSWORD_ASKTYPE_INVALIDPASSWD,	// ������ ������ ��ȣ�� Ʋ����
};
#define ARK_MAX_PATH		300
#define ARK_MAX_PASS		300
struct IArkEvent
{
	ARKMETHOD(void)			OnOpening(const SArkFileItem* pFileItem, float progress, BOOL32& bStop) PURE;

	ARKMETHOD(void)			OnStartFile(const SArkFileItem* pFileItem, BOOL32& bStopCurrent, BOOL32& bStopAll, int index) PURE;
	ARKMETHOD(void)			OnProgressFile(const SArkProgressInfo* pProgressInfo, BOOL32& bStopCurrent, BOOL32& bStopAll) PURE;
	ARKMETHOD(void)			OnCompleteFile(const SArkProgressInfo* pProgressInfo, ARKERR nErr) PURE;

	ARKMETHOD(void)			OnError(ARKERR nErr, const SArkFileItem* pFileItem, BOOL32 bIsWarning, BOOL32& bStopAll) PURE;
	ARKMETHOD(void)			OnMultiVolumeFileChanged(LPCWSTR szPathFileName) PURE;

	ARKMETHOD(void)			OnAskOverwrite(const SArkFileItem* pFileItem, LPCWSTR szLocalPathName, ARK_OVERWRITE_MODE& overwrite, WCHAR pathName2Rename[ARK_MAX_PATH]) PURE;
	ARKMETHOD(void)			OnAskPassword(const SArkFileItem* pFileItem, ARK_PASSWORD_ASKTYPE askType, ARK_PASSWORD_RET& ret, WCHAR passwordW[ARK_MAX_PASS]) PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �������� ��� ��Ʈ��
//
struct IArkSimpleOutStream
{
	ARKMETHOD(BOOL32)		Open(LPCWSTR szPathName) PURE;
	ARKMETHOD(BOOL32)		SetSize(INT64 nSize) PURE;
	ARKMETHOD(BOOL32)		Write(const void* lpBuffer, UINT32 nNumberOfBytesToWrite) PURE;
	ARKMETHOD(BOOL32)		Close() PURE;
	ARKMETHOD(BOOL32)		CreateFolder(LPCWSTR szPathName) PURE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �������� �Է� ��Ʈ��
//
struct IArkSimpleInStream
{
	ARKMETHOD(BOOL32)		Read(void* lpBuffer, UINT32 nNumberOfBytesToRead, UINT32* lpNumberOfBytesRead) PURE;
	ARKMETHOD(INT64)		SetPos(INT64 pos) PURE;
	ARKMETHOD(INT64)		GetPos() PURE;
	ARKMETHOD(INT64)		GetSize() PURE;
	ARKMETHOD(BOOL32)		Close() PURE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MBCS ó���� �ڵ�������
//
struct SArkCodepage
{
	SArkCodepage(){Init();}
	SArkCodepage(int a, int b, int c, int d) {}
	void Init()
	{
		#ifdef _WIN32
		fileSystem = ARK_CP_ACP;
		#else
		fileSystem = ARK_CP_UTF8;	// POSIX �� ���Ͻý��ۿ� ���� UTF8 �ڵ������� ���
		#endif
		fileName = ARK_CP_OEM;
		comment = ARK_CP_ACP;
		password = ARK_CP_ACP;
	}
	int		fileSystem;				// ���� �ý����� ���� ���������� �� �� ����ϴ� �ڵ�������. ���� CP_ACP
	int		fileName;				// �������� ������ ���ϸ��� ó���Ҷ� ����ϴ� �ڵ�������. ���� CP_OEM
	int		comment;				// �������� ������ �ڸ�Ʈ�� ó���Ҷ� ����ϴ� �ڵ�������. ���� CP_ACP
	int		password;				// MBCS ��ȣ�� ó���Ҷ� ����ϴ� �ڵ�������. ���� CP_ACP
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���������� ���� ���� �������̽�
//
struct IArk
{
	ARKMETHOD(void)					Release() PURE;
									
	ARKMETHOD(BOOL32)  				Open(LPCSTR  filePath, LPCSTR password) PURE; 
	ARKMETHOD(BOOL32)  				Open(LPCWSTR filePath, LPCWSTR password) PURE; 
	ARKMETHOD(BOOL32)				Open(ARKBYTE* src, int srcLen, LPCWSTR password) PURE;
	ARKMETHOD(BOOL32)  				Open(IArkSimpleInStream* srcStream, LPCWSTR password) PURE; 
	ARKMETHOD(void)					Close() PURE;
	ARKMETHOD(BOOL32)  				TestArchive() PURE; 

	ARKMETHOD(ARK_FF)  				CheckFormat(LPCSTR  filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(LPCWSTR filePath) const PURE; 
	ARKMETHOD(ARK_FF)  				CheckFormat(const unsigned char* buffer, int bufLen) const PURE; 

	ARKMETHOD(void)					SetPassword(LPCSTR password) PURE;
	ARKMETHOD(void)					SetPassword(LPCWSTR password) PURE;
	ARKMETHOD(int)					GetFileItemCount() const PURE;
	ARKMETHOD(const SArkFileItem*)	GetFileItem(int index) const PURE;
	ARKMETHOD(ARK_FF)				GetFileFormat() const PURE;
	ARKMETHOD(BOOL32)				IsBrokenArchive() const PURE;
	ARKMETHOD(BOOL32)				IsEncryptedArchive() const PURE;
	ARKMETHOD(BOOL32)				IsSolidArchive() const PURE;
	ARKMETHOD(BOOL32)				IsOpened() const PURE;

	ARKMETHOD(BOOL32)				ExtractAllTo(LPCSTR folderPath) PURE;						// ��ü ���� Ǯ��
	ARKMETHOD(BOOL32)				ExtractAllTo(LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				ExtractAllTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL32)				ExtractOneTo(int index, LPCWSTR folderPath) PURE;			// �ϳ� ���� Ǯ��
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, LPCSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, IArkSimpleOutStream* outStream) PURE;
	ARKMETHOD(BOOL32)				ExtractOneTo(int index, ARKBYTE* outBuf, int outBufLen) PURE;
	ARKMETHOD(BOOL32)				ExtractOneAs(int index, LPCWSTR filePathName, WCHAR resultPathName[ARK_MAX_PATH]) PURE;			// ���ϸ��� �����ؼ� ���� �ϳ� Ǯ��

	ARKMETHOD(BOOL32)				AddIndex2ExtractList(int index) PURE;						// ����Ǯ ���� �ε����� ��Ͽ� �߰�
	ARKMETHOD(void)					ClearExtractList() PURE;									// ����Ǯ ���� ��� �����ϱ�
	ARKMETHOD(int)					GetExtractListCount() const PURE;							// ����Ǯ ���� ����� ����
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(LPCSTR szDestPath) PURE;					// � ���� Ǯ��
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL) PURE;
	ARKMETHOD(BOOL32)				ExtractMultiFileTo(IArkSimpleOutStream* outStream) PURE;

	ARKMETHOD(BOOL32)				SetEvent(IArkEvent* pEvent) PURE;
	ARKMETHOD(ARKERR)				GetLastError() const PURE;
	ARKMETHOD(UINT32)				GetLastSystemError() const PURE;
	ARKMETHOD(void)					SetCodePage(SArkCodepage cp) PURE;

	ARKMETHOD(LPCWSTR)				EncryptionMethod2Str(ARK_ENCRYPTION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				CompressionMethod2Str(ARK_COMPRESSION_METHOD method) const PURE;
	ARKMETHOD(LPCWSTR)				FileFormat2Str(ARK_FF ff) const PURE;

	ARKMETHOD(void)					SetGlobalOpt(const SArkGlobalOpt& opt) PURE;
	ARKMETHOD(INT64)				GetArchiveFileSize() const PURE;
	ARKMETHOD(INT64)				GetArchiveStartPos() const PURE;
	ARKMETHOD(LPCWSTR)				GetFilePathName() const PURE;
	ARKMETHOD(int)					FindIndex(LPCWSTR szFileNameW, LPCSTR szFileNameA, BOOL32 bCaseSensitive) const PURE;
	ARKMETHOD(LPCWSTR)				GetArchiveComment() const PURE;

	ARKMETHOD(ARK_MULTIVOL_STYLE)	GetMultivolStyle() const PURE;
	ARKMETHOD(int)					GetMultivolCount() const PURE;
	ARKMETHOD(LPCWSTR)				GetMultivolFilePathName(int volume) const PURE;

	ARKMETHOD(BOOL32)				DetectCurrentArchivesCodepage(SArkDetectCodepage& dcp) const PURE;
	ARKMETHOD(BOOL32)				ChangeCurrentArchivesCodepage(int codePage) PURE;


	///////////////////////
	// undocumented (do not use)
	ARKMETHOD(void)					_Test() PURE;
	ARKMETHOD(const void*)			_GetBondFileInfo() PURE;
	ARKMETHOD(LPCWSTR)				_GetAlias() PURE;
	ARKMETHOD(void)					_SetAlias(LPCWSTR szAlias) PURE;
	ARKMETHOD(void)					_SetUserKey(void* key) PURE;
	ARKMETHOD(UINT32)  				_CheckCRC32(LPCWSTR filePath) PURE; 
	ARKMETHOD(void*)				_GetExtractor() PURE;
	ARKMETHOD(void*)				_GetInStream() PURE;
	ARKMETHOD(BOOL32)				_DisableItem(int index) PURE;

	// for c++ builder
	ARKMETHOD(BOOL32)  				_OpenW(LPCWSTR filePath, LPCWSTR password) PURE; 
	ARKMETHOD(ARK_FF)  				_CheckFormatW(LPCWSTR filePath) const PURE; 
	ARKMETHOD(void)					_SetPasswordW(LPCWSTR password) PURE;
	ARKMETHOD(BOOL32)				_ExtractAllToW(LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				_ExtractOneToW(int index, LPCWSTR folderPath) PURE;
	ARKMETHOD(BOOL32)				_ExtractMultiFileToW(LPCWSTR szDestPath, LPCWSTR szPath2Remove=NULL) PURE;
};


/////////////////////////////////////////////////////////
//
// ���� �ɼ�
//
struct SArkCompressorOpt
{
	SArkCompressorOpt(){Init();}
	void Init()
	{
		ff = ARK_FF_ZIP;
		saveNTFSTime = FALSE;
		streamOutput = FALSE;
		compressionMethod = ARK_COMPRESSION_METHOD_DEFLATE;
		encryptionMethod = ARK_ENCRYPTION_METHOD_ZIP;
		compressionLevel = -1;							// -1 �� Z_DEFAULT_COMPRESSION
		splitSize = 0;
		forceZip64 = FALSE;
		useDosTime2PasswordCheck = TRUE;
		sfxPathName = NULL;
		forceUtf8FileName = FALSE;
		forceUtf8Comment = FALSE;
		utf8FileNameIfNeeded = TRUE;
		bypassWhenUncompressible = FALSE;
		lzmaEncodeThreadCount = 2;
		enableMultithreadDeflate = FALSE;
		deflateEncodeThreadCount = 0;
		_7zCompressHeader = TRUE;
		_7zEncryptHeader = FALSE;
		lzma2NumBlockThreads = -1;
		threadPriority = 0;
		deleteArchiveWhenFailed = TRUE;
	}
	ARK_FF					ff;							// ���� ���� ARK_FF_ZIP, ARK_FF_TAR, ARK_FF_TGZ, ARK_FF_7Z, ARK_FF_LZH, ARK_FF_ISO
	BOOL32					saveNTFSTime;				// ntfs �ð� ���� ����
	BOOL32					streamOutput;				// stream ���·� ���� - �� ���� TRUE �� ��� ���� ���ϴ� ���α׷��� �ʹ� ����.
	ARK_COMPRESSION_METHOD	compressionMethod;			// ���� ��� ( ARK_COMPRESSION_METHOD_STORE, ARK_COMPRESSION_METHOD_DEFLATE, ARK_COMPRESSION_METHOD_LZMA )
	ARK_ENCRYPTION_METHOD	encryptionMethod;			// ���Ͽ� ��ȣ�� �� ��� ����� ��ȣ ��� ( ARK_ENCRYPTION_METHOD_ZIP, ARK_ENCRYPTION_METHOD_AES256 �� ��ȿ)
	int						compressionLevel;			// ���� ���� ( Z_NO_COMPRESSION, Z_BEST_SPEED ~ Z_BEST_COMPRESSION )
	INT64					splitSize;					// ���� ���� ũ�� (bytes,  0 �̸� ���� ���� ����)
	BOOL32					forceZip64;					// ������ zip64 ���� ����
	BOOL32					useDosTime2PasswordCheck;	// ��ȣ üũ ����Ÿ�� crc ��� dostime �� ����Ѵ�. (���� ���� �ӵ� ���). �� ���Ҿ���� �� �ɼ��� ���õ�
	LPCWSTR					sfxPathName;				// sfx�� ������ sfx ���ϰ�θ�. NULL �̸� ������� ����.
	BOOL32					forceUtf8FileName;			// ���ϸ��� ��� utf8 �� ����
	BOOL32					forceUtf8Comment;			// �������� ������ utf8 �� ���� (�ٸ� ���α׷��� ȣ�ϵ��� ����)
	BOOL32					utf8FileNameIfNeeded;		// ���ϸ� �����ڵ尡 ���ԵǾ� ���� ��� utf8 �� ����
	BOOL32					bypassWhenUncompressible;	// ������ ������ �ȵɰ�� �׳� bypass
	int						lzmaEncodeThreadCount;		// LZMA ����� ������ ī��Ʈ. 1~2
	BOOL32					enableMultithreadDeflate;	// Deflate ����� ��Ƽ������ ���
	int						deflateEncodeThreadCount;	// Deflate ����� ����� ������ ����. 0 �̸� �⺻�� ���
	BOOL32					deleteArchiveWhenFailed;	// ������ ���� �߻��� ������ ���� �����ϱ�

	BOOL32					_7zCompressHeader;			// 7zip ����� ����� ������ ���ΰ�?
	BOOL32					_7zEncryptHeader;			// 7zip ����� ����� ��ȣȭ �� ���ΰ�? (��ȣ ������)
	int						lzma2NumBlockThreads;		// lzma2 ����� ������ ����, -1 �̸� �ý��� ������ŭ
	int						threadPriority;				// ��Ƽ�ھ �̿��ؼ� ����� ������ �켱 ����
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �������� ����� �������̽�
//
struct IArkCompressor
{
	ARKMETHOD(void)			Release() PURE;												// ��ü ����

	ARKMETHOD(void)			Init() PURE;												// �ʱ�ȭ (���ο� �������� ���� ����)
	ARKMETHOD(void)			SetEvent(IArkEvent* pEvent) PURE;							// �ݵ�� Init() ȣ���� �Ź� ȣ���ؾ� �Ѵ�.
	ARKMETHOD(BOOL32)		SetOption(SArkCompressorOpt& opt, const ARKBYTE* password, int pwLen) PURE;// CreateArchive() ȣ�������� ȣ���ϸ� ���� ȣ���ص� �������, �ѹ� ȣ���ϸ� ��

	ARKMETHOD(BOOL32)		SetArchiveFile(IArk* pArchive) PURE;						// ���� ���� ���� 
	ARKMETHOD(BOOL32)		AddFileItem(LPCWSTR	szSrcPathName, LPCWSTR szTargetPathName, BOOL32 overwrite, LPCWSTR szFileComment=NULL, INT64 fileSize=-1) PURE;

	ARKMETHOD(BOOL32)		RenameItem(int index, LPCWSTR szPathName) PURE;				// SetArchiveFile() �� ������ ������ �̸��� �ٲ۴�.
	ARKMETHOD(BOOL32)		DeleteItem(int index) PURE;									// SetArchiveFile() �� ������ ������ �����Ѵ�.

	ARKMETHOD(int)			FindFileItemIndex2Add(LPCWSTR szTargetPathName) PURE;						// ���� ��Ͽ� �����ϴ��� Ȯ���Ѵ�.
	ARKMETHOD(BOOL32)		GetFileItemInfo(int index, INT64& fileSize, ARK_TIME_T& fileTime) PURE;		// ��Ͽ� �ִ� ������ ���� ��������
	ARKMETHOD(INT64)		GetTotalFileSize2Archive() PURE;

	ARKMETHOD(BOOL32)		CreateArchive(LPCWSTR szPathName, LPCWSTR szArchiveComment=NULL) PURE;

	ARKMETHOD(ARKERR)		GetLastError() const PURE;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IArk, IArkCompressor ��ü�� �����մϴ�. SDKVersion �Ķ���ʹ� ARK_LIBRARY_VERSION �� �ѱ�� �˴ϴ�.
//

#ifdef _WIN32
extern "C" __declspec(dllexport) IArk*				CreateArk(UINT32 SDKVersion);
extern "C" __declspec(dllexport) IArkCompressor*	CreateArkCompressor(UINT32 SDKVersion);
#endif
extern "C" IArk*									CreateArkLib(UINT32 SDKVersion);


#endif // _ARK_H_
