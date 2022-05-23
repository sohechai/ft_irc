#include "KickCmd.hpp"

KickCmd::KickCmd() {
    _name = "KICK";
    _description = "/kick <#channel> <user> - kick a user from channel";
}

KickCmd::~KickCmd() {
    return;
}

void KickCmd::execute()
{
    if (!_sender->getRegistered())
        throw ERR_RESTRICTED;
    if (_args.size() < 2)
        throw ERR_NEEDMOREPARAMS(_name);
    if (!checkChannelName(_args[1]))
        throw ERR_BADCHANMASK(_args[1]);

    Channel *channel = _server->getChannel(_args[1]);

    if (channel == nullptr)
        throw ERR_NOSUCHCHANNEL(_args[1]);
    if (channel->getAdmin() != _sender)
        throw ERR_CHANOPRIVSNEEDED(channel->getName());
    if (!channel->getUser(_sender->getNickName()))
        throw ERR_NOTONCHANNEL(channel->getName());

    User    *userToKick = channel->getUser(_args[2]);

    if (userToKick == nullptr)
        throw ERR_USERNOTINCHANNEL(_args[2], channel->getName());

    channel->sendMsgToUsers(_sender, "kicked " + userToKick->getNickName(), this->_name);
	userToKick->getResponse(userToKick->getNickName() + ": you have been kicked by :" + _sender->getNickName());
    channel->removeUser(userToKick);
}