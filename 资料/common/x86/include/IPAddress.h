// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2015-07
//

#ifndef  __IPADDRESS_H
#define  __IPADDRESS_H

#include "BaseTypes.h"
#include "BaseHeaders.h"
#include "BaseCalls.h"
#include "ErrorCode.h"

#if defined(WIN32) || defined(WINDOWS)
#include <ws2tcpip.h>
#include <ws2ipdef.h>
#elif defined(LINUX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#endif

namespace tzc {

// network address family
enum __ADDR_FAMILY {

	AF_V4,
	AF_V6,
	AF_UN,
	AF_UNKNOWN
};

void DECLDLL InitOSNetwork();

void DECLDLL UninitOSNetwork();


class IPAddressImp {

public:
	virtual TZ_Uint32 Size() const = 0;
	
	virtual TZ_Uint32 Scope() const = 0;

	virtual TZ_Uint32 Family() const = 0;

	virtual std::string ToString() const = 0;

	virtual const void * Addr() const = 0;

	virtual TZ_BOOL IsWildcard() const = 0;
	
	virtual TZ_BOOL IsBroadcast() const = 0;

	virtual TZ_BOOL IsLoopback() const = 0;

	virtual TZ_BOOL IsMulticast() const = 0;

	virtual TZ_INT SetAddress(const void * bytes) = 0;

	virtual ~IPAddressImp()
	{
		tzc::UninitOSNetwork();
	}
	
protected:
	IPAddressImp()
	{
		tzc::InitOSNetwork();
	}

private:
	IPAddressImp(const IPAddressImp &);
	IPAddressImp & operator = (const IPAddressImp &);
};

class IPv4IPAddressImp : public IPAddressImp {

public:
	IPv4IPAddressImp();

	IPv4IPAddressImp(const void * bytes);

	virtual TZ_Uint32 Size() const;

	virtual TZ_Uint32 Scope() const;

	virtual TZ_Uint32 Family() const;

	virtual std::string ToString() const;

	virtual const void * Addr() const;

	virtual TZ_BOOL IsWildcard() const;
	
	virtual TZ_BOOL IsBroadcast() const;

	virtual TZ_BOOL IsLoopback() const;

	virtual TZ_BOOL IsMulticast() const;

	virtual TZ_INT SetAddress(const void * bytes);

	static IPv4IPAddressImp * Parse(const std::string & addr);

private:
	struct in_addr m_addr;
};

class IPv6IPAddressImp : public IPAddressImp {

public:
	IPv6IPAddressImp();

	IPv6IPAddressImp(const void * bytes);
	
	IPv6IPAddressImp(const void * bytes, TZ_Uint32 scope);

	virtual TZ_Uint32 Size() const;

	virtual TZ_Uint32 Scope() const;

	virtual TZ_Uint32 Family() const;

	virtual std::string ToString() const;

	virtual const void * Addr() const;

	virtual TZ_BOOL IsWildcard() const;
	
	virtual TZ_BOOL IsBroadcast() const;

	virtual TZ_BOOL IsLoopback() const;

	virtual TZ_BOOL IsMulticast() const;

	virtual TZ_INT SetAddress(const void * bytes);

	static IPv6IPAddressImp * Parse(const std::string & addr);

private:
	struct in6_addr m_addr;
	TZ_Uint32 m_scope;
};

#if defined(LINUX)	// only for Linux
class UnixIPAddressImp : public IPAddressImp {

public:
	UnixIPAddressImp();

	UnixIPAddressImp(const std::string & addr);

	virtual TZ_Uint32 Size() const;

	virtual TZ_Uint32 Scope() const;

	virtual TZ_Uint32 Family() const;

	virtual std::string ToString() const;

	virtual const void * Addr() const;

	virtual TZ_BOOL IsWildcard() const;
	
	virtual TZ_BOOL IsBroadcast() const;

	virtual TZ_BOOL IsLoopback() const;

	virtual TZ_BOOL IsMulticast() const;

	virtual TZ_INT SetAddress(const void * bytes);

private:
	TZ_CHAR m_addr[108];
};
#endif

class DECLDLL IPAddress {

public:
	IPAddress();

	IPAddress(TZ_Uint32 family);

	IPAddress(const IPAddress & addr);

	explicit IPAddress(const std::string & addr, TZ_BOOL isUnix = FALSE);

	// when @size is INVALID_VALUE32, then it indicates 
	// the address is a unix socket address
	IPAddress(const void * bytes, TZ_Uint32 size);

	// just for IPv6
	IPAddress(const void * bytes, TZ_Uint32 size, TZ_Uint32 scope);

	~IPAddress();

	// returns E_OK on success, otherwise returns E_FAILED
	TZ_INT SetAddress(const std::string & addr);

	// returns E_OK on success, otherwise returns E_FAILED
	TZ_INT SetAddress(const void * bytes, TZ_Uint32 size);

	void Swap(IPAddress & addr);

	TZ_Uint32 Size() const;

	TZ_Uint32 Scope() const;

	TZ_Uint32 Family() const;

	std::string ToString() const;

	const void * Addr() const;

public:
	IPAddress & operator = (const IPAddress & addr);

	bool operator == (const IPAddress & addr) const;

	bool operator != (const IPAddress & addr) const;

	bool operator < (const IPAddress & addr) const;
	bool operator <= (const IPAddress & addr) const;
	
	bool operator > (const IPAddress & addr) const;
	bool operator >= (const IPAddress & addr) const;

public:
	// returns TRUE if the address is a wildcard (all zero) address
	TZ_BOOL IsWildcard() const;

	// 
	// for IPv4, 
	// returns TRUE if the address is a broadcast (all one) address
	// for IPv6 or UnixSocket
	// always returns FALSE
	TZ_BOOL IsBroadcast() const;

	// 
	// returns true if the address is a loopback address
	// for IPv4, the address is 127.0.0.1
	// for IPv6, the address is ::1
	// for UnixSocket, always returns FALSE
	TZ_BOOL IsLoopback() const;

	// 
	// returns true if the address is a multicast address
	// for IPv4, multicast addresses are in the 224.0.0.0 to 239.255.255.255 range
	// for IPv6, multicast addresses are in the FFxx:x:x:x:x:x:x:x range
	// for UnixSocket, always returns FALSE
	TZ_BOOL IsMulticast() const;

	// 
	// returns TRUE if the address is neither a wildcard, 
	// broadcast or multicast address
	TZ_BOOL IsUnicast() const;

private:
	IPAddressImp * m_imp;
};

// 
// inlines
//
inline TZ_Uint32 IPAddress::Size() const
{
	return m_imp->Size();
}

inline TZ_Uint32 IPAddress::Scope() const
{
	return m_imp->Scope();
}

inline TZ_Uint32 IPAddress::Family() const
{
	return m_imp->Family();
}

inline std::string IPAddress::ToString() const
{
	return m_imp->ToString();
}

inline const void * IPAddress::Addr() const
{
	return m_imp->Addr();
}

inline bool IPAddress::operator == (const IPAddress & addr) const
{
	return (this->Family() == addr.Family() && 
			this->ToString() == addr.ToString());
}

inline bool IPAddress::operator != (const IPAddress & addr) const
{
	return (this->Family() != addr.Family() ||
			this->ToString() != addr.ToString());
}

inline TZ_BOOL IPAddress::IsWildcard() const
{
	return m_imp->IsWildcard();
}

inline TZ_BOOL IPAddress::IsBroadcast() const
{
	return m_imp->IsBroadcast();
}

inline TZ_BOOL IPAddress::IsLoopback() const
{
	return m_imp->IsLoopback();
}

inline TZ_BOOL IPAddress::IsMulticast() const
{
	return m_imp->IsMulticast();
}

inline TZ_BOOL IPAddress::IsUnicast() const
{
	return (!this->IsWildcard() && !this->IsBroadcast() && !this->IsMulticast());
}

};	// namespace tzc

#endif   /* ----- #ifndef __IPADDRESS_H  ----- */

