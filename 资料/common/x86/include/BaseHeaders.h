// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __BASEHEADERS_H
#define  __BASEHEADERS_H

#if defined(WIN32) || defined(WINDOWS)
#include <winsock2.h>
#include <windows.h>
#elif defined(LINUX)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <time.h>
#include <stdexcept>

// STL
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>

#endif   /* ----- #ifndef __BASEHEADERS_H  ----- */

