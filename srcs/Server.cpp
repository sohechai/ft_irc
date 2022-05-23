#include "Server.hpp"

Server::Server()
{
    this->_opt = 1;
	this->_max_clients = 30;

    return ;
}

Server::~Server()
{
    return ;
}

// ############################# GETTER ################################

Channel				*Server::getChannel(std::string name)
{
    std::vector<Channel *>::iterator    it;
    std::string                         tmp = name;

    if (name.empty())
        return (nullptr);
    if (tmp.c_str()[0] == '#')
    {
        tmp = tmp.substr(1, tmp.size());
    }

    for (it = _channels.begin(); it != _channels.end(); it++)
	{
        if ((*it)->getName() == tmp)
            return (*it);
    }
    return (nullptr);
}

User * 				Server::getUser(std::string userName)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
    {
        if ((*it)->getNickName() == userName)
            return (*it);
    }

    return (nullptr);
}

std::string			Server::getHost() const
{
	return (this->_host);
}

// Channel management

Channel				*Server::createChannel(std::string name, User *admin)
{
    Channel *newChannel = new Channel(name, admin->getSocketFd(), this); // new Channel(name, admin, this); pour multi channel

	std::string str = "Canal " + newChannel->getName() + " : " + std::to_string(newChannel->getNbOfUser()) + " pseudos (1 op, 0 voice, 1 normal)";

    _channels.push_back(newChannel);

    return (newChannel);
}

void				Server::deleteChannel(Channel *channel) {
    std::vector<Channel *>::iterator it;

    for (it = _channels.begin(); it < _channels.end(); it++) {
        if (*it == channel) {
            _channels.erase(it);
            break;
        }
    }
}

std::vector<Channel *> Server::getChannels() {
    return (_channels);
}

std::string			Server::get_password() const
{
	return (this->_password);
}


int					Server::get_max_clients() const
{
    return (_max_clients);
}

void				Server::init_clients()
{
    for (int i = 0; i < _max_clients; i++)
        _client_socket.push_back(0);
}

int         		Server::get_server_socket() const
{
    return (this->_server_socket);
}

User				*Server::getUser(int client_socket)
{
	std::vector<User *>::iterator it;
    for (it = _users.begin(); it != _users.end(); it++)
    {
        int		fd = (*it)->getSocketFd();
		if (fd == client_socket)
			return (*it);
    }
	return (nullptr);
}

void				Server::error(std::string str_error)
{
    std::cout << "Error: " << str_error << std::endl;
    exit(EXIT_FAILURE);
}

User* 				Server::getUserId(std::string id) {
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
    {
        if ((*it)->getId() == id)
            return (*it);
    }

    return (nullptr);
}

void 				Server::removeUser(User *user)
{
    // Remove User from Socket
    std::vector<int>::iterator itfd = _client_socket.begin();
    std::vector<int>::iterator itefd = _client_socket.end();

    for (; itfd != itefd; itfd++)
    {
        if (user->getSocketFd() == (*itfd))
        {
            // close user_fd
            _client_socket.erase(itfd);
            break;
        }
    }

    std::cout << "Host disconnected , ip " <<  inet_ntoa(_address.sin_addr) << " , port " << ntohs(_address.sin_port) << std::endl;

    // Remove User from User vector
    std::vector<User *>::iterator it = _users.begin();
    std::vector<User *>::iterator ite = _users.end();

    for (; it != ite; it++)
    {
        if ((*it)->getNickName() == user->getNickName())
        {
            delete user;
            _users.erase(it);
            break ;
        }
    }
}

void				Server::create_server_socket(int port)
{
    if( (_server_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
        error("socket failed to create");

    if(fcntl(_server_socket, F_SETFL, O_NONBLOCK) < 0)
        error("couldnt non block socket serv");

    //set master socket to allow multiple connections ,
    if(setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&_opt, sizeof(_opt)) < 0)
        error("setsock_opt");

    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(port);
    if (bind(_server_socket, (struct sockaddr *)&_address, sizeof(_address))<0)
        error("bind socket serveur");

	std::cout << "\n\n+-+-+-+-+-+-+-+ +-+-+ +-+-+-+ +-+-+-+ +-+-+-+-+-+-+\n|W|e|l|c|o|m|e| |t|o| |o|u|r| |i|r|c| |s|e|r|v|e|r|\n+-+-+-+-+-+-+-+ +-+-+ +-+-+-+ +-+-+-+ +-+-+-+-+-+-+\n" << std::endl;

    std::cout << "Listener on port " << port << std::endl;

    if (listen(_server_socket, 3) < 0)
        error("listen");

    _addrlen = sizeof(_address);
    std::cout << "Waiting for connections ..." << std::endl;

    return ;
}

void 				Server::start(std::string host, int port, std::string password)
{
	this->_password = password;
	this->_host = host;
    init_clients();

    this->create_server_socket(port);
	_operate = new Operate(this);
    while (1)
    {
        this->loop();
    }
}

void				Server::loop()
{
    FD_ZERO(&_readfds); //clear le sockets set
    FD_SET(_server_socket, &_readfds); //add server socket to set
    _max_sd = _server_socket;

    std::vector<int>::iterator	it = _client_socket.begin();
    for (it = _client_socket.begin(); it != _client_socket.end(); ++it)
    {
        _sd = *it;
        if(_sd > 0) // socket ok add to list
            FD_SET( _sd , &_readfds);
        if(_sd > _max_sd) // set max socket for select fonction
            _max_sd = _sd;
    }
    _activity = select( _max_sd + 1 , &_readfds , NULL , NULL , NULL);

    if ((_activity < 0) && (errno != EINTR))
        std::cout << "select error" << std::endl;
    if (FD_ISSET(_server_socket, &_readfds)) // incomming connection
    {
        if ((_new_socket = accept(_server_socket, (struct sockaddr *)&_address, (socklen_t*)&_addrlen)) < 0)
            error("accept");
		if(fcntl(_new_socket, F_SETFL, O_NONBLOCK) < 0)
       		error("couldnt non block client socket");
        std::cout << "New connection , socket fd is " << _new_socket << " , ip is : " << inet_ntoa(_address.sin_addr) << " , port : " << ntohs(_address.sin_port) << std::endl;
		std::cout << "To register please, set the following commands : PASS NICK USER" << std::endl;
        std::vector<int>::iterator	it = _client_socket.begin();
        int i = 0;
        for (it = _client_socket.begin(); it != _client_socket.end(); ++it)
        {
            if(*it == 0) // add new user
            {
                *it = _new_socket;
                std::cout << "Adding to list of sockets as " << i << std::endl;
				User	*newUser = new User(_new_socket, inet_ntoa(_address.sin_addr), ntohs(_address.sin_port)); // socket client, addresse client, port client
				_users.push_back(newUser); // add new user au vector de user
				newUser->setJoined(true);
                break ;
            }
            i++;
        }
    }

    //IO operation
    it = _client_socket.begin();
    for (it = _client_socket.begin(); it != _client_socket.end(); ++it)
    {
        _sd = *it;
        if (FD_ISSET( _sd , &_readfds))
        {
            if ((_valread = read( _sd , _buffer, 1024)) == 0) // client disconnected
            {
                getpeername(_sd , (struct sockaddr*)&_address , (socklen_t*)&_addrlen);
                close( _sd );
                *it = 0;
				it = _client_socket.begin();
				removeUser(getUser(_sd));
            }
            else
            {
                std::cout << "command = [" << _buffer << ']' << std::endl;
				_buffer[_valread] = '\0';
				if (strchr(_buffer, '\n') && strncmp(_buffer, "\n", 1) != 0)
				{
					if (str.empty())
					{
						_operate->runCmd(getUser(_sd), _buffer);
						memset(_buffer, 0, 1025);
					}
					else
                	{
						str = str + _buffer;
						std::string tmp = str;
						str.clear();
						_operate->runCmd(getUser(_sd), tmp);
						memset(_buffer, 0, 1025);
					}
				}
				else if (strncmp(_buffer, "\n", 1) != 0)
					str = str + _buffer;
            }
        }
    }
    return;
}
