#ifndef _FILECONFIG_H
#define _FILECONFIG_H

#include "File.h"

namespace tzc {

class DECLDLL FileConfig
{
public:
	FileConfig(const std::string & filePath, TZ_BOOL readonly = TRUE);
	~FileConfig();

	TZ_INT Initialize();

	// seek to begin of the file befor searching for @key
	TZ_INT GetValue(const std::string & key, std::string & value);
	TZ_INT GetValueContinous(const std::string & key, std::string & value);
	
	TZ_INT SetValue(const std::string & key, const std::string & value);


private:
	TZ_BOOL m_readonly;

	File * m_file;
};

}	// end of namespace tzc

#endif /*-----#ifndef _FILECONFIG_H-----*/

