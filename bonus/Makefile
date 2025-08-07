NAME		= miniRT
LIBMLX		= $(MLX_PATH)/build/libmlx42.a

FLAGS		= -Werror -Wall -Wextra -O3 -march=native -g
MLX42		= $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm

SRC_PATH	= src_bonus/
OBJ_PATH	= obj_bonus/
MLX_PATH	= ../lib/MLX42/

HEADERS		= -I./inc_bonus -I./$(MLX_PATH)/include

SRC			= main.c utils.c init.c setup.c render.c color.c update_hit.c\
			  sphere.c plane.c cylinder.c cylinder_cap.c light.c \
			  vector_math1.c vector_math2.c vector_math3.c \
			  random.c input.c
OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)

SRC_HEADER	= ./inc_bonus/mini_rt.h \
			  ./inc_bonus/shapes.h \
			  ./inc_bonus/scene_elements.h

all:		$(NAME)

$(NAME):	$(LIBMLX) $(OBJ_PATH) $(OBJ) $(SRC_HEADER)
			cc $(OBJ) $(MLX42) -o $@ -lm

$(LIBMLX):
			cmake $(MLX_PATH) -B $(MLX_PATH)/build
			make -C $(MLX_PATH)/build -j4

$(LIBFT):
			make all -C ./libft
			
$(OBJ):		$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			cc $(FLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			rm -rf $(OBJ) $(OBJ_PATH)

fclean:		clean
			rm -rf $(NAME)
			rm -rf $(MLX_PATH)/build
			#rm -rf $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re

