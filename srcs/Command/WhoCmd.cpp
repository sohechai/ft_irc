#include "WhoCmd.hpp"

WhoCmd::WhoCmd() {
    _name = "WHO";
    _description = "WHO <#channel> - show the list of users on channel";
}

WhoCmd::~WhoCmd() {
    return;
}

void WhoCmd::execute()
{
    if (!_sender->getRegistered())
        throw ERR_RESTRICTED;
    if (_args.size() < 1)
        throw ERR_NEEDMOREPARAMS(_name);

    Channel *channel = _server->getChannel((_args[1]));

    if (channel == nullptr)
        throw ERR_NOSUCHCHANNEL(_args[1]);

    std::vector<User *> users = channel->getUsers();

    _sender->getResponse("300 * Channel " + channel->getName() + " has " + std::to_string(users.size()) + " users");

    std::vector<User *>::iterator it;
    for (it = users.begin(); it != users.end(); it++)
    {
        if (channel->getAdmin() == *it)
            _sender->getResponse("300 * @" + (*it)->getNickName());
        else
            _sender->getResponse("300 * " + (*it)->getNickName());
    }
}