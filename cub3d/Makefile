NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

# SAN = -fsanitize=address -g3

# MLX = -lmlx -framework OpenGL -framework AppKit

LINUX = -Lminilibx-linux -lmlx_Linux -lXext -lX11  -lXext -lX11 -lm

SRC = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	ft_utils.c ft_split.c cub3d.c  ft_texture.c moving.c raycasting.c mini_map.c \
	next_cub3d.c next_texture.c next_utils.c next_main.c next1_main.c \
	next2_main.c  next3_main.c next_moving.c ft_spaces.c ft_next_norm.c


OBJ_BONUS = $(SRC_BONUS:.c=.o)

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINUX)  $(MLX)  -o $(NAME)

clean :
	rm -f $(OBJ)

fclean :
	rm -rf $(NAME) $(OBJ)

re : fclean all


.PHONY : all clean fclean re