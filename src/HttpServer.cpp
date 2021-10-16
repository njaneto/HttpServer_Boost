/*
 * HttpServer.cpp
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#include "HttpServer.h"
#include <signal.h>
#include <utility>

namespace HTTP {
namespace SERVER {
//-------------------------------------------------------------------
HttpServer::HttpServer( const std::string& address, const std::string& port, const std::string& docRoot )
	: io_context( 1 ),
	  signals( io_context ),
	  acceptor( io_context ),
	  httpConnectionManager(),
	  httpRequestHandler( docRoot )

{
	// Registre-se para manipular os sinais que indicam quando o servidor deve sair.
	// É seguro registrar-se para o mesmo sinal várias vezes em um programa,
	// desde que todo o registro para o sinal especificado seja feito através do Asio.	signals.add(SIGINT);
	signals.add(SIGTERM);
	#if defined(SIGQUIT)
	signals.add(SIGQUIT);
	#endif

	do_await_stop();

	// Abra o aceitador com a opção de reutilizar o endereço (ou seja, SO_REUSEADDR).

	boost::asio::ip::tcp::resolver resolver( io_context );
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( address, port ).begin()
			;
	acceptor.open(endpoint.protocol());
	acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor.bind(endpoint);
	acceptor.listen();

	do_accept();
}
//-------------------------------------------------------------------
void HttpServer::run()
{
	// A chamada io_context :: run () será bloqueada até todas as operações assíncronas
	// terminou. Enquanto o servidor está em execução, sempre há pelo menos um
	// operação assíncrona pendente: a chamada de aceitação assíncrona em espera
	// para novas conexões de entrada.

	io_context.run();
}
//-------------------------------------------------------------------
void HttpServer::do_accept()
{
	acceptor.async_accept(
		[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
		{
		// Verifique se o servidor foi parado por um sinal antes deste
		// manipulador de conclusão teve a chance de executar.

			if (!acceptor.is_open())
			{
				return;
			}

			if (!ec)
			{
				httpConnectionManager.start(std::make_shared<HttpConnection>(
				std::move(socket), httpConnectionManager, httpRequestHandler ));
			}
			do_accept();
		});
}
//-------------------------------------------------------------------
void HttpServer::do_await_stop()
{
	signals.async_wait(
		[this](boost::system::error_code , int )
		{
			// O servidor é parado cancelando todas as assinaturas assíncronas pendentes
			// operações. Depois que todas as operações terminarem, io_context :: run ()
			// a chamada será encerrada.
			acceptor.close();
			httpConnectionManager.stop_all();
		});
}



}  // namespace server
}  // namespace http

