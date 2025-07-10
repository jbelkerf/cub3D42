NAME=cub3D

CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g

SRC= gnl/get_next_line.c gnl/get_next_line_utils.c \
	src/cube.c src/map_validity.c src/free_resource.c \
	src/map_to_table.c src/check_map_header.c  src/errors.c\
	src/check_walls.c src/fill_the_data.c

all: $(NAME)
$(NAME): $(SRC)
	make -C Libft
	$(CC) $(CFLAGS) $(SRC) Libft/libft.a -o $(NAME)

clean:
	make clean -C Libft

fclean:
	make fclean -C Libft
	rm -f $(NAME)
redo: fclean all