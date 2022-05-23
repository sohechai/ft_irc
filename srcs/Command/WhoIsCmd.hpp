#ifndef WHOISCMD_HPP
# define WHOISCMD_HPP
# include "../Command.hpp"

class WhoIsCmd : public Command
{

public:
    WhoIsCmd();
    virtual 	~WhoIsCmd();

    void 		execute();
};

#endif