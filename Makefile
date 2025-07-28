NAME		= miniRT

FLAGS		= -Werror -Wall -Wextra -O3

SRC_PATH	= src/
OBJ_PATH	= obj/
HEADERS		= -I./inc -I./libft

SRC			= main.c utils.c init.c render.c update_hit.c\
			  sphere.c plane.c cylinder.c cylinder_cap.c light.c \
			  vector_math1.c vector_math2.c vector_math3.c \
			  parsing.c parsing_utils.c init_shapes.c \
			  init_ambient.c init_shapes_utils.c init_plane.c

OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_HEADER	= ./inc/mini_rt.h ./inc/shapes.h ./inc/scene_elements.h

all:		$(NAME)

debug:		FLAGS:=$(FLAGS) -g
debug:		re

sanitize:	FLAGS:=$(FLAGS) -g -fsanitize=address -fsanitize=leak -fsanitize=leak
sanitize:	re

$(LIBFT):
			make --no-print-directory -C $(LIBFT_DIR)

$(NAME):	$(OBJ_PATH) $(OBJ) $(LIBFT) $(SRC_HEADER)
			cc $(OBJ) $(LIBFT) -o $@ -lm

$(OBJ):		$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIBFT_DIR)/libft.h
			cc $(FLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			rm -rf $(OBJ) $(OBJ_PATH)
			make fclean --no-print-directory -C $(LIBFT_DIR)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

run:		all
			./run.sh

.PHONY:		all clean fclean re debug sanitize
