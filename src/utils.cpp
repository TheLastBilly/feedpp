#include "utils.h"
#include "log.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iconv.h>
#include <errno.h>
#include <pwd.h>
#include <libgen.h>
#include <sys/utsname.h>

#include <unistd.h>
#include <sstream>
#include <locale>
#include <cwchar>
#include <cstring>
#include <cstdlib>
#include <cstdarg>

#include <curl/curl.h>

#include <langinfo.h>
#include <libxml/uri.h>

#if HAVE_GCRYPT
#include <gnutls/gnutls.h>
#include <gcrypt.h>
#include <errno.h>
#include <pthread.h>
GCRY_THREAD_OPTION_PTHREAD_IMPL;
#endif

#if HAVE_OPENSSL
#include <openssl/crypto.h>
#endif

namespace feedpp {

std::string utils::absolute_url(const std::string& url, const std::string& link) {
	xmlChar * newurl = xmlBuildURI((const xmlChar *)link.c_str(), (const xmlChar *)url.c_str());
	std::string retval;
	if (newurl)
	{
		retval = (const char *)newurl;
		xmlFree(newurl);
	}
	else
	{
		retval = link;
	}
	return retval;
}

std::string utils::strprintf(const char * format, ...)
{
	if (!format)
		return std::string();

	char buffer[1024];

	va_list ap;
	va_start(ap, format);

	unsigned int len = vsnprintf(buffer, sizeof(buffer), format, ap) + 1;

	va_end(ap);
	if (len <= sizeof(buffer))
		return buffer;

	va_start(ap, format);

	char * buf = new char[len];
	vsnprintf(buf, len, format, ap);
	va_end(ap);

	std::string ret(buf);
	delete[] buf;

	return ret;
}


}
