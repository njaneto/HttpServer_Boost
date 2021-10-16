/*
 * HttpRequestParser.cpp
 *
 *  Created on: 8 de jan de 2020
 *      Author: njaneto
 */

#include "HttpRequestParser.h"
#include "HttpRequest.h"

namespace HTTP {
namespace SERVER {
//--------------------------------------------------
HttpRequestParser::HttpRequestParser() : state( method_start )
{}
//--------------------------------------------------
void HttpRequestParser::reset()
{
	state = method_start;
}
//--------------------------------------------------
HttpRequestParser::resultType HttpRequestParser::consume( HttpRequest& _request, char input )
{
	if ( input != '\n' ){
		_request.method.push_back(input);
		return indeterminate;
	}

	return good;

	switch ( state )
	{
		case method_start:
			if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				state = method;
				_request.method.push_back(input);
				return indeterminate;
			}

		case method:
			if (input == ' ')
			{
				state = uri;
				return indeterminate;
			}
			else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				_request.method.push_back(input);
				return indeterminate;
			}

		case uri:
			if (input == ' ')
			{
				state = http_version_h;
				return indeterminate;
			}
			else if (is_ctl(input))
			{
				return bad;
			}
			else
			{
				_request.uri.push_back(input);
				return indeterminate;
			}

		case http_version_h:
			if (input == 'H')
			{
				state = http_version_t_1;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_t_1:
			if (input == 'T')
			{
				state = http_version_t_2;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_t_2:
			if (input == 'T')
			{
				state = http_version_p;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_p:
			if (input == 'P')
			{
				state = http_version_slash;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_slash:
			if (input == '/')
			{
				_request.http_version_major = 0;
				_request.http_version_minor = 0;
				state = http_version_major_start;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_major_start:
			if (is_digit(input))
			{
				_request.http_version_major = _request.http_version_major * 10 + input - '0';
				state = http_version_major;
			  	return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_major:
			if (input == '.')
			{
				state = http_version_minor_start;
				return indeterminate;
			}
			else if (is_digit(input))
			{
				_request.http_version_major = _request.http_version_major * 10 + input - '0';
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_minor_start:
			if (is_digit(input))
			{
				_request.http_version_minor = _request.http_version_minor * 10 + input - '0';
				state = http_version_minor;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case http_version_minor:
			if (input == '\r')
			{
				state = expecting_newline_1;
				return indeterminate;
			}
			else if (is_digit(input))
			{
				_request.http_version_minor = _request.http_version_minor * 10 + input - '0';
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case expecting_newline_1:
			if (input == '\n')
			{
				state = header_line_start;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case header_line_start:
			if (input == '\r')
			{
				state = expecting_newline_3;
				return indeterminate;
			}
			else if (!_request.headers.empty() && (input == ' ' || input == '\t'))
			{
				state = header_lws;
				return indeterminate;
			}
			else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				_request.headers.push_back( HttpHeader() );
				_request.headers.back().name.push_back(input);
				state = header_name;
				return indeterminate;
			}

		case header_lws:
			if (input == '\r')
			{
				state = expecting_newline_2;
				return indeterminate;
			}
			else if (input == ' ' || input == '\t')
			{
				return indeterminate;
			}
			else if (is_ctl(input))
			{
				return bad;
			}
			else
			{
				state = header_value;
				_request.headers.back().value.push_back(input);
				return indeterminate;
			}

		case header_name:
			if (input == ':')
			{
				state = space_before_header_value;
				return indeterminate;
			}
			else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
			{
				return bad;
			}
			else
			{
				_request.headers.back().name.push_back(input);
				return indeterminate;
			}

		case space_before_header_value:
			if (input == ' ')
			{
				state = header_value;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case header_value:
			if (input == '\r')
			{
				state = expecting_newline_2;
				return indeterminate;
			}
			else if (is_ctl(input))
			{
				return bad;
			}
			else
			{
				_request.headers.back().value.push_back(input);
				return indeterminate;
			}

		case expecting_newline_2:
			if (input == '\n')
			{
				state = header_line_start;
				return indeterminate;
			}
			else
			{
				return bad;
			}

		case expecting_newline_3:
				return (input == '\n') ? good : bad;

		default:
				return bad;
	}

}
//--------------------------------------------------
bool HttpRequestParser::is_char(int c)
{
  return c >= 0 && c <= 127;
}
//--------------------------------------------------
bool HttpRequestParser::is_ctl(int c)
{
  return (c >= 0 && c <= 31) || (c == 127);
}
//--------------------------------------------------
bool HttpRequestParser::is_tspecial(int c)
{
  switch (c)
  {
  case '(': case ')': case '<': case '>': case '@':
  case ',': case ';': case ':': case '\\': case '"':
  case '/': case '[': case ']': case '?': case '=':
  case '{': case '}': case ' ': case '\t':
    return true;
  default:
    return false;
  }
}
//--------------------------------------------------
bool HttpRequestParser::is_digit(int c)
{
  return c >= '0' && c <= '9';
}


}  // namespace server
}  // namespace http


