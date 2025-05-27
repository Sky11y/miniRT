# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 15:25:30 by jpiensal          #+#    #+#              #
#    Updated: 2025/05/19 15:35:34 by jpiensal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minirt

FLAGS		= -Werror -Wall -Wextra -g

SRC_PATH	= src/
OBJ_PATH	= obj/

SRC			= main.c mini_rt_utils.c
OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)
HEADER		= ./mini_rt.h

all:		$(NAME)

$(NAME):	$(OBJ_PATH) $(OBJ) $(HEADER)
			cc $(OBJ) -o $@ -lm

$(OBJ):		$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			cc $(FLAGS) -c $< -o $@ -I.

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			rm -rf $(OBJ) $(OBJ_PATH)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re $(NAME)

