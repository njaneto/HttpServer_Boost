/*
 * HttpRequestParser.h
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#ifndef HTTPREQUESTPARSER_H_
#define HTTPREQUESTPARSER_H_

#include <tuple>

namespace HTTP {
namespace SERVER {

struct HttpRequest;

class HttpRequestParser {
public:
	HttpRequestParser();

	void reset();

	enum resultType {
		good,
		bad,
		indeterminate
	};

	template <typename InputIterator>
	std::tuple<resultType, InputIterator> parse(HttpRequest& req,
	  InputIterator begin, InputIterator end)
		{
			while (begin != end)
			{
				resultType result = consume(req, *begin++);
			  if (result == good || result == bad)
				return std::make_tuple(result, begin);
			}
		return std::make_tuple(indeterminate, begin);
	}
private:

	resultType consume(HttpRequest& _request, char input); /// Handle the next character of input.

	static bool is_char(int c); /// Check if a byte is an HTTP character.
	static bool is_ctl(int c); /// Check if a byte is an HTTP control character.
	static bool is_tspecial(int c); /// Check if a byte is defined as an HTTP tspecial character.
	static bool is_digit(int c); /// Check if a byte is a digit.

	enum State
	{
		method_start,
		method,
		uri,
		http_version_h,
		http_version_t_1,
		http_version_t_2,
		http_version_p,
		http_version_slash,
		http_version_major_start,
		http_version_major,
		http_version_minor_start,
		http_version_minor,
		expecting_newline_1,
		header_line_start,
		header_lws,
		header_name,
		space_before_header_value,
		header_value,
		expecting_newline_2,
		expecting_newline_3
	} state;

};

}  // namespace server
}  // namespace http

#endif /* HTTPREQUESTPARSER_H_ */
