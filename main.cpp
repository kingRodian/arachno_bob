#include <string>
#include <chrono>
#include <thread>

#include "Connection.h"
#include "Buffer.h"
#include "Arachno_Bob.h"
#include "Handler.h"




const std::string nickname
{
	"arachno_bob"
};

const std::string user
{
	"ARACHNO_BOB"
};

const int mode = 0;


int main()
{
	Arachno_Bob bot(nickname, user, mode);
	std::string host{"irc.rizon.net"};
	std::string port{"6660"};
	bot.connect(host, port);
	bot.event_loop();
	bot.quit();
	
	return 0;
}
		
	
