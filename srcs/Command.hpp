#ifndef COMMAND_HPP
# define COMMAND_HPP

class	Command;

# include "Server.hpp"
# include "Channel.hpp"
# include "User.hpp"
# include "utils/ircserv.hpp"

// liste commandes irc weechat : https://www.linode.com/docs/guides/using-weechat-for-irc/

class Command
{

public:

    Command();
    virtual ~Command();

    std::string             getName() const;
    std::string             getDescription() const;
	std::string				getCommand() const;

    void                    setSender(User* sender);
    void                    setServer(Server* server);
    void                    setArgs(std::deque<std::string> args);
	void                    setCommand(std::string command);

    virtual void            execute() = 0;

protected:
    std::string             _name;
    std::string             _description;
	std::string				_command;
    Server                 	*_server;
    User					*_sender;
	Channel					*_channel;
    std::deque<std::string> _args;
};


#endif
