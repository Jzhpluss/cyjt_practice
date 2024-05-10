// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2015-07
//

#ifndef  __TCPSERVER_H
#define  __TCPSERVER_H

#include "Socket.h"

namespace tzc {

class TCPSocket;

class DECLDLL TCPServer : public Socket
{
public:
	TCPServer(TZ_Uint32 type = STYPE_TCPS);

	virtual ~TCPServer();

	virtual TZ_INT Bind(const SockAddress & addr);

	virtual TZ_INT Connect(const SockAddress & raddr);
	
	virtual TZ_INT RecvBytes(TZ_BYTE * buffer, TZ_Uint32 length);
	
	virtual TZ_INT SendBytes(const TZ_BYTE * buffer, TZ_Uint32 length);

	// the socket type must be UDP or UNIX_UDP
	virtual TZ_INT SendBytes(const TZ_BYTE * buffer, TZ_Uint32 length, 
			const SockAddress & raddr);

public:
	TZ_INT Listen(TZ_Uint32 backlog);

	TCPSocket * Accept(SockAddress & raddr);

private:
	TCPServer(const Socket & sock);

	TCPServer & operator = (const Socket & sock);
};

};	// namespace tzc

#endif   /* ----- #ifndef __TCPSERVER_H  ----- */


