/*
 * HttpHeader.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPHEADER_H_
#define HTTPHEADER_H_

#include <string.h>
#include <iostream>

namespace HTTP {
namespace SERVER {

	struct HttpHeader {
		std::string name;
		std::string value;
	};

}  // namespace server
}  // namespace http


#endif /* HTTPHEADER_H_ */
