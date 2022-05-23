#include "NickCmd.hpp"

NickCmd::NickCmd()
{
    _name = "NICK";
    _description = "/nick <command> - change your nickname after you have connected";
}

NickCmd::~NickCmd()
{
    return;
}

void		NickCmd::execute()
{
    if (_args.size() < 1)
        throw ERR_NEEDMOREPARAMS(_name);
    if (_args.size() != 2)
        throw ERR_NONICKNAMEGIVEN;
	else
	{
		if (_sender->getNickName() == _args[1])//check si nickname existe
			throw ERR_NICKNAMEINUSE(_args[1]);
		else if (_sender->getPass() == false)
			throw ERR_PASSWDMISMATCH;
		else
		{
			_sender->setNickName(_args[1]);
			if (_sender->getUserName() != "")
				_sender->getResponse(RPL_WELCOME(_sender->getNickName(), _sender->getUserName(), _sender->getHost()));
			_sender->getResponse("300 * nickname has been set: " + _args[1]);
		}
	}
}