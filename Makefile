NAME			= 		ircserv

SRC				=		./main.cpp						\
						./srcs/Server.cpp				\
						./srcs/User.cpp					\
						./srcs/Operate.cpp				\
						./srcs/Command.cpp				\
						./srcs/Channel.cpp				\
						./srcs/Command/HelpCmd.cpp		\
						./srcs/Command/QuitCmd.cpp		\
						./srcs/Command/NickCmd.cpp		\
						./srcs/Command/WhoIsCmd.cpp		\
						./srcs/Command/PrivMsgCmd.cpp	\
						./srcs/Command/JoinCmd.cpp		\
						./srcs/Command/UserCmd.cpp		\
						./srcs/Command/KickCmd.cpp		\
						./srcs/Command/PartCmd.cpp		\
						./srcs/Command/ListCmd.cpp		\
						./srcs/Command/WhoCmd.cpp		\
						./srcs/Command/PassCmd.cpp


OBJ				=       $(SRC:.cpp=.o)

FLAGS			=      -Wall -Wextra -Werror

RM				=		rm -rf

all: $(NAME)

%.o: %.cpp
		clang++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
		clang++ $(FLAGS) $(OBJ) -o $(NAME)

clean:
		@${RM} ${OBJ}
		@echo "\033[91m\n./$(NAME) and *.o have been deleted\n\n$(NAME) is now clean"

fclean: clean
		@${RM} ${NAME}

re: fclean all

.PHONY: all clean flclean re