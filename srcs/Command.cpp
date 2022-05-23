#include "Command.hpp"

Command::Command() : _name(""), _description(""), _server(NULL), _sender(NULL)
{
	return;
}

Command::~Command() {
	return;
}

std::string			Command::getName() const
{
	return (_name);
}

std::string			Command::getDescription() const
{
	return (_description);
}

std::string			Command::getCommand() const
{
	return (_command);
}


void				Command::setSender(User *sender)
{
	_sender = sender;
}

void				Command::setServer(Server *server)
{
	_server = server;
}

void				Command::setArgs(std::deque <std::string> args)
{
	_args = args;
}

void				Command::setCommand(std::string command)
{
	_command = command;
}
