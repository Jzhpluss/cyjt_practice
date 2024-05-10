#include "Types.h"
#include "BytesOrder.h"
#include "ErrorCode.h"
#include "OSTime.h"
#include "Socket.h"
#include "TCPSocket.h"
#include "TCPServer.h"
#include "UDPSocket.h"
#include "Logger.h"
#include "Thread.h"
#include "SysUtils.h"
#include "BytesOrder.h"
#include "FileConfig.h"
#include "SysUtils.h"
#include "Network.h"

using namespace std;
using namespace tzc;

class ExtraThread : public OSThread
{
public:
	ExtraThread()
	{
		m_index = 0;
		TZLogWarn("construct ExtraThread~~~");

		this->Start();
	}

	~ExtraThread()
	{
		TZLogWarn("de-construct ExtraThread~~~");
	}

private:
	virtual void Entry()
	{
		while (true)
		{
			TZLogInfo("[!!!!!] [%u] this is the thread log line, index is %u", 
					OSThread::CurrentTid(), m_index++);
			SysUtils::DelayMseconds(10);
		}
	}

private:
	TZ_Uint32 m_index;
};

vector<OSTime> timeList;

//#define TEST_LOGGER
//#define TEST_UDP_SOCKET
#define TEST_SOCKET_NUM

int main(int argc, char * argv[])
{
	INITIALIZE_LOGGER_NORMAL("test", "./test.log", 1, 100, 
			6, 1, 1);

#ifdef WIN32
	std::list<UDPSocket *> udplist;

	for (TZ_UINT idx = 0; idx < 2024; ++idx)
	{
		UDPSocket * sock = new UDPSocket();
		TZ_INT ret = sock->SelectForRead(40000);
		
		TZLogInfo("local addr is %s, socket fd is %d, ret is %d~~~", 
				sock->LocalAddress().ToString().c_str(), sock->Descriptor(), ret);

		TZ_delete(sock);
		//udplist.push_back(sock);
	}

#endif

#if 1
	ExtraThread * extraThread = new ExtraThread();

	TZ_Uint32 port = tzc::SysUtils::GetAvailPortTCP("10.1.60.68", 60000, 60500);
	if (port == 0)
	{
		TZLogWarn("get tcp avail port failed!!!");
		return -1;
	}
	else
	{
		TZLogInfo("tcp avail port: %u", port);
	}

	TZ_delete(extraThread);

#endif

#ifdef WIN32

	TZ_Uint32 idx = 0;

	while (TRUE)
	{
		TZLogInfo("this is log line %d~~~~", idx++);

		SysUtils::DelayMseconds(10);
	}

#endif	// TEST_LOGGER

#ifdef WIN32

	OSTime ttm = OSTime::Now();

	TZLogInfo("DateTime Now is [%04d-%02d-%02d %02d:%02d:%02d]",
		ttm.year, ttm.month, ttm.day,
		ttm.hour, ttm.minute, ttm.second);

#endif // TEST_TIME

#ifdef WIN32

	UDPSocket udpSocket;

	tzc::SockAddress laddr("0.0.0.0", 51321);
	udpSocket.Bind(laddr);

	TZLogInfo("udp socket local addr is %s~~~", 
			udpSocket.LocalAddress().ToString().c_str());
	
	SockAddress tempAddr("10.1.0.141", 5060);

	TZ_Uint32 iRet = udpSocket.Connect(tempAddr);
	if (iRet != 0)
	{
		TZLogWarn("Connect to the UDP socket failed: %d", errno);
		return -1;
	}
	else
	{
		TZLogInfo("Connect to the UDP socket succeed");
	}

	TZ_INT totalLen(100);

	TZ_BYTE * sendBuf = new TZ_BYTE[totalLen];

	TZ_INT pLen = udpSocket.SendBytes(sendBuf, totalLen);

	TZ_delete_a(sendBuf);

#endif // TEST_UDP_SOCKET


#ifdef WIN32
	UDPSocket sock;
	SockAddress addr("10.1.0.51", 3000);

	TZ_Uint32 count = 10;

	while (--count > 0)
	{
		TZ_BYTE buffer[16];

		sock.SendBytes(buffer, sizeof(buffer), addr);

		TZLogInfo("send 16 bytes to address %s~~~", addr.ToString().c_str());

		SysUtils::DelaySeconds(1);
	}
#endif

#ifdef WIN32
	std::string filePath = "./file.conf";
	FileConfig fc(filePath, FALSE);

	fc.Initialize();

	std::string value;

	fc.SetValue("vendor", "test");
	TZLogInfo("key = vendor, value = %s~~~", value.c_str());

	fc.GetValueContinous("soname", value);
	TZLogInfo("key = soname, value = %s~~~", value.c_str());

	fc.GetValueContinous("version", value);
	TZLogInfo("key = version, value = %s~~~", value.c_str());
	
	fc.GetValueContinous("vendor", value);
	TZLogInfo("key = vendor, value = %s~~~", value.c_str());

	fc.GetValueContinous("soname", value);
	TZLogInfo("key = soname, value = %s~~~", value.c_str());

	fc.GetValueContinous("version", value);
	TZLogInfo("key = version, value = %s~~~", value.c_str());
#endif

	return 0;
}

