#include "Handler.h"

//void Handler::join_trigger(str_vector args)



//void Handler::part_trigger(str_vector args)



void Handler::ping_trigger(str_vector args)
{
	std::string message;
	message = "PONG " + args.at(MSG) + LINEFEED;
	connection->send_msg(message);
}

void Handler::privmsg_trigger(str_vector args)
{
	std::string sender = args.at(SENDER);
	bool is_auth = false;
	for (auto s : authorized)
	{
		if (sender.find(s) != std::string::npos)
		{
			is_auth = true;
			break;
		}
	}
		
	if (is_auth)
	{
		std::smatch match;
		std::regex_search(args.at(MSG), match, user_cmd);
		std::string cmd = match.str(1);
		std::string msg = match.str(2);
		args.at(MSG) = msg;
		
		auto cmd_search = user_cmds.find(cmd);
		if (cmd_search != user_cmds.end())
		{
			cmd_search->second(args);
		}
	}
}

//void Handler::quit_trigger(std::smatch args)


void Handler::say(str_vector args)
{
	std::string msg = args.at(MSG);
	if (msg.empty())
	{
		return;
	}
	std::string target = args.at(TARGET);
	if (target == nickname)
	{
		target = args.at(SENDER);
		auto n = target.find("!");
		target = target.substr(0, n);
	}
	connection->send_msg(std::string("PRIVMSG " + target + " :" + args.at(MSG) + LINEFEED));
}

void Handler::sayto(str_vector args)
{
	auto n = args.at(MSG).find(" ");
	std::string target = args.at(MSG).substr(0, n);
	std::string msg = args.at(MSG).substr(n + 1, std::string::npos);

	if (!target.empty())
	{
		connection->send_msg(std::string("PRIVMSG " + target + " :" + msg + LINEFEED));
	}
}

void Handler::reverse(str_vector args)
{
	std::string msg = args.at(MSG);
	std::reverse(msg.begin(), msg.end());

	std::string target = args.at(TARGET);
	if (target == nickname)
	{
		target = args.at(SENDER);
		auto n = target.find("!");
		target = target.substr(0, n);
	}
	connection->send_msg(std::string("PRIVMSG " + target + " :" + msg + LINEFEED));
}


void Handler::sort(str_vector args)
{
	std::string msg = args.at(MSG);
	std::sort(msg.begin(), msg.end());

	std::string target = args.at(TARGET);
	if (target == nickname)
	{
		target = args.at(SENDER);
		auto n = target.find("!");
		target = target.substr(0, n);
	}
	connection->send_msg(std::string("PRIVMSG " + target + " :" + msg + LINEFEED));
}





void Handler::join(str_vector args)
{
	auto n = args.at(MSG).find(" ");
	std::string target = args.at(MSG).substr(0, n);

	if (!target.empty())
	{
		connection->send_msg(std::string("JOIN  " + target  + LINEFEED));
	}
}

void Handler::part(str_vector args)
{
	auto n = args.at(MSG).find(" ");
	std::string target = args.at(MSG).substr(0, n);

	if (target.empty() && args.at(TARGET) != nickname)
	{
		target = args.at(TARGET);

	}
	else if (target.empty())
	{
		return;
	}
	connection->send_msg(std::string("PART  " + target  + LINEFEED));
}

void Handler::quit(str_vector args)
{
	connection->send_msg(std::string("QUIT" + LINEFEED));
}

Handler::Handler(const std::shared_ptr<Connection>& connection, std::string nickname)
: connection(connection), nickname(nickname)
{
}

void Handler::handle_msg(str_vector args)
{
	auto search = irc_messages.find(args.at(HEADER));
	if (search != irc_messages.end())
	{
		search->second(args);
	}
}
