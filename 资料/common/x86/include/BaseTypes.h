#ifndef  __BASETYPES_H
#define  __BASETYPES_H

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif

#if defined(WIN32) || defined(WINDOWS)

#define SCHED_OTHER		(0)
#define SCHED_FIFO		(1)
#define SCHED_RR		(2)

#ifndef SDKAPI
#define SDKAPI __declspec(dllexport)
#define SO_PREFIX	""
#define SO_SUFFIX   ".dll"
#endif

#ifdef EXPORT_COMMON
#define DECLDLL	__declspec(dllexport)
#else
#define DECLDLL
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#elif defined(LINUX)

#ifndef SDKAPI
#define SDKAPI
#define SO_PREFIX	"lib"
#define SO_SUFFIX   ".so"
#endif

#define DECLDLL

#ifndef CALLBACK
#define CALLBACK
#endif

#endif

#define NUMBERICS       "0123456789"

#define INVALID_VALUE16 ((TZ_Uint16)-1)
#define INVALID_VALUE32 ((TZ_Uint32)-1)
#define INVALID_VALUE64 ((TZ_Uint64)-1)
#define INVALID_HANDLE	((TZ_ULONG)-1)
#define INVALID_DLLHD	(0)

#define MAX_INTEGER_16	INVALID_VALUE16
#define MAX_INTEGER_32	INVALID_VALUE32
#define MAX_INTEGER_64	INVALID_VALUE64

typedef int						TZ_BOOL;

typedef unsigned char           TZ_BYTE;

typedef unsigned char           TZ_UCHAR;
typedef char             		TZ_CHAR;
typedef signed char             TZ_SCHAR;

typedef unsigned short          TZ_USHORT;
typedef short              		TZ_SHORT;
typedef signed short            TZ_SSHORT;

typedef unsigned int            TZ_UINT;
typedef int              		TZ_INT;
typedef signed int              TZ_SINT;

typedef unsigned long           TZ_ULONG;
typedef long             		TZ_LONG;
typedef signed long             TZ_SLONG;

typedef unsigned long long      TZ_ULONGLONG;
typedef long long        		TZ_LONGLONG;
typedef signed long long        TZ_SLONGLONG;

typedef unsigned char           TZ_Uint8;
typedef char             		TZ_Int8;
typedef signed char             TZ_Sint8;

typedef unsigned short          TZ_Uint16;
typedef short            		TZ_Int16;
typedef signed short            TZ_Sint16;

typedef unsigned int            TZ_Uint32;
typedef int              		TZ_Int32;
typedef signed int              TZ_Sint32;

typedef unsigned long long      TZ_Uint64;
typedef long long        		TZ_Int64;

typedef float	                TZ_FLOAT;
typedef double                  TZ_DOUBLE;

typedef void *					TZ_PVOID;

typedef void *					TZ_DLLHD;

typedef unsigned long			TZ_HANDLE;

typedef unsigned long long		TZ_HANDLE64;

#endif   /* ----- #ifndef __BASETYPES_H  ----- */

