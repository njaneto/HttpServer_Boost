/*
 * HttpConnection.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPCONNECTION_H_
#define HTTPCONNECTION_H_

#include <array>
#include <memory>
#include <boost/asio.hpp>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpRequestHandler.h"
#include "HttpRequestParser.h"

namespace HTTP {
namespace SERVER {

class HttpConnectionManager;

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	HttpConnection(const HttpConnection&) = delete;
	HttpConnection& operator=(const HttpConnection&) = delete;

	//Construct a connection with the given socket.
	explicit HttpConnection(boost::asio::ip::tcp::socket socket, HttpConnectionManager& manager, HttpRequestHandler& handler );

	void start();
	void stop();

private:

	  void do_read();  /// Perform an asynchronous read operation.
	  void do_write();  /// Perform an asynchronous write operation.

	  boost::asio::ip::tcp::socket _socket; 	  			   /// Socket for the connection.
	  HttpConnectionManager& httpConnectionManager; 	   /// The manager for this connection.
	  HttpRequestHandler& httpRequestHandler; 	  		   /// The handler used to process the incoming request.

	  std::array<char, 8192> buffer; 					   /// Buffer for incoming data.

	  HttpRequest request; 								   /// The incoming request.
	  HttpRequestParser httpRequestParser; 				   /// The parser for the incoming request.;
	  HttpResponse response;							   /// The reply to be sent back to the client.;


};

	typedef std::shared_ptr<HttpConnection> httpConnection_ptr;

}  // namespace server
}  // namespace http


#endif /* HTTPCONNECTION_H_ */
