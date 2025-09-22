SRCS = main.c utils.c ./parsing/parse.c ./parsing/find_map.c ./parsing/parse_cub.c move.c raycasting.c cleaners.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c

SRCS = main.c\
	   utils.c\
	   move.c\
	   ./parsing/read.c\
	   ./parsing/config_p1.c\
	   ./parsing/config_p2.c\
	   ./parsing/player.c\
	   ./parsing/map_find.c\
	   ./parsing/map_square.c\
	   ./parsing/map_parse.c\
	   ./raycasting/frame.c\
	   ./raycasting/init.c\
	   ./raycasting/dda.c\
	   ./raycasting/draw.c\
	   ./cleaners/free_utils.c\
	   ./cleaners/free_exit.c\
	   ./gnl/get_next_line.c\
	   ./gnl/get_next_line_utils.c

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f

LIB_DIR = ./libft
LIB		= $(LIB_DIR)/libft.a

MLX = ./mlx
MLXFLAGS = -L$(MLX) -lmlx -lXext -lX11 -lm

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(FLAGS) $(OBJS) $(LIB) $(MLXFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) clean

re: fclean all

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) ./mapas/error5.cub

.PHONY: all clean fclean re bonus