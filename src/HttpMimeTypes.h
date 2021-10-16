/*
 * HttpMimeTypes.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPMIMETYPES_H_
#define HTTPMIMETYPES_H_

#include <string.h>
#include <iostream>

namespace HTTP {
	namespace SERVER {
		namespace MIMETYPES {

		/*
		 * O MIME type � o mecanismo para dizer ao cliente a variedade de documentos transmitidos:
		 * a extens�o de um nome de arquivo n�o tem significado na web. Portanto,
		 * � importante que o servidor esteja configurado corretamente, de modo que o MIME-type
		 * correto seja transmitido com cada documento. Os navegadores costumam usar o MIME-type
		 * para determinar qual a��o usar como padr�o para fazer quando um recurso � obtido.
		 *
		 * https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Basico_sobre_HTTP/MIME_types
		 * */

			std::string extension_to_type(const std::string& _extension );

		}  // namespace mimeTypes
	}  // namespace server
}  // namespace http


#endif /* HTTPMIMETYPES_H_ */
