#include <windows.h>
#include <stdlib.h>
#pragma pack(push, curAlignment)
#pragma pack(1)
////////////////////////////  boot sector info ///////////////////////////////////////
struct NTFS_PART_BOOT_SEC
{
	char		chJumpInstruction[3];
	char		chOemID[4] ;
	char		chDummy[4];

	struct NTFS_BPB
	{
		WORD		wBytesPerSec;
		BYTE		uchSecPerClust;
		WORD		wReservedSec;
		BYTE		uchReserved[3];
		WORD		wUnused1;
		BYTE		uchMediaDescriptor;
		WORD		wUnused2;
		WORD		wSecPerTrack;
		WORD		wNumberOfHeads;
		DWORD		dwHiddenSec;
		DWORD		dwUnused3;
		DWORD		dwUnused4;
		LONGLONG	n64TotalSec;
		LONGLONG	n64MFTLogicalClustNum;
		LONGLONG	n64MFTMirrLogicalClustNum;
		int			nClustPerMFTRecord;
		int			nClustPerIndexRecord;
		LONGLONG	n64VolumeSerialNum;
		DWORD		dwChecksum;
	} bpb;

	char		chBootstrapCode[426] ;
	WORD		wSecMark ;
};

/////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop, curAlignment)
