#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#pragma pack(push, curAlignment)
#pragma pack(1)

////////////////////////////MFT record header and attribute header //////////////////////
struct NTFS_MFT_FILE
{
	char		szSignature[4];		// Signature "FILE"
	WORD		wFixupOffset;		// offset to fixup pattern
	WORD		wFixupSize;			// Size of fixup-list +1
	LONGLONG	n64LogSeqNumber;	// log file seq number
	WORD		wSequence;			// sequence nr in MFT
	WORD		wHardLinks;			// Hard-link count
	WORD		wAttribOffset;		// Offset to seq of Attributes
	WORD		wFlags;				// 0x01 = NonRes; 0x02 = Dir
	DWORD		dwRecLength;		// Real size of the record
	DWORD		dwAllLength;		// Allocated size of the record
	LONGLONG	n64BaseMftRec;		// ptr to base MFT rec or 0
	WORD		wNextAttrID;		// Minimum Identificator +1
	WORD		wFixupPattern;		// Current fixup pattern
	DWORD		dwMFTRecNumber;		// Number of this MFT Record
								// followed by resident and
								// part of non-res attributes
};

typedef struct
{
	DWORD	dwType;			//идентификатор типа атрибута
	DWORD	dwFullLength;	//длина атрибута
	BYTE	uchNonResFlag;	//флаг нерезидентного блока
	BYTE	uchNameLength;	//длина имени
	WORD	wNameOffset;	//смещение имени
	WORD	wFlags;			//флаги
	WORD	wID;			//идентификатор атрибута

	union ATTR
	{
		struct RESIDENT
		{
			DWORD	dwLength;		//размер содержимого
			WORD	wAttrOffset;	//смещение содержимого
			BYTE	uchIndexedTag;
			BYTE	uchPadding;
		} Resident;
		
		struct NONRESIDENT
		{
			LONGLONG	n64StartVCN;		//начальный виртуальный номер кластера (VCN) списка
			LONGLONG	n64EndVCN;			//конечный номер
			WORD		wDatarunOffset;		//смещение списка серии относительно начала атрибута
			WORD		wCompressionSize;	//размер блока сжатия
			BYTE		uchPadding[4];		//не используется
			LONGLONG	n64AllocSize;		//выделенный размер содержимого атрибута
			LONGLONG	n64RealSize;		//фактический размер содержимого атрибута
			LONGLONG	n64StreamSize;		//инициализированный размер содержимого атрибута
			// data runs...
		}NonResident;
		
	}Attr;
} NTFS_ATTRIBUTE;


//////////////////////////////////////////////////////////////////////////////////////////

///////////////////////// Attributes /////////////////////////////////////////////////////

typedef struct
{
	LONGLONG	n64Create;		// Creation time
	LONGLONG	n64Modify;		// Last Modify time
	LONGLONG	n64Modfil;		// Last modify of record
	LONGLONG	n64Access;		// Last Access time
	DWORD		dwFATAttributes;// As FAT + 0x800 = compressed
	DWORD		dwReserved1;	// unknown

} ATTR_STANDARD;   
  
typedef struct
{
	LONGLONG	dwMftParentDir;            // Seq-nr parent-dir MFT entry
	LONGLONG	n64Create;                  // Creation time
	LONGLONG	n64Modify;                  // Last Modify time
	LONGLONG	n64Modfil;                  // Last modify of record
	LONGLONG	n64Access;                  // Last Access time
	LONGLONG	n64Allocated;               // Allocated disk space
	LONGLONG	n64RealSize;                // Size of the file
	DWORD		dwFlags;					// attribute
	DWORD		dwEAsReparsTag;				// Used by EAs and Reparse
	BYTE		chFileNameLength;
	BYTE		chFileNameType;            // 8.3 / Unicode
	WORD		wFilename[512];             // Name (in Unicode ?)

}ATTR_FILENAME; 
//////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(pop, curAlignment)




