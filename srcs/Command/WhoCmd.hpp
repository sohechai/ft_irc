#ifndef WHOCMD_HPP
# define WHOCMD_HPP

# include "../Command.hpp"

class WhoCmd : public Command {
public:
    WhoCmd();
    virtual ~WhoCmd();

    void    execute();
};


#endif
