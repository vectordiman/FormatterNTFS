#include "stdafx.h"
#include "Formatter.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <winioctl.h>
#include <locale.h>
using namespace std;

void format(char* path)
{
	setlocale(LC_ALL, "Russian");
	Formatter format;
	NTFS_PART_BOOT_SEC ntfsBS; 
	OUR_WORK_INFO info;
	cout << format.getName() << endl;
	cout << "Список съемных дисков (флешек):" << endl;

	format.getDrives();
	format.ScanPartition();
	format.fillInfoStructure(&ntfsBS,&info);
	format.printfNtfsBS(ntfsBS);
    format.LoadMFT(ntfsBS.bpb.n64MFTLogicalClustNum, &info, path);

	CloseHandle(info.hDrive);
}
