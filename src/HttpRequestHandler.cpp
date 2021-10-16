/*
 * httpRequestHandler.cpp
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#include "HttpRequestHandler.h"

#include <fstream>
#include <sstream>
#include <string>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpMimeTypes.h"

namespace HTTP {
namespace SERVER {

//-----------------------------------------------------------------------------------------
HttpRequestHandler::HttpRequestHandler( const std::string& _docRoot )
	: docRoot( _docRoot )
{}

//-----------------------------------------------------------------------------------------
void HttpRequestHandler::handlerRequest( const HttpRequest& _request, HttpResponse& _response )
{


	std::cerr << "HttpRequestHandler::handlerRequest -> " << __LINE__<< " _request.method -> " << _request.method << "\n";


/*
	std::string request_path;
	if ( ! url_decode( _request.uri , request_path ) ){
		std::cerr << "HttpRequestHandler::handlerRequest -> " << __LINE__<< "\n";
		_response = HttpResponse::stock_response( HttpResponse::bad_request );
		return;
	}

	std::cerr << "HttpRequestHandler::handlerRequest -> " << __LINE__<< " _request.uri -> " << _request.uri << "\n";
	std::cerr << "HttpRequestHandler::handlerRequest -> " << __LINE__<< " request_path -> " << request_path << "\n";

	if ( request_path.empty()
			|| request_path[0] != '/'
			|| request_path.find("..") != std::string::npos )
	{
		_response = HttpResponse::stock_response( HttpResponse::bad_request );
	}

	if ( request_path[request_path.size() - 1] == '/' ){
		request_path += "index.html";
	}

	std::size_t last_slash_pos = request_path.find_last_of("/");
	std::size_t last_dot_pos = request_path.find_last_of(".");
	std::string extension;

	if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
	    extension = request_path.substr(last_dot_pos + 1);
	}

	std::string full_path = docRoot + request_path;
	std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	if (!is)
	{
		_response = HttpResponse::stock_response(HttpResponse::not_found);
		return;
	}
*/

	_response.status = HttpResponse::ok;
	_response.content = "chegou bb ---------------------------\n msg entrada -> ";
	_response.headers.resize(2);
	_response.headers[0].name = "Content-Length";
	_response.headers[0].value = std::to_string(_response.content.size());
	_response.headers[1].name = "Content-Type";
	_response.headers[1].value = MIMETYPES::extension_to_type("");



/*
	char buf[4096];
	while (is.read(buf, sizeof(buf)).gcount() > 0)
	{
		_response.content.append(buf, is.gcount());
		_response.headers.resize(2);
		_response.headers[0].name = "Content-Length";
		_response.headers[0].value = std::to_string(_response.content.size());
		_response.headers[1].name = "Content-Type";
		_response.headers[1].value = MIMETYPES::extension_to_type( extension );

	}
*/

}

/*
bool HttpRequestHandler::url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}
*/

}  // namespace server
}  // namespace http
