/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:35:22 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:35:23 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
			if (ft_strchr2("0NEWS", map[y][x]))
			{
				if (y == 0 || y == length || x == 0 || x == ft_strlen(map[y]))
				{
					put_error("map not soronded", map);
				}
				else if (!(ft_strchr2("0NEWS1", map[y][x + 1])
					&& ft_strchr2("0NEWS1", map[y][x - 1])
						&& ft_strchr2("0NEWS1", map[y + 1][x])
						&& ft_strchr2("0NEWS1", map[y - 1][x])))
					put_error("map not soronded", map);
			}
		}
	}
}
