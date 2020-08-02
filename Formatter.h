#include "stdafx.h"
#include "MFT.h"
#include "NTFS.h"
#include "NTFS_Structures.h"
#include <windows.h>
#include "iostream"
#include <fstream>
#include <string>
#include <string.h>
#include <winioctl.h>
#include <locale.h>

#include <QMessageBox>
using namespace std;


class Formatter
{
private:
	const string programName = "FormatterNTFS - formatting utility NTFS";
	string DriveLabel; 

	
public:
	string getName() { return programName; }
	string getDriveLabel() { return DriveLabel; }
	void setDriveLabel(string label) { DriveLabel = label; }
	void ScanPartition();
	wstring s2ws(const std::string& s);
	int ReadRaw(LONGLONG n64LCN, BYTE *chData, DWORD &dwLen, OUR_WORK_INFO* info);
	int ExtractData(NTFS_ATTRIBUTE ntfsAttr, BYTE *&puchData, DWORD &dwDataLen, DWORD m_dwCurPos, OUR_WORK_INFO *info, BYTE *m_pMFTRecord);
	int ExtractFile(BYTE *puchMFTBuffer, DWORD dwLen, bool bExcludeData, OUR_WORK_INFO *info);
	void die(const char * error);
	void LoadMFT(LONGLONG nStartCluster,  OUR_WORK_INFO *info, char* path);
	void seek_to_sect(HANDLE hDevice, DWORD Sector, DWORD BytesPerSect);
	void getDrives();
	void chooseDrive(int count, string *AS);
	void fillInfoStructure( NTFS_PART_BOOT_SEC *ntfsBS, OUR_WORK_INFO *info);
	void printfNtfsBS(NTFS_PART_BOOT_SEC ntfsBS);
};

