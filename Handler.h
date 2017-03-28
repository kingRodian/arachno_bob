#ifndef HANDLER_H__
#define HANDLER_H__

#include <map>
#include <set>
#include <vector>
#include <regex>
#include <string>
#include <memory>
#include <functional>

#include "Connection.h"

const std::regex user_cmd_target
{
	"(\\.[-\\w]+) ([\\S]*) (.*)"
};

const std::regex user_cmd
{
	"(\\.[-\\w]+)(?: (.*))?"
};

const std::string LINEFEED
{
	"\r\n"
};

enum TOKENS
{
	SENDER,
	HEADER, 
	TARGET,
	MSG
};

class Handler
{
	typedef std::vector<std::string> str_vector;
	typedef std::function<void(str_vector)> msg_func;
	std::shared_ptr<Connection> connection;
	std::string nickname;

	// Hosts that are authorized to send commands
	std::set<std::string> authorized
	{
		"!~king@simulation.humanoid.buffoon",
		"!~cn28h@programming.addict"

	};

	// Actions to call based on the irc message received
	// Dont actually need actions on joins etc, do we?
	std::map<std::string, msg_func> irc_messages
	{
		//{"JOIN", Handler::join}, TODO Action?
		//{"PART", Handler::part)}, TODO Any point?
		{"PING", std::bind(&Handler::ping_trigger, this, std::placeholders::_1)},
		{"PRIVMSG", std::bind(&Handler::privmsg_trigger, this, std::placeholders::_1)},
		//{"QUIT", Handler::quit}
	};

	std::map<std::string, msg_func> user_cmds
	{
		{".say", std::bind(&Handler::say, this, std::placeholders::_1)},
		{".sayto", std::bind(&Handler::sayto, this, std::placeholders::_1)},
		{".join", std::bind(&Handler::join, this, std::placeholders::_1)},
		{".part", std::bind(&Handler::part, this, std::placeholders::_1)},
		{".quit", std::bind(&Handler::quit, this, std::placeholders::_1)}
	};

	
	// Responses to the various irc message headers
	//void join_trigger(std::smatch args);
	//void part_trigger(std::smatch args);
	void ping_trigger(str_vector args);
	void privmsg_trigger(str_vector args);
	//void quit_trigger(std::smatch args);

	//  TODO: Add user commands
	void say(str_vector args);
	void sayto(str_vector args);
	void join(str_vector args);
	void part(str_vector args);
	void quit(str_vector args);

public:
	Handler(const std::shared_ptr<Connection>& connection, std::string nickname);
	void handle_msg(str_vector);
};


#endif
