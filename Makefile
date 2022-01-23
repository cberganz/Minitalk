
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 14:42:18 by cberganz          #+#    #+#              #
#    Updated: 2022/01/22 15:16:42 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER		= server
NAME_CLIENT		= client
NAME_SERVER_B	= server_bonus
NAME_CLIENT_B	= client_bonus

INCLUDE			= include/

HEADER			= $(INCLUDE)minitalk.h

CC				= clang

CFLAGS			= -Wall -Wextra -Werror

SRC_S			= server.c			\
				  receive.c			\
				  utils.c

SRC_C			= client.c			\
				  send.c

SRC_S_BONUS		= server_bonus.c	\
				  receive_bonus.c	\
				  send_bonus.c		\
				  utils_bonus.c

SRC_C_BONUS		= client_bonus.c	\
				  send_bonus.c

SRC_DIR			= src/
SRC_SERVER		= $(addprefix $(SRC_DIR), $(SRC_S))
SRC_CLIENT		= $(addprefix $(SRC_DIR), $(SRC_C))

OBJ_DIR			= objs/
OBJ_DIRS		= $(sort $(dir $(OBJ_SERVER)$(OBJ_CLIENT)))
OBJ_S			= $(SRC_S:.c=.o)
OBJ_C			= $(SRC_C:.c=.o)
OBJ_SERVER		= $(addprefix $(OBJ_DIR), $(OBJ_S))
OBJ_CLIENT		= $(addprefix $(OBJ_DIR), $(OBJ_C))

SRC_BONUS_DIR	= src_bonus/
SRC_BONUS_SERVER= $(addprefix $(SRC_BONUS_DIR), $(SRC_S_BONUS))
SRC_BONUS_CLIENT= $(addprefix $(SRC_BONUS_DIR), $(SRC_C_BONUS))

OBJ_BONUS_DIR	= objs_bonus/
OBJ_BONUS_DIRS	= $(sort $(dir $(OBJ_BONUS_SERVER)$(OBJ_BONUS_CLIENT)))
OBJ_S_BONUS		= $(SRC_S_BONUS:.c=.o)
OBJ_C_BONUS		= $(SRC_C_BONUS:.c=.o)
OBJ_BONUS_SERVER= $(addprefix $(OBJ_BONUS_DIR), $(OBJ_S_BONUS))
OBJ_BONUS_CLIENT= $(addprefix $(OBJ_BONUS_DIR), $(OBJ_C_BONUS))

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	@make -sC ./libft/
	$(CC) $(CFLAGS) -L./libft $(OBJ_SERVER) -lft -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	@make -sC ./libft/
	$(CC) $(CFLAGS) -L./libft $(OBJ_CLIENT) -lft -o $(NAME_CLIENT)

bonus: $(NAME_SERVER_B) $(NAME_CLIENT_B)

$(NAME_SERVER_B): $(OBJ_BONUS_SERVER)
	@make -sC ./libft/
	$(CC) $(CFLAGS) -L./libft $(OBJ_BONUS_SERVER) -lft -o $(NAME_SERVER_B)

$(NAME_CLIENT_B): $(OBJ_BONUS_CLIENT)
	@make -sC ./libft/
	$(CC) $(CFLAGS) -L./libft $(OBJ_BONUS_CLIENT) -lft -o $(NAME_CLIENT_B)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ_BONUS_DIRS):
	mkdir -p $@

$(OBJ_SERVER): | $(OBJ_DIRS)
$(OBJ_BONUS_SERVER): | $(OBJ_BONUS_DIRS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@make clean -sC ./libft/
	rm -rf ${OBJ_DIR}
	rm -rf ${OBJ_BONUS_DIR}

fclean: clean
	@make fclean -sC ./libft/
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_SERVER_B)
	rm -f $(NAME_CLIENT_B)

re: fclean all

.PHONY : all clean fclean re
