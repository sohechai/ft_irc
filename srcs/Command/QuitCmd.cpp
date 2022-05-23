#include "QuitCmd.hpp"

QuitCmd::QuitCmd()
{
    _name = "QUIT";
    _description = "/quit - Quit WeeChat";
}

QuitCmd::~QuitCmd()
{
    return;
}

void		QuitCmd::execute()
{
    _server->removeUser(_sender);
}