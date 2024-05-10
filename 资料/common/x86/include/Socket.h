// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2015-07
//

#ifndef  __SOCKET_H
#define  __SOCKET_H

#include "Types.h"
#include "RefCounter.h"
#include "SockAddress.h"

#if defined(WIN32) || defined(WINDOWS)
#include <MSTcpIP.h>
#elif defined(LINUX)
#include <netinet/tcp.h>
#include <sys/poll.h>
#endif

namespace tzc {

class DECLDLL Socket {

public:
	enum __SOCK_TYPE {

		STYPE_UDP,
		STYPE_TCP,
		STYPE_TCPS,
		STYPE_UNIX_UDP,
		STYPE_UNIX_TCP,
		STYPE_UNIX_TCPS,
		STYPE_UNKNOWN
	};

	typedef std::vector<Socket *> SockList;

	static TZ_INT LastError();

	// @timeout in microsecond
	static TZ_INT SelectList(SockList & readList, 
							SockList & writeList, 
							SockList & errorList, 
							TZ_Uint32 timeout);

public:
	Socket(TZ_Uint32 type = STYPE_UNKNOWN);

	Socket(const Socket & sock);

	virtual ~Socket();

	virtual TZ_INT Bind(const SockAddress & addr) = 0;

	virtual TZ_INT Connect(const SockAddress & raddr) = 0;
	
	virtual TZ_INT RecvBytes(TZ_BYTE * buffer, TZ_Uint32 length) = 0;
	
	virtual TZ_INT SendBytes(const TZ_BYTE * buffer, TZ_Uint32 length) = 0;

	// the socket type must be UDP or UNIX_UDP
	virtual TZ_INT SendBytes(const TZ_BYTE * buffer, TZ_Uint32 length, 
			const SockAddress & raddr) = 0;

	// the following two functions always should be 
	// called after the first SendBytes()
	virtual SockAddress LocalAddress() const;

	virtual SockAddress PeerAddress() const;

	// operator reloaded interfaces
public:
	Socket & operator = (const Socket& socket);

	bool operator == (const Socket& socket) const;

	bool operator != (const Socket& socket) const;

	bool operator <  (const Socket& socket) const;

	bool operator <= (const Socket& socket) const;

	bool operator >  (const Socket& socket) const;

	bool operator >= (const Socket& socket) const;

	// configuration interfaces
public:
	// return number of available bytes in the read buffer
	// -1 indicates failure, the error number can be fetched by LastError()
	TZ_INT Available();

	// return 0 on success, otherwise return -1
	TZ_INT SetBlocking(TZ_BOOL flag);

	TZ_BOOL GetBlocking() const;

	// return 0 on success, otherwise return -1
	TZ_INT SetSendBuffSize(TZ_Uint32 size);

	TZ_Uint32 GetSendBuffSize();

	// return 0 on success, otherwise return -1
	TZ_INT SetRecvBuffSize(TZ_Uint32 size);

	TZ_Uint32 GetRecvBuffSize();

	// return 0 on success, otherwise return -1
	TZ_INT SetReuseAddress(TZ_BOOL flag);

	TZ_BOOL GetReuseAddress();

	// return 0 on success, otherwise return -1
	TZ_INT SetReusePort(TZ_BOOL flag);

	TZ_BOOL GetReusePort();

	// data interfaces
public:
	
	// all the Select functions are in following rules
	//
	// @timeout in microsecond, 
	// return value : 0 for timeout, -1 for failure, 1 for success
	//
	// it indicates the select will block indefinitely 
	// if @timeout is equal to INVALID_VALUE32
	
	// select for all
	TZ_INT Select(TZ_Uint32 timeout, TZ_BOOL & rdSet, 
			TZ_BOOL & wrSet, TZ_BOOL & errSet);

	// select for read only
	TZ_INT SelectForRead(TZ_Uint32 timeout);

	// select for write only
	TZ_INT SelectForWrite(TZ_Uint32 timeout);

	// select for error only
	TZ_INT SelectForError(TZ_Uint32 timeout);

	void Close();

public:
	TZ_BOOL IsValid() const;

	TZ_SOCKET Descriptor() const;

	TZ_Uint32 Type() const;

	TZ_Uint32 State() const;

#ifdef LINUX
	const struct pollfd & Pollfd() const;
#endif

protected:
	int setOption(int level, int option, int value);
	int setOption(int level, int option, unsigned value);
	int setOption(int level, int option, unsigned char value);
	int setOption(int level, int option, struct ip_mreq value);
	int setOption(int level, int option, struct in_addr value);
	
	int setRawOption(int level, int option, 
			const void * value, TZ_SOCKLEN length);

	int getOption(int level, int option, int & value);
	int getOption(int level, int option, unsigned & value);
	int getOption(int level, int option, unsigned char & value);
	int getOption(int level, int option, struct ip_mreq & value);
	int getOption(int level, int option, struct in_addr & value);
	
	int getRawOption(int level, int option, 
			void * value, TZ_SOCKLEN & length);

	void setState(TZ_Uint32 state);

#ifdef LINUX
	void initfd();
#endif

protected:
	TZ_SOCKET m_sock;
	TZ_Uint32 m_type;

	TZ_BOOL m_blocking;
	TZ_BOOL m_connected;

#ifdef LINUX
	struct pollfd  	m_pfd;
#endif

private:
	RefCounter * m_refcnt;
};

//
// inlines
//
inline bool Socket::operator == (const Socket& socket) const
{
	return (this->m_sock == socket.m_sock);
}

inline bool Socket::operator != (const Socket& socket) const
{
	return !(*this == socket);
}

inline bool Socket::operator <  (const Socket& socket) const
{
	return (this->m_sock < socket.m_sock);
}

inline bool Socket::operator <= (const Socket& socket) const
{
	return (*this == socket || *this < socket);
}

inline bool Socket::operator >  (const Socket& socket) const
{
	return !(*this <= socket);
}

inline bool Socket::operator >= (const Socket& socket) const
{
	return !(*this < socket);
}

inline TZ_BOOL Socket::GetBlocking() const
{
	return m_blocking;
}

inline TZ_BOOL Socket::IsValid() const
{
	return (m_sock != INVALID_SOCKET);
}

inline TZ_SOCKET Socket::Descriptor() const
{
	return m_sock;
}

inline TZ_Uint32 Socket::Type() const
{
	return m_type;
}

#ifdef LINUX
inline const struct pollfd & Socket::Pollfd() const
{
	return m_pfd;
}
#endif

};	// namespace tzc

#endif   /* ----- #ifndef __SOCKET_H  ----- */

