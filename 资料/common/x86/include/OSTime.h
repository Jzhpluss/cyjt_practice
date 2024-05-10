// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __OSTIME_H
#define  __OSTIME_H

#include "BaseTypes.h"
#include "BaseHeaders.h"

namespace tzc {

struct DECLDLL OSTime {

	TZ_Uint32	year;
	TZ_Uint32	month;
	TZ_Uint32	day;
	TZ_Uint32	hour;
	TZ_Uint32	minute;
	TZ_Uint32	second;
	TZ_Uint32	usecond;
	
	OSTime();

	//
	// 64 60     48 44  38  32  26  20          0
	//  |--|------|--|---|---|---|---|----------|
	//    R      Y  M   D   h   m   s         us
	//
	OSTime(TZ_Uint64 bt);

	//
	// "YYYY-MM-DD hh:mm:ss.usec"
	//
	OSTime(const std::string & st);

	OSTime(TZ_Uint32 syssec, TZ_Uint32 usec);

	static OSTime Now();

	static TZ_Uint64 GetOSTick();
	static TZ_Uint64 GetOSFreq();

	TZ_Uint64 ToUint64() const;
	std::string ToString(TZ_Uint32 level = 0) const;
	std::string ToStringISO() const;

	time_t Syssec() const;
	
	bool operator < (const OSTime & tt) const;
	bool operator == (const OSTime & tt) const;
	bool operator != (const OSTime & tt) const;

private:
	bool timeIsValid(void);
	bool isLeapYear(void);
};

};	// namespace tzc

#endif   /* ----- #ifndef __TIME_H  ----- */

