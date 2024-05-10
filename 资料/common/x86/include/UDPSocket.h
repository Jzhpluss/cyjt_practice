// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2015-07
//

#ifndef  __UDPSOCKET_H
#define  __UDPSOCKET_H

#include "Socket.h"

namespace tzc {

class DECLDLL UDPSocket : public Socket
{
public:
	UDPSocket(TZ_Uint32 type = STYPE_UDP);

	UDPSocket(const Socket & sock);

	virtual ~UDPSocket();

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

	virtual SockAddress PeerAddress() const;

public:
	TZ_INT SetBroadcast(TZ_BOOL on);

	TZ_BOOL GetBroadcast();

private:
	SockAddress m_raddr;
};

// 
// inlines
//
inline SockAddress UDPSocket::PeerAddress() const
{
	return m_raddr;
}

};	// namespace tzc

#endif   /* ----- #ifndef __UDPSOCKET_H  ----- */

