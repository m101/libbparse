/*
    libbparse - Binary file parser library
    Copyright (C) 2010  m_101

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(_FILE_PE_DEFS_H_) && !defined(WIN32)
#define _FILE_PE_DEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined (WIN32)
#include "type_windows.h"
#endif

#define IMAGE_SIZEOF_SHORT_NAME             8
    // magic numbers
#define IMAGE_DOS_SIGNATURE                 0x5A4D
#define IMAGE_OS2_SIGNATURE                 0x454E
#define IMAGE_OS2_SIGNATURE_LE              0x454C
#define IMAGE_VXD_SIGNATURE                 0x454C
#define IMAGE_NT_SIGNATURE                  0x00004550
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
#define IMAGE_ORDINAL_FLAG32                0x80000000L
#define IMAGE_ORDINAL_FLAG64                0x8000000000000000L
#define OPTIONAL_HEADER_MAGIC_PE            0x10b
#define OPTIONAL_HEADER_MAGIC_PE_PLUS       0x20b

    // image characteristics
#define IMAGE_FILE_RELOCS_STRIPPED          0x0001
#define IMAGE_FILE_EXECUTABLE_IMAGE         0x0002
#define IMAGE_FILE_LINE_NUMS_STRIPPED       0x0004
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED      0x0008
#define IMAGE_FILE_AGGRESIVE_WS_TRIM        0x0010
#define IMAGE_FILE_LARGE_ADDRESS_AWARE      0x0020
#define IMAGE_FILE_16BIT_MACHINE            0x0040
#define IMAGE_FILE_BYTES_REVERSED_LO        0x0080
#define IMAGE_FILE_32BIT_MACHINE            0x0100
#define IMAGE_FILE_DEBUG_STRIPPED           0x0200
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP  0x0400
#define IMAGE_FILE_NET_RUN_FROM_SWAP        0x0800
#define IMAGE_FILE_SYSTEM                   0x1000
#define IMAGE_FILE_DLL                      0x2000
#define IMAGE_FILE_UP_SYSTEM_ONLY           0x4000
#define IMAGE_FILE_BYTES_REVERSED_HI        0x8000

    // section characteristics
#define IMAGE_SCN_CNT_CODE                  0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA      0x00000040
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA    0x00000080
#define IMAGE_SCN_LNK_OTHER                 0x00000100
#define IMAGE_SCN_LNK_INFO                  0x00000200
#define IMAGE_SCN_LNK_REMOVE                0x00000800
#define IMAGE_SCN_LNK_COMDAT                0x00001000
#define IMAGE_SCN_MEM_FARDATA               0x00008000
#define IMAGE_SCN_MEM_PURGEABLE             0x00020000
#define IMAGE_SCN_MEM_16BIT                 0x00020000
#define IMAGE_SCN_MEM_LOCKED                0x00040000
#define IMAGE_SCN_MEM_PRELOAD               0x00080000
#define IMAGE_SCN_ALIGN_1BYTES              0x00100000
#define IMAGE_SCN_ALIGN_2BYTES              0x00200000
#define IMAGE_SCN_ALIGN_4BYTES              0x00300000
#define IMAGE_SCN_ALIGN_8BYTES              0x00400000
#define IMAGE_SCN_ALIGN_16BYTES             0x00500000
#define IMAGE_SCN_ALIGN_32BYTES             0x00600000
#define IMAGE_SCN_ALIGN_64BYTES             0x00700000
#define IMAGE_SCN_ALIGN_128BYTES            0x00800000
#define IMAGE_SCN_ALIGN_256BYTES            0x00900000
#define IMAGE_SCN_ALIGN_512BYTES            0x00A00000
#define IMAGE_SCN_ALIGN_1024BYTES           0x00B00000
#define IMAGE_SCN_ALIGN_2048BYTES           0x00C00000
#define IMAGE_SCN_ALIGN_4096BYTES           0x00D00000
#define IMAGE_SCN_ALIGN_8192BYTES           0x00E00000
#define IMAGE_SCN_ALIGN_MASK                0x00F00000
#define IMAGE_SCN_LNK_NRELOC_OVFL           0x01000000
#define IMAGE_SCN_MEM_DISCARDABLE           0x02000000
#define IMAGE_SCN_MEM_NOT_CACHED            0x04000000
#define IMAGE_SCN_MEM_NOT_PAGED             0x08000000
#define IMAGE_SCN_MEM_SHARED                0x10000000
#define IMAGE_SCN_MEM_EXECUTE               0x20000000
#define IMAGE_SCN_MEM_READ                  0x40000000
#define IMAGE_SCN_MEM_WRITE                 0x80000000L

    // debug_types
#define IMAGE_DEBUG_TYPE_UNKNOWN        0
#define IMAGE_DEBUG_TYPE_COFF           1
#define IMAGE_DEBUG_TYPE_CODEVIEW       2
#define IMAGE_DEBUG_TYPE_FPO            3
#define IMAGE_DEBUG_TYPE_MISC           4
#define IMAGE_DEBUG_TYPE_EXCEPTION      5
#define IMAGE_DEBUG_TYPE_FIXUP          6
#define IMAGE_DEBUG_TYPE_OMAP_TO_SRC    7
#define IMAGE_DEBUG_TYPE_OMAP_FROM_SRC  8
#define IMAGE_DEBUG_TYPE_BORLAND        9
#define IMAGE_DEBUG_TYPE_RESERVED10     10

    // subsystem types
#define IMAGE_SUBSYSTEM_UNKNOWN     0
#define IMAGE_SUBSYSTEM_NATIVE      1
#define IMAGE_SUBSYSTEM_WINDOWS_GUI 2
#define IMAGE_SUBSYSTEM_WINDOWS_CUI 3
#define IMAGE_SUBSYSTEM_OS2_CUI     5
#define IMAGE_SUBSYSTEM_POSIX_CUI   7
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI  9
#define IMAGE_SUBSYSTEM_EFI_APPLICATION 10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER      12
#define IMAGE_SUBSYSTEM_EFI_ROM     13
#define IMAGE_SUBSYSTEM_XBOX        14)]

    // machine types
#define IMAGE_FILE_MACHINE_UNKNOWN  0
#define IMAGE_FILE_MACHINE_AM33     0x1d3
#define IMAGE_FILE_MACHINE_AMD64    0x8664
#define IMAGE_FILE_MACHINE_ARM      0x1c0
#define IMAGE_FILE_MACHINE_EBC      0xebc
#define IMAGE_FILE_MACHINE_I386     0x14c
#define IMAGE_FILE_MACHINE_IA64     0x200
#define IMAGE_FILE_MACHINE_MR32     0x9041
#define IMAGE_FILE_MACHINE_MIPS16   0x266
#define IMAGE_FILE_MACHINE_MIPSFPU  0x366
#define IMAGE_FILE_MACHINE_MIPSFPU160x466
#define IMAGE_FILE_MACHINE_POWERPC  0x1f0
#define IMAGE_FILE_MACHINE_POWERPCFP0x1f1
#define IMAGE_FILE_MACHINE_R4000    0x166
#define IMAGE_FILE_MACHINE_SH3      0x1a2
#define IMAGE_FILE_MACHINE_SH3DSP   0x1a3
#define IMAGE_FILE_MACHINE_SH4      0x1a6
#define IMAGE_FILE_MACHINE_SH5      0x1a8
#define IMAGE_FILE_MACHINE_THUMB    0x1c2
#define IMAGE_FILE_MACHINE_WCEMIPSV20x169

    // relocation_types
#define IMAGE_REL_BASED_ABSOLUTE        0
#define IMAGE_REL_BASED_HIGH            1
#define IMAGE_REL_BASED_LOW             2
#define IMAGE_REL_BASED_HIGHLOW         3
#define IMAGE_REL_BASED_HIGHADJ         4
#define IMAGE_REL_BASED_MIPS_JMPADDR    5
#define IMAGE_REL_BASED_SECTION         6
#define IMAGE_REL_BASED_REL             7
#define IMAGE_REL_BASED_MIPS_JMPADDR16  9
#define IMAGE_REL_BASED_IA64_IMM64      9
#define IMAGE_REL_BASED_DIR64           10
#define IMAGE_REL_BASED_HIGH3ADJ        11

    // dll characteristics
#define IMAGE_DLL_CHARACTERISTICS_RESERVED_0x0001 0x0001
#define IMAGE_DLL_CHARACTERISTICS_RESERVED_0x0002 0x0002
#define IMAGE_DLL_CHARACTERISTICS_RESERVED_0x0004 0x0004
#define IMAGE_DLL_CHARACTERISTICS_RESERVED_0x0008 0x0008
#define IMAGE_DLL_CHARACTERISTICS_DYNAMIC_BASE      0x0040
#define IMAGE_DLL_CHARACTERISTICS_FORCE_INTEGRITY   0x0080
#define IMAGE_DLL_CHARACTERISTICS_NX_COMPAT         0x0100
#define IMAGE_DLL_CHARACTERISTICS_NO_ISOLATION      0x0200
#define IMAGE_DLL_CHARACTERISTICS_NO_SEH    0x0400
#define IMAGE_DLL_CHARACTERISTICS_NO_BIND   0x0800
#define IMAGE_DLL_CHARACTERISTICS_RESERVED_0x1000 0x1000
#define IMAGE_DLL_CHARACTERISTICS_WDM_DRIVER    0x2000
#define IMAGE_DLL_CHARACTERISTICS_TERMINAL_SERVER_AWARE 0x8000

    // Resource types
#define RT_CURSOR          1
#define RT_BITMAP          2
#define RT_ICON            3
#define RT_MENU            4
#define RT_DIALOG          5
#define RT_STRING          6
#define RT_FONTDIR         7
#define RT_FONT            8
#define RT_ACCELERATOR     9
#define RT_RCDATA          10
#define RT_MESSAGETABLE    11
#define RT_GROUP_CURSOR    12
#define RT_GROUP_ICON      14
#define RT_VERSION         16
#define RT_DLGINCLUDE      17
#define RT_PLUGPLAY        19
#define RT_VXD             20
#define RT_ANICURSOR       21
#define RT_ANIICON         22
#define RT_HTML            23
#define RT_MANIFEST        24

    // Language definitions
#define LANG_NEUTRAL       0x00
#define LANG_INVARIANT     0x7f
#define LANG_AFRIKAANS     0x36
#define LANG_ALBANIAN      0x1c
#define LANG_ARABIC        0x01
#define LANG_ARMENIAN      0x2b
#define LANG_ASSAMESE      0x4d
#define LANG_AZERI         0x2c
#define LANG_BASQUE        0x2d
#define LANG_BELARUSIAN    0x23
#define LANG_BENGALI       0x45
#define LANG_BULGARIAN     0x02
#define LANG_CATALAN       0x03
#define LANG_CHINESE       0x04
#define LANG_CROATIAN      0x1a
#define LANG_CZECH         0x05
#define LANG_DANISH        0x06
#define LANG_DIVEHI        0x65
#define LANG_DUTCH         0x13
#define LANG_ENGLISH       0x09
#define LANG_ESTONIAN      0x25
#define LANG_FAEROESE      0x38
#define LANG_FARSI         0x29
#define LANG_FINNISH       0x0b
#define LANG_FRENCH        0x0c
#define LANG_GALICIAN      0x56
#define LANG_GEORGIAN      0x37
#define LANG_GERMAN        0x07
#define LANG_GREEK         0x08
#define LANG_GUJARATI      0x47
#define LANG_HEBREW        0x0d
#define LANG_HINDI         0x39
#define LANG_HUNGARIAN     0x0e
#define LANG_ICELANDIC     0x0f
#define LANG_INDONESIAN    0x21
#define LANG_ITALIAN       0x10
#define LANG_JAPANESE      0x11
#define LANG_KANNADA       0x4b
#define LANG_KASHMIRI      0x60
#define LANG_KAZAK         0x3f
#define LANG_KONKANI       0x57
#define LANG_KOREAN        0x12
#define LANG_KYRGYZ        0x40
#define LANG_LATVIAN       0x26
#define LANG_LITHUANIAN    0x27
#define LANG_MACEDONIAN    0x2f
#define LANG_MALAY         0x3e
#define LANG_MALAYALAM     0x4c
#define LANG_MANIPURI      0x58
#define LANG_MARATHI       0x4e
#define LANG_MONGOLIAN     0x50
#define LANG_NEPALI        0x61
#define LANG_NORWEGIAN     0x14
#define LANG_ORIYA         0x48
#define LANG_POLISH        0x15
#define LANG_PORTUGUESE    0x16
#define LANG_PUNJABI       0x46
#define LANG_ROMANIAN      0x18
#define LANG_RUSSIAN       0x19
#define LANG_SANSKRIT      0x4f
#define LANG_SERBIAN       0x1a
#define LANG_SINDHI        0x59
#define LANG_SLOVAK        0x1b
#define LANG_SLOVENIAN     0x24
#define LANG_SPANISH       0x0a
#define LANG_SWAHILI       0x41
#define LANG_SWEDISH       0x1d
#define LANG_SYRIAC        0x5a
#define LANG_TAMIL         0x49
#define LANG_TATAR         0x44
#define LANG_TELUGU        0x4a
#define LANG_THAI          0x1e
#define LANG_TURKISH       0x1f
#define LANG_UKRAINIAN     0x22
#define LANG_URDU          0x20
#define LANG_UZBEK         0x43
#define LANG_VIETNAMESE    0x2a
#define LANG_GAELIC        0x3c
#define LANG_MALTESE       0x3a
#define LANG_MAORI         0x28
#define LANG_RHAETO_ROMANCE0x17
#define LANG_SAAMI         0x3b
#define LANG_SORBIAN       0x2e
#define LANG_SUTU          0x30
#define LANG_TSONGA        0x31
#define LANG_TSWANA        0x32
#define LANG_VENDA         0x33
#define LANG_XHOSA         0x34
#define LANG_ZULU          0x35
#define LANG_ESPERANTO     0x8f
#define LANG_WALON         0x90
#define LANG_CORNISH       0x91
#define LANG_WELSH         0x92
#define LANG_BRETON        0x93

    // Sublanguage definitions
#define SUBLANG_NEUTRAL                        0x00
#define SUBLANG_DEFAULT                        0x01
#define SUBLANG_SYS_DEFAULT                    0x02
#define SUBLANG_ARABIC_SAUDI_ARABIA            0x01
#define SUBLANG_ARABIC_IRAQ                    0x02
#define SUBLANG_ARABIC_EGYPT                   0x03
#define SUBLANG_ARABIC_LIBYA                   0x04
#define SUBLANG_ARABIC_ALGERIA                 0x05
#define SUBLANG_ARABIC_MOROCCO                 0x06
#define SUBLANG_ARABIC_TUNISIA                 0x07
#define SUBLANG_ARABIC_OMAN                    0x08
#define SUBLANG_ARABIC_YEMEN                   0x09
#define SUBLANG_ARABIC_SYRIA                   0x0a
#define SUBLANG_ARABIC_JORDAN                  0x0b
#define SUBLANG_ARABIC_LEBANON                 0x0c
#define SUBLANG_ARABIC_KUWAIT                  0x0d
#define SUBLANG_ARABIC_UAE                     0x0e
#define SUBLANG_ARABIC_BAHRAIN                 0x0f
#define SUBLANG_ARABIC_QATAR                   0x10
#define SUBLANG_AZERI_LATIN                    0x01
#define SUBLANG_AZERI_CYRILLIC                 0x02
#define SUBLANG_CHINESE_TRADITIONAL            0x01
#define SUBLANG_CHINESE_SIMPLIFIED             0x02
#define SUBLANG_CHINESE_HONGKONG               0x03
#define SUBLANG_CHINESE_SINGAPORE              0x04
#define SUBLANG_CHINESE_MACAU                  0x05
#define SUBLANG_DUTCH                          0x01
#define SUBLANG_DUTCH_BELGIAN                  0x02
#define SUBLANG_ENGLISH_US                     0x01
#define SUBLANG_ENGLISH_UK                     0x02
#define SUBLANG_ENGLISH_AUS                    0x03
#define SUBLANG_ENGLISH_CAN                    0x04
#define SUBLANG_ENGLISH_NZ                     0x05
#define SUBLANG_ENGLISH_EIRE                   0x06
#define SUBLANG_ENGLISH_SOUTH_AFRICA           0x07
#define SUBLANG_ENGLISH_JAMAICA                0x08
#define SUBLANG_ENGLISH_CARIBBEAN              0x09
#define SUBLANG_ENGLISH_BELIZE                 0x0a
#define SUBLANG_ENGLISH_TRINIDAD               0x0b
#define SUBLANG_ENGLISH_ZIMBABWE               0x0c
#define SUBLANG_ENGLISH_PHILIPPINES            0x0d
#define SUBLANG_FRENCH                         0x01
#define SUBLANG_FRENCH_BELGIAN                 0x02
#define SUBLANG_FRENCH_CANADIAN                0x03
#define SUBLANG_FRENCH_SWISS                   0x04
#define SUBLANG_FRENCH_LUXEMBOURG              0x05
#define SUBLANG_FRENCH_MONACO                  0x06
#define SUBLANG_GERMAN                         0x01
#define SUBLANG_GERMAN_SWISS                   0x02
#define SUBLANG_GERMAN_AUSTRIAN                0x03
#define SUBLANG_GERMAN_LUXEMBOURG              0x04
#define SUBLANG_GERMAN_LIECHTENSTEIN           0x05
#define SUBLANG_ITALIAN                        0x01
#define SUBLANG_ITALIAN_SWISS                  0x02
#define SUBLANG_KASHMIRI_SASIA                 0x02
#define SUBLANG_KASHMIRI_INDIA                 0x02
#define SUBLANG_KOREAN                         0x01
#define SUBLANG_LITHUANIAN                     0x01
#define SUBLANG_MALAY_MALAYSIA                 0x01
#define SUBLANG_MALAY_BRUNEI_DARUSSALAM        0x02
#define SUBLANG_NEPALI_INDIA                   0x02
#define SUBLANG_NORWEGIAN_BOKMAL               0x01
#define SUBLANG_NORWEGIAN_NYNORSK              0x02
#define SUBLANG_PORTUGUESE                     0x02
#define SUBLANG_PORTUGUESE_BRAZILIAN           0x01
#define SUBLANG_SERBIAN_LATIN                  0x02
#define SUBLANG_SERBIAN_CYRILLIC               0x03
#define SUBLANG_SPANISH                        0x01
#define SUBLANG_SPANISH_MEXICAN                0x02
#define SUBLANG_SPANISH_MODERN                 0x03
#define SUBLANG_SPANISH_GUATEMALA              0x04
#define SUBLANG_SPANISH_COSTA_RICA             0x05
#define SUBLANG_SPANISH_PANAMA                 0x06
#define SUBLANG_SPANISH_DOMINICAN_REPUBLIC     0x07
#define SUBLANG_SPANISH_VENEZUELA              0x08
#define SUBLANG_SPANISH_COLOMBIA               0x09
#define SUBLANG_SPANISH_PERU                   0x0a
#define SUBLANG_SPANISH_ARGENTINA              0x0b
#define SUBLANG_SPANISH_ECUADOR                0x0c
#define SUBLANG_SPANISH_CHILE                  0x0d
#define SUBLANG_SPANISH_URUGUAY                0x0e
#define SUBLANG_SPANISH_PARAGUAY               0x0f
#define SUBLANG_SPANISH_BOLIVIA                0x10
#define SUBLANG_SPANISH_EL_SALVADOR            0x11
#define SUBLANG_SPANISH_HONDURAS               0x12
#define SUBLANG_SPANISH_NICARAGUA              0x13
#define SUBLANG_SPANISH_PUERTO_RICO            0x14
#define SUBLANG_SWEDISH                        0x01
#define SUBLANG_SWEDISH_FINLAND                0x02
#define SUBLANG_URDU_PAKISTAN                  0x01
#define SUBLANG_URDU_INDIA                     0x02
#define SUBLANG_UZBEK_LATIN                    0x01
#define SUBLANG_UZBEK_CYRILLIC                 0x02
#define SUBLANG_DUTCH_SURINAM                  0x03
#define SUBLANG_ROMANIAN                       0x01
#define SUBLANG_ROMANIAN_MOLDAVIA              0x02
#define SUBLANG_RUSSIAN                        0x01
#define SUBLANG_RUSSIAN_MOLDAVIA               0x02
#define SUBLANG_CROATIAN                       0x01
#define SUBLANG_LITHUANIAN_CLASSIC             0x02
#define SUBLANG_GAELIC                         0x01
#define SUBLANG_GAELIC_SCOTTISH                0x02
#define SUBLANG_GAELIC_MANX                    0x03

    typedef struct _IMAGE_DOS_HEADER
    {
        WORD e_magic;
        WORD e_cblp;
        WORD e_cp;
        WORD e_crlc;
        WORD e_cparhdr;
        WORD e_minalloc;
        WORD e_maxalloc;
        WORD e_ss;
        WORD e_sp;
        WORD e_csum;
        WORD e_ip;
        WORD e_cs;
        WORD e_lfarlc;
        WORD e_ovno;
        WORD e_res[4];
        WORD e_oemid;
        WORD e_oeminfo;
        WORD e_res2[10];
        DWORD e_lfanew;
    } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

    typedef struct _IMAGE_FILE_HEADER
    {
        WORD  Machine;
        WORD  NumberOfSections;
        DWORD TimeDateStamp;
        DWORD PointerToSymbolTable;
        DWORD NumberOfSymbols;
        WORD  SizeOfOptionalHeader;
        WORD  Characteristics;
    } IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
#define IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor

    typedef struct _IMAGE_DATA_DIRECTORY
    {
        DWORD VirtualAddress;
        DWORD Size;
    } IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

    typedef struct _IMAGE_OPTIONAL_HEADER
    {
        WORD                 Magic;
        BYTE                 MajorLinkerVersion;
        BYTE                 MinorLinkerVersion;
        DWORD                SizeOfCode;
        DWORD                SizeOfInitializedData;
        DWORD                SizeOfUninitializedData;
        DWORD                AddressOfEntryPoint;
        DWORD                BaseOfCode;
        DWORD                BaseOfData;
        DWORD                ImageBase;
        DWORD                SectionAlignment;
        DWORD                FileAlignment;
        WORD                 MajorOperatingSystemVersion;
        WORD                 MinorOperatingSystemVersion;
        WORD                 MajorImageVersion;
        WORD                 MinorImageVersion;
        WORD                 MajorSubsystemVersion;
        WORD                 MinorSubsystemVersion;
        DWORD                Win32VersionValue;
        DWORD                SizeOfImage;
        DWORD                SizeOfHeaders;
        DWORD                CheckSum;
        WORD                 Subsystem;
        WORD                 DllCharacteristics;
        DWORD                SizeOfStackReserve;
        DWORD                SizeOfStackCommit;
        DWORD                SizeOfHeapReserve;
        DWORD                SizeOfHeapCommit;
        DWORD                LoaderFlags;
        DWORD                NumberOfRvaAndSizes;
        IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
    } IMAGE_OPTIONAL_HEADER, *PIMAGE_OPTIONAL_HEADER;

    typedef struct _IMAGE_OPTIONAL_HEADER64
    {
        WORD        Magic;
        BYTE        MajorLinkerVersion;
        BYTE        MinorLinkerVersion;
        DWORD       SizeOfCode;
        DWORD       SizeOfInitializedData;
        DWORD       SizeOfUninitializedData;
        DWORD       AddressOfEntryPoint;
        DWORD       BaseOfCode;
        ULONGLONG   ImageBase;
        DWORD       SectionAlignment;
        DWORD       FileAlignment;
        WORD        MajorOperatingSystemVersion;
        WORD        MinorOperatingSystemVersion;
        WORD        MajorImageVersion;
        WORD        MinorImageVersion;
        WORD        MajorSubsystemVersion;
        WORD        MinorSubsystemVersion;
        DWORD       Win32VersionValue;
        DWORD       SizeOfImage;
        DWORD       SizeOfHeaders;
        DWORD       CheckSum;
        WORD        Subsystem;
        WORD        DllCharacteristics;
        ULONGLONG   SizeOfStackReserve;
        ULONGLONG   SizeOfStackCommit;
        ULONGLONG   SizeOfHeapReserve;
        ULONGLONG   SizeOfHeapCommit;
        DWORD       LoaderFlags;
        DWORD       NumberOfRvaAndSizes;
        IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
    } IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

    typedef struct _IMAGE_SECTION_HEADER
    {
        BYTE  Name[IMAGE_SIZEOF_SHORT_NAME];
        union
        {
            DWORD PhysicalAddress;
            DWORD VirtualSize;
        } Misc;
        DWORD VirtualAddress;
        DWORD SizeOfRawData;
        DWORD PointerToRawData;
        DWORD PointerToRelocations;
        DWORD PointerToLinenumbers;
        WORD  NumberOfRelocations;
        WORD  NumberOfLinenumbers;
        DWORD Characteristics;
    } IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

    typedef struct _IMAGE_THUNK_DATA32
    {
        union
        {
            DWORD ForwarderString;      // PBYTE
            DWORD Function;             // PDWORD
            DWORD Ordinal;
            DWORD AddressOfData;        // PIMAGE_IMPORT_BY_NAME
        } u1;
    } IMAGE_THUNK_DATA32;
    typedef IMAGE_THUNK_DATA32      *PIMAGE_THUNK_DATA32;
    typedef PIMAGE_THUNK_DATA32     PIMAGE_THUNK_DATA;

    typedef struct _IMAGE_IMPORT_DESCRIPTOR
    {
        union
        {
            //PIMAGE_THUNK_DATA OriginalFirstThunk;
			DWORD OriginalFirstThunk;
            DWORD Characteristics;
        };

        DWORD TimeDateStamp;
        DWORD ForwarderChain;
        DWORD Name;
		//PIMAGE_THUNK_DATA FirstThunk;
        DWORD FirstThunk;
    } IMAGE_IMPORT_DESCRIPTOR, *PIMAGE_IMPORT_DESCRIPTOR;

    typedef struct _IMAGE_IMPORT_BY_NAME
    {
        WORD    Hint;
        BYTE    Name[1];
    } IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;

    typedef struct _IMAGE_TLS_DIRECTORY64
    {
        ULONGLONG   StartAddressOfRawData;
        ULONGLONG   EndAddressOfRawData;
        ULONGLONG   AddressOfIndex;         // PDWORD
        ULONGLONG   AddressOfCallBacks;     // PIMAGE_TLS_CALLBACK *;
        DWORD   SizeOfZeroFill;
        DWORD   Characteristics;
    } IMAGE_TLS_DIRECTORY64;
    typedef IMAGE_TLS_DIRECTORY64 * PIMAGE_TLS_DIRECTORY64;

    typedef struct _IMAGE_TLS_DIRECTORY32
    {
        DWORD   StartAddressOfRawData;
        DWORD   EndAddressOfRawData;
        DWORD   AddressOfIndex;             // PDWORD
        DWORD   AddressOfCallBacks;         // PIMAGE_TLS_CALLBACK *
        DWORD   SizeOfZeroFill;
        DWORD   Characteristics;
    } IMAGE_TLS_DIRECTORY32;
    typedef IMAGE_TLS_DIRECTORY32 * PIMAGE_TLS_DIRECTORY32;

    typedef struct _IMAGE_RESOURCE_DIRECTORY
    {
        DWORD   Characteristics;
        DWORD   TimeDateStamp;
        WORD    MajorVersion;
        WORD    MinorVersion;
        WORD    NumberOfNamedEntries;
        WORD    NumberOfIdEntries;
        //  IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[];
    } IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

    typedef struct _IMAGE_EXPORT_DIRECTORY
    {
        DWORD   Characteristics;
        DWORD   TimeDateStamp;
        WORD    MajorVersion;
        WORD    MinorVersion;
        DWORD   Name;
        DWORD   Base;
        DWORD   NumberOfFunctions;
        DWORD   NumberOfNames;
        DWORD   AddressOfFunctions;     // RVA from base of image
        DWORD   AddressOfNames;         // RVA from base of image
        DWORD   AddressOfNameOrdinals;  // RVA from base of image
    } IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

    typedef struct _IMAGE_NT_HEADERS
    {
        DWORD                 Signature;
        IMAGE_FILE_HEADER     FileHeader;
        IMAGE_OPTIONAL_HEADER OptionalHeader;
    } IMAGE_NT_HEADERS, *PIMAGE_NT_HEADERS;

#ifdef __cplusplus
}
#endif

#endif /* _FILE_PE_H_ */
