// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __BYTESORDER_H
#define  __BYTESORDER_H

#define  hton_16(x)   cpu_to_be16(x)
#define  ntoh_16(x)   be16_to_cpu(x)
#define  hton_32(x)   cpu_to_be32(x)
#define  ntoh_32(x)   be32_to_cpu(x)
#define  hton_64(x)   cpu_to_be64(x)
#define  ntoh_64(x)   be64_to_cpu(x)

#define  htole_16(x)  cpu_to_le16(x)
#define  htole_32(x)  cpu_to_le32(x)
#define  htole_64(x)  cpu_to_le64(x)
#define  htobe_16(x)  cpu_to_be16(x)
#define  htobe_32(x)  cpu_to_be32(x)
#define  htobe_64(x)  cpu_to_be64(x)
#define  letoh_16(x)  le16_to_cpu(x)
#define  letoh_32(x)  le32_to_cpu(x)
#define  letoh_64(x)  le64_to_cpu(x)
#define  betoh_16(x)  be16_to_cpu(x)
#define  betoh_32(x)  be32_to_cpu(x)
#define  betoh_64(x)  be64_to_cpu(x)

#include "BaseTypes.h"

#define swap_int16(x) \
( \
  (TZ_Uint16)( \
	  (((TZ_Uint16)(x) & (TZ_Uint16)0x00ffU) << 8) | \
	  (((TZ_Uint16)(x) & (TZ_Uint16)0xff00U) >> 8) ) \
)

#define swap_int32(x) \
( \
  (TZ_Uint32)( \
	  (((TZ_Uint32)(x) & (TZ_Uint32)0x000000ffUL) << 24) | \
	  (((TZ_Uint32)(x) & (TZ_Uint32)0x0000ff00UL) <<  8) | \
	  (((TZ_Uint32)(x) & (TZ_Uint32)0x00ff0000UL) >>  8) | \
	  (((TZ_Uint32)(x) & (TZ_Uint32)0xff000000UL) >> 24) ) \
)

#define swap_int64(x) \
( \
  (TZ_Uint64)( \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x00000000000000ffULL) << 56) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x000000000000ff00ULL) << 40) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x0000000000ff0000ULL) << 24) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x00000000ff000000ULL) <<  8) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x000000ff00000000ULL) >>  8) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x0000ff0000000000ULL) >> 24) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0x00ff000000000000ULL) >> 40) | \
	  (TZ_Uint64)(((TZ_Uint64)(x) & (TZ_Uint64)0xff00000000000000ULL) >> 56) ) \
)

#ifdef BIG_ENDIAN_CPU	// big-endian

#define  be16_to_cpu(x)  ((TZ_Uint16)(x))
#define  cpu_to_be16(x)  ((TZ_Uint16)(x))

#define  be32_to_cpu(x)  ((TZ_Uint32)(x))
#define  cpu_to_be32(x)  ((TZ_Uint32)(x))

#define  be64_to_cpu(x)  ((TZ_Uint64)(x))
#define  cpu_to_be64(x)  ((TZ_Uint64)(x))  

#define  le16_to_cpu(x)  (swap_int16((x)))
#define  cpu_to_le16(x)  (swap_int16((x)))

#define  le32_to_cpu(x)  (swap_int32((x)))
#define  cpu_to_le32(x)  (swap_int32((x)))

#define  le64_to_cpu(x)  (swap_int64((x)))
#define  cpu_to_le64(x)  (swap_int64((x)))

#else	// little-endian

#define  be16_to_cpu(x)  (swap_int16((x)))
#define  cpu_to_be16(x)  (swap_int16((x)))

#define  be32_to_cpu(x)  (swap_int32((x)))
#define  cpu_to_be32(x)  (swap_int32((x)))

#define  be64_to_cpu(x)  (swap_int64((x)))
#define  cpu_to_be64(x)  (swap_int64((x)))

#define  le16_to_cpu(x)  ((TZ_Uint16)(x))
#define  cpu_to_le16(x)  ((TZ_Uint16)(x))

#define  le32_to_cpu(x)  ((TZ_Uint32)(x))
#define  cpu_to_le32(x)  ((TZ_Uint32)(x))

#define  le64_to_cpu(x)  ((TZ_Uint64)(x))
#define  cpu_to_le64(x)  ((TZ_Uint64)(x))

#endif

#endif   /* ----- #ifndef __BYTESORDER_H  ----- */

