#ifndef JOINCMD_HPP
#define JOINCMD_HPP

# include "../Command.hpp"

class JoinCmd : public Command
{

public:
    JoinCmd();
    virtual ~JoinCmd();

    void 		execute();
    void 		sendInfoToChan(Channel* channel, std::string message) const;

};

#endif
