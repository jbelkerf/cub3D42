/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:18 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/07 18:22:03 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	check_the_file_extention(char *file)
{
	int	name_lenght;

	name_lenght = ft_strlen(file);
	if (name_lenght <= 4)
	{
		ft_putendl_fd("file name not correct", 2);
		exit(1);
	}
	if (file[name_lenght - 1] != 'b' || file[name_lenght - 2] != 'u')
	{
		ft_putendl_fd("file name not correct", 2);
		exit(1);
	}
	if (file[name_lenght - 3] != 'c' || file[name_lenght - 4] != '.')
	{
		ft_putendl_fd("file name not correct", 2);
		exit(1);
	}
	if (file[name_lenght - 5] == '/')
	{
		ft_putendl_fd("file name not correct", 2);
		exit(1);
	}
}

void	check_the_file_readablity(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("file not exist or not readable", 2);
		close(fd);
		exit(1);
	}
	close(fd);
}

void	check_map_walls(char **map)
{
	int	x;
	int	y;
	
	y = 0;
	while (map[y])
	{
		x = 0;
	}
}

void	check_map_validity(char *file)
{
	char	**map;

	check_the_file_readablity(file);
	check_the_file_extention(file);
	check_map_header(file);
	map = map_to_str(file);
	check_map_walls(map);
}
