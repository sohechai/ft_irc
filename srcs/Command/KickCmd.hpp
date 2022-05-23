#ifndef KICKCMD_HPP
# define KICKCMD_HPP

# include "../Command.hpp"

class KickCmd : public Command {
public:
    KickCmd();
    virtual ~KickCmd();

    void    execute();
};


#endif
