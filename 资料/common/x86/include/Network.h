// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __NETWORK_H
#define  __NETWORK_H

#include "IPAddress.h"

#if defined(LINUX)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace tzc {

struct Route {

	Route(): 
		ages(0), flags(0)
	{
		// Nothing
	}

	Route & operator=(const Route & right);

	IPAddress destination;
	IPAddress netmask;
	IPAddress gateway;		// Next HOP
	IPAddress NICAddr;
	
	TZ_ULONG ages;		// in seconds
	TZ_ULONG flags;	// U,G,H,D...
};

//
// inlines
//
inline Route & Route::operator=(const Route & right)
{
	this->destination = right.destination;
	this->netmask = right.netmask;
	this->gateway = right.gateway;
	this->NICAddr = right.NICAddr;
	this->ages = right.ages;
	this->flags = right.flags;

	return *this;
}

inline bool operator==(const Route & route1, const Route & route2)
{
	return (route1.destination == route2.destination);
}

inline bool operator!=(const Route & route1, const Route & route2)
{
	return !(route1 == route2);
}

struct NICInfo {

	NICInfo(): iNICIndex(0), 
				eNICType(NIC_TYPE_UNKNOW)
	{
		// Nothing
	}

	enum __NIC_TYPE {

		NIC_TYPE_LO,
		NIC_TYPE_VIR,
		NIC_TYPE_ETH,

		NIC_TYPE_UNKNOW
	};

	NICInfo & operator=(const NICInfo & right);

	IPAddress broadcast;
	IPAddress ipaddr;
	IPAddress netmask;
	
	TZ_ULONG iNICIndex;
	TZ_ULONG eNICType;

	std::string	  sNICName;
	std::string	  sPhyAddr;
};

//
// inlines
//
inline NICInfo & NICInfo::operator=(const NICInfo & right)
{
	this->broadcast = right.broadcast;
	this->ipaddr = right.ipaddr;
	this->netmask = right.netmask;
	this->iNICIndex = right.iNICIndex;
	this->eNICType = right.eNICType;
	this->sNICName = right.sNICName;
	this->sPhyAddr = right.sPhyAddr;

	return *this;
}

inline bool operator==(const NICInfo & nic1, const NICInfo & nic2)
{
	return (nic1.ipaddr == nic2.ipaddr);
}

inline bool operator!=(const NICInfo & nic1, const NICInfo & nic2)
{
	return !(nic1 == nic2);
}

class DECLDLL RouteTable {

public:
	RouteTable();
	~RouteTable();

	void AddRoute(const Route & route);
	void DelRoute(const Route & route);

	size_t GetTableSize() const;

	Route & operator[] (const size_t index);
	const Route & operator[] (const size_t index) const;

private:
	std::vector<Route> m_routeTable;
};

class DECLDLL NICsTable {

public:
	NICsTable();
	~NICsTable();

	void AddNICInfo(const NICInfo & nic);
	void DelNICInfo(const NICInfo & nic);

	size_t GetTableSize() const;

	NICInfo & operator[] (const size_t index);
	const NICInfo & operator[] (const size_t index) const;

private:
	std::vector<NICInfo> m_NICInfoTable;
};

}	// namespace tzc

#endif   /* ----- #ifndef __NETWORK_H  ----- */

