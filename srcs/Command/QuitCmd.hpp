#ifndef QUITCMD_HPP
# define QUITCMD_HPP
# include "../Command.hpp"

class QuitCmd : public Command
{

public:
    QuitCmd();
    virtual 	~QuitCmd();

    void 		execute();
};

#endif