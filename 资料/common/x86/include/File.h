// 
// Copyright @ 2015 Hangzhou Topzen Ltd.
// Author: Zeng Hanyang (zenghy@es.zju.edu.cn) @ 2015-05
//

#ifndef _FILE_H
#define _FILE_H

#include "Types.h"

namespace tzc {

class DECLDLL File {

public:
	typedef enum {

		OpenModeRead = 0x01,
		OpenModeWrite = 0x02,
		OpenModeAppend = 0x04,
		OpenModeBinary = 0x08,
		OpenModeText = 0x10, // default in stream file in windows
		OpenModeSync = 0x20

	} FileOpenMode;

	typedef enum {

		SeekPosSet = 0,
		SeekPosCur,
		SeekPosEnd

	} FileSeekPos;

#if defined(WIN32) || defined(WINDOWS)
	typedef HANDLE FileHandle;
	#define INVALID_FILE_HANDLE (INVALID_HANDLE_VALUE)
#elif defined(LINUX)
	typedef int    FileHandle;
	#define INVALID_FILE_HANDLE (-1)
#endif

protected:
	File(const std::string &);
	File(); // tmpfile

public:
	virtual ~File();

	//return 0 for success, -1 for failed
	virtual TZ_Int32 Open(TZ_Uint32 openMode = OpenModeRead | OpenModeWrite
			| OpenModeSync) = 0;

	virtual TZ_Int32 Close(void) = 0;

	// return the real Bytes, negative number for failed
	virtual TZ_Int32 Read(TZ_BYTE *, TZ_Uint32) = 0;
	virtual TZ_Int32 Write(const TZ_BYTE *, TZ_Uint32) = 0;

	// return 0 for success, -1 for failed, for stream file
	virtual TZ_Int32 ReadLine(TZ_CHAR *, TZ_Uint32) = 0;
	virtual TZ_Int32 WriteLine(const TZ_CHAR *) = 0;

	// 0 for success, -1 for failed
	virtual TZ_Int32 Seek(TZ_Int64, FileSeekPos) = 0;

	// -1 for failed, otherwise return current offset
	virtual TZ_Int64 Tell(void) = 0;

	virtual TZ_Int64 Truncate(TZ_Uint64 newSize) = 0;

	// returns zero on success, otherwise returns -1
	virtual TZ_INT Lock(TZ_BOOL shared = FALSE, TZ_BOOL blocking = FALSE) = 0;

	// returns zero on success, otherwise returns -1
	virtual TZ_INT Unlock() = 0;

	// -1 for failed, otherwise return current size
	TZ_Int64 GetFileSize(void);

	const std::string & GetFilePath() const;

	// none-zero for in the end, zero for not
	TZ_BOOL IsEndOfFile(void);

public:
	// delete file, 0 for succeed, -1 for failed
	static TZ_INT Remove(const std::string & path);

	static TZ_INT Rename(const std::string & origin, const std::string & target);

protected:
	std::string m_filePath;
	TZ_Uint32 m_openMode;

};  // end of class File

class DECLDLL PrimeFile : public File
{
public:
	PrimeFile(const std::string &);
	PrimeFile();
	virtual ~PrimeFile();

	virtual TZ_Int32 Open(TZ_Uint32 openMode = OpenModeRead | OpenModeWrite
			| OpenModeSync);

	virtual TZ_Int32 Close(void);

	virtual TZ_Int32 Read(TZ_BYTE *, TZ_Uint32);
	virtual TZ_Int32 Write(const TZ_BYTE *, TZ_Uint32);

	virtual TZ_Int32 ReadLine(TZ_CHAR *, TZ_Uint32);
	virtual TZ_Int32 WriteLine(const TZ_CHAR *);

	virtual TZ_Int32 Seek(TZ_Int64, FileSeekPos);

	virtual TZ_Int64 Truncate(TZ_Uint64 newSize);

	virtual TZ_INT Lock(TZ_BOOL shared = FALSE, TZ_BOOL blocking = FALSE);

	virtual TZ_INT Unlock();

	virtual TZ_Int64 Tell(void);

private:
#if defined(WIN32) || defined(WINDOWS)
	void GetFileAttr(DWORD & access, DWORD & attr, DWORD & flags);
#elif defined(LINUX)
	int GetIntFileMode(void);
#endif

	FileHandle m_handle;

};// end of class PrimeFile

class DECLDLL StreamFile : public File
{
public:
	StreamFile(const std::string &);
	StreamFile();
	virtual ~StreamFile();

	virtual TZ_Int32 Open(TZ_Uint32 openMode = OpenModeRead | OpenModeWrite
			| OpenModeSync);

	virtual TZ_Int32 Close(void);

	virtual TZ_Int32 Read(TZ_BYTE *, TZ_Uint32);
	virtual TZ_Int32 Write(const TZ_BYTE *, TZ_Uint32);

	virtual TZ_Int32 ReadLine(TZ_CHAR *, TZ_Uint32);
	virtual TZ_Int32 WriteLine(const TZ_CHAR *);

	virtual TZ_Int32 Seek(TZ_Int64, FileSeekPos);

	virtual TZ_Int64 Tell(void);

	virtual TZ_Int64 Truncate(TZ_Uint64 newSize);

	virtual TZ_INT Lock(TZ_BOOL shared = FALSE, TZ_BOOL blocking = FALSE);

	virtual TZ_INT Unlock();

private:
	std::string getStrFileMode(void);

	FILE * m_file;

};// end of class StreamFile

} // end of namespace tzc

#endif /*-----#ifndef _FILE_H-----*/

