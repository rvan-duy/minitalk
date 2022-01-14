# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rvan-duy <rvan-duy@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/12 13:12:43 by rvan-duy      #+#    #+#                  #
#    Updated: 2022/01/14 12:50:48 by rvan-duy      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME_SERVER	= server
NAME_CLIENT = client
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
HEADER		= -I include

SRC_SERVER	= server.c
SRC_CLIENT	= client.c

LIBFT		= libft/libft.a

BOLD 		= \e[1m
RESET 		= \e[0m
LIGHT_GREEN = \e[92m
LIGHT_CYAN 	= \e[96m

SRCS_SERVER = $(addprefix src/, $(SRC_SERVER))
SRCS_CLIENT = $(addprefix src/, $(SRC_CLIENT))
OBJ_SERVER	= $(SRCS_SERVER:src/%.c=obj/%.o)
OBJ_CLIENT	= $(SRCS_CLIENT:src/%.c=obj/%.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@printf "${LIGHT_CYAN}${BOLD}make${RESET}   [${LIGHT_GREEN}${NAME_SERVER}${RESET}] : "
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@

$(NAME_SERVER): $(OBJ_SERVER)
	@make -C libft
	@$(CC) $(FLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)
	@printf "${LIGHT_CYAN}${BOLD}make${RESET}   [${LIGHT_GREEN}${NAME_SERVER}${RESET}] : "
	@printf "$(NAME_SERVER) created\n"

$(NAME_CLIENT): $(OBJ_CLIENT)
	@make -C libft
	@$(CC) $(FLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)
	@printf "${LIGHT_CYAN}${BOLD}make${RESET}   [${LIGHT_GREEN}${NAME_CLIENT}${RESET}] : "
	@printf "$(NAME_CLIENT) created\n"

clean:
	@printf "${LIGHT_CYAN}${BOLD}clean${RESET}  [${LIGHT_GREEN}${NAME_SERVER} ${NAME_CLIENT}${RESET}] : "
	/bin/rm -rf obj
	@make -C libft clean

fclean: clean
	@printf "${LIGHT_CYAN}${BOLD}fclean${RESET} [${LIGHT_GREEN}${NAME_SERVER}${RESET}] : "
	/bin/rm -f $(NAME_SERVER)
	@printf "${LIGHT_CYAN}${BOLD}fclean${RESET} [${LIGHT_GREEN}${NAME_CLIENT}${RESET}] : "
	/bin/rm -f $(NAME_CLIENT)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re