/*
 * HttpMimeTypes.cpp
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#include "HttpMimeTypes.h"

namespace HTTP {
namespace SERVER {
namespace MIMETYPES {

struct mapMimeType {

	const char* _extension;
	const char* _mimeType;

} _mapMimeTypes[] = {
		  { "gif", "image/gif" },
		  { "htm", "text/html" },
		  { "html", "text/html" },
		  { "jpg", "image/jpeg" },
		  { "png", "image/png" }
};

std::string extension_to_type(const std::string& _extension ){

	for ( mapMimeType t : _mapMimeTypes ){

		if(t._extension == _extension ) {
			return t._mimeType;
		}
	}

	return "text/plain";
}

}  // namespace mimeTypes
}  // namespace server
}  // namespace http
