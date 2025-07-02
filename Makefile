NAME		= miniRT

FLAGS		= -Werror -Wall -Wextra -g

SRC_PATH	= src/
OBJ_PATH	= obj/
HEADERS		= -I./inc

SRC			= main.c mini_rt_utils.c utils.c init.c render.c
OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)

SRC_HEADER	= ./inc/mini_rt.h ./inc/shapes.h ./inc/scene_elements.h

all:		$(NAME)

$(NAME):	$(OBJ_PATH) $(OBJ) $(SRC_HEADER)
			cc $(OBJ) -o $@ -lm

$(OBJ):		$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			cc $(FLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			rm -rf $(OBJ) $(OBJ_PATH)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

run:		all
			./run.sh

.PHONY:		all clean fclean re

