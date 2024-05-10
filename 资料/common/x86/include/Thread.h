// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __THREAD_H
#define  __THREAD_H

#include "Types.h"

namespace tzc {

class DECLDLL OSThread {

public:
#if defined(WIN32) || defined(WINDOWS)
	typedef DWORD			STTid;	// just a integer, represent for thread ID
	typedef DWORD			STKey;
	typedef HANDLE			STAttr;	// use to handle the thread, is different from Linux
#elif defined(LINUX)
	typedef pthread_t		STTid;
	typedef pthread_key_t	STKey;
	typedef pthread_attr_t	STAttr;
#endif

public:
	OSThread();
	virtual ~OSThread();

	virtual void Entry() = 0;

	void Start();

	void Stop();
	void StopAndWait();

	void Join();

	TZ_BOOL IsRunning() const;
	TZ_BOOL IsStop() const;

	TZ_BOOL SetStackSize(const TZ_Int32 iSize);		// in Bytes
	TZ_Int32 GetStackSize() const;

	TZ_BOOL SetCPUIndex(const TZ_Int32 iIndex);
	TZ_Int32 GetCPUIndex() const;

	TZ_BOOL SetPolicy(const TZ_Int32 iPolicy);
	TZ_Int32 GetPolicy() const;

	TZ_BOOL SetPriority(const TZ_Int32 iPriority);
	TZ_Int32 GetPriority() const;

	TZ_BOOL SetThreadName(const std::string & sName);
	const std::string & GetThreadName();

	STTid GetTid() const;

	static STTid CurrentTid();

	static OSThread * Current();

	static const std::string & CurrentName();

protected:
#if defined(WIN32) || defined(WINDOWS)
	static unsigned WINAPI __Running(void *arg);
#elif defined(LINUX)
	static void * __Running(void *arg);
#endif

private:
	volatile TZ_BOOL m_bRunning;
	volatile TZ_BOOL m_bStop;

	TZ_Int32  m_iStackSize;
	TZ_Int32  m_iPolicy;
	TZ_Int32  m_iPriority;
	TZ_Int32  m_iCPUIndex;
	
	STTid	m_threadID;
	STAttr	m_threadAttr;

	std::string m_sName;

	class ThreadHolder {
		public:
			ThreadHolder()
			{
			#if defined(WIN32) || defined(WINDOWS)
				m_key = TlsAlloc();
				if (TLS_OUT_OF_INDEXES == m_key)
					throw std::runtime_error("Create thread key failed");
			#elif defined(LINUX)
				if (pthread_key_create(&m_key, NULL))
					throw std::runtime_error("Create thread key failed");
			#endif
			}
			~ThreadHolder()
			{
			#if defined(WIN32) || defined(WINDOWS)
				TlsFree(m_key);
			#elif defined(LINUX)
				pthread_key_delete(m_key);
			#endif
			}

			void * Get() const
			{
			#if defined(WIN32) || defined(WINDOWS)
				return TlsGetValue(m_key);
			#elif defined(LINUX)
				return pthread_getspecific(m_key);
			#endif
			}

			void Set(void *pData)
			{
			#if defined(WIN32) || defined(WINDOWS)
				TlsSetValue(m_key, pData);
			#elif defined(LINUX)
				pthread_setspecific(m_key, pData);
			#endif
			}

		private:
			STKey m_key;
	};

	static ThreadHolder m_holder;
};

//
// inlines
//
inline TZ_BOOL OSThread::IsRunning() const
{
	return !m_bStop;
}

inline TZ_BOOL OSThread::IsStop() const
{
	return m_bStop;
}

inline TZ_Int32 OSThread::GetStackSize() const
{
	if (m_bRunning)
		return m_iStackSize;

	return -1;
}

inline TZ_Int32 OSThread::GetCPUIndex() const
{
	if (m_bRunning)
		return m_iCPUIndex;

	return -1;
}

inline TZ_Int32 OSThread::GetPolicy() const
{
	if (m_bRunning)
		return m_iPolicy;

	return -1;
}

inline TZ_Int32 OSThread::GetPriority() const
{
	if (m_bRunning)
		return m_iPriority;

	return -1;
}

inline OSThread::STTid OSThread::GetTid() const
{
	if (m_bRunning)
		return m_threadID;

	return static_cast<STTid>(-1);
}

}	// namespace tzc

#endif   /* ----- #ifndef __THREAD_H  ----- */

