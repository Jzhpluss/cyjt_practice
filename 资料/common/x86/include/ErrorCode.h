// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __ERRORCODE_H
#define  __ERRORCODE_H

#include "BaseTypes.h"
#include "BaseHeaders.h"

namespace tzc {

// Error Code:
// 
// |--------|--------|
//   class     code
// 
// class:
// 		01 - common error
// 		02 - epoll error
// 		... ....
//
enum __ErrorCode {

	E_OK = 0x0000,
	E_FAILED = -0x0001,		// common failed

	E_INVTYPE	= -0x1001,	// invalid type
	E_INVPARAM	= -0x1002,	// invalid parameter
	E_INVVALUE	= -0x1003,	// invalid value. eg. invalid ipaddress
	E_UNSUPPORT = -0x1004,	// unsupported implementation

	E_CREATEFAIL		= -0x2001,
	E_ADDFAIL			= -0x2002,
	E_MODIFYFAIL		= -0x2003,
	E_DELETEFAIL		= -0x2004,
	E_WAITFAIL			= -0x2005,
	E_IOEVENTEXIST		= -0x2006,
	E_IOEVENTNOTFOUND	= -0x2007,
};

std::string ErrorStringCN(TZ_Int32 errcode);
std::string ErrorStringEN(TZ_Int32 errcode);

};	// namespace tzc

#endif   /* ----- #ifndef __ERRORCODE_H  ----- */

