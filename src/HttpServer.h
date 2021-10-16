/*
 * HttpServer.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <string>

#include "HttpConnection.h"
#include "HttpConnectionManager.h"
#include "HttpRequestHandler.h"


namespace HTTP {
namespace SERVER {


class HttpServer {
public:
	HttpServer( const HttpServer&) = delete;
	HttpServer& operator=(HttpServer&) = delete;

	explicit HttpServer( const std::string& address, const std::string& port, const std::string& docRoot );

	void run();

private:

	void do_accept(); /// Perform an asynchronous accept operation.
	void do_await_stop(); /// Wait for a request to stop the server.

	boost::asio::io_context io_context; /// The io_context used to perform asynchronous operations.
	boost::asio::signal_set signals; /// The signal_set is used to register for process termination notifications.
	boost::asio::ip::tcp::acceptor acceptor; /// Acceptor used to listen for incoming connections.
	HttpConnectionManager httpConnectionManager; /// The connection manager which owns all live connections.
	HttpRequestHandler httpRequestHandler; /// The handler for all incoming requests.
};


}  // namespace server
}  // namespace http


#endif /* HTTPSERVER_H_ */
