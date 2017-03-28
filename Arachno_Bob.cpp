#include "Arachno_Bob.h"

Arachno_Bob::Arachno_Bob(const std::string& nickname, const std::string& user, const int& mode)
: nickname(nickname), user(user), mode(mode), connection(std::make_shared<Connection>()), buffer(), handler(connection, nickname)
{
}

bool Arachno_Bob::connect(const std::string& host, const std::string& port)
{
	if (!(connection->get_address(host, port) && connection->open_socket() && connection->get_connection()))
	{
		return false;
	}

	buffer.set_socket(connection->get_socket());
	
	for (auto i = 0; i < 2; i++)
	{
		buffer.read_to_buffer();
		buffer.extract_lines();
		std::string tmp{};
		while (!((tmp = buffer.getline()).empty()))
		{
			std::cout << tmp << '\n';
		}
	}
	connection->send_msg(std::string("USER bot " + std::to_string(mode) + " * :Arachno_Bob\r\n"));
	std::this_thread::sleep_for(std::chrono::seconds(1));
	connection->send_msg(std::string("NICK " + nickname + "\r\n"));
	return true;
}

void Arachno_Bob::event_loop()
{
	while (buffer.read_to_buffer())
	{
		buffer.extract_lines();
		std::string tmp{};
		while (!((tmp = buffer.getline()).empty()))
		{
			std::cout << tmp << '\n';
			auto tokens = buffer.tokenize(tmp);
			if (!tokens.empty())
			{
				handler.handle_msg(tokens);
			}
		}
	}
}

void Arachno_Bob::quit()
{
	connection->send_msg(std::string("QUIT\r\n"));
}
