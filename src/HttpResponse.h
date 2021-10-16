/*
 * httpResponse.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <string.h>
#include <vector>
#include <iostream>

#include "HttpHeader.h"
#include <boost/asio.hpp>

namespace HTTP {
namespace SERVER {

struct HttpResponse
{
  enum statusType
  {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  } status;

  std::vector<HttpHeader> headers;
  std::string content;
  std::vector<boost::asio::const_buffer> to_buffers();
  static HttpResponse stock_response(statusType status);

};

}  // namespace server
}  // namespace http


#endif /* HTTPRESPONSE_H_ */
