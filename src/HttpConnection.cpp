/*
 * HttpConnection.cpp
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#include "HttpConnection.h"
#include "HttpConnectionManager.h"

#include <utility>
#include <vector>


namespace HTTP {
namespace SERVER {
//-----------------------------------------------------------------
HttpConnection::HttpConnection( boost::asio::ip::tcp::socket _socket, HttpConnectionManager& manager, HttpRequestHandler& handler )
	:_socket(std::move( _socket )),httpConnectionManager( manager ), httpRequestHandler( handler )
{}
//-----------------------------------------------------------------
void HttpConnection::start()
{
	do_read();
}
//-----------------------------------------------------------------
void HttpConnection::stop()
{
	_socket.close();
}
//-----------------------------------------------------------------
void HttpConnection::do_read()
{

	auto self( shared_from_this() );
	_socket.async_read_some(boost::asio::buffer(buffer),
		[this, self](boost::system::error_code ec, std::size_t bytes_transferred )
		{
			 if(!ec)
			 {

				 HttpRequestParser::resultType result;
				 std::tie( result, std::ignore ) = httpRequestParser.parse( request, buffer.data(), buffer.data() + bytes_transferred );

				 if( result == HttpRequestParser::good )
				 {
					 httpRequestHandler.handlerRequest( request, response );
			         do_write();
				 }
				 else if ( result == HttpRequestParser::bad )
				 {
					 response = HttpResponse::stock_response( HttpResponse::bad_request );
					 std::cerr << "HttpConnection::do_read -> " << __LINE__ << "\n";

			         do_write();
				 }
				 else
				 {
					 do_read();
				 }
			 }
			 else if ( ec != boost::asio::error::operation_aborted )
			 {
				 httpConnectionManager.stop( shared_from_this() );
			 }
		});
}
//-----------------------------------------------------------------
void HttpConnection::do_write()
{
	  auto self(shared_from_this());
	  boost::asio::async_write(_socket, response.to_buffers(),
	      [this, self](boost::system::error_code ec, std::size_t)
	      {
	        if (!ec)
	        {
	          // Initiate graceful connection closure.
	          boost::system::error_code ignored_ec;
	          _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,ignored_ec);
	        }

	        if (ec != boost::asio::error::operation_aborted)
	        {
	        	httpConnectionManager.stop( shared_from_this() );
	        }
	      });
}

}  // namespace server
}  // namespace http


