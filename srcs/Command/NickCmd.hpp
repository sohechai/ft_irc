#ifndef NICKCMD_HPP
# define NICKCMD_HPP
# include "../Command.hpp"

class NickCmd : public Command
{

public:
    NickCmd();
    virtual 	~NickCmd();

    void 		execute();
};

#endif