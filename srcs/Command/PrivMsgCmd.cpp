#include "PrivMsgCmd.hpp"

PrivMsgCmd::PrivMsgCmd()
{
    _name = "PRIVMSG";
    _description = "/msg <receiver> <text to be sent> - Send a message to a nick or a channel";
}

PrivMsgCmd::~PrivMsgCmd()
{
    return;
}

void		PrivMsgCmd::execute()
{
	if (!_sender->getRegistered())
        throw ERR_RESTRICTED;
	if (_args.size() == 2)
        throw ERR_NOTEXTTOSEND;
	if (_args.size() == 1)
        throw ERR_NONICKNAMEGIVEN;

    if (this->isUser() != nullptr)
    {
        User    *user = this->isUser();

        _sender->sendMsg(user, "PRIVMSG " + user->getNickName() + " :" + this->toString());
    }
    else if (this->isChannel() != nullptr)
    {
        Channel     *tmpChan = this->isChannel();
        std::string tmp = this->toString();

        if (tmpChan && !tmp.empty())
        {
			if (tmpChan->getUser(_sender->getNickName()) != nullptr)
		   		tmpChan->sendMsgToChan(_sender, tmp, this->_name);
			else
				_sender->getResponse("300 * you're not in channel :" + _args[1]);
		}
    }
    else
        _sender->getResponse("300 * error nick or channel not found");
    this->clearArgs();
}

User * PrivMsgCmd::isUser()
{
    if (_args.empty())
        return (nullptr);
    else
    {
        User*   user = _server->getUser(_args[1]);

        if (user == nullptr)
            return (nullptr);
        else
            return (user);
    }
}

Channel * PrivMsgCmd::isChannel() {
    if (_args.empty())
        return (nullptr);
    else
    {
        std::string name = _args[1].substr(1, _args[1].size());
        Channel *channel = _server->getChannel(name);

        if (channel == nullptr)
            return (nullptr);
        else
            return (channel);
    }
}

std::string PrivMsgCmd::toString() {
    std::string tmp;
    for (size_t i  = 1; i <= _args.size(); i++)
    {
        if (!this->_args[i].empty())
        {
            if (tmp.empty()) {
                tmp =  this->_args[i];
            }
            else {
                tmp = tmp +  " " + this->_args[i];
            }
        }
    }
    tmp.erase(tmp.find_last_not_of("\r\n") + 1);
    return tmp;
}

void PrivMsgCmd::clearArgs() {
    _args.erase(_args.begin(), _args.end());
}
