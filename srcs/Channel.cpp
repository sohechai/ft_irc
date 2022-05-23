#include "Channel.hpp"

// ###################### GLOBAL ##############################

bool				checkChannelName(std::string channelName)
{
    if (channelName.empty())
        return false;
    if (channelName[0] != '#' /*&& channelName[0] != '&'*/)
        return false;
    for (size_t i = 0; i < channelName.size(); i++)
	{
        if (channelName[i] == ' ' || channelName[i] == 7 || channelName[i] == ',')
            return false;
    }
    return true;
}

// ######################### CONSTRUCTOR & DESTRUCTOR ###########################

Channel::Channel(std::string name, int adminfd, Server *server) : _adminfd(adminfd), _server(server)
{
    setName(name);
}

Channel::~Channel()
{
    return;
}

// ################################ GETTER #####################################

std::string			Channel::getName() const
{
    return (_name);
}

User *				Channel::getAdmin() const
{
    return (_server->getUser(_adminfd));
}

User *				Channel::getUser(std::string userName) const
{
    std::vector<User *>::const_iterator it;

    for (it = _usersinchann.begin(); it != _usersinchann.end(); it++)
    {
        if ((*it)->getNickName() == userName)
            return (*it);
    }
    return (nullptr);
}

std::vector<User *> Channel::getUsers() const
{
    return (this->_usersinchann);
}

int					Channel::getNbOfUser() const
{
	std::vector<User *>::const_iterator it;
	int									i = 0;
    for (it = _usersinchann.begin(); it != _usersinchann.end(); it++)
    {
       i++;
    }
    return (0);
}

// #################################### SETTER #################################

void				Channel::setName(std::string name)
{
    _name = name.substr(1, 15);
    return;
}


// ########################## User management ##################################

void				Channel::addUser(User *user)
{
    _usersinchann.push_back(user);
}

void				Channel::removeUser(User *user)
{
    std::vector<User *>::iterator it;

    for (it = _usersinchann.begin(); it < _usersinchann.end(); it++)
	{
        if (*it == user)
		{
            _usersinchann.erase(it);
            (*it)->setChannel(nullptr);
            break ;
        }
    }
    // Si on veux delete les channels quand il n'y a plus personne dedans
    if (_usersinchann.empty())
        _server->deleteChannel(this);
}

bool				Channel::isUser(User *user) const
{
    std::vector<User *>::const_iterator it;

    for (it = _usersinchann.begin(); it != _usersinchann.end(); it++)
	{
        if (*it == user)
            return (true);
    }

    return (false);
}

// ##################### Message management in the channel ###########################

void				Channel::sendMsgToUsers(User *sender, std::string message, std::string cmd)
{
    std::vector<User *>::iterator it;

    for (it = _usersinchann.begin(); it != _usersinchann.end(); ++it)
	{
        sender->sendMsg(*it, cmd + " #" + this->getName() + " +" + message + "\r\n");
    }
}

void				Channel::sendMsgToChan(User *sender, std::string message, std::string cmd)
{
    std::vector<User *>::iterator it;

    for (it = _usersinchann.begin(); it != _usersinchann.end(); ++it)
	{
        if ((*it) != sender)
            sender->sendMsg(*it, cmd + " #" + this->getName() + " +" + message + "\r\n");
    }
}
