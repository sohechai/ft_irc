#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class	Channel;

# include "utils/ircserv.hpp"
# include "User.hpp"
# include "Server.hpp"
# include <stdlib.h>

bool    checkChannelName(std::string name);

class Channel
{

    public:
        Channel(std::string name, int adminfd, Server *server); //         Channel(std::string name, User* admin, Server *server); pour multi chann
        ~Channel();

        // GETTER

        std::string         getName() const;
        User                *getAdmin() const;
        User                *getUser(std::string userName) const;
        std::vector<User *>	getUsers() const;
		int					getNbOfUser() const;


        // SETTER

        void                setName(std::string name);

        // User management

        void                addUser(User *user);
        void                removeUser(User *user);
        bool                isUser(User *user) const;

        // Message management in the channel

		void				sendMsgToUsers(User *sender, std::string message, std::string cmd);
        void                sendMsgToChan(User *sender, std::string message, std::string cmd);

    private:
        std::string         _name;
        int                 _adminfd;
        Server*             _server; // pour multi channel
        std::vector<User *>	_usersinchann;

};


#endif
