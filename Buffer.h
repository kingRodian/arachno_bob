#ifndef BUFFER_H__
#define BUFFER_H__

#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <string>
#include <regex>
#include <sys/types.h>
#include <sys/socket.h>

const int LINELEN = 512; // Max chars for an irc line

class Buffer
{
private:
	std::array<char, LINELEN> buffer;			// Buffer
	std::array<char, LINELEN>::iterator put_position;	// Iterator pointing to next free element
	int bytes_left;						// Free bytes left in buffer
	int socket_fd;
	std::deque<std::string> msg_queue;
	std::regex irc_expr{"(?::(\\S+))? ?(\\S+) (\\S*) ?:(.*)"};

public:
	Buffer();
	void set_socket(const int& socket_fd);
	int read_to_buffer();
	void extract_lines();
	std::string getline();
	std::vector<std::string> tokenize(std::string line);
};

#endif


		
	
