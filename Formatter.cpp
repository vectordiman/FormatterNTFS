#include "stdafx.h"
#include "Formatter.h"

#define DRIVE_MAX 4		

DRIVEPACKET OurDrive;
BYTE *m_pMFTRecord;
BYTE *m_puchFileData;
DWORD m_dwCurPos;
ATTR_STANDARD m_attrStandard;
ATTR_FILENAME m_attrFilename;
//BYTE *uchTmpData;
DWORD m_dwFileDataSz;

using namespace std;

void Formatter::getDrives() {
	string* AS = nullptr;  // массив сменных дисков
	string* AS2;           // дополнительный массив строк
	int count = 0;              // количество элементов в массиве

	wchar_t disks[256];
	wchar_t* disk;
	DWORD sizebuf = 256;

	GetLogicalDriveStringsW(sizebuf, disks);
	disk = disks;
	while (*disk)
	{
		// Чтение съемных дисков
		int d = GetDriveTypeW(disk);
		if (d == DRIVE_REMOVABLE)
		{
			count++;
			AS2 = new string[count];

			for (int i = 0; i < count - 1; i++) AS2[i] = AS[i];

			wstring ws(disk);
			string str(ws.begin(), ws.end());
			AS2[count - 1] = str;

			if (AS != nullptr) delete[] AS;
			AS = AS2;

		}

		disk = disk + wcslen(disk) + 1;

	}

	// Вывод флешек:
	for (int i = 0; i < count; i++)
		cout << "Номер диска: " << i << " | " << AS[i] << endl;

	chooseDrive(count, AS);
}
void Formatter::chooseDrive(int count,string *AS) {

	int id = 0;

	if (id != -1 && id < count)
	{
		size_t pos = AS[id].find('\\');
		AS[id].replace(pos, 1, "\0");

		string str = "\\\\.\\";
		str += AS[id];
		setDriveLabel(str);
	}
	else
	{
		exit(1);
	}
}

void Formatter::ScanPartition()	//ищем все разделы на диске
{
	PARTITION *Partition;
	DRIVEPACKET stDrive[DRIVE_MAX];
	WORD wDrive =0;
	DWORD dwMainPrevRelSector =0;
	DWORD dwPrevRelSector =0;
	BYTE szSector[512];
	DWORD dwBytes;
	int i, nRet;
	
	wstring stemp = s2ws(getDriveLabel());

	
	LPCWSTR currentDisk = stemp.c_str();
	HANDLE hDrive = CreateFile(currentDisk, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hDrive == INVALID_HANDLE_VALUE)
		return;
	ReadFile(hDrive,szSector,512,&dwBytes,0);
	Partition = (PARTITION*)(szSector+0x1BE);
	for (i = 0; i < 4; i++)	{
		stDrive[wDrive].wCylinder = Partition->chCylinder;
		stDrive[wDrive].wHead = Partition->chHead;
		stDrive[wDrive].wSector = Partition->chSector;
		stDrive[wDrive].dwNumSectors = Partition->dwNumberSectors;
		stDrive[wDrive].wType = ((Partition->chType == PART_EXTENDED) || (Partition->chType == PART_DOSX13X)) ? EXTENDED_PART:BOOT_RECORD;
		if((Partition->chType == PART_EXTENDED) || (Partition->chType == PART_DOSX13X))		{
			dwMainPrevRelSector			= Partition->dwRelativeSector;
			stDrive[wDrive].dwNTRelativeSector	= dwMainPrevRelSector;
		}
		else stDrive[wDrive].dwNTRelativeSector = dwMainPrevRelSector + Partition->dwRelativeSector;
		if(stDrive[wDrive].wType == EXTENDED_PART) break;
		if(Partition->chType == 0) break;
		Partition++;
		cout<<"Was found partition: "<<wDrive<<"\n";
		wDrive++;
	}
	if(i==4) return;
	for(int LogiHard=0; LogiHard<50; LogiHard++) // scanning extended partitions
	{
		if(stDrive[wDrive].wType == EXTENDED_PART) {
			LARGE_INTEGER n64Pos;
			n64Pos.QuadPart = ((LONGLONG) stDrive[wDrive].dwNTRelativeSector) * 512;
			nRet = SetFilePointer(hDrive, n64Pos.LowPart,&n64Pos.HighPart, FILE_BEGIN);
			if(nRet == 0xffffffff) return;
			dwBytes = 0;
			nRet = ReadFile(hDrive, szSector, 512, (DWORD *) &dwBytes, NULL);
			if(!nRet) return;
			if(dwBytes != 512) return;
			Partition = (PARTITION *) (szSector+0x1BE);
			for(i=0; i<4; i++) {
				stDrive[wDrive].wCylinder = Partition->chCylinder;
				stDrive[wDrive].wHead = Partition->chHead;
				stDrive[wDrive].dwNumSectors = Partition->dwNumberSectors;
				stDrive[wDrive].wSector = Partition->chSector;
				stDrive[wDrive].dwRelativeSector = 0;
				stDrive[wDrive].wType = ((Partition->chType == PART_EXTENDED) || (Partition->chType == PART_DOSX13X)) ? EXTENDED_PART:BOOT_RECORD;
				if((Partition->chType == PART_EXTENDED) || (Partition->chType == PART_DOSX13X))	{
					dwPrevRelSector = Partition->dwRelativeSector;
					stDrive[wDrive].dwNTRelativeSector = dwPrevRelSector + dwMainPrevRelSector;
				}
				else stDrive[wDrive].dwNTRelativeSector = dwMainPrevRelSector + dwPrevRelSector + Partition->dwRelativeSector;
				if(stDrive[wDrive].wType == EXTENDED_PART) break;
				if(Partition->chType == 0) break;
				Partition++;
				cout<<"Was found partition: "<<wDrive<<"\n";
				wDrive++;
			}
			if(i==4) break;
		}
	}
	cout<<"Please, choose the drive: ";
	int DriveNum = 0;
	memcpy(&OurDrive, &stDrive[DriveNum], sizeof(DRIVEPACKET));
	CloseHandle(hDrive);
	return;
}
void Formatter::fillInfoStructure(NTFS_PART_BOOT_SEC *ntfsBS, OUR_WORK_INFO *info) {
	
	
	LARGE_INTEGER StartPos;
	DWORD dwBytes;
	wstring stemp = s2ws(getDriveLabel());


	LPCWSTR currentDisk = stemp.c_str();
	//открываем HDD!!!
	info->hDrive = CreateFile(currentDisk, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (info->hDrive == INVALID_HANDLE_VALUE)
		die("Failed to open");
	//заполняем нашу структуру
	info->dwStartSector = OurDrive.dwNTRelativeSector;
	info->dwBytesPerSector = 512;
	//вычисляем смещение относительно начала диска
	StartPos.QuadPart = (LONGLONG)info->dwBytesPerSector * info->dwStartSector;
	//DWORD dwCur = SetFilePointer(info.hDrive, StartPos.LowPart, &StartPos.HighPart, FILE_BEGIN);	//позиционируем на начало MFT (содержит младшую часть нового адреса)
	SetFilePointer(info->hDrive, 0, NULL, FILE_BEGIN);
	//читаем базовую информацию в начале диска и проверяем на правильность
	if (!ReadFile(info->hDrive, ntfsBS, sizeof(NTFS_PART_BOOT_SEC), &dwBytes, NULL))
		return die("Failed to read");
	//6212976
//дозаполняем структуру
	info->dwBytesPerCluster = ntfsBS->bpb.uchSecPerClust * ntfsBS->bpb.wBytesPerSec;
	//info.dwMFTRecordSize = 0x01<<((-1)*((char)ntfsBS.bpb.nClustPerMFTRecord));
	info->dwMFTRecordSize = 1024;
	CloseHandle(info->hDrive);
}
// читаем данные с диска
int Formatter::ReadRaw(LONGLONG n64LCN, BYTE *chData, DWORD &dwLen, OUR_WORK_INFO* info)
{
	int nRet;
	LARGE_INTEGER n64Pos;	//физический адрес

	n64Pos.QuadPart = (n64LCN)*(info->dwBytesPerCluster);	//переводим кластеры в байты
	//n64Pos.QuadPart += (LONGLONG)info->dwStartSector*info->dwBytesPerSector;	//с учетом смещения относителньо начало винчестера

	//устанавливаем позицию на диске
	nRet = SetFilePointer(info->hDrive,n64Pos.LowPart,&n64Pos.HighPart,FILE_BEGIN);
	if(nRet == 0xFFFFFFFF) return GetLastError();

	BYTE *pTmp			= chData;
	DWORD dwBytesRead	=0;
	DWORD dwBytes		=0;
	DWORD dwTotRead		=0;

	//читаем данные в размере кластера
	while(dwTotRead <dwLen)
	{
		//размер чтения
		dwBytesRead = info->dwBytesPerCluster;
		//читаем
		nRet = ReadFile(info->hDrive,pTmp,dwBytesRead,&dwBytes,NULL);
		if(!nRet) return GetLastError();
		dwTotRead += dwBytes;
		pTmp += dwBytes;
	}
	//число прочитанных байт
	dwLen = dwTotRead;

	return ERROR_SUCCESS;
}

int Formatter::ExtractData(NTFS_ATTRIBUTE ntfsAttr, BYTE *&puchData, DWORD &dwDataLen, DWORD m_dwCurPos, OUR_WORK_INFO *info, BYTE *m_pMFTRecord)
{
	DWORD dwCurPos = m_dwCurPos;
	if(!ntfsAttr.uchNonResFlag)	//резидентный блок? Если да, то просто копируем данные
	{
		puchData = new BYTE[ntfsAttr.Attr.Resident.dwLength];
		dwDataLen = ntfsAttr.Attr.Resident.dwLength;
		memcpy(puchData,&m_pMFTRecord[m_dwCurPos+ntfsAttr.Attr.Resident.wAttrOffset],dwDataLen);
	}
	else	//нерезидентный блок => будем собирать информацию по всему диску
	{

		//if(!ntfsAttr.Attr.NonResident.n64AllocSize) // i don't know Y, but fails when its zero
		//	ntfsAttr.Attr.NonResident.n64AllocSize = (ntfsAttr.Attr.NonResident.n64EndVCN - ntfsAttr.Attr.NonResident.n64StartVCN) + 1;

		dwDataLen = ntfsAttr.Attr.NonResident.n64RealSize;				//фактический размер содержимого атрибута
		puchData = new BYTE[ntfsAttr.Attr.NonResident.n64AllocSize];	//выделенный размер содержимого атрибута

		BYTE chLenOffSz;			//
		BYTE chLenSz;				//
		BYTE chOffsetSz;			//
		LONGLONG n64Len, n64Offset; //реальный размер и смещение
		LONGLONG n64LCN =0;			//содержит реальный адрес файла
		BYTE *pTmpBuff = puchData;
		int nRet;

		dwCurPos += ntfsAttr.Attr.NonResident.wDatarunOffset;;			//берем смещение к данным (если = 64, то выходим ровно за блок NTFS_ATTRIBUTE)

		for(;;)
		{
			//берем первый байт данных после NTFS_ATTRIBUTE
			chLenOffSz = 0;
			memcpy(&chLenOffSz,&m_pMFTRecord[dwCurPos],sizeof(BYTE));
			
			//смещаемся на сл. байт
			dwCurPos += sizeof(BYTE);
			//пусто?
			if(!chLenOffSz) break;	//нулевой байт сигнализирует об конце списка
			/* разбиваем полученное 16-ричное число на 2. Например:			 *	
			 *			Пусть прочитали число: 21h
			 * Тогда мы его разбиваем соответственно на 2 и 1
			 */
			chLenSz		= chLenOffSz & 0x0F;		//описываем размер поля длины отрезка (мл. байт)
			chOffsetSz	= (chLenOffSz & 0xF0) >> 4;	//размер поля начального кластера (ст. байт) - понадобится далее

			//вычисляем длину отрезка
			n64Len = 0;
			memcpy(&n64Len,&m_pMFTRecord[dwCurPos],chLenSz);
			dwCurPos += chLenSz;

			//считываем номер начального кластера отрезка
			n64Offset = 0;
			memcpy(&n64Offset,&m_pMFTRecord[dwCurPos],chOffsetSz);
			dwCurPos += chOffsetSz;

			/*
			 * На данном этапе получили следующее:
			 *		chLenSz		-	размер поля длины отрезка
			 *		chOffsetSz	-	размер поля начального кластера
			 *		n64Len		-	длина отрезка в кластерах
			 *		n64Offset	-	считываем номер начального кластера
			 *	Пример:
			 *		поле, расположенное после NTFS_ATTRIBUTE:
			 *				21 18 34 56 00
			 *		chLenSz    = 1h
			 *		chOffsetSz = 2h
			 *		n64Len     = 18h
			 *		n64Offset  = 34h 56h
			 *  Т.о. делаем вывод: начальный кластер - 5634h, а конечный кластер - 5634h+18h == 564Ch
			 */

			////// if the last bit of n64Offset is 1 then its -ve so u got to make it -ve /////
			//if((((char*)&n64Offset)[chOffsetSz-1])&0x80)
			//	for(int i=sizeof(LONGLONG)-1;i>(chOffsetSz-1);i--)
			//		((char*)&n64Offset)[i] = 0xff;
			
			n64LCN += n64Offset;				//изм. указатель на файл
			n64Len *= info->dwBytesPerCluster;	//переводим длину из кластеров в байты
			//читаем данные и повторяем цикл
			nRet = ReadRaw(n64LCN,pTmpBuff,(DWORD&)n64Len, info);
			if(nRet) return nRet;
			pTmpBuff += n64Len;					//смещаемся на сл. фрагмент для анализа
		}
	}
	return ERROR_SUCCESS;
}

int Formatter::ExtractFile(BYTE *puchMFTBuffer, DWORD dwLen, bool bExcludeData, OUR_WORK_INFO *info)
{
	//проверяем на выходы за пределы массива
	if (info->dwMFTRecordSize > dwLen) {
		cout << "3";
		return ERROR_INVALID_PARAMETER;
	}
	if (!puchMFTBuffer) {
		cout << "4";
		return ERROR_INVALID_PARAMETER;
	}
	NTFS_MFT_FILE	ntfsMFT;		//структура MFT-файла
	NTFS_ATTRIBUTE	ntfsAttr;		//атрибут  DATA
	BYTE *puchTmp = 0;
	BYTE *uchTmpData =0;			//помещаем сюда информацию, кот. берется из ExtractData
	DWORD dwTmpDataLen;				//длина буфера
	int nRet;
	m_pMFTRecord = puchMFTBuffer;	//берем указатель на прочитанный блок
	m_dwCurPos = 0;					//текущая позиция в прочитанном буфере
	int Finish = 0;
	if(m_puchFileData) delete m_puchFileData;

	m_puchFileData = 0;
	m_dwFileDataSz = 0;

	//заполняем структуру ntfsMFT
	memcpy(&ntfsMFT,&m_pMFTRecord[m_dwCurPos],sizeof(NTFS_MFT_FILE));
	//проверяем: правильно ли вышли?
	if (memcmp(ntfsMFT.szSignature, "FILE", 4))
	{
		cout << "5";
		return ERROR_INVALID_PARAMETER; // not the right signature
	}
	//берем смещение до аттрибута
	m_dwCurPos = ntfsMFT.wAttribOffset;
	//максимальная длина обрабатываемого буфера
	DWORD Max_Pos = m_dwCurPos + dwLen;
	//организуем цикл просмтора данного блока
	do
	{	//извлекаем очередной заголовок аттрибута
		memcpy(&ntfsAttr,&m_pMFTRecord[m_dwCurPos],sizeof(NTFS_ATTRIBUTE));
		//анализируем его
		switch(ntfsAttr.dwType)
		{
			case 0x30: //FILE_NAME
				nRet = ExtractData(ntfsAttr,uchTmpData,dwTmpDataLen, m_dwCurPos, info, puchMFTBuffer);
				if (nRet) { 
					cout << "1";
					return nRet ;
				}
				memcpy(&m_attrFilename,uchTmpData,dwTmpDataLen);
				delete uchTmpData;
				uchTmpData = 0;
				dwTmpDataLen = 0;
				break;
			
		case 0x80: //DATA
			Finish = 1;
			if (!bExcludeData)
			{
				nRet = ExtractData(ntfsAttr, uchTmpData, dwTmpDataLen, m_dwCurPos, info, puchMFTBuffer);
				if (nRet) {
					cout << "2";
					return nRet;
			}
				m_dwFileDataSz = dwTmpDataLen;
				if (m_puchFileData != 0) delete[] m_puchFileData;
				m_puchFileData = new BYTE[dwTmpDataLen];
				memcpy(m_puchFileData,uchTmpData,dwTmpDataLen);
				
				delete uchTmpData;
				uchTmpData = 0;
				dwTmpDataLen = 0;
			}
			break;
		case 0xFFFFFFFF: // конец 
			if(uchTmpData) delete uchTmpData;
			uchTmpData = 0;
			dwTmpDataLen = 0;
			return ERROR_SUCCESS;
		default:
			break;
		};
		m_dwCurPos += ntfsAttr.dwFullLength; //смещаемся на следующий атрибут
	}
	while(m_dwCurPos < Max_Pos && Finish == 0);
	if(uchTmpData) delete uchTmpData;
	uchTmpData = 0;
	dwTmpDataLen = 0;
	return ERROR_SUCCESS;
}
void Formatter::die(const char * error)
{
	// Retrieve the system error message for the last-error code

	DWORD dw = GetLastError();

	if (dw != NO_ERROR)
	{
		LPSTR lpMsgBuf;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&lpMsgBuf,
			0, NULL);

		// Display the error message and exit the process

		fprintf(stderr, "%s\nGetLastError()=%lu: %s\n", error, dw, lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	else
	{
		fprintf(stderr, "%s\n", error);
	}

	system("pause");
	exit(dw);

}
void Formatter::printfNtfsBS(NTFS_PART_BOOT_SEC r) {
	
	cout <<endl<< "FILE SYSTEM INFORMATION" << endl << endl;
	cout << "File System: ";
	for(int i =0;i<4;i++)
	cout << r.chOemID[i];
	cout << endl << "Bytes per Sector: " << r.bpb.wBytesPerSec << endl;
	cout << "Sector per Cluster: " << (int)(r.bpb.uchSecPerClust) << endl;
	cout << "Reserved sectors: " << r.bpb.wReservedSec << endl;
	cout << "Media Descriptor: " << (int)(r.bpb.uchMediaDescriptor) << endl;
	cout << "Sector per Truck: " << r.bpb.wSecPerTrack << endl;
	cout << "Number of head: " << r.bpb.wNumberOfHeads << endl;
	cout << "Hidden sectors: " << r.bpb.dwHiddenSec << endl;
	cout << "Total sectors: " << r.bpb.n64TotalSec << endl;
	cout << "MFT Logical Cluster num: " << r.bpb.n64MFTLogicalClustNum << endl;
	cout << "MFT Mirror logical cluster num: " << r.bpb.n64MFTMirrLogicalClustNum << endl;
	cout << "Cluster per MFT Record: " << r.bpb.nClustPerMFTRecord << endl;
	cout << "Cluster per Index Record: " << r.bpb.nClustPerIndexRecord << endl;
	cout << "Volume serial number: " << r.bpb.n64VolumeSerialNum << endl;;

	

}
void Formatter::LoadMFT(LONGLONG nStartCluster, OUR_WORK_INFO *info, char* path)
{
    string deviceEnd = "\\\\.\\";
    deviceEnd += path;
    deviceEnd = deviceEnd.substr(0, 6);

	LARGE_INTEGER m64;
	BYTE pZeroSect[1024] = { 0 };
	BYTE buff[1024];
	BYTE FirstBoot[5120];
	BYTE indxalloc[4096];
	BYTE bufff[1024];
	BYTE boot[512] = {0};
	BYTE bitmap[512];
	DWORD dwBytes;
	BYTE *uchTmpData = 0;
	BYTE *puchTmp = 0;
	BYTE BigZero[655360] = { 0 };
	BOOL ret;
	info->hDrive = CreateFileA(deviceEnd.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
	if (info->hDrive == INVALID_HANDLE_VALUE)
		die("Failed to open device - close any files before formatting and make sure you have Admin rights when using fat32format\n Are you SURE you're formatting the RIGHT DRIVE!!!");

	ret = DeviceIoControl(
		(HANDLE)info->hDrive,              // handle to device
		FSCTL_ALLOW_EXTENDED_DASD_IO,  // dwIoControlCode
		NULL,                          // lpInBuffer
		0,                             // nInBufferSize
		NULL,                          // lpOutBuffer
		0,                             // nOutBufferSize
		&dwBytes,				         // number of bytes returned
		NULL                           // OVERLAPPED structure
	);

	if (!ret)
		puts("Failed to allow extended DASD on device");
	else
		puts("FSCTL_ALLOW_EXTENDED_DASD_IO OK");
			
	m64.QuadPart = (LONGLONG)info->dwBytesPerCluster * nStartCluster; //m64.QuadPart += (LONGLONG)info->dwBytesPerCluster * nStartCluster;


	//////const char* MFT = "D:\\store\\MFT.txt";       //Путь к файлу
	//////const char* MFTMirr = "D:\\store\\MFTMirr.txt";       //Путь к файлу
	//////const char* LogFile = "D:\\store\\LogFile.txt";       //Путь к файлу
	//////const char* Volume = "D:\\store\\Volume.txt";       //Путь к файлу
	//////const char* AttrDef = "D:\\store\\AttrDef.txt";       //Путь к файлу
	//////const char* RootDirectory = "D:\\store\\RootDirectory.txt";       //Путь к файлу
	//////const char* Bitmap = "D:\\store\\Bitmap.txt";       //Путь к файлу
	//////const char* Boot = "D:\\store\\Boot.txt";       //Путь к файлу
	//////const char* BadClus = "D:\\store\\BadClus.txt";       //Путь к файлу
	//////const char* Secure = "D:\\store\\Secure.txt";       //Путь к файлу
	//////const char* UpCase = "D:\\store\\UpCase.txt";       //Путь к файлу
	//////const char*  NTFSBoot = "D:\\store\\NTFSBoot.txt"; 
	//////const char* IndexAllocation = "D:\\store\\IndexAllocation.txt";
	



    const char* storeMFT[13] = { "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\MFT.txt" , "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\MFTMirr.txt", "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\LogFile.txt", "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\Volume.txt",
        "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\AttrDef.txt", "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\RootDirectory.txt", "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\Bitmap.txt", "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\Boot.txt",
        "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\BadClus.txt", "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\Secure.txt","D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\UpCase.txt","D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\NTFSBoot.txt",
        "D:\\BSUIR\\4cem\\Kursach\\FormatProcess\\storeMFT\\IndexAllocation.txt" };



	SetFilePointer(info->hDrive, 0, NULL, FILE_BEGIN);

	ifstream in0(storeMFT[11], ios::binary);
	in0.read((char*)FirstBoot, 5120);
	in0.close();
	ret = WriteFile(info->hDrive, FirstBoot, 5120, &dwBytes, NULL);
	if (!ret)
		die("Failed to write");


	SetFilePointer(info->hDrive, m64.LowPart, &m64.HighPart, FILE_BEGIN);
	for (int i = 0; i < 11; i++)
	{
		ifstream in(storeMFT[i], ios::binary);
		in.read((char*)buff, 1024);
		in.close();
		ret = WriteFile(info->hDrive, buff, 1024, &dwBytes, NULL);
		if (!ret)
			die("Failed to write");
		
	}

	m64.QuadPart = (LONGLONG)info->dwBytesPerCluster * 36;

	SetFilePointer(info->hDrive, m64.LowPart, &m64.HighPart, FILE_BEGIN);
	ifstream in11(storeMFT[12], ios::binary);
	in11.read((char*)indxalloc, 4096);
	in11.close();
	
	ret = WriteFile(info->hDrive, indxalloc, 4096, &dwBytes, NULL);
	if (!ret)
		die("Failed to write");
	
/*
 * //////m64.QuadPart = (LONGLONG)info->dwBytesPerCluster * 36;
	//////ofstream out0(IndexAllocation, ios::binary);            //Ставим режим "бинарный файл"
	//////SetFilePointer(info->hDrive, m64.LowPart, &m64.HighPart, FILE_BEGIN);
	//////ReadFile(info->hDrive, indxalloc, 4096, &dwBytes, NULL);
	//////out0.write((char*)indxalloc, 4096);
	//////out0.close();

	//////ofstream out100(NTFSBoot, ios::binary);            //Ставим режим "бинарный файл"
	//////SetFilePointer(info->hDrive, 0, NULL, FILE_BEGIN);
	//////ReadFile(info->hDrive, FirstBoot, 5120, &dwBytes, NULL);
	//////out100.write((char*)FirstBoot, 5120);
	//////out100.close();

	//////m64.QuadPart = (LONGLONG)info->dwBytesPerCluster * nStartCluster;
	//////ofstream out(MFT, ios::binary);            //Ставим режим "бинарный файл"
	//////SetFilePointer(info->hDrive, m64.LowPart, &m64.HighPart, FILE_BEGIN);
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out.write((char*)buff, 1024);
	//////out.close();

	//////ofstream out1(MFTMirr, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out1.write((char*)buff, 1024);
	//////out1.close();

	//////ofstream out2(LogFile, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out2.write((char*)buff, 1024);
	//////out2.close();
	//////
	//////ofstream out3(Volume, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out3.write((char*)buff, 1024);
	//////out3.close();

	//////ofstream out4(AttrDef, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out4.write((char*)buff, 1024);
	//////out4.close();

	//////ofstream out5(RootDirectory, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out5.write((char*)buff, 1024);
	//////out5.close();

	//////ofstream out6(Bitmap, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out6.write((char*)buff, 1024);
	//////out6.close();

	//////ofstream out7(Boot, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out7.write((char*)buff, 1024);
	//////out7.close();

	//////ofstream out8(BadClus, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out8.write((char*)buff, 1024);
	//////out8.close();

	//////ofstream out9(Secure, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out9.write((char*)buff, 1024);
	//////out9.close();

	//////ofstream out10(UpCase, ios::binary);            //Ставим режим "бинарный файл"
	//////ReadFile(info->hDrive, buff, info->dwMFTRecordSize, &dwBytes, NULL);
	//////out10.write((char*)buff, 1024);
	//////out10.close();
    ///
*/
    /*
     * SetFilePointer(info->hDrive, 0, NULL, FILE_BEGIN);

	int j = 0;
	while (j < 64) {
		ret = WriteFile(info->hDrive, BigZero, 655360, &dwBytes, NULL);
		if (!ret)
			die("Failed to write");
		j++;
	}
*/

    if (ExtractFile(buff, dwBytes, false, info) != ERROR_SUCCESS)
    {
         QMessageBox::critical(nullptr, "Warning", "Error");
		return;
	}
	      	
}

void Formatter::seek_to_sect(HANDLE hDevice, DWORD Sector, DWORD BytesPerSect)
{
	LONGLONG Offset = Sector * BytesPerSect;
	LONG HiOffset = (LONG)(Offset >> 32);
	SetFilePointer(hDevice, (LONG)Offset, &HiOffset, FILE_BEGIN);
}
wstring Formatter::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
