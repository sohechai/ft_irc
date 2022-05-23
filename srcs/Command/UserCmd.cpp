#include "UserCmd.hpp"

UserCmd::UserCmd()
{
    _name = "USER";
    _description = "/user <username> <hostname> <servername> <realname> - register command";
}

UserCmd::~UserCmd()
{
    return;
}

void		UserCmd::execute()
{
	if (_args.size() != 5)
		throw	ERR_NEEDMOREPARAMS(getCommand());
	else if (_sender->getPass() == false)
		_server->removeUser(_sender);
	else if (_sender->getRegistered() == false)
	{
		_sender->setUserName(_args[1]);
		_sender->setHostName(_server->getHost());
		_sender->setRealName(_args[4].substr(1, sizeof(_args[4])));
		_sender->getResponse(RPL_WELCOME(_sender->getNickName(), _sender->getUserName(), _sender->getHost()));
		_sender->setRegistered(true);
	}
	else
		throw	ERR_ALREADYREGISTRED;
}