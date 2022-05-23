#include "WhoIsCmd.hpp"

WhoIsCmd::WhoIsCmd()
{
    _name = "WHOIS";
    _description = "/whois <pseudonyme> - Shows information about a user";
}

WhoIsCmd::~WhoIsCmd()
{
    return;
}

void		WhoIsCmd::execute()
{
	if (_args.size() == 1)
    {
		_sender->getResponse((RPL_WHOISUSER(_sender->getNickName(), _sender->getUserName(), _sender->getHost(), _sender->getRealName())));
        return;
	}
	else
	{
		std::vector<int> client_socket = _server->_client_socket;
		std::vector<int>::iterator	it = client_socket.begin();
        for (it = client_socket.begin(); it != client_socket.end(); ++it)
        {
            if(_server->getUser(*it) != nullptr && _server->getUser(*it)->getNickName() == _args[1])
			{
				_sender->getResponse(RPL_WHOISUSER(_server->getUser(*it)->getNickName(), _server->getUser(*it)->getUserName(), _server->getUser(*it)->getHost(), _server->getUser(*it)->getRealName()));
                return ;
            }
        }
		throw	ERR_NOSUCHNICK(_args[1]);
		return ;
	}
}