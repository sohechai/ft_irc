#include "User.hpp"

// CONSTRUCTOR

User::User(int socketFd, int port, std::string nickname) :	_socketFd(socketFd),
															_port(port),
															_nickname(nickname)
{
	return ;
}


User::User(int socketFd, char *host, int port) {
    _id = setId();
    _nickname = "";
    _host = host;
    _port = port;
    _socketFd = socketFd;
    _hasJoined = false;
    _isRegistered = false;
}

// DESTRUCTOR

User::~User() {
    return;
}

// ########################### GETTER ############################

std::string		User::getUserName() const {
    return (this->_username);
}

std::string 	User::getRealName() const {
    return (this->_realname);
}

std::string 	User::getNickName() const {
    return (this->_nickname);
}

std::string 	User::getHost() const {
    return (this->_host);
}

std::string 	User::getId() const {
    return (this->_id);
}

bool 			User::getRegistered() const
{
    return (this->_isRegistered);
}

bool 			User::getJoined() const {
    return (this->_hasJoined);
}

bool			User::getPass() const
{
	return (this->_pass);
}

int 			User::getSocketFd() const {
    return (this->_socketFd);
}

int 			User::getPort() const {
    return (this->_port);
}

bool			User::getOpRight() const
{
	return (this->_opRight);
}

void 			User::getResponse(std::string reply)
{
    std::string formatedReply = reply + "\r\n";

    send(this->_socketFd, formatedReply.c_str(), formatedReply.length(), 0);
    return;
}

void 			User::getResponseToFd(std::string reply, int fd)
{
    std::string formatedReply = reply + "\r\n";

    send(fd, formatedReply.c_str(), formatedReply.length(), 0);
    return;
}

std::string		User::getPrefix() const {
	return ":" + _nickname;
}

Channel * 		User::getChannel() const {
    return (_channel);
}

//AJOUT
bool            User::getAway() const
{
	return (this->_away);
}

// ############################### SETTER #############################

void			User::setPass(bool value)
{
	this->_pass = value;
}

void 			User::setUserName(std::string username)
{
    this->_username = username;
    return;
}

void 			User::setRealName(std::string realname)
{
    this->_realname = realname;
    return;
}

void 			User::setNickName(std::string nickname)
{
    this->_nickname = nickname; // nickname.substr(0, 9);
    return;
}

void            User::setHostName(std::string hostname)
{
	this->_host = hostname;
}


void 			User::setRegistered(bool value)
{
    this->_isRegistered = value;

    return;
}

void 			User::setJoined(bool joined)
{
    this->_hasJoined = joined;
    return;
}

void			User::setOpRight(bool value)
{
	this->_opRight = value;
}


std::string 	User::setId()
{
    std::string newId;
    static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";

    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        newId += alphanum[rand() % (sizeof(alphanum) -1)];
    }
    return (newId);
}

void 			User::setChannel(Channel *channel)
{
    _channel = channel;
}

// MSG

void 			User::clearMsg() {
    this->_msg.clear();
    return;
}

void 			User::sendMsg(User *user, std::string message)
{
    user->getResponse(this->getPrefix() + " " + message);
    return;
}

//AJOUT
void			User::setAway(bool away)
{
	_away = away;
}


void 			User::appendMsg(std::string message) {
    this->_msg.append(message);
    this->_msg.erase(this->_msg.find_last_not_of("\r\n") +1);
    this->_msg.append("\n");
    return;
}

// ############## CHANNEL #####################

void 			User::quitChannel() {
    if (_channel != nullptr)
        this->_channel->removeUser(this);
}

