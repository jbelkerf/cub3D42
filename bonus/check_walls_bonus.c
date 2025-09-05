/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:41:24 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/09/05 15:12:12 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

void	check_map_walls(char **map, int length)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr2("0NEWSD", map[y][x]))
			{
				if (y == 0 || y == length - 1|| x == 0 || x == ft_strlen(map[y]))
					put_error("map not soronded", map);
				else if (!(ft_strchr2("0NEWS1D", map[y][x + 1])
					&& ft_strchr2("0NEWS1D", map[y][x - 1])
					&& ft_strchr2("0NEWS1D", map[y + 1][x])
					&& ft_strchr2("0NEWS1D", map[y - 1][x])))
					put_error("map not soronded", map);
			}
		}
	}
}

char	*skipi_abdsami3(int file_fd)
{
	char	*line;

	line = get_next_line(file_fd);
	if (!line)
		return (NULL);
	if (line[0] == '\n' && !line[1])
		return (free(line), skipi_abdsami3(file_fd));
	else
		return (line);
}
