#ifndef _UTIL_H
#define _UTIL_H

#include <vector>
#include <cstring>
#include <string>      // due to a bug in Xcode
#include <stdexcept>

#include <curl/curl.h>
#include <libxml/parser.h>

namespace feedpp {


// wrapped curl handle for exception safety and so on
// see also: https://github.com/gsauthof/ccurl
class curl_handle {
	private:
		CURL *h;
		curl_handle(const curl_handle &);
		curl_handle &operator=(const curl_handle &);
	public:
		curl_handle()
			: h(0) {
			h = curl_easy_init();
			if (!h)
				throw std::runtime_error("Can't obtain curl handle");
		}
		~curl_handle() {
			curl_easy_cleanup(h);
		}
		CURL *ptr() {
			return h;
		}
};

class utils {
	public:
		static std::string absolute_url(const std::string& url, const std::string& link);

		static std::string strprintf(const char * format, ...);

};

}

#endif /*UTIL_H_*/
