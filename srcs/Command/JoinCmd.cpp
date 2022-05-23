#include "JoinCmd.hpp"

JoinCmd::JoinCmd()
{
    _name = "JOIN";
    _description = "/join <#channel> - join or create a channel";
}

JoinCmd::~JoinCmd()
{
    return;
}

void JoinCmd::execute()
{
    if (!_sender->getRegistered())
        throw ERR_RESTRICTED;
    if (_args.size() < 1)
        throw ERR_NEEDMOREPARAMS(_name);
    if (!checkChannelName(_args[1]))
        throw ERR_BADCHANMASK(_args[1]);

    Channel *channel = _server->getChannel(_args[1]);

    if (!channel)
    {
	    channel = _server->createChannel(_args[1], _sender);
	}
    _sender->setChannel(channel);
	_sender->setOpRight(true);
    channel->addUser(_sender);
    sendInfoToChan(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
}

void		JoinCmd::sendInfoToChan(Channel *channel, std::string message) const
{
    std::vector<User *>::iterator    it;
    std::vector<User *>              users = channel->getUsers();

    for (it = users.begin(); it != users.end(); it++)
	{
        (*it)->getResponse(message);
    }
}
