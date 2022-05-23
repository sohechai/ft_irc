#ifndef PASSCMD_HPP
# define PASSCMD_HPP
# include "../Command.hpp"

class PassCmd : public Command
{

public:
    PassCmd();
    virtual 	~PassCmd();

    void 		execute();
};

#endif