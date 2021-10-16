/*
 * httpRequestHandler.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPREQUESTHANDLER_H_
#define HTTPREQUESTHANDLER_H_

#include <string.h>
#include <iostream>

namespace HTTP {
namespace SERVER {

struct HttpRequest;
struct HttpResponse;

class HttpRequestHandler
{
public:
	HttpRequestHandler( const HttpRequestHandler& ) = delete;
	HttpRequestHandler& operator=( const HttpRequestHandler& ) = delete;

	explicit HttpRequestHandler( const std::string& _docRoot );
	void handlerRequest( const HttpRequest& _request, HttpResponse& _response );

private:
	std::string docRoot;

	static bool url_decode(const std::string& in, std::string& out);
};


}  // namespace server
}  // namespace http



#endif /* HTTPREQUESTHANDLER_H_ */
