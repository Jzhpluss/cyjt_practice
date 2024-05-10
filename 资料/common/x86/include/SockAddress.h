// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2015-07
//

#ifndef  __SOCKADDRESS_H
#define  __SOCKADDRESS_H

#include "IPAddress.h"

#if defined(WIN32) || defined(WINDOWS)
typedef SOCKET		TZ_SOCKET;
typedef int			TZ_SOCKLEN;
#elif defined(LINUX)
typedef int			TZ_SOCKET;
typedef socklen_t	TZ_SOCKLEN;
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET	(-1)
#endif

namespace tzc {

class SockAddressImp {

public:
	virtual IPAddress Host() const = 0;

	virtual TZ_Uint16 Port() const = 0;

	virtual TZ_SOCKLEN Size() const = 0;

	virtual TZ_Uint32 Family() const = 0;

	virtual int SinFamily() const = 0;

	virtual const struct sockaddr * Addr() const = 0;

	virtual ~SockAddressImp()
	{
		tzc::UninitOSNetwork();
	}

protected:
	SockAddressImp()
	{
		tzc::InitOSNetwork();
	}

private:
	SockAddressImp(const SockAddressImp &);
	SockAddressImp & operator = (const SockAddressImp &);
};

class IPv4SockAddressImp : public SockAddressImp {

public:
	IPv4SockAddressImp();

	IPv4SockAddressImp(const struct sockaddr_in * addr);

	IPv4SockAddressImp(const void * addr, TZ_Uint16 port);

	virtual IPAddress Host() const;

	virtual TZ_Uint16 Port() const;

	virtual TZ_SOCKLEN Size() const;

	virtual TZ_Uint32 Family() const;

	virtual int SinFamily() const;

	virtual const struct sockaddr * Addr() const;

private:
	struct sockaddr_in m_addr;
};

class IPv6SockAddressImp : public SockAddressImp {

public:
	IPv6SockAddressImp(const struct sockaddr_in6 * addr);

	IPv6SockAddressImp(const void * addr, TZ_Uint16 port);

	IPv6SockAddressImp(const void * addr, TZ_Uint16 port, TZ_Uint32 scope);
	
	virtual IPAddress Host() const;

	virtual TZ_Uint16 Port() const;

	virtual TZ_SOCKLEN Size() const;

	virtual TZ_Uint32 Family() const;

	virtual int SinFamily() const;

	virtual const struct sockaddr * Addr() const;

private:
	struct sockaddr_in6 m_addr;
};

#if defined(LINUX)
class UnixSockAddressImp : public SockAddressImp {

public:
	UnixSockAddressImp();

	UnixSockAddressImp(const struct sockaddr_un * addr);
	
	UnixSockAddressImp(const std::string & addr);

	virtual IPAddress Host() const;

	virtual TZ_Uint16 Port() const;

	virtual TZ_SOCKLEN Size() const;

	virtual TZ_Uint32 Family() const;

	virtual int SinFamily() const;

	virtual const struct sockaddr * Addr() const;

private:
	struct sockaddr_un m_addr;
};
#endif

class DECLDLL SockAddress {

public:
	enum {

		MAX_ADDRESS_SIZE = sizeof(struct sockaddr_storage)
	};

public:
	// default, IPv4, INADDR_ANY + random port
	SockAddress();

	// IPv4, INADDR_ANY
	SockAddress(TZ_Uint16 port);

	SockAddress(const IPAddress & host, TZ_Uint16 port);

	SockAddress(const std::string & host, TZ_Uint16 port);

	SockAddress(const SockAddress & addr);

	SockAddress(const struct sockaddr * addr, TZ_SOCKLEN size);

#if defined(LINUX)
	// just only for unix socket address 
	SockAddress(const std::string & unixPath);
#endif

	~SockAddress();

	SockAddress & operator = (const SockAddress & addr);

	void Swap(SockAddress & addr);

	IPAddress Host() const;

	TZ_Uint16 Port() const;

	TZ_SOCKLEN Size() const;

	TZ_Uint32 Family() const;

	int SinFamily() const;

	const struct sockaddr * Addr() const;

	std::string ToString() const;

	bool operator == (const SockAddress & addr) const;
	bool operator != (const SockAddress & addr) const;

	bool operator < (const SockAddress & addr) const;
	bool operator <= (const SockAddress & addr) const;
	
	bool operator > (const SockAddress & addr) const;
	bool operator >= (const SockAddress & addr) const;

private:
	SockAddressImp * m_imp;
};

// 
// inlines
//
inline TZ_Uint32 SockAddress::Family() const
{
	return m_imp->Family();
}

inline int SockAddress::SinFamily() const
{
	return m_imp->SinFamily();
}

inline IPAddress SockAddress::Host() const
{
	return m_imp->Host();
}

inline TZ_Uint16 SockAddress::Port() const
{
	return m_imp->Port();
}

inline TZ_SOCKLEN SockAddress::Size() const
{
	return m_imp->Size();
}

inline const struct sockaddr * SockAddress::Addr() const
{
	return m_imp->Addr();
}

inline bool SockAddress::operator == (const SockAddress & addr) const
{
	return this->Host() == addr.Host() && this->Port() == addr.Port();
}

inline bool SockAddress::operator != (const SockAddress & addr) const
{
	return this->Host() != addr.Host() || this->Port() != addr.Port();
}

};	// namespace tzc

#endif   /* ----- #ifndef __SOCKADDRESS_H  ----- */

