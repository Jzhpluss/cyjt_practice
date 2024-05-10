// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __BASECALLS_H
#define  __BASECALLS_H

#define TZ_free(ptr) \
	do { if ( ptr ) { free(ptr); ptr = NULL; } } while (0)

#define TZ_delete(ptr) \
	do { if ( ptr ) { delete ptr; ptr = NULL; } } while (0)
#define TZ_delete_a(ptr) \
	do { if ( ptr ) { delete [] ptr; ptr = NULL; } } while (0)

#if defined(WIN32) || defined(WINDOWS)	// Windows

#define UNLINK(a)					_unlink(a)
#define STRNCPY(a, b, c)			strcpy_s(a, c, b)
#define SNPRINTF					_snprintf

#elif defined(LINUX)	// Linux

#define UNLINK(a)					unlink(a)
#define STRNCPY(a, b, c)			strncpy(a, b, c)
#define SNPRINTF					snprintf

#endif

#endif   /* ----- #ifndef __BASECALLS_H  ----- */

