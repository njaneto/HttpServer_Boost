/*
 * HttpConnectionManager.cpp
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#include "HttpConnectionManager.h"

namespace HTTP {
namespace SERVER {

//------------------------------------------------------------
HttpConnectionManager::HttpConnectionManager(){}
//------------------------------------------------------------
void HttpConnectionManager::start( httpConnection_ptr _ptr ){

	connection_.insert( _ptr );
	_ptr->start();

}
//------------------------------------------------------------
void HttpConnectionManager::stop( httpConnection_ptr _ptr ){

	connection_.insert( _ptr );
	_ptr->stop();

}
//------------------------------------------------------------
void HttpConnectionManager::stop_all(){

	for( auto c: connection_ )
		c->stop();
	connection_.clear();
}

}  // namespace server
}  // namespace http
