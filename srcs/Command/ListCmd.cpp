#include "ListCmd.hpp"

ListCmd::ListCmd() {
    _name = "LIST";
    _description = "/list - show channels on the server";
}

ListCmd::~ListCmd() {
    return;
}

void ListCmd::execute() {
    if (!_sender->getRegistered())
        throw ERR_RESTRICTED;

    std::vector<Channel *>              channels = _server->getChannels();
    std::vector<Channel *>::iterator    it;

    for (it = channels.begin(); it != channels.end(); it++)
        _sender->getResponse(RPL_LIST((*it)->getName(), std::to_string((*it)->getUsers().size())));
    _sender->getResponse(RPL_LISTEND);
}