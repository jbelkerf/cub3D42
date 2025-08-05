/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:SCALE:18 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/09 16:27:14 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define ORANGE  "\033[0;33m"
#define RESET   "\033[0m"

void	check_the_file_extention(char *file)
{
	int	name_lenght;

	name_lenght = ft_strlen(file);
	if (name_lenght <= 4)
		put_error("file name not correct");
	if (file[name_lenght - 1] != 'b' || file[name_lenght - 2] != 'u')
		put_error("file name not correct");
	if (file[name_lenght - 3] != 'c' || file[name_lenght - 4] != '.')
		put_error("file name not correct");
	if (file[name_lenght - 5] == '/')
		put_error("file name not correct");
}

void	check_the_file_readablity(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	close(fd);
	if (fd == -1)
		put_error("file not exist or not readable");
}

void	check_map_symbols(char **map)
{
	int		p;
	int		y;
	int		x;
	char	syb;

	p = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			syb = map[y][x];
			if (ft_strchr("NWSE", syb))
				p++;
			if (!ft_strchr("NWSE10 \n", syb))
			{
				free_arr(map);
				put_error("strange sybmol apeares");
			}
			x++;
		}
		y++;
	}
	if (p != 1)
	{
		free_arr(map);
		put_error("invalid player number");
	}
}

void	check_map_validity(char *file)
{
	char	**map;
	int		length;
	int		width;

	printf(GREEN "checking map's readablity...\n" RESET);
	check_the_file_readablity(file);
	printf(GREEN "done!\nchecking map's extention...\n" RESET);
	check_the_file_extention(file);
	printf(GREEN "done!\nchecking map's header...\n" RESET);
	check_map_header(file);
	printf(GREEN "done!\nchecking map's symbols...\n" RESET);
	map = map_to_str(file, &length, &width);
	check_map_symbols(map);
	printf(GREEN "done!\nchecking map's walls...\n" RESET);
	check_map_walls(map, length);
	printf(GREEN "done!\n" RESET);
	free_arr(map);
}
