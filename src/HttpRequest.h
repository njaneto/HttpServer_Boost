/*
 * HttpRequest.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string.h>
#include <vector>
#include <iostream>

#include "HttpHeader.h"

namespace HTTP {
namespace SERVER {

	struct HttpRequest
	{
	  std::string method;
	  std::string uri;
	  int http_version_major;
	  int http_version_minor;
	  std::vector<HttpHeader> headers;

	};


}  // namespace server
}  // namespace http


#endif /* HTTPREQUEST_H_ */
