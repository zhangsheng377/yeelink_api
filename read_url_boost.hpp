//http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/http/client/sync_client.cpp
//http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/socks4/sync_client.cpp

#ifndef __READ_URL_BOOST__
#define __READ_URL_BOOST__

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost\array.hpp>

using boost::asio::ip::tcp;

class READ_URL_BOOST {
public:
	static std::string read_url(std::string host, std::string path) {
		try
		{
			boost::asio::io_service io_service;

			// Get a list of endpoints corresponding to the server name.
			tcp::resolver resolver(io_service);
			tcp::resolver::query query(host, "http");
			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			tcp::resolver::iterator end;

			// Try each endpoint until we successfully establish a connection.
			tcp::socket socket(io_service);
			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && endpoint_iterator != end)
			{
				socket.close();
				socket.connect(*endpoint_iterator++, error);
			}
			if (error)
				throw boost::system::system_error(error);

			// Form the request. We specify the "Connection: close" header so that the
			// server will close the socket after transmitting the response. This will
			// allow us to treat all data up until the EOF as the content.
			boost::asio::streambuf request;
			std::ostream request_stream(&request);
			request_stream << "GET " << path << " HTTP/1.0\r\n";
			request_stream << "Host: " << host << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "Connection: close\r\n\r\n";

			// Send the request.
			boost::asio::write(socket, request);
			/*
			// Read the response status line.
			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");

			// Check that response is OK.
			std::istream response_stream(&response);
			std::string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			std::string status_message;
			std::getline(response_stream, status_message);
			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
			return "Invalid response\n";
			}
			if (status_code != 200)
			{
			std::string result = "Response returned with status code " + status_code;
			result += "\n";
			return result;
			}

			// Read the response headers, which are terminated by a blank line.
			boost::asio::read_until(socket, response, "\r\n\r\n");

			std::string result_0 = "";
			// Process the response headers.
			std::string header;
			while (std::getline(response_stream, header) && header != "\r")
			result_0 += header + "\n";
			result_0 += "\n";


			std::string result = "";
			// Write whatever content we already have to output.
			if (response.size() > 0) {
			std::istream temp_istream(&response);
			std::string temp_string;
			temp_istream >> temp_string;
			std::cout <<"size : " << temp_string << std::endl;
			result += temp_string;
			}
			*/

			std::string result = "";
			// Read until EOF, writing data to output as we go.
			boost::array<char, 99999> re_buf;
			int count_buf = 0;
			char pp[99999];
			while (std::size_t s = socket.read_some(boost::asio::buffer(re_buf), error)) {
				//while (boost::asio::read(socket, response,boost::asio::transfer_at_least(1), error)) {
				//std::size_t s1 = boost::asio::buffer_size(response.data());
				//const unsigned char* p1 = boost::asio::buffer_cast<const unsigned char*>(response.data());
				//char *p = (char*)p1;
				memcpy(pp + count_buf, re_buf.data(), s);
				pp[count_buf + s] = '\0';
				count_buf += s;
				//std::istream temp_istream(&response);
				//break;
			}
			std::string temp_string = pp;
			result += temp_string;
			if (error != boost::asio::error::eof)
				throw boost::system::system_error(error);

			//int index_r = 0;
			//std::cout << result.find("\r\n\r\n") << std::endl;
			//std::cout << result.substr(258) << std::endl;


			return result.substr(result.find("\r\n\r\n") + 4);
		}
		catch (std::exception& e)
		{
			std::string result = "Exception: ";
			std::string temp_string = e.what();
			result += "\n";
			return result;
		}
	}
};

#endif // !__READ_URL_BOOST__
