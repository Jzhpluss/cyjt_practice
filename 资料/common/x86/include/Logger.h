// 
// Copyright @ 2014 Hangzhou Topzen Ltd.
// Author: Tang (tang@hztopzen.com) @ 2014-12
//

#ifndef  __LOGGER_H
#define  __LOGGER_H

#include "BaseTypes.h"
#include "BaseHeaders.h"
#include "BaseCalls.h"
#include "Locks.h"
#include "Thread.h"
#include "Semaphore.h"

namespace tzc {

class DECLDLL Logger : public OSThread {

public:
	static Logger * Instance();
	static void DestroyInstance();

public:

	void Initialize(const std::string & sConfig = "./logger.config");

	void Initialize(const std::string & sModule, 
					const std::string & sLogFile, 
					const TZ_Uint32 iMaxMBytes,
					const TZ_Uint32 iMaxLines,
					const TZ_Uint32 iDebugLevel,
					const TZ_BOOL bForeground, 
					const TZ_BOOL bSyncWrite);

	const std::string & LogFilePath() const;

	TZ_Uint32 TotalLines();
	void SetLogDebugLevel(TZ_Uint32 level);

	void LogInfo(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_CHAR * format, ...);
	
	void LogWarn(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_CHAR * format, ...);
	
	void LogError(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_CHAR * format, ...);
	
	void LogAlert(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_CHAR * format, ...);
	
	void LogDebug(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_UINT iLevel, const TZ_CHAR * format, ...);

protected:
	void doLog(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_CHAR * prefix, const TZ_CHAR * format, va_list ap);

    void doLogAsync(const TZ_CHAR * file, const TZ_CHAR * func, const TZ_INT line, 
			const TZ_CHAR * prefix, const TZ_CHAR * format, va_list ap);

	void check4Seperate();

	TZ_INT touchFilePath(const std::string & sFilePath);

	TZ_INT getFileLineCount(const std::string & sFilePath);
	
	void outputLogItem(const std::string & item);

    virtual void Entry();

protected:
	Logger();
	virtual ~Logger();

private:
	TZ_BOOL m_bSyncWrite;
	TZ_BOOL m_bForeground;
	TZ_BOOL m_bInitialized;
	volatile TZ_Uint32 m_iDebugLevel;

	TZ_Uint32 m_iCurrLineIdx;
	TZ_Uint32 m_iCurrFileIdx;

	TZ_Uint32 m_iMaxBytes;
	TZ_Uint32 m_iMaxLines;
	TZ_Uint32 m_iMaxFiles;

	std::string m_sFilePath;
	std::string m_sModuleName;

	Mutex  m_mutex;
	FILE * m_fileStream;

	Semaphore m_sem;
	Mutex m_queueMutex;
	std::list<std::string> m_itemQueue;

private:
	static const std::string PREFIX_INFO;
	static const std::string PREFIX_WARN;
	static const std::string PREFIX_ERROR;
	static const std::string PREFIX_ALERT;
	static const std::string PREFIX_DEBUG;

	static const TZ_UINT MAX_LENGTH = 1000;

	static Mutex _mutex;
	static Logger * _instance;
};

};	// namespace tzc

#define POSITION __FILE__, __FUNCTION__, __LINE__

#define INITIALIZE_LOGGER_CONFIG(configurefile) \
	tzc::Logger::Instance()->Initialize(configurefile)

// 
// Notice: @level should be larger than 5 while 1 ~ 5 levels are used for
// Common inner implementation; otherwise there will be much more logs 
// output in the application.
//
#define INITIALIZE_LOGGER_NORMAL(module, file, mbytes, lines, level, forground, sync) \
	tzc::Logger::Instance()->Initialize(module, file, mbytes, lines, level, forground, sync)

#define DESTROY_Logger() tzc::Logger::DestroyInstance()

#define TotalLogLines() \
	tzc::Logger::Instance()->TotalLines()
#define TZLogSetDebugLevel(level) \
	tzc::Logger::Instance()->SetLogDebugLevel(level)

#if defined(WIN32) || defined(WINDOWS)
#define TZLogInfo(format, ...) \
	tzc::Logger::Instance()->LogInfo(POSITION, format, __VA_ARGS__)
#define TZLogWarn(format, ...) \
	tzc::Logger::Instance()->LogWarn(POSITION, format, __VA_ARGS__)
#define TZLogError(format, ...) \
	tzc::Logger::Instance()->LogError(POSITION, format, __VA_ARGS__)
#define TZLogAlert(format, ...) \
	tzc::Logger::Instance()->LogAlert(POSITION, format, __VA_ARGS__)
#define TZLogDebug(level, format, ...) \
	tzc::Logger::Instance()->LogDebug(POSITION, level, format, __VA_ARGS__)
#elif defined(LINUX)	// Linux
#define TZLogInfo(format, args...) \
	tzc::Logger::Instance()->LogInfo(POSITION, format, ##args)
#define TZLogWarn(format, args...) \
	tzc::Logger::Instance()->LogWarn(POSITION, format, ##args)
#define TZLogError(format, args...) \
	tzc::Logger::Instance()->LogError(POSITION, format, ##args)
#define TZLogAlert(format, args...) \
	tzc::Logger::Instance()->LogAlert(POSITION, format, ##args)
#define TZLogDebug(level, format, args...) \
	tzc::Logger::Instance()->LogDebug(POSITION, level, format, ##args)
#endif

#endif   /* ----- #ifndef __LOGGER_H  ----- */

