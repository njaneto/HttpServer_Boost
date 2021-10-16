/*
 * HttpConnectionManager.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPCONNECTIONMANAGER_H_
#define HTTPCONNECTIONMANAGER_H_

#include <set>
#include "HttpConnection.h"

namespace HTTP {
namespace SERVER {

class HttpConnectionManager {
public:
	HttpConnectionManager( const HttpConnectionManager&) = delete;
	HttpConnectionManager& operator=( const HttpConnectionManager&) = delete;

	HttpConnectionManager();

	void start( httpConnection_ptr _ptr );
	void stop( httpConnection_ptr _ptr );

	void stop_all();
private:

	std::set<httpConnection_ptr> connection_;
};


}  // namespace server
}  // namespace http


#endif /* HTTPCONNECTIONMANAGER_H_ */
