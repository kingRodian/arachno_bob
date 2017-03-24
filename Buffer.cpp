#include "Buffer.h"

Buffer::Buffer()
: bytes_left(LINELEN), socket_fd(0)
{
	put_position = buffer.begin();
	buffer = {0};
}

void Buffer::set_socket(const int& socket_fd)
{
	this->socket_fd = socket_fd;
}

int Buffer::read_to_buffer()
{
	int n = 0;
	n = recv(socket_fd, put_position, bytes_left - 1, 0);
	bytes_left -= n;
	put_position += n;
	*put_position = '\0';
	
	if (n == -1)
	{
		put_position = buffer.begin();
		*put_position = '\0';
		bytes_left = LINELEN;
	}
	return true;
}

void Buffer::extract_lines()
{
	std::string line{};
	int cutoff = 0;
	for (auto it = buffer.begin(); it != put_position; ++it)
	{
		if (*it == '\n' && !line.empty())
		{
			msg_queue.push_back(line);
			cutoff += line.length() + 1;
			line.clear();
		}
		else
		{
			line += *it;
		}
	}
	
	// Move elements in buffer to make space
	int bytes_to_move = std::distance(buffer.begin() + cutoff, put_position);
	if (bytes_to_move)
	{
		std::copy(buffer.begin() + cutoff, put_position, buffer.begin());
	}
	bytes_left += cutoff;
	put_position -= cutoff;
	
}

std::string Buffer::getline()
{
	std::string s{""};
	if (!msg_queue.empty())
	{
		s = msg_queue.front();
		msg_queue.pop_front();
	}
	return s;
}

std::vector<std::string> Buffer::tokenize(std::string line)
{	
	std::smatch match;
	std::vector<std::string> tokens;
	std::regex_search(line, match, irc_expr);
	std::copy
	(
	 	match.begin() + 1, 
		match.end(),
		std::back_inserter(tokens)
	);
	
	return tokens;
}

