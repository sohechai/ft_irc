#ifndef LISTCMD_HPP
# define LISTCMD_HPP

# include "../Command.hpp"

class ListCmd : public Command {
public:
    ListCmd();
    virtual ~ListCmd();

    void    execute();
};


#endif
