NAME=cub3D

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRC= gnl/get_next_line.c gnl/get_next_line_utils.c cube.c map_validity.c

$(NAME): $(SRC)
	make -C Libft
	$(CC) $(CFLAGS) $(SRC) Libft/libft.a -o $(NAME)