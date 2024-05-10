// 
// Copyright @ 2020 Hangzhou Topzen Ltd.
// Author: Huchengzhi (huchengzhi@hztopzen.com) @ 2020-05
//

#ifndef __EX_HEADERS_H
#define __EX_HEADERS_H

#include "BaseHeaders.h"

template<class T>
using SPtr = std::shared_ptr<T>;

template<class T>
using UPtr = std::unique_ptr<T>;

#endif