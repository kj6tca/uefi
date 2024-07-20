#ifndef _UEFI_H_
#define _UEFI_H_

/* References
	[USWG]	UEFI Specification Working Group
		Unified Extensible Firmware Interface (UEFI) Specification.
		UEFI Forum, Inc. Release 2.10 Aug. 29, 2022.
*/

#include <stdint.h>

/* Table 5. Common UEFI Data Types [USWG pp.21-22] */
typedef uint8_t	  		BOOLEAN;
#define FALSE (BOOLEAN)0
#define TRUE (BOOLEAN)1
typedef	int8_t			INT8;
typedef uint8_t			UINT8, CHAR8;
typedef	int16_t			INT16;
typedef uint16_t		UINT16, CHAR16;
typedef	int32_t			INT32;
typedef uint32_t		UINT32;
typedef	int64_t			INT64, INTN;
typedef uint64_t		UINT64, UINTN;
typedef void			VOID;

typedef struct _EFI_GUID {
	UINT32				time_low;
	UINT16				time_mid;
	UINT16				time_hi_and_version;
	UINT8				clock_seq_hi_and_reserved;
	UINT8				clock_seq_low;
	UINT8				node[6];
} EFI_GUID __attribute__((aligned (8)));

typedef UINTN			EFI_STATUS;
typedef VOID*			EFI_HANDLE;
typedef VOID*			EFI_EVENT;
typedef UINT64			EFI_LBA;
typedef UINTN			EFI_TPL;

typedef struct {
	UINT8	Addr[32];
} EFI_MAC_ADDRESS;

typedef struct {
	UINT8	Addr[4];
} EFI_IPv4_ADDRESS;

typedef struct {
	UINT8	Addr[16];
}EFI_IPv6_ADDRESS;

typedef union {
	EFI_IPv4_ADDRESS		v4;
	EFI_IPv6_ADDRESS		v6;
} EFI_IP_ADDRESS __attribute__((aligned (4)));

/* Table 6. Modifiers for Common UEFI Data Types [USWG pg.22] */
#define IN
#define OUT
#define OPTIONAL
#define CONST	const
#define EFIAPI	__attribute__((ms_abi))

/* 4.2 EFI Table Header [USWG pp.89-90] */
typedef struct _EFI_TABLE_HEADER {
	UINT64		Signature;
	UINT32		Revision;
	UINT32		HeaderSize;
	UINT32		CRC32;
	UINT32		Reserved;
} EFI_TABLE_HEADER;

/* Helper macros for EFI_STATUS code literals */
#define EFI_WARN(a)	(0x0000000000000000 | a)
#define PIA_WARN(a)	(0x2000000000000000 | a)
#define OEM_WARN(a)	(0x4000000000000000 | a)
#define EFI_ERR(a)	(0x8000000000000000 | a)
#define PIA_ERR(a)	(0xA000000000000000 | a)
#define OEM_ERR(a)	(0xC000000000000000 | a)

/* Table D.1 EFI_STATUS Code Ranges [USWG 1841] */
#define EFI_WARNING(a)  (((uint64_t)(a) > 0x0000000000000000) && ((uint64_t)(a) <= 0x1FFFFFFFFFFFFFFF))
#define PIA_WARNING(a)	(((uint64_t)(a) >= 0x2000000000000000) && ((uint64_t)(a) <= 0x3FFFFFFFFFFFFFFF))
#define OEM_WARNING(a)	(((uint64_t)(a) >= 0x4000000000000000) && ((uin64_t)(a) <= 0x7fffffffffffffff))
#define EFI_ERROR(a)	(((uint64_t)(a) >= 0x8000000000000000) && ((uint64_t)(a) <= 0x9FFFFFFFFFFFFFFF))
#define PIA_ERROR(a)	(((uint64_t)(a) >= 0xA000000000000000) && ((uint64_t)(a) <= 0xBFFFFFFFFFFFFFFF))
#define OEM_ERROR(a)	(((uint64_t)(a) >= 0xC000000000000000) && ((uint64_t)(a) <= 0xCFFFFFFFFFFFFFFF))

/* Table D.2 EFI_STATUS Success Codes (High Bit Clear) [USWG pg.1841] */
#define	EFI_SUCCESS			EFI_WARN(0)

/* Table D.3 EFI_STATUS Error Codes (High Bit Set) [USWG pp.1841-1842] */
#define	EFI_LOAD_ERROR			EFI_ERR(1)
#define	EFI_INVALID_PARAMETER		EFI_ERR(2)
#define	EFI_UNSUPPORTED			EFI_ERR(3)
#define	EFI_BAD_BUFFER_SIZE		EFI_ERR(4)
#define	EFI_BUFFER_TOO_SMALL		EFI_ERR(5)
#define	EFI_NOT_READY			EFI_ERR(6)
#define	EFI_DEVICE_ERROR		EFI_ERR(7)
#define	EFI_WRITE_PROTECTED		EFI_ERR(8)
#define	EFI_OUT_OF_RESOURCES		EFI_ERR(9)
#define	EFI_VOLUME_CORRUPTED		EFI_ERR(10)
#define	EFI_VOLUME_FULL			EFI_ERR(11)
#define	EFI_NO_MEDIA			EFI_ERR(12)
#define	EFI_MEDIA_CHANGED		EFI_ERR(13)
#define	EFI_NOT_FOUND			EFI_ERR(14)
#define	EFI_ACCESS_DENIED		EFI_ERR(15)
#define	EFI_NO_RESPONSE			EFI_ERR(16)
#define	EFI_NO_MAPPING			EFI_ERR(17)
#define	EFI_TIMEOUT			EFI_ERR(18)
#define	EFI_NOT_STARTED			EFI_ERR(19)
#define	EFI_ALREADY_STARTED		EFI_ERR(20)
#define	EFI_ABORTED			EFI_ERR(21)
#define	EFI_ICMP_ERROR			EFI_ERR(22)
#define	EFI_TFTP_ERROR			EFI_ERR(23)
#define	EFI_PROTOCOL_ERROR		EFI_ERR(24)
#define	EFI_INCOMPATIBLE_VERSION	EFI_ERR(25)
#define	EFI_SECURITY_VIOLATION		EFI_ERR(26)
#define	EFI_CRC_ERROR			EFI_ERR(27)
#define	EFI_END_OF_MEDIA		EFI_ERR(28)
#define	EFI_END_OF_FILE			EFI_ERR(31)
#define	EFI_INVALID_LANGUAGE		EFI_ERR(32)
#define	EFI_COMPROMISED_DATA		EFI_ERR(33)
#define	EFI_IP_ADDRESS_CONFLICT		EFI_ERR(34)
#define	EFI_HTTP_ERROR			EFI_ERR(35)

/* Table D.4 EFI_STATUS Warning Codes (High Bit Clear) [USWG pp.1842-1843] */
#define EFI_WARN_UNKNOWN_GLYPH		EFI_WARN(1)
#define EFI_WARN_DELETE_FAILURE		EFI_WARN(2)
#define EFI_WARN_WRITE_FAILURE		EFI_WARN(3)
#define EFI_WARN_BUFFER_TOO_SMALL	EFI_WARN(4)
#define EFI_WARN_STALE_DATA		EFI_WARN(5)
#define EFI_WARN_FILE_SYSTEM		EFI_WARN(6)
#define EFI_WARN_RESET_REQUIRED		EFI_WARN(7)

/* Includes for System Table by order of appearance */
#include "uefi_boot_services.h"
#include "uefi_runtime_services.h"
#include "uefi_simple_text_output_protocol.h"
#include "uefi_simple_text_input_protocol.h"
#include "uefi_system_table.h"

#endif // _UEFI_H_
