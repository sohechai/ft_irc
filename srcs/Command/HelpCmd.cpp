#include "HelpCmd.hpp"

HelpCmd::HelpCmd(std::vector<Command*>&	commands) : _commands(commands)
{
    _name = "HELP";
    _description = "/help <command> - Lists commands, if a command is given then shows command usage and description";
}

HelpCmd::~HelpCmd()
{
    return;
}

void		HelpCmd::execute()
{
	if (_args.size() == 1)
	{
		std::vector<Command *>::iterator    it;
		for (it = _commands.begin(); it != _commands.end(); it++)
		{
			_sender->getResponse("300 * " + (*it)->getDescription());
		}
	}
	else if (_args.size() == 2)
	{
		std::vector<Command *>::iterator    it;
		for (it = _commands.begin(); it != _commands.end(); ++it)
		{
			if (_args[1].compare((*it)->getName()) == 0)
			{
				_sender->getResponse("300 * " + (*it)->getDescription());
				break ;
			}
		}
		if (it == _commands.end())
			_sender->getResponse("300 * Command not found");
	}
	else
	{
		_sender->getResponse("300 * Too much arguments");
	}
}