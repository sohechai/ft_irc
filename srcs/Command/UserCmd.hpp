#ifndef USERCMD_HPP
# define USERCMD_HPP
# include "../Command.hpp"

class UserCmd : public Command
{

public:
    UserCmd();
    virtual 	~UserCmd();

    void 		execute();
};

#endif