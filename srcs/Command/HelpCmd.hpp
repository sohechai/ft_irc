#ifndef HELPCMD_HPP
# define HELPCMD_HPP
# include "../Command.hpp"

class HelpCmd : public Command
{

public:
    HelpCmd(std::vector<Command*>&	commands);
    virtual 	~HelpCmd();

    void 		execute();

private:
	std::vector<Command*>& 			_commands;
};

#endif