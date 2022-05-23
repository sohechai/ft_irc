#ifndef SERVER_HPP
# define SERVER_HPP

class		Server;


# include "User.hpp"
# include "Channel.hpp"
# include "Operate.hpp"
# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <vector>
# include <cerrno>
# include <memory>
# include <cstring>
# include <string>
# include <csignal>
# include <fstream>


class		Server
{

public:

    Server();
    ~Server();


	Channel						*getChannel(std::string name);
	std::vector<Channel *>      getChannels();
	Channel                 	*createChannel(std::string name, User *admin);
    void                    	deleteChannel(Channel *channel);
	std::string					get_password() const;
	std::string					getHost() const;
    int							get_max_clients() const;
	void						init_clients();
    int         				get_server_socket() const;
	User						*getUser(int client_socket);
	User                        *getUser(std::string userName);
	User                        *getUserId(std::string id);
    void						error(std::string str_error);
    void						create_server_socket(int port);
    void        				start(std::string host, int port, std::string password);
    void        				loop();
    std::vector<int>			_client_socket;
    void                        removeUser(User *user);


private:

    struct sockaddr_in			_address;
    int 						_opt;
    int 						_server_socket;
    int							_addrlen;
    int							_new_socket;
    int							_activity;
    int							_valread;
    int							_sd;
    int							_max_sd;
    char 						_buffer[1025];  //data buffer de 1K
	std::string					_password;
	std::string					_host;
    fd_set 						_readfds;
	int							_max_clients;
	std::vector<User *>			_users;
	std::vector<Channel *>		_channels;
	Operate						*_operate;

	std::string					str;
};

#endif

