#ifndef  __MD5_H
#define  __MD5_H

#include "Types.h"

namespace tzc {

class DECLDLL MD5 {

public:
	MD5();
	MD5(const std::string & str);
	MD5(const void * bytes, TZ_Uint32 length);
	~MD5();

public:
	void Reset();

	// append data to current context
	void Append(const std::string & str);
	void Append(const void * bytes, TZ_Uint32 length);

	const TZ_BYTE * Digest();

	std::string ToString();

private:
	void append(const TZ_BYTE * bytes, TZ_Uint32 length);

	void final();

	void md5Transform(void);

	std::string bytes2HexString(const TZ_BYTE * input, TZ_Uint32 length) const;

private:
	TZ_Uint32 m_buf[4];
	TZ_Uint32 m_bytes[2];
	TZ_Uint32 m_in[16];

	TZ_BYTE m_digest[16];	// message digest

	TZ_BOOL m_finished;

private:
	static const TZ_CHAR HEX[16];

private:
	MD5(const MD5 &);
	MD5 & operator = (const MD5 &);
};

};	// namespace tzc

#endif   /* ----- #ifndef __MD5_H  ----- */

