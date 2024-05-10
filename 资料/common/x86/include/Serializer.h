// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef __SERIALIZER_H
#define __SERIALIZER_H

#include <cassert>
#include "BaseTypes.h"
#include "BaseHeaders.h"
#include "BaseCalls.h"

namespace tzc {

class Serializer {

public:
	Serializer()
	{
	}

	virtual ~Serializer()
	{
	}

	virtual TZ_BOOL ToByteArray(TZ_BYTE *, TZ_Uint32 &) = 0;
	virtual TZ_BOOL FromByteArray(const TZ_BYTE *, TZ_Uint32 ) = 0;
	virtual TZ_Uint32 GetPackedSize(void) const = 0;

protected:
	// from memory to property
	template<class T>
	TZ_Uint32 MemToProperty(const TZ_BYTE *, T &);
	TZ_Uint32 MemToProperty(const TZ_BYTE *, TZ_BYTE *, TZ_Uint32);
	TZ_Uint32 MemToProperty(const TZ_BYTE *, TZ_CHAR *, TZ_Uint32);

	// from property to memory
	template<class T>
	TZ_Uint32 PropertyToMem(TZ_BYTE *, const T &);
	TZ_Uint32 PropertyToMem(TZ_BYTE *, const TZ_BYTE *, TZ_Uint32);
	TZ_Uint32 PropertyToMem(TZ_BYTE *, const TZ_CHAR *, TZ_Uint32);
};

// 
// inlines
//
inline TZ_Uint32 Serializer::MemToProperty(const TZ_BYTE * pMem, 
		TZ_BYTE * property, TZ_Uint32 len)
{
	assert(pMem != NULL && property != NULL && len != 0);
	memcpy(property, pMem, len);
				
	return len;
}

inline TZ_Uint32 Serializer::MemToProperty(const TZ_BYTE * pMem, 
		TZ_CHAR * property, TZ_Uint32 len)
{
	assert(pMem != NULL && property != NULL && len != 0);
	STRNCPY(property, reinterpret_cast<const TZ_CHAR *>(pMem), len);
				
	return len;
}

inline TZ_Uint32 Serializer::PropertyToMem(TZ_BYTE * pMem, 
		const TZ_BYTE * property, const TZ_Uint32 len)
{
	assert(pMem != NULL && property != NULL && len != 0);
	memcpy(pMem, property, len);

	return len;
}

inline TZ_Uint32 Serializer::PropertyToMem(TZ_BYTE * pMem, 
		const TZ_CHAR * property, const TZ_Uint32 len)
{
	assert(pMem != NULL && property != NULL && len != 0);
	STRNCPY(reinterpret_cast<TZ_CHAR *>(pMem), property, len);

	return len;
}

template<class T> 
TZ_Uint32 Serializer::MemToProperty(const TZ_BYTE * pMem, T & property)
{
	assert(pMem != NULL);
	property = *(reinterpret_cast<const T *>(pMem));
	return sizeof(property);
}

template<class T>
TZ_Uint32 Serializer::PropertyToMem(TZ_BYTE * pMem, const T & property)
{
	assert(pMem != NULL);
	*(reinterpret_cast<T *>(pMem)) = property;
	return sizeof(property);
}

};	// namespace tzc

#endif

