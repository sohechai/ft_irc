#ifndef IRCSERV_HPP
# define IRCSERV_HPP

# include <iostream>
# include <string>
# include <stdexcept>       // expection throw std::runtime_error
# include <vector>
# include <deque>
# include <sstream>

# include <poll.h>          // poll() | struct pollfd{int fd, short events, short revents}
# include <unistd.h>        // select()
# include <sys/types.h>     // send() getaddrinfo()
# include <sys/socket.h>    // send() getaddrinfo()
# include <netdb.h>         // getaddrinfo()
# include <fcntl.h>         // fcntl() -> fd operation
# include <stdio.h>         // memset()
# include <string.h>        // memset()

#define RPL_WELCOME(nickname, username, host)   	"001 * " + nickname + " Welcome to the Internet Relay Network " + nickname + "!" + username + "@" + host
#define RPL_LIST(channel, usersCount)				("322 * #" + channel + " " + usersCount)
#define RPL_LISTEND									"323 * :End of LIST"
#define RPL_WHOISUSER(pseudo, user, host, realname)	"311 * " + pseudo + " " + user + " " + host + " * :" + realname
#define RPL_NONE(str)								"300 * " + str

// ERRORS
# define ERR_NEEDMOREPARAMS(command)				("461 * " + command + " : Not enough parameters")
# define ERR_ALREADYREGISTRED						"462 * :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH							"464 * :Password incorrect"
# define ERR_NICKNAMEINUSE(nick)					("433 * " + nick + " :Nickname is already in use")
# define ERR_RESTRICTED								"484 * :Your connection is restricted!"
# define ERR_NOTONCHANNEL(channel)					("442 * " + channel + " :You're not on that channel")
# define ERR_NOSUCHCHANNEL(channel)					("403 * #" + channel + " :No such channel")
# define ERR_CHANOPRIVSNEEDED(channel)				("482 * #" + channel + " :You're not channel operator")
# define ERR_USERNOTINCHANNEL(nick, channel)		("441 * " + nick + " #" + channel + " :They aren't on that channel")
# define ERR_BADCHANMASK(channel)					("476 * #" + channel + " :Bad Channel Mask")
# define ERR_NOSUCHNICK(nick)						("401 * " + nick + " :No such nick/channel")
# define ERR_NONICKNAMEGIVEN						"431 * :No nickname given"
# define ERR_NOTEXTTOSEND							"412 * :No text to send"

#endif
