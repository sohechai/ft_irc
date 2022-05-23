#ifndef USER_HPP
# define USER_HPP

class	User;

# include "utils/ircserv.hpp"
# include "Channel.hpp"

class User
{

public:
    User(int socketFd, int port, std::string nickname);
    User(int socketFd, char *host, int port);
    ~User();

    // GETTER

    std::string     getUserName() const;
    std::string     getRealName() const;
    std::string     getNickName() const;
    std::string     getHost() const;
    std::string     getId() const;
    std::string     getPrefix() const;
    bool            getRegistered() const;
    bool            getJoined() const;
	bool            getAway() const;
	bool			getOpRight() const;
	bool			getPass() const;
    int             getSocketFd() const;
    int             getPort() const;
    void            getResponse(std::string reply);
	void			getResponseToFd(std::string reply, int fd);
	Channel         *getChannel() const;

    // SETTER

    void            setUserName(std::string username);
    void            setRealName(std::string realname);
    void            setNickName(std::string nickname);
	void            setHostName(std::string hostname);
    void            setRegistered(bool value);
    void            setJoined(bool joined);
	void			setOpRight(bool value);
    std::string     setId();
    void            setChannel(Channel *channel);
	void			setAway(bool away);
	void			setPass(bool value);

    // MSG

    void            clearMsg();
    void            sendMsg(Channel* channel, std::string message);
    void            sendMsg(User* user, std::string message);
    void            appendMsg(std::string message);

    // CHANNEL

    void            quitChannel();

private:

    int         	_socketFd; // sera remplacer par un vector de int
    int         	_port;
    bool        	_isRegistered;
    bool        	_hasJoined;
    std::string 	_id;
    std::string 	_username;
    std::string 	_realname;
    std::string 	_nickname;
    std::string 	_host;
    std::string 	_msg;
	bool			_opRight;
	bool			_pass;

    Channel 		*_channel;

	bool			_away;

};


#endif
