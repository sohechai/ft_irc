#ifndef PRIVMSGCMD_HPP
# define PRIVMSGCMD_HPP
# include "../Command.hpp"

class PrivMsgCmd : public Command
{

public:
    PrivMsgCmd();
    virtual ~PrivMsgCmd();

    void 		    execute();
    //void            sendMsgToChann(Channel *channel, std::string message) const;
    User            *isUser();
    Channel         *isChannel();
    std::string     toString();
    void            clearArgs();
};

#endif