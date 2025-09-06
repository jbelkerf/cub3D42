/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:36:06 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:36:08 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define ORANGE  "\033[0;33m"
#define RESET   "\033[0m"

void	check_the_file_readablity(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	close(fd);
	if (fd == -1)
		put_error("file not exist or not readable", NULL);
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
				put_error("strange sybmol apeares", map);
			x++;
		}
		y++;
	}
	if (p != 1)
		put_error("invalid player number", map);
}

void	check_map_validity(char *file)
{
	char	**map;
	int		length;
	int		width;

	printf(GREEN "checking map's readablity...\n" RESET);
	check_the_file_readablity(file);
	printf(GREEN "done!\nchecking map's extention...\n" RESET);
	if (!check_the_file_extention(file, ".cub"))
		put_error("file name not correct", NULL);
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
