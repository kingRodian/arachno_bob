#ifndef CONNECTION_H__
#define CONNECTION_H__

#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <deque>
#include <array>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

/*
 ------------------------------------------------------------------------------
 |                             Connection.h                                   |
 ------------------------------------------------------------------------------
 | A c++ wrapper to abstract away the sockets used.                            *
 | Instead we want the bot to use iostreams.                               *
 |                                          *
 |                                          *
 |
 |
 |
 |
 */

class Connection
{
protected:
	int socket_fd;
	struct addrinfo addr_hints;		// Fill out with info to get an address
	struct addrinfo* server_info;		// Get the address to desired host

public:
	Connection();
	~Connection();
	bool get_address(const std::string& host, const std::string& port);
	void print_addresses();
	bool open_socket();
	int get_socket()
	{
		return socket_fd;
	}
	bool get_connection();
	bool send_msg(const std::string& msg);
	bool check_socket_status();
	void close();
};

#endif
