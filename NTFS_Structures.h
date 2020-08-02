#include <windows.h>
#include <stdlib.h>

#define PART_TABLE 0
#define BOOT_RECORD 1
#define EXTENDED_PART 2

#define PART_UNKNOWN 0x00		//Unknown.  
#define PART_DOS2_FAT 0x01		//12-bit FAT.  
#define PART_DOS3_FAT 0x04		//16-bit FAT. Partition smaller than 32MB.  
#define PART_EXTENDED 0x05		//Extended MS-DOS Partition.  
#define PART_DOS4_FAT 0x06		//16-bit FAT. Partition larger than or equal to 32MB.  
#define PART_DOS32 0x0B			//32-bit FAT. Partition up to 2047GB.  
#define PART_DOS32X 0x0C		//Same as PART_DOS32(0Bh), but uses Logical Block Address Int 13h extensions.  
#define PART_DOSX13 0x0E		//Same as PART_DOS4_FAT(06h), but uses Logical Block Address Int 13h extensions.  
#define PART_DOSX13X 0x0F		//Same as PART_EXTENDED(05h), but uses Logical Block Address Int 13h extensions.  

typedef struct
{
	BYTE	chBootInd;
	BYTE	chHead;
	BYTE	chSector;
	BYTE	chCylinder;
	BYTE	chType;
	BYTE	chLastHead;
	BYTE	chLastSector;
	BYTE	chLastCylinder;
	DWORD	dwRelativeSector;
	DWORD	dwNumberSectors;

}PARTITION;

typedef struct
{
	WORD	wCylinder;
	WORD	wHead;
	WORD	wSector;
	DWORD	dwNumSectors;
	WORD	wType;
	DWORD	dwRelativeSector;
	DWORD	dwNTRelativeSector;
	DWORD	dwBytesPerSector;

}DRIVEPACKET;

typedef struct
{
	DWORD	dwStartSector;
	DWORD	dwBytesPerSector;
	HANDLE	hDrive;
	DWORD	dwBytesPerCluster;
	DWORD	dwMFTRecordSize;
}OUR_WORK_INFO;