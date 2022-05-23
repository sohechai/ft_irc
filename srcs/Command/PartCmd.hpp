#ifndef PARTCMD_HPP
#define PARTCMD_HPP

# include "../Command.hpp"

class PartCmd : public Command {

public:
    PartCmd();
    virtual ~PartCmd();

    void execute();
    void sendInfoToChan(Channel* channel, std::string message) const;
};


#endif
