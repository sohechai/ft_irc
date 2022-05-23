#include "PartCmd.hpp"

PartCmd::PartCmd() {
    _name = "PART";
    _description = "/part <#channel> - leave channel";
}

PartCmd::~PartCmd() {
    return;
}

void PartCmd::execute() {
	std::cout << _args.size() << std::endl;
    if (_args.size() != 4)
        throw ERR_NEEDMOREPARAMS(_name);
    if (!_sender->getRegistered())
        throw ERR_RESTRICTED;

    Channel *channel = _server->getChannel(_args[1]);

    if (!channel)
        throw ERR_NOSUCHCHANNEL(_args[1]);
    if (_sender->getChannel() != channel)
        throw ERR_NOTONCHANNEL(_args[1]);

    sendInfoToChan(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
    _sender->quitChannel();
    _sender->setChannel(nullptr);
}

void PartCmd::sendInfoToChan(Channel *channel, std::string message) const {
    std::vector<User *>::iterator    it;
    std::vector<User *>              users = channel->getUsers();

    for (it = users.begin(); it != users.end(); it++)
	{
        (*it)->getResponse(message);
    }
}