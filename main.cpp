#include "srcs/utils/ircserv.hpp"
#include "srcs/Server.hpp"
#include <cstdio>


int main(int argc , char **argv)
{
	Server			server;

	if (argc < 2 && argc > 3)
	{
		std::cout << "Error arguments.\r\nCorrect usage: \"./ircserv [host:port:password] <port> <password>\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if (argc == 3)
		server.start("127.0.0.1", std::atoi(argv[1]), argv[2]);
	else
	{
		std::vector<std::string>    result;
		std::stringstream           ss(argv[1]);
		std::string                 token;

		while (std::getline(ss, token, ':'))
			if (!token.empty())
				result.push_back(token);

		if (result.size() != 3)
			throw std::runtime_error("Error arguments.\r\nCorrect usage: ./ircserv [host:port:password] <port> <password>");

		const char *av = result[1].c_str();
		server.start(result[0], std::atoi(av), result[2]);
	}

    return (0);
}
