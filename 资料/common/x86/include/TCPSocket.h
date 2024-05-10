// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2015-07
//

#ifndef  __TCPSOCKET_H
#define  __TCPSOCKET_H

#include "Socket.h"

namespace tzc {

class TCPServer;

class DECLDLL TCPSocket : public Socket
{
public:
	TCPSocket(TZ_Uint32 type = STYPE_TCP);

	TCPSocket(TZ_SOCKET sock, TZ_Uint32 type);

	TCPSocket(const Socket & sock);

	virtual ~TCPSocket();

	virtual TZ_INT Bind(const SockAddress & addr);

	virtual TZ_INT Connect(const SockAddress & raddr);

	// On success, return the number of characters received. 
	// On error, -1 is returned
	virtual TZ_INT RecvBytes(TZ_BYTE * buffer, TZ_Uint32 length);

	// the following two functions have the same return value:
	// On success, return the number of characters sent. 
	// On error, -1 is returned
	virtual TZ_INT SendBytes(const TZ_BYTE * buffer, TZ_Uint32 length);

	virtual TZ_INT SendBytes(const TZ_BYTE * buffer, TZ_Uint32 length, 
			const SockAddress & raddr);

public:
	TZ_INT SetLinger(TZ_BOOL on, TZ_Uint32 seconds);

	TZ_INT GetLinger(TZ_BOOL & on, TZ_Uint32 & seconds);

	TZ_INT SetNoDelay(TZ_BOOL flag);

	TZ_BOOL GetNoDelay();

	TZ_INT SetKeepAlive(TZ_BOOL flag);

	TZ_BOOL GetKeepAlive();

	// Sends one byte of urgent data through the socket
	TZ_INT SendUrgent(TZ_BYTE byte);

	friend class TCPServer;
};

};	// namespace tzc

#endif   /* ----- #ifndef __TCPSOCKET_H  ----- */

