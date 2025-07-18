NAME=cub3D

OS:=$(shell uname -s)
ifeq ($(OS),Darwin)
	LFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -L ~/.brew/opt/glfw/lib -l glfw3
else
	LFLAGS := -glfw
endif

RED=\033[0;31m
GRN=\033[0;32m
YEL=\033[1;33m
ORA= \033[38;5;208m
RESET=\033[0m

CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g
MLX=./MLX42/build/libmlx42.a

SRC= gnl/get_next_line.c gnl/get_next_line_utils.c \
	src/cube.c src/map_validity.c src/free_resource.c \
	src/map_to_table.c src/check_map_header.c  src/errors.c\
	src/check_walls.c src/fill_the_data.c

all: $(NAME)
$(NAME): $(SRC)
	@make -C Libft
	@echo "$(ORA)  _______           ______   ______   ______  $(RESET)"
	@echo "$(ORA) (  ____ \|\     /|(  ___ \ / ___  \ (  __  \ $(RESET)"
	@echo "$(ORA) | (    \/| )   ( || (   ) )\/   \  \| (  \  )$(RESET)"
	@echo "$(ORA) | |      | |   | || (__/ /    ___) /| |   ) |$(RESET)"
	@echo "$(ORA) | |      | |   | ||  __ (    (___ ( | |   | |$(RESET)"
	@echo "$(ORA) | |      | |   | || (  \ \       ) \| |   ) |$(RESET)"
	@echo "$(ORA) | (____/\| (___) || )___) )/\___/  /| (__/  )$(RESET)"
	@echo "$(ORA) (_______/(_______)|/ \___/ \______/ (______/ $(RESET)"
                                                   

	@if find . -name "libmlx42.a" | grep -q .;then\
		echo "$(GRN)mlx exist$(RESET)";\
	else\
		echo "$(YEL)MLX42 not found, setuping it...$(RESET)";\
		rm -rf MLX42;\
		git clone https://github.com/codam-coding-college/MLX42.git ;\
		cd MLX42 && cmake -B build && cmake --build build;\
		cd -;\
		fi
	
	$(CC) $(CFLAGS) $(SRC) Libft/libft.a $(MLX) $(LFLAGS) -o $(NAME)

clean:
	make clean -C Libft

fclean:
	make fclean -C Libft
	rm -f $(NAME)
redo: fclean all