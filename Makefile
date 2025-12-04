NAME		= miniRT
LIBMLX		= $(MLX_PATH)/build/libmlx42.a

FLAGS		= -Werror -Wall -Wextra -O3
MLX42		= $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm

SRC_PATH	= src/
OBJ_PATH	= obj/
MLX_PATH	= lib/MLX42/

HEADERS		= -I./inc -I./$(MLX_PATH)/include -I./lib/libft

SRC			= main.c utils.c init.c render.c update_hit.c\
			  sphere.c plane.c cylinder.c cylinder_cap.c light.c \
			  vector_math1.c vector_math2.c vector_math3.c \
			  parsing.c parsing_utils.c init_shapes.c \
			  init_ambient.c init_camera.c init_light.c \
			  init_plane.c init_sphere.c init_vectors.c init_cylinder.c \
			  init_shapes_utils.c init_shapes_utils2.c rt_cleanup.c \
			  events.c
OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)

LIBFT_DIR	= ./lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_HEADER	= ./inc/mini_rt.h ./inc/shapes.h ./inc/scene_elements.h

all:		$(NAME)


$(NAME):	$(LIBMLX) $(OBJ_PATH) $(OBJ) $(LIBFT) $(SRC_HEADER)
			cc $(OBJ) $(MLX42) $(LIBFT) -o $@ -lm

$(LIBMLX):
			cmake $(MLX_PATH) -B $(MLX_PATH)/build
			make -C $(MLX_PATH)/build -j4

debug:		FLAGS:=$(FLAGS) -g
debug:		re

sanitize:	FLAGS:=$(FLAGS) -g -fsanitize=address -fsanitize=undefined -fsanitize=leak
sanitize:	re

$(LIBFT):
			make --no-print-directory -C $(LIBFT_DIR)

$(OBJ):		$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIBFT_DIR)/libft.h
			cc $(FLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			rm -rf $(OBJ_PATH)
			make clean --no-print-directory -C $(LIBFT_DIR)

fclean:		clean
			rm -rf $(NAME)
			rm -rf $(MLX_PATH)/build
			make fclean --no-print-directory -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re debug sanitize
