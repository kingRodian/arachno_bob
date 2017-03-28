#include "Connection.h"


Connection::Connection()
: socket_fd(0), server_info(nullptr)
{
}

Connection::~Connection()
{
	freeaddrinfo(server_info);
}



bool Connection::get_address(const std::string& host, const std::string& port)
{
	// Set hints to all zeroes 
	std::memset(&addr_hints, 0, sizeof(addr_hints));
	addr_hints.ai_flags = AI_PASSIVE; // Fill out own ip automatically
	addr_hints.ai_family = AF_UNSPEC; // Accept both ipv4 and 6
	addr_hints.ai_socktype = SOCK_STREAM; // Stream, tcp

	// Try to connect to the first address
	int status = 0;
	if (status != getaddrinfo(host.c_str(), port.c_str(), &addr_hints, &server_info))
	{
		std::cerr << "Could not resolve host address of " << host << '\n';
		return false;
	}
	return true;
} 

void Connection::print_addresses()
{
	std::cout << "Printing addresses:\n";
	void* addr;
	for (auto* current = server_info; current != nullptr; current = current->ai_next)
	{
		if (current->ai_family == AF_INET) // ipv4
		{
			struct sockaddr_in* ipv4 = reinterpret_cast<struct sockaddr_in*>(current->ai_addr);
			addr = &(ipv4->sin_addr);
		}
		else // ipv6
		{
			struct sockaddr_in6* ipv6 = reinterpret_cast<struct sockaddr_in6*>(current->ai_addr);
			addr = &(ipv6->sin6_addr);
		}
		char ip_string[32];
		inet_ntop(current->ai_family, addr, ip_string, sizeof(ip_string)); // Convert binary ip address to a string
		std::cout << std::string{ip_string} << '\n';
	}
}


bool Connection::open_socket()
{
	if (server_info != nullptr)
	{
		std::cout << "Opening socket.\n";
		// Get values from the server info, do not hardcode the arguments
		socket_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
		if (socket_fd < 0)
		{
			std::cerr << "ERROR: Could not open socket.\n";
			return false;
		}
		return true;
	}
	else 
	{
		std::cerr << "ERROR: Could not open socket: server_info not filled out.\n";
		return false;
	}
}

bool Connection::get_connection()
{
	std::cout << "Connecting..\n";
	if (connect(socket_fd, server_info->ai_addr, server_info->ai_addrlen) == 0)
	{
		std::cout << "Connected.\n";
		return true;
	}
	else
	{
		std::cerr << "ERROR: Could not connect.\n";
		return false;
	}
}

bool Connection::send_msg(const std::string& msg)
{
	uint32_t bytes_sent = 0;
	std::cout << "Sending: " << msg;
	if ((bytes_sent = send(socket_fd, msg.c_str(), msg.length(), 0)) != msg.length())
	{
		std::cerr << "ERROR: Could not send message.\n";
		return false;
	}
	return true;
			
}


void Connection::close()
{
}

