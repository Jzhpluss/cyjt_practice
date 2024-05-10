// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __SYSUTILS_H
#define  __SYSUTILS_H

#include "BaseTypes.h"
#include "BaseHeaders.h"
#include "Network.h"
#include "SockAddress.h"
#include "Locks.h"

namespace tzc {

// process schedule policy
enum __POLICY {

	POLICY_OTHER = SCHED_OTHER,
	POLICY_FIFO = SCHED_FIFO,
	POLICY_RR = SCHED_RR,

	DEFAULT_POLICY = POLICY_OTHER
};  

// process schedule priority
enum __PRIORITY {

	PRIO_LOWEST,
	PRIO_LOW,
	PRIO_NORMAL,
	PRIO_HIGHEST,
	PRIO_HIGH,

	DEFAULT_PRIO = PRIO_NORMAL
};  

// thread privacy stack size
enum __STACKSIZE {

	STACK_MIN = (16 << 10),
	STACK_NORMAL = (2 << 20),
	STACK_MAX = (16 << 20),

	DEFAULT_STACKSIZE = STACK_NORMAL
}; 

class DECLDLL SysUtils {

private:
	SysUtils();
	~SysUtils();

public:
	static TZ_Int32 GetOSMinPriority(TZ_Int32 policy = POLICY_OTHER);
	static TZ_Int32 GetOSMaxPriority(TZ_Int32 policy = POLICY_OTHER);

	static TZ_Int32 MapPriority(TZ_Int32 prio, TZ_Int32 policy);
	static TZ_Int32 ReverseMapPriority(TZ_Int32 prio, TZ_Int32 policy);

	static TZ_Int32 GetCPUNumber();
	static TZ_Int32 InvalidCPU(const TZ_Int32 iIndex);

	static TZ_Int32 DelaySeconds(const TZ_Int32 iCount);
	static TZ_Int32 DelayMseconds(const TZ_Int32 iCount);
	static TZ_Int32 DelayUseconds(const TZ_Int32 iCount);

	static TZ_Int32 GetSysRouteTable(RouteTable & routeTable);
	static TZ_Int32 GetSysNICsTable(NICsTable & NICsTable);

	static TZ_BOOL IsLinkFile(const std::string & sPath);
	static TZ_BOOL IsDeviceFile(const std::string & sPath);
	static TZ_BOOL IsHiddenFile(const std::string & sPath);
	static TZ_BOOL IsDirectoryFile(const std::string & sPath);

	// return 0 if failed
	static TZ_Uint16 GetAvailPortTCP(const TZ_CHAR * szIPAddr, 
		const TZ_Uint16 iBegin = 0, const TZ_Uint16 iEnd = 0);
	static TZ_Uint16 GetAvailPortUDP(const TZ_CHAR * szIPAddr, 
		const TZ_Uint16 iBegin = 0, const TZ_Uint16 iEnd = 0);

	static TZ_DLLHD LoadLibrary(const std::string & libpath);
	static TZ_PVOID GetSymbol(TZ_DLLHD dllhd, const std::string & symbol);
	static void FreeLibrary(TZ_DLLHD dllhd);

	static TZ_INT ForkDaemon();

private:
	// return 0 if failed
	static TZ_Uint16 getAvailPort(TZ_SOCKET iSock, 
		const TZ_CHAR * szIPAddr,
		const TZ_Uint16 iBegin, const TZ_Uint16 iEnd);

	static TZ_Int32 getNICAddrInfo(const TZ_ULONG & iIndex, 
		IPAddress & ipaddr, IPAddress & netmask, IPAddress & broadcast);
	static TZ_Int32 getNICAddrInfo(const std::string & sNICName, 
		IPAddress & ipaddr, IPAddress & netmask, IPAddress & broadcast);

	// ...

private:
	static Mutex m_portMutex;
};

}	// namespace tzc

#endif   /* ----- #ifndef __SYSUTILS_H  ----- */

