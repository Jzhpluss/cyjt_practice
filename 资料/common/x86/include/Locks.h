// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __LOCKS_H
#define  __LOCKS_H

#include "Types.h"

namespace tzc {

class DECLDLL Mutex {

public:
	Mutex(TZ_BOOL bFast = false);
	~Mutex();

	void Lock();

	TZ_BOOL TryLock();
	TZ_BOOL TryLock(const TZ_LONG mseconds);

	void Unlock();

private:

#if defined(WIN32) || defined(WINDOWS)
	CRITICAL_SECTION m_cs;
#elif defined(LINUX)
	pthread_mutex_t m_mutex;
#endif

};

class DECLDLL RWLock {

public:
	RWLock();
	~RWLock();

	void ReadLock();
	TZ_BOOL TryReadLock();

	void WriteLock();
	TZ_BOOL TryWriteLock();

	void Unlock();

private:

#if defined(WIN32) || defined(WINDOWS)
	typedef enum _LockState
	{
		RWLOCK_IDLE,
		RWLOCK_READ,
		RWLOCK_WRITE,

		RWLOCK_END
	}LockState;

	TZ_Int32	m_iState;			// Lock State
	TZ_Int32	m_iRDLockCnt;		// ReadLock Count
	TZ_Int32	m_iRDWaitingCnt;	// ReadLock Waiting Count
	TZ_Int32	m_iWRWaitingCnt;	// WriteLock Waiting Count

	HANDLE		m_ev;				// Event
	CRITICAL_SECTION m_cs;			// Critical Section
#elif defined(LINUX)
	pthread_rwlock_t m_rw;
#endif
};

class DECLDLL ScopedLock {

public:
	ScopedLock(Mutex & mtx) : m_mutex(mtx)
	{
		m_mutex.Lock();
	}
	
	~ScopedLock()
	{
		m_mutex.Unlock();
	}

private:
	Mutex & m_mutex;

private:
	ScopedLock(const ScopedLock &);
	ScopedLock & operator=(const ScopedLock &);
};

}	// namespace tzc

#endif   /* ----- #ifndef __LOCKS_H  ----- */

