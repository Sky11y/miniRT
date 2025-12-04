NAME		= miniRT
LIBMLX		= $(MLX_PATH)/build/libmlx42.a

FLAGS		= -Werror -Wall -Wextra -O3 -march=native
MLX42		= $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm

SRC_PATH	= src_bonus/
OBJ_PATH	= obj_bonus/
MLX_PATH	= ../lib/MLX42/
LIBFT_DIR	= ../lib/libft

HEADERS		= -I./inc_bonus -I./$(MLX_PATH)/include -I./$(LIBFT_DIR)

SRC			= main.c utils.c init.c setup.c render.c render_simple.c \
			  color.c update_hit.c \
			  sphere.c plane.c cylinder.c cylinder_cap.c light.c \
			  vector_math1.c vector_math2.c vector_math3.c \
			  input.c thread.c reflect_refract.c check_move.c \
			  parsing.c parsing_utils.c init_shapes.c \
			  init_ambient.c init_camera.c init_light.c \
			  init_plane.c init_sphere.c init_vectors.c init_cylinder.c \
			  init_shapes_utils.c init_shapes_utils2.c \
			  init_shapes_utils_bonus.c rt_cleanup.c \

OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)

LIBFT		= $(LIBFT_DIR)/libft.a

SRC_HEADER	= ./inc_bonus/mini_rt.h \
			  ./inc_bonus/shapes.h \
			  ./inc_bonus/scene_elements.h

all:		$(NAME)

$(NAME):	$(LIBMLX) $(OBJ_PATH) $(OBJ) $(LIBFT) $(SRC_HEADER)
			cc $(OBJ) $(MLX42) $(LIBFT) -o $@ -lm

$(LIBMLX):
			cmake $(MLX_PATH) -B $(MLX_PATH)/build
			make -C $(MLX_PATH)/build -j4

$(LIBFT):
			@make --no-print-directory -C $(LIBFT_DIR)
			
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

.PHONY:		all clean fclean re

