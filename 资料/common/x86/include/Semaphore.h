// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __SEMAPHORE_H
#define  __SEMAPHORE_H

#include "Types.h"

namespace tzc {

class DECLDLL Semaphore {

public:
	Semaphore(TZ_Uint32 iMax = 4096);
	~Semaphore();

	void Signal();
	void Wait();
	TZ_Int32 Count();
	const TZ_Int32 Max();
	TZ_BOOL Wait(TZ_LONG lMseconds);

private:

#if defined(WIN32) || defined(WINDOWS)
	HANDLE hd;
#elif defined(LINUX)
	pthread_mutex_t m_mutex;
	pthread_cond_t  m_cond;
#endif

	volatile TZ_Int32 m_iCount;
	const TZ_Int32 m_iMax;
};

inline TZ_Int32 Semaphore::Count()
{
	return m_iCount;
}

inline const TZ_Int32 Semaphore::Max()
{
	return m_iMax;
}

}	// namespace tzc

#endif   /* ----- #ifndef __SEMAPHORE_H  ----- */

