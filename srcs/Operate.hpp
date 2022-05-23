#ifndef OPERATE_HPP
#define OPERATE_HPP

class	Operate;

# include "Command.hpp"
# include "utils/ircserv.hpp"
# include "Server.hpp"
# include "User.hpp"

class	Operate
{

public:

    Operate(Server* server);
    virtual ~Operate();

	std::deque<std::string>		parseCmd(std::string msg);
	void						runCmd(User *_sender, std::string message);
    bool    					isCmd(std::string msg);

private:
    Server                 		*_server;
    std::vector<Command*>   	_commands;
};


#endif