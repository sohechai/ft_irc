#include "Operate.hpp"
#include "./Command/HelpCmd.hpp"
#include "./Command/QuitCmd.hpp"
#include "./Command/NickCmd.hpp"
#include "./Command/WhoIsCmd.hpp"
#include "./Command/PrivMsgCmd.hpp"
#include "./Command/JoinCmd.hpp"
#include "./Command/UserCmd.hpp"
#include "./Command/KickCmd.hpp"
#include "./Command/PartCmd.hpp"
#include "./Command/WhoCmd.hpp"
#include "./Command/ListCmd.hpp"
#include "./Command/PassCmd.hpp"

Operate::Operate(Server *server) : _server(server)
{
	_commands.push_back(new HelpCmd(_commands));
	_commands.push_back(new QuitCmd());
	_commands.push_back(new NickCmd());
	_commands.push_back(new WhoIsCmd());
	_commands.push_back(new PrivMsgCmd());
	_commands.push_back(new JoinCmd());
	_commands.push_back(new UserCmd());
	_commands.push_back(new KickCmd());
	_commands.push_back(new PartCmd());
    _commands.push_back(new ListCmd());
    _commands.push_back(new WhoCmd());
	_commands.push_back(new PassCmd());
}

Operate::~Operate()
{
    std::vector<Command*>::iterator  it;

    for (it = _commands.begin(); it != _commands.end(); it++)
	{
        delete *it;
    }
	return ;
}

std::deque<std::string>		Operate::parseCmd(std::string msg)
{
    std::stringstream       ssMsg(msg);
    std::string             tmp;
    std::deque<std::string> argument;

    while (getline(ssMsg, tmp, ' '))
	{
        tmp.erase(tmp.find_last_not_of("\r\n") + 1);
        if (!tmp.empty())
            argument.push_back(tmp);
    }

	return argument ;

}

bool						Operate::isCmd(std::string msg)
{
    std::vector<Command*>::iterator  it;

    for (it = _commands.begin(); it != _commands.end(); it++)
	{
        if ((*it)->getName() == msg)
            return (true);
    }
    return (false);
}

void						Operate::runCmd(User *_sender, std::string command)
{
	std::deque<std::string>		args = parseCmd(command);
	std::string					cmdName = args[0].substr(1, sizeof(args[0]) - 1);
	if(!args.empty() && this->isCmd(args[0]))
	{
		for (size_t i = 0; i < _commands.size(); i++)
		{
			if (args[0] == _commands[i]->getName())
			{
				_commands[i]->setServer(_server);
				_commands[i]->setSender(_sender);
				_commands[i]->setArgs(args);
				_commands[i]->setCommand(command);
				try
				{
					_commands[i]->execute();
				}
				catch(const char* command)
				{
					_sender->getResponse(RPL_NONE(std::string(command)));
				}
				catch(std::string command)
				{
					_sender->getResponse(RPL_NONE(command));
				}
				break ;
			}
		}
	}
}