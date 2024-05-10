#ifndef  __REFCOUNTER_H
#define  __REFCOUNTER_H

#include "Locks.h"

namespace tzc {

class RefCounter {

public:
	RefCounter() : m_count(0) {}
	~RefCounter() {}

	void Duplicate();

	void Release();

	bool ReleaseAndTest();

	TZ_Uint32 Current();

protected:
	RefCounter(const RefCounter &);
	RefCounter & operator = (const RefCounter &);

private:
	Mutex m_mutex;
	TZ_Uint32 m_count;
};

// 
// inlines
//
inline void RefCounter::Duplicate()
{
	ScopedLock lock(m_mutex);

	++m_count;
}

inline void RefCounter::Release()
{
	ScopedLock lock(m_mutex);

	if (m_count > 0)
	{
		--m_count;
	}
}

inline bool RefCounter::ReleaseAndTest()
{
	ScopedLock lock(m_mutex);

	if (m_count > 0)
	{
		--m_count;
	}

	return m_count == 0;
}

inline TZ_Uint32 RefCounter::Current()
{
	ScopedLock lock(m_mutex);

	return m_count;
}

};	// namespace tzc

#endif   /* ----- #ifndef __REFCOUNTER_H  ----- */

