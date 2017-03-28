#ifndef ARACHNO_BOB_H__
#define ARACHNO_BOB_H__

#include <string>
#include <deque>
#include <set>
#include <thread>
#include <chrono>
#include <algorithm>
#include <regex>

#include "Connection.h"
#include "Buffer.h"
#include "Handler.h"

enum command_enum
{
	USER,
	NICK,
	PING,
	PONG,
	JOIN,
	PART,
	PRIVMSG,
	QUIT
};

const std::string PING_str
{
	"PING"
};

const std::string master
{
	"king@simulation.humanoid.buffoon"
};

class Arachno_Bob
{
private:
	std::string nickname;
	std::string user;
	std::string user_string;
	int mode;
	std::shared_ptr<Connection> connection;
	Buffer buffer;
	Handler handler;
	//std::map<std::string, int> user_commands =
	//{
//		std::make_pair<std::string, int>("say", 0),
//		std::make_pair<std::string, int>("reverse", 1)
//	};

public:	
	Arachno_Bob(const std::string& nickname, const std::string& user, const int& mode);
	bool connect(const std::string& host, const std::string& port);
	void event_loop();
	void fill_buffer();
	std::string getline();
	std::string create_command(enum command_enum, std::string arg);
	void handle_msg(std::string msg);
	void identify();
	void join(const std::string& channel);
	void send_msg(const std::string& target, const std::string& msg);
	void execute_command(const std::string& command, const std::string& target, std::string arg);
	void quit();

};
	
#endif
