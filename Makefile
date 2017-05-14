DEBUG		=		no

NAME		=		server

SRC_DIR		=		./src/

SRC			=		command_cwd.c 		\
					command_delete.c	\
					command_error.c		\
					command_help.c		\
					command_list.c		\
					command_noop.c		\
					command_pasv.c		\
					command_port.c		\
					command_retr.c		\
					command_stor.c		\
					command_user.c		\
					command_quit.c		\
					command_syst.c		\
					command_pwd.c		\
					get_command.c		\
					raw_command.c		\
					server.c		\
					server_init.c		\
					server_listener.c	\
					server_logic.c		\
					server_tools.c		\
					replies.c

SRCS		= 		$(addprefix $(SRC_DIR), $(SRC))

OBJ			=		$(SRCS:.c=.o)

INCLUDE		=		-I./include

CC			=		gcc

CFLAGS		=		-W -Wall -Wextra -Werror $(INCLUDE)

ifeq ($(DEBUG),yes)
CFLAGS		+=		-g3
endif

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDE)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
