#include "PassCmd.hpp"

PassCmd::PassCmd()
{
    _name = "PASS";
    _description = "/pass <password> - The PASS command is used to set a 'connection password'";
}

PassCmd::~PassCmd()
{
    return;
}

void		PassCmd::execute()
{
    if(_args.size() != 2)
		throw	ERR_NEEDMOREPARAMS(_args[0]);
	if (_sender->getRegistered() == true)
		throw	ERR_ALREADYREGISTRED;
	else
	{
		if (_args[1] != _server->get_password())
		{
			throw ERR_PASSWDMISMATCH;
			_sender->setPass(false);
		}
		else
			_sender->setPass(true);
	}
}